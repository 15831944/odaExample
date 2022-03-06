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

#include "tuple"
#include "OdaCommon.h"

class OdTvDatabaseId;
class OdGsDevice;
class OdDbDatabase;
class OdEdCommandContext;
class IStreamOutput;
class INativeHandleEntityStore;
/*
 * class DwgHelper
 * Helper for setup dwg and visualize export device
 */
class DwgHelper
{
public:
  std::tuple<OdTvDatabaseId*, OdGsDevice*> setupRuntimeImportDwgToVsf(OdDbDatabase* pDb, ODCOLORREF background = ODRGB(255, 255, 255));

  OdDbDatabase* getDwgDatabase(OdEdCommandContext* pCtx);

  OdGsDevice* getImportDevice(OdEdCommandContext* pCtx);

  OdTvDatabaseId* getVisualizeDbId(OdEdCommandContext* pCtx);

  void setDwgDatabase(OdEdCommandContext* pCtx, OdDbDatabase* pDb);

  void setImportDevice(OdEdCommandContext* pCtx, OdGsDevice* pGs);

  void setVisualizeDbId(OdEdCommandContext* pCtx, OdTvDatabaseId* pVsDbId);

  void invalidateAndUpdate(OdEdCommandContext* pCtx);

  void invalidateWithRegenerationAndUpdate(OdEdCommandContext* pCtx);

  IStreamOutput* getStreamOutput(OdEdCommandContext* pCtx);

  INativeHandleEntityStore* getNativeHandleEntityStore(OdEdCommandContext* pCtx);

  void bindNativeHandlesWithVisualizeEntities(OdEdCommandContext* pCtx);
};