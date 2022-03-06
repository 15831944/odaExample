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


#ifndef _OD_DWGR18PAGEDSTREAMMTHELPER_H_INCLUDED_
#define _OD_DWGR18PAGEDSTREAMMTHELPER_H_INCLUDED_

#include "DwgFileController.h"

// ODA_MT_DBIO_BEGIN
//----------------------------------------------------------
//
// OdTvDwgR18PagedStreamMTHelper
//
//----------------------------------------------------------
class OdTvDwgR18PagedStreamMTHelper : public OdRxObjectImpl<OdStreamBuf>
{
public:
  static inline OdStreamBufPtr create(OdTvDwgR18PagedStream* pPagedStream, OdTvDwgFileLoader* pLoader, int threadId)
  {
    return OdStreamBufPtr((OdStreamBuf*)new OdTvDwgR18PagedStreamMTHelper(pPagedStream, pLoader, threadId), kOdRxObjAttach);
  }
  OdTvDwgR18PagedStreamMTHelper(OdTvDwgR18PagedStream* pPagedStream, OdTvDwgFileLoader* pLoader, int threadId)
    : m_curPosInPage(0)
    , m_pPagedStream(pPagedStream)
    , m_pLoader(pLoader)
    , m_threadId(threadId)
  {
    m_curPage = m_pPagedStream->pages().end();
  }
  ~OdTvDwgR18PagedStreamMTHelper()
  {}

  //
  // OdStreamBuf overridden
  //
  OdUInt8 getByte()
  {
    if ( m_curPage == m_pPagedStream->pages().end()
      || curPos() >= m_pPagedStream->m_dataSize)
    {
      throw OdError(eEndOfFile);
    }

    if (!m_curPage->data())
    {
      getPage();
    }
    OdUInt8 res = m_curPage->getByte(m_curPosInPage);
    ++m_curPosInPage;
    if (m_curPosInPage == m_curPage->m_dataSize)
    {
      nextPageR();
    }
    return res;
  }
  void getBytes(void* buffer, OdUInt32 len)
  {
    if (len==0)
      return;

    if ( m_curPage == m_pPagedStream->pages().end()
      || curPos() + len > m_pPagedStream->m_dataSize)
    {
      throw OdError(eEndOfFile);
    }

    OdUInt8* dst = (OdUInt8*)buffer;
    OdUInt32 copySize = odmin(m_curPage->m_dataSize - m_curPosInPage, len);
    if (copySize)
    {
      if (!m_curPage->data())
      {
        getPage();
      }
      m_curPage->getBytes(m_curPosInPage, dst, copySize);
      dst += copySize;
      len -= copySize;
    }
    while (len)
    {
      nextPageR();
      copySize = odmin(m_curPage->m_dataSize, len);
      if (!m_curPage->data())
      {
        getPage();
      }
      m_curPage->getBytes(0, dst, copySize);
      dst += copySize;
      len -= copySize;
    }

    m_curPosInPage += copySize;
    if (m_curPosInPage == m_curPage->m_dataSize)
    {
      nextPageR();
    }
  }
  void putByte(OdUInt8 value)
  { 
    ODA_FAIL();
    throw OdError(eUnsupportedMethod);
  }
  void putBytes(const void* buffer, OdUInt32 len)
  { 
    ODA_FAIL();
    throw OdError(eUnsupportedMethod);
  }

  OdUInt64 seek(OdInt64 offset, OdDb::FilerSeekType from)
  {
    OdUInt64 newPos;
    switch (from)
    {
    case OdDb::kSeekFromEnd:
      newPos = m_pPagedStream->m_dataSize + offset;
      break;
    case OdDb::kSeekFromCurrent:
      newPos = tell() + offset;
      break;
    case OdDb::kSeekFromStart:
      newPos = offset;
      break;
    default:
      throw OdError(eInvalidInput);
      break;
    }

    if (newPos > m_pPagedStream->m_dataSize)
    {
      throw OdError(eEndOfFile);
    }

    if (newPos == 0)
    {
      // New position is the start of stream
      rewind();
    }
    else if (newPos == m_pPagedStream->m_dataSize)
    {
      // New position is the end of stream
      ODA_ASSERT(m_pPagedStream->pages().size());
      m_curPage = m_pPagedStream->pages().end();
      --m_curPage;
      if (newPos < m_curPage->m_dataOffset + m_pPagedStream->m_pageSize)
      {
        m_curPosInPage = m_curPage->m_dataSize;
      }
      else
      {
        m_curPage = m_pPagedStream->pages().end();
        m_curPosInPage = 0;
      }
    }
    else
    {
      ODA_ASSERT(m_pPagedStream->pages().size());
      if (m_curPage == m_pPagedStream->pages().end())
      {
        --m_curPage;
      }

      // Verify if the current position is changed
      if (newPos != curPos())
      {
        // Seek page of a new position
        m_curPage = m_pPagedStream->pages().begin() + (newPos/m_pPagedStream->m_pageSize);
        // Set position in the current page
        m_curPosInPage = (OdUInt32)(newPos - m_curPage->m_dataOffset);
      }
    }

    return newPos;
  }

  OdUInt64 tell()
  {
    return m_curPage == m_pPagedStream->pages().end() ? m_pPagedStream->m_dataSize : curPos();
  }
  OdUInt64 length()
  {
    return m_pPagedStream->m_dataSize; 
  }
  bool isEof()
  {
    return m_curPage == m_pPagedStream->pages().end() || curPos() >= m_pPagedStream->m_dataSize;
  }
  void rewind()
  {
    m_curPosInPage = 0;
    m_curPage = m_pPagedStream->pages().begin();
    ODA_ASSERT(m_curPage == m_pPagedStream->pages().end() || m_curPage->m_dataOffset == 0);
  }
  void truncate()
  {
    ODA_FAIL();
    throw OdError(eUnsupportedMethod);
  }

protected:
  OdTvDwgR18PagedStream* m_pPagedStream;
  OdTvDwgFileLoader* m_pLoader;
  int m_threadId;
  OdTvDwgR18PagedStream::OdPageArrayIterator m_curPage;
  OdUInt32 m_curPosInPage;

  OdUInt64 curPos()
  { 
    ODA_ASSERT(m_curPage != m_pPagedStream->pages().end());
    return m_curPage->m_dataOffset + m_curPosInPage;
  }

  void nextPageR()
  {
    ODA_ASSERT(m_pPagedStream->pages().size() && m_curPage != m_pPagedStream->pages().end());
    ++m_curPage;
    m_curPosInPage = 0;
  }

  void getPage()
  {
    TD_AUTOLOCK(*m_curPage->m_dataLock);
    if (m_curPage->data())
      return;

    ODA_ASSERT((OD_T("Re-loading of a file page"), m_curPage->data() == 0));
    ODA_ASSERT((OD_T("Reading from an empty page"), m_curPage->m_dataSize != 0));

    OdTvDwgR18FileLoader::R18MTContext* pR18MTContext = (OdTvDwgR18FileLoader::R18MTContext*)m_pLoader->getMTContext();
    OdBinaryData& pageData = pR18MTContext->m_buffs[m_threadId];
    OdTvDwgR18Compressor& cmpr =  pR18MTContext->m_compressors[m_threadId];

    m_pPagedStream->getPage(*m_curPage, pageData, cmpr);
  }
};
// ODA_MT_DBIO_END

#endif // _OD_DWGR18PAGEDSTREAMMTHELPER_H_INCLUDED_
