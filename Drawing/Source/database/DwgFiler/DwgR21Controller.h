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


#ifndef _OD_DWGR21CONTROLLER_H_INCLUDED_
#define _OD_DWGR21CONTROLLER_H_INCLUDED_

#include "OdPlatform.h"
#include "OdBinaryData.h"
#include "DbSecurity.h"
#include "RxObject.h"
#include "FlatMemStream.h"
#include "RxDictionary.h"
#include "RxObjectImpl.h"
#include "OdPlatformStreamer.h"
#include "DwgDumpUtils.h"
#include "DwgR21Compressor.h"
#include "DwgR21PagedStream.h"
#include "DwgFileController.h"

class OdDwgR21FileController;

//----------------------------------------------------------
//
// OdDwgR21FileSection
//
//----------------------------------------------------------
class OdDwgR21FileSection;
typedef OdSmartPtr<OdDwgR21FileSection> OdDwgR21FileSectionPtr;

class OdDwgR21FileSection : public OdDwgR21PagedStream
{
public:
  static OdDwgR21FileSectionPtr create(OdDwgR21FileController* pController)
  {
    OdDwgR21FileSectionPtr pSec = OdRxObjectImpl<OdDwgR21FileSection>::createObject();
    pSec->setController(pController);
    return pSec;
  }

  OdDwgR21FileSection()
    : m_hashCode(0)
    , m_unknown6(0)
  {}

  void read(OdStreamBuf* pStream);
  void write(OdStreamBuf* pStream);

  OdUInt64 m_hashCode;
  OdUInt64 m_unknown6;
  OdString m_secName;
};

//----------------------------------------------------------
//
// OdDwgR21FileHeader
//
//----------------------------------------------------------
class OdDwgR21FileHeader
{
public:
  OdDwgR21FileHeader ()
    : m_headerSize(0x70)
    , m_fileSize(0)
    , m_pagesMapCrcCompr(0)
    , m_pagesMapFactor(0)
    , m_pagesMap2Offset(0)
    , m_pagesMap2Id(0)
    , m_pagesMapOffset(0)
    , m_pagesMapId(0)
    , m_header2Offset(0)
    , m_pagesMapSizeCompr(0)
    , m_pagesMapSizeSrc(0)
    , m_pagesAmount(0)
    , m_pagesMaxId(0)
    , m_Unknown15(0x20)
    , m_Unknown16(0x40)
    , m_pagesMapCrcSrc(0)
    , m_Unknown18(0xf800)
    , m_Unknown19(4)
    , m_Unknown20(1)
    , m_sectionsAmount(0)
    , m_sectionsMapCrcSrc(0)
    , m_sectionsMapSizeCompr(0)
    , m_sectionsMap2Id(0)
    , m_sectionsMapId(0)
    , m_sectionsMapSizeSrc(0)
    , m_sectionsMapCrcCompr(0)
    , m_sectionsMapFactor(0)
    , m_streamVersion(0x60100)
    , m_crcSeed(0)
    , m_crcSeedEncoded(0)
    , m_randomSeed(0)
    , m_headerCrc64(0)
  {
    m_pagesMapCrcSeed = m_crcSeed;
    m_sectionsMapCrcSeed = m_crcSeed;
  }

  static const int OFFSET;      // 0x80  - Offset of the file header page
  static const int DDPAGE_SIZE; // 0x400 - Size of the file header page
  static const int SIZE_BETA;   // 0xe8  - Size of decoded file header data
  static const int SIZE;        // 0x110 - Size of decoded file header data

  void readBeta(OdBinaryData& data);
  void read(OdBinaryData& data);
  void write(OdBinaryData& data);

  OdUInt64  m_headerSize;
  OdUInt64  m_fileSize;
  OdUInt64  m_pagesMapCrcCompr;
  OdUInt64  m_pagesMapFactor;
  OdUInt64  m_pagesMapCrcSeed;
  OdUInt64  m_pagesMap2Offset;
  OdUInt64  m_pagesMap2Id;
  OdUInt64  m_pagesMapOffset;
  OdUInt64  m_pagesMapId;
  OdUInt64  m_header2Offset;
  OdUInt64  m_pagesMapSizeCompr;
  OdUInt64  m_pagesMapSizeSrc;
  OdUInt64  m_pagesAmount;
  OdUInt64  m_pagesMaxId;
  OdUInt64  m_Unknown15;
  OdUInt64  m_Unknown16;
  OdUInt64  m_pagesMapCrcSrc;
  OdUInt64  m_Unknown18;
  OdUInt64  m_Unknown19;
  OdUInt64  m_Unknown20;
  OdUInt64  m_sectionsAmount;
  OdUInt64  m_sectionsMapCrcSrc;
  OdUInt64  m_sectionsMapSizeCompr;
  OdUInt64  m_sectionsMap2Id;
  OdUInt64  m_sectionsMapId;
  OdUInt64  m_sectionsMapSizeSrc;
  OdUInt64  m_sectionsMapCrcCompr;
  OdUInt64  m_sectionsMapFactor;
  OdUInt64  m_sectionsMapCrcSeed;
  OdUInt64  m_streamVersion;
  OdUInt64  m_crcSeed;
  OdUInt64  m_crcSeedEncoded;
  OdUInt64  m_randomSeed;
  OdUInt64  m_headerCrc64;
};

//----------------------------------------------------------
//
// OdDwgR21Random
//
//----------------------------------------------------------
class OdDwgR21Random
{
public:
  OdDwgR21Random()
    : _count(0)
    , _seed(0)
  {
    memset(_data, 0, sizeof(_data));
    memset(_data1, 0, sizeof(_data1));
  }

  void generate();
  void generate(OdUInt64 seed);
  void update();
  void generate1();

  OdUInt64 get()
  {
    _count += 2;
    if (_count >= 0x270)
      update();

    OdUInt32 low = _data[_count];
    OdUInt32 hi = _data[_count+1];
    odSwap4BytesNumber(low);
    odSwap4BytesNumber(hi);
    return OdUInt64(low) | (OdUInt64(hi) << 32);
  }

  OdUInt8* data() { return (OdUInt8*)_data1; }
  OdUInt32 dataSize() { return 0x80 * sizeof(OdUInt32); }

  OdUInt64 encode(OdUInt32 val)
  {
    OdUInt64 rand = get();
    OdUInt32 mask0 = rand & 0x0DF7DF7DF;
    OdUInt32 mask1 = (rand >> 32) & 0x0F7DF7DF7;
    if (val & 0x200) mask0 |= 0x20;
    if (val & 0x100) mask0 |= 0x800;
    if (val & 0x80 ) mask0 |= 0x20000;
    if (val & 0x40 ) mask0 |= 0x800000;
    if (val & 0x20 ) mask0 |= 0x20000000;
    if (val & 0x10 ) mask1 |= 0x8;
    if (val & 0x8  ) mask1 |= 0x200;
    if (val & 0x4  ) mask1 |= 0x8000;
    if (val & 0x2  ) mask1 |= 0x200000;
    if (val & 0x1  ) mask1 |= 0x8000000;
    return OdUInt64(mask0) | (OdUInt64(mask1) << 32);
  }

  OdUInt64 decode(OdUInt64 val)
  {
    OdUInt32 res = 0;
    OdUInt32 mask = val >> 32;
    if (mask & 0x8000000 ) res |= 0x1;
    if (mask & 0x200000  ) res |= 0x2;
    if (mask & 0x8000    ) res |= 0x4;
    if (mask & 0x200     ) res |= 0x8;
    if (mask & 0x8       ) res |= 0x10;
    mask = val;             
    if (mask & 0x20000000) res |= 0x20;
    if (mask & 0x800000  ) res |= 0x40;
    if (mask & 0x20000   ) res |= 0x80;
    if (mask & 0x800     ) res |= 0x100;
    if (mask & 0x20      ) res |= 0x200;
    return res;
  }

  OdUInt64 seed() const { return _seed; };

private:
  OdUInt64 _seed;
  OdUInt32 _count;
  OdUInt32 _data[0x270];
  OdUInt32 _data1[0x80];
};

//----------------------------------------------------------
//
// OdDwgR21FileController
//
//----------------------------------------------------------
class OdDwgR21FileController : public OdDwgFileSecurity
{
public:
  OdDwgR21FileController();

  OdDb::DwgVersion m_dwgVersion;
  OdDb::MaintReleaseVer m_MaintRelease;

  void loadHeaderPage();
  void writeHeaderPage();

  OdBinaryData& loadSysPage(
      OdUInt32 fileOffset
    , OdUInt64 sizeCompr
    , OdUInt64 sizeSrc
    , OdUInt64 crcCompr
    , OdUInt64 crcSrc 
    , OdUInt64 factor
    , OdUInt64 crcSeed
    );
  OdBinaryData& writeSysPage(
      OdStreamBuf* pSrcStream
    , OdUInt64 filePageSize
    , OdUInt64& sizeCompr
    , OdUInt64& sizeSrc
    , OdUInt64& crcCompr
    , OdUInt64& crcSrc
    , OdUInt64& factor
    , OdUInt64 crcSeed
    );
  inline OdUInt64 sysPageSize(OdUInt64 sizeSrc);


  virtual OdStreamBufPtr rawStream() { return m_pRawStream; }

  OdDwgR21Compressor m_cmpr;

  // Reed-Solomon encoder
  OdRSCoder m_rsSys;
  OdRSCoder m_rsData;

  // Local caches - ??? TODO stack of caches
  OdBinaryData m_buff1;
  OdBinaryData m_buff2;

  // Random sequence
  OdDwgR21Random m_random;

// ODA_MT_DBIO_BEGIN
  OdMutex m_rawStreamLock;
// ODA_MT_DBIO_END

  OdUInt64 streamVersion() { return m_header.m_streamVersion; }
  OdUInt64 crcSeed() { return m_header.m_crcSeed; }

  // The methods provide access to PagesMap
  inline OdUInt64 pageOffset(OdInt64 pageId);
  inline OdUInt64 pageSize(OdInt64 pageId);

  OdUInt64 putPage(OdBinaryData& data);
protected:
  class Page
  {
  public:
    Page(OdInt64 id, OdUInt64 offset, OdUInt64 size)
      : m_id(id)
      , m_offset(offset)
      , m_size(size)
    {}

    Page() // required on SGI
      : m_id(0)
      , m_offset(0)
      , m_size(0)
    {}

    OdInt64  m_id;
    OdUInt64 m_offset;
    OdUInt64 m_size;

    static inline OdUInt64 toFileOffset(OdUInt64 mapOffset) { return mapOffset + (OdDwgR21FileHeader::OFFSET + OdDwgR21FileHeader::DDPAGE_SIZE); }
    static inline OdUInt64 toMapOffset(OdUInt64 fileOffset) { return fileOffset - (OdDwgR21FileHeader::OFFSET + OdDwgR21FileHeader::DDPAGE_SIZE); }
    static inline OdUInt64 alignSize(OdUInt64 pageSize) { return (pageSize + 0x20 - 1) & (OdInt64)(-0x20); }
  };
  OdDwgR21FileHeader  m_header;
  OdArray<Page>       m_pages;
  OdRxDictionaryPtr   m_sections;

  OdStreamBufPtr m_pRawStream;

  OdUInt32 m_crcSeed;
};

//----------------------------------------------------------
//
// Inline methods
//
//----------------------------------------------------------
inline OdUInt64 OdDwgR21FileController::pageOffset(OdInt64 pageId)
{
  return Page::toFileOffset(m_pages[pageId].m_offset);
}

inline OdUInt64 OdDwgR21FileController::pageSize(OdInt64 pageId)
{
  return m_pages[pageId].m_size;
}

inline OdUInt64 OdDwgR21FileController::sysPageSize(OdUInt64 sizeSrc)
{
  OdUInt64 alignedSize = (sizeSrc + R21_CRC_BLOCK_SIZE - 1) & (OdInt64)(-R21_CRC_BLOCK_SIZE);
  OdUInt32 blockSize = m_rsSys.dsize();
  OdUInt64 filePageSize = (alignedSize * 2 + blockSize - 1) / blockSize * R21_RS_BLOCK_SIZE;
  if (filePageSize < 0x400)
  {
    filePageSize = 0x400;
  }
  else
  {
    filePageSize = Page::alignSize(filePageSize);
  }
  return filePageSize;
}

#endif // _OD_DWGR21CONTROLLER_H_INCLUDED_
