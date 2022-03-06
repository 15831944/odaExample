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
#include "DynamicLinker.h"
#include "PdfPublish/PdfPublish.h"


using namespace OdPdfPublish;

//1191,   842

OdResult OdPdfPublishCADEx(OdDbBaseHostAppServices* pHostApp, OdDbBaseDatabase *pDatabase, const OdString& sServiceCaption, const OdString& sOutPdf, const OdString& sInputFileName)
{
  if (sOutPdf.isEmpty())
  {
    return eInvalidInput;
  }

  OdFilePtr pPublisher = OdFile::createObject();

  OdDocumentPtr pDoc = OdDocument::createObject();
  pDoc->setInformation(L"Pdf Publish CAD* Sample Document", L"Author", L"CAD* Sample", L"Oda Pdf Publish");
  pDoc->setHostServices(pHostApp);

  OdCADDefinitionPtr pCADDef = OdCADDefinition::createObject();
  pCADDef->setDatabase(pDatabase);
  pCADDef->setMediaSize(Page::kMillimeters, 840., 594.);

  // Page 1
  OdPagePtr pPage1 = OdPage::createObject();
  pPage1->setFormat(Page::kA3);
  pPage1->setOrientation(Page::kLandscape);
  pDoc->addPage(pPage1);

  OdTextPtr pCaptionPage1 = OdText::createObject();
  pCaptionPage1->setText(sServiceCaption + L" sample");
  pCaptionPage1->setSize(20);
  pCaptionPage1->setFont(Text::kTimesBold);
  pPage1->addText(pCaptionPage1, OdRect(550, 1186, 820, 842));

  OdCADReferencePtr pCADRef1 = OdCADReference::createObject();
  pCADRef1->setCADDefinition(pCADDef);
  pPage1->addCADReference(pCADRef1, OdRect(5, 1180, 5, 800));

  // Page 2. Rotation
  OdPagePtr pPage2 = OdPage::createObject();
  pPage2->setFormat(Page::kA3);
  pPage2->setOrientation(Page::kLandscape);
  pDoc->addPage(pPage2);

  OdTextPtr pCaptionPage2 = OdText::createObject();
  pCaptionPage2->setText(sServiceCaption + L" rotation sample");
  pCaptionPage2->setSize(20);
  pCaptionPage2->setFont(Text::kTimesBold);
  pPage2->addText(pCaptionPage2, OdRect(550, 1186, 820, 842));

  OdCADReferencePtr pCADRef2 = OdCADReference::createObject();
  pCADRef2->setCADDefinition(pCADDef);
  pCADRef2->setRotation(OdaPI4);
  pCADRef2->setBorder(true);
  pPage2->addCADReference(pCADRef2, OdRect(5, 1180, 10, 800));


  // Page 3. Clip
  OdPagePtr pPage3 = OdPage::createObject();
  pPage3->setFormat(Page::kA3);
  pPage3->setOrientation(Page::kLandscape);
  pDoc->addPage(pPage3);

  OdTextPtr pCaptionPage3 = OdText::createObject();
  pCaptionPage3->setText(sServiceCaption + L" clip sample");
  pCaptionPage3->setSize(20);
  pCaptionPage3->setFont(Text::kTimesBold);
  pPage3->addText(pCaptionPage3, OdRect(550, 1186, 820, 842));

  OdCADReferencePtr pCADRef3 = OdCADReference::createObject();
  pCADRef3->setCADDefinition(pCADDef);
  OdGePoint2dArray clip_box;
  clip_box.append(OdGePoint2d(360, 100));
  clip_box.append(OdGePoint2d(320, 225));
  clip_box.append(OdGePoint2d(360, 350));
  clip_box.append(OdGePoint2d(455, 400));
  clip_box.append(OdGePoint2d(550, 350));
  clip_box.append(OdGePoint2d(590, 225));
  clip_box.append(OdGePoint2d(550, 100));
  pCADRef3->setClipBoundary(Page::kMillimeters, clip_box);
  pCADRef3->setClipBoundaryBorder(true);
  pCADRef3->setClipBoundaryBorderColor(ODRGB(255,0,0));
  pCADRef3->setClipBoundaryBorderWidth(2);
  pPage3->addCADReference(pCADRef3, OdRect(600, 1180, 50, 800));

  OdTableCreatorPtr table_creator = OdTableCreator::createObject();

  table_creator->setRowCount(30);
  table_creator->setColumnCount(3);

  table_creator->setParticularColumnWidth(1, 245);

  table_creator->setCellFillColor(0, 0, ODRGB(127, 255, 68));
  table_creator->setCellFillColor(0, 1, ODRGB(127, 255, 68));
  table_creator->setCellFillColor(0, 2, ODRGB(127, 255, 68));

  table_creator->setParticularRowHeight(0, 70);

  OdTablePtr table1 = table_creator->createTable();

  OdTextPtr text1 = OdText::createObject();
  text1->setText(L"NB");
  text1->setSize(20);
  table1->setText(0, 0, text1);

  OdTextPtr text2 = OdText::createObject();
  text2->setText(L"Part Name");
  text2->setSize(20);
  table1->setText(0, 1, text2);

  OdTextPtr text3 = OdText::createObject();
  text3->setText(L"QTY");
  text3->setSize(20);
  table1->setText(0, 2, text3);

  for (OdUInt8 i = 1; i < 30; ++i)
  {
    OdTextPtr text_c1 = OdText::createObject();
    text_c1->setText(OdString().format(L"%i", i));
    text_c1->setSize(15);
    table1->setText(i, 0, text_c1);

    OdTextPtr text_c2 = OdText::createObject();
    text_c2->setText(OdString().format(L"part_name_%i", i));
    text_c2->setSize(12);
    table1->setText(i, 1, text_c2);

    OdTextPtr text_c3 = OdText::createObject();
    text_c3->setText(OdString().format(L"%i", rand() % 20 + 1));
    text_c3->setSize(12);
    table1->setText(i, 2, text_c3);
  }

  pPage3->addTable(table1, OdRect(10, 550, 10, 800));

  // Page 4. Matrix transform
  OdPagePtr pPage4 = OdPage::createObject();
  pPage4->setFormat(Page::kA3);
  pPage4->setOrientation(Page::kLandscape);
  pDoc->addPage(pPage4);

  OdTextPtr pCaptionPage4 = OdText::createObject();
  pCaptionPage4->setText(sServiceCaption + L" Matrix transform sample");
  pCaptionPage4->setSize(20);
  pCaptionPage4->setFont(Text::kTimesBold);
  pPage4->addText(pCaptionPage4, OdRect(550, 1186, 820, 842));

  OdCADReferencePtr pCADRef4 = OdCADReference::createObject();
  pCADRef4->setCADDefinition(pCADDef);
  OdGeMatrix2d transform;
  transform.setCoordSystem(OdGePoint2d(350, 50), OdGeVector2d::kXAxis, OdGeVector2d::kYAxis);
  transform *= OdGeMatrix2d::scaling(0.035);
  transform *= OdGeMatrix2d::rotation(OdaPI/6.0);
  pCADRef4->setTransform(transform);

  pPage4->addCADReference(pCADRef4);

  //Add source file to attachment
  OdString sDescription(L"source");
  pDoc->addAttachment(sInputFileName, sDescription);

  pPublisher->exportPdf(pDoc, sOutPdf);
  return ::eOk;
}
