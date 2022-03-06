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

#ifndef _PRCCRVEQUATION_2D_INCLUDED_
#define _PRCCRVEQUATION_2D_INCLUDED_ 
 

#include "PrcCurve2d.h"
#include "PrcMath1d.h"

/** \details 
<group PRC_Curve_Classes> 

Class implements a two-dimensional curve defined by mathematical functions of one variable on the X and Y axis. 
Equation curve can be parameterized and transformed for positioning in model space. 
\remarks
Transformation can be one of the following:
  <table>
    Value  Description
    0x00  Identity
    0x01  Translate
    0x02  Rotate
    0x08  Scale
  </table>

  OdPrcEquationCurve2d inherits the OdPrcCurve class and can be reparameterized and trimmed using the OdPrcParameterization class and setParameterization() method. 
*/
class PRC_TOOLKIT OdPrcEquationCurve2d : public OdPrcCurve2d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcEquationCurve2d)
  //DOM-IGNORE-END

  /** \details
  Destroys the equation curve object.
  */
  ~OdPrcEquationCurve2d();

  /** \details
  Sets a new mathematical function for the X-axis of the equation curve.
  
  \param value [in] A new function to be set.
  
  \returns Returns eOk if a new function was successfully set or an appropriate error code in the other case.
  */
  OdResult setFunctionX(const OdPrcMath1dPtr &value);
  
  /** \details
  Returns the current mathematical function for the X-axis.
  */
  const OdPrcMath1dPtr &functionX() const;

  /** \details
  Sets a new mathematical function for the Y-axis of the equation curve.
  
  \param value [in] A new function to be set.
  
  \returns Returns eOk if a new function was successfully set or an appropriate error code in the other case.
  */
  OdResult setFunctionY(const OdPrcMath1dPtr &value);
  
  /** \details
  Returns the current mathematical function for the Y-axis.
  */
  const OdPrcMath1dPtr &functionY() const;
};
SMARTPTR(OdPrcEquationCurve2d);

#endif // _PRCCRVEQUATION_2D_INCLUDED_

