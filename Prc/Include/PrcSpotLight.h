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

#ifndef _PRCSPOTLIGHT_INCLUDED_
#define _PRCSPOTLIGHT_INCLUDED_ 
 

#include "PrcContentPointLight.h"

SMARTPTR(OdPrcSpotLight);

/** \details 
<group PRC_Graphic_Classes> 

Class stores information about a light from a spot illumination.
*/
class PRC_TOOLKIT OdPrcSpotLight : public OdPrcContentPointLight
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcSpotLight);
  //DOM-IGNORE-END

  /** \details
  Returns the current direction of the light.
  The light direction is returned as a reference to an OdGeVector3d object, therefore it can be used to set a new direction or modify the current one.
  */
  OdGeVector3d &direction();
  
  /** \details
  Returns the current direction of the light.
  */
  const OdGeVector3d &direction() const;
  
  /** \details
  Sets a new distribution intensity of the light.

  \param fallOffExponent [in] A new distribution intensity of the light to be set.
  */
  void setFallOffExponent(double fallOffExponent);
  
  /** \details
  Returns the current distribution intensity of the light.
  */
  double fallOffExponent() const;
  
  /** \details
  Sets a new maximum light spread angle.

  \param fallOffAngle [in] A new maximum light spread angle to be set.
  */
  void setFallOffAngle(double fallOffAngle);
  
  /** \details
  Returns the current maximum light spread angle.
  */
  double fallOffAngle() const;
};

typedef OdArray<OdPrcSpotLight> OdPrcSpotLightArray;

#endif // _PRCSPOTLIGHT_INCLUDED_

