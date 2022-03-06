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

#ifndef LRUCACHE_INCLUDED
#define LRUCACHE_INCLUDED

#include "OdHashMap.h"
#include "ThreadsCounter.h"

#ifdef HASHMAP_SUPPORTED

/**
 * Least-recently-used cache.
 * Cache items are stored in a hashmap. The items are ordered (with the help of
 * a linked list). When the cache is full, the last item is discarded.
 * When an item is accessed, it is moved at the front of the linked list.
 *
 * More info about template parameter <Hash>: http://msdn.microsoft.com/en-us/library/1s1byw77(VS.71).aspx
 */
template<typename Key, typename Value, typename Hash>
class LRUCache
{
    struct Item
    {
        Item()
            : m_prev(NULL)
            , m_next(NULL)
        {

        }
        Item(const Key& key, const Value& value)
            : m_key(key)
            , m_value(value)
            , m_prev(NULL)
            , m_next(NULL)
        {

        }

        Item* m_prev;
        Item* m_next;
        Value m_value;
        Key m_key;
    };
    typedef typename LRUCache<Key, Value, Hash>::Item ItemType;
    typedef OdHashMap<Key, ItemType*, Hash> LRUHashMap;

    LRUHashMap m_map;
    Item *m_first, *m_last;
    size_t m_maxSize;

public:
    LRUCache(size_t maxSize = 1000)
        : m_first(NULL)
        , m_last(NULL)
        , m_maxSize(maxSize)
    {
        if (m_maxSize < 1)
            m_maxSize = 1;
    }
    ~LRUCache()
    {
        while(m_first)
        {
            Item* item = m_first;
            m_first = m_first->m_next;
            delete item;
        }
    }

    bool set(const Key& key, const Value& value);
    bool get(const Key& key, Value& value);

    bool getUpdateKey(Key& key, Value& value);

    size_t capacity() const { return m_maxSize; }
    void setCapacity(size_t size);

    // call this if you are sure that getItem(key) returns NULL
    void add(const Key& key, const Value& value);

protected:
    bool contains(const Key& key) const;

private:
    inline Item* getItem(const Key& key);
    inline void removeItem(Item* item);
    inline void addItemToFront(Item* item);
    inline void moveItemToFront(Item* item);
};


template<typename Key, typename Value, typename Hash>
bool LRUCache<Key, Value, Hash>::set(const Key& key, const Value& value)
{
    ItemType* item = getItem(key);

    bool existsAlready = false;
    if (item)
    {
        item->m_value = value;
        moveItemToFront(item);
        existsAlready = true;
    }
    else
    {
        item = new ItemType(key, value);
        m_map[key] = item;
        addItemToFront(item);
        while (m_map.size() > m_maxSize)
        {
            ItemType* last = m_last;
            removeItem(last);
            m_map.erase(last->m_key);
            ODA_ASSERT(m_map.size() == m_maxSize);
            delete last;
        }
    }
    return existsAlready;
}

template<typename Key, typename Value, typename Hash>
void LRUCache<Key, Value, Hash>::add(const Key& key, const Value& value)
{
    ODA_ASSERT(!contains(key));

    ItemType* item = new ItemType(key, value);
    m_map[key] = item;
    addItemToFront(item);
    while (m_map.size() > m_maxSize)
    {
        ItemType* last = m_last;
        removeItem(last);
        m_map.erase(last->m_key);
        delete last;
    }
}

template<typename Key, typename Value, typename Hash>
bool LRUCache<Key, Value, Hash>::get(const Key& key, Value& value)
{
    ItemType* item = getItem(key);
    if (! item)
        return false;

    moveItemToFront(item);
    value = item->m_value;
    return true;
}

template<typename Key, typename Value, typename Hash>
bool LRUCache<Key, Value, Hash>::getUpdateKey(Key& key, Value& value)
{
  typename LRUHashMap::iterator it = m_map.find(key);
  if(it == m_map.end())
    return false;
  key.update(it->first);
  value = it->second->m_value;
  moveItemToFront(it->second);
  return true;
}

template<typename Key, typename Value, typename Hash>
inline bool LRUCache<Key, Value, Hash>::contains(const Key& key) const
{
    return m_map.find(key) != m_map.end();
}

template<typename Key, typename Value, typename Hash>
inline typename LRUCache<Key, Value, Hash>::Item* LRUCache<Key, Value, Hash>::getItem(const Key& key)
{
    typename LRUHashMap::iterator it = m_map.find(key);
    if (it == m_map.end())
        return NULL;
    else
        return (*it).second;
}

template<typename Key, typename Value, typename Hash>
inline void LRUCache<Key, Value, Hash>::removeItem(typename LRUCache<Key, Value, Hash>::Item* item)
{
    if (item == m_first)
        m_first = m_first->m_next;
    if (item == m_last)
        m_last = m_last->m_prev;

    if (item->m_prev)
        item->m_prev->m_next = item->m_next;
    if (item->m_next)
        item->m_next->m_prev = item->m_prev;
    //item->m_next = item->m_prev = NULL;
}

template<typename Key, typename Value, typename Hash>
inline void LRUCache<Key, Value, Hash>::addItemToFront(typename LRUCache<Key, Value, Hash>::Item* item)
{
    item->m_prev = NULL;
    if (m_first)
    {
        item->m_next = m_first;
        m_first->m_prev = item;
        m_first = item;
    }
    else // empty linkedlist
    {
        item->m_next = NULL;
        m_first = m_last = item;
    }
}

template<typename Key, typename Value, typename Hash>
inline void LRUCache<Key, Value, Hash>::moveItemToFront(typename LRUCache<Key, Value, Hash>::Item* item)
{
    if (item != m_first)
    {
        removeItem(item);
        addItemToFront(item);
    }
}

template<typename Key, typename Value, typename Hash>
void LRUCache<Key, Value, Hash>::setCapacity(size_t size)
{
  m_maxSize = size;
  while (m_map.size() > m_maxSize)
  {
    ItemType* last = m_last;
    removeItem(last);
    m_map.erase(last->m_key);
    delete last;
  }
}

template<typename Key, typename Value, typename Hash>
class LRUCacheTs: protected LRUCache<Key, Value, Hash>
{
public:
    LRUCacheTs(size_t maxSize = 1000): LRUCache<Key, Value, Hash>(maxSize){}
    bool set(const Key& key, const Value& value)
    {
      TD_AUTOLOCK(m_mt);
      return LRUCache<Key, Value, Hash>::set(key, value);
    }

    bool get(const Key& key, Value& value)
    {
      TD_AUTOLOCK(m_mt);
      return LRUCache<Key, Value, Hash>::get(key, value);
    }

    bool getUpdateKey(Key& key, Value& value)
    {
      TD_AUTOLOCK(m_mt);
      return LRUCache<Key, Value, Hash>::getUpdateKey(key, value);
    }

    // call this if you are sure that getItem(key) returns NULL
    void add(const Key& key, const Value& value)
    {
      TD_AUTOLOCK(m_mt);
      if(LRUCache<Key, Value, Hash>::contains(key))
          return;
      LRUCache<Key, Value, Hash>::add(key, value);
    }

    size_t capacity()
    {
      TD_AUTOLOCK(m_mt);
      return LRUCache<Key, Value, Hash>::capacity();
    }

    void setCapacity(size_t size)
    {
      TD_AUTOLOCK(m_mt);
      return LRUCache<Key, Value, Hash>::setCapacity(size);
    }

protected:
  OdMutex m_mt;
};

#endif

#endif // LRUCACHE_INCLUDED
