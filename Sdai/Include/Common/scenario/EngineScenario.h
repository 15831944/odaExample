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

#ifndef _SCENARIO_ENGINE_SCENARIO_H_
#define _SCENARIO_ENGINE_SCENARIO_H_


#include "SharedPtr.h"
#include "ScenarioEngineDeclarations.h"
#include "ScenarioEngineUtils.h"

namespace ScenarioEngine
{
  enum NextState
  {
    goToNextScenario,
    failedStopRunning,
    successStopRunning,
  };

  class Scenario
  {
  public:
    virtual ~Scenario() {}
    virtual NextState run(int argc, test_arg_char* argv[], int& errorCode) = 0;
    virtual void  showDescription(const wchar_t* startAppName) = 0;
  };

  typedef OdSharedPtr<Scenario> ScenarioPtr;

  enum RunScenariosResult
  {
    runSuccess,
    runFailed,
    nobodyRun,
  };

  static RunScenariosResult runScenarios(std::vector<OdSharedPtr<Scenario> >& scenarioCollection, int argc, test_arg_char* argv[], int& errorCode)
  {
    RunScenariosResult  runningResult = nobodyRun;
    std::vector<OdSharedPtr<Scenario> >::iterator scenarioIterator = scenarioCollection.begin();
    
    for (; scenarioIterator != scenarioCollection.end(); ++scenarioIterator)
    {
      NextState sceneState = (*scenarioIterator)->run(argc, argv, errorCode);

      if (sceneState == goToNextScenario)
      {
        continue;
      }

      if (sceneState == failedStopRunning)
      {
        runningResult = runFailed;
        break;
      }
      
      if (sceneState == successStopRunning)
      {
        runningResult = runSuccess;
        break;
      }
    }

    return runningResult;
  }

  static void showScenariosInfo(std::vector<OdSharedPtr<Scenario> >& scenarioCollection, const wchar_t* startAppName)
  {
    std::vector<OdSharedPtr<Scenario> >::iterator scenarioIterator = scenarioCollection.begin();

    printConsoleString(L"Not enough parameters, or some parameters are wrong.\r\n");
    printConsoleString(L"Command line examples:\r\n\r\n");

    for (; scenarioIterator != scenarioCollection.end(); ++scenarioIterator)
    {
      (*scenarioIterator)->showDescription(startAppName);
    }
  }

}

#endif
