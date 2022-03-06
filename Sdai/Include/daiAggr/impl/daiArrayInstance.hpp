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

#ifndef _DAI_ARRAY_INSTANCE_H
#define _DAI_ARRAY_INSTANCE_H

#include "daiSelectValueType.h"
#include "daiEnumValueType.h"

#include "daiAggr/daiAggr.h"
#include "OdArray.h"

namespace OdDAI
{
  template<typename TItem>
  class DAI_EXPORT ArrayInstanceBase
    : public AggrOrderedInstance<TItem>
  {
  public:
    using container_type = Array<TItem>;
    using item_type = TItem;

    static const AggrType type_aggr;

    virtual IteratorPtr createIterator(Aggr& aggrHolder) ODRX_OVERRIDE
    {
      IteratorPtr pIter = new OdDAI::IteratorCollection<OdDAI::Array<TItem>, TItem>(aggrHolder);
      return pIter;
    }

    virtual ConstIteratorPtr createConstIterator(const Aggr& aggrHolder) const ODRX_OVERRIDE
    {
      ConstIteratorPtr pIter = new OdDAI::ConstIteratorCollection<OdDAI::Array<TItem>, TItem>(aggrHolder);
      return pIter;
    }

    void reindex()
    {
      this->m_itemCollection.removeAllByValue(OdDAI::Utils::getUnset<TItem>());
    }

    void resetIndex(int newLower, int newUpper)
    {
      if (newLower > newUpper)
      {
        throw OdDAI::DaiException(sdaiVA_NSET, "Value not set", TD_FUNC);
      }

      unsigned int copyOldFrom = toInternalIndex(m_lowerBound < newLower ? newLower : m_lowerBound);
      unsigned int copyOldTo = toInternalIndex(m_upperBound > newUpper ? newUpper : m_upperBound);

      if (copyOldFrom >= copyOldTo)
      {
        this->m_itemCollection.clear();
        this->m_itemCollection.resize(newUpper - newLower, OdDAI::Utils::getUnset<TItem>());
      }
      else
      {
        OdArray<TItem>  oldValues(this->m_itemCollection.getCollection());
        this->m_itemCollection.clear();
        this->m_itemCollection.resize(newUpper - newLower, OdDAI::Utils::getUnset<TItem>());

        unsigned int startCopyIndex = newLower < m_upperBound ? 0 : newLower - m_upperBound;

        this->m_itemCollection.assignRange(startCopyIndex, oldValues);
      }

      m_lowerBound = newLower;
      m_upperBound = newUpper;
    }

    virtual AggrType aggrType() const ODRX_OVERRIDE
    {
      return aggrTypeArray;
    }

    virtual int getLowerBound() const ODRX_OVERRIDE
    {
      return m_lowerBound;
    }

    virtual int getUpperBound() const ODRX_OVERRIDE
    {
      return m_upperBound;
    }


    bool testByIndex(int indexToTest) const
    {
      this->indexCheck(indexToTest);
      unsigned int internalIndex = toInternalIndex(indexToTest);
      return internalIndex < this->m_itemCollection.size() && this->m_itemCollection[internalIndex] != OdDAI::Utils::getUnset<TItem>();
    }

    void unsetValueByIndex(int indexToUnset)
    {
      this->indexCheck(indexToUnset);
      this->m_itemCollection.setValue(toInternalIndex(indexToUnset), OdDAI::Utils::getUnset<TItem>());
    }

    virtual int getUpperIndex() const 
    {
      if (this->m_itemCollection.size() != 0)
      {
        for (unsigned int itemIndex = this->m_itemCollection.size() - 1; itemIndex > 0; --itemIndex)
        {
          if (this->m_itemCollection[itemIndex] != OdDAI::Utils::getUnset<TItem>())
          {
            return toOuterIndex(itemIndex);
          }
        }
      }

      return m_lowerBound;
    }

    virtual int getLowerIndex() const 
    {
      for (unsigned int itemIndex = 0; itemIndex < this->m_itemCollection.size(); ++itemIndex)
      {
        if (this->m_itemCollection[itemIndex] != OdDAI::Utils::getUnset<TItem>())
        {
          return toOuterIndex(itemIndex);
        }
      }

      return m_lowerBound;
    }

    virtual void checkArrayBeforeSet(const OdArray<TItem>& newArray) ODRX_OVERRIDE
    {
      if (newArray.size() > static_cast<unsigned int>(getUpperBound() - getLowerBound()))
      {
        throw OdDAI::DaiException(sdaiSY_ERR, "Underlying system error", TD_FUNC);
      }
    }

  protected:
    ArrayInstanceBase()
      : AggrOrderedInstance<TItem>()
      , m_lowerBound(orderedDefaultLowerBound)
      , m_upperBound(orderedDefaultUpperBound)
    {
    }

    ArrayInstanceBase(int lowerBound, int upperBound)
      : AggrOrderedInstance<TItem>()
      , m_lowerBound(lowerBound)
      , m_upperBound(upperBound)
    {
      if (m_lowerBound > m_upperBound)
      {
        throw OdDAI::DaiException(sdaiVA_NSET, "Value not set", TD_FUNC);
      }
    }

    virtual unsigned int toInternalIndex(int index) const ODRX_OVERRIDE
    {
      if (index - m_lowerBound < 0)
      {
        throw OdDAI::DaiException(sdaiIX_NVLD, "Index invalid ", TD_FUNC);
      }

      return static_cast<unsigned int>(index - m_lowerBound);
    }

    virtual int toOuterIndex(unsigned int index) const ODRX_OVERRIDE
    {
      return m_lowerBound + static_cast<int>(index);
    }

    virtual bool removeOdRxValueByIndex(int index)  ODRX_OVERRIDE
    {
      unsetValueByIndex(index);
      return true;
    }


  private:
    int m_lowerBound;
    int m_upperBound;
  };

  template<class TItem>
  const AggrType ArrayInstanceBase<TItem>::type_aggr = aggrTypeArray;
}



namespace OdDAI
{
  template<typename TItem>
  inline int extractLowerBound(const AggrInstance* aggrInstance);

  template<typename TItem>
  inline int extractUpperBound(const AggrInstance* aggrInstance);

  template<typename TItem>
  class DAI_EXPORT ArrayInstance
    : public ArrayInstanceBase<TItem>
  {
  public:
    ArrayInstance() = default;
    ArrayInstance(AggrInstance* aggrInstance)
      : ArrayInstanceBase<TItem>(extractLowerBound<TItem>(aggrInstance), extractUpperBound<TItem>(aggrInstance))
      , m_defaultInstance(aggrInstance)
    {
    }

  public:
    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new ArrayInstance(m_defaultInstance);
      
      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }

      return new Array<TItem>(clonedInstance);
    }

    virtual AggrInstance* createEmpty() const ODRX_OVERRIDE
    {
      return new ArrayInstance(m_defaultInstance);
    }

    virtual  AggrInstance* defaultInstance() const ODRX_OVERRIDE
    {
      return m_defaultInstance;
    }

    static AggrInstance* getDefaultInstance();
    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType);

  private:
    AggrInstance* m_defaultInstance;
  };


  template<class TItem>
  class DAI_EXPORT TypedAggrInstanceDefault<ArrayInstance<TItem> >
    : public AggrInstanceDefaultBase<ArrayInstance<TItem> >
  {
  public:
    TypedAggrInstanceDefault(const AggregationType* aggregationType)
      : m_aggregationType(aggregationType)
    {}

    static AggrInstance& getDefaultInstance()
    {
      static TypedAggrInstanceDefault<ArrayInstance<TItem> > null_instance(nullptr);
      return null_instance;
    }

    static AggrInstance& getDefaultInstance(AggregationType* aggregationType);

    virtual ~TypedAggrInstanceDefault() {}

    virtual AggrInstance* defaultInstance() const  ODRX_OVERRIDE
    {
      return const_cast<TypedAggrInstanceDefault<ArrayInstance<TItem> >*>(this);
    }

    virtual AggrInstance* createEmpty() const  ODRX_OVERRIDE
    {
      auto newInstance = new ArrayInstance<TItem>(defaultInstance());
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
  class DAI_EXPORT ArrayInstance<OdDAI::Select>
    : public ArrayInstanceBase<OdDAI::Select>
  {
  public:
    ArrayInstance() = default;
    ArrayInstance(AggrInstance* aggrInstance)
      : ArrayInstanceBase<OdDAI::Select>(extractLowerBound<OdDAI::Select>(aggrInstance), extractUpperBound<OdDAI::Select>(aggrInstance))
      , m_defaultInstance(aggrInstance)
    {
    }

  public:
    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new ArrayInstance(m_defaultInstance);

      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }

      return new Array<OdDAI::Select>(clonedInstance);
    }

    virtual AggrInstance* createEmpty() const ODRX_OVERRIDE
    {
      return new ArrayInstance(m_defaultInstance);
    }

    virtual  AggrInstance* defaultInstance() const ODRX_OVERRIDE
    {
      return m_defaultInstance;
    }

    virtual OdDAI::Select  generateAggrItem() const;

    static AggrInstance* getDefaultInstance();
    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType);

  private:
    AggrInstance* m_defaultInstance = nullptr;
  };

}

namespace OdDAI
{
  template<>
  class DAI_EXPORT ArrayInstance<OdDAI::Enum>
    : public ArrayInstanceBase<OdDAI::Enum>
  {
  public:
    ArrayInstance() = default;
    ArrayInstance(AggrInstance* aggrInstance)
      : ArrayInstanceBase<OdDAI::Enum>(extractLowerBound<OdDAI::Enum>(aggrInstance), extractUpperBound<OdDAI::Enum>(aggrInstance))
      , m_defaultInstance(aggrInstance)
    {
    }

  public:
    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new ArrayInstance(m_defaultInstance);

      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }

      return new Array<OdDAI::Enum>(clonedInstance);
    }

    virtual AggrInstance* createEmpty() const ODRX_OVERRIDE
    {
      return new ArrayInstance(m_defaultInstance);
    }

    virtual  AggrInstance* defaultInstance() const ODRX_OVERRIDE
    {
      return m_defaultInstance;
    }

    virtual OdDAI::Enum  generateAggrItem() const;

    static AggrInstance* getDefaultInstance();
    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType);

  private:
    AggrInstance* m_defaultInstance;
  };

}

namespace OdDAI
{
  template<>
  class DAI_EXPORT ArrayInstance<OdDAI::Aggr*>
    : public ArrayInstanceBase<OdDAI::Aggr*>
  {
  public:
    using AggrRawPtr = OdDAI::Aggr*;

  public:
    ArrayInstance() = default;
    ArrayInstance(AggrInstance* aggrInstance)
      : ArrayInstanceBase<OdDAI::Aggr*>(extractLowerBound<OdDAI::Aggr*>(aggrInstance), extractUpperBound<OdDAI::Aggr*>(aggrInstance))
      , m_defaultInstance(aggrInstance)
    {
    }

  public:
    Aggr* cloneAndCreateAggrFrom(bool withItems = true) const override
    {
      auto clonedInstance = new ArrayInstance(m_defaultInstance);
      if (withItems)
      {
        clonedInstance->copyFrom(this);
      }
      return new Array<OdDAI::Aggr*>(clonedInstance);
    }

    AggrInstance* createEmpty() const override
    {
      return new ArrayInstance(m_defaultInstance);
    }

    AggrInstance* defaultInstance() const override
    {
      return m_defaultInstance;
    }

    void putByIndex(int  index, const AggrRawPtr& element) override
    {
      throw OdDAI::DaiException(sdaiEX_NSUP, "Expression evaluation not supported ", TD_FUNC);
    }


    void createAggrInstanceByIndex(int  index, Aggr*& newAggr) override;

    OdDAI::Aggr*  generateAggrItem() const override;

    bool compareTo(const AggrInstance* to) const override;

    static AggrInstance* getDefaultInstance();
    static AggrInstance* getDefaultInstance(const AggregationType* aggregationType);

  private:
    AggrInstance* m_defaultInstance = nullptr;
  };

}

/** A special class for internal use. */
namespace OdDAI
{
  template<typename TItem>
  Array<TItem>::Array()
    : AggrOrdered(ArrayInstance<TItem>::getDefaultInstance())
  {
  }

  template<typename TItem>
  Array<TItem>::Array(const AggregationType* aggregationType)
    : AggrOrdered(ArrayInstance<TItem>::getDefaultInstance(aggregationType))
  {
  }



  template<typename TItem>
  Array<TItem>::Array(AggrInstance* defaultInstance)
    : AggrOrdered(defaultInstance)
  {
  }


  template<typename TItem>
  void Array<TItem>::reindex()
  {
    Aggr::instance<ArrayInstance<TItem>*>()->reindex();
  }

  template<typename TItem>
  void Array<TItem>::resetIndex(int  lower, int upper)
  {
    Aggr::instance<ArrayInstance<TItem>*>()->resetIndex(lower, upper);
  }

  template<typename TItem>
  bool Array<TItem>::testByIndex(int  indexToTest) const
  {
    return Aggr::instance<ArrayInstance<TItem>*>()->testByIndex(indexToTest);
  }

  template<typename TItem>
  void Array<TItem>::unsetValueByIndex(int  indexToUnset)
  {
    Aggr::instance<ArrayInstance<TItem>*>()->unsetValueByIndex(indexToUnset);
  }

  template<typename TItem>
  int  Array<TItem>::getUpperIndex() const
  {
    return Aggr::instance<ArrayInstance<TItem>*>()->getUpperIndex();
  }

  template<typename TItem>
  int  Array<TItem>::getLowerIndex() const
  {
    return Aggr::instance<ArrayInstance<TItem>*>()->getLowerIndex();

  }

  template<typename TItem>
  bool Array<TItem>::operator == (const Array<TItem>& aggr) const
  {
    if (isNil() || aggr.isNil())
    {
      return empty() == aggr.empty();
    }

    return Aggr::instance<ArrayInstance<TItem>*>()->compareTo(aggr.instance<ArrayInstance<TItem>*>());
  }

  template<typename TItem>
  Array<TItem>& Array<TItem>::operator=(const Array<TItem>& right)
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
    class createAggrInstanceAsCurrentMember<OdDAI::Array<OdDAI::Aggr*>, OdDAI::Aggr*>
    {
    public:
      static Aggr* Impl(OdDAI::Array<OdDAI::Aggr*>& container, OdArray<OdDAI::Aggr*>::size_type currentItertor)
      {
        OdDAI::Aggr* aggrBase = NULL;
        size_t  currentIndex = currentItertor + static_cast<size_t>(container.getLowerBound());
        container.createAggrInstanceByIndex(static_cast<int>(currentIndex), aggrBase);
        return aggrBase;
      }
    };

    template<>
    class createAggrInstanceAfterCurrentMember<OdDAI::Array<OdDAI::Aggr*>, OdDAI::Aggr*>
    {
    public:
      static OdDAI::Aggr* Impl(OdDAI::Array<OdDAI::Aggr*>& container, OdArray<OdDAI::Aggr*>::size_type currentItertor)
      {
        OdDAI::Aggr* aggrBase = NULL;
        size_t  currentIndex = currentItertor;
        currentIndex += static_cast<size_t>(container.getLowerBound()) + 1;
        container.createAggrInstanceByIndex(static_cast<int>(currentIndex), aggrBase);

        return aggrBase;
      }
    };

    template<>
    class createAggrInstanceBeforeCurrentMember<OdDAI::Array<OdDAI::Aggr*>, OdDAI::Aggr*>
    {
    public:
      static OdDAI::Aggr* Impl(OdDAI::Array<OdDAI::Aggr*>& container, OdArray<OdDAI::Aggr*>::size_type currentItertor)
      {
        OdDAI::Aggr* aggrBase = nullptr;
        size_t  currentIndex = currentItertor;
        if (currentIndex > 0)
        {
          currentIndex += static_cast<size_t>(container.getLowerBound());
          container.createAggrInstanceByIndex(static_cast<int>(currentIndex) - 1, aggrBase);
        }
        else if (currentIndex == 0)
        {
          ODA_ASSERT(0 && "Attempt to set value before beginning position");
        }
        return aggrBase;
      }
    };

    template <class TType>
    class putCurrentMember<Array<TType>, TType>
    {
    public:
      static void Impl(Array<TType>& container, typename OdArray<TType>::size_type place, const TType& anItem)
      {
        size_t  placeIndex = place + static_cast<size_t>(container.getLowerBound());
        container.putByIndex(static_cast<int>(placeIndex), anItem);
      }
    };
  }
}


namespace OdDAI
{

  template<class TItem>
  inline AggrInstance* ArrayInstance<TItem>::getDefaultInstance()
  {
    return &AggrInstanceDefault<ArrayInstance>::instance();
  }


  template<class TItem>
  inline AggrInstance* ArrayInstance<TItem>::getDefaultInstance(const AggregationType* aggregationType)
  {
    if (aggregationType == nullptr)
    {
      return &AggrInstanceDefault<ArrayInstance>::instance();
    }

    return &TypedAggrInstanceDefault<ArrayInstance>::getDefaultInstance(const_cast<AggregationType*>(aggregationType));
  }

  namespace gcc_fix
  {
    DAI_EXPORT const OdDAI::AggrInstance* getCachedInstance(AggregationType* aggregationType);
    DAI_EXPORT const void setCachedInstance(AggregationType* aggregationType, OdDAI::AggrInstancePtr& newInstance);
  }

  template<class TItem>
  AggrInstance& TypedAggrInstanceDefault<ArrayInstance<TItem> >::getDefaultInstance(AggregationType* aggregationType)
  {
    static OdMutex sharedAccess;
    TD_AUTOLOCK(sharedAccess);

    const OdDAI::AggrInstance* cachedInstance = gcc_fix::getCachedInstance(aggregationType);
    if (cachedInstance)
    {
      return *const_cast<OdDAI::AggrInstance*>(cachedInstance);
    }

    OdDAI::AggrInstancePtr result(new TypedAggrInstanceDefault<ArrayInstance<TItem> >(aggregationType));
    gcc_fix::setCachedInstance(aggregationType, result);
    return *result;
  }

  namespace utils 
  {
    DAI_EXPORT int extractArrayBoundInternal(const OdDAI::AggregationType* aggrType, bool isLower);
  }

  template<typename TItem>
  inline int extractLowerBound(const AggrInstance* aggrInstance)
  {
    auto castedInstance = dynamic_cast<const TypedAggrInstanceDefault<ArrayInstance<TItem> >* > (aggrInstance);
    
    if (castedInstance == nullptr)
    {
      return orderedDefaultLowerBound;
    }

    return utils::extractArrayBoundInternal(castedInstance->aggregationType(), true);
  }

  template<typename TItem>
  inline int extractUpperBound(const AggrInstance* aggrInstance)
  {
    auto castedInstance = dynamic_cast<const TypedAggrInstanceDefault<ArrayInstance<TItem> >*> (aggrInstance);

    if (castedInstance == nullptr)
    {
      return orderedDefaultUpperBound;
    }

    return utils::extractArrayBoundInternal(castedInstance->aggregationType(), false);
  }
}


//DOM-IGNORE-END

#endif // _DAI_AGGR_H
