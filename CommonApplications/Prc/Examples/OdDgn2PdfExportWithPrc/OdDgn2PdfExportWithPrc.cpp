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

#ifdef WD_WIN_SYSTEM
#include <io.h>
#include <direct.h>
#endif

#include <stdlib.h>

#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a

#include "PrcCommon.h"
#include "OdDgn2PdfExportWithPrcStart.h"
#include "ServicesForExample.h"
#include "RxDynamicModule.h"

/************************************************************************/
/* Define a module map for statically linked modules:                   */
/************************************************************************/
#ifndef _TOOLKIT_IN_DLL_

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDgnModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(DgModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDgn7IOModuleImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDgPsPlotStyleServicesImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(RasterExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(BitmapModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRasterProcessingServicesImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPdfExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcBaseExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDgn2PrcExportModule);

#ifdef TDRAWING_ENABLED
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDwgModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDwgDbModuleImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ModelerModule);
#endif

ODRX_BEGIN_STATIC_MODULE_MAP()
  ODRX_DEFINE_STATIC_APPMODULE(L"TG_Db", OdDgnModule)
  ODRX_DEFINE_STATIC_APPMODULE(L"TG_ModelerGeometry", DgModelerModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdRasterExportModuleName,          RasterExportModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdWinBitmapModuleName,             BitmapModule)
  ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME,        ExRasterModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName,       OdRasterProcessingServicesImpl)
  ODRX_DEFINE_STATIC_APPMODULE(OdPdfExportModuleName,             OdPdfExportModule) 
  ODRX_DEFINE_STATIC_APPLICATION(L"TG_Dgn7IO", OdDgn7IOModuleImpl)
  ODRX_DEFINE_STATIC_APPLICATION(OdPrcModuleName,                 OdPrcModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdPrcBaseExportModuleName,       OdPrcBaseExportModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdDgn2PrcExportModuleName,       OdDgn2PrcExportModule)
#ifdef TDRAWING_ENABLED
  ODRX_DEFINE_STATIC_APPMODULE(OdDbModuleName, OdDwgModule)
  ODRX_DEFINE_STATIC_APPLICATION(L"TG_DwgDb", OdDwgDbModuleImpl)
  ODRX_DEFINE_STATIC_APPMODULE(OdModelerGeometryModuleName, ModelerModule)
#endif
ODRX_END_STATIC_MODULE_MAP()

#endif

//----------------------------------------------------------------------------------

class MyServicesForTestDGN : public MyDgServicesBase<PrcHostFindFile<OdExPrcHostAppServices> , /*OdExDgnSystemServices*/OdExDgnHostAppServices>
{
public:
  void setSearchPath(const OdString& path)
  {
    ((PrcHostFindFile<OdExPrcHostAppServices>&)hostPRC()).m_searchPath = path;
  }

  void setTestFolder(const OdString& pathToFolder)
  {
    ((PrcHostFindFile<OdExPrcHostAppServices>&)hostPRC()).m_testDirectory = pathToFolder;
  }

};

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if defined(TARGET_OS_MAC) && !defined(__MACH__)
  argc = ccommand(&argv);
#endif

  int nRes = 0; // Return value for main
  ExportMode mode;
  bool bInvalidArgs = (argc != 3);
  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }
  else
  {
    OdString testName (argv[1]);
    #define ODPRCEXPORTCASE(name, description, callmethod) if (testName == #name) mode = k##name; else
    #include "ExampleCases.h"
    bInvalidArgs = true;
  }

  if (bInvalidArgs)
  {
    STD(cout) << "usage: OdDgn2PdfExportWithPrc <export case> <target file>" << STD(endl)
      << "<export case> - name of the export case to execute" << STD(endl)
      << "<target file> - output .pdf file" << STD(endl)
      ;
    #define ODPRCEXPORTCASE(name, description, callmethod) odPrintConsoleString(L"\n\t%ls - %ls", OdString(#name).c_str(), OdString(description).c_str());
    #include "ExampleCases.h"

    return nRes;
  }

  // call test function
  {
    /********************************************************************/
    /* For correct Unicode translation, apply the current system locale.*/
    /********************************************************************/
    setlocale(LC_ALL, "");
    /********************************************************************/
    /* But use usual conversion for scanf()/sprintf()                   */
    /********************************************************************/
    setlocale(LC_NUMERIC, "C");

#ifndef _TOOLKIT_IN_DLL_
    ODRX_INIT_STATIC_MODULE_MAP();
#endif

    /********************************************************************/
    /* Create a custom Services instance.                               */
    /********************************************************************/
    MyServicesForTestDGN svcs;
    odrxInitialize(svcs.systemServices());

    /********************************************************************/
    /* Display the Product and Version that created the executable      */
    /********************************************************************/
    STD(cout) << "Developed using " << (const char*)svcs.hostTG().product() << ", " << (const char*)svcs.hostTG().versionString() << STD(endl);

    /********************************************************************/
    /* Process command line parameters                                  */
    /********************************************************************/
 
    try 
    {
      OdDgn2PdfExportWithPrcStart(svcs.hostTG(), argv[2], mode);
    }
    catch (OdError& err)
    {
      OdString msg = err.description();
      STD(cout) << "ODA Platform Error: " << (const char*)msg << STD(endl) << STD(endl);
    }
    catch (...)
    {
      STD(cout) << "Unknown Error." << STD(endl) << STD(endl);
      return 0;
    }

    odrxUninitialize();
  }

  return 0;
}
