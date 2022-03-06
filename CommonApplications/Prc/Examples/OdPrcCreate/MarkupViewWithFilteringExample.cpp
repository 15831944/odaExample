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

#include "PrcFile.h"
#include "Ge/GeExtents3d.h"
#include "OdPrcCreateStart.h"
#include "PrcBrepModel.h"
#include "PrcBrepData.h"
#include "PrcSphere.h"
#include "PrcTorus.h"
#include "PrcMarkupTessBuf.h"
#include "PrcAnnotationItem.h"
#include "PrcCreateTopologyHelper.h"

void FillTopoBrepFace (OdPrcBrepDataPtr brepData, OdPrcSurfacePtr pSurface);
OdPrcProductOccurrencePtr CreateTopologyCommonForBrepCylinder(OdPrcFileStructure & FSt, OdGeExtents3d &extents);

void addColorToBaseWithGraphics(OdPrcFileStructurePtr curFileStructure, OdPrcBaseWithGraphicsPtr pBaseWithGraphics, double r, double g, double b)
{
  OdPrcObjectId newLineStyleId = OdPrcCategory1LineStyle::createByColor(r, g, b, *curFileStructure);
  
  // Attribute
  pBaseWithGraphics->styleId() = newLineStyleId;
  pBaseWithGraphics->setBehaviourBitField(PRC_GRAPHICS_Show);
}

OdPrcSurfacePtr CreateTorusForMkpView ()
{
  OdPrcTorusPtr pPrcTorus = OdPrcTorus::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcTorus->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named torus in srfContent");

    pPrcTorus->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, 0, Oda2PI));

    // can add transformation if needed here
    // TBD

    pPrcTorus->setMajorRadius(1.5);
    pPrcTorus->setMinorRadius(0.75);
  }
  return pPrcTorus;
}

OdPrcSurfacePtr CreateSphereForMkpView ()
{
  OdPrcSpherePtr pPrcSphere = OdPrcSphere::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcSphere->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named sphere in srfContent");
    pPrcSphere->setUVParameterization(OdPrcUVParameterization(0., Oda2PI, -OdaPI/2, OdaPI/2));

    // can add transformation if needed here
    OdPrcTransformation3d trans;
    trans.set(OdGeMatrix3d::translation(OdGeVector3d(0., 5., 0.)));
    pPrcSphere->setTransformation(&trans);
    // TBD

    pPrcSphere->setRadius(2.);
  }
  return pPrcSphere;
}

struct TextInfo
{
  OdString text;
  OdGeMatrix3d matr;
  double textWidth;
  double textHeight;
  OdPrcRgbColor color;
  OdUInt16 behBitField;

  TextInfo()
    : textWidth(1.)
    , textHeight(1.)
    , behBitField(PRC_GRAPHICS_Show)
  {
  }
};

OdPrcAnnotationItemPtr CreateTextMarkup(OdPrcProductOccurrencePtr &newProductOccurrence, const TextInfo &textInfo)
{
  OdPrcFileStructure *pCurFS = (OdPrcFileStructure *)newProductOccurrence->objectId().database();
  ODA_VERIFY(pCurFS);

  OdPrcMarkupPtr pMkp = OdPrcMarkup::createObject();
  pCurFS->addObject(pMkp);

  pMkp->setBehaviourBitField(textInfo.behBitField);
  pMkp->setType(OdPrcMarkup::kText, OdPrcMarkup::kUnknownSubtype);

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  pFirstMkpTess->setColor(textInfo.color);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  OdPrcFontKeysSameFont font;
  font.setFontName(L"Arial");
  font.setCharSet(0);
  font.fontKeys().resize(1);
  font.fontKeys()[0].font_size = 5;
  font.fontKeys()[0].attributes = 1;
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(textInfo.matr);
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(textInfo.text, textInfo.textWidth, textInfo.textHeight) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, *pCurFS) == eOk);
  mTess->setLabel(L"test");

  pMkp->tessellation() = mTess;
  pCurFS->fileStructureTessellation().tessellations().push_back(mTess);

  OdPrcAnnotationItemPtr pAnn = OdPrcAnnotationItem::createObject();
  pCurFS->addObject(pAnn);
  pAnn->markup() = pMkp->objectId();
  newProductOccurrence->markups().markups().push_back(pMkp->objectId());
  newProductOccurrence->markups().annotationEntities().push_back(pAnn->objectId());
  return pAnn;
}

void AddViewWithFilteringExample(OdPrcProductOccurrencePtr &newPO, OdPrcProductOccurrencePtr &newPOBrep1, OdPrcProductOccurrencePtr &newPOBrep2)
{
  OdPrcFileStructure *pCurFS = (OdPrcFileStructure *)newPO->objectId().database();
  ODA_VERIFY(pCurFS);

  OdPrcName name;
  name.setName(L"test");
  OdPrcObjectIdArray &arr_view = newPO->annotationViews();
  OdPrcViewPtr torusView = OdPrcView::createObject();
  name.setName(L"TorusView");
  torusView->name() = name;

  OdPrcPlanePtr torusPlane = OdPrcPlane::createObject();
  OdPrcContentSurface content_suface;
  OdPrcTransformation3d transform;
  OdGeMatrix3d geMatrix;
  geMatrix.setTranslation(OdGeVector3d(0, 1.3, -2));
  geMatrix *= OdGeMatrix3d::rotation(OdaPI+OdaPI2, OdGeVector3d::kZAxis);
  geMatrix *= OdGeMatrix3d::rotation(OdaPI2, OdGeVector3d::kXAxis);
  transform.set(geMatrix);
  torusPlane->setTransformation(&transform);
  torusPlane->setUVParameterization(OdPrcUVParameterization(OdPrcDomain::kInfinite));
  content_suface.baseGeometry().setBaseInformation(false);
  torusPlane->contentSurface() = content_suface;
  torusView->plane() = torusPlane;
  torusView->setIsAnnotationView(true);
  torusView->setBehaviourBitField(PRC_GRAPHICS_FatherHeritShow);

  pCurFS->addObject(torusView);
  arr_view.push_back(torusView->objectId());

  // markup for invisibility sphere
  OdPrcMarkupLinkedItemPtr pMkpLIS = OdPrcMarkupLinkedItem::createObject();
  pCurFS->addObject(pMkpLIS);
  newPO->markups().linkedItem().push_back(pMkpLIS->objectId());
  pMkpLIS->referencedProductOccurrence().referenceOnPRCBase() = newPOBrep2->objectId();
  pMkpLIS->referenceData().referenceOnPRCBase() = newPOBrep2->getPartDefinition()->representationItem().last();
  pMkpLIS->setBehaviourBitField(PRC_GRAPHICS_FatherHeritShow);
  torusView->linkedItems().push_back(pMkpLIS->objectId());
  // end of markup

  // create text
  TextInfo textInfo;
  textInfo.text = L"Torus";
  textInfo.matr = geMatrix;
  textInfo.textWidth = 2.3;
  textInfo.textHeight = 1.3;
  textInfo.color.set(1., 1, 0.);
  textInfo.behBitField = PRC_GRAPHICS_FatherHeritShow;
  torusView->annotations().push_back(CreateTextMarkup(newPOBrep1, textInfo)->objectId());

  // camera configuration
  OdPrcCameraPtr pCam1 = OdPrcCamera::createObject();
  pCurFS->addObject(pCam1);
  pCam1->location().set(-5.92978, -2.39579, 1.3594);
  pCam1->lookAt().set(0, 0, 0);
  pCam1->up().set(0.192772, 0.0778851, 0.978148);
  pCam1->setXFov(3.26917);
  pCam1->setYFov(3.26917);
  pCam1->setZFar(13.0767);
  pCam1->setOrthographic(true);
  pCam1->setAspectRatio(1.);
  pCam1->setZNear(0.);
  OdPrcSceneDisplayParametersPtr pSDP1 = OdPrcSceneDisplayParameters::createObject();
  pCurFS->addObject(pSDP1);
  pSDP1->camera() = pCam1->objectId();
  torusView->sceneDisplayParameters() = pSDP1->objectId();

  OdPrcViewPtr sphereView = OdPrcView::createObject();
  name.setName(L"SphereView");
  sphereView->name() = name;

  OdPrcPlanePtr spherePlane = OdPrcPlane::createObject();
  content_suface.baseGeometry().setBaseInformation(false);
  spherePlane->contentSurface() = content_suface;
  geMatrix.setTranslation(OdGeVector3d(0, 6.1, -3.));
  transform.set(geMatrix);
  spherePlane->setTransformation(&transform);
  spherePlane->setUVParameterization(OdPrcUVParameterization(OdPrcDomain::kInfinite));
  sphereView->plane() = spherePlane;
  sphereView->setIsAnnotationView(true);
  sphereView->setBehaviourBitField(PRC_GRAPHICS_FatherHeritShow);

  pCurFS->addObject(sphereView);
  arr_view.push_back(sphereView->objectId());

  // markup for invisibility torus
  OdPrcMarkupLinkedItemPtr pMkpLIT = OdPrcMarkupLinkedItem::createObject();
  pCurFS->addObject(pMkpLIT);
  newPO->markups().linkedItem().push_back(pMkpLIT->objectId());
  pMkpLIT->referencedProductOccurrence().referenceOnPRCBase() = newPOBrep1->objectId();
  pMkpLIT->referenceData().referenceOnPRCBase() = newPOBrep1->getPartDefinition()->representationItem().last();
  pMkpLIT->setBehaviourBitField(PRC_GRAPHICS_FatherHeritShow);
  sphereView->linkedItems().push_back(pMkpLIT->objectId());
  // end of markup

  // create text
  textInfo.text = L"Sphere";
  textInfo.matr = geMatrix;
  textInfo.textWidth = 2.3;
  textInfo.textHeight = 1.3;
  textInfo.color.set(0., 1., 1.);
  textInfo.behBitField = PRC_GRAPHICS_FatherHeritShow;
  sphereView->annotations().push_back(CreateTextMarkup(newPOBrep2, textInfo)->objectId());

  // camera configuration
  OdPrcCameraPtr pCam2 = OdPrcCamera::createObject();
  pCurFS->addObject(pCam2);
  pCam2->location().set(-5.92978, 2.60421, 1.3594);
  pCam2->lookAt().set(0, 5, 0);
  pCam2->up().set(0.192772, 0.0778851, 0.978148);
  pCam2->setXFov(4.);
  pCam2->setYFov(4.);
  pCam2->setZFar(13.0767);
  pCam2->setOrthographic(true);
  pCam2->setAspectRatio(1.);
  pCam2->setZNear(0.);
  OdPrcSceneDisplayParametersPtr pSDP2 = OdPrcSceneDisplayParameters::createObject();
  pCurFS->addObject(pSDP2);
  pSDP2->camera() = pCam2->objectId();
  sphereView->sceneDisplayParameters() = pSDP2->objectId();
}

OdPrcFilePtr CreateViewWithFilteringExample (bool filterByLayer = true)
{
  // common
  OdGeExtents3d extents;
  extents.addPoint(OdGePoint3d(-10,-10,-10));
  extents.addPoint(OdGePoint3d(10,10,10));
  OdPrcFilePtr pFile = createTopologyCommon();
  OdPrcFileStructure &newStructure = *(pFile->fileStructures().last());

  OdPrcProductOccurrencePtr rootOccurrence = pFile->modelFileData().getStartRootOccurrences().last().openObject(kForWrite);
  rootOccurrence->name().setName(L"rootPO");

  // product occurrence for torus
  OdPrcProductOccurrencePtr newPOBrep1;
  {
    newPOBrep1 = CreateTopologyCommonForBrepCylinder(newStructure, extents);
    newPOBrep1->name().setName(L"TorusPO");

    // Add color
    addColorToBaseWithGraphics(&newStructure, newPOBrep1, 1., 0., 0.);

    // fill it with Brep Data
    OdPrcTopoContextPtr newTopoContext = newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
    OdPrcBrepDataPtr brepData = newTopoContext->bodies().last().safeOpenObject(kForWrite);
    FillTopoBrepFace(brepData, CreateTorusForMkpView());

    OdPrcPartDefinitionPtr newDefinition = newStructure.fileStructureTree().partDefinition().last().safeOpenObject(kForWrite);
    OdPrcBrepModelPtr pBrepModel1 = newDefinition->representationItem().last().openObject(kForWrite);
    pBrepModel1->name().setName(L"TorusBM");
    ODA_VERIFY(pBrepModel1->updateIsClosedFlag() == eOk);
  }

  // product occurrence for sphere
  OdPrcProductOccurrencePtr newPOBrep2;
  {
    newPOBrep2 = CreateTopologyCommonForBrepCylinder(newStructure, extents);
    newPOBrep2->name().setName(L"SpherePO");

    // Add color
    addColorToBaseWithGraphics(&newStructure, newPOBrep2, 0., 1., 0.);

    // fill it with Brep Data
    OdPrcTopoContextPtr newTopoContext = newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
    OdPrcBrepDataPtr brepData = newTopoContext->bodies().last().safeOpenObject(kForWrite);
    FillTopoBrepFace(brepData, CreateSphereForMkpView());

    OdPrcPartDefinitionPtr newDefinition = newStructure.fileStructureTree().partDefinition().last().safeOpenObject(kForWrite);
    OdPrcBrepModelPtr pBrepModel2 = newDefinition->representationItem().last().openObject(kForWrite);
    pBrepModel2->name().setName(L"SphereBM");
    ODA_VERIFY(pBrepModel2->updateIsClosedFlag() == eOk);
  }

  TextInfo textInfo;
  textInfo.text = L"Sphere and Torus";
  OdGeMatrix3d geMatrix;
  geMatrix.setTranslation(OdGeVector3d(0, 5.5, -3.5));
  geMatrix *= OdGeMatrix3d::rotation(OdaPI+OdaPI2, OdGeVector3d::kZAxis);
  geMatrix *= OdGeMatrix3d::rotation(OdaPI2, OdGeVector3d::kXAxis);
  textInfo.matr = geMatrix;
  textInfo.textWidth = 6;
  textInfo.textHeight = 2;
  textInfo.color.set(0., 0., 1.);
  textInfo.behBitField = PRC_GRAPHICS_Show;
  CreateTextMarkup(rootOccurrence, textInfo);

  AddViewWithFilteringExample(rootOccurrence, newPOBrep1, newPOBrep2);

  return pFile;
}

// main
void markupViewWithFilteringExample (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  ODA_ASSERT(mode == kMarkupViewWithFilteringExample);

  OdPrcFilePtr pFile = CreateViewWithFilteringExample(false);
  // export prc
  pFile->writeFile(pPrcStream);
}

