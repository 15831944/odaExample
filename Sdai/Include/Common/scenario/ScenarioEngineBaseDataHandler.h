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

#ifndef _SCENARIO_ENGINE_DATA_HANDLER_BASE_H_
#define _SCENARIO_ENGINE_DATA_HANDLER_BASE_H_


#include "SharedPtr.h"

#define STL_USING_VECTOR
#include "OdaSTL.h"

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices>
  class BaseDataHandler
  {
  public:
    BaseDataHandler(ScenarioDataType* testDataArray, unsigned int testDataArrayLength);

    virtual ~BaseDataHandler();

    OdString  getScenarioName(unsigned int testNumber) const;
    unsigned int getScenariosCount() const;

    const ScenarioDataType* getScenarioDataByName(const OdString& testName) ;

    int runScenario(const OdString& testName, THostAppServices& hostAppService);
    int runScenario(const ScenarioDataType& testData, THostAppServices& hostAppService);
    int runAllScenarios(THostAppServices& hostAppService);

  protected:
    virtual int runScenarioImpl(const ScenarioDataType& testData, THostAppServices& hostAppService) = 0;
    
  protected:
    std::vector<ScenarioDataType>  m_testDataCollection;
  };
}

namespace ScenarioEngine
{
  template<class ScenarioDataType, class THostAppServices>
  BaseDataHandler<ScenarioDataType, THostAppServices>::BaseDataHandler(ScenarioDataType* testDataArray, unsigned int testDataArrayLength)
  {
    m_testDataCollection.resize(testDataArrayLength);
    std::copy(&testDataArray[0], &testDataArray[testDataArrayLength], m_testDataCollection.begin());
  }

  template<class ScenarioDataType, class THostAppServices>
  BaseDataHandler<ScenarioDataType, THostAppServices>::~BaseDataHandler()
  {
  }

  template<class ScenarioDataType, class THostAppServices>
  OdString  BaseDataHandler<ScenarioDataType, THostAppServices>::getScenarioName(unsigned int testNumber) const
  {
    if (testNumber >= m_testDataCollection.size())
    {
      return "";
    }

    return m_testDataCollection[testNumber].testName;
  }

  template<class ScenarioDataType, class THostAppServices>
  unsigned int  BaseDataHandler<ScenarioDataType, THostAppServices>::getScenariosCount() const
  { 
    return static_cast<unsigned int>(m_testDataCollection.size());
  }

  template<class ScenarioDataType, class THostAppServices>
  const ScenarioDataType* BaseDataHandler<ScenarioDataType, THostAppServices>::getScenarioDataByName(const OdString& testName)  
  {
    if (testName.isEmpty())
    {
      return NULL;
    }

    typename std::vector<ScenarioDataType>::iterator nextDataIterator = m_testDataCollection.begin();
    for (; nextDataIterator != m_testDataCollection.end(); ++nextDataIterator)
    {
      if (!testName.iCompare((*nextDataIterator).testName))
      {
        return &(*nextDataIterator);
      }
    }

    return NULL;
  }

  template<class ScenarioDataType, class THostAppServices>
  int BaseDataHandler<ScenarioDataType, THostAppServices>::runScenario(const OdString& testName, THostAppServices& hostAppService)
  {
    if (testName.isEmpty())
    {
      return false;
    }

    typename std::vector<ScenarioDataType>::iterator nextDataIterator = m_testDataCollection.begin();
    for (; nextDataIterator != m_testDataCollection.end(); ++nextDataIterator)
    {
      if ((*nextDataIterator).testName == testName)
      {
        return runScenario(*nextDataIterator, hostAppService);
      }
    }

    return -1;
  }

  template<class ScenarioDataType, class THostAppServices>
  int BaseDataHandler<ScenarioDataType, THostAppServices>::runScenario(const ScenarioDataType& testData, THostAppServices& hostAppService)
  {
    return runScenarioImpl(testData, hostAppService);
  }

  template<class ScenarioDataType, class THostAppServices>
  int BaseDataHandler<ScenarioDataType, THostAppServices>::runAllScenarios(THostAppServices& hostAppService)
  {
    int result = 0;

    typename std::vector<ScenarioDataType>::iterator nextDataIterator = m_testDataCollection.begin();
    for (; nextDataIterator != m_testDataCollection.end(); ++nextDataIterator)
    {
      int currentResult = runScenario(*nextDataIterator, hostAppService);
      if (currentResult != 0)
      {
        result = currentResult;
      }
    }

    return result;
  }
}

#endif
