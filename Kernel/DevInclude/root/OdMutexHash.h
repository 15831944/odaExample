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

#ifndef _ODMUTEXHASH_H_
#define _ODMUTEXHASH_H_

#include "TD_PackPush.h"

#include "OdVector.h"

#ifdef _MSC_VER
#pragma warning (disable:4311)
#endif

template<class K, class T, class A = OdObjectsAllocator<T>, class Mm = OdrxMemoryManager> class OdMutexHash;

template<class K, class T, class A, class Mm>
class OdMutexHash
{
protected:
  class Bucket
  {
  protected:
    struct Entry
    {
      Entry(): m_next(NULL){}
      Entry(const K& key): m_next(NULL), m_key(key){}
      Entry(const K& key, const T& value): m_next(NULL), m_key(key), m_value(value){}

    public:
      K m_key;
      T m_value;
      Entry* m_next;
    };

    class EntryList
    {
      public:
        EntryList(): m_bBufferUsed(false), m_bBufferRecordValid(false), m_top(NULL) {}
        ~EntryList() { clear(); }

      public:
        T& getAt(const K& key)
        {
          for(Entry* ptr = m_top; ptr; ptr = ptr->m_next)
          {
            if(ptr->m_key == key)
              return ptr->m_value;
          }
          return add(key);
        }

        template<class P>
        void removeIf(const K& key, P pred)
        {
          Entry* prev = NULL;
          if(find(key, prev))
          {
            Entry* ptr = prev ? prev->m_next : m_top;
            if(pred(ptr->m_value))
            {
              if(prev)
                prev->m_next = ptr->m_next;
              else
              {
                m_top = ptr->m_next;
              }
              destroyEntry(ptr, true);
            }
          }
        }

        void clear()
        {
          for(Entry* ptr = m_top; ptr; )
          {
            Entry* next = ptr->m_next;
            destroyEntry(ptr, false);
            ptr = next;
          }
          m_top = NULL;
          if(m_bBufferRecordValid)
          {
            A::destroy(&reinterpret_cast<Entry*>(m_buf)->m_value);
            m_bBufferRecordValid = false;
          }
        }

      protected:
        void destroyEntry(Entry* ptr, bool bKeepBufferRecord)
        {
          if(ptr == reinterpret_cast<Entry*>(m_buf))
          {
            m_bBufferRecordValid = bKeepBufferRecord;
            if(!bKeepBufferRecord)
              A::destroy(&ptr->m_value);
            ODA_ASSERT(m_bBufferUsed);
            m_bBufferUsed = false;
          }
          else
          {
            A::destroy(&ptr->m_value);
            Mm::Free(ptr);
          }
        }

        bool find(const K& key, Entry*& prev)
        {
          prev = NULL;
          for(Entry* ptr = m_top; ptr; prev = ptr, ptr = ptr->m_next)
          {
            if(ptr->m_key == key)
              return true;
          }
          return false;
        }
        T& add(const K& key)
        {
          Entry* ptr;
          if(m_bBufferUsed)
          {
            ptr = reinterpret_cast<Entry*>(Mm::Alloc(sizeof(Entry)));
            A::construct(&ptr->m_value);
          }
          else
          {
            ptr = reinterpret_cast<Entry*>(m_buf);
            m_bBufferUsed = true;
            if(!m_bBufferRecordValid)
              A::construct(&ptr->m_value);
          }
          ptr->m_key = key;
          ptr->m_next = m_top;
          m_top = ptr;
          return ptr->m_value;
        }
      protected:
        Entry* m_top;
        char m_buf[sizeof(Entry)];
        bool m_bBufferUsed;
        bool m_bBufferRecordValid;
    };

  public:
    Bucket(){}

    OdMutex& mutex() { return m_mutex; }

    T& getAt(const K& key)
    {
      return m_entries.getAt(key);
    }

    template<class P>
    void removeIf(const K& key, P pred)
    {
      m_entries.removeIf(key, pred);
    }

    void clear()
    {
      m_entries.clear();
    }

  protected:
    EntryList m_entries;
    OdMutex m_mutex;
  };

  typedef OdVector<Bucket*> Vector;

public:
  OdMutexHash(){}

  ~OdMutexHash(){
    initialize(0);
  }

  void initialize(const int hashTableSize) {
    // NB!: for a test purposes we suggest, that workflow of this object is always
    // between
    //      initialize & clear functions.

    int iOldHashTableSize = m_hashTable.size();
    if (hashTableSize < iOldHashTableSize) {
      for (int i = hashTableSize; i < iOldHashTableSize; ++i) {
        delete m_hashTable[i];
        m_hashTable[i] = NULL;
      }
      m_hashTable.setLogicalLength(hashTableSize);
    } else if (hashTableSize > iOldHashTableSize) {
      m_hashTable.setLogicalLength(hashTableSize);
      for (; iOldHashTableSize < hashTableSize; ++iOldHashTableSize) {
        m_hashTable[iOldHashTableSize] = new Bucket;
      }
    }
  }

  template<class C>
  T& getAt(const K& key, C callback)
  {
    const unsigned int bucketIndex = hashFunction(key);

    ODA_ASSERT(bucketIndex < m_hashTable.length());

    Bucket& bucket = *(m_hashTable[bucketIndex]);

    TD_AUTOLOCK(bucket.mutex());

    T& value = bucket.getAt(key);

    callback(value);

    return value;
  }

  template<class P>
  void removeIf(const K& key, P pred)
  {
    const unsigned int bucketIndex = hashFunction(key);

    ODA_ASSERT(bucketIndex < m_hashTable.length());

    Bucket& bucket = *(m_hashTable[bucketIndex]);

    TD_AUTOLOCK(bucket.mutex());

    bucket.removeIf(key, pred);
  }

  void clear() {
    for(int i = 0, n = m_hashTable.length(); i < n; ++i) {
      m_hashTable[i]->clear();
    }
  }

protected:
  unsigned int hashFunction(const void* key) const
  {
    ODA_ASSERT(m_hashTable.length());
    return ((((unsigned int)((OdIntPtr)key))>>4)%m_hashTable.length());
  }

private:

  Vector m_hashTable;
};

#include "TD_PackPop.h"

#endif // _ODMUTEXHASH_H_
