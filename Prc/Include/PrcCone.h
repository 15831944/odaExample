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

#ifndef _PRCSRFCONE_INCLUDED_
#define _PRCSRFCONE_INCLUDED_ 
 

#include "PrcSurface.h"

/** \details 
<group PRC_Surface_Classes> 

Class implements a conical surface. The axis of this surface lies along the z-axis.
*/
class PRC_TOOLKIT OdPrcCone : public OdPrcSurface
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_SURF(OdPrcCone)
  //DOM-IGNORE-END

  /** \details
  Destroys the conical surface.
  */
  ~OdPrcCone();
  
  /** \details 
  Sets a new value of a semi angle.

  \param semi_angle [in] A new value of the angle in radians to be set.
  */
  void setSemiAngle(double semi_angle);
  
  /** \details
  Returns the current value of the semi angle in radians.
  */
  double semiAngle() const;
  
  /** \details
  Sets a new value of the bottom radius.

  \param bottom_radius [in] A new value of the bottom radius to be set.
  */
  void setBottomRadius(double bottom_radius);
  
  /** \details
  Returns the current value of the bottom radius.
  */
  double bottomRadius() const;
};

SMARTPTR(OdPrcCone);

#endif // _PRCSRFCONE_INCLUDED_

