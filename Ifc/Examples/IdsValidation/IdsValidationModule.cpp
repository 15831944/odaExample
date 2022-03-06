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

#include "IdsValidationModule.h"
#include "IdsValidationExport.h"
#include "RxDynamicModule.h"
#include "OdIdsIds.h"

#include "daiValidationCommon.h"

#include "IdsValidationTaskCreator.h"

#include "IdsInstanceValidationTask.h"
#include "IdsExtentValidationTask.h"

using namespace OdIds;

static std::map<OdAnsiString, std::list<OdDAI::ValidationTaskPtr> > IdsValidationTaskList;

class IDS_VALIDATION_EXPORT OdIdsValidationModuleImpl : public OdIdsValidationModule
{
public:

  virtual void loadFile(OdAnsiString path);

  virtual std::map<OdAnsiString, std::list<OdDAI::ValidationTaskPtr> > idsValidationTasks();
  virtual void clearValidationTaskLists();

  virtual void initApp();
  virtual void uninitApp();
};

ODRX_DEFINE_DYNAMIC_MODULE(OdIdsValidationModuleImpl);

void OdIdsValidationModuleImpl::loadFile(OdAnsiString path)
{
  std::list<OdDAI::ValidationTaskPtr> validationTasks = IdsValidationTaskCreator::openIdsFile(path);

  IdsValidationTaskList.insert(std::make_pair(path.right(path.getLength() - path.reverseFind('/') - 1), validationTasks));
}

std::map<OdAnsiString, std::list<OdDAI::ValidationTaskPtr> > OdIdsValidationModuleImpl::idsValidationTasks()
{
  return IdsValidationTaskList;
}

void OdIdsValidationModuleImpl::clearValidationTaskLists()
{
  IdsValidationTaskList.clear();
}

void OdIdsValidationModuleImpl::initApp()
{
  OdIdsInitalize(odrxSystemServices());

  IdsValidationTaskCreator::rxInit();
  IdsInstanceValidationTask::rxInit();
  IdsExtentValidationTask::rxInit();
}

void OdIdsValidationModuleImpl::uninitApp()
{
  clearValidationTaskLists();
  OdIdsUninitalize();

  IdsValidationTaskCreator::rxUninit();
  IdsInstanceValidationTask::rxUninit();
  IdsExtentValidationTask::rxUninit();
}
