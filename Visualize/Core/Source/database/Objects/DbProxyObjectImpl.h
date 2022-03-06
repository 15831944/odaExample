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

#ifndef _ODDBPROXYOBJECTIMPL_INCLUDED_
#define _ODDBPROXYOBJECTIMPL_INCLUDED_


#include "ProxyStuff.h"
#include "DbSystemInternals.h"
#include "DbProxyObject.h"
#include "DbObjectImpl.h"

class DBIO_EXPORT OdTvDbProxyObjectImpl : public OdTvDbObjectImpl, public OdTvProxyStuff
{
public:
  static OdTvDbProxyObjectImpl* getImpl(const OdTvDbProxyObject *pObj)
  {
    return (OdTvDbProxyObjectImpl*)OdTvDbSystemInternals::getImpl(pObj);
  }
  OdTvDbProxyObjectImpl() { setAProxy(true); }

  void adjustProxyForSave(OdTvDbFiler* pFiler) { OdTvProxyStuff::adjustProxyForSave(pFiler); }

  OdTvProxyStuff* getProxyStuff() { return this; }

  virtual OdTvDbObjectPtr getObject() const;

  OdRxClass* saveAsClass(OdRxClass* pClass) const { return OdTvProxyStuff::saveAsClass(pClass); }

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format,
    OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format,
    OdDb::DwgVersion version);

  static void setWrapper(OdTvDbProxyObject * pObj)
  { getImpl(pObj)->setWrapperClass(); }

  friend class OdTvDbProxyObject;
};

#endif // _ODDBPROXYOBJECTIMPL_INCLUDED_
