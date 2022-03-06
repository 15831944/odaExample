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

#ifndef __TNW_GRAPHIC_MATERIAL_H__
#define __TNW_GRAPHIC_MATERIAL_H__

#include "NwObject.h"
#include "NwExport.h"
#include "NwColor.h"

class NWDBEXPORT OdNwGraphicMaterial : public OdNwObject
{
  ODRX_DECLARE_MEMBERS(OdNwGraphicMaterial);

public:
  OdNwGraphicMaterial();

public:
  virtual ~OdNwGraphicMaterial();

public:
  inline const OdNwColor& getAmbient() const { return m_ambientColor; }
  inline const OdNwColor& getDiffuse() const { return m_diffuseColor; }
  inline const OdNwColor& getSpecular() const { return m_specularColor; }
  inline const OdNwColor& getEmissive() const { return m_emissiveColor; }
  inline float getShininess() const { return m_shininess; }
  inline float getTransparency() const { return m_transparency; }

public:
  inline void setAmbient(const OdNwColor& value) { m_ambientColor = value; }
  inline void setDiffuse(const OdNwColor& value) { m_diffuseColor = value; }
  inline void setSpecular(const OdNwColor& value) { m_specularColor = value; }
  inline void setEmissive(const OdNwColor& value) { m_emissiveColor = value; }
  inline void setShininess(float value) { m_shininess = value; }
  inline void setTransparency(float value) { m_transparency = value; }

private:
  OdNwColor m_ambientColor;
  OdNwColor m_diffuseColor;
  OdNwColor m_specularColor;
  OdNwColor m_emissiveColor;
  float m_shininess;
  float m_transparency;
};

typedef OdSmartPtr<OdNwGraphicMaterial> OdNwGraphicMaterialPtr;

#endif //__TNW_GRAPHIC_MATERIAL_H__
