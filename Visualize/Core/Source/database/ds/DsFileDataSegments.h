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


#ifndef _OD_DSFILEDATASEGMENT_H_INCLUDED_
#define _OD_DSFILEDATASEGMENT_H_INCLUDED_


#include "RxObject.h"
#include "DbFiler.h"
#include "UInt32Array.h"
#include "DsFileSegments.h"

#define DATA_SEGMENT_ENTRY_HDR_SIZE 0x14
#define BLOB_SEGMENT_PAGE_SIZE 0x0fffb0

namespace OdTvDs
{
  //----------------------------------------------------------
  //
  // DatIdxSegment
  // The "datidx" segment
  //
  //----------------------------------------------------------
  class DatIdxSegment : public FileSegment
  {
  public:
    static const OdUInt8 Name[7];
    DatIdxSegment() 
      : FileSegment(Name)
    {}

    class Entry
    {
    public:
      Entry()
        : m_SegmentIndex(0)
        , m_LocalOffset(0)
        , m_SchemaIndex(0)
      {}
      Entry(OdUInt32 segmentIndex, OdUInt32 localOffset, OdUInt32 schemaIndex)
        : m_SegmentIndex(segmentIndex)
        , m_LocalOffset(localOffset)
        , m_SchemaIndex(schemaIndex)
      {}
      void read(OdTvDbDwgFiler* pFiler)
      {
        m_SegmentIndex = pFiler->rdInt32();
        m_LocalOffset = pFiler->rdInt32();
        m_SchemaIndex = pFiler->rdInt32();
      }
      void write(OdTvDbDwgFiler* pFiler)
      {
        pFiler->wrInt32(m_SegmentIndex);
        pFiler->wrInt32(m_LocalOffset);
        pFiler->wrInt32(m_SchemaIndex);
      }
      OdUInt32 m_SegmentIndex;
      OdUInt32 m_LocalOffset;
      OdUInt32 m_SchemaIndex;
    };

    void read(OdTvDbDwgFiler* pFiler);
    void write(OdTvDbDwgFiler* pFiler);

    typedef std::map<OdUInt32, OdUInt32Array> EntriesMap;
    void getSegmentEntryMap(EntriesMap& entriesMap) const;

    const Entry& getEntry(OdUInt32 index) const
    {
      return m_entries.getAt(index);
    }

    void addEntry(OdUInt32 segmentIndex, OdUInt32 localOffset, OdUInt32 schemaIndex)
    {
      m_entries.push_back(Entry(segmentIndex, localOffset, schemaIndex));
    }

  private:
    OdArray<Entry> m_entries;
  };

  //----------------------------------------------------------
  //
  // DataBlobEntryReference
  //
  //----------------------------------------------------------
  class DataBlobEntryReference
  {
  public:
    DataBlobEntryReference()
      : m_allDataSize(0)
      , m_pagesCount(1)
      , m_pageSize(0)
      , m_lastPageSize(0)
    {}
    DataBlobEntryReference(OdTvDbDwgFiler* pFiler)
    {
      read(pFiler);
    }
    void read(OdTvDbDwgFiler* pFiler)
    {
      OdUInt32 startOffset = pFiler->tell();

      m_allDataSize = pFiler->rdInt64();
      m_pagesCount = pFiler->rdInt32();
      OdUInt32 recordSize = pFiler->rdInt32();
      m_pageSize = pFiler->rdInt32();
      m_lastPageSize = pFiler->rdInt32();
      OdUInt32 unk1 = pFiler->rdInt32(); ODA_ASSERT(unk1 == 0);
      OdUInt32 unk2 = pFiler->rdInt32(); ODA_ASSERT(unk2 == 0);
      m_pages.reserve(m_pagesCount);
      for (unsigned i = 0; i < m_pagesCount; ++i)
      {
        m_pages.push_back(PageInfo(pFiler));
      }

      ODA_ASSERT(recordSize == (pFiler->tell() - startOffset));
    }
    void write(OdTvDbDwgFiler* pFiler)
    {
      OdUInt32 startOffset = pFiler->tell();

      pFiler->wrInt64(m_allDataSize);
      pFiler->wrInt32(m_pagesCount);
      OdUInt32 recordSize = 32 + m_pages.size()* 8;
      pFiler->wrInt32(recordSize);
      pFiler->wrInt32(m_pageSize);
      pFiler->wrInt32(m_lastPageSize);
      pFiler->wrInt32(0); // unknown
      pFiler->wrInt32(0); // unknown
      for (unsigned i = 0; i < m_pagesCount; ++i)
      {
        m_pages[i].write(pFiler);
      }

      ODA_ASSERT(recordSize == (pFiler->tell() - startOffset));
    }

    void setDataSize(OdUInt64 allDataSize)
    {
      m_allDataSize = allDataSize;
      m_pagesCount = (m_allDataSize >= BLOB_SEGMENT_PAGE_SIZE) ? m_allDataSize / BLOB_SEGMENT_PAGE_SIZE : 1;
      if (m_pagesCount == 1)
      {
        m_pageSize = m_allDataSize;
        m_lastPageSize = m_allDataSize;
      }
      else
      {
        m_pageSize = BLOB_SEGMENT_PAGE_SIZE;
        m_lastPageSize = m_allDataSize - BLOB_SEGMENT_PAGE_SIZE * (m_pagesCount - 1);
      }
    }

    OdUInt64 m_allDataSize;
    OdUInt32 m_pagesCount;
    OdUInt32 m_pageSize;
    OdUInt32 m_lastPageSize;

    class PageInfo
    {
    public:
      PageInfo()
        : m_segIndex(0)
        , m_size(0)
      {}
      PageInfo(OdUInt32 segIndex, OdUInt32 size)
        : m_segIndex(segIndex)
        , m_size(size)
      {}
      PageInfo(OdTvDbDwgFiler* pFiler)
      {
        read(pFiler);
      }

      void read(OdTvDbDwgFiler* pFiler)
      {
        m_segIndex = pFiler->rdInt32();
        m_size = pFiler->rdInt32();
      }
      void write(OdTvDbDwgFiler* pFiler)
      {
        pFiler->wrInt32(m_segIndex);
        pFiler->wrInt32(m_size);
      }

      OdUInt32 m_segIndex;
      OdUInt32 m_size;
    };
    OdArray<PageInfo> m_pages;
  };

  //----------------------------------------------------------
  //
  // DataRecordHeader
  //
  //----------------------------------------------------------
  class DataRecordHeader
  {
  private:
    OdUInt64 m_Handle;
    OdUInt32 m_LocalOffset;
    OdUInt32 m_OffsetType;
  public:
    enum
    {
      kInvalid        = 0,
      kStreamOffset   = 1,
      kDataRecIndex   = 2,
      kBlobRecIndex   = 3,
    };

    static const OdUInt32 Size; // = 0x14

    DataRecordHeader()
      : m_Handle(0)
      , m_LocalOffset(0)
      , m_OffsetType(0)
    {}

    DataRecordHeader(const OdUInt64& h, OdUInt32 recIndex, bool isData)
      : m_Handle(h)
      , m_LocalOffset(recIndex)
      , m_OffsetType(isData ? kDataRecIndex : kBlobRecIndex)
    {}

    DataRecordHeader(OdTvDbDwgFiler* pFiler)
    {
      read(pFiler);
    }

    void setHandle(OdUInt64 val) { m_Handle = val; }
    OdUInt64 getHandle() const { return m_Handle; }

    OdUInt32 getLocalOffset() const { ODA_ASSERT(m_OffsetType==kStreamOffset); return m_LocalOffset; }
    void setLocalOffset(OdUInt32 val)
    {
      m_LocalOffset = val;
      m_OffsetType = kStreamOffset;
    }

    OdUInt32 getIndex() const { ODA_ASSERT(m_OffsetType>kStreamOffset); return m_LocalOffset; }
    void setIndex(OdUInt32 val, bool isData)
    {
      m_LocalOffset = val;
      m_OffsetType = isData ? kDataRecIndex : kBlobRecIndex;
    }

    OdUInt32 getOffsetType() const { return m_OffsetType; }

    OdResult read(OdTvDbDwgFiler* pFiler)
    {
      OdUInt32 entrySize = pFiler->rdInt32();
      if (entrySize != Size)
      {
        ODA_FAIL_ONCE();
        m_Handle = 0;
        m_LocalOffset = 0;
        m_OffsetType = kInvalid;
        return eInvalidInput;
      }
      OdUInt32 unknown = pFiler->rdInt32(); ODA_ASSERT(unknown == 1); // (?) counter
      m_Handle = pFiler->rdInt64();
      m_LocalOffset = pFiler->rdInt32();
      m_OffsetType = kStreamOffset;
      return eOk;
    }

    void write(OdTvDbDwgFiler* pFiler)
    {
      pFiler->wrInt32(Size);
      pFiler->wrInt32(1); // (?) counter
      pFiler->wrInt64(m_Handle);
      ODA_ASSERT(m_OffsetType == kStreamOffset);
      pFiler->wrInt32(m_LocalOffset);
    }
  };

  //----------------------------------------------------------
  //
  // DataSegment
  // The "_data_" segment
  //
  //----------------------------------------------------------
  class FileController;

  class DataSegment : public FileSegment
  {
  public:
    static const OdUInt8 Name[7];
    DataSegment()
      : FileSegment(Name)
    {}
    DataSegment(OdUInt32 recordsCount)
      : FileSegment(Name)
    {
      m_entries.reserve(recordsCount);
      m_dataRecs.reserve(recordsCount);
    }

    void read(OdTvDbDwgFiler* pFiler, FileController* pFileController, const OdUInt32Array& entryIndexes);
    void write(OdTvDbDwgFiler* pFiler);
    void readRecordData(OdTvDbDwgFiler* pFiler, OdUInt32 entryIndex, OdUInt32 maxRawSize, FileController* pFileController, const OdUInt32Array& entryIndexes);

    void addDataRecord(const OdDbHandle& handle, const OdBinaryData& binData)
    {
      m_entries.push_back(DataRecordHeader(handle, m_dataRecs.size(), true));
      m_dataRecs.push_back(binData);
    }
    void addDataRecord(const OdDbHandle& handle, OdStreamBufPtr& pBinData)
    {
      m_entries.push_back(DataRecordHeader(handle, m_dataRecs.size(), true));
      m_dataRecs.resize(m_dataRecs.size() + 1);
      OdBinaryData& dataRec = m_dataRecs.last();
      dataRec.resize(pBinData->length());
      pBinData->getBytes(dataRec.asArrayPtr(), dataRec.size());
    }
    void addBlobRefRecord(const OdDbHandle& handle, const DataBlobEntryReference& blobRef)
    {
      m_entries.push_back(DataRecordHeader(handle, m_blobRefs.size(), false));
      m_blobRefs.push_back(blobRef);
    }

    void setRecHdrOffsets(OdUInt32Array& hdrOffsets) { m_hdrOffsets = hdrOffsets; }
    OdUInt32Array& recHdrOffsets() { return m_hdrOffsets; }

  //private:
    OdArray<DataRecordHeader> m_entries;
    OdArray<OdBinaryData> m_dataRecs;
    OdArray<DataBlobEntryReference> m_blobRefs;

  private:
    OdUInt32Array m_hdrOffsets;
  };

  //----------------------------------------------------------
  //
  // Blob01Segment
  // The "blob01" segment
  //
  //----------------------------------------------------------
  class Blob01Segment : public FileSegment
  {
  public:
    static const OdUInt8 Name[7];

    Blob01Segment() 
      : FileSegment(Name)
      , m_AllDataSize(0)
      , m_PageStartOffset(0)
      , m_PageIndex(0)
      , m_PagesCount(0)
      , m_PageDataSize(0)
    {
      m_Header.m_Unknown1 = 1;
    }

    void read(OdTvDbDwgFiler* pFiler);
    void write(OdTvDbDwgFiler* pFiler);
    void write(OdTvDbDwgFiler* pFiler, const OdUInt8* pData, OdUInt32 dataSize);

    OdUInt64 m_AllDataSize;
    OdUInt64 m_PageStartOffset;
    OdUInt32 m_PageIndex;
    OdUInt32 m_PagesCount;
    OdUInt64 m_PageDataSize;
    OdBinaryData m_binData;
  };
}

#endif // _OD_DSFILEDATASEGMENT_H_INCLUDED_
