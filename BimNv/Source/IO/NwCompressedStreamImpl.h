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




// NwCompressedStreamImpl.h: implementation for the OdNwCompressedStreamImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_NW_COMPRESSED_STREAMIMPL_H_INCLUDED_)
#define _NW_COMPRESSED_STREAMIMPL_H_INCLUDED_

#include "OdaCommon.h"
#define STL_USING_VECTOR
#include "OdaSTL.h"


#include "RxObjectImpl.h"
#include "NwCompressedStream.h"
#include "OdAlloc.h"
#include "NwCompressor.h"
#include "FlatMemStream.h"


/** \details

    {group:Other_Classes}
*/
class OdNwCompressedStreamDummyBase { };

/** \details

    {group:Other_Classes}
*/
template <class TBase = OdNwCompressedStreamDummyBase>
class OdNwCompressedStreamImpl : public TBase
{
private:
  struct TCompressedStreamDef
  {
    OdUInt64 offset;
    OdUInt64 size;
    OdBinaryData data;
    TCompressedStreamDef() 
    {
      offset = 0;
      size = 0;
    }
    TCompressedStreamDef(OdUInt64 offset, OdUInt64 size, OdBinaryData compressedData)
    {
      this->offset = offset;
      this->size = size;
      this->data = compressedData;
    }
  };
  struct TUncompresedStreamDef
  {
    OdInt32 index;
    OdBinaryData data;

    TUncompresedStreamDef()
    {
      index = -1;
    }
  };
  std::vector<TCompressedStreamDef>   m_compressedStreams;
  TUncompresedStreamDef               m_uncompressedStream;
  OdInt32                             m_currentStreamNumber;

private:
  friend class OdwCompressedStream;
  
  OdNwCompressedStreamImpl& operator= (const OdNwCompressedStreamImpl&) {return *this;}
protected:
  OdUInt64  m_nCurPos;
  OdUInt64  m_nEndPos;
  OdUInt32  m_nPageDataSize;

  inline OdInt32 pageNo(OdUInt64 pos) const 
  { 
    if (m_nPageDataSize)
    {
      return m_compressedStreams.empty() ? -1 : OdInt32(pos / m_nPageDataSize);
    }
    OdInt32 pageNum = 0;
    OdUInt64 len = 0;
    for (auto item: m_compressedStreams) 
    {
      len += item.size;
      if (len > pos)
        break;
      pageNum++;
    };

    return pageNum;
  }

  inline OdUInt64 curPageNo() const { 
    return m_currentStreamNumber; 
  }
  inline OdInt64 posInCurPage() const { 
    if (m_compressedStreams.empty())
      return -1;

    return OdInt64((m_nCurPos - m_compressedStreams[m_uncompressedStream.index].offset) % m_uncompressedStream.data.size());
  }

  inline OdInt64 leftInCurPage() const { 
      return (m_uncompressedStream.data.size() - posInCurPage());
  }

  inline OdUInt8* currPos() { return m_uncompressedStream.data.asArrayPtr() + posInCurPage(); }

  inline bool decompressPage(OdUInt32 pageNum) {
    if (m_uncompressedStream.index == pageNum)
      return true;

    m_uncompressedStream.data.clear();
    m_currentStreamNumber = pageNum;
    m_uncompressedStream.index = m_currentStreamNumber;
    if (m_currentStreamNumber >= m_compressedStreams.size())
      return false;

    OdFlatMemStreamPtr compressed = OdFlatMemStream::createNew(m_compressedStreams[m_currentStreamNumber].data.asArrayPtr(), m_compressedStreams[m_currentStreamNumber].data.size());
    bool res = OdNwCompressor::NwInflate(compressed, m_uncompressedStream.data);
    ODA_ASSERT(res);
    // only last stream can e less than m_nPageDataSize
    ODA_ASSERT(m_uncompressedStream.data.size() == m_compressedStreams[m_currentStreamNumber].size);
    return res;
  }
  
public:
  OdNwCompressedStreamImpl(OdUInt32 nPageDataSize = 0)
    : m_compressedStreams()
    , m_uncompressedStream()
    , m_currentStreamNumber(0)
    , m_nCurPos(0)
    , m_nEndPos(0)
    , m_nPageDataSize(nPageDataSize)
  {
  }

  // The methods correspond to OdMemoryStream interface
  //
  OdUInt32 pageDataSize() const { return m_nPageDataSize; }

  void setPageDataSize(OdUInt32 nPageSize) { m_nPageDataSize = nPageSize; }

  // The methods correspond to OdStreamBuf interface
  //
  OdUInt64 length() 
	{
    OdUInt64 len = 0;
    for(auto item: m_compressedStreams) 
    {
      len += item.size;
    }

		return len;
	}

  OdUInt64 seek(OdInt64 offset, OdDb::FilerSeekType whence);

  OdUInt64 tell()
  {
    return m_nCurPos;
  }

  bool isEof()
  {
    return (m_nCurPos >= m_nEndPos);
  }

  OdUInt8 getByte();
  void getBytes(void* buffer, OdUInt32 nLen);

  void putByte(OdUInt8 val);
  void putBytes(const void* buffer, OdUInt32 nLen);

  void copyDataTo(TBase* pDest, OdUInt32 nSrcStart = 0, OdUInt32 nSrcEnd = 0)
  {
    //TBase::copyDataTo(pDest, nSrcStart, nSrcEnd);
    //seek(nSrcStart, OdDb::kSeekFromStart);
    //getBytes(pDest->buffer, nSrcEnd - nSrcStart);
    ODA_ASSERT(!"OdNwCompressedStreamImpl::copyDataTo() not implemented!");
  }

  void rewind()
  {
    m_nCurPos = 0;
    decompressPage(0);
  }

  void truncate()
  {
    ODA_ASSERT(!"OdNwCompressedStreamImpl::truncate() not implemented!");
  }
  void addCompressedStream(OdUInt64 size, OdBinaryData stream)
  {
    size_t offset = m_compressedStreams.empty() ? 0 : (m_compressedStreams.back().offset + m_compressedStreams.back().size);
    m_compressedStreams.push_back({ offset, size, stream });
    m_nEndPos = offset + size;
  }

  ~OdNwCompressedStreamImpl()
  {
    m_currentStreamNumber = 0;
    m_compressedStreams.clear();
  }
};

////////////////////////////////////////////////////////
/** \details

    {group:Other_Classes}
*/

template <class TBase>
OdUInt64 OdNwCompressedStreamImpl<TBase>::seek(OdInt64 offset, OdDb::FilerSeekType from)
{
  OdUInt64 nNewPos;
	switch(from)
	{
	case OdDb::kSeekFromEnd:
		nNewPos = m_nEndPos + offset;
		break;
	case OdDb::kSeekFromCurrent:
		nNewPos = m_nCurPos + offset;
		break;
	case OdDb::kSeekFromStart:
    if(!offset)
    {
      rewind();
      return 0;
    }
		nNewPos = offset;
		break;
	default:
		throw OdError(eInvalidInput);
		break;
	};
  if(nNewPos != m_nCurPos)
  {
    if (nNewPos > m_nEndPos)
      throw OdError( eEndOfFile );

    const OdInt32 page = pageNo(nNewPos);
    bool res = decompressPage(page);
    ODA_ASSERT(res);
    m_nCurPos = nNewPos;
  }
  return m_nCurPos;
}

template <class TBase>
OdUInt8 OdNwCompressedStreamImpl<TBase>::getByte()
{
  OdUInt8 ret;
  if(m_nCurPos < m_nEndPos)
  {
    OdUInt32 nPosInPage = posInCurPage();
    ret = m_uncompressedStream.data.asArrayPtr()[nPosInPage];
    ++m_nCurPos;
    if ((nPosInPage + 1) == m_uncompressedStream.data.size())
      decompressPage(m_currentStreamNumber + 1);
  }
  else
  {
    throw OdError(eEndOfFile);
  }
  return ret;
}

template <class TBase>
void OdNwCompressedStreamImpl<TBase>::getBytes(void* buffer, OdUInt32 nLen)
{
  if (nLen==0)
    return;

  OdUInt64 nNewPos = m_nCurPos + nLen;
  if(nNewPos <= m_nEndPos)
  {
    OdUInt8* pDest = (OdUInt8*)buffer;
    OdUInt32 nToCopy = odmin(leftInCurPage(), nLen);
    if(nToCopy)
    {
      ::memcpy(pDest, currPos(), nToCopy);
      pDest += nToCopy;
      nLen -= nToCopy;
    }
    while(nLen)
    {
      decompressPage(m_currentStreamNumber + 1);
      nToCopy = odmin(m_uncompressedStream.data.size(), nLen);
      ::memcpy(pDest, m_uncompressedStream.data.asArrayPtr(), nToCopy);
      pDest += nToCopy;
      nLen -= nToCopy;
    }
    m_nCurPos = nNewPos;
    if(m_nCurPos && ((m_nCurPos - m_compressedStreams[m_uncompressedStream.index].offset) % m_uncompressedStream.data.size())==0)
      decompressPage(m_currentStreamNumber + 1);
  }
  else
  {
    throw OdError(eEndOfFile);
  }
}

template <class TBase>
void OdNwCompressedStreamImpl<TBase>::putByte(OdUInt8 val)
{
  ODA_ASSERT(!"OdNwCompressedStreamImpl::putByte() not implemented!");
}

template <class TBase>
void OdNwCompressedStreamImpl<TBase>::putBytes(const void* buffer, OdUInt32 nLen)
{
  if (nLen == 0)
  {
    return;
  }

  ODA_ASSERT(!"OdNwCompressedStreamImpl::putBytes() not implemented!");
}
#endif // !defined(_NW_COMPRESSED_STREAMIMPL_H_INCLUDED_)

