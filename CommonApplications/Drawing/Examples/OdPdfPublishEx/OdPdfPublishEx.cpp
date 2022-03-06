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
/* This console application saves                                       */
/* the PDF files with the specified export options                      */
/*                                                                      */
/*                                                                      */
/* Calling sequence:                                                    */
/*                                                                      */
/*    OdPdfPublishEx <source file> <target file> <options>              */
/************************************************************************/


#ifdef WD_WIN_SYSTEM
#include <io.h>
#include <direct.h>
#endif

#include <stdlib.h>

#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a


#include "PrcCommon.h"
#include "ExSystemServices.h"
#include "ExHostAppServices.h"
#include "RxDynamicModule.h"
#include "ExStringIO.h"
#include "Ed/EdCommandStack.h"

#include "ExPrcHostAppServices.h"
#include "ExPrcCommandContext.h"

#include <locale.h>

#if defined(BIM_ENABLED) && defined(_TOOLKIT_IN_DLL_)
#include "BimCommon.h"
#include "DbBaseHostAppServices.h"
#include "BmHostAppServices.h"
#include "ExBimHostAppServices.h"
#include "BmDatabase.h"
#endif

#ifdef DGN_ENABLED
#include "DgHostAppServices.h"
#include "ExDgnServices.h"
#include "ExDgnHostAppServices.h"
#include "DgDatabase.h"
#endif

#ifdef ODA_WINDOWS
#include <tchar.h>
#endif

#ifdef OD_HAVE_CONSOLE_H_FILE
#include <console.h>
#endif

/************************************************************************/
/* Define a module map for statically linked modules:                   */
/************************************************************************/
#ifndef _TOOLKIT_IN_DLL_

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(RasterExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(BitmapModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPdfExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRecomputeDimBlockModule);
#if defined(OD_HAS_OPENGL)
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(WinOpenGLModule);
#endif
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);
#ifdef DGN_ENABLED
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDgnModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDgn7IOModuleImpl);   //this library allows to read V7 files
#endif
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRasterProcessingServicesImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(PdfPublishModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcPublish3dCmdsModule);

ODRX_BEGIN_STATIC_MODULE_MAP()
  ODRX_DEFINE_STATIC_APPMODULE(OdRasterExportModuleName,          RasterExportModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdWinBitmapModuleName,             BitmapModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdPdfExportModuleName,             OdPdfExportModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdRecomputeDimBlockModuleName,   OdRecomputeDimBlockModule)
#if defined(OD_HAS_OPENGL)
  ODRX_DEFINE_STATIC_APPMODULE(OdWinOpenGLModuleName,             WinOpenGLModule)
#endif
#ifdef DGN_ENABLED
  ODRX_DEFINE_STATIC_APPLICATION(OdDgnDbModuleName,               OdDgnModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdDgn7IOModuleName,              OdDgn7IOModuleImpl)
#endif
  ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME,        ExRasterModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName,       OdRasterProcessingServicesImpl)
  ODRX_DEFINE_STATIC_APPMODULE(OdPdfPublishModuleName,            PdfPublishModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdPrcModuleName,                   OdPrcModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdPrcPublish3dCmdsModuleName,      OdPrcPublish3dCmdsModule)
ODRX_END_STATIC_MODULE_MAP()

#endif

//----------------------------------------------------------------------------------

class MyServices : public ExSystemServices, public ExHostAppServices
{
public:
  OdGsDevicePtr gsBitmapDevice(OdRxObject* /*pViewObj*/, OdDbBaseDatabase* /*pDb*/, OdUInt32 flags)
  {

    try
    {
      OdGsModulePtr pM;
      if (GETBIT(flags, kFor2dExportRender))
      {
        // Don't export HiddenLine viewports as bitmap in Pdf/Dwf/Svg exports.
        if (GETBIT(flags, kFor2dExportRenderHLR))
          return OdGsDevicePtr();
        // Try to export shaded viewports using OpenGL device.
        pM = ::odrxDynamicLinker()->loadModule(OdWinOpenGLModuleName);
      }
      // Use currently selected device for thumbnails and etc.
      if (pM.isNull())
        pM = ::odrxDynamicLinker()->loadModule(OdWinBitmapModuleName);
      if (pM.isNull())
        return OdGsDevicePtr();
      // Create device.
      return pM->createBitmapDevice();
    }
    catch (const OdError&)
    {
    }
    return OdGsDevicePtr();
  }
};

OdResult OdPdfPublishControlsEx(OdDbBaseHostAppServices* pHostApp, const OdString& sOutPdf);
OdResult OdPdfPublishCADEx(OdDbBaseHostAppServices* pHostApp, OdDbBaseDatabase *pDatabase, const OdString& sServiceCaption, const OdString& sOutPdf, const OdString& sInputFileName);

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#ifdef OD_HAVE_CCOMMAND_FUNC
  argc = ccommand(&argv);
#endif

  if (argc < 3)
  {
    STD(cout) << "usage: OdPdfPublishEx <source file> <target file> [options] [--outputfile]" << STD(endl)
      << "options could be:" << STD(endl)
      << " --mode prc2pdf --- convert prc to pdf" << STD(endl)
      << " --mode dwg2pdf2d --- convert DWG to pdf 2D" << STD(endl)
#ifdef DGN_ENABLED
      << " --mode dgn2pdf2d --- convert DGN to pdf 2D" << STD(endl)
#endif
#if defined(BIM_ENABLED) && defined(_TOOLKIT_IN_DLL_)
      << " --mode bim2pdf2d --- convert BIM to pdf 2D" << STD(endl)
#endif
      << " --outputfile --- makes target file name precisely like <target file> " << STD(endl)
      ;
  }
  else
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
    OdStaticRxObject<MyServices> svcs;
    odInitialize(&svcs);
    {

      /********************************************************************/
      /* Display the Product and Version that created the executable      */
      /********************************************************************/
      STD(cout) << "Developed using " << (const char*)svcs.product() << ", " << (const char*)svcs.versionString() << STD(endl);

      /********************************************************************/
      /* Process command line parameters                                  */
      /********************************************************************/
      //////////////////////////////////////////////////////////////////////////
      OdString sIn(argv[1]);
      OdString sOutFile(argv[2]);

      bool bPRC2PDF = false;
      bool bDWG2PDF2D = false;
      bool bDGN2PDF2D = false;
      bool bBIM2PDF2D = false;

      STD(map) < OdString, OdString > paramsMap;
      int curIndex = 3;
      int outputfileFlag = 0;
      OdString lastArg(argv[argc - 1]);

      if (!odStrICmp(lastArg, OD_T("--outputfile")))
      {
       outputfileFlag = 1;
      }
      if ((argc - outputfileFlag - curIndex) % 2)
      {
        STD(cout) << "Wrong options count." << STD(endl);
        return 1;
      }
      while (curIndex + 1 < argc)
      {
        paramsMap[OdString(argv[curIndex])] = OdString(argv[curIndex + 1]);
        curIndex += 2;
      }

      STD(map) < OdString, OdString > ::iterator iterMode = paramsMap.find(L"--mode");
      if (iterMode != paramsMap.end())
      {
        if (iterMode->second == L"prc2pdf")
        {
          bPRC2PDF = true;
        }
        else
          if (iterMode->second == L"dwg2pdf2d")
          {
            bDWG2PDF2D = true;
          }
#ifdef DGN_ENABLED
          else
            if (iterMode->second == L"dgn2pdf2d")
            {
              bDGN2PDF2D = true;
            }
#endif
            else
              if (iterMode->second == L"bim2pdf2d")
              {
#if defined(BIM_ENABLED) && defined(_TOOLKIT_IN_DLL_)
                bBIM2PDF2D = true;
#else
                STD(cout) << "BimRv isn't avaliable on this platform." << STD(endl);
                return 0;
#endif
              }
              else
              {
                STD(cout) << "Wrong mode option." << STD(endl);
                return 1;
              }
      }
      else
      {
        STD(cout) << "Wrong mode options" << STD(endl);
        return 1;
      }
      //////////////////////////////////////////////////////////////////////////

      OdRxModulePtr pModule = ::odrxDynamicLinker()->loadApp(OdPdfPublishModuleName, false);

      if (bPRC2PDF)
      {
        OdRxModulePtr pModulePrc = ::odrxDynamicLinker()->loadApp(OdPrcModuleName, false);
        OdRxModulePtr pModulePublCmds = ::odrxDynamicLinker()->loadApp(OdPrcPublish3dCmdsModuleName, false);

        OdStreamBufPtr pStreamPrc = odrxSystemServices()->createFile(sIn, Oda::kFileRead);

        OdStaticRxObject<OdExPrcHostAppServices> prcHostAppServ;
        OdPrcFilePtr pPrcFile = prcHostAppServ.readFile(pStreamPrc);

        OdString sOutTemplate1(sOutFile + L"Template1.pdf"),
          sOutTemplate2(sOutFile + L"Template2.pdf"),
          sOutTemplate3(sOutFile + L"Template3.pdf"),
          sOutTemplate4(sOutFile + L"Template4.pdf"),
          sOutTemplate5(sOutFile + L"Template5.pdf"),
          sOutTemplate6(sOutFile + L"Template6.pdf"),
          sOutTemplate9(sOutFile + L"Template9.pdf");

        OdSmartPtr<ExStringIO> pStringIO = ExStringIO::create(sOutTemplate1 + L"\n" + sOutTemplate2 + L"\n" + sOutTemplate3 + L"\n" + sOutTemplate4 + L"\n" + 
          sOutTemplate5 + L"\n" + sOutTemplate6 + L"\n" + sOutTemplate9);
        OdPrcCommandContextPtr pPrcCmdCtx = ExPrcCommandContext::createObject(pStringIO, pPrcFile);

        ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE1").isNull());
        ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE2").isNull());
        ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE3").isNull());
        ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE4").isNull());
        ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE5").isNull());
        ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE6").isNull());
        ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE9").isNull());

        ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE1", pPrcCmdCtx);
        ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE2", pPrcCmdCtx);
        ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE3", pPrcCmdCtx);
        ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE4", pPrcCmdCtx);
        ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE5", pPrcCmdCtx);
        ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE6", pPrcCmdCtx);
        ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE9", pPrcCmdCtx);

        if (outputfileFlag == 0)
        {
          ODA_VERIFY(::eOk == OdPdfPublishControlsEx(&svcs, sOutFile + L"PdfPublishControlsEx.pdf"));
        }
        else
        {
         ODA_VERIFY(::eOk == OdPdfPublishControlsEx(&svcs, sOutFile));
        }

      } //bPRC2PDF

      if (bDWG2PDF2D)
      {
        OdDbDatabasePtr pDb = svcs.readFile(sIn, false, false);
        ODA_VERIFY(!pDb.isNull());
        if (outputfileFlag == 0)
        {
          ODA_VERIFY(::eOk == OdPdfPublishCADEx(&svcs, pDb, L"DWG", sOutFile + L"PdfPublishDWG2DEx.pdf", sIn));
        }
        else
        {
         ODA_VERIFY(::eOk == OdPdfPublishCADEx(&svcs, pDb, L"DWG", sOutFile, sIn));
        }

      } //bDWG2PDF2D

      if (bDGN2PDF2D)
      {
#ifdef DGN_ENABLED
        ::odrxDynamicLinker()->loadModule(OdDgnDbModuleName, false);
        OdStaticRxObject<OdDgHostAppServices> dgnSvc;
        OdDgDatabasePtr pDgnDb = dgnSvc.readFile(sIn, Oda::kShareDenyRead);
        ODA_VERIFY(!pDgnDb.isNull());
        if (outputfileFlag == 0)
        {
          ODA_VERIFY(::eOk == OdPdfPublishCADEx(&svcs, pDgnDb, L"DGN", sOutFile + L"PdfPublishDGN2DEx.pdf", sIn));
        }
        else
        {
          ODA_VERIFY(::eOk == OdPdfPublishCADEx(&svcs, pDgnDb, L"DGN", sOutFile, sIn));
        }
#endif
      } //bDGN2PDF2D

      if (bBIM2PDF2D)
      {
#if defined(BIM_ENABLED) && defined(_TOOLKIT_IN_DLL_)
        ::odrxDynamicLinker()->loadModule(OdBmBaseModuleName, false);
        ::odrxDynamicLinker()->loadModule(OdBmLoaderModuleName, false);
        ::odrxDynamicLinker()->loadModule(OdBmLabelUtils, false);

        OdStaticRxObject<OdExBimHostAppServices> bimSvc;
        OdBmDatabasePtr pBmDb = bimSvc.readFile(sIn, Oda::kShareDenyRead);
        ODA_VERIFY(!pBmDb.isNull());
        if (outputfileFlag == 0)
        {
          ODA_VERIFY(::eOk == OdPdfPublishCADEx(&svcs, pBmDb, L"BIM", sOutFile + L"PdfPublishBIM2DEx.pdf", sIn));
        }
        else
        {
          ODA_VERIFY(::eOk == OdPdfPublishCADEx(&svcs, pBmDb, L"BIM", sOutFile, sIn));
        }
#endif
      } //bBIM2PDF2D

    }
    odUninitialize();

  } //argc >=3

  return 0;
}
