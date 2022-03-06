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

// ODA_MT_DB_BEGIN
// ODA_MT_DB_1_BEGIN

#ifndef _OD_MUTEXPOOL_INCLUDED_
#define _OD_MUTEXPOOL_INCLUDED_ /** {Secret} */

#include "ThreadsCounter.h"

#include "RootExport.h"
#include "TD_PackPush.h"

#if 0
// Old mutex pool version

#define STL_USING_ALGORITHM
#define STL_USING_VECTOR
#include "OdaSTL.h"

#ifdef OD_HAVE_FUNCTIONAL_FILE
#include <functional>
#endif

class FIRSTDLL_EXPORT OdMutexPool
{
public:
  typedef void* IdType;
  OdMutexPool(){}
  ~OdMutexPool(){ clear(); }
  void initialize(unsigned count)
  {
    m_array.reserve(count);
  }
  OdMutex* get(const IdType id)
  {
    if(odThreadsCounter())
    {
      if(!id)
        return NULL;
      TD_AUTOLOCK(m_mt);
      _mpair key(id, 0, 1);
      _mmap::iterator it = std::lower_bound(m_map.begin(), m_map.end(), key, std::less<_mpair>());
      if((it != m_map.end()) && (it->m_key == key.m_key))
      {
        ODA_ASSERT(it->m_val);
        it->m_count++;
        return it->m_val;
      }
      key.m_val = createMutex();
      m_map.insert(it, key);
      return key.m_val;
    }
    clear();
    return NULL;
  }

  void release(const IdType id)
  {
    TD_AUTOLOCK(m_mt);
    _mpair key(id);
    _mmap::iterator it = std::lower_bound(m_map.begin(), m_map.end(), key, std::less<_mpair>());
    ODA_ASSERT(it != m_map.end());
    if((it != m_map.end()) && (it->m_key == key.m_key))
    {
      ODA_ASSERT(it->m_count > 0);
      it->m_count--;
      if(!it->m_count)
      {
        m_array.push_back(it->m_val);
        m_map.erase(it);
      }
    }
  }
  void clear()
  {
    for(_mmap::iterator it = m_map.begin(); it!= m_map.end(); ++it)
      delete it->m_val;
    m_map.clear();
    for(unsigned i = 0; i < m_array.size(); ++i)
      delete m_array[i];
    m_array.clear();
  }
protected:
  OdMutex* createMutex()
  {
    if(m_array.size())
    {
      //reuse existing mutex
      OdMutex* ptr = m_array.back();
      m_array.pop_back();
      return ptr;
    }
    return new OdMutex;
  }

protected:
  struct _mpair
  {
    IdType m_key;
    OdMutex* m_val;
    int m_count;

    _mpair(IdType key, OdMutex* val = 0, int count = 0): m_key(key), m_val(val), m_count(count){}
    _mpair(): m_key(0), m_val(0), m_count(0){}
    _mpair(const _mpair& c): m_key(c.m_key), m_val(c.m_val), m_count(c.m_count){}

    bool operator < (const _mpair& c) const { return m_key < c.m_key; }
  };

  typedef std::vector<_mpair> _mmap;
  typedef std::vector<OdMutex*> _marray;

  _mmap m_map;
  _marray m_array;
  OdMutex m_mt;
};

#else
// Optimized mutex pool

#include "OdMutexHash.h"

class FIRSTDLL_EXPORT OdMutexPool
{
  static const int cHashTableSize = 97;

  struct SData
  {
    SData(OdMutex* pMutex = NULL, int count = 0)
    : m_pMutex(pMutex), m_count(count)
    {
    }

    ~SData()
    {
      delete m_pMutex;
    }

  public:
    OdMutex* m_pMutex;
    int m_count;
  };

  class IncCount
  {
  public:
    void operator()(SData& data)
    {
      if(data.m_pMutex == NULL)
        data.m_pMutex = new OdMutex();
      ++data.m_count;
    }
  };

  class IsEmpty
  {
  public:
    bool operator()(SData& data)
    {
      ODA_ASSERT(data.m_count > 0 && data.m_pMutex != NULL);
      return (--data.m_count == 0);
    }
  };

public:
  typedef void* IdType;

public:
  OdMutexPool(){}

  void initialize() { m_hash.initialize(cHashTableSize); }

  OdMutex* get(const IdType id)
  {
    if(!id)
      return NULL;
    return m_hash.getAt(id, IncCount()).m_pMutex;
  }

  void release(const IdType id)
  {
    m_hash.removeIf(id, IsEmpty());
  }

  void clear()
  {
    m_hash.clear();
  }

protected:
  typedef OdMutexHash<IdType, SData> Hash;
  Hash m_hash;
};

#endif

class FIRSTDLL_EXPORT OdMutexInPoolAutoLock: protected OdMutexPtrAutoLock
{
public:
  OdMutexInPoolAutoLock(OdMutexPool* pool, const OdMutexPool::IdType id) 
    : OdMutexPtrAutoLock(), m_pool(pool), m_id(0)
  {
    if(odThreadsCounter() && id)
    {
    ODA_ASSERT(m_pool);
    m_id = id;
    m_mutex = m_pool->get(m_id);
    ODA_ASSERT(m_mutex);
    lock();
    }
  }
  ~OdMutexInPoolAutoLock()
  {
    release();
  }

  void release()
  {
    if(m_id)
    {
      unlock();
      m_pool->release(m_id);
      m_id = NULL;
    }
  }
protected:
  OdMutexPool::IdType m_id;
  OdMutexPool* m_pool;
};

#include "TD_PackPop.h"
#endif // _OD_MUTEXPOOL_INCLUDED_

// ODA_MT_DB_1_END
// ODA_MT_DB_END
