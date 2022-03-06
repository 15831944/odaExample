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
#include "TviLimitManager.h"

#ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
#include "TviMemoryStatus.h"
#endif

TviLimitManager::TviLimitManager()
{
    m_nMemoryLimit = 50 * 1024 * 1024;
}

TviLimitManager::~TviLimitManager(){ }

OdTvLimitManager::MemoryLimitControlResult TviLimitManager::checkMemoryUsage(OdUInt8 nReason, OdUInt64 nApproximateMemoryUsage) const
{
#ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
    m_mutex.lock();
    TviMemoryStatus memStatus;
    if(memStatus.getFreeMemory() > m_nMemoryLimit) {
        m_mutex.unlock();
        return OdTvLimitManager::kPassed;
    }
    m_mutex.unlock();
    return OdTvLimitManager::kNotPassed;
#endif
}

