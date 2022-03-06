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
#include "Dwg2PrcExportModule.h"
#include "AppServices/PrcHostAppServices.h"
#include "MemoryStream.h"
#include "PrcBrepModel.h"
#include "PrcExportContext.h"
#include "PrcExport.h"
#include "PdfExportService.h"

#if 0
#include "ColorMapping.h"
#include "PdfExport.h"
#include "PrcDefaultContextForTD.h"
#include "ExPrintConsole.h"
using namespace TD_PDF_2D_EXPORT;

void getPrcViaPdfExport(PRCStreamsMap & outStreamsPRC, PDFExportParams & publishParams);

// prc file for test is created here
void createTestGeometryForCrossSectionTest(OdStreamBufPtr &pMemStream, OdDbHostAppServices &pH)
{
  // create a solid object
  OdDb3dSolidPtr p3dSolid = OdDb3dSolid::createObject();
  p3dSolid->createFrustum(4.0, 1.0, 1.0, 0.0);

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
  pIt->second->copyDataTo(pMemStream);
}

#else
// prc file for test is created here
void createTestGeometryForCrossSectionTest(OdStreamBufPtr &pMemStream, OdDbHostAppServices &pH)
{
  // create a solid object
  OdDb3dSolidPtr p3dSolid = OdDb3dSolid::createObject();
  p3dSolid->createFrustum(4.0, 1.0, 1.0, 0.0);

  OdDbDatabasePtr pDb = pH.createDatabase();
  OdDbBlockTableRecordPtr pRec = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
  pRec->appendOdDbEntity(p3dSolid);

  // load module
  odrxDynamicLinker()->loadModule(OdDwg2PrcExportModuleName);
  PdfExportServiceInterfacePtr pExportIFace = getPdfExportService();

  // write file to stream
  PDF2PRCExportParams params;
  OdRxObjectPtr pContext = pExportIFace->createPrcExportContext(pDb);
  OdResult res = pExportIFace->exportPrc(pContext, p3dSolid, &params);
  if (res != eOk)
  {
    throw OdError(res);
  }
  res = pExportIFace->serialize(pMemStream, pContext, &params);
  if (res != eOk)
  {
    throw OdError(res);
  }
}
#endif

void simpleCrossSectioExample(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  // create an object
  OdStreamBufPtr pMemStream = OdMemoryStream::createNew();
  createTestGeometryForCrossSectionTest(pMemStream, pH);

  // open file
  pMemStream->rewind();
  OdPrcFilePtr pFile = pPrcHost.readFile(pMemStream);
  OdPrcFileStructurePtr pNewFileStructure = pFile->fileStructures().last();
  
  // create view
  {
    OdPrcViewPtr pNewView = OdPrcView::createObject();
    pNewFileStructure->addObject(pNewView);
    OdPrcName name;
    name.setName(L"NE Isometric");
    pNewView->name() = name;
    // - add view to PO
    OdPrcProductOccurrencePtr productOc = pFile->fileStructures().last()->fileStructureTree().productOccurrence().last();
    OdPrcObjectIdArray &arr_view = productOc->annotationViews();
    arr_view.push_back(pNewView->id());
    OdPrcSceneDisplayParametersPtr pSceneDisplayParameters = OdPrcSceneDisplayParameters::createObject();
    pNewFileStructure->addObject(pSceneDisplayParameters);
    pNewView->sceneDisplayParameters() = pSceneDisplayParameters->id();

    // - setup camera for view
    OdPrcCameraPtr pCamera = OdPrcCamera::createObject();
    pNewFileStructure->addObject(pCamera);
    pCamera->lookAt().set(0.0, 0.0, 0.0);
    pCamera->up().set(0.0, 0.0, 1.0);
    pCamera->location().set(5.0, 5.0, 5.0);
    pCamera->setXFov(1.0472);
    pCamera->setYFov(1.0472);
    pSceneDisplayParameters->camera() = pCamera->id();
  }

  // create view with XZ clipping plane
  {
    OdPrcViewPtr pNewView = OdPrcView::createObject();
    pNewFileStructure->addObject(pNewView);
    OdPrcName name;
    name.setName(L"NE Isometric clipped by XZ");
    pNewView->name() = name;
    // - add view to PO
    OdPrcProductOccurrencePtr productOc = pFile->fileStructures().last()->fileStructureTree().productOccurrence().last();
    OdPrcObjectIdArray &arr_view = productOc->annotationViews();
    arr_view.push_back(pNewView->id());
    OdPrcSceneDisplayParametersPtr pSceneDisplayParameters = OdPrcSceneDisplayParameters::createObject();
    pNewFileStructure->addObject(pSceneDisplayParameters);
    pNewView->sceneDisplayParameters() = pSceneDisplayParameters->id();

    // - setup camera for view
    OdPrcCameraPtr pCamera = OdPrcCamera::createObject();
    pNewFileStructure->addObject(pCamera);
    pCamera->lookAt().set(0.0, 0.0, 0.0);
    pCamera->up().set(0.0, 0.0, 1.0);
    pCamera->location().set(5.0, 5.0, 5.0);
    pCamera->setXFov(1.0472);
    pCamera->setYFov(1.0472);
    pSceneDisplayParameters->camera() = pCamera->id();

    // - add clipping plane to the view
    OdPrcSurfacePtrArray &viewClippingPlanes = ((OdPrcSceneDisplayParameters*)pSceneDisplayParameters)->clippingPlanes();
    OdPrcPlanePtr pPlane = OdPrcPlane::createObject();
    OdGeVector3d normal(0.0, 1.0, 0.0);
    OdGePoint3d origin(0.0, 0.0, 0.0);
    normal.normalize();
    OdGePlane gePlane(origin, normal);
    OdGeInterval intU(-3., 3);
    OdGeInterval intV(-3., 3);
    gePlane.setEnvelope(intU, intV);
    pPlane->setFromOdGeSurface(gePlane);
    viewClippingPlanes.push_back(pPlane);
  }

  // create view with XY clipping plane translated from origin
  {
    OdPrcViewPtr pNewView = OdPrcView::createObject();
    pNewFileStructure->addObject(pNewView);
    OdPrcName name;
    name.setName(L"top view clipped by XY");
    pNewView->name() = name;
    // - add view to PO
    OdPrcProductOccurrencePtr productOc = pFile->fileStructures().last()->fileStructureTree().productOccurrence().last();
    OdPrcObjectIdArray &arr_view = productOc->annotationViews();
    arr_view.push_back(pNewView->id());
    OdPrcSceneDisplayParametersPtr pSceneDisplayParameters = OdPrcSceneDisplayParameters::createObject();
    pNewFileStructure->addObject(pSceneDisplayParameters);
    pNewView->sceneDisplayParameters() = pSceneDisplayParameters->id();

    // - setup camera for view
    OdPrcCameraPtr pCamera = OdPrcCamera::createObject();
    pNewFileStructure->addObject(pCamera);
    pCamera->lookAt().set(0.0, 0.0, 0.0);
    pCamera->up().set(-1.0, -1.0, 0.0);
    pCamera->location().set(0.0, 0.0, 5.0);
    pCamera->setXFov(1.0472); // - in radians
    pCamera->setYFov(1.0472);
    pSceneDisplayParameters->camera() = pCamera->id();

    // - add clipping plane to the view
    {
      OdPrcSurfacePtrArray &viewClippingPlanes = ((OdPrcSceneDisplayParameters*)pSceneDisplayParameters)->clippingPlanes();
      OdPrcPlanePtr pPlane = OdPrcPlane::createObject();
      OdGeVector3d normal(0.0, 0.0, -1.0);
      OdGePoint3d origin(0.0, 0.0, 0.5);
      normal.normalize();
      OdGePlane gePlane(origin, normal);
      OdGeInterval intU(-3., 3);
      OdGeInterval intV(-3., 3);
      gePlane.setEnvelope(intU, intV);
      pPlane->setFromOdGeSurface(gePlane);
      viewClippingPlanes.push_back(pPlane);
    }
//     {
//       // - add clipping plane to the view
//       OdPrcSurfacePtrArray &viewClippingPlanes = ((OdPrcSceneDisplayParameters*)pSceneDisplayParameters)->clippingPlanes();
//       OdPrcPlanePtr pPlane = OdPrcPlane::createObject();
//       OdGeVector3d normal(0.0, 1.0, 0.0);
//       OdGePoint3d origin(0.0, 0.0, 0.0);
//       normal.normalize();
//       OdGePlane gePlane(origin, normal);
//       OdGeInterval intU(-3., 3);
//       OdGeInterval intV(-3., 3);
//       gePlane.setEnvelope(intU, intV);
//       pPlane->setFromOdGeSurface(gePlane);
//       viewClippingPlanes.push_back(pPlane);
//     }
  }

  // create view with tilted clipping plane
  {
    OdPrcViewPtr pNewView = OdPrcView::createObject();
    pNewFileStructure->addObject(pNewView);
    OdPrcName name;
    name.setName(L"NE Isometric clipped by 111");
    pNewView->name() = name;
    // - add view to PO
    OdPrcProductOccurrencePtr productOc = pFile->fileStructures().last()->fileStructureTree().productOccurrence().last();
    OdPrcObjectIdArray &arr_view = productOc->annotationViews();
    arr_view.push_back(pNewView->id());
    OdPrcSceneDisplayParametersPtr pSceneDisplayParameters = OdPrcSceneDisplayParameters::createObject();
    pNewFileStructure->addObject(pSceneDisplayParameters);
    pNewView->sceneDisplayParameters() = pSceneDisplayParameters->id();

    // - setup camera for view
    OdPrcCameraPtr pCamera = OdPrcCamera::createObject();
    pNewFileStructure->addObject(pCamera);
    pCamera->lookAt().set(0.0, 0.0, 0.0);
    pCamera->up().set(0.0, 0.0, 1.0);
    pCamera->location().set(5.0, 5.0, 5.0);
    pCamera->setXFov(1.0472);
    pCamera->setYFov(1.0472);
    pSceneDisplayParameters->camera() = pCamera->id();

    // - add clipping plane to the view
    OdPrcSurfacePtrArray &viewClippingPlanes = ((OdPrcSceneDisplayParameters*)pSceneDisplayParameters)->clippingPlanes();
    OdPrcPlanePtr pPlane = OdPrcPlane::createObject();
    OdGeVector3d normal(1.0, 1.0, 0.0);
    OdGePoint3d origin(0.0, 0.0, 0.0);
    normal.normalize();
    OdGePlane gePlane(origin, normal);
    OdGeInterval intU(-3., 3);
    OdGeInterval intV(-3., 3);
    gePlane.setEnvelope(intU, intV);
    pPlane->setFromOdGeSurface(gePlane);
    viewClippingPlanes.push_back(pPlane);
  }

  // write file
  pFile->writeFile(pPrcStream);
}

void viewWithBackgroundExample(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  // create an object
  OdStreamBufPtr pMemStream = OdMemoryStream::createNew();
  createTestGeometryForCrossSectionTest(pMemStream, pH);

  // open file
  pMemStream->rewind();
  OdPrcFilePtr pFile = pPrcHost.readFile(pMemStream);
  OdPrcFileStructurePtr pNewFileStructure = pFile->fileStructures().last();

  // create view
  {
    OdPrcViewPtr pNewView = OdPrcView::createObject();
    pNewFileStructure->addObject(pNewView);
    OdPrcName name;
    name.setName(L"NE Isometric");
    pNewView->name() = name;
    // - add view to PO
    OdPrcProductOccurrencePtr productOc = pFile->fileStructures().last()->fileStructureTree().productOccurrence().last();
    OdPrcObjectIdArray &arr_view = productOc->annotationViews();
    arr_view.push_back(pNewView->id());
    OdPrcSceneDisplayParametersPtr pSceneDisplayParameters = OdPrcSceneDisplayParameters::createObject();
    pNewFileStructure->addObject(pSceneDisplayParameters);
    pNewView->sceneDisplayParameters() = pSceneDisplayParameters->id();

    // - setup camera for view
    OdPrcCameraPtr pCamera = OdPrcCamera::createObject();
    pNewFileStructure->addObject(pCamera);
    pCamera->lookAt().set(0.0, 0.0, 0.0);
    pCamera->up().set(0.0, 0.0, 1.0);
    pCamera->location().set(5.0, 5.0, 5.0);
    pCamera->setXFov(1.0472);
    pCamera->setYFov(1.0472);
    pSceneDisplayParameters->camera() = pCamera->id();

    // create background for view
    OdPrcObjectId backgroundColorID = OdPrcCategory1LineStyle::createByColor(0.00, 1.00, 1.00, *pNewFileStructure); // add line style to prc file
    pSceneDisplayParameters->backgroundStyle() = backgroundColorID;
  }

  // write file
  pFile->writeFile(pPrcStream);
}
