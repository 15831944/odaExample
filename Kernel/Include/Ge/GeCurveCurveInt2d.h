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

#ifndef OD_GE_CURVE_CURVE_INT_2D_H
#define OD_GE_CURVE_CURVE_INT_2D_H /*!DOM*/

#include "Ge/GeEntity2d.h"
#include "Ge/GeInterval.h"
#include "Ge/GeCurve2d.h"
#include "Ge/GePointOnCurve2d.h"

#include "TD_PackPush.h"

/** \details
  This class represents intersections of 2D curves.

  \remarks
  The intersection object links to 2D curve objects but does not contain them.
  Calculation of the intersection is performed by a query function.

  If one of the curve objects is deleted, the intersection must be recalculated.

  Corresponding C++ library: TD_Ge

  <group OdGe_Classes>

  \sa
  <link ge_OdGeIntersectEntities, Working with Intersected Entities>
*/
class GE_TOOLKIT_EXPORT OdGeCurveCurveInt2d : public OdGeEntity2d
{
public:

  /** \details
    Default constructor for objects of the OdGeCurveCurveInt2d class. Constructs
    an invalid curve-curve intersector with no intersection curves and default
    tolerance.
  */
  OdGeCurveCurveInt2d();

  /** \details
    Constructor. Creates an OdGeCurveCurveInt2d object with specified two curves
    and geometric tolerance.
    \param curve1 [in]  First 2D curve.
    \param curve2 [in]  Second 2D curve.
    \param tol    [in]  Geometric tolerance.
  */
  OdGeCurveCurveInt2d(
    const OdGeCurve2d& curve1,
    const OdGeCurve2d& curve2,
    const OdGeTol& tol = OdGeContext::gTol);

  /** \details
    Constructor. Creates an OdGeCurveCurveInt2d object with specified two
    curves, their ranges and geometric tolerance.
    \param curve1 [in]  First 2D curve.
    \param curve2 [in]  Second 2D curve.
    \param range1 [in]  Range of the first curve.
    \param range2 [in]  Range of the second curve.
    \param tol    [in]  Geometric tolerance.

    \remarks
    Intersection points and overlaps are only returned if they are within the
    two specified parameter ranges.
  */
  OdGeCurveCurveInt2d(
    const OdGeCurve2d& curve1,
    const OdGeCurve2d& curve2,
    const OdGeInterval& range1,
    const OdGeInterval& range2,
    const OdGeTol& tol = OdGeContext::gTol);

  /** \details
    Copy constructor. Creates an OdGeCurveCurveInt2d object and initializes it
    with parameters of the specified source object.
    \param source [in]  Object to be cloned.
  */
  OdGeCurveCurveInt2d(
    const OdGeCurveCurveInt2d& source);

  // General query functions.
  //

  /** \details
    Returns the first curve.

    \returns
    A pointer to the instance of OdGeCurve2d.
  */
  const OdGeCurve2d* curve1() const;

  /** \details
    Returns the second curve.

    \returns
    A pointer to the instance of OdGeCurve2d.
  */
  const OdGeCurve2d* curve2() const;

  /** \details
    Retrieves the ranges of the two curves.

    \param range1 [out]  Receives the range of the first curve.
    \param range2 [out]  Receives the range of the second curve.
  */
  void getIntRanges(
    OdGeInterval& range1,
    OdGeInterval& range2) const;

  /** \details
    Returns the tolerance for determining intersections.

    \returns
    An instance of the OdGeTol class.
  */
  OdGeTol tolerance() const;

  // Intersection query methods.
  //

  /** \details
    Returns the number of intersections between the curves within the specified
    ranges.

    \returns
    The number of intersections as an integer value.
  */
  int numIntPoints() const;

  /** \details
    Returns an intersection point by its index.

    \param intNum [in]  The zero-based index of the intersection point to return.

    \returns
    An instance of the OdGePoint2d class.
  */
  OdGePoint2d intPoint(
    int intNum) const;

  /** \details
    Retrieves the curve parameters at the specified intersection point.

    \param intNum  [in]  The zero-based index of the intersection point to return.
    \param param1 [out]  Receives the parameter of the first curve at the intersection point.
    \param param2 [out]  Receives the parameter of the second curve at the intersection point.
  */
  void getIntParams(
    int intNum,
    double& param1,
    double& param2) const;

  /** \details
    Retrieves the specified intersection point as an OdGePointOnCurve2d on the
    first curve.

    \param intNum  [in]  The zero-based index of the intersection point to return.
    \param intPnt [out]  Receives the specified intersection point on the first curve.
  */
  void getPointOnCurve1(
    int intNum,
    OdGePointOnCurve2d& intPnt) const;

  /** \details
    Retrieves the specified intersection point as an OdGePointOnCurve2d on the
    second curve.

    \param intNum  [in]  The zero-based index of the intersection point to return.
    \param intPnt [out]  Receives the specified intersection point on the second curve.
  */
  void getPointOnCurve2(
    int intNum,
    OdGePointOnCurve2d& intPnt) const;

  /** \details
    Calculates the configuration of the first curve with respect to the second
    at the intersection point, and vice versa.

    \param intNum       [in]  The zero-based index of the intersection point to query.
    \param config1wrt2 [out]  Receives the configuration of the first curve with respect to the second.
    \param config2wrt1 [out]  Receives the configuration of the second curve with respect to the first.

    \remarks
    The possible values for config1wrt2 and config2wrt1 are as follows:

    * kNotDefined
    * kUnknown
    * kLeftRight
    * kRightLeft
    * kLeftLeft
    * kRightRight
    * kPointLeft
    * kPointRight
    * kLeftOverlap
    * kOverlapLeft
    * kRightOverlap
    * kOverlapRight
    * kOverlapStart
    * kOverlapEnd
    * kOverlapOverlap

    \remarks
    Currently not implemented.
  */
  void getIntConfigs(
    int intNum,
    OdGe::OdGeXConfig& config1wrt2,
    OdGe::OdGeXConfig& config2wrt1) const;

  /** \details
    Checks if the curves are tangential at the specified intersection point.

    \param intNum [in]  The zero-based index of the intersection point to query.

    \returns
    True if and only if the curves are tangential at the specified intersection
    point; false otherwise.

    \remarks
    Currently not implemented.
  */
  bool isTangential(
    int intNum) const;

  /** \details
    Checks if the curves are transversal (cross) at the specified intersection
    point.

    \param intNum [in]  The zero-based index of the intersection point to query.

    \returns
    True if and only if the curves are transversal; false otherwise.

    \remarks
    Currently not implemented.
  */
  bool isTransversal(
    int intNum) const;

  /** \details
    Returns the tolerance used to compute the specified intersection point.

    \param intNum [in]  The zero-based index of the intersection point to query.

    \returns
    The tolerance as a double value.
  */
  double intPointTol(
    int intNum) const;

  /** \details
    Returns the number of intervals of overlap for the two curves.

    \returns
    The number of intervals as an integer value.
  */
  int overlapCount() const;

  /** \details
    Checks if the curves are oriented in the same direction where they overlap.

    \returns
    True if and only if the curves are oriented in the same direction; false
    otherwise.

    \remarks
    This value has meaning only if overlapCount() > 0.

    \remarks
    Currently not implemented.
  */
  bool overlapDirection() const;

  /** \details
    Returns the ranges for each curve a the specified overlap.

    \param overlapNum [in]  The zero-based index of the overlap range to query.
    \param range1    [out]  Receives the range of the first curve for the specified overlap.
    \param range2    [out]  Receives the range of the second curve for the specified overlap.
  */
  void getOverlapRanges(
    int overlapNum,
    OdGeInterval& range1,
    OdGeInterval& range2) const;

  /** \details
    Makes the first curve the second, and vice versa.
  */
  void changeCurveOrder();

  /** \details
    Orders the intersection points so that they correspond to increasing
    parameter values of the first curve.

    \returns
    Reference to this OdGeCurveCurveInt2d object.
  */
  OdGeCurveCurveInt2d& orderWrt1();

  /** \details
    Orders the intersection points so that they correspond to increasing
    parameter values of the second curve.

    \returns
    Reference to this OdGeCurveCurveInt2d object.
  */
  OdGeCurveCurveInt2d& orderWrt2();

  /** \details
    Sets the curves and tolerance for which to determine intersections.

    \param curve1 [in]  First 2D curve.
    \param curve2 [in]  Second 2D curve.
    \param tol    [in]  Geometric tolerance.

    \returns
    Reference to this OdGeCurveCurveInt2d object.
  */
  OdGeCurveCurveInt2d& set(
    const OdGeCurve2d& curve1,
    const OdGeCurve2d& curve2,
    const OdGeTol& tol = OdGeContext::gTol);

  /** \details
    Sets the curves, ranges and tolerance for which to determine intersections.

    \param curve1 [in]  First 2D curve.
    \param curve2 [in]  Second 2D curve.
    \param range1 [in]  Range of first curve.
    \param range2 [in]  Range of second curve.
    \param tol    [in]  Geometric tolerance.

    \returns
    Reference to this OdGeCurveCurveInt2d object.
  */
  OdGeCurveCurveInt2d& set(
    const OdGeCurve2d& curve1,
    const OdGeCurve2d& curve2,
    const OdGeInterval& range1,
    const OdGeInterval& range2,
    const OdGeTol& tol = OdGeContext::gTol);

  /** \details
    Assignment operator for the OdGeCurveCurveInt2d object.
    
    \param crvCrvInt [in]  OdGeCurveCurveInt2d object to assign.

    \returns
    Reference to this OdGeCurveCurveInt2d object.
  */
  OdGeCurveCurveInt2d& operator =(
    const OdGeCurveCurveInt2d& crvCrvInt);

  //////////////////////////////////////////////////////////////////////////
};

#include "TD_PackPop.h"

#endif // OD_GE_CURVE_CURVE_INT_2D_H
