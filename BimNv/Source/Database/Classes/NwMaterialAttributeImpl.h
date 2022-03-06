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

#ifndef __NW_MATERIAL_ATTRIBUTE_IMPL_H__
#define __NW_MATERIAL_ATTRIBUTE_IMPL_H__

#include "NwMaterialAttribute.h"
#include "NwAttributeImpl.h"
#include "NwColor.h"

class OdNwMaterialAttributeImpl : public OdNwAttributeImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwMaterialAttribute)
public:
  OdNwMaterialAttributeImpl();
  virtual ~OdNwMaterialAttributeImpl();
  ODRX_DECLARE_MEMBERS(OdNwMaterialAttributeImpl);

public:
  static OdNwMaterialAttributeImpl* getImpl(const OdNwMaterialAttribute* pNwMat);
  static OdNwMaterialAttributeImpl* getImpl(const OdRxObject* pRxMat);

public:
  const OdNwColor& getAmbient() const;
  const OdNwColor& getDiffuse() const;
  const OdNwColor& getSpecular() const;
  const OdNwColor& getEmissive() const;
  double getShininess() const;
  double getTransperency() const;

public:
  void setAmbient(const OdNwColor& value);
  void setDiffuse(const OdNwColor& value);
  void setSpecular(const OdNwColor& value);
  void setEmissive(const OdNwColor& value);
  void setShininess(const double& value);
  void setTransperency(const double& value);

protected:
  OdNwColor m_ambientColor;
  OdNwColor m_diffuseColor;
  OdNwColor m_specularColor;
  OdNwColor m_emissiveColor;
  double m_shininess;
  double m_transperency;
};



#endif //__NW_MATERIAL_ATTRIBUTE_IMPL_H__
