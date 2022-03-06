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

#ifndef _PRCCRVOFFSET3d_INCLUDED_
#define _PRCCRVOFFSET3d_INCLUDED_ 
 

#include "PrcCurve3d.h"

/** \details
<group PRC_Curve_Classes>

Class implements an offset of a three-dimensional curve along the binormal.
Binormal is defined by the curve's tangent and plane normal offset.
The offset curve must be a 3D curve without transformation. 
Parameterization has coefficients with default values (coef_a is equal 1.0, coef_b is equal 0.0), and the interval is equal to the base curve interval.
*/
class PRC_TOOLKIT OdPrcOffsetCurve3d : public OdPrcCurve3d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcOffsetCurve3d)
  //DOM-IGNORE-END
  
  /** \details
  Sets a new value of the offset distance for the offset curve.
  
  \param offset_distance [in] A new offset distance value to be set.
  */
  void setOffsetDistance(double offset_distance);
  
  /** \details
  Returns the current offset distance value for the offset curve.
  */
  double offsetDistance() const;

  /** \details
  Sets a new base curve to offset.
  
  \param value [in] A smart pointer to a OdPrcCurve object to be set as a base curve.
  
  \returns Returns eOk if a new base curve was successfully set or an appropriate error code in the other case.
  */
  OdResult setBaseCurve(const OdPrcCurvePtr &value);
  
  /** \details
  Returns the current base curve for the offset curve.
  */
  const OdPrcCurvePtr &baseCurve() const;

  /** \details
  Set a new offset plane normal for the offset curve. 
  
  \param value [in] A new offset plane normal to be set.
  
  \returns Returns eOk if a new offset plane normal was successfully set or an appropriate error code in the other case.
  */
  OdResult setOffsetPlaneNormal(const OdGeVector3d& value);
  
  /** \details
  Returns the current offset plane normal of the offset curve. 
  */
  const OdGeVector3d &offsetPlaneNormal() const;
};
SMARTPTR(OdPrcOffsetCurve3d);

#endif // _PRCCRVOFFSET3d_INCLUDED_

