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

#ifndef _RXDICTIONARYIMPL_INC_
#define _RXDICTIONARYIMPL_INC_

#include "BaseDictionaryImpl.h"
#include "RxDictionary.h"
#include "RxObjectImpl.h"
#include "ThreadsCounter.h"

#ifdef _MSC_VER
#pragma warning( disable : 4097 ) // typedef-name 'typedef-name' used as synonym for class-name 'class-name'
#endif

#if defined(_MSC_VER)
#ifndef _DEBUG
#pragma warning (push)
#pragma warning( disable : 4702 )
#endif
#endif

class OdMutexDummy
{
public:
#if defined(_MSC_VER)
#ifdef _DEBUG
  OdUInt32 m_lastThreadId;
  OdMutexDummy() : m_lastThreadId(0) {}
#endif
#endif
  void lock() {
#if defined(_MSC_VER)
#ifdef _DEBUG
    OdUInt32 nThreadId=::GetCurrentThreadId();
    if( m_lastThreadId==0 ) {
      m_lastThreadId = nThreadId;
    }
    else {
      ODA_ASSERT_ONCE( ( "Multithreaded access to unprotected object detected", m_lastThreadId == nThreadId ) );
    }
#endif
#endif
  }
  void unlock() {
#if defined(_MSC_VER)
#ifdef _DEBUG
    m_lastThreadId=0;
#endif
#endif
  }
};

class OdMutexAux
{
public:
  OdMutexAux()
  {
  }

  void lock()
  {
    if(odThreadsCounter())
      m_mutex.get()->lock();
  }

  void unlock()
  {
    if(odThreadsCounter())
      m_mutex.get()->unlock();
  }

private:
  OdMutexPtr m_mutex;
};

template<class TMutex>
class OdDicAutoLock
{
public:
  OdDicAutoLock(const TMutex* pMutex) { m_pMutex = const_cast<TMutex*>(pMutex); m_pMutex->lock(); }
  ~OdDicAutoLock() { m_pMutex->unlock(); }
private:
  TMutex* m_pMutex;
};

#ifndef TD_SINGLE_THREAD
#define DD_DIC_AUTOLOCK() OdDicAutoLock<TMutex> autoLock(this)
#else
#define DD_DIC_AUTOLOCK()
#endif


template <class ArrayType, class TMutex>
class OdRxDictionaryIteratorImpl
  : private OdBaseIteratorImpl<ArrayType, OdString, OdRxObjectPtr>
  , public  OdRxObjectImpl<OdRxDictionaryIterator>
{
  OdRxDictionaryPtr m_pParent;
  TMutex* m_pMutex;
  OdRxDictionaryIteratorImpl& operator = (const OdRxDictionaryIteratorImpl&);
public:
  OdRxDictionaryIteratorImpl(OdRxDictionary* pParent, ArrayType& items, bool atBeginning, TMutex* pMutex)
    : m_pParent(pParent) // to lock parent
    , m_pMutex(pMutex)
  {
    m_pMutex->lock();
    OdBaseIteratorImpl<ArrayType, OdString, OdRxObjectPtr>::init(items, atBeginning);
  }

  ~OdRxDictionaryIteratorImpl()
  {
    m_pMutex->unlock();
  }

  static OdRxDictionaryIteratorPtr createObject(OdRxDictionary* pParent, ArrayType& items, bool atBeginning, TMutex* pMutex)
  {
    OdRxDictionaryIteratorPtr pRes;
    pRes.attach((OdRxObject*)new OdRxDictionaryIteratorImpl(pParent, items, atBeginning, pMutex));
    return pRes;
  }

  OdRxObjectPtr object() const
  {
    return OdBaseIteratorImpl<ArrayType, OdString, OdRxObjectPtr>::getItem();
  }

  OdString getKey() const
  {
    return OdBaseIteratorImpl<ArrayType, OdString, OdRxObjectPtr>::getKey();
  }

  OdUInt32 id() const
  {
    return OdBaseIteratorImpl<ArrayType, OdString, OdRxObjectPtr>::id();
  }

  bool done() const
  {
    return OdBaseIteratorImpl<ArrayType, OdString, OdRxObjectPtr>::isDone();
  }

  bool next()
  {
    return OdBaseIteratorImpl<ArrayType, OdString, OdRxObjectPtr>::next();
  }
};


const OdUInt32 kOdDictItemNullId = ((OdUInt32)-1);
const OdUInt32 kOdDictItemLastId = ((OdUInt32)-2);

class OdRxDictionaryItemImpl
{
  OdString      m_key;
  OdRxObjectPtr m_val;
  OdUInt32      m_nextId;
public:
  OdRxDictionaryItemImpl() : m_nextId(kOdDictItemNullId) {}
  OdRxDictionaryItemImpl(const OdString& key, const OdRxObjectPtr& val)
    : m_key(key), m_val(val), m_nextId(kOdDictItemNullId) {}

  const OdString& getKey() const { return m_key; }
  void setKey(const OdString& key) { m_key = key; }
  const OdRxObjectPtr& getVal() const { return m_val; }
  void setVal(const OdRxObjectPtr& val) { m_val = val; }
  bool isErased() const { return m_val.isNull(); }
  void erase() { m_val.release(); }

  OdUInt32 nextId() const { return m_nextId; }
  void setNextId(OdUInt32 nextId) { m_nextId = nextId; }
};


template < class Pr = std::less<OdString>, class TMutex = OdMutexAux >
class OdRxDictionaryImpl
  : public OdBaseDictionaryImpl<OdString, OdRxObjectPtr, Pr, OdRxDictionaryItemImpl>
  , public OdRxDictionary
  , public TMutex
{
  OdRxDictionaryImpl& operator = (const OdRxDictionaryImpl&);
  typedef ::OdBaseDictionaryImpl<OdString, OdRxObjectPtr, Pr, OdRxDictionaryItemImpl> BaseClass;
  typedef ::OdRxDictionaryItemImpl Item;
  OdUInt32  m_firstErasedId;
  OdUInt32  m_numErased;
public:
  OdRxDictionaryImpl()
    : m_firstErasedId(kOdDictItemLastId)
    , m_numErased(0)
  {
  }

  ~OdRxDictionaryImpl()
  {
  }

#if defined(_WIN32_WCE)
#define OD_TYPENAME_TEMP
#else
# ifdef EMCC
#   define OD_TYPENAME_TEMP typename
# else
#   define OD_TYPENAME_TEMP OD_TYPENAME
# endif
#endif

  OdRxDictionaryIteratorPtr newIterator(OdRx::DictIterType type = OdRx::kDictCollated)
  {
    OdRxDictionaryIteratorPtr pNewIter;
    switch(type)
    {
    case OdRx::kDictSorted:
      pNewIter = OdRxDictionaryIteratorImpl<BaseClass, TMutex>::createObject(this, *this, true, this);
      BaseClass::sort();
      break;
    case OdRx::kDictCollated:
      pNewIter = OdRxDictionaryIteratorImpl<OD_TYPENAME_TEMP BaseClass::ItemArray, TMutex>::createObject(this, this->m_items, true, this);
      break;
    case OdRx::kDictReversed:
      pNewIter = OdRxDictionaryIteratorImpl<OD_TYPENAME_TEMP BaseClass::ItemArray, TMutex>::createObject(this, this->m_items, false, this);
      break;
    }
    return pNewIter;
  }

#undef ID_TYPENAME_TEMP

  bool isCaseSensitive() const
  {
    Pr less;
    return less(OdString(OD_T("A")), OdString(OD_T("a")));
  }


  OdRxObjectPtr getAt(const OdString& key) const
  {
    DD_DIC_AUTOLOCK();
    typename BaseClass::SortedItemArray::iterator pItem;
    if(BaseClass::find(key, pItem))
    {
      return this->m_items[*pItem].getVal();
    }
    else
    {
      return NULL;
    }
  }

  OdRxObjectPtr getAt(OdUInt32 id) const
  {
    DD_DIC_AUTOLOCK();
    if(id < this->m_items.size())
    {
      return this->m_items[id].getVal();
    }
    else
    {
      return NULL;
    }
  }

  OdRxObjectPtr putAt(const OdString& key, OdRxObject* pObject, OdUInt32* pResId = NULL)
  {
    DD_DIC_AUTOLOCK();
    typename BaseClass::SortedItemArray::iterator pId;
    OdRxObjectPtr OldObjPtr;
    OdUInt32 id;
		if(BaseClass::find(key, pId))
    {
      // there is key
      OldObjPtr = this->m_items[*pId].getVal();
      this->m_items[id = *pId].setVal(pObject);
    }
    else
    {
      if(m_numErased)
      {
        --m_numErased;
        id = m_firstErasedId;
        OdRxDictionaryItemImpl& item = this->m_items[id];
        m_firstErasedId = item.nextId();
        item.setNextId(kOdDictItemNullId);
        item.setKey(key);
        item.setVal(pObject);
        this->m_sortedItems.insert(pId, id);
      }
      else
      {
        id = BaseClass::insert(Item(key, pObject), pId);
      }
    }
    if(pResId)
    {
      *pResId = id;
    }
    return OldObjPtr;
  }

  OdRxObjectPtr putAt(OdUInt32 id, OdRxObject* pObject)
  {
    DD_DIC_AUTOLOCK();
    if(id < this->m_items.size())
    {
      OdRxObjectPtr pOldObj = this->m_items[id].getVal();
      this->m_items[id].setVal(pObject);
      return pOldObj;
    }
    else
    {
      throw OdError(eKeyNotFound);
    }
	//	pmk 08.27.2004 -- Unreachable Code
	//  return OdRxObjectPtr();
  }

  bool resetKey(OdUInt32 id, const OdString& newKey)
  {
    DD_DIC_AUTOLOCK();
    return BaseClass::resetKey(id, newKey);
  }

  bool atKeyAndIdPut(const OdString& newKey, OdUInt32 id, OdRxObject* pObject)
  {
    DD_DIC_AUTOLOCK();
    typename BaseClass::SortedItemArray::iterator before;
		if (BaseClass::find(newKey, before))
    {
      return false;
    }
    this->m_items[id].setKey(newKey);
    this->m_items[id].setVal(pObject);
    BaseClass::sort();
		BaseClass::find(newKey, before);
    this->m_sortedItems.insert(before, id);
    return true;
  }

  OdRxObjectPtr remove(typename BaseClass::SortedItemArray::iterator& pSortedItem)
  {
    DD_DIC_AUTOLOCK();
    OdRxObjectPtr retVal;
    retVal = this->m_items[*pSortedItem].getVal();
    if(this->m_items.size()-1 == *pSortedItem)
    {
      this->m_items.erase(this->m_items.begin() + *pSortedItem);
    }
    else
    {
      OdRxDictionaryItemImpl& item = this->m_items[*pSortedItem];
      item.setVal((OdRxObjectPtr)0);
      item.setNextId(m_firstErasedId);
      m_firstErasedId = *pSortedItem;
      ++m_numErased;
    }
    this->m_sortedItems.erase(pSortedItem);
    return retVal;
  }

  OdRxObjectPtr remove(const OdString& key)
  {
    DD_DIC_AUTOLOCK();
    typename BaseClass::SortedItemArray::iterator pSortedItem;
    OdRxObjectPtr retVal;
		if (BaseClass::find(key, pSortedItem))
    {
      retVal = remove(pSortedItem);
    }
    return retVal;
  }

  OdRxObjectPtr remove(OdUInt32 id)
  {
    DD_DIC_AUTOLOCK();
    OdRxObjectPtr retVal;
    if(this->has(id))
    {
      typename BaseClass::SortedItemArray::iterator pSortedItem;
			if(BaseClass::find(this->m_items[id].getKey(), pSortedItem))
      {
        retVal = remove(pSortedItem);
      }
    }
    return retVal;
  }

  bool has(const OdString& entryName) const
  {
    DD_DIC_AUTOLOCK();
    typename BaseClass::SortedItemArray::iterator pSortedItem;
    return BaseClass::find(entryName, pSortedItem);
  }

  bool has(OdUInt32 id) const
  {
    DD_DIC_AUTOLOCK();
    return (id < this->m_items.size() && !this->m_items[id].isErased());
  }

  OdUInt32 idAt(const OdString& key) const
  {
    DD_DIC_AUTOLOCK();
    typename BaseClass::SortedItemArray::iterator pId;
    bool res = BaseClass::find(key, pId);
    return (res ? *pId : OdRx::kNullDictId);
  }

  OdString keyAt(OdUInt32 id) const
  {
    DD_DIC_AUTOLOCK();
    return this->m_items[id].getKey();
  }

  OdUInt32 numEntries() const
  {
    return (this->m_items.size() - m_numErased);
  }

  void clear()
  {
    m_firstErasedId = kOdDictItemLastId;
    m_numErased = 0;
    BaseClass::clear();
  }
};

#if defined(_MSC_VER)
#ifndef _DEBUG
#pragma warning (pop)
#endif
#endif

#endif // _RXDICTIONARYIMPL_INC_
