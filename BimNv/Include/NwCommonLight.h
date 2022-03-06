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

#ifndef __TNW_COMMONLIGHT_H__
#define __TNW_COMMONLIGHT_H__

#include "NwObject.h"
#include "NwLightValueType.h"
#define STL_USING_MAP
#include "OdaSTL.h"

class OdNwColor;
class OdGeVector3d;
class OdGePoint3d;
class OdGeMatrix3d;
class OdNwVariant;
class OdNwProperty;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwProperty object pointers.
*/
typedef OdSmartPtr<OdNwProperty> OdNwPropertyPtr;

/** \details
  This class represents a common light of the model.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwCommonLight : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwCommonLight);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwCommonLight
    class.
  */
  OdNwCommonLight();

  /** \details
    Constructor for objects of the OdNwCommonLight class. Creates a new
    OdNwCommonLight object for the specified item.

    \param pImpl [in] Item to create an OdNwCommonLight object for.
  */
  explicit OdNwCommonLight(OdNwObjectImpl* pImpl);

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwCommonLight();

public:
  /** \details
    Checks whether the light is enabled. 

    \returns True if the light is enabled, or false otherwise.
  */
  bool isLightOn() const;

  /** \details
    Returns the ambient color of this light.

    \returns Returns an OdNwColor object with the ambient color of this light.
  */
  OdNwColor getAmbient() const;

  /** \details
    Returns the diffuse color of this light.

    \returns Returns an OdNwColor object with the diffuse color of this light.

    \remarks It is the main color.
  */
  OdNwColor getDiffuse() const;

  /** \details
    Returns the specular color of this light.

    \returns Returns an OdNwColor object with the specular color of this light.

    \remarks It is the main color.
  */
  OdNwColor getSpecular() const;

  /** \details
    Returns the variant param value depending on the value of the paramter's type.

    \param
      type [in] Parameter with type NwLightValueType::Enum.

    \returns
      Returns the OdNwVariant value depending on the value of the type.

    \remarks
      Type must be one of the following:

    <table>
    Name                                         Value     Description 
    NwLightValueType::light_filter_color          0         OdNwColor value with the filter color of a common light
    NwLightValueType::light_tint_color            1         OdNwColor value with the tint color of a common light
    NwLightValueType::light_rgb_color             2         OdNwColor value with the RGB light color of a common light
    NwLightValueType::light_shadow_color          3         OdNwColor value with the shadow color of a common light
    NwLightValueType::light_intensity_value       4         Double value with the intensity of a common light
    NwLightValueType::light_position_is_targeted  5         Boolean value with the target status of a position light
    NwLightValueType::light_spot_web_matrix       6         Matrix value with the web rotation, scale and translation of a spot light
    NwLightValueType::light_ambient_only_flag     7         Boolean value with the ambient-only status of a common light
    NwLightValueType::light_use_tint_flag         8         Boolean value with the tint-use status of a common light
    NwLightValueType::light_shadow_on_flag        9         Boolean value with the shadow-enabled status of a common light
    </table>
  */
  OdNwVariant getValue(NwLightValueType::Enum val_type) const;

  /** \details
    Checks whether the light has a stable ID.

    \returns True if the light has a stable ID, or false otherwise.
  */
  bool hasStableId() const;

  /** \details
    Returns the Int64 stable ID of the light.

    \returns Int64 stable ID of the light as an OdUInt64 object.
  */
  OdUInt64 getInt64StableId() const;

  /** \details
    Returns the string stable ID of the light.

    \returns String stable ID of the light as an OdString object.
  */
  OdString getStringStableId() const;

  /** \details
    Returns the display name of the light.

    \returns Display name of the light as an OdString object.

    \remarks Display name is a localized name.
  */
  OdString getDisplayName() const;

  /** \details
    Returns the name of the light.

    \returns Name of the light as an OdString object.
  */
  OdString getName() const;

  /** \details
    Gets the properties of the light as std::map.

    \param mProperties [out] std::map with smart pointers to properties as values, and string descriptions as keys.

    \returns eOk if the properties are retrieved successfully, or an appropriate error code otherwise.
  */
  OdResult getProperties(std::map<OdString, OdNwPropertyPtr>& mProperties) const;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwCommonLight object pointers.
*/
typedef OdSmartPtr<OdNwCommonLight> OdNwCommonLightPtr;

#endif //__TNW_COMMONLIGHT_H__
