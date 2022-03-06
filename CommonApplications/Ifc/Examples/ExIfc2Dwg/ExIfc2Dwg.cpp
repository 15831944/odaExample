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
#include "OdString.h"
#include "RxVariantValue.h"

#include "ExSystemServices.h"
#include "ExHostAppServices.h"

#include "IfcExamplesCommon.h"
#include "IfcCore.h"

#include "StaticRxObject.h"
#include "RxDynamicModule.h"
#include "OdPerfTimer.h"

#include "ExPrintConsole.h"

#include "Common/ModuleNames.h"
#include "../Exchange/Exports/Ifc2Dwg/Include/IfcExport.h"
using namespace TD_IFC_EXPORT;

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

class DbServices : public ExSystemServices, public ExHostAppServices
{
protected:
  ODRX_USING_HEAP_OPERATORS(ExSystemServices);
  virtual void warning(const char*, const OdString& msg) ODRX_OVERRIDE
  {
    odPrintConsoleString(L"Exception: ");
    odPrintConsoleString(msg.c_str());
    odPrintConsoleString(L"\n");
  }
};

//
// Define module map for statically linked modules:
//
#if !defined(_TOOLKIT_IN_DLL_)
  ODRX_DECLARE_IFC2DWG_STATIC_MODULES_ENTRY_POINTS()
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRecomputeDimBlockModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxThreadPoolService);
  ODRX_BEGIN_STATIC_MODULE_MAP()
    ODRX_DEFINE_IFC2DWG_STATIC_APPMODULES()
    ODRX_DEFINE_STATIC_APPMODULE(OdRecomputeDimBlockModuleName, OdRecomputeDimBlockModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdThreadPoolModuleName, OdRxThreadPoolService)
  ODRX_END_STATIC_MODULE_MAP()
#endif

#include <iostream>
#include <cstdlib>

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

#if defined(TARGET_OS_MAC) && !defined(__MACH__)
  argc = ccommand(&argv);
#endif

  setlocale(LC_TIME, ""); // set current user locale (not OD_T("C")), for strftime

  /**********************************************************************/
  /* Create a Services object                                           */
  /**********************************************************************/
  OdStaticRxObject<DbServices> dbSvcs;
  OdStaticRxObject<MyServices> ifcSvcs;
  
  /**********************************************************************/
  /* Display the Product and Version that created the executable        */
  /**********************************************************************/
  odPrintConsoleString(L"\nExIfc2Dwg example developed using %ls ver %ls", 
    ifcSvcs.product().c_str(), ifcSvcs.versionString().c_str());

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  bool bInvalidArgs = (argc != 2 && argc != 3 && argc != 4);
  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }

  if (bInvalidArgs)    
  {
    odPrintConsoleString(L"\n\nusage: ExIfc2Dwg <in filename> [out filename]");
    odPrintConsoleString(L"\n<in filename> - input .ifc or .ifczip file\n");
    odPrintConsoleString(L"\n[out filename] - output .dwg file, optional\n");
    return nRes;
  }

#if !defined(_TOOLKIT_IN_DLL_) 
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  /**********************************************************************/
  /* Initialize ODA SDK                                                 */
  /**********************************************************************/
  odrxInitialize(&dbSvcs);
  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize Drawings SDK                                            */
  /**********************************************************************/
  odInitialize(&dbSvcs);

  /**********************************************************************/
  /* Initialize IFC SDK                                                 */
  /**********************************************************************/
  // 1. Conversion can be done using just abstract OdIfcExportPtr interface,
  //   so IFC SDK initialization can be skipped here. In this case it is
  //   performed inside Ifc2Dwg module.
  // 2. ifcSvcs is also optional, if it isn't provided, internal implementation
  //   will be used.
  odIfcInitialize(false /* No CDA */, true /* Geometry calculation needed */);

  try
  {
    OdString ifcInFileName(argv[1]);
    OdString dwgOutFileName;
    if (argc > 2)
      dwgOutFileName = argv[2];

    OdIfc2DwgModulePtr pIfc2DwgModule = ::odrxDynamicLinker()->loadApp(OdIfc2DwgModuleName, false);
    if (!pIfc2DwgModule.isNull())
    {
      OdIfcExportPtr Exporter = pIfc2DwgModule->create();

      Exporter->properties()->putAt(L"OdDbServices", static_cast<ExHostAppServices*>(&dbSvcs));
      Exporter->properties()->putAt(L"IfcServices", static_cast<OdExIfcHostAppServices*>(&ifcSvcs)); // Optional
      Exporter->properties()->putAt(L"IfcFilePath", OdRxVariantValue(ifcInFileName));
      Exporter->properties()->putAt(L"ExportBuildingElementProxy", OdRxVariantValue(true));
      Exporter->properties()->putAt(L"ZoomExtents", OdRxVariantValue(true));
      Exporter->properties()->putAt(L"ExportMode", OdRxVariantValue(OdInt16(TD_IFC_EXPORT::kAsPolyFaceMesh)));

      OdPerfTimerWrapper timerWrapper;
      timerWrapper.getTimer()->start();

        // Start conversion
        OdIfcExport::ExportResult res = Exporter->exportIfc();

      timerWrapper.getTimer()->stop();
      odPrintConsoleString(L"\nIfc2Dwg: ifc reading time is %d msec", timerWrapper.getTimer()->countedMSec());

      OdDbDatabasePtr pDb;
      if (res == OdIfcExport::success)
      {
        odPrintConsoleString(L"\nIfc2Dwg: successful conversion");

        pDb = Exporter->properties()->getAt(L"Database"); // Created inside of Ifc2Dwg module if wasn't provided before.
        OdRxObjectPtr pFile = Exporter->properties()->getAt(L"IfcFile");
        OdIfcConnectionMapPtr pMap = Exporter->properties()->getAt(L"IfcConnectionMap");
        OdRxObjectPtr pMapAssignedFile = pMap->getIfcFile();
        ODA_ASSERT(pFile.get() == pMapAssignedFile.get());

        if (!dwgOutFileName.isEmpty())
        {
          odPrintConsoleString(L"\nIfc2Dwg: writing .dwg file %s", dwgOutFileName.c_str());
          pDb->writeFile(dwgOutFileName, OdDb::kDwg, OdDb::vAC32);
        }
      }
      else
      {
        switch (res)
        {
        case OdIfcExport::bad_database:
          odPrintConsoleString(L"\nIfc2Dwg: bad database\n");
          break;
        case OdIfcExport::bad_file:
          odPrintConsoleString(L"\nIfc2Dwg: bad ifc file\n");
          break;
        case OdIfcExport::fail:
          odPrintConsoleString(L"\nIfc2Dwg: unknown conversion error\n");
          break;
        }
      }
    }

    // Unload Ifc2Dwg module
    pIfc2DwgModule = nullptr;
    odrxDynamicLinker()->unloadModule(OdIfc2DwgModuleName);

    odPrintConsoleString(L"\nPress any key.\n");
    getchar();
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
  /* Uninitialize IFC SDK                                               */
  /**********************************************************************/
  odIfcUninitialize();

  /**********************************************************************/
  /* Uninitialize Drawings SDK                                          */
  /**********************************************************************/
  odUninitialize();

  /**********************************************************************/
  /* Uninitialize ODA SDK                                               */
  /**********************************************************************/
  odDbRootUninitialize();
  odrxUninitialize();
  return nRes;
}
