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

#ifndef __NWSTREAMSPLITTER_H__
#define __NWSTREAMSPLITTER_H__

#include "NwExport.h"
#include "OdBinaryData.h"
#include "NwStreamConfig.h"

class OdNwStreamSplitter
{
public:
  OdNwStreamSplitter()
    : m_nInternalVersion (0)
    , m_nSecondSignaturePos (-1)
    , m_bIsBinary (false)
    , m_useCompressedMode(false)
  {}
  virtual ~OdNwStreamSplitter() {}

public:
  OdNwLoadError::Enum Load(OdStreamBufPtr stream);
  OdNwLoadError::Enum LoadOld(OdStreamBufPtr stream);
  OdInt32 getVersion() const;
  void setCompressedMode(bool compressed);
  OdInt32 getInternalVersion() const;
  bool isBinary() const;
  OdUInt32 getStreamsCount() const;
  OdString getStreamName(const OdUInt32 index) const;
  NwSubStreamDef& getStreamDef(const OdUInt32 index);
  OdStreamBufPtr getStreamByName(const OdString& sName, OdUInt32 nChunk = 0);
  OdStreamBufPtr getStream(const OdUInt32 index, OdUInt32 nChunk = 0);
  OdUInt32 getChunksCount(const OdString& sName) const;
  OdUInt32 getChunksCount(const OdUInt32 index) const;
  void setDumpPath(OdString path = OD_T(""));
  OdString getDumpPath() const;

private:
  OdResult parseStream(const OdUInt32 index, OdArray<OdStreamBufPtr>& output);
  OdResult parseStreams();
  OdNwLoadError::Enum readStreamConfig(OdStreamBufPtr stream, TNwStreamConfig& config);

private:
  OdInt32 m_nInternalVersion;
  bool m_useCompressedMode;
  OdInt64 m_nSecondSignaturePos;
  bool m_bIsBinary;
  TNwStreamConfig m_oStreamConfig;
  OdArray<NwSubStreamDef> m_aSubStreamsDefs;
  OdStreamBufPtr m_oStream;
  OdString m_sDumpPath;
};


#endif // __NWSTREAMSPLITTER_H__
