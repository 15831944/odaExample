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


#ifndef _OD_DSFILESEGMENTS_H_INCLUDED_
#define _OD_DSFILESEGMENTS_H_INCLUDED_


#include "RxObject.h"
#include "DbFiler.h"
#include "UInt32Array.h"

#define SEGMENT_HEADER_SIZE 0x30
#define SEGMENT_ALIGN_SIZE 0x40
#define SEGMENT_PART_ALIGN_SIZE 0x10

namespace OdTvDs
{
  //----------------------------------------------------------
  //
  // FileSegment
  // The base class of the DS file segment classes
  //
  //----------------------------------------------------------
  class FileSegment
  {
  public:
    class Header
    {
    public:
      Header()
        : m_Signature((OdUInt16)0xd5ac)
        , m_SegmentIndex(0)
        , m_Unknown1(0)
        , m_SegmentSize(0)
        , m_Unknown2(0)
        , m_DsRevision(1)
        , m_Unknown3(0)
        , m_SysDataAlignOffset(0)
        , m_ObjDataAlignOffset(0)
      {
        ::memset(m_Name, 0, 7);
      }
      void read(OdTvDbDwgFiler* pFiler)
      {
        m_Signature = pFiler->rdInt16(); ODA_ASSERT(m_Signature == (OdUInt16)0xd5ac);
        pFiler->rdBytes(m_Name, 6); m_Name[6] = 0;
        m_SegmentIndex = pFiler->rdInt32();
        m_Unknown1 = pFiler->rdInt32(); ODA_ASSERT(m_Unknown1 == 0 || m_Unknown1 == 1); // 1 in 'blob01' segment
        m_SegmentSize = pFiler->rdInt32();
        m_Unknown2 = pFiler->rdInt32(); ODA_ASSERT(m_Unknown2 == 0);
        m_DsRevision = pFiler->rdInt32();
        m_Unknown3 = pFiler->rdInt32(); ODA_ASSERT(m_Unknown3 == 0);
        m_SysDataAlignOffset = pFiler->rdInt32();
        m_ObjDataAlignOffset = pFiler->rdInt32();

        OdUInt8 alignBytes[8];
        pFiler->rdBytes(alignBytes, 8);
#if _DEBUG
        OdUInt8 dbgAlignBytes[8];
        ::memset(dbgAlignBytes, 0x55, 8);
        ODA_ASSERT(!::memcmp(alignBytes, dbgAlignBytes, 8));
#endif
      }

      void write(OdTvDbDwgFiler* pFiler)
      {
        pFiler->wrInt16(m_Signature);
        pFiler->wrBytes(m_Name, 6);
        pFiler->wrInt32(m_SegmentIndex);
        pFiler->wrInt32(m_Unknown1);
        if (m_Unknown1 == 1)
          pFiler->wrInt32(SEGMENT_HEADER_SIZE); // 'blob01' segment
        else
          pFiler->wrInt32(m_SegmentSize);
        pFiler->wrInt32(m_Unknown2);
        pFiler->wrInt32(m_DsRevision);
        pFiler->wrInt32(m_Unknown3);
        pFiler->wrInt32(m_SysDataAlignOffset);
        pFiler->wrInt32(m_ObjDataAlignOffset);

        pFiler->wrBytes(m_hdrAlignBytes, 8);
      }

      OdUInt64 sysDataLocalOffset() const
      {
        return ((static_cast<OdUInt64>(m_SysDataAlignOffset)) << 4);
      }
      OdUInt64 objDataLocalOffset() const
      {
        return ((static_cast<OdUInt64>(m_ObjDataAlignOffset)) << 4);
      }
      void setSysDataLocalOffset(OdUInt32 val)
      {
        ODA_ASSERT((val&0xf)==0);
        m_SysDataAlignOffset = val >> 4;
      }
      void setObjDataLocalOffset(OdUInt32 val)
      {
        ODA_ASSERT((val&0xf)==0);
        m_ObjDataAlignOffset = val >> 4;
      }

      OdUInt16 m_Signature;
      OdUInt8 m_Name[7];
      OdInt32 m_SegmentIndex;
      OdInt32 m_Unknown1;
      OdInt32 m_SegmentSize;
      OdInt32 m_Unknown2;
      OdInt32 m_DsRevision;
      OdInt32 m_Unknown3;
      OdInt32 m_SysDataAlignOffset;
      OdInt32 m_ObjDataAlignOffset;
    };

    static const OdUInt8 m_hdrAlignBytes[SEGMENT_HEADER_SIZE];
    static const OdUInt8 m_segAlignBytes[SEGMENT_ALIGN_SIZE];
    static const OdUInt8 m_segPartAlignBytes[SEGMENT_PART_ALIGN_SIZE];
    static const OdUInt8 m_segDataPartAlignBytes[SEGMENT_PART_ALIGN_SIZE];

    FileSegment()
      : m_startOffset(0)
    {}
    FileSegment(const OdUInt8 segName[7])
      : m_startOffset(0)
    {
      ::memcpy(m_Header.m_Name, segName, 7);
    }
    virtual ~FileSegment()
    {}

    void setSegmentIndex(OdUInt32 val)
    {
      m_Header.m_SegmentIndex = val;
    }
    OdUInt32 getSegmentIndex()
    {
      return m_Header.m_SegmentIndex;
    }

    static OdUInt32 alignSize(OdUInt32 len, OdUInt32 step)
    {
      ODA_ASSERT(len && step);
      return (step-1) - (len-1)%step;
    }
  //protected:
    Header m_Header;
    OdUInt64 m_startOffset;

    OdUInt64 hdrDataOffset() const
    {
      return m_startOffset + SEGMENT_HEADER_SIZE; // skip segment header
    }
    OdUInt64 sysDataOffset() const
    {
      return m_startOffset + m_Header.sysDataLocalOffset();
    }
    OdUInt64 objDataOffset() const
    {
      return m_startOffset + m_Header.objDataLocalOffset();
    }
    void setSysDataOffset(OdUInt64 val)
    {
      ODA_ASSERT(val > m_startOffset);
      m_Header.setSysDataLocalOffset(val - m_startOffset);
    }
    void setObjDataOffset(OdUInt64 val)
    {
      ODA_ASSERT(val > m_startOffset);
      m_Header.setObjDataLocalOffset(val - m_startOffset);
    }

    void beginReading(OdTvDbDwgFiler* pFiler)
    {
      m_startOffset = pFiler->tell();
      m_Header.read(pFiler);
      ODA_ASSERT((pFiler->tell() - m_startOffset) == SEGMENT_HEADER_SIZE);
    }

    void beginWriting(OdTvDbDwgFiler* pFiler)
    {
      m_startOffset = pFiler->tell();
      ODA_ASSERT(m_startOffset%0x10==0);
      // Reserve place for header data
      pFiler->wrBytes(m_hdrAlignBytes, SEGMENT_HEADER_SIZE);
    }

    void endWriting(OdTvDbDwgFiler* pFiler)
    {
      OdUInt32 segSize = pFiler->tell() - m_startOffset;
      OdUInt32 segAlignSize = alignSize(segSize, SEGMENT_ALIGN_SIZE);
      m_Header.m_SegmentSize = segSize + segAlignSize;
      // Write align bytes of segment page
      pFiler->wrBytes(m_segAlignBytes, segAlignSize);

      OdUInt64 endPos = pFiler->tell();
      pFiler->seek(m_startOffset, OdDb::kSeekFromStart);
      m_Header.write(pFiler);
      pFiler->seek(endPos, OdDb::kSeekFromStart);
    }
  };

  //----------------------------------------------------------
  //
  // SegIdxSegment
  // The "segidx" segment
  //
  //----------------------------------------------------------
  class SegIdxSegment : public FileSegment
  {
  public:
    class Entry
    {
    public:
      Entry()
        : m_Offset(0)
        , m_Size(0)
      {}
      Entry(OdUInt64 offset, OdUInt32 size)
        : m_Offset(offset)
        , m_Size(size)
      {}
      void read(OdTvDbDwgFiler* pFiler)
      {
        m_Offset = pFiler->rdInt64();
        m_Size = pFiler->rdInt32();
      }
      void write(OdTvDbDwgFiler* pFiler)
      {
        pFiler->wrInt64(m_Offset);
        pFiler->wrInt32(m_Size);
      }
      OdUInt64 m_Offset;
      OdUInt32 m_Size;
    };

    static const OdUInt8 Name[7];

    SegIdxSegment() 
      : FileSegment(Name)
    {}

    void setSize(unsigned newSize)
    {
      m_entries.resize(newSize);
    };

    void read(OdTvDbDwgFiler* pFiler)
    {
      beginReading(pFiler);

      for (unsigned i = 0; i < m_entries.size(); ++i)
      {
        m_entries[i].read(pFiler);
      }
    }

    void write(OdTvDbDwgFiler* pFiler)
    {
      beginWriting(pFiler);
      
      for (unsigned i = 0; i < m_entries.size(); ++i)
      {
        m_entries[i].write(pFiler);
      }

      endWriting(pFiler);
    }

    OdArray<Entry> m_entries;
  };

}

#endif // _OD_DSFILESEGMENTS_H_INCLUDED_
