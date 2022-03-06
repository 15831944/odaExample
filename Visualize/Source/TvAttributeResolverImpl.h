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

#ifndef _ODTV_ATTRIBUTERESOLVERIMPL_H_INCLUDED_
#define _ODTV_ATTRIBUTERESOLVERIMPL_H_INCLUDED_

#include "TvAttributeResolver.h"
#include "TvLayer.h"
#include "TvMaterial.h"
#include "TvLinetype.h"
#include "TvVisualStyle.h"
#include "TvTextStyle.h"
#include "TvRasterImage.h"
#include "TvBlock.h"
#include "TvRasterImageImpl.h"
#include "TvInsertImpl.h"
#include "TvLightImpl.h"
#include "TvBlockTableRecordImpl.h"

#define STL_USING_MAP

#define ODTV_DEFAULT_LINETYPES_NUM 3
#define ODTV_DEFAULT_MATERIALS_NUM 3

OdTvEntityId createEntityInBlockFunct(const OdString& sEntityName, OdTvBlockTableRecord* pBlock, OdTvBlockId secondBlock);
OdString getEntityName(OdSmartPtr<OdTvEntityImpl> pEntityImpl);
OdTvEntityId createInsertInBlockFunct(const OdString& sEntityName, OdTvBlockTableRecord* pBlock, OdTvBlockId secondBlock);
OdString getInsertName(OdSmartPtr<OdTvInsertImpl> pInsertImpl);
OdTvEntityId createLightInBlockFunct(const OdString& sEntityName, OdTvBlockTableRecord* pBlock, OdTvBlockId secondBlock);
OdString getLightName(OdSmartPtr<OdTvLightImpl> pLightImpl);
OdTvEntityId findEntityInBlock(const OdString& sEntityName, OdTvBlockTableRecord* pBlock);

class ODTV_EXPORT OdTvAttributeResolverImpl : public OdTvAttributeResolver
{
protected:
  OdTvDatabaseId m_srcDb;
  OdTvDatabaseId m_dstDb;
  ConflictResolvingMethod m_method;
  OdString m_prefix;
  OdUInt32 m_nAttempts;

  unsigned int m_nRefCounter;

  std::map< OdTvLayerId, OdTvLayerId > m_layers;
  std::map< OdTvLinetypeId, OdTvLinetypeId > m_linetypes;
  std::map< OdTvMaterialId, OdTvMaterialId > m_materials;
  std::map< OdTvVisualStyleId, OdTvVisualStyleId > m_visualStyles;
  std::map< OdTvTextStyleId, OdTvTextStyleId > m_textStyles;
  std::map< OdTvRasterImageId, OdTvRasterImageId > m_rasterImages;
  std::map< OdTvBlockId, OdTvBlockId > m_blocks;

  bool m_bZeroLayerResolved;
  OdTvLayerId m_resolvedZeroLayer;

  struct DefaultLinetype
  {
    OdTvLinetypeId ltId;
    bool bResolved;
  };
  DefaultLinetype m_defLt[ODTV_DEFAULT_LINETYPES_NUM];

  struct DefaultMaterial
  {
    OdTvMaterialId matId;
    bool bResolved;
  };
  DefaultMaterial m_defMat[ODTV_DEFAULT_MATERIALS_NUM];

  std::map<OdString, OdTvVisualStyleId> m_defVisStyle;

public:
  enum DefaultTypes
  {
    kContinious = 0,
    kByLayer = 1,
    kByBlock = 2,
    kGlobal = 3
  };

  OdTvAttributeResolverImpl( OdTvDatabaseId srcDb, OdTvDatabaseId dstDb, ConflictResolvingMethod method = kReuse );
  virtual ~OdTvAttributeResolverImpl();

  virtual OdTvDatabaseId sourceDatabase() const;
  virtual OdTvDatabaseId destinationDatabase() const;
  virtual ConflictResolvingMethod resolvingMethod() const;
  virtual void setPrefix( const OdString& str );
  virtual OdString prefix() const;
  virtual void setMangleAttempts( OdUInt32 nAttempts );
  virtual OdUInt32 mangleAttempts() const;

  OdTvLayerId resolveLayer( OdTvLayerId );
  OdTvLayerId resolveZeroLayer( const OdTvDbDatabase* pSrcDatabase, OdTvDbDatabase* pDstDatabase );

  OdTvMaterialId resolveMaterial( OdTvMaterialId );
  OdTvMaterialId resolveDefaultMaterial( const OdTvDbDatabase* pSrcDatabase, OdTvDbDatabase* pDstDatabase, DefaultTypes type );

  OdTvLinetypeId resolveLinetype( OdTvLinetypeId );
  OdTvLinetypeId resolveDefaultLinetype( const OdTvDbDatabase* pSrcDatabase, OdTvDbDatabase* pDstDatabase, DefaultTypes type );

  OdTvVisualStyleId resolveVisualStyle( OdTvVisualStyleId );
  OdTvVisualStyleId resolveDefaultVisualStyle(const OdTvDbDatabase* pSrcDatabase, OdTvDbDatabase* pDstDatabase, OdTvDbObjectId visualStyleDbId);

  OdTvTextStyleId resolveTextStyle( OdTvTextStyleId );

  OdTvRasterImageId resolveRasterImage( OdTvRasterImageId );

  OdTvBlockId resolveBlock( OdTvBlockId srcBlockId );

  // Second block is dst block for insert. Set empty OdTvBlockId if entity type is not insert.
  template<class Type, class TypeImpl>
  OdTvEntityId resolveEntity(OdTvEntityId srcObjectId, OdTvBlockTableRecord* pDstBlock, OdTvBlockId secondBlock, OdTvEntityId(*findFunct)(const OdString&, OdTvBlockTableRecord*),
    OdTvEntityId(*createFunct)(const OdString&, OdTvBlockTableRecord*, OdTvBlockId), OdString(*getNameFunct)(OdSmartPtr<TypeImpl>), bool& bNeedCopyProperties);

  virtual void addRef()
  {
    ++m_nRefCounter;
  }
  virtual void release()
  {
    if (m_nRefCounter == 1)
    {
      delete this;
    }
    else
      --m_nRefCounter;
  }
  virtual long numRefs() const
  {
    return m_nRefCounter;
  }

protected:

  template<class TypeId, class Type, class TypeImpl>
  TypeId resolveType(TypeId srcObjectId, std::map< TypeId, TypeId >& objectsMap, 
    TypeId (*findFunct)(OdString, OdTvDatabaseId), TypeId(*createFunct)(OdString, OdTvDatabaseId),
    OdString (*getNameFunct)(OdSmartPtr<TypeImpl>), bool& bNeedReturn);

  OdTvRasterImageId createRasterImageFromSrc(const OdString& sSrcImageName, OdTvRasterImageImplPtr pSrcImageImpl, OdTvDatabasePtr pDstDb, OdTvResult* rc = NULL) const;
};

#endif // _ODTV_ATTRIBUTERESOLVERIMPL_H_INCLUDED_

