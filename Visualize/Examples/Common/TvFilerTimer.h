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

#ifndef OD_TV_FILERTIMER_H
#define OD_TV_FILERTIMER_H

// ODA Platform
#include "OdPerfTimer.h"

class OdTvFilerTimeProfiling;
bool needTimer(OdTvFilerTimeProfiling* pProfileRes);

#if defined(__APPLE__)
#include <chrono>
#include <ctime>
#include <cmath>

struct OdTvStdTimer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
};
#endif

class  OdTvFilerTimer
{
public:
  OdTvFilerTimer(bool bWithTiming);
  ~OdTvFilerTimer();

  void startTotal();
  void startVectorizing();
  void startMisc();
  void endVectorizing();
  void endTotal();
  void endMisc();
  double getTotalTime() const;
  double getVectorizingTime() const;
  double getMiscTime() const;

private:
#if defined(__APPLE__)
    OdTvStdTimer                             m_timerTotal;
    OdTvStdTimer                             m_timerVectorizing;
    OdTvStdTimer                             m_timerMisc;
#else
    OdPerfTimerBase*                         m_timerTotal;
    OdPerfTimerBase*                         m_timerVectorizing;
    OdPerfTimerBase*                         m_timerMisc;
#endif
};


#endif //OD_TV_FILERTIMER_H
