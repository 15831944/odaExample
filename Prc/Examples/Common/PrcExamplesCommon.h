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

#ifndef _PRCEXAMPLESCOMMON_INCLUDED_
#define _PRCEXAMPLESCOMMON_INCLUDED_ 
/** { Secret } */

#ifdef _MSC_VER
#define _WIN32_WINNT 0x0400 // to enable Windows Cryptographic API
#endif

#include "PrcCommon.h"

#include "StaticRxObject.h"
#include "ExPrcHostAppServices.h"
#include "ExSystemServices.h"
#include "DynamicLinker.h"
#include "diagnostics.h"
#include "RxInit.h"

#include "RxDynamicModule.h"
#include <locale.h>

#include "PrcFile.h"
#include "OdFileBuf.h"
#include "ExPrintConsole.h"

#ifdef OD_HAVE_CONSOLE_H_FILE
#include <console.h>
#endif

/************************************************************************/
/* Freeze a local time                                                  */
/************************************************************************/
typedef void (*PgetLocalTime)( OdTimeStamp& ts );
extern FIRSTDLL_EXPORT_STATIC PgetLocalTime g_pLocalTimeFunc; // global variable defined in TD_Root
static void getLocalTime(OdTimeStamp &localTime)
{
  localTime.setDate(12, 22, 2009);
  localTime.setTime(18, 0, 0, 0);
}

/************************************************************************/
/* Define a Custom Services class.                                      */
/*                                                                      */
/* Combines the platform dependent functionality of                     */
/* OdRxSystemServices and OdDbBaseHostAppServices                       */ 
/************************************************************************/
class MyServices : public ExSystemServices, public OdExPrcHostAppServices
{
protected:
  ODRX_USING_HEAP_OPERATORS(ExSystemServices);
  OdGsDevicePtr gsBitmapDevice(OdRxObject* /*pViewObj*/ = NULL,
    OdDbBaseDatabase* /*pDb*/ = NULL,
    OdUInt32 /*flags*/ = 0)
  {
    try
    {
      OdGsModulePtr pGsModule = ::odrxDynamicLinker()->loadModule(OdWinBitmapModuleName);
      return pGsModule->createBitmapDevice();
    }
    catch(const OdError&)
    {
    }
    return OdGsDevicePtr();
  }

public:

  virtual OdString findFile(
    const OdString& filename,
    OdDbBaseDatabase* pDb,
    FindFileHint hint)
  {
    return filename;
  }

  virtual const OdString program()
  {
    return OdString::kEmpty;
  }

  virtual const OdString product()
  {
    return OdString::kEmpty;
  }

  virtual const OdString companyName()
  {
    return OdString::kEmpty;
  }

  virtual bool ttfFileNameByDescriptor(
    const OdTtfDescriptor& description,
    OdString& filename)
  {
    return false;
  }

  virtual OdString getAlternateFontName() const
  {
    return OdString::kEmpty;
  }

  virtual OdString getFontMapFileName() const
  {
    return OdString::kEmpty;
  }

  virtual OdString getPreferableFont(
    const OdString& fontName,
    OdFontType fontType)
  {
    return OdString::kEmpty;
  }

  virtual OdString getSubstituteFont(
    const OdString& fontName,
    OdFontType fontType) 
  {
    return OdString::kEmpty;
  }

};


/********************************************************************************/
/* Define Assert function to not crash Debug application if assertion is fired. */
/*******************************************************************************/

static void MyAssert(const char* expression, const char* fileName, int nLineNo)
{
  OdString message;
  message.format(L"\n!!! Assertion failed: \"%s\"\n    file: %ls, line %d\n", OdString(expression).c_str(), OdString(fileName).c_str(), nLineNo);
  odPrintConsoleString(message);
}

#endif // _PRCCOMMON_INCLUDED_

