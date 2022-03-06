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

#ifndef _ODTV_IDACCESS_H_INCLUDED_
#define _ODTV_IDACCESS_H_INCLUDED_

#include "TD_PackPush.h"
#include "Tv.h"
#include "TvIObject.h"
#include "OdDbStub.h"

/** \details
    This class implements memory-resident ObjectId objects for OdTvDatabaseImpl objects.  

    \remarks
    This class is for the internal using only
*/
class OdTvIdAccess : public OdTvId
{
public:
  static void objectSet(OdTvId* pId, void* pObj)
  {
    if ( pId )
      (static_cast<OdTvIdAccess*>(pId))->m_pImplId = pObj;
  }

  static void* objectGet(const OdTvId* pId)
  {
    if (pId)
      return (static_cast<const OdTvIdAccess*>(pId))->m_pImplId;
    return NULL;
  }
};

/** \details

This template class provides the access to the protected data of the typified implementation of the smart pointers for instances of classes
derived from the OdTvIObject class.
*/
template <class T> class OdTvSmartPtrAccess : public OdTvSmartPtr<T>
{
public:

  static T* get(const OdTvSmartPtr<T>* pPtr)
  {
    if (pPtr)
      return static_cast<T*>((static_cast<const OdTvSmartPtrAccess*>(pPtr))->m_pObject);

    return NULL;
  }
};

template <class T, class S>
S openDbObjectFromTvId(const T& id, OdDb::OpenMode mode)
{
  void* pDbId = OdTvIdAccess::objectGet(&id);
  OdTvDbObjectId dbId = OdTvDbObjectId(static_cast<OdDbStub*>(pDbId));

  // partial loading support 
  OdDbStub* stub = dbId;
  if (stub->flags(kOdDbIdLoading|kObjectLeftOnDisk) != 0)
  { 
    return S();
  }

  return dbId.openObject(mode);
}

template <class T>
OdTvDbObjectId getDbIdFromTvId(const T& id)
{
  void* pDbId = OdTvIdAccess::objectGet(&id);
  return OdTvDbObjectId(static_cast<OdDbStub*>(pDbId));
}

#include "TD_PackPop.h"

#endif //_ODTV_OBJECTID_H_INCLUDED_
