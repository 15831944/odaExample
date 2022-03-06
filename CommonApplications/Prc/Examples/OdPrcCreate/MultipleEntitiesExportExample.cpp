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
#include "DbBlockTableRecord.h"
#include "OdPrcCreateStart.h"
#include "PrcExport.h"
#include "PdfExportService.h"

#if 0
#include "ColorMapping.h"
#include "PdfExport.h"
#include "PrcDefaultContextForTD.h"
#include "ExPrintConsole.h"
using namespace TD_PDF_2D_EXPORT;

void getPrcViaPdfExport(PRCStreamsMap & outStreamsPRC, PDFExportParams & publishParams);

void multipleEntitiesExportExample(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  //prepare database
  OdDbDatabasePtr pDb = pH.createDatabase();
  OdDbBlockTableRecordPtr pRec = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

  // create 3 solid objects and export them
  for (OdUInt32 i = 0; i < 3; ++i)
  {
    //create entity and add it to database
    OdDb3dSolidPtr p3dSolid = OdDb3dSolid::createObject();
    p3dSolid->createFrustum(i+1, 1.0, 1.0, 0.0);
    pRec->appendOdDbEntity(p3dSolid);
  }

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

void multipleEntitiesExportExample(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  // load module
  odrxDynamicLinker()->loadModule(OdDwg2PrcExportModuleName, false);

  //setup export parameters
  PDF2PRCExportParams params;

  //prepare database
  OdDbDatabasePtr pDb = pH.createDatabase();
  OdDbBlockTableRecordPtr pRec = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);

  PdfExportServiceInterfacePtr pExportIFace = getPdfExportService();
  OdRxObjectPtr pContext = pExportIFace->createPrcExportContext(pDb);

  // create 3 solid objects and export them
  for (OdUInt32 i = 0; i < 3; ++i)
  {
    //create entity and add it to database
    OdDb3dSolidPtr p3dSolid = OdDb3dSolid::createObject();
    p3dSolid->createFrustum(i + 1, 1.0, 1.0, 0.0);
    pRec->appendOdDbEntity(p3dSolid);

    //export entity
    OdResult res = pExportIFace->exportPrc(pContext, p3dSolid, &params);
    if (res != eOk)
    {
      throw OdError(res);
    }
  }

  //get PrcFile
  OdResult res = pExportIFace->serialize(pPrcStream, pContext, &params);
  if (res != eOk)
  {
    throw OdError(res);
  }
}

#endif
