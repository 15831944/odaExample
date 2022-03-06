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
#include "PrcBrepModel.h"
#include "PrcBrepData.h"
#include "PrcCylinder.h"
#include "PrcCreateTopologyHelper.h"

void addLineStyleForBrep (OdPrcFileStructure &newStructure, double r, double g, double b);
void addGraphicDataToBrep (OdPrcFileStructure &newStructure);
void FillTopoBrepFace (OdPrcBrepDataPtr brepData, OdPrcSurfacePtr pSurface);
OdPrcSurfacePtr createCylinderforView ()
{
  OdPrcCylinderPtr pPrcCylinder = OdPrcCylinder::createObject();
  {
    OdPrcContentSurface &srfContent  = pPrcCylinder->contentSurface();

    // set name
    srfContent.baseGeometry().name().setName(L"named cylinder in srfContent");

    pPrcCylinder->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, 0, 9));
    // can add transformation if needed here
    // TBD

    pPrcCylinder->setRadius(2);

    OdPrcTransformation3d transform;
    OdGeMatrix3d geMatrix;
    geMatrix.setCoordSystem(OdGePoint3d(0,0,0),OdGeVector3d(1,0,0),OdGeVector3d(0,0,-1),OdGeVector3d(0,1,0));
    //transform.set(geMatrix);
    transform.set(geMatrix);
    pPrcCylinder->setTransformation(&transform);

  }
  return pPrcCylinder;
}

OdPrcProductOccurrencePtr CreateTopologyCommonForBrepCylinder(OdPrcFileStructure & FSt, OdGeExtents3d &extents)
{
  OdPrcProductOccurrencePtr pRootPO = FSt.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcProductOccurrencePtr newProductOccurrence = createProductOccurrence(FSt, *pRootPO);
  OdPrcPartDefinitionPtr newDefinition = createPartDefinition(FSt, *newProductOccurrence);

  // bounding box
  newDefinition->boundingBox().box() = extents;

  // create brep model
  OdPrcBrepModelPtr newBrep = OdPrcBrepModel::createObject();
  FSt.addObject(newBrep);
  newBrep->setIsClosed(true);
  newDefinition->representationItem().push_back(newBrep->objectId());

  // create Brep Data
  OdPrcBrepDataPtr newBrepData = OdPrcBrepData::createObject();
  FSt.addObject(newBrepData);
  newBrepData->boundingBox().box() = extents;
  newBrepData->contentBody().setBoundingBoxBehaviour(2);

  // set reference to this body in representation item
  newBrep->setReferenceToBody(newBrepData);

  // file structure geometry section
  OdPrcTopoContextPtr newTopoContext = createTopoContext(FSt);
  newTopoContext->appendBody(newBrepData->objectId());
  return newProductOccurrence;
}

void CreateHeightDimensionMarkup(OdPrcMarkupPtr &markup)
{
  markup->setType(OdPrcMarkup::kDimension, OdPrcMarkup::kDimension_Distance);

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor redCol;
  redCol.set(1, 0, 0);
  pFirstMkpTess->setColor(redCol);

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
  OdGePoint3d origP(2.5, 4, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"9.000", 3, 2) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(3);
  pntsArr[0].set(3, 9, 0);
  pntsArr[1].set(3.1, 8.8, 0);
  pntsArr[2].set(2.9, 8.8, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  pntsArr[0].set(3, 0, 0);
  pntsArr[1].set(3.1, 0.2, 0);
  pntsArr[2].set(2.9, 0.2, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr.resize(2);
  pntsArr[0].set(3, 0.2, 0);
  pntsArr[1].set(3, 3.5, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr[0].set(3, 8.8, 0);
  pntsArr[1].set(3, 5.5, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  OdPrcFileStructurePtr pCurFS = markup->objectId().database();
  ODA_VERIFY(!pCurFS.isNull());

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, *pCurFS) == eOk);
  mTess->setLabel(L"test");

  markup->tessellation() = mTess;
}

void CreateLengthDimensionMarkup(OdPrcMarkupPtr &markup)
{
  markup->setType(OdPrcMarkup::kDimension, OdPrcMarkup::kDimension_Distance);

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor redCol;
  redCol.set(1, 0, 0);
  pFirstMkpTess->setColor(redCol);

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
  OdGePoint3d origP(-1.5, 10, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"4.000", 3, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(3);
  pntsArr[0].set(-2, 10, 0);
  pntsArr[1].set(-1.8, 10.1, 0);
  pntsArr[2].set(-1.8, 9.9, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  pntsArr[0].set(2, 10, 0);
  pntsArr[1].set(1.8, 10.1, 0);
  pntsArr[2].set(1.8, 9.9, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr.resize(2);
  pntsArr[0].set(-1.8, 10, 0);
  pntsArr[1].set(-1.5, 10, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr[0].set(1.8, 10, 0);
  pntsArr[1].set(1.5, 10, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  OdPrcFileStructurePtr pCurFS = markup->objectId().database();
  ODA_VERIFY(!pCurFS.isNull());

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, *pCurFS) == eOk);
  mTess->setLabel(L"test");

  markup->tessellation() = mTess;
}

void CreateDiameterDimensionMarkup(OdPrcMarkupPtr &markup)
{
  markup->setType(OdPrcMarkup::kDimension, OdPrcMarkup::kDimension_Angle);

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor redCol;
  redCol.set(1, 0, 0);
  pFirstMkpTess->setColor(redCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  OdPrcFontKeysSameFont font;
  font.setFontName(L"Arial");
  font.setCharSet(0);
  font.fontKeys().resize(1);
  font.fontKeys()[0].font_size = 4;
  font.fontKeys()[0].attributes = 1;
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  OdGePoint3d origP(-1.5, 9, -3);
  OdGeMatrix3d matr;
  OdGeVector3d vecX(0, 0, -1);
  OdGeVector3d vecY(1, 0, 0);
  matr.setCoordSystem(origP, vecX, vecY, vecX.crossProduct(vecY));
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(matr);
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"\u2300", 1, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  font.fontKeys()[0].font_size = 5;
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(-0.4, 9, -3.1);
  vecX.set(1, 0, 0);
  vecY.set(0, 0, -1);
  matr.setCoordSystem(origP, vecX, vecY, vecX.crossProduct(vecY));
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(matr);
  OdPrcMarkupTessBufTextPtr pBufText1 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText1->setText(L"4.00", 2, 1.5) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText1);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(3);
  pntsArr[0].set(-2, 9, -3);
  pntsArr[1].set(-1.8, 9, -3.1);
  pntsArr[2].set(-1.8, 9, -2.9);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  pntsArr[0].set(2, 9, -3);
  pntsArr[1].set(1.8, 9, -3.1);
  pntsArr[2].set(1.8, 9, -2.9);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr.resize(2);
  pntsArr[0].set(-1.8, 9, -3);
  pntsArr[1].set(1.8, 9, -3);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  OdPrcFileStructurePtr pCurFS = markup->objectId().database();
  ODA_VERIFY(!pCurFS.isNull());

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, *pCurFS) == eOk);
  mTess->setLabel(L"test");

  markup->tessellation() = mTess;
}

void CreateHeightDimensionLeaders (OdPrcObjectIdArray &leaders, OdPrcFileStructure &newStructure)
{
  //Create Leader
  OdPrcMarkupLeaderPtr leader = OdPrcMarkupLeader::createObject();
  newStructure.addObject(leader);

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor redCol;
  redCol.set(1, 0, 0);
  pFirstMkpTess->setColor(redCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(2);
  pntsArr[0].set(2, 0, 0);
  pntsArr[1].set(4, 0, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, newStructure) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader->objectId());
  newStructure.fileStructureTessellation().tessellations().push_back(mTess);

  leader = OdPrcMarkupLeader::createObject();
  newStructure.addObject(leader);

  pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  pFirstMkpTess->setColor(redCol);

  pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr[0].set(2, 9, 0);
  pntsArr[1].set(4, 9, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, newStructure) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader->objectId());
  newStructure.fileStructureTessellation().tessellations().push_back(mTess);
}

void CreateLengthDimensionLeaders (OdPrcObjectIdArray &leaders, OdPrcFileStructure &newStructure)
{
  //Create Leader
  OdPrcMarkupLeaderPtr leader = OdPrcMarkupLeader::createObject();
  newStructure.addObject(leader);

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor redCol;
  redCol.set(1, 0, 0);
  pFirstMkpTess->setColor(redCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(2);
  pntsArr[0].set(-2, 9, 0);
  pntsArr[1].set(-2, 11, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, newStructure) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader->objectId());
  newStructure.fileStructureTessellation().tessellations().push_back(mTess);

  leader = OdPrcMarkupLeader::createObject();
  newStructure.addObject(leader);

  pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  pFirstMkpTess->setColor(redCol);

  pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr[0].set(2, 9, 0);
  pntsArr[1].set(2, 11, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, newStructure) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader->objectId());
  newStructure.fileStructureTessellation().tessellations().push_back(mTess);
}

void CreateDiameterDimensionLeaders (OdPrcObjectIdArray &leaders, OdPrcFileStructure &newStructure)
{
  //Create Leader
  OdPrcMarkupLeaderPtr leader = OdPrcMarkupLeader::createObject();
  newStructure.addObject(leader);

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor redCol;
  redCol.set(1, 0, 0);
  pFirstMkpTess->setColor(redCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(2);
  pntsArr[0].set(-2, 9, 0);
  pntsArr[1].set(-2, 9, -4);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, newStructure) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader->objectId());
  newStructure.fileStructureTessellation().tessellations().push_back(mTess);
  
  leader = OdPrcMarkupLeader::createObject();
  newStructure.addObject(leader);

  pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  pFirstMkpTess->setColor(redCol);

  pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr[0].set(2, 9, 0);
  pntsArr[1].set(2, 9, -4);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, newStructure) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader->objectId());
  newStructure.fileStructureTessellation().tessellations().push_back(mTess);
}

void AddViewExample(OdPrcFileStructure &newStructure,OdPrcProductOccurrencePtr &newProductOccurrence)
{
  OdPrcObjectId un_id;
  OdPrcName name;
  name.setName(L"test");

  //Create Leader
  OdPrcObjectIdArray &leaders = newProductOccurrence->markups().leaders();
  CreateHeightDimensionLeaders(leaders, newStructure);
  CreateLengthDimensionLeaders(leaders, newStructure);
  CreateDiameterDimensionLeaders(leaders, newStructure);

  OdPrcObjectIdArray &arr = newProductOccurrence->markups().markups();
  OdPrcMarkupPtr heightDimensionMarkup = OdPrcMarkup::createObject();
  newStructure.addObject(heightDimensionMarkup);
  CreateHeightDimensionMarkup(heightDimensionMarkup);
  un_id = leaders[0];
  heightDimensionMarkup->leader().push_back(un_id);
  un_id = leaders[1];
  heightDimensionMarkup->leader().push_back(un_id);

  OdPrcMarkupPtr lengthDimensionMarkup = OdPrcMarkup::createObject();
  newStructure.addObject(lengthDimensionMarkup);
  CreateLengthDimensionMarkup(lengthDimensionMarkup);
  un_id = leaders[2];
  lengthDimensionMarkup->leader().push_back(un_id);
  un_id = leaders[3];
  lengthDimensionMarkup->leader().push_back(un_id);

  OdPrcMarkupPtr diameterDimensionMarkup = OdPrcMarkup::createObject();
  newStructure.addObject(diameterDimensionMarkup);
  CreateDiameterDimensionMarkup(diameterDimensionMarkup);
  un_id = leaders[4];
  diameterDimensionMarkup->leader().push_back(un_id);
  un_id = leaders[5];
  diameterDimensionMarkup->leader().push_back(un_id);

  arr.push_back(heightDimensionMarkup->objectId());
  arr.push_back(lengthDimensionMarkup->objectId());
  arr.push_back(diameterDimensionMarkup->objectId());

  OdPrcObjectIdArray &arr_entity = newProductOccurrence->markups().annotationEntities();

  OdPrcAnnotationSetPtr annSetFront = OdPrcAnnotationSet::createObject();
  annSetFront->name() = name;
  newStructure.addObject(annSetFront);
  OdPrcObjectIdArray &arr_front_ann = annSetFront->entities();

  {
    OdPrcAnnotationItemPtr annForHeight = OdPrcAnnotationItem::createObject();
    annForHeight->name() = name;
    un_id = heightDimensionMarkup->objectId();
    annForHeight->markup() = un_id;
    newStructure.addObject(annForHeight);
    arr_front_ann.push_back(annForHeight->objectId());
  }
  {
    OdPrcAnnotationItemPtr annForLength = OdPrcAnnotationItem::createObject();
    annForLength->name() = name;
    un_id = lengthDimensionMarkup->objectId();
    annForLength->markup() = un_id;
    newStructure.addObject(annForLength);
    arr_front_ann.push_back(annForLength->objectId());
  }
  arr_entity.push_back(annSetFront->objectId());

  OdPrcAnnotationSetPtr annSetTop = OdPrcAnnotationSet::createObject();
  annSetTop->name() = name;
  newStructure.addObject(annSetTop);
  OdPrcObjectIdArray &arr_top_ann = annSetTop->entities();
  {
    OdPrcAnnotationItemPtr annForDiameter = OdPrcAnnotationItem::createObject();
    annForDiameter->name() = name;
    un_id = diameterDimensionMarkup->objectId();
    annForDiameter->markup() = un_id;
    newStructure.addObject(annForDiameter);
    arr_top_ann.push_back(annForDiameter->objectId());
  }
  arr_entity.push_back(annSetTop->objectId());

  newStructure.fileStructureTessellation().tessellations().push_back(heightDimensionMarkup->tessellation());
  newStructure.fileStructureTessellation().tessellations().push_back(lengthDimensionMarkup->tessellation());
  newStructure.fileStructureTessellation().tessellations().push_back(diameterDimensionMarkup->tessellation());

  OdPrcObjectIdArray &arr_view = newProductOccurrence->annotationViews();
  OdPrcViewPtr frontView = OdPrcView::createObject();
  name.setName(L"frontView");
  frontView->name() = name;
  un_id = annSetFront->objectId();
  frontView->annotations().push_back(un_id);

  OdPrcPlanePtr frontPlane = OdPrcPlane::createObject();
  OdPrcContentSurface content_suface;
  content_suface.baseGeometry().setBaseInformation(false);
  frontPlane->contentSurface() = content_suface;
  frontView->plane() = frontPlane;
  frontView->setIsAnnotationView(true);

  newStructure.addObject(frontView);
  arr_view.push_back(frontView->objectId());
  
  OdPrcViewPtr topView = OdPrcView::createObject();
  name.setName(L"topView");
  topView->name() = name;
  un_id = annSetTop->objectId();
  topView->annotations().push_back(un_id);

  OdPrcPlanePtr topPlane = OdPrcPlane::createObject();
  content_suface.baseGeometry().setBaseInformation(false);
  topPlane->contentSurface() = content_suface;
  OdPrcTransformation3d transform;
  OdGeMatrix3d geMatrix;
  geMatrix.setCoordSystem(OdGePoint3d(0,9,0),OdGeVector3d(1,0,0),OdGeVector3d(0,0,-1),OdGeVector3d(0,1,0));
  transform.set(geMatrix);   
  topPlane->setTransformation(&transform);
  topView->plane() = topPlane;
  topView->setIsAnnotationView(true);
  newStructure.addObject(topView);
  arr_view.push_back(topView->objectId());
}

OdPrcFilePtr CreateViewExample (void)
{
  // common
  OdGeExtents3d extents;
  extents.addPoint(OdGePoint3d(0,0,0));
  extents.addPoint(OdGePoint3d(1,1,1));
  OdPrcFilePtr pFile = createTopologyCommon();
  OdPrcFileStructure &newStructure = *(pFile->fileStructures().last());

  CreateTopologyCommonForBrepCylinder(newStructure, extents);

  // Add line style to globals
  addLineStyleForBrep(newStructure, 1.0f, 0.0f, 0.0f);

  // Add graphic
  addGraphicDataToBrep(newStructure);

  // fill it with Brep Data
  OdPrcTopoContextPtr newTopoContext = newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
  OdPrcBrepDataPtr brepData = newTopoContext->bodies().last().safeOpenObject(kForWrite);
  FillTopoBrepFace(brepData,createCylinderforView());

  OdPrcProductOccurrencePtr pRootPO = newStructure.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcProductOccurrencePtr pPO = createProductOccurrence(newStructure, *pRootPO);
  OdPrcPartDefinitionPtr pPD = createPartDefinition(newStructure, *pPO);
  pPD->boundingBox().box() = extents;

  AddViewExample(newStructure, pPO);

  return pFile;
}

// main
void markupViewExample (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  ODA_ASSERT(mode == kMarkupViewExample);
  
  OdPrcFilePtr pFile = CreateViewExample();
  // export prc
  pFile->writeFile(pPrcStream);
}

