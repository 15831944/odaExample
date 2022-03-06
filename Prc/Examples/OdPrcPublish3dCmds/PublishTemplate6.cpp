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

OdResult PublishTemplate6(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGeExtents3d& extPrc,
                          const OdString& sOutPdf)
{
  if (pStreamPrc.isNull() || !extPrc.isValidExtents() || sOutPdf.isEmpty())
  {
    return eInvalidInput;
  }

  OdFilePtr pPublisher = OdFile::createObject();
  if (pPublisher.isNull())
    return eNullObjectPointer;

  OdDocumentPtr pDoc = OdDocument::createObject();
  OdString creatorStr = OdString(TD_PRODUCT_NAME_START_W) + L" Publish";
  pDoc->setInformation(creatorStr + L" Template Document", creatorStr, L" Template Document", creatorStr);

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

  OdRect rect(9, 832, 30, 530);


  pPage1->addAnnotation(pAnnot, rect);

  double field_w = 100;
  double field_h = 100;

  OdArtworkPtr pArtwork = OdArtwork::createObject();

   //Default View
  OdGePoint3d defCamPos(-0.90612681748501411, -0.37532908821626582, 0.19509553088993711);
  OdGeVector3d defUpVec(0.18024483319542611, 0.074659669699104828, 0.98078424427943056);
  addView(pArtwork, defCamPos, OdGePoint3d::kOrigin, defUpVec, L"Default", L"Default", Camera::kOrthographic, field_w, field_h, extPrc, Rendering::kSolid, Lighting::kDefault, true);

  OdString animationStr;
  animationStr += L"var Timer=0;                                                                               \n";
  animationStr += L"var time=0;                                                                                \n";
  animationStr += L"function RoatateZAnimation (event)                                                         \n";
  animationStr += L"{                                                                                          \n";
  animationStr += L"  time += event.deltaTime;                                                                 \n";
  animationStr += L"  if (time>=0.02)                                                                          \n";
  animationStr += L"  {                                                                                        \n";
  animationStr += L"    time = 0;                                                                              \n";
  animationStr += L"    var camera = scene.cameras.getByIndex(0);                                              \n";
  animationStr += L"    var camdir = camera.transform.rotateAboutVectorInPlace(0.0123599, new Vector3(0,0,1)); \n";
  animationStr += L"  }                                                                                        \n";
  animationStr += L"}                                                                                          \n";
  animationStr += L"                                                                                           \n";
  animationStr += L"function PlayAnimation()                                                                   \n";
  animationStr += L"{                                                                                          \n";
  animationStr += L"  if (Timer == 0)                                                                          \n";
  animationStr += L"  {                                                                                        \n";
  animationStr += L"    runtime.setView('Default');                                                            \n";
  animationStr += L"    Timer=new TimeEventHandler();                                                          \n";
  animationStr += L"    Timer.onEvent=RoatateZAnimation;                                                       \n";
  animationStr += L"    runtime.addEventHandler(Timer);                                                        \n";
  animationStr += L"  }                                                                                        \n";
  animationStr += L"  runtime.play();                                                                          \n";
  animationStr += L"}                                                                                          \n";
  animationStr += L"PlayAnimation()                                                                            \n";
  pArtwork->setJavaScript(animationStr);

  pAnnot->setArtwork(pArtwork);

  addPageFooter(pPage1, rect);

  pPublisher->exportPdf(pDoc, sOutPdf);
  return ::eOk;
}

OdResult PublishTemplate6(OdDbBaseHostAppServices* pHostApp, const OdString& prc_file_name, const OdGeExtents3d& extPrc,
                          const OdString& sOutPdf)
{
  if (prc_file_name.isEmpty() || !extPrc.isValidExtents() || sOutPdf.isEmpty() )
  {
    return eInvalidInput;
  }
  OdStreamBufPtr pStreamPrc = odrxSystemServices()->createFile(prc_file_name, Oda::kFileRead);
  OdGiRasterImagePtrArray arrPreviewImages;
  OdRxRasterServicesPtr pRasSvcs = ::odrxDynamicLinker()->loadApp(RX_RASTER_SERVICES_APPNAME);
  if(pRasSvcs.isNull())
    return eNullObjectPointer;

  return PublishTemplate6(pHostApp, pStreamPrc, extPrc, sOutPdf);
}
