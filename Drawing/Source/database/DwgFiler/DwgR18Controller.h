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


#ifndef _OD_DWGR18CONTROLLER_H_INCLUDED_
#define _OD_DWGR18CONTROLLER_H_INCLUDED_

#include "OdPlatform.h"
#include "OdBinaryData.h"
#include "DbSecurity.h"
#include "RxObject.h"
#include "FlatMemStream.h"
#include "RxDictionary.h"
#include "DwgR18Compressor.h"
#include "RxObjectImpl.h"
#include "OdPlatformStreamer.h"
#include "DwgFileController.h"

#include "DwgR18PagedStream.h"

#include "PagesMapEntry.h"
#include "GapsTree.h"

//----------------------------------------------------------
//
// OdDwgR18FileHeader
//
//----------------------------------------------------------
class DBIO_EXPORT OdDwgR18FileHeader
{
public:
  OdDwgR18FileHeader();

  void write(OdUInt8* data);
  void read(OdUInt8* data);
  void encode(OdUInt8* data, OdUInt32 size);

  static OdInt8 m_fileR18Id[];

  OdInt32 m_gapsRootId;   // gaps: root tree node
  OdInt32 m_IdOfMaxGap;   // gaps: tree node with a MAX key value (the size of gap is used as a key)
  OdInt32 m_IdOfMinGap;   // gaps: tree node with a MIN key value (the size of gap is used as a key)
  OdInt32 m_gapsUnknown;  // gaps: ?

  OdInt32 m_lastPageId;
  OdUInt64 m_lastPageEndOffset;
  OdUInt64 m_header2Offset;

  OdUInt32 m_gapsAmount;
  OdUInt32 m_pagesAmount;

  OdUInt32 m_pagesMapId;
  OdUInt64 m_pagesMapOffset;

  OdUInt32 m_sectionsMapId;

  OdUInt32 m_pagesMaxId;
  OdUInt32 m_gapsMaxId;

  OdBinaryData m_random;
};

//----------------------------------------------------------
//
// SysPageHeader
//
//----------------------------------------------------------
class SysPageHeader
{
public:
  SysPageHeader(OdUInt32 type)
    : m_type(type)
    , m_decomprSize(0)
    , m_comprSize(0)
    , m_comprType(2)
    , m_checksum(0) {}

  inline void clear();
  inline void read(OdStreamBufPtr pOrigStream, OdUInt8* data);
  inline void write(OdStreamBufPtr pOrigStream);
  inline void write(OdUInt8* data);

  OdUInt32 m_type;
  OdUInt32 m_decomprSize;
  OdUInt32 m_comprSize;
  OdUInt32 m_comprType; // presumably, always == 2
  OdUInt32 m_checksum;
};

//----------------------------------------------------------
//
// PageHeader
//
//----------------------------------------------------------
class PageHeader
{
public:
  PageHeader()
    : m_type(DATA_PAGE_TYPE)
    , m_sectionId(0)
    , m_dataSize(0)
    , m_pageSize(0)
    , m_startOffset(0)
    , m_checksum1(0)
    , m_checksum2(0) {}

  inline void read(OdStreamBufPtr pStream, OdUInt8* hdrData, OdUInt64 offset);
  inline void read(OdUInt8* hdrData);
  inline void write(OdStreamBufPtr pStream, OdUInt8* hdrData, OdUInt64 offset);
  inline void write(OdUInt8* hdrData);
  inline void encode(OdUInt8* hdrData, OdUInt32 offset);

  OdUInt32 m_type;
  OdUInt32 m_sectionId;
  OdUInt32 m_dataSize;
  OdUInt32 m_pageSize;
  OdUInt64 m_startOffset;
  OdUInt32 m_checksum1;
  OdUInt32 m_checksum2;
};

//----------------------------------------------------------
//
// OdDwgR18FileController
//
//----------------------------------------------------------
class DBIO_EXPORT OdDwgR18FileController : public OdDwgFileSecurity
{
public:
  friend class OdDwgR18FileWriter;
  OdDwgR18FileController();

  virtual OdStreamBufPtr rawStream() { return m_pRawStream; }

  typedef IncSaveNamespace::PagesMapEntryPtrsList PagesContainer;
  typedef std::map<OdInt32, IncSaveNamespace::PagesMapEntryPtrsList::iterator> PagesIndex;
  typedef IncSaveNamespace::GapsTree GapsIndex;
    
  inline OdUInt32 addPage(OdUInt32 pageSize, OdInt64 pageOffset, IncSaveNamespace::GapsTreeNode* pGapNode);
  inline void addSysPage(OdUInt32 pageSize, OdInt64 pageOffset, IncSaveNamespace::GapsTreeNode* pGapNode);

  struct IncrementalInfo
  {
    IncrementalInfo()
      : m_skipStreamPosChecking(false)
      , m_incSaveModeLaunched(false)
      , m_disableIncSaveDueToException(false)
      , m_actualEndOffset(0)
      , m_writeDS(false)
      , m_writeObjects(false)
      , m_writeHandles(false)
      , m_writeClasses(false)
      , m_numErrorsByAudit(0)
      , m_freeSpaceSize(0)
      , m_newFreeSpaceSize(0)
    {
      m_sections = odrxCreateRxDictionary();
    }

    OdDwgR18FileHeader     m_header;

    PagesContainer m_pagesContainer;
    PagesIndex  m_pagesIndex;
    GapsIndex   m_gapsIndex;
            
    OdRxDictionaryPtr      m_sections;    

    bool m_skipStreamPosChecking;
    bool m_incSaveModeLaunched;
    bool m_disableIncSaveDueToException;

    OdUInt64 m_actualEndOffset;

    //section flags for IncSave:
    bool m_writeDS;
    bool m_writeObjects;
    bool m_writeHandles;
    bool m_writeClasses;

    OdUInt32 m_numErrorsByAudit;

    //ObjFreeSpace data:    
    OdUInt64 m_freeSpaceSize;
    OdUInt64 m_newFreeSpaceSize;
  };
  
  typedef OdSharedPtr<IncrementalInfo> IncrementalInfoPtr;

  // The methods provide access to PagesMap
  inline OdUInt64 pageOffset(OdInt32 pageId);
  inline OdUInt32 pageSize(OdInt32 pageId);

  OdDwgR18Compressor  m_cmpr;
  const OdBinaryData& randomData() { return m_II->m_header.m_random; }

// ODA_MT_DBIO_BEGIN
  OdMutex m_rawStreamLock;
// ODA_MT_DBIO_END

  IncrementalInfoPtr getIncrementalInfo() { return m_II; }
  
  bool getOffsetOfSuitableGap(OdUInt32 requiredSize, OdUInt64& resultOffset, 
    IncSaveNamespace::GapsTreeNode*& pGapNode);

  bool registerExistingPageAsNewGap(OdUInt32 pageId);

  void checkLeftSideAndMerge(IncSaveNamespace::PagesMapEntryPtrsList::iterator& currentGapIt);
  void checkRightSideAndMerge(IncSaveNamespace::PagesMapEntryPtrsList::iterator& currentGapIt);
  void checkBothSidesAndMerge(IncSaveNamespace::PagesMapEntryPtrsList::iterator& currentGapIt);

  void mergeLeftSide(IncSaveNamespace::PagesMapEntryPtrsList::iterator& currentGapIt, 
    IncSaveNamespace::PagesMapEntryPtrsList::iterator& leftGapIt);
  void mergeRightSide(IncSaveNamespace::PagesMapEntryPtrsList::iterator& currentGapIt, 
    IncSaveNamespace::PagesMapEntryPtrsList::iterator& rightGapIt);
  void mergeBothSides(IncSaveNamespace::PagesMapEntryPtrsList::iterator& currentGapIt, 
    IncSaveNamespace::PagesMapEntryPtrsList::iterator& leftGapIt, 
    IncSaveNamespace::PagesMapEntryPtrsList::iterator& rightGapIt);

  void collectPagesDataBySections(OdUInt32 sectionIdToExclude = 0);
  void setThisControllerForAllExistingSections();

protected:
  IncrementalInfoPtr m_II;

  OdStreamBufPtr      m_pRawStream;

public:
  OdBinaryData m_buffCompr;
  OdBinaryData m_buffDecompr;

  bool m_openedInRecoverMode;
};

//----------------------------------------------------------
//
// Inline methods
//
//----------------------------------------------------------
inline void SysPageHeader::clear()
{
  m_decomprSize = 0;
  m_comprSize = 0;
  m_checksum = 0;
}

inline void SysPageHeader::read(OdStreamBufPtr pOrigStream, OdUInt8* data)
{
  OdStreamBuf* pStream = pOrigStream;
  pOrigStream->getBytes(data, SYS_SECTION_HEADER_SIZE);

  OdStreamBufPtr pFlatMemStream = OdFlatMemStream::createNew(data, SYS_SECTION_HEADER_SIZE);
  pStream = pFlatMemStream;
  if (m_type != (OdUInt32)OdPlatformStreamer::rdInt32(*pStream))
  {
    ODA_FAIL();
    throw OdError(eDwgNeedsRecovery);
  }
  m_decomprSize = OdPlatformStreamer::rdInt32(*pStream);
  m_comprSize = OdPlatformStreamer::rdInt32(*pStream);
  ODA_VERIFY(m_comprType == (OdUInt32)OdPlatformStreamer::rdInt32(*pStream));
  m_checksum = OdPlatformStreamer::rdInt32(*pStream);
}

inline void SysPageHeader::write(OdStreamBufPtr pOrigStream)
{
  OdStreamBuf* pStream = pOrigStream;
  OdPlatformStreamer::wrInt32(*pStream, m_type);
  OdPlatformStreamer::wrInt32(*pStream, m_decomprSize);
  OdPlatformStreamer::wrInt32(*pStream, m_comprSize);
  OdPlatformStreamer::wrInt32(*pStream, m_comprType);
  OdPlatformStreamer::wrInt32(*pStream, m_checksum);
}

inline void SysPageHeader::write(OdUInt8* data)
{
  write(OdFlatMemStream::createNew(data, SYS_SECTION_HEADER_SIZE));
}

inline void PageHeader::read(OdStreamBufPtr pStream, OdUInt8* hdrData, OdUInt64 offset)
{
  pStream->seek(offset, OdDb::kSeekFromStart);
  pStream->getBytes(hdrData, SECTION_HEADER_SIZE);
  encode(hdrData, (OdUInt32)offset);
  read(hdrData);
}

inline void PageHeader::read(OdUInt8* hdrData)
{
  OdStreamBufPtr pOrigStream(OdFlatMemStream::createNew(hdrData, SECTION_HEADER_SIZE));
  OdStreamBuf* pStream = pOrigStream;

  if (OdPlatformStreamer::rdInt32(*pStream) != DATA_PAGE_TYPE)
  {
    ODA_FAIL_ONCE();
    throw OdError(eDwgNeedsRecovery);
  }
  m_sectionId = OdPlatformStreamer::rdInt32(*pStream);

  //ODA_TRACE1("SECTION_ID = %d", m_sectionId);

  m_dataSize = OdPlatformStreamer::rdInt32(*pStream);
  m_pageSize = OdPlatformStreamer::rdInt32(*pStream);
  m_startOffset = OdPlatformStreamer::rdInt64(*pStream);
  m_checksum1 = OdPlatformStreamer::rdInt32(*pStream);
  m_checksum2 = OdPlatformStreamer::rdInt32(*pStream);
  if (m_dataSize > m_pageSize)
    throw OdError(eDwgNeedsRecovery);
}

inline void PageHeader::write(OdStreamBufPtr pStream, OdUInt8* hdrData, OdUInt64 offset)
{
  write(hdrData);
  encode(hdrData, (OdUInt32)offset);
  pStream->seek(offset, OdDb::kSeekFromStart);
  pStream->putBytes(hdrData, SECTION_HEADER_SIZE);
}

inline void PageHeader::write(OdUInt8* hdrData)
{
  OdStreamBufPtr pOrigStream(OdFlatMemStream::createNew(hdrData, SECTION_HEADER_SIZE));
  OdStreamBuf* pStream = pOrigStream;

  OdPlatformStreamer::wrInt32(*pStream, m_type);
  OdPlatformStreamer::wrInt32(*pStream, m_sectionId);
  OdPlatformStreamer::wrInt32(*pStream, m_dataSize);
  OdPlatformStreamer::wrInt32(*pStream, m_pageSize);
  OdPlatformStreamer::wrInt64(*pStream, m_startOffset);
  OdPlatformStreamer::wrInt32(*pStream, m_checksum1);
  OdPlatformStreamer::wrInt32(*pStream, m_checksum2);
}

inline void PageHeader::encode(OdUInt8* hdrData, OdUInt32 offset)
{
  // Encode/Decode section header
  OdUInt32 secMask = DATA_PAGE_MASK ^ offset;
  odSwap4BytesNumber(secMask); // big-endian support
  OdUInt32* pHdr = (OdUInt32*)hdrData;
  OdUInt32* pHdrEnd = pHdr + (SECTION_HEADER_SIZE/sizeof(OdUInt32));
  while (pHdr < pHdrEnd)
    *pHdr++ ^= secMask;
}

inline OdUInt64 OdDwgR18FileController::pageOffset(OdInt32 pageId)
{  
  OdUInt64 resultOffset = 0;

  if (m_openedInRecoverMode)
  { 
    PagesIndex::iterator it = m_II->m_pagesIndex.find(pageId);
    if (it != m_II->m_pagesIndex.end())
    {
      resultOffset = (*it->second)->m_offset;
    }
    else
    {
      throw OdError(eDwgNeedsRecovery);
    }    
  }
  else
  {
    resultOffset = (*m_II->m_pagesIndex[pageId])->m_offset;
  }

  return resultOffset;
}

inline OdUInt32 OdDwgR18FileController::pageSize(OdInt32 pageId)
{
  return (*m_II->m_pagesIndex[pageId])->m_size;
}

inline OdUInt32 OdDwgR18FileController::addPage(OdUInt32 pageSize, OdInt64 pageOffset, 
  IncSaveNamespace::GapsTreeNode* pGapNode)
{ 
  OdUInt32 pageId = m_II->m_header.m_pagesMaxId + 1;
  m_II->m_header.m_pagesMaxId = pageId;

  IncSaveNamespace::PagesMapEntryPtr pPageData = 
    new IncSaveNamespace::PagesMapEntry(pageId, pageSize, pageOffset);
  if (!pGapNode)
  {
    m_II->m_pagesContainer.push_back(pPageData);
    IncSaveNamespace::PagesMapEntryPtrsList::iterator pageElemIt = --m_II->m_pagesContainer.end();
    m_II->m_pagesIndex[pageId] = pageElemIt;
  }
  else
  {
    IncSaveNamespace::PagesMapEntryPtrsList::iterator oldGapElemIt = pGapNode->getNodeValue();
    m_II->m_gapsIndex.deleteNode(pGapNode);

    OdUInt32 gapSize = (*oldGapElemIt)->getPageSize();
    OdUInt64 gapOffset = (*oldGapElemIt)->getPageOffset();

    (*oldGapElemIt) = pPageData;
    m_II->m_pagesIndex[pageId] = oldGapElemIt;
        
    OdUInt64 newPageEndOffset = pageOffset + pageSize;
    OdUInt64 usedPartOfGapSize = newPageEndOffset - gapOffset;
    if (gapSize > usedPartOfGapSize)
    {
      OdInt32 absNewGapId = m_II->m_header.m_gapsMaxId + 1;
      m_II->m_header.m_gapsMaxId = absNewGapId;

      OdUInt64 remainingGapSize = gapSize - usedPartOfGapSize;
      OdUInt64 remainingGapOffset = newPageEndOffset;
      IncSaveNamespace::PagesMapEntryPtr pRemainingGapData = 
        new IncSaveNamespace::GapsMapEntry(-absNewGapId, (OdUInt32)remainingGapSize, remainingGapOffset);

      IncSaveNamespace::PagesMapEntryPtrsList::iterator remainingGapElemIt = 
        m_II->m_pagesContainer.insert(++oldGapElemIt, pRemainingGapData);

      ((IncSaveNamespace::GapsMapEntry*)pRemainingGapData.get())->m_pTreeNode = 
        m_II->m_gapsIndex.insertNode((OdUInt32)remainingGapSize, remainingGapElemIt);
    }
  }

  return pageId;
}

inline void OdDwgR18FileController::addSysPage(OdUInt32 pageSize, OdInt64 pageOffset, 
  IncSaveNamespace::GapsTreeNode* pGapNode)
{ 
  m_II->m_header.m_pagesMaxId++;

  addPage(pageSize, pageOffset, pGapNode);
}

#endif // _OD_DWGR18CONTROLLER_H_INCLUDED_
