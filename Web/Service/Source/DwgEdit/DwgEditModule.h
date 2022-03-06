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
#include "RxDynamicModule.h"
#include "Ed/EdCommandStack.h"
#include "DbDatabase.h"
#include "DbGsManager.h"
#include "TvGsView.h"
#include "Gs/Gs.h"
#include "OdString.h"
#include "Ed/EdCommandContext.h"
#include "DbObjectId.h"

using namespace Oda;

#ifdef _WIN32
#define OUT_PUT "devnull"
#else
#define OUT_PUT "null"
#endif // _WIN32

OdDbObjectId activeBlockTableRecord(const OdDbDatabase* pDb);

OdGeVector3d ucsNormal(const OdDbDatabase * pDb);

class DwgEditModule : public OdRxModule {
public:
  static void switchDwgLayout(OdEdCommandContext* ctx);

  static void AddLine(OdEdCommandContext *ctx);

  static void MoveToFront(OdEdCommandContext* ctx);

  static void MoveToBottom(OdEdCommandContext* ctx);

  static void DeleteLine(OdEdCommandContext *ctx);

  static void MoveLine(OdEdCommandContext *ctx);

  static void CreateLayer(OdEdCommandContext* ctx);

  static void CreateBlockRef(OdEdCommandContext* ctx);

  static void BindNativeHandlesWithVisualizeEntities(OdEdCommandContext* ctx);
protected:
  void initApp();
  void uninitApp();
};
