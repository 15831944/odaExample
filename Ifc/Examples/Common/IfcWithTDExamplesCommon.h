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

#ifndef _IFC_EXAMPLESCOMMON_H_
#define _IFC_EXAMPLESCOMMON_H_
/** { Secret } */

#include "PrcCommon.h"

#include "StaticRxObject.h"
#include "DbSystemServices.h"
#include "DynamicLinker.h"
#include "diagnostics.h"

#include "RxDynamicModule.h"
#include <locale.h>

#include "OdFileBuf.h"
#include "ExSystemServices.h"
#include "ExHostAppServices.h"
#include "ExPrcHostAppServices.h"

#ifdef OD_HAVE_CONSOLE_H_FILE
#include <console.h>
#endif

void odPrintConsoleString(const wchar_t* fmt, ...);
// {
//   va_list argList;
//   va_start(argList, fmt);
//   OdString s;
//   s.formatV(fmt, argList);
//   va_end(argList);
// #ifdef OD_WINDOWS_DESKTOP
//   DWORD dw;
//   HANDLE o = ::GetStdHandle(STD_OUTPUT_HANDLE);
//   if (o != NULL)
//   {
//     if (::GetFileType(o) == FILE_TYPE_CHAR)
//       ::WriteConsoleW(o, s.c_str(), s.getLength(), &dw, 0);
//     else
//       ::WriteFile(o, (const char*)s, s.getLengthA(), &dw, 0);
//   }
// #elif defined(ANDROID)
//   printf("%s", (const char*)s);
// #elif defined(_WINRT)
//   g_printConsoleFunc(L"%ls", s.c_str());
// #else
//   printf("%ls", s.c_str());
// #endif
// }

/************************************************************************/
/* Define a Custom Services class.                                      */
/*                                                                      */
/* Combines the platform dependent functionality of                     */
/* OdRxSystemServices and OdPrcHostAppServices                       */ 
/************************************************************************/

template <class PrcHost = OdExPrcHostAppServices, class TdHost = ExHostAppServices, class exServices = ExSystemServices> 
class MyServicesBase
{
  OdStaticRxObject<PrcHost>    m_PrcHostAppServices;
  OdStaticRxObject<TdHost>     m_TdHostAppServices;
  OdStaticRxObject<exServices> m_systemServices;

public:

  virtual OdDbSystemServices *systemServices() { return &m_systemServices; }
  virtual TdHost &hostTD() { return m_TdHostAppServices; }
  virtual OdExPrcHostAppServices &hostPRC() { return m_PrcHostAppServices; }

  virtual const OdDbSystemServices *systemServices() const { return &m_systemServices; }
  virtual const TdHost &hostTD() const { return m_TdHostAppServices; }
  virtual const OdExPrcHostAppServices &hostPRC() const { return m_PrcHostAppServices; }

  virtual ~MyServicesBase() {}
};

class MyServices : public MyServicesBase<>
{
};

/********************************************************************************/
/* Define Assert function to not crash Debug application if assertion is fired. */
/********************************************************************************/
static void MyAssert(const char* expression, const char* fileName, int nLineNo)
{
  OdString message;
  message.format(L"\n!!! Assertion failed: \"%ls\"\n    file: %ls, line %d\n", OdString(expression).c_str(), OdString(fileName).c_str(), nLineNo);
  odPrintConsoleString(message);
}

#endif // _IFC_EXAMPLESCOMMON_H_

