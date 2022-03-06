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


#ifndef _ODDB_DBSTUBEXT_INCLUDED_
#define _ODDB_DBSTUBEXT_INCLUDED_


#include "OdDbStub.h"
#include "DbSystemInternals.h"


class TOOLKIT_EXPORT OdTvDbStubExt : public OdDbStub
{
public:
  OdTvDbStubExt(OdDbBaseDatabase* pDatabase, const OdDbHandle& h)
    : OdDbStub(pDatabase, h)
  {}

  void bindObject(OdTvDbObject* pObj);
  void detachObject();
  void erasePermanently();

  OdTvDbObjectId ownerId() const { return m_pOwner; }
  void setOwnerId(OdTvDbObjectId id) { m_pOwner = id; }

  //This function should be used only after all objects are loaded:
  bool isObjectEffectivelyErased()
  { 
    if (this->getObject().isNull())
      return true;

    if (this->flags(kOdDbIdErased|kErasedPermanently) != 0)
      return true;

    // Check owners
    OdTvDbStubExt* pOwner = (OdTvDbStubExt*)owner();
    if (!pOwner)
      return false;

    return pOwner->isObjectEffectivelyErased();
  }
};


class TOOLKIT_EXPORT OdTvDbStubExtFactory : public OdDbStubFactory
{
public:
  virtual OdDbStub* createStub(OdDbBaseDatabase* pDb, const OdDbHandle& h);
  virtual void freeStub(OdDbStub* pStub);
};


#endif // _ODDB_DBSTUBEXT_INCLUDED_
