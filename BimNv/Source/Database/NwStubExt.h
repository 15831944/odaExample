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

#ifndef _OD_NWTUBEXT_INCLUDED_
#define _OD_NWTUBEXT_INCLUDED_

#include "OdDbStub.h"
#include "NwObject.h" // "NwObjectImpl.h"

class OdNwStubExt : public OdDbStub
{
public:
  OdNwStubExt(OdDbBaseDatabase* pDatabase, const OdDbHandle& h)
    : OdDbStub(pDatabase, h)
  {
  }

  //void bindObject(OdNwObject* pObj)
  //{
  //  setObject(pObj);
  //  setFlags(0, kOdDbIdErased|kErasedPermanently);
  //  pObj->objectId() = this;
  //  //OdNwObjectImpl::cast(pObj)->setDatabase(static_cast<NwDatabaseImpl*>(static_cast<OdNwObject*>(database())));
  //}

  //void erasePermanently()
  //{
  //  setFlags(kErasedPermanently, kErasedPermanently);
  //  detachObject();
  //}

  void detachObject()
  {
    if (getObject().get() && getObject()->numRefs() > 1)
    {
      OdNwObject* pObj = OdNwObject::cast(getObject()).get();
      if (pObj)
      {
        if (pObj->objectId() == OdNwObjectId(this))
        {
          pObj->objectId() = OdNwObjectId::kNull;
          //OdNwObjectImpl::cast(pObj)->setDatabase(0);
        }
        getObject().release();
      }
    }
  }

  OdNwObjectId ownerId() const 
  { 
    return m_pOwner; 
  }
  void setOwnerId(OdNwObjectId id) 
  { 
    m_pOwner = id; 
  }
};

class OdNwStubExtFactory : public OdDbStubFactory
{
public:
  virtual OdDbStub* createStub(OdDbBaseDatabase* pDb, const OdDbHandle& h)
  {
    return new OdNwStubExt(pDb, h);
  }
  virtual void freeStub(OdDbStub* pStub)
  {
    if (pStub)
    {
      OdNwStubExt* pStubExt = static_cast<OdNwStubExt*>(pStub);
      pStubExt->detachObject();
      delete pStubExt;
    }
  }
};

#endif // _OD_NWTUBEXT_INCLUDED_

