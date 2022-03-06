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
#include "Dgn2PrcExportGiDrawablePE_Impl.h"
#include "PrcExport.h"
#include "RxVariantValue.h"
#include "DgCellHeader.h"
#include "DgBRepEntityPE.h"
#include "MemoryStream.h"
#include "DgModelerGeometryCreator.h"
#include "DgModelerGeometry.h"
#include "Br/BrBrep.h"
#include "MaterialResolver.h"
#include "DgHostAppServices.h"
#include "BrepBuilderInitialParams.h"
#include "PrcMaterialAndColorHelper.h"
#include "PrcCreateTopologyHelper.h"
#include "BrepBuilderFillerModule.h"
#include "DynamicLinker.h"
#include "PrcBrepData.h"
#include "PrcCoordinateSystem.h"
#include "PrcBrepModel.h"
#include "DgDatabase.h"
#include "Dg3DObject.h"
#include "DgBrepBuilderFilerInitPE.h"

#define RET_ERROR(expr) if (OdResult res = expr) return res;

ODRX_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_DGN_Default, PdfExportGiDrawablePE_Default, RXIMPL_CONSTR);

OdResult PdfExportGiDrawablePE_DGN_Default::drawableToPRC(const OdGiDrawable *pDrawable, const PDF2PRCExportParams *pPdfPrcParams, OdRxObject *context) const
{
  // call default export mode
  if (!pPdfPrcParams->m_exportAsBrep)
  {
    return PdfExportGiDrawablePE_Default::drawableToPRC(pDrawable, pPdfPrcParams, context);
  }

  OdBrepBuilderFiller BBFiller;
  OdBrepBuilder builder;
  RET_ERROR(createBrepBuilder(builder, kOpenShell));

  OdPrcExportContextPtr pContext = context;
  OdDbBaseDatabase * pDb = pContext->getDatabase();
  OdDgDatabasePtr pDgDb = OdDgDatabase::cast(pDb);

  OdPrcFilePtr pFile = OdPrcExportContext::cast(context)->getFile();

  PrcMaterialAndColorHelper materialHelper(pPdfPrcParams, context);

  OdGeExtents3d extents;
  OdGeMatrix3d brepMatrix;

  if (pDrawable->isA() == OdDgCellHeader3d::desc())
  {
    OdDgCellHeader3dPtr pCell(pDrawable);
    OdDgBRepEntityPEPtr pBrepPE(pCell);
    if (pBrepPE.isNull())
    {
      return eNotApplicable;
    }

    pCell->getGeomExtents(extents);

    OdStreamBufPtr pStream = OdMemoryStream::createNew();
    if (pBrepPE->type(pCell) == OdDgBRepEntityPE::eNotBRepEntity)
    {
      return PdfExportGiDrawablePE_Default::drawableToPRC(pDrawable, pPdfPrcParams, context);
    }

    RET_ERROR(pBrepPE->brepOutNative(pCell, *pStream));
    pStream->rewind();

    OdRxClassPtr pService(odrxServiceDictionary()->getAt(OD_T("OdDgModelerGeometryCreator")));
    if (pService.isNull())
    {
      return eInvalidInput;
    }

    OdDgModelerGeometryCreatorPtr pCreator = pService->create();
    if (pCreator.isNull())
    {
      return eInvalidInput;
    }

    OdArray<OdDgModelerGeometryPtr> models;
    RET_ERROR(pCreator->createModeler(models, pStream))

    OdBrBrep brep;
    RET_ERROR(models.first()->brep(brep));

    OdDgModelerGeometry::OdDgModelerVersion modelerVersion = 0;
    RET_ERROR(models.first()->comeFromVersion(modelerVersion));
    OdBrepBuilderFillerParams::BrepType srcBrepType = (modelerVersion & OdDgModelerGeometry::kAcisMask)
      ? OdBrepBuilderFillerParams::kBrepAcisDgn : OdBrepBuilderFillerParams::kBrepPS;

    BBFiller.params().setupFor(srcBrepType, pDb, pFile);
    RET_ERROR(BBFiller.initFrom(builder, brep, &materialHelper));

    double dBrepScale = OdDgBRepEntityPEPtr(pCell)->getInternalScale(*pCell.get(), 0.0);
   
    brep.getTransformation(brepMatrix);
    brepMatrix *= OdGeMatrix3d::scaling(dBrepScale);
    brepMatrix *= pCell->getTransformation();
    brepMatrix.setTranslation(pCell->getOrigin().asVector());
  }
  else
  {
    OdDgElementPtr pElem(pDrawable);
    try
    {
      OdDgBrepBuilderInitialDataPEPtr pBrepPE(pElem);
    }
    catch (OdError_NotThatKindOfClass err)
    {
      return PdfExportGiDrawablePE_Default::drawableToPRC(pDrawable, pPdfPrcParams, context);
    }

    OdDgBrepBuilderInitialDataPEPtr pBrepPE(pElem);
    pElem->getGeomExtents(extents);
    BrepBuilderInitialData brepData;
    double scale = 1.0;
    if (!pBrepPE->getBrepBuilderInitialData(pElem, brepData, scale))
    {
      return PdfExportGiDrawablePE_Default::drawableToPRC(pDrawable, pPdfPrcParams, context);
    }

    BBFiller.params().setupFor(pDb, pFile);
    RET_ERROR(BBFiller.initFrom(builder, brepData));

    brepMatrix.setToScaling(scale);
  }

  if (!extents.isValidExtents())
  {
    return eInvalidExtents;
  }

  OdPrcBrepDataPtr pNewData;
  try
  {
    OdPrcBrepDataPtr pNewData = builder.finish();

    OdPrcFileStructurePtr pFS = pFile->fileStructures().last();
    OdPrcProductOccurrencePtr pRootPO = pFS->fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
    OdPrcProductOccurrencePtr pPO = createProductOccurrence(*pFS, *pRootPO);
    OdPrcPartDefinitionPtr pPD = createPartDefinition(*pFS, *pPO);
    OdPrcTopoContextPtr pTopoContext = createTopoContext(*pFS);

    pPD->boundingBox().box() = extents;
    OdPrcBrepModelPtr pBrepModel = createRI<OdPrcBrepModel>(*pFS, *pPD);
    OdPrcBrepDataPtr pOldData = createBody<OdPrcBrepData>(*pFS, *pTopoContext, *pBrepModel);
    pOldData->boundingBox().box() = extents;
    pOldData->contentBody().setBoundingBoxBehaviour(2);

    brepMatrix = pPdfPrcParams->m_bodyTransformationMatr * brepMatrix;

    const OdPrcConnexPtrArray & connexes = pNewData->connex();
    OdPrcConnexPtrArray::const_iterator connexIt = connexes.begin();
    for (; connexIt != connexes.end(); ++connexIt)
    {
      pOldData->addConnex(*connexIt);
    }

    if (brepMatrix != OdGeMatrix3d())
    {
      // - create representation item for transformation
      OdPrcCoordinateSystemPtr pCS = OdPrcCoordinateSystem::createObject();
      pFS->addObject(pCS);
      pCS->axisSet().set(brepMatrix);
      // - add this item to file structure globals
      pFS->fileStructureGlobals().coordinateSystem().push_back(pCS->objectId());
      pBrepModel->localCoordinateSystemID() = pCS->objectId();
    }
  }
  catch (OdError& er)
  {
    return er.code();
  }

  return eOk;
}
