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

#ifndef __NWSTREAMCONFIG_H__
#define __NWSTREAMCONFIG_H__

#include "NwExport.h"
#include "OdBinaryData.h"

//uncomment next line to dump streams into defined path
//#define NW_DUMP_LOAD_STREAM_PATH L"C:\\dumps\\load\\"
//#define NW_DUMP_SAVE_STREAM_PATH L"C:\\dumps\\save\\"

#define NW_STREAM_UNCOMPRESSED 0
#define NW_STREAM_COMPRESSED   1
#define NW_STREAM_CIPHERED     2

static const OdAnsiString sFormatStreamSignature = "#LcUStream-V1.1 binary double release utf8 navisworks:";
static const OdAnsiString sFirstSignatureBinary = "#LcUStream-V1.1 binary double release C lichunk-";

static const OdAnsiString sFormatStreamSignatureSave = sFormatStreamSignature; 
static const OdAnsiString sFirstSignatureBinarySave = sFirstSignatureBinary;

static OdUInt8 sBlowfishKey[32] = {
  0xF1, 0xFB, 0xF2, 0x39,
  0xDB, 0xB7, 0x88, 0x49,
  0x7A, 0xE7, 0x45, 0x9F,
  0xA3, 0xF9, 0x0E, 0x8F,
  0xFA, 0x5A, 0xB9, 0x83,
  0xAC, 0xEC, 0xBF, 0x66,
  0x49, 0x1D, 0xF2, 0x32,
  0x83, 0x8D, 0x6E, 0x6B
};

static OdUInt8 sGeometryCompressKey[32] = {
  0x20, 0xD9, 0xAF, 0xE0, 0x80, 0xF1, 0x17, 0x52,
  0xDE, 0x9D, 0xD9, 0x12, 0x43, 0xDE, 0x1A, 0x98,
  0x58, 0x1E, 0x2D, 0xB0, 0x4D, 0x78, 0x2F, 0xE4,
  0x69, 0x21, 0x8E, 0x52, 0xD7, 0x05, 0x1F, 0x07
};

struct NwSubStreamDefBase
{
  OdString name;
  OdUInt32 bitfield;
  OdInt64 offset;
  OdInt64 size;
  OdInt32 size_FirstStream;
  OdInt32 size_LastStream;

  NwSubStreamDefBase()
    : bitfield(0)
    , offset(0)
    , size(0)
    , size_FirstStream(0)
    , size_LastStream(0)
  {}
};

struct NwSubStreamDef: public NwSubStreamDefBase
{
  OdArray<OdStreamBufPtr> streams;

  NwSubStreamDef(): NwSubStreamDefBase()
  {}
};

namespace OdNwLoadError
{
  enum Enum
  {
    NoError = 0,
    EndOfStream,
    UnknownFormat,
    UnknownVersion,
    SignaturesMismatch,
    ParseStream,
    FileCorrupted
  };
}

namespace OdNwSaveError
{
  enum Enum
  {
    NoError = 0,
    NoDiskSpace,
    UnknownFormat,
    UnknownVersion,
    UnknownError
  };
}

struct TNwStreamConfig
{
  enum Type {
    Ascii,
    Binary
  } m_nType;
  enum Percision
  {
    Single,
    Double
  } m_nPrecision;
  enum Build {
    Debug,
    Release
  } m_nBuild;
  enum Codepage {
    utf8,
    Other
  } m_nCodepage;
  OdInt32 m_nVersion;
  bool m_bZlib;
  TNwStreamConfig()
    : m_nType(Ascii)
    , m_nPrecision(Single)
    , m_nBuild (Debug)
    , m_nCodepage(utf8) 
    , m_nVersion(0)
    , m_bZlib(false) {}
};

static void Dump_StreamDef(OdString sName, OdBinaryData &data)
{
  sName += L"StreamDefs";
  OdAnsiString sAnsiName(sName, CP_UTF_8);
  FILE* pFile = fopen(sName, "wb");
  ODA_ASSERT(NULL != pFile);

  size_t nWritten = fwrite(data.asArrayPtr(), data.size(), 1, pFile);
  fclose(pFile);
}

static void Dump_StreamContent(OdString aName, OdArray<NwSubStreamDef> &aSubStreamsDefs)
{
  for (OdUInt32 nStream = 0; nStream < aSubStreamsDefs.size(); ++nStream)
  {
    OdString sName = aName;
    OdString sFileName = aSubStreamsDefs[nStream].name;
    sFileName.replace("\\", "_");
    sFileName.replace(":", "_colon_");
    sName += sFileName;
    for (OdUInt32 nChunk = 0; nChunk < aSubStreamsDefs[nStream].streams.size(); ++nChunk)
    {
      sName += OdString().format(OD_T("_%u"), nChunk);
      OdStreamBufPtr pFile = odrxSystemServices()->createFile(sName, Oda::kFileWrite, Oda::kShareDenyNo, Oda::kCreateAlways);
      ODA_ASSERT(!pFile.isNull());
      
      OdStreamBufPtr pBuf = aSubStreamsDefs[nStream].streams[nChunk];
      pBuf->rewind();
      pBuf->copyDataTo(pFile);
    }
  }
}

static OdUInt32 sumChunkSizes(OdArray<OdUInt32> vector)
{
  OdUInt32 sum = 0;
  for (auto& n : vector)
    sum += n;
  return sum;
}

static void Dump_StreamContentCompressed(OdStreamBufPtr stream, OdString aName, OdArray<NwSubStreamDef> &aSubStreamsDefs)
{
  for (OdUInt32 nStream = 0; nStream < aSubStreamsDefs.size(); ++nStream)
  {
    OdString sName = aName;
    OdString sFileName = aSubStreamsDefs[nStream].name;
    sFileName.replace("\\", "_");
    sFileName.replace(":", "_colon_");
    sName += sFileName;

    auto save_campressed = [&](OdUInt32 nChunk, OdUInt64 offset, OdUInt64 size) {
      OdAnsiString sAnsiName(sName, CP_UTF_8);
      sAnsiName += OdAnsiString().format("_%u.compress", nChunk);
      FILE* pFile = fopen(sAnsiName, "wb");
      ODA_ASSERT(NULL != pFile);

      OdBinaryData data;
      data.resize(size);
      stream->seek(offset, OdDb::kSeekFromStart);
      stream->getBytes(data.asArrayPtr(), data.size());
      size_t nWritten = fwrite(data.asArrayPtr(), data.size(), 1, pFile);
      fclose(pFile);
    };

    OdUInt32 nChunk = 0;
    if (aSubStreamsDefs[nStream].size_FirstStream != 0)
    {
      save_campressed(nChunk, aSubStreamsDefs[nStream].offset, aSubStreamsDefs[nStream].size_FirstStream);
      nChunk++;
    }
    {
      save_campressed(nChunk, aSubStreamsDefs[nStream].offset + aSubStreamsDefs[nStream].size_FirstStream,
        aSubStreamsDefs[nStream].size - aSubStreamsDefs[nStream].size_LastStream - aSubStreamsDefs[nStream].size_FirstStream);
      nChunk++;
    }
    if (aSubStreamsDefs[nStream].size_LastStream != 0)
    {
      save_campressed(nChunk, aSubStreamsDefs[nStream].offset + aSubStreamsDefs[nStream].size - aSubStreamsDefs[nStream].size_LastStream,
        aSubStreamsDefs[nStream].size_LastStream);
      nChunk++;
    }
  }
  stream->seek(0, OdDb::kSeekFromStart);
}

#endif // __NWSTREAMCONFIG_H__
