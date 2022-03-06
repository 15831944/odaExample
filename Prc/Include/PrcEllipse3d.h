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

#ifndef _PRCCRVELLIPSE3D_INCLUDED_
#define _PRCCRVELLIPSE3D_INCLUDED_ 
 

#include "PrcCurve3d.h"

/** \details 
<group PRC_Curve_Classes>

Class implements a three-dimensional ellipse with its possible parameterization and transformation for positioning in model space. 
\remarks
Transformation can be one of the following:
  <table>
    Value  Description
    0x00  Identity
    0x01  Translate
    0x02  Rotate
    0x08  Scale
  </table>

OdPrcEllipse3d inherits the OdPrcCurve class and can be reparameterized and trimmed through the OdPrcParameterization class and setParameterization() method. 
*/
class PRC_TOOLKIT OdPrcEllipse3d : public OdPrcCurve3d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcEllipse3d)
  //DOM-IGNORE-END

  /** \details
  Destroys the ellipse object.
  */
  ~OdPrcEllipse3d();
  
  /** \details
  Sets a new value of the ellipse radius at the Y-axis.
  
  \param radius_at_y_axis [in] A new Y-axis radius value to be set.
  */
  void setRadiusAtYAxis(double radius_at_y_axis);
  
  /** \details
  Returns the current ellipse Y-axis radius value.
  */
  double radiusAtYAxis() const;
  
  /** \details
  Sets a new value of the ellipse radius at the X-axis.
  
  \param radius_at_x_axis [in] A new X-axis radius value to be set.
  */
  void setRadiusAtXAxis(double radius_at_x_axis);
  
  /** \details
  Returns the current ellipse X-axis radius value.
  */
  double radiusAtXAxis() const;
};
SMARTPTR(OdPrcEllipse3d);

#endif // _PRCCRVELLIPSE3D_INCLUDED_

