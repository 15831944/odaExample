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

#ifndef _ODDBIDBUFIMPL_INCLUDED_
#define _ODDBIDBUFIMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbIdBuffer.h"
#include "DbObjectImpl.h"

#include "OdLinkedArray.h"


typedef OdLinkedArray<OdTvDbObjectId, OdMemoryAllocator<OdTvDbObjectId> >   IdArray;

class OdTvDbIdBufferImpl : public OdTvDbObjectImpl
{
  static OdTvDbIdBufferImpl* getImpl(const OdTvDbIdBuffer *pObj)
  { return (OdTvDbIdBufferImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  IdArray          m_Ids;
  OdUInt8          m_UnkUInt8;

public:
  OdTvDbIdBufferImpl()
    : m_Ids(128)    // Page size
    , m_UnkUInt8(0)
  {}

  friend class OdTvDbIdBuffer;
  friend class OdTvDbIdBufferIteratorImpl;

private:
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
};

#endif // _ODDBIDBUFIMPL_INCLUDED_
