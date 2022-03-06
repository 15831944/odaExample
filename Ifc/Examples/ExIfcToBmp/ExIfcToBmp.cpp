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
/* Simple application to load a Ifc file and save as BMP                */
/************************************************************************/

#include "OdaCommon.h"

#include "StaticRxObject.h"

#include "IfcExamplesCommon.h"
#include "IfcCore.h"
#include "IfcGsManager.h"
#include "IfcGiContext.h"

#include "ExIfcHostAppServices.h"

#include "RxVariantValue.h"
#include "Gi/GiRasterImage.h"
#include "Gs/Gs.h"
#include "Gs/GsBaseInclude.h"
#include "ColorMapping.h"
#include "RxRasterServices.h"
#include "AbstractViewPE.h"

#include "ExPrintConsole.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

//
// Define module map for statically linked modules:
//
#if !defined(_TOOLKIT_IN_DLL_)
  #include "RxDynamicModule.h"

  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);                          
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);                           
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x3Module);                            
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4Module);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcGeomModuleImpl);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcFacetModelerModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcBrepBuilderModule);   
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(BitmapModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);
  ODRX_BEGIN_STATIC_MODULE_MAP()                                                     
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)                 
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)               
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x3ModuleName, OdIfc2x3Module)                 
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc4ModuleName, OdIfc4Module)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcGeomModuleName, OdIfcGeomModuleImpl)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcFacetModelerModuleName, OdIfcFacetModelerModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcBrepBuilderModuleName, OdIfcBrepBuilderModule) 
    ODRX_DEFINE_STATIC_APPMODULE(OdWinBitmapModuleName, BitmapModule)
    ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME, ExRasterModule)
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
  bool  disableOutput = false;  // Disable output if it is indicated in command line

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
  odPrintConsoleString(L"\nExIfcToBmp sample program. Copyright (c) 2022, Open Design Alliance\n");

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  bool bInvalidArgs = (argc < 3);
  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }

  if (bInvalidArgs)    
  {
    odPrintConsoleString(L"\n\tusage: ExIfcToBmp <source file> <destination file> [-DO]");
    odPrintConsoleString(L"\n\t-DO disables progress meter output.\n");
    return nRes;
  }

  /**********************************************************************/
  /* Disable progress meter                                             */
  /**********************************************************************/
  if (argc >= 4)
  {
    OdString argv2(argv[3]);
    if (!odStrICmp(argv2, OD_T("-DO")))
    {
      disableOutput = true;
    }
  }

  OdString srcFileName = argv[1];
  OdString dstFileName = argv[2];

  /************************************************************************/
  /* Disable/Enable progress meter                                       */
  /************************************************************************/
  svcs.disableProgressMeterOutput( disableOutput );

#if !defined(_TOOLKIT_IN_DLL_)
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  /**********************************************************************/
  /* Initialize ODA SDK                                                 */
  /**********************************************************************/
  odrxInitialize(&svcs);

  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize IfcCore                                                 */
  /**********************************************************************/

  odIfcInitialize(false /* No CDA */, true /* Geometry calculation needed */);

  try
  {
    OdString ifcFileName(argv[1]);

    OdIfcFilePtr pDatabase = svcs.createDatabase();
    
    if (pDatabase->readFile(ifcFileName) != eOk)
    {
      throw OdError( eCantOpenFile );
    }

    if (OdResult res = pDatabase->composeEntities())
    {
      if (res == eFileInternalErr) {
        throw OdError( eFileInternalErr );
      }
      if (res == eNullPtr) {
        throw OdError( eNullPtr );
      }
    }

    OdGsModulePtr pGsModule = ::odrxDynamicLinker()->loadModule( OdWinBitmapModuleName );

#ifdef _TOOLKIT_IN_DLL_
    if ( pGsModule.isNull() )
    {
      pGsModule = ::odrxDynamicLinker()->loadModule( OdWinGDIModuleName );
    }
#endif
    
    OdGsDevicePtr pBitmapDevice;

    if ( pGsModule.get() )
    {
      pBitmapDevice = pGsModule->createBitmapDevice();
    }

    if ( pBitmapDevice.get() )
    {
      OdGiContextForIfcDatabasePtr pIfcContext = OdGiContextForIfcDatabase::createObject();

      pIfcContext->setDatabase(pDatabase);
      pIfcContext->enableGsModel(true);

      OdGsDevicePtr pDevice = OdIfcGsManager::setupActiveLayoutViews(pBitmapDevice, pIfcContext);
      OdGsView* pView = pDevice->viewAt(0);

      pView->setMode(OdGsView::kHiddenLine);
      pView->setView(OdGePoint3d(1, 1, 1), OdGePoint3d(0, 0, 0), OdGeVector3d::kZAxis, 1000, 1000);
      pDatabase->setContextSelection(OdIfc::Utils::getDefaultRepresentationContextsSelection(pDatabase, false));

      const ODCOLORREF* palette  = odcmAcadPalette(ODRGB(255, 255, 255));
      OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;
      ODCOLORREF background(ODRGB(192, 192, 192));

      pDevice->setBackgroundColor(background);
      pIfcContext->setPaletteBackground(background);
      pPalCpy.insert(pPalCpy.begin(), palette, palette + 256);
      pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

      OdGsDCRect screenRect(OdGsDCPoint(0, 768), OdGsDCPoint(1024, 0));

      pDevice->onSize(screenRect);
      pDevice->properties()->putAt(OD_T("BitPerPixel"), OdRxVariantValue(OdUInt32(24)));
      OdAbstractViewPEPtr(pView)->zoomExtents(pView);
      pDevice->update();

      OdGiRasterImagePtr ptrImage = pDevice->properties()->getAt( OD_T("RasterImage") );
      OdRxRasterServicesPtr pRasSvcs = odrxDynamicLinker()->loadApp(RX_RASTER_SERVICES_APPNAME);

      ODA_ASSERT_ONCE(pRasSvcs.get())
      if (pRasSvcs.isNull()) {
        throw OdError(eNotApplicable);
      }
      pRasSvcs->saveRasterImage(OdGiRasterImagePtr(pDevice->properties()->getAt(OD_T("RasterImage"))), dstFileName);
    }
    else
    {
      odPrintConsoleString(L"BMP skipped: inaccessible bitmap device.\n");
    }
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

  odDbRootUninitialize();
  /**********************************************************************/
  /* Uninitialize ODA SDK                                               */
  /**********************************************************************/
  odrxUninitialize();

  return nRes;
}
