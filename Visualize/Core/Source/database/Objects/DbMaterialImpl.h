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

class OdTvDbMaterialImpl : public OdTvDbObjectImpl
{
  static OdTvDbMaterialImpl* getImpl(const OdTvDbMaterial* pObj)
  { return (OdTvDbMaterialImpl*)OdTvDbSystemInternals::getImpl(pObj); }

	static void dxfInMaterialColor(OdTvDbDxfFiler *pFiler, OdGiMaterialColor& clr, int offset);

  friend class OdTvDbMaterial;

public:
  OdTvDbMaterialImpl();
  
  OdString                 m_Name;
  OdString name(const OdTvDbObject* pObj) const;
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
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler, OdTvDbObject* pObj);
  void dwgOutFields(OdTvDbDwgFiler* pFiler, const OdTvDbObject* pObj) const;
  OdResult dxfInFields(OdTvDbDxfFiler* pFiler, OdTvDbObject* pObj);
  void dxfOutFields(OdTvDbDxfFiler* pFiler, const OdTvDbObject* pObj) const;

  void rdMatrix3d(OdTvDbDwgFiler* pFiler, OdGeMatrix3d& m);
  void rdMap(OdTvDbDwgFiler* pFiler, OdGiMaterialMap& mp);
  void rdMapper(OdTvDbDwgFiler* pFiler, OdGiMapper& mpr);
  void rdTexture(OdTvDbDwgFiler* pFiler, OdGiMaterialMap& map);
  void rdColor(OdTvDbDwgFiler* pFiler, OdGiMaterialColor& clr);
	void rdMatrix3d(OdTvDbDxfFiler* pFiler, OdGeMatrix3d& m, int grcode);
	void rdTexture(OdTvDbDxfFiler* pFiler, OdGiMaterialMap& map, int grcode);
	OdTvResBufPtr rdResBufTexture(OdTvResBufPtr pRb, OdGiMaterialMap& map);

  void wrMatrix3d(OdTvDbDwgFiler* pFiler, const OdGeMatrix3d& m) const;
  void wrMap(OdTvDbDwgFiler* pFiler, const OdGiMaterialMap& mp) const;
  void wrMapper(OdTvDbDwgFiler* pFiler, const OdGiMapper& mpr) const;
  void wrColor(OdTvDbDwgFiler* pFiler, const OdGiMaterialColor& clr) const;
	void wrTexture(OdTvDbDwgFiler* pFiler, const OdGiMaterialMap& map) const;
  void wrMatrix3dOpt(OdTvDbDxfFiler* pFiler, const OdGeMatrix3d& m, int grcode) const;
	void wrTexture(OdTvDbDxfFiler* pFiler, const OdGiMaterialMap& map, int chanCode = 0) const;
	void wrResBufTexture(OdTvResBufPtr &pRb1, const OdGiMaterialMap& map) const;

  void rdGenericTextureVariant(OdTvDbDwgFiler *pFiler, OdGiVariantPtr pParent);
  void rdGenericTextureVariant(OdTvDbDxfFiler *pFiler, OdGiVariantPtr pParent);
  OdGiProceduralTexturePtr rdProceduralTexture(OdTvDbDxfFiler *pFiler);
  void syncWithXrec(OdGiMaterialMap &mMapOpt, OdGiMaterialMap &mMapSync, OdTvDbObject *pObj, MapChannel xrecType, bool compose,
                    OdDb::SaveType format = OdDb::kDwg, OdDb::DwgVersion version = OdDb::vAC21);
  void wrGenericTextureVariant(OdTvDbDwgFiler *pFiler, OdGiVariantPtr pParent) const;
  void wrGenericTextureVariant(OdTvDbDxfFiler *pFiler, OdGiVariantPtr pParent) const;
  bool wrProceduralTexture(OdTvDbDxfFiler *pFiler, OdGiMaterialTexturePtr pTexture, int groupCode);
  void syncToXrec(OdGiMaterialMap &mMapOpt, OdGiMaterialMap &mMapSync, OdTvDbObject *pObj, MapChannel xrecType, bool decompose,
                  OdDb::SaveType format = OdDb::kDwg, OdDb::DwgVersion version = OdDb::vAC21);
  void rdUVTiling(OdGiMaterialMap &mMap, OdTvDbObject *pObj, MapChannel mapType, OdDb::SaveType format = OdDb::kDwg, OdDb::DwgVersion version = OdDb::vAC21);
  void wrUVTiling(OdGiMaterialMap &mMap, OdTvDbObject *pObj, MapChannel mapType, OdDb::SaveType format = OdDb::kDwg, OdDb::DwgVersion version = OdDb::vAC21);
  void rdAdvMaterial(OdTvDbObject *pObj, OdDb::SaveType format = OdDb::kDwg, OdDb::DwgVersion version = OdDb::vAC21);
  void rdAdvMaterial(OdTvDbDxfFiler *pFiler);
  void rdAdvMaterial(OdTvDbDwgFiler *pFiler);
  void wrAdvMaterial(OdTvDbObject *pObj, OdDb::SaveType format = OdDb::kDwg, OdDb::DwgVersion version = OdDb::vAC21) const;
  void wrAdvMaterial(OdTvDbDxfFiler *pFiler) const;
  void wrAdvMaterial(OdTvDbDwgFiler *pFiler) const;
  void syncWithSyncMaps();
  void syncSyncMaps();
public:
	void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
	void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
};

void odtvdbCreateDefMaterials(OdTvDbDatabaseImpl* pDbImpl);
TOOLKIT_EXPORT void odtvdbVerifyDefMaterials(OdTvDbDatabaseImpl* pDbImpl);

#endif // _DB_MATERIAL_IMPL_
