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

#ifndef _ODDBVIEWREPBLOCKREFIMPL_INCLUDED_
#define _ODDBVIEWREPBLOCKREFIMPL_INCLUDED_

#include "DbBlockReferenceImpl.h"
#include "DbViewRepBlockReference.h"

class OdDbViewRepBlockReferenceImpl : public OdDbBlockReferenceImpl
{ 
public:
  OdDbViewRepBlockReferenceImpl() {}
  void setOwnerViewportId(const OdDbObjectId& viewportId) {m_ownerViewportId = viewportId;}
  OdDbObjectId ownerViewportId() const                    {return m_ownerViewportId;}

  virtual void audit(OdDbAuditInfo* pAuditInfo) ODRX_OVERRIDE;

private:
  OdDbObjectId m_ownerViewportId;

  static OdDbViewRepBlockReferenceImpl* getImpl(const OdDbViewRepBlockReference *pObj)
  { 
    return (OdDbViewRepBlockReferenceImpl*)OdDbSystemInternals::getImpl(pObj);
  }

  friend class OdDbViewRepBlockReference;
};

#endif // _ODDBVIEWREPBLOCKREFIMPL_INCLUDED_
