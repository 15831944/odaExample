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

#ifndef _DAI_SET_INSTANCE_H
#define _DAI_SET_INSTANCE_H

#include <daiSelectValueType.h>
#include <daiEnumValueType.h>

#define STL_USING_MAP
#include "OdaSTL.h"


namespace OdDAI
{
  template<typename TItem>
  class DAI_EXPORT SetInstanceBase
    : public AggrUnorderedInstance<TItem>
  {
    friend class AggrInstanceDefault<SetInstanceBase>;

  public:
    using container_type = Set<TItem>;
    using item_type = TItem;

    static const AggrType type_aggr;

    IteratorPtr createIterator(Aggr& aggrHolder) override
    {
      IteratorPtr pIter = new OdDAI::IteratorCollection<OdDAI::Set<TItem>, TItem>(aggrHolder);
      return pIter;
    }

    ConstIteratorPtr createConstIterator(const Aggr& aggrHolder) const override
    {
      ConstIteratorPtr pIter = new OdDAI::ConstIteratorCollection<OdDAI::Set<TItem>, TItem>(aggrHolder);
      return pIter;
    }

    AggrType aggrType() const override
    {
      return aggrTypeSet;
    }

    bool Add(const TItem& elementToAdd) override
    {
      if (this->m_itemCollection.getCollection().isEmpty())
      {
        this->m_itemCollection.pushBackValue(elementToAdd);
        return true;
      }

      const TItem* lowerBound = std::lower_bound(this->m_itemCollection.getCollection().begin(),
                                                 this->m_itemCollection.getCollection().end(),
                                                 elementToAdd,
                                                 customCompare<TItem>);

      if (!lowerBound || lowerBound == this->m_itemCollection.getCollection().end())
      {
        this->m_itemCollection.pushBackValue(elementToAdd);
        return true;
      }

      if (*lowerBound == elementToAdd)
      {
        return false;
      }

      ODA_ASSERT(elementToAdd < *lowerBound);

      this->m_itemCollection.insertBeforeValue(lowerBound - this->m_itemCollection.getCollection().begin(), elementToAdd);

      return true;
    }

    bool Remove(const TItem& elementToRemove) override
    {
      if (this->m_itemCollection.getCollection().isEmpty())
      {
        return false;
      }

      const TItem* lowerBound = std::lower_bound(this->m_itemCollection.getCollection().begin(),
                                                 this->m_itemCollection.getCollection().end(),
                                                 elementToRemove,
                                                 customCompare<TItem>);

      if (*lowerBound != elementToRemove)
      {
        return false;
      }

      this->m_itemCollection.removeByIndex(lowerBound - this->m_itemCollection.getCollection().begin());
      return true;
    }


    void setArray(const OdArray<TItem>& newArray)  override
    {
      this->m_itemCollection.setCollection(newArray);
      this->m_itemCollection.sortAndRemoveDuplicates();
    }

    bool read(IAggrReader<TItem>& aggrReader) override
    {
      if (AggrInstanceCommonBase<TItem>::read(aggrReader))
      {
        this->m_itemCollection.sortAndRemoveDuplicates();
        return true;
      }

      return false;
    }


  protected:
    SetInstanceBase()
      : AggrUnorderedInstance<TItem>()
    {
    }
  };

  template<class TItem>
  const AggrType SetInstanceBase<TItem>::type_aggr = aggrTypeSet;
}


namespace OdDAI
{
  template<typename TItem>
  class DAI_EXPORT SetInstance
    : public SetInstanceBase<TItem>
  {
  public:
    AggrInstance* createEmpty() const override
    {
      return new SetInstance();
    }

    AggrInstance* defaultInstance() const override
    {
      return getDefaultInstance();
    }

    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new SetInstance();
      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }
      return new Set<TItem>(clonedInstance);
    }

    static AggrInstance* getDefaultInstance()
    {
      return &AggrInstanceDefault<SetInstance>::instance();
    }

    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType)
    {
      return &AggrInstanceDefault<SetInstance>::instance();
    }
  };
}


namespace OdDAI 
{
  template<>
  class DAI_EXPORT SetInstance<OdDAI::Select>
    : public SetInstanceBase<OdDAI::Select>
  {
  public:
    SetInstance(AggrInstance* defaultInstance)
      : m_defaultInstance(defaultInstance)
    {
    }

    AggrInstance* createEmpty() const override
    {
      return new SetInstance(m_defaultInstance);
    }

    AggrInstance* defaultInstance() const override
    {
      return m_defaultInstance;
    }

    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new SetInstance<OdDAI::Select>(m_defaultInstance);
      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }
      return new Set<OdDAI::Select>(clonedInstance);
    }

    virtual OdDAI::Select  generateAggrItem() const;

    static AggrInstance* getDefaultInstance();
    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType);

  private:
    AggrInstance* m_defaultInstance;
  };

  template<>
  class TypedAggrInstanceDefault<SetInstance<OdDAI::Select> >
    : public AggrInstanceDefaultBase<SetInstance<OdDAI::Select> >
  {
  public:
    TypedAggrInstanceDefault(const AggregationType* aggregationType)
      : m_aggregationType(aggregationType)
    {}

    static AggrInstance& getDefaultInstance()
    {
      static TypedAggrInstanceDefault<SetInstance<OdDAI::Select> > null_instance(nullptr);
      return null_instance;
    }

    static AggrInstance& getDefaultInstance(AggregationType* aggregationType);


    virtual ~TypedAggrInstanceDefault() {}

    virtual AggrInstance* defaultInstance() const  ODRX_OVERRIDE
    {
      return const_cast<TypedAggrInstanceDefault<SetInstance<OdDAI::Select> >*>(this);
    }

    virtual AggrInstance* createEmpty() const  ODRX_OVERRIDE
    {
      auto newInstance = new SetInstance<OdDAI::Select>(defaultInstance());
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
  class DAI_EXPORT SetInstance<OdDAI::Enum>
    : public SetInstanceBase<OdDAI::Enum>
  {
  public:
    SetInstance(AggrInstance* defaultInstance)
      : m_defaultInstance(defaultInstance)
    {
    }

    AggrInstance* createEmpty() const override
    {
      return new SetInstance(m_defaultInstance);
    }

    AggrInstance* defaultInstance() const override
    {
      return m_defaultInstance;
    }

    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new SetInstance<OdDAI::Enum>(m_defaultInstance);
      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }
      return new Set<OdDAI::Enum>(clonedInstance);
    }

    virtual OdDAI::Enum  generateAggrItem() const;

    static AggrInstance* getDefaultInstance();
    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType);

  private:
    AggrInstance* m_defaultInstance;
  };

  template<>
  class TypedAggrInstanceDefault<SetInstance<OdDAI::Enum> >
    : public AggrInstanceDefaultBase<SetInstance<OdDAI::Enum> >
  {
  public:
    static AggrInstance& getDefaultInstance()
    {
      static TypedAggrInstanceDefault<SetInstance<OdDAI::Enum> > null_instance(nullptr);
      return null_instance;
    }

    static AggrInstance& getDefaultInstance(AggregationType* aggregationType);

    TypedAggrInstanceDefault(const AggregationType* aggregationType)
      : m_aggregationType(aggregationType)
    {}

    virtual ~TypedAggrInstanceDefault() {}

    virtual AggrInstance* defaultInstance() const  ODRX_OVERRIDE
    {
      return const_cast<TypedAggrInstanceDefault<SetInstance<OdDAI::Enum> >*>(this);
    }

    virtual AggrInstance* createEmpty() const  ODRX_OVERRIDE
    {
      auto newInstance = new SetInstance<OdDAI::Enum>(defaultInstance());
      return newInstance;
    }

    const AggregationType* aggregationType() const {
      return m_aggregationType;
    }

  private:
    const AggregationType* m_aggregationType = nullptr;
  };
}


//DOM-IGNORE-BEGIN
namespace OdDAI
{
  template<typename TItem>
  Set<TItem>::Set()
    : AggrUnordered(SetInstance<TItem>::getDefaultInstance(nullptr))
  {
  }

  template<typename TItem>
  Set<TItem>::Set(const AggregationType* aggregationType)
    : AggrUnordered(SetInstance<TItem>::getDefaultInstance(aggregationType))
  {
  }


  template<typename TItem>
  Set<TItem>::Set(AggrInstance* defaultInstance)
    : AggrUnordered(defaultInstance)
  {
  }

  template<typename TItem>
  bool Set<TItem>::operator == (const Set<TItem>& aggr) const
  {
    if (isNil() || aggr.isNil())
    {
      return empty() == aggr.empty();
    }

    return Aggr::instance<SetInstance<TItem>*>()->compareTo(aggr.instance<SetInstance<TItem> *>());
  }

  template<typename TItem>
  Set<TItem>& Set<TItem>::operator=(const Set<TItem>& right)
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
    template <class TType>
    class removeCurrentMember<Set<TType>, TType>
    {
    public:
      static bool Impl(Set<TType>& container, typename OdArray<TType>::size_type place)
      {
        const OdArray<TType>* internalArray = container;
        
        if (!internalArray)
        {
          return false;
        }

        container.Remove(*(internalArray->begin() + place));
        return true;
      }
    };
  }
}


//DOM-IGNORE-END

#endif // _DAI_AGGR_H
