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

#ifndef _PRCDIRECTIONALLIGHT_INCLUDED_
#define _PRCDIRECTIONALLIGHT_INCLUDED_ 
 

#include "PrcContentLight.h"

SMARTPTR(OdPrcDirectionalLight);


/** \details 
<group PRC_Graphic_Classes> 

Class representing a scene directional illumination.
*/
class PRC_TOOLKIT OdPrcDirectionalLight : public OdPrcContentLight
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcDirectionalLight);
  //DOM-IGNORE-END

  /** \details
  Returns the current direction of the light.
  The direction is returned as a reference to an OdGeVector3d object, therefore it can be used to set a new direction.
  */
  OdGeVector3d &direction();

  /** \details
  Returns the current direction of the light.
  */
  const OdGeVector3d &direction() const;

  /** \details
  Sets a new light intensity value of the directional light.

  \param light_intensity [in] A new light intensity value to be set. Must be in the range [0.0, 1.0].
  */
  void setLightIntensity(double light_intensity);

  /** \details
  Returns the current light intensity value of the directional light.
  The light intensity value is in the range [0.0, 1.0].
  */  
  double lightIntensity() const;
};

typedef OdArray<OdPrcDirectionalLight> OdPrcDirectionalLightArray;

#endif // _PRCDIRECTIONALLIGHT_INCLUDED_

