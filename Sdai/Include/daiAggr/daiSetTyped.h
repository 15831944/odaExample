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

#ifndef _DAI_SET_TYPED_H
#define _DAI_SET_TYPED_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"

#include "daiSet.h"
#include "daiTypedAggrItemManager.h"
#include "daiEnum.h"
#include "daiSelect.h"

namespace OdDAI 
{
  /** \details
  Template class for containers defined within a schema.
  */
  template<typename TItem, class SchemaItemTypeProvider>
  class DAI_EXPORT SetTyped
    : public Set<TItem>
  {
    friend class Duplicator;
  public:
    typedef TItem template_type;
    typedef TItem value_type;
    typedef Set<TItem> base_type;

  public:
    /**\details
    Creates a new Set aggregate.
    */
    SetTyped();

    SchemaItemTypeProvider* getItemSchemaTypeProvider();

    //DOM-IGNORE-BEGIN
  protected:
    SetTyped(AggrInstance* defaultInstance);

    template<typename TItemInst, class SchemaItemTypeProviderInst>
    friend class SetTypedInstance;
  };

  template <class SchemaItemTypeProvider>
  using SetEnum = SetTyped<OdDAI::Enum, SchemaItemTypeProvider>;

  template <class SchemaItemTypeProvider>
  using SetEnumPtr = OdSharedPtr<SetEnum<SchemaItemTypeProvider>>;

  typedef Set<OdDAI::Enum> OdEnumSet;
  typedef OdSharedPtr<OdEnumSet> OdEnumSetPtr;

  template <class SchemaItemTypeProvider>
  using SetSelect = SetTyped<OdDAI::Select, SchemaItemTypeProvider>;

  template <class SchemaItemTypeProvider>
  using SetSelectPtr = OdSharedPtr<SetSelect<SchemaItemTypeProvider>>;

}

namespace OdDAI
{

  template<typename TItem, class SchemaItemTypeProvider>
  class SetTypedInstance
    : public SetInstanceBase<TItem>
  {
    friend class AggrInstanceDefault<SetTypedInstance>;

  public:
    using container_type = SetTyped<TItem, SchemaItemTypeProvider>;

    bool Add(const TItem& elementToAdd) override
    {
      if (!checkItem(elementToAdd))
      {
        return false;
      }

      return SetInstanceBase<TItem>::Add(elementToAdd);
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

      SetInstanceBase<TItem>::setArray(newArray);
    }

    Aggr* cloneAndCreateAggrFrom() const override
    {
      auto clonedInstance = new SetTypedInstance();
      clonedInstance->copyFrom(this);
      return new SetTyped<TItem, SchemaItemTypeProvider>(clonedInstance);
    }

    static AggrInstance* getDefaultInstance()
    {
      return &AggrInstanceDefault<SetTypedInstance>::instance();
    }

    bool AddOdRxValue(const OdRxValue& value) override
    {
      TItem transitValue = Utils::getUnset<TItem>();
      return TypedAggrItemManager<TItem, SchemaItemTypeProvider>::translate(value, transitValue) && Add(transitValue);
    }

    bool RemoveOdRxValue(const OdRxValue& value) override
    {
      TItem transitValue = Utils::getUnset<TItem>();
      return TypedAggrItemManager<TItem, SchemaItemTypeProvider>::translate(value, transitValue) && this->Remove(transitValue);
    }

  protected:
    SetTypedInstance()
      : SetInstanceBase<TItem>()
    {
    }

    virtual bool checkItem(const TItem& elementToAdd)
    {
      return TypedAggrItemManager<TItem, SchemaItemTypeProvider>::checkType(elementToAdd);
    }

  private:

    virtual AggrInstance* createEmpty() const
    {
      return new SetTypedInstance();
    }

    virtual  AggrInstance* defaultInstance() const
    {
      return getDefaultInstance();
    }
  };
}

//DOM-IGNORE-BEGIN
/** A special class for internal use. */
namespace OdDAI
{
  template<typename TItem, class SchemaItemTypeProvider>
  SetTyped<TItem, SchemaItemTypeProvider>::SetTyped()
    : Set<TItem>(SetTypedInstance<TItem, SchemaItemTypeProvider>::getDefaultInstance())
  {
  }

  template<typename TItem, class SchemaItemTypeProvider>
  SetTyped<TItem, SchemaItemTypeProvider>::SetTyped(AggrInstance* defaultInstance)
    : Set<TItem>(defaultInstance)
  {
  }

  template<typename TItem, class SchemaItemTypeProvider>
  SchemaItemTypeProvider* SetTyped<TItem, SchemaItemTypeProvider>::getItemSchemaTypeProvider()
  {
    return  Aggr::instance<SetTypedInstance<TItem, SchemaItemTypeProvider>*>()->getItemSchemaTypeProvider();
  }

}

namespace OdDAI
{
  namespace IteratorImpl
  {
    template <typename TType, class SchemaItemTypeProvider>
    class removeCurrentMember<SetTyped<TType, SchemaItemTypeProvider>, TType>
    {
    public:
      static bool Impl(SetTyped<TType, SchemaItemTypeProvider>& container, typename OdArray<TType>::size_type place)
      {
        return removeCurrentMember<Set<TType>, TType>::Impl(container, place);
      }
    };
  }
}


#include "daiPrepareAggregateItem.h"

//DOM-IGNORE-END

#endif // _DAI_SET_TYPED_H
