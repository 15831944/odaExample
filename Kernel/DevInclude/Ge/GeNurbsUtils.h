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


#ifndef __OD_GE_NURBS_UTILS__
#define __OD_GE_NURBS_UTILS__ /* {Secret} */

class OdGeKnotVector;

#include "Ge/GeDoubleArray.h"
#include "Ge/GeIntArray.h"
#include "Ge/GeExport.h"
#include "Ge/GeInterval.h"
#include "Ge/GePoint3dArray.h"
#include "Ge/GeTol.h"
#include "Ge/GeCone.h"
#include "Ge/GeNurbSurface.h"
#include "Ge/GeCurve3dPtrArray.h"
#include "Ge/GeCylinder.h"
#include "Ge/GeTorus.h"

class OdGeNurbSurface;
class OdGeSurface;
class OdGeCurve3d;
class OdGeInterval;
class OdGeNurbCurve3d;

namespace OdGeNurbsUtils
{
#define BSplineBasis_MaxBin_DEF 4

  template <class NURBS, class POINT> 
  void reverseParamNurbsAcis(NURBS* pThis)
  {
    if (pThis->hasFitData())
    {
      throw OdError(eGeneralModelingFailure);
    }
    if(pThis->numControlPoints() == 0)
    {
      return;
    }

    // swapping...
    int i, sz;
    sz = pThis->numWeights();
    for(i = 0; i < sz/2; i++)
    {
      double tmp = pThis->weightAt(i);
      pThis->setWeightAt(i, pThis->weightAt(sz - i - 1));
      pThis->setWeightAt(sz - i - 1, tmp);
    }
    sz = pThis->numControlPoints();
    for(i = 0; i < sz/2; i++)
    {
      POINT tmp = pThis->controlPointAt(i);
      pThis->setControlPointAt(i, pThis->controlPointAt(sz - i - 1));
      pThis->setControlPointAt(sz - i - 1, tmp);
    }

    sz = pThis->numKnots();
    for(i = 0; i < sz/2; i++)
    {
      double tmp = pThis->knotAt(i);
      pThis->setKnotAt(i, pThis->knotAt(sz - i - 1));
      pThis->setKnotAt(sz - i - 1, tmp);
    }
    for(i = 0; i < sz; i ++)
    {
      pThis->setKnotAt(i, pThis->knotAt(i)*-1.);
    }

    OdGeInterval interval;
    pThis->getInterval(interval);
    const bool bIntervalBounded = !OdEqual(interval.lowerBound(), pThis->knotAt(0)) || !OdEqual(interval.upperBound(), pThis->knotAt(sz - 1));
    if(bIntervalBounded)
    {
      pThis->setInterval(OdGeInterval(-interval.upperBound(), -interval.lowerBound()));
    }
  }

  //extern int BSplineBasis_MaxBin; // maximal binomial coefficient
  
  extern const double binCoeffa[BSplineBasis_MaxBin_DEF+1][BSplineBasis_MaxBin_DEF+1];

  int GE_TOOLKIT_EXPORT lookForSpan(double u, const OdGeKnotVector& U, int degree);

  // This is little modified version of TNB A2.2
  // input:
  // i - number of span
  // u - parameter
  // p - degree
  // U - knot vector
  // output:
  // N - basis functions
  void basisFunctions(int i, double u, int p, const OdGeKnotVector& U,
    OdGeDoubleArray& N);

  int       // return value is the span containing "u"
    dersBasisFunctions(const OdGeKnotVector& U,
    int degree,
    /* input: */ double u, int nDerivs,
    /* output:*/ double**& ders); // caller responsible: "delete2DArrayD(ders);"

  double** new2DArrayD(int rows, int cols);
  void delete2DArrayD(double**& a);

  int binCoef(OdGeIntArray& coefCache, int& orderCached, int n, int k);

  double deBoor(const OdGeKnotVector& knots, int i, int k, double t);
  double deBoorDer(const OdGeKnotVector& knots, int i, int k, double t);
  double deBoor2Der(const OdGeKnotVector& knots, int i, int k, double t);

  bool GE_TOOLKIT_EXPORT srfOffsetCtlPoints(OdGeNurbSurface& nurb, double distance);

  struct SrfRollingBallBlendParams
  {
    SrfRollingBallBlendParams(const OdGeCurve3d& spine)
    : m_spine(spine)
    , m_pSrfLeft(NULL)
    , m_pSrfRight(NULL)
    , m_pCrvLeft(NULL)
    , m_pCrvRight(NULL)
    , m_radius(0)
    , m_bSpineParamU(true)
    , m_parametrizationType(0)
    {}
    const OdGeCurve3d& m_spine;
    const OdGeSurface* m_pSrfLeft;
    const OdGeSurface* m_pSrfRight;
    const OdGeCurve3d* m_pCrvLeft; // PRC
    const OdGeCurve3d* m_pCrvRight; // PRC
    double m_radius;
    bool m_bSpineParamU; // what param direction (U or V) is formed by spine? Parasolid, PRC = true, ACIS = false
    int m_parametrizationType; // PRC: 0 - [0..1], 1 - [0..2PI]
  };
  bool GE_TOOLKIT_EXPORT srfRollingBallBlend(OdGeNurbSurface& nurb, const SrfRollingBallBlendParams& params);
  // legacy call for back-compatibility
  bool GE_TOOLKIT_EXPORT srfRollingBallBlend(OdGeNurbSurface& nurb, const OdGeCurve3d& spine, const OdGeSurface& srfLeft, const OdGeSurface& srfRight, double radius, bool bSpineParamU);

//#define FIX_12352
#ifdef FIX_12352
  bool GE_TOOLKIT_EXPORT intersectWith(const OdGeNurbSurface& nurbs1, const OdGeNurbSurface& nurbs2, OdGeCurve3dPtrArray &intersections, double tol);

  bool GE_TOOLKIT_EXPORT coneToNurb(OdGeNurbSurface &nurb, const OdGeCone& cone, const OdGeInterval& u , const OdGeInterval& v);

  bool GE_TOOLKIT_EXPORT cylinderToNurb(OdGeNurbSurface &nurb, const OdGeCylinder& cylinder, const OdGeInterval& u , const OdGeInterval& v);

  bool GE_TOOLKIT_EXPORT planeToNurb(OdGeNurbSurface &nurb, const OdGePlane& plane, const OdGeInterval& u , const OdGeInterval& v);

  bool GE_TOOLKIT_EXPORT torusToNurb(OdGeNurbSurface &surf, const OdGeTorus& torus, const OdGeInterval& intervalU , const OdGeInterval& intervalV);
#endif

  void GE_TOOLKIT_EXPORT makeUniformKnots(OdGeKnotVector& aKt, int degree, int nKt, double paramStart = 0., double paramEnd = 1.);
  bool GE_TOOLKIT_EXPORT makeCrossSectionCircle(const OdGeSurface* srfLeft, const OdGeSurface* srfRight, const OdGeCurve3d& spine, double spineParam, OdGeCircArc3d& xsCir, double& uLeft, double& uRight, double r, double tol = 0., const OdGeCurve3d* pCrvLeft = NULL, const OdGeCurve3d* pCrvRight = NULL);
  void GE_TOOLKIT_EXPORT scaleKnots(OdGeKnotVector& aKt, double paramStart, double paramEnd);
  void GE_TOOLKIT_EXPORT constructSurfaceOfRevolution(OdGeNurbSurface& surf, const OdGePoint3d& base, const OdGeVector3d& axis, const OdGeNurbCurve3d& contour, double uMin, double uMax, double vMin, double vMax);
  // method: 0 - create spline approximating the curve traced out by a curve in the parameter plane (works only with nurbs surface and curve)
  // 1 - to compute the approximation to the data given by the points and the derivatives (slower, more CPs, works with any input type)
  bool GE_TOOLKIT_EXPORT convertParamCurveTo3d(const OdGeSurface& surf, const OdGeCurve2d& curveParam, OdGeNurbCurve3d& result, double tol, int iMethod = 0);
  bool GE_TOOLKIT_EXPORT intersectCurvePlane(const OdGeCurve3d& crv, const OdGePlane& plane, OdGePoint3d& ptInt, double tol);
}

#endif // __OD_GE_NURBS_UTILS__
