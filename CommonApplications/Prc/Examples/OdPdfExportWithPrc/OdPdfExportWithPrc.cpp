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
#include "RxDynamicModule.h"

#include "OdPdfExportWithPrcStart.h"

#include "ExSystemServices.h"
#include "ExHostAppServices.h"
#ifdef OD_HAVE_CONSOLE_H_FILE
#include <console.h>
#endif

#ifdef OD_HAVE_CLOCALE_FILE
#include <clocale>
using namespace std; 
#endif

/************************************************************************/
/* Define a module map for statically linked modules:                   */
/************************************************************************/
#ifndef _TOOLKIT_IN_DLL_

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPdfExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRecomputeDimBlockModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(RasterExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(BitmapModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPsPlotStyleServicesImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPlotSettingsValidatorModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRasterProcessingServicesImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcBaseExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDwg2PrcExportModule);

ODRX_BEGIN_STATIC_MODULE_MAP()
  ODRX_DEFINE_STATIC_APPMODULE(OdPdfExportModuleName,             OdPdfExportModule) 
  ODRX_DEFINE_STATIC_APPMODULE(OdModelerGeometryModuleName,       ModelerModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdRecomputeDimBlockModuleName,   OdRecomputeDimBlockModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdRasterExportModuleName,          RasterExportModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdWinBitmapModuleName,             BitmapModule)
  ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME,        ExRasterModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdPlotSettingsValidatorModuleName, OdPlotSettingsValidatorModule)
  ODRX_DEFINE_STATIC_APPLICATION(ODPS_PLOTSTYLE_SERVICES_APPNAME, OdPsPlotStyleServicesImpl)
  ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName,       OdRasterProcessingServicesImpl)
  ODRX_DEFINE_STATIC_APPLICATION(OdPrcModuleName,                 OdPrcModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdPrcBaseExportModuleName,       OdPrcBaseExportModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdDwg2PrcExportModuleName,       OdDwg2PrcExportModule)
ODRX_END_STATIC_MODULE_MAP()

#endif

//----------------------------------------------------------------------------------

class MyServices : public ExSystemServices, public ExHostAppServices
{
protected:
  ODRX_USING_HEAP_OPERATORS(ExSystemServices);
private:

/************************************************************************/
/* Compile password support for R18 Drawings                            */
/************************************************************************/
#if defined(_MSC_VER) && !(defined(_WINRT))
bool getPassword(const OdString& dwgName, bool isXref, OdPassword& password)
{
  char buff[_MAX_PATH] = {0};
  STD(cout) << "Enter password to open drawing: " << STD(endl);
  ::CharToOemA((const char*)dwgName, buff);
  STD(cout) << "    " << buff << STD(endl);

  STD(cin).get(buff, '\n').get();
  
  wchar_t pwdBuff[_MAX_PATH] = {0};
  // convert to upper case unicode:
  ::OemToCharW( buff, pwdBuff );
  ::CharUpperW( pwdBuff );
  password = pwdBuff;
  return !password.isEmpty();
}
#endif
public:
  OdGsDevicePtr gsBitmapDevice(OdRxObject* /*pViewObj*/ = NULL,
                               OdDbBaseDatabase* /*pDb*/ = NULL,
                               OdUInt32 flags = 0)
  {
    OdGsModulePtr pM;
    if (GETBIT(flags, kFor2dExportRender))
    {
      if (GETBIT(flags, kFor2dExportRenderHLR))
        return OdGsDevicePtr();
      pM = ::odrxDynamicLinker()->loadModule(OdWinOpenGLModuleName);
    }
    if (pM.isNull())
      pM = ::odrxDynamicLinker()->loadModule(OdWinBitmapModuleName);
    if (pM.isNull())
      return OdGsDevicePtr();

    return pM->createBitmapDevice();
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
    #define ODPRCEXPORTCASE(name, description) if (testName == #name) mode = k##name; else
    #include "ExampleCases.h"
    bInvalidArgs = true;
  }

  if (bInvalidArgs)
  {
    STD(cout) << "usage: OdPdfExportWithPrc <export case> <target file>" << STD(endl)
      << "<export case> - name of the export case to execute" << STD(endl)
      << "<target file> - output .pdf file" << STD(endl)
      ;
    #define ODPRCEXPORTCASE(name, description) odPrintConsoleString(L"\n\t%ls - %ls", OdString(#name).c_str(), OdString(description).c_str());
    #include "ExampleCases.h"

    return nRes;
  }

  // call test function
  {
#ifdef OD_HAVE_SETLOCALE_FUNC
    /********************************************************************/
    /* For correct Unicode translation, apply the current system locale.*/
    /********************************************************************/
    setlocale(LC_ALL, "");
    /********************************************************************/
    /* But use usual conversion for scanf()/sprintf()                   */
    /********************************************************************/
    setlocale(LC_NUMERIC, "C");
#endif

#ifndef _TOOLKIT_IN_DLL_
    ODRX_INIT_STATIC_MODULE_MAP();
#endif

    /********************************************************************/
    /* Create a custom Services instance.                               */
    /********************************************************************/
    OdStaticRxObject<MyServices> svcs;
    odInitialize(&svcs);

    /********************************************************************/
    /* Display the Product and Version that created the executable      */
    /********************************************************************/
    STD(cout) << "Developed using " << (const char*)svcs.product() << ", " << (const char*)svcs.versionString() << STD(endl);

    /********************************************************************/
    /* Process command line parameters                                  */
    /********************************************************************/
 
    try 
    {
      OdPdfExportWithPrcStart(svcs, argv[2], mode);
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

    odUninitialize();
  }

  return 0;
}
