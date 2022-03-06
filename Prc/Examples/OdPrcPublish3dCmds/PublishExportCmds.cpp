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
#include "Ed/EdCommandContext.h"
#include "DbAux/PrcCommandContext.h"
#include "DynamicLinker.h"
#include "MemoryStream.h"
#include "DbBaseHostAppServices.h"
#include "PrcPreviewGenerator.h"
#include "PrcExtentsCalculator.h"
#include "PrcCalculateUniqueNames.h"

#include "ExStringIO.h"
#include "ExPrcCommandContext.h"
#include "ExPrcHostAppServices.h"
#include "Ed/EdCommandStack.h"


// Publish 3D
OdResult PublishTemplate1(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGiRasterImagePtrArray& arrPreviewImg, const OdGeExtents3d& extPrc, const OdString& sOutPdf);
OdResult PublishTemplate2(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGiRasterImagePtrArray& arrPreviewImg, const OdGeExtents3d& extPrc, const OdString& sOutPdf, const OdStringArray& nodeNames);
OdResult PublishTemplate3(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGiRasterImagePtrArray& arrPreviewImg, const OdGeExtents3d& extPrc, const OdString& sOutPdf, const OdStringArray& nodeNames);
OdResult PublishTemplate4(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGeExtents3d& extPrc, const OdString& sOutPdf);
OdResult PublishTemplate5(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGeExtents3d& extPrc, const OdString& sOutPdf);
OdResult PublishTemplate6(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGeExtents3d& extPrc, const OdString& sOutPdf);
OdResult PublishTemplate7(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGeExtents3d& extPrc, const OdString& sOutPdf);
OdResult PublishTemplate8(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGiRasterImagePtrArray& arrPreviewImg, const OdGeExtents3d& extPrc, const OdString& sOutPdf);
OdResult PublishTemplate9(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGeExtents3d& extPrc, const OdString& sOutPdf);


static bool Publish3DCommon(OdEdCommandContext* pCmdCtx, OdUInt32 publishMode)
{
  ::odrxDynamicLinker()->loadApp(OdPdfPublishModuleName, false);

  OdPrcCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdPrcFilePtr pDb = pDbCmdCtx->database();
  OdEdBaseUserIO* pIO = (OdEdBaseUserIO*)pCmdCtx->userIO();

  OdStaticRxObject<OdExPrcHostAppServices> prcHostAppServ;
  if (pDb.isNull())
  {
    OdString pStreamPrc = pIO->getFilePath(L"PRC path", OdEd::kGfpForOpen, L"PRC path", L"PRC", L"", L"PRC files (*.prc)|*.prc");
    pDb = prcHostAppServ.readFile(pStreamPrc);
  }

  OdString pdfPath = pDbCmdCtx->dbUserIO()->getFilePath(L"PDF path", OdEd::kGfpForSave, L"PDF path", L"PDF", L"", L"PDF files (*.pdf)|*.pdf");

  {
    // generating previews
    OdGiRasterImagePtrArray arrRasImg;
    switch (publishMode)
    {
    case 1:
    case 2:
    case 3:
    case 8:
      OdPrcPreviewGeneratorPtr pPreviewGen = OdPrcPreviewGenerator::createObject();
      ODA_VERIFY(pPreviewGen->init(pDb) == eOk);

      pPreviewGen->setBackground(ODRGB(192, 220, 248));
      pPreviewGen->setBitmapSize(286, 150);

      ODA_VERIFY(pPreviewGen->generatePreviewSet(arrRasImg) == eOk);
      // end generating previews
      break;
    }

    OdStreamBufPtr pStreamPrc = pDbCmdCtx->arbitraryData("PrcStream");
    if (pStreamPrc.isNull()) //arbitrary data wasn't set
    {
      pStreamPrc = OdMemoryStream::createNew();
      pDb->writeFile(pStreamPrc);
    }
    ODA_ASSERT(!pStreamPrc.isNull());

    switch (publishMode)
    {
      case 1:
      {
        ODA_VERIFY(PublishTemplate1((OdDbBaseHostAppServices *)pDb->getAppServices(), pStreamPrc, arrRasImg, OdPrcExtentsCalculator::calculateExtents(pDb), pdfPath) == eOk);
        break;
      }
      case 2:
      {
        OdStringArray nodeArr = CalculateUniqueNames(pDb);
        ODA_VERIFY(PublishTemplate2((OdDbBaseHostAppServices *)pDb->getAppServices(), pStreamPrc, arrRasImg, OdPrcExtentsCalculator::calculateExtents(pDb), pdfPath, nodeArr) == eOk);
        break;
      }
      case 3:
      {
        OdStringArray nodeArr = CalculateUniqueNames(pDb);
        ODA_VERIFY(PublishTemplate3((OdDbBaseHostAppServices *)pDb->getAppServices(), pStreamPrc, arrRasImg, OdPrcExtentsCalculator::calculateExtents(pDb), pdfPath, nodeArr) == eOk);
        break;
      }
      case 4:
      {
        ODA_VERIFY(PublishTemplate4((OdDbBaseHostAppServices *)pDb->getAppServices(), pStreamPrc, OdPrcExtentsCalculator::calculateExtents(pDb), pdfPath) == eOk);
        break;
      }
      case 5:
      {
        ODA_VERIFY(PublishTemplate5((OdDbBaseHostAppServices *)pDb->getAppServices(), pStreamPrc, OdPrcExtentsCalculator::calculateExtents(pDb), pdfPath) == eOk);
        break;
      }
      case 6:
      {
        ODA_VERIFY(PublishTemplate6((OdDbBaseHostAppServices *)pDb->getAppServices(), pStreamPrc, OdPrcExtentsCalculator::calculateExtents(pDb), pdfPath) == eOk);
        break;
      }
      case 7:
      {
        ::odrxDynamicLinker()->loadModule("OdPrcExCommands", false);
        OdPrcFilePtr pPrcFile = prcHostAppServ.createDatabase();
        OdSmartPtr<ExStringIO> pStringIO = ExStringIO::create(L"");
        OdPrcCommandContextPtr pPrcCmdCtx = ExPrcCommandContext::createObject(pStringIO, pPrcFile);
        ODA_VERIFY(!::odedRegCmds()->lookupCmd("CREATECOMPLEXEXAMPLE").isNull());
        ::odedRegCmds()->executeCommand("CREATECOMPLEXEXAMPLE", pPrcCmdCtx);
        OdStreamBufPtr pOutStream = OdMemoryStream::createNew();
        pPrcFile->writeFile(pOutStream);
        ODA_VERIFY(PublishTemplate7((OdDbBaseHostAppServices *)pPrcFile->getAppServices(), pOutStream, OdPrcExtentsCalculator::calculateExtents(pPrcFile), pdfPath) == eOk);
        break;
      }
      case 8:
      {
        ODA_VERIFY(PublishTemplate8((OdDbBaseHostAppServices *)pDb->getAppServices(), pStreamPrc, arrRasImg, OdPrcExtentsCalculator::calculateExtents(pDb), pdfPath) == eOk);
        break;
      }
      case 9:
      {
        ODA_VERIFY(PublishTemplate9((OdDbBaseHostAppServices*)pDb->getAppServices(), pStreamPrc, OdPrcExtentsCalculator::calculateExtents(pDb), pdfPath) == eOk);
        break;
      }
      default:
        return false;
    }
  }

  return true;
}

void _PrcPublish3Dcase1_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 1));
}

void _PrcPublish3Dcase2_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 2));
}

void _PrcPublish3Dcase3_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 3));
}

void _PrcPublish3Dcase4_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 4));
}

void _PrcPublish3Dcase5_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 5));
}

void _PrcPublish3Dcase6_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 6));
}

void _PrcPublish3Dcase7_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 7));
}

void _PrcPublish3Dcase8_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 8));
}

void _PrcPublish3Dcase9_func(OdEdCommandContext* pCmdCtx)
{
  ODA_VERIFY(Publish3DCommon(pCmdCtx, 9));
}
