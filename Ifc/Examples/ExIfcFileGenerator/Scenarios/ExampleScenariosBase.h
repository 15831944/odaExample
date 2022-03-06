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

#ifndef _EXAMPLE_SCENARIOS_H_
#define _EXAMPLE_SCENARIOS_H_

#include "scenario/ScenarioEngineCmdLine.h"
#include "scenario/EngineScenario.h"

namespace ExampleScenario
{
  template<class ScenarioDataType, class SHostAppServices, class SDataHandler>
  class ExampleScenarioBase
    : public ScenarioEngine::Scenario
  {
  public:
    ExampleScenarioBase(SDataHandler& testDataHandler)
      : m_dataHandler(testDataHandler)
    {
    }

  protected:
    SDataHandler& m_dataHandler;
  };
}

namespace ExampleScenario
{
  template<class ScenarioDataType, class SHostAppServices, class SDataHandler>
  class ScenarioGetNamesBase
    : public ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>
  {
  public:
    ScenarioGetNamesBase(SDataHandler& testDataHandler)
      : ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>(testDataHandler)
    {
    }

    virtual ScenarioEngine::NextState run(int argc, test_arg_char* argv[], int& errorCode)
    {
      if (!parseParams(argc, argv))
      {
        return ScenarioEngine::goToNextScenario;
      }

      ScenarioEngine::printConsoleString(L"The next scenarios are registered:\n\n", ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>::m_dataHandler.getScenariosCount());
      
      for (unsigned int dataIndex = 1; dataIndex < ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>::m_dataHandler.getScenariosCount(); ++dataIndex)
      {
        testDataOutput(dataIndex);
      }

      ScenarioEngine::printConsoleString(L"\nList completed.\n", ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>::m_dataHandler.getScenariosCount());
      return ScenarioEngine::successStopRunning;
    }


  private:
    virtual bool parseParams(int argc, test_arg_char* argv[]) = 0;
    virtual void testDataOutput(unsigned int dataIndex) = 0;
  };
}

namespace ExampleScenario
{
  template<class ScenarioDataType, class SHostAppServices, class TOdScenarioEngineInitializer, class SDataHandler>
  class ScenarioRunByNumberBase
    : public ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>
  {
  public:
    ScenarioRunByNumberBase(SDataHandler& testDataHandler)
      : ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>(testDataHandler)
    {
    }

    ScenarioEngine::NextState run(int argc, test_arg_char* argv[], int& errorCode)
    {
      OdString pathToExecutableFile;
      OdString pathToResultingFile;
      int      subScenarioNumber = 0;

      if (!parseParams(argc, argv, pathToExecutableFile, pathToResultingFile, subScenarioNumber))
      {
        return ScenarioEngine::goToNextScenario;
      }

      if (subScenarioNumber == 0)
      {
        return ScenarioEngine::goToNextScenario;
      }

      TOdScenarioEngineInitializer odInitializer;
      SHostAppServices& appService = odInitializer.getAppService();
      appService.setCurrentDirectoryByFile(pathToExecutableFile);
      appService.setFileName(pathToResultingFile);

      errorCode = ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>::m_dataHandler.runScenario(subScenarioNumber, appService);

      if (errorCode)
      {
        return ScenarioEngine::failedStopRunning;
      }

      return ScenarioEngine::successStopRunning;
    }

  protected:
    virtual bool parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToResultingFile, int& subScenarioNumber) = 0;
  };
}


namespace ExampleScenario
{
  template<class ScenarioDataType, class SHostAppServices, class TOdScenarioEngineInitializer, class SDataHandler>
  class ScenarioRunByNameBase
    : public ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>
  {
  public:
    ScenarioRunByNameBase(SDataHandler& testDataHandler)
      : ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>(testDataHandler)
    {
    }

    ScenarioEngine::NextState run(int argc, test_arg_char* argv[], int& errorCode)
    {
      OdString pathToExecutableFile;
      OdString pathToResultingFile;
      OdString testName;

      if (!parseParams(argc, argv, pathToExecutableFile, pathToResultingFile, testName))
      {
        return ScenarioEngine::goToNextScenario;
      }
  
      const ScenarioDataType* pScenarioData = ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>::m_dataHandler.getScenarioDataByName(testName);
      if (pScenarioData == NULL)
      {
        return ScenarioEngine::goToNextScenario;
      }

      TOdScenarioEngineInitializer odInitializer;
      SHostAppServices& appService = odInitializer.getAppService();
      appService.setCurrentDirectoryByFile(pathToExecutableFile);
      appService.setFileName(pathToResultingFile);

      errorCode = ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>::m_dataHandler.runScenario(*const_cast<ScenarioDataType*>(pScenarioData), appService);

      if (errorCode)
      {
        return ScenarioEngine::failedStopRunning;
      }

      return ScenarioEngine::successStopRunning;
    }

  private:
    virtual bool parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToResultingFile, OdString& testName) = 0;
  };
}

namespace ExampleScenario
{
  template<class ScenarioDataType, class SHostAppServices, class TOdScenarioEngineInitializer, class SDataHandler>
  class ScenarioRunAllBase
    : public ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>
  {
  public:
    ScenarioRunAllBase(SDataHandler& testDataHandler)
      : ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>(testDataHandler)
    {
    }

    ScenarioEngine::NextState run(int argc, test_arg_char* argv[], int& errorCode)
    {
      OdString pathToExecutableFile;
      OdString pathToResultingFolder;
      
      if (!parseParams(argc, argv, pathToExecutableFile, pathToResultingFolder))
      {
        return ScenarioEngine::goToNextScenario;
      }

      TOdScenarioEngineInitializer odInitializer;
      SHostAppServices& appService = odInitializer.getAppService();
      appService.setCurrentDirectoryByFile(pathToExecutableFile);
      appService.setBugDirectory(pathToResultingFolder);

      errorCode = ExampleScenarioBase<ScenarioDataType, SHostAppServices, SDataHandler>::m_dataHandler.runAllScenarios(appService);

      if (errorCode)
      {
        return ScenarioEngine::failedStopRunning;
      }

      return ScenarioEngine::successStopRunning;
    }

  private:
    virtual bool parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToResultingFolder) = 0;
  };
}

#endif //_EXAMPLE_SCENARIOS_H_
