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

#ifndef _EXAMPLE_SCENARIOS_IMPL_H_
#define _EXAMPLE_SCENARIOS_IMPL_H_

#include "ExampleScenariosBase.h"
#include "scenario/ScenarioEngineDataHandler.h"

namespace ExampleScenario
{
  template<class ScenarioDataType, class SHostAppServices>
  class ExampleScenarioGetNames
    : public ScenarioGetNamesBase<ScenarioDataType, SHostAppServices, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices> >
  {
  public:
    ExampleScenarioGetNames(ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices>& scenarioDataHandler)
      : ScenarioGetNamesBase<ScenarioDataType, SHostAppServices, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices> >(scenarioDataHandler)
    {
    }

  private:
    virtual bool parseParams(int argc, test_arg_char* argv[]) 
    {
      OdString pathToExecutableFile;
      OdString keyword;

      ScenarioEngine::CmdParseRule parserRule(ScenarioEngine::cmdParamStrictCompliance);
      parserRule << pathToExecutableFile;
      parserRule << keyword;

      return parserRule.parse(argc, argv) && !keyword.iCompare("GET_SCENARIO_NAMES");
    }

    virtual void showDescription(const wchar_t* startAppName)
    {
      ScenarioEngine::printConsoleString(L"%s GET_SCENARIO_NAMES\n", startAppName);
      ScenarioEngine::printConsoleString(L"GET_SCENARIO_NAMES is a keyword. Names of all available scenarios should be printed.\n");
      ScenarioEngine::printConsoleString(L"\n");
    }

    virtual void testDataOutput(unsigned int dataIndex)
    {
      ScenarioEngine::printConsoleString(L"%ls : %d \n",
                         ScenarioGetNamesBase<ScenarioDataType, SHostAppServices, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices> >::m_dataHandler.getScenarioName(dataIndex).c_str(),
                         ScenarioGetNamesBase<ScenarioDataType, SHostAppServices, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices> >::m_dataHandler.getScenarioRunsNumber(dataIndex));
    }
  };
}


namespace ExampleScenario
{
  template<class ScenarioDataType, class SHostAppServices, class TOdScenarioEngineInitializer>
  class ExampleScenarioRunByNumber
    : public ScenarioRunByNumberBase<ScenarioDataType, SHostAppServices, TOdScenarioEngineInitializer, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices> >
  {
  public:
    ExampleScenarioRunByNumber(ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices>& scenarioDataHandler)
      : ScenarioRunByNumberBase<ScenarioDataType, SHostAppServices, TOdScenarioEngineInitializer, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices> >(scenarioDataHandler)
    {
    }


  protected:
    virtual void showDescription(const wchar_t* startAppName)
    {
      ScenarioEngine::printConsoleString(L"%s <NUMBER> <FILENAME>\n", startAppName);
      ScenarioEngine::printConsoleString(L"NUMBER - index of scenario in scenario collection. Single scenario run.\n");
      ScenarioEngine::printConsoleString(L"FILENAME - name of resulting file.\n");
      ScenarioEngine::printConsoleString(L"\n");

    }

    virtual bool parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToResultingFile, int& subScenarioNumber)
    {
      ScenarioEngine::CmdParseRule parserRule(ScenarioEngine::cmdParamStrictCompliance);
      parserRule << pathToExecutableFile;
      parserRule << subScenarioNumber;
      parserRule << pathToResultingFile;

      return parserRule.parse(argc, argv);
    }
  };
}

namespace ExampleScenario
{
  template<class ScenarioDataType, class SHostAppServices, class TOdScenarioEngineInitializer>
  class ExampleScenarioRunByName
    : public ScenarioRunByNameBase<ScenarioDataType, SHostAppServices, TOdScenarioEngineInitializer,ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices> >
  {
  public:
    ExampleScenarioRunByName(ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices>& scenarioDataHandler)
      : ScenarioRunByNameBase<ScenarioDataType, SHostAppServices, TOdScenarioEngineInitializer,ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices> >(scenarioDataHandler)
    {
    }

    virtual bool parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToResultingFile, OdString& testName)
    {
      ScenarioEngine::CmdParseRule parserRule(ScenarioEngine::cmdParamStrictCompliance);
      parserRule << pathToExecutableFile;
      parserRule << testName;
      parserRule << pathToResultingFile;

      return parserRule.parse(argc, argv) && !testName.isEmpty();
    }
    
    virtual void showDescription(const wchar_t* startAppName)
    {
      ScenarioEngine::printConsoleString(L"%s <SCENARIO> <FILENAME>\n", startAppName);
      ScenarioEngine::printConsoleString(L"SCENARIO - name of scenario in scenario collection. Single scenario run.\n");
      ScenarioEngine::printConsoleString(L"FILENAME - name of resulting file.\n");
      ScenarioEngine::printConsoleString(L"\n");
    }
  };
}

namespace ExampleScenario
{
  template<class ScenarioDataType, class SHostAppServices, class TOdScenarioEngineInitializer>
  class ExampleScenarioRunAll
    : public ScenarioRunAllBase<ScenarioDataType, SHostAppServices, TOdScenarioEngineInitializer, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices> >
  {
  public:
    ExampleScenarioRunAll(ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices>& scenarioDataHandler)
      : ScenarioRunAllBase<ScenarioDataType, SHostAppServices, TOdScenarioEngineInitializer, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, SHostAppServices> >(scenarioDataHandler)
    {
    }

  private:
    virtual bool parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToResultingFolder)
    {
      OdString keyword;

      ScenarioEngine::CmdParseRule parserRule(ScenarioEngine::cmdParamStrictCompliance);
      parserRule << pathToExecutableFile;
      parserRule << keyword;
      parserRule << pathToResultingFolder;

      return parserRule.parse(argc, argv) && !keyword.iCompare("ALL");
    }

    virtual void showDescription(const wchar_t* startAppName)
    {
      ScenarioEngine::printConsoleString(L"%s ALL <PATH>\n", startAppName);
      ScenarioEngine::printConsoleString(L"ALL is a keyword. Run all scenarios from scenario collection one by one (not safe way).\n");
      ScenarioEngine::printConsoleString(L"PATH - path to folder with resulting files.\n");
      ScenarioEngine::printConsoleString(L"\n");
    }

  };
}

#endif //_EXAMPLE_SCENARIOS_IMPL_H_
