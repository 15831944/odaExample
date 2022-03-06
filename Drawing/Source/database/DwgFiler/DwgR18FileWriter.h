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


#ifndef _OD_DWGR18FILEWRITER_H_INCLUDED_
#define _OD_DWGR18FILEWRITER_H_INCLUDED_

#include "DwgWriter.h"
#include "DbSecurity.h"
#include "DwgR18Controller.h"

class DBIO_EXPORT OdDwgR18FileWriter : public OdDwgFileWriter,
                           public OdDwgR18FileController
{
public:
  ODRX_DECLARE_MEMBERS(OdDwgR18FileWriter);
  OdDwgR18FileWriter();

  void writeDatabase(OdDbDatabase* pDb);
  void writeDbIncremental(OdDbDatabase* pDb);

  void writeSectionsMap();
  void writePagesMap();
protected:
  void wrFileHeader();
  void wrR18FileHeader();
  void writeSysSection(OdUInt32 secType, OdInt64& offset, OdStreamBufPtr pSrc);

  void compressDataAndFillSysHeader(OdStreamBufPtr pSrc, OdBinaryData& comprData, SysPageHeader& sysHeader);
  void writeSysHeaderAndData(SysPageHeader& sysHeader, OdBinaryData& comprData);

  void wrHeader();
  void wrObjects();
  void wrObjectsIncSave();
  void wrClasses();
  void wrHandles();
  void wrPreviewImg();
  void wrPreviewImgIncSave();
  void wrAuxHeader();
  void wrObjFreeSpace();
  void wrFileDepList();
  void wrSecurity();
  void wrVbaProject();
  void wrSummaryInfo();
  void wrSummaryInfoIncSave();
  void wrTemplate();

  virtual void wrAppInfo();
  virtual void wrAppInfoIncSave();
  virtual void wrRevHistory();

  virtual void wrAcDsPrototype();
  virtual bool hasDsRecords();
  
  void wrSignature();


  void createSectionsMap();

  void moveSectionPagesToGaps(const OdString& sectionName);

  void registerGapsForRewritableSections();
  void registerGapForSectionsMap();
  void registerGapForPagesMap();

  void prepareSummaryInfo();
  void preparePreviewImg();
  void prepareAppInfo();
  void prepareAcDsPrototype();
  void prepareObjFreeSpace();
  void prepareHandles();
  void prepareClasses();
  void prepareAuxHeader();
  void prepareHeader();

  void removeExistingSignature();
  void prepareSignature();
  void prepareEmptyStreamForOldSignature();

  void removeEndGaps();
  void targetOffsetInit();
  
  OdBinaryData m_vbaData;
};

#endif // _OD_DWGR18FILEWRITER_H_INCLUDED_
