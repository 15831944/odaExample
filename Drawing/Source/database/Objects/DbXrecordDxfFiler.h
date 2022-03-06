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

#ifndef _OdDbXrecDxfFiler_h_Included_
#define _OdDbXrecDxfFiler_h_Included_

#include "RxObjectImpl.h"
#include "DbXrecord.h"

class TOOLKIT_EXPORT OdDbXrecDxfFiler : public OdDbDxfFiler
{
  OdRefCounter m_nRefCounter;
  OdDbXrecordIteratorPtr m_pIt;
  OdDbXrecordPtr m_pXrec;
  OdDbDatabase* m_pDb;

  OdResBufPtr   m_pRbInitial;
  OdResBufPtr   m_pRb;

  bool          m_bPushedBack;

public:

  OdDbXrecDxfFiler() { m_nRefCounter = 1; }
  OdDbXrecDxfFiler(OdDbXrecord* pXrec, OdDbDatabase* db);
  ~OdDbXrecDxfFiler() { push(); }

  void addRef() { ++m_nRefCounter; }
  void release() {
    ODA_ASSERT((m_nRefCounter > 0));
    if (!(--m_nRefCounter))
      delete this;
  }
  long numRefs() const { return m_nRefCounter; }

  FilerType filerType() const { return OdDbFiler::kCopyFiler; }
  OdDbDatabase* database() const { return m_pDb; }
  OdDb::DwgVersion dwgVersion(OdDb::MaintReleaseVer* = NULL) const;
  bool atEOF();
  int nextItem();
  void pushBackItem();

  // Data output functions
  void wrString( int groupCode, const OdString& string );
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

  /*
  Push the whole OdResBuf sequence into m_pXrec and then clear the sequence,
  must be used when writing data after collecting the sequence of OdResBufs
  with wr* functions. If there was no explicit callind of the method, destructor
  will call push() automatically.
  */
  void push();
  
  OdString rdString();
  void        rdString(OdString &string);
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
};

#endif // _OdDbXrecDxfFiler_h_Included_
