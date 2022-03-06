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

#ifndef _EX_PRCHOSTAPPSERVICES_H_
#define _EX_PRCHOSTAPPSERVICES_H_

#include "DbHostAppProgressMeter.h"
#include "AppServices/PrcHostAppServices.h"

/** \details
Auxiliary function to display different messages. 

\param fmt [in] A formatting string for displaying a message. 
*/
void odbmPrintConsoleString(const wchar_t* fmt, ...);


/** \details
This class implements platform specific progress metering within ODA PRC SDK.

\remarks
This class receives progress notifications during various database operations such as loading and saving a .prc file.

Working with an instance of the class should include the following steps:
1. Call the setLimit() method for setting the maximum progress value.
2. Call the start() method to begin progress metering.
3. Call the meterProgress() method each time you need to change the current progress value.
4. Call the stop() method to stop progress metering.

<group PRC_Protocol_Extensions_Classes>
*/
class OdExPrcHostAppProgressMeter : public OdDbHostAppProgressMeter
{
public:
  /** \details 
  Creates a new ODA PRC SDK progress meter object.
  */
  OdExPrcHostAppProgressMeter();

  /** \details 
    Initializes the progress meter object.
    \param displayString [in] A string to be displayed.
  */
  virtual void start(const OdString& displayString = OdString::kEmpty);

  /** \details 
    Stops the progress metering.
  */
  virtual void stop();

  /** \details 
    Increments the progress meter object.

    \remarks
    The completion percentage can be calculated by dividing the number of times this function is called by the value set by the setLimit() method.
    If an exception is thrown, the operation associated with the progress meter object should be halted.
  */
  virtual void meterProgress();

  /** \details 
    Specifies the maximum number of times the progress meter object can be incremented.

    \param max [in]  A maximum increments count.
  */
  virtual void setLimit(int max);

  /** \details
    Controls display of the progress meter object.
    \param disable [in] A flag that disables progress metering. 
  */
  void disableOutput(bool disable) { m_disableOutput = disable; }

  /** \details 
    Sets the prefix for the progress meter object.
    
    \param prefix [in] A new prefix for the progress meter object.
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
  This class implements platform-dependent operations and progress metering for ODA PRC SDK.

  <group PRC_Protocol_Extensions_Classes>
*/
class OdExPrcHostAppServices : public OdPrcHostAppServices
{
public:
  /** \details 
  Creates an instance of services for platform-dependent operations and progress metering. 
  */
  OdExPrcHostAppServices();

  /** \details
    Returns an instance of a progress meter object.
  */
  virtual OdDbHostAppProgressMeter* newProgressMeter();

  /** \details
    This method is called whenever ODA PRC SDK no longer needs the specified progress meter object. 

    \param pProgressMeter [in] A pointer to the progress meter object that should be released.

    \remarks
    The current implementation does nothing.
  */
  virtual void releaseProgressMeter(OdDbHostAppProgressMeter* pProgressMeter);

  /** \details 
    Controls the display of the progress meter object.
    \param disable [in] A new value of the disable flag for the progress meter object. 
  */
  void disableProgressMeterOutput(bool disable) { m_progressMeter.disableOutput(disable); }

private:
  OdExPrcHostAppProgressMeter m_progressMeter;
};

#endif  // _EX_PRCHOSTAPPSERVICES_H_

