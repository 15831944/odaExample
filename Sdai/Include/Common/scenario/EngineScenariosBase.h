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

#ifndef _SCENARIO_ENGINE_BASE_SCENARIOS_H_
#define _SCENARIO_ENGINE_BASE_SCENARIOS_H_

#include "ScenarioEngineCmdLine.h"
#include "EngineScenario.h"

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices, class TDataHandler>
  class ScenarioBase
    : public Scenario
  {
  public:
    ScenarioBase(TDataHandler& testDataHandler)
      : m_dataHandler(testDataHandler)
    {
    }

  protected:
    TDataHandler&  m_dataHandler;
  };
}

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices, class TDataHandler>
  class ScenarioGetScenarioNamesBase
    : public ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>
  {
  public:
    ScenarioGetScenarioNamesBase(TDataHandler& testDataHandler)
      : ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>(testDataHandler)
    {
    }

    virtual NextState run(int argc, test_arg_char* argv[], int& errorCode)
    {
      if (!parseParams(argc, argv))
      {
        return goToNextScenario;
      }

      printConsoleString(L"The next tests are registered:\n\n", ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>::m_dataHandler.getScenariosCount());
      
      for (unsigned int dataIndex = 1; dataIndex < ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>::m_dataHandler.getScenariosCount(); ++dataIndex)
      {
        testDataOutput(dataIndex);
      }

      printConsoleString(L"\nList completed.\n", ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>::m_dataHandler.getScenariosCount());
      return successStopRunning;
    }


  private:
    virtual bool parseParams(int argc, test_arg_char* argv[]) = 0;
    virtual void testDataOutput(unsigned int dataIndex) = 0;
  };
}

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices, class TOdScenarioEngineInitializer, class TDataHandler>
  class ScenarioRunByNumberBase
    : public ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>
  {
  public:
    ScenarioRunByNumberBase(TDataHandler& testDataHandler)
      : ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>(testDataHandler)
    {
    }

    NextState run(int argc, test_arg_char* argv[], int& errorCode)
    {
      OdString pathToExecutableFile;
      OdString pathToScenarioFolder;
      int      subScenarioNumber = 0;

      if (!parseParams(argc, argv, pathToExecutableFile, pathToScenarioFolder, subScenarioNumber))
      {
        return goToNextScenario;
      }

      if (subScenarioNumber == 0)
      {
        return goToNextScenario;
      }

      TOdScenarioEngineInitializer odInitializer;
      THostAppServices& appService = odInitializer.getAppService();
      appService.setCurrentDirectoryByFile(pathToExecutableFile);
      appService.setBugDirectory(pathToScenarioFolder);

      errorCode = ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>::m_dataHandler.runScenario(subScenarioNumber, appService);

      if (errorCode)
      {
        return failedStopRunning;
      }

      return successStopRunning;
    }

  protected:
    virtual bool parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToScenarioFolder, int& subScenarioNumber) = 0;
  };
}


namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices, class TOdScenarioEngineInitializer, class TDataHandler>
  class ScenarioRunByNameBase
    : public ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>
  {
  public:
    ScenarioRunByNameBase(TDataHandler& testDataHandler)
      : ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>(testDataHandler)
    {
    }

    NextState run(int argc, test_arg_char* argv[], int& errorCode)
    {
      OdString pathToExecutableFile;
      OdString pathToScenarioFolder;
      OdString testName;

      if (!parseParams(argc, argv, pathToExecutableFile, pathToScenarioFolder, testName))
      {
        return goToNextScenario;
      }
  
      const ScenarioDataType* pScenarioData = ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>::m_dataHandler.getScenarioDataByName(testName);
      if (pScenarioData == NULL)
      {
        return goToNextScenario;
      }

      TOdScenarioEngineInitializer odInitializer;
      THostAppServices& appService = odInitializer.getAppService();
      appService.setCurrentDirectoryByFile(pathToExecutableFile);
      appService.setBugDirectory(pathToScenarioFolder);

      errorCode = ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>::m_dataHandler.runScenario(*const_cast<ScenarioDataType*>(pScenarioData), appService);

      if (errorCode)
      {
        return failedStopRunning;
      }

      return successStopRunning;
    }

  private:
    virtual bool parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToScenarioFolder, OdString& testName) = 0;
  };
}

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices, class TOdScenarioEngineInitializer, class TDataHandler>
  class ScenarioRunAllBase
    : public ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>
  {
  public:
    ScenarioRunAllBase(TDataHandler& testDataHandler)
      : ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>(testDataHandler)
    {
    }

    NextState run(int argc, test_arg_char* argv[], int& errorCode)
    {
      OdString pathToExecutableFile;
      OdString pathToScenarioFolder;
      
      if (!parseParams(argc, argv, pathToExecutableFile, pathToScenarioFolder))
      {
        return goToNextScenario;
      }

      TOdScenarioEngineInitializer odInitializer;
      THostAppServices& appService = odInitializer.getAppService();
      appService.setCurrentDirectoryByFile(pathToExecutableFile);
      appService.setBugDirectory(pathToScenarioFolder);

      errorCode = ScenarioBase<ScenarioDataType, THostAppServices, TDataHandler>::m_dataHandler.runAllScenarios(appService);

      if (errorCode)
      {
        return failedStopRunning;
      }

      return successStopRunning;
    }

  private:
    virtual bool parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToScenarioFolder) = 0;
  };
}

#endif
