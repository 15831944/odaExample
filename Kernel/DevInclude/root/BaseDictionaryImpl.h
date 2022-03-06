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

#ifndef _BASEDICTIONARYIMPL_INC_
#define _BASEDICTIONARYIMPL_INC_

#define STL_USING_ALGORITHM
#define STL_USING_FUNCTIONAL
#include "OdaSTL.h"

#include "OdArray.h"
#include "OdString.h"
#include "RxSystemServices.h"

namespace OdRx
{
  static const OdUInt32 kNullDictId = OdUInt32(-1);
}

template <class Key, class Value>
class OdBaseDictItem
{
  Key m_key;
  Value m_val;
  bool m_erased;
public:
  OdBaseDictItem() : m_erased(false) {}
  OdBaseDictItem(const Key& key, const Value& val) : m_erased(false), m_key(key), m_val(val) {}
  const Key& getKey() const { return m_key; }
  void setKey(const Key& key) { m_key = key; }
  const Value& getVal() const { return m_val; }
  void setVal(const Value& val) { m_val = val; }
  bool isErased() const { return m_erased; }
  void erase() { m_erased = false; }
};

template <class ArrayType, class Key, class Value>
class OdBaseIteratorImpl
{
protected:
  ArrayType*  m_pItems;
  OdUInt32    m_nIndex;
  int         m_nInc;
  bool        m_bSkipDeleted;
public:
  OdBaseIteratorImpl()
    : m_pItems(NULL)
    , m_nIndex(0)
    , m_nInc(1)
    , m_bSkipDeleted(true)
  {
  }

  bool isForward() const
  {
    return m_nInc > 0;
  }

  bool isReverse() const
  {
    return m_nInc < 0;
  }

  void skipDeleted(int nInc)
  {
    if (m_bSkipDeleted)
    {
      while (!isDone() && m_pItems->__getItemAt__(m_nIndex)->isErased())
      {
        m_nIndex += nInc;
      }
    }
  }

  void init(ArrayType& items, bool bAtBeginning = true, bool bSkipDeleted = true)
  {
    m_pItems = &items;
    start(bAtBeginning, bSkipDeleted);
  }

  void start(bool bAtBeginning = true, bool bSkipDeleted = true)
  {
    if (bAtBeginning)
    {
      m_nInc = 1;
      m_nIndex = 0;
    }
    else
    {
      m_nInc = -1;
      m_nIndex = m_pItems->size() - 1;
    }
    m_bSkipDeleted = bSkipDeleted;
    skipDeleted(m_nInc);
  }

  bool isDone() const
  {
    return (m_nIndex >= m_pItems->size());  // kNullDictId > any size
  }

  bool next()
  {
    // AMark : 17.10.2008 : #5326
    if (isForward() && m_nIndex > m_pItems->size() && m_pItems->size() > 0)
    {
      m_nIndex = 0;
      skipDeleted(m_nInc);
    }
    else if (isReverse() && m_nIndex == m_pItems->size() && m_pItems->size() > 0)
    {
      --m_nIndex;
      skipDeleted(m_nInc);
    }
    //
    if(isDone())
      return false;
    m_nIndex += m_nInc;
    skipDeleted(m_nInc);
    return !isDone();
  }

  bool prev()
  {
    // AMark : 17.10.2008 : #5326
    if (isReverse() && m_nIndex > m_pItems->size() && m_pItems->size() > 0)
    {
      m_nIndex = 0;
      skipDeleted(-m_nInc);
    }
    else if (isForward() && m_nIndex == m_pItems->size() && m_pItems->size() > 0)
    {
      --m_nIndex;
      skipDeleted(-m_nInc);
    }
    //
    if(isDone())
      return false;
    m_nIndex -= m_nInc;
    skipDeleted(-m_nInc);
    return !isDone();
  }

  const Key& getKey() const
  {
    return m_pItems->__getItemAt__(m_nIndex)->getKey();
  }

  const Value& getItem() const
  {
    return m_pItems->__getItemAt__(m_nIndex)->getVal();
  }

  OdUInt32 id() const
  {
    return m_pItems->__getItemIdAt__(m_nIndex);
  }

  bool seek(const Value& Val)
  {
    for(OdUInt32 i = 0; i < m_pItems->size(); i ++)
    {
      if(m_pItems->__getItemAt__(i)->getVal() == Val)
      {
        m_nIndex = i;
        return true;
      }
    }
    return false;
  }
};

template <class Key, class Value, class Pr, class Itm>
class OdBaseDictionaryImpl
{
public:
  typedef ::OdArray<OdUInt32, ::OdMemoryAllocator<OdUInt32> > SortedItemArray;
	typedef Itm Item;

  class ItemArray : public OdArray<Item>
  {
    //ItemArray& operator = (const ItemArray&);
  public:
    typedef typename OdArray<Item>::size_type  size_type;
    typedef typename OdArray<Item>::iterator iterator;
    typedef typename OdArray<Item>::const_iterator const_iterator;
    Item* __getItemAt__(size_type index) const
    {
      // interval check already is in OdArray
      return const_cast<Item*>(&OdArray<Item>::at(index));
    }
    OdUInt32 __getItemIdAt__(size_type index)const
    {
      return index;
    }
  };
  typedef typename OdArray<Item>::size_type  size_type;
  typedef typename ItemArray::iterator iterator;
  typedef typename ItemArray::const_iterator const_iterator;

protected:
  volatile mutable bool            m_sorted;

  class DictPr
  {
    const ItemArray* m_pItems;
  public:
    DictPr(const ItemArray& items) : m_pItems(&items) {}
    static const Pr& getCmpPr()
    {
      static Pr pr;
      return pr;
    }

    bool operator ()(OdUInt32 id, const Key& key) const
    {
      return getCmpPr()(m_pItems->at(id).getKey(), key);
    }

    bool operator ()(const Key& key, OdUInt32 id) const
    {
      return getCmpPr()(key, m_pItems->at(id).getKey());
    }

    bool operator () (OdUInt32 id1, OdUInt32 id2) const
    {
      return getCmpPr()(m_pItems->at(id1).getKey(), m_pItems->at(id2).getKey());
    }
  };

  class CheckVal
  {
    ItemArray* m_pItems;
    const Value* m_pKey;
  public:
    CheckVal(const ItemArray& items, const Value& key)
      : m_pItems((ItemArray*)&items)
      , m_pKey(&key) {}

    bool operator ()(OdUInt32 id) const
    {
      return (m_pItems->at(id).getVal() == *m_pKey);
    }
  };

public:
  ItemArray               m_items;
  mutable SortedItemArray m_sortedItems;

  typedef typename SortedItemArray::iterator sorted_iterator;
  typedef typename SortedItemArray::const_iterator const_sorted_iterator;
  virtual void sort() const
  {
    if(!m_sorted)
    {
      std::sort(m_sortedItems.begin(), m_sortedItems.end(), DictPr(m_items));
      m_sorted = true;
    }
  }

  bool find(const Key& key, sorted_iterator& p) const
  {
    DictPr less(m_items);
    sort();
    p = (sorted_iterator)std::lower_bound(m_sortedItems.begin(), m_sortedItems.end(), key, less);
    return (p != m_sortedItems.end() && !less(key, *p));
  }

  bool find(const Value& key, sorted_iterator& p) const
  {
    p = std::find_if(m_sortedItems.begin(), m_sortedItems.end(), CheckVal(m_items, key));
    return (p != m_sortedItems.end());
  }

  const Item* __getItemAt__(size_type index) const 
  {
    if (index < m_sortedItems.size())
    {
      return &(m_items[m_sortedItems[index]]);
    }
    ODA_FAIL();
    throw OdError_InvalidIndex();
  }

  Item* __getItemAt__(size_type index)
  {
    if (index < m_sortedItems.size())
    {
      return &(m_items[m_sortedItems[index]]);
    }
    ODA_FAIL();
    throw OdError_InvalidIndex();
  }

  OdUInt32 __getItemIdAt__(size_type index) const
  {
    if (index < m_sortedItems.size())
    {
      return m_sortedItems[index];
    }
    ODA_FAIL();
    throw OdError_InvalidIndex();
  }

  // AlexR m_items->m_sortedItems : problem with remove elem of dictionary
  // Delete elem, save to dwg, load -> GRF (try to load dict with erazed elems)
  // size return 8 elem but 1 is erazed -> trying load 8 elem, but only 7 was saved
  size_type size() const { return m_sortedItems.size(); }

  OdBaseDictionaryImpl() : m_sorted(true)
  {
  }

  OdUInt32 insert(const Item& item, sorted_iterator before)
  {
    OdUInt32 resId = m_items.size();
    m_items.push_back(item);
    m_sortedItems.insert(before, resId);
//    m_sorted = false; 
    return resId;
  }

  bool getAt(const Key& key, Value& val) const
  {
    sorted_iterator iter;
    if(find(key, iter))
    {
      val = m_items[*iter].getVal();
      return true;
    }
    return false;
  }

  bool getAt(OdUInt32 id, Value& val) const
  {
    if(m_items.size()>id)
    {
      val = m_items[id].getVal();
      return true;
    }
    return false;
  }

  bool setAt(const Key& key, const Value& val)
  {
    sorted_iterator iter;
    if(find(key, iter))
    {
      m_items[*iter].setVal(val);
      return true;
    }
    insert(Itm(key, val), iter);
    return false;
  }

  bool has(const Key& key)
  {
    sorted_iterator iter;
    return find(key, iter);
  }

  bool has(const Value& key)
  {
    sorted_iterator iter;
    return find(key, iter);
  }

  void push_back(const Item& item)
  {
    m_sorted = (!insert(item, m_sortedItems.end())); // IF FIRST ID==0
  }

  void clear() { m_items.clear(); m_sortedItems.clear(); m_sorted = true; }

  void reserve(size_type n) { m_items.reserve(n); m_sortedItems.reserve(n);}

  iterator begin() { return m_items.begin(); }
  const_iterator begin() const { return m_items.begin(); }

  iterator end() { return m_items.end(); }
  const_iterator end() const { return m_items.end(); }

  bool resetKey(const Key& oldKey, const Key& newKey)
  {
    sorted_iterator iter;
    if (find(oldKey, iter))
    {
      OdUInt32 id = *iter;
      ODA_ASSERT(id < m_items.size());
      ODA_ASSERT(m_sorted);
      // Erase old item in sorted array
      iter = m_sortedItems.erase (iter);
      // Find place for new key
      sorted_iterator before;
      if (!find(newKey, before))
      {
        m_sortedItems.insert(before, id);
        m_items[id].setKey(newKey);
        return true;
      }
      // Un-erase old item in case of duplicate Key
      m_sortedItems.insert(iter, id);
    }
    return false;
  }

  bool resetKey(OdUInt32 id, const Key& newKey)
  {
    if(id < m_items.size())
    {
      m_items[id].setKey(newKey);
      m_sorted = false;
      return true;
    }
    return false;
  }

  void needSorting() { m_sorted = false; }
  bool isSorted() { return m_sorted; }
};

#endif // _BASEDICTIONARYIMPL_INC_
