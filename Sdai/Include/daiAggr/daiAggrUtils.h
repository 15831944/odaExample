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

#ifndef _DAI_AGGR_UTILS_H
#define _DAI_AGGR_UTILS_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"

#include "daiBuildOptions.h"
#include "daiUtils/daiUnset.h"

#include "daiArray.h"
#include "daiList.h"
#include "daiSet.h"
#include "daiBag.h"

#include "daiPrepareAggregateItem.h"

namespace OdDAI
{

  template <typename TAggr, bool>
  class AggrPushCommonInterface
  {
  };

  template <class TAggrOrdered>
  class AggrPushCommonInterface<TAggrOrdered, true>
  {
  public:

    AggrPushCommonInterface(TAggrOrdered& internalAggr)
      : m_internalAggr(internalAggr)
      , m_nextIndex(0)
    {
    }

    void prepare()
    {
      m_internalAggr.createEmpty();
      if (m_internalAggr.aggrType() == aggrTypeArray)
        m_nextIndex = m_internalAggr.getLowerBound();
      else
        m_nextIndex = 0;
    }

    void prepareItem(typename TAggrOrdered::value_type& valueToPush)
    {
      valueToPush = m_internalAggr.template generateAggrItem<TAggrOrdered::value_type>();
    }

    bool push(const typename TAggrOrdered::value_type& valueToPush)
    {
      m_internalAggr.putByIndex(m_nextIndex, valueToPush);
      ++m_nextIndex;
      
      return true;
    }

  private:
    TAggrOrdered&  m_internalAggr;
    unsigned int   m_nextIndex;
  };


  template<class TAggrUnordered>
  class AggrPushCommonInterface<TAggrUnordered, false>
  {
  public:
    AggrPushCommonInterface(TAggrUnordered& internalAggr)
      : m_internalAggr(internalAggr)
    {
    }

    void prepare()
    {
      m_internalAggr.createEmpty();
    }

    void prepareItem(typename TAggrUnordered::value_type& valueToPush)
    {
      valueToPush = m_internalAggr.template generateAggrItem<TAggrUnordered::value_type>();
    }

    bool push(const typename TAggrUnordered::value_type& valueToPush)
    {
      return m_internalAggr.Add(valueToPush);
    }

  private:
    TAggrUnordered&  m_internalAggr;
  };


  template <typename TItem>
  class ArrayPushCommonInterface
  {
  public:
    ArrayPushCommonInterface(OdArray<TItem>& internalArray)
      : m_internalArray(internalArray)
    {
    }

    void prepare()
    {
      m_internalArray.clear();
    }

    bool push(const TItem& valueToPush)
    {
      m_internalArray.push_back(valueToPush);
      return true;
    }

  private:
    OdArray<TItem>&  m_internalArray;
  };


  template <typename TItem>
  class RawPointerPushCommonInterface
  {
  public:
    RawPointerPushCommonInterface(TItem* begin, TItem* end)
      : m_begin(begin)
      , m_end(end)
      , m_current(NULL) 
    {
      ODA_ASSERT(m_begin <= m_end);
    }

    void prepare()
    {
      m_current = m_begin;
    }

    bool push(const TItem& valueToPush)
    {
      if (!m_current)
      {
        return false;
      }

      bool arrayIsFinished = (m_current == m_end);
      *m_current = valueToPush;

      if (arrayIsFinished)
      {
        m_current = NULL;

      }
      else
      {
        ++m_current;
      }

      return true;
    }

  private:
    TItem*  m_begin;
    TItem*  m_current;
    TItem*  m_end;
  };

}

namespace OdDAI
{

  template <typename TItem>
  int extractLower(const Array<TItem>& array)
  {
    return (!array.isNil() && array.getMemberCount() > 0) ? array.getLowerIndex() : 0;
  }

  template <typename TItem>
  int extractUpper(const Array<TItem>& array)
  {
    return (!array.isNil() && array.getMemberCount() > 0) ? array.getUpperIndex() + 1 : 0;
  }

  template <typename TItem>
  int extractLower(const List<TItem>& list)
  {
    return !list.isNil() ? list.getLowerBound() : 0;
  }

  template <typename TItem>
  int extractUpper(const List<TItem>& list)
  {
    return !list.isNil() ? list.getUpperBound() : 0;
  }


  template <class TAggr, bool>
  class AggrReadCommonInterface
  {};


  namespace
  {
    template <class TAggr, class TType>
    bool unsetReadFilter(const TType&, TAggr* aggr = nullptr) { return true; }
    bool unsetReadFilter(const OdDAIObjectId& value,  OdDAI::Set<OdDAIObjectId>* aggr = nullptr) { return !OdDAI::Utils::isUnset(value); }
    bool unsetReadFilter(const OdDAIObjectId& value,  OdDAI::List<OdDAIObjectId>* aggr = nullptr) { return !OdDAI::Utils::isUnset(value); }
    bool unsetReadFilter(const OdDAIObjectId& value,  OdDAI::Bag<OdDAIObjectId>* aggr = nullptr) { return !OdDAI::Utils::isUnset(value); }
  }

  template <class TAggrOrdered>
  class AggrReadCommonInterface <TAggrOrdered, true>
  {
    // Skips erased instances. At this moment is using at file writing functionality only.
  public:
    //typedef typename std::enable_if<std::is_base_of<AggrOrdered, TAggrOrdered<TItem> >::value>::type AggrOrderedType;

    AggrReadCommonInterface(TAggrOrdered& internalAggr)
      : m_internalAggr(internalAggr)
      , m_nextIndex(0)
      , m_lower(extractLower<typename TAggrOrdered::value_type>(internalAggr))
      , m_upper(extractUpper<typename TAggrOrdered::value_type>(internalAggr))
    {
    }


    bool isValid()
    {
      return !m_internalAggr.isNil();
    }

    void prepare()
    {
      if (!isValid())
      {
        return;
      }

      m_nextIndex = m_lower;
    }

    void prepareItem(typename TAggrOrdered::value_type& valueToPush)
    {
      valueToPush = m_internalAggr.template generateAggrItem<TAggrOrdered::value_type>();
    }

    bool getNext(typename TAggrOrdered::value_type& valueToGet)
    {
      if (!isValid())
      {
        return false;
      }

      bool succeeded = false;
      typename TAggrOrdered::value_type transitValue;
      prepareItem(transitValue);

      while (m_upper > m_nextIndex)
      {
        transitValue = m_internalAggr.template getByIndex<typename TAggrOrdered::value_type>(m_nextIndex);
        ++m_nextIndex;

        if (unsetReadFilter(transitValue, &m_internalAggr))
        {
          valueToGet = transitValue;
          succeeded = true;
          break;
        }
      }

      return succeeded;
    }

  protected:
    

  private:
    TAggrOrdered&         m_internalAggr;
    int                   m_nextIndex;
    const int             m_lower;
    const int             m_upper;
  };


  template <class TAggrUnordered>
  class AggrReadCommonInterface <TAggrUnordered, false>
  {
  public:
    AggrReadCommonInterface(TAggrUnordered& internalAggr)
      : m_internalAggr(internalAggr)
      , m_nextIterator(!internalAggr.isNil() ? internalAggr.createIterator() : NULL)
    {
    }

    bool isValid()
    {
      return !m_nextIterator.isNull();
    }

    void prepare()
    {
      if (!isValid())
      {
        return;
      }

      m_nextIterator->beginning();
    }
    
    void prepareItem(typename TAggrUnordered::value_type& valueToPush)
    {
      valueToPush = m_internalAggr.template generateAggrItem<TAggrUnordered::value_type>();
    }

    bool getNext(typename TAggrUnordered::value_type& valueToGet)
    {
      if (!isValid())
      {
        return false;
      }

      typename TAggrUnordered::value_type transitValue;
      prepareItem(transitValue);

      while (m_nextIterator->next())
      {
#ifdef _AGGR_RETURN_PTR
        if ((m_nextIterator->getCurrentMemberValue() >> transitValue) == false)
        {
          continue;
        }
#else
        if ((m_nextIterator->getCurrentMember() >> transitValue) == false)
        {
          continue;
        }
#endif
        TAggrUnordered* templateSpecHelper = nullptr;
        if (!unsetReadFilter(transitValue, templateSpecHelper))
        {
          continue;
        }

        valueToGet = transitValue;
        return true;
      }

      return false;
    }

  private:
    IteratorPtr m_nextIterator;
    TAggrUnordered& m_internalAggr;
  };


  template <typename TItem>
  class ArrayReadCommonInterface
  {
  public:
    ArrayReadCommonInterface(OdArray<TItem>& internalArray)
      : m_internalArray(internalArray)
      , m_nextIndex(0)
    {
    }

    bool isValid()
    {
      return !m_internalArray.isEmpty();
    }

    void prepare()
    {
      m_nextIndex = 0;
    }

    bool getNext(TItem& valueToGet)
    {
      if (m_internalArray.length() <= m_nextIndex)
      {
        return false;
      }

      valueToGet = m_internalArray[m_nextIndex];
      ++m_nextIndex;

      return true;
    }

  private:
    OdArray<TItem>&   m_internalArray;
    unsigned int      m_nextIndex;
  };


  template <typename TItem>
  class RawPointerReadCommonInterface
  {
  public:
    RawPointerReadCommonInterface(TItem* begin, TItem* end)
      : m_begin(begin)
      , m_end(end)
      , m_current(NULL)
    {
      ODA_ASSERT(m_begin <= m_end);
    }

    bool isValid()
    {
      return m_begin <= m_end;
    }

    void prepare()
    {
      m_current = m_begin;
    }

    bool getNext(TItem& valueToGet)
    {
      if (!m_current)
      {
        return false;
      }

      bool arrayIsFinished = m_current == m_end;
      valueToGet = *m_current;
      
      if (arrayIsFinished)
      {
        m_current = NULL;
      }
      else
      {
        ++m_current;
      }

      return true;
    }

  private:
    TItem*  m_begin;
    TItem*  m_current;
    TItem*  m_end;
  };

}

namespace OdDAI
{
  template<class AggrValueType>
  void copyFromAggrToRxValueArray(const AggrValueType& aggrFrom, OdArray<OdRxValue>& arrayTo)
  {
    if (!aggrFrom.isNil())
    {
      const OdArray<typename AggrValueType::value_type>*  internalArray = aggrFrom;
      if(!internalArray)
      {
        return;
      }

      unsigned int selectsCount = internalArray->size();

      if (selectsCount > 0)
      {
        arrayTo.reserve(selectsCount);

        for (unsigned int selectIndex = 0; selectIndex < selectsCount; ++selectIndex)
        {
          arrayTo.push_back((*internalArray)[selectIndex]);
        }
      }
    }
  }
}


#endif // _DAI_AGGR_H
