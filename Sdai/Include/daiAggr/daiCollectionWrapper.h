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

#ifndef _DAI_COLLECTION_WRAPPER_H
#define _DAI_COLLECTION_WRAPPER_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"
#include "OdArray.h"

#include "daiUtils/daiUnset.h"

#define STL_USING_ALGORITHM
#include "OdaSTL.h"

namespace OdDAI
{
  class Aggr;

  template<class TItem>
  inline void itemCleaner(TItem& itemToClean)
  {}

  template<class TItem>
  class CollectionWrapper
  {
  public:
    typedef typename OdArray<TItem>::size_type size_type;

  public:
    ~CollectionWrapper();

    void clear();
  
    size_type size() const;
    void resize(const size_type& newSize, const TItem& itemToFill = OdDAI::Utils::getUnset<TItem>());

    bool removeByValue(const TItem& erasedValue);
    void removeAllByValue(const TItem& erasedValue);
    void removeByIndex(const size_type& indexToRemove);

    void setValue(const size_type& index, const TItem& newValue);
    void assignRange(const size_type& indexFrom, const OdArray<TItem>& range);
    void pushBackValue(const TItem& newValue);
    void insertAfterValue(const size_type& index, const TItem& newValue);
    void insertBeforeValue(const size_type& index, const TItem& newValue);

    bool isContains(const TItem& itemToCheck) const;

    const TItem& operator[](const size_type& index) const;

    const OdArray<TItem>& getCollection() const;
    void setCollection(const OdArray<TItem>& newArray);

    void sortAndRemoveDuplicates()
    {
      std::sort(m_collection.begin(), m_collection.end());
      typename OdArray<TItem>::iterator newEnd = std::unique(m_collection.begin(), m_collection.end());

      if (newEnd != m_collection.end())
      {
        m_collection.erase(newEnd, m_collection.end());
      }
    }

  private:
    OdArray<TItem>  m_collection;
  };
}


namespace OdDAI
{
  template<class TItem>
  inline CollectionWrapper<TItem>::~CollectionWrapper()
  {
    clear();
  }
  template<class TItem>
  inline void CollectionWrapper<TItem>::clear()
  {
    typename OdArray<TItem>::iterator  iteratorDelete = m_collection.begin();
    for (; iteratorDelete != m_collection.end(); ++iteratorDelete)
    {
      itemCleaner(*iteratorDelete);
    }

    m_collection.clear();
  }

  template<class TItem>
  inline typename CollectionWrapper<TItem>::size_type CollectionWrapper<TItem>::size() const
  {
    return m_collection.size();
  }

  template<class TItem>
  inline void CollectionWrapper<TItem>::resize(const typename CollectionWrapper<TItem>::size_type& newSize, const TItem& itemToFill)
  {
    if (m_collection.size() > newSize)
    {
      typename OdArray<TItem>::iterator  iteratorDelete = m_collection.begin() + newSize;
      for (; iteratorDelete != m_collection.end(); ++iteratorDelete)
      {
        itemCleaner(*iteratorDelete);
      }
    }

    m_collection.resize(newSize, itemToFill);
  }

  template<class TItem>
  inline bool CollectionWrapper<TItem>::removeByValue(const TItem& erasedValue)
  {
    typename OdArray<TItem>::iterator iteratorToDelete = std::find(m_collection.begin(),
                                                          m_collection.end(),
                                                          erasedValue);

    if (iteratorToDelete == m_collection.end())
    {
      return false;
    }

    itemCleaner(*iteratorToDelete);
    m_collection.erase(iteratorToDelete);
    return true;
  }


  template<class TItem>
  inline void CollectionWrapper<TItem>::removeAllByValue(const TItem& erasedValue)
  {
    typename OdArray<TItem>::iterator newEnd = std::remove(m_collection.begin(),
                                                  m_collection.end(),
                                                  erasedValue);

    typename OdArray<TItem>::iterator  deleteIterator = newEnd;
    while (deleteIterator != m_collection.end())
    {
      itemCleaner(*deleteIterator);
      ++deleteIterator;
    }

    m_collection.erase(newEnd, m_collection.end());
  }

  template<class TItem>
  inline void CollectionWrapper<TItem>::removeByIndex(const size_type& indexToRemove)
  {
    itemCleaner(m_collection[indexToRemove]);
    m_collection.erase(m_collection.begin() + indexToRemove);
  }

  template<class TItem>
  inline void CollectionWrapper<TItem>::setValue(const typename CollectionWrapper<TItem>::size_type& index, const TItem& newValue)
  {
    itemCleaner(m_collection[index]);
    m_collection[index] = newValue;
  }

  template<class TItem>
  inline void CollectionWrapper<TItem>::assignRange(const typename CollectionWrapper<TItem>::size_type& indexFrom, const OdArray<TItem>& range)
  {    
    Od_memcpy_s(&m_collection[indexFrom], m_collection.size(), &range[0], range.size() * sizeof(TItem));
  }

  template<class TItem>
  inline void CollectionWrapper<TItem>::pushBackValue(const TItem& newValue)
  {
    m_collection.push_back(newValue);
  }

  template<class TItem>
  inline void CollectionWrapper<TItem>::insertAfterValue(const typename CollectionWrapper<TItem>::size_type& index, const TItem& newValue)
  {
    typename OdArray<TItem>::iterator insertionPlace = m_collection.begin() + index + 1;
    m_collection.insert(insertionPlace, newValue);
  }

  template<class TItem>
  inline void CollectionWrapper<TItem>::insertBeforeValue(const size_type& index, const TItem& newValue)
  {
    typename OdArray<TItem>::iterator insertionPlace = m_collection.begin() + index;
    m_collection.insert(insertionPlace, newValue);

  }

  template<class TItem>
  inline bool CollectionWrapper<TItem>::isContains(const TItem& itemToCheck) const
  {
    return std::find(m_collection.begin(), m_collection.end(), itemToCheck) != m_collection.end();
  }

  template<class TItem>
  inline const TItem& CollectionWrapper<TItem>::operator[](const typename CollectionWrapper<TItem>::size_type& index) const
  {
    return m_collection[index];
  }

  template<class TItem>
  inline const OdArray<TItem>& CollectionWrapper<TItem>::getCollection() const
  {
    return m_collection;
  }

  template<class TItem>
  inline void CollectionWrapper<TItem>::setCollection(const OdArray<TItem>& newArray)
  {
    typename OdArray<TItem>::iterator  cleanNext = m_collection.begin();
    for (; cleanNext != m_collection.end(); ++cleanNext)
    {
      itemCleaner(*cleanNext);
    }
    m_collection = newArray;
  }


  template <>
  inline void itemCleaner<Aggr*>(Aggr*& itemToClean)
  {
    if (itemToClean == NULL)
    {
      return;
    }
    delete itemToClean;
    itemToClean = NULL;
  }

}


#endif // _DAI_ITERATOR_H
