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
#include "DbHostAppServices.h"
#include "Db3dSolid.h"
#include "DbDatabase.h"
#include "DbBlockTableRecord.h"
#include "Br/BrBrep.h"
#include "OdPrcCreateStart.h"
#include "AppServices/PrcHostAppServices.h"
#include "MemoryStream.h"
#include "PrcExport.h"
#include "PdfExportService.h"

#if 0
#include "ColorMapping.h"
#include "PdfExport.h"
#include "PrcDefaultContextForTD.h"
#include "ExPrintConsole.h"
using namespace TD_PDF_2D_EXPORT;

void getPrcViaPdfExport(PRCStreamsMap & outStreamsPRC, PDFExportParams & publishParams);

// prc file for test is created here
void createTestGeometryForAttributeTest(OdStreamBufPtr &pMemStream, OdDbHostAppServices &pH)
{
  // create a solid object
  OdDb3dSolidPtr p3dSolid = OdDb3dSolid::createObject();
  p3dSolid->createSphere(10);

  OdDbDatabasePtr pDb = pH.createDatabase();
  OdDbBlockTableRecordPtr pRec = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
  pRec->appendOdDbEntity(p3dSolid);

  PRCStreamsMap outStreamsPRC;
  PDFExportParams publishParams;
  publishParams.setPalette(odcmAcadDarkPalette());
  publishParams.setDatabase(pDb);
  publishParams.setPRCMode(PDFExportParams::kAsBrep);
  getPrcViaPdfExport(outStreamsPRC, publishParams);

  std::map<OdUInt32, OdStreamBufPtr>::iterator pIt = outStreamsPRC.find(0);
  if (pIt == outStreamsPRC.end())
  {
    throw OdError(L"\nRESULT PRC MISSING!\n");
  }
  pIt->second->rewind();
  pIt->second->copyDataTo(pMemStream);
}
#else
// prc file for test is created here
void createTestGeometryForAttributeTest(OdStreamBufPtr &pMemStream, OdDbHostAppServices &pH)
{
  // create a solid object
  OdDb3dSolidPtr p3dSolid = OdDb3dSolid::createObject();
  p3dSolid->createSphere(10);

  OdDbDatabasePtr pDb = pH.createDatabase();
  OdDbBlockTableRecordPtr pRec = pDb->getModelSpaceId().safeOpenObject(OdDb::kForWrite);
  pRec->appendOdDbEntity(p3dSolid);

  // load module
  odrxDynamicLinker()->loadModule(OdDwg2PrcExportModuleName, false);
  PdfExportServiceInterfacePtr pExportIFace = getPdfExportService();

  // write file to stream
  PDF2PRCExportParams params;
  OdRxObjectPtr pContext = pExportIFace->createPrcExportContext(pDb);
  OdResult res = pExportIFace->exportPrc(pContext, p3dSolid, &params);
  if (res != eOk)
  {
    throw OdError(res);
  }
  res = pExportIFace->serialize(pMemStream, pContext, &params);
  if (res != eOk)
  {
    throw OdError(res);
  }
}
#endif


// sample timestamp sub attribute created here!
void AddAttributeTimeStamp(OdPrcAttribute &newAttribute)
{
  // create pair
  OdPrcContentSingleAttribute attributeDataPair;
  OdTimeStamp testtime(OdTimeStamp::kInitLocalTime);
  testtime.setDate(1, 1, 1970); // month, day, year
  testtime.setTime(1, 2, 3, 0); // hour, minute, second, millisecond
  attributeDataPair.setData(testtime);

  // pair title
  OdPrcAttributeEntry subtitle;
  subtitle.setData(EPRCAttributeEntryCreateTimeDate); // can be one of pre-defined names from enum or any string
  attributeDataPair.attributeEntry() = subtitle;

  // add pair to attribute
  newAttribute.AddDataPair(attributeDataPair);
}

// sample integer sub attribute created here!
void AddAttributeInt(OdPrcAttribute &newAttribute)
{
  // create pair
  OdPrcContentSingleAttribute attributeDataPair;
  attributeDataPair.setData((OdInt32)112233); // can be negative as well!

  // pair title
  OdPrcAttributeEntry subtitle;
  subtitle.setData(EPRCAttributeEntryRevisionNumber); // can be one of pre-defined names from enum or any string
  attributeDataPair.attributeEntry() = subtitle;

  // add pair to attribute
  newAttribute.AddDataPair(attributeDataPair);
}

// sample double sub attribute created here!
void AddAttributeDouble(OdPrcAttribute &newAttribute)
{
  // create pair
  OdPrcContentSingleAttribute attributeDataPair;
  attributeDataPair.setData(0.123);

  // pair title
  OdPrcAttributeEntry subtitle;
  subtitle.setData(L"example double title"); // can be one of pre-defined names from enum or any string
  attributeDataPair.attributeEntry() = subtitle;

  // add pair to attribute
  newAttribute.AddDataPair(attributeDataPair);
}

// sample string sub attribute created here!
void AddAttributeString(OdPrcAttribute &newAttribute)
{
  // create pair
  OdPrcContentSingleAttribute attributeDataPair;
  attributeDataPair.setData(L"ODA PRC SDK Create Example App");

  // pair title
  OdPrcAttributeEntry subtitle;
  subtitle.setData(EPRCAttributeEntryAuthor); // can be one of pre-defined names from enum or any string
  attributeDataPair.attributeEntry() = subtitle;

  // add pair to attribute
  newAttribute.AddDataPair(attributeDataPair);
}

// creates an attribute and fills it with several sub attributes of different type
void AddAttribute(OdPrcAttributeData &attrdata, OdString strTitle)
{
  OdPrcAttributeArray &attrArr = attrdata.attributes();
  attrArr.append();
  OdPrcAttribute &newAttribute = attrArr.last();

  // add data
  AddAttributeTimeStamp(newAttribute);
  AddAttributeInt(newAttribute);
  AddAttributeDouble(newAttribute);
  AddAttributeString(newAttribute);

  // add title to attribute
  OdPrcAttributeEntry title;
  title.setData(strTitle);
  newAttribute.SetTitle(title);
}

void attributeExample(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  // create an object
  OdStreamBufPtr pMemStream = OdMemoryStream::createNew();
  createTestGeometryForAttributeTest(pMemStream, pH);

  // add attribute to the object
  pMemStream->rewind();
  OdPrcFilePtr pFile = pPrcHost.readFile(pMemStream);
  OdPrcFileStructureTree &tree = pFile->fileStructures().last()->fileStructureTree();
  for (OdUInt32 i = 0; i < tree.productOccurrence().size(); ++i)
  {
    OdPrcProductOccurrencePtr pPO = tree.productOccurrence()[i];
    pPO->name().setName(L"sphere");
  }

  if (mode == kAttributeToProductOccurrence)
  {
    //  write to product occurrence
    OdPrcProductOccurrencePtr productOc = tree.productOccurrence().last();
    // - write several attributes
    AddAttribute(productOc->attributeData(), L"attribute in PrOcc #1");
    AddAttribute(productOc->attributeData(), L"attribute in PrOcc #2");
    AddAttribute(productOc->attributeData(), L"attribute in PrOcc #3");
  }
  if (mode == kAttributeToPartDefinition)
  {
    // write to part definition
    OdPrcPartDefinitionPtr part = tree.partDefinition().last().safeOpenObject(kForWrite);
    // - write several attributes
    AddAttribute(part->attributeData(), L"attribute in PtDef #1");
    AddAttribute(part->attributeData(), L"attribute in PtDef #2");
    AddAttribute(part->attributeData(), L"attribute in PtDef #3");
  }
  if (mode == kAttributeToRepresentationItem)
  {
    // write to representation item
    OdPrcPartDefinitionPtr part = tree.partDefinition().last().safeOpenObject(kForWrite);
    OdPrcRepresentationItemPtr item = part->representationItem().last().safeOpenObject(kForWrite);
    // - write several attributes
    AddAttribute(item->attributeData(), L"attribute in RpIt #1");
    AddAttribute(item->attributeData(), L"attribute in RpIt #2");
    AddAttribute(item->attributeData(), L"attribute in RpIt #3");
  }

  // write file
  pFile->writeFile(pPrcStream);
}
