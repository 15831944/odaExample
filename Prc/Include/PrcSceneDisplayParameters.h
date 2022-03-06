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

#ifndef _PRCSCENEDISPLAYPARAMETERS_INCLUDED_
#define _PRCSCENEDISPLAYPARAMETERS_INCLUDED_ 
 

#include "PrcSurface.h"
#include "PrcCamera.h"
#include "PrcAmbientLight.h"
#include "PrcBase.h"

SMARTPTR(OdPrcSceneDisplayParameters);

/** \details 
<group PRC_Graphic_Classes> 

Class representing a group of parameters used for scene visualization, such as an ambient light and camera. 
*/
class PRC_TOOLKIT OdPrcSceneDisplayParameters : public OdPrcReferencedBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcSceneDisplayParameters)
  //DOM-IGNORE-END

  /** \details
  Returns the current array of parameter types.
  The array of parameter types is returned as a reference to an OdUInt32Array object, therefore it can be used to set new parameter types and change existing ones.

  */
  OdUInt32Array &types();

  /** \details
  Returns the current array of parameter types.
  */
  const OdUInt32Array &types() const;

  /** \details
  Returns the current rotation center. 
  Rotation center is a point around which all objects in the scene shall turn.
  The rotation center is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new rotation center or change the existing one.
  */
  OdGePoint3d &rotationCenter();

  /** \details
  Returns the current rotation center. 
  Rotation center is a point around which all objects in the scene shall turn.
  */
  const OdGePoint3d &rotationCenter() const;

  /** \details
  Returns the current array of ambient light identifiers.
  The array of ambient light identifiers is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to add new identifiers or change existing ones.
  */
  OdPrcObjectIdArray &ambientLight();
  
  /** \details
  Returns the current array of ambient light identifiers.
  */
  const OdPrcObjectIdArray &ambientLight() const;

  /** \details
  Returns the current identifier of the camera used in the scene visualization.
  The camera identifier is returned as a reference to an OdPrcObjectId object, therefore it can be used to set a identifier.
  */
  OdPrcObjectId &camera();

  /** \details
  Returns the current identifier of the camera used in the scene visualization.
  */
  const OdPrcObjectId &camera() const;

  /** \details
  Returns the current array of planar surfaces.
  The array of planar surfaces is returned as a reference to an OdPrcSurfacePtrArray object, therefore it can be used to set new planar surfaces or change existing ones.
  */
  OdPrcSurfacePtrArray &clippingPlanes();

  /** \details
  Returns the current array of planar surfaces.
  */
  const OdPrcSurfacePtrArray &clippingPlanes() const;

  /** \details
  Returns the current array of default line attributes.
  The array of default line style ids is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new line style ids or change existing ones.
  */
  OdPrcObjectIdArray &defaultStylesPerType();
  
  /** \details
  Returns the current array of default line styles.
  */
  const OdPrcObjectIdArray &defaultStylesPerType() const;
  
  /** \details
  Returns the current background line style.
  The background line style is returned as a reference to an OdPrcObjectId object, therefore it can be used to set a new line style.
  */
  OdPrcObjectId &backgroundStyle();
  
  /** \details
  Returns the current background line style.
  */
  const OdPrcObjectId  &backgroundStyle() const;
  
  /** \details
  Sets a new value of the active flag. 
  The active flag indicates whether the object is currently an active scene (if true).

  \param is_active [in] A a new flag value to be set.
  */
  void setIsActive(bool is_active);
  
  /** \details
  Returns the current value of the active flag. 
  The active flag indicates whether the object is currently an active scene (if true).
  */
  bool isActive() const;

  /** \details
  Sets a new value of the absolute flag.
  The absolute flag indicates whether the position of the camera, lights, and clipping planes are absolute.
  If the position of the camera, light, and clipping planes are absolute, the flag is equal to true; in the other case the flag is equal to false.

  \param is_absolute [in] A new flag value to be set.
  */
  void setIsAbsolute(bool is_absolute);

  /** \details
  Returns the current value of the absolute flag.
  The absolute flag indicates whether the position of the camera, lights, and clipping planes are absolute.
  If the position of the camera, light, and clipping planes are absolute, the flag is equal to true; in the other case the flag is equal to false.
  */
  bool isAbsolute() const;

  /** \details
  Returns the current default line style.
  The default line style is returned as a reference to an OdPrcObjectId object, therefore it can be used to set a new default line style.
  */
  OdPrcObjectId &defaultStyle();
  
  /** \details
  Returns the current default line style.
  */
  const OdPrcObjectId &defaultStyle() const;
};

typedef OdArray<OdPrcSceneDisplayParameters> OdPrcSceneDisplayParametersArray;

#endif // _PRCSCENEDISPLAYPARAMETERS_INCLUDED_

