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
#include "BimCommon.h"
#include "Bim2PrcExportGiDrawablePE_Impl.h"
#include "Geometry/Entities/BmGeometry.h"
#include "BrepBuilderFillerModule.h"
#include "BmDatabase.h"
#include "BmHostAppServices.h"
#include "DynamicLinker.h"
#include "PrcCreateTopologyHelper.h"
#include "PrcBrepData.h"
#include "PrcBrepModel.h"
#include "PrcCoordinateSystem.h"
#include "PrcMaterialAndColorHelper.h"
#include "Database/Entities/BmInstance.h"
#include "Database/Entities/BmInstanceInfo.h"
#include "Entities/BmSerializedDummy.h"
#include "Geometry/Entities/BmGInstance.h"
#include "Geometry/Entities/BmGElement.h"

#define RET_ERROR(expr) if (OdResult res = expr) return res;

ODRX_CONS_DEFINE_MEMBERS(PdfExportBmElementPE, PdfExportGiDrawablePE_Default, RXIMPL_CONSTR);

// ===============================================
// BEGIN: those functions are copy-paste from TB_DevGuideCommands/BmGetBrepGeometryCmd.cpp
static void parseGElementForGeometry(OdBmGNodeIteratorPtr& pGNodeIter, 
  const OdGeMatrix3d& matCurrTransform, // Added
  OdBmGNodePtrArray& arrGeometries, 
  OdGeMatrix3dArray& arrTransforms, // Added
  const bool bGetGeometryFromGIntance)
{
  for (OdBmGNodePtr pGNode : pGNodeIter) 
  {
    if (pGNode->isA() == OdBmGeometry::desc())
    {
      arrGeometries.push_back(pGNode);
      arrTransforms.push_back(matCurrTransform); // Added
    }
    else if ((pGNode->isA() == OdBmGInstance::desc()) && bGetGeometryFromGIntance) {
      OdBmGInstancePtr pGInstance = pGNode;
      OdGeMatrix3d mat = pGInstance->getInstanceInfo()->getTrf() * matCurrTransform; // Added
      OdBmObjectPtr pObjRes2;
      OdBmGeometryOptions opts;
      if (eOk == pGInstance->getGeometry(opts, pObjRes2)) {
        OdBmGElementPtr pGElement = pObjRes2;
        OdBmGNodeIteratorPtr iter = pGElement->newGNodeIterator();
        parseGElementForGeometry(iter, mat, arrGeometries, arrTransforms, bGetGeometryFromGIntance);
      }
    }
    else if (pGNode->isKindOf(OdBmGGroup::desc())) {
      OdBmGGroupPtr pGGroup = static_cast<OdBmGGroupPtr>(pGNode);
      OdBmGNodeIteratorPtr iter = pGGroup->newGNodeIterator();
      parseGElementForGeometry(iter, matCurrTransform, arrGeometries, arrTransforms, bGetGeometryFromGIntance);
    }
  }
}
// END: those functions are copy-paste from BimRv
// ===============================================

OdResult PdfExportBmElementPE::drawableToPRC(const OdGiDrawable *pDrawable, const PDF2PRCExportParams *pPdfPrcParams, OdRxObject *context) const
{
  if (!pPdfPrcParams->m_exportAsBrep)
  {
    return PdfExportGiDrawablePE_Default::drawableToPRC(pDrawable, pPdfPrcParams, context);
  }

  OdPrcExportContextPtr pContext = context;
  OdBmElementPtr pElem = pDrawable;

  // Check extents
  OdGeExtents3d extents = pElem->getBBox();
  if (!extents.isValidExtents())
  {
    return eInvalidExtents;
  }

  OdBmGElementPtr pGElement;
  {
    OdBmGeometryOptions options;
    //options.setDetailLevel();
    //options.setComputeReferences();
    //options.setDbView();
    options.setIncludeNonVisibleObjects(false);
    OdBmObjectPtr pBmGeomObj;
    pElem->getGeometry(options, pBmGeomObj);
    pGElement = pBmGeomObj;
  }
  if (pGElement.isNull())
  {
    return eNullPtr;
  }
  if (pGElement->isA() == OdBmSerializedDummy::desc())
  {
    return eBadObjType;
  }

  OdBmGNodePtrArray arrGeometries;
  OdBmGNodeIteratorPtr elIt = pGElement->newGNodeIterator();
  OdGeMatrix3d mat;
  OdGeMatrix3dArray arrTransforms;
  // note that it will return only OdBmGeometry objects - brep objects, but other objects, e.g. lines, will be skipped...
  parseGElementForGeometry(elIt, mat, arrGeometries, arrTransforms, true);
  if (arrGeometries.isEmpty())
  {
    return eEmptySet;
  }

  OdPrcFilePtr pFile = pContext->getFile();
  OdPrcFileStructurePtr pFS = pFile->fileStructures().last();
  OdPrcProductOccurrencePtr pRootPO = pFS->fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);

  OdGeMatrix3dArray::iterator itMat = arrTransforms.begin();
  for (OdBmGNodePtrArray::iterator it = arrGeometries.begin(); it != arrGeometries.end(); ++it, ++itMat)
  {
    OdBmGeometryPtr pGeometry = *it;
    if (!pGeometry.isNull())
    {
      OdBrBrep brep;
      pGeometry->brep(brep);
      if (!brep.isValid())
      {
        continue;
      }

      OdBrepBuilder builder;
      RET_ERROR(createBrepBuilder(builder, kOpenShell));
      builder.enableValidator(false);

      OdDbStub * pResMaterial = NULL;
      if (pPdfPrcParams->m_pTraitsData && pPdfPrcParams->m_pTraitsData->material())
      {
        pResMaterial = pPdfPrcParams->m_pTraitsData->material();
      }

      PrcMaterialAndColorHelper materialHelper(pPdfPrcParams, context, pResMaterial);
      OdBrepBuilderFiller BBFiller;
      BBFiller.params().setupFor(pContext->getDatabase(), pFile);
      RET_ERROR(BBFiller.initFrom(builder, brep, &materialHelper));
      try
      {
        OdGeMatrix3d brepMatrix;
        brep.getTransformation(brepMatrix);
        brepMatrix = pPdfPrcParams->m_bodyTransformationMatr * *itMat * brepMatrix;

        OdPrcBrepDataPtr pNewData = builder.finish();

        OdPrcProductOccurrencePtr pPO = createProductOccurrence(*pFS, *pRootPO);
        OdPrcPartDefinitionPtr pPD = createPartDefinition(*pFS, *pPO);
        OdPrcTopoContextPtr pTopoContext = createTopoContext(*pFS);

        pPD->boundingBox().box() = extents; // TODO: Looks wrong to use this extents for all geometries
        OdPrcBrepModelPtr pBrepModel = createRI<OdPrcBrepModel>(*pFS, *pPD);
        OdPrcBrepDataPtr pOldData = createBody<OdPrcBrepData>(*pFS, *pTopoContext, *pBrepModel);
        pOldData->boundingBox().box() = extents;
        pOldData->contentBody().setBoundingBoxBehaviour(2);

        const OdPrcConnexPtrArray & connexes = pNewData->connex();
        for (OdPrcConnexPtrArray::const_iterator connexIt = connexes.begin(); connexIt != connexes.end(); ++connexIt)
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
    }
  }
  return eOk;
}
