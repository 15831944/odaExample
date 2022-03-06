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

const OdChar* SynchronizedViewJS =
L"host.getAnnots3D(0)[0].activated = true;                                                                                                    \n"
L"host.getAnnots3D(0)[1].activated = true;                                                                                                    \n"
L"function fillCam(cam, other)                                                                                                                \n"
L"{                                                                                                                                           \n"
L"  cam.projectionType = other.projectionType;                                                                                                \n"
L"  cam.up.set(other.up);                                                                                                                     \n"
L"  cam.position.set(other.position);                                                                                                         \n"
L"  cam.targetPosition.set(other.targetPosition);                                                                                             \n"
L"  cam.binding = other.binding;                                                                                                              \n"
L"  cam.far = other.far;                                                                                                                      \n"
L"  cam.fov = other.fov;                                                                                                                      \n"
L"  cam.near = other.near;                                                                                                                    \n"
L"  cam.positionLocal.set(other.positionLocal);                                                                                               \n"
L"  cam.transform.set(other.transform);                                                                                                       \n"
L"  cam.roll = other.roll;                                                                                                                    \n"
L"  cam.targetPositionLocal.set(other.targetPositionLocal);                                                                                   \n"
L"  cam.upLocal.set(other.upLocal);                                                                                                           \n"
L"  cam.viewPlaneSize = other.viewPlaneSize;                                                                                                  \n"
L"}                                                                                                                                           \n"
L"                                                                                                                                            \n"
L"function synchronizeAnnots()                                                                                                                \n"
L"{                                                                                                                                           \n"
L"  var cur_cam = scene.cameras.getByIndex(0);                                                                                                \n"
L"  if (host.getAnnots3D(0)[0].context3D.scene == scene)                                                                                      \n"
L"  {                                                                                                                                         \n"
L"    var other_cam = host.getAnnots3D(0)[1].context3D.scene.cameras.getByIndex(0);                                                           \n"
L"    fillCam(other_cam, cur_cam);                                                                                                            \n"
L"    host.getAnnots3D(0)[1].context3D.scene.update();                                                                                        \n"
L"  }                                                                                                                                         \n"
L"  else                                                                                                                                      \n"
L"  {                                                                                                                                         \n"
L"    var other_cam = host.getAnnots3D(0)[0].context3D.scene.cameras.getByIndex(0);                                                           \n"
L"    fillCam(other_cam, cur_cam);                                                                                                            \n"
L"    host.getAnnots3D(0)[0].context3D.scene.update();                                                                                        \n"
L"  }                                                                                                                                         \n"
L"}                                                                                                                                           \n"
L"                                                                                                                                            \n"
L"var OdScrollWheelEventHandler;                                                                                                              \n"
L"if (!OdScrollWheelEventHandler)                                                                                                             \n"
L"{                                                                                                                                           \n"
L"  OdScrollWheelEventHandler = new ScrollWheelEventHandler();                                                                                \n"
L"  OdScrollWheelEventHandler.onEvent = function(event)                                                                                       \n"
L"  {                                                                                                                                         \n"
L"    synchronizeAnnots();                                                                                                                    \n"
L"  }                                                                                                                                         \n"
L"                                                                                                                                            \n"
L"  runtime.addEventHandler(OdScrollWheelEventHandler);                                                                                       \n"
L"}                                                                                                                                           \n"
L"                                                                                                                                            \n"
L"var OdMouseEventHandler;                                                                                                                    \n"
L"var is_mouse_down = false;                                                                                                                  \n"
L"if (!OdMouseEventHandler)                                                                                                                   \n"
L"{                                                                                                                                           \n"
L"  OdMouseEventHandler = new MouseEventHandler();                                                                                            \n"
L"  OdMouseEventHandler.onMouseMove = true;                                                                                                   \n"
L"  OdMouseEventHandler.onMouseDown = true;                                                                                                   \n"
L"  OdMouseEventHandler.onMouseUp = true;                                                                                                     \n"
L"  OdMouseEventHandler.reportAllTargets = false;                                                                                             \n"
L"  OdMouseEventHandler.onMouseOver = false;                                                                                                  \n"
L"  OdMouseEventHandler.onMouseOut = false;                                                                                                   \n"
L"  OdMouseEventHandler.onMouseDoubleClick = false;                                                                                           \n"
L"  OdMouseEventHandler.onMouseHit = false;                                                                                                   \n"
L"  OdMouseEventHandler.onEvent = function(event)                                                                                             \n"
L"  {                                                                                                                                         \n"
L"    if (event.isMouseDown)                                                                                                                  \n"
L"      is_mouse_down = true;                                                                                                                 \n"
L"    if (event.isMouseUp)                                                                                                                    \n"
L"      is_mouse_down = false;                                                                                                                \n"
L"    if (is_mouse_down)                                                                                                                      \n"
L"    {                                                                                                                                       \n"
L"      synchronizeAnnots();                                                                                                                  \n"
L"    }                                                                                                                                       \n"
L"  }                                                                                                                                         \n"
L"                                                                                                                                            \n"
L"  runtime.addEventHandler(OdMouseEventHandler);                                                                                             \n"
L"}                                                                                                                                           \n";


OdResult PublishTemplate9(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGeExtents3d& extPrc,
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

  OdAnnotationPtr pAnnot1 = OdAnnotation::createObject();
  pAnnot1->setSource(pModel);

  pAnnot1->setTransparentBackground(false);
  pAnnot1->setBorderWidth(2);
  pAnnot1->setName("Test 3D Annotation 1");
  pAnnot1->setToolbarVisibility(false);

  OdRect rect1(9, 411, 30, 530);
  pPage1->addAnnotation(pAnnot1, rect1);

  double field_w = 100;
  double field_h = 100;

  OdArtworkPtr pArtwork1 = OdArtwork::createObject();

   //Default View
  OdGePoint3d defCamPos(-0.90612681748501411, -0.37532908821626582, 0.19509553088993711);
  OdGeVector3d defUpVec(0.18024483319542611, 0.074659669699104828, 0.98078424427943056);
  addView(pArtwork1, defCamPos, OdGePoint3d::kOrigin, defUpVec, L"Default", L"Default", Camera::kOrthographic, field_w, field_h, extPrc, Rendering::kSolid, Lighting::kDefault, true);

  pAnnot1->setArtwork(pArtwork1);

  OdAnnotationPtr pAnnot2 = OdAnnotation::createObject();
  pAnnot2->setSource(pModel);

  pAnnot2->setTransparentBackground(false);
  pAnnot2->setBorderWidth(2);
  pAnnot2->setName("Test 3D Annotation 2");
  pAnnot2->setToolbarVisibility(false);

  OdRect rect2(421, 832, 30, 530);
  pPage1->addAnnotation(pAnnot2, rect2);

  OdArtworkPtr pArtwork2 = OdArtwork::createObject();

  addView(pArtwork2, defCamPos, OdGePoint3d::kOrigin, defUpVec, L"Default", L"Default", Camera::kOrthographic, field_w, field_h, extPrc, Rendering::kWireframe, Lighting::kDefault, true);

  OdString JS2(SynchronizedViewJS);
  pArtwork2->setJavaScript(JS2);

  pAnnot2->setArtwork(pArtwork2);

  OdRect rect(9, 832, 30, 530);
  addPageFooter(pPage1, rect);

  pPublisher->exportPdf(pDoc, sOutPdf);
  return ::eOk;
}

OdResult PublishTemplate9(OdDbBaseHostAppServices* pHostApp, const OdString& prc_file_name, const OdGeExtents3d& extPrc,
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

  return PublishTemplate9(pHostApp, pStreamPrc, extPrc, sOutPdf);
}
