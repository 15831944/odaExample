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


#ifndef _OD_DWGR18COMPRESSOR_H_INCLUDED_
#define _OD_DWGR18COMPRESSOR_H_INCLUDED_

#include "OdStreamBuf.h"
#include "OdBinaryData.h"

class OdDwgR18Compressor
{
public:
  OdDwgR18Compressor();

  void compress(OdBinaryData& src, OdBinaryData& dst);
  void compress(const OdUInt8* srcData, OdUInt32 srcSize, OdBinaryData& dstData);
  void decompress(OdBinaryData& src, OdBinaryData& dst, OdUInt32 maxSize);
  void decompress(const OdUInt8* srcData, OdUInt32 srcSize, OdUInt8* dstData, OdUInt32 dstSize);

private:
  //
  // Decompression methods
  //
  inline void readLiteral(int opcode);
  inline void readLongLength(int& length);
  inline void readLength(int& length, int opcode, int mask);
  inline void readOffset(int& opcode1, int& opcode2, int& offset);
  inline void readCompressed(int length, int offset);

  //
  // Compression methods
  //
  void writeLength(OdInt32 opcode, OdInt32 length, OdInt32 threshold);
  void writeLongLength(OdInt32 val);
  void writeLiteral(OdUInt32 litLength);
  void writeMatch(OdInt32 offset, OdInt32 length, OdInt32 litLength);
  bool findMatch(OdUInt32& matchLength, OdUInt32& matchOffset);

  OdArray<OdUInt8*> m_HashTable;

  OdUInt8* m_pSrcStart;
  OdUInt8* m_pSrcCurr;
  OdUInt8* m_pSrcPrev;
  OdUInt8* m_pSrcEnd;
  OdUInt8* m_pDstCurr;
  OdUInt8* m_pDstStart;
  OdUInt8* m_pDstEnd;


  OdStreamBufPtr m_Target;
};

//----------------------------------------------------------
//
// Inline implementation
//
//----------------------------------------------------------
inline
void OdDwgR18Compressor::readLongLength(int& length)
{
  OdUInt8 val = *m_pSrcCurr++;
  while (!val)
  {
    length += 0xff; 
    val = *m_pSrcCurr++;
  }
  length += val;
}

inline
void OdDwgR18Compressor::readLength(int& length, int opcode, int mask)
{
  length = opcode & mask;
  if (!length)
  {
    length = mask; // threshold-2
    readLongLength(length);
  }
  length += 2;
}

inline
void OdDwgR18Compressor::readLiteral(int opcode)
{
  int litLength = opcode & 3;
  if ( !litLength             // literal length was written in opcode
    && !(*m_pSrcCurr & 0xf0)) // literal length == 0, this is the next opcode
  {
    readLength(litLength, *m_pSrcCurr++, 0xf);
    litLength++;
  }

  if (litLength)
  {
    ODA_ASSERT(litLength > 0);
    if  (m_pDstCurr < m_pDstStart || m_pDstCurr + litLength > m_pDstEnd
      || m_pSrcCurr < m_pSrcStart || m_pSrcCurr + litLength > m_pSrcEnd)
    { // May happen in specially crafted files  CORE-17326
      throw OdError_DwgObjectImproperlyRead();
    }
    ::memcpy(m_pDstCurr, m_pSrcCurr, litLength);
    m_pSrcCurr += litLength;
    m_pDstCurr += litLength;
  }
}

inline
void OdDwgR18Compressor::readCompressed(int length, int offset)
{
  OdUInt8* pDstPrev = m_pDstCurr - offset;

  if (length < offset)
  {
    ODA_ASSERT(length > 0);
    if (m_pDstCurr < m_pDstStart || m_pDstCurr + length > m_pDstEnd
      || pDstPrev   < m_pDstStart || pDstPrev + length > m_pDstEnd)
    { // May happen in specially crafted files  CORE-17326
      throw OdError_DwgObjectImproperlyRead();
    }
    ::memcpy(m_pDstCurr, pDstPrev, length);
    m_pDstCurr += length;
  }
  else
  {
    while (length--)
    {
      *m_pDstCurr++ = *pDstPrev++;
    }
  }
}

inline
void OdDwgR18Compressor::readOffset(int& opcode1, int& opcode2, int& offset)
{
  opcode1 = *m_pSrcCurr++;
  opcode2 = *m_pSrcCurr++;
  
  offset |= opcode1 >> 2;
  offset |= opcode2 << 6;
}

#endif // _OD_DWGR18COMPRESSOR_H_INCLUDED_
