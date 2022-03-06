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

#ifndef _SCENARIO_ENGINE_PERF_TICK_SAVER_H_
#define _SCENARIO_ENGINE_PERF_TICK_SAVER_H_

#include "BasePerfTest.h"
#include "OdPerfTimer.h"
#include "ScenarioEngineUtils.h"

namespace ScenarioEngine
{
  
  class  PerformanceCounter
  {
  public:
    inline PerformanceCounter(const OdString&  processName);
    inline ~PerformanceCounter();

    inline void begin();
    inline void end();
    inline void cancel();

    inline void finalResult() const ;

  private:
    PerformanceCounter(const PerformanceCounter&) {}
    PerformanceCounter& operator=(const PerformanceCounter&) {}

  private:
    OdPerfTimerBase*          m_pTimer;
    BaseTicksSaver<int>       m_tickSaver;
    unsigned int              m_ticksCount;
    OdString                  m_processName;
  };

  PerformanceCounter::PerformanceCounter(const OdString&  processName)
    : m_processName(processName)
    , m_ticksCount(0)
  {
    m_pTimer = OdPerfTimerBase::createTiming();
  }

  PerformanceCounter::~PerformanceCounter()
  {
    OdPerfTimerBase::destroyTiming(m_pTimer);
  }

  void PerformanceCounter::begin()
  {
    m_pTimer->start();
  }

  void PerformanceCounter::end()
  {
    m_pTimer->stop();

    int executionTime = m_pTimer->countedMSec();
    m_tickSaver.addNewTick(executionTime);

    printConsoleString(L"duration of iter N %d ", m_ticksCount);

    if (!m_processName.isEmpty())
    {
      printConsoleString(L"of % s process ", m_processName.c_str());
    }

    printConsoleString(L"is %d ms\n", executionTime);
    ++m_ticksCount;

#if defined(ODA_WINDOWS)
    _flushall();
#endif
  }

  void PerformanceCounter::cancel()
  {
    m_pTimer->stop();
    m_pTimer->clear();
  }

  void PerformanceCounter::finalResult() const
  {
    int ticks = m_tickSaver.getAverage(1);
    OdUInt32 nErr = OdUInt32(const_cast<BaseTicksSaver<int>&>(m_tickSaver).error(1, ticks));
    printConsoleString(L"Final average result: %8dms %2d%%\n", ticks, nErr);

#if defined(ODA_WINDOWS)
    _flushall();
#endif
  }

}


#endif
