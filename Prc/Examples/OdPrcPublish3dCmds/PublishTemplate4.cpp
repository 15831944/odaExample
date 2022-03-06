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

OdResult PublishTemplate4(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGeExtents3d& extPrc, const OdString& sOutPdf)
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
  OdPagePtr pPage2 = OdPage::createObject();
  pPage1->setOrientation(Page::kLandscape);
  pPage2->setOrientation(Page::kLandscape);

  pDoc->addPage(pPage1);
  pDoc->addPage(pPage2);

  addPageHeader(pPage1, sOutPdf, 0);
  addPageHeader(pPage2, sOutPdf, 1);

  //Rect[158 33 436 808]
  OdCADModelPtr pModel = OdCADModel::createObject();
  pModel->setSource(pStreamPrc);

  OdAnnotationPtr pAnnot1 = OdAnnotation::createObject();
  pAnnot1->setSource(pModel);
  pAnnot1->setTransparentBackground(false);
  pAnnot1->setBorderWidth(2);
  pAnnot1->setName("3D Annotation 1");
  pAnnot1->setModelTreeVisibility(false);

  OdAnnotationPtr pAnnot2 = OdAnnotation::createObject();
  pAnnot2->setSource(pModel);
  pAnnot2->setTransparentBackground(false);
  pAnnot2->setBorderWidth(2);
  pAnnot2->setName("3D Annotation 2");
  pAnnot2->setModelTreeVisibility(false);

  OdAnnotationPtr pAnnot3 = OdAnnotation::createObject();
  pAnnot3->setSource(pModel);
  pAnnot3->setTransparentBackground(false);
  pAnnot3->setBorderWidth(2);
  pAnnot3->setName("3D Annotation 3");
  pAnnot3->setModelTreeVisibility(false);

  OdAnnotationPtr pAnnot4 = OdAnnotation::createObject();
  pAnnot4->setSource(pModel);
  pAnnot4->setTransparentBackground(false);
  pAnnot4->setBorderWidth(2);
  pAnnot4->setName("3D Annotation 4");
  pAnnot4->setModelTreeVisibility(false);

  OdAnnotationPtr pAnnot5 = OdAnnotation::createObject();
  pAnnot5->setSource(pModel);
  pAnnot5->setTransparentBackground(false);
  pAnnot5->setBorderWidth(2);
  pAnnot5->setName("3D Annotation 4");
  pAnnot5->setModelTreeVisibility(false);

  OdInt32 startX = 9, startY = 30, endX = 832, endY = 530;
  OdRect rect(startX, endX, startY, endY);
  pPage1->addAnnotation(pAnnot1, rect);

  double field_w = 100;
  double field_h = 100;

  OdArtworkPtr pArtwork1 = OdArtwork::createObject();
  OdGePoint3d defCamPos(-0.90612681748501411, -0.37532908821626582, 0.19509553088993711);
  OdGeVector3d defUpVec(0.18024483319542611, 0.074659669699104828, 0.98078424427943056);
  addView(pArtwork1, defCamPos, OdGePoint3d::kOrigin, defUpVec, L"Default", L"Default", Camera::kOrthographic, field_w, field_h, extPrc, Rendering::kDefault, Lighting::kDefault, true);
  pAnnot1->setArtwork(pArtwork1);

  OdArtworkPtr pArtwork2 = OdArtwork::createObject();
  addView(pArtwork2, OdGePoint3d(1, 0, 0), OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, L"Right", L"Right", Camera::kOrthographic, field_w, field_h, extPrc);
  pAnnot2->setArtwork(pArtwork2);

  OdArtworkPtr pArtwork3 = OdArtwork::createObject();
  addView(pArtwork3, OdGePoint3d(-1, 0, 0), OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, L"Left", L"Left", Camera::kOrthographic, field_w, field_h, extPrc);
  pAnnot3->setArtwork(pArtwork3);

  OdArtworkPtr pArtwork4 = OdArtwork::createObject();
  addView(pArtwork4, OdGePoint3d(0, -1, 0), OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, L"Front", L"Front", Camera::kOrthographic, field_w, field_h, extPrc);
  pAnnot4->setArtwork(pArtwork4);

  OdArtworkPtr pArtwork5 = OdArtwork::createObject();
  addView(pArtwork5, OdGePoint3d(0, 1, 0), OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, L"Back", L"Back", Camera::kOrthographic, field_w, field_h, extPrc);
  pAnnot5->setArtwork(pArtwork5);

  OdRect rect2(startX, (endX - startX)*0.75 - 1, startY, endY - (endY - startY) / 2 - 1);
  pPage2->addAnnotation(pAnnot2, rect2);

  OdRect rect3(startX, (endX - startX)*0.75 - 1, endY - (endY - startY) / 2 + 1, endY);
  pPage2->addAnnotation(pAnnot3, rect3);

  OdRect rect4((endX - startX)*0.75 + 1, endX, startY, endY - (endY - startY) / 2 - 1);
  pPage2->addAnnotation(pAnnot4, rect4);

  OdRect rect5((endX - startX)*0.75 + 1, endX, endY - (endY - startY) / 2 + 1, endY);
  pPage2->addAnnotation(pAnnot5, rect5);

  addPageFooter(pPage1, rect);
  addPageFooter(pPage2, rect);

  pPublisher->exportPdf(pDoc, sOutPdf);
  return ::eOk;
}

OdResult PublishTemplate4(OdDbBaseHostAppServices* pHostApp, const OdString& prc_file_name, const OdStringArray& arrPreviewFileNames, const OdGeExtents3d& extPrc, const OdString& sOutPdf)
{
  if (prc_file_name.isEmpty() || arrPreviewFileNames.size() != 7 || !extPrc.isValidExtents() || sOutPdf.isEmpty())
  {
    return eInvalidInput;
  }
  OdStreamBufPtr pStreamPrc = odrxSystemServices()->createFile(prc_file_name, Oda::kFileRead);

  return PublishTemplate4(pHostApp, pStreamPrc, extPrc, sOutPdf);
}
