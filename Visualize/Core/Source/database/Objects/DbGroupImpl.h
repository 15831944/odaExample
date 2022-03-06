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

#ifndef _OD_DB_GROUP_IMPL_
#define _OD_DB_GROUP_IMPL_


#include "OdArray.h"
#include "DbSystemInternals.h"
#include "DbGroup.h"
#include "DbObjectImpl.h"

class OdTvDbGroupImpl : public OdTvDbObjectImpl
{
  static OdTvDbGroupImpl* getImpl(const OdTvDbGroup *pObj)
  { return (OdTvDbGroupImpl*)OdTvDbSystemInternals::getImpl(pObj);}
  enum Flags { Anonymous = 1, Inaccessible = 2 };
public:
  OdString         m_strDescription;
  OdHardPtrIdArray m_Ids;

  OdInt16          m_Flags;
  bool isAnonymous() const {return (m_Flags & Anonymous) != 0; }
  bool isInaccessible() const {return (m_Flags & Inaccessible) != 0; }
  bool             m_bSelectable;

  OdTvDbGroupImpl();
	void audit(OdTvDbAuditInfo* pAuditInfo);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format,
                    OdDb::DwgVersion version);
private:
  inline bool has(OdTvDbObjectId id);
  inline OdHardPtrIdArray::iterator find(OdTvDbObjectId id);
  inline OdHardPtrIdArray::iterator internalIterator(OdUInt32 extInd);

  friend class OdTvDbGroup;
};

// The group iterator class.
//
class OdTvDbGroupIteratorImpl: public OdRxObjectImpl<OdTvDbGroupIterator>
{
protected:
  OdHardPtrIdArray::iterator m_pItem;
  OdHardPtrIdArray::iterator m_pEndItem;
public:
  OdTvDbGroupIteratorImpl(OdHardPtrIdArray::iterator begin, OdHardPtrIdArray::iterator end )
    : m_pItem(begin), m_pEndItem(end) 
  {
    skipErased();
  }
  static OdTvDbGroupIteratorPtr createObject(OdHardPtrIdArray::iterator begin, 
        OdHardPtrIdArray::iterator end )
  {
    return OdTvDbGroupIteratorPtr((OdTvDbGroupIterator*)new OdTvDbGroupIteratorImpl(begin, end), kOdRxObjAttach);
  }

  OdTvDbObjectPtr getObject(OdDb::OpenMode openMode)
  {
    return m_pItem->openObject(openMode);
  }

  OdTvDbObjectId objectId() const { return *m_pItem; }

  bool done() const { return m_pItem == m_pEndItem; }

  bool next() 
  {
    if(OdTvDbGroupIteratorImpl::done())
      return false;
    ++m_pItem;
    skipErased();
    return !OdTvDbGroupIteratorImpl::done();
  }
private:
  void skipErased()
  {
    while (m_pItem != m_pEndItem && ((*m_pItem).isNull() || (*m_pItem).isErased()))
    {
      ++m_pItem;
    }
  }
};


inline bool OdTvDbGroupImpl::has(OdTvDbObjectId id)
{
  return find(id) != m_Ids.end();
}

inline OdHardPtrIdArray::iterator OdTvDbGroupImpl::find(OdTvDbObjectId id)
{
  OdHardPtrIdArray::iterator curIt = m_Ids.begin(),
                             endIt = m_Ids.end();
  for (; curIt != endIt; ++curIt)
  {
    if (*curIt == id)
      break;
  }
  return curIt;
}

inline OdHardPtrIdArray::iterator OdTvDbGroupImpl::internalIterator(OdUInt32 extInd)
{
  OdHardPtrIdArray::iterator curIt = m_Ids.begin(),
                             endIt = m_Ids.end();
  for (; curIt != endIt; ++curIt)
  {
    if (!(*curIt).isNull() && !(*curIt).isErased())
    {
      if (extInd == 0)
        return curIt;
      --extInd;
    }
  }
  if (extInd == 0)
    return endIt;

  // Index is out of array bounds
  throw OdError(eInvalidIndex);
}

#endif
