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

#ifndef _ODTV_MATERIAL_H_INCLUDED_
#define _ODTV_MATERIAL_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvUserData.h"

class OdTvMaterialColor;
class OdTvMaterialMap;

class OdTvColorDef;

/** \details
  The abstract interface class that implements handling of material entities supported by ODA Visualize SDK.
  \sa
  <link tv_working_with_attributes_materials, Work with Materials>
*/
class ODTV_EXPORT OdTvMaterial : public OdTvHandledIObject
{
public:

  /** \details
    Sets a new name for the material object.
    
    \param sName [in] A string that contains the new material object's name.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The name string length should be from 0 to 255 characters.
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    If the new material object name was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
    Retrieves the current material object's name.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string that contains the name of the material object.
    \remarks 
    If the rc parameter is not null and the name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getName(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new description for the material object. 
    
    It can be a comment or series of underscores, dots, dashes, and spaces to reflect the representation of the material. 
    The initial value is an empty string.
    \param sDescription [in] A string that contains the description.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new material object description was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setDescription(const OdString& sDescription) = 0;

  /** \details
    Retrieves the current material object's description.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string that contains the description of the material object.
    \remarks 
    If the rc parameter is not null and the description was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getDescription(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new ambient (shadow) color for the material object. 
    
    \param ambientColor [in] A new ambient color to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new ambient color was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setAmbient(const OdTvMaterialColor& ambientColor) = 0;

  /** \details
    Retrieves the current ambient (shadow) color of the material object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an <link OdTvMaterialColor, OdTvMaterialColor> object that contains the current ambient color.
    \remarks 
    If the rc parameter is not null and the ambient color was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvMaterialColor getAmbient(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new diffuse (main) color for the material object. 
    
    \param diffuseColor [in] A new diffuse color to be set.
    \param diffuseMap   [in] A diffuse map, according to which a material is applied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new diffuse color was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setDiffuse(const OdTvMaterialColor& diffuseColor, const OdTvMaterialMap& diffuseMap) = 0;

  /** \details
    Retrieves the current diffuse (main) color of the material object.
    
    \param diffuseColor [out] A placeholder for an <link OdTvMaterialColor, OdTvMaterialColor> object that represents the current diffuse color.
    \param diffuseMap   [out] A placeholder for an <link OdTvMaterialMap, OdTvMaterilMap> object that represents the current diffuse material map.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The method fills the passed color and material map objects and returns them to a calling subroutine.
    If the current diffuse color and diffuse map were successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getDiffuse(OdTvMaterialColor& diffuseColor, OdTvMaterialMap& diffuseMap) const = 0;

  /** \details
    Sets a new specular (reflection) color for the material object. 
    
    \param specularColor [in] A new specular color to be set.
    \param dGlossFactor  [in] A new value of the gloss factor.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new specular color and gloss factor were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setSpecular(const OdTvMaterialColor& specularColor, double dGlossFactor) = 0;

  /** \details
    Retrieves the current specular (reflection) color and gloss factor value of the material object.
    
    \param specularColor  [out] A placeholder for an <link OdTvMaterialColor, OdTvMaterialColor> object that represents the current specular color.
    \param dGlossFactor   [out] A placeholder for a gloss factor value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The method fills the passed color object and gloss factor placeholders and returns them to a calling subroutine.
    If the current specular color and gloss factor were successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getSpecular(OdTvMaterialColor& specularColor, double& dGlossFactor) const = 0;

  /** \details
    Sets a new emission (glow) color for the material object. 
    
    \param emissionColor [in] A new emission color to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new emission color was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEmission(const OdTvMaterialColor& emissionColor) = 0;

  /** \details
    Retrieves the current emission (glow) color of the material object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an <link OdTvMaterialColor, OdTvMaterialColor> object that contains the current emission color.
    \remarks 
    If the rc parameter is not null and the current emission color was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvMaterialColor getEmission(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new specular gloss value for the material object. 
    
    \param dSpecularGloss [in] A new specular gloss to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new specular gloss value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setSpecularGloss(double dSpecularGloss) = 0;

  /** \details
    Retrieves the current specular gloss value of the material object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current specular gloss value.
    \remarks 
    If the rc parameter is not null and the current specular gloss was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual double getSpecularGloss(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new opacity value for this material object. 
    
    \param dOpacityPercentage [in] A new opacity value to be set.
    \param pOpacityMap        [in] A new opacity map to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The opacity value varies from 0 (transparent) to 1 (non-transparent).
    If pOpacityMap is NULL, opacity value will be used.
    If the new opacity value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setOpacity(double dOpacityPercentage, const OdTvMaterialMap* pOpacityMap = NULL) = 0;

  /** \details
    Retrieves the current opacity value of the material object.
    
    \param opacityPercent [out] Opacity value.
    \param opacityMap     [out] A placeholder for an <link OdTvMaterialMap, OdTvMaterilMap> object that represents the current opacity material map.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    The method fills the passed value and material map objects and returns them to a calling subroutine.
    The opacity value varies from 0 (transparent) to 1 (non-transparent).
    If the current opacity value and opacity map were successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getOpacity(double& opacityPercent, OdTvMaterialMap& opacityMap) const = 0;

  /** \details
    Sets the bump component of this Material object.
    
    \param bumpMap [in]  A new bump map.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new bump map was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setBump(const OdTvMaterialMap& bumpMap) = 0;

  /** \details
    Returns the bump component of this Material object.
    
    \param bumpMap [out]  Receives the bump map.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult getBump(OdTvMaterialMap& bumpMap) const = 0;

  /** \details
    Sets the tint component of this Material object.
    
    \param tintColor [in]  A new tint color.
    \param bEnable [in]  Enables or disabled tint material channel.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new tint color was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setTint(const OdTvMaterialColor &tintColor, bool bEnable = true) = 0;

  /** \details
    Returns the tint component of this Material object.
    
    \param tintColor [out]  Receives the tint color.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true in case if tint material channel enabled or false elsewhere.
    \remarks
    If the rc parameter is not null and the current tint color was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getTint(OdTvMaterialColor &tintColor, OdTvResult *rc = NULL) const = 0;

  /** \details
    Sets a new secondary ambient (shadow) color for the material object. 
    
    \param ambientColor [in] A new <link OdTvMaterialColor, material color> to be set. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new secondary ambient color was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    Using this method makes sense only if non-texture mode support is enabled by the setSupportNonTextureMode() method.
  */
  virtual OdTvResult setSecondaryAmbient(const OdTvMaterialColor& ambientColor) = 0;

  /** \details
    Retrieves the current secondary ambient (shadow) color of the material object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a <link OdTvMaterialColor, material color> object that represents the current secondary ambient color.
    \remarks 
    If the rc parameter is not null and the current secondary ambient (shadow) color was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvMaterialColor getSecondaryAmbient(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new secondary diffuse color for the material object. 
    
    \param diffuseColor [in] A new <link OdTvMaterialColor, material color> to be set. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new secondary diffuse color was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    Using this method makes sense only if non-texture mode support is enabled by the setSupportNonTextureMode() method.
  */
  virtual OdTvResult setSecondaryDiffuse(const OdTvMaterialColor& diffuseColor) = 0;

  /** \details
    Retrieves the current secondary diffuse color of the material object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a <link OdTvMaterialColor, material color> object that represents the current secondary diffuse color.
    \remarks 
    If the rc parameter is not null and the current secondary diffuse color was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
  */
  virtual OdTvMaterialColor getSecondaryDiffuse(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new secondary specular (reflection) for the material object. 
    
    \param specularColor [in] A new <link OdTvMaterialColor, material color> to be set. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new secondary specular (reflection) was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    Using this method makes sense only if non-texture mode support is enabled by the setSupportNonTextureMode() method.
  */
  virtual OdTvResult setSecondarySpecular(const OdTvMaterialColor& specularColor) = 0;

  /** \details
    Retrieves the current secondary specular (reflection) of the material object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a <link OdTvMaterialColor, material color> object that represents the current secondary specular (reflection) color.
    \remarks 
    If the rc parameter is not null and the current secondary specular (reflection) was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
  */
  virtual OdTvMaterialColor getSecondarySpecular(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new secondary opacity value for the material object. 
    
    \param opacityPercentage [in] A new opacity value to be set. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The opacity value varies from 0 (transparent) to 1 (non-transparent).
    If the new secondary opacity value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    Using this method makes sense only if non-texture mode support is enabled by the setSupportNonTextureMode() method.
  */
  virtual OdTvResult setSecondaryOpacity(double opacityPercentage) = 0;

  /** \details
    Retrieves the current secondary opacity value of the material object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current secondary opacity value.
    \remarks 
    The opacity value varies from 0 (transparent) to 1 (non-transparent).
    If the rc parameter is not null and the current secondary opacity value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual double getSecondaryOpacity(OdTvResult* rc = NULL) const = 0;

  /** \details
    Enables or disables non-texture mode support for the material object.
    
    \param bNonTextureMode [in] A new support flag value. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the parameter passed to the method is equal to true, non-texture mode support is enabled; 
    otherwise (if the parameter is equal to false) non-texture mode support is disabled.
    Using this method makes sense only if materials are disabled for the current visual style.
    If non-texture mode support was successfully enabled or disabled, the method returns the tvOk value; 
    otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setSupportNonTextureMode(bool bNonTextureMode) = 0;

  /** \details
    Retrieves whether non-texture mode support is enabled for the material object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if non-texture mode support is enabled; otherwise the method returns false.
    \remarks 
    If the rc parameter is not null and the current value of the non-texture mode support flag was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
  */
  virtual bool getSupportNonTextureMode(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets coefficient of opacity influence onto received shadows.
    
    \param dShadowsOpacityEffect [in]  Coefficient in 0.0-1.0 range.
    \param dNonShadowLightsMergeEffect [in]  Value in 0.0-1.0 range that influences ignoring shadows casting by lights.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The effect percentage value varies from 0 to 1.
    If dNonShadowLightsMergeEffect is 0.0 lights can cast shadows on the material, if dNonShadowLightsMergeEffect is 1.0 - lights do not cast shadows on the material.
    If the new shadows opacity effect and shadow lights merge effect values were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setShadowsOpacityEffect(double dShadowsOpacityEffect, double dNonShadowLightsMergeEffect = 1.0) = 0;

  /** \details
    Returns coefficient of opacity influence onto received shadows.
    
    \param nonShadowLightsMergeEffect [out]  Receives a value in 0.0-1.0 range that influences ignoring shadows casting by lights.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current shadows opacity effect value.
    \remarks
    Coefficient set to 1.0 by default, which is means that shadows opacity fully depends from material opacity.
  */
  virtual double getShadowsOpacityEffect(double* dNonShadowLightsMergeEffect = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets that for the specular highlighting it is need to use value from the visual style
    
    \param bUse               [in]  New value for the flag which indicates that it is need to use specular value from the visual style
    \param dMaxSpecularFactor [in]  Maximal specular highlighting factor
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The maximal specular factor varies from 0.01 to 1. Final specular parameter should be in the range [1;128]. The maximal specular factor 
    allows to vary this range. When the maximal specular factor is equal to 1, the final specular parameter will be in the range of [1;128]
    (for the value in Visual style equal to 0% the final specular parameter will 128, for the value in Visual style equal to 100% the final specular parameter will 1).
    When the maximal specular factor is equal to 0.5, the final specular parameter will be in the range of [1;64]
    (for the value in Visual style equal to 0% the final specular parameter will 64, for the value in Visual style equal to 100% the final specular parameter will 1). And so on.
  */
  virtual OdTvResult setUseVisualStyleSpecular(bool bUse, double dMaxSpecularFactor = 0.1) = 0;

  /** \details
    Checks whether the specular highlighting should be used a value from the visual style.
    
    \param dMaxSpecularFactor [out] Maximal specular highlighting factor
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns flag that indicates whether for the specular highlighting should be used a value from the visual style.
    \remarks
    This flag is set to false by default which means that for specular highlighting would be used material's own value.
  */
  virtual bool getUseVisualStyleSpecular(double* dMaxSpecularFactor = NULL, OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvMaterial, OdTvMaterial> object.
*/
typedef OdTvSmartPtr<OdTvMaterial> OdTvMaterialPtr;

/** \details
  The interface class for a material object identifier that allows access to the <link OdTvMaterial, OdTvMaterial> object.
*/
class ODTV_EXPORT OdTvMaterialId : public OdTvId
{
public:
  /** \details
    Opens the material determined with its identifier for a read or write operation. 
    
    \param mode [in] An open mode value.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the material object.
    \remarks
    If the rc parameter is not null and the material object was successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvMaterialPtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

};

/** \details
  The base interface class for the iterator of Visualize SDK material objects.
  An iterator object provides sequential access to a collection of materials.
*/
class ODTV_EXPORT OdTvMaterialsIterator : public OdTvIterator, public OdTvIObject
{
public:

  /** \details
    Retrieves the material object that is currently referenced by the iterator object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the material object identifier if the iterator refers to a material object; otherwise it returns an identifier with a null value.
    \remarks 
    If the rc parameter is not null and the material object identifier is successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    If the iterator refers to a material object, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvMaterialId getMaterial(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches for the material defined through its identifier and moves the iterator to this material if found.
    
    \param materialId [in] A material identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the material object specified through its identifier is found, the method returns the tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek(const OdTvMaterialId& materialId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvMaterialsIterator, materials iterator> object.
*/
typedef OdTvSmartPtr<OdTvMaterialsIterator> OdTvMaterialsIteratorPtr;

/** \details
  Describes interface for materials comparison.
*/
class ODTV_EXPORT OdTvMaterialComparator
{
public:
  /** \details
    Compares materials.
    
    \param pMaterial [in] Pointer to the material to compare.
    \returns 
    Returns true if materials are equal; otherwise returns false.
  */
  virtual bool isEqual( OdTvMaterialPtr pMaterial ) const = 0;
};


#endif // _ODTV_MATERIAL_H_INCLUDED_
