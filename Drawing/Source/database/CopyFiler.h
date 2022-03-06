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

// CopyFiler.h: interface for the OdDwgCopyFiler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COPYFILER_H_INCLUDED_)
#define AFX_COPYFILER_H_INCLUDED_  /* {Secret} */

#include "DbObjectId.h"
#include "Ge/GePoint2d.h"
#include "Ge/GePoint3d.h"
#include "Ge/GeVector2d.h"
#include "Ge/GeVector3d.h"
#include "Ge/GeScale3d.h"
#include "OdString.h"
#include "OdStreamBuf.h"
#include "DbFiler.h"

#if defined(_MSC_VER)
#pragma warning ( disable : 4505 ) //  unreferenced local function
#endif

template< class TBase >
class OdCopyFilerImpl : public TBase
{
public:
  void seek(OdInt64 offset, OdDb::FilerSeekType whence);
  OdUInt64 tell() const;
  void rewind();
  OdDbFiler::FilerType filerType() const;


  //////////////////////////////////////////////
  // reading
  bool         rdBool();
  OdString     rdString();
  void         rdBytes(void* buffer, OdUInt32 nLen);

  OdInt8       rdInt8();
  OdUInt8      rdUInt8();

  OdInt16      rdInt16();
  OdInt32      rdInt32();
  OdInt64      rdInt64();
  double       rdDouble();
  OdDbHandle   rdDbHandle();

  OdDbObjectId rdSoftOwnershipId();
  OdDbObjectId rdHardOwnershipId();
  OdDbObjectId rdHardPointerId();
  OdDbObjectId rdSoftPointerId();
	void*        rdAddress();

  OdGePoint2d  rdPoint2d();
  OdGePoint3d  rdPoint3d();
  OdGeVector2d rdVector2d();
  OdGeVector3d rdVector3d();
	OdGeScale3d  rdScale3d();

  //////////////////////////////////////////////
  // writing
  void wrBool(bool);
  void wrString(const OdString &string);
  void wrBytes(const void* buffer, OdUInt32 nLen);

  void wrInt8(OdInt8 val);
  void wrUInt8(OdUInt8 val);

  void wrInt16(OdInt16 val);
  void wrInt32(OdInt32 val);
  void wrInt64(OdInt64 val);
  void wrDouble(double val);
  void wrDbHandle(const OdDbHandle& val);

  void wrSoftOwnershipId(const OdDbObjectId& id);
  void wrHardOwnershipId(const OdDbObjectId& id);
  void wrSoftPointerId(const OdDbObjectId& id);
  void wrHardPointerId(const OdDbObjectId& id);
	void wrAddress(const void* pAddress);

  void wrPoint2d(const OdGePoint2d& pt);
  void wrPoint3d(const OdGePoint3d& pt);
  void wrVector2d(const OdGeVector2d& vec);
  void wrVector3d(const OdGeVector3d& vec);
	void wrScale3d(const OdGeScale3d& point);
};

template< class TBase>
inline void OdCopyFilerImpl<TBase>::rewind()
{
  TBase::stream().seek(0, OdDb::kSeekFromStart);
}

template< class TBase>
void OdCopyFilerImpl<TBase>::seek(OdInt64 offset, OdDb::FilerSeekType whence)
{
  TBase::stream().seek(offset, whence);
}

template< class TBase>
OdUInt64 OdCopyFilerImpl<TBase>::tell() const
{
  return TBase::stream().tell();
}

template< class TBase>
OdDbFiler::FilerType OdCopyFilerImpl<TBase>::filerType() const
{
  return OdDbFiler::kCopyFiler;
}

//////////////////////////////////////////////
// reading
template< class TBase>
bool OdCopyFilerImpl<TBase>::rdBool()
{
  return (TBase::stream().getByte()!=0);
}

template< class TBase>
OdString OdCopyFilerImpl<TBase>::rdString()
{
  OdString str;
  OdUInt16 nSize = rdInt16();
  OdChar* pBuff = str.getBuffer(nSize);
  TBase::stream().getBytes(pBuff, sizeof(OdChar) * nSize);
  str.releaseBuffer();
  return str;
}

template< class TBase>
void OdCopyFilerImpl<TBase>::rdBytes(void* pBuff, OdUInt32 nLen)
{
  TBase::stream().getBytes(pBuff, nLen);
}


template< class TBase>
OdInt8 OdCopyFilerImpl<TBase>::rdInt8()
{
  return TBase::stream().getByte();
}

template< class TBase>
OdUInt8 OdCopyFilerImpl<TBase>::rdUInt8()
{
  return TBase::stream().getByte();
}


template< class TBase>
OdInt16 OdCopyFilerImpl<TBase>::rdInt16()
{
  OdInt16 res = 0;
  TBase::stream().getBytes(&res, sizeof(OdInt16));
  return res;
}

template< class TBase>
OdInt32 OdCopyFilerImpl<TBase>::rdInt32()
{
  OdInt32 res = 0;
  TBase::stream().getBytes(&res, sizeof(OdInt32));
  return res;
}

template< class TBase>
OdInt64 OdCopyFilerImpl<TBase>::rdInt64()
{
  OdInt64 res = 0;
  TBase::stream().getBytes(&res, sizeof(OdInt64));
  return res;
}

template< class TBase>
double OdCopyFilerImpl<TBase>::rdDouble()
{
  double res = 0.;
  TBase::stream().getBytes(&res, sizeof(double));
  return res;
}

template< class TBase>
OdDbHandle OdCopyFilerImpl<TBase>::rdDbHandle()
{
  OdDbHandle res;
  TBase::stream().getBytes(&res, sizeof(OdDbHandle));
  return res;
}


template< class TBase>
OdDbObjectId OdCopyFilerImpl<TBase>::rdSoftOwnershipId()
{
  OdDbObjectId id;
  TBase::stream().getBytes(&id, sizeof(OdDbObjectId));
  return id;
}

template< class TBase>
OdDbObjectId OdCopyFilerImpl<TBase>::rdHardOwnershipId()
{
  OdDbObjectId id;
  TBase::stream().getBytes(&id, sizeof(OdDbObjectId));
  return id;
}

template< class TBase>
OdDbObjectId OdCopyFilerImpl<TBase>::rdHardPointerId()
{
  OdDbObjectId id;
  TBase::stream().getBytes(&id, sizeof(OdDbObjectId));
  return id;
}

template< class TBase>
OdDbObjectId OdCopyFilerImpl<TBase>::rdSoftPointerId()
{
  OdDbObjectId id;
  TBase::stream().getBytes(&id, sizeof(OdDbObjectId));
  return id;
}

template< class TBase>
void* OdCopyFilerImpl<TBase>::rdAddress()
{
  void* pAddress = 0;
  TBase::stream().getBytes(&pAddress, sizeof(void*));
  return pAddress;
}


template< class TBase>
OdGePoint2d OdCopyFilerImpl<TBase>::rdPoint2d()
{
  OdGePoint2d pt;
  TBase::stream().getBytes(&pt, sizeof(pt));
  return pt;
}

template< class TBase>
OdGePoint3d OdCopyFilerImpl<TBase>::rdPoint3d()
{
  OdGePoint3d pt;
  TBase::stream().getBytes(&pt, sizeof(pt));
  return pt;
}

template< class TBase>
OdGeVector2d OdCopyFilerImpl<TBase>::rdVector2d()
{
  OdGeVector2d vec;
  TBase::stream().getBytes(&vec, sizeof(vec));
  return vec;
}

template< class TBase>
OdGeVector3d OdCopyFilerImpl<TBase>::rdVector3d()
{
  OdGeVector3d vec;
  TBase::stream().getBytes(&vec, sizeof(vec));
  return vec;
}

template< class TBase>
OdGeScale3d OdCopyFilerImpl<TBase>::rdScale3d()
{
  OdGeScale3d scale;
  TBase::stream().getBytes(&scale, sizeof(scale));
  return scale;
}


//////////////////////////////////////////////
// writing
template< class TBase>
void OdCopyFilerImpl<TBase>::wrBool(bool val)
{
  TBase::stream().putByte(OdUInt8(val ? 1 : 0));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrString(const OdString &string)
{
  OdUInt16 nLen = OdUInt16(string.getLength());
  ODA_ASSERT(nLen==string.getLength());
  wrInt16(nLen);
  TBase::stream().putBytes(string.c_str(), sizeof(OdChar)*nLen);
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrBytes(const void* buffer, OdUInt32 nLen)
{
  TBase::stream().putBytes(buffer, nLen);
}


template< class TBase>
void OdCopyFilerImpl<TBase>::wrInt8(OdInt8 val)
{
  TBase::stream().putByte(val);
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrUInt8(OdUInt8 val)
{
  TBase::stream().putByte(val);
}


template< class TBase>
void OdCopyFilerImpl<TBase>::wrInt16(OdInt16 val)
{
  TBase::stream().putBytes(&val, sizeof(val));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrInt32(OdInt32 val)
{
  TBase::stream().putBytes(&val, sizeof(val));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrInt64(OdInt64 val)
{
  TBase::stream().putBytes(&val, sizeof(val));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrDouble(double val)
{
  TBase::stream().putBytes(&val, sizeof(val));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrDbHandle(const OdDbHandle& val)
{
  TBase::stream().putBytes(&val, sizeof(val));
}


template< class TBase>
void OdCopyFilerImpl<TBase>::wrSoftOwnershipId(const OdDbObjectId& id)
{
  TBase::stream().putBytes(&id, sizeof(OdDbObjectId));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrHardOwnershipId(const OdDbObjectId& id)
{
  TBase::stream().putBytes(&id, sizeof(OdDbObjectId));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrSoftPointerId(const OdDbObjectId& id)
{
  TBase::stream().putBytes(&id, sizeof(OdDbObjectId));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrHardPointerId(const OdDbObjectId& id)
{
  TBase::stream().putBytes(&id, sizeof(OdDbObjectId));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrAddress(const void* pAddress)
{
  TBase::stream().putBytes(&pAddress, sizeof(void*));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrPoint2d(const OdGePoint2d& pt)
{
  TBase::stream().putBytes(&pt, sizeof(pt));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrPoint3d(const OdGePoint3d& pt)
{
  TBase::stream().putBytes(&pt, sizeof(pt));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrVector2d(const OdGeVector2d& vec)
{
  TBase::stream().putBytes(&vec, sizeof(vec));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrVector3d(const OdGeVector3d& vec)
{
  TBase::stream().putBytes(&vec, sizeof(vec));
}

template< class TBase>
void OdCopyFilerImpl<TBase>::wrScale3d(const OdGeScale3d& scale)
{
  TBase::stream().putBytes(&scale, sizeof(scale));
}


class OdCopyFilerDummyInterface {};

#include "MemoryStreamImpl.h"

template< class TBase = OdCopyFilerDummyInterface, class TStream = OdMemoryStreamImpl<> >
class OdCopyFilerBase : public TBase
{
  mutable TStream m_stream;
public:
  inline TStream& stream() const { return m_stream; }
};

#endif // !defined(AFX_COPYFILER_H_INCLUDED_)
