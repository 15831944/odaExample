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

#ifndef __NWSTREAMCONTEXT_H__
#define __NWSTREAMCONTEXT_H__

#include "NwExport.h"
#include "NwStreamType.h"
#include "NwStreamConfig.h"
#include "NwStreamAlignment.h"
#include "NwFormatVersionEx.h"
#define STL_USING_MEMORY
#include "OdaSTL.h"

class OdNwDatabaseImpl;
class OdNwPathLinkMap;
typedef std::weak_ptr<OdNwPathLinkMap> OdNwPathLinkMapWeakPtr;

class OdNwStreamContext
{
public:
  OdNwStreamContext()
    : m_nAlignmentMode(OdNmStreamAlignment::EightBytes)
    , m_nVersion(NwFormatVersionEx::NAWISWORKS2016)
    , m_pDb(NULL)
    , m_pPathLinkMap()
  {}
  OdNwStreamContext(
    OdNwDatabaseImpl* db
    , const OdStreamBufPtr &stream
    , OdNmStreamAlignment::Enum alignmentMode
    , NwFormatVersionEx::Enum version)
    : m_pStream(stream)
    , m_nAlignmentMode(alignmentMode)
    , m_nVersion(version)
    , m_pDb (db)
    , m_pPathLinkMap()
  {}
  OdNwStreamContext(const OdNwStreamContext& ctx)
    : m_pStream(ctx.m_pStream)
    , m_nAlignmentMode(ctx.m_nAlignmentMode)
    , m_nVersion(ctx.m_nVersion)
    , m_pDb(ctx.m_pDb)
    , m_pPathLinkMap(ctx.m_pPathLinkMap)
  {
  }
  OdNwStreamContext& operator = (const OdNwStreamContext& ctx)
  {
    if (this != &ctx)
    { 
      m_pStream = ctx.m_pStream;
      m_pDb = ctx.m_pDb;
      m_nAlignmentMode = ctx.m_nAlignmentMode;
      m_nVersion = ctx.m_nVersion;
      m_pPathLinkMap = ctx.m_pPathLinkMap;
    }
    return *this;
  }
  virtual ~OdNwStreamContext()
  {}
public:
  inline OdNwDatabaseImpl* getDatabase() const
  {
    return m_pDb;
  }
  inline OdStreamBufPtr getStream() const
  {
    return m_pStream;
  }
  inline OdNmStreamAlignment::Enum getAlignment() const
  {
    return m_nAlignmentMode;
  }
  inline NwFormatVersionEx::Enum getVersion() const
  {
    return m_nVersion;
  }
  inline OdNwPathLinkMapWeakPtr getPathLinkMap() const
  {
    return m_pPathLinkMap;
  }

public:
  OdNwStreamContext& setStream(const OdStreamBufPtr& stream)
  {
    m_pStream = stream;
    return *this;
  }

  inline void setPathLinkMap(OdNwPathLinkMapWeakPtr pPathLinkMap)
  {
    m_pPathLinkMap = pPathLinkMap;
  }

protected:
  OdStreamBufPtr m_pStream;
  OdNmStreamAlignment::Enum m_nAlignmentMode;
  NwFormatVersionEx::Enum m_nVersion;
  OdNwDatabaseImpl* m_pDb;
  OdNwPathLinkMapWeakPtr m_pPathLinkMap;
};

typedef std::shared_ptr<OdNwStreamContext> OdNwStreamContextPtr;
typedef std::weak_ptr<OdNwStreamContext> OdNwStreamContextWeakPtr;

#endif // __NWSTREAMCONTEXT_H__
