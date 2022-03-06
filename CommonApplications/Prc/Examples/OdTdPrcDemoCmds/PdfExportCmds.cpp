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

using namespace TD_PDF_2D_EXPORT;

class PrcSelectionFilter : public OdPrcContextForPdfExport
{
private:
  OdArray<OdDbObjectIdArray> m_groups;

public:
  ODRX_DECLARE_MEMBERS(PrcSelectionFilter);

  void setGroups(const OdArray<OdDbObjectIdArray> &groups)
  {
    m_groups = groups;
  }

  virtual bool shouldExportAsPRC (const OdGiDrawable *pDrawable,
    const OdGiPathNode *entity,
    const OdGsClientViewInfo *pView,
    OdUInt32 &viewportidx) const
  {
    OdDbEntityPtr pEnt = OdDbEntity::cast(pDrawable);

    if (pEnt.isNull())
      return false; // to pdf

    OdDbObjectId id = pEnt->objectId();

    if (id.isNull())
      return false; // to pdf

    for(OdUInt32 f=0;f<m_groups.size(); ++f)
    {
      for(OdUInt32 k=0;k<m_groups[f].size(); ++k)
      {
        if (m_groups[f][k] == id)
        {
          viewportidx = f;
          return true; // to prc
        }
      }
    }

    return false; // to pdf
  }
};

void fillPdfExportParams(PDFExportParams &params, OdDbDatabasePtr pDb, OdString pdfPath, const OdArray<OdDbObjectIdArray> &groups)
{
  params.setDatabase(pDb);
  params.setVersion(PDFExportParams::kPDFv1_6);
  params.setOutput(odSystemServices()->createFile(pdfPath, Oda::kFileWrite, Oda::kShareDenyNo, Oda::kCreateAlways));

  params.setExportFlags(PDFExportParams::PDFExportFlags(PDFExportParams::kDefault));

  params.setTitle("Batch PDF File");
  params.setAuthor("PrcSelection");
  params.setCreator("Open Design Alliance");
  params.setPRCMode(PDFExportParams::kAsBrep);

  OdSmartPtr<PrcSelectionFilter> pPrcContext = PrcSelectionFilter::createObject();
  pPrcContext->setGroups(groups);
  params.setPRCContext(pPrcContext);

  /****************************************************************/
  /* Initialize the conversion parameters: Layouts                */
  /****************************************************************/

  params.layouts().push_back("Model");
  params.pageParams().resize(1, OdGsPageParams());
}

ODRX_CONS_DEFINE_MEMBERS(PrcSelectionFilter, OdPrcContextForPdfExport, RXIMPL_CONSTR);

void _PrcSelection_func(OdEdCommandContext* pCmdCtx)
{
  /******************************************************************/
  /* Create a Pdf export module                                     */
  /******************************************************************/
  OdPdfExportModulePtr pModule = ::odrxDynamicLinker()->loadApp(OdPdfExportModuleName, false);

  ::odrxDynamicLinker()->loadApp(OdPrcModuleName, false);
  ::odrxDynamicLinker()->loadApp(OdDwg2PrcExportModuleName, false);

  PrcSelectionFilter::rxInit();

  OdString tmp;

  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();

  OdArray<OdDbObjectIdArray> groups;

  for(;;)
  {
    tmp.format(L"Select entities for PRC view number %d <done>:", groups.size() + 1);
    OdDbSelectionSetIteratorPtr pIter = pIO->select(tmp.c_str(),OdEd::kSelDefault)->newIterator();

    if (pIter->done())
      break;

    groups.append();
    for (;!pIter->done();pIter->next())
    {
      groups.last().append(pIter->objectId());
    }
    if (1 == pIO->getKeyword(OD_T("Next group? [Yes/Export]:"), OD_T("Yes Export"), 0))
      break;
  }

  OdString pdfPath = pDbCmdCtx->dbUserIO()->getFilePath(L"PDF path", OdEd::kGfpForSave,L"PDF path", L"PDF", L"", L"PDF files (*.pdf)|*.pdf");

  {
    /****************************************************************/
    /* Initialize the conversion parameters                         */
    /****************************************************************/
    PDFExportParams params;
    fillPdfExportParams(params, pDb, pdfPath, groups);

    OdPdfExportPtr exporter = pModule->create();
    OdUInt32 errCode = exporter->exportPdf(params);
    if (errCode != 0)
    {
      OdString errMes = exporter->exportPdfErrorCode(errCode);
      printf("\nexportPdf error returned : 0x%x. \n%s", (unsigned)errCode, (const char*)errMes);     
    }
  }

  PrcSelectionFilter::rxUninit();
}
