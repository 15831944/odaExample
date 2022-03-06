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

#ifndef _PRCCRVHELIXTYPE0_INCLUDED_
#define _PRCCRVHELIXTYPE0_INCLUDED_ 
 

#include "PrcCurve3d.h"
#include "PrcMath1d.h"

/** \details
<group PRC_Curve_Classes>

Class implements a helix with a constant pitch. A helix is a three-dimensional curve defined on an [-infinite, infinite] interval.
A helix can be parameterized and transformed for positioning in model space. 
\remarks
Transformation can be one of the following:
  <table>
    Value  Description
    0x00  Identity
    0x01  Translate
    0x02  Rotate
    0x08  Scale
  </table>

OdPrcHelixType0Curve inherits the OdPrcCurve class and can be reparameterized and trimmed using the OdPrcParameterization class and setParameterization() method. 
*/
class PRC_TOOLKIT OdPrcHelixType0Curve : public OdPrcCurve3d
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_CRV(OdPrcHelixType0Curve)
  //DOM-IGNORE-END

  /** \details 
  Destroys the helix.
  */
  ~OdPrcHelixType0Curve();
  
  /** \details
  Returns the current direction of the helix.
  The direction is returned as a reference to an OdGeVector3d object, therefore it can be used to set a new direction.
  */
  OdGeVector3d &direction();
  
  /** \details
  Returns the current direction of the helix.
  */
  const OdGeVector3d &direction() const;
  
  /** \details
  Returns the current origin point on the helix axis.
  The origin point is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new origin point.
  */
  OdGePoint3d &origin();
  
  /** \details
  Returns the current origin point on the helix axis.
  */
  const OdGePoint3d &origin() const;
  
  /** \details
  Returns the current start point of the helix.
  The start point is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new start point.
  */
  OdGePoint3d &start();
  
  /** \details
  Returns the current start point of the helix.
  */
  const OdGePoint3d &start() const;
  
  /** \details
  Sets a new value of the radius evolution of the helix.
  
  \param radius_evolution [in] A new value of the radius evolution to be set.
  */  
  void setRadiusEvolution(double radius_evolution);
  
  /** \details
  Returns the current value of the radius evolution of the helix.
  */  
  double radiusEvolution() const;
  
  /** \details
  Sets a new value of the helix pitch.
  
  \param pitch [in] A new value of the pitch to be set.
  */  
  void setPitch(double pitch);
  
  /** \details
  Returns the current value of the helix pitch.
  */  
  double pitch() const;
  
  /** \details
  Sets the trigonometric orientation flag.
  The trigonometric orientation flag determines the turn direction of the helix.
  If the flag is set to true, the helix turns in the clockwise direction; if the flag is set to false, it turns in the counter-clockwise direction.  
  
  \param trigonometric_orientation [in] A new value of the trigonometric orientation.
  */
  void setTrigonometricOrientation(bool trigonometric_orientation);
  
  /** \details
  Returns the current value of the trigonometric orientation flag.
  The trigonometric orientation flag determines the turn direction of the helix.
  If the flag is set to true, the helix turns in the clockwise direction; if the flag is set to false, it turns in the counter-clockwise direction.
  */
  bool trigonometricOrientation() const;
};
SMARTPTR(OdPrcHelixType0Curve);

#endif // _PRCCRVHELIXTYPE0_INCLUDED_

