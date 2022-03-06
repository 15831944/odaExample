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

class CameraCallback : public OdBaseCameraMotion
{
  double     m_Angle;
  OdUInt64   m_StartBreak;
  OdUInt64   m_EndBreak;
  double     m_AngleOffset;
public:
  CameraCallback(const OdUInt64& start_break, const OdUInt64& end_break, double angle_offset)
    :m_Angle(0.0)
    ,m_StartBreak(start_break)
    ,m_EndBreak(end_break)
    ,m_AngleOffset(angle_offset)
  {
  }
  ~CameraCallback() {}
  bool getPosition(OdGePoint3d& position)
  {
    position.z = cos(m_Angle);
    position.y = sin(m_Angle);
    m_Angle += m_AngleOffset;
    position.x = 0;
    return true;
  }
  bool getTarget(OdGePoint3d& target)
  {
    target = OdGePoint3d::kOrigin;
    return true;
  }
  bool getUpVector(OdGeVector3d& vector)
  {
    vector = OdGeVector3d::kXAxis;
    return true;
  }

  bool step(const OdUInt64& frame)
  {
    return frame < m_StartBreak || frame > m_EndBreak;
  }
};


class NodeCallback : public OdBaseNodeMotion
{
protected:
  OdUInt64 m_Step;
  double   m_Angle;
  double   m_AngleOffset;
  bool     m_RotationState;
  double   m_OffsetFactor;
  OdString m_NodeName;
  OdUInt64 m_Start;
  OdUInt64 m_End;
  OdGeVector3d m_offset;
public:
  NodeCallback(const OdString& node_name, const OdUInt64& start, const OdUInt64& end, double offset_factor, bool state = false, double angle_offset = 0.0)
    :m_NodeName(node_name)
    , m_Angle(0.0)
    , m_Start(start)
    , m_End(end)
    , m_OffsetFactor(offset_factor)
    , m_RotationState(state)
    , m_AngleOffset(angle_offset)
  {
  }

  virtual ~NodeCallback() {}

  bool getName(OdString& name)
  {
    name = m_NodeName;
    return true;
  }
  bool getTransformation(OdGeMatrix3d& matrix)
  {
    OdGeMatrix3d int_matrix;
    if (m_Step < m_End - 1)
    {
      if (m_RotationState)
      {
        int_matrix = OdGeMatrix3d::rotation(m_Angle, OdGeVector3d(0., 0., -1.));
        m_Angle += m_AngleOffset;
      }
      m_offset.z += m_OffsetFactor;
      int_matrix = int_matrix.setTranslation(m_offset);
      if (m_Step == m_Start + (m_End - m_Start) / 2.0)
      {
        m_OffsetFactor = -m_OffsetFactor;
        m_AngleOffset = -m_AngleOffset;
      }
    }
    matrix = int_matrix;
    return true;
  }
  bool getColor(ODCOLORREF& color)
  {
    color = ODRGB(0, 255, 0);
    if (m_Step > m_End - 2)
      color = ODRGB(255, 0, 0);
    return true;
  }
  bool getOpacity(double& opacity)
  {
    opacity = 1.0;
    return true;
  }

  bool step(const OdUInt64& frame)
  {
    m_Step = frame;
    return true;
  }

};

OdResult PublishTemplate7(OdDbBaseHostAppServices* pHostApp, const OdStreamBufPtr& pStreamPrc, const OdGeExtents3d& extPrc,
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

  pAnnot->setModelTreeVisibility(true);

  OdRect rect(9, 832, 30, 530);


  pPage1->addAnnotation(pAnnot, rect);

  double field_w = 100;
  double field_h = 100;

  OdArtworkPtr pArtwork = OdArtwork::createObject();

  //Default View
  OdGePoint3d defCamPos(-0.90612681748501411, -0.37532908821626582, 0.19509553088993711);
  OdGeVector3d defUpVec(0.18024483319542611, 0.074659669699104828, 0.98078424427943056);
  addView(pArtwork, defCamPos, OdGePoint3d::kOrigin, defUpVec, L"Default", L"Default", Camera::kOrthographic, field_w, field_h, extPrc, Rendering::kDefault, Lighting::kDefault, true);

  pAnnot->setArtwork(pArtwork);

  OdAnimationPtr animation1 = OdAnimation::createObject();
  animation1->setAutoReplay(true);
  animation1->setName(L"Animation1");
  animation1->setPlayOnOpenDocument(true);
  animation1->setFramesPerSecond(100);
  animation1->setFramesCount(1888);

  OdBaseCameraMotionPtr cameraCallback = new CameraCallback(341, 1720, 0.0123599);

  animation1->setCameraMotion(0, 1888, cameraCallback);

  OdUInt64 nut_start_frame(340), nut_end_frame(1720);

  OdBaseNodeMotionPtr node1 = new NodeCallback(L"Nut.88a2489a289b405080", nut_start_frame, nut_end_frame, -0.1, true, 0.05);

  animation1->addNodeMotion(nut_start_frame, nut_end_frame, node1);

  OdBaseNodeMotionPtr node2 = new NodeCallback(L"Nut.88a2489a289b4050b0", nut_start_frame, nut_end_frame, -0.1, true, 0.05);

  animation1->addNodeMotion(nut_start_frame, nut_end_frame, node2);

  OdBaseNodeMotionPtr node3 = new NodeCallback(L"Nut.88a2489a289b4050e0", nut_start_frame, nut_end_frame, -0.1, true, 0.05);

  animation1->addNodeMotion(nut_start_frame, nut_end_frame, node3);

  OdBaseNodeMotionPtr node4 = new NodeCallback(L"Nut.88a2489a289b405110", nut_start_frame, nut_end_frame, -0.1, true, 0.05);

  animation1->addNodeMotion(nut_start_frame, nut_end_frame, node4);

  OdUInt64 washer_start_frame(380), washer_end_frame(1680);

  OdBaseNodeMotionPtr node5 = new NodeCallback(L"Washer.88a2489a289b405070", washer_start_frame, washer_end_frame, -0.1);

  animation1->addNodeMotion(washer_start_frame, washer_end_frame, node5);

  OdBaseNodeMotionPtr node6 = new NodeCallback(L"Washer.88a2489a289b4050a0", washer_start_frame, washer_end_frame, -0.1);

  animation1->addNodeMotion(washer_start_frame, washer_end_frame, node6);

  OdBaseNodeMotionPtr node7 = new NodeCallback(L"Washer.88a2489a289b4050d0", washer_start_frame, washer_end_frame, -0.1);

  animation1->addNodeMotion(washer_start_frame, washer_end_frame, node7);

  OdBaseNodeMotionPtr node8 = new NodeCallback(L"Washer.88a2489a289b405100", washer_start_frame, washer_end_frame, -0.1);

  animation1->addNodeMotion(washer_start_frame, washer_end_frame, node8);

  OdUInt64 bolt_start_frame(400), bolt_end_frame(1660);

  OdBaseNodeMotionPtr node9 = new NodeCallback(L"BrepModelBolt.84a1485a18f4206088a2489a289b405060", bolt_start_frame, bolt_end_frame, 0.1);

  animation1->addNodeMotion(bolt_start_frame, bolt_end_frame, node9);

  OdBaseNodeMotionPtr node10 = new NodeCallback(L"BrepModelBolt.84a1485a18f4206088a2489a289b405090", bolt_start_frame, bolt_end_frame, 0.1);

  animation1->addNodeMotion(bolt_start_frame, bolt_end_frame, node10);

  OdBaseNodeMotionPtr node11 = new NodeCallback(L"BrepModelBolt.84a1485a18f4206088a2489a289b4050c0", bolt_start_frame, bolt_end_frame, 0.1);

  animation1->addNodeMotion(bolt_start_frame, bolt_end_frame, node11);

  OdBaseNodeMotionPtr node12 = new NodeCallback(L"BrepModelBolt.84a1485a18f4206088a2489a289b4050f0", bolt_start_frame, bolt_end_frame, 0.1);

  animation1->addNodeMotion(bolt_start_frame, bolt_end_frame, node12);

  OdUInt64 rim_start_frame(550), rim_end_frame(1510);

  OdBaseNodeMotionPtr node13 = new NodeCallback(L"Rim.88a2489a289b405050", rim_start_frame, rim_end_frame, 0.1);

  animation1->addNodeMotion(rim_start_frame, rim_end_frame, node13);

  pArtwork->addAnimation(animation1);

  addPageFooter(pPage1, rect);

  pPublisher->exportPdf(pDoc, sOutPdf);
  return ::eOk;
}

OdResult PublishTemplate7(OdDbBaseHostAppServices* pHostApp, const OdString& prc_file_name, const OdGeExtents3d& extPrc,
                          const OdString& sOutPdf)
{
  if (prc_file_name.isEmpty() || !extPrc.isValidExtents() || sOutPdf.isEmpty())
  {
    return eInvalidInput;
  }
  OdStreamBufPtr pStreamPrc = odrxSystemServices()->createFile(prc_file_name, Oda::kFileRead);
  OdGiRasterImagePtrArray arrPreviewImages;
  OdRxRasterServicesPtr pRasSvcs = ::odrxDynamicLinker()->loadApp(RX_RASTER_SERVICES_APPNAME);
  if(pRasSvcs.isNull())
    return eNullObjectPointer;

  return PublishTemplate7(pHostApp, pStreamPrc, extPrc, sOutPdf);
}
