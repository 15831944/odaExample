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


#ifndef __OD_GE_VALIDATION_UTILS__
#define __OD_GE_VALIDATION_UTILS__ /* {Secret} */

#include "Ge/GePoint3d.h"
#include "Ge/GeVector3d.h"

class OdGeCurve2d;
class OdGeCurve3d;
class OdGeInterval;
class OdGeSurface;

/**
Functions for geometry validation. 
Approximate algorithms are used to estimate distance between curves, surface and curve,
intersections of two curves.
*/
namespace OdGeValidationUtils
{
  /**
  \details
  Returns approximate maximal distance from a given curve to a given surface.

  \param curve [i] Input curve.
  \param surface [i] Input surface.
  \param curvePoint [o] Point of sampled curve which gives greatest distance to the surface
  \param surfPoint [o] Projection of curve point onto surface

  \remarks
  OdGeSurface::paramOf() is used for points of the curve. If they are not on surface within a tolerance, result can be unpredictable.
  It may be better to use isOn().
  */
  GE_TOOLKIT_EXPORT double estimateDistanceCurve3dToSurface(
    const OdGeCurve3d& curve, const OdGeSurface& surface, 
    OdGePoint3d& curvePoint, OdGePoint3d& surfPoint, const OdGeTol& tolerance = OdGeContext::gTol);

  /**
  \details
  Returns the maximal distance between 3d curve and a curve represented by
  a surface and 2d curve in parameter domain of this surface.

  \param curve3d [i] Curve in 3d space.
  \param curve2d [i] Curve in 2d parametric space of surface.
  \param surface [i] Input surface.

  \param curve3dPoint [o] Projection of point of sampled parametric curve on surface which gives the maximal distance onto 3d curve
  \param surfPoint [o] Point of sampled parametric curve on surface which gives the maximal distance to 3d curve

  \remarks
  OdGeCurve3d::paramOf() is used for points of curves. If they are not on surface within a tolerance, result can be unpredictable.
  It may be better to use isOn().
  */
  GE_TOOLKIT_EXPORT double estimateDistanceCurve3dToCurveOnSurface(
    const OdGeCurve3d& curve3d, const OdGeCurve2d& curve2d, const OdGeSurface& surface,
    OdGePoint3d& curve3dPoint, OdGePoint3d& surfaceCurvePoint, const OdGeTol& tolerance = OdGeContext::gTol, const OdGeInterval* ipCoedgeInt = NULL);

  /**
  \details
  Returns true if approximate intersections are found for two curves

  \param curve1 [i] The first curve to intersect.
  \param interval1 [i] Interval of the first curve.
  \param curve2 [i] The second curve to intersect.
  \param interval2 [i] Interval of the second curve.
  \param tolerance [i] Tolerance of intersection
  \param bSkipCommonEnds [i] true if common end points of two curves are to be ignored
  \param arrInters [o] Recieves approximate intersection points of two curves 
  */
  GE_TOOLKIT_EXPORT bool estimateCurvesIntersections(
    const OdGeCurve3d& curve1, const OdGeInterval& interval1, const OdGeCurve3d& curve2, const OdGeInterval& interval2, 
    const OdGeTol& tolerance, OdArray<OdGePoint3d>& arrInters, bool bSkipCommonEnds = true, bool bStopOnFirstInters = false);

  /**
  \details
  Returns true if approximate self-intersections of a given 3d curve are found

  \param curve [i] A curve to be checked.
  \param interval [i] Interval of the curve.
  \param tolerance [i] Tolerance of intersection
  \param arrInters [o] Recieves approximate intersection points
  */
  GE_TOOLKIT_EXPORT bool estimateCurveSelfIntersections(
    const OdGeCurve3d& curve, const OdGeInterval& interval, const OdGeTol& tolerance, 
    OdArray<OdGePoint3d>& arrInters, bool bSkipCloseEndPoints = true, bool bStopOnFirstInters = false);

  /**
  \details
  Returns true if approximate self-intersections of a given 2d curve are found

  \param curve [i] A curve to be checked.
  \param interval [i] Interval of the curve.
  \param tolerance [i] Tolerance of intersection
  \param arrInters [o] Recieves approximate intersection points
  \param tol       [in] Tolerance of intersection check.
  */
  //static bool estimateCurveSelfIntersections(
  //  const OdGeCurve2d& curve, const OdGeInterval& interval, double tolerance, 
  //  OdArray<OdGePoint2d>& arrInters, bool bSkipCloseEndPoints = true, bool bStopOnFirstInters = false);

  /**
  \details
  Returns true if approximate self-intersections of a OdGeCurve3dArray are found

  \param curves [i] Curves to be checked.
  \param arrInters [o] Recieves intersection points
  */
  GE_TOOLKIT_EXPORT bool CheckSelfIntersectionCurve(const OdGeCurve3dArray & curves, OdArray<OdGePoint3d>& arrInters, const OdGeTol& tol = OdGeContext::gTol);

  /**
  \details
  Returns true if approximate self-intersections of a OdGeCurve3dArray are found

  \param curves [i] Curves to be checked.
  \param tol    [in] Tolerance of intersection check.
  */
  GE_TOOLKIT_EXPORT bool CheckSelfIntersectionCurve(const OdGeCurve3dArray & curves, const OdGeTol& tol = OdGeContext::gTol);
};

#endif // __OD_GE_VALIDATION_UTILS__
