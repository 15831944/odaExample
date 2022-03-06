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
/************************************************************************/
/* Simple application to load a Ifc file                                */
/* and save as STL geometry collection                                  */
/************************************************************************/

#include "OdaCommon.h"

#include "StaticRxObject.h"
#include "RxDynamicModule.h"

#include "IfcExamplesCommon.h"
#include "IfcCore.h"
#include "IfcGsManager.h"
#include "IfcGiContext.h"

#include "ExIfcHostAppServices.h"
#include "ExGsSimpleDevice.h"

#include "RxVariantValue.h"
#include "Gs/Gs.h"
#include "Gs/GsBaseInclude.h"
#include "ColorMapping.h"
#include "AbstractViewPE.h"

#include "ExPrintConsole.h"
#include "ExKeyPressCatcher.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

GS_TOOLKIT_EXPORT void odgsInitialize();
GS_TOOLKIT_EXPORT void odgsUninitialize();

//
// Define module map for statically linked modules:
//
#if !defined(_TOOLKIT_IN_DLL_)
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x3Module);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4Module);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcGeomModuleImpl);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcFacetModelerModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcBrepBuilderModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxThreadPoolService);
  ODRX_BEGIN_STATIC_MODULE_MAP()
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x3ModuleName, OdIfc2x3Module)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc4ModuleName, OdIfc4Module)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcGeomModuleName, OdIfcGeomModuleImpl)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcFacetModelerModuleName, OdIfcFacetModelerModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcBrepBuilderModuleName, OdIfcBrepBuilderModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdThreadPoolModuleName, OdRxThreadPoolService)
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
  int   nRes = 0;               // Return value for the function

#ifdef OD_HAVE_CCOMMAND_FUNC
  argc = ccommand(&argv);
#endif

  /********************************************************************/
  /* Create a Services object                                         */
  /********************************************************************/
  OdStaticRxObject<MyServices> svcs;

  /**********************************************************************/
  /* Display the Product and Version that created the executable        */
  /**********************************************************************/
  odPrintConsoleString(L"\nExIfcVectorize sample program. Copyright (c) 2022, Open Design Alliance\n");

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  bool bInvalidArgs = (argc < 2);

  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }

  if (bInvalidArgs)    
  {
    odPrintConsoleString(L"\n\tusage: ExIfcVectorize <filename> [stlFilename] [-DO]");
    odPrintConsoleString(L"\n\t-DO disables progress meter output.\n");
    return nRes;
  }

  OdString szSource = argv[1];
  OdString strStlFilename = OdString::kEmpty;

  if (argc > 2)
  {
    strStlFilename = argv[2];
    if (strStlFilename == L"-DO")
      strStlFilename = OdString::kEmpty;
  }

#if !defined(_TOOLKIT_IN_DLL_)
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  /**********************************************************************/
  /* Initialize ODA SDK                                                 */
  /**********************************************************************/
  odrxInitialize(&svcs);
  odDbRootInitialize();
  odgsInitialize();

  /**********************************************************************/
  /* Initialize IfcCore                                                 */
  /**********************************************************************/

  odIfcInitialize(false /* No CDA */, true);

  try
  {
    OdIfcFilePtr pDatabase = svcs.createDatabase();
    
    if (pDatabase->readFile(szSource) != eOk)
    {
      throw OdError( eCantOpenFile );
    }

    auto ctx = pDatabase->getContext();
    
    // // Specialize deviation parameters
    // //OdIfcDeviationParams deviationParams;
    // //deviationParams.setMinPerCircle(16);
    // //deviationParams.setMaxPerCircle(128);
    // //deviationParams.setDeviation(0.005);
    // //ctx.setDeviationParams(deviationParams);

    // // Turn on IfcSpace visualization
    // //ctx.getGeometryComposeTypes().append(OdIfc::kIfcSpace);

    // Specialize callback function for geometry compose process interruption
    KeyPressCatcher keyPressCatcher;
    ctx.setInterruptCallback(keyPressCatcher.getInterruptCallback());

    pDatabase->setContext(ctx);

    if (OdResult res = pDatabase->composeEntities())
    {
      if (res == eFileInternalErr) {
        throw OdError( eFileInternalErr );
      }
      if (res == eNullPtr) {
        throw OdError( eNullPtr );
      }
    }

    OdGsDevicePtr pSimpleDevice = ExGsSimpleDevice::createObject(ExGsSimpleDevice::k3dDevice);
    OdGiContextForIfcDatabasePtr pIfcContext = OdGiContextForIfcDatabase::createObject();

    pIfcContext->setDatabase(pDatabase);
    pIfcContext->enableGsModel(true);

    const ODCOLORREF* palette = odcmAcadPalette(ODRGB(255, 255, 255));
    OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;
    ODCOLORREF background(ODRGB(192, 192, 192));

    pSimpleDevice->setBackgroundColor(background);
    pIfcContext->setPaletteBackground(background);
    pPalCpy.insert(pPalCpy.begin(), palette, palette + 256);
    pSimpleDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

    OdGsDevicePtr pDevice = OdIfcGsManager::setupActiveLayoutViews(pSimpleDevice, pIfcContext);
    OdGsView* pView = pDevice->viewAt(0);

    pView->setMode(OdGsView::kGouraudShaded);
    pView->setView(OdGePoint3d(1, 1, 1), OdGePoint3d(0, 0, 0), OdGeVector3d::kZAxis, 1000, 1000);

    OdDAIObjectIds contextsSelection = OdIfc::Utils::getDefaultRepresentationContextsSelection(pDatabase, false);
    if (contextsSelection.isEmpty())
      contextsSelection = OdIfc::Utils::getAllRepresentationContexts(pDatabase);
    pDatabase->setContextSelection(contextsSelection);

    OdGsDCRect screenRect(OdGsDCPoint(0, 0), OdGsDCPoint(1024, 768));

    pDevice->onSize(screenRect);
    OdAbstractViewPEPtr(pView)->zoomExtents(pView);
    pDevice->update();

    // Write triangle data to stl.

    if (!strStlFilename.isEmpty())
      OdGiDumper::writeFaceDataToStlFile(strStlFilename, OdGiDumper::getStlTriangles());

    OdGiDumper::clearStlTriangles();
  }
  catch (OdError& e)
  {
    odPrintConsoleString(L"\n\nError: %ls", e.description().c_str());
    nRes = -1;
  }
  catch (...)
  {
    odPrintConsoleString(L"\n\nUnexpected error.");
    nRes = -1;
    throw;
  }

  /**********************************************************************/
  /* Uninitialize IfcCore                                               */
  /**********************************************************************/
  odIfcUninitialize();

  odgsUninitialize();
  odDbRootUninitialize();

  /**********************************************************************/
  /* Uninitialize ODA SDK                                               */
  /**********************************************************************/
  odrxUninitialize();

  return nRes;
}
