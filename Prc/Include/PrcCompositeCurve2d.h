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

#ifndef _PRCCRVCOMPOSITE_2D_INCLUDED_
#define _PRCCRVCOMPOSITE_2D_INCLUDED_ 
 

#include "PrcCurve2d.h"

/** \details 
<group PRC_Curve_Classes>

Class implements a two-dimensional composite curve containing one or several sub curves.

\remarks
Each of the sub curves must also be a two-dimensional and piecewise continuous curve. 
Transformation can be one of the following:
  <table>
    Value   Description
    0x00    Identity
    0x01    Translate
    0x02    Rotate
    0x08    Scale
  </table>
  
The composite curve can be reparameterized and trimmed using the setParameterization() or setData() methods.
*/
class PRC_TOOLKIT OdPrcCompositeCurve2d : public OdPrcCurve2d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcCompositeCurve2d)
  //DOM-IGNORE-END

  /** \details
  Destroys the composite curve.
  */
  ~OdPrcCompositeCurve2d();
  
  /** \details
  Sets new values of the composite curve's data.
  
  \param base_curve [in] An array of sub curves which the composite curve must consist of.
  \param base_sense [in] An array of sub curves direction data (each element is true if the sub curve has the same direction as the composite curve or false if it is not).
  \param is_closed [in] A new value of the closed curve flag (is true if composite curve is closed or false in the other case).
  \param param [in] A new parameterization parameters value.
  
  \returns Returns eOk if all the passed information was successfully set to the composite curve or an appropriate error in the other case.
  */
  OdResult setData(const OdPrcCurvePtrArray& base_curve, const OdBoolArray& base_sense, bool is_closed, const OdPrcParameterization& param);

  /** \details
  Sets the  closed curve flag.
  \param bIsClosed [in] A new value of the closed curve flag.
  */
  void setIsClosed(bool bIsClosed);

  /** \details
  Returns the current value of the closed curve flag. 
  If returned value is equal to true, the composite curve is closed.
  */
  bool isClosed() const;

  /** \details
  Returns the current array of sub curves included in the composite curve.
  Array of sub curves is returned as a reference to an OdPrcCurvePtrArray object, therefore it can be used to set new array of sub curves for the composite curve.
  */
  OdPrcCurvePtrArray &baseCurve();

  /** \details
  Returns the current array of sub curves included in the composite curve.
  */
  const OdPrcCurvePtrArray &baseCurve() const;
  
  /** \details
  Returns the current sub curve's direction data.
  Array of base sence is returned as a reference to an OdBoolArray object, therefore it can be used to set new array of base sence for the composite curve.
  */
  OdBoolArray &baseSense();

  /** \details
  Returns the current sub curve's direction data.
  */
  const OdBoolArray &baseSense() const;
};
SMARTPTR(OdPrcCompositeCurve2d);

#endif // _PRCCRVCOMPOSITE_2D_INCLUDED_

