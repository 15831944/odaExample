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

#include "IfcValidationModule.h"

#include "RxDynamicModule.h"

#include "daiValidationCommon.h"

#include "daiModelValidationTask.h"
#include "daiExtentValidationTask.h"
#include "daiInstanceValidationTask.h"

#include "IfcPlaneAngleUnitValidationTask.h"
#include "IfcCompositeCurveConsistencyValidationTask.h"
#include "IfcProfileDefValidationTask.h"
#include "IfcProfileDef.h"
//#include "IfcFacetedBrepValidationTask.h"
//#include "IfcFacetedBrep.h"

using namespace OdIfc;

static std::list<OdRxClass*> IfcModelValidationTaskList;
static std::list<OdRxClass*> IfcExtentValidationTaskList;
static std::list<OdRxClass*> IfcInstanceValidationTaskList;

void addValidationTask(OdRxClass* task)
{
  if (!OdDAI::ModelValidationTask::cast(task->create()).isNull())
    IfcModelValidationTaskList.push_back(task);
  else if (!OdDAI::ExtentValidationTask::cast(task->create()).isNull())
    IfcExtentValidationTaskList.push_back(task);
  else if (!OdDAI::InstanceValidationTask::cast(task->create()).isNull())
    IfcInstanceValidationTaskList.push_back(task);
}

void removeValidationTask(OdRxClass* task)
{
  IfcModelValidationTaskList.remove(task);
  IfcInstanceValidationTaskList.remove(task);
  IfcExtentValidationTaskList.remove(task);
}

class IFC_VALIDATION_EXPORT OdIfcValidationModuleImpl : public OdIfcValidationModule
{
public:

  virtual std::list<OdRxClass*> ifcModelValidationTasks();
  virtual std::list<OdRxClass*> ifcExtentValidationTasks();
  virtual std::list<OdRxClass*> ifcInstanceValidationTasks();

  /** \details
  Initialization of the IFC validation module.
  */
  virtual void initApp();
  /** \details
  Uninitialization of the IFC validation module.
  */
  virtual void uninitApp();
};

ODRX_DEFINE_DYNAMIC_MODULE(OdIfcValidationModuleImpl);

std::list<OdRxClass*> OdIfcValidationModuleImpl::ifcModelValidationTasks()
{
  return IfcModelValidationTaskList;
}

std::list<OdRxClass*> OdIfcValidationModuleImpl::ifcExtentValidationTasks()
{
  return IfcExtentValidationTaskList;
}

std::list<OdRxClass*> OdIfcValidationModuleImpl::ifcInstanceValidationTasks()
{
  return IfcInstanceValidationTaskList;
}

void OdIfcValidationModuleImpl::initApp()
{
  PlaneAngleUnitValidationTask::rxInit();
    PlaneAngleUnitValidationHealer::rxInit();
  CompositeCurveConsistencyValidationTask::rxInit();
  OdIfcProfileDefValidationTask::rxInit();
//  OdIfcFacetedBrepValidationTask::rxInit();

  PlaneAngleUnitValidationTask::desc()->addX(OdDAI::ModelValidationHealer::desc(), PlaneAngleUnitValidationHealer::createObject());
//  OdIfcFacetedBrep::desc()->addX(OdDAI::ModelValidationTask::desc(), OdIfcFacetedBrepValidationTask::createObject());
}

void OdIfcValidationModuleImpl::uninitApp()
{
//  OdIfcFacetedBrepValidationTask::rxUninit();
  PlaneAngleUnitValidationTask::rxUninit();
    PlaneAngleUnitValidationHealer::rxUninit();
  CompositeCurveConsistencyValidationTask::rxUninit();
  OdIfcProfileDefValidationTask::rxUninit();
}
