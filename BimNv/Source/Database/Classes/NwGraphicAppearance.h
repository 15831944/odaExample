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

#ifndef __TNW_GRAPHIC_APPEARANCE_H__
#define __TNW_GRAPHIC_APPEARANCE_H__

#include "NwObject.h"
#include "NwExport.h"
#include "NwModeType.h"
#include "NwModelUnits.h"

class OdNwGraphicMaterial;
typedef OdSmartPtr<OdNwGraphicMaterial> OdNwGraphicMaterialPtr;
class OdNwGraphicJsonBundle;
typedef OdSmartPtr<OdNwGraphicJsonBundle> OdNwGraphicJsonBundlePtr;
class OdGiRasterImage;
typedef OdSmartPtr<OdGiRasterImage> OdGiRasterImagePtr;
class OdGeMatrix3d;

class NWDBEXPORT OdNwGraphicAppearance : public OdNwObject
{
  ODRX_DECLARE_MEMBERS(OdNwGraphicAppearance);

public:
  OdNwGraphicAppearance();

public:
  virtual ~OdNwGraphicAppearance();

public:
  inline OdUInt32& getParts() { return m_parts; }
  inline bool isProteinTransperent() const { return m_bIsProteinTransperent; }
  inline bool isEnableLighting() const { return m_bIsEnableLighting; }
  inline OdUInt32 getPoligonMode() const { return m_poligonMode; }
  inline OdUInt32 getShadeMode() const { return m_shadeMode; }
  //VAS: method which return OdNwObjectId with OdNwMaterial object
  OdNwObjectId getComponentMaterial(const OdNwObjectId& ownerId, NwModeType::Enum viewType) const;
  void clearComponentMaterial(NwModeType::Enum viewType);
  OdNwGraphicMaterialPtr getMaterial() const;
  OdNwGraphicJsonBundlePtr getJsonBundle() const;

public:
  inline void setIsProteinTransperent(bool val) { m_bIsProteinTransperent = val; }
  inline void setIsEnableLighting(bool val) { m_bIsEnableLighting = val; }
  inline void setPoligonMode(OdUInt32 val) { m_poligonMode = val; }
  inline void setShadeMode(OdUInt32 val) { m_shadeMode = val; }
  void setMaterial(OdNwGraphicMaterialPtr pMaterial);
  void setJsonBundle(OdNwGraphicJsonBundlePtr pJsonBundle);

public:
  OdResult setInternalTextureData(const OdString& txtPath, OdGiRasterImagePtr pTxtData, const OdGeMatrix3d* pMaterialMapping, NwModelUnits::Enum modelUnits);
  OdResult setExternalTextureData(const OdString& txtPath, const OdGeMatrix3d* pMaterialMapping, NwModelUnits::Enum modelUnits);

protected:
  OdUInt32 m_parts;
  bool m_bIsProteinTransperent;
  bool m_bIsEnableLighting;
  OdUInt32 m_poligonMode;
  OdUInt32 m_shadeMode;
  OdNwGraphicMaterialPtr m_pMaterial;
  mutable OdNwGraphicJsonBundlePtr m_pGraphicJsonBundle;
  mutable OdNwObjectId m_componentRealisticMaterialId;//material object for api
  mutable OdNwObjectId m_componentShadedMaterialId;//material object for api
};

typedef OdSmartPtr<OdNwGraphicAppearance> OdNwGraphicAppearancePtr;

#endif //__TNW_GRAPHIC_APPEARANCE_H__
