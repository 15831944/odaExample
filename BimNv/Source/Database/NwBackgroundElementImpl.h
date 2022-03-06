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

#ifndef __NWBACKGROUNDELEMENTIMPL_INCLUDED__
#define __NWBACKGROUNDELEMENTIMPL_INCLUDED__

#include "NwBackgroundElement.h"
#include "NwColor.h"
#include "OdArray.h"
#include "NwObjectImpl.h"
#include "NwCategory.h"
#include "NwBackgroundType.h"

class OdNwBackgroundElementImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwBackgroundElement)
public:
  OdNwBackgroundElementImpl();
  virtual ~OdNwBackgroundElementImpl();
  ODRX_DECLARE_MEMBERS(OdNwBackgroundElementImpl);

  DrawableType drawableType() const override;
  OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const override;

public:
  static OdNwBackgroundElementImpl* getImpl(const OdNwBackgroundElement* pNwBck);
  static OdNwBackgroundElementImpl* getImpl(const OdRxObject* pRxBck);
  void subSetDatabaseDefaults(OdNwDatabase* pDb, bool doSubents) override;

//public implementation's methods
public:
  NwBackgroundType::Enum getBackgroundType() const;

  OdResult getPlainColor(OdNwColor& color) const;
  OdResult getGraduatedColor(OdNwColor& top, OdNwColor& bottom) const;
  OdResult getHorizonColor(OdNwColor& skyColor, OdNwColor& horizonSkyColor, OdNwColor& horizonGroundColor, OdNwColor& groundColor) const;

public:
  OdInt32 getVersion() const;
  OdInt32 getColorCount() const;
  OdNwColor getColor(OdInt32 nIndex) const;
  OdRxObjectPtr getPaperStyle() const;
  OdNwCategoryPtr getMaterial() const;
  OdNwGraphicJsonBundlePtr getGraphicJson() const;

public:
  void setColor(OdInt32 nIndex, const OdNwColor& color);
  void addColor(const OdNwColor& color);
  void setPaperStyle(OdRxObjectPtr paperStyle);
  void setMaterial(OdNwCategoryPtr material);
  void setGraphicJson(OdNwGraphicJsonBundlePtr jsonObj);

  void setBackgroundType(NwBackgroundType::Enum type);

  OdResult setPlainBackground(const OdNwColor& plainColor);
  OdResult setGraduatedBackground(const OdNwColor& topColor, const OdNwColor& bottomColor);

protected:
  OdInt32                m_nVersion;
  OdArray<OdNwColor>     m_aColor;
  OdRxObjectPtr          m_pPaperStyle;
  OdString               m_sJson;
  OdNwCategoryPtr        m_pMaterial;
  OdNwGraphicJsonBundlePtr     m_pGraphicJson;
  NwBackgroundType::Enum m_BackgroundType;
};



#endif //__NWBACKGROUNDELEMENTIMPL_INCLUDED__
