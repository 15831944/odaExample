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

#ifndef _SCENARIO_ENGINE_SCENARIOS_FOR_TEST_H_
#define _SCENARIO_ENGINE_SCENARIOS_FOR_TEST_H_

#include "EngineScenariosBase.h"
#include "ScenarioEngineDataHandler.h"

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices>
  class ScenarioGetScenarioNames
    : public ScenarioGetScenarioNamesBase<ScenarioDataType, THostAppServices, ScenarioDataHandler<ScenarioDataType, THostAppServices> >
  {
  public:
    ScenarioGetScenarioNames(ScenarioDataHandler<ScenarioDataType, THostAppServices>& testDataHandler)
      : ScenarioGetScenarioNamesBase<ScenarioDataType, THostAppServices, ScenarioDataHandler<ScenarioDataType, THostAppServices> >(testDataHandler)
    {
    }

  private:
    virtual bool parseParams(int argc, test_arg_char* argv[]) 
    {
      OdString pathToExecutableFile;
      OdString keyword;

      CmdParseRule  parserRule(cmdParamStrictCompliance);
      parserRule << pathToExecutableFile;
      parserRule << keyword;

      return parserRule.parse(argc, argv) && !keyword.iCompare("GET_TEST_NAMES");
    }

    virtual void  showDescription(const wchar_t* startAppName)
    {
      printConsoleString(L"%s GET_TEST_NAMES\n", startAppName);
      printConsoleString(L"GET_TEST_NAMES is a keyword. Names of all available tests should be printed.\n");
      printConsoleString(L"\n");
    }

    virtual void testDataOutput(unsigned int dataIndex)
    {
      printConsoleString(L"%ls : %d \n", 
                         ScenarioGetScenarioNamesBase<ScenarioDataType, THostAppServices, ScenarioDataHandler<ScenarioDataType, THostAppServices> >::m_dataHandler.getScenarioName(dataIndex).c_str(),
                         ScenarioGetScenarioNamesBase<ScenarioDataType, THostAppServices, ScenarioDataHandler<ScenarioDataType, THostAppServices> >::m_dataHandler.getScenarioRunsNumber(dataIndex));
    }
  };
}


namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices, class TOdScenarioEngineInitializer>
  class ScenarioRunByNumber
    : public ScenarioRunByNumberBase<ScenarioDataType, THostAppServices, TOdScenarioEngineInitializer, ScenarioDataHandler<ScenarioDataType, THostAppServices> >
  {
  public:
    ScenarioRunByNumber(ScenarioDataHandler<ScenarioDataType, THostAppServices>& testDataHandler)
      : ScenarioRunByNumberBase<ScenarioDataType, THostAppServices, TOdScenarioEngineInitializer, ScenarioDataHandler<ScenarioDataType, THostAppServices> >(testDataHandler)
    {
    }


  protected:
    virtual void showDescription(const wchar_t* startAppName)
    {
      printConsoleString(L"%s <NUMBER> <PATH>\n", startAppName);
      printConsoleString(L"NUMBER - index of test(subtest) in test collection. Single test run..\n");
      printConsoleString(L"PATH - path to folder with support files.\n");
      printConsoleString(L"\n");

    }

    virtual bool parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToScenarioFolder, int& subScenarioNumber)
    {
      CmdParseRule  parserRule(cmdParamStrictCompliance);
      parserRule << pathToExecutableFile;
      parserRule << subScenarioNumber;
      parserRule << pathToScenarioFolder;

      return parserRule.parse(argc, argv);
    }
  };
}

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices, class TOdScenarioEngineInitializer>
  class ScenarioRunByName
    : public ScenarioRunByNameBase<ScenarioDataType, THostAppServices, TOdScenarioEngineInitializer,ScenarioDataHandler<ScenarioDataType, THostAppServices> >
  {
  public:
    ScenarioRunByName(ScenarioDataHandler<ScenarioDataType, THostAppServices>& testDataHandler)
      : ScenarioRunByNameBase<ScenarioDataType, THostAppServices, TOdScenarioEngineInitializer,ScenarioDataHandler<ScenarioDataType, THostAppServices> >(testDataHandler)
    {
    }

    virtual bool  parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToScenarioFolder, OdString& testName)
    {
      CmdParseRule  parserRule(cmdParamStrictCompliance);
      parserRule << pathToExecutableFile;
      parserRule << testName;
      parserRule << pathToScenarioFolder;

      return parserRule.parse(argc, argv) && !testName.isEmpty();
    }
    
    virtual void  showDescription(const wchar_t* startAppName)
    {
      printConsoleString(L"%s <TESTNAME> <PATH>\n", startAppName);
      printConsoleString(L"TESTNAME - name of test in test collection. Single test run.\n");
      printConsoleString(L"PATH - path to folder with support files.\n");
      printConsoleString(L"\n");
    }
  };
}

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices, class TOdScenarioEngineInitializer>
  class ScenarioRunAll
    : public ScenarioRunAllBase<ScenarioDataType, THostAppServices, TOdScenarioEngineInitializer, ScenarioDataHandler<ScenarioDataType, THostAppServices> >
  {
  public:
    ScenarioRunAll(ScenarioDataHandler<ScenarioDataType, THostAppServices>& testDataHandler)
      : ScenarioRunAllBase<ScenarioDataType, THostAppServices, TOdScenarioEngineInitializer, ScenarioDataHandler<ScenarioDataType, THostAppServices> >(testDataHandler)
    {
    }

  private:
    virtual bool  parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToScenarioFolder)
    {
      OdString  testAllKeyword;

      CmdParseRule  parserRule(cmdParamStrictCompliance);
      parserRule << pathToExecutableFile;
      parserRule << testAllKeyword;
      parserRule << pathToScenarioFolder;

      return parserRule.parse(argc, argv) && !testAllKeyword.iCompare("ALL");
    }

    virtual void  showDescription(const wchar_t* startAppName)
    {
      printConsoleString(L"%s ALL <PATH>\n", startAppName);
      printConsoleString(L"ALL is a keyword. Run all tests from test collection one by one (not safe way).\n");
      printConsoleString(L"PATH - path to folder with support files.\n");
      printConsoleString(L"\n");
    }

  };
}

#endif
