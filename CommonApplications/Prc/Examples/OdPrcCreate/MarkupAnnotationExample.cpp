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
#include "PrcMarkupTessBuf.h"
#include "PrcAnnotationItem.h"
#include "PrcAnnotationSet.h"
#include "Ge/GeExtents3d.h"
#include "OdPrcCreateStart.h"
#include "PrcCreateTopologyHelper.h"

void CreateAnnItemMarkup(OdPrcMarkupPtr &markup)
{
  markup->setType(OdPrcMarkup::kText);

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

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
  OdGePoint3d origP(0, 0, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"Annotation Item", 3, 2) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  OdPrcFileStructurePtr pCurFS = markup->objectId().database();
  ODA_VERIFY(!pCurFS.isNull());

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, *pCurFS) == eOk);
  mTess->setLabel(L"test");

  markup->tessellation() = mTess;
}

void CreateAnnItem1ForSetMarkup(OdPrcMarkupPtr &markup)
{
  markup->setType(OdPrcMarkup::kText);

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

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
  OdGePoint3d origP(0, 0, -1);
  OdGeMatrix3d matr;
  matr.setCoordSystem(origP, OdGeVector3d::kXAxis, OdGeVector3d(0, 0, -1), OdGeVector3d(0, 1, 0));
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(matr);
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"Annotation Item.1", 3, 2) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  OdPrcFileStructurePtr pCurFS = markup->objectId().database();
  ODA_VERIFY(!pCurFS.isNull());

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, *pCurFS) == eOk);
  mTess->setLabel(L"test");

  markup->tessellation() = mTess;
}

void CreateAnnItem2ForSetMarkup(OdPrcMarkupPtr &markup)
{
  markup->setType(OdPrcMarkup::kText);

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

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
  OdGeMatrix3d matr;
  matr.setCoordSystem(OdGePoint3d::kOrigin, OdGeVector3d::kXAxis, OdGeVector3d(0, 0, -1), OdGeVector3d(0, 1, 0));
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(matr);
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"Annotation Item.2", 3, 2) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  OdPrcFileStructurePtr pCurFS = markup->objectId().database();
  ODA_VERIFY(!pCurFS.isNull());

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, *pCurFS) == eOk);
  mTess->setLabel(L"test");

  markup->tessellation() = mTess;
}


void AddAnnotationExample(OdPrcFileStructure &newStructure,OdPrcProductOccurrencePtr &newProductOccurrence)
{
  OdPrcObjectId un_id;
  OdPrcName name;
  name.setName(L"test");

  OdPrcObjectIdArray &arr = newProductOccurrence->markups().markups();

  OdPrcMarkupPtr annItemMarkup = OdPrcMarkup::createObject();
  newStructure.addObject(annItemMarkup);
  CreateAnnItemMarkup(annItemMarkup);

  OdPrcMarkupPtr annItem1ForSetMarkup = OdPrcMarkup::createObject();
  newStructure.addObject(annItem1ForSetMarkup);
  CreateAnnItem1ForSetMarkup(annItem1ForSetMarkup);

  OdPrcMarkupPtr annItem2ForSetMarkup = OdPrcMarkup::createObject();
  newStructure.addObject(annItem2ForSetMarkup);
  CreateAnnItem2ForSetMarkup(annItem2ForSetMarkup);

  arr.push_back(annItemMarkup->objectId());
  arr.push_back(annItem1ForSetMarkup->objectId());
  arr.push_back(annItem2ForSetMarkup->objectId());

  OdPrcObjectIdArray &arr_entity = newProductOccurrence->markups().annotationEntities();

  OdPrcAnnotationItemPtr annItem = OdPrcAnnotationItem::createObject();
  annItem->name() = name;
  un_id = annItemMarkup->objectId();
  annItem->markup() = un_id;
  newStructure.addObject(annItem);
  arr_entity.push_back(annItem->objectId());

  OdPrcAnnotationSetPtr annSet = OdPrcAnnotationSet::createObject();
  annSet->name() = name;
  newStructure.addObject(annSet);
  OdPrcObjectIdArray &arr_set_ann = annSet->entities();
  {
    OdPrcAnnotationItemPtr annItem1ForSet = OdPrcAnnotationItem::createObject();
    annItem1ForSet->name() = name;
    un_id = annItem1ForSetMarkup->objectId();
    annItem1ForSet->markup() = un_id;
    newStructure.addObject(annItem1ForSet);
    arr_set_ann.push_back(annItem1ForSet->objectId());
  }
  {
    OdPrcAnnotationItemPtr annItem2ForSet = OdPrcAnnotationItem::createObject();
    annItem2ForSet->name() = name;
    un_id = annItem2ForSetMarkup->objectId();
    annItem2ForSet->markup() = un_id;
    newStructure.addObject(annItem2ForSet);
    arr_set_ann.push_back(annItem2ForSet->objectId());
  }
  arr_entity.push_back(annSet->objectId());

  
  newStructure.fileStructureTessellation().tessellations().push_back(annItemMarkup->tessellation());
  newStructure.fileStructureTessellation().tessellations().push_back(annItem1ForSetMarkup->tessellation());
  newStructure.fileStructureTessellation().tessellations().push_back(annItem2ForSetMarkup->tessellation());

  OdPrcObjectIdArray &arr_view = newProductOccurrence->annotationViews();
  OdPrcViewPtr itemView = OdPrcView::createObject();
  name.setName(L"AnnotationItemView");
  itemView->name() = name;
  un_id = annItem->objectId();
  itemView->annotations().push_back(un_id);

  OdPrcPlanePtr itemPlane = OdPrcPlane::createObject();
  OdPrcContentSurface content_suface;
  content_suface.baseGeometry().setBaseInformation(false);
  itemPlane->contentSurface() = content_suface;
  itemView->plane() = itemPlane;
  itemView->setIsAnnotationView(true);

  newStructure.addObject(itemView);
  arr_view.push_back(itemView->objectId());
  
  OdPrcViewPtr setView = OdPrcView::createObject();
  name.setName(L"AnnotationSetView");
  setView->name() = name;
  un_id = annSet->objectId();
  setView->annotations().push_back(un_id);

  OdPrcPlanePtr setPlane = OdPrcPlane::createObject();
  content_suface.baseGeometry().setBaseInformation(false);
  setPlane->contentSurface() = content_suface;
  OdPrcTransformation3d transform;
  OdGeMatrix3d geMatrix;
  geMatrix.setCoordSystem(OdGePoint3d(0,9,0),OdGeVector3d(1,0,0),OdGeVector3d(0,0,-1),OdGeVector3d(0,1,0));
  transform.set(geMatrix);   
  setPlane->setTransformation(&transform);
  setView->plane() = setPlane;
  setView->setIsAnnotationView(true);
  newStructure.addObject(setView);
  arr_view.push_back(setView->objectId());
}

OdPrcFilePtr CreateAnnotationExample (void)
{
  // common
  OdGeExtents3d extents;
  extents.addPoint(OdGePoint3d(0,0,0));
  extents.addPoint(OdGePoint3d(1,1,1));
  OdPrcFilePtr pFile = createTopologyCommon();
  OdPrcFileStructurePtr pFS = pFile->fileStructures().last();

  OdPrcProductOccurrencePtr pRootPO = pFS->fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcProductOccurrencePtr pPO = createProductOccurrence(*pFS, *pRootPO);
  OdPrcPartDefinitionPtr pPD = createPartDefinition(*pFS, *pPO);
  pPD->boundingBox().box() = extents;

  AddAnnotationExample(*pFS, pPO);

  return pFile;
}

// main
void markupAnnotationExample (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  ODA_ASSERT(mode == kMarkupAnnotationExample);
  
  OdPrcFilePtr pFile = CreateAnnotationExample();
  // export prc
  pFile->writeFile(pPrcStream);
}

