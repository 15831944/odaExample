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

#ifndef _DAI_CONST_ITERATOR_COLLECTION_H
#define _DAI_CONST_ITERATOR_COLLECTION_H

#include "daiConstIterator.h"
#include "daiAggrMemberAccess.h"

#define STL_USING_ALGORITHM
#include "OdaSTL.h"

namespace OdDAI
{
  /** \details
  Class that represents type-specified const iterator.
  */
  template <class TContainer, class TType>
  class DAI_EXPORT ConstIteratorCollection
    : public ConstIterator
  {
  public:
    ConstIteratorCollection(const Aggr& collection);

    virtual void beginning() ODRX_OVERRIDE;

    virtual bool next() ODRX_OVERRIDE;
    virtual bool previous() ODRX_OVERRIDE;

    virtual void end()  ODRX_OVERRIDE;

    virtual const OdRxValue getCurrentMember() const ODRX_OVERRIDE;

    virtual int getValueBound() const ODRX_OVERRIDE;
    virtual bool testCurrentMember() const ODRX_OVERRIDE;

    virtual const OdRxValueType& type() const ODRX_OVERRIDE;

  private:

    typedef OdArray<TType>  InternalArray;

    typename InternalArray::size_type       m_index;
    const TContainer&                m_collection;
    bool                                    m_isBegin;
  };

  template  <class TContainer, class TType>
  ConstIteratorCollection<TContainer, TType>::ConstIteratorCollection(const Aggr& collection)
    : m_collection(*reinterpret_cast<const TContainer*>(&collection))
    , m_isBegin(false)
  {
    beginning();
  }

  template <class TContainer, class TType>
  void ConstIteratorCollection<TContainer, TType>::beginning()
  {
    m_isBegin = true;
    m_index = 0;
  }
  
  template <class TContainer, class TType>
  bool ConstIteratorCollection<TContainer, TType>::next()
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
  bool ConstIteratorCollection<TContainer, TType>::previous()
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
  void ConstIteratorCollection<TContainer, TType>::end()
  {
    const OdArray<TType>* internalArray = m_collection;

    if (!internalArray)
    {
      return;
    }

    m_index = internalArray->size();
  }

  template <class TContainer, class TType>
  const OdRxValue ConstIteratorCollection<TContainer, TType>::getCurrentMember() const
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
  int ConstIteratorCollection<TContainer, TType>::getValueBound() const
  {
    const OdArray<TType>* internalArray = m_collection;
    return internalArray ? internalArray->size() : 0;
  }
  
  template <class TContainer, class TType>
  bool ConstIteratorCollection<TContainer, TType>::testCurrentMember() const
  {
    const OdArray<TType>* internalArray = m_collection;
    return internalArray && m_index != internalArray->size() && !m_isBegin;
  }
  
  template <class TContainer, class TType>
  const OdRxValueType& ConstIteratorCollection<TContainer, TType>::type() const
  {
    return OdRxValueType::Desc<TType>::value();
  }
}


#endif // _DAI_CONST_ITERATOR_COLLECTION_H
