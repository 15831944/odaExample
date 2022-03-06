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

#ifndef _SCENARIO_ENGINE_PERF_DATA_HANDLER_H_
#define _SCENARIO_ENGINE_PERF_DATA_HANDLER_H_


#include "ScenarioEngineBaseDataHandler.h"

namespace ScenarioEngine
{
  template<class TestDataType, class THostAppServices>
  class PerfDataHandler
    : public BaseDataHandler<TestDataType, THostAppServices>
  {
  public:
    PerfDataHandler(TestDataType* testDataArray, unsigned int testDataArrayLength, unsigned int iterationCount = static_cast<unsigned int>(-1));
    virtual ~PerfDataHandler();

    void setIterationCount(unsigned int iterationCount);
    unsigned int getIterationCount() const;

    int runScenario(unsigned int testNumber, THostAppServices& hostAppService);

    unsigned int calculateDataIterationCount(const TestDataType& testData) const;
    unsigned int calculateDataIterationCount(unsigned int dataIndex) const;

    using BaseDataHandler<TestDataType, THostAppServices>::runScenario;
    using BaseDataHandler<TestDataType, THostAppServices>::runScenarioImpl;

  private:
    unsigned int m_iterationCount;
  };
}

namespace ScenarioEngine
{
  template<class TestDataType, class THostAppServices>
  PerfDataHandler<TestDataType, THostAppServices>::PerfDataHandler(TestDataType* testDataArray, unsigned int testDataArrayLength, unsigned int iterationCount)
    : BaseDataHandler<TestDataType, THostAppServices>(testDataArray, testDataArrayLength)
    , m_iterationCount(iterationCount)
  {
  }

  template<class TestDataType, class THostAppServices>
  PerfDataHandler<TestDataType, THostAppServices>::~PerfDataHandler()
  {
  }

  template<class TestDataType, class THostAppServices>
  void PerfDataHandler<TestDataType, THostAppServices>::setIterationCount(unsigned int iterationCount)
  {
    m_iterationCount = iterationCount;
  }

  template<class TestDataType, class THostAppServices>
  unsigned int PerfDataHandler<TestDataType, THostAppServices>::getIterationCount() const
  {
    return m_iterationCount;
  }

  template<class TestDataType, class THostAppServices>
  inline int PerfDataHandler<TestDataType, THostAppServices>::runScenario(unsigned int testNumber, THostAppServices & hostAppService)
  {
    if (PerfDataHandler<TestDataType, THostAppServices>::m_testDataCollection.size() > testNumber)
    {
      return runScenarioImpl(PerfDataHandler<TestDataType, THostAppServices>::m_testDataCollection[testNumber], hostAppService);
    }

    printConsoleString(L"END_OF_TESTS_REACHED\n");
    return 0;
  }

  template<class TestDataType, class THostAppServices>
  unsigned int PerfDataHandler<TestDataType, THostAppServices>::calculateDataIterationCount(const TestDataType& testData) const
  {
    return m_iterationCount != static_cast<unsigned int>(-1) ? m_iterationCount : testData.ownIterationCount;
  }

  template<class TestDataType, class THostAppServices>
  unsigned int PerfDataHandler<TestDataType, THostAppServices>::calculateDataIterationCount(unsigned int dataIndex) const
  {
    if (PerfDataHandler<TestDataType, THostAppServices>::getTestsCount() <= dataIndex)
    {
      ODA_ASSERT(0);
      return 0;
    }

    return calculateDataIterationCount(PerfDataHandler<TestDataType, THostAppServices>::m_testDataCollection[dataIndex]);
  }


}

#endif
