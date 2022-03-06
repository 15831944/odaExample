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

#ifndef _DUMMYMODELERGEOMETRY_INCLUDED_
#define _DUMMYMODELERGEOMETRY_INCLUDED_

#include "ModelerGeometry.h"
#include "ModelerDefs.h"
#include "MemoryStreamImpl.h"
#include "MemoryStream.h"
#include "StaticRxObject.h"

#if defined(_MSC_VER)
#pragma warning ( disable : 4100 ) //   unreferenced formal parameter
#endif


class OdDummyModelerGeometry : public OdModelerGeometry
{
  AfTypeVer m_typeVer;
  mutable OdStaticRxObject<OdMemoryStreamImpl<OdMemoryStream> > m_Stream;
protected:

  OdStreamBuf *getDummyStream() const { return &m_Stream; }

public:  
  ODRX_DECLARE_MEMBERS(OdDummyModelerGeometry);

  OdDummyModelerGeometry(); 

  virtual OdResult in(OdStreamBuf* pStreamIn, AfTypeVer *typeVer, bool bStandardSaveFlag = true);
  virtual OdResult out(OdStreamBuf* pStreamOut, AfTypeVer typeVer, bool bStandardSaveFlag = true) const;

  virtual bool brep(OdBrBrep& ) const { return false; }

  virtual OdResult getEdgeSubentityGeometry(OdArray<OdUInt32> indexesOfEdgeCalculation, OdGeCurve3d*& pEdgeCurve)
  { 
    return eNotImplemented;
  }
  virtual bool setFACETRES(double) { return false; }

  virtual bool worldDraw(OdGiCommonDraw* , OdUInt32, const OdModelerGeometry::NumIsolines * ) { return true; }
  virtual OdResult getCachedSilhouettes(OdGeCurve3dPtrArray*){ return eNotImplemented; }
  virtual bool drawSilhouettes(OdGiViewportDraw* ) { return true; }

  virtual OdResult getHlrCurves(OdEdgeHLREdgeVisitor& edgeVisitor,
                                const OdGeVector3d& viewDir,
                                const OdTvDbEntityPtrArray& entities,
                                const OdGeMatrix3dArray* xforms = NULL,
                                OdEdgeTypeFlags edgeType = kTangent) { return eNotImplemented; }


  virtual bool getTransformation(OdGeMatrix3d& ) { return false; }
  virtual bool explode(OdTvDbEntityPtrArray& ) const { return false; }
  virtual void transformBy( const OdGeMatrix3d& ) {}

  virtual void createBox( double , double , double ) {}
  virtual void createFrustum( double , double , double , double ) {}
  virtual void createSphere( double ) {}
  virtual void createTorus( double , double ) {}
  virtual void createWedge( double , double , double ) {}
  virtual OdResult extrude(const OdTvDbRegion*, double, double, bool isSolid = true ) { return eNotImplemented; }
  virtual OdResult revolve(const OdTvDbRegion*, const OdGePoint3d&, const OdGeVector3d&, double, bool isSolid = true ) { return eNotImplemented; }
  virtual void ClearColorAttributes() { }
  virtual void ClearMaterialAttributes(const OdArray<OdDbSubentId>* aSubents = NULL) { }
  virtual void ClearMaterialMapperAttributes() { }
  virtual MaterialState hasMaterials() const;
  virtual bool hasTrueColorAttributes() const { return false; }
  virtual OdResult getPlane(OdGePlane& ) const { return eNotImplemented; }

  virtual bool setMMPerUnit(double  ) { return false; }
  virtual bool getMMPerUnit(double &) const  { return false; }

  virtual geomType bodyType() const { return OdModelerGeometry::kUndefined; }
  virtual OdResult booleanOper(OdTvDbDatabase* /*database*/, OdDb::BoolOperType /*operation*/, OdSmartPtr<OdModelerGeometry> /*otherRegion*/) { return eNotImplemented; }
  virtual OdResult booleanOper(OdDb::BoolOperType /*operation*/, 
                               const OdSmartPtr<OdModelerGeometry>/*pModelerPar*/, 
                               OdTvDbEntityPtrArray& intersectionEntities)
    { return eNotImplemented; }

  virtual OdResult booleanOper3dSolid(OdDb::BoolOperType /*operation*/, OdSmartPtr<OdModelerGeometry> /*otherSolid*/) { return eNotImplemented; }
  virtual OdResult getArea(double& /*regionArea*/) const { return eNotImplemented; }
  virtual OdResult getPerimeter(double&) const { return eNotImplemented; }
  virtual OdResult getAreaProp( const OdGePoint3d& , const OdGeVector3d& ,
    const OdGeVector3d& , double& ,
    double& , OdGePoint2d& ,
    double [2], double& ,
    double [2], OdGeVector2d [2],
    double [2], OdGePoint2d& ,
    OdGePoint2d&  ) const { return eNotImplemented; }
  virtual OdResult clear( ) { return eNotImplemented; }
  virtual OdResult extrudeAlongPath(const OdTvDbRegion* /*region*/, const OdTvDbCurve* /*path*/, double /*taperAngle*/ = 0.0, bool /*isSolid */= true) { return eNotImplemented; }
  virtual OdResult imprintEntity(const OdTvDbEntity * /*pEntity*/)  { return eNotImplemented; }

  virtual OdResult checkInterference(const OdTvDb3dSolid* otherSolid,
    bool createNewSolid, 
    bool& solidsInterfere,
    OdTvDb3dSolidPtr &commonVolumeSolid)
    const { return eNotImplemented; }

  virtual OdResult getMassProp(double& volume,
    OdGePoint3d& centroid,
    double momInertia[3],
    double prodInertia[3],
    double prinMoments[3],
    OdGeVector3d prinAxes[3], 
    double radiiGyration[3],
    OdGeExtents3d& extents) const { return eNotImplemented; }

  virtual OdResult getSection(const OdGePlane& plane, OdTvDbRegionPtr &sectionRegion, OdTvDbEntityPtrArray* pSectionCurves = NULL) const { return eNotImplemented; }

  virtual OdResult getSlice(const OdGePlane& plane, bool bGetNegHalfToo, OdTvDb3dSolidPtr &pNegHalfSolid) 
  { return eNotImplemented; }
  virtual OdResult getSlice(OdTvDbSurface* pSurface,  bool bGetNegHalfToo, OdTvDb3dSolidPtr& pNegHalfSolid)
  { return eNotImplemented; }
  virtual OdResult sliceByPlane(const OdGePlane& slicePlane, OdTvDbSurfacePtr& pNegHalfSurface, OdTvDbSurfacePtr& pNewSurface, bool bNotModifyItself)
  { return eNotImplemented; }
  virtual OdResult sliceBySurface(const OdTvDbSurfacePtr pSlicingSurface, OdTvDbSurfacePtr& pNegHalfSurface, OdTvDbSurfacePtr& pNewSurface, bool bNotModifyItself)
  { return eNotImplemented; }

  virtual OdResult cleanBody() { return eNotImplemented; }
  
  virtual OdResult offsetBody(double offsetDistance) { return eNotImplemented; }
  //virtual OdResult offsetBody(OdTvDbEntity* pOffsetEnt, double offsetDistance) { return eNotImplemented; }

  virtual OdResult separateBody(OdTvDb3dSolidPtrArray &newSolids) { return eNotImplemented; }

  virtual OdResult createExtrudedObject ( OdTvDbEntity* pSweepEnt,
                                          const OdGeVector3d& directionVec,
                                          OdTvDbSweepOptions& sweepOptions,
                                          bool isSolid = true,
                                          bool bHistoryEnabled = false) { return eNotImplemented; }

  virtual OdResult createLoftedObject (
    OdTvDbEntityPtrArray& crossSectionCurves,
    OdTvDbEntityPtrArray& guideCurves,
    OdTvDbEntity* pPathCurve, 
    OdTvDbLoftOptions& loftOptions,
    bool isSolid = true) { return eNotImplemented; }

  virtual OdResult createBlendObject(
    OdTvDbEntityPtrArray& blendedEdges,
    OdTvDbBlendOptions& loftOptions,
    bool isSolid = true) {
    return eNotImplemented;
  }
  //virtual OdResult createLoftedObjectByCoedges(
  //  OdTvDbEntityPtrArray& crossSectionCurves,
  //  OdTvDbEntityPtrArray& guideCurves,
  //  OdTvDbEntity* pPathCurve,
  //  OdTvDbLoftOptions& loftOptions,
  //  bool isSolid = true) {
  //  return eNotImplemented;
  //}

  virtual OdResult createPyramid(double height, int sides,
    double radius, double topRadius = 0.0 ) { return eNotImplemented; }

  virtual OdResult createRevolvedObject ( OdTvDbEntity* pRevEnt,
    const OdGePoint3d& axisPnt,
    const OdGeVector3d& axisDir,
    double revAngle, double startAngle,
    OdTvDbRevolveOptions& revolveOptions,
    bool isSolid = true,
    bool bHistoryEnabled = false) { return eNotImplemented; }

  virtual OdResult createSweptObject ( OdTvDbEntity* pSweepEnt,
    OdTvDbEntity* pPathEnt,
    OdTvDbSweepOptions& sweepOptions,
    bool isSolid = true,
    bool bHistoryEnabled = false) { return eNotImplemented; }

  // Loft options utility functions
  virtual OdResult checkCrossSectionCurves (
    OdTvDbEntityPtrArray& crossSectionCurves,
    bool& allOpen, bool& allClosed, bool& allPlanar,
    bool displayErrorMessages = false ) { return eNotImplemented; }

  virtual OdResult checkGuideCurves ( OdTvDbEntityPtrArray& guideCurves,
    bool displayErrorMessages = false )  { return eNotImplemented; }

  virtual OdResult checkPathCurve ( OdTvDbEntity *pPathCurve,
    bool displayErrorMessages = false )  { return eNotImplemented; }

  // Sweep options utility functions
  virtual OdResult  checkSweepCurve ( OdTvDbEntity *pSweepEnt,
    OdDb::Planarity& planarity, OdGePoint3d& pnt, OdGeVector3d& vec,
    bool& closed, double& approxArcLen, bool displayErrorMessages = false ) { return eNotImplemented; }

  virtual OdResult  checkSweepPathCurve ( OdTvDbEntity *pPathEnt,    bool displayErrorMessages = false ) { return eNotImplemented; }

  // Revolve options utility functions
  virtual OdResult checkRevolveCurve(
    OdTvDbEntity* pRevEnt,
    const OdGePoint3d& axisPnt,
    const OdGeVector3d& axisDir,
    bool& closed,
    bool& endPointsOnAxis,
    bool& planar,
    bool displayErrorMessages = false) { return eNotImplemented; }

  virtual OdResult createFrom ( const OdTvDbEntity* pFromEntity ) { return eNotImplemented; }

  virtual OdResult convertToRegion ( OdTvDbEntityPtrArray& regions ) { return eNotImplemented; }
  virtual OdResult thicken(double thickness, bool bBothSides, OdTvDb3dSolidPtr& pSolid) const { return eNotImplemented; }

  virtual OdResult intersectWith(const OdTvDbEntity* pEnt, OdDb::Intersect intType,
    OdGePoint3dArray& points, OdGsMarker thisGsMarker, OdGsMarker otherGsMarker) const { return eNotImplemented; }

  virtual OdResult intersectWith( const OdTvDbEntity* ent, OdDb::Intersect intType,
    const OdGePlane& projPlane, OdGePoint3dArray& points,
    OdGsMarker thisGsMarker, OdGsMarker otherGsMarker ) const { return eNotImplemented; }

  virtual OdResult copySubEntity(const OdDbSubentId &subentId, OdTvDbEntityPtr &newEntity) const { return eNotImplemented; }
  virtual OdResult taperFaces(const OdArray<OdDbSubentId *> &faceSubentIds, const OdGePoint3d &basePoint, 
                              const OdGeVector3d &draftVector, double draftAngle) { return eNotImplemented; }
  virtual OdResult removeFaces(const OdArray<OdDbSubentId *> &faceSubentIds) { return eNotImplemented; }
  virtual OdResult offsetFaces(const OdArray<OdDbSubentId *> &faceSubentIds, double offsetDistance) {return eNotImplemented;}
  virtual OdResult shellBody(const OdArray<OdDbSubentId *> &faceSubentIds, double offsetDistance) {return eNotImplemented;}
  virtual OdResult transformFaces(const OdArray<OdDbSubentId *> &faceSubentIds, const OdGeMatrix3d &matrix) {return eNotImplemented;}

  virtual OdResult getSubentPathsAtGsMarker(OdDb::SubentType type,
                                            OdGsMarker gsMark, 
                                            const OdGePoint3d& pickPoint,
                                            const OdGeMatrix3d& viewXform, 
                                            OdTvDbFullSubentPathArray& subentPaths, 
                                            const OdTvDbObjectIdArray* pEntAndInsertStack = 0) const {return eNotImplemented;}

  virtual OdResult getGsMarkersAtSubentPath(const OdTvDbFullSubentPath& subPath, 
                                            OdGsMarkerArray& gsMarkers) const {return eNotImplemented;}

  virtual OdDbSubentId internalSubentId(void* ent) const {return OdDbSubentId();}
  virtual void* internalSubentPtr(const OdDbSubentId& id) const {return NULL;}

  virtual OdResult setSubentColor(const OdDbSubentId &subentId, const OdTvCmColor &color) { return eNotImplemented; }
  virtual OdResult getSubentColor(const OdDbSubentId &subentId, OdTvCmColor &color) const { return eNotImplemented; }
  virtual OdResult setSubentMaterial(const OdDbSubentId &subentId, OdTvDbObjectId matId) { return eNotImplemented; }
  virtual OdResult getSubentMaterial(const OdDbSubentId &subentId, OdUInt64& numId) const { return eNotImplemented; }
  virtual OdResult setSubentMaterialMapper( const OdDbSubentId &subentId, 
                                            OdGeMatrix3d &mx, 
                                            OdUInt8 &projection, 
                                            OdUInt8 &tiling, 
                                            OdUInt8 &autoTransform) {return eNotImplemented;}
  virtual OdResult getSubentMaterialMapper( const OdDbSubentId &subentId,
                                            OdGeMatrix3d &mx, 
                                            OdUInt8 &projection, 
                                            OdUInt8 &tiling, 
                                            OdUInt8 &autoTransform) const { return eNotImplemented; }

  virtual OdResult chamferEdges(const OdArray<OdDbSubentId *> &edgeSubentIds,
                                const OdDbSubentId& baseFaceSubentId, 
                                double baseDist, 
                                double otherDist) 
  { return eNotImplemented; }

  virtual OdResult filletEdges( const OdArray<OdDbSubentId *> &edgeSubentIds,
                                const OdGeDoubleArray& radius, 
                                const OdGeDoubleArray& startSetback, 
                                const OdGeDoubleArray& endSetback)
  { return eNotImplemented; }

  virtual OdResult createSectionObjects(const OdGePlane& sectionPlane, OdTvDbEntityPtrArray& sectionObjects) const
  { return eNotImplemented; }

  virtual OdResult createInterferenceObjects( OdTvDbEntityPtrArray& interferenceObjects,
                                              OdTvDbEntityPtr pEntity, 
                                              unsigned int flags ) const
  { return eNotImplemented; }

  virtual OdResult extrudeFaces(const OdArray<OdDbSubentId *> &faceSubentIds, double height, double taper)
    { return eNotImplemented; }
  virtual OdResult extrudeFacesAlongPath(const OdArray<OdDbSubentId *> &faceSubentIds, const OdTvDbCurve* path)
    { return eNotImplemented; }

  virtual OdResult ChangeFacesDoubleSidedParam(bool isDoubleSided) {return eNotImplemented;}

  virtual OdResult convertToNurbSurface(OdTvDbNurbSurfacePtrArray& nurbSurfaceArray) {return eNotImplemented;}

  virtual OdResult get( int& iUDegree, int& iVDegree, bool& bRational, int& iUNumControlPoints, int& iVNumControlPoints,
                        OdGePoint3dArray& ctrlPtsArr, OdGeDoubleArray& weights, 
                        OdGeKnotVector& uKnots, OdGeKnotVector& vKnots) const  { return eNotImplemented; }

  virtual OdResult set( int iUDegree, int iVDegree, bool bRational, int iUNumControlPoints, int iVNumControlPoints,
                        const OdGePoint3dArray& ctrlPtsArr, const OdGeDoubleArray& weights, 
                        const OdGeKnotVector& uKnots, const OdGeKnotVector& vKnots) {return eNotImplemented;}

  virtual OdResult getNumberOfControlPointsInU(int& iCount) const { return eNotImplemented; }
  virtual OdResult getNumberOfControlPointsInV(int& iCount) const { return eNotImplemented; }

  virtual OdResult getNumberOfKnotsInU(int& iCount) const { return eNotImplemented; }
  virtual OdResult getNumberOfKnotsInV(int& iCount) const { return eNotImplemented; }

  virtual OdResult getUKnots(OdGeKnotVector& knots) const { return eNotImplemented; }
  virtual OdResult getVKnots(OdGeKnotVector& knots) const { return eNotImplemented; }

  virtual OdResult getDegreeInU(int& iDegree) const { return eNotImplemented; }
  virtual OdResult getDegreeInV(int& iDegree) const { return eNotImplemented; }

  virtual OdResult isClosedInU(bool& bIsClosed) const { return eNotImplemented; }
  virtual OdResult isClosedInV(bool& bIsClosed) const { return eNotImplemented; }

  virtual OdResult isPeriodicInU(bool& bIsPeriodic) const { return eNotImplemented; }
  virtual OdResult isPeriodicInV(bool& bIsPeriodic) const { return eNotImplemented; }

  virtual OdResult getPeriodInU(double& dPeriod) const { return eNotImplemented; }
  virtual OdResult getPeriodInV(double& dPeriod) const { return eNotImplemented; }

  virtual OdResult evaluate(double dU, double dV, OdGePoint3d& pos) const { return eNotImplemented; }

  virtual OdResult evaluate(double dU, double dV, OdGePoint3d& pos, OdGeVector3d& uDeriv, OdGeVector3d& vDeriv) const { return eNotImplemented; }

  virtual OdResult evaluate(double dU, double dV, OdGePoint3d& pos, OdGeVector3d& uDeriv, OdGeVector3d& vDeriv,
                            OdGeVector3d& uuDeriv, OdGeVector3d& uvDeriv, OdGeVector3d& vvDeriv) const { return eNotImplemented; }

  virtual OdResult evaluate(double dU, double dV, int iDerivDegree, OdGePoint3d& point, OdGeVector3dArray& derivatives) const { return eNotImplemented; }

  virtual OdResult isRational(bool& bIsRational) const { return eNotImplemented; }

  virtual OdResult isPlanar(bool& bIsPlanar, OdGePoint3d& ptOnSurface, OdGeVector3d& normal) const { return eNotImplemented; }

  virtual OdResult isPointOnSurface(const OdGePoint3d& point, bool& bOnSurface) const { return eNotImplemented; }

  virtual OdResult getNormal(double dU, double dV, OdGeVector3d& normal) const { return eNotImplemented; }

  virtual OdResult getNumberOfSpansInU(int& iSpan) const { return eNotImplemented; }
  virtual OdResult getNumberOfSpansInV(int& iSpan) const { return eNotImplemented; }

  virtual OdResult getIsolineAtU(double dNumberSegments, OdTvDbCurvePtrArray& lineSegments) const { return eNotImplemented; }
  virtual OdResult getIsolineAtV(double dNumberSegments, OdTvDbCurvePtrArray& lineSegments) const { return eNotImplemented; }

  virtual OdResult InsertKnot(double dVal, int iUorV) { return eNotImplemented; }

  virtual OdResult InsertControlPointsAtU(double dVal, const OdGePoint3dArray& vCtrlPts, const OdGeDoubleArray& vWeights) { return eNotImplemented; }
  virtual OdResult InsertControlPointsAtV(double dVal, const OdGePoint3dArray& vCtrlPts, const OdGeDoubleArray& vWeights) { return eNotImplemented; }

  virtual OdResult RemoveControlPointsAtU(int iIndex) { return eNotImplemented; }
  virtual OdResult RemoveControlPointsAtV(int iIndex) { return eNotImplemented; }

  virtual OdResult rebuild(int iUDegree, int iVDegree, int iNumUCtrlPts, int iNumVCtrlPts, bool bRestore) { return eNotImplemented; }

  virtual OdResult modifyPositionAndTangent(double dU, double dV, const OdGePoint3d& point, const OdGeVector3d* uDeriv, const OdGeVector3d* vDeriv) { return eNotImplemented; }

  virtual OdResult getParameterOfPoint(const OdGePoint3d& point, double& dU, double& dV) const { return eNotImplemented; }

  virtual OdResult getControlPoints(int& iUCount, int& iVCount, OdGePoint3dArray& points) const { return eNotImplemented; }

  virtual OdResult setControlPoints(int iUCount, int iVCount, const OdGePoint3dArray& points) { return eNotImplemented; }

  virtual OdResult getControlPointAndWeight(int iUIndex, int iVIndex, OdGePoint3d& point, double& weight, bool& bIsRational) const { return eNotImplemented; }

  virtual OdResult setControlPointAndWeight(int iUIndex, int iVIndex, const OdGePoint3d& point, double weight)  { return eNotImplemented; }

  virtual OdResult generateSectionGeometry( const OdTvDbSection*      pSection,
                                            OdTvDbEntityPtrArray&     sourceEntArr,
                                            OdArray<OdTvDbEntityPtr>& intBoundaryEnts,
                                            OdArray<OdTvDbEntityPtr>& intFillEnts,
                                            OdArray<OdTvDbEntityPtr>& backgroundEnts,
                                            OdArray<OdTvDbEntityPtr>& foregroundEnts,
                                            OdArray<OdTvDbEntityPtr>& curveTangencyEnts,
                                            bool                    bIsSetProperties) { return eNotImplemented; }

  virtual OdResult setColorToSubents(OdTvCmColor const& color) { return eNotImplemented; }

  virtual OdResult setMaterialToSubents(OdTvDbObjectId materialId) { return eNotImplemented; }

  virtual OdResult setMaterialMapperToSubents(OdGeMatrix3d &mx, OdUInt8 &projection,
                                              OdUInt8 &tiling, OdUInt8 &autoTransform) { return eNotImplemented; }

  virtual OdResult trimSurface( const OdTvDbObjectIdArray& toolIds,
                                const OdTvDbObjectIdArray& toolCurveIds, 
                                const OdGeVector3dArray& projVectors,
                                const OdGePoint3d&       pickPoint, 
                                const OdGeVector3d&      viewVector,
                                bool                     bAutoExtend,
                                bool                     bAssociativeEnabled) { return eNotImplemented; }

  virtual OdResult projectOnToEntity( const OdTvDbEntity*   pEntityToProject,
                                      const OdGeVector3d& projectionDirection,
                                      OdTvDbEntityPtrArray& projectedEntities ) const { return eNotImplemented; }

  virtual OdResult createSculptedSolid(OdTvDbEntityPtrArray& limitingBodies,
                                       const OdGeIntArray& limitingFlags) { return eNotImplemented; }

  virtual OdResult rayTest( const OdGePoint3d&      rayBasePoint, 
                            const OdGeVector3d&     rayDir,
                            double                  rayRadius, 
                            OdArray<OdDbSubentId> & subEntIds, 
                            OdGeDoubleArray&        parameters) const { return eNotImplemented; }

  virtual OdResult createFilletSurface (OdTvDbSurfacePtr&      surf1,
                                        const OdGePoint3d&   pickPt1,
                                        OdTvDbSurfacePtr&      surf2,
                                        const OdGePoint3d&   pickPt2,
                                        double               dRadius,
                                        OdDb::FilletTrimMode trimMode,
                                        const OdGeVector3d&  projDir) { return eNotImplemented; }

  virtual OdResult extendEdges( OdTvDbFullSubentPathArray& edgesId,
                                double                   dExtDist, 
                                EdgeExtensionType        extOption ) { return eNotImplemented; }

  virtual OdResult getObjectMesh( const OdTvDbFaceterSettings *faceter,
    OdGePoint3dArray& vertexArray, 
    OdInt32Array& faceArray,
    OdGiFaceData*& faceData ) { return eNotImplemented; }

  virtual OdResult createCachedCurves(OdGeCurve3dPtrArray& pCurve) { return eNotImplemented; }
  virtual OdResult restoreAttributes( OdModelerGeometry* oldmodeler ) { return eNotImplemented; }
  virtual OdResult  addSubentitySpecialSettings(AcisDataType addedDT, AcisDataTypeArrFirst addedDTFirst, const OdDbSubentId subentId, OdArray<OdUInt32>& retArray, OdUInt32 idx) { return eNotImplemented; }

  virtual OdResult getBoundingBox(OdGeExtents3d &box) { return eNotImplemented; }
  
  // for internal use only
  virtual OdResult generateSectionGeometry( SectArgs& sectArgs, OdTvDbEntity *pEnt, bool* bHasForeground ) { return eNotImplemented; }

  virtual OdResult convertTo(const OdGePoint3dArray &arrVertexes, const OdInt32Array &arrEdges, const OdInt32Array &arrFaces, OdGiFaceData &fd,
    OdBoolArray &arrFacesColors, OdBoolArray &arrFacesMaterials, OdTvDbEntity* pEntity) { return eNotImplemented; }

  virtual bool getFaceMesh(GeMesh::OdGeTrMesh& mesh, OdGsMarker iFace, const wrTriangulationParams& triangulationParams)
  { return false; }

  virtual OdResult auditAcisData(OdTvDbAuditInfo* pAuditInfo, const OdRxObject* pObj) { return eNotImplemented; };
  virtual void enableAcisAudit(bool bEnableAcisAudit) { };
  virtual OdResult getSectionViewInfo(const OdArray<OdTvDbEntityPtr>& pEnts, const OdGePoint3dArray& pPoints, const OdGeVector3d& normal, OdArray<OdTvDbEntityPtr>& backgroundEnts, OdArray<OdTvDbEntityPtr>& intHatchEnts, OdArray<OdTvDbEntityPtr>& intBoundaryEnts, OdArray<OdTvDbEntityPtr>& curveVisibilityEdges, SectionType sectType = kFull_ST, OdEdgeTypeFlags edgeVis = kTangent) { return eNotImplemented; };
};

typedef OdSmartPtr<OdDummyModelerGeometry> OdDummyModelerGeometryPtr;

#endif //_DUMMYMODELERGEOMETRY_INCLUDED_
