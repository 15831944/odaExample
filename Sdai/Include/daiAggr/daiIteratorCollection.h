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

#ifndef _DAI_ITERATOR_COLLECTION_H
#define _DAI_ITERATOR_COLLECTION_H

#include "daiIterator.h"
#include "daiAggrMemberAccess.h"

#define STL_USING_ALGORITHM
#include "OdaSTL.h"
#include "daiPrepareAggregateItem.h"

namespace OdDAI
{
  /** \details
  Class that represents type-specified iterator.
  */
  template <class TContainer, class TType>
  class DAI_EXPORT IteratorCollection
    : public Iterator
  {
  public:
    IteratorCollection(Aggr& collection);

    virtual void beginning() ODRX_OVERRIDE;

    virtual bool next() ODRX_OVERRIDE;
    virtual bool previous() ODRX_OVERRIDE;

    virtual void end()  ODRX_OVERRIDE;

    virtual Aggr* createAggrInstanceAsCurrentMember() ODRX_OVERRIDE;
    virtual Aggr* createAggrInstanceBeforeCurrentMember() ODRX_OVERRIDE;
    virtual Aggr* createAggrInstanceAfterCurrentMember() ODRX_OVERRIDE;

    virtual OdRxValue getCurrentMember() const ODRX_OVERRIDE;
    virtual OdRxValue getCurrentMemberValue() const ODRX_OVERRIDE;

    virtual void putCurrentMember(const OdRxValue& anItem) ODRX_OVERRIDE;
    virtual void addBeforeCurrentMember(const OdRxValue& anItem) ODRX_OVERRIDE;
    virtual void addAfterCurrentMember(const OdRxValue& anItem) ODRX_OVERRIDE;
    virtual bool removeCurrentMember() ODRX_OVERRIDE;

    virtual int getValueBound() const ODRX_OVERRIDE;
    virtual bool testCurrentMember() const ODRX_OVERRIDE;

    virtual const OdRxValueType& type() const ODRX_OVERRIDE;

  private:
    typedef OdArray<TType>  InternalArray;

    typename InternalArray::size_type   m_index;
    TContainer&                         m_collection;
    bool                                m_isBegin;
  };


  template<typename TItem>
  class List;

  namespace IteratorImpl
  {
    template <class TContainer, class TType>
    class createAggrInstanceAsCurrentMember
    {
    public:
      static OdDAI::Aggr* Impl(TContainer& container, typename OdArray<TType>::size_type place)
      {
        throw DaiException(sdaiEX_NSUP, "Expression evaluation not supported", TD_FUNC);
      }
    };

    template <class TContainer, class TType>
    class createAggrInstanceBeforeCurrentMember
    {
    public:
      static OdDAI::Aggr* Impl(TContainer& container, typename OdArray<TType>::size_type place)
      {
        throw DaiException(sdaiEX_NSUP, "Expression evaluation not supported", TD_FUNC);
      }
    };

    template <class TContainer, class TType>
    class createAggrInstanceAfterCurrentMember
    {
    public:
      static OdDAI::Aggr* Impl(TContainer& container, typename OdArray<TType>::size_type place)
      {
        throw DaiException(sdaiEX_NSUP, "Expression evaluation not supported", TD_FUNC);
      }
    };

    template <class TContainer, class TType>
    class putCurrentMember
    {
    public:
      static void Impl(TContainer& container, typename OdArray<TType>::size_type place, const TType& anItem)
      {
        throw DaiException(sdaiEX_NSUP, "Expression evaluation not supported", TD_FUNC);
      }
    };

    template <class TContainer, class TType>
    class addBeforeCurrentMember
    {
    public:
      static void Impl(TContainer& container, typename OdArray<TType>::size_type place, const TType& anItem)
      {
        // Do nothing
      }
    };

    template <class TContainer, class TType>
    class addAfterCurrentMember
    {
    public:
      static void Impl(TContainer& container, typename OdArray<TType>::size_type place, const TType& anItem)
      {
        // Do nothing
      }
    };

    template <class TContainer, class TType>
    class removeCurrentMember
    {
    public:
      static bool Impl(TContainer& container, typename OdArray<TType>::size_type place)
      {
        throw DaiException(sdaiEX_NSUP, "Expression evaluation not supported", TD_FUNC);
      }
    };

    template <class TContainer, class TType>
    inline TType processPasteValue(IteratorCollection<TContainer, TType>& iteratorToPaste, 
                                   const OdRxValue& anItem, 
                                   TContainer& collection)
    {
      TType valueProxy = collection.template generateAggrItem<TType>();

      if (!(anItem >> valueProxy))
      {
        throw DaiException(sdaiVT_NVLD, "Value type invalid ", TD_FUNC);
      }

      if (iteratorToPaste.getValueBound() == 0)
      {
        throw DaiException(sdaiAI_NSET, "Aggregate instance is empty", TD_FUNC);
      }

      if (!iteratorToPaste.testCurrentMember())
      {
        throw DaiException(sdaiIR_NSET, "Current member is not defined", TD_FUNC);
      }

      return valueProxy;
    }

    template <class TContainer, class TType,
      typename std::enable_if<!std::is_base_of<OdDAI::List<TType>, TContainer>::value, bool>::type = true >
    inline TType processPasteValueList(IteratorCollection<TContainer, TType>& iteratorToPaste, 
                                       const OdRxValue& anItem,
                                       TContainer& collection)
    {
      throw DaiException(sdaiAI_NVLD, "The aggregate instance is not a list", TD_FUNC);
    }

    template <class TContainer, class TType,
      typename std::enable_if<std::is_base_of<OdDAI::List<TType>, TContainer>::value, bool>::type = true >
    inline TType processPasteValueList(IteratorCollection<TContainer, TType>& iteratorToPaste, 
                                       const OdRxValue& anItem, 
                                       TContainer& collection)
    {
      TType valueProxy = collection.template generateAggrItem<TType>();

      if (!(anItem >> valueProxy))
      {
        throw DaiException(sdaiVT_NVLD, "Value type invalid ", TD_FUNC);
      }

      return valueProxy;
    }
  }

  template  <class TContainer, class TType>
  IteratorCollection<TContainer, TType>::IteratorCollection(Aggr& collection)
    : m_collection(*reinterpret_cast<TContainer*>(&collection))
    , m_isBegin(false)
  {
    beginning();
  }

  template <class TContainer, class TType>
  void IteratorCollection<TContainer, TType>::beginning()
  {
    m_isBegin = true;
    m_index = 0;
  }

  template <class TContainer, class TType>
  bool IteratorCollection<TContainer, TType>::next()
  {
    const OdArray<TType>* internalArray = m_collection;

    if (!internalArray)
    {
      return false;
    }

    if (m_isBegin)
    {
      m_isBegin = false;
      return m_index != internalArray->size();
    }

    if (m_index != internalArray->size())
    {
      ++m_index;
      return m_index != internalArray->size();
    }

    return false;
  }

  template <class TContainer, class TType>
  bool IteratorCollection<TContainer, TType>::previous()
  {
    if (m_isBegin)
    {
      return false;
    }

    if (m_index != 0)
    {
      --m_index;
      return true;
    }

    m_isBegin = true;
    return false;
  }

  template <class TContainer, class TType>
  void IteratorCollection<TContainer, TType>::end()
  {
    const OdArray<TType>* internalArray = m_collection;
    m_index = internalArray ? internalArray->size() : 0;
  }
  
  template <class TContainer, class TType>
  Aggr* IteratorCollection<TContainer, TType>::createAggrInstanceAsCurrentMember()
  {
    return IteratorImpl::createAggrInstanceAsCurrentMember<TContainer, TType>::Impl(m_collection, m_index);
  }
  
  template <class TContainer, class TType>
  Aggr* IteratorCollection<TContainer, TType>::createAggrInstanceBeforeCurrentMember()
  {
    return IteratorImpl::createAggrInstanceBeforeCurrentMember<TContainer, TType>::Impl(m_collection, m_index);
  }

  template <class TContainer, class TType>
  Aggr* IteratorCollection<TContainer, TType>::createAggrInstanceAfterCurrentMember()
  {
    return IteratorImpl::createAggrInstanceAfterCurrentMember<TContainer, TType>::Impl(m_collection, m_index);
  }

  template <class TContainer, class TType>
  OdRxValue IteratorCollection<TContainer, TType>::getCurrentMemberValue() const
  {
    if (!testCurrentMember())
    {
      throw DaiException(sdaiIR_NSET, "Current member is not defined", TD_FUNC);
    }

    const OdArray<TType>* internalArray = m_collection;
    ODA_ASSERT(internalArray && "can not be here cause testCurrentMember should exclude this situation?");

    return *(internalArray->begin() + m_index);
  }

  template <class TContainer, class TType>
  OdRxValue IteratorCollection<TContainer, TType>::getCurrentMember() const
  {
    if (!testCurrentMember())
    {
      throw DaiException(sdaiIR_NSET, "Current member is not defined", TD_FUNC);
    }

    const OdArray<TType>* internalArray = m_collection;
    ODA_ASSERT(internalArray && "can not be here cause testCurrentMember should exclude this situation?");

#ifdef _AGGR_RETURN_PTR
    return _getCurrentMemberTyped(const_cast<OdArray<TType>* >(internalArray), m_index);
#else
    return *(internalArray->begin() + m_index);
#endif
  }

  template <class TContainer, class TType>
  void IteratorCollection<TContainer, TType>::putCurrentMember(const OdRxValue& anItem)
  {
    TType valueProxy = IteratorImpl::processPasteValue(*this, anItem, m_collection);
    IteratorImpl::putCurrentMember<TContainer, TType>::Impl(m_collection, m_index, valueProxy);
  }

  template <class TContainer, class TType>
  void IteratorCollection<TContainer, TType>::addBeforeCurrentMember(const OdRxValue& anItem)
  {
    TType valueProxy = IteratorImpl::processPasteValueList(*this, anItem, m_collection);
    IteratorImpl::addBeforeCurrentMember<TContainer, TType>::Impl(m_collection, m_index, valueProxy);
    next();
  }

  template <class TContainer, class TType>
  void IteratorCollection<TContainer, TType>::addAfterCurrentMember(const OdRxValue& anItem)
  {
    TType valueProxy = IteratorImpl::processPasteValueList(*this, anItem, m_collection);
    IteratorImpl::addAfterCurrentMember<TContainer, TType>::Impl(m_collection, m_index, valueProxy);
  }

  template <class TContainer, class TType>
  bool IteratorCollection<TContainer, TType>::removeCurrentMember()
  {
    bool wasDeleted = IteratorImpl::removeCurrentMember<TContainer, TType>::Impl(m_collection, m_index);
    previous();
    return wasDeleted;
  }
  
  template <class TContainer, class TType>
  int IteratorCollection<TContainer, TType>::getValueBound() const
  {
    const OdArray<TType>* internalArray = m_collection;
    return internalArray ? internalArray->size() : 0;
  }

  template <class TContainer, class TType>
  bool IteratorCollection<TContainer, TType>::testCurrentMember() const
  {
    const OdArray<TType>* internalArray = m_collection;
    return internalArray && m_index != internalArray->size() && !m_isBegin;
  }

  template <class TContainer, class TType>
  const OdRxValueType& IteratorCollection<TContainer, TType>::type() const
  {
    return OdRxValueType::Desc<TType>::value();
  }
}


#endif // _DAI_ITERATOR_H
