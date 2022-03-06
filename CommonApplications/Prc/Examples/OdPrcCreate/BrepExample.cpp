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
#include "DbHostAppServices.h"
#include "Db3dSolid.h"
#include "DbDatabase.h"
#include "DbBlockTableRecord.h"
#include "Br/BrBrep.h"
#include "OdPrcCreateStart.h"
#include "Pdf2PrcExportParams.h"
#include "PrcExport.h"
#include "PdfExportService.h"

#if 0
#include "ColorMapping.h"
#include "PdfExport.h"
#include "PrcDefaultContextForTD.h"
#include "ExPrintConsole.h"
using namespace TD_PDF_2D_EXPORT;

void getPrcViaPdfExport(PRCStreamsMap & outStreamsPRC, PDFExportParams & publishParams)
{
  // create a pdf export module
  OdPdfExportModulePtr pModule = ::odrxDynamicLinker()->loadApp(OdPdfExportModuleName, false);
  ::odrxDynamicLinker()->loadApp(OdPrcModuleName, false);
  ::odrxDynamicLinker()->loadApp(OdPrcExportModuleName, false);

  publishParams.setPRCContext(odCreatePrcAllInSingleViewContextForTD());

  // initialize the conversion parameters
  OdPdfExportPtr exporter = pModule->create();
  OdUInt32 errCode = exporter->publish3d(publishParams, outStreamsPRC);
  if (errCode != 0)
  {
    OdString errMes = exporter->exportPdfErrorCode(errCode);
    throw OdError(OdString().format(L"\nexportPdf error returned : 0x%x. \n%ls\n", (unsigned)errCode, errMes.c_str()));
  }
}

void brepExample(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pHostApp)
{
  OdDb3dSolidPtr p3dSolid = OdDb3dSolid::createObject();

  if (mode == kBrepSphere)
  {
    p3dSolid->createSphere(10);
  }
  if (mode == kBrepBox)
  {
    p3dSolid->createBox(10, 20, 30);
  }

  OdDbDatabasePtr pDb = pH.createDatabase();
  OdDbBlockTableRecordPtr pRec = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
  pRec->appendOdDbEntity(p3dSolid);

  PRCStreamsMap outStreamsPRC;
  PDFExportParams publishParams;
  publishParams.setPalette(odcmAcadDarkPalette());
  publishParams.setDatabase(pDb);
  publishParams.setPRCMode(PDFExportParams::kAsBrep);
  getPrcViaPdfExport(outStreamsPRC, publishParams);

  std::map<OdUInt32, OdStreamBufPtr>::iterator pIt = outStreamsPRC.find(0);
  if (pIt == outStreamsPRC.end())
  {
    throw OdError(L"\nRESULT PRC MISSING!\n");
  }
  pIt->second->rewind();
  pIt->second->copyDataTo(pPrcStream);
}
#else
void brepExample(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  OdDb3dSolidPtr p3dSolid = OdDb3dSolid::createObject();

  if (mode == kBrepSphere)
  {
    p3dSolid->createSphere(10);
  }
  if (mode == kBrepBox)
  {
    p3dSolid->createBox(10, 20, 30);
  }

  OdDbDatabasePtr pDb = pH.createDatabase();
  OdDbBlockTableRecordPtr pRec = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
  pRec->appendOdDbEntity(p3dSolid);

  PDF2PRCExportParams params;

  odrxDynamicLinker()->loadModule(OdDwg2PrcExportModuleName);
  PdfExportServiceInterfacePtr pExportIFace = getPdfExportService();

  OdRxObjectPtr pContext = pExportIFace->createPrcExportContext(pDb);
  OdResult res = pExportIFace->exportPrc(pContext, p3dSolid, &params);
  if (res != eOk)
  {
    throw OdError(res);
  }
  res = pExportIFace->serialize(pPrcStream, pContext, &params);
  if (res != eOk)
  {
    throw OdError(res);
  }
}

#endif
