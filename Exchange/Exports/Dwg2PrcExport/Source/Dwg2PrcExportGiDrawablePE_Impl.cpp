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
#include "Dwg2PrcExportGiDrawablePE_Impl.h"
#include "PrcExport.h"
#include "DbSurface.h"
#include "DbBody.h"
#include "Br/BrBrep.h"
#include "DbLayerTableRecord.h"
#include "DbLine.h"
#include "DbCircle.h"
#include "DbPolyline.h"
#include "DbSpline.h"
#include "PrcLine3d.h"
#include "PrcCircle3d.h"
#include "PrcPolyLine3d.h"
#include "PrcNurbsCurve3d.h"
#include "DbMaterial.h"
#include "PrcExportColor.h"
#include "PrcCreateTopologyHelper.h"
#include "PrcSingleWireBody.h"
#include "PrcWireEdge.h"
#include "PrcCoordinateSystem.h"
#include "DbBaseHostAppServices.h"
#include "BrepBuilder/BrepBuilder.h"
#include "PrcMaterialAndColorHelper.h"
#include "Gi/GiSubEntityTraitsDataSaver.h"
#include "BrepBuilderFillerModule.h"
#include "DbArc.h"
#include "PrcBrepData.h"
#include "Gi/GiMaterialTraitsData.h"

ODRX_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_Entity, PdfExportGiDrawablePE_Default, RXIMPL_CONSTR);

ODRX_NO_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_Solid_IFace, PdfExportGiDrawablePE_Entity);

ODRX_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_3dSolid, PdfExportGiDrawablePE_Solid_IFace, RXIMPL_CONSTR);
ODRX_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_Region,  PdfExportGiDrawablePE_Solid_IFace, RXIMPL_CONSTR);
ODRX_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_Surface, PdfExportGiDrawablePE_Solid_IFace, RXIMPL_CONSTR);
ODRX_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_Body,    PdfExportGiDrawablePE_Solid_IFace, RXIMPL_CONSTR);

ODRX_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_Curve,      PdfExportGiDrawablePE_Entity,    RXIMPL_CONSTR);

ODRX_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_Line,       PdfExportGiDrawablePE_Curve,     RXIMPL_CONSTR);
ODRX_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_Circle,     PdfExportGiDrawablePE_Curve,     RXIMPL_CONSTR);
ODRX_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_Arc,        PdfExportGiDrawablePE_Curve,     RXIMPL_CONSTR);
ODRX_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_Polyline,   PdfExportGiDrawablePE_Curve,     RXIMPL_CONSTR);
ODRX_CONS_DEFINE_MEMBERS(PdfExportGiDrawablePE_2dPolyline, PdfExportGiDrawablePE_Curve,     RXIMPL_CONSTR);

ODRX_CONS_DEFINE_MEMBERS(PdfExportLayerPE_LayerTableRecord, PdfExportLayerPE, RXIMPL_CONSTR);


void fillBrepModel(const OdBrBrep &brep, const PDF2PRCExportParams &params, OdPrcExportContext *pContext, const OdGiDrawable *pDrawable)
{
  // get extents
  OdGeExtents3d extents;
  OdResult extentsOk = pDrawable->getGeomExtents(extents);
  if (extentsOk != eOk)
  {
    throw OdError(extentsOk);
  }

  OdPrcFileStructurePtr pFS = pContext->getFile()->fileStructures().last();
  OdPrcProductOccurrencePtr pRootPO = pFS->fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcProductOccurrencePtr pPO = createProductOccurrence(*pFS, *pRootPO);
  OdPrcPartDefinitionPtr pPD = createPartDefinition(*pFS, *pPO);
  OdPrcTopoContextPtr pTopoContext = createTopoContext(*pFS);
  OdPrcBrepModelPtr pRI = createRI<OdPrcBrepModel>(*pFS, *pPD);

  OdBrepBuilder bbuilder;
  if (OdResult res = createBrepBuilder(bbuilder, kOpenShell))
  {
    throw OdError(res);
  }

  OdDbStub * pResMaterial = getCurrentEntityMaterial(params, pDrawable);
  PrcMaterialAndColorHelper materialHelper(&params, pContext, pResMaterial);

  OdBrepBuilderFiller BBFiller;
  BBFiller.params()
    .setupFor(pContext->getDatabase(), pContext->getFile())
    .setSkipNullSurface(true);
  if (OdResult res = BBFiller.initFrom(bbuilder, brep, &materialHelper))
  {
    throw OdError(res);
  }

  bbuilder.enableValidator(false);
  pPD->boundingBox().box() = extents;

  // create brep body
  OdPrcBrepDataPtr brepData = bbuilder.finish();
  brepData->boundingBox().box() = extents;
  pFS->addObject(brepData);
  brepData->contentBody().setBoundingBoxBehaviour(2);
  // - set reference to this body in representation item
  pRI->setReferenceToBody(brepData);
  pTopoContext->appendBody(brepData->objectId());

  ODA_VERIFY(pRI->updateIsClosedFlag() == eOk);

  // transformation matrix
  OdGeMatrix3d brepMatrix;
  brep.getTransformation(brepMatrix);
  brepMatrix = params.m_bodyTransformationMatr * brepMatrix;
  if (brepMatrix != OdGeMatrix3d())
  {
    // - create representation item for transformation
    OdPrcCoordinateSystemPtr pCS = OdPrcCoordinateSystem::createObject();
    pFS->addObject(pCS);
    pCS->axisSet().set(brepMatrix);
    // - add this item to file structure globals
    pFS->fileStructureGlobals().coordinateSystem().push_back(pCS->objectId());
    pRI->localCoordinateSystemID() = pCS->objectId();
  }

  //save color or material
  saveCurrentEntityMaterial(*pContext, params, pDrawable);
}

struct OdGiMaterialTraits_Stub_PRC : public OdGiMaterialTraits_Stub
{
  OdGiMaterialColor m_diffuseColor;
  OdGiMaterialMap   m_diffuseMap;

  virtual void setDiffuse(const OdGiMaterialColor & diffuseColor, const OdGiMaterialMap& diffuseMap)
  {
    m_diffuseColor = diffuseColor;
    m_diffuseMap = diffuseMap;
  }

  void diffuse(OdGiMaterialColor& diffuseColor, OdGiMaterialMap& diffuseMap) const
  {
    diffuseColor = m_diffuseColor;
    diffuseMap = m_diffuseMap;
  }
};

bool materialHasTexture(OdDbStub *materialId, const OdDbBaseDatabase *pDb)
{
  OdGiDrawablePtr pGiMaterial = OdDbBaseDatabasePEPtr(pDb)->openObject(materialId);

  OdGiMaterialTraits_Stub_PRC myTraits;

  OdUInt32 flags = pGiMaterial->setAttributes(&myTraits);

  if (myTraits.m_diffuseColor.method() == OdGiMaterialColor::kOverride)
  {
    if (!myTraits.m_diffuseMap.sourceFileName().isEmpty())
    {
      // try to find file
      OdString textureName = OdDbBaseDatabasePEPtr(pDb)->appServices((OdDbBaseDatabase*)pDb)->findFile(
        myTraits.m_diffuseMap.sourceFileName(), (OdDbBaseDatabase*)pDb, OdDbBaseHostAppServices::kTextureMapFile);
      return !textureName.isEmpty();
    }
    const OdGiMaterialTexturePtr pTexture = myTraits.m_diffuseMap.texture();
    return !pTexture.isNull() && pTexture->isKindOf(OdGiRasterImageTexture::desc()) && ((const OdGiRasterImageTexturePtr)pTexture)->rasterImage();
  }

  return false;
}

//forward declarations
OdResult exportBrepToPrc(const OdGiDrawable *pDrawable, const PDF2PRCExportParams &params, const OdBrBrep &brep, OdRxObject *pContext)
{
  OdPrcExportContextPtr ptrContext = pContext;
  if (ptrContext.isNull())
  {
    return eInvalidInput;
  }

  OdPrcFilePtr pFile = ptrContext->getFile();
  if (pFile.isNull())
  {
    return eCreateFailed;
  }

  OdDbStub * material = getCurrentEntityMaterial(params, pDrawable);
  if (materialHasTexture(material, ptrContext->getDatabase()))
  {
    //export as tessellation
    return exportMeshToPrc(pDrawable, params, pContext);
  }
  else
  {
    // export as brep
    fillBrepModel(brep, params, ptrContext, pDrawable);
  }

  return eOk;
}

OdResult fillSingleWireBody(OdPrcCurve3dPtr &curve, const PDF2PRCExportParams &params, OdRxObject *pContext, const OdGiDrawable *pDrawable)
{
  // cast rxobject to context
  OdPrcExportContextPtr ptrContext = pContext;
  if (ptrContext.isNull())
  {
    return eInvalidInput;
  }

  // ensure has file
  OdPrcFilePtr pFile = ptrContext->getFile();
  if (pFile.isNull())
  {
    return eCreateFailed;
  }

  OdPrcFileStructure &newStructure = *pFile->fileStructures().last();
  OdPrcProductOccurrencePtr pRootPO = newStructure.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcProductOccurrencePtr pPO = createProductOccurrence(newStructure, *pRootPO);
  OdPrcPartDefinitionPtr pPD = createPartDefinition(newStructure, *pPO);
  OdPrcTopoContextPtr pTopoContext = createTopoContext(newStructure);

  // get extents
  OdGeExtents3d extents;
  OdResult extentsOk = pDrawable->getGeomExtents(extents);
  if (extentsOk != eOk)
  {
    return extentsOk;
  }

  OdPrcWireCurvePtr pCurve = createRI<OdPrcWireCurve>(newStructure, *pPD);
  pPD->boundingBox().box() = extents;
  OdPrcSingleWireBodyPtr wireBody = createBody<OdPrcSingleWireBody>(newStructure, *pTopoContext, *pCurve);

  // - fill params for SingleWireBody
  OdPrcWireEdgePtr wEdge = OdPrcWireEdge::createObject();
  wireBody->wireEdge() = wEdge;
  OdPrcContentWireEdge &wContent = wEdge->contentWireEdge();
  OdPrcContentCurve &crvContent = curve->contentCurve();
  wContent.curve() = curve;

  // transformation matrix
  if (params.m_bodyTransformationMatr != OdGeMatrix3d::kIdentity)
  {
    // - create representation item for transformation
    OdPrcCoordinateSystemPtr pCS = OdPrcCoordinateSystem::createObject();
    newStructure.addObject(pCS);
    pCS->axisSet().set(params.m_bodyTransformationMatr);
    // - add this item to file structure globals
    newStructure.fileStructureGlobals().coordinateSystem().push_back(pCS->objectId());
    pCurve->localCoordinateSystemID() = pCS->objectId();
  }
  saveCurrentTrueColor(*ptrContext, params, pDrawable);
  return eOk;
}

OdResult fillPointSet(OdGePoint3d pt, const PDF2PRCExportParams &params, OdRxObject *pContext, const OdGiDrawable *pDrawable)
{
  OdPrcExportContextPtr ptrContext = pContext;
  if (ptrContext.isNull())
  {
    return eInvalidInput;
  }

  if (ptrContext->getFile().isNull())
  {
    return eCreateFailed;
  }

  OdPrcFilePtr pFile = ptrContext->getFile();
  if (pFile.isNull())
  {
    return eCreateFailed;
  }

  OdPrcFileStructure &newStructure = *pFile->fileStructures().last();
  OdPrcProductOccurrencePtr pRootPO = newStructure.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcProductOccurrencePtr pPO = createProductOccurrence(newStructure, *pRootPO);
  OdPrcPartDefinitionPtr newDefinition = createPartDefinition(newStructure, *pPO);

  // get extents
  OdGeExtents3d extents;
  OdResult extentsOk = pDrawable->getGeomExtents(extents);
  if (extentsOk != eOk)
  {
    return extentsOk;
  }

  // create single wire topology
  OdPrcPointSetPtr pPointSet = createRI<OdPrcPointSet>(newStructure, *newDefinition);
  newDefinition->boundingBox().box() = extents;

  // transformation matrix
  if (params.m_bodyTransformationMatr != OdGeMatrix3d())
  {
    pt.transformBy(params.m_bodyTransformationMatr);
  }
  pPointSet->point().push_back(pt);
  saveCurrentTrueColor(*ptrContext, params, pDrawable);
  return eOk;
}

OdCmEntityColor PdfExportLayerPE_LayerTableRecord::getColor(const OdRxObject *pObj) const
{
  OdDbLayerTableRecordPtr pLayer = OdDbLayerTableRecord::cast(pObj);
  if (pLayer.get())
  {
    return pLayer->color().entityColor();
  }
  return PdfExportLayerPE::getColor(pObj);
}

OdDbStub * PdfExportLayerPE_LayerTableRecord::getMaterial(const OdRxObject *pObj) const
{
  OdDbLayerTableRecordPtr pLayer = OdDbLayerTableRecord::cast(pObj);
  if (pLayer.get())
  {
    return pLayer->materialId();
  }
  return PdfExportLayerPE::getMaterial(pObj);
}

OdCmTransparency PdfExportLayerPE_LayerTableRecord::getTransparency(const OdRxObject *pObj) const
{
  OdDbLayerTableRecordPtr pLayer = OdDbLayerTableRecord::cast(pObj);
  if (pLayer.get())
  {
    return pLayer->transparency();
  }
  return PdfExportLayerPE::getTransparency(pObj);
}

OdCmEntityColor PdfExportGiDrawablePE_Entity::getColor(const OdGiDrawable *pDrawable) const
{
  if (pDrawable && pDrawable->isKindOf(OdDbEntity::desc()))
  {
    OdDbEntityPtr pEntity = pDrawable;
    if (pEntity->color().isByColor() || pEntity->color().isByACI())
    {
      return pEntity->color().entityColor();
    }
    else if (pEntity->color().isByLayer())
    {
      OdDbObjectId layerID = pEntity->layerId();
      if (layerID.isValid())
      {
        OdDbLayerTableRecordPtr pLayer = layerID.openObject();
        if (pLayer.get())
        {
          return pLayer->color().entityColor();
        }
      }
    }
    else if (pEntity->color().isByBlock())
    {
      OdCmEntityColor col;
      col.setColorIndex(7);
      return col;
    }
  }
  return OdCmEntityColor::kNone;
}

OdDbStub * PdfExportGiDrawablePE_Entity::getMaterial(const OdGiDrawable *pDrawable) const
{
  if (pDrawable && pDrawable->isKindOf(OdDbEntity::desc()))
  {
    OdDbEntityPtr pEntity = pDrawable;
    if (pEntity->materialId().isValid())
    {
      return pEntity->materialId();
    }
  }
  return NULL;
}

OdCmTransparency PdfExportGiDrawablePE_Entity::getTransparency(const OdGiDrawable *pDrawable) const
{
  if (pDrawable && pDrawable->isKindOf(OdDbEntity::desc()))
  {
    OdDbEntityPtr pEntity = pDrawable;
    OdDbObjectId materialID = pEntity->materialId();
    if (materialID.isValid())
    {
      OdDbMaterialPtr pMaterial = materialID.openObject();
      if (pMaterial.get())
      {
        if (pMaterial->channelFlags() & OdGiMaterialTraits::kUseOpacity)
        {
          double dPercent = 1.;
          OdGiMaterialMap map;
          pMaterial->opacity(dPercent, map);
          return OdCmTransparency(dPercent);
        }

        if (pEntity->transparency().isByAlpha())
        {
          return pEntity->transparency();
        }
        else if (pEntity->transparency().isByLayer())
        {
          OdDbObjectId layerID = pEntity->layerId();
          if (layerID.isValid())
          {
            OdDbLayerTableRecordPtr pLayer = layerID.openObject();
            if (pLayer.get())
            {
              return pLayer->transparency();
            }
          }
        }
        else if (pEntity->transparency().isByBlock())
        {
          return OdCmTransparency(1.);
        }
      }
    }
  }
  return OdCmTransparency(1.);
}

OdResult PdfExportGiDrawablePE_Solid_IFace::drawableToPRC(const OdGiDrawable *pDrawable, const PDF2PRCExportParams *pPdfPrcParams, OdRxObject *pContext) const
{
  // ensure valid input
  ODA_ASSERT(pPdfPrcParams); ODA_ASSERT(pDrawable);
  if ((!pPdfPrcParams) || (!pDrawable))
    return ::eInvalidInput;

  if (pPdfPrcParams->m_exportAsBrep)
  {
    // brep => export as brep
    // - cast to OdDb to get entity and brep
    OdBrBrep brep;
    GetBrep(pDrawable, brep);

    // - do export
    return exportBrepToPrc(pDrawable, *pPdfPrcParams, brep, pContext);
  }
  // mesh => export as mesh
  return exportMeshToPrc(pDrawable, *pPdfPrcParams, pContext);
}

void PdfExportGiDrawablePE_3dSolid::GetBrep(const OdGiDrawable *pDrawable, OdBrBrep &brep) const
{
  OdDb3dSolidPtr pEnt = OdDb3dSolid::cast(pDrawable);
  pEnt->brep(brep);
} 

void PdfExportGiDrawablePE_Region::GetBrep(const OdGiDrawable *pDrawable, OdBrBrep &brep) const
{
  OdDbRegionPtr pEnt = OdDbRegion::cast(pDrawable);
  pEnt->brep(brep);
}

void PdfExportGiDrawablePE_Surface::GetBrep(const OdGiDrawable *pDrawable, OdBrBrep &brep) const
{
  OdDbSurfacePtr pEnt = OdDbSurface::cast(pDrawable);
  pEnt->brep(brep);
}

void PdfExportGiDrawablePE_Body::GetBrep (const OdGiDrawable *pDrawable, OdBrBrep &brep) const
{
  OdDbBodyPtr pEnt = OdDbBody::cast(pDrawable);
  pEnt->brep(brep);
}

OdResult PdfExportGiDrawablePE_Curve::drawableToPRC(const OdGiDrawable *pDrawable, const PDF2PRCExportParams *pPdfPrcParams, OdRxObject *pContext) const
{
  ODA_ASSERT(pDrawable);
  if (!pDrawable)
  {
    return eInvalidInput;
  }
  OdDbCurvePtr pDbCrv = OdDbCurve::cast(pDrawable);
  
  if (pDbCrv.isNull())
  {
    return eInvalidInput;
  }

  // get curve
  OdGeCurve3d *pGeCrv = NULL;
  OdResult isOk = pDbCrv->getOdGeCurve(pGeCrv);
  if (isOk == eOk)
  {
    OdPrcCurve3dPtr pPrcCrv;
    isOk = OdPrcCurve3d::createFromOdGeCurve(*pGeCrv, pPrcCrv);
    delete pGeCrv;
    if (isOk != eOk)
    {
      // - export through vectorizer
      return exportMeshToPrc(pDrawable, *pPdfPrcParams, pContext);
    }
    // - export as appropriate prc curve
    return fillSingleWireBody(pPrcCrv, *pPdfPrcParams, pContext, pDrawable);
  }
  //means that curve is a point
  OdGePoint3d pt;
  if (eOk != pDbCrv->getStartPoint(pt))
  {
    return eInvalidInput;
  }
  // - export as point
  return fillPointSet(pt, *pPdfPrcParams, pContext, pDrawable);
}

OdResult PdfExportGiDrawablePE_Line::drawableToPRC(const OdGiDrawable *pDrawable, const PDF2PRCExportParams *pPdfPrcParams, OdRxObject *pContext) const
{
  if (OdDbLine::cast(pDrawable)->thickness() != 0.)
  {
    // TODO: Export as OdPrcExtrusionSurface in B-rep
    // - export through vectorizer
    return exportMeshToPrc(pDrawable, *pPdfPrcParams, pContext);
  }

  return PdfExportGiDrawablePE_Curve::drawableToPRC(pDrawable, pPdfPrcParams, pContext);
}

OdResult PdfExportGiDrawablePE_Circle::drawableToPRC(const OdGiDrawable *pDrawable, const PDF2PRCExportParams *pPdfPrcParams, OdRxObject *pContext) const
{
  if (OdDbCircle::cast(pDrawable)->thickness() != 0.)
  {
    // TODO: Export as OdPrcExtrusionSurface in B-rep
    // - export through vectorizer
    return exportMeshToPrc(pDrawable, *pPdfPrcParams, pContext);
  }

  return PdfExportGiDrawablePE_Curve::drawableToPRC(pDrawable, pPdfPrcParams, pContext);
}

OdResult PdfExportGiDrawablePE_Arc::drawableToPRC(const OdGiDrawable *pDrawable, const PDF2PRCExportParams *pPdfPrcParams, OdRxObject *pContext) const
{
  if (OdDbArc::cast(pDrawable)->thickness() != 0.)
  {
    // TODO: Export as OdPrcExtrusionSurface in B-rep
    // - export through vectorizer
    return exportMeshToPrc(pDrawable, *pPdfPrcParams, pContext);
  }

  return PdfExportGiDrawablePE_Curve::drawableToPRC(pDrawable, pPdfPrcParams, pContext);
}

OdResult PdfExportGiDrawablePE_Polyline::drawableToPRC(const OdGiDrawable *pDrawable, const PDF2PRCExportParams *pPdfPrcParams, OdRxObject *pContext) const
{
  if (OdDbPolyline::cast(pDrawable)->thickness() != 0.)
  {
    // TODO: Export as OdPrcExtrusionSurface in B-rep
    // - export through vectorizer
    return exportMeshToPrc(pDrawable, *pPdfPrcParams, pContext);
  }

  return PdfExportGiDrawablePE_Curve::drawableToPRC(pDrawable, pPdfPrcParams, pContext);
}

OdResult PdfExportGiDrawablePE_2dPolyline::drawableToPRC(const OdGiDrawable *pDrawable, const PDF2PRCExportParams *pPdfPrcParams, OdRxObject *pContext) const
{
  if (OdDb2dPolyline::cast(pDrawable)->thickness() != 0.)
  {
    // TODO: Export as OdPrcExtrusionSurface in B-rep
    // - export through vectorizer
    return exportMeshToPrc(pDrawable, *pPdfPrcParams, pContext);
  }

  return PdfExportGiDrawablePE_Curve::drawableToPRC(pDrawable, pPdfPrcParams, pContext);
}
