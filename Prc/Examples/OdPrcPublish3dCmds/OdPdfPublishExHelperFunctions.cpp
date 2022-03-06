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
#include "PdfPublish/PdfPublish.h"
#include "Ge/GeBoundBlock3d.h"
#include "Ge/GeExtents2d.h"
#include "Ge/GeLine2d.h"
#include "Ge/GePlane.h"


using namespace OdPdfPublish;


void calculateCameraHelper(const OdGeBoundBlock3d& extents, OdGePoint3d& camPos, OdGePoint3d& targPos, OdGeVector3d& upVec, 
                          Camera::Projection& proj, double& f_w, double& f_h)
{
  OdGeBoundBlock3d tmp_ext = extents;

  if ((proj != Camera::kPerspective) && !extents.isBox())
  {
    tmp_ext.setToBox(true);
  }

  //set target to center of the scene
  OdGePoint3d newTarg = tmp_ext.center();
  OdGeVector3d viewDir = camPos - targPos;
  OdGeMatrix3d xEyeToWorld;
  {
    OdGeVector3d yVector = upVec;
    yVector.normalize();
    OdGeVector3d zVector = (camPos - targPos).normalize();
    OdGeVector3d xVector = yVector.crossProduct(zVector);
    xEyeToWorld.setCoordSystem(newTarg, xVector, yVector, zVector);
  }

  //rotate extents
  tmp_ext.transformBy(xEyeToWorld);

  OdGePoint3d min_pt = tmp_ext.minPoint(), max_pt = tmp_ext.maxPoint();

  double distance(0.0);

  if (proj == Camera::kPerspective)
  {
      const OdGePoint3d cameraPos = newTarg;
      const OdGeVector3d cameraY = upVec.normal();
      const OdGeVector3d cameraZ = (camPos - targPos).normalize();
      const OdGeVector3d cameraX = cameraY.crossProduct(cameraZ);

      const OdGeVector3d boxVecX(max_pt.x - min_pt.x, 0.0, 0.0),
        boxVecY(0.0, max_pt.y - min_pt.y, 0.0),
        boxVecZ(0.0, 0.0, max_pt.z - min_pt.z);
      const OdGePoint3d boxPt[8] = { min_pt, min_pt + boxVecX, min_pt + boxVecY, min_pt + boxVecZ,
                                      max_pt, max_pt - boxVecX, max_pt - boxVecY, max_pt - boxVecZ };

      // Project extents onto view plane
      OdGeExtents2d projectedExt;
      {
        for (int nPt = 0; nPt < 8; nPt++)
          projectedExt.addPoint(OdGePoint2d((boxPt[nPt] - cameraPos).dotProduct(cameraX), (boxPt[nPt] - cameraPos).dotProduct(cameraY)));
      }
      // Compute center of extents
      const OdGePoint2d extCenter = projectedExt.minPoint() + (projectedExt.maxPoint() - projectedExt.minPoint()) * 0.5;

      f_w = 2.0* (projectedExt.maxPoint().x - projectedExt.minPoint().x);
      f_h = 2.0* (projectedExt.maxPoint().y - projectedExt.minPoint().y);

      distance = odmax(f_w / 2.0, f_h / 2.0) / ::tan(OdaPI/6.0);
  }
  else
  {
    f_w = fabs(max_pt.x - min_pt.x);//use fabs(...) for the case if min and max points are swapped
    f_h = fabs(max_pt.y - min_pt.y);

    //move the camera outside the object extents
    distance = odmax(newTarg.distanceTo(tmp_ext.maxPoint()), newTarg.distanceTo(tmp_ext.minPoint()));
  }

  viewDir = distance * viewDir;

  camPos = newTarg + viewDir;
  targPos = newTarg;
}

void addView(OdArtworkPtr pArtwork, const OdGePoint3d& camPos, const OdGePoint3d& targPos, const OdGeVector3d& upVec,
  const OdString& extName, const OdString& intName,
  Camera::Projection proj, double f_w, double f_h,
  const OdGeExtents3d& extPrc,
  Rendering::Mode rMode, Lighting::Mode lMode, bool bDefault, double camera_roll_angle = 0)
{
  OdGePoint3d tmpCamPos = camPos;
  OdGePoint3d tmpTargPos = targPos;
  OdGeVector3d tmpUpVec = upVec;
  
  OdGeBoundBlock3d bbox(extPrc.minPoint(), extPrc.maxPoint());
  calculateCameraHelper(bbox, tmpCamPos, tmpTargPos, tmpUpVec, proj, f_w, f_h);
  //////////////////////////////////////////////////////////////////////////

  OdCameraPtr pCamera = OdCamera::createObject();
  pCamera->setPosition(tmpCamPos);
  pCamera->setTarget(tmpTargPos);
  pCamera->setUpVector(tmpUpVec);
  pCamera->setField(f_w, f_h);
  pCamera->setProjection(proj);
  pCamera->zoom(0.8);

  if (camera_roll_angle)
    pCamera->roll(camera_roll_angle);

  OdViewPtr pView = OdView::createObject();

  pView->setCamera(pCamera);
  pView->setExternalName(extName);
  pView->setInternalName(intName);
  pView->setDefault(bDefault);
  pView->setBackgroundColor(ODRGB(192, 220, 248));
  pView->setLighting(lMode);
  pView->setRendering(rMode);
  pArtwork->addView(pView);
}

OdString correctPathForSample(const OdString& filePath)
{
  OdRxSystemServices* pSs = odrxSystemServices();
  if (pSs)
  {
    OdString validPath = filePath;
    if (pSs->accessFile(validPath, Oda::kFileRead))
      return validPath; // Found path as is.
#if defined(ODA_WINDOWS)
    validPath.insert(0, "Prc\\Examples\\OdPrcPublish3dCmds\\");
#else
    validPath.insert(0, "Prc//Examples//OdPrcPublish3dCmds//");
#endif
    if (pSs->accessFile(validPath, Oda::kFileRead))
      return validPath;
    for (OdUInt32 i = 0; i < 7; i++)
    {
#if defined(ODA_WINDOWS)
      validPath.insert(0, "..\\");
#else
      validPath.insert(0, "..//");
#endif
      if (pSs->accessFile(validPath, Oda::kFileRead))
        return validPath;
    }
  }
  return OdString::kEmpty; // not found

};

void addTextFields(OdUInt32 iStartIndex, const OdString& sOutPdf, OdRect topTextRect, OdRect fieldRect, OdPagePtr& pPage)
{
  for (OdUInt32 i = iStartIndex; i < iStartIndex + 3; ++i)
  {
    OdTextFieldPtr field = OdTextField::createObject();
    OdString fieldName;
    fieldName.format(L"Field%i", i);
    field->setName(fieldName);
    field->setBorder(false);
    field->setFont(Text::kTimesBold);
    field->setTextJustification(Text::kLeft);
    field->setReadOnly(true);

    OdTextPtr text = OdText::createObject();
    text->setSize(8);

    if (i == iStartIndex)
    {
      OdInt32 outPos = sOutPdf.reverseFind(L'\\');
      if (-1 == outPos)
        outPos = sOutPdf.reverseFind(L'/');
      OdString outFileName = sOutPdf;
      if (-1 != outPos)
        outFileName = sOutPdf.right(sOutPdf.getLength() - outPos - 1);
      field->setDefaultValue(outFileName);
      text->setText(L"FILE NAME");
    }
    else if (i == iStartIndex + 1)
    {
      OdTimeStamp date;
      date.getLocalTime();
      OdString dateStr;
      date.strftime(L"%x", dateStr);
      field->setDefaultValue(dateStr);
      text->setText(L"DATE CREATED");
    }
    else if (i == iStartIndex + 2)
    {
      field->setDefaultValue(OdString(TD_PRODUCT_NAME_START_W) + L" Publish");
      text->setText(L"AUTHOR");
    }

    pPage->addTextField(field, fieldRect);

    fieldRect.m_min.x = fieldRect.m_max.x + 10;
    fieldRect.m_max.x = fieldRect.m_min.x + 160;

    topTextRect.m_min.x += 2;
    pPage->addText(text, topTextRect);

    topTextRect.m_min.x = fieldRect.m_min.x;
    topTextRect.m_max.x = fieldRect.m_max.x;
  }
}

void addPageHeader(OdPagePtr& pPage, const OdString& sOutPdf, const OdUInt8 page_index)
{
  OdImagePtr topLogo = OdImage::createObject();
  OdString validPath = correctPathForSample("brand-logo.jpg");
  if (validPath.isEmpty())
  {
    validPath = "brand-logo.jpg";
    ODA_VERIFY(!"File 'brand-logo.jpg' not found! Please copy this file from 'Prc/Examples/OdPrcPublish3dCmds' to the folder in the support path.");
  }
  topLogo->setFile(validPath);
  OdRect topLogoRect(9, 256, 540, 584);
  pPage->addImage(topLogo, topLogoRect);

  OdRect fieldRect(332, 492, 564, 584);

  OdRect topTextRect = fieldRect;
  topTextRect.m_max.y = fieldRect.m_min.y - 3;
  topTextRect.m_min.y = topTextRect.m_max.y - 10;

  addTextFields(page_index * 3, sOutPdf, topTextRect, fieldRect, pPage);
}

void addPageFooter(OdPagePtr& pPage, const OdRect& rect)
{
  OdInt32 secondLineTop = 18;
  OdRect leftBottomTextRect1 = rect;
  leftBottomTextRect1.m_max.y = rect.m_min.y - 5;
  leftBottomTextRect1.m_min.y = secondLineTop;
  leftBottomTextRect1.m_max.x = rect.m_min.x + 10;
  OdTextPtr copText = OdText::createObject();
  copText->setSize(8);
  copText->setFont(Text::kSymbol);
  char copyright_char = (char)211;
  OdString copStr(&copyright_char, 1, CP_ASCII);
  copText->setText(copStr);
  pPage->addText(copText, leftBottomTextRect1);

  leftBottomTextRect1.m_min.x = leftBottomTextRect1.m_max.x;
  leftBottomTextRect1.m_max.x = rect.m_max.x / 2;
  OdTextPtr leftBottomText1 = OdText::createObject();
  leftBottomText1->setSize(8);
  OdString copyrightStr(TD_COPYRIGHT_END_W);
  leftBottomText1->setText(copyrightStr.right(copyrightStr.getLength() - 1));
  pPage->addText(leftBottomText1, leftBottomTextRect1);

  leftBottomTextRect1.m_min.x = rect.m_min.x;
  leftBottomTextRect1.m_max.x = 220;
  leftBottomTextRect1.m_min.y = 9;
  leftBottomTextRect1.m_max.y = secondLineTop;
  OdTextPtr leftBottomText2 = OdText::createObject();
  leftBottomText2->setSize(8);
  leftBottomText2->setText(L"10115 E Bell Road, Suite 107 #447 Scottsdale, AZ 85260, USA. ");
  pPage->addText(leftBottomText2, leftBottomTextRect1);

  leftBottomTextRect1.m_min.x = 220;
  leftBottomTextRect1.m_max.x = rect.m_max.x / 2;
  leftBottomTextRect1.m_min.y = 9;
  leftBottomTextRect1.m_max.y = secondLineTop;
  OdTextPtr leftBottomText3 = OdText::createObject();
  leftBottomText3->setSize(8);
  leftBottomText3->setFont(Text::kTimesBold);
  leftBottomText3->setText(L"www.opendesign.com");
  pPage->addText(leftBottomText3, leftBottomTextRect1);

  OdImagePtr bottomLogo = OdImage::createObject();
  OdString validPath = correctPathForSample("brand-logo-small.jpg");
  if (validPath.isEmpty())
  {
    validPath = "brand-logo-small.jpg";
    ODA_VERIFY(!"File 'brand-logo-small.jpg' not found! Please copy this file from 'Prc/Examples/OdPrcPublish3dCmds' to the folder in the support path.");
  }
  bottomLogo->setFile(validPath);
  OdRect bottomLogoRect;
  bottomLogoRect.m_min.x = 742;
  bottomLogoRect.m_max.y = rect.m_min.y - 5;
  bottomLogoRect.m_min.y = 3;
  bottomLogoRect.m_max.x = bottomLogoRect.m_min.x + (bottomLogoRect.m_max.y - bottomLogoRect.m_min.y);
  pPage->addImage(bottomLogo, bottomLogoRect);

  OdRect rightBottomTextRect1 = OdRect(bottomLogoRect.m_max.x + 3, 832, secondLineTop, rect.m_min.y - 5);
  OdTextPtr rightBottomText1 = OdText::createObject();
  rightBottomText1->setSize(8);
  rightBottomText1->setText(L"Created with");
  pPage->addText(rightBottomText1, rightBottomTextRect1);

  rightBottomTextRect1.m_max.y = secondLineTop;
  rightBottomTextRect1.m_min.y = 9;
  OdTextPtr rightBottomText2 = OdText::createObject();
  rightBottomText2->setSize(8);
  rightBottomText2->setFont(Text::kTimesBold);
  rightBottomText2->setText(OdString(TD_PRODUCT_NAME_START_W) + L" Publish");
  pPage->addText(rightBottomText2, rightBottomTextRect1);
}
