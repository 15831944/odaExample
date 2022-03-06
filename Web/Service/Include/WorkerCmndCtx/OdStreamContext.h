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
//   This application incorporates Open Design Alliance software pursuant to a
//   license agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance.
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "CloudLibTools.h"
#include "OdaCommon.h"


#include "GsBaseVectorizeDevice.h"
#include "GsViewImpl.h"
#include "DbObjectIterator.h"
#include "DbPartialViewing.h"

#include "DynamicLinker.h"
#include "RuntimeIO/DbRuntimeIO.h"
#include "OdStreamOutput.h"
#include "TvDatabase.h"
#include "../Source/TvGsDeviceImpl.h"
#include "OdObjectIteratorSet.h"

#include "IStreamOutput.hpp"

#include <set>

namespace OdWeb {


struct CLOUD_CMDCTX_EXPORT OdStreamContextSettings {
  OdUInt64 packageSize;
  OdUInt64 memoryLimit;
  bool     useCache;

  OdStreamContextSettings(OdUInt64 pkgSize = 256000, OdUInt64 memLimit = 1000000000, bool enableCache = true)
    : packageSize(pkgSize),
    memoryLimit(memLimit),
    useCache(enableCache) {}
};

typedef OdSmartPtr<OdStreamContextSettings> OdStreamContextSettingsPtr;

enum PackageType {
  Database,
  AddObject,
  EraseObject,
  NewObject,
  ChangeOrder
};

class OdStreamContext;
typedef OdSmartPtr<OdStreamContext>             OdStreamContextPtr;
typedef std::map<OdTvGsDeviceId, OdGsDevicePtr> DeviceFilterMap;

class CLOUD_CMDCTX_EXPORT OdStreamContext : public OdTvDbPartialViewingModule::DataManagerContext {

public:
  OdStreamContext();

  ~OdStreamContext();

  void setSettings(const OdStreamContextSettings &settings);

  OdStreamContextSettings getSettings();

  void initialize(OdTvDbRtFilerController* dataCntrl, OdStreamOutputPtr output, OdTvDatabaseId db);

  void setupDevices(OdTvDatabaseId db);

  void addIndex();

  virtual OdTvDbObjectIteratorPtr currentSet();

  void orderModify(const OdTvModelId& modelId, const OdArray<OdTvEntityId>& entitiesArray, Order direction);

  void writeErase(OdTvDbObjectIterator& iterator);

  void writeAdd(OdTvDbObjectIterator& iterator);

  void manageData(OdTvDbObjectIterator& willBeShown, OdTvDbObjectIterator& mayBeUnloaded) override;

  static OdStreamContextPtr create();

  void filter();

  void wrDatabase(bool enableCompression = false);

  void wrObjects(const OdTvDbObjectId& id, OdStreamBufPtr &output);

  void send(OdStreamBufPtr buff);

  OdObjectIteratorSet* getSended();

  bool checkNeedSend(OdStreamBufPtr& buffer);

  void wrPackageType(PackageType type, OdStreamBuf *output);

  OdStreamBufPtr createStreamForPackage(PackageType type);

  OdTvDbDwgFilerPtr createFlatFilerForStream(OdStreamBufPtr &buffer);

  void setActiveDevice(const OdTvGsDeviceId& id);
private:
  OdArray<OdTvDbFilterPtr>                m_filters;
  OdTvDbPartialViewingFilterPtr           m_viewingFilter;
  OdTvDbPartialViewingModulePtr           m_partialViewingModule;
  OdGsDevicePtr                           m_activeDevice;
  OdStreamOutputPtr                       m_dataOutput;
  OdTvDbRtFilerController*                m_dataController;
  OdTvDatabaseId                          m_dbId;
  OdStreamContextSettings                 m_settings;
  OdTvDbObjectIteratorPtr                 m_sendedItr;
  OdUInt64                                m_memoryLength;
  OdStreamContextPtr                      m_streamCtx;
  std::map<OdTvGsDeviceId, OdGsDevicePtr> m_gsDevices;
  std::map<OdUInt64, OdUInt64>            m_entitySize;

};

}
