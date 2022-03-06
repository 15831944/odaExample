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

#ifndef __NWCOMMONLIGHTIMPL_INCLUDED__
#define __NWCOMMONLIGHTIMPL_INCLUDED__

#include "NwCategoryImpl.h"
#include "NwCommonLight.h"
#include "SharedPtr.h"

class OdNwGraphicJsonBundle;
typedef OdSmartPtr<OdNwGraphicJsonBundle> OdNwGraphicJsonBundlePtr;

class OdNwCommonLightImpl : public OdNwCategoryImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwCommonLight)
public:
  OdNwCommonLightImpl();
  OdNwCommonLightImpl(const OdString& name, const OdString& displayName);
  virtual ~OdNwCommonLightImpl();
  ODRX_DECLARE_MEMBERS(OdNwCommonLightImpl);
  
public:
  static OdNwCommonLightImpl* getImpl(const OdNwCommonLight* pNwCategory);
  static OdNwCommonLightImpl* getImpl(const OdRxObject* pRxCategory);

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const override;

public:
  virtual void ParseProperties();

public:
  OdNwColor getAmbient() const;
  OdNwColor getDiffuse() const;
  OdNwColor getSpecular() const;
  bool isLightOn() const;
  OdResult getFilterColor(OdNwColor& color) const;
  OdResult getTintColor(OdNwColor& color) const;
  OdResult getRGBLightColor(OdNwColor& color) const;
  OdResult getShadowColor(OdNwColor& color) const;
  float getIntensity() const;
  bool isAmbientOnly() const;
  bool isUseTintColor() const;
  bool isShadowOn() const;

  virtual OdNwVariant getValue(NwLightValueType::Enum val_type) const;

public:
  bool isEye() const;
  bool isCastShadow() const;
  OdNwGraphicJsonBundlePtr getJson() const;

public:
  void setAmbient(const OdNwColor& Ambient);
  void setDiffuse(const OdNwColor& Diffuse);
  void setSpecular(const OdNwColor& Specular);
  void setLightOn(bool status);
  void setFilterColor(const OdNwColor& color);
  void setTintColor(const OdNwColor& color);
  void setRGBLightColor(const OdNwColor& color);
  void setShadowColor(const OdNwColor& color);
  void setIntensity(float val);
  void setAmbientOnly(bool status);
  void setUseTintColor(bool status);
  void setShadowOn(bool status);

public:
  void setIsEye(bool val);
  void setIsCastShadow(bool val);
  void setJson(OdNwGraphicJsonBundlePtr pJson);

protected:
  bool m_bIsOn;
  bool m_bIsEye;
  bool m_bIsCastShadow;
  OdNwGraphicJsonBundlePtr m_pJson;
  OdNwColor m_Ambient;
  OdNwColor m_Specular;
  // It's a main color.
  OdNwColor m_Diffuse;
  //params from protein:
  OdSharedPtr<OdNwColor> m_pFilterColor;
  OdSharedPtr<OdNwColor> m_pTintColor;
  OdSharedPtr<OdNwColor> m_pRgbLightColor;
  OdSharedPtr<OdNwColor> m_pShadowColor;
  float m_IntensityValue;
  bool m_bIsAmbientOnly;
  bool m_bUseTintColor;
  bool m_bShadowOn;
};

typedef OdSmartPtr<OdNwCommonLightImpl> OdNwCommonLightImplPtr;

#endif //__NWCOMMONLIGHTIMPL_INCLUDED__
