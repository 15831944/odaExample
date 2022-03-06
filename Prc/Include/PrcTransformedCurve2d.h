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

#ifndef _PRCCRVTRANSFORM_2D_INCLUDED_
#define _PRCCRVTRANSFORM_2D_INCLUDED_ 
 

#include "PrcCurve2d.h"
#include "PrcMath3d.h"

/** \details
<group PRC_Curve_Classes>

Class implements a two-dimensional transformed curve.
A transformed curve is a curve defined by the result of a three-dimensional mathematical function applied to a base curve.
A transfomed curve can be parameterized and transformed for positioning in model space. 

\remarks
Transformation can be one of the following:
  <table>
    Value  Description
    0x00  Identity
    0x01  Translate
    0x02  Rotate
    0x08  Scale
  </table>
  
OdPrcTransformedCurve2d inherits the OdPrcCurve class and can be reparameterized and trimmed using the OdPrcParameterization class and setParameterization() method. 
*/
class PRC_TOOLKIT OdPrcTransformedCurve2d : public OdPrcCurve2d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcTransformedCurve2d)
  //DOM-IGNORE-END

  /** \details
  Destroys the transformed curve object.
  */
  ~OdPrcTransformedCurve2d();

  /** \details
  Returns the current 3D mathematical function applied to the base curve of the transformed curve. Represented as a reference to a smart pointer to an OdPrcMath3d object.
  The 3D mathematical function is returned as a reference to a smart pointer to an OdPrcMath3d object, therefore it can be used to set a new 3D mathematical function.
  */
  OdPrcMath3dPtr &mathTransformation();
  
  /** \details
  Returns the current 3D mathematical function applied to the base curve of the transformed curve.
  */
  const OdPrcMath3dPtr &mathTransformation() const;
  
  /** \details
  Sets a new base curve for the transformed curve.
  
  \param value [in] A new base curve to be set.
  
  \returns Returns eOk if a new base curve was successfully set or an appropriate error code in the other case.
  */
  OdResult setBaseCurve(const OdPrcCurvePtr &value);
  
  /** \details
  Returns the current base curve for the transformed curve.
  */
  const OdPrcCurvePtr &baseCurve() const;
};
SMARTPTR(OdPrcTransformedCurve2d);

#endif // _PRCCRVTRANSFORM_2D_INCLUDED_

