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

#include "PrcWithTDExamplesCommon.h"
#include "OdModuleNames.h"
#include "OdPrcCreateStart.h"

// Define module map for statically linked modules:
#if !defined(_TOOLKIT_IN_DLL_) 

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPdfExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcBaseExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDwg2PrcExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRecomputeDimBlockModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);

ODRX_BEGIN_STATIC_MODULE_MAP()
  ODRX_DEFINE_STATIC_APPMODULE(OdPdfExportModuleName,             OdPdfExportModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdModelerGeometryModuleName,       ModelerModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdPrcModuleName,                 OdPrcModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdPrcBaseExportModuleName,       OdPrcBaseExportModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdDwg2PrcExportModuleName,       OdDwg2PrcExportModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdRecomputeDimBlockModuleName,   OdRecomputeDimBlockModule)
  ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME,        ExRasterModule)
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
  MyServices svcs;

  /**********************************************************************/
  /* Display the Product and Version that created the executable        */
  /**********************************************************************/
  odPrintConsoleString(L"\nOdPrcCreate developed using %ls ver %ls", 
    svcs.hostPRC().product().c_str(), svcs.hostPRC().versionString().c_str());

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  CreationMode mode;
  bool bInvalidArgs = (argc != 3);
  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }
  else
  {
    OdString s(argv[1]);
    #define ODPRCCREATECASE(a, b, c, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14) if (s == #a) mode = k##a; else
    #include "ExampleCases.h"
    bInvalidArgs = true;
  }

  if (bInvalidArgs)
  {
    odPrintConsoleString(L"\n\nusage: OdPrcCreate <example> <filename>");
    odPrintConsoleString(L"\n<example>:");
    #define ODPRCCREATECASE(a, b, c, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14) odPrintConsoleString(L"\n\t%ls - %ls", OdString(#a).c_str(), OdString(b).c_str());
    #include "ExampleCases.h"
    odPrintConsoleString(L"\n<filename> - output .prc file\n");

    return nRes;
  }

#if !defined(_TOOLKIT_IN_DLL_) 
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  /**********************************************************************/
  /* Initialize ODA Platform                                            */
  /**********************************************************************/
  odInitialize(svcs.systemServices());

  ::odrxDynamicLinker()->loadApp(OdPrcModuleName, false);

  try
  {
    OdString prcName(argv[2]);
    OdPrcCreateStart(prcName, mode, svcs.hostTD(), svcs.hostPRC());
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
  odUninitialize();
  return nRes;
}
