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

#include "OdaCommon.h"
#include "OdString.h"
#include "TvDatabase.h"
#include "TvFactory.h"
#include <memory>
#include "TvModel.h"
#include "TvGsDevice.h"

struct MetaDataItem {
  OdString name;
  OdString path;
};

struct OdBaseConvertOptions
{
  OdString dist;
};

struct BaseConvertWorker
{
  virtual void convert(OdBaseConvertOptions *opt) = 0;

  void removeDatabase(const OdTvDatabaseId& t_dbId) {
    OdTvFactoryId factory = odTvGetFactory();
    if (factory.isNull()) {
      return;
    }

    if (t_dbId.isNull()) {
      return;
    }
    // Try unload gs view 
    // Fix for Linux 
    try {
      OdTvDevicesIteratorPtr devItr = t_dbId.openObject(OdTv::kForWrite)->getDevicesIterator();
      for (; !devItr->done(); devItr->step()) {
        OdTvGsDeviceId devId = devItr->getDevice();
        if (!devId.isNull()) {
          OdTvGsDevicePtr devicePtr = devId.openObject(OdTv::kForWrite);
          if (devicePtr->isGsLoaded()) {
            devicePtr->unloadGs();
          }
          devicePtr->eraseAllViews();
        }
      }
      factory.removeDatabase(t_dbId);
    }
    catch (...) {}
  }
protected:
  OdTvModelId getActiveModel(const OdTvDatabaseId& tvDbId)
  {
    OdTvModelsIteratorPtr mItr = tvDbId.openObject()->getModelsIterator();
    if (mItr->done()) {
      throw OdError("Fail export to DWG not found active model");
    }
    return mItr->getModel();
  }

  OdTvGsDeviceId getActiveDevice(const OdTvDatabaseId& tvDbId)
  {
    OdTvGsDeviceId actDevId;
    OdTvDevicesIteratorPtr devItr = tvDbId.openObject()->getDevicesIterator();
    for (; !devItr->done(); devItr->step()) {
      OdTvGsDeviceId devId = devItr->getDevice();
      if (devId.openObject()->getActive()) {
        actDevId = devId;
      }
    }

    if (actDevId.isNull()) {
      devItr = tvDbId.openObject()->getDevicesIterator();
      if (!devItr->done()) {
        actDevId = devItr->getDevice();
      }
    }

    if (actDevId.isNull()) {
      throw OdError("Fail export to DWG not found active device");
    }

    return actDevId;
  }

  OdTvGsViewId getActiveView(const OdTvGsDeviceId& actDevId)
  {
    OdTvGsViewId actViewId = actDevId.openObject()->getActiveView();
    if (actViewId.isNull()) {
      throw OdError("Fail export to DWG not found active view");
    }
    return actViewId;
  }

  OdString getExtension(const OdString& path) {
    return path.right(3).makeUpper();
  }
};

typedef std::shared_ptr<BaseConvertWorker> BaseConvertWorkerPtr;
