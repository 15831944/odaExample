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

#ifndef _ODTV_MATERIALIMPL_H_INCLUDED_
#define _ODTV_MATERIALIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvMaterial.h"
#include "TvMaterialsTraits.h"
#include "TvInterfaceWrappers.h"
#include "TvUserDataImpl.h"

#include "RxObject.h"
#include "GiMaterial.h"

#include "DbMaterial.h"
#include "DbDictionary.h"
#include "DbSymbolTable.h"

class OdTvMaterialImpl : public OdTvDbMaterial, public OdTvXDataStorage
{
  OdTvMaterialImpl();

  virtual ~OdTvMaterialImpl();

public:
  ODRX_DECLARE_MEMBERS(OdTvMaterialImpl);

  /** \details
  Sets the emission color of this Material object.
  */
  virtual OdTvResult setEmission(const OdTvMaterialColor& emissionColor);

  /** \details
  Gets the emission color of this Material object.
  */
  virtual OdTvMaterialColor getEmission(OdTvResult* rc = NULL) const;

  /** \details
  Sets the raster image texture
  */
  virtual OdTvResult setRasterImageTexture(OdTvRasterImageId textureId);

  /** \details
  Gets the raster image texture
  */
  virtual OdTvRasterImageId getRasterImageTexture() const;

  /** \details
  Sets the opacity raster image texture
  */
  virtual OdTvResult setOpacityRasterImageTexture(OdTvRasterImageId textureId);

  /** \details
  Gets the opacity raster image texture
  */
  virtual OdTvRasterImageId getOpacityRasterImageTexture() const;

  /** \details
  Sets the bump raster image texture
  */
  virtual OdTvResult setBumpRasterImageTexture(OdTvRasterImageId textureId);

  /** \details
  Gets the bump raster image texture
  */
  virtual OdTvRasterImageId getBumpRasterImageTexture() const;

  /** \details
  Sets the tint component of this Material object.
  */
  virtual OdTvResult setTint(const OdTvMaterialColor &tintColor, bool bEnable);

  /** \details
  Returns the tint component of this Material object.
  */
  virtual bool getTint(OdTvMaterialColor &tintColor, OdTvResult *rc = NULL) const;

  /** \details
  Sets the secondary ambient (shadow) color of this Material object.
  */
  virtual OdTvResult setSecondaryAmbient(const OdTvMaterialColor& ambientColor);

  /** \details
  Gets the secondary ambient (shadow) color of this Material object.
  */
  virtual OdTvMaterialColor getSecondaryAmbient(OdTvResult* rc = NULL) const;

  /** \details
  Sets the secondary diffuse color of this Material object
  */
  virtual OdTvResult setSecondaryDiffuse(const OdTvMaterialColor& diffuseColor);

  /** \details
  Gets the secondary diffuse color of this Material object
  */
  virtual OdTvMaterialColor getSecondaryDiffuse(OdTvResult* rc = NULL) const;

  /** \details
  Sets the secondary specular (reflection) color of this Material object.
  */
  virtual OdTvResult setSecondarySpecular(const OdTvMaterialColor& specularColor);

  /** \details
  Gets the secondary specular (reflection) color of this Material object.
  */
  virtual OdTvMaterialColor getSecondarySpecular(OdTvResult* rc = NULL) const;

  /** \details
  Sets the secondary opacity component of this Material object.
  */
  virtual OdTvResult setSecondaryOpacity(double opacityPercentage);

  /** \details
  Gets the secondary opacity component of this Material object.
  */
  virtual double getSecondaryOpacity(OdTvResult* rc = NULL) const;

  /** \details
  Sets the support of non-texture mode for this Material object
  */
  virtual OdTvResult setSupportNonTextureMode(bool bNonTextureMode);

  /** \details
  Gets the support of non-texture mode for this Material object
  */
  virtual bool getSupportNonTextureMode(OdTvResult* rc = NULL) const;

  /** \details
  Sets coefficient of opacity influence onto received shadows.
  */
  virtual OdTvResult setShadowsOpacityEffect(double dShadowsOpacityEffectPercentage, double dNonShadowLightsMergeEffect);

  /** \details
  Returns coefficient of opacity influence onto received shadows.
  */
  virtual double getShadowsOpacityEffect(double* dNonShadowLightsMergeEffect, OdTvResult* rc = NULL) const;

  /** \details
  Sets that for the specular highlighting it is need to use value from the visual style
  */
  virtual OdTvResult setUseVisualStyleSpecular(bool bUse, double dMaxSpecularFactor = 0.1);

  /** \details
  Returns flag which indicates whether for the specular highlighting should be used a value from the visual style or not
  */
  virtual bool getUseVisualStyleSpecular(double* dMaxSpecularFactor = NULL, OdTvResult* rc = NULL) const;

  /** \details
  read data

  \param pFiler [in] Filer
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  write data

  \param pFiler [in] Filer
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  Sets the values of this object's subentity traits, and returns with the calling
  object's subentity traits.

  \param pTraits [in] Pointer to the OdGiDrawableTraits object to be set.
  */
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;

protected:
    void wrColor(OdTvDbDwgFiler* pFiler, const OdTvMaterialColor& color) const;
    void rdColor(OdTvDbDwgFiler* pFiler, OdTvMaterialColor& mcolor);

private:
  OdTvMaterialColor m_emissionColor;
  OdTvDbHardPointerId m_diffuseImageDefId;
  OdTvDbHardPointerId m_opacityImageDefId;
  OdTvDbHardPointerId m_bumpImageDefId;
  OdTvMaterialColor m_tintColor;
  OdTvMaterialColor m_secondaryAmbient;
  OdTvMaterialColor m_secondaryDiffuse;
  OdTvMaterialColor m_secondarySpecular;
  double m_dSecondaryOpacity;
  bool m_bNonTextureMode;
  double m_dShadowsOpacityEffectPercentage;
  double m_dNonShadowLightsMergeEffect;
  
  bool   m_bUseVisualStyleSpecular;
  double m_dMaxSpecularFactor;
};
typedef OdSmartPtr<OdTvMaterialImpl> OdTvMaterialImplPtr;

/** \details
This is an wrapper of the interface class for OdTvMaterial object.

\remarks
The purpose of this class is to connect the internal material object with an interface object
*/
class OdTvMaterialWrapper : public OdTvMaterial
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvMaterial, OdTvMaterialImpl)

  friend class OdTvEntityImpl;
  friend class OdTvGeometryDataImpl;
  friend class OdTvMaterialsIteratorImpl;
  friend class OdTvInsertWrapper;
  friend class OdTvInsertDataImpl;
  friend class OdTvDatabaseImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:
  /** \details
  Sets the name of this Material object.
  */
  virtual OdTvResult setName(const OdString& sName);

  /** \details
  Gets the name of this Material object.
  */
  virtual OdString getName(OdTvResult* rc = NULL) const;

  /** \details
  Sets the description of this Material object.
  */
  virtual OdTvResult setDescription(const OdString& sDescription);

  /** \details
  Gets the description of this Material object.
  */
  virtual OdString getDescription(OdTvResult* rc = NULL) const;

  /** \details
  Sets the ambient (shadow) color of this Material object.
  */
  virtual OdTvResult setAmbient(const OdTvMaterialColor& ambientColor);

  /** \details
  Gets the ambient (shadow) color of this Material object.
  */
  virtual OdTvMaterialColor getAmbient(OdTvResult* rc = NULL) const;

  /** \details
  Sets the diffuse (main) color of this Material object
  */
  virtual OdTvResult setDiffuse(const OdTvMaterialColor& diffuseColor, const OdTvMaterialMap& diffuseMap);

  /** \details
  Gets the diffuse (main) color of this Material object
  */
  virtual OdTvResult getDiffuse(OdTvMaterialColor& diffuseColor, OdTvMaterialMap& diffuseMap) const;

  /** \details
  Sets the specular (reflection) color of this Material object.
  */
  virtual OdTvResult setSpecular(const OdTvMaterialColor& specularColor, double dGlossFactor);

  /** \details
  Gets the specular (reflection) color of this Material object.
  */
  virtual OdTvResult getSpecular(OdTvMaterialColor& specularColor, double& dGlossFactor) const;

  /** \details
  Sets the emission color of this Material object.
  */
  virtual OdTvResult setEmission(const OdTvMaterialColor& emissionColor);

  /** \details
  Gets the emission color of this Material object.
  */
  virtual OdTvMaterialColor getEmission(OdTvResult* rc = NULL) const;

  /** \details
  Sets the specular gloss of this Material object.
  */
  virtual OdTvResult setSpecularGloss(double dSpecularGloss);

  /** \details
  Gets the specular gloss of this Material object.
  */
  virtual double getSpecularGloss(OdTvResult* rc = NULL) const;

  /** \details
  Sets the opacity component of this Material object.
  */
  virtual OdTvResult setOpacity(double dOpacityPercentage, const OdTvMaterialMap* pOpacityMap = NULL);

  /** \details
  Gets the opacity component of this Material object.
  */
  virtual OdTvResult getOpacity(double& opacityPercent, OdTvMaterialMap& opacityMap) const;

  /** \details
  Sets the bump component of this Material object.
  */
  virtual OdTvResult setBump(const OdTvMaterialMap& bumpMap);

  /** \details
  Returns the bump component of this Material object.
  */
  virtual OdTvResult getBump(OdTvMaterialMap& bumpMap) const;

  /** \details
  Sets the tint component of this Material object.
  */
  virtual OdTvResult setTint(const OdTvMaterialColor &tintColor, bool bEnable);

  /** \details
  Returns the tint component of this Material object.
  */
  virtual bool getTint(OdTvMaterialColor &tintColor, OdTvResult *rc = NULL) const;

  /** \details
  Sets the secondary ambient (shadow) color of this Material object.
  */
  virtual OdTvResult setSecondaryAmbient(const OdTvMaterialColor& ambientColor);

  /** \details
  Gets the secondary ambient (shadow) color of this Material object.
  */
  virtual OdTvMaterialColor getSecondaryAmbient(OdTvResult* rc = NULL) const;

  /** \details
  Sets the secondary diffuse color of this Material object
  */
  virtual OdTvResult setSecondaryDiffuse(const OdTvMaterialColor& diffuseColor);

  /** \details
  Gets the secondary diffuse color of this Material object
  */
  virtual OdTvMaterialColor getSecondaryDiffuse(OdTvResult* rc = NULL) const;

  /** \details
  Sets the secondary specular (reflection) color of this Material object.
  */
  virtual OdTvResult setSecondarySpecular(const OdTvMaterialColor& specularColor);

  /** \details
  Gets the secondary specular (reflection) color of this Material object.
  */
  virtual OdTvMaterialColor getSecondarySpecular(OdTvResult* rc = NULL) const;

  /** \details
  Sets the secondary opacity component of this Material object.
  */
  virtual OdTvResult setSecondaryOpacity(double opacityPercentage);

  /** \details
  Gets the secondary opacity component of this Material object.
  */
  virtual double getSecondaryOpacity(OdTvResult* rc = NULL) const;

  /** \details
  Sets the support of non-texture mode for this Material object
  */
  virtual OdTvResult setSupportNonTextureMode(bool bNonTextureMode);

  /** \details
  Gets the support of non-texture mode for this Material object
  */
  virtual bool getSupportNonTextureMode(OdTvResult* rc = NULL) const;

  /** \details
  Sets coefficient of opacity influence onto received shadows.
  */
  virtual OdTvResult setShadowsOpacityEffect(double dShadowsOpacityEffectPercentage, double dNonShadowLightsMergeEffect = 1.0);

  /** \details
  Returns coefficient of opacity influence onto received shadows.
  */
  virtual double getShadowsOpacityEffect(double* dNonShadowLightsMergeEffect = NULL, OdTvResult* rc = NULL) const;

  /** \details
  Sets that for the specular highlighting it is need to use value from the visual style
  */
  virtual OdTvResult setUseVisualStyleSpecular(bool bUse, double dMaxSpecularFactor = 0.1);

  /** \details
  Returns flag which indicates whether for the specular highlighting should be used a value from the visual style or not
  */
  virtual bool getUseVisualStyleSpecular(double* dMaxSpecularFactor = NULL, OdTvResult* rc = NULL) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Internal methods
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  OdTvDbObjectId getWrappedDbObjectId();

};

/** \details
This is an implementation of the iterator class for the materials
*/
class ODTV_EXPORT OdTvMaterialsIteratorImpl : public OdTvMaterialsIterator
{
  friend class OdTvDatabaseImpl;
public:

  /** \details
  Returns true if and only if the traversal by this Iterator object is complete.
  */
  virtual bool done(OdTvResult* rc = NULL) const;

  /** \details
  Steps this Iterator object.
  */
  virtual OdTvResult step();

  /** \details
  Returns the material currently referenced by this Iterator object.
  */
  virtual OdTvMaterialId getMaterial(OdTvResult* rc = NULL) const;

  /** \details
  Positions this Iterator object at the specified material.
  \param objectId [in]  Material ID.
  */
  virtual OdTvResult seek(const OdTvMaterialId& MaterialId);

  /** \details
  Methods for creating the object
  */
  static OdTvMaterialsIteratorPtr createObject(OdTvDbDictionaryIterator* pDbDictIterator);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvMaterialsIteratorImpl();
  OdTvMaterialsIteratorImpl(OdTvDbDictionaryIterator* pDbDictIterator);

  virtual ~OdTvMaterialsIteratorImpl();

  // Db iterator
  OdTvDbDictionaryIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;
};

//***************************************************************************//
// A few helper functions
//***************************************************************************//

/** \details
Get data from OdGiMaterialColor and write in OdTvMaterialColor
*/
OdTvMaterialColor getOdTvMaterialColorFromOdGiMaterialColor(const OdGiMaterialColor& dbMaterialColor);

/** \details
Get data from OdTvMaterialColor and write in OdGiMaterialColor
*/
OdGiMaterialColor getOdGiMaterialColorFromOdTvMaterialColor(const OdTvMaterialColor& materialColor);

/** \details
Get data from OdGiMaterialMap and write in OdTvMaterialMap
*/
OdTvMaterialMap getOdTvMaterialMapFromOdGiMaterialMap(const OdGiMaterialMap& dbMaterialMap);

/** \details
Get data from OdTvMaterialMap and write in OdGiMaterialMap
*/
OdGiMaterialMap getOdGiMaterialMapFromOdTvMaterialMap(const OdTvMaterialMap& materialMap);

typedef OdVector<OdGiMapper, OdMemoryAllocator<OdGiMapper> > OdGiMapperArray;

#include "TD_PackPop.h"

#endif // _ODTV_MATERIAL_H_INCLUDED_
