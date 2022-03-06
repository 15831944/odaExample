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
#ifndef __NW_STREAMLOADER_H__
#define __NW_STREAMLOADER_H__

#include "OdBinaryData.h"
#include "NwStreamType.h"
#include "NwStreamContext.h"
#include "NwStreamAlignment.h"
#define STL_USING_MEMORY
#define STL_USING_FUNCTIONAL
#define STL_USING_MAP
#include "OdaSTL.h"

#include "TD_PackPush.h"

typedef std::map<OdUInt32, OdUInt64> OdReuseMap;

class OdNwDatabaseImpl;
class OdNwStreamLoader;

typedef std::shared_ptr<OdNwStreamLoader> OdNwStreamLoaderPtr;
typedef std::map<NwStreamType::Enum, OdNwStreamLoaderPtr> OdNwLoadersMap;

class OdNwStreamLoader: public std::enable_shared_from_this<OdNwStreamLoader>
{
public:
  OdNwStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx)
    : m_context(ctx)
    , m_bParsed (false)
  {}
  virtual ~OdNwStreamLoader() {};
  virtual OdResult parseStream() = 0;

  virtual void setLinkLoaderGetter(const std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)>& getLoader);
  inline bool isParsed() { return m_bParsed; }

  std::shared_ptr<OdNwStreamLoader> getPtr() {
    return shared_from_this();
  }

protected:
  void fillReuseMapping(OdUInt32 index, OdInt32 positionOffset = 0);
  void alignPointer();
  std::shared_ptr<OdNwStreamContext> context();

protected:
  std::shared_ptr<OdNwStreamContext>  m_context;
  OdReuseMap                m_reuseMapping;   // map for the [UInt32_index : UInt64_filePos] pairs
  bool                      m_bParsed;        // this flag means stream is parsed (for partial loading)
};

#include "TD_PackPop.h"

#endif // __NW_STREAMLOADER_H__
