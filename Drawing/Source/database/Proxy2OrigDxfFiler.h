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


#ifndef PROXY2ORIGDXFFILER_INCLUDED
#define PROXY2ORIGDXFFILER_INCLUDED

#include "DbFiler.h"
#include "IdArrays.h"
#include "DwgStream.h"

class OdBinaryData;
class OdProxyStuff;

//----------------------------------------------------------
//
// OdProxyDxfFiler
//
//----------------------------------------------------------

class OdProxyDxfFiler : public OdDbDxfFiler
{
public:
  OdProxyDxfFiler();

  // Overridden
  //
  OdDbDatabase* database() const;
  FilerType filerType() const;
  OdDb::DwgVersion dwgVersion(OdDb::MaintReleaseVer* = NULL) const;
  bool atEOF();
  bool atEndOfObject();
  bool atExtendedData();
  bool atSubclassData(const OdString& subClassName);
  bool atEmbeddedObjectStart();
  int nextItem();
  void pushBackItem();

  void        rdString(OdString& string);
  bool        rdBool();
  OdInt8      rdInt8();
  OdInt16     rdInt16();
  OdInt32     rdInt32();
  OdInt64     rdInt64();
  OdUInt8     rdUInt8();
  OdUInt16    rdUInt16();
  OdUInt32    rdUInt32();
  OdUInt64    rdUInt64();
  OdDbHandle  rdHandle();
  OdDbObjectId rdObjectId();
  double      rdAngle();
  double      rdDouble();
  void        rdPoint2d(OdGePoint2d& pt);
  void        rdPoint3d(OdGePoint3d& pt);
  void        rdVector2d(OdGeVector2d& pt);
  void        rdVector3d(OdGeVector3d& pt);
  void        rdScale3d(OdGeScale3d& pt);
  void        rdBinaryChunk(OdBinaryData&);

  void wrString(int groupCode, const OdString& string);
  void wrName(int groupCode, const OdString& string);
  void wrBool(int groupCode, bool val);
  void wrInt8(int groupCode, OdInt8 val);
  void wrUInt8(int groupCode, OdUInt8 val);
  void wrInt16(int groupCode, OdInt16 val);
  void wrUInt16(int groupCode, OdUInt16 val);
  void wrInt32(int groupCode, OdInt32 val);
  void wrUInt32(int groupCode, OdUInt32 val);
  void wrInt64(int groupCode, OdInt64 val);
  void wrUInt64(int groupCode, OdUInt64 val);
  void wrHandle(int groupCode, OdDbHandle val);
  void wrObjectId(int groupCode, OdDbObjectId val);
  void wrAngle(int groupCode, double val, int precision = kDfltPrec);
  void wrDouble(int groupCode, double val, int precision = kDfltPrec);
  void wrPoint2d(int groupCode, const OdGePoint2d& pt, int precision = kDfltPrec);
  void wrPoint3d(int groupCode, const OdGePoint3d& pt, int precision = kDfltPrec);
  void wrVector2d(int groupCode, const OdGeVector2d& pt, int precision = kDfltPrec);
  void wrVector3d(int groupCode, const OdGeVector3d& pt, int precision = kDfltPrec);
  void wrScale3d(int groupCode, const OdGeScale3d& pt, int precision = kDfltPrec);
  void wrBinaryChunk(int groupCode, const OdUInt8* pBuff, OdUInt32 nSize);

  inline void copyItemsTo(OdDbDxfFiler* pFiler);

protected:
  void openR(OdDbDatabase* pDb, OdDwgStream* pDataStream, OdDwgStream* pStrStream, OdTypedIdsArray* pIds);
  void openW(OdDbDatabase* pDb, OdDwgStream* pDataStream, OdDwgStream* pStrStream, OdTypedIdsArray* pIds);

protected:
  OdDwgStream* getDataStream() const { return m_pDataStream; }
  OdDwgStream* getStrStream() const { return m_pStrStream; }
  bool isOpenForWrite() const { return m_status == kWrite; }

  enum status { kNotOpen, kNotReady, kCodeReady, kAtData, kWrite } m_status;

private:
  void skipData();
  inline int getCurrCode();

  OdDbDatabase*    m_pDb;
  OdDwgStream*     m_pDataStream;
  OdDwgStream*     m_pStrStream;
  OdTypedIdsArray* m_pIds;
  OdUInt32         m_nIdIndex;
  int              m_nGroupCode;
  OdUInt64         m_lastPos;
  bool             m_bUsedDataStream;

};

//----------------------------------------------------------
//
// OdProxy2OrigDxfFiler
//
//----------------------------------------------------------

class OdProxy2OrigDxfFiler : public OdProxyDxfFiler
{
  OdProxy2OrigDxfFiler& operator = (const OdProxy2OrigDxfFiler&);
public:
  OdProxy2OrigDxfFiler();
  void openR(OdDbDatabase* pDb, const OdProxyStuff* pProxy);
  void openW(OdDbDatabase* pDb, OdProxyStuff* pProxy);
  void close();

  // Overridden
  //
  OdDb::DwgVersion dwgVersion(OdDb::MaintReleaseVer* = NULL) const;

private:
  OdProxyStuff*                    m_pProxy;
  OdStaticRxObject<OdDwgStream>    m_dataStream;
  OdStaticRxObject<OdDwgR21Stream> m_strStream;
};

//----------------------------------------------------------
//
// OdProxy2ProxyDxfFiler
//
//----------------------------------------------------------

class OdProxy2ProxyDxfFiler : public OdProxyDxfFiler
{
  OdProxy2ProxyDxfFiler& operator = (const OdProxy2ProxyDxfFiler&);
public:
  OdProxy2ProxyDxfFiler();
  void openW(OdDwgStream* pFiler);
  void close();

  // Overridden
  //
  OdDbObjectId rdObjectId();
  void wrObjectId(int groupCode, OdDbObjectId val);
};

//----------------------------------------------------------
//
// Inline methods
//
//----------------------------------------------------------

int OdProxyDxfFiler::getCurrCode()
{
  if(m_status==kNotReady)
  {
    m_nGroupCode = m_pDataStream->rdInt16();
    m_status=kCodeReady;
  }
  return m_nGroupCode;
}

void OdProxyDxfFiler::copyItemsTo(OdDbDxfFiler* pFiler) 
{
  while (!atEndOfObject())
  {
    pFiler->copyItem(this);
  }
}

#endif //PROXY2ORIGDXFFILER_INCLUDED
