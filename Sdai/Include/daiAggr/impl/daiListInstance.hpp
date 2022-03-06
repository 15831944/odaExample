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

#ifndef _DAI_LIST_INSTANCE_H
#define _DAI_LIST_INSTANCE_H

#include <daiSelectValueType.h>
#include <daiEnumValueType.h>

#define STL_USING_MAP
#include "OdaSTL.h"


namespace OdDAI
{
  template<typename TItem>
  class ListInstanceBase
    : public AggrOrderedInstance<TItem>
  {
  public:
    using container_type = List<TItem>;
    using item_type = TItem;

    static const AggrType type_aggr;

    virtual IteratorPtr createIterator(Aggr& aggrHolder) ODRX_OVERRIDE
    {
      IteratorPtr pIter = new OdDAI::IteratorCollection<OdDAI::List<TItem>, TItem>(aggrHolder);
      return pIter;
    }

    virtual ConstIteratorPtr createConstIterator(const Aggr& aggrHolder) const ODRX_OVERRIDE
    {
      ConstIteratorPtr pIter = new OdDAI::ConstIteratorCollection<OdDAI::List<TItem>, TItem>(aggrHolder);
      return pIter;
    }

    virtual void insertOdRxValueByIndex(int  index, const OdRxValue& value) override
    {
      TItem transitValue = this->generateAggrItem();
      if ((value >> transitValue) == true)
      {
        addByIndex(index, transitValue);
      }
    }


    virtual AggrType aggrType() const ODRX_OVERRIDE
    {
      return OdDAI::AggrType::aggrTypeList;
    }

    virtual void addByIndex(int  indexToAdd, const TItem& elementToAdd) 
    {
      unsigned int internalIndexToAdd = this->toInternalIndex(indexToAdd);

      if (this->m_itemCollection.size() > internalIndexToAdd)
      {
        this->m_itemCollection.insertAfterValue(indexToAdd, elementToAdd);
      }
      else if (this->m_itemCollection.size() == internalIndexToAdd)
      {
        this->m_itemCollection.pushBackValue(elementToAdd);
      }
      else
      {
        throw OdDAI::DaiException(sdaiIX_NVLD, "Index invalid ", TD_FUNC);
      }
    }

    virtual void addAggregateInstanceByIndex(int index, Aggr*& aggr) 
    {
      throw OdDAI::DaiException(sdaiEX_NSUP, "Expression evaluation not supported ", TD_FUNC);
    }

    virtual void removeByIndex(int  indexToRemove) 
    {
      this->indexCheck(indexToRemove);

      unsigned int internalIndexToRemove = this->toInternalIndex(indexToRemove);
      if (internalIndexToRemove < this->m_itemCollection.size())
      {
        this->m_itemCollection.removeByIndex(internalIndexToRemove);
      }
    }

    virtual int getLowerBound() const  ODRX_OVERRIDE
    {
      return 0;
    }

    virtual int getUpperBound() const  ODRX_OVERRIDE
    {
      return static_cast<int>(this->m_itemCollection.size());
    }

    int  getValueBoundByIndex(int  index)
    {
      this->indexCheck(index);
      return index;
    }

  protected:
    ListInstanceBase()
      : AggrOrderedInstance<TItem>()
    {
    }

    virtual bool removeOdRxValueByIndex(int index)  ODRX_OVERRIDE
    {
      removeByIndex(index);
      return true;
    }
  };

  template<class TItem>
  const AggrType ListInstanceBase<TItem>::type_aggr = aggrTypeList;
}


namespace OdDAI
{
  template<typename TItem>
  class ListInstance
  : public ListInstanceBase<TItem>
  {
  public:
    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new ListInstance();
      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }
      return new List<TItem>(clonedInstance);
    }

    static AggrInstance* getDefaultInstance()
    {
      return &AggrInstanceDefault<ListInstance>::instance();
    }

    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType)
    {
      return &AggrInstanceDefault<ListInstance>::instance();
    }

    virtual AggrInstance* createEmpty() const ODRX_OVERRIDE
    {
      return new ListInstance();
    }

    virtual  AggrInstance* defaultInstance() const ODRX_OVERRIDE
    {
      return getDefaultInstance();
    }
  };
}


namespace OdDAI
{
  template<>
  class DAI_EXPORT ListInstance<OdDAI::Select>
    : public ListInstanceBase<OdDAI::Select>
  {
  public:
    ListInstance(AggrInstance* defaultInstance)
      : m_defaultInstance(defaultInstance)
    {
    }

    AggrInstance* createEmpty() const override
    {
      return new ListInstance(m_defaultInstance);
    }

    AggrInstance* defaultInstance() const override
    {
      return m_defaultInstance;
    }

    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new ListInstance<OdDAI::Select>(m_defaultInstance);
      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }
      return new List<OdDAI::Select>(clonedInstance);
    }

    virtual OdDAI::Select  generateAggrItem() const;

    static AggrInstance* getDefaultInstance();
    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType);

  private:
    AggrInstance* m_defaultInstance;
  };

  template<>
  class TypedAggrInstanceDefault<ListInstance<OdDAI::Select> >
    : public AggrInstanceDefaultBase<ListInstance<OdDAI::Select> >
  {
  public:
    TypedAggrInstanceDefault(const AggregationType* aggregationType)
      : m_aggregationType(aggregationType)
    {}

    static AggrInstance& getDefaultInstance()
    {
      static TypedAggrInstanceDefault<ListInstance<OdDAI::Select> > null_instance(nullptr);
      return null_instance;
    }

    static AggrInstance& getDefaultInstance(AggregationType* aggregationType);

    virtual ~TypedAggrInstanceDefault() {}

    virtual AggrInstance* defaultInstance() const  ODRX_OVERRIDE
    {
      return const_cast<TypedAggrInstanceDefault<ListInstance<OdDAI::Select> >*>(this);
    }

    virtual AggrInstance* createEmpty() const  ODRX_OVERRIDE
    {
      auto newInstance = new ListInstance<OdDAI::Select>(defaultInstance());
      return newInstance;
    }

    const AggregationType* aggregationType() const {
      return m_aggregationType;
    }

  private:
    const AggregationType* m_aggregationType = nullptr;
  };
}

namespace OdDAI
{
  template<>
  class DAI_EXPORT ListInstance<OdDAI::Enum>
    : public ListInstanceBase<OdDAI::Enum>
  {
  public:
    ListInstance(AggrInstance* defaultInstance)
      : m_defaultInstance(defaultInstance)
    {
    }

    AggrInstance* createEmpty() const override
    {
      return new ListInstance(m_defaultInstance);
    }

    AggrInstance* defaultInstance() const override
    {
      return m_defaultInstance;
    }

    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new ListInstance<OdDAI::Enum>(m_defaultInstance);
      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }
      return new List<OdDAI::Enum>(clonedInstance);
    }

    virtual OdDAI::Enum  generateAggrItem() const;

    static AggrInstance* getDefaultInstance();
    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType);

  private:
    AggrInstance* m_defaultInstance;
  };

  template<>
  class TypedAggrInstanceDefault<ListInstance<OdDAI::Enum> >
    : public AggrInstanceDefaultBase<ListInstance<OdDAI::Enum> >
  {
  public:
    TypedAggrInstanceDefault(const AggregationType* aggregationType)
      : m_aggregationType(aggregationType)
    {}

    static AggrInstance& getDefaultInstance()
    {
      static TypedAggrInstanceDefault<ListInstance<OdDAI::Enum> > null_instance(nullptr);
      return null_instance;
    }

    static AggrInstance& getDefaultInstance(AggregationType* aggregationType);

    virtual ~TypedAggrInstanceDefault() {}

    virtual AggrInstance* defaultInstance() const  ODRX_OVERRIDE
    {
      return const_cast<TypedAggrInstanceDefault<ListInstance<OdDAI::Enum> >*>(this);
    }

    virtual AggrInstance* createEmpty() const  ODRX_OVERRIDE
    {
      auto newInstance = new ListInstance<OdDAI::Enum>(defaultInstance());
      return newInstance;
    }

    const AggregationType* aggregationType() const {
      return m_aggregationType;
    }

  private:
    const AggregationType* m_aggregationType = nullptr;
  };
}

namespace OdDAI
{
  template<>
  class DAI_EXPORT ListInstance<OdDAI::Aggr*>
    : public ListInstanceBase<OdDAI::Aggr*>
  {
  public:
    using AggrRawPtr = OdDAI::Aggr* ;

  public:
    ListInstance(AggrInstance* defaultInstance)
      : m_defaultInstance(defaultInstance)
    {
    }

    AggrInstance* createEmpty() const override
    {
      return new ListInstance(m_defaultInstance);
    }

    AggrInstance* defaultInstance() const override
    {
      return m_defaultInstance;
    }

    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new ListInstance<OdDAI::Aggr*>(m_defaultInstance);
      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }
      return new List<OdDAI::Aggr*>(clonedInstance);
    }

    void addByIndex(int indexToAdd, const AggrRawPtr& elementToAdd) override
    {
      throw OdDAI::DaiException(sdaiEX_NSUP, "Expression evaluation not supported ", TD_FUNC);
    }

    void createAggrInstanceByIndex(int  indexToCreate, Aggr*& newAggr) override;

    void addAggregateInstanceByIndex(int index, Aggr*& aggr) override;

    OdDAI::Aggr*  generateAggrItem() const override;

    bool compareTo(const AggrInstance* to) const override;

    static AggrInstance* getDefaultInstance();
    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType);

  private:
    AggrInstance* m_defaultInstance;
  };

  template<>
  class TypedAggrInstanceDefault<ListInstance<OdDAI::Aggr*> >
    : public AggrInstanceDefaultBase<ListInstance<OdDAI::Aggr*> >
  {
  public:
    TypedAggrInstanceDefault(const AggregationType* aggregationType)
      : m_aggregationType(aggregationType)
    {}

    static AggrInstance& getDefaultInstance()
    {
      static TypedAggrInstanceDefault<ListInstance<OdDAI::Aggr*> > null_instance(nullptr);
      return null_instance;
    }

    static AggrInstance& getDefaultInstance(AggregationType* aggregationType);

    virtual ~TypedAggrInstanceDefault() {}

    AggrInstance* defaultInstance() const  override
    {
      return const_cast<TypedAggrInstanceDefault<ListInstance<OdDAI::Aggr*> >*>(this);
    }

    AggrInstance* createEmpty() const  override
    {
      auto newInstance = new ListInstance<OdDAI::Aggr*>(defaultInstance());
      return newInstance;
    }

    const AggregationType* aggregationType() const {
      return m_aggregationType;
    }

  private:
    const AggregationType* m_aggregationType = nullptr;
  };
}


/** A special class for internal use. */
namespace OdDAI
{
  template<typename TItem>
  List<TItem>::List()
    : AggrOrdered(ListInstance<TItem>::getDefaultInstance())
  {
  }

  template<typename TItem>
  List<TItem>::List(const AggregationType* aggregationType)
    : AggrOrdered(ListInstance<TItem>::getDefaultInstance(aggregationType))
  {
  }

  template<typename TItem>
  List<TItem>::List(AggrInstance* defaultInstance)
    : AggrOrdered(defaultInstance)
  {
  }

  template<typename TItem>
  void List<TItem>::addByIndex(int  indexToAdd, const TItem & elementToAdd)
  {
    Aggr::instance<ListInstance<TItem>*>()->addByIndex(indexToAdd, elementToAdd);
  }
  
  template<typename TItem>
  void List<TItem>::addAggregateInstanceByIndex(int  indexToAdd, Aggr*& aggr)
  {
    Aggr::instance<ListInstance<TItem>*>()->addAggregateInstanceByIndex(indexToAdd, aggr);
  }
  
  template<typename TItem>
  void List<TItem>::removeByIndex(int  ind)
  {
    Aggr::instance<ListInstance<TItem>*>()->removeByIndex(ind);
  }
  
  template<typename TItem>
  int  List<TItem>::getValueBoundByIndex(int  index)
  {
    throw OdError(eNotImplementedYet);
  }

  template<typename TItem>
  bool List<TItem>::operator == (const List<TItem>& aggr) const
  {
    if (isNil() || aggr.isNil())
    {
      return empty() == aggr.empty();
    }

    return Aggr::instance<ListInstance<TItem>*>()->compareTo(aggr.instance<ListInstance<TItem>*>());
  }

  template<typename TItem>
  List<TItem>& List<TItem>::operator= (const List<TItem>& right) 
  {
    if (&right != this)
    {
      auto aggrArray = static_cast<const OdArray<TItem>*>(right);
      if (aggrArray != nullptr)
      {
        setArray(*aggrArray);
      }
    }

    return *this;
  }

}

namespace OdDAI
{
  namespace IteratorImpl
  {
    template<>
    class createAggrInstanceAsCurrentMember<OdDAI::List<OdDAI::Aggr*>, OdDAI::Aggr*>
    {
    public:
      static Aggr* Impl(OdDAI::List<OdDAI::Aggr*>& container, OdArray<OdDAI::Aggr*>::size_type currentItertor)
      {
        OdDAI::Aggr* aggrBase = NULL;
        container.createAggrInstanceByIndex(currentItertor, aggrBase);
        return aggrBase;
      }
    };

    template<>
    class createAggrInstanceAfterCurrentMember<OdDAI::List<OdDAI::Aggr*>, OdDAI::Aggr*>
    {
    public:
      static OdDAI::Aggr* Impl(OdDAI::List<OdDAI::Aggr*>& container, OdArray<OdDAI::Aggr*>::size_type currentItertor)
      {
        OdDAI::Aggr* aggrBase = NULL;
        container.addAggregateInstanceByIndex(static_cast<int>(currentItertor), aggrBase);

        return aggrBase;
      }
    };

    template<>
    class createAggrInstanceBeforeCurrentMember<OdDAI::List<OdDAI::Aggr*>, OdDAI::Aggr*>
    {
    public:
      static OdDAI::Aggr* Impl(OdDAI::List<OdDAI::Aggr*>& container, OdArray<OdDAI::Aggr*>::size_type currentItertor)
      {
        OdDAI::Aggr* aggrBase = nullptr;
        size_t  currentIndex = currentItertor;
        if (currentIndex > 0)
        {
          container.addAggregateInstanceByIndex(static_cast<int>(currentIndex - 1), aggrBase);
        }
        else if (currentIndex == 0)
        {
          ODA_ASSERT(0 && "Attempt to set value before beginning position");
        }
        return aggrBase;
      }
    };


    template <class TType>
    class putCurrentMember<List<TType>, TType>
    {
    public:
      static void Impl(List<TType>& container, typename OdArray<TType>::size_type place, const TType& anItem)
      {
        container.putByIndex(static_cast<int>(place), anItem);
      }
    };


    template <class TType>
    class addBeforeCurrentMember<List<TType>, TType>
    {
    public:
      static void Impl(List<TType>& container, typename OdArray<TType>::size_type place, const TType& anItem)
      {
        container.addByIndex(static_cast<int>(place - 1), anItem);
      }
    };

    template <class TType>
    class addAfterCurrentMember<List<TType>, TType>
    {
    public:
      static void Impl(List<TType>& container, typename OdArray<TType>::size_type place, const TType& anItem)
      {
        container.addByIndex(static_cast<int>(place), anItem);
      }
    };

    template <class TType>
    class removeCurrentMember<List<TType>, TType>
    {
    public:
      static bool Impl(List<TType>& container, typename OdArray<TType>::size_type place)
      {
        container.removeByIndex(static_cast<int>(place));
        return true;
      }
    };
  }
}
//DOM-IGNORE-END

#endif // _DAI_AGGR_H
