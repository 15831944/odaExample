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
#include "OdPdfExportWithPrcStart.h"
#include "DbDatabase.h"
#include "Db3dSolid.h"
#include "DbBlockTableRecord.h"
#include "PdfExport.h"
#include "DbHostAppServices.h"
#include "PrcDefaultContextForTD.h"

using namespace TD_PDF_2D_EXPORT;

void fillDatabase(OdDbDatabasePtr &pDb)
{
  OdDb3dSolidPtr pSolid = OdDb3dSolid::createObject();
  pSolid->setDatabaseDefaults(pDb);
  pSolid->createBox(10,10,10);

  OdCmColor red;
  red.setRGB(255,0,0);
  pSolid->setColor(red);

  OdGeMatrix3d mx;
  mx.setToRotation(45, OdGeVector3d::kXAxis);
  pSolid->transformBy(mx);
  mx.setToRotation(45, OdGeVector3d::kYAxis);
  pSolid->transformBy(mx);

  OdDbBlockTableRecordPtr pRecord = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
  pRecord->appendOdDbEntity(pSolid);
}

void fillDatabaseWithSeveralEntities(OdDbDatabasePtr &pDb)
{
  // box
  OdDb3dSolidPtr pSolid;
  pSolid = OdDb3dSolid::createObject();
  pSolid->setDatabaseDefaults(pDb);
  pSolid->createBox(1.0, 1.0, 1.0);

  OdCmColor red;
  red.setRGB(255 , 0, 0);
  pSolid->setColor(red);

  OdDbBlockTableRecordPtr pRecord = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
  pRecord->appendOdDbEntity(pSolid);

  // cylinder
  pSolid = OdDb3dSolid::createObject();
  pSolid->setDatabaseDefaults(pDb);
  pSolid->createFrustum(2.0, 0.5, 0.5, 0.5);

  OdCmColor green;
  green.setRGB(0, 255, 0);
  pSolid->setColor(green);

  OdGeMatrix3d mx;
  mx.setToTranslation(OdGeVector3d(2.0, 0.0, 0.0));
  pSolid->transformBy(mx);

  pRecord->appendOdDbEntity(pSolid);

  // cone
  pSolid = OdDb3dSolid::createObject();
  pSolid->setDatabaseDefaults(pDb);
  pSolid->createFrustum(2.0, 0.5, 0.5, 0);

  OdCmColor blue;
  blue.setRGB(0, 0, 255);
  pSolid->setColor(blue);

  mx.setToTranslation(OdGeVector3d(0.0, 2.0, 0.0));
  pSolid->transformBy(mx);

  pRecord->appendOdDbEntity(pSolid);

  // torus
  pSolid = OdDb3dSolid::createObject();
  pSolid->setDatabaseDefaults(pDb);
  pSolid->createTorus(1.0, 0.2);

  OdCmColor magenta;
  magenta.setRGB(255, 0, 255);
  pSolid->setColor(magenta);

  mx.setToRotation(45, OdGeVector3d::kXAxis);
  pSolid->transformBy(mx);
  mx.setToRotation(45, OdGeVector3d::kYAxis);
  pSolid->transformBy(mx);

  pRecord->appendOdDbEntity(pSolid);
}

void OdPdfExportWithPrc(OdDbHostAppServices &svcs, OdString pdfPath, PDFExportParams::PRCSupport flags, bool shouldUseSingleViewMode, void (*fillerfunc)(OdDbDatabasePtr &pDb))
{
  /******************************************************************/
  /* Create a Pdf export module                                     */
  /******************************************************************/
  OdPdfExportModulePtr pModule = ::odrxDynamicLinker()->loadApp(OdPdfExportModuleName, false);

  ::odrxDynamicLinker()->loadApp(OdPrcModuleName, false);
  ::odrxDynamicLinker()->loadApp(OdDwg2PrcExportModuleName, false);

  /******************************************************************/
  /* Create a database and load the drawing into it.                */
  /******************************************************************/

  OdDbDatabasePtr pDb = svcs.createDatabase();
  fillerfunc(pDb);

  {
    /****************************************************************/
    /* Initialize the conversion parameters                         */
    /****************************************************************/

    OdPdfExportPtr exporter = pModule->create();

    PDFExportParams params;

    params.setDatabase(pDb);
    params.setVersion(PDFExportParams::kPDFv1_6);
    params.setOutput(odSystemServices()->createFile(pdfPath, Oda::kFileWrite, Oda::kShareDenyNo, Oda::kCreateAlways));

    params.setExportFlags(PDFExportParams::PDFExportFlags(PDFExportParams::kDefault));

    params.setTitle("Batch PDF File");
    params.setAuthor("OdPdfExportWithPrc");
    params.setCreator("Open Design Alliance");
    params.setPRCMode(flags);
    OdPrcContextForPdfExportPtr pContext = (shouldUseSingleViewMode) ? odCreatePrcAllInSingleViewContextForTD() : odCreatePrcDefaultContextForTD();
    params.setPRCContext(pContext);

    /****************************************************************/
    /* Initialize the conversion parameters: Layouts                */
    /****************************************************************/

    OdDbBlockTableRecordPtr pLayoutBlock = pDb->getActiveLayoutBTRId().safeOpenObject();
    OdDbLayoutPtr pLayout = pLayoutBlock->getLayoutId().safeOpenObject();
    params.layouts().push_back(pLayout->getLayoutName());

    params.pageParams().resize(1, OdGsPageParams());

    OdUInt32 errCode = exporter->exportPdf(params);
    if (errCode != 0)
    {
      OdString errMes = exporter->exportPdfErrorCode(errCode);
      printf("\nexportPdf error returned : 0x%x. \n%s", (unsigned)errCode, (const char*)errMes);     
    }
  }
}

void OdPdfExportWithPrcWithBackground(OdDbHostAppServices &svcs, OdString pdfPath, PDFExportParams::PRCSupport flags, bool shouldUseSingleViewMode, void(*fillerfunc)(OdDbDatabasePtr &pDb))
{
  /******************************************************************/
  /* Create a Pdf export module                                     */
  /******************************************************************/
  OdPdfExportModulePtr pModule = ::odrxDynamicLinker()->loadApp(OdPdfExportModuleName, false);

  ::odrxDynamicLinker()->loadApp(OdPrcModuleName, false);
  ::odrxDynamicLinker()->loadApp(OdDwg2PrcExportModuleName, false);

  /******************************************************************/
  /* Create a database and load the drawing into it.                */
  /******************************************************************/

  OdDbDatabasePtr pDb = svcs.createDatabase();
  fillerfunc(pDb);

  {
    /****************************************************************/
    /* Initialize the conversion parameters                         */
    /****************************************************************/

    OdPdfExportPtr exporter = pModule->create();

    PDFExportParams params;

    params.setDatabase(pDb);
    params.setVersion(PDFExportParams::kPDFv1_6);
    params.setOutput(odSystemServices()->createFile(pdfPath, Oda::kFileWrite, Oda::kShareDenyNo, Oda::kCreateAlways));

    params.setExportFlags(PDFExportParams::PDFExportFlags(PDFExportParams::kDefault));

    params.setTitle("Batch PDF File");
    params.setAuthor("OdPdfExportWithPrc");
    params.setCreator("Open Design Alliance");
    params.setPRCMode(flags);
    OdPrcContextForPdfExportPtr pContext = (shouldUseSingleViewMode) ? odCreatePrcAllInSingleViewContextForTD() : odCreatePrcDefaultContextForTD();
    params.setPRCContext(pContext);
    params.setPrcBackground(0x0000ffff); // 00 ff ff => teal background should appear when file is opened

    /****************************************************************/
    /* Initialize the conversion parameters: Layouts                */
    /****************************************************************/

    OdDbBlockTableRecordPtr pLayoutBlock = pDb->getActiveLayoutBTRId().safeOpenObject();
    OdDbLayoutPtr pLayout = pLayoutBlock->getLayoutId().safeOpenObject();
    params.layouts().push_back(pLayout->getLayoutName());

    params.pageParams().resize(1, OdGsPageParams());

    OdUInt32 errCode = exporter->exportPdf(params);
    if (errCode != 0)
    {
      OdString errMes = exporter->exportPdfErrorCode(errCode);
      printf("\nexportPdf error returned : 0x%x. \n%s", (unsigned)errCode, (const char*)errMes);
    }
  }
}

void OdPdfExportWithPrc(OdDbHostAppServices &svcs, OdString pdfPath)
{
  OdPdfExportWithPrc(svcs, pdfPath, PDFExportParams::kAsMesh, false, fillDatabase);
}

void OdPdfExportWithPrcSeveralEnteties(OdDbHostAppServices &svcs, OdString pdfPath)
{
  OdPdfExportWithPrc(svcs, pdfPath, PDFExportParams::kAsBrep, true, fillDatabaseWithSeveralEntities);
}

void OdPdfExportWithPrcWithBackground(OdDbHostAppServices &svcs, OdString pdfPath)
{
  OdPdfExportWithPrcWithBackground(svcs, pdfPath, PDFExportParams::kAsMesh, true, fillDatabase);
}

#define ODPRCEXPORTCASE(name, description) void name(OdDbHostAppServices &svcs, OdString pdfPath);
#include "ExampleCases.h"

void OdPdfExportWithPrcStart(OdDbHostAppServices &svcs, OdString pdfPath, ExportMode emode)
{
#define ODPRCEXPORTCASE(name, description) if (emode == k##name) name(svcs, pdfPath); else
#include "ExampleCases.h"
  ODA_ASSERT(false);
}
