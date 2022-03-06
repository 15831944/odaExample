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

#ifndef __NWMATERIALIMPL_INCLUDED__
#define __NWMATERIALIMPL_INCLUDED__

#include "NwMaterial.h"
#include "NwCategoryImpl.h"
#include "NwModeType.h"

class OdNwMaterialImpl : public OdNwCategoryImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwMaterial)
public:
  OdNwMaterialImpl();
  virtual ~OdNwMaterialImpl();
  ODRX_DECLARE_MEMBERS(OdNwMaterialImpl);

  virtual OdResult fillTraits(OdGiDrawableTraits* pTraits, NwModeType::Enum renderMode) const;
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const override;

public:
  static OdNwMaterialImpl* getImpl(const OdNwMaterial* pNwMaterial);
  static OdNwMaterialImpl* getImpl(const OdRxObject* pRxMaterial);

public:
  //public implementation's methods
  OdNwColor getAmbient() const;
  OdNwColor getDiffuse() const;
  OdNwColor getSpecular() const;
  OdNwColor getEmissive() const;
  float getShininess() const;
  float getTransparency() const;

public:
  inline OdNwColor& getAmbient()  { return m_clrAmbient; }
  inline OdNwColor& getDiffuse()  { return m_clrDiffuse; };
  inline OdNwColor& getSpecular() { return m_clrSpecular; }
  inline OdNwColor& getEmissive() { return m_clrEmissive; }

public:
  void setAmbient(const OdNwColor& pAmbient);
  void setDiffuse(const OdNwColor& pDiffuse);
  void setSpecular(const OdNwColor& pSpecular);
  void setEmissive(const OdNwColor& pEmissive);
  void setShininess(float shininess);
  void setTransparency(float transparency);

protected:
  OdNwColor m_clrAmbient;
  // It's a main color.
  OdNwColor m_clrDiffuse;
  OdNwColor m_clrSpecular;
  OdNwColor m_clrEmissive;
  float m_fShininess;
  float m_fTransparency;
};

#endif //__NWMATERIALIMPL_INCLUDED__
