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


#ifndef _OD_DWGR24FILEWRITER_H_INCLUDED_
#define _OD_DWGR24FILEWRITER_H_INCLUDED_

#include "DwgR18FileWriter.h"
#include "DwgR24FileSplitStream.h"

class DBIO_EXPORT OdDwgR24FileWriter : public OdDwgR18FileWriter
{
public:
  ODRX_DECLARE_MEMBERS(OdDwgR24FileWriter);
  OdDwgR24FileWriter();

protected:
  // OdDwgFileController overridden
  void wrString(const OdString& val);
  void wrString32(const OdString& str);

  // OdDwgFileWriter overridden
  void openBitStream(bool isObjectStream);
  void closeBitStream();
  OdDwgFileSplitStream* bitStream();

  // OdDwgR18FileWriter overridden
  void wrAppInfo();
  void wrAppInfoIncSave();
  void wrRevHistory();

private:
  OdStaticRxObject<OdDwgR21FileSplitStream> m_dwgR21Filer;
  OdStaticRxObject<OdDwgR24FileSplitStream> m_dwgR24Filer;
  OdDwgFileSplitStream* m_pDwgStream;
protected:
  OdBinaryData m_strBuffer;
};

#endif // _OD_DWGR24FILEWRITER_H_INCLUDED_
