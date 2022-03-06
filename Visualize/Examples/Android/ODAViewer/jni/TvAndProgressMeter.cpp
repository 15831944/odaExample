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

// ODA
#include "OdaCommon.h"
#include "TvAndProgressMeter.h"

TvAndProgressMeter::TvAndProgressMeter(TvAndJniProgressMeter* pJniProgress) 
    : m_nProgressLimit(100)
    , m_meterLastValue(0)
    , m_nProgressPos(0)
 {
     m_pJniProgress = pJniProgress;
 }

TvAndProgressMeter::~TvAndProgressMeter()
{
    if(m_pJniProgress)
    {
        delete m_pJniProgress;
        m_pJniProgress = NULL;
    }
}

void TvAndProgressMeter::start(const OdString& displayString)
{
    //reset last value
    m_meterLastValue = 0;
    m_nProgressPos = 0;
    if(m_pJniProgress)
    {
        m_pJniProgress->start();
        m_pJniProgress->setProgress(0);
    }
}

void TvAndProgressMeter::stop()
{
    if(m_pJniProgress)
        m_pJniProgress->stop();
}

void TvAndProgressMeter::meterProgress()
{
    m_nProgressPos++;
    int nPercent = (double(m_nProgressPos) / double(m_nProgressLimit)) * 100;
    
    if(m_pJniProgress && nPercent != m_meterLastValue)
        m_pJniProgress->setProgress(nPercent);
    
    m_meterLastValue = nPercent;
    
    return;
}

void TvAndProgressMeter::setLimit(int max)
{
    m_nProgressLimit = max ? max : 1;
}

