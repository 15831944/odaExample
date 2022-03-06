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

#ifndef _OD_DWGSTREAM_H_INCLUDED_
#define _OD_DWGSTREAM_H_INCLUDED_


#include "OdBinaryData.h"
#include "DbFiler.h"
#include "OdStreamBuf.h"
#include "IdArrays.h"

class OdString;

//----------------------------------------------------------
//
// OdTvDwgStream
//
//----------------------------------------------------------

class TOOLKIT_EXPORT OdTvDwgStream : public OdTvDbDwgFiler
{
  // state
  bool              m_bWrite;
  OdUInt64          m_nStreamEndBit;
  OdBinaryData*     m_pBuffer;

  // current position
  OdUInt32          m_nByte;
  OdUInt8           m_mask;
  unsigned          m_nBitPos; // 0-7

public:
  bool isOpenForWrite() const { return m_bWrite; }
  OdBinaryData* buffer() const { return m_pBuffer; }

public:
  ODRX_DECLARE_MEMBERS(OdTvDwgStream);
  OdTvDwgStream();
  virtual ~OdTvDwgStream();

  virtual void          openR(const OdBinaryData* pBuffer);
  virtual void          openR(const OdBitBinaryData* pBuffer);
  virtual void          openW(OdBinaryData* pBuffer);

   inline void          curtailEndBit(OdUInt64 nStreamEndBit);

          bool          isEof();

          OdUInt64      length()
          {
            return m_nStreamEndBit; 
          }

          OdUInt64      tell() const;
  virtual OdUInt64      tell();

  virtual void          close();
  virtual void          seek(OdInt64 offset, OdDb::FilerSeekType whence);

  OdDb::DwgVersion      dwgVersion(OdDb::MaintReleaseVer *pnMaintReleaseVer = NULL) const;

  virtual FilerType     filerType() const { return OdTvDbFiler::kCopyFiler; }

  virtual bool          rdBool();
  virtual OdUInt8       rdUInt8();
  virtual OdInt8        rdInt8();
  virtual void          rdBytes(void* buffer, OdUInt32 nLen);
  virtual OdInt16       rdInt16();
  virtual OdInt32       rdInt32();
  virtual OdInt64       rdInt64();
  virtual double        rdDouble();
  virtual OdDbHandle    rdDbHandle();
  virtual OdTvDbObjectId  rdSoftOwnershipId();
  virtual OdTvDbObjectId  rdHardOwnershipId();
  virtual OdTvDbObjectId  rdHardPointerId();
  virtual OdTvDbObjectId  rdSoftPointerId();
  virtual OdTvDbObjectId  rdObjectId(OdDb::ReferenceType* pRefType = NULL);
  virtual OdString      rdString();
  virtual OdGePoint2d   rdPoint2d();
  virtual OdGePoint3d   rdPoint3d();
  virtual OdGeVector3d  rdVector3d();
  virtual OdGeVector2d  rdVector2d();
  virtual OdGeScale3d   rdScale3d();

  virtual void          wrBool(bool val);
  virtual void          wrUInt8(OdUInt8 val);
  virtual void          wrInt8(OdInt8 val);
  virtual void          wrBytes(const void* buffer, OdUInt32 nLen);
  virtual void          wrInt16(OdInt16 val);
  virtual void          wrInt32(OdInt32 val);
  virtual void          wrInt64(OdInt64 val);
  virtual void          wrDouble(double val);
  virtual void          wrDbHandle(const OdDbHandle& val);
  virtual void          wrSoftOwnershipId(const OdTvDbObjectId& id);
  virtual void          wrHardOwnershipId(const OdTvDbObjectId& id);
  virtual void          wrSoftPointerId(const OdTvDbObjectId& id);
  virtual void          wrHardPointerId(const OdTvDbObjectId& id);
  virtual void          wrString(const OdString& val);
  virtual void          wrPoint2d(const OdGePoint2d& pt);
  virtual void          wrPoint3d(const OdGePoint3d& pt);
  virtual void          wrVector2d(const OdGeVector2d& pt);
  virtual void          wrVector3d(const OdGeVector3d& pt);
  virtual void          wrScale3d(const OdGeScale3d& point);

          void          rdPoint3PairWDef(OdGePoint3d& p1, OdGePoint3d& p2);
          void          wrPoint3PairWDef(const OdGePoint3d& p1, const OdGePoint3d& p2);

          double        rdDoubleWithDefault(double);
          void          wrDoubleWithDefault(double val, double defVal);

  virtual double        rdRawDouble();
  virtual void          wrRawDouble(double);
          void          wrPointWithDefault(const OdGePoint3d& pt, const OdGePoint3d& def);
          OdGePoint3d&  rdPointWithDefault(OdGePoint3d& pt, OdGePoint3d& def);
          OdUInt8       rdHandleParts(OdUInt64& res);
          void          wrHandleParts(OdUInt8 ctrl, OdInt64 value);

          OdUInt16      rdRawUInt16();
          OdUInt32      rdRawUInt32();
          void          wrRawUInt16(OdUInt16 val);
          void          wrRawUInt32(OdUInt32 val);

  virtual OdUInt64      rdEndBits(OdBitBinaryData& data);
  virtual OdUInt64      wrEndBits(const OdBitBinaryData& data);

  virtual double        rdThickness();
  virtual void          wrThickness(double val);
  virtual OdGeVector3d  rdExtrusion();
  virtual void          wrExtrusion(const OdGeVector3d& p);

protected:
   inline OdUInt32      internalRdUInt2();
   inline OdUInt32      internalRdUInt3();
   inline OdUInt32      internalRdUInt8();
   inline OdUInt16      internalRdUInt16();
   inline OdUInt32      internalRdUInt32();
   inline OdUInt64      internalRdUInt64();
   inline void*         internalRdPointer();
   
   inline void          internalWrUInt2(OdUInt8 nValue);
   inline void          internalWrUInt3(OdUInt8 nValue);
   inline void          internalWrUInt8(OdUInt8 nValue);
   inline void          internalWrUInt16(OdUInt16 val);
   inline void          internalWrUInt32(OdUInt32 val);
   inline void          internalWrInt64(const OdInt64& val);
   inline void          internalWrPointer(void* val);

   inline void          move_to_next_bit();
   inline void          move_to_next_bit_w();
   inline void          internalOpen(OdBinaryData* pBuffer);
   inline bool          internalEof();
   inline OdUInt64      internalTell() const;
};

typedef OdSmartPtr<OdTvDwgStream> OdTvDwgStreamPtr;

//----------------------------------------------------------
//
// OdTvDwgR21Stream
//
//----------------------------------------------------------

class TOOLKIT_EXPORT OdTvDwgR21Stream : public OdTvDwgStream
{
public:
  OdTvDwgR21Stream() {}

  // Overriden open for write function
  void openW(OdBinaryData* pBuffer);

  // Overridden string r/w functions
  OdString rdString();
  void wrString(const OdString& val);
};

//----------------------------------------------------------
//
// Read/write wchar-string macroses
//
//----------------------------------------------------------

#define DD_HAS_NULL_CHAR 1
#define DD_NO_NULL_CHAR  0

#if ODCHAR_IS_INT16LE

#define DD_READ_UC_STRING(numCharsToRead, str, readShortCall, readBytesCall, nullIncluded) \
  if (numCharsToRead) \
  { \
    readBytesCall((OdUInt8*)str.getBuffer(numCharsToRead + 1 - nullIncluded), numCharsToRead << 1); \
    str.releaseBuffer(numCharsToRead - nullIncluded); \
  } \
  else \
  { \
    str = OdString::kEmpty; \
  }

#define DD_WRITE_UC_STRING(numCharsToWrite, str, writeShortCall, writeBytesCall) \
  writeBytesCall(str.c_str(), numCharsToWrite << 1);

#else

#define DD_READ_UC_STRING(numCharsToRead, str, readShortCall, readBytesCall, nullIncluded) \
  if (numCharsToRead) \
  { \
    OdChar* p = (OdChar*)str.getBuffer(numCharsToRead + 1); \
    for (unsigned j = 0; j < numCharsToRead; ++j) \
      p[j] = (OdChar)readShortCall; \
    str.releaseBuffer(numCharsToRead - nullIncluded); \
  } \
  else \
  { \
    str = OdString::kEmpty; /* prevent UMR */ \
  }

#define DD_WRITE_UC_STRING(numCharsToWrite, str, writeShortCall, writeBytesCall) \
  OdChar* p = (OdChar*)str.c_str(); \
  for (unsigned j = 0; j < numCharsToWrite; ++j) \
    writeShortCall((OdUInt16)p[j]);

#endif

//----------------------------------------------------------
//
// OdTvDwgStream inline methods
//
//----------------------------------------------------------

#ifdef DD_ELIMINATE_UMRS
#define RESIZE(ptr, size) ptr->resize(size, 0)
#define RESIZE2(ptr, size) \
  ptr->resize(size, 0);\
  memset(&ptr->at(ptr->length() - 1), 0, ptr->capacity() - ptr->length() + 1) // needed to prevent UMR's on SGI
#else
#define RESIZE(ptr, size) ptr->resize(size)
#define RESIZE2(ptr, size) RESIZE(ptr, size)
#endif

inline
void OdTvDwgStream::curtailEndBit(OdUInt64 endBit)
{
  //if (endBit <= m_nStreamEndBit)
  // In R21 curtailEndBit() is used for extending size of data part of stream
  // while proxy loading
  ODA_ASSERT(endBit <= (OdUInt64)m_pBuffer->size() << 3);
  if (endBit <= (OdUInt64)m_pBuffer->size() << 3)
    m_nStreamEndBit = endBit;
}

inline
void* OdTvDwgStream::internalRdPointer()
{
  void* res;
  rdBytes(&res, sizeof(res));
  return res;
}

inline
void OdTvDwgStream::internalWrPointer(void* val)
{
  wrBytes(&val, sizeof(val));
}

inline
bool OdTvDwgStream::internalEof()
{
  return (internalTell() >= m_nStreamEndBit);
}

inline
void OdTvDwgStream::internalOpen(OdBinaryData* pBuffer)
{
  ODA_ASSERT(pBuffer != NULL);
  m_pBuffer = pBuffer;
  m_mask = 0x80;
  m_nBitPos = m_nByte = 0;
}

inline
void OdTvDwgStream::move_to_next_bit()
{
  m_mask >>= 1;
  ++m_nBitPos;
  if(!m_mask)
  {
    m_mask = 0x80;
    m_nBitPos = 0;
    m_nByte++;
  }
}

inline
void OdTvDwgStream::move_to_next_bit_w()
{
  m_mask >>= 1;
  ++m_nBitPos;
  if(!m_mask)
  {
    m_mask = 0x80;
    m_nBitPos = 0;
    m_nByte++;
    if(m_nByte>=m_pBuffer->size())
    {
      RESIZE2(m_pBuffer, (m_nByte+1));
    }
  }
  OdUInt64 nCurBit = internalTell();
  if (nCurBit > m_nStreamEndBit)
    m_nStreamEndBit = nCurBit;
}

inline
OdUInt32 OdTvDwgStream::internalRdUInt2()
{
  if (internalTell()+2 <= length())
  {
    const OdUInt8* pbuff = m_pBuffer->getPtr();
    OdUInt32 res = ((pbuff[m_nByte] & m_mask) != 0) ? 1 : 0;
    move_to_next_bit();
    res <<= 1;
    res |= ((pbuff[m_nByte] & m_mask) != 0) ? 1 : 0;
    move_to_next_bit();
    return res;
  }
  throw OdError_DwgObjectImproperlyRead();
}

inline
OdUInt32 OdTvDwgStream::internalRdUInt3()
{
  if (internalTell()+3 <= length())
  {
    const OdUInt8* pbuff = m_pBuffer->getPtr();
    OdUInt32 res = ((pbuff[m_nByte] & m_mask) != 0) ? 1 : 0;
    move_to_next_bit();
    res <<= 1;
    res |= ((pbuff[m_nByte] & m_mask) != 0) ? 1 : 0;
    move_to_next_bit();
    res <<= 1;
    res |= ((pbuff[m_nByte] & m_mask) != 0) ? 1 : 0;
    move_to_next_bit();
    return res;
  }
  throw OdError_DwgObjectImproperlyRead();
}

inline
OdUInt32 OdTvDwgStream::internalRdUInt8()
{
  if (internalTell()+8 <= length())
  {
    const OdUInt8* pos = m_pBuffer->getPtr() + m_nByte;
    ++m_nByte;
    return m_nBitPos ? OdUInt8((*pos << m_nBitPos) | (*(pos+1) >> (8-m_nBitPos))) : *pos;
  }
  throw OdError_DwgObjectImproperlyRead();
}

inline
void OdTvDwgStream::internalWrUInt2(OdUInt8 nValue)
{
  if ((nValue & 2) != 0)
    m_pBuffer->at(m_nByte) |= m_mask;
  else
    m_pBuffer->at(m_nByte) &= ~m_mask;
  move_to_next_bit_w();

  if ((nValue & 1) != 0)
    m_pBuffer->at(m_nByte) |= m_mask;
  else
    m_pBuffer->at(m_nByte) &= ~m_mask;
  move_to_next_bit_w();
}

inline
void OdTvDwgStream::internalWrUInt3(OdUInt8 nValue)
{
  if ((nValue & 4) != 0)
    m_pBuffer->at(m_nByte) |= m_mask;
  else
    m_pBuffer->at(m_nByte) &= ~m_mask;
  move_to_next_bit_w();

  if ((nValue & 2) != 0)
    m_pBuffer->at(m_nByte) |= m_mask;
  else
    m_pBuffer->at(m_nByte) &= ~m_mask;
  move_to_next_bit_w();

  if ((nValue & 1) != 0)
    m_pBuffer->at(m_nByte) |= m_mask;
  else
    m_pBuffer->at(m_nByte) &= ~m_mask;
  move_to_next_bit_w();
}

inline
void OdTvDwgStream::internalWrUInt8(OdUInt8 nValue)
{
  if (m_nByte+1 >= m_pBuffer->size())
  {
    RESIZE(m_pBuffer, (m_nByte+2));
  }

  if (m_nBitPos)
  {
    OdUInt8* posTo = &m_pBuffer->at(m_nByte);
    OdUInt32 shift1 = 8-m_nBitPos;
    *posTo >>= shift1;
    *posTo <<= shift1;
    *posTo |= OdUInt8(nValue >> m_nBitPos);
    ++posTo;
    *posTo <<= m_nBitPos;
    *posTo >>= m_nBitPos;
    *posTo |= OdUInt8(nValue << shift1);
  }
  else
  {
    m_pBuffer->at(m_nByte) = nValue;
  }
  ++m_nByte;

  OdUInt64 nCurBit = internalTell();
  if (nCurBit > m_nStreamEndBit)
    m_nStreamEndBit = nCurBit;
}

inline
OdUInt16 OdTvDwgStream::internalRdUInt16()
{
  if (internalTell()+16 > length())
  {
    throw OdError_DwgObjectImproperlyRead();
  }

  OdUInt16 res = 0;
  const OdUInt8* pos = m_pBuffer->getPtr() + m_nByte;
  m_nByte += 2;
  if (m_nBitPos)
  {
    res = OdUInt8((*pos << m_nBitPos) | (*(pos+1) >> (8-m_nBitPos)));
    ++pos;
    res |= OdUInt8((*pos << m_nBitPos) | (*(pos+1) >> (8-m_nBitPos))) << 8;
  }
  else
  {
    res = *pos;
    ++pos;
    res |= *pos << 8;
  }
  return res;
}

inline
OdUInt32 OdTvDwgStream::internalRdUInt32()
{
  if (internalTell()+32 > length())
  {
    throw OdError_DwgObjectImproperlyRead();
  }

  OdUInt32 res = 0;
  const OdUInt8* pos = m_pBuffer->getPtr() + m_nByte;
  m_nByte += 4;
  if (m_nBitPos)
  {
    res = OdUInt8((*pos << m_nBitPos) | (*(pos+1) >> (8-m_nBitPos)));
    ++pos;
    res |= OdUInt8((*pos << m_nBitPos) | (*(pos+1) >> (8-m_nBitPos))) << 8;
    ++pos;
    res |= OdUInt8((*pos << m_nBitPos) | (*(pos+1) >> (8-m_nBitPos))) << 16;
    ++pos;
    res |= OdUInt8((*pos << m_nBitPos) | (*(pos+1) >> (8-m_nBitPos))) << 24;
  }
  else
  {
    res = *pos;
    ++pos;
    res |= *pos << 8;
    ++pos;
    res |= *pos << 16;
    ++pos;
    res |= *pos << 24;
  }
  return res;
}

inline
void OdTvDwgStream::internalWrUInt16(OdUInt16 val)
{
  internalWrUInt8(OdUInt8(val & 0x00FF));
  internalWrUInt8(OdUInt8((val >> 8) & 0x00FF));
}

inline
void OdTvDwgStream::internalWrUInt32(OdUInt32 val)
{
  internalWrUInt16(OdUInt16(val & 0x0000FFFF));
  internalWrUInt16(OdUInt16((val >> 16) & 0x0000FFFF));
}

inline
void OdTvDwgStream::internalWrInt64(const OdInt64& val)
{
  internalWrUInt32((OdUInt32)(val & 0xFFFFFFFF));
  internalWrUInt32((OdUInt32)((val >> 32) & 0xFFFFFFFF));
}

inline
OdUInt64 OdTvDwgStream::internalRdUInt64()
{
  OdInt64 val = internalRdUInt32();
  val += ((OdUInt64)internalRdUInt32()) << 32;
  return val;
}

inline
OdUInt64 OdTvDwgStream::internalTell() const
{
  ODA_ASSERT(m_mask);
  return ((OdUInt64)m_nByte * 8 + m_nBitPos);
}

#endif // _OD_DWGSTREAM_H_INCLUDED_
