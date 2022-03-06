/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#include "OdaCommon.h"
#include "BrepBuilderFillerModule.h"
#include "BrepBuilderInitialData.h"
#include "IMaterialAndColorHelper.h"
// br
#include "Br/BrBrep.h"
#include "Br/BrComplex.h"
#include "Br/BrShell.h"
#include "Br/BrFace.h"
#include "Br/BrLoop.h"
#include "Br/BrEdge.h"
#include "Br/BrBrepComplexTraverser.h"
#include "Br/BrComplexShellTraverser.h"
#include "Br/BrShellFaceTraverser.h"
#include "Br/BrFaceLoopTraverser.h"
#include "Br/BrLoopEdgeTraverser.h"
#include "Br/BrLoopVertexTraverser.h"
#include "Br/BrBrepFaceTraverser.h"
// bb
#include "BrepBuilder/BrepBuilder.h"
// ge
#include "Ge/GeExt.h"
#include "Ge/GePoint3d.h"
#include "Ge/GePoint2d.h"
#include "Ge/GeExtents2d.h"
#include "Ge/GePoint2dArray.h"
// curve
#include "Ge/GeCurve2d.h"
#include "Ge/GeLineSeg2d.h"
#include "Ge/GeLineSeg3d.h"
#include "Ge/GeCircArc3d.h"
#include "Ge/GeEllipArc3d.h"
#include "Ge/GeNurbCurve2d.h"
#include "Ge/GeNurbCurve3d.h"
#include "Ge/GeExternalCurve3d.h"
// surf
#include "Ge/GeEllipCone.h"
#include "Ge/GeEllipCylinder.h"
#include "Ge/GeExternalSurface.h"
#include "Ge/GeExternalBoundedSurface.h"
// stl
#define STL_USING_VECTOR
#define STL_USING_ALGORITHM
#define STL_USING_UTILITY
#define STL_USING_SET
#define STL_USING_LIMITS
#include "OdaSTL.h"
//
#include "OdHashSet.h"
#include "OdHashMap.h"
#include "TPtr.h"
typedef TPtr< OdGeCurve3d, TObjDelete<OdGeCurve3d> > OdGeTempCurve3dPtr;
typedef TPtr< OdGeCurve2d, TObjDelete<OdGeCurve2d> > OdGeTempCurve2dPtr;
typedef TPtr< OdGeNurbCurve3d, TObjDelete<OdGeNurbCurve3d> > OdGeTempNurbCurve3dPtr;
typedef TPtr< OdGeNurbCurve2d, TObjDelete<OdGeNurbCurve2d> > OdGeTempNurbCurve2dPtr;
typedef TPtr< OdGeSurface, TObjDelete<OdGeSurface> > OdGeTempSurfacePtr;
#ifdef OD_DBG_SEE_THE_INVISIBLE
# include "GeInvisible.h"
#endif

// Helper functions
class OdBrepBuilderFillerHelper
{
  BrepBuilderInitialData& m_initialData;

  OdIMaterialAndColorHelper* m_pMaterialHelper;
  const OdBrepBuilderFillerParams& m_params;

  OdHashMap<OdUInt64, OdUInt32> m_edges;
  OdHashMap<OdUInt64, OdUInt32> m_vertices;

  double m_toleranceInterval;
  double m_toleranceDiffPoints;
  double m_toleranceRestore2dCurve;
  double m_toleranceCoincide;
  bool m_loopsSplitted;

  //TODO: unordered_set
  //for OdHashSet: error /usr/include/c++/5/backward/hashtable.h:609:31: error:
  //no match for call to (const hasher {aka const _gnu_cxx::hash}) (const OdGeCurve3d* const&) { return M_hash(__key) % __n; }
  mutable std::set<const OdGeCurve3d*> m_edgeCurveChanged;// true if edge curve was fixed => required to update coedge curve

  // Structure for addFaceExplicitLoop
  struct EdgeCurveCompareData
  {
    const OdGeCurve3d* pCurve;
    const OdUInt32 idEdge;
    const OdGePoint3dArray aSamplePts;
    double dDist;

    EdgeCurveCompareData(const double distance = 0.0)
      : pCurve(NULL), idEdge(0), dDist(distance)
    {}

    EdgeCurveCompareData(const OdGeCurve3d* curve, const OdUInt32 id, const OdGePoint3dArray& points, const double distance)
      : pCurve(curve), idEdge(id), aSamplePts(points), dDist(distance)
    {}

    bool operator<(const EdgeCurveCompareData& other) const { return dDist < other.dDist; }
  };

  // Field for addFaceExplicitLoop
  std::multiset<EdgeCurveCompareData> m_edgesAdded;

public:
  static inline OdResult checkRet(OdResult status)
  {
#ifdef ODA_DIAGNOSTICS
    if (eOk != status) {
      return status;
    }
#endif
    return status;
  }

  static inline void assertGsMarkerValue(OdGsMarker marker)
  {
    ODA_ASSERT_ONCE(marker >= 0 && marker <= UINT_MAX);
  }

  explicit OdBrepBuilderFillerHelper(
    BrepBuilderInitialData& initialData,
    const OdBrepBuilderFiller& filler,
    OdIMaterialAndColorHelper* pMaterialHelper = NULL
  )
    : m_initialData(initialData)
    , m_pMaterialHelper(pMaterialHelper)
    , m_params(filler.params())
    , m_toleranceInterval(1e-9)// double d2dParamTol = 1e-9;//TODO: possible investigation needed
    , m_toleranceDiffPoints(1e-3)
    , m_toleranceRestore2dCurve(1e-6)
    , m_toleranceCoincide(1e-6)
  {}

  // Interval
  /** \details
    Test that scndInt interval is part of frstInt.
  */
  bool isIntervalContain(const OdGeInterval& frstInt, const OdGeInterval& scndInt) const;
  /** \details
    Test that scndInt interval is part of reversed frstInt.
  */
  bool isIntervalContainReversed(const OdGeInterval& frstInt, const OdGeInterval& scndInt) const;
  bool needParamCurves() const;

  // Edge
  enum FixCurveStatus { eSuccess, eSkip, eFail };
  OdGeCurve3dPtr getEdgeCurve(const OdBrEdge& edge) const;
  bool fixEllipse(OdGeCurve3dPtr& pCurve, const OdBrEdge& edge) const;
  bool fixCircle(OdGeCurve3dPtr& pCurve, const OdBrEdge& edge) const;
  void fixEllipseRadiusRatio(OdGeCurve3d* pCurve) const;
  bool fixNurb(OdGeCurve3dPtr& pCurve, const OdBrEdge& edge) const;
  OdResult getEdgeCurveFixed(const OdBrEdge& edge, OdGeCurve3dPtr& pCurve) const;
  FixCurveStatus getCurveParams(const OdBrEdge& edge, const OdGeCurve3d* pCurve, OdGePoint3d& pntStart, OdGePoint3d& pntEnd, OdGeInterval& interval) const;
  void setArcInterval(OdGeCurve3d* pCurve, OdGeInterval& interval, OdGePoint3d& pntStart, OdGePoint3d& center, OdGeVector3d& major, OdGeVector3d& normal) const;

  // Coedge
  OdGeCurve2dPtr getParamCurve(const OdBrLoopEdgeTraverser& loEdTrav) const;
  OdResult checkNurb2dFor3d(const OdGeSurface* pSurf, const OdGeCurve3d* pCurve3d, OdGeCurve2d* pCurve2d) const;
  OdResult checkCurve2dFor3d(const OdGeSurface* pSurf, const OdGeCurve3d* pCurve3d, OdGeCurve2d* pCurve2d) const;
  void moveParamCurveNurbInterval(const OdGeSurface* pSurf, const OdGeCurve3d* pCurve3d, OdGeCurve2d* pCurve2d) const;
  OdResult moveParamCurveInterval(const OdGeSurface* pSurf, const OdGeCurve3d* pCurve3d, OdGeCurve2d* pCurve2d) const;
  void moveParamIntoExtents(const OdGeSurface* pSurf, const OdGeCurve2d* pCurve2d, OdGePoint2d &pnt) const;
  //this routine compare a 2d curve direction with 3d curve direction
  OdResult fixParamCurve(const OdGeSurface* pSurf, const OdGeCurve3d* pCurve3d, OdGeCurve2dPtr& pCurve2d) const;
  OdResult createParamCurve(const OdGeSurface* pSurf, const OdGeCurve3d* pCurve3d, OdGeCurve2dPtr& pCurve2d) const;
  OdResult addFaceExplicitLoop(BrepBuilderInitialSurface& surfData, const OdBrFace& face);
  static bool needPCurve(const OdGeSurface* pSurf);

  // Face
  OdGeSurfacePtr checkExtSurface(const OdGeSurface* resSurf, const OdBrFace& face) const;
  OdGeSurfacePtr getFaceSurface(const OdBrFace& face) const;
  void fixEllipConeRRatio(OdGeSurface* resSurf) const;

  // Vertex
  BrepBuilderInitialEdge::VertexIndex addVertex(const OdBrVertex& vertex);

  // Loop
  OdResult performLoopWithApex(const OdBrLoop& loop, OdGeCurve3dPtr& pCurve3d, OdGeCurve2dPtr& pCurve2d, OdBrVertex* vertex = NULL) const;
  OdResult splitOuterLoops(BrepBuilderInitialSurfaceArray& arrSurfaces);

  // Topology
  OdResult performBrep(const OdBrBrep& brep);
  OdResult performComplex(const OdBrComplex& complex);
  OdResult performShell(const OdBrShell& shell, BrepBuilderShellsArray& arrShells);
  OdResult performFace(const OdBrFace& face, BrepBuilderInitialSurfaceArray& arrSurfaces);
  OdResult performLoop(const OdBrLoop& loop, BrepBuilderInitialSurface& surfData);
  OdResult performEdge(const OdBrEdge& loop, unsigned& edgeIdx, OdGeCurve3d*& curve);

  static OdResult initFromImpl(OdBrepBuilderFiller& filler, OdBrepBuilder& builder, const BrepBuilderInitialData& data);

  void groupFaces(BrepBuilderInitialSurfaceArray& arrFaces, OdArray<OdUInt32Array>& groupedFaces);
  void findAdjacentFaces(BrepBuilderInitialSurfaceArray& arrFaces, OdHashSet<OdUInt32>& usedFaces,
    const OdHashMap<OdUInt32, OdUInt32Array>& edgesFaces, OdUInt32 iCurrFace, OdUInt32Array& facesIndexes);

  OdResult fixFaceRegionsConnections(BrepBuilderInitialSurfaceArray& arrFaces);

  static OdResult getDataFrom(
    BrepBuilderInitialData& data,
    const OdBrepBuilderFiller& filler,
    const OdBrBrep& brep,
    OdIMaterialAndColorHelper* materialHelper);

  //-----------------------------------
  //BimRv specific. Face regions
  struct CoedgeIndex {
    unsigned faceIdx;
    unsigned loopIdx;
    unsigned coedgeIdx;
    CoedgeIndex(unsigned faceIdx, unsigned loopIdx, unsigned coedgeIdx)
      : faceIdx(faceIdx), loopIdx(loopIdx), coedgeIdx(coedgeIdx) {}
    CoedgeIndex() : faceIdx(-1), loopIdx(-1), coedgeIdx(-1) {}
  };
  typedef OdUInt32 EdgeIndex;
  typedef std::pair<EdgeIndex, CoedgeIndex> EdgeCoedgeIndex;

  OdResult getFaceEdges(const OdBrFace& face, OdArray<EdgeIndex>& faceCurvesIdx);
  OdResult findParentEdge(EdgeIndex edgeIdx, const OdArray<EdgeIndex>& parentEdgeIndices, EdgeIndex& parentIdx);
  OdResult sortEdges(const BrepBuilderInitialSurfaceArray& arrFaces, OdArray<EdgeCoedgeIndex>& coedges);
  inline OdResult fixCoedgeIdx(const BrepBuilderInitialSurfaceArray& arrFaces, OdUInt32 edgeIdx, CoedgeIndex& coedgeIndex);

  OdArray<OdArray<EdgeIndex> > m_parentFacesEdgesIdx; //Arrays of edges indices in m_initialData.edges; each array corresponds to OdBrFace that has face regions.
  //-----------------------------------
};

// Interval
bool OdBrepBuilderFillerHelper::isIntervalContain(const OdGeInterval& frstInt, const OdGeInterval& scndInt) const
{
  return OdLessOrEqual(frstInt.lowerBound(), scndInt.lowerBound(), m_toleranceInterval)
    && OdGreaterOrEqual(frstInt.upperBound(), scndInt.upperBound(), m_toleranceInterval);
}
bool OdBrepBuilderFillerHelper::isIntervalContainReversed(const OdGeInterval& frstInt, const OdGeInterval& scndInt) const
{
  return OdGreaterOrEqual(frstInt.lowerBound()*-1, scndInt.upperBound(), m_toleranceInterval)
    && OdLessOrEqual(frstInt.upperBound()*-1, scndInt.lowerBound(), m_toleranceInterval);
}

// Edge
OdGeCurve3dPtr OdBrepBuilderFillerHelper::getEdgeCurve(const OdBrEdge& edge) const
{
  OdGeCurve3dPtr curve3d(edge.getCurve());

  if (!curve3d)
  {
    OdGeNurbCurve3d nurbCurve3d;
    if (edge.getCurveAsNurb(nurbCurve3d)) {
      return static_cast<OdGeCurve3d*>(nurbCurve3d.copy());
    }
    return NULL;
  }

  OdGe::EntityId entType = curve3d->type();
  if (OdGe::kExternalCurve3d == entType)
  {
    OdGeCurve3d* resCurve3d = NULL;
    const OdGeExternalCurve3d* extCurve = static_cast<OdGeExternalCurve3d*>(curve3d.get());

    if (extCurve->isNativeCurve(resCurve3d))
    {
      OdGeCurve3dPtr pCurveStore(resCurve3d);

      OdGeInterval curvIntOrig, curvIntNew;
      curve3d->getInterval(curvIntOrig);
      pCurveStore->getInterval(curvIntNew);

      if (isIntervalContain(curvIntOrig, curvIntNew)
        || isIntervalContainReversed(curvIntOrig, curvIntNew)
        || m_params.isSkipCoedge2dCurve()
        || pCurveStore->type() == OdGe::kLineSeg3d)
      {
        curve3d = pCurveStore;
      }
    }
  }

  return curve3d;
}

OdBrepBuilderFillerHelper::FixCurveStatus OdBrepBuilderFillerHelper::getCurveParams(const OdBrEdge& edge, const OdGeCurve3d* pCurve,
  OdGePoint3d& pntStart, OdGePoint3d& pntEnd, OdGeInterval& interval) const
{
  OdBrVertex startVertex;
  OdBrVertex endVertex;
  if (!edge.getVertex1(startVertex) || !edge.getVertex2(endVertex)) {
    // seems only parasolid may be without vertices
    return eSkip; //can't get vertexes - skip this curve
  }

  if (edge.getOrientToCurve()) {
    pntStart = startVertex.getPoint();
    pntEnd = endVertex.getPoint();
  } else {
    pntEnd = startVertex.getPoint();
    pntStart = endVertex.getPoint();
  }

  OdGePoint3d curveStart;
  OdGePoint3d curveEnd;
  if (!pCurve->hasStartPoint(curveStart)
    || !pCurve->hasEndPoint(curveEnd))
  {
    return eFail;//Can't get vert points - this is error
  }

  if (pntStart.isEqualTo(curveStart, m_toleranceDiffPoints)) {
    return eSkip;//points are equals
  }
  pCurve->getInterval(interval);
  return eSuccess;//ok, we got params
}

void OdBrepBuilderFillerHelper::setArcInterval(OdGeCurve3d* pCurve, OdGeInterval& interval, OdGePoint3d& pntStart, OdGePoint3d& center, OdGeVector3d& major, OdGeVector3d& normal) const
{
  OdGeVector3d centerToStart = pntStart - center;
  if (major.isCodirectionalTo(centerToStart))
  {
    if (OdNegative(interval.lowerBound())) {
      pCurve->setInterval(OdGeInterval(0., interval.length()));
      m_edgeCurveChanged.insert(pCurve);
    }
  }
  else
  {
    double angle = major.angleTo(centerToStart, normal);

    if (!OdZero(angle))
    {
      pCurve->rotateBy(angle, normal, center);
      if (OdNegative(interval.lowerBound())) {
        pCurve->setInterval(OdGeInterval(0., interval.length()));
        m_edgeCurveChanged.insert(pCurve);
      }
    }
  }
#ifdef ODA_DIAGNOSTICS
  OdGePoint3d curveStart;
  pCurve->hasStartPoint(curveStart);
  ODA_ASSERT_ONCE(pCurve->hasStartPoint(curveStart));
  ODA_ASSERT_ONCE(pntStart.isEqualTo(curveStart, 1e-05));
#endif //  ODA_DIAGNOSTICS
}

bool OdBrepBuilderFillerHelper::fixEllipse(OdGeCurve3dPtr& pCurve, const OdBrEdge& edge) const
{
  OdGeEllipArc3d& geEllipse = static_cast<OdGeEllipArc3d&>(*pCurve);
  OdGePoint3d startPoint;
  OdGePoint3d endPoint;
  OdGeInterval interval;
  FixCurveStatus res = getCurveParams(edge, pCurve, startPoint, endPoint, interval);
  if (eSuccess != res) {
    return res == eSkip;
  }

  if (!geEllipse.isCircular() || !startPoint.isEqualTo(endPoint, m_toleranceDiffPoints))
  {
    double newStartParam = geEllipse.paramOf(startPoint);
    geEllipse.setInterval(OdGeInterval(newStartParam, newStartParam + interval.length()));
    pCurve = new OdGeNurbCurve3d(geEllipse);
    m_edgeCurveChanged.insert(pCurve);

    ODA_ASSERT_ONCE(static_cast<OdGeNurbCurve3d*>(pCurve.get())->startPoint().isEqualTo(startPoint, 1e-04));
    return true;
  }

  // closed circle
  OdGePoint3d center = geEllipse.center();
  OdGeVector3d major = geEllipse.majorAxis();
  OdGeVector3d normal = geEllipse.normal();

  ODA_ASSERT_ONCE(OdEqual(startPoint.distanceTo(center), geEllipse.majorRadius(), 1e-05));
  setArcInterval(pCurve, interval, startPoint, center, major, normal);
  return true;
}

bool OdBrepBuilderFillerHelper::fixCircle(OdGeCurve3dPtr& pCurve, const OdBrEdge& edge) const
{
  OdGePoint3d startPoint;
  OdGePoint3d endPoint;
  OdGeInterval interval;
  FixCurveStatus res = getCurveParams(edge, pCurve, startPoint, endPoint, interval);
  if (eSuccess != res) {
    return res == eSkip;
  }

  OdGeCircArc3d& geCircle = static_cast<OdGeCircArc3d&>(*pCurve);

  if (!startPoint.isEqualTo(endPoint, m_toleranceDiffPoints))
  {
    double newStartParam = pCurve->paramOf(startPoint);
    pCurve->setInterval(OdGeInterval(newStartParam, newStartParam + interval.length()));
    pCurve = new OdGeNurbCurve3d(geCircle);
    m_edgeCurveChanged.insert(pCurve);

    ODA_ASSERT_ONCE(static_cast<OdGeNurbCurve3d*>(pCurve.get())->startPoint().isEqualTo(startPoint, 1e-04));
    return true;
  }

  OdGePoint3d center = geCircle.center();
  OdGeVector3d major = geCircle.refVec();
  OdGeVector3d normal = geCircle.normal();

  ODA_ASSERT_ONCE(OdEqual(startPoint.distanceTo(center), geCircle.radius(), 1e-05));
  setArcInterval(pCurve, interval, startPoint, center, major, normal);
  return true;
}

void OdBrepBuilderFillerHelper::fixEllipseRadiusRatio(OdGeCurve3d* pCurve) const
{
  if (!m_params.isMakeEllipMajorGreaterMinor()) {
    return;
  }

  //major radius should be >= minor for acis
  OdGeEllipArc3d& geEllipse = static_cast<OdGeEllipArc3d&>(*pCurve);
  OdGeVector3d vecMajAxis = geEllipse.majorAxis();
  OdGeVector3d vecMinAxis = geEllipse.minorAxis();
  const double majorRadius = geEllipse.majorRadius();
  const double minorRadius = geEllipse.minorRadius();
  if (OdZero(majorRadius, m_toleranceInterval) || !vecMajAxis.isPerpendicularTo(vecMinAxis, OdGeContext::gTol)) {
    throw OdError(eNotImplementedYet);
  }
  if (!OdGreater(minorRadius / majorRadius, 1, m_toleranceInterval)) {
    return;
  }
  geEllipse.set(geEllipse.center(), vecMinAxis, vecMajAxis.negate(), minorRadius, majorRadius, geEllipse.startAng() - OdaPI2, geEllipse.endAng() - OdaPI2);
  m_edgeCurveChanged.insert(pCurve);
}

bool OdBrepBuilderFillerHelper::fixNurb(OdGeCurve3dPtr& pCurve, const OdBrEdge& edge) const
{
  OdGeNurbCurve3d& geNurb = static_cast<OdGeNurbCurve3d&>(*pCurve);
  OdGePoint3d startPoint;
  OdGePoint3d endPoint;
  OdGeInterval interval;
  FixCurveStatus res = getCurveParams(edge, pCurve, startPoint, endPoint, interval);
  if (eSuccess != res) {
    return res == eSkip;
  }
  if (startPoint.isEqualTo(endPoint, m_toleranceDiffPoints))
  {
    // Closed curve
    // isOn not implemented
    double splitParam = geNurb.paramOf(startPoint);
    OdGeInterval curve3dInt;
    geNurb.getInterval(curve3dInt);
    if (OdEqual(splitParam, curve3dInt.lowerBound(), m_toleranceDiffPoints)
      || OdEqual(splitParam, curve3dInt.upperBound(), m_toleranceDiffPoints))
    {
      // it seems that point is not on curve
      return true;
    }

    OdGeCurve3d* piece1 = NULL;
    OdGeCurve3d* piece2 = NULL;
    geNurb.getSplitCurves(splitParam, piece1, piece2);
    OdGeTempCurve3dPtr pPiece1(piece1);
    OdGeTempCurve3dPtr pPiece2(piece2);
    if (!pPiece1.isNull() && !pPiece2.isNull())
    {
      ODA_ASSERT_ONCE(OdGe::kNurbCurve3d == pPiece1->type());
      ODA_ASSERT_ONCE(OdGe::kNurbCurve3d == pPiece2->type());
      OdGeNurbCurve3d& geNurb1 = static_cast<OdGeNurbCurve3d&>(*pPiece1);
      OdGeNurbCurve3d& geNurb2 = static_cast<OdGeNurbCurve3d&>(*pPiece2);
      geNurb = geNurb2.joinWith(geNurb1);
      m_edgeCurveChanged.insert(pCurve);

      ODA_ASSERT_ONCE(geNurb.startPoint().isEqualTo(startPoint, 1e-02) && geNurb.endPoint().isEqualTo(endPoint, 1e-02));
    }
  }
  else
  {
    double startParamNew = geNurb.paramOf(startPoint);
    double endParamNew = geNurb.paramOf(endPoint);
    OdGeInterval curve3dInt;
    geNurb.getInterval(curve3dInt);
    if ((OdEqual(startParamNew, curve3dInt.lowerBound(), m_toleranceDiffPoints)
      && OdEqual(endParamNew, curve3dInt.upperBound(), m_toleranceDiffPoints)))
    {
      // it seems that point is not on curve
      return true;
    }

    double startParam = geNurb.startParam();
    double endParam = geNurb.endParam();
    if ((startParam < startParamNew && startParamNew < endParam) && (startParam < endParamNew && endParamNew < endParam))
    {
      if ((startParamNew > endParamNew) && geNurb.isClosed())
      {
        // remove middle of curve and merge second part with first
        OdGeTempNurbCurve3dPtr pNurb1(static_cast<OdGeNurbCurve3d*>(geNurb.copy()));
        OdGeTempNurbCurve3dPtr pNurb2(static_cast<OdGeNurbCurve3d*>(geNurb.copy()));
        if (!pNurb1.isNull() && !pNurb2.isNull())
        {
          pNurb1->hardTrimByParams(startParamNew, endParam);
          pNurb2->hardTrimByParams(startParam, endParamNew);
          geNurb = pNurb1->joinWith(*pNurb2);
          m_edgeCurveChanged.insert(pCurve);

          ODA_ASSERT_ONCE(geNurb.startPoint().isEqualTo(startPoint, 1e-02) && geNurb.endPoint().isEqualTo(endPoint, 1e-02));
        }
      }
      else
      {
        // trim curve
        ODA_ASSERT_ONCE(startParamNew < endParamNew);
        geNurb.hardTrimByParams(startParamNew, endParamNew);
        m_edgeCurveChanged.insert(pCurve);

        ODA_ASSERT_ONCE(geNurb.startPoint().isEqualTo(startPoint, 1e-02) && geNurb.endPoint().isEqualTo(endPoint, 1e-02));
      }
    }
  }

  return true;
}

OdResult OdBrepBuilderFillerHelper::getEdgeCurveFixed(const OdBrEdge& edge, OdGeCurve3dPtr& pCurve) const
{
  pCurve = getEdgeCurve(edge);

  if (pCurve.isNull()) {
    return checkRet(eNullEdgeCurve);
  }

  bool result = true;
  OdGe::EntityId curveType = pCurve->type();
  switch (curveType)
  {
  case OdGe::kEllipArc3d:
  {
    result = fixEllipse(pCurve, edge);
    curveType = pCurve->type(); // become useless if fixEllipse doesn't change curve type
    if (OdGe::kEllipArc3d == curveType) {
      fixEllipseRadiusRatio(pCurve);
    }
    break;
  }
  case OdGe::kCircArc3d: result = fixCircle(pCurve, edge); break;
  case OdGe::kNurbCurve3d: result = fixNurb(pCurve, edge); break;
  }

  return checkRet(result ? eOk : eCurveEndsMissed);
}

// Coedge
OdGeCurve2dPtr OdBrepBuilderFillerHelper::getParamCurve(const OdBrLoopEdgeTraverser& loEdTrav) const
{
  OdGeNurbCurve2d nurbCurve2d;
  if (odbrOK == loEdTrav.getParamCurveAsNurb(nurbCurve2d)) {
    return static_cast<OdGeCurve2d*>(nurbCurve2d.copy());
  }

  OdGeTempCurve2dPtr paramCurve(loEdTrav.getParamCurve());
  if (paramCurve.isNull()) return NULL;

  // Acis bb required nurb 2d curve. Another (bim,prc) bb doesn't use 2d curve.
  if (OdGe::kNurbCurve2d == paramCurve->type()) return paramCurve.detach();
  return OdGeNurbCurve2d::convertFrom(paramCurve.get(), m_toleranceRestore2dCurve, true);
}

OdResult OdBrepBuilderFillerHelper::checkNurb2dFor3d(const OdGeSurface* pSurf, const OdGeCurve3d* pCurve3d,
  OdGeCurve2d* pCurve2d) const
{
  OdGeNurbCurve2d& geNurb2d = static_cast<OdGeNurbCurve2d&>(*pCurve2d);

  OdGePoint3d curve3dStart;
  OdGePoint3d curve3dEnd;
  OdGePoint2d curve2dStart = geNurb2d.startPoint();
  OdGePoint2d curve2dEnd = geNurb2d.endPoint();

  if (!pCurve3d->hasStartPoint(curve3dStart)
    || !pCurve3d->hasEndPoint(curve3dEnd))
  {
    return checkRet(eCurveEndsMissed);
  }

  OdGePoint3d surf3dStart = pSurf->evalPoint(curve2dStart);
  OdGePoint3d surf3dEnd = pSurf->evalPoint(curve2dEnd);

  if ((surf3dStart.isEqualTo(curve3dStart, m_toleranceDiffPoints)
    && surf3dEnd.isEqualTo(curve3dEnd, m_toleranceDiffPoints))
    || (surf3dStart.isEqualTo(curve3dEnd, m_toleranceDiffPoints)
    && surf3dEnd.isEqualTo(curve3dStart, m_toleranceDiffPoints)))
  {
    return checkRet(eOk);
  }
  // required to fix curve
  OdGePoint2d start2dPoint;
  OdGePoint2d end2dPoint;
  OdGe::EntityId surfType = pSurf->type();
  if (OdGe::kNurbSurface == surfType)
  {
    const OdGeNurbSurface* pNurbSurf = static_cast<const OdGeNurbSurface*>(pSurf);
    start2dPoint = pNurbSurf->paramOfPrec(curve3dStart);
    end2dPoint = pNurbSurf->paramOfPrec(curve3dEnd);
  }
  else
  {
    start2dPoint = pSurf->paramOf(curve3dStart);
    end2dPoint = pSurf->paramOf(curve3dEnd);
  }

  if (!curve3dStart.isEqualTo(pSurf->evalPoint(start2dPoint), m_toleranceDiffPoints)
    || !curve3dEnd.isEqualTo(pSurf->evalPoint(end2dPoint), m_toleranceDiffPoints))
  {
    return checkRet(ePointNotOnCurve);
  }

  if (start2dPoint.isEqualTo(end2dPoint, m_toleranceDiffPoints))
  {
    if (start2dPoint.isEqualTo(curve2dStart, m_toleranceDiffPoints)
      || start2dPoint.isEqualTo(curve2dEnd, m_toleranceDiffPoints))
    {
      return checkRet(ePointNotOnCurve);
    }

    double splitParam;
    if (!geNurb2d.isOn(start2dPoint, splitParam, OdGeTol(m_toleranceDiffPoints, OdGeContext::gTol.equalVector())))
    {
      //checking for periodic surface. Parametric curves may on start/end of period
      //and paramof() can return points on another "side" of this surface
      //so we need check it at start parameter and at period
      moveParamIntoExtents(pSurf, pCurve2d, start2dPoint);
      if (!geNurb2d.isOn(start2dPoint, splitParam, OdGeTol(m_toleranceDiffPoints, OdGeContext::gTol.equalVector()))) {
        return checkRet(ePointNotOnCurve);
      }
    }
    OdGeCurve2d* piece1 = NULL;
    OdGeCurve2d* piece2 = NULL;
    geNurb2d.getSplitCurves(splitParam, piece1, piece2);
    OdGeTempCurve2dPtr pPiece1(piece1);
    OdGeTempCurve2dPtr pPiece2(piece2);
    if (!pPiece1.isNull() && !pPiece2.isNull())
    {
      ODA_ASSERT_ONCE(OdGe::kNurbCurve2d == pPiece1->type());
      ODA_ASSERT_ONCE(OdGe::kNurbCurve2d == pPiece2->type());
      OdGeNurbCurve2d& geNurb1 = static_cast<OdGeNurbCurve2d&>(*pPiece1);
      OdGeNurbCurve2d& geNurb2 = static_cast<OdGeNurbCurve2d&>(*pPiece2);
      geNurb2.transformBy(OdGeMatrix2d::translation(geNurb1.startPoint() - geNurb2.endPoint()));
      geNurb2d = geNurb2.joinWith(geNurb1);

      bool res = (pSurf->evalPoint(geNurb2d.startPoint()).isEqualTo(curve3dStart, m_toleranceDiffPoints)
        && pSurf->evalPoint(geNurb2d.endPoint()).isEqualTo(curve3dEnd, m_toleranceDiffPoints));
      return checkRet(res ? eOk : ePointNotOnCurve);
    }
  }
  else
  {
    double startParamNew;
    double endParamNew;
    if (!geNurb2d.isOn(start2dPoint, startParamNew, OdGeTol(m_toleranceDiffPoints, OdGeContext::gTol.equalVector()))
      || !geNurb2d.isOn(end2dPoint, endParamNew, OdGeTol(m_toleranceDiffPoints, OdGeContext::gTol.equalVector())))
    {
      return checkRet(ePointNotOnCurve);
    }

    double startParam = geNurb2d.startParam();
    double endParam = geNurb2d.endParam();
    if ((startParam < startParamNew && startParamNew < endParam) && (startParam < endParamNew && endParamNew < endParam))
    {
      if ((startParamNew > endParamNew) && geNurb2d.isClosed())
      {
        OdGeTempNurbCurve2dPtr pNurb1(static_cast<OdGeNurbCurve2d*>(geNurb2d.copy()));
        OdGeTempNurbCurve2dPtr pNurb2(static_cast<OdGeNurbCurve2d*>(geNurb2d.copy()));
        if (!pNurb1.isNull() && !pNurb2.isNull())
        {
          pNurb1->hardTrimByParams(startParamNew, endParam);
          pNurb2->hardTrimByParams(startParam, endParamNew);
          geNurb2d = pNurb1->joinWith(*pNurb2);

          bool res = (pSurf->evalPoint(geNurb2d.startPoint()).isEqualTo(curve3dStart, m_toleranceDiffPoints)
            && pSurf->evalPoint(geNurb2d.endPoint()).isEqualTo(curve3dEnd, m_toleranceDiffPoints));
          return checkRet(res ? eOk : ePointNotOnCurve);
        }
      }
      else
      {
        ODA_ASSERT_ONCE(startParamNew < endParamNew);
        try {
          geNurb2d.hardTrimByParams(startParamNew, endParamNew);
        } catch (...) {
          ODA_FAIL_M_ONCE("Unsucessfull hardTrimByParams for nurb curve.");
        }

        bool res = (pSurf->evalPoint(geNurb2d.startPoint()).isEqualTo(curve3dStart, m_toleranceDiffPoints)
          && pSurf->evalPoint(geNurb2d.endPoint()).isEqualTo(curve3dEnd, m_toleranceDiffPoints));
        return checkRet(res ? eOk : ePointNotOnCurve);
      }
    }
  }

  return checkRet(eInvalidCurve);
}

OdResult OdBrepBuilderFillerHelper::checkCurve2dFor3d(const OdGeSurface* pSurf, const OdGeCurve3d* pCurve3d, OdGeCurve2d* pCurve2d) const
{
  if (m_edgeCurveChanged.end() == m_edgeCurveChanged.find(pCurve3d)) {
    return checkRet(eOk);
  }

  OdGe::EntityId curve2dType = pCurve2d->type();
  if (OdGe::kNurbCurve2d == curve2dType) {
    return checkRet(checkNurb2dFor3d(pSurf, pCurve3d, pCurve2d));
  }

  // TODO not nurb curve
  return checkRet(eNotImplemented);
}

void OdBrepBuilderFillerHelper::moveParamCurveNurbInterval(const OdGeSurface* pSurf, const OdGeCurve3d* pCurve3d, OdGeCurve2d* pCurve2d) const
{
  OdGeNurbCurve2d& geNurb2d = static_cast<OdGeNurbCurve2d&>(*pCurve2d);

  OdGeInterval curv3dInt, curv2dInt;
  pCurve3d->getInterval(curv3dInt);
  geNurb2d.getInterval(curv2dInt);

  //OdGeNurbCurve2d can have interval < knots. This code scales knots so that curv2dInt will be equal to curv3dInt and 2d geometry won't change
  const OdGeKnotVector& aKt = geNurb2d.knots();
  ODA_ASSERT_ONCE(!aKt.isEmpty());
  double a = (curv3dInt.upperBound() - curv3dInt.lowerBound()) / (curv2dInt.upperBound() - curv2dInt.lowerBound());
  double b = curv3dInt.lowerBound() - a * curv2dInt.lowerBound();

  for (int i = 0; i < aKt.length(); ++i) {
    geNurb2d.setKnotAt(i, a * aKt[i] + b);
  }
  //clamp knots (due to machine epsilon)
  if (aKt.startParam() > curv3dInt.lowerBound()) {
    for (int i = 0; i <= geNurb2d.degree(); ++i) {
      ODA_ASSERT_ONCE(OdEqual(curv3dInt.lowerBound(), aKt[i], aKt.tolerance()));
      geNurb2d.setKnotAt(i, curv3dInt.lowerBound());
    }
  }
  if (aKt.endParam() < curv3dInt.upperBound()) {
    for (int i = geNurb2d.numControlPoints(); i < aKt.length(); ++i) {
      ODA_ASSERT_ONCE(OdEqual(curv3dInt.upperBound(), aKt[i], aKt.tolerance()));
      geNurb2d.setKnotAt(i, curv3dInt.upperBound());
    }
  }
  bool intervalSet = geNurb2d.setInterval(curv3dInt);
  ODA_ASSERT_ONCE(intervalSet);
}

void OdBrepBuilderFillerHelper::moveParamIntoExtents(const OdGeSurface* pSurf, const OdGeCurve2d* pCurve2d, OdGePoint2d& pnt) const
{
  bool bClosedInU = pSurf->isClosedInU();
  bool bClosedInV = pSurf->isClosedInV();
  if (!bClosedInU && !bClosedInV) {
    return;
  }

  OdGeInterval iu, iv;
  pSurf->getEnvelope(iu, iv);

  OdGeExtents2d extents;
  OdGePoint2dArray pnts;
  OdGeInterval intCur;
  pCurve2d->getInterval(intCur);
  pCurve2d->getSamplePoints(intCur.lowerBound(), intCur.upperBound(), 0., pnts);
  extents.addPoints(pnts);

  if (bClosedInU)
  {
    double dI = iu.length();
    while (pnt.x > extents.maxPoint().x + m_toleranceInterval) pnt.x -= dI;
    while (pnt.x < extents.minPoint().x - m_toleranceInterval) pnt.x += dI;

    // uv should be as close to curveExtents as possible
    if (pnt.x > extents.maxPoint().x + m_toleranceInterval && pnt.x - extents.maxPoint().x > extents.minPoint().x - (pnt.x - dI)) {
      pnt.x -= dI;
    }
  }

  if (bClosedInV)
  {
    double dI = iv.length();
    while (pnt.y > extents.maxPoint().y + m_toleranceInterval) pnt.y -= dI;
    while (pnt.y < extents.minPoint().y - m_toleranceInterval) pnt.y += dI;

    // uv should be as close to curveExtents as possible
    if (pnt.y > extents.maxPoint().y + m_toleranceInterval && pnt.y - extents.maxPoint().y > extents.minPoint().y - (pnt.y - dI)) {
      pnt.y -= dI;
    }
  }
}

OdResult OdBrepBuilderFillerHelper::moveParamCurveInterval(const OdGeSurface* pSurf, const OdGeCurve3d* pCurve3d, OdGeCurve2d* pCurve2d) const
{
  OdGe::EntityId curve2dType = pCurve2d->type();
  if (OdGe::kNurbCurve2d == curve2dType) {
    moveParamCurveNurbInterval(pSurf, pCurve3d, pCurve2d);
    return checkRet(eOk);
  }

  // TODO not nurb curve
  return checkRet(eNotImplemented);
}

static OdGeCurve2d* restoreUvCurveAsNurb(const OdGeCurve3d* pCurve3d, const OdGeSurface* pSurf, double tol)
{
  OdGeTempCurve2dPtr pProjCurve(OdGeCurve2d::restoreUvCurve(pCurve3d, pSurf, tol));
  if (pProjCurve.isNull())
    return NULL;
  if (OdGe::kNurbCurve2d == pProjCurve->type())
    return pProjCurve.detach();
  return OdGeNurbCurve2d::convertFrom(pProjCurve.get(), OdGeTol(tol, OdGeContext::gTol.equalVector()));
}

OdResult OdBrepBuilderFillerHelper::createParamCurve(const OdGeSurface* pSurf, const OdGeCurve3d* pCurve3d, OdGeCurve2dPtr& pCurve2d) const
{
  ODA_ASSERT(pSurf && pCurve3d);
  //estimate tolerance for creating param curve
  OdGePoint3dArray arrCrvSamplePnts(21);
  pCurve3d->getSamplePoints(21, arrCrvSamplePnts);
  double dTol = 0.;
  for (OdGePoint3dArray::size_type iPoint = 0; iPoint < arrCrvSamplePnts.length(); ++iPoint)
  {
    OdGePoint3d p3dCurve = arrCrvSamplePnts[iPoint];
    OdGePoint2d p2d;
    pSurf->type() == OdGe::kNurbSurface ? p2d = static_cast<const OdGeNurbSurface*>(pSurf)->paramOfPrec(p3dCurve) : p2d = pSurf->paramOf(p3dCurve);
    OdGePoint3d p3dSurf = pSurf->evalPoint(p2d);
    double dDistance = p3dSurf.distanceTo(p3dCurve);
    if (dTol < dDistance) {
      dTol = dDistance;
    }
  }
  dTol = dTol + dTol * 0.1;
  pCurve2d = restoreUvCurveAsNurb(pCurve3d, pSurf, dTol > m_toleranceRestore2dCurve ? dTol : m_toleranceRestore2dCurve);
  if (!pCurve2d) {
    return checkRet(eCreateFailed);
  }
  return checkRet(eOk);
}
OdResult OdBrepBuilderFillerHelper::fixParamCurve(const OdGeSurface* pSurf, const OdGeCurve3d* pCurve3d, OdGeCurve2dPtr& pCurve2d) const
{
  if (!pCurve2d) {
    return checkRet(eOk);
  }

  // First update 2d curve if 3d was fixed
  OdResult status = checkCurve2dFor3d(pSurf, pCurve3d, pCurve2d);
  if (eOk != status) {
    return checkRet(status);
  }

  OdGeInterval curv3dInt, curv2dInt;
  if (m_params.isMake2dIntervalInclude3d())
  {
    pCurve3d->getInterval(curv3dInt);
    pCurve2d->getInterval(curv2dInt);

    if (!isIntervalContain(curv2dInt, curv3dInt)
      && !isIntervalContainReversed(curv2dInt, curv3dInt))
    {
      //2d and 3d intervals are different.
      //TODO: this code is incorrect! Coedge may be a part of 2d curve! E.g., allSingleFaceNurbs.2010.dxf, 0x17E
      //In this case we need trimming instead of scaling.
      status = moveParamCurveInterval(pSurf, pCurve3d, pCurve2d);
      if (eOk != status) {
        return checkRet(status);
      }
      pCurve2d->getInterval(curv2dInt);
    }
    else
    {
      //Brep Builder waits for int3d == int2d. They should be equal because tolerance for tedges (and tvertex) computed with
      //parametric curves and if spatr parameter of parcur != start parameter of edge curvre invalid tol valued will be computed.
      if (!(OdEqual(curv2dInt.lowerBound(), curv3dInt.lowerBound(), m_toleranceInterval) && OdEqual(curv2dInt.upperBound(), curv3dInt.upperBound(), m_toleranceInterval)))
      {
        if (needPCurve(pSurf)) {
          return checkRet(createParamCurve(pSurf, pCurve3d, pCurve2d));
        }
        return checkRet(eCreateFailed);
      }
    }
  }

  bool bCoincide(true);
  if (geIsDir2dOnSurfCoincide3d(pSurf, pCurve3d, pCurve2d, bCoincide, m_toleranceCoincide) == eOk)
  {
    if (!bCoincide) {
      pCurve2d->reverseParam();
      pCurve2d->getInterval(curv2dInt);
    }
  }
  else
  {
    pCurve2d = restoreUvCurveAsNurb(pCurve3d, pSurf, m_toleranceRestore2dCurve);
    if (!pCurve2d) {
      return checkRet(eCreateFailed);
    }
    pCurve2d->getInterval(curv2dInt);
  }

  if (m_params.isMake2dIntervalInclude3d())
  {
    if (isIntervalContain(curv2dInt, curv3dInt)) {
      return checkRet(eOk);
    }

    //should never be here
    ODA_FAIL_M_ONCE("Probably invalid 2d and 3d intervals");
    return checkRet(moveParamCurveInterval(pSurf, pCurve3d, pCurve2d));
  }

  return checkRet(eOk);
}

/** \details
   Compares two points arrays with tolerance specified and gets maximal distance between correspond points.

   \param pts1   [in] First array.
   \param pts2   [in] Second array.
   \param dDist [out] Maximal distance.
   \param tol    [in] Tolerance.
   \returns true if arrays are equal, false - otherwise.
*/
static bool arePointsEqual(const OdGePoint3dArray& pts1, const OdGePoint3dArray& pts2, double& dDist, const OdGeTol& tol = OdGeContext::gTol)
{
  dDist = 0.0;
  if (pts1.length() != pts2.length()) {
    return false;
  }

  for (unsigned int k = 0; k < pts1.length(); k++)
  {
    double dCurDist = (pts1[k] - pts2[k]).lengthSqrd();
    if (dCurDist > dDist) {
      dDist = dCurDist;
    }
    if (dCurDist > tol.equalPoint() * tol.equalPoint()) {
      return false;
    }
  }
  return true;
}

OdResult OdBrepBuilderFillerHelper::addFaceExplicitLoop(BrepBuilderInitialSurface& surfData, const OdBrFace& face)
{
  OdGeInterval ivU, ivV;
  surfData.pSurf->getEnvelope(ivU, ivV);

  if (surfData.pSurf->isKindOf(OdGe::kSphere)
    && surfData.pSurf->isClosedInU(m_toleranceInterval)
    && surfData.pSurf->isClosedInV(m_toleranceInterval))
  {
    // Do nothing for closed sphere
    return checkRet(eOk);
  }
  else if (surfData.pSurf->isKindOf(OdGe::kTorus)
    && surfData.pSurf->isClosedInU(m_toleranceInterval)
    && surfData.pSurf->isClosedInV(m_toleranceInterval))
  {
    // Do nothing for closed torus
    return checkRet(eOk);
  }
  else if (!surfData.pSurf->isNormalReversed()
    && ivU.isBounded() && ivV.isBounded()) // Add new loop by envelope borders
  {
    const unsigned int iBorders = 4;
    const unsigned int iPtsCnt = 7;
    OdGePoint2dArray aParams(iBorders);
    OdGeCurve3dPtrArray aIsoparamCurves(iBorders);
    OdGeCurve2dPtrArray aParamCurves(iBorders);
    OdBrepBuilder::EntityDirection aDirs[iBorders] = {
      OdBrepBuilder::kForward, OdBrepBuilder::kForward,
      OdBrepBuilder::kReversed, OdBrepBuilder::kReversed };

    aParams.resize(iBorders);
    aParamCurves.resize(iBorders);
    aIsoparamCurves.resize(iBorders);

    // Create borders curves
    aIsoparamCurves[0] = surfData.pSurf->makeIsoparamCurve(false, ivV.lowerBound());
    aIsoparamCurves[1] = surfData.pSurf->makeIsoparamCurve(true, ivU.upperBound());
    aIsoparamCurves[2] = surfData.pSurf->makeIsoparamCurve(false, ivV.upperBound());
    aIsoparamCurves[3] = surfData.pSurf->makeIsoparamCurve(true, ivU.lowerBound());

    // Check makeIsoparamCurve results (can be NULL)
    if (aIsoparamCurves[0].isNull() || aIsoparamCurves[1].isNull()
      || aIsoparamCurves[2].isNull() || aIsoparamCurves[3].isNull())
    {
      return checkRet(eNullEdgeCurve);
    }

    // Change loop direction for reversed case
    if (surfData.direction == OdBrepBuilder::kReversed)
    {
      aIsoparamCurves.reverse();
      aParamCurves.reverse();
      ODA_FAIL_M_ONCE("Reversed face without loops.");
    }

    // Create corner parametric points
    aParams[0] = OdGePoint2d(ivU.lowerBound(), ivV.lowerBound());
    aParams[1] = OdGePoint2d(ivU.upperBound(), ivV.lowerBound());
    aParams[2] = OdGePoint2d(ivU.upperBound(), ivV.upperBound());
    aParams[3] = OdGePoint2d(ivU.lowerBound(), ivV.upperBound());

    if (needPCurve(surfData.pSurf))
    {
      for (unsigned int i = 0; i < iBorders; i++)
      {
        aParamCurves[i] = new OdGeNurbCurve2d(OdGeLineSeg2d(aParams[i], aParams[(i + 1) % iBorders]));
        OdResult eStatus = fixParamCurve(surfData.pSurf, aIsoparamCurves[i], aParamCurves[i]);
        if (eStatus != eOk) {
          return checkRet(eStatus);
        }
      }
    }

    // Create new loop
    BrepBuilderInitialLoop loopData;
    for (unsigned int i = 0; i < iBorders; i++)
    {
      // Degenerate edge
      OdGe::EntityId iType;
      if (aIsoparamCurves[i]->isDegenerate(iType, 1.e-10/*, m_toleranceCoincide*/)) {
        continue;
      }

      // Create coedge
      BrepBuilderInitialCoedge& coedgeData = *loopData.coedges.append();
      // Reverse direction of two coedges
      coedgeData.direction = aDirs[i];
      coedgeData.curve = aParamCurves[i];

      // Create sample points array
      OdGePoint3dArray aSmplPts;
      aIsoparamCurves[i]->getSamplePoints(iPtsCnt, aSmplPts);

      // Calculate distance from first to last points.
      OdGeInterval iv;
      aIsoparamCurves[i]->getInterval(iv);
      double dIvLength = iv.length();

      std::multiset<EdgeCurveCompareData>::iterator start = m_edgesAdded.lower_bound(EdgeCurveCompareData(dIvLength - m_toleranceInterval));
      std::multiset<EdgeCurveCompareData>::iterator end = m_edgesAdded.upper_bound(EdgeCurveCompareData(dIvLength + m_toleranceInterval));

      if (start != end)
      {
        double dMinDist = std::numeric_limits<double>::max(), dCurDist;
        std::multiset<EdgeCurveCompareData>::iterator thebest;
        bool bFound = false;
        for (std::multiset<EdgeCurveCompareData>::iterator it = start; it != end; ++it)
        {
          if (arePointsEqual(aSmplPts, it->aSamplePts, dCurDist, m_toleranceInterval) && dCurDist < dMinDist)
          {
            dMinDist = dCurDist;
            thebest = it;
            bFound = true;
          }
        }
        if (bFound) {
          coedgeData.edgeIndex = thebest->idEdge;
          continue;
        }
      }

      // Create edge
      BrepBuilderInitialEdge& edgeData = *m_initialData.edges.append();
      edgeData.curve = aIsoparamCurves[i];

      // Fill edge visual
      edgeData.hasColor = surfData.hasColor;
      if (edgeData.hasColor)
        edgeData.color = surfData.color;

      // Here we can't get OdGsMarker. There is no edge to getGsMarker.

      coedgeData.edgeIndex = m_initialData.edges.size() - 1;
      m_edges[(OdUInt64)edgeData.curve.get()] = coedgeData.edgeIndex;
      m_edgesAdded.insert(EdgeCurveCompareData(edgeData.curve.get(), coedgeData.edgeIndex, aSmplPts, dIvLength));
    }

    surfData.loops.append(loopData);
  }
  else
  {
    return checkRet(eNotApplicable);
  }
  return checkRet(eOk);
}

bool OdBrepBuilderFillerHelper::needPCurve(const OdGeSurface* pSurf)
{
  OdGe::EntityId sType = pSurf->type();
  return !(sType == OdGe::kPlane         || sType == OdGe::kSphere    || sType == OdGe::kCylinder || sType == OdGe::kCone ||
           sType == OdGe::kEllipCylinder || sType == OdGe::kEllipCone || sType == OdGe::kTorus);
}

// Face
OdGeSurfacePtr OdBrepBuilderFillerHelper::checkExtSurface(const OdGeSurface* resSurf, const OdBrFace &face) const
{
  const OdGeExternalSurface* extSurf = static_cast<const OdGeExternalSurface*>(resSurf);
  OdGeSurface* pSurf = NULL;
  if (extSurf->isNativeSurface(pSurf))
    return pSurf;

  OdGeNurbSurface nurbFace;
  OdBrErrorStatus err = face.getSurfaceAsNurb(nurbFace);
  if (odbrOK != err) {
    return NULL;
  }
  return new OdGeNurbSurface(nurbFace);
}

OdGeSurfacePtr OdBrepBuilderFillerHelper::getFaceSurface(const OdBrFace& face) const
{
  OdGeSurfacePtr surf(face.getSurface());
  if (!surf)
  {
    OdGeNurbSurface nurbSurf;
    try
    {
      if (odbrOK == face.getSurfaceAsNurb(nurbSurf)) {
        return static_cast<OdGeSurface*>(nurbSurf.copy());
      }
    }
    catch (const OdError& err)
    {
      if (err.code() != eNotImplemented) {
        throw err;
      }
    }

    return NULL;
  }

  OdGe::EntityId entType = surf->type();
  if (OdGe::kExternalBoundedSurface == entType)
  {
    OdGeSurface* tResSurf = NULL;
    const OdGeExternalBoundedSurface* extSurf = static_cast<OdGeExternalBoundedSurface*>(surf.get());
    extSurf->getBaseSurface(tResSurf);
    OdGeTempSurfacePtr resSurf(tResSurf);
    if (!resSurf.isNull() && resSurf->type() != OdGe::kExternalSurface)
      surf = resSurf.detach();
    else if (!resSurf.isNull() && resSurf->type() == OdGe::kExternalSurface)
      surf = checkExtSurface(resSurf, face);
  }
  else if (OdGe::kExternalSurface == entType)
    surf = checkExtSurface(surf, face);

  return surf;
}

void OdBrepBuilderFillerHelper::fixEllipConeRRatio(OdGeSurface* pSurf) const
{
  if (!m_params.isMakeEllipMajorGreaterMinor()) {
    return;
  }

  double dStartAngle, dEndAngle;
  OdGe::EntityId sType = pSurf->type();
  if (sType == OdGe::kEllipCone)
  {
    OdGeEllipCone *pEllipCone = static_cast<OdGeEllipCone*>(pSurf);
    OdGeVector3d vecMajAxis = pEllipCone->majorAxis();
    OdGeVector3d vecMinAxis = pEllipCone->minorAxis();
    const double majorRadius = pEllipCone->majorRadius();
    const double minorRadius = pEllipCone->minorRadius();
    if (OdZero(majorRadius, m_toleranceInterval) || !vecMajAxis.isPerpendicularTo(vecMinAxis, OdGeContext::gTol)) {
      throw OdError(eNotImplementedYet);
    }
    double dRaduisRatio = minorRadius / majorRadius;
    if (OdGreater(dRaduisRatio, 1, m_toleranceDiffPoints))
    {
      double dSinAngle, dCosAngle;
      pEllipCone->getHalfAngle(dCosAngle, dSinAngle);
      //this code need for determine sign of sin
      if (!(pEllipCone->isNormalReversed() ^ pEllipCone->isOuterNormal())) {
        dCosAngle *= -1;
      }
      if (!(pEllipCone->baseCenter() - pEllipCone->axisOfSymmetry() * (majorRadius * dCosAngle / dSinAngle)).isEqualTo(pEllipCone->apex())) {
        dSinAngle *= -1;
      }
      pEllipCone->getAngles(dStartAngle, dEndAngle);
      dStartAngle -= OdaPI2;
      dEndAngle -= OdaPI2;
      OdGeInterval height;
      pEllipCone->getHeight(height);
      pEllipCone->set(dCosAngle, dSinAngle, pEllipCone->baseCenter(), minorRadius, majorRadius, pEllipCone->axisOfSymmetry(), vecMinAxis, height, dStartAngle, dEndAngle);
    }
  }
  else if (sType == OdGe::kEllipCylinder)
  {
    OdGeEllipCylinder *pEllipCylinder = static_cast<OdGeEllipCylinder*>(pSurf);
    OdGeVector3d vecMajAxis = pEllipCylinder->majorAxis();
    OdGeVector3d vecMinAxis = pEllipCylinder->minorAxis();
    const double majorRadius = pEllipCylinder->majorRadius();
    const double minorRadius = pEllipCylinder->minorRadius();
    if (OdZero(majorRadius, m_toleranceInterval) || !vecMajAxis.isPerpendicularTo(vecMinAxis, OdGeContext::gTol)) {
      throw OdError(eNotImplementedYet);
    }
    double dRaduisRatio = minorRadius / majorRadius;
    if (OdGreater(dRaduisRatio, 1, m_toleranceDiffPoints))
    {
      pEllipCylinder->getAngles(dStartAngle, dEndAngle);
      dStartAngle -= OdaPI2;
      dEndAngle -= OdaPI2;
      OdGeInterval height;
      pEllipCylinder->getHeight(height);
      pEllipCylinder->set(majorRadius, minorRadius, pEllipCylinder->origin(), pEllipCylinder->axisOfSymmetry(), vecMinAxis.negate(), height, dStartAngle, dEndAngle);
    }
  }
}

//Vertex
BrepBuilderInitialEdge::VertexIndex OdBrepBuilderFillerHelper::addVertex(const OdBrVertex& vertex)
{
  OdHashMap<OdUInt64, OdUInt32>::const_iterator pIt = m_vertices.find(vertex.getUniqueId());
  if (pIt != m_vertices.end()) {
    return pIt->second;
  }
  BrepBuilderInitialVertex& initVertex = *m_initialData.vertices.append();
  initVertex.point = vertex.getPoint();
  if (m_params.isSetVertexGsMarkersTags())
    initVertex.marker.first = odbrOK == vertex.getGsMarker(initVertex.marker.second);
  BrepBuilderInitialEdge::VertexIndex vertexIndex = m_initialData.vertices.size() - 1;
  m_vertices[vertex.getUniqueId()] = vertexIndex;
  return vertexIndex;
}

// Loop
OdResult OdBrepBuilderFillerHelper::performLoopWithApex(const OdBrLoop& loop, 
  OdGeCurve3dPtr& pCurve3d, OdGeCurve2dPtr& pCurve2d, OdBrVertex* vertex) const
{
  OdBrLoopVertexTraverser loopVertTrav;
  if (odbrOK != loopVertTrav.setLoop(loop)) {
    return checkRet(eBadApexLoop);
  }

  if (vertex)
    *vertex = loopVertTrav.getVertex();
  OdGePoint3d point = vertex ? vertex->getPoint() : loopVertTrav.getVertex().getPoint();

  if ((odbrOK != loopVertTrav.next()) || !loopVertTrav.done())
  {
    // unexpected: more then one point
    return checkRet(eBadApexLoop);
  }

  pCurve3d = new OdGeLineSeg3d(point, point);
  pCurve2d = NULL;

  return checkRet(eOk);
}

OdResult OdBrepBuilderFillerHelper::splitOuterLoops(BrepBuilderInitialSurfaceArray& arrSurfaces)
{
  ODA_ASSERT_ONCE(arrSurfaces.size() > 0);
  OdGeIntArray::size_type currentFaceIdx = arrSurfaces.size() - 1;
  BrepBuilderInitialSurface* pSurfData = &arrSurfaces.last();
  if (pSurfData->loops.size() <= 1)
    return checkRet(eOk);

  OdResult eStatus = eOk;

  const OdGeTol tol(m_toleranceDiffPoints, OdGeContext::gTol.equalVector());

  OdArray<OdGeIntArray> loopIndices;
  struct CurveStore
  {
    std::vector<OdGeCurve2d*> data;

    ~CurveStore() {
      for (OdGeIntArray::size_type iCurve = 0; iCurve < data.size(); ++iCurve)
        delete data[iCurve];
    }
  } store;
  OdArray< OdArray<const OdGeCurve2d*> > loops;
  OdArray< OdArray<bool> > revFlags;

  loops.reserve(pSurfData->loops.size());
  revFlags.reserve(pSurfData->loops.size());
  for (OdGeIntArray::size_type iLoop = 0; iLoop < pSurfData->loops.size(); ++iLoop)
  {
    const BrepBuilderInitialCoedgeArray& coedges = pSurfData->loops.getAt(iLoop).coedges;
    ODA_ASSERT_ONCE(!coedges.isEmpty());

    OdArray<const OdGeCurve2d*>& loopCurves = *loops.append();
    OdArray<bool>& loopReVFlags = *revFlags.append();

    loopCurves.reserve(coedges.size());
    loopReVFlags.reserve(coedges.size());
    for (OdGeIntArray::size_type iCoedge = 0; iCoedge < coedges.size(); ++iCoedge)
    {
      const BrepBuilderInitialCoedge& coedge = coedges.getAt(iCoedge);
      const OdGeCurve2d* pCurve = coedge.curve.get();
      if (!pCurve) {
        store.data.push_back(NULL);
        pCurve = store.data.back() = OdGeCurve2d::restoreUvCurve(m_initialData.edges.getAt(coedge.edgeIndex).curve, pSurfData->pSurf, tol);
      }

      loopCurves.append(pCurve);
      loopReVFlags.append(OdBrepBuilder::kForward != coedge.direction);
    }
  }

  eStatus = OdGeExt::calcLoopIncludeOrder(loopIndices,
    *pSurfData->pSurf, OdBrepBuilder::kForward != pSurfData->direction, loops, revFlags, tol);
  if (eOk != eStatus || 1 == loopIndices.size())
    return checkRet(eStatus);

  m_loopsSplitted = true;
  for (OdGeIntArray::size_type iLoopSeq = 1; iLoopSeq < loopIndices.size(); ++iLoopSeq)
  {
    // create a new face and move loop into to it
    BrepBuilderInitialSurface& surfDataNew = *arrSurfaces.append();
    pSurfData = &arrSurfaces[currentFaceIdx];
    surfDataNew.copyFaceExceptLoops(*pSurfData);

    const OdGeIntArray& loopIds = loopIndices.getAt(iLoopSeq);
    for (OdGeIntArray::size_type iLoop = 0; iLoop < loopIds.size(); ++iLoop)
    {
      BrepBuilderInitialLoop& loop = pSurfData->loops[loopIds.getAt(iLoop)];
      loop.coedges.swap(surfDataNew.loops.append()->coedges);
    }
  }

  for (OdGeIntArray::size_type iLoop = 0; iLoop < pSurfData->loops.size();)
  {
    if (pSurfData->loops.getAt(iLoop).coedges.isEmpty())
      pSurfData->loops.removeAt(iLoop);
    else
      ++iLoop;
  }

  return checkRet(eOk);
}

OdResult OdBrepBuilderFillerHelper::findParentEdge(EdgeIndex edgeIdx, const OdArray<EdgeIndex>& parentEdgeIndices, EdgeIndex& parentIdx)
{
  const OdGeCurve3d* childCurve = m_initialData.edges[edgeIdx].curve;
  //find curve which contains childCurve
  for (unsigned i = 0; i < parentEdgeIndices.size(); ++i)
  {
    const OdGeCurve3d* parentCurve = m_initialData.edges[parentEdgeIndices[i]].curve;
    if (childCurve->type() != parentCurve->type())
      continue;
    OdGePoint3d startPoint, endPoint;
    if (!childCurve->hasStartPoint(startPoint))
      return eInvalidCurve;
    if (!parentCurve->isOn(startPoint, OdGeTol(m_toleranceCoincide, OdGeContext::gTol.equalVector())))
      continue;
    if (!childCurve->hasEndPoint(endPoint))
      return eInvalidCurve;
    if (!parentCurve->isOn(endPoint, OdGeTol(m_toleranceCoincide, OdGeContext::gTol.equalVector())))
      continue;
    const int numSamples = 10;
    for (int idxSample = 1; idxSample < numSamples; ++idxSample)
      if (!parentCurve->isOn(childCurve->midPoint(double(idxSample) / numSamples), OdGeTol(m_toleranceCoincide, OdGeContext::gTol.equalVector())))
        continue;
    parentIdx = parentEdgeIndices[i];
    return checkRet(eOk);
  }
  return checkRet(eGeneralModelingFailure);
}

bool OdBrepBuilderFillerHelper::needParamCurves() const
{
  return m_params.destinationBrepType() == OdBrepBuilderFillerParams::kBrepAcisDgn || m_params.destinationBrepType() == OdBrepBuilderFillerParams::kBrepAcisDwg;
}

OdResult OdBrepBuilderFillerHelper::fixFaceRegionsConnections(BrepBuilderInitialSurfaceArray& arrFaces)
{
  bool needPCurves = needParamCurves();
  if (!m_params.isSkipCoedge2dCurve())
    return checkRet(eNotImplemented);
  //edge idx -> (num coedges, one coedge index)
  OdHashMap<EdgeIndex, std::pair<unsigned, CoedgeIndex> > edgesCoedges;
  for (unsigned iFace = 0; iFace < arrFaces.size(); ++iFace)
  {
    for (unsigned iLoop = 0; iLoop < arrFaces[iFace].loops.size(); ++iLoop)
    {
      const BrepBuilderInitialLoop& loop = arrFaces[iFace].loops[iLoop];
      for (unsigned iCoedge = 0; iCoedge < loop.coedges.size(); ++iCoedge)
      {
        const BrepBuilderInitialCoedge& coedge = loop.coedges[iCoedge];
        std::pair<unsigned, CoedgeIndex>& edgeInfo = edgesCoedges[coedge.edgeIndex];
        ++edgeInfo.first;
        edgeInfo.second = CoedgeIndex(iFace, iLoop, iCoedge);
      }
    }
  }

  //map: parent edge idx -> (parent face idx, array of child's (edge idx, CoedgeIndex))
  typedef std::pair<OdUInt32, OdArray<EdgeCoedgeIndex> > ParentFaceAndChildEdges;
  OdHashMap<EdgeIndex, ParentFaceAndChildEdges> parentEdgesNotConnectedEdges[2];
  //connect parent edges with all child coedges, distributed to 2 parent faces
  for (OdHashMap<EdgeIndex, std::pair<unsigned, CoedgeIndex> >::iterator itEdge = edgesCoedges.begin(); itEdge != edgesCoedges.end(); ++itEdge)
  {
    EdgeIndex edgeIdx = itEdge->first;
    unsigned numCoedges = itEdge->second.first;
    //non manifold edges are forbidden
    if (numCoedges > 2)
      return checkRet(eNotImplemented);
    //fix only edges with 1 coedge
    if (numCoedges == 2)
      continue;
    const CoedgeIndex& coedgeIndex = itEdge->second.second;
    //parse only face regions
    OdUInt32 parentFaceIdx = arrFaces[coedgeIndex.faceIdx].parentFaceIdx;
    if (parentFaceIdx == -1)
      continue;
    const OdArray<EdgeIndex>& parentEdgeIndices = m_parentFacesEdgesIdx[parentFaceIdx];
    //TODO: it would be nice to find parent edge using GStep history, but it is complicated
    EdgeIndex parentEdgeIdx;
    OdResult res = findParentEdge(edgeIdx, parentEdgeIndices, parentEdgeIdx);
    if (eOk != res)
      return checkRet(res);
    for (int idx = 0; idx < 2; ++idx)
    {
      OdHashMap<EdgeIndex, ParentFaceAndChildEdges>::iterator it = parentEdgesNotConnectedEdges[idx].find(parentEdgeIdx);
      if (it == parentEdgesNotConnectedEdges[idx].end())
      {
        ParentFaceAndChildEdges parentFaceAndChildEdges;
        parentFaceAndChildEdges.first = parentFaceIdx;
        parentFaceAndChildEdges.second.push_back(std::make_pair(edgeIdx, coedgeIndex));
        parentEdgesNotConnectedEdges[idx][parentEdgeIdx] = parentFaceAndChildEdges;
        break;
      }
      else if (it->second.first == parentFaceIdx)
      {
        it->second.second.push_back(std::make_pair(edgeIdx, coedgeIndex));
        break;
      }
      else if (idx == 1)
      {
        //edge has more than 2 adjacent faces?
        return checkRet(eGeneralModelingFailure);
      }
    }
  }

  //split and connect edges
  while (!parentEdgesNotConnectedEdges[0].empty())
  {
    OdHashMap<OdUInt32, ParentFaceAndChildEdges>::iterator it[2];
    it[0] = parentEdgesNotConnectedEdges[0].begin();
    EdgeIndex parentEdgeIdx = it[0]->first;
    OdArray<EdgeCoedgeIndex>& edges = it[0]->second.second;
    it[1] = parentEdgesNotConnectedEdges[1].find(parentEdgeIdx);
    if (it[1] == parentEdgesNotConnectedEdges[1].end())
    {
      if (edgesCoedges[parentEdgeIdx].first == 0)
      {
        //boundary edge
        parentEdgesNotConnectedEdges[0].erase(it[0]);
        continue;
      }
      //coincident to already present edge
      OdResult res = sortEdges(arrFaces, edges);
      if (eOk != res)
        return checkRet(res);

      CoedgeIndex& parentIdx = edgesCoedges[parentEdgeIdx].second;
      BrepBuilderInitialLoop& parentLoop = arrFaces[parentIdx.faceIdx].loops[parentIdx.loopIdx];
      //parentIdx may be invalid now as we may have split some coedges, thus shifting coedgeIdx, so we are fixing it
      while (parentLoop.coedges[parentIdx.coedgeIdx].edgeIndex != parentEdgeIdx)
      {
        ++parentIdx.coedgeIdx;
        if (parentIdx.coedgeIdx >= parentLoop.coedges.size())
          return checkRet(eGeneralModelingFailure);
      }
      BrepBuilderInitialCoedge& parentCoedge = parentLoop.coedges[parentIdx.coedgeIdx];

      res = fixCoedgeIdx(arrFaces, edges.first().first, edges.first().second);
      if (res != eOk)
        return checkRet(res);
      const CoedgeIndex& idx = edges.first().second;
      BrepBuilderInitialCoedge& firstCoedge = arrFaces[idx.faceIdx].loops[idx.loopIdx].coedges[idx.coedgeIdx];
#ifdef ODA_DIAGNOSTICS
      const OdGeCurve3d* parentCurve = m_initialData.edges[parentCoedge.edgeIndex].curve;
      OdGePoint3d parentEndPoints[2];
      bool succ = parentCurve->hasStartPoint(parentEndPoints[0]) && parentCurve->hasEndPoint(parentEndPoints[1]);
      ODA_ASSERT(succ);
      if (parentCoedge.direction == OdBrepBuilder::kReversed)
        std::swap(parentEndPoints[0], parentEndPoints[1]);

      OdGePoint3d childEndPoints[2];
      for (int end = 0; end < 2; ++end)
      {
        CoedgeIndex idx = end == 0 ? edges.first().second : edges.last().second;
        const BrepBuilderInitialCoedge& endCoedge = arrFaces[idx.faceIdx].loops[idx.loopIdx].coedges[idx.coedgeIdx];
        const OdGeCurve3d* childCurve = m_initialData.edges[endCoedge.edgeIndex].curve;
        bool succ = ((endCoedge.direction == OdBrepBuilder::kForward) ^ (end == 1)) ? childCurve->hasStartPoint(childEndPoints[end]) : childCurve->hasEndPoint(childEndPoints[end]);
        ODA_ASSERT(succ);
      }
      ODA_ASSERT(parentEndPoints[0].isEqualTo(childEndPoints[1], m_toleranceDiffPoints));
      ODA_ASSERT(parentEndPoints[1].isEqualTo(childEndPoints[0], m_toleranceDiffPoints));
#endif

      //coedges must be oriented oppositely
      parentCoedge.edgeIndex = firstCoedge.edgeIndex;
      parentCoedge.direction = firstCoedge.direction == OdBrepBuilder::kForward ? OdBrepBuilder::kReversed : OdBrepBuilder::kForward;
      if (needPCurves && needPCurve(arrFaces[idx.faceIdx].pSurf))
      {
        OdResult eStatus = createParamCurve(arrFaces[idx.faceIdx].pSurf, m_initialData.edges[edges.first().first].curve, parentCoedge.curve);
        if (eOk != eStatus) {
          return checkRet(eStatus);
        }
      }

      //split parent coedge
      bool appendCoedgesAfter = parentCoedge.direction == OdBrepBuilder::kForward;
      for (unsigned i = 1; i < edges.size(); ++i)
      {
        res = fixCoedgeIdx(arrFaces, edges[i].first, edges[i].second);
        if (res != eOk)
          return checkRet(res);
        const CoedgeIndex& idx = edges[i].second;
        const BrepBuilderInitialCoedge& childCoedge = arrFaces[idx.faceIdx].loops[idx.loopIdx].coedges[idx.coedgeIdx];
        BrepBuilderInitialCoedge newParentCoedge = childCoedge;
        newParentCoedge.direction = childCoedge.direction == OdBrepBuilder::kForward ? OdBrepBuilder::kReversed : OdBrepBuilder::kForward;
        if (needPCurves && needPCurve(arrFaces[idx.faceIdx].pSurf))
        {
          OdResult eStatus = createParamCurve(arrFaces[idx.faceIdx].pSurf, m_initialData.edges[edges[i].first].curve, newParentCoedge.curve);
          if (eOk != eStatus) {
            return checkRet(eStatus);
          }
        }
        parentLoop.coedges.insertAt(appendCoedgesAfter ? parentIdx.coedgeIdx + 1 : parentIdx.coedgeIdx, newParentCoedge);
        appendCoedgesAfter ? ++parentIdx.coedgeIdx : --parentIdx.coedgeIdx;
      }
    }
    else {
      //both faces have face regions
      OdResult res = sortEdges(arrFaces, edges);
      if (eOk != res)
        return checkRet(res);
      OdArray<EdgeCoedgeIndex>& edgesOther = it[1]->second.second;
      res = sortEdges(arrFaces, edgesOther);
      if (eOk != res)
        return checkRet(res);
      
      OdArray<EdgeCoedgeIndex>* arrEdges[2] = { &edges, &edgesOther };
#ifdef ODA_DIAGNOSTICS
      OdGePoint3d endPoints[2][2];
      for (int side = 0; side < 2; ++side)
      {
        for (int end = 0; end < 2; ++end)
        {
          CoedgeIndex idx = end == 0 ? arrEdges[side]->first().second : arrEdges[side]->last().second;
          const BrepBuilderInitialCoedge& endCoedge = arrFaces[idx.faceIdx].loops[idx.loopIdx].coedges[idx.coedgeIdx];
          const OdGeCurve3d* curve = m_initialData.edges[endCoedge.edgeIndex].curve;
          bool succ = ((endCoedge.direction == OdBrepBuilder::kForward) ^ (end == 1)) ? curve->hasStartPoint(endPoints[side][end]) : curve->hasEndPoint(endPoints[side][end]);
          ODA_ASSERT(succ);
        }
      }
      ODA_ASSERT(endPoints[0][0].isEqualTo(endPoints[1][1], m_toleranceDiffPoints));
      ODA_ASSERT(endPoints[0][1].isEqualTo(endPoints[1][0], m_toleranceDiffPoints));
#endif
      int currEdgeIdx[2] = { 0, (int)edgesOther.size() - 1 };
      while (currEdgeIdx[0] < (int)edges.size())
      {
        EdgeCoedgeIndex* curEdge[2] = { &(*arrEdges[0])[currEdgeIdx[0]], &(*arrEdges[1])[currEdgeIdx[1]] };
        if (currEdgeIdx[1] < 0)
          return checkRet(eGeneralModelingFailure);
        for (int side = 0; side < 2; ++side)
        {
          res = fixCoedgeIdx(arrFaces, curEdge[side]->first, curEdge[side]->second);
          if (res != eOk)
            return checkRet(res);
        }
        CoedgeIndex idx[2] = { curEdge[0]->second, curEdge[1]->second };
        BrepBuilderInitialLoop* currLoop[2] = { &arrFaces[idx[0].faceIdx].loops[idx[0].loopIdx], &arrFaces[idx[1].faceIdx].loops[idx[1].loopIdx] };
        BrepBuilderInitialCoedge* currCoedge[2] = { &currLoop[0]->coedges[idx[0].coedgeIdx], &currLoop[1]->coedges[idx[1].coedgeIdx] };
        OdGeCurve3d* currCurve[2] = { m_initialData.edges[currCoedge[0]->edgeIndex].curve, m_initialData.edges[currCoedge[1]->edgeIndex].curve };
        OdGePoint3d currEndPoints[2];
        if (currCoedge[0]->direction == OdBrepBuilder::kForward ? !currCurve[0]->hasEndPoint(currEndPoints[0]) : !currCurve[0]->hasStartPoint(currEndPoints[0]))
          return checkRet(eInvalidCurve);
        if (currCoedge[1]->direction == OdBrepBuilder::kForward ? !currCurve[1]->hasStartPoint(currEndPoints[1]) : !currCurve[1]->hasEndPoint(currEndPoints[1]))
          return checkRet(eInvalidCurve);
#ifdef ODA_DIAGNOSTICS
        //start points should be equal
        OdGePoint3d currStartPoints[2];
        bool succ = currCoedge[0]->direction == OdBrepBuilder::kForward ? currCurve[0]->hasStartPoint(currStartPoints[0]) : currCurve[0]->hasEndPoint(currStartPoints[0]);
        ODA_ASSERT(succ);
        succ = currCoedge[1]->direction == OdBrepBuilder::kForward ? currCurve[1]->hasEndPoint(currStartPoints[1]) : currCurve[1]->hasStartPoint(currStartPoints[1]);
        ODA_ASSERT(succ);
        ODA_ASSERT(currStartPoints[0].isEqualTo(currStartPoints[1], m_toleranceDiffPoints));
#endif

        if (currEndPoints[0].isEqualTo(currEndPoints[1], m_toleranceDiffPoints))
        {
          //same edges, union them
          currCoedge[1]->edgeIndex = currCoedge[0]->edgeIndex;
          currCoedge[1]->direction = currCoedge[0]->direction == OdBrepBuilder::kForward ? OdBrepBuilder::kReversed : OdBrepBuilder::kForward;
          if (needPCurves && needPCurve(arrFaces[idx[1].faceIdx].pSurf))
          {
            OdResult eStatus = createParamCurve(arrFaces[idx[1].faceIdx].pSurf, m_initialData.edges[currCoedge[1]->edgeIndex].curve, currCoedge[1]->curve);
            if (eOk != eStatus) {
              return checkRet(eStatus);
            }
          }
          ++currEdgeIdx[0];
          --currEdgeIdx[1];
        }
        else
        {
          bool succ = false;
          for (int side = 0; side < 2; ++side)
          {
            double splitParam;
            if (currCurve[side]->isOn(currEndPoints[!side], splitParam, OdGeTol(m_toleranceDiffPoints, OdGeContext::gTol.equalVector())))
            {
              //'side' edge is longer than '!side', split 'side' into two
              //common part will get shorter edge, longer part will get its own edge with reduced interval
              OdGeInterval interval;
              currCurve[side]->getInterval(interval);
              if ((currCoedge[side]->direction == OdBrepBuilder::kForward) ^ (side == 1))
                interval.setLower(splitParam);
              else
                interval.setUpper(splitParam);
              currCurve[side]->setInterval(interval); //TODO: trim nurbs?

              BrepBuilderInitialCoedge newCoedge = *currCoedge[!side];
              newCoedge.direction = currCoedge[!side]->direction == OdBrepBuilder::kForward ? OdBrepBuilder::kReversed : OdBrepBuilder::kForward;
              if (needPCurves && needPCurve(arrFaces[idx[side].faceIdx].pSurf))
              {
                OdResult eStatus = createParamCurve(arrFaces[idx[side].faceIdx].pSurf, m_initialData.edges[newCoedge.edgeIndex].curve, newCoedge.curve);
                if (eOk != eStatus) {
                  return checkRet(eStatus);
                }
              }
              bool appendCoedgesAfter = (currCoedge[side]->direction == OdBrepBuilder::kForward) ^ (side == 0);
              currLoop[side]->coedges.insertAt(appendCoedgesAfter ? idx[side].coedgeIdx + 1 : idx[side].coedgeIdx, newCoedge);
              side == 0 ? --currEdgeIdx[1] : ++currEdgeIdx[0];
              succ = true;
              break;
            }
          }
          if (!succ)
            return checkRet(eGeneralModelingFailure);
        }
      }
      if (currEdgeIdx[1] != -1)
        return checkRet(eGeneralModelingFailure);
    }
    parentEdgesNotConnectedEdges[0].erase(it[0]);
  }
  return checkRet(eOk);
}

//coedgeIndex.coedgeIdx may be invalid as we may have split some coedges, thus shifting coedgeIdx, so we are fixing it
OdResult OdBrepBuilderFillerHelper::fixCoedgeIdx(const BrepBuilderInitialSurfaceArray& arrFaces, OdUInt32 edgeIdx, CoedgeIndex& coedgeIndex)
{
  const BrepBuilderInitialLoop& loop = arrFaces[coedgeIndex.faceIdx].loops[coedgeIndex.loopIdx];
  while (loop.coedges[coedgeIndex.coedgeIdx].edgeIndex != edgeIdx)
  {
    ++coedgeIndex.coedgeIdx;
    if (coedgeIndex.coedgeIdx >= loop.coedges.size())
      return checkRet(eGeneralModelingFailure);
  }
  return checkRet(eOk);
}

OdResult OdBrepBuilderFillerHelper::sortEdges(const BrepBuilderInitialSurfaceArray& arrFaces, OdArray<EdgeCoedgeIndex>& edges)
{
  OdResult res;
  for (int i = 0; i < (int)edges.size(); ++i)
  {
    res = fixCoedgeIdx(arrFaces, edges[i].first, edges[i].second);
    if (res != eOk)
      return checkRet(res);
  }
  //I assume that coedges on one parent face should be codirectional
  int endIdx = -1;
  for (int dir = 1; dir >= -1; dir -= 2)
  {
    //connect end points with start points
    for (int i = (dir == 1 ? 0 : endIdx); dir == 1 ? (i < (int)edges.size() - 1) : (i > 0); i += dir)
    {
      CoedgeIndex idx = edges[i].second;
      const BrepBuilderInitialCoedge& iCoedge = arrFaces[idx.faceIdx].loops[idx.loopIdx].coedges[idx.coedgeIdx];
      const OdGeCurve3d* iCurve = m_initialData.edges[edges[i].first].curve;
      OdGePoint3d endPoint;
      if (((iCoedge.direction == OdBrepBuilder::kForward) ^ (dir == -1)) ? !iCurve->hasEndPoint(endPoint) : !iCurve->hasStartPoint(endPoint))
        return checkRet(eInvalidCurve);
      bool connected = false;
      for (int j = i + dir; dir == 1 ? (j < (int)edges.size()) : (j >= 0); j += dir)
      {
        idx = edges[j].second;
        const BrepBuilderInitialCoedge& jCoedge = arrFaces[idx.faceIdx].loops[idx.loopIdx].coedges[idx.coedgeIdx];
        const OdGeCurve3d* jCurve = m_initialData.edges[edges[j].first].curve;
        OdGePoint3d startPoint;
        if (((jCoedge.direction == OdBrepBuilder::kForward) ^ (dir == -1)) ? !jCurve->hasStartPoint(startPoint) : !jCurve->hasEndPoint(startPoint))
          return checkRet(eInvalidCurve);
        if (startPoint.isEqualTo(endPoint, m_toleranceDiffPoints))
        {
          std::swap(edges[i + dir], edges[j]);
          connected = true;
          break;
        }
      }
      if (!connected)
        if (endIdx != -1)
          return checkRet(eGeneralModelingFailure); //can't create a coedges chain
        else
          endIdx = i;
    }
    if (endIdx == -1)
      break;
    OdArray<EdgeCoedgeIndex> shiftedEdges;
    shiftedEdges.resize(edges.size());
    for (int i = 0; i <= endIdx; ++i)
      shiftedEdges[i + edges.size() - (endIdx + 1)] = edges[i];
    for (int i = endIdx + 1; i < (int)edges.size(); ++i)
      shiftedEdges[i - (endIdx + 1)] = edges[i];
    edges.swap(shiftedEdges);
    endIdx = edges.size() - (endIdx + 1);
  }
  return checkRet(eOk);
}

// Topology
OdResult OdBrepBuilderFillerHelper::performBrep(const OdBrBrep& brep)
{
  ODA_ASSERT_ONCE(brep.isValid());

  OdBrBrepComplexTraverser complxTrav;
  OdBrErrorStatus errStatus = complxTrav.setBrep(brep);
  if (odbrOK != errStatus) {
    return checkRet(eBrComplexMissed);
  }

  while (!complxTrav.done())
  {
    OdBrComplex complex = complxTrav.getComplex();

    OdResult res = performComplex(complex);
    if (eOk != res) {
      return checkRet(res);
    }

    if (odbrOK != complxTrav.next()) {
      return checkRet(eNullIterator);
    }
  }

  return checkRet(eOk);
}

OdResult OdBrepBuilderFillerHelper::performComplex(const OdBrComplex& complex)
{
  OdBrComplexShellTraverser complxShellTrav;
  OdBrErrorStatus errStatus = complxShellTrav.setComplex(complex);
  if (odbrUnsuitableTopology == errStatus) {
    return checkRet(eOk);
  }
  if (odbrOK != errStatus) {
    return checkRet(eBrComplexMissed);
  }

  BrepBuilderShellsArray shells;
  while (!complxShellTrav.done())
  {
    OdBrShell shell = complxShellTrav.getShell();

    OdResult res = performShell(shell, shells);
    if (eOk != res) {
      return checkRet(res);
    }

    if (odbrOK != complxShellTrav.next()) {
      return checkRet(eNullIterator);
    }
  }
  m_initialData.complexes.append(shells);

  return checkRet(eOk);
}

OdResult OdBrepBuilderFillerHelper::performShell(const OdBrShell& shell, BrepBuilderShellsArray& arrShells)
{
  OdBrShellFaceTraverser shellFaceTrav;
  OdBrErrorStatus errStatus = shellFaceTrav.setShell(shell);
  if (odbrUnsuitableTopology == errStatus) {
    return checkRet(eOk);
  }
  if (odbrOK != errStatus) {
    return checkRet(eBrShellMissed);
  }

  bool bCheckFaces = false;
  m_edgesAdded.clear();
  BrepBuilderInitialSurfaceArray arrSurfaces;
  unsigned int oldParentFaceIdx = m_parentFacesEdgesIdx.size();
  m_loopsSplitted = false;
  while (!shellFaceTrav.done())
  {
    OdBrFace face = shellFaceTrav.getFace();
    unsigned int numFacesOld = arrSurfaces.length();
    unsigned int parentFaceIdx = m_parentFacesEdgesIdx.size();

    OdResult res = performFace(face, arrSurfaces);
    if (eOk != res) {
      return checkRet(res);
    }

    if (m_params.isFixFaceRegionsConnections() && m_parentFacesEdgesIdx.size() != parentFaceIdx)
      for (unsigned i = numFacesOld; i < arrSurfaces.length(); ++i)
        arrSurfaces[i].parentFaceIdx = parentFaceIdx;

    if (odbrOK != shellFaceTrav.next()) {
      return checkRet(eNullIterator);
    }
  }
  if (m_params.isFixFaceRegionsConnections() && m_parentFacesEdgesIdx.size() != oldParentFaceIdx)
  {
    OdResult res = fixFaceRegionsConnections(arrSurfaces);
    if (eOk != res)
      return checkRet(res);
  }
  if (m_loopsSplitted || m_params.isCheckShellsConnectivity())
  {
    //detect connected faces and move it to logical groups. Each of this group should be in separate shell
    OdArray<OdUInt32Array> groupedFaces;
    groupFaces(arrSurfaces, groupedFaces);
    for (unsigned int i = 0; i < groupedFaces.length(); ++i)
    {
      BrepBuilderInitialSurfaceArray arrNewSurfaces;
      for (unsigned int j = 0; j < groupedFaces[i].length(); ++j)
      {
        arrNewSurfaces.append(arrSurfaces[groupedFaces[i][j]]);
      }
      arrShells.append(arrNewSurfaces);
    }
    return checkRet(eOk);
  }
  arrShells.append(arrSurfaces);

  return checkRet(eOk);
}

OdResult OdBrepBuilderFillerHelper::getFaceEdges(const OdBrFace& face, OdArray<EdgeIndex>& faceCurvesIdx)
{
  OdBrFaceLoopTraverser faceLoopTrav;
  OdBrErrorStatus err = faceLoopTrav.setFace(face);
  if (err != eOk) {
    return checkRet(eNotApplicable);
  }
  while (!faceLoopTrav.done())
  {
    OdBrLoop loop = faceLoopTrav.getLoop();

    OdBrLoopEdgeTraverser loopEdgeTrav;
    err = loopEdgeTrav.setLoop(loop);
    if (odbrOK != err) {
      return checkRet(eNotApplicable);
    }
    while (!loopEdgeTrav.done())
    {
      OdBrEdge edge = loopEdgeTrav.getEdge();
      unsigned edgeIdx;
      OdGeCurve3d* curve;
      OdResult res = performEdge(edge, edgeIdx, curve);
      if (eOk != res) {
        return checkRet(res);
      }
      faceCurvesIdx.push_back(edgeIdx); 
      if (odbrOK != loopEdgeTrav.next()) {
        return checkRet(eNullIterator);
      }
    }
    if (odbrOK != faceLoopTrav.next()) {
      return checkRet(eNullIterator);
    }
  }
  return checkRet(eOk);
}

OdResult OdBrepBuilderFillerHelper::performFace(const OdBrFace& face, BrepBuilderInitialSurfaceArray& arrSurfaces)
{
  if (m_params.isUseFaceRegions())
  {
    OdBrFace faceRegion;
    if (face.getFirstFaceRegion(faceRegion))
    {
      if (m_params.isFixFaceRegionsConnections())
      {
        getFaceEdges(face, *m_parentFacesEdgesIdx.append());
      }
      do
      {
        //can face regions have their own sub regions?
        OdResult res = performFace(faceRegion, arrSurfaces);
        if (eOk != res) {
          return checkRet(res);
        }
      } while (face.getNextFaceRegion(faceRegion));
      return checkRet(eOk);
    }
  }

  OdResult eStatus;
  BrepBuilderInitialSurface surfData;
  surfData.pSurf = getFaceSurface(face);
  if (surfData.pSurf.isNull())
  {
    // skip face without surface
    if (m_params.isSkipNullSurface()) {
      return checkRet(eOk);
    }
    return checkRet(eNullFaceSurface);
  }
  fixEllipConeRRatio(surfData.pSurf);

  // face direction
  surfData.direction = face.getOrientToSurface() ? OdBrepBuilder::kForward : OdBrepBuilder::kReversed;

  if (m_params.isSetFaceGsMarkersTags())
    surfData.marker.first = odbrOK == face.getGsMarker(surfData.marker.second);

  // face visual
  eStatus = surfData.setupVisualInfo(face, m_pMaterialHelper);
  if (eOk != eStatus) {
    return checkRet(eStatus);
  }

  OdBrFaceLoopTraverser faceLoopTrav;
  OdBrErrorStatus err = faceLoopTrav.setFace(face);
  if (odbrUnsuitableTopology == err)
  {
    if (m_params.isGenerateExplicitLoops())
    {
      eStatus = addFaceExplicitLoop(surfData, face);
      if (eStatus != eOk) {
        ODA_FAIL_M_ONCE("Face without loops - unsupported case");
      }
    }
    // Face without loops (sphere, torus)
    arrSurfaces.append(surfData);
    return checkRet(eOk);
  }
  if (odbrOK != err) {
    return checkRet(eBrFaceMissed);
  }

  while (!faceLoopTrav.done())
  {
    OdBrLoop loop = faceLoopTrav.getLoop();
    eStatus = performLoop(loop, surfData);
    if (eOk != eStatus) {
      return checkRet(eStatus);
    }

    if (odbrOK != faceLoopTrav.next()) {
      return checkRet(eNullIterator);
    }
  }

  arrSurfaces.append(surfData);

  if (m_params.isSkipCheckLoopType()) {
    return checkRet(eOk);
  }

  return checkRet(splitOuterLoops(arrSurfaces));
}

OdResult OdBrepBuilderFillerHelper::performLoop(const OdBrLoop& loop,
  BrepBuilderInitialSurface& surfData)
{
  OdBrErrorStatus err;
  OdBrLoopEdgeTraverser loopEdgeTrav;
  err = loopEdgeTrav.setLoop(loop);

  // Loop with apex:
  if (odbrDegenerateTopology == err) // maybe there should be odbrUnsuitableTopology (see arx)
  {
    OdGeCurve3dPtr curve;
    OdGeCurve2dPtr paramCurve;
    OdBrVertex vertex;
    OdResult resStatus = performLoopWithApex(loop, curve, paramCurve, &vertex);
    if (eOk == resStatus)
    {
      BrepBuilderInitialEdge::VertexIndex vertexIndex = addVertex(vertex);

      m_initialData.edges.append(BrepBuilderInitialEdge(curve, vertexIndex, vertexIndex));
      surfData.loops.append(BrepBuilderInitialLoop(
        paramCurve,
        m_initialData.edges.size() - 1, // stub edge for correct index
        OdBrepBuilder::kForward
      ));

      return checkRet(eOk);
    }
    return checkRet(resStatus);
  }
  if (odbrOK != err) {
    return checkRet(eBrEmptyLoop);
  }

  // Regular loop:
  BrepBuilderInitialLoop loopData;

  while (!loopEdgeTrav.done())
  {
    OdBrEdge edge = loopEdgeTrav.getEdge();
    BrepBuilderInitialCoedge& coedgeData = *loopData.coedges.append();
    unsigned edgeIdx;
    OdGeCurve3d* curve;
    OdResult res = performEdge(edge, edgeIdx, curve);
    coedgeData.edgeIndex = edgeIdx;
    if (eOk != res)
      return checkRet(res);

    if (!m_params.isSkipCoedge2dCurve())
    {
      coedgeData.curve = getParamCurve(loopEdgeTrav);
      // acis bb required 2d coedge curve for SPLINE surface(ruled, spun etc - are SPLINE surfaces)
      ODA_ASSERT_ONCE(curve);
      ODA_ASSERT_ONCE(!surfData.pSurf.isNull());
      if (coedgeData.curve.isNull() && (needPCurve(surfData.pSurf)))
      {
        coedgeData.curve = restoreUvCurveAsNurb(curve, surfData.pSurf, m_toleranceRestore2dCurve);
        if (coedgeData.curve.isNull()) {
          return checkRet(eCreateFailed);
        }
      }

      OdResult eStatus = fixParamCurve(surfData.pSurf, curve, coedgeData.curve);
      //if surface is analytic-defined (cone, plane etc.) parametric curves may not required
      //so if we have such surface (any but not a spline) and 2d curve is "wrong" (wrong interval or direction)
      //this 2d curve may be detached and will not given to brep builder
      if (eOk != eStatus)
      {
        if (!needPCurve(surfData.pSurf)) {
          coedgeData.curve = OdGeCurve2dPtr();
        }
        else if (eCreateFailed == eStatus)
        {//already tried create parcur
          return checkRet(eStatus);
        }
        else
        {
          eStatus = createParamCurve(surfData.pSurf, curve, coedgeData.curve);
          if (eOk != eStatus)
          {
            return checkRet(eStatus);
          }
        }
      }
    }
    else if (needParamCurves())
    {
      //we reject input parametric curves but if output data is a ACIS - parametric curves should used in some cases
      //so we reject input and create own
      ODA_ASSERT_ONCE(curve);
      ODA_ASSERT_ONCE(!surfData.pSurf.isNull());
      if (needPCurve(surfData.pSurf))
      {
        OdResult eStatus = createParamCurve(surfData.pSurf, curve, coedgeData.curve);
        if (eOk != eStatus) {
          return checkRet(eStatus);
        }
      }
    }
    coedgeData.direction = (edge.getOrientToCurve() == loopEdgeTrav.getEdgeOrientToLoop())
      ? OdBrepBuilder::kForward : OdBrepBuilder::kReversed;

    if (odbrOK != loopEdgeTrav.next()) {
      return checkRet(eNullIterator);
    }
  }

  // skip loop without coedge
  if (!loopData.coedges.empty()) {
    surfData.loops.append(loopData);
  }

  return checkRet(eOk);
}

OdResult OdBrepBuilderFillerHelper::performEdge(const OdBrEdge& edge, unsigned& edgeIdx, OdGeCurve3d*& curve)
{
  bool isNewEdge = true;

  OdHashMap<OdUInt64, OdUInt32>::const_iterator pIt = m_edges.find(edge.getUniqueId());
  if (pIt != m_edges.end())
  {
    isNewEdge = false;
    edgeIdx = pIt->second;
    curve = m_initialData.edges[edgeIdx].curve;
  }

  if (isNewEdge)
  {
    OdGeCurve3dPtr curvePtr;
    OdResult resStatus = getEdgeCurveFixed(edge, curvePtr);
    curve = curvePtr.get();
    if (eOk != resStatus) {
      return checkRet(resStatus);
    }

    OdBrVertex vertices[2];
    bool res[2];
    res[0] = m_params.isGenerateVertices() && edge.getVertex1(vertices[0]);
    res[1] = m_params.isGenerateVertices() && edge.getVertex2(vertices[1]);
    if (res[0] && res[1] && !edge.getOrientToCurve())
    {
      std::swap(vertices[0], vertices[1]);
    }
    BrepBuilderInitialEdge::VertexIndex vertexIndex[2];
    for (int idx = 0; idx < 2; ++idx)
    {
      vertexIndex[idx] = res[idx] ? addVertex(vertices[idx]) : BrepBuilderInitialEdge::kInvalidIndex;
    }

    m_initialData.edges.append(BrepBuilderInitialEdge(curvePtr, vertexIndex[0], vertexIndex[1]));
    BrepBuilderInitialEdge& edgeData = m_initialData.edges.last();
    edgeIdx = m_initialData.edges.size() - 1;
    m_edges[edge.getUniqueId()] = edgeIdx;

    // edge visual
    OdResult eStatus = edgeData.setupVisualInfo(edge, m_pMaterialHelper);
    if (eOk != eStatus) {
      return checkRet(eStatus);
    }
    if (m_params.isSetEdgeGsMarkersTags())
      edgeData.marker.first = odbrOK == edge.getGsMarker(edgeData.marker.second);
  }
  return checkRet(eOk);
}

//TODO: we should, probably, union shells with a common vertex, not only a common edge
void OdBrepBuilderFillerHelper::groupFaces(BrepBuilderInitialSurfaceArray& arrFaces, OdArray<OdUInt32Array>& groupedFaces)
{
  //create map between edges and their faces
  OdHashMap<OdUInt32, OdUInt32Array> edgesFaces;
  for (OdUInt32 faceIdx = 0; faceIdx < arrFaces.length(); ++faceIdx)
  {
    const BrepBuilderInitialLoopArray& loops = arrFaces[faceIdx].loops;
    for (OdUInt32 loopIdx = 0; loopIdx < loops.length(); ++loopIdx)
    {
      const BrepBuilderInitialCoedgeArray& coedges = loops[loopIdx].coedges;
      for (OdUInt32 coedgeIdx = 0; coedgeIdx < coedges.length(); ++coedgeIdx)
      {
        edgesFaces[coedges[coedgeIdx].edgeIndex].append(faceIdx);
      }
    }
  }

  OdHashSet<OdUInt32> usedFaces;
  for (OdUInt32 faceIdx = 0; faceIdx < arrFaces.length(); ++faceIdx)
  {
    if (usedFaces.find(faceIdx) != usedFaces.end()) {
      continue;
    }
    OdUInt32Array facesIndices;
    findAdjacentFaces(arrFaces, usedFaces, edgesFaces, faceIdx, facesIndices);
    groupedFaces.push_back(facesIndices);
  }
}

void OdBrepBuilderFillerHelper::findAdjacentFaces(BrepBuilderInitialSurfaceArray& arrFaces, OdHashSet<OdUInt32>& usedFaces,
  const OdHashMap<OdUInt32, OdUInt32Array>& edgesFaces, OdUInt32 iCurrFace, OdUInt32Array& facesIndexes)
{
  usedFaces.insert(iCurrFace);
  facesIndexes.append(iCurrFace);
  const BrepBuilderInitialSurface& currFace = arrFaces[iCurrFace];
  OdHashSet<OdUInt32> adjacentEdges;
  for (OdUInt32 i = 0; i < currFace.loops.length(); ++i)
  {
    const BrepBuilderInitialCoedgeArray& arrCurrLoopCoedges = currFace.loops[i].coedges;
    for (OdUInt32 j = 0; j < arrCurrLoopCoedges.length(); ++j) {
      adjacentEdges.insert(arrCurrLoopCoedges[j].edgeIndex);
    }
  }
  for (OdHashSet<OdUInt32>::iterator it = adjacentEdges.begin(); it != adjacentEdges.end(); ++it)
  {
    OdHashMap<OdUInt32, OdUInt32Array>::const_iterator facesArr = edgesFaces.find(*it); //no at() in __gnu_cxx::hash_map :(
    for (OdUInt32 j = 0; j < facesArr->second.length(); ++j)
    {
      OdUInt32 faceIdx = facesArr->second[j];
      if (usedFaces.find(faceIdx) != usedFaces.end()) {
        continue;
      }
      findAdjacentFaces(arrFaces, usedFaces, edgesFaces, faceIdx, facesIndexes);
    }
  }
}


/*static*/ OdResult OdBrepBuilderFillerHelper::initFromImpl(OdBrepBuilderFiller& filler, OdBrepBuilder& builder, const BrepBuilderInitialData& data)
{
  OdResult status = eOk;

  OdArray<BRepBuilderGeometryId> verticesIds(data.vertices.size());
  for (BrepBuilderInitialEdge::VertexIndex i = 0; i < data.vertices.size(); ++i)
  {
    const BrepBuilderInitialVertex& vertexData = data.vertices[i];
    verticesIds.append(builder.addVertex(vertexData.point));
    if (vertexData.marker.first) {
      assertGsMarkerValue(vertexData.marker.second);
      builder.setTag(verticesIds.last(), static_cast<OdUInt32>(vertexData.marker.second));
    }
  }

  filler.m_edges.reserve(data.edges.size());
  OdArray<BRepBuilderGeometryId> edgeIds(data.edges.size());
  for (BrepBuilderInitialCoedge::EdgeIndex i = 0; i < data.edges.size(); ++i)
  {
    const BrepBuilderInitialEdge& edgeData = data.edges[i];
    filler.m_edges.append(edgeData.curve);
    BRepBuilderGeometryId vertexIndex[2] = { OdBrepBuilder::kDefaultVertexId, OdBrepBuilder::kDefaultVertexId };
    for (int idx = 0; idx < 2; ++idx)
    {
      if (edgeData.vertexIndex[idx] != BrepBuilderInitialEdge::kInvalidIndex)
      {
        vertexIndex[idx] = verticesIds[edgeData.vertexIndex[idx]];
      }
    }
    edgeIds.append(builder.addEdge(edgeData.curve, vertexIndex[0], vertexIndex[1]));
    if (edgeData.marker.first) {
      assertGsMarkerValue(edgeData.marker.second);
      builder.setTag(edgeIds.last(), static_cast<OdUInt32>(edgeData.marker.second));
    }

    if (edgeData.hasColor)
    {
      status = builder.setEdgeColor(edgeIds.last(), edgeData.color);
      if (eOk != status) {
        return checkRet(status);
      }
    }
  }

  const bool addComplexShell = !filler.m_params.isIgnoreComplexShell();
  for (BrepBuilderComplexArray::const_iterator complexIt = data.complexes.begin(); complexIt != data.complexes.end(); ++complexIt)
  {
    BRepBuilderGeometryId currentComplexId = 0;
    if (addComplexShell) {
      currentComplexId = builder.addComplex();
    }

    for (BrepBuilderShellsArray::const_iterator shellIt = complexIt->begin(); shellIt != complexIt->end(); ++shellIt)
    {
      BRepBuilderGeometryId currentShellId(OdBrepBuilder::kDefaultShellId);
      if (addComplexShell) {
        currentShellId = builder.addShell(currentComplexId);
        ODA_ASSERT_ONCE(currentShellId != OdBrepBuilder::kDefaultShellId);
      }

      for (BrepBuilderInitialSurfaceArray::const_iterator surfIt = shellIt->begin(); surfIt != shellIt->end(); ++surfIt)
      {
        filler.m_surfaces.append(surfIt->pSurf);
        BRepBuilderGeometryId currentFaceId = builder.addFace(surfIt->pSurf, surfIt->direction, currentShellId);
        if (surfIt->marker.first) {
          assertGsMarkerValue(surfIt->marker.second);
          builder.setTag(currentFaceId, static_cast<OdUInt32>(surfIt->marker.second));
        }
        if (surfIt->material) {
          builder.setFacesMaterial(currentFaceId, *surfIt->material);
        }
        if (surfIt->hasMaterialMapping)
        {
          status = builder.setFaceMaterialMapping(currentFaceId, surfIt->materialMapper);
          if (eOk != status) {
            return checkRet(status);
          }
        }
        if (surfIt->hasColor)
        {
          status = builder.setFaceColor(currentFaceId, surfIt->color);
          if (eOk != status) {
            return checkRet(status);
          }
        }

        const BrepBuilderInitialLoopArray& loops = surfIt->loops;
        for (BrepBuilderInitialLoopArray::const_iterator loopIt = loops.begin(); loopIt != loops.end(); ++loopIt)
        {
          BRepBuilderGeometryId currentLoopId = builder.addLoop(currentFaceId);

          const BrepBuilderInitialCoedgeArray& coedges = loopIt->coedges;
          for (BrepBuilderInitialCoedgeArray::const_iterator coedgeIt = coedges.begin(); coedgeIt != coedges.end(); ++coedgeIt)
          {
            filler.m_coedges.append(coedgeIt->curve);
            builder.addCoedge(currentLoopId, edgeIds[coedgeIt->edgeIndex], coedgeIt->direction, coedgeIt->curve);
          }

          builder.finishLoop(currentLoopId);
        }

        builder.finishFace(currentFaceId);
      }

      if (addComplexShell) {
        builder.finishShell(currentShellId);
      }
    }
    if (addComplexShell) {
      builder.finishComplex(currentComplexId);
    }
  }

  return checkRet(status);
}


/*static*/  OdResult OdBrepBuilderFillerHelper::getDataFrom(
  BrepBuilderInitialData& data,
  const OdBrepBuilderFiller& filler,
  const OdBrBrep& brep,
  OdIMaterialAndColorHelper* materialHelper)
{
  if (!brep.isValid()) {
    return OdBrepBuilderFillerHelper::checkRet(eNotInitializedYet);
  }

  OdResult status = eOk;
  try {
    if (materialHelper) {
      status = materialHelper->init(filler.params());
      if (eOk != status) {
        return OdBrepBuilderFillerHelper::checkRet(status);
      }
    }

    OdBrepBuilderFillerHelper brepBuilderFillerHelper(data, filler, materialHelper);
    status = brepBuilderFillerHelper.performBrep(brep);
  }
  catch (const OdError& err) {
    return OdBrepBuilderFillerHelper::checkRet(err.code());
  }
  catch (...) {
    return OdBrepBuilderFillerHelper::checkRet(eGeneralModelingFailure);
  }
  return OdBrepBuilderFillerHelper::checkRet(status);
}

//

OdResult OdBrepBuilderFiller::initFrom(OdBrepBuilder& builder, const BrepBuilderInitialData& data)
{
  if (!builder.isValid()) {
    return OdBrepBuilderFillerHelper::checkRet(eNotInitializedYet);
  }
  // TODO check can add geom (not implemented now)
  //if (!builder.canAddGeometry()) {
  //  return OdBrepBuilderFillerHelper::checkRet(eInvalidInput);
  //}

  clearTempArrays();

  OdResult status = eOk;
  try {
    status = OdBrepBuilderFillerHelper::initFromImpl(*this, builder, data);
  }
  catch (const OdError& err) {
    return OdBrepBuilderFillerHelper::checkRet(err.code());
  }
  catch (...) {
    return OdBrepBuilderFillerHelper::checkRet(eGeneralModelingFailure);
  }

  return OdBrepBuilderFillerHelper::checkRet(status);
}

OdResult OdBrepBuilderFiller::initFrom(OdBrepBuilder& builder, const OdBrBrep& brep,
  OdIMaterialAndColorHelper* materialHelper)
{
  BrepBuilderInitialData initData;
  OdResult status = OdBrepBuilderFillerHelper::getDataFrom(initData, *this, brep, materialHelper);
  if (eOk != status) {
    return OdBrepBuilderFillerHelper::checkRet(status);
  }

  return OdBrepBuilderFillerHelper::checkRet(initFrom(builder, initData));
}


OdResult OdBrepBuilderFiller::initFromNURBSingleFace(OdBrepBuilder& builder, const OdBrBrep& brep)
{
  clearTempArrays();

  try
  {
    OdBrErrorStatus err = odbrOK;
    OdBrBrepFaceTraverser bft;
    BrepBuilderInitialData ignore;
    OdBrepBuilderFillerHelper fillerHelper(ignore, *this);
    if (bft.setBrep(brep) != odbrOK)
    {
      return eBrBrepMissed;
    }
    while (!bft.done() && (err == odbrOK))
    {
      OdBrFaceLoopTraverser faLoTrav;
      OdBrFace face = bft.getFace();
      OdGeNurbSurface *pNurbSurf = new OdGeNurbSurface;
      face.getSurfaceAsNurb(*pNurbSurf);
      m_surfaces.append(pNurbSurf);

      //add nurbs surface to BB
      bool bOrientToSurface = face.getOrientToSurface();
      BRepBuilderGeometryId complexId = builder.addComplex();
      BRepBuilderGeometryId shellId = builder.addShell(complexId);
      BRepBuilderGeometryId faceId = builder.addFace(pNurbSurf, bOrientToSurface ? OdBrepBuilder::kForward : OdBrepBuilder::kReversed, shellId);
      //iterate over trimming-loop and create data for BB
      for (faLoTrav.setFace(face); !faLoTrav.done(); faLoTrav.next())
      {
        BRepBuilderGeometryId LoopId = builder.addLoop(faceId);
        OdBrLoopEdgeTraverser loEdTrav;
        OdBrLoop loop = faLoTrav.getLoop();
        err = loEdTrav.setLoop(loop);
        if (odbrDegenerateTopology == err)
        {
          OdGeCurve3dPtr pCurve3d;
          OdGeCurve2dPtr pCurve2d;
          OdResult resStatus = fillerHelper.performLoopWithApex(loop, pCurve3d, pCurve2d);
          if (eOk == resStatus)
          {
            m_edges.append(pCurve3d);
            m_coedges.append(pCurve2d);
            BRepBuilderGeometryId edgeId = builder.addEdge(pCurve3d);
            builder.addCoedge(LoopId, edgeId, OdBrepBuilder::kForward, pCurve2d);
            err = odbrOK;
            continue;
          }
          return resStatus;
        }

        OdArray<OdBrEdge> arrBrepEdges;
        OdArray<BRepBuilderGeometryId> arrBrepEdgesID;
        for (; !loEdTrav.done(); loEdTrav.next())
        {
          OdBrEdge edge = loEdTrav.getEdge();
          unsigned int iFindIndex = 0;
          bool bFindEdge = false;
          for (unsigned int k = 0; k < arrBrepEdges.size(); k++)
          {
            if (edge.isEqualTo(&arrBrepEdges[k]))
            {
              //In case of nurbs cone we have one edge and 2 coedges, but brep returns 2 edges
              iFindIndex = k;
              bFindEdge = true;
              break;
            }
          }

          bool bEdgeForward = edge.getOrientToCurve();
          bool bCoedgeForward = loEdTrav.getEdgeOrientToLoop();

          OdGeCurve3dPtr pCurve3d;
          OdResult resStatus = fillerHelper.getEdgeCurveFixed(edge, pCurve3d);
          if (eOk != resStatus)
          {
            return resStatus;
          }
          m_edges.append(pCurve3d);
          OdGeCurve2dPtr pCurve2d = fillerHelper.getParamCurve(loEdTrav);

          OdGeSurfacePtr surface = m_surfaces.first();
          resStatus = fillerHelper.fixParamCurve(surface, pCurve3d, pCurve2d);
          //if surface is analytic-defined (cone, plane etc.) parametric curves may not required
          //so if we have such surface (any but not a spline) and 2d curve is "wrong" (wrong interval or direction)
          //this 2d curve may be detached and will not given to brep builder
          if (eOk != resStatus)
          {
            if (OdBrepBuilderFillerHelper::needPCurve(surface))
            {
              return resStatus;
            }
            else
            {
              pCurve2d = OdGeCurve2dPtr();
            }
          }
          m_coedges.append(pCurve2d);
          BRepBuilderGeometryId edgeId;
          if (!bFindEdge)
          {
            edgeId = builder.addEdge(pCurve3d);
            builder.addCoedge(LoopId, edgeId, bCoedgeForward ? OdBrepBuilder::kForward : OdBrepBuilder::kReversed, pCurve2d);
            arrBrepEdgesID.append(edgeId);
            arrBrepEdges.append(edge);
          }
          else
          {
            builder.addCoedge(LoopId, arrBrepEdgesID.at(iFindIndex), bCoedgeForward ? OdBrepBuilder::kForward : OdBrepBuilder::kReversed, pCurve2d);
          }
        }
      }
      builder.finishFace(faceId);
      builder.finishShell(shellId);
      builder.finishComplex(complexId);
      break;//Only one face
    }
  }
  catch (const OdError& err)
  {
    throw err;
  }
  catch (...)
  {
    return eInvalidInput;
  }
  return eOk;
}

void OdBrepBuilderFiller::clearTempArrays()
{
  m_edges.clear();
  m_coedges.clear();
  m_surfaces.clear();
}

// Member methods of BrepBuilderInitialData.h classes
OdResult BrepBuilderInitialSurface::setupVisualInfo(const OdBrFace& face, OdIMaterialAndColorHelper* pMaterialHelper)
{
  if (!pMaterialHelper) return eOk;
  return pMaterialHelper->getFaceVisualInfo(face, material, materialMapper, hasMaterialMapping, color, hasColor);
}

OdResult BrepBuilderInitialEdge::setupVisualInfo(const OdBrEdge& edge, OdIMaterialAndColorHelper* pMaterialHelper)
{
  if (!pMaterialHelper) return eOk;
  return pMaterialHelper->getEdgeVisualInfo(edge, color, hasColor);
}
