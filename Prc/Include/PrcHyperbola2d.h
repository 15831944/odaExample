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

#ifndef _PRCCRVHYPERBOLA_2D_INCLUDED_
#define _PRCCRVHYPERBOLA_2D_INCLUDED_ 
 

#include "PrcCurve2d.h"

/** \details
<group PRC_Curve_Classes>

Class implements a two-dimensional hyperbola defined on an [-infinite, infinite] interval.
A hyperbola can be parameterized and transformed for positioning in model space. 
\remarks
Transformation can be one of the following:
  <table>
    Value  Description
    0x00  Identity
    0x01  Translate
    0x02  Rotate
    0x08  Scale
  </table>

OdPrcHyperbola2d inherits the OdPrcCurve class and can be reparameterized and trimmed using the OdPrcParameterization class and setParameterization() method. 
*/
class PRC_TOOLKIT OdPrcHyperbola2d : public OdPrcCurve2d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcHyperbola2d)
  //DOM-IGNORE-END

  /** \details
  Destroys the hyperbola.
  */
  ~OdPrcHyperbola2d();
  
  /** \details
  Sets a new value of the semi_image_axis length for the hyperbola.
  The semi_image_axis length determines the length the hyperbola is centered with at the origin. The semi_image_axis length is along the Y-axis. 
  
  \param semi_image_axis [in] A new value of the semi_image_axis to be set. 
  */
  void setSemiImageAxis(double semi_image_axis);
  
  /** \details
  Returns the current value of the semi_image_axis length for the hyperbola. 
  The semi_image_axis length determines the length the hyperbola is centered with at the origin. The semi_image_axis length is along the Y-axis. 
  */
  double semiImageAxis() const;
  
  /** \details
  Sets a new value of the semi_axis length for the hyperbola. 
  The semi_axis length determines the length the hyperbola is centered with at the origin. The semi_axis length is along the X-axis. 
  
  \param semi_axis [in] A new value of the semi_axis to be set.
  */
  void setSemiAxis(double semi_axis);
  
  /** \details
  Returns the current value of the semi_axis length for the hyperbola. 
  The semi_axis length determines the length the hyperbola is centered with at the origin. The semi_axis length is along the X-axis. 
  */
  double semiAxis() const;
 
   /** \details
  Sets a new value of the hyperbola parameterization type. 
  There are two types of hyperbola parameterization: 
  <table>
    Value  Description
    0      Parameter represents the Y-axis coordinate value.
    1      Parameterization formula is used. It is based on cosh (x) and sinh(y) functions.
  </table>
  
  \param value [in] A new value of the parameterization type.
  
  \returns Returns eOk if a new parameterization type was successfully set or an appropriate error code in the other case.
  */
  OdResult setParameterizationType(OdUInt8 value);
  
  /** \details
  Returns the current parameterization type used for the hyperbola.
  
  There are two types of hyperbola parameterization: 
  <table>
    Value  Description
    0      Parameter represents the Y-axis coordinate value.
    1      Parameterization formula is used. It is based on cosh (x) and sinh(y) functions.
  </table>
  */
  OdUInt8 parameterizationType() const;
};
SMARTPTR(OdPrcHyperbola2d);

#endif // _PRCCRVHYPERBOLA_2D_INCLUDED_

