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
#include "PrcAnnotationItem.h"
#include "Ge/GeCircArc3d.h"
#include "OdPrcCreateStart.h"
#include "PrcMarkupTessBuf.h"
#include "PrcCreateTopologyHelper.h"

// tessellation for markup with type =  1, sub_type = 0
OdPrcMarkupTessPtr CreatePlainTextMarkup (OdPrcFileStructure &pCurFS)
{
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
  OdGePoint3d origP(3, 3, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"Markup with Text type", 20, 4) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray polyLine;
  polyLine.resize(6);
  polyLine[0].set(0, 0, 0);
  polyLine[1].set(1, 1, 0);
  polyLine[2].set(25, 1, 0);
  polyLine[3].set(25, 7, 0);
  polyLine[4].set(1, 7, 0);
  polyLine[5].set(1, 1, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(polyLine) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

// tessellation for markup with type =  2, sub_type = 1
OdPrcMarkupTessPtr CreateDistanceDimensionMarkup (OdPrcFileStructure &pCurFS)
{
  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  OdPrcFontKeysSameFont font;
  font.setFontName(L"Verdana");
  font.setCharSet(0);
  font.fontKeys().resize(1);
  font.fontKeys()[0].font_size = 5;
  font.fontKeys()[0].attributes = 1 | 2 | 16; // bold, strike-out
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  OdGePoint3d origP(2, 2.1, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"9.000", 5, 2) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(3);
  pntsArr[0].set(0, 2, 0);
  pntsArr[1].set(0.2, 2.1, 0);
  pntsArr[2].set(0.2, 1.9, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  pntsArr[0].set(9, 2, 0);
  pntsArr[1].set(8.8, 2.1, 0);
  pntsArr[2].set(8.8, 1.9, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr.resize(2);
  pntsArr[0].set(0, 2, 0);
  pntsArr[1].set(2, 2, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr[0].set(7, 2, 0);
  pntsArr[1].set(9, 2, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

// tessellation for markup with type =  2, sub_type = 7
OdPrcMarkupTessPtr CreateDimensionRadiusMarkup (OdPrcFileStructure &pCurFS)
{
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
  OdGePoint3d origP(2.5, 0.5, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"R", 1, 2) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  font.fontKeys()[0].font_size = 4;
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(4, 1.5, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText1 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText1->setText(L".1350", 5, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText1);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(4, 0, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText2 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText2->setText(L".1150", 5, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText2);
  // end matrix

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

// tessellation for markup with type =  2, sub_type = 11
OdPrcMarkupTessPtr CreateDiameterDimensionMarkup (OdPrcFileStructure &pCurFS)
{
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
  OdGePoint3d origP(3, 0.3, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"\u2300", 1, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  font.fontKeys()[0].font_size = 4;
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(4.3, 0.5, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText1 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText1->setText(L"3.127", 3, 2) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText1);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(3);
  pntsArr[0].set(0, 0, 0);
  pntsArr[1].set(0.2, 0.1, 0);
  pntsArr[2].set(0.2, -0.1, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  pntsArr[0].set(2, 0, 0);
  pntsArr[1].set(1.8, 0.1, 0);
  pntsArr[2].set(1.8, -0.1, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr.resize(2);
  pntsArr[0].set(0, 0, 0);
  pntsArr[1].set(10, 0, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

// tessellation for markup with type =  2, sub_type = 12
OdPrcMarkupTessPtr CreateTangentDiameterDimensionMarkup (OdPrcFileStructure &pCurFS)
{
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
  OdGePoint3d origP(3, 0.3, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"\u2300", 1, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  font.fontKeys()[0].font_size = 4;
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(4.3, 0.5, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText1 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText1->setText(L"2.500", 3, 2) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText1);
  // end matrix

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(7.3, 0.5, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText2 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText2->setText(L"+/-.001 2PL", 6, 2) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText2);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(3);
  pntsArr[0].set(0.4, 0, 0);
  pntsArr[1].set(0.2, 0.1, 0);
  pntsArr[2].set(0.2, -0.1, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  pntsArr[0].set(2.4, 0, 0);
  pntsArr[1].set(2.6, 0.1, 0);
  pntsArr[2].set(2.6, -0.1, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr.resize(2);
  pntsArr[0].set(0, 0, 0);
  pntsArr[1].set(14, 0, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

// tessellation for markup with type =  2, sub_type = 13
OdPrcMarkupTessPtr createCylinderDiameterDimensionMarkup (OdPrcFileStructure &pCurFS)
{
  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

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
  OdGePoint3d origP(1, 3.2, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"\u2300", 1, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  font.fontKeys()[0].font_size = 5;
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(2, 4, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText1 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText1->setText(L"49.07", 4, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText1);
  // end matrix

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(2, 3, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText2 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText2->setText(L"49.02", 4, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText2);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(3);
  pntsArr[0].set(0, 2.7, 0);
  pntsArr[1].set(0.2, 2.8, 0);
  pntsArr[2].set(0.2, 2.6, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  pntsArr[0].set(7, 2.7, 0);
  pntsArr[1].set(6.8, 2.8, 0);
  pntsArr[2].set(6.8, 2.6, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr.resize(2);
  pntsArr[0].set(0, 2.7, 0);
  pntsArr[1].set(7, 2.7, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

// tessellation for markup with type =  2, sub_type = 16
OdPrcMarkupTessPtr CreateLengthDimensionMarkup (OdPrcFileStructure &pCurFS)
{
  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

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
  OdGePoint3d origP(3, 3, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"\u2300", 1, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  font.fontKeys()[0].font_size = 5;
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(4, 3.2, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText1 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText1->setText(L"9.575", 4, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText1);
  // end matrix

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(8, 3.2, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText2 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText2->setText(L"\u00b1", 0.5, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText2);
  // end matrix

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(8.5, 3.2, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText3 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText3->setText(L"0.075", 4, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText3);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(3);
  pntsArr[0].set(0, 2.7, 0);
  pntsArr[1].set(0.2, 2.8, 0);
  pntsArr[2].set(0.2, 2.6, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  pntsArr[0].set(2, 2.7, 0);
  pntsArr[1].set(1.8, 2.8, 0);
  pntsArr[2].set(1.8, 2.6, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr.resize(2);
  pntsArr[0].set(0, 0, 0);
  pntsArr[1].set(0, 3, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr[0].set(2, 0, 0);
  pntsArr[1].set(2, 3, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr[0].set(0, 2.7, 0);
  pntsArr[1].set(12, 2.7, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

// tessellation for markup with type =  2, sub_type = 19
OdPrcMarkupTessPtr CreateAngleDimensionMarkup (OdPrcFileStructure &pCurFS)
{
  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  OdPrcFontKeysSameFont font;
  font.setFontName(L"Arial");
  font.setCharSet(0);
  font.fontKeys().resize(1);
  font.fontKeys()[0].font_size = 4;
  font.fontKeys()[0].attributes = 1;
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdGePoint3dArray circlePntsArr;
  circlePntsArr.resize(20);
  OdGePoint3d point(0,0,0);
  OdGeCircArc3d circle = OdGeCircArc3d();
  circle.setCenter(point);
  circle.setRadius(5);
  circle.setAngles(OdaPI+OdaPI4,OdaPI+1.5*OdaPI4);
  circle.getSamplePoints( 20, circlePntsArr );
  
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(circlePntsArr.size());
  for (OdUInt32 i = 0; i < circlePntsArr.size(); ++i)
  {
    pntsArr[i].set(circlePntsArr[i].x, circlePntsArr[i].y, circlePntsArr[i].z);
  }
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  circle.setAngles(Oda2PI-1.5*OdaPI4,Oda2PI-OdaPI4);
  circle.getSamplePoints( 20, circlePntsArr );
  for (OdUInt32 i = 0; i < circlePntsArr.size(); ++i)
  {
    pntsArr[i].set(circlePntsArr[i].x, circlePntsArr[i].y, circlePntsArr[i].z);
  }
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  pntsArr.resize(3);
  pntsArr[0].set(-3.54, -3.54, 0);
  pntsArr[1].set(-3.34, -3.54, 0);
  pntsArr[2].set(-3.54, -3.74, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  pntsArr[0].set(3.54, -3.54, 0);
  pntsArr[1].set(3.34, -3.54, 0);
  pntsArr[2].set(3.54, -3.74, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(pntsArr) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  OdGePoint3d origP(-1.5, -4.5, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"89\u00b0", 3, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(-1.5, -5.5, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText1 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText1->setText(L"91\u00b0", 3, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText1);
  // end matrix

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

// tessellation for markup with type =  7, sub_type = 1
OdPrcMarkupTessPtr CreateDatumIdentifierMarkup (OdPrcFileStructure &pCurFS)
{
  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(5);
  pntsArr[0].set(1, 1, 0);
  pntsArr[1].set(5, 1, 0);
  pntsArr[2].set(5, 4, 0);
  pntsArr[3].set(1, 4, 0);
  pntsArr[4].set(1, 1, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  OdPrcFontKeysSameFont font;
  font.setFontName(L"Arial");
  font.setCharSet(0);
  font.fontKeys().resize(1);
  font.fontKeys()[0].font_size = 5;
  font.fontKeys()[0].attributes = 1;
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  OdGePoint3d origP(2, 2, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"A", 2, 3) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

// tessellation for markup with type =  7, sub_type = 2
OdPrcMarkupTessPtr CreateDatumTargetMarkup (OdPrcFileStructure &pCurFS)
{
  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdGePoint3d point(2,3,0);
  OdGeCircArc3d circle = OdGeCircArc3d();
  circle.setCenter(point);
  circle.setRadius(2);
  OdGePoint3dArray circlePntsArr;
  circlePntsArr.resize(100);
  circle.getSamplePoints(100, circlePntsArr);
  circlePntsArr.push_back(circlePntsArr.first());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(circlePntsArr.size());
  for (OdUInt32 i = 0; i < circlePntsArr.size(); ++i)
  {
    pntsArr[i].set(circlePntsArr[i].x, circlePntsArr[i].y, circlePntsArr[i].z);
  }
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr.resize(2);
  pntsArr[0].set(0, 3, 0);
  pntsArr[1].set(4, 3, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  OdPrcFontKeysSameFont font;
  font.setFontName(L"Arial");
  font.setCharSet(0);
  font.fontKeys().resize(1);
  font.fontKeys()[0].font_size = 5;
  font.fontKeys()[0].attributes = 1;
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  OdGePoint3d origP(1.5, 1.5, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"B", 1, 3) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

// tessellation for markup with type =  9, sub_type = 1
OdPrcMarkupTessPtr CreateGDTMarkup (OdPrcFileStructure &pCurFS)
{
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
  OdGePoint3d origP(1, 2, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"\u2225", 10, 4) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(13, 2, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText1 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText1->setText(L".010", 10, 4) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText1);
  // end matrix

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  origP.set(25, 2, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText2 = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText2->setText(L"A", 5, 4) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText2);
  // end matrix

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(5);
  pntsArr[0].set(0, 1, 0);
  pntsArr[1].set(31, 1, 0);
  pntsArr[2].set(31, 7, 0);
  pntsArr[3].set(0, 7, 0);
  pntsArr[4].set(0, 1, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr.resize(2);
  pntsArr[0].set(12, 1, 0);
  pntsArr[1].set(12, 7, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr.resize(2);
  pntsArr[0].set(24, 1, 0);
  pntsArr[1].set(24, 7, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

// tessellation for markup with type =  12, sub_type = 0
OdPrcMarkupTessPtr CreateRoughnessMarkup (OdPrcFileStructure &pCurFS)
{
  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufFont::createObject());
  OdPrcFontKeysSameFont font;
  font.setFontName(L"Arial");
  font.setCharSet(0);
  font.fontKeys().resize(1);
  font.fontKeys()[0].font_size = 4;
  font.fontKeys()[0].attributes = 1;
  ODA_VERIFY(((OdPrcMarkupTessBufFontPtr &) pCurMkpTess)->setFont(font) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray pntsArr;
  pntsArr.resize(3);
  pntsArr[0].set(4.5, 1, 0);
  pntsArr[1].set(5, 1, 0);
  pntsArr[2].set(5, 0.5, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr[0].set(4, 0, 0);
  pntsArr[1].set(6, 2, 0);
  pntsArr[2].set(10, 2, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  pntsArr.resize(5);
  pntsArr[0].set(9, 4, 0);
  pntsArr[1].set(7, 4, 0);
  pntsArr[2].set(8, 3, 0);
  pntsArr[3].set(10, 5, 0);
  pntsArr[4].set(11, 5, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(pntsArr) == eOk);

  // matrix
  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufMatrix::createObject());
  OdGePoint3d origP(6.8, 4.3, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"250", 1, 1) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

// tessellation for markup with type =  15, sub_type = 0
OdPrcMarkupTessPtr CreateTableMarkup (OdPrcFileStructure &pCurFS)
{
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
  OdGePoint3d origP(1, 1, 0);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setMatrix(OdGeMatrix3d::translation(origP.asVector()));
  OdPrcMarkupTessBufTextPtr pBufText = OdPrcMarkupTessBufText::createObject();
  ODA_VERIFY(pBufText->setText(L"Markup with table type", 20, 5) == eOk);
  ((OdPrcMarkupTessBufMatrixPtr &) pCurMkpTess)->setNextInBlock(pBufText);
  // end matrix

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  return mTess;
}

OdPrcMarkupLeaderPtrArray CreateNoLeader()
{
  //Create Leader
  OdPrcMarkupLeaderPtrArray leaders;
  return leaders;
}

OdPrcMarkupLeaderPtrArray CreateDistanceDimensionLeader(OdPrcFileStructure &pCurFS)
{
  //Create Leader
  OdPrcMarkupLeaderPtrArray leaders;
  OdPrcMarkupLeaderPtr leader = OdPrcMarkupLeader::createObject();

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray arrPnts;
  arrPnts.resize(2);
  arrPnts[0].set(0, 0, 0);
  arrPnts[1].set(0, 2.2, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader);

  leader = OdPrcMarkupLeader::createObject();

  pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  pFirstMkpTess->setColor(greenCol);

  pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  arrPnts[0].set(9, 0, 0);
  arrPnts[1].set(9, 2.2, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader);
  return leaders;
}

OdPrcMarkupLeaderPtrArray CreateDimensionRadiusLeader(OdPrcFileStructure &pCurFS)
{
  //Create Leader
  OdPrcMarkupLeaderPtrArray leaders;
  OdPrcMarkupLeaderPtr leader = OdPrcMarkupLeader::createObject();

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufTriangles::createObject());
  OdPrcFloatPointArray arrPnts;
  arrPnts.resize(3);
  arrPnts[0].set(0, 1, 0);
  arrPnts[1].set(0.2, 1.1, 0);
  arrPnts[2].set(0.2, 0.9, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufTrianglesPtr &) pCurMkpTess)->setTriangles(arrPnts) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  arrPnts.resize(2);
  arrPnts[0].set(0.2, 1, 0);
  arrPnts[1].set(2, 1, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader);
  return leaders;
}

OdPrcMarkupLeaderPtrArray CreateTangentDiameterDimensionLeader(OdPrcFileStructure &pCurFS)
{
  //Create Leader
  OdPrcMarkupLeaderPtrArray leaders;
  OdPrcMarkupLeaderPtr leader = OdPrcMarkupLeader::createObject();

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray arrPnts;
  arrPnts.resize(2);
  arrPnts[0].set(0.4, 3, 0);
  arrPnts[1].set(0.4, -0.3, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader);

  leader = OdPrcMarkupLeader::createObject();

  pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  pFirstMkpTess->setColor(greenCol);

  pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  arrPnts[0].set(2.4, 3, 0);
  arrPnts[1].set(2.4, -0.3, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader);
  return leaders;
}

OdPrcMarkupLeaderPtrArray createCylinderDiameterDimensionLeader(OdPrcFileStructure &pCurFS)
{
  //Create Leader
  OdPrcMarkupLeaderPtrArray leaders;
  OdPrcMarkupLeaderPtr leader = OdPrcMarkupLeader::createObject();

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray arrPnts;
  arrPnts.resize(2);
  arrPnts[0].set(0, 0, 0);
  arrPnts[1].set(0, 3, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader);

  leader = OdPrcMarkupLeader::createObject();

  pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  pFirstMkpTess->setColor(greenCol);

  pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  arrPnts[0].set(7, 0, 0);
  arrPnts[1].set(7, 3, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader);
  return leaders;
}

OdPrcMarkupLeaderPtrArray CreateAngleDimensionLeader(OdPrcFileStructure &pCurFS)
{
  //Create Leader
  OdPrcMarkupLeaderPtrArray leaders;
  OdPrcMarkupLeaderPtr leader = OdPrcMarkupLeader::createObject();

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray arrPnts;
  arrPnts.resize(2);
  arrPnts[0].set(-1.9, -1, 0);
  arrPnts[1].set(-3.7, -3.8, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader);

  leader = OdPrcMarkupLeader::createObject();

  pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  pFirstMkpTess->setColor(greenCol);

  pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  arrPnts[0].set(1.9, -1, 0);
  arrPnts[1].set(3.7, -3.8, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader);
  return leaders;
}

OdPrcMarkupLeaderPtrArray CreateDatumIdentifierLeader(OdPrcFileStructure &pCurFS)
{
  //Create Leader
  OdPrcMarkupLeaderPtrArray leaders;
  OdPrcMarkupLeaderPtr leader = OdPrcMarkupLeader::createObject();

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray arrPnts;
  arrPnts.resize(2);
  arrPnts[0].set(2, 0, 0);
  arrPnts[1].set(2, 1, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  arrPnts.resize(4);
  arrPnts[0].set(1.6, 0, 0);
  arrPnts[1].set(2.4, 0, 0);
  arrPnts[2].set(2, 0.5, 0);
  arrPnts[3].set(1.6, 0, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader);
  return leaders;
}

OdPrcMarkupLeaderPtrArray CreateDatumTargetLeader(OdPrcFileStructure &pCurFS)
{
  //Create Leader
  OdPrcMarkupLeaderPtrArray leaders;
  OdPrcMarkupLeaderPtr leader = OdPrcMarkupLeader::createObject();

  OdPrcMarkupTessBufColorPtr pFirstMkpTess = OdPrcMarkupTessBufColor::createObject();
  OdPrcRgbColor greenCol;
  greenCol.set(0, 1, 0);
  pFirstMkpTess->setColor(greenCol);

  OdPrcMarkupTessBufPtr pCurMkpTess = pFirstMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  OdPrcFloatPointArray arrPnts;
  arrPnts.resize(2);
  arrPnts[0].set(2, 0, 0);
  arrPnts[1].set(2, 1, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  arrPnts[0].set(1.5, -0.5, 0);
  arrPnts[1].set(2.5, 0.5, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  pCurMkpTess = pCurMkpTess->setNext(OdPrcMarkupTessBufPolyline::createObject());
  arrPnts[0].set(1.5, 0.5, 0);
  arrPnts[1].set(2.5, -0.5, 0);
  ODA_VERIFY(((OdPrcMarkupTessBufPolylinePtr &) pCurMkpTess)->setPoints(arrPnts) == eOk);

  OdPrcMarkupTessPtr mTess = OdPrcMarkupTess::createObject();
  ODA_VERIFY(mTess->setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == eOk);
  mTess->setLabel(L"test");

  leader->tessellation() = mTess;
  leaders.push_back(leader);
  return leaders;
}

void FillTopoMarkups (OdPrcFileStructure &newStructure,OdPrcProductOccurrencePtr &newProductOccurrence, OdPrcMarkupTessPtr mTess, OdPrcMarkup::MarkupType type, OdPrcMarkup::MarkupSubType subtype, OdPrcMarkupLeaderPtrArray arr_leader, OdPrcName name)
{
  OdPrcObjectId un_id;

  //Create Leader
  OdPrcObjectIdArray &leaders = newProductOccurrence->markups().leaders();
  leaders.resize(arr_leader.size());
  for(OdUInt32 f=0;f<arr_leader.size();++f)
  {
    newStructure.addObject(arr_leader[f]);
    leaders[f] = arr_leader[f]->objectId();
  }
  if (leaders.size() > 0)
  {   
    newStructure.fileStructureTessellation().tessellations().push_back(arr_leader[0]->tessellation());
    if (leaders.size() == 2)
    {
      newStructure.fileStructureTessellation().tessellations().push_back(arr_leader[1]->tessellation());
    }
  }
  OdPrcObjectIdArray &arr = newProductOccurrence->markups().markups();
  OdPrcMarkupPtr markup = OdPrcMarkup::createObject();
  newStructure.addObject(markup);
  markup->name() = name;
  ODA_VERIFY(markup->setType(type, subtype) == eOk);
  markup->tessellation() = mTess;
  if (leaders.size() > 0)
  {
    un_id = leaders[0];
    markup->leader().push_back(un_id);
    if (leaders.size() == 2)
    {
      un_id = leaders[1];
      markup->leader().push_back(un_id);
    }
  }
  arr.push_back(markup->objectId());

  OdPrcObjectIdArray &arr_entity = newProductOccurrence->markups().annotationEntities();
  OdPrcAnnotationItemPtr ann_item = OdPrcAnnotationItem::createObject();

  ann_item->name() = name;
  un_id = markup->objectId();
  ann_item->markup() = un_id;
  newStructure.addObject(ann_item);
  arr_entity.push_back(ann_item->objectId());
  
  newStructure.fileStructureTessellation().tessellations().push_back(mTess);
}

// main
void markupExample(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  // common
  OdGeExtents3d extents;
  extents.addPoint(OdGePoint3d(0,0,0));
  extents.addPoint(OdGePoint3d(1,1,1));
  OdPrcFilePtr pFile = createTopologyCommon();
  OdPrcFileStructure &newStructure = *(pFile->fileStructures().last());

  OdPrcProductOccurrencePtr pRootPO = newStructure.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(kForWrite);
  OdPrcProductOccurrencePtr pPO = createProductOccurrence(newStructure, *pRootPO);
  OdPrcPartDefinitionPtr pPD = createPartDefinition(newStructure, *pPO);
  pPD->boundingBox().box() = extents;

  OdPrcName name;
  switch (mode)
  {
  case kPlainTextMarkup:
    name.setName(L"PlainTextMarkup");  
    FillTopoMarkups(newStructure,pPO,CreatePlainTextMarkup(newStructure),OdPrcMarkup::kText,OdPrcMarkup::kUnknownSubtype,CreateNoLeader(), name);
    break;
  case kDistanceDimensionMarkup:
    name.setName(L"DistanceDimensionMarkup");  
    FillTopoMarkups(newStructure,pPO,CreateDistanceDimensionMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Distance,CreateDistanceDimensionLeader(newStructure), name);
    break;
  case kDimensionRadiusMarkup:
    name.setName(L"DimensionRadiusMarkup");  
    FillTopoMarkups(newStructure,pPO,CreateDimensionRadiusMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Radius,CreateDimensionRadiusLeader(newStructure), name);
    break;
  case kDiameterDimensionMarkup:
    name.setName(L"DiameterDimensionMarkup");  
    FillTopoMarkups(newStructure,pPO,CreateDiameterDimensionMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Diameter,CreateNoLeader(), name);
    break;
  case kTangentDiameterDimensionMarkup:
    name.setName(L"TangentDiameterDimensionMarkup");  
    FillTopoMarkups(newStructure,pPO,CreateTangentDiameterDimensionMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Diameter_Tangent,CreateTangentDiameterDimensionLeader(newStructure), name);
    break;
  case kCylinderDiameterDimensionMarkup:
    name.setName(L"CylinderDiameterDimensionMarkup");  
    FillTopoMarkups(newStructure,pPO,createCylinderDiameterDimensionMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Diameter_Cylinder,createCylinderDiameterDimensionLeader(newStructure), name);
    break;
  case kLengthDimensionMarkup:
    name.setName(L"LengthDimensionMarkup");  
    FillTopoMarkups(newStructure,pPO,CreateLengthDimensionMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Length,CreateNoLeader(), name);
    break;
  case kAngleDimensionMarkup:
    name.setName(L"AngleDimensionMarkup");  
    FillTopoMarkups(newStructure,pPO,CreateAngleDimensionMarkup(newStructure),OdPrcMarkup::kDimension,OdPrcMarkup::kDimension_Angle,CreateAngleDimensionLeader(newStructure), name);
    break;
  case kDatumIdentifierMarkup:
    name.setName(L"DatumIdentifierMarkup");  
    FillTopoMarkups(newStructure,pPO,CreateDatumIdentifierMarkup(newStructure),OdPrcMarkup::kDatum,OdPrcMarkup::kDatum_Ident,CreateDatumIdentifierLeader(newStructure), name);
  break;
  case kDatumTargetMarkup:
    name.setName(L"DatumTargetMarkup");  
    FillTopoMarkups(newStructure,pPO,CreateDatumTargetMarkup(newStructure),OdPrcMarkup::kDatum,OdPrcMarkup::kDatum_Target,CreateDatumTargetLeader(newStructure), name);
    break;
  case kGDTMarkup:
    name.setName(L"GDTMarkup");  
    FillTopoMarkups(newStructure,pPO,CreateGDTMarkup(newStructure),OdPrcMarkup::kGdt,OdPrcMarkup::kGdt_Fcf,CreateNoLeader(), name);
    break;
  case kRoughnessMarkup:
    name.setName(L"RoughnessMarkup");  
    FillTopoMarkups(newStructure,pPO,CreateRoughnessMarkup(newStructure),OdPrcMarkup::kRoughness,OdPrcMarkup::kUnknownSubtype,CreateNoLeader(), name);
    break;
  case kTableMarkup:
    name.setName(L"TableMarkup");  
    FillTopoMarkups(newStructure,pPO,CreateTableMarkup(newStructure),OdPrcMarkup::kTable,OdPrcMarkup::kUnknownSubtype,CreateNoLeader(), name);
    break;
  default:
    ODA_ASSERT(false);
  }

  // export prc
  pFile->writeFile(pPrcStream);
}

