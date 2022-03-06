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
#ifndef __NW_SCENESETSTREAMLOADER_H__
#define __NW_SCENESETSTREAMLOADER_H__

#include "NwStreamLoader.h"
#include "NwModelUnits.h"
#include "TD_PackPush.h"

class OdNwModel;
typedef OdSmartPtr<OdNwModel> OdNwModelPtr;
class OdNwObjectReaderManager;
typedef OdSharedPtr<OdNwObjectReaderManager> OdNwObjectReaderManagerPtr;
class OdNwSceneSet;
typedef OdSharedPtr<OdNwSceneSet> OdNwSceneSetPtr;
class OdNwModelValidData;
typedef OdSharedPtr<OdNwModelValidData> OdNwModelValidDataPtr;
class OdNwCachePlugin;
class OdNwCacheXref;
typedef OdSharedPtr<OdNwCacheXref> OdNwCacheXrefPtr;
class OdNwXRefTable;
typedef OdSharedPtr<OdNwXRefTable> OdNwXRefTablePtr;

class OdNwSceneSetStreamContext : public OdNwStreamContext
{
public:
  OdNwSceneSetStreamContext(const OdNwStreamContext& ctx, OdNwXRefTablePtr pXRefTable);
  virtual ~OdNwSceneSetStreamContext() = default;

  OdNwXRefTablePtr getXRefTable() const;

protected:
  OdNwXRefTablePtr m_pXRefTable;
};

typedef std::shared_ptr<OdNwSceneSetStreamContext> OdNwSceneSetStreamContextPtr;

class OdNwSceneSetStreamLoader : public OdNwStreamLoader
{
public:
  OdNwSceneSetStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual ~OdNwSceneSetStreamLoader();
  static OdNwStreamLoaderPtr createStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual OdResult parseStream() override;

public:
  OdNwSceneSetPtr getSceneSet() const;
  NwModelUnits::Enum getModelUnits() const;

public:
  static OdNwModelPtr readModel(OdNwObjectReaderManagerPtr manager);
  static OdNwSceneSetPtr readSceneSet(OdNwObjectReaderManagerPtr manager);

  static OdNwModelValidDataPtr readModelValidData(OdNwObjectReaderManagerPtr manager);
  static OdResult readCachePlugin(OdNwObjectReaderManagerPtr manager, OdNwCachePlugin* pCachePlugin);
  static OdResult readNW5(OdNwObjectReaderManagerPtr manager, OdNwModelValidDataPtr pModelValidData);
  static OdNwCacheXrefPtr readCacheXref(OdNwObjectReaderManagerPtr manager, const OdString& name);
  static OdString readXRef(OdNwSceneSetStreamContextPtr context);

private:
  NwModelUnits::Enum m_modelUnits;
  OdNwSceneSetPtr m_pSceneSet;
  OdNwObjectReaderManagerPtr m_pReaderMgr;
};

#include "TD_PackPop.h"

#endif // __NW_SCENESETSTREAMLOADER_H__
