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

#include "OdaCommon.h"
#include "ExPrintConsole.h"
#include "Gs/Gs.h"
#include "Gi/TtfDescriptor.h"
#include "RxObjectImpl.h"
#include "OdFontServices.h"
#include "RxSysRegistry.h"

#include "IfcCore.h"
#include "ExIfcHostAppServices.h"

//----------------------------------------------------------
//
// OdExIfcHostAppServices
//
//----------------------------------------------------------
OdExIfcHostAppServices::OdExIfcHostAppServices() 
{
}

OdDbHostAppProgressMeter* OdExIfcHostAppServices::newProgressMeter()
{
  return &m_progressMeter;
}

void OdExIfcHostAppServices::releaseProgressMeter(OdDbHostAppProgressMeter* pProgressMeter)
{
}

OdExIfcHostAppProgressMeter::OdExIfcHostAppProgressMeter()
  : m_MeterLimit(0)
  , m_MeterCurrent(0)
  , m_MeterOld(0)
  , m_disableOutput(false)
{
}

void OdExIfcHostAppProgressMeter::start(const OdString& displayString)
{
  if (!m_disableOutput)
  {
#ifndef _WIN32_WCE
    odPrintConsoleString(L"%ls------- Started %ls\n", m_Prefix.c_str(), displayString.c_str());
#endif
  }
}

void OdExIfcHostAppProgressMeter::stop()
{
  if (!m_disableOutput)
  {
#ifndef _WIN32_WCE
    odPrintConsoleString(L"%ls------- Stopped\n", m_Prefix.c_str());
#endif
  }
}

void OdExIfcHostAppProgressMeter::meterProgress()
{
  m_MeterCurrent++;
  if (!m_disableOutput)
  {
    double  f1, f2;

    f1 = (double)m_MeterCurrent / m_MeterLimit * 100;
    f2 = (double)m_MeterOld / m_MeterLimit * 100;
    if ((f1 - f2) > 0.7)
    {
#ifndef _WIN32_WCE
      odPrintConsoleString(L"%lsProgress: %2.2lf%%\n", m_Prefix.c_str(), f1);
#endif
      m_MeterOld = m_MeterCurrent;
    }
  }
}

void OdExIfcHostAppProgressMeter::setLimit(int max)
{
  m_MeterLimit = max;
  m_MeterCurrent = 0;
  m_MeterOld = 0;
  if (!m_disableOutput)
  {
#ifndef _WIN32_WCE
    odPrintConsoleString(L"%lsMeter Limit: %d\n", m_Prefix.c_str(), max);
#endif
  }
}
