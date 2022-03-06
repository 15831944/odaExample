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


#ifndef _OD_DSFILEHEADER_H_INCLUDED_
#define _OD_DSFILEHEADER_H_INCLUDED_


#include "RxObject.h"
#include "DbFiler.h"

#define DSFILE_HEADER_SIZE 0x80
#define DSFILE_HEADER_DATA_SIZE 0x42

namespace OdTvDs
{
  class FileHeader
  {
  public:
    FileHeader()
      : m_FileSignature(0x6472616A) // 'jard'
      , m_FileHeaderSize(0x80)
      , m_MinorVersion(2)
      , m_Version(2)
      , m_Unknown5(0)
      , m_DsRevision(1)
      , m_SegIdxOffset(0x80)
      , m_SegIdxUnknown(0)
      , m_SegIdxEntryCount(0)
      , m_SchIdxIndex(0)
      , m_DatIdxIndex(0)
      , m_SearchIndex(0)
      , m_PrvsavIndex(0)
      , m_FileSize(0)
    {}

    void read(OdTvDbDwgFiler* pFiler)
    {
      m_FileSignature = pFiler->rdInt32();
      m_FileHeaderSize = pFiler->rdInt32();
      // FileVerMVer >= kMRelease8  -> m_MinorVersion == 2 (AC2013 product release)
      // FileVerMVer >= kMRelease10 -> m_MinorVersion == 3 (AC2013 SP1)
      // FileVerMVer >= 55          -> m_MinorVersion == 6 (AC2014)
      // FileVerMVer >= kMRelease20 -> m_MinorVersion == 7 (AC2013 SP2)
      // FileVerMVer >= 81          -> m_MinorVersion == 8 (AC2015)
      m_MinorVersion = pFiler->rdInt32(); ODA_ASSERT(m_MinorVersion <= 8);
      m_Version = pFiler->rdInt32(); ODA_ASSERT(m_Version == 2);
      m_Unknown5 = pFiler->rdInt32(); ODA_ASSERT(m_Unknown5 == 0);
      m_DsRevision = pFiler->rdInt32();
      m_SegIdxOffset = pFiler->rdInt32();
      m_SegIdxUnknown = pFiler->rdInt32(); ODA_ASSERT(m_SegIdxUnknown == 0);
      m_SegIdxEntryCount = pFiler->rdInt32();
      m_SchIdxIndex = pFiler->rdInt32();
      m_DatIdxIndex = pFiler->rdInt32();
      m_SearchIndex = pFiler->rdInt32();
      m_PrvsavIndex = pFiler->rdInt32();
      m_FileSize = pFiler->rdInt32();
    }

    void write(OdTvDbDwgFiler* pFiler)
    {
      pFiler->wrInt32(m_FileSignature);
      pFiler->wrInt32(m_FileHeaderSize);
      pFiler->wrInt32(m_MinorVersion);
      pFiler->wrInt32(m_Version);
      pFiler->wrInt32(m_Unknown5);
      pFiler->wrInt32(m_DsRevision);
      pFiler->wrInt32(m_SegIdxOffset);
      pFiler->wrInt32(m_SegIdxUnknown);
      pFiler->wrInt32(m_SegIdxEntryCount);
      pFiler->wrInt32(m_SchIdxIndex);
      pFiler->wrInt32(m_DatIdxIndex);
      pFiler->wrInt32(m_SearchIndex);
      pFiler->wrInt32(m_PrvsavIndex);
      pFiler->wrInt32(m_FileSize);
    }

    OdUInt32 m_FileSignature;
    OdInt32 m_FileHeaderSize;
    OdInt32 m_MinorVersion;
    OdInt32 m_Version;
    OdInt32 m_Unknown5;
    OdInt32 m_DsRevision;
    OdInt32 m_SegIdxOffset;
    OdInt32 m_SegIdxUnknown;
    OdInt32 m_SegIdxEntryCount;
    OdInt32 m_SchIdxIndex;
    OdInt32 m_DatIdxIndex;
    OdInt32 m_SearchIndex;
    OdInt32 m_PrvsavIndex;
    OdInt32 m_FileSize;
  };
}

#endif // _OD_DSFILEHEADER_H_INCLUDED_
