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


#ifndef _OD_DSFILESCHEMASEGMENT_H_INCLUDED_
#define _OD_DSFILESCHEMASEGMENT_H_INCLUDED_


#include "RxObject.h"
#include "DbFiler.h"
#include "UInt32Array.h"
#include "UInt64Array.h"
#include "DsFileSegments.h"
#include "DsSchema.h"
#define STL_USING_SET
#include "OdaSTL.h"

namespace OdTvDs
{
  //----------------------------------------------------------
  //
  // SchIdxSegment
  // The "schidx" segment
  //
  //----------------------------------------------------------
  class SchIdxSegment : public FileSegment
  {
  public:
    static const OdUInt8 Name[7];
    SchIdxSegment() 
      : FileSegment(Name)
    {}

    class SchemaEntry
    {
    public:
      SchemaEntry()
        : m_NameIndex(0)
        , m_SegmentIndex(0)
        , m_LocalOffset(0)
      {}
      SchemaEntry(OdUInt32 nameIndex, OdUInt32 segmentIndex, OdUInt32 localOffset)
        : m_NameIndex(nameIndex)
        , m_SegmentIndex(segmentIndex)
        , m_LocalOffset(localOffset)
      {}
      void read(OdTvDbDwgFiler* pFiler)
      {
        m_NameIndex = pFiler->rdInt32();
        m_SegmentIndex = pFiler->rdInt32();
        m_LocalOffset = pFiler->rdInt32();
      }
      void write(OdTvDbDwgFiler* pFiler)
      {
        pFiler->wrInt32(m_NameIndex);
        pFiler->wrInt32(m_SegmentIndex);
        pFiler->wrInt32(m_LocalOffset);
      }
      OdUInt32 m_NameIndex;
      OdUInt32 m_SegmentIndex;
      OdUInt32 m_LocalOffset;
    };

    class AttributeEntry
    {
    public:
      AttributeEntry()
        : m_NameIndex(0)
        , m_SegmentIndex(0)
        , m_LocalOffset(0)
      {}
      AttributeEntry(OdUInt32 nameIndex, OdUInt32 segmentIndex, OdUInt32 localOffset)
        : m_NameIndex(nameIndex)
        , m_SegmentIndex(segmentIndex)
        , m_LocalOffset(localOffset)
      {}
      void read(OdTvDbDwgFiler* pFiler)
      {
        m_SegmentIndex = pFiler->rdInt32();
        m_LocalOffset = pFiler->rdInt32();
        m_NameIndex = pFiler->rdInt32();
      }
      void write(OdTvDbDwgFiler* pFiler)
      {
        pFiler->wrInt32(m_SegmentIndex);
        pFiler->wrInt32(m_LocalOffset);
        pFiler->wrInt32(m_NameIndex);
      }
      OdUInt32 m_NameIndex;
      OdUInt32 m_SegmentIndex;
      OdUInt32 m_LocalOffset;
    };

    void read(OdTvDbDwgFiler* pFiler);
    void write(OdTvDbDwgFiler* pFiler);

    OdArray<SchemaEntry> m_schemaEntries;
    OdArray<AttributeEntry> m_attrEntries;
    OdArray<OdAnsiString> m_schemaNames;

    std::set<OdUInt32> m_segments;
  };


  //----------------------------------------------------------
  //
  // SchemaData
  //
  //----------------------------------------------------------
  //class SchemaData
  //{
  //public:
  //  SchemaData()
  //  {}
  //  SchemaData(OdTvDbDwgFiler* pFiler)
  //  {
  //    read(pFiler);
  //  }

  //  void read(OdTvDbDwgFiler* pFiler);
  //  void write(OdTvDbDwgFiler* pFiler);

  //  OdUInt64Array m_indexes;
  //  OdArray<SchemaProperty> m_properties;
  //};

  //----------------------------------------------------------
  //
  // SchDatSegment
  // The "schdat" segment
  //
  //----------------------------------------------------------
  class SchDatSegment : public FileSegment
  {
  public:
    static const OdUInt8 Name[7];
    SchDatSegment() 
      : FileSegment(Name)
      , m_pSchemaIndex(0)
    {}

    void read(OdTvDbDwgFiler* pFiler);
    void write(OdTvDbDwgFiler* pFiler);

    void setSchemaIndex(SchIdxSegment* pSchemaIndex) { m_pSchemaIndex = pSchemaIndex; }
    SchIdxSegment* getSchemaIndex() { return m_pSchemaIndex; }

    OdArray<SchemaPtr> m_schemas;
    OdArray<SchemaAttributeData> m_attributesData;

  private:
    SchIdxSegment* m_pSchemaIndex;
  };

  //----------------------------------------------------------
  //
  // SchemaSearchData
  //
  //----------------------------------------------------------
  class SchemaSearchData
  {
  public:
    class IdEntry
    {
    public:
      IdEntry()
        : m_Handle(0)
      {}
      IdEntry(OdUInt64 handle, OdUInt64 index)
        : m_Handle(handle)
      {
        m_Indexes.push_back(index);
      }
      void read(OdTvDbDwgFiler* pFiler)
      {
        m_Handle = pFiler->rdInt64();
        OdUInt64 numEntries = pFiler->rdInt64();
        m_Indexes.resize(numEntries);
        for (OdUInt64 i = 0; i < numEntries; ++i)
        {
          m_Indexes[i] = pFiler->rdInt64();
        }
      }
      void write(OdTvDbDwgFiler* pFiler)
      {
        pFiler->wrInt64(m_Handle);
        OdUInt64 numEntries = m_Indexes.size();
        pFiler->wrInt64(numEntries);
        for (OdUInt64 i = 0; i < numEntries; ++i)
        {
          pFiler->wrInt64(m_Indexes[i]);
        }
      }
      OdUInt64 m_Handle;
      OdUInt64Array m_Indexes;
    };

    SchemaSearchData()
    {}
    SchemaSearchData(OdTvDbDwgFiler* pFiler)
    {
      read(pFiler);
    }
    void read(OdTvDbDwgFiler* pFiler)
    {
      m_SchemaNameIndex = pFiler->rdInt32();
      OdUInt64 numIndexes = pFiler->rdInt64();
      m_SortedIndexes.resize(numIndexes);
      for (OdUInt64 i = 0; i < numIndexes; ++i)
      {
        m_SortedIndexes[i] = pFiler->rdInt64();
      }
      OdUInt32 numSets = pFiler->rdInt32();
      if (numSets > 0)
      {
        OdUInt32 unknown = pFiler->rdInt32(); ODA_ASSERT_ONCE(unknown==0);
        m_IdIndexesSet.resize(numSets);
        for (OdUInt64 i = 0; i < numSets; ++i)
        {
          OdUInt32 numIds = pFiler->rdInt32();
          m_IdIndexesSet[i].resize(numIds);
          for (unsigned j = 0; j < numIds; ++j)
          {
            m_IdIndexesSet[i][j].read(pFiler);
          }
        }
      }
    }

    void write(OdTvDbDwgFiler* pFiler)
    {
      pFiler->wrInt32(m_SchemaNameIndex);
      OdUInt64 numIndexes = m_SortedIndexes.size();
      pFiler->wrInt64(numIndexes);
      for (OdUInt64 i = 0; i < numIndexes; ++i)
      {
        pFiler->wrInt64(m_SortedIndexes[i]);
      }
      OdUInt32 numSets = m_IdIndexesSet.size();
      pFiler->wrInt32(numSets);
      pFiler->wrInt32(0);
      for (OdUInt64 i = 0; i < numSets; ++i)
      {
        OdUInt32 numIds = m_IdIndexesSet[i].size();
        pFiler->wrInt32(numIds);
        for (unsigned j = 0; j < numIds; ++j)
        {
          m_IdIndexesSet[i][j].write(pFiler);
        }
      }
    }

    OdUInt32 m_SchemaNameIndex;
    OdUInt64Array m_SortedIndexes;
    OdArray<OdArray<IdEntry> > m_IdIndexesSet;
  };

  //----------------------------------------------------------
  //
  // SearchSegment
  // The "search" segment
  //
  //----------------------------------------------------------
  class SearchSegment : public FileSegment
  {
  public:
    static const OdUInt8 Name[7];
    SearchSegment() 
      : FileSegment(Name)
    {}

    void read(OdTvDbDwgFiler* pFiler);
    void write(OdTvDbDwgFiler* pFiler);

    OdArray<SchemaSearchData> m_schemas;
  };
}

#endif // _OD_DSFILESCHEMASEGMENT_H_INCLUDED_
