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

// OdTimeProvider.h - interface of time provider

#ifndef _OD_TIMEPROVIDER_H__35B11389_12BC_4334_96BC_1C56DCD9D03E__INCLUDED_
#define _OD_TIMEPROVIDER_H__35B11389_12BC_4334_96BC_1C56DCD9D03E__INCLUDED_

#include "RxModule.h"
#include "RootExport.h"

#include "TD_PackPush.h"
#include "OdTimeStamp.h"

/** \details
    This class defines the interface for time provider object.

 	Corresponding C++ library: TD_Root
  
  	<group Other_Classes>
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdTimeProvider : public OdRxModule
{
public:
  /** \details
    Returns a time stamp from a server as OdTimeStamp.
    \param serverName [in]  Server name.
    \param timeStamp [out]  Time stamp.
  */
  virtual bool getTimeFromServer(const OdString& serverName, OdTimeStamp& timeStamp) = 0;
};

typedef OdSmartPtr<OdTimeProvider> OdTimeProviderPtr;

#include "TD_PackPop.h"

#endif // _OD_TIMEPROVIDER_H__35B11389_12BC_4334_96BC_1C56DCD9D03E__INCLUDED_
