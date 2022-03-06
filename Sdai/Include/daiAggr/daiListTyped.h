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

#ifndef _DAI_LIST_TYPED_H
#define _DAI_LIST_TYPED_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"

#include "daiList.h"
#include "daiTypedAggrItemManager.h"
#include "daiEnum.h"
#include "daiSelect.h"


namespace OdDAI
{
  /** \details
  Template class for containers defined within a schema.
  */
  template<typename TItem, class SchemaItemTypeProvider>
  class DAI_EXPORT ListTyped
    : public List<TItem>
  {
  public:
    typedef TItem template_type;
    typedef TItem value_type;
    typedef List<TItem> base_type;

  public:
    /**\details
    Creates a new ListTyped aggregate.
    */
    ListTyped();
    SchemaItemTypeProvider* getItemSchemaTypeProvider();

//DOM-IGNORE-BEGIN
  protected:
    ListTyped(AggrInstance* defaultInstance);

  protected:
    template<typename TItemInst, class SchemaItemTypeProviderInst>
    friend class ListTypedInstance;
  };

  template <class SchemaItemTypeProvider>
  using ListEnum = ListTyped<OdDAI::Enum, SchemaItemTypeProvider>;

  template <class SchemaItemTypeProvider>
  using ListEnumPtr = OdSharedPtr<ListEnum<SchemaItemTypeProvider>>;

  typedef List<OdDAI::Enum> OdEnumList;
  typedef OdSharedPtr<OdEnumList> OdEnumListPtr;


  template <class SchemaItemTypeProvider>
  using ListSelect = ListTyped<OdDAI::Select, SchemaItemTypeProvider>;

  template <class SchemaItemTypeProvider>
  using ListSelectPtr = OdSharedPtr<ListSelect<SchemaItemTypeProvider>>;

  typedef List<OdDAI::Select> OdSelectList;
  typedef OdSharedPtr<OdSelectList> OdSelectListPtr;
}


namespace OdDAI
{
  template<typename TItem, class SchemaItemTypeProvider>
  class ListTypedInstance
    : public ListInstanceBase<TItem>
  {
    friend class AggrInstanceDefault<ListTypedInstance>;

  public:
    using container_type = ListTyped<TItem, SchemaItemTypeProvider>;

    virtual IteratorPtr createIterator(Aggr& aggrHolder) ODRX_OVERRIDE
    {
      IteratorPtr pIter = new OdDAI::IteratorCollection<OdDAI::ListTyped<TItem, SchemaItemTypeProvider>, TItem>(aggrHolder);
      return pIter;
    }

    void addByIndex(int  indexToAdd, const TItem& elementToAdd) override
    {
      if (!checkItem(elementToAdd))
      {
        return;
      }

      ListInstanceBase::addByIndex(indexToAdd, elementToAdd);
    }

    void setArray(const OdArray<TItem>& newArray)  override
    {
      for (auto& item : newArray)
      {
        if (!checkItem(item))
        {
          return;
        }
      }

      ListInstanceBase::setArray(newArray);
    }

    void putOdRxValueByIndex(int index, const OdRxValue& value) override
    {
      TItem transitValue = Utils::getUnset<TItem>();
      if (TypedAggrItemManager<TItem, SchemaItemTypeProvider>::translate(value, transitValue))
      {
        ListInstanceBase::putByIndex(index, transitValue);
      }
    }

    void insertOdRxValueByIndex(int  index, const OdRxValue& value) override
    {
      TItem transitValue = Utils::getUnset<TItem>();
      if (TypedAggrItemManager<TItem, SchemaItemTypeProvider>::translate(value, transitValue))
      {
        ListInstanceBase::addByIndex(index, transitValue);
      }
    }

    Aggr* cloneAndCreateAggrFrom() const override
    {
      auto clonedInstance = new ListTypedInstance();
      clonedInstance->copyFrom(this);
      return new ListTyped<TItem, SchemaItemTypeProvider>(clonedInstance);
    }

    static AggrInstance* getDefaultInstance()
    {
      return &AggrInstanceDefault<ListTypedInstance>::instance();
    }

  protected:
    ListTypedInstance()
      : ListInstanceBase()
    {
    }

    virtual bool checkItem(const TItem& elementToAdd)
    {
      return TypedAggrItemManager<TItem, SchemaItemTypeProvider>::checkType(elementToAdd);
    }

  private:

    AggrInstance* createEmpty() const override
    {
      return new ListTypedInstance();
    }

    AggrInstance* defaultInstance() const override
    {
      return getDefaultInstance();
    }
  };
}

/** A special class for internal use. */
namespace OdDAI
{
  template<typename TItem, class SchemaItemTypeProvider>
  ListTyped<TItem, SchemaItemTypeProvider>::ListTyped()
    : List<TItem>(ListTypedInstance<TItem, SchemaItemTypeProvider>::getDefaultInstance())
  {
  }

  template<typename TItem, class SchemaItemTypeProvider>
  ListTyped<TItem, SchemaItemTypeProvider>::ListTyped(AggrInstance* defaultInstance)
    : List<TItem>(defaultInstance)
  {
  }

  template<typename TItem, class SchemaItemTypeProvider>
  SchemaItemTypeProvider* ListTyped<TItem, SchemaItemTypeProvider>::getItemSchemaTypeProvider()
  {
    return  Aggr::instance<ListTypedInstance<TItem, SchemaItemTypeProvider>*>()->getItemSchemaTypeProvider();
  }

}


namespace OdDAI
{
  namespace IteratorImpl
  {

    template <class TType, class SchemaItemTypeProvider>
    class putCurrentMember<ListTyped<TType, SchemaItemTypeProvider>, TType>
    {
    public:
      static void Impl(ListTyped<TType, SchemaItemTypeProvider>& container, typename OdArray<TType>::size_type place, const TType& anItem)
      {
        putCurrentMember<List<TType>, TType>::Impl(container, place, anItem);
      }
    };


    template <class TType, class SchemaItemTypeProvider>
    class addBeforeCurrentMember<ListTyped<TType, SchemaItemTypeProvider>, TType>
    {
    public:
      static void Impl(ListTyped<TType, SchemaItemTypeProvider>& container, typename OdArray<TType>::size_type place, const TType& anItem)
      {
        addBeforeCurrentMember<List<TType>, TType>::Impl(container, place, anItem);
      }
    };

    template <class TType, class SchemaItemTypeProvider>
    class addAfterCurrentMember<ListTyped<TType, SchemaItemTypeProvider>, TType>
    {
    public:
      static void Impl(ListTyped<TType, SchemaItemTypeProvider>& container, typename OdArray<TType>::size_type place, const TType& anItem)
      {
        addAfterCurrentMember<List<TType>, TType>::Impl(container, place, anItem);
      }
    };

    template <class TType, class SchemaItemTypeProvider>
    class removeCurrentMember<ListTyped<TType, SchemaItemTypeProvider>, TType>
    {
    public:
      static bool Impl(ListTyped<TType, SchemaItemTypeProvider>& container, typename OdArray<TType>::size_type place)
      {
        return removeCurrentMember<List<TType>, TType>::Impl(container, place);
      }
    };
  }
}

#include "daiPrepareAggregateItem.h"

//DOM-IGNORE-END

#endif // _DAI_LIST_TYPED_H
