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

// ODA Platform
#include "OdaCommon.h"

#include "TvFilerTimer.h"

bool needTimer(OdTvFilerTimeProfiling* pProfileRes)
{
  //check that time profiling is need
  bool bUseTimeProfiling = false;
  if (pProfileRes)
    bUseTimeProfiling = true;

  return bUseTimeProfiling;
}

//***************************************************************************//
// 'OdTvFilerTimer' methods implementation
//***************************************************************************//

OdTvFilerTimer::OdTvFilerTimer(bool bWithTiming)
{
#if !defined(__APPLE__)
  if (bWithTiming)
  {
    m_timerTotal = OdPerfTimerBase::createTiming();
    m_timerVectorizing = OdPerfTimerBase::createTiming();
    m_timerMisc = OdPerfTimerBase::createTiming();
  }
  else
  {
    m_timerTotal = NULL;
    m_timerVectorizing = NULL;
    m_timerMisc = NULL;
  }
#endif
}

OdTvFilerTimer::~OdTvFilerTimer()
{
#if !defined(__APPLE__)
  if (m_timerTotal)
  {
    OdPerfTimerBase::destroyTiming(m_timerTotal);
    m_timerTotal = NULL;
  }

  if (m_timerVectorizing)
  {
    OdPerfTimerBase::destroyTiming(m_timerVectorizing);
    m_timerVectorizing = NULL;
  }

  if (m_timerMisc)
  {
    OdPerfTimerBase::destroyTiming(m_timerMisc);
    m_timerMisc = NULL;
  }
#endif
}

void OdTvFilerTimer::startTotal()
{
#if defined(__APPLE__)
    m_timerTotal.start = std::chrono::high_resolution_clock::now();
#else
  if (m_timerTotal)
    m_timerTotal->start();
#endif
}

void OdTvFilerTimer::startVectorizing()
{
#if defined(__APPLE__)
    m_timerVectorizing.start = std::chrono::high_resolution_clock::now();
#else
  if (m_timerVectorizing)
    m_timerVectorizing->start();
#endif
}

void OdTvFilerTimer::startMisc()
{
#if defined(__APPLE__)
    m_timerMisc.start = std::chrono::high_resolution_clock::now();
#else
  if (m_timerMisc)
    m_timerMisc->start();
#endif
}

void OdTvFilerTimer::endVectorizing()
{
#if defined(__APPLE__)
    m_timerVectorizing.end = std::chrono::high_resolution_clock::now();
#else
  if (m_timerVectorizing)
    m_timerVectorizing->stop();
#endif
}

void OdTvFilerTimer::endTotal()
{
#if defined(__APPLE__)
    m_timerTotal.end = std::chrono::high_resolution_clock::now();
#else
  if (m_timerTotal)
    m_timerTotal->stop();
#endif
}

void OdTvFilerTimer::endMisc()
{
#if defined(__APPLE__)
    m_timerMisc.end = std::chrono::high_resolution_clock::now();
#else
  if (m_timerMisc)
    m_timerMisc->stop();
#endif
}

double OdTvFilerTimer::getTotalTime() const
{
#if defined(__APPLE__)
    return std::chrono::duration<double>( m_timerTotal.end - m_timerTotal.start ).count();
#else
  if (m_timerTotal)
    return m_timerTotal->countedSec();
  else
    return 0.;
#endif
}

double OdTvFilerTimer::getVectorizingTime() const
{
#if defined(__APPLE__)
    return std::chrono::duration<double>( m_timerVectorizing.end - m_timerVectorizing.start ).count();
#else
  if (m_timerVectorizing)
    return m_timerVectorizing->countedSec();
  else
    return 0.;
#endif
}

double OdTvFilerTimer::getMiscTime() const
{
#if defined(__APPLE__)
    return std::chrono::duration<double>( m_timerMisc.end - m_timerMisc.start ).count();
#else
  if (m_timerMisc)
    return m_timerMisc->countedSec();
  else
    return 0.;
#endif
}
