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

#ifndef _PRCCRVCIRCLE_2D_INCLUDED_
#define _PRCCRVCIRCLE_2D_INCLUDED_ 
 

#include "PrcCurve2d.h"

/** \details 
<group PRC_Graphic_Classes>

Class implements a two-dimensional circle with its possible parameterization and transformation for positioning in model space. 
\remarks
Transformation can be one of the following:
  <table>
    Value  Description
    0x00  Identity
    0x01  Translate
    0x02  Rotate
    0x08  Scale
  </table>

  OdPrcCircle2d inherits the OdPrcCurve class and can be reparameterized and trimmed using the OdPrcParameterization class and setParameterization() method. 
*/
class PRC_TOOLKIT OdPrcCircle2d : public OdPrcCurve2d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcCircle2d)
  //DOM-IGNORE-END

  /** \details
  Destroys the circle.
  */
  ~OdPrcCircle2d();
  
  /** \details
  Sets a new value of the circle radius.
  
  \param radius [in] A new radius value to be set.
  */  
  void setRadius(double radius);
  
  /** \details
  Returns the current circle radius value.
  */  
  double radius() const;
};
SMARTPTR(OdPrcCircle2d);

#endif // _PRCCRVCIRCLE_2D_INCLUDED_

