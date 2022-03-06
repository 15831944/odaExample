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


#ifndef _OD_DWGR18PAGEDSTREAM_H_INCLUDED_
#define _OD_DWGR18PAGEDSTREAM_H_INCLUDED_

#include "DwgFileController.h"
// ODA_MT_DBIO_BEGIN
#include "OdMutexArray.h"
#include "DwgR18Compressor.h"
// ODA_MT_DBIO_END

class OdDwgR18FileController;

OdUInt32 checksum(OdUInt32 seed, const OdBinaryData& data);
OdUInt32 checksum(OdUInt32 seed, const OdUInt8* p, OdUInt32 sz);

//----------------------------------------------------------
//
// Const
//
//----------------------------------------------------------
#define FILE_HEADER_OFFSET      0x80
#define FILE_HEADER_DATA_SIZE   0x6c
#define FILE_HEADER_PAGE_SIZE   0x80
#define RANDOM_SEQ_SIZE         0x100
#define SECTION_HEADER_SIZE     0x20
#define SYS_SECTION_HEADER_SIZE 0x14
#define PAGE_ALIGN_OFFSET       0x20

#define PAGES_MAP_TYPE    0x41630e3b
#define SECTIONS_MAP_TYPE 0x4163003b
#define DATA_PAGE_TYPE    0x4163043b
#define DATA_PAGE_MASK    0x4164536b

//----------------------------------------------------------
//
// OdStreamWithCrc32
//
//----------------------------------------------------------
class OdStreamWithCrc32 : public OdStreamWithCrc
{
  OdUInt32 m_crc;
  static const OdUInt32 m_crc32Table[];
  void crc(OdUInt8 byte)
  {
    m_crc = (m_crc >> 8) ^ m_crc32Table[(m_crc ^ byte) & 0xff];
  }
  void crc(OdUInt8 *p, OdUInt32 n)
  {
    while (n--) crc(*p++);
  }

  OdStreamWithCrc32(OdStreamBuf* pStreamBuf) : OdStreamWithCrc(pStreamBuf) { initCRC(0); }
public:
  ODRX_DECLARE_MEMBERS(OdStreamWithCrc32);
  
  static inline OdStreamBufPtr create(OdStreamBuf* pStreamBuf)
  {
    return OdStreamBufPtr((OdRxObject*)new OdStreamWithCrc32(pStreamBuf), kOdRxObjAttach);
  }

  void initCRC(OdUInt32 seed) { m_crc = ~seed; }
  OdUInt32 getCRC() { return ~m_crc; }
  void checkCRC(OdUInt32 testCrc) { if (getCRC() != testCrc) throw OdError(eDwgCRCError); }

  OdUInt8 getByte();
  void getBytes(void* buffer, OdUInt32 nLen);
  void putByte(OdUInt8 val);
  void putBytes(const void* bytes, OdUInt32 len);
};

//----------------------------------------------------------
//
// OdDwgR18PagedStream
//
//----------------------------------------------------------
class DBIO_EXPORT OdDwgR18PagedStream : public OdStreamBuf
{
// ODA_MT_DBIO_BEGIN
// OdArray<OdMutex> can not be copied safely
  OdDwgR18PagedStream(const OdDwgR18PagedStream&);
  OdDwgR18PagedStream& operator = (const OdDwgR18PagedStream&);
// ODA_MT_DBIO_END
public:
  ODRX_DECLARE_MEMBERS(OdDwgR18PagedStream);

  OdDwgR18PagedStream();
  ~OdDwgR18PagedStream();

  void openW();
  void openAppend();
  void setController(OdDwgR18FileController* pController) { m_pController = pController; }
  OdDwgR18FileController* getController() { return m_pController; }

  //
  // OdStreamBuf overridden
  //
  OdUInt8 getByte();
  void getBytes(void* buffer, OdUInt32 len);
  void putByte(OdUInt8 value);
  void putBytes(const void* buffer, OdUInt32 len);
  OdUInt64 seek(OdInt64 offset, OdDb::FilerSeekType whence);
  OdUInt64 tell();
  OdUInt64 length();
  bool isEof();
  void rewind();
  void truncate();

  //
  // Stream attributes (file data from SectionsMap)
  //
  OdUInt64 m_dataSize;
  //OdUInt32 m_pagesAmount;
  OdUInt32 m_pageSize;
  OdUInt32 m_unknown;
  OdUInt32 m_compressed;    // NotCompressed = 1, Compressed = 2
  OdUInt32 m_sectionId;
  OdUInt32 m_encrypted;    // NotEncrypted = 0, Encrypted = 1

  bool isEncrypted() const { return m_encrypted == 1; }
  bool isCompressed() const { return m_compressed == 2; }

  //
  // Implementation of the paged structure
  //
  class Page
  {
  public:
    // Page data from SectionsMap
    OdUInt32 m_pageId;
    OdUInt32 m_comprSize;
    OdUInt64 m_dataOffset;
    // Run-time data
    // (all pages have the same size)
    OdUInt8* m_data;
    OdUInt32 m_dataSize; // read  : is equal to PageSize except the last page
                             // write : used to control page filling
// ODA_MT_DBIO_BEGIN
    OdMutex* m_dataLock;
// ODA_MT_DBIO_END

    Page()  // default argument here won't work for array initialization on SGI, separate no-arg constructor required
      : m_pageId(0)
      , m_comprSize(0)
      , m_dataOffset(0)
      , m_dataSize(0)
      , m_data(0)
// ODA_MT_DBIO_BEGIN
      , m_dataLock(0)
// ODA_MT_DBIO_END
    {}

    Page(OdInt64 dataOffset)
    {
      new (this) Page();
      m_dataOffset = dataOffset;
    }

    OdUInt8 getByte(OdUInt32 pos) const
    {
      ODA_ASSERT(m_data && pos < m_dataSize);
      return m_data[pos];
    }
    void getBytes(OdUInt32 pos, OdUInt8* dst, OdUInt32 size) const
    {
      ODA_ASSERT(m_data && pos + size <= m_dataSize);
      ::memcpy(dst, m_data + pos, size);
    }
    void putByte(OdUInt32 pos, OdUInt8 val)
    {
      ODA_ASSERT(m_data);
      m_data[pos] = val;
      if (pos >= m_dataSize)
        m_dataSize = pos + 1;
    }
    void putBytes(OdUInt32 pos, const OdUInt8* src, OdUInt32 size)
    {
      OdUInt32 newSize = pos + size;
      ODA_ASSERT(m_data);
      ::memcpy(m_data + pos, src, size);
      if (newSize > m_dataSize)
        m_dataSize = newSize;
    }

    OdUInt8* data()
    {
      return m_data;
    }
    void allocData(OdUInt64 size)
    {
      ODA_ASSERT(size >> 32 == 0);
      m_data = (OdUInt8*)::odrxAlloc((OdUInt32)size);
      if (!m_data)
        throw OdError(eOutOfMemory);
    }
    void freeData()
    {
      if (m_data)
      {
        ::odrxFree(m_data);
        m_data = 0;
      }
// ODA_MT_DBIO_BEGIN
      m_dataLock = 0;
// ODA_MT_DBIO_END
    }

// ODA_MT_DBIO_BEGIN
    void setData(OdUInt8* pdata)
    {
      ODA_ASSERT(!m_data);
      m_data = pdata;
    }
// ODA_MT_DBIO_END
  };
  typedef OdArray<Page> OdPageArray;
  typedef OdArray<Page>::iterator OdPageArrayIterator;
  //typedef OdLinkedArray<Page> OdPageArray;
  //typedef OdLinkedArray<Page>::iterator OdPageArrayIterator;

  bool isPageFull(Page* pPage) const
  {
    return pPage->m_dataSize == m_pageSize;
  }

// ODA_MT_DBIO_BEGIN
  OdMutexArray m_pageLocks;
  void createPageLocks()
  {
    ODA_ASSERT(m_pageLocks.size()==0);
    unsigned psize = m_pages.size();
    m_pageLocks.resize(psize);
    for (unsigned i = 0; i < psize; ++i)
    {
      m_pages[i].m_dataLock = &m_pageLocks[i];
    }
  }
  OdPageArray& pages() { return m_pages; }
  void getPage(Page& page, OdBinaryData& pageData, OdDwgR18Compressor& cmpr);
// ODA_MT_DBIO_END

  void getPageDataByPageId(OdUInt32 pageId, OdBinaryData& pageData);
  void setMinmalMemoryMode(bool m) { m_bMinmalMemoryMode = m; }
protected:
  OdPageArray m_pages;

private:
  bool m_bMinmalMemoryMode;
  OdPageArrayIterator m_curPage; 
  OdUInt32 m_curPosInPage;
  inline OdUInt64 curPos();

  inline void nextPageR();
  inline void nextPageW();
  inline void getPage();
  inline void putPage();

  OdDwgR18FileController* m_pController;
};

typedef OdSmartPtr<OdDwgR18PagedStream> OdDwgR18PagedStreamPtr;

//----------------------------------------------------------
//
// OdDwgR18FileSection
//
//----------------------------------------------------------
class OdDwgR18FileSection;
typedef OdSmartPtr<OdDwgR18FileSection> OdDwgR18FileSectionPtr;

class DBIO_EXPORT OdDwgR18FileSection : public OdDwgR18PagedStream
{
public:
  static OdDwgR18FileSectionPtr create(OdDwgR18FileController* pController)
  {
    OdDwgR18FileSectionPtr pSec = OdRxObjectImpl<OdDwgR18FileSection>::createObject();
    pSec->setController(pController);
    return pSec;
  }

  OdDwgR18FileSection()
  {}

  void read(OdStreamBuf* pStream);
  void write(OdStreamBuf* pStream);

  void registerSectionPagesAsGaps();

  OdUInt32 collectDataFromAllPages(OdArray<OdBinaryData>& binDataArray);

  OdString m_secName;
};

//----------------------------------------------------------
//
// Inline methods
//
//----------------------------------------------------------
inline
OdUInt32 alignSize(OdUInt32 len, OdUInt32 step)
{
  ODA_ASSERT(len && step);
  return (step-1) - (len-1)%step;
}

inline
OdUInt64 alignPageStart(OdStreamBufPtr pStream, OdUInt32 len, const OdBinaryData& stub
#ifdef _DEBUG
, bool skipStreamPosChecking
#endif
)
{ 
#ifdef _DEBUG
  ODA_ASSERT_ONCE( (!skipStreamPosChecking) ? (pStream->length() == pStream->tell()) 
                                            : true); // warning about writing in pre-allocated stream
#endif

  OdUInt32 nStub = OdUInt32(pStream->tell() % len);
  if (nStub)
  {
    nStub = len - nStub;
    ODA_ASSERT(nStub <= stub.size());
    pStream->putBytes(stub.asArrayPtr(), nStub);
  }
  return pStream->tell();
}

//----------------------------------------------------------
//
// OdDwgR21PagedStream inline methods
//
//----------------------------------------------------------
inline
OdUInt64 OdDwgR18PagedStream::curPos()
{ 
  ODA_ASSERT(m_curPage != m_pages.end());
  return m_curPage->m_dataOffset + m_curPosInPage;
}

inline
void OdDwgR18PagedStream::nextPageR()
{
  ODA_ASSERT(m_pages.size() && m_curPage != m_pages.end());
  ++m_curPage;
  m_curPosInPage = 0;
}

inline
void OdDwgR18PagedStream::nextPageW()
{
  ODA_ASSERT(m_curPage == m_pages.end());
  OdUInt64 dataOffset = 0;
  if ( m_pages.size() )
  {
    dataOffset = m_pages.last().m_dataOffset + m_pageSize;
  }
  m_curPage = m_pages.append();
  ODA_ASSERT(!m_curPage->data());
  m_curPage->allocData(m_pageSize);
  m_curPage->m_dataOffset = dataOffset;
  m_curPosInPage = 0;
}

#endif // _OD_DWGR18PAGEDSTREAM_H_INCLUDED_
