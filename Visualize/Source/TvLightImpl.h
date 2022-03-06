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

#ifndef _ODTV_LIGHTIMPL_H_INCLUDED_
#define _ODTV_LIGHTIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "OdDbStub.h"
#include "DbLight.h"

#include "TvLight.h"
#include "TvInterfaceWrappers.h"
#include "TvUserDataImpl.h"

#include "DbObjectIterator.h"
#include "TvEntity.h"

/** \details
This class is the internal implementation of the light
*/
class OdTvLightImpl : public OdTvDbLight, public OdTvXDataStorage
{
protected:
  OdTvLightImpl();
public:
  ODRX_DECLARE_MEMBERS(OdTvLightImpl);

  virtual ~OdTvLightImpl();

  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;

  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;

  /** \details
  Copy all light data to specified light
  */
  OdTvResult copyTo(OdTvEntityId& targetLightId, bool bFromInterface = true) const;
};

typedef OdSmartPtr<OdTvLightImpl> OdTvLightImplPtr;

/** \details
This is an wrapper of the interface class for OdTvLight object.

\remarks
The purpose of this class is to connect the internal light object with an interface object
*/
class OdTvLightWrapper : public OdTvLight
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvLight, OdTvLightImpl)

  friend class OdTvDatabaseImpl;
  friend class OdTvModelRootEntityImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Interface implementation
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
    Sets the name for the light.

    \param sName [in]  Layer name as a String value up to 255 characters long.

    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvResult setName(OdString sName);

  /** \details
    Returns the name of the light.
  */
  virtual OdString getName(OdTvResult* rc = NULL) const;

  /** \details
    Sets the light type of the light. Light type determines the way the lighting is illuminated.

    \param type    [in] Light type to be set.

  */
  virtual OdTvResult setLightType(LightType type);

  /** \details
    Returns the light type of the light.
  */
  virtual LightType getLightType(OdTvResult* rc = NULL) const;

  /** \details
    Sets the light is on.

    \param bValue    [in] True if light is on.

  */
  virtual OdTvResult setOn(bool bValue);

  /** \details
    Returns true if light is on.
  */
  virtual bool isOn(OdTvResult* rc = NULL) const;

  /** \details
    Sets the color of the light.

    \param color    [in] Reference to the color instance to be set.

  */
  virtual OdTvResult setLightColor(const OdTvColorDef& color);

  /** \details
    Returns the color of the light.
  */
  virtual OdTvColorDef getLightColor(OdTvResult* rc = NULL) const;

  /** \details
    Sets the intensity for the light.

    \param intensity    [in] Intensity to be set.

  */
  virtual OdTvResult setIntensity(double dIntensity);

  /** \details
    Returns intensity of the light.
  */
  virtual double getIntensity(OdTvResult* rc = NULL) const;

  /** \details
    Sets the light attenuation for the light.

    \param params    [in] Light attenuation to be set.

  */
  virtual OdTvResult setLightAttenuation(const OdTvLightAttenuation& params);

  /** \details
    Returns light attenuation of the light.
  */
  virtual OdTvLightAttenuation getLightAttenuation(OdTvResult* rc = NULL) const;

  /** \details
    Sets position for the light.

    \param pos    [in] Position to be set.

  */
  virtual OdTvResult setPosition(const OdTvPoint& pos);

  /** \details
    Returns position of the light.
  */
  virtual OdTvPoint getPosition(OdTvResult* rc = NULL) const;

  /** \details
    Sets target for the spot light.

    \param newVal    [in] Target to be set.

  */
  virtual OdTvResult setTargetLocation(const OdTvPoint& newVal);

  /** \details
    Returns position of the target.
  */
  virtual OdTvPoint getTargetLocation(OdTvResult* rc = NULL) const;

  /** \details
    Sets hotspot and falloff angles for the light.

    \param dHotspot    [in] Hotspot angle to be set.
    \param dFalloff    [in] Falloff angle to be set.

  */
  virtual OdTvResult setHotspotAndFalloff(double dHotspot, double dFalloff);

  /** \details
    Returns hotspot angle.
  */
  virtual double getHotspotAngle(OdTvResult* rc = NULL) const;

  /** \details
    Returns falloff angle.
  */
  virtual double getFalloffAngle(OdTvResult* rc = NULL) const;

  /** \details
    Sets light direction for the distant light.

    \param lightvec    [in] Light direction to be set.

  */
  virtual OdTvResult setLightDirection(const OdTvVector& lightvec);

  /** \details
    Returns light direction.
  */
  virtual OdTvVector getLightDirection(OdTvResult* rc = NULL) const;

  /** \details
    Sets if need to draw glyph or not.

    \param glyphType    [in] Glyph display type.
  */
  virtual OdTvResult setGlyphDisplay(GlyphDisplayType glyphType);

  /** \details
    Returns glyph display type.
  */
  virtual GlyphDisplayType getGlyphDisplay(OdTvResult* rc = NULL) const;

  virtual OdTvResult setShadowParameters( const OdTvShadowParameters& params );
  virtual OdTvShadowParameters getShadowParameters( OdTvResult* rc = NULL  ) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);
};

//***************************************************************************//
// A few helper functions
//***************************************************************************//

/** \details
  Get OdGiDrawable::DrawableType from OdTvLightWrapper::LightType
*/
OdGiDrawable::DrawableType getOdGiDrawableTypeFromOdTvLightType(OdTvLightWrapper::LightType tvType);

/** \details
Get OdTvLightWrapper::LightType from OdGiDrawable::DrawableType
*/
OdTvLight::LightType getOdTvLightTypeFromOdDrawableType(OdGiDrawable::DrawableType dType);


#endif //_ODTV_LIGHTIMPL_H_INCLUDED_
