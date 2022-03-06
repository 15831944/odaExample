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

OdResult PublishTemplate3(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGiRasterImagePtrArray& arrPreviewImg, const OdGeExtents3d& extPrc,
                          const OdString& sOutPdf, const OdStringArray& nodeNames)
{
  if (pStreamPrc.isNull() || arrPreviewImg.size() != 7 || !extPrc.isValidExtents() || sOutPdf.isEmpty() || 0 == nodeNames.size())
  {
    return eInvalidInput;
  }

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

  OdCADModelPtr pModel = OdCADModel::createObject();
  pModel->setSource(pStreamPrc);
  OdAnnotationPtr pAnnot = OdAnnotation::createObject();
  pAnnot->setSource(pModel);

  pAnnot->setTransparentBackground(false);
  pAnnot->setBorderWidth(2);
  pAnnot->setName("Test 3D Annotation");

  pAnnot->setModelTreeVisibility(true);

  OdRect rect(9, 585, 30, 530);


  pPage1->addAnnotation(pAnnot, rect);

  OdStringArray headers;
  headers.push_back(L"NB");
  headers.push_back(L"Part Name");
  headers.push_back(L"QTY");

  OdDoubleArray columns;
  columns.push_back(0.2);
  columns.push_back(0.6);
  columns.push_back(0.2);

  pAnnot->setPartsList(nodeNames, OdRect(592, 832, 305, 530), headers, columns);

  OdTextPtr PMIText = OdText::createObject();
  PMIText->setSize(14);
  PMIText->setText(L"Property list:");
  pPage1->addText(PMIText, OdRect(592, 832, 280, 300));

  pAnnot->setPropertyList(OdRect(592, 832, 30, 275));

  double field_w = 100;
  double field_h = 100;

  OdArtworkPtr pArtwork = OdArtwork::createObject();

  //Front
  addView(pArtwork, OdGePoint3d(0, -1, 0), OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, L"Front", L"Front", Camera::kOrthographic, field_w, field_h, extPrc/*, Rendering::kIllustration, Lighting::kNight*/ );
  //Back
  addView(pArtwork, OdGePoint3d(0, 1, 0), OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, L"Back", L"Back", Camera::kOrthographic, field_w, field_h, extPrc);
  //Top
  addView(pArtwork, OdGePoint3d(0, 0, 1), OdGePoint3d::kOrigin, OdGeVector3d::kYAxis, L"Top", L"Top", Camera::kOrthographic, field_w, field_h, extPrc);
  //Bottom
  addView(pArtwork, OdGePoint3d(0, 0, -1), OdGePoint3d::kOrigin, -OdGeVector3d::kYAxis, L"Bottom", L"Bottom", Camera::kOrthographic, field_w, field_h, extPrc);
  //Right
  addView(pArtwork, OdGePoint3d(1, 0, 0), OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, L"Right", L"Right", Camera::kOrthographic, field_w, field_h, extPrc);
  //Left
  addView(pArtwork, OdGePoint3d(-1, 0, 0), OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, L"Left", L"Left", Camera::kOrthographic, field_w, field_h, extPrc);
  //Default View
  OdGePoint3d defCamPos(-0.90612681748501411, -0.37532908821626582, 0.19509553088993711);
  OdGeVector3d defUpVec(0.18024483319542611, 0.074659669699104828, 0.98078424427943056);
  addView(pArtwork, defCamPos, OdGePoint3d::kOrigin, defUpVec, L"Default", L"Default", Camera::kOrthographic, field_w, field_h, extPrc, Rendering::kDefault, Lighting::kDefault, true);

  pAnnot->setArtwork(pArtwork);

  OdStringArray buttonNames;
  buttonNames.push_back(L"Default");
  buttonNames.push_back(L"Front");
  buttonNames.push_back(L"Back");
  buttonNames.push_back(L"Top");
  buttonNames.push_back(L"Bottom");
  buttonNames.push_back(L"Right");
  buttonNames.push_back(L"Left");
  pAnnot->setCarouselButtons(buttonNames, OdString::kEmpty, OdString::kEmpty, 1);

  OdImagePtrArray images;
  OdUInt32Array indices;
  for(OdUInt32 i = 0; i < buttonNames.size(); ++i)
  {
    indices.push_back(i%7);
    OdImagePtr image = OdImage::createObject();
    image->setImage(arrPreviewImg[i]);
    images.push_back(image);
  }

  pAnnot->setCarouselViews(indices, images);

  addPageFooter(pPage1, rect);

  pPublisher->exportPdf(pDoc, sOutPdf);
  return ::eOk;
}

OdResult PublishTemplate3(OdDbBaseHostAppServices* pHostApp, const OdString& prc_file_name, const OdStringArray& arrPreviewFileNames, const OdGeExtents3d& extPrc,
                          const OdString& sOutPdf , const OdStringArray& nodeNames)
{
  if (prc_file_name.isEmpty() || arrPreviewFileNames.size() != 7 || !extPrc.isValidExtents() || sOutPdf.isEmpty() || 0 == nodeNames.size())
  {
    return eInvalidInput;
  }
  OdStreamBufPtr pStreamPrc = odrxSystemServices()->createFile(prc_file_name, Oda::kFileRead);
  OdGiRasterImagePtrArray arrPreviewImages;
  OdRxRasterServicesPtr pRasSvcs = ::odrxDynamicLinker()->loadApp(RX_RASTER_SERVICES_APPNAME);
  if(pRasSvcs.isNull())
    return eNullObjectPointer;
  for (OdUInt32 i = 0; i < arrPreviewFileNames.size(); i++)
  {
    OdGiRasterImagePtr pRasterImage = pRasSvcs->loadRasterImage(arrPreviewFileNames[i]);
    if(pRasterImage.isNull())
      return eNullObjectPointer;
    arrPreviewImages.push_back(pRasterImage);
  }

  return PublishTemplate3(pHostApp, pStreamPrc, arrPreviewImages, extPrc, sOutPdf, nodeNames);
}
