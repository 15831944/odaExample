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

#ifndef _EX_NWHOSTAPPSERVICES_H_
#define _EX_NWHOSTAPPSERVICES_H_

#include "NwHostAppServices.h"

// Auxiliary function to display different messages
void oddgPrintConsoleString(const wchar_t* fmt, ...);


/** \details
  <group Nw_Extension_Classes>

  This class implements the progress meter for a DGN application.  
*/
class OdExNwHostAppProgressMeter : public OdDbHostAppProgressMeter
{
public:
  OdExNwHostAppProgressMeter();

  // OdDbHostAppProgressMeter overridden
  virtual void start(const OdString& displayString = OdString::kEmpty);
  virtual void stop();
  virtual void meterProgress();
  virtual void setLimit(int max);

  /** \details
    Controls the display of this progress meter.
    \param disable [in]  Disables this progress meter. 
  */
  void disableOutput(bool disable) { m_disableOutput = disable; }

  /** \details
    Sets the prefix for this progress meter.
    \param prefix [in]  Prefix for this progress meter.
  */
  void setPrefix(const OdString& prefix) { m_Prefix = prefix; }

private:
  OdString  m_Prefix;
  long      m_MeterLimit;
  long      m_MeterCurrent;
  long      m_MeterOld;
  bool      m_disableOutput;
};

/** \details
  This class implements platform-dependent operations and progress metering.

  <group Nw_Extension_Classes> 
*/
class OdExNwHostAppServices : public OdNwHostAppServices
{
public:
  OdExNwHostAppServices();

  // OdNwHostAppServices overridden
  virtual bool ttfFileNameByDescriptor(const OdTtfDescriptor& description, OdString& filename);
  virtual OdDbHostAppProgressMeter* newProgressMeter();
  virtual void releaseProgressMeter(OdDbHostAppProgressMeter* pProgressMeter);

  /** \details
    Controls the display of this progress meter.
    \param disable [in]  Disables this progress meter. 
  */
  void disableProgressMeterOutput(bool disable) { m_progressMeter.disableOutput(disable); }

private:
  OdExNwHostAppProgressMeter m_progressMeter;
};

#endif  // _EX_NWHOSTAPPSERVICES_H_

