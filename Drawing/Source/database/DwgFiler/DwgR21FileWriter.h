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


#ifndef _OD_DWGR21FILEWRITER_H_INCLUDED_
#define _OD_DWGR21FILEWRITER_H_INCLUDED_

#include "DwgWriter.h"
#include "DwgR21Controller.h"
#include "DwgStreams.h"
#include "DbSecurity.h"

class OdDwgR21FileWriter : public OdDwgFileWriter,
                           public OdDwgR21FileController
{
public:
  ODRX_DECLARE_MEMBERS(OdDwgR21FileWriter);
  OdDwgR21FileWriter();

  void writeDatabase(OdDbDatabase* pDb);

private:
  void wrMetadata();
  void wrSectionsMap();
  void wrPagesMap();

  void wrHeader();
  void wrObjects();
  void wrClasses();
  void wrHandles();
  void wrPreviewImg();
  void wrAuxHeader();
  void wrObjFreeSpace();
  void wrFileDepList();
  void wrSecurity();
  void wrVbaProject();
  void wrSummaryInfo();
  void wrTemplate();
  void wrAppInfo();
  void wrRevHistory();

  void wrString(const OdString& val);
  void wrString32(const OdString& str);

  void createSectionsMap();

  virtual void openBitStream(bool isObjectStream);
  virtual void closeBitStream();
  virtual OdDwgFileSplitStream* bitStream();
  OdStaticRxObject<OdDwgR21FileSplitStream> m_dwgR21Filer;
  OdBinaryData m_strBuffer;

  OdBinaryData m_vbaData;
};

#endif // _OD_DWGR21FILEWRITER_H_INCLUDED_
