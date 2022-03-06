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

#include "OdaCommon.h"
#include "Ge/GeBoundBlock3d.h"
#include "OdTimeStamp.h"
#include "DynamicLinker.h"
#include "PdfPublish/PdfPublish.h"
#include "RxRasterServices.h"
#include "Gi/GiRasterImageArray.h"


using namespace OdPdfPublish;

OdString correctPath(const OdString& filePath);

void addView(OdArtworkPtr pArtwork, const OdGePoint3d& camPos, const OdGePoint3d& targPos, const OdGeVector3d& upVec,
             const OdString& extName, const OdString& intName,
             Camera::Projection proj, double f_w, double f_h,
             const OdGeExtents3d& extPrc,
             Rendering::Mode rMode = Rendering::kDefault, 
             Lighting::Mode lMode = Lighting::kDefault, bool bDefault = false, double camera_roll_angle = 0);

void addPageHeader(OdPagePtr& pPage, const OdString& sOutPdf, const OdUInt8 page_index);
void addPageFooter(OdPagePtr& pPage, const OdRect& rect);

void initTankLeg(Od2dGeometryBlockPtr& pGeom, const OdGeMatrix2d& mx)
{
//   OdGeMatrix2d rotMat;
//   rotMat.setCoordSystem(OdGePoint2d(132.5, 79.5), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis);
//   rotMat.setToRotation(-OdaPI / 6);

  pGeom->putColor(ODRGB(0, 0, 0));

  OdGePoint2dArray line;
  line.append(OdGePoint2d(28, 12).transformBy(mx));
  line.append(OdGePoint2d(46, 12).transformBy(mx));
  line.append(OdGePoint2d(46, -12).transformBy(mx));
  line.append(OdGePoint2d(28, -12).transformBy(mx));
  line.append(OdGePoint2d(28, 12).transformBy(mx));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(12, 11).transformBy(mx));
  line.append(OdGePoint2d(44, 11).transformBy(mx));
  line.append(OdGePoint2d(44, 7).transformBy(mx));
  line.append(OdGePoint2d(12, 7).transformBy(mx));
  line.append(OdGePoint2d(12, 11).transformBy(mx));
  pGeom->putColor(ODRGB(0, 255, 0));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(12, -7).transformBy(mx));
  line.append(OdGePoint2d(44, -7).transformBy(mx));
  line.append(OdGePoint2d(44, -11).transformBy(mx));
  line.append(OdGePoint2d(12, -11).transformBy(mx));
  line.append(OdGePoint2d(12, -7).transformBy(mx));
  pGeom->addLine(line);
  line.clear();

  line.append(OdGePoint2d(22, 11).transformBy(mx));
  line.append(OdGePoint2d(22, 7).transformBy(mx));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(28, 11).transformBy(mx));
  line.append(OdGePoint2d(28, 7).transformBy(mx));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(22, -11).transformBy(mx));
  line.append(OdGePoint2d(22, -7).transformBy(mx));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(28, -11).transformBy(mx));
  line.append(OdGePoint2d(28, -7).transformBy(mx));
  pGeom->addLine(line);
  line.clear();

  line.append(OdGePoint2d(19, -7).transformBy(mx));
  line.append(OdGePoint2d(19, 7).transformBy(mx));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(21, -7).transformBy(mx));
  line.append(OdGePoint2d(21, 7).transformBy(mx));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(33, 7).transformBy(mx));
  line.append(OdGePoint2d(33, -7).transformBy(mx));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(31, 7).transformBy(mx));
  line.append(OdGePoint2d(31, -7).transformBy(mx));
  pGeom->addLine(line);
  line.clear();
}

void init2dGeometry(Od2dGeometryBlockPtr& pGeom)
{
  pGeom->putLineWeight(1);
  ///test extents
  {
    OdGePoint2dArray testLine;
    testLine.append(OdGePoint2d(60, 54));
    testLine.append(OdGePoint2d(205, 54));
    testLine.append(OdGePoint2d(205, 150));
    testLine.append(OdGePoint2d(60, 150));
    testLine.append(OdGePoint2d(60, 54));
    //pGeom->addLine(testLine);
  }

  pGeom->putColor(ODRGB(0, 255, 0));

  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(100, 100), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 10, 10));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(100, 100), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 20, 20));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(100, 100), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 30, 30));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(100, 100), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 40, 40));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(195, 100), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 5, 5));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(195, 100), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 10, 10));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(80, 100), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 15, 15));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(105, 120), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 10, 10));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(105, 140), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 10, 10));
  pGeom->putColor(ODRGB(0, 255, 255));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(115, 65), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 5, 5));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(115, 75), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 5, 5));
  pGeom->putColor(ODRGB(0, 255, 0));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(115, 75), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 7, 7));
  pGeom->putColor(ODRGB(0, 255, 255));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(115, 75), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 10, 10));
  pGeom->putColor(ODRGB(0, 0, 255));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(93, 73), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 2, 2));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(93, 73), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 3, 3));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(93, 73), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 3.5, 3.5));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(93, 73), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 5, 5));
  pGeom->putColor(ODRGB(0, 255, 0));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(93, 73), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 7, 7));
  pGeom->putColor(ODRGB(0, 0, 255));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(93, 73), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 8, 8));
  pGeom->putColor(ODRGB(0, 255, 0));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(127, 93), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 5, 5));
  pGeom->putColor(ODRGB(0, 0, 255));
  pGeom->addEllipse(OdGeEllipArc2d(OdGePoint2d(127, 93), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis, 6, 6));

  pGeom->putColor(ODRGB(0, 255, 0));
  OdGePoint2dArray line;
  line.append(OdGePoint2d(60, 100));
  line.append(OdGePoint2d(185, 100));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(100, 60));
  line.append(OdGePoint2d(100, 140));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(185, 100));
  line.append(OdGePoint2d(205, 100));
  pGeom->putColor(ODRGB(0, 0, 0));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(195, 110));
  line.append(OdGePoint2d(195, 90));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(139.5, 107));
  line.append(OdGePoint2d(187.9, 107));
  pGeom->putColor(ODRGB(0, 255, 0));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(139.5, 93));
  line.append(OdGePoint2d(187.9, 93));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(95, 130));
  line.append(OdGePoint2d(115, 130));
  line.append(OdGePoint2d(115, 145));
  line.append(OdGePoint2d(95, 145));
  line.append(OdGePoint2d(95, 130));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(105, 130));
  line.append(OdGePoint2d(105, 145));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(112, 130));
  line.append(OdGePoint2d(112, 113));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(98, 130));
  line.append(OdGePoint2d(98, 113));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(114, 130));
  line.append(OdGePoint2d(114, 124));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(96, 130));
  line.append(OdGePoint2d(96, 124));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(110, 70));
  line.append(OdGePoint2d(120, 70));
  line.append(OdGePoint2d(120, 58));
  line.append(OdGePoint2d(110, 58));
  line.append(OdGePoint2d(110, 70));
  pGeom->putColor(ODRGB(0, 255, 255));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(111, 70));
  line.append(OdGePoint2d(111, 71.9));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(119, 70));
  line.append(OdGePoint2d(119, 71.9));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(113, 70));
  line.append(OdGePoint2d(113, 79.6));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(117, 70));
  line.append(OdGePoint2d(117, 79.6));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(115, 70));
  line.append(OdGePoint2d(115, 58));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(88, 67.5));
  line.append(OdGePoint2d(88, 78.5));
  line.append(OdGePoint2d(98, 78.5));
  line.append(OdGePoint2d(98, 67.5));
  line.append(OdGePoint2d(88, 67.5));
  pGeom->putColor(ODRGB(0, 0, 255));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(97, 67.7));
  line.append(OdGePoint2d(89, 67.7));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(93, 67.7));
  line.append(OdGePoint2d(93, 78.5));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(89.5, 67.7));
  line.append(OdGePoint2d(89.5, 78.5));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(96.5, 67.7));
  line.append(OdGePoint2d(96.5, 78.5));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(88, 73));
  line.append(OdGePoint2d(91, 73));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(95, 73));
  line.append(OdGePoint2d(98, 73));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(127, 101));
  line.append(OdGePoint2d(127, 85));
  pGeom->putColor(ODRGB(0, 0, 0));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(119, 93));
  line.append(OdGePoint2d(135, 93));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(125, 96));
  line.append(OdGePoint2d(129, 96));
  line.append(OdGePoint2d(129, 90));
  line.append(OdGePoint2d(125, 90));
  line.append(OdGePoint2d(125, 96));
  pGeom->putColor(ODRGB(0, 0, 255));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(126, 96));
  line.append(OdGePoint2d(126, 91));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(128, 96));
  line.append(OdGePoint2d(128, 91));
  pGeom->addLine(line);
  line.clear();
  line.append(OdGePoint2d(125.5, 91));
  line.append(OdGePoint2d(128.5, 91));
  pGeom->addLine(line);
  line.clear();

  OdGeMatrix2d mx;
  mx.setCoordSystem(OdGePoint2d(100, 100), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis);
  initTankLeg(pGeom, mx);
  mx.setToRotation(-2. * OdaPI / 3.);
  mx.setTranslation(OdGeVector2d(100, 100));
  initTankLeg(pGeom, mx);
  mx.setToRotation(2. * OdaPI / 3.);
  mx.setTranslation(OdGeVector2d(100, 100));
  initTankLeg(pGeom, mx);
}

OdResult PublishTemplate5(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGeExtents3d& extPrc, const OdString& sOutPdf)
{
  if (pStreamPrc.isNull() || !extPrc.isValidExtents() || sOutPdf.isEmpty())
    return eInvalidInput;

  OdFilePtr pPublisher = OdFile::createObject();
  if (pPublisher.isNull())
    return eNullObjectPointer;

  OdDocumentPtr pDoc = OdDocument::createObject();
  OdString creatorStr = OdString(TD_PRODUCT_NAME_START_W) + L" Publish";
  pDoc->setInformation(creatorStr + L" Template Document", creatorStr, L" Template Document", creatorStr);
  pDoc->setHostServices(pHostApp);

  OdPagePtr pPage1 = OdPage::createObject();
  pPage1->setOrientation(Page::kLandscape);
  pDoc->addPage(pPage1);

  addPageHeader(pPage1, sOutPdf, 0);

  //Rect[158 33 436 808]
  OdCADModelPtr pModel = OdCADModel::createObject();
  pModel->setSource(pStreamPrc);

  OdAnnotationPtr pAnnot = OdAnnotation::createObject();
  pAnnot->setSource(pModel);
  pAnnot->setTransparentBackground(true);
  pAnnot->setBorderWidth(2);
  pAnnot->setName("3D Annotation 1");
  pAnnot->setModelTreeVisibility(false);
  //pAnnot->setBackgroundColor(ODRGB(0, 25, 255));

  OdInt32 startX = 9, startY = 30, endX = 832, endY = 530;
  OdRect rect(startX, endX, startY, endY);

  double field_w = 100;
  double field_h = 100;

  OdArtworkPtr pArtwork = OdArtwork::createObject();
  //OdGePoint3d defCamPos(-0.90612681748501411, -0.37532908821626582, 0.19509553088993711);
  //OdGeVector3d defUpVec(0.18024483319542611, 0.074659669699104828, 0.98078424427943056);
  //addView(pArtwork, defCamPos, OdGePoint3d::kOrigin, defUpVec, L"Default", L"Default", Camera::kOrthographic, field_w, field_h, extPrc, Rendering::kDefault, Lighting::kDefault, true);
  addView(pArtwork, OdGePoint3d(0, 0, 1), OdGePoint3d::kOrigin, OdGeVector3d::kYAxis, L"Top", L"Top", Camera::kOrthographic, field_w, field_h, extPrc, Rendering::kDefault, Lighting::kDefault, false, OdaPI / 6);
  pAnnot->setArtwork(pArtwork);

  OdRect rectAnnot((endX - startX)*0.6, endX, endY - (endY - startY) / 2 + 20, endY);
  pPage1->addAnnotation(pAnnot, rectAnnot);

  //////////////////////////////////////////////////////////////////////////
  Od2dGeometryBlockPtr pGeom = Od2dGeometryBlock::createObject();
  init2dGeometry(pGeom);
  pGeom->setOrigin(OdGePoint2d(60, 54));

  Od2dGeometryReferencePtr pGeomRef1 = Od2dGeometryReference::createObject();
  pGeomRef1->setGeometryBlock(pGeom);

  OdGeMatrix2d mat, tmpMatr;
  mat *= tmpMatr.setToScaling(4.3);
  mat *= tmpMatr.setToRotation(-OdaPI / 6);
  OdGePoint2d startP(startX + 10, startY + 165);
  mat.setTranslation(startP.asVector());
  pGeomRef1->setTransform(mat);
  
  //Check auto scale
  //pGeomRef1->setScale(0);
  //pGeomRef1->setRotation(-OdaPI / 6);

  OdRect rect1(startX+60, endX, startY, endY - 50);
  pPage1->add2dGeometry(pGeomRef1/*, rect1*/);

  OdTextPtr topViewText = OdText::createObject();
  topViewText->setSize(18);
  topViewText->setFont(Text::kTimesBold);
  topViewText->setText(L"Top View in 2D:");
  OdRect topViewTextRect(startX + 5, startX + 100, endY - 50, endY);
  pPage1->addText(topViewText, topViewTextRect);
  //////////////////////////////////////////////////////////////////////////

  addPageFooter(pPage1, rect);

  pPublisher->exportPdf(pDoc, sOutPdf);
  return ::eOk;
}

OdResult PublishTemplate5(OdDbBaseHostAppServices* pHostApp, const OdString& prc_file_name, const OdStringArray& arrPreviewFileNames, const OdGeExtents3d& extPrc, const OdString& sOutPdf)
{
  if (prc_file_name.isEmpty() || arrPreviewFileNames.size() != 7 || !extPrc.isValidExtents() || sOutPdf.isEmpty())
  {
    return eInvalidInput;
  }
  OdStreamBufPtr pStreamPrc = odrxSystemServices()->createFile(prc_file_name, Oda::kFileRead);

  return PublishTemplate5(pHostApp, pStreamPrc, extPrc, sOutPdf);
}
