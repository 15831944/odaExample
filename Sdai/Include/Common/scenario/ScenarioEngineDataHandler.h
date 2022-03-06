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

#ifndef _SCENARIO_ENGINE_DATA_HANDLER_H_
#define _SCENARIO_ENGINE_DATA_HANDLER_H_

#include "ScenarioEngineBaseDataHandler.h"
#include "ScenarioEngineUtils.h"

#define BASE_EXECUTION_COUNT 5

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices>
  class ScenarioDataHandler
    : public BaseDataHandler<ScenarioDataType, THostAppServices>
  {
  public:
    ScenarioDataHandler(ScenarioDataType* testDataArray, unsigned int testDataArrayLength);
    virtual ~ScenarioDataHandler();

    unsigned int getScenarioRunsNumber(unsigned int testNumber) const;

    int runScenario(unsigned int subScenarioNumber, THostAppServices& hostAppService);
    int runScenario(unsigned int testNumber, unsigned int runNumber, THostAppServices& hostAppService);
    
    using BaseDataHandler<ScenarioDataType, THostAppServices>::runScenario;

  protected:
    virtual int runScenarioImpl(const ScenarioDataType& testData, unsigned int runNumber, THostAppServices& hostAppService) = 0;
    virtual int runScenarioImpl(const ScenarioDataType& testData, THostAppServices& hostAppService);

  };

  template<class ScenarioDataType, class THostAppServices>
  class PerfScenarioDataHandler
    : public ScenarioDataHandler<ScenarioDataType, THostAppServices>
  {
  public:
    PerfScenarioDataHandler(ScenarioDataType* testDataArray, unsigned int testDataArrayLength);
    virtual ~PerfScenarioDataHandler();

    void setPerfIterationsCount(unsigned int perfIterationCount);
    unsigned int getPerfIterationsCount();

  private:
    unsigned int m_perfIterationCount = BASE_EXECUTION_COUNT;

  };
}

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices>
  ScenarioDataHandler<ScenarioDataType, THostAppServices>::ScenarioDataHandler(ScenarioDataType* testDataArray, unsigned int testDataArrayLength)
    : BaseDataHandler<ScenarioDataType, THostAppServices>(testDataArray, testDataArrayLength)
  {
  }

  template<class ScenarioDataType, class THostAppServices>
  ScenarioDataHandler<ScenarioDataType, THostAppServices>::~ScenarioDataHandler()
  {
  }

  template<class ScenarioDataType, class THostAppServices>
  unsigned int  ScenarioDataHandler<ScenarioDataType, THostAppServices>::getScenarioRunsNumber(unsigned int testNumber) const
  {
    if (testNumber >= ScenarioDataHandler<ScenarioDataType, THostAppServices>::m_testDataCollection.size())
    {
      return static_cast<unsigned int> (-1);
    }

    return ScenarioDataHandler<ScenarioDataType, THostAppServices>::m_testDataCollection[testNumber].runsNum;
  }

  template<class ScenarioDataType, class THostAppServices>
  int ScenarioDataHandler<ScenarioDataType, THostAppServices>::runScenario(unsigned int subScenarioNumber, THostAppServices& hostAppService)
  {
    unsigned int  currentScenarioNumber = 0;

    typename std::vector<ScenarioDataType>::iterator nextDataIterator = ScenarioDataHandler<ScenarioDataType, THostAppServices>::m_testDataCollection.begin();
    for (; nextDataIterator != ScenarioDataHandler<ScenarioDataType, THostAppServices>::m_testDataCollection.end(); ++nextDataIterator)
    {
      if ((currentScenarioNumber < subScenarioNumber) &&
        (subScenarioNumber <= currentScenarioNumber + (*nextDataIterator).runsNum))
      {
        return runScenarioImpl(*nextDataIterator, subScenarioNumber - currentScenarioNumber - 1, hostAppService);
      }
      currentScenarioNumber += (*nextDataIterator).runsNum;
    }

    printConsoleString(L"END_OF_TESTS_REACHED\n");
    return 0;
  }

  template<class ScenarioDataType, class THostAppServices>
  int ScenarioDataHandler<ScenarioDataType, THostAppServices>::runScenario(unsigned int testNumber, unsigned int runNumber, THostAppServices& hostAppService)
  {
    if (ScenarioDataHandler<ScenarioDataType, THostAppServices>::m_testDataCollection.size() < testNumber)
    {
      return -1;
    }

    const ScenarioDataType& testData = ScenarioDataHandler<ScenarioDataType, THostAppServices>::m_testDataCollection[testNumber];
    if (testData.runsNum < runNumber)
    {
      return -1;
    }

    return runScenarioImpl(testData, runNumber, hostAppService);
  }

  template<class ScenarioDataType, class THostAppServices>
  int ScenarioDataHandler<ScenarioDataType, THostAppServices>::runScenarioImpl(const ScenarioDataType& testData, THostAppServices& hostAppService)
  {
    int result = 0;
    for (unsigned int runIndex = 0; runIndex < testData.runsNum; ++runIndex)
    {
      int currentResult = runScenarioImpl(testData, runIndex, hostAppService);
      if (currentResult != 0)
      {
        result = currentResult;
      }
    }

    return result;
  }


  template<class ScenarioDataType, class THostAppServices>
  PerfScenarioDataHandler<ScenarioDataType, THostAppServices>::PerfScenarioDataHandler(ScenarioDataType* testDataArray, unsigned int testDataArrayLength)
    : ScenarioDataHandler<ScenarioDataType, THostAppServices>(testDataArray, testDataArrayLength)
  {
  }

  template<class ScenarioDataType, class THostAppServices>
  PerfScenarioDataHandler<ScenarioDataType, THostAppServices>::~PerfScenarioDataHandler()
  {
  }

  template<class ScenarioDataType, class THostAppServices>
  void PerfScenarioDataHandler<ScenarioDataType, THostAppServices>::setPerfIterationsCount(unsigned int perfIterationCount)
  {
    m_perfIterationCount = perfIterationCount;
  }

  template<class ScenarioDataType, class THostAppServices>
  unsigned int PerfScenarioDataHandler<ScenarioDataType, THostAppServices>::getPerfIterationsCount()
  {
    return m_perfIterationCount;
  }
}

#endif
