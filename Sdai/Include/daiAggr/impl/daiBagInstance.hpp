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

#ifndef _DAI_BAG_INSTANCE_H
#define _DAI_BAG_INSTANCE_H

#define STL_USING_MAP
#include "OdaSTL.h"


namespace OdDAI
{
  template<typename TItem>
  class BagInstanceBase
    : public AggrUnorderedInstance<TItem>
  {
  public:
    using container_type = Bag<TItem>;
    using item_type = TItem;

    static const AggrType type_aggr;

    virtual IteratorPtr createIterator(Aggr& aggrHolder) ODRX_OVERRIDE
    {
      IteratorPtr pIter = new OdDAI::IteratorCollection<OdDAI::Bag<TItem>, TItem>(aggrHolder);
      return pIter;
    }

    virtual ConstIteratorPtr createConstIterator(const Aggr& aggrHolder) const ODRX_OVERRIDE
    {
      ConstIteratorPtr pIter = new OdDAI::ConstIteratorCollection<OdDAI::Bag<TItem>, TItem>(aggrHolder);
      return pIter;
    }

    virtual AggrType aggrType() const
    {
      return aggrTypeBag;
    }

    virtual bool Add(const TItem& elementToAdd)
    {
      this->m_itemCollection.pushBackValue(elementToAdd);
      return true;
    }

    virtual bool Remove(const TItem& elementToRemove)
    {
      bool wasDeleted = false;
      return this->m_itemCollection.removeByValue(elementToRemove);
    }

  protected:
    BagInstanceBase()
      : AggrUnorderedInstance<TItem>()
    {
    }

  };

  template<class TItem>
  const AggrType BagInstanceBase<TItem>::type_aggr = aggrTypeBag;
}

namespace OdDAI
{
  template<typename TItem>
  class BagInstance
    : public BagInstanceBase<TItem>
  {
  public:
    virtual AggrInstance* createEmpty() const
    {
      return new BagInstance();
    }

    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new BagInstance();
      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }
      return new Bag<TItem>(clonedInstance);
    }

    virtual  AggrInstance* defaultInstance() const
    {
      return getDefaultInstance();
    }

    static AggrInstance* getDefaultInstance()
    {
      return &AggrInstanceDefault<BagInstance>::instance();
    }

    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType)
    {
      return &AggrInstanceDefault<BagInstance>::instance();
    }
  };
}

namespace OdDAI
{
  template<>
  class BagInstance<OdDAI::Select>
    : public BagInstanceBase<OdDAI::Select>
  {
  public:
    BagInstance(AggrInstance* defaultInstance)
      : m_defaultInstance(defaultInstance)
    {
    }

    virtual AggrInstance* createEmpty() const
    {
      return new BagInstance<OdDAI::Select>(m_defaultInstance);
    }

    AggrInstance* defaultInstance() const override
    {
      return m_defaultInstance;
    }

    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new BagInstance<OdDAI::Select>(m_defaultInstance);
      clonedInstance->copyFrom(this);
      return new Bag<OdDAI::Select>(clonedInstance);
    }

    virtual OdDAI::Select  generateAggrItem() const;

    static AggrInstance* getDefaultInstance();
    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType);


  private:
    AggrInstance* m_defaultInstance;

  };


  template<>
  class TypedAggrInstanceDefault<BagInstance<OdDAI::Select> >
    : public AggrInstanceDefaultBase<BagInstance<OdDAI::Select> >
  {
  public:
    TypedAggrInstanceDefault(const AggregationType* aggregationType)
      : m_aggregationType(aggregationType)
    {}

    static AggrInstance& getDefaultInstance()
    {
      static TypedAggrInstanceDefault<BagInstance<OdDAI::Select> > null_instance(nullptr);
      return null_instance;
    }

    static AggrInstance& getDefaultInstance(AggregationType* aggregationType);

    virtual ~TypedAggrInstanceDefault() {}

    virtual AggrInstance* defaultInstance() const  ODRX_OVERRIDE
    {
      return const_cast<TypedAggrInstanceDefault<BagInstance<OdDAI::Select> >*>(this);
    }

    virtual AggrInstance* createEmpty() const  ODRX_OVERRIDE
    {
      auto newInstance = new BagInstance<OdDAI::Select>(defaultInstance());
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
  class DAI_EXPORT BagInstance<OdDAI::Enum>
    : public BagInstanceBase<OdDAI::Enum>
  {
  public:
    BagInstance(AggrInstance* defaultInstance)
      : m_defaultInstance(defaultInstance)
    {
    }

    AggrInstance* createEmpty() const override
    {
      return new BagInstance(m_defaultInstance);
    }

    AggrInstance* defaultInstance() const override
    {
      return m_defaultInstance;
    }

    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new BagInstance<OdDAI::Enum>(m_defaultInstance);
      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }
      return new Bag<OdDAI::Enum>(clonedInstance);
    }

    virtual OdDAI::Enum  generateAggrItem() const;

    static AggrInstance* getDefaultInstance();
    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType);

  private:
    AggrInstance* m_defaultInstance;
  };

  template<>
  class TypedAggrInstanceDefault<BagInstance<OdDAI::Enum> >
    : public AggrInstanceDefaultBase<BagInstance<OdDAI::Enum> >
  {
  public:
    TypedAggrInstanceDefault(const AggregationType* aggregationType)
      : m_aggregationType(aggregationType)
    {}

    static AggrInstance& getDefaultInstance()
    {
      static TypedAggrInstanceDefault<BagInstance<OdDAI::Enum> > null_instance(nullptr);
      return null_instance;
    }

    static AggrInstance& getDefaultInstance(AggregationType* aggregationType);

    virtual ~TypedAggrInstanceDefault() {}

    virtual AggrInstance* defaultInstance() const  ODRX_OVERRIDE
    {
      return const_cast<TypedAggrInstanceDefault<BagInstance<OdDAI::Enum> >*>(this);
    }

    virtual AggrInstance* createEmpty() const  ODRX_OVERRIDE
    {
      auto newInstance = new BagInstance<OdDAI::Enum>(defaultInstance());
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
  Bag<TItem>::Bag()
    : AggrUnordered(BagInstance<TItem>::getDefaultInstance())
  {
  }

  template<typename TItem>
  Bag<TItem>::Bag(const AggregationType* aggregationType)
    : AggrUnordered(BagInstance<TItem>::getDefaultInstance(aggregationType))
  {
  }


  template<typename TItem>
  Bag<TItem>::Bag(AggrInstance* defaultInstance)
    : AggrUnordered(defaultInstance)
  {
  }

  template<typename TItem>
  bool Bag<TItem>::operator == (const Bag<TItem>& aggr) const
  {
    if (isNil() || aggr.isNil())
    {
      return empty() == aggr.empty();
    }

    return Aggr::instance<BagInstance<TItem>*>()->compareTo(aggr.instance<BagInstance<TItem>*>());
  }

  template<typename TItem>
  Bag<TItem> & Bag<TItem>::operator=(const Bag & right)
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

//DOM-IGNORE-END

#endif // _DAI_AGGR_H
