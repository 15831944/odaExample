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
/************************************************************************/
/* This console application validate instance attributes                */
/*                                                                      */
/* Calling sequence:                                                    */
/*                                                                      */
/* ExIfcModelValidator <target filename>                                */
/*                                                                      */
/************************************************************************/
#include "ExIfcModelValidator.h"
#include "RxDynamicModule.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

ODGI_EXPORT void odgiInitialize();
ODGI_EXPORT void odgiUninitialize();

#include "IfcExamplesCommon.h"

#include "ExIfcHostAppServices.h"

#include "RxDynamicModule.h"

#include "DynamicLinker.h"

#include "ValidationNotifiers.h"

#include "daiStringWidthValidationTask.h"
#include "daiAggrSizeValidationTask.h"
#include "daiRequiredExplicitAttrsAssignedValidationTask.h"
#include "daiInverseAttrsValidationTask.h"
#include "daiWhereRulesAttrsValidationTask.h"
#include "daiWhereRulesEntitiesValidationTask.h"
#include "daiGlobalRulesValidationTask.h"

#include "daiValidator.h"

#include "IfcValidationModule.h"
#include "IfcPlaneAngleUnitValidationTask.h"

using namespace OdDAI;
using namespace OdIfc;

void initApp()
{
  odrxDynamicLinker()->loadModule(OdIfcValidation);

  ConsoleValidationNotifier::rxInit();
  TextValidationNotifier::rxInit();
  HtmlValidationNotifier::rxInit();
}

void uninitApp()
{
  odrxDynamicLinker()->unloadModule(OdIfcValidation);

  ConsoleValidationNotifier::rxUninit();
  TextValidationNotifier::rxUninit();
  HtmlValidationNotifier::rxUninit();
}

#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  if (argc < 2)
  {
    odPrintConsoleString(L"\nExIfcModelValidator sample program. Copyright (c) 2022, Open Design Alliance\n");
    odPrintConsoleString(L"\tusage: nExIfcModelValidator <target filename>\n");
    odPrintConsoleString(L"\nPress ENTER to continue...\n");
    return 1;
  }

  OdString szTargetFileName = argv[1];

  // create a service
  OdStaticRxObject< MyServices > svcs;

  /**********************************************************************/
  /* Initialize Runtime Extension environment                           */
  /**********************************************************************/
  odrxInitialize(&svcs);
  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize IfcCore                                                 */
  /**********************************************************************/
  odIfcInitialize(false /* No CDA */, false /* No geometry calculation needed */);

  initApp();
  
  try 
  {

    OdIfcFilePtr pIfcFile = svcs.readFile(szTargetFileName);
    if (pIfcFile.isNull())
    {
      return 1;
    }

    OdDAI::ModelPtr pModel = pIfcFile->getModel(sdaiRW);

    ValidatorPtr validator = Validator::createObject(pModel);

    StringWidthValidationTaskPtr stringTask = StringWidthValidationTask::createObject();
    AggrSizeValidationTaskPtr aggrTask = AggrSizeValidationTask::createObject();
    RequiredExplicitAttrsAssignedValidationTaskPtr reqTask = RequiredExplicitAttrsAssignedValidationTask::createObject();
    InverseAttrsValidationTaskPtr inverseTask = InverseAttrsValidationTask::createObject();
    WhereRulesAttrsValidationTaskPtr wrAttrsTask = WhereRulesAttrsValidationTask::createObject();
    WhereRulesEntitiesValidationTaskPtr wrEntitiesTask = WhereRulesEntitiesValidationTask::createObject();

    GlobalRulesValidationTaskPtr globalRulesTask = GlobalRulesValidationTask::createObject();

    PlaneAngleUnitValidationTaskPtr angleTask = PlaneAngleUnitValidationTask::createObject();

    ConsoleValidationNotifierPtr consoleValidationNotifier = ConsoleValidationNotifier::createObject();
    TextValidationNotifierPtr textValidationNotifier = TextValidationNotifier::createObject();
    HtmlValidationNotifierPtr htmlValidationNotifier = HtmlValidationNotifier::createObject();

    PlaneAngleUnitValidationHealerPtr angleHealer = PlaneAngleUnitValidationHealer::createObject();

    NotifierExtraInfo extraInfo;
    extraInfo.fileName = OdAnsiString(pIfcFile->getFileName());
    extraInfo.schemaName = pModel->underlyingSchemaName();

    consoleValidationNotifier->setModelInfo(&extraInfo);
    textValidationNotifier->setModelInfo(&extraInfo);
    htmlValidationNotifier->setModelInfo(&extraInfo);

    OdAnsiString textFileName = OdAnsiString(szTargetFileName.left(szTargetFileName.getLength() - 4) + L"_ValidationLog.txt");
    textValidationNotifier->setFileName(textFileName);
    OdAnsiString htmlFileName = OdAnsiString(szTargetFileName.left(szTargetFileName.getLength() - 4) + L"_ValidationLog.html");
    htmlValidationNotifier->setFileName(htmlFileName);

    PlaneAngleUnitValidationTask::desc()->addX(ModelValidationHealer::desc(), angleHealer);

    validator->addInstanceTask(stringTask);
    validator->addInstanceTask(aggrTask);
    validator->addInstanceTask(reqTask);
    validator->addInstanceTask(inverseTask);
    validator->addInstanceTask(wrAttrsTask);
    validator->addInstanceTask(wrEntitiesTask);

    validator->addModelTask(globalRulesTask);
    validator->addModelTask(angleTask);

    validator->addNotifier(consoleValidationNotifier);
    validator->addNotifier(textValidationNotifier);
    validator->addNotifier(htmlValidationNotifier);

    validator->setProgressMeter(svcs.newProgressMeter());

//    validator->setPrintingResult(Validator::kAll);
//    validator->setPrintingResult(Validator::kNotOk);
//    validator->setValidationType(Validator::kModelValidation);

    validator->run();
    
  }
  catch (...)
  {
    return 1;
  }

  uninitApp();
/**********************************************************************/
/* Uninitialize IfcCore                                               */
/**********************************************************************/
  odIfcUninitialize();

  /**********************************************************************/
  /* Uninitialize Runtime Extension environment                         */
  /**********************************************************************/
  odDbRootUninitialize();
  ::odrxUninitialize();
  return 0;
}
