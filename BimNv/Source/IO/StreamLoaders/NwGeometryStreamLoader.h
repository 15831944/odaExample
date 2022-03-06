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
#ifndef __NW_GEOMETRYSTREAMLOADER_H__
#define __NW_GEOMETRYSTREAMLOADER_H__

#include "NwStreamLoader.h"
#include "NwGeometry.h"
#include "TD_PackPush.h"

class OdNwDatabaseImpl;

class OdNwGeometryCompressSettings;
typedef OdSmartPtr<OdNwGeometryCompressSettings> OdNwGeometryCompressSettingsPtr;

class OdNwSharedNodesStreamLoader;
typedef std::shared_ptr<OdNwSharedNodesStreamLoader> OdNwSharedNodesStreamLoaderPtr;
typedef std::weak_ptr<OdNwSharedNodesStreamLoader> OdNwSharedNodesStreamLoaderWeakPtr;

struct NwGeometryObjectDef
{
  OdUInt64 pos;
  OdUInt32 size;
  bool loaded;
  NwGeometryObjectDef(OdUInt64 apos = 0, OdUInt32 asize = 0, bool aloaded = false)
    : pos(apos), size(asize), loaded(aloaded) {}
};

typedef OdArray<NwGeometryObjectDef> NwGeometryObjectDefArray;

class OdNwGeometryStreamContext : public OdNwStreamContext
{
public:
  OdNwGeometryStreamContext(const OdNwStreamContext& ctx, const OdStreamBufPtr& streamTable);
  virtual ~OdNwGeometryStreamContext() = default;

  OdStreamBufPtr getStreamTable() const;
  OdNwGeometryCompressSettingsPtr getGeomCompressSettings() const;

  void setGeomCompressSettings(OdNwGeometryCompressSettingsPtr pGCSettings);

protected:
  OdStreamBufPtr m_streamTable;
  OdNwGeometryCompressSettingsPtr m_pGeomCompressSettings;
};

class OdNwGeometryStreamLoader : public OdNwStreamLoader
{
public:
  OdNwGeometryStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  static OdNwStreamLoaderPtr createStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual OdResult parseStream() override;

public:
  OdNwProxyPtr getComponentByIndex(OdUInt32 index);
  virtual OdArray<OdNwProxyPtr>& getGeometries();

  void setLinkLoaderGetter(const std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)>& getLoader) override;
  OdNwGeometryPtr readElement(OdUInt32 nElement);

public:
  OdResult resolveDependencies(OdNwGeometryPtr pGeometry);

protected:
  OdResult readObjectsTable();
  virtual OdStreamBufPtr getStream(OdUInt64 nElementPos, OdUInt64 nElementEnd);

protected:
  std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)> m_getLoaderCallBack;

  NwGeometryObjectDefArray  m_aObjectDefs;
  OdArray<OdNwProxyPtr>     m_aGeometries;
  OdStreamBufPtr            m_streamTable;

  OdNwSharedNodesStreamLoaderWeakPtr m_pSharedNodesLoader;

  bool m_bIsTableRead;//temporary
  bool m_bCacheGeometry;
};

typedef std::shared_ptr<OdNwGeometryStreamLoader> OdNwGeometryStreamLoaderPtr;
typedef std::weak_ptr<OdNwGeometryStreamLoader> OdNwGeometryStreamLoaderWeakPtr;

#include "TD_PackPop.h"

#endif // __NW_GEOMETRYSTREAMLOADER_H__
