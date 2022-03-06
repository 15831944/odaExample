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

#ifndef _ODDBPROXYENTITYIMPL_INCLUDED_
#define _ODDBPROXYENTITYIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "ProxyStuff.h"
#include "DbSystemInternals.h"
#include "DbProxyEntity.h"
#include "OdBinaryData.h"
#include "DbEntityWithGrData.h"


////////////////////////////////////////////////////////////////////////
class OdDbEntityWithGrDataPEImpl : public OdDbEntityWithGrDataPE
{
public:
  virtual bool worldDraw(const OdDbEntity * pEnt, OdGiWorldDraw* pWd) const;
};


//////////////////////////////////////////////////////////////////////////////

class DBIO_EXPORT OdDbProxyEntityImpl : public OdDbEntityImpl, public OdProxyStuff
{
  static OdDbProxyEntityImpl* getImpl(const OdDbProxyEntity *pObj)
  { return (OdDbProxyEntityImpl*)OdDbSystemInternals::getImpl(pObj);}


  OdDbProxyEntity::GraphicsMetafileType m_graphicsMetafileType;

protected:
  virtual OdDbEntityImpl* getEntityImpl() const { return (OdDbEntityImpl*)this; }

public:
  OdDbProxyEntityImpl()
      :m_graphicsMetafileType(OdDbProxyEntity::kNoMetafile)
  { setAProxy(true); }

  void adjustProxyForSave(OdDbFiler* pFiler) { OdProxyStuff::adjustProxyForSave(pFiler); }

  virtual OdProxyStuff* getProxyStuff() { return this; }

  virtual OdDbObjectPtr getObject() const;

  OdRxClass* saveAsClass(OdRxClass* pClass) const { return OdProxyStuff::saveAsClass(pClass); }

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format,
    OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format,
    OdDb::DwgVersion version);

  static void setWrapper(OdDbProxyEntity * pEnt)
  { getImpl(pEnt)->setWrapperClass(); }

  friend class OdDbProxyEntity;
};

#endif // _ODDBPROXYENTITYIMPL_INCLUDED_
