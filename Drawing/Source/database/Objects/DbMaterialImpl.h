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


#ifndef _DB_MATERIAL_IMPL_
#define _DB_MATERIAL_IMPL_

#include "DbObjectImpl.h"
#include "DbSystemInternals.h"
#include "Gi/GiMaterial.h"
#include "DbMaterial.h"

class OdDbMaterialImpl : public OdDbObjectImpl
{
  static OdDbMaterialImpl* getImpl(const OdDbMaterial* pObj)
  { return (OdDbMaterialImpl*)OdDbSystemInternals::getImpl(pObj); }

	static void dxfInMaterialColor(OdDbDxfFiler *pFiler, OdGiMaterialColor& clr, int offset);

  friend class OdDbMaterial;

public:
  OdDbMaterialImpl();
  
  OdString                 m_Name;
  OdString name(const OdDbObject* pObj) const;
  OdString                 m_Description;

  OdGiMaterialColor        m_AmbientColor;
  OdGiMaterialColor        m_DiffuseColor;
  OdGiMaterialMap          m_DiffuseMap;
  OdGiMaterialColor        m_SpecularColor;
  OdGiMaterialMap          m_SpecularMap;
  double                   m_SpecularGloss;
  OdGiMaterialMap          m_ReflectionMap;
  OdGiMaterialMap          m_OpacityMap;
  double                   m_OpacityPercent;
  OdGiMaterialMap          m_BumpMap;
  OdGiMaterialMap          m_RefractionMap;

  double                   m_RefractionIndex;

  double                   m_Translucence;
  double                   m_SelfIllumination;

  double                   m_Reflectivity;
  OdGiMaterialTraits::Mode m_Mode;
  OdGiMaterialTraits::ChannelFlags m_ChannelFlags;
  OdGiMaterialTraits::IlluminationModel m_IlluminationModel;

  // Extended material properties
  double                   m_ColorBleedScale;
  double                   m_IndirectBumpScale;
  double                   m_ReflectanceScale;
  double                   m_TransmitScale;
  bool                     m_TwoSided;
  OdGiMaterialTraits::LuminanceMode m_LuminanceMode;
  double                   m_Luminance;
  OdGiMaterialMap          m_NormalMap;
  OdGiMaterialTraits::NormalMapMethod m_NormalMapMethod;
  double                   m_NormalMapStrength;
  bool                     m_Anonymous;
  OdGiMaterialTraits::GlobalIlluminationMode m_GlobalIllumination;
  OdGiMaterialTraits::FinalGatherMode m_FinalGather;
  bool                     m_AdvDataChanged; // Enables saving of extended properties into XRec

  // Synchronized maps
  OdGiMaterialMap          m_DiffuseMapSync;
  OdGiMaterialMap          m_SpecularMapSync;
  OdGiMaterialMap          m_ReflectionMapSync;
  OdGiMaterialMap          m_OpacityMapSync;
  OdGiMaterialMap          m_BumpMapSync;
  OdGiMaterialMap          m_RefractionMapSync;

  enum MapChannel
  {
    MapChan_Diffuse = 0,
    MapChan_Specular,
    MapChan_Reflection,
    MapChan_Opacity,
    MapChan_Bump,
    MapChan_Refraction
  };

private:
  OdResult dwgInFields(OdDbDwgFiler* pFiler, OdDbObject* pObj);
  void dwgOutFields(OdDbDwgFiler* pFiler, const OdDbObject* pObj) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler, OdDbObject* pObj);
  void dxfOutFields(OdDbDxfFiler* pFiler, const OdDbObject* pObj) const;

  void rdMatrix3d(OdDbDwgFiler* pFiler, OdGeMatrix3d& m);
  void rdMap(OdDbDwgFiler* pFiler, OdGiMaterialMap& mp);
  void rdMapper(OdDbDwgFiler* pFiler, OdGiMapper& mpr);
  void rdTexture(OdDbDwgFiler* pFiler, OdGiMaterialMap& map);
  void rdColor(OdDbDwgFiler* pFiler, OdGiMaterialColor& clr);
	void rdMatrix3d(OdDbDxfFiler* pFiler, OdGeMatrix3d& m, int grcode);
	void rdTexture(OdDbDxfFiler* pFiler, OdGiMaterialMap& map, int grcode);
	OdResBufPtr rdResBufTexture(OdResBufPtr pRb, OdGiMaterialMap& map);

  void wrMatrix3d(OdDbDwgFiler* pFiler, const OdGeMatrix3d& m) const;
  void wrMap(OdDbDwgFiler* pFiler, const OdGiMaterialMap& mp) const;
  void wrMapper(OdDbDwgFiler* pFiler, const OdGiMapper& mpr) const;
  void wrColor(OdDbDwgFiler* pFiler, const OdGiMaterialColor& clr) const;
	void wrTexture(OdDbDwgFiler* pFiler, const OdGiMaterialMap& map) const;
  void wrMatrix3dOpt(OdDbDxfFiler* pFiler, const OdGeMatrix3d& m, int grcode) const;
	void wrTexture(OdDbDxfFiler* pFiler, const OdGiMaterialMap& map, int chanCode = 0) const;
	void wrResBufTexture(OdResBufPtr &pRb1, const OdGiMaterialMap& map) const;

  void rdGenericTextureVariant(OdDbDwgFiler *pFiler, OdGiVariantPtr pParent);
  void rdGenericTextureVariant(OdDbDxfFiler *pFiler, OdGiVariantPtr pParent);
  OdGiProceduralTexturePtr rdProceduralTexture(OdDbDxfFiler *pFiler);
  void syncWithXrec(OdGiMaterialMap &mMapOpt, OdGiMaterialMap &mMapSync, OdDbObject *pObj, MapChannel xrecType, bool compose,
                    OdDb::SaveType format = OdDb::kDwg, OdDb::DwgVersion version = OdDb::vAC21);
  void wrGenericTextureVariant(OdDbDwgFiler *pFiler, OdGiVariantPtr pParent) const;
  void wrGenericTextureVariant(OdDbDxfFiler *pFiler, OdGiVariantPtr pParent) const;
  bool wrProceduralTexture(OdDbDxfFiler *pFiler, OdGiMaterialTexturePtr pTexture, int groupCode);
  void syncToXrec(OdGiMaterialMap &mMapOpt, OdGiMaterialMap &mMapSync, OdDbObject *pObj, MapChannel xrecType, bool decompose,
                  OdDb::SaveType format = OdDb::kDwg, OdDb::DwgVersion version = OdDb::vAC21);
  void rdUVTiling(OdGiMaterialMap &mMap, OdDbObject *pObj, MapChannel mapType, OdDb::SaveType format = OdDb::kDwg, OdDb::DwgVersion version = OdDb::vAC21);
  void wrUVTiling(OdGiMaterialMap &mMap, OdDbObject *pObj, MapChannel mapType, OdDb::SaveType format = OdDb::kDwg, OdDb::DwgVersion version = OdDb::vAC21);
  void rdAdvMaterial(OdDbObject *pObj, OdDb::SaveType format = OdDb::kDwg, OdDb::DwgVersion version = OdDb::vAC21);
  void rdAdvMaterial(OdDbDxfFiler *pFiler);
  void rdAdvMaterial(OdDbDwgFiler *pFiler);
  void wrAdvMaterial(OdDbObject *pObj, OdDb::SaveType format = OdDb::kDwg, OdDb::DwgVersion version = OdDb::vAC21) const;
  void wrAdvMaterial(OdDbDxfFiler *pFiler) const;
  void wrAdvMaterial(OdDbDwgFiler *pFiler) const;
  void syncWithSyncMaps();
  void syncSyncMaps();
public:
	void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
	void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
};

void oddbCreateDefMaterials(OdDbDatabaseImpl* pDbImpl);
TOOLKIT_EXPORT void oddbVerifyDefMaterials(OdDbDatabaseImpl* pDbImpl);

#endif // _DB_MATERIAL_IMPL_
