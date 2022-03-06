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

#ifndef _NW_MODELITEM_RESOLVER_H_
#define _NW_MODELITEM_RESOLVER_H_

#include "NwModelItem.h"
#include "MemoryStream.h"
#include "NwDatabase.h"

//----------------------------------------------------------
//
// OdNwModelItemResolver
//
//----------------------------------------------------------

class OdNwModelItemResolver;
typedef OdSmartPtr<OdNwModelItemResolver> OdNwModelItemResolverPtr;

class OdNwModelItemResolver : public OdRxObject {
public:
  static OdNwModelItemResolverPtr
  createObject(OdInt64 offset, OdInt64 size, OdStreamBufPtr pStream, OdNwDatabase* pDb);

  OdRxObject* queryX(const OdRxClass* pClass) const;
  OdStreamBufPtr getStream() const;

  OdNwModelItemResolver();

  OdInt64 getSize() const;
  OdInt64 getOffset() const;

private:
  mutable OdStreamBufPtr m_pStream;
  mutable OdInt64        m_nOffset;
  mutable OdInt64        m_nSize;
  mutable OdNwObjectPtr  m_pObject;
  mutable OdNwDatabase*  m_pDb;
};

#endif // _NW_MODELITEM_RESOLVER_H_
