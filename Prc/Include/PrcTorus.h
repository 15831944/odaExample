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

#ifndef _PRCSRFTORUS_INCLUDED_
#define _PRCSRFTORUS_INCLUDED_ 
 

#include "PrcSurface.h"

/** \details 
<group PRC_Surface_Classes> 

Class representing a torus centred at the origin. 
The major axis of this surface is placed in the XY plane. 
*/
class PRC_TOOLKIT OdPrcTorus : public OdPrcSurface
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_SURF(OdPrcTorus)
  //DOM-IGNORE-END

  /** \details
  Destroys the torus.
  */
  ~OdPrcTorus();
  
  /** \details
  Sets a new minor radius value.

  \param minor_radius [in] A new minor radius value to be set.
  */
  void setMinorRadius(double minor_radius);
  
  /** \details
  Returns the current minor radius value.
  */
  double minorRadius() const;
  
  /** \details
  Sets a new major radius value.

  \param major_radius [in] A new major radius value to be set.
  */
  void setMajorRadius(double major_radius);
  
  /** \details
  Returns the current major radius value.
  */
  double majorRadius() const;
};

SMARTPTR(OdPrcTorus);

#endif // _PRCSRFTORUS_INCLUDED_

