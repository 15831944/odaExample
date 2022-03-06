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

#ifndef _SCENARIO_ENGINE_SCENARIOS_FOR_PERF_H_
#define _SCENARIO_ENGINE_SCENARIOS_FOR_PERF_H_

#include "EngineScenariosBase.h"

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices>
  class PerfScenarioGetScenarioNames
    : public ScenarioGetScenarioNamesBase<ScenarioDataType, THostAppServices, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, THostAppServices> >
  {
  public:
    PerfScenarioGetScenarioNames(ScenarioDataHandler<ScenarioDataType, THostAppServices>& testDataHandler)
      : ScenarioGetScenarioNamesBase<ScenarioDataType, THostAppServices, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, THostAppServices> >(testDataHandler)
    {
    }


    virtual void  showDescription(const wchar_t* startAppName)
    {
      printConsoleString(L"%s GET_TEST_NAMES PERFTEST\n", startAppName);
      printConsoleString(L"GET_TEST_NAMES is a keyword. Names of all available performance tests should be printed.\n");
      printConsoleString(L"PERFTEST is a keyword. Define performance mode.\n");
      printConsoleString(L"\n");
    }

  private:
    virtual bool parseParams(int argc, test_arg_char* argv[])
    {
      OdString pathToExecutableFile;
      OdString keyword;
      OdString keywordPerf;
      int iterationCount = 0;

      CmdParseRule  parserRule(cmdParamStrictCompliance, 3);
      parserRule << pathToExecutableFile;
      parserRule << keyword;
      parserRule << keywordPerf;
      parserRule << iterationCount;

      return (parserRule.parse(argc, argv) &&
        !keywordPerf.iCompare("PERFTEST") &&
        !keyword.iCompare("GET_TEST_NAMES"));
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
  class PerfScenarioRunByNumber
    : public ScenarioRunByNumberBase<ScenarioDataType, THostAppServices, TOdScenarioEngineInitializer, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, THostAppServices> >
  {
  public:
    PerfScenarioRunByNumber(ScenarioDataHandler<ScenarioDataType, THostAppServices>& testDataHandler)
      : ScenarioRunByNumberBase<ScenarioDataType, THostAppServices, TOdScenarioEngineInitializer, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, THostAppServices> >(testDataHandler)
    {
    }


  protected:
    virtual void  showDescription(const wchar_t* startAppName)
    {
      printConsoleString(L"%s <TESTNAME> <PATH> PERFTEST [ITERATION_COUNT]\n", startAppName);
      printConsoleString(L"NUMBER - index of test(subtest) in test collection. Single test run..\n");
      printConsoleString(L"PATH - path to folder with support files.\n");
      printConsoleString(L"PERFTEST is a keyword. Define performance mode.\n");
      printConsoleString(L"ITERATION_COUNT - optional parameter. Common iteration count for all preformance tests. If it is not defined or equal -1, iteration count would be default for each test.\n");
      printConsoleString(L"\n");

    }

    virtual bool  parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToScenarioFolder, int& subScenarioNumber)
    {
      OdString keywordPerf;
      int iterationCount = 0;

      CmdParseRule  parserRule(cmdParamPartCompliance, 4);
      parserRule << pathToExecutableFile;
      parserRule << subScenarioNumber;
      parserRule << pathToScenarioFolder;
      parserRule << keywordPerf;
      parserRule << iterationCount;

      if (!parserRule.parse(argc, argv) ||
          keywordPerf.iCompare("PERFTEST"))
      {
        return false;
      }

      if (iterationCount > 0)
      {
        ScenarioEngine::PerfScenarioDataHandler<ScenarioDataType, THostAppServices>* handler = dynamic_cast<ScenarioEngine::PerfScenarioDataHandler<ScenarioDataType, THostAppServices>*>(&(this->m_dataHandler));
        if (handler == NULL)
        {
          ODA_ASSERT(false);
          return false;
        }
        handler->setPerfIterationsCount(iterationCount);
      }
      return true;
    }
  };
}



namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices, class TOdScenarioEngineInitializer>
  class PerfScenarioRunByName
    : public ScenarioRunByNameBase<ScenarioDataType, THostAppServices, TOdScenarioEngineInitializer, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, THostAppServices> >
  {
  public:
    PerfScenarioRunByName(ScenarioDataHandler<ScenarioDataType, THostAppServices>& testDataHandler)
      : ScenarioRunByNameBase<ScenarioDataType, THostAppServices, TOdScenarioEngineInitializer, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, THostAppServices> >(testDataHandler)
    {
    }

    virtual void  showDescription(const wchar_t* startAppName)
    {
      printConsoleString(L"%s <TESTNAME> <PATH> PERFTEST [ITERATION_COUNT]\n", startAppName);
      printConsoleString(L"TESTNAME - name of performance test in test collection. Single performance test run.\n");
      printConsoleString(L"PATH - path to folder with support files.\n");
      printConsoleString(L"PERFTEST is a keyword. Define performance mode.\n");
      printConsoleString(L"ITERATION_COUNT - optional parameter. Common iteration count for all preformance tests. If it is not defined or equal -1, iteration count would be default for each test.\n");
      printConsoleString(L"\n");
    }

  private:
    virtual bool  parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToScenarioFolder, OdString& testName)
    {
      OdString keywordPerf;
      int iterationCount = 0;

      CmdParseRule  parserRule(cmdParamPartCompliance, 4);
      parserRule << pathToExecutableFile;
      parserRule << testName;
      parserRule << pathToScenarioFolder;
      parserRule << keywordPerf;
      parserRule << iterationCount;

      if (!parserRule.parse(argc, argv) || 
          keywordPerf.iCompare("PERFTEST") || 
          testName.isEmpty())
      {
        return false;
      }
      
      if (iterationCount > 0)
      {
        ScenarioEngine::PerfScenarioDataHandler<ScenarioDataType, THostAppServices>* handler = dynamic_cast<ScenarioEngine::PerfScenarioDataHandler<ScenarioDataType, THostAppServices>*>(&(this->m_dataHandler));
        if (handler == NULL)
        {
          ODA_ASSERT(false);
          return false;
        }
        handler->setPerfIterationsCount(iterationCount);
      }
      return true;
    }

  };
}

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices, class TOdScenarioEngineInitializer>
  class PerfScenarioRunAll
    : public ScenarioRunAllBase<ScenarioDataType, THostAppServices, TOdScenarioEngineInitializer, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, THostAppServices> >
  {
  public:
    PerfScenarioRunAll(ScenarioDataHandler<ScenarioDataType, THostAppServices>& testDataHandler)
      : ScenarioRunAllBase<ScenarioDataType, THostAppServices, TOdScenarioEngineInitializer, ScenarioEngine::ScenarioDataHandler<ScenarioDataType, THostAppServices> >(testDataHandler)
    {
    }

    virtual void  showDescription(const wchar_t* startAppName)
    {
      printConsoleString(L"%s ALL <PATH> PERFTEST [ITERATION_COUNT]\n", startAppName);
      printConsoleString(L"ALL is a keyword. Run all tests from performance test collection one by one (not safe way).\n");
      printConsoleString(L"PATH - path to folder with support files.\n");
      printConsoleString(L"PERFTEST is a keyword. Define performance mode.\n");
      printConsoleString(L"ITERATION_COUNT - optional parameter. Common iteration count for all preformance tests. If it is not defined or equal -1, iteration count would be default for each test.\n");
      printConsoleString(L"\n");
    }

  private:
    virtual bool  parseParams(int argc, test_arg_char* argv[], OdString& pathToExecutableFile, OdString& pathToScenarioFolder)
    {
      OdString  testAllKeyword;
      OdString  keywordPerf;
      int iterationCount = 0;


      CmdParseRule  parserRule(cmdParamPartCompliance, 4);
      parserRule << pathToExecutableFile;
      parserRule << testAllKeyword;
      parserRule << pathToScenarioFolder;
      parserRule << keywordPerf;
      parserRule << iterationCount;

      if (!parserRule.parse(argc, argv) || 
          testAllKeyword.iCompare("ALL") ||
          keywordPerf.iCompare("PERFTEST"))
      {
        return false;
      }

      if (iterationCount > 0)
      {
        ScenarioEngine::PerfScenarioDataHandler<ScenarioDataType, THostAppServices>* handler = dynamic_cast<ScenarioEngine::PerfScenarioDataHandler<ScenarioDataType, THostAppServices>*>(&(this->m_dataHandler));
        if (handler == NULL)
        {
          ODA_ASSERT(false);
          return false;
        }
        handler->setPerfIterationsCount(iterationCount);
      }
      return true;
    }
  };
}

#endif
