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
#include "CustomCmndModule.h"
#include "Ed/EdCommandStack.h"
#include "OdCommandContext.h"
#include "TvDatabase.h"

DISABLE_THREAD_LIBRARY_CALLS();

using namespace OdWeb;

void CustomCmndModule::entitiesCount(OdEdCommandContext *ctx)
{
  OdCommandContext* pCtx = static_cast<OdCommandContext*>(ctx);
  OdTvDatabaseId dbId = pCtx->getDatabase();

  long count = 0;
  OdTvEntitiesIteratorPtr entItr;
  OdTvModelsIteratorPtr   itr = dbId.openObject()->getModelsIterator();
 
  for (; !itr->done(); itr->step()) {
    entItr = itr->getModel().openObject()->getEntitiesIterator();
    for (; !entItr->done(); entItr->step()) {
      if (entItr->getEntity().getType() == OdTvEntityId::kEntity) {
        count++;
      }
    }
  }

  TBaseIO &io = *pCtx->getIo();

  OdString entitiesCntStr;
  entitiesCntStr.format(OD_T("%d"), count);
  io.putString(entitiesCntStr);
}

void CustomCmndModule::initApp()
{
  OdEdCommandStackPtr regCmds = ::odedRegCmds();
  OdString cmd, grp = "CloudCustomCmnd";

  cmd = "ENTITIES_COUNT";
  regCmds->addCommand(grp, cmd, cmd, 0, &CustomCmndModule::entitiesCount);
}

void CustomCmndModule::uninitApp()
{
  ::odedRegCmds()->removeGroup("CloudCustomCmnd");
}

ODRX_DEFINE_DYNAMIC_MODULE(CustomCmndModule);
