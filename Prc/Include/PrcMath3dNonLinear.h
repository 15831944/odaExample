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

#ifndef _PRCMATH3DNONLINEAR_INCLUDED_
#define _PRCMATH3DNONLINEAR_INCLUDED_ 
 

#include "PrcMath3dLinear.h"

/** \details 
<group PRC_Mathematical_Operator_Classes> 

Class stores information about the evaluation of a 3D non-linear function.
*/
class PRC_TOOLKIT OdPrcMath3dNonLinear : public OdPrcMath3d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_MATH(OdPrcMath3dNonLinear)
  //DOM-IGNORE-END

  /** \details
  Sets a new square discriminant value.

  \param d2 [in] A new square discriminant value to be set.
  */
  void setD2(double d2);
  
  /** \details
  Returns the current square discriminant value.
  */
  double d2() const;

  /** \details
  Evaluates a specified parameter using the following formula: 

  tmp_result = left_transformation.evaluate(param);
  output.x = tmp_result.x * cos(tmp_result.y * d2); 
  output.y = tmp_result.x * sin(tmp_result.y *d2);
  output.z = tmp_result.z;
  output = right_transformation.evaluate(output);

  \param ptBase [in] A parameter to be evaluated.
  */
  virtual OdGePoint3d transformPoint( const OdGePoint3d& ptBase ) const;

  /** \details
  Sets a new left 3D non-linear transformation. 

  \param value [in] A new left 3D non-linear transformation to be set.

  \returns Returns eOk if a new left 3D non-linear transformation was successfully set or an appropriate error code in the other case.
  */
  OdResult setLeftTransformation(const OdPrcMath3dLinearPtr &value);

  /** \details
  Returns the current left 3D non-linear transformation.
  */
  const OdPrcMath3dLinearPtr &leftTransformation() const;

  /** \details
  Sets a new right 3D non-linear transformation.

  \param value [in] A new right 3D non-linear transformation to be set.

  \returns Returns eOk if a new right 3D non-linear transformation was successfully set or an appropriate error code in the other case.
  */
  OdResult setRightTransformation(const OdPrcMath3dLinearPtr &value);

  /** \details
  Returns the current right 3D non-linear transformation.
  */
  const OdPrcMath3dLinearPtr &rightTransformation() const;
};

SMARTPTR(OdPrcMath3dNonLinear);

#endif // _PRCMATH3DNONLINEAR_INCLUDED_

