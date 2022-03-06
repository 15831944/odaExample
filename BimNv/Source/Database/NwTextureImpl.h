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

#ifndef __NWTEXTUREIMPL_INCLUDED__
#define __NWTEXTUREIMPL_INCLUDED__

#include "NwTexture.h"
#include "NwMaterialImpl.h"
#include "NwTextureMapper.h"

class OdGiMaterialMap;
class OdNwGraphicJsonBundle;

class NWDBEXPORT OdNwTextureImpl : public OdNwMaterialImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwTexture)
public:
  OdNwTextureImpl();
  virtual ~OdNwTextureImpl();
  ODRX_DECLARE_MEMBERS(OdNwTextureImpl);

  OdResult fillTraits(OdGiDrawableTraits* pTraits, NwModeType::Enum renderMode) const override;

public:
  static OdNwTextureImpl* getImpl(const OdNwTexture* pNwTexture);
  static OdNwTextureImpl* getImpl(const OdRxObject* pRxTexture);

public:
  void ParseProperties(const OdString& texturesSourceDirectory, OdNwGraphicJsonBundle* pJsonBundle);

public:
  void setTransparency(float value);
  void setRefraction(float value);
  void UpdateMaterialSpecificProperties(OdString tag, OdString type, OdString finish, OdString colorIndex, OdSharedPtr<OdNwColor> customColor);

public:
  OdString getStringValue(NwTextureValueType::Enum type, OdResult* pResult) const;
  double getDoubleValue(NwTextureValueType::Enum type, OdResult* pResult) const;
  NwModelUnits::Enum getUnitValue(NwTextureValueType::Enum type, OdResult* pResult) const;
  OdGiRasterImagePtr getRasterImageValue(NwTextureValueType::Enum type, OdResult* pResult) const;
  OdGeMatrix3d getMatrixValue(NwTextureValueType::Enum type, NwModelUnits::Enum desiredUnits, OdResult* pResult) const;

public:
  inline double getDiffuseIntensity()  const { return m_DiffuseIntensity; }
  inline double getSpecularIntensity() const { return m_SpecularIntensity; }
  inline double getReflectIntensity()  const { return m_ReflectIntensity; }
  inline double getBumpAmount()  const { return m_BumpAmount; }
  OdResult getTint(OdNwColor& tint) const;
  inline bool IsUseTintColor() const { return m_bUseTintColor; }
  OdResult getTransmitColor(OdNwColor& transmit) const;
  bool IsColorByObject() const;

public:
  OdNwTextureMapper& getBumpMapper();
  OdNwTextureMapper& getPatternMapper();
  OdNwTextureMapper& getDiffuseMapper();
  OdNwTextureMapper& getOpacityMapper();

public:
  inline void setDiffuseIntensity(double dif_intensity) { m_DiffuseIntensity = dif_intensity; }
  inline void setSpecularIntensity(double spec_intensity) { m_SpecularIntensity = spec_intensity; }
  inline void setReflectIntensity(double ref_intensity) { m_ReflectIntensity = ref_intensity; }
  inline void setBumpAmount(double bumpAmount) { m_BumpAmount = bumpAmount; }
  inline void setUseTint(bool flag) { m_bUseTintColor = flag; }
  void setTint(std::unique_ptr<OdNwColor> tint);
  void setTransmitColor(std::unique_ptr<OdNwColor> transmit);
  void setColorByObject(bool flag);

private:
  OdNwTextureMapper m_PatternMap;
  OdNwTextureMapper m_BumpMap;
  OdNwTextureMapper m_OpacityMap;
  OdNwTextureMapper m_DiffuseMap;
  double m_DiffuseIntensity;
  double m_SpecularIntensity;
  double m_ReflectIntensity;
  double m_RefractionIndex;
  double m_BumpAmount;
  std::unique_ptr<OdNwColor> m_pTint;
  bool m_bUseTintColor;
  std::unique_ptr<OdNwColor> m_pTransmitColor;
  bool m_bColorByObject;

  bool m_bTransparencyFromAutodeskMaterial;
};



#endif //__NWTEXTUREIMPL_INCLUDED__
