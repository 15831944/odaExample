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
#include "PdfExport.h"
#include "DbDatabase.h"
#include "DbHostAppServices.h"
#include "DbBlockTableRecord.h"
#include "PrcContextForPdfExport.h"
#include "DbPolyline.h"
#include "StaticRxObject.h"
#include "DbLayerTableRecord.h"
#include "DbLayerTable.h"
#include "PrcDefaultContextForTD.h"

using namespace TD_PDF_2D_EXPORT;

#define FRAME_LAYER "Frame"

void fillDatabaseWithSeveralEntities(OdDbDatabasePtr &pDb);

static void fillpoly(OdDbPolylinePtr pPoly, double x, double y, double x2, double y2)
{
  pPoly->addVertexAt(0, OdGePoint2d(x, y));
  pPoly->addVertexAt(0, OdGePoint2d(x, y2));
  pPoly->addVertexAt(0, OdGePoint2d(x2, y2));
  pPoly->addVertexAt(0, OdGePoint2d(x2, y));
  pPoly->addVertexAt(0, OdGePoint2d(x, y));
}

static OdDbObjectId addLayer(OdDbDatabase* pDb, const OdString& name)
{
  /**********************************************************************/
  /* Open the layer table                                               */
  /**********************************************************************/
  OdDbLayerTablePtr pLayers = pDb->getLayerTableId().safeOpenObject(OdDb::kForWrite);

  /**********************************************************************/
  /* Create a layer table record                                        */
  /**********************************************************************/
  OdDbLayerTableRecordPtr pLayer = OdDbLayerTableRecord::createObject();

  /**********************************************************************/
  /* Layer must have a name before adding it to the table.              */
  /**********************************************************************/
  pLayer->setName(name);

  /**********************************************************************/
  /* Add the record to the table.                                       */
  /**********************************************************************/
  return pLayers->add(pLayer);
} 

static void addFrame(OdDbDatabasePtr &pDb)
{
  OdDbBlockTableRecordPtr pRecord = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
  OdDbObjectId layer = addLayer(pDb, FRAME_LAYER);

  OdDbPolylinePtr pPoly = OdDbPolyline::createObject();
  fillpoly(pPoly, -2, -2, 3, 3);
  pPoly->setLayer(layer);
  pRecord->appendOdDbEntity(pPoly);

  pPoly = OdDbPolyline::createObject();
  fillpoly(pPoly, -3, -3, 4, 4);
  pPoly->setLayer(layer);
  pRecord->appendOdDbEntity(pPoly);

  pPoly = OdDbPolyline::createObject();
  fillpoly(pPoly, -2.5,  -2.5, 3.5,   3.5);
  pPoly->setLayer(layer);
  pRecord->appendOdDbEntity(pPoly);

  pPoly = OdDbPolyline::createObject();
  fillpoly(pPoly, -1.9,  -1.9, 2.9,   2.9);
  pPoly->setColorIndex(5);
  pRecord->appendOdDbEntity(pPoly);

}

static OdDbDatabasePtr fillDatabase(OdDbHostAppServices &svcs)
{
  OdDbDatabasePtr pDb = svcs.createDatabase();

  fillDatabaseWithSeveralEntities(pDb);
  addFrame(pDb);

  return pDb;
}

class PrcLayerFilter : public OdPrcContextForPdfExport
{
  ODRX_DECLARE_MEMBERS(PrcLayerFilter);

  virtual bool shouldExportAsPRC (const OdGiDrawable *pDrawable,
    const OdGiPathNode *entity,
    const OdGsClientViewInfo *pView,
    OdUInt32 &viewportidx) const
  {
    viewportidx = 0;

    OdDbEntityPtr pEnt = OdDbEntity::cast(pDrawable);
    if (pEnt.isNull())
      return false; // to PDF

    if (pEnt->layer() == FRAME_LAYER)
      return false; // to pdf

    return true;
  }
};


void fillPdfExportParams(PDFExportParams &params, OdDbDatabasePtr pDb, OdString pdfPath)
{
  params.setDatabase(pDb);
  params.setVersion(PDFExportParams::kPDFv1_6);
  params.setOutput(odSystemServices()->createFile(pdfPath, Oda::kFileWrite, Oda::kShareDenyNo, Oda::kCreateAlways));

  params.setExportFlags(PDFExportParams::PDFExportFlags(PDFExportParams::kDefault));

  params.setTitle("Batch PDF File");
  params.setAuthor("OdPdfExportWithPrc");
  params.setCreator("Open Design Alliance");
  params.setPRCMode(PDFExportParams::kAsBrep);
  params.setPRCContext(PrcLayerFilter::createObject());

  /****************************************************************/
  /* Initialize the conversion parameters: Layouts                */
  /****************************************************************/

  params.layouts().push_back("Model");
  params.pageParams().resize(1, OdGsPageParams());
}

ODRX_CONS_DEFINE_MEMBERS(PrcLayerFilter, OdPrcContextForPdfExport, RXIMPL_CONSTR);

static void setupFilters(bool init = true)
{
  if (init)
  {
    PrcLayerFilter::rxInit();
  }
  else
  {
    PrcLayerFilter::rxUninit();
  }
}

void OdPdfPrcFilterExample(OdDbHostAppServices &svcs, OdString pdfPath)
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

  OdDbDatabasePtr pDb = fillDatabase(svcs);

  /******************************************************************/
  /* Setup PRC or PDF filters.                                      */
  /******************************************************************/
  setupFilters();

  /****************************************************************/
  /* Initialize the conversion parameters                         */
  /****************************************************************/
  PDFExportParams params;
  fillPdfExportParams(params, pDb, pdfPath);

  OdPdfExportPtr exporter = pModule->create();
  OdUInt32 errCode = exporter->exportPdf(params);
  setupFilters(false);
  if (errCode != 0)
  {
    OdString errMes = exporter->exportPdfErrorCode(errCode);
    printf("\nexportPdf error returned : 0x%x. \n%s", (unsigned)errCode, (const char*)errMes);     
  }
}
