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

#ifndef _DWGR18UTILS_H_
#define _DWGR18UTILS_H_

#include "OdArray.h"

class OdR18FileUtils
{
  OdInt32  m_numReactors;
  bool     m_XDicNull;
  OdInt16  m_XDataSize;
  OdInt32  m_fileSize;
  
  void reset() 
  { 
    m_numReactors = 0; 
    m_XDicNull = true; 
    m_XDataSize = 0;
  }
  
public:
  
  OdR18FileUtils() 
  {
  }
  
  ~OdR18FileUtils() 
  {
  }
      
  void decompress(OdDwgFileStream& dwgStream, OdDwgFileLoader* pLoader);
  
  static void dumpHeader(OdDwgFileStream& dwgStream);
  
  void hexDump(OdDwgFileLoader* pLoader, OdUInt8* data, OdInt32 addr, OdInt32 size, FILE* fp, int lineSize);
  static void traceBytes(OdDwgFileStream& dwgStream, int num, bool asBits = false);
};


#endif //_DWGR18UTILS_H_
