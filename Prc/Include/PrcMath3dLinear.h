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

#ifndef _PRCMATH3DLINEAR_INCLUDED_
#define _PRCMATH3DLINEAR_INCLUDED_ 
 

#include "PrcMath3d.h"
#include "Ge/GeMatrix3d.h"

/** \details 
<group PRC_Mathematical_Operator_Classes> 

Class stores information about the evaluation of a 3D linear function.
*/
class PRC_TOOLKIT OdPrcMath3dLinear : public OdPrcMath3d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_MATH(OdPrcMath3dLinear)
  //DOM-IGNORE-END

  /** \details
  Returns the current matrix with size 3x3.
  The matrix is returned as a reference to an OdGeMatrix3d object, therefore it can be used to set a new matrix.
  */
  OdGeMatrix3d &mat();
  
  /** \details
  Returns the current matrix with size 3x3.
  */
  const OdGeMatrix3d &mat() const;

  /** \details
  Sets a new vector of 3 coordinates.

  \param value [in] A new vector of 3 coordinates to be set.
  */
  void setVect(const OdDoubleArray &value);

  /** \details
  Returns the current vector of 3 coordinates.
  */
  OdDoubleArray vect() const;

  /** \details
  Evaluates a specified parameter using the following formula: 

  output.x = mat[0] [0] * param.x + mat[1] [0] * param.y + mat[2][0] * param.z + vect[0]
  output.y = mat[0] [1] * param.x + mat[1] [1] * param.y + mat[2][1] * param.z + vect[1] 
  output.z = mat[0] [2] * param.x + mat[1] [2] * param.y + mat[2][2] * param.z + vect[2]

  \param ptBase [in] A parameter to be evaluated.
  */
  virtual OdGePoint3d transformPoint( const OdGePoint3d& ptBase ) const;
};

SMARTPTR(OdPrcMath3dLinear);

#endif // _PRCMATH3DLINEAR_INCLUDED_

