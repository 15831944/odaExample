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

#include "PrcCommon.h"
#include "DbCommandContext.h"
#include "DbEntity.h"
#include "PdfExport.h"
#include "ExStringIO.h"
#include "Ed/EdCommandStack.h"
#include "Gs/GsBaseVectorizeDevice.h"

#include "CmdPrcHostAppServices.h"
#include "ExPrcCommandContext.h"

#include "PrcDefaultContextForTD.h"

#include "PrcDefaultContextForBIM.h"

#include "PrcDefaultContextForDGN.h"

#include "ExtDbUtils.h"

#ifdef DGN_ENABLED
#include "DgUserIO.h"
#endif



using namespace TD_PDF_2D_EXPORT;

class PrcPublish3DFilter : public OdPrcContextForPdfExport
{
private:
  OdDbStubPtrArray m_selectedItems;

public:
  ODRX_DECLARE_MEMBERS(PrcPublish3DFilter);

  void setSelectedItems(const OdDbStubPtrArray &selectedItems)
  {
    m_selectedItems = selectedItems;
  }

  virtual bool shouldExportAsPRC (const OdGiDrawable *pDrawable,
    const OdGiPathNode *entity,
    const OdGsClientViewInfo *pView,
    OdUInt32 &viewportidx) const
  {
    viewportidx = 0;

    if (!pDrawable || !pDrawable->id())
      return false;

    for(OdUInt32 i = 0; i < m_selectedItems.size(); i++)
    {
      if (m_selectedItems[i] == pDrawable->id())
      {
        return true; // publish this item
      }
    }

    return false;
  }
};

ODRX_CONS_DEFINE_MEMBERS(PrcPublish3DFilter, OdPrcContextForPdfExport, RXIMPL_CONSTR);

class FilterInit
{
  public:
    FilterInit() { 
      ::odrxDynamicLinker()->loadApp(OdPrcModuleName, false);
      ::odrxDynamicLinker()->loadApp(OdPdfPublishModuleName, false);
      ::odrxDynamicLinker()->loadApp(OdPrcPublish3dCmdsModuleName, false);

      PrcPublish3DFilter::rxInit(); 
    }
    ~FilterInit() 
    { 
      PrcPublish3DFilter::rxUninit(); 

      ::odrxDynamicLinker()->unloadModule(OdPrcPublish3dCmdsModuleName);
      ::odrxDynamicLinker()->unloadModule(OdPdfPublishModuleName);
      ::odrxDynamicLinker()->unloadModule(OdDwg2PrcExportModuleName);
      ::odrxDynamicLinker()->unloadModule(OdDgn2PrcExportModuleName);
      ::odrxDynamicLinker()->unloadModule(OdBim2PrcExportModuleName);
      ::odrxDynamicLinker()->unloadModule(OdPrcModuleName);
    }
};

static bool Publish3DCommon(OdEdCommandContext* pCmdCtx, OdUInt32 publishMode)
{
  {
    /******************************************************************/
    /* Create a Pdf export module                                     */
    /******************************************************************/
    OdPdfExportModulePtr pModule = ::odrxDynamicLinker()->loadApp(OdPdfExportModuleName, false);

    OdDbBaseDatabasePtr pDb(pCmdCtx->baseDatabase());
    if (pDb.isNull())
    {
      return false;
    }

    OdEdUserIO* pIO = pCmdCtx->userIO();
    ODA_VERIFY(pIO);

    OdExtDbUtils::DbType dbType = OdExtDbUtils::getProduct(pDb);
    bool bIsBimDB = OdExtDbUtils::kDbBim == dbType;
    bool bIsTdDB = OdExtDbUtils::kDbDwg == dbType;
    bool bIsDgnDB = OdExtDbUtils::kDbDgn == dbType;

    bool bAllEnt = pIO->getKeyword(OD_T("Publish all geometry [Yes/No]"), OD_T("Yes No"), 0) == 0;
    bool bPrcMode = pIO->getKeyword(OD_T("Prc mode [Tess/Brep]"), OD_T("Tess Brep"), 0) == 0;
    OdDbStubPtrArray selectedItems;
    OdString tmp;
    tmp.format(L"Select entities for Publish 3D <done>:");

    if (bIsTdDB || bIsDgnDB)
    {
      OdSelectionSetIteratorPtr pIter;
      if (bIsTdDB)
      {
        ::odrxDynamicLinker()->loadApp(OdDwg2PrcExportModuleName, false);
        if (!bAllEnt)
        {
          pIter = ((OdDbUserIO*)pIO)->select(tmp, OdEd::kSelDefault)->newIterator();
        }
      }
      if (bIsDgnDB)
      {

#ifdef DGN_ENABLED
        ::odrxDynamicLinker()->loadApp(OdDgn2PrcExportModuleName, false);
        if (!bAllEnt)
        {
          OdString sIOClassName = pIO->isA()->name();
          bool bValidDbUserIO = sIOClassName == L"OdDbUserIO"; // valid situation in the case of ODA File Viewer, for example
          if (sIOClassName == L"OdDgUserIO" || bValidDbUserIO)
          {
            pIter = bValidDbUserIO ? ((OdDbUserIO*)pIO)->select(tmp, OdEd::kSelDefault)->newIterator() : ((OdDgUserIO*)pIO)->select(NULL, tmp, OdEd::kSelDefault)->newIterator();
          }
          else
          {
            ODA_VERIFY(!"Error! Unknown userIO!");
            return false;
          }
        }
#else
        ODA_VERIFY(!"Error! Unknown database!");
        return false;
#endif
        }
      if (!pIter.isNull())
      {
        for (; !pIter->done(); pIter->next())
        {
          selectedItems.append(pIter->id());
        }
      }
    }
    else if (bIsBimDB)
    {
      ::odrxDynamicLinker()->loadApp(OdBim2PrcExportModuleName, false);
    }
    else
    {
      ODA_VERIFY(!"Error! Unknown database!");
      return false;
    }

    FilterInit autoRx;

    OdPrcContextForPdfExportPtr pPrcContext;
    if (bIsBimDB)
    {
      pPrcContext = odCreatePrcAllInSingleViewContextForBIM();
    }
    else
    {
      if (bAllEnt)
      {
        if (bIsTdDB)
        {
          pPrcContext = odCreatePrcAllInSingleViewContextForTD(); 
        }
        else
        {
          pPrcContext = odCreatePrcAllInSingleViewContextForDGN();
        }
      }
      else
      {
        pPrcContext = PrcPublish3DFilter::createObject();
        ((PrcPublish3DFilter *)pPrcContext.get())->setSelectedItems(selectedItems);
      }
    }

    OdString pdfPath = pIO->getFilePath(L"PDF path", OdEd::kGfpForSave,L"PDF path", L"PDF", L"", L"PDF files (*.pdf)|*.pdf");

    {
      OdPdfExportPtr exporter = pModule->create();
      PRCStreamsMap outStreamsPRC;
      PDFExportParams publishParams;
      publishParams.setDatabase(pDb);
      pPrcContext->setWritePdfFile(false);
      publishParams.setPRCContext(pPrcContext);
      publishParams.setPRCMode(bPrcMode ? PDFExportParams::kAsMesh : PDFExportParams::kAsBrep);

      OdUInt32 errCode = exporter->publish3d(publishParams, outStreamsPRC);
      if (errCode != 0)
      {
        OdString errMes = exporter->exportPdfErrorCode(errCode);
        printf("\nexportPdf error returned : 0x%x. \n%s", (unsigned)errCode, (const char*)errMes);
      }

      if (outStreamsPRC.empty())
      {
        return false;
      }

      OdStreamBufPtr pStreamPrc = outStreamsPRC.begin()->second;
      pStreamPrc->rewind();


      OdStaticRxObject<OdCmdPrcHostAppServices> prcHostAppServ;

      OdDbBaseDatabasePEPtr pPE = OdDbBaseDatabasePE::cast(pDb);
      if (!pPE.isNull())
      {
        OdDbBaseHostAppServices* pHost = pPE->appServices(pDb);
        if (NULL != pHost)
        {
          prcHostAppServ.setSourceHostAppServices(pHost);
        }
      }

      OdPrcFilePtr pPrcFile = prcHostAppServ.readFile(pStreamPrc);

      OdSmartPtr<ExStringIO> pStringIO = ExStringIO::create(pdfPath);
      OdPrcCommandContextPtr pPrcCmdCtx = ExPrcCommandContext::createObject(pStringIO, pPrcFile);
      pPrcCmdCtx->setArbitraryData("PrcStream", pStreamPrc);

      switch (publishMode)
      {
        case 1:
        {
          ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE1").isNull());
          ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE1", pPrcCmdCtx);
          break;
        }
        case 2:
        {
          ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE2").isNull());
          ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE2", pPrcCmdCtx);
          break;
        }
        case 3:
        {
          ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE3").isNull());
          ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE3", pPrcCmdCtx);
          break;
        }
        case 4:
        {
          ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE4").isNull());
          ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE4", pPrcCmdCtx);
          break;
        }
        case 5:
        {
          ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE5").isNull());
          ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE5", pPrcCmdCtx);
          break;
        }
        case 6:
        {
          ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE6").isNull());
          ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE6", pPrcCmdCtx);
          break;
        }
        case 7:
        {
          ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE7").isNull());
          ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE7", pPrcCmdCtx);
          break;
        }
        case 8:
        {
          ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE8").isNull());
          ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE8", pPrcCmdCtx);
          break;
        }
        case 9:
        {
          ODA_VERIFY(!::odedRegCmds()->lookupCmd("PRCPUBLISH3DCASE9").isNull());
          ::odedRegCmds()->executeCommand("PRCPUBLISH3DCASE9", pPrcCmdCtx);
          break;
        }
        default:
          return false;
      }
    }
  }

  return true;
}

void _Publish3Dcase1_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 1));
}

void _Publish3Dcase2_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 2));
}

void _Publish3Dcase3_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 3));
}

void _Publish3Dcase4_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 4));
}

void _Publish3Dcase5_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 5));
}

void _Publish3Dcase6_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 6));
}

void _Publish3Dcase7_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 7));
}

void _Publish3Dcase8_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 8));
}

void _Publish3Dcase9_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 9));
}
