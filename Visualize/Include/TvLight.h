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

#ifndef _ODTV_LIGHT_H_INCLUDED_
#define _ODTV_LIGHT_H_INCLUDED_

#include "OdaCommon.h"

#include "Tv.h"
#include "TvIObject.h"
#include "TvTraitsDef.h"
#include "TvUserData.h"

/** \details
  The base interface class for managing the light attenuation for Visualize SDK entities.
  \sa
  <link tv_working_with_lights, Work with Lights>
*/
class ODTV_EXPORT OdTvLightAttenuation
{
public:

  /** \details 
    Creates a new instance of the light attenuation class. 
  */
  OdTvLightAttenuation();
  
  /** \details 
    Creates a new instance of the light attenuation class based on an existing object (copy constructor). 
    
    \param params [in] An original object to be copied. 
  */
  OdTvLightAttenuation(const OdTvLightAttenuation& params);

  /** \details 
    Types of light attenuation. 
  */
  enum AttenuationType
  {
    kNone = 0,      // No light attenuation.
    kInverseLinear, // Inverse linear light attenuation.
    kInverseSquare  // Inverse square light attenuation.
  };

  /** \details
    Sets a new attenuation type for the light attenuation object.
    
    \param type [in] A new attenuation to be set.
  */
  void setAttenuationType(AttenuationType type);

  /** \details
    Retrieves the current type of light attenuation.
    
    \returns Returns a value of the <link OdTvLightAttenuation::AttenuationType, AttenuationType> type.
  */
  AttenuationType getAttenuationType() const;

  /** \details
    Switches the light attenuation on or off.
    
    \param on [in] A flag value that determines whether the light attenuation if on (true) or off (false).
  */
  void setUseLimits(bool on);

  /** \details
    Retrieves whether the light attenuation is switched on or off.
    
    \returns Returns true if light attenuation is on; otherwise returns false.
  */
  bool getUseLimits() const;

  /** \details
    Sets new limits for the light attenuation.
    
    \param startlim [in] A start limit value to be set.
    \param endlim   [in] An end limit value to be set.
  */
  void setLimits(double startlim, double endlim);

  /** \details
    Retrieves the current start limit of the light attenuation.
    
    \returns Returns the start limit value.
  */
  double getStartLimit() const;

  /** \details
    Retrieves the current end limit of the light attenuation.
    
    \returns Returns the end limit value.
  */
  double getEndLimit() const;

//DOM-IGNORE-BEGIN
private:
  AttenuationType m_attenType;
  bool            m_bUseAttenLimits;
  double          m_dAttenStartLimit;
  double          m_dAttenEndLimit;
//DOM-IGNORE-END
};


/** \details
  The base interface class for managing the light shadows for Visualize SDK entities.
  \sa
  <link tv_working_with_lights, Work with Lights>
*/
class ODTV_EXPORT OdTvShadowParameters
{
public:
  /** \details
    Creates a new instance of the light shadow parameters class.
  */
  OdTvShadowParameters();
  /** \details
    Creates a new instance of the light shadow parameters class based on an existing object (copy constructor).
    
    \param params [in] An original object to be copied.
  */
  OdTvShadowParameters( const OdTvShadowParameters& params );
  
  /** \details
    Switches the light shadow parameters on or off.
    
    \param bSet [in] A flag value that determines whether the light shadow parameters is on (true) or off (false).
    \remarks
    If enabled, parameters always use Shadow Map.
  */
  void setShadowsOn( bool bSet );
  
  /** \details
    Retrieves whether the light shadow parameters is on or off.
    
    \returns Returns true if the light shadow parameters is switched on; otherwise the method returns false.
  */
  bool getShadowsOn() const;
  
  /** \details
    Specifies the size of the shadow map texture. Size have to be power of 2 in interval [64, 4096].
    
    \param sz [in] Size of shadow map texture
    \returns Returns tvOK if size is appropriate; otherwise returns tvWarning
    \remarks
    Larger texture sizes increase shadow details but require additional resources and make final shadows crisper. Smaller texture sizes decrease shadow details but make final shadows smoother.
  */
  OdTvResult setShadowMapSize( OdUInt16 sz );
  
  /** \details
    Retrieves the size of the shadow map texture.
    
    \returns Size of shadow map texture.
  */
  OdUInt16 getShadowMapSize() const;
  
  /** \details
    Specifies the shadow smoothness.
    
    \param soft [in] The shadow smoothness.
    \details
    Currently four smoothing stages are supported: 
    0 - Disable smoothing
    1 - Invoke smoothing using 3x3 Gaussian blur kernel
    2 - Invoke smoothing using 5x5 Gaussian blur kernel
    3 and more - Invoke smoothing using 7x7 Gaussian blur kernel
    Since blur is executed on the GPU side, there is no serious performance difference between Gaussian kernel sizes; primarily this parameter affects the amount of blur effect (size of the blurred area).
  */
  void setShadowMapSoftness( OdUInt8 soft );
  
  /** \details
    Retrieves the shadow smoothness.
    
    \returns The shadow smoothness.
  */
  OdUInt8 getShadowMapSoftness() const;

//DOM-IGNORE-BEGIN
protected:
  bool        m_bShadowOn;
  OdUInt16    m_shadowMapSize;
  OdUInt8     m_shadowMapSoft;
//DOM-IGNORE-END
};


/** \details
  The abstract interface class for a Visualize SDK light object.
  \sa
  <link tv_working_with_lights, Work with Lights>
*/
class ODTV_EXPORT OdTvLight : public OdTvHandledIObject
{
public:

  /** \details
    Light types.
  */
  enum LightType
  {
    kDistantLight = 1,  // A distant light.
    kPointLight = 2,    // A point light.
    kSpotLight = 3      // A spot light.
  };

  /** \details
    Types of glyph display.
  */
  enum GlyphDisplayType
  {
    kGlyphDisplayAuto = 0,  // Auto display of glyph.
    kGlyphDisplayOn,        // Display of glyph is on.
    kGlyphDisplayOff        // Display of glyph is off.
  };

  //**************************************************************************************
  // Group of the methods for setting the attributes
  //**************************************************************************************

  /** \details
    Sets a new name for the light object.
    
    \param sName [in] A string with length from 0 to 255 characters that represents the light object name.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    If the new name of the light object was successfully set, the method returns tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName(OdString sName) = 0;

  /** \details
    Retrieves the current name of the light object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string object that contains the current name of the light object.
    If the rc parameter is not null and the light object name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getName(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new type for the light object. 
    
    The light type determines how the lighting is illuminated.
    \param type [in] A light type value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new type of the light object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setLightType(LightType type) = 0;

  /** \details
    Retrieves the current type of the light object. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current light type.
    \remarks 
    If the rc parameter is not null and the current light type value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual LightType getLightType(OdTvResult* rc = NULL) const = 0;

  /** \details
    Switches the light on or off.
    
    \param bValue [in] A flag value that determines whether the light is on (true) or off (false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the light was successfully switched on or off, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setOn(bool bValue) = 0;

  /** \details
    Retrieves whether the light is on or off.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the light is switched on; otherwise the method returns false.
    \remarks 
    If the rc parameter is not null and the flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool isOn(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new color of the light object.
    
    \param color [in] A reference to a color definition object to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the light color was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setLightColor(const OdTvColorDef& color) = 0;

  /** \details
    Retrieves the current color of the light object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the <link OdTvColorDef, color definition object> that represents the current color of the light object.
    \remarks 
    If the rc parameter is not null and the light object color was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvColorDef getLightColor(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new light intensity value for the light object.
    
    \param dIntensity [in] Intensity to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new intensity value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setIntensity(double dIntensity) = 0;

  /** \details
    Retrieves the current light intensity of the light object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current light intensity.
    \remarks 
    If the rc parameter is not null and the light intensity value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual double getIntensity(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets new light attenuation parameters for the light object.
    
    \param params [in] A reference to a <link OdTvLightAttenuation, light attenuation object> that contains attenuation parameters.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If new light attenuation parameters were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setLightAttenuation(const OdTvLightAttenuation& params) = 0;

  /** \details
    Retrieves the current light attenuation parameters of the light object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a <link OdTvLightAttenuation, OdTvLightAttenuation> object that contains attenuation parameters.
    \remarks 
    If the rc parameter is not null and the light attenuation parameters were successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvLightAttenuation getLightAttenuation(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new position for the light object.
    
    \param pos [in] A light position to be set represented with an <link OdTvPoint, OdTvPoint> object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If a new light position was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPosition(const OdTvPoint& pos) = 0;

  /** \details
    Retrieves the current light position.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an <link OdTvPoint, OdTvPoint> object that represents the current light position.
    \remarks 
    If the rc parameter is not null and the current light position was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvPoint getPosition(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new target for the light object.
    
    \param newVal [in] A light target to be set represented with an <link OdTvPoint, OdTvPoint> object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If a new light target was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setTargetLocation(const OdTvPoint& newVal) = 0;

  /** \details
    Retrieves the current light target.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an <link OdTvPoint, OdTvPoint> object that represents the current light target.
    \remarks 
    If the rc parameter is not null and the current light target was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvPoint getTargetLocation(OdTvResult* rc = NULL) const = 0;
  
  /** \details
    Sets new hot-spot and fall-off angles for the light object. 
    
    \param dHotspot [in] A new value of the hot-spot angle to be set.
    \param dFalloff [in] A new value of the fall-off angle to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If new hot-spot and fall-off angles were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setHotspotAndFalloff(double dHotspot, double dFalloff) = 0;

  /** \details
    Retrieves the current hot-spot angle for the light object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current hot-spot angle value.
    \remarks 
    If the rc parameter is not null and the hot-spot angle value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual double getHotspotAngle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current fall-off angle for the light object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current fall-off angle value.
    \remarks 
    If the rc parameter is not null and the fall-off angle value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual double getFalloffAngle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new light direction for the light object.
    
    \param lightvec [in] A reference to an <link OdTvVector, OdTvVector> object that represents the light direction to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new direction of the light object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setLightDirection(const OdTvVector& lightvec) = 0;

  /** \details
    Retrieves the current light direction of the light object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an <link OdTvVector, OdTvVector> object that represents the light direction.
    \remarks 
    If the rc parameter is not null and the GS device identifier was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvVector getLightDirection(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new glyph display type to the light object.
    
    \param glyphType    [in] A new glyph display type.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new glyph display type was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setGlyphDisplay(GlyphDisplayType glyphType) = 0;

  /** \details
    Retrieves the current glyph display type of the light object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current glyph display type.
    \remarks 
    If the rc parameter is not null and the current glyph display type was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual GlyphDisplayType getGlyphDisplay(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a light shadow parameters.
    
    \param params [in] Shadow parameters
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the light shadow parameters was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setShadowParameters( const OdTvShadowParameters& params ) = 0;
  
  /** \details
    Retrieves the current light shadow parameters.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current light shadow parameters.
    \remarks
    If the rc parameter is not null and the current light shadow parameters was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvShadowParameters getShadowParameters( OdTvResult* rc = NULL  ) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvLight, OdTvLight> object.
*/
typedef OdTvSmartPtr<OdTvLight> OdTvLightPtr;

#endif //_ODTV_LIGHT_H_INCLUDED_
