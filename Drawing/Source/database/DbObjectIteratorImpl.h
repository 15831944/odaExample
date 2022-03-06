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

#ifndef _ODDBOBJECTITERATORIMPL_H_INCLUDED_
#define _ODDBOBJECTITERATORIMPL_H_INCLUDED_

#include "OdPlatform.h"
#include "DbObjectIterator.h"
#include "RxObjectImpl.h"
#include "OdLinkedArray.h"

typedef OdLinkedArray<OdDbObjectId, OdMemoryAllocator<OdDbObjectId> > OdIdContainer;
typedef OdIdContainer::iterator OdIdContainerIterator;
typedef OdIdContainer::const_iterator OdIdContainerConstIterator;

//----------------------------------------------------------
//
// OdDbObjectIteratorImpl
//
//----------------------------------------------------------
class OdDbObjectIteratorImpl : public OdRxObjectImpl<OdDbObjectIterator>
{
protected:
  OdDbObjectIteratorImpl(const OdIdContainer* pContainer)
    : m_pContainer(pContainer) {}

public:
  static OdRxObjectPtr createObject(const OdIdContainer* pContainer);
 
  virtual OdRxObjectPtr clone() const;

  void start(bool bForward = true, bool bSkipDeleted = true);
  bool done() const;
  OdDbObjectId objectId() const;
  OdDbEntityPtr entity(OdDb::OpenMode openMode = OdDb::kForRead, bool openErased = false);
  bool seek(OdDbObjectId id);
  bool seek(const OdDbEntity* pEntity);
  void step(bool bForward = true, bool bSkipDeleted = true);

  TD_USING(OdRxObjectImpl<OdDbObjectIterator>::seek);

protected:
  virtual void skipDeleted(bool bForward);

  const OdIdContainer* m_pContainer;
  OdIdContainerConstIterator m_iter;
};

typedef OdSmartPtr<OdDbObjectIteratorImpl> OdDbObjectIteratorImplPtr;

//----------------------------------------------------------
//
// OdDbNonDBROObjectIteratorImpl
//
//----------------------------------------------------------
class OdDbNonDBROObjectIteratorImpl : public OdDbObjectIteratorImpl
{
  OdDbNonDBROObjectIteratorImpl(const OdIdContainer* pContainer)
    : OdDbObjectIteratorImpl(pContainer) {}

public:
  static OdRxObjectPtr createObject(const OdIdContainer* pContainer);

  OdDbObjectId objectId() const;
  OdDbEntityPtr entity(OdDb::OpenMode, bool);
  bool seek(const OdDbEntity* pEntity);

  TD_USING(OdDbObjectIteratorImpl::seek);

protected:
  virtual void skipDeleted(bool bForward);
};

typedef OdSmartPtr<OdDbNonDBROObjectIteratorImpl> OdDbNonDBROObjectIteratorImplPtr;

//----------------------------------------------------------
//
// OdDbAc15ListObjectIteratorImpl
//
//----------------------------------------------------------
class OdDbAc15ListObjectIteratorImpl : public OdRxObjectImpl<OdDbObjectIterator>
{
public:
  static OdRxObjectPtr createObject(OdDbObjectId firstId, OdDbObjectId lastId);

  virtual OdRxObjectPtr clone() const;
  
  void start(bool bForward = true, bool bSkipDeleted = true);
  bool done() const;
  OdDbObjectId objectId() const;
  OdDbEntityPtr entity(OdDb::OpenMode openMode, bool openErased);
  bool seek(OdDbObjectId id);
  bool seek(const OdDbEntity* pEntity);
  void step(bool bForward, bool bSkipDeleted);

private:
  OdDbAc15ListObjectIteratorImpl(OdDbObjectId firstId, OdDbObjectId lastId)
    : m_firstId(firstId), m_lastId(lastId) {}

  void skipDeleted(bool bForward);

  OdDbObjectId m_id;
  OdDbObjectId m_firstId;
  OdDbObjectId m_lastId;
};

typedef OdSmartPtr<OdDbAc15ListObjectIteratorImpl> OdDbAc15ListObjectIteratorImplPtr;

#endif //_ODDBOBJECTITERATORIMPL_H_INCLUDED_
