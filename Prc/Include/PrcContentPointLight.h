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

#ifndef _PRCCONTENTPOINTLIGHT_INCLUDED_
#define _PRCCONTENTPOINTLIGHT_INCLUDED_ 
 

#include "PrcContentLight.h"

/** \details 
<group PRC_Graphic_Classes> 

Class representing a light of a scene from a point with attenuation factors.
*/
class PRC_TOOLKIT OdPrcContentPointLight : public OdPrcContentLight
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_NOTYPE_PRCBASE(OdPrcContentPointLight)
  //DOM-IGNORE-END

  /** \details
  Returns current point location coordinates of a light.
  Point location coordinates are returned as a reference to an OdGePoint3d object, therefore it can be used to set a new location.
  */
  OdGePoint3d &location();
  
  /** \details
  Returns current point location coordinates of a light.
  */
  const OdGePoint3d &location() const;

  /** \details
  Sets a new value of the quadratic light attenuation factor.

  \param quadratic_attenuation [in] A new value in the range [0.0, 1.0] to be set.
  */
  void setQuadraticAttenuation(double quadratic_attenuation);

  /** \details
  Returns the current value of the quadratic light attenuation factor.
  Returned value is in the range [0.0, 1.0].
  */
  double quadraticAttenuation() const;
  
  /** \details
  Sets a new value of the linear light attenuation factor.
  
  \param linear_attenuation [in] A new value in the range [0.0, 1.0] to be set.
  */
  void setLinearAttenuation(double linear_attenuation);

  /** \details
  Returns the current value of the linear light attenuation factor.
  Returned value is in the range [0.0, 1.0].
  */
  double linearAttenuation() const;

  /** \details
  Sets a new value of the constant light attenuation factor.
  
  \param constant_attenuation [in] A new value in the range [0.0, 1.0] to be set.
  */
  void setConstantAttenuation(double constant_attenuation);

  /** \details
  Returns the current value of the constant light attenuation factor.
  Returned value is in the range [0.0, 1.0].
  */
  double constantAttenuation() const;
};

typedef OdArray<OdPrcContentPointLight> OdPrcContentPointLightArray;

#endif // _PRCCONTENTPOINTLIGHT_INCLUDED_

