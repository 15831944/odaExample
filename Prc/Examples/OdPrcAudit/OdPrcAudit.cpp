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

#include "PrcExamplesCommon.h"

#include "PrcAuditInfoImpl.h"

// Define module map for statically linked modules:
#if !defined(_TOOLKIT_IN_DLL_) 

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcModule);

ODRX_BEGIN_STATIC_MODULE_MAP()
ODRX_DEFINE_STATIC_APPLICATION(OdPrcModuleName, OdPrcModule)
ODRX_END_STATIC_MODULE_MAP()

#endif

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  int nRes = 0; // Return value for main

  /**********************************************************************/
  /* Overload OdTimeStamp::getLocalTime internal implementation         */
  /**********************************************************************/
  g_pLocalTimeFunc = getLocalTime;

  /**********************************************************************/
  /* Set customized assert function                                     */
  /**********************************************************************/
  odSetAssertFunc(MyAssert);

#if defined(TARGET_OS_MAC) && !defined(__MACH__)
  argc = ccommand(&argv);
#endif

  setlocale(LC_TIME, ""); // set current user locale (not OD_T("C")), for strftime

  /**********************************************************************/
  /* Create a Services object                                           */
  /**********************************************************************/
  OdStaticRxObject<MyServices> svcs;

  /**********************************************************************/
  /* Display the Product and Version that created the executable        */
  /**********************************************************************/
  odPrintConsoleString(L"\nOdPrcAudit developed using %ls ver %ls", 
    svcs.product().c_str(), svcs.versionString().c_str());

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  bool bInvalidArgs = (argc != 2);
  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }

  if (bInvalidArgs)    
  {
    odPrintConsoleString(L"\n\nusage: OdPrcAudit <filename>");
    odPrintConsoleString(L"\n<filename> - input .prc file\n");
    return nRes;
  }

#if !defined(_TOOLKIT_IN_DLL_) 
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  /**********************************************************************/
  /* Initialize ODA Platform                                            */
  /**********************************************************************/
  odrxInitialize(&svcs);

  ::odrxDynamicLinker()->loadApp(OdPrcModuleName, false);

  try
  {
    OdString prcName(argv[1]);

    OdPrcAuditInfoImplPtr auditInfo = OdPrcAuditInfoImpl::createObject();

    OdPrcFilePtr pDatabase = svcs.createDatabase();
    pDatabase->readFile(prcName, auditInfo);

    if (auditInfo->errorsFound())
    {
      const OdStringArray &info = auditInfo->errorInfo();
      odPrintConsoleString(L"\nAudit reported %d error(s):\n", info.size());
      for(OdUInt32 f=0; f<info.size(); ++f)
      {
        odPrintConsoleString(L"%ls\n", info[f].c_str());
      }
    }
    else
    {
      odPrintConsoleString(L"\nAudit reported no errors.");
    }
  }
  catch(OdError& e)
  {
    odPrintConsoleString(L"\n\nError: %ls", e.description().c_str());
    nRes = -1;
  }
  catch(...)
  {
    odPrintConsoleString(L"\n\nUnexpected error.");
    nRes = -1;
    throw;
  }

  /**********************************************************************/
  /* Uninitialize ODA Platform                                          */
  /**********************************************************************/
  odrxUninitialize();
  return nRes;
}
