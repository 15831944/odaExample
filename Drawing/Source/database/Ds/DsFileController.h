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


#ifndef _OD_DSFILECONTROLLER_H_INCLUDED_
#define _OD_DSFILECONTROLLER_H_INCLUDED_


#include "RxObject.h"
#include "DsFileHeader.h"
#include "DsFileSegments.h"
#include "DsFileDataSegments.h"
#include "DsFileSchemaSegments.h"
#include "FlatFiler.h"
#include "DbDatabaseImpl.h"
#include "UInt32Array.h"
#define STL_USING_MAP
#include "OdaSTL.h"

namespace OdDs
{
  //----------------------------------------------------------
  //
  // FileController
  // The DS file controller class
  //
  //----------------------------------------------------------
  class FileController : public OdRxObject
  {
  public:
    ODRX_DECLARE_MEMBERS(FileController);

    FileController();
    virtual ~FileController();

    void read();
    void write();


    void setDatabase(OdDbDatabase* pDb)
    { 
      m_pDb = pDb;
    }
    void setStream(OdStreamBuf* pStream)
    { 
      m_pFileStream = pStream;
    }

    const OdDbDatabase* database() const
    {
      return m_pDb;
    }

    static OdAnsiString readName(OdDbDwgFiler* pFiler, int maxStringLength);
    static void writeName(OdDbDwgFiler* pFiler, const OdAnsiString& name);

    RecordType GetRecordType(RecordsSet& dbDsRecordsSet, unsigned int RecIndex) const;
    OdStreamBufPtr ReadBlobData(OdDbDwgFiler* pFiler, DataBlobEntryReference& blobRef);
    void ReadBlobData(OdDbDwgFiler* pFiler, DataBlobEntryReference& blobRef, DataInFileAsBlob *pDataLocator);

  private:
    void readSegIdx(OdDbDwgFiler* pFiler);
    void readDatIdx(OdDbDwgFiler* pFiler);
    void readData(OdDbDwgFiler* pFiler);
    void readSchIdx(OdDbDwgFiler* pFiler);
    void readSchDat(OdDbDwgFiler* pFiler);
    void readSearch(OdDbDwgFiler* pFiler);

    void writeSegIdx(OdDbDwgFiler* pFiler);
    void writeDatIdx(OdDbDwgFiler* pFiler);
    void writeData(OdDbDwgFiler* pFiler);
    void writeData(OdDbDwgFiler* pFiler, RecordType recType, OdUInt32 schemaIndex);
    void writeSchIdx(OdDbDwgFiler* pFiler);
    void writeSchDat(OdDbDwgFiler* pFiler);
    void writeSearch(OdDbDwgFiler* pFiler);
    void writeBlobData(OdDbDwgFiler* pFiler, const OdDbHandle& handle, OdStreamBufPtr& pBinData, DataBlobEntryReference& blobSegsRef);

    OdDbDatabase* m_pDb;
    OdStreamBuf* m_pFileStream;
    OdUInt64 m_dsStartOffset;
    OdUInt32 m_curSegIndex; // write-support
    OdStreamBufPtr m_pDsStream; // write-support

    FileHeader m_FileHeader;
    SegIdxSegment m_SegIdx;
    DatIdxSegment m_DatIdx;
    SchIdxSegment m_SchIdx;
    OdArray<SchDatSegment> m_SchDatSegs;
    SearchSegment m_Search;

  };
}

#endif // _ODDS_FILECONTROLLER_H_INCLUDED_
