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


#ifndef _OD_DSRECORDSSET_H_INCLUDED_
#define _OD_DSRECORDSSET_H_INCLUDED_


#include "DbHandle.h"
#include "OdBinaryData.h"
#include "FlatMemStream.h"
#include "DsSchema.h"
#include "DsFileSchemaSegments.h"
#include "DsFileDataSegments.h"
#include "../DwgFiler/FlatFiler.h"
#include "SharedPtr.h"

namespace OdDs
{
  class DataLocator
  {
  public:
    virtual ~DataLocator(){};

    virtual OdStreamBufPtr GetData(OdDbDwgFiler* pFiler = NULL) const = 0;
  };

  typedef OdSharedPtr<DataLocator> DataLocatorPtr;

  class DataInMemory : public DataLocator
  {
  public:

    DataInMemory(OdStreamBufPtr pStreamBufPtr)
      : m_pStreamBufPtr(pStreamBufPtr)
    {

    }

    virtual OdStreamBufPtr GetData(OdDbDwgFiler* pFiler = NULL) const
    {
      return m_pStreamBufPtr;
    }

  private:
    OdStreamBufPtr m_pStreamBufPtr;
  };


  class DataInFileAsRecord : public DataLocator
  {
  public:

    DataInFileAsRecord(OdInt64 offset, OdInt32 size)
      : m_offset(offset), m_size(size)
    {

    }

    virtual OdStreamBufPtr GetData(OdDbDwgFiler* pFiler = NULL) const
    {
      OdStreamBufPtr pDsData = OdMemoryStream::createNew(BLOB_SEGMENT_PAGE_SIZE);
      pFiler->seek(m_offset, OdDb::kSeekFromStart);
      OdBinaryData cache;
      cache.resize(m_size);
      pFiler->rdBytes(cache.asArrayPtr(), m_size);
      pDsData->putBytes(cache.asArrayPtr(), m_size);
      pDsData->seek(0, OdDb::kSeekFromStart); //Current position must be on the data start.
      return pDsData;
    }

  private:
    OdInt64 m_offset;
    OdInt32 m_size;
  };

  class DataInFileAsBlob : public DataLocator
  {
  public:

    struct BlobPartPosition
    {
      OdInt64 offset;
      OdInt32 size;
    };

    DataInFileAsBlob()
    {

    }

    virtual OdStreamBufPtr GetData(OdDbDwgFiler* pFiler = NULL) const
    {
      OdStreamBufPtr pDsData = OdMemoryStream::createNew(BLOB_SEGMENT_PAGE_SIZE);
      OdArray<BlobPartPosition>::const_iterator it;
      for (it = offsets.begin(); it != offsets.end(); it++)
      {
        pFiler->seek(it->offset, OdDb::kSeekFromStart);
        Blob01Segment blobSeg;
        blobSeg.read(pFiler);
        pDsData->putBytes(blobSeg.m_binData.asArrayPtr(), blobSeg.m_binData.size());
      }
      pDsData->seek(0, OdDb::kSeekFromStart); //Current position must be on the data start.
      return pDsData;
    }

    void AddBlobSeg(OdInt64 offset, OdInt32 size)
    {
      BlobPartPosition partPosition;
      partPosition.offset = offset;
      partPosition.size = size;
      offsets.push_back(partPosition);
    }

  private:
    OdArray<BlobPartPosition> offsets;
  };

}

typedef std::multimap<OdDbHandle, OdDs::DataLocatorPtr> OdDsRecords;

namespace OdDs
{
  //----------------------------------------------------------
  //
  // 
  //
  //----------------------------------------------------------
  class RecordsSet
  {
  public:

    void addDsRecord(RecordType type, const OdDbHandle& h, const OdBinaryData& binData)
    {
      m_DsCache.push_back(binData);
      OdStreamBufPtr pStream = OdFlatMemStream::createNew(m_DsCache.back().asArrayPtr(), binData.size());
      addDsRecord(type, h, pStream);
    }
    void addDsRecord(RecordType type, const OdDbHandle& h, OdStreamBufPtr& pBinStream)
    {
      DataLocatorPtr pDataLocator(new DataInMemory(pBinStream));
      dsRecords(type).insert( std::pair<const OdDbHandle, OdSharedPtr<OdDs::DataLocator> >(h, pDataLocator));
    }

    void addDsRecord(RecordType type, const OdDbHandle& h, OdInt64 offset, OdInt32 size)
    {
      DataLocatorPtr pDataLocator(new DataInFileAsRecord(offset, size));
      dsRecords(type).insert( std::pair<const OdDbHandle, OdSharedPtr<OdDs::DataLocator> >(h, pDataLocator));
    }

    void addDsRecord(RecordType type, const OdDbHandle& h, DataLocatorPtr& pDataLocator)
    {
        dsRecords(type).insert( std::pair<const OdDbHandle, OdSharedPtr<OdDs::DataLocator> >(h, pDataLocator));
    }

    OdStreamBufPtr extractDsAcisData(RecordType type, OdDbHandle h)
    {
      TD_AUTOLOCK(m_dsLock);
      OdStreamBufPtr pStream;
      OdDsRecords& dsRecs = dsRecords(type);

      OdDsRecords::iterator itDataInMemory = dsRecs.end();

      std::pair< OdDsRecords::iterator, OdDsRecords::iterator > findresult;
      findresult = dsRecs.equal_range(h);
      for (OdDsRecords::iterator it = findresult.first; it != findresult.second; it++)
      {
        if (dynamic_cast<DataInMemory *>(it->second.get()))
        {
          itDataInMemory = it;
          break;
        }
      }

      if (itDataInMemory != dsRecs.end())
      {
        pStream = itDataInMemory->second->GetData(&filer);
        dsRecs.erase(itDataInMemory);
        pStream->seek(0, OdDb::kSeekFromStart); //Current position must be on the data start.
      }
      else if (findresult.first != findresult.second)
      {
        pStream = findresult.first->second->GetData(&filer);
        pStream->seek(0, OdDb::kSeekFromStart); //Current position must be on the data start.
      }

      return pStream;
    }
    bool hasDsRecords(RecordType type, OdDbHandle h) const
    {
      const OdDsRecords& dsRecs = dsRecords(type);
      OdDsRecords::const_iterator it = dsRecs.find(h);
      return it != dsRecs.end();
    }
    bool hasDsRecords() const
    {
      return hasDsRecords(kDsAsm) || hasDsRecords(kDsPreview);
    }
    bool hasDsRecords(RecordType type) const
    {
      return !dsRecords(type).empty();
    }
    OdDsRecords& dsRecords(RecordType type)
    {
      return m_DsRecordsSet[(int)type];
    }
    const OdDsRecords& dsRecords(RecordType type) const
    {
      return m_DsRecordsSet[(int)type];
    }
    void clear()
    {
      for (int i = 0; i < kDsTypesCount; ++i)
      {
        m_DsRecordsSet[i].clear();
      }
      m_DsCache.resize(0);
    }

    // TODO: Avoid duplicate storages of Schema data pointers (array and map)
    OdArray<OdDs::SchemaPtr> m_schemas;
    typedef std::map<OdUInt32, OdDs::SchemaPtr> SchemasMap;
    SchemasMap m_schemasMap;
    OdArray<OdDs::SchemaAttributeData> m_attributeData;
    OdArray<OdDs::SchemaSearchData> m_schemaSearch;
    OdStaticRxObject<OdFlatFiler> filer;
  private:
    OdDsRecords m_DsRecordsSet[kDsTypesCount];
    std::list<OdBinaryData> m_DsCache;
    OdMutex m_dsLock;
  };

}

#endif // _OD_DSRECORDSSET_H_INCLUDED_
