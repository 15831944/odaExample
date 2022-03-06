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

#ifndef _DAI_BAG_TYPED_H
#define _DAI_BAG_TYPED_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"

#include "daiList.h"
#include "daiTypedAggrItemManager.h"

namespace OdDAI 
{

  /** \details
  Template class for containers defined within a schema.
  */
  template<typename TItem, class SchemaItemTypeProvider>
  class DAI_EXPORT BagTyped
    : public Bag<TItem>
  {
  public:
    typedef TItem template_type;
    typedef TItem value_type;
    typedef Bag<TItem> base_type;

  public:
    BagTyped();
    SchemaItemTypeProvider* getItemSchemaTypeProvider();

    //DOM-IGNORE-BEGIN
  protected:
    BagTyped(AggrInstance* defaultInstance);

    template<typename TItem, class SchemaItemTypeProvider>
    friend class BagTypedInstance;
  };
}


namespace OdDAI
{
  template<typename TItem, class SchemaItemTypeProvider>
  class BagTypedInstance
    : public BagInstance<TItem>
  {
    friend class AggrInstanceDefault<BagTypedInstance>;

  public:
    using container_type = BagTyped<TItem, SchemaItemTypeProvider>;

    bool Add(const TItem& elementToAdd) override
    {
      if (!checkItem(elementToAdd))
      {
        return false;
      }

      return BagInstance<TItem>::Add(elementToAdd);
    }

    Aggr* cloneAndCreateAggrFrom() const override
    {
      auto clonedInstance = new BagTypedInstance();
      clonedInstance->copyFrom(this);
      return new BagTyped<TItem, SchemaItemTypeProvider>(clonedInstance);
    }

    static AggrInstance* getDefaultInstance()
    {
      return &AggrInstanceDefault<TItem, BagTypedInstance, aggrTypeBag>::instance();
    }

    bool AddOdRxValue(const OdRxValue& value) override
    {
      TItem transitValue = Utils::getUnset<TItem>();
      return TypedAggrItemManager<TItem, SchemaItemTypeProvider>::translate(value, transitValue) && Add(transitValue);
    }

    bool RemoveOdRxValue(const OdRxValue& value) override
    {
      TItem transitValue = Utils::getUnset<TItem>();
      return TypedAggrItemManager<TItem, SchemaItemTypeProvider>::translate(value, transitValue) && Remove(transitValue);
    }

  protected:
    BagTypedInstance()
      : BagInstance<TItem>()
    {
    }

    virtual bool checkItem(const TItem& elementToAdd)
    {
      return TypedAggrItemManager<TItem, SchemaItemTypeProvider>::checkType(elementToAdd);
    }

  private:

    AggrInstance* createEmpty() const override
    {
      return new BagTypedInstance();
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
  BagTyped<TItem, SchemaItemTypeProvider>::BagTyped()
    : Bag<TItem>(BagTypedInstance<TItem, SchemaItemTypeProvider>::getDefaultInstance())
  {
  }

  template<typename TItem, class SchemaItemTypeProvider>
  BagTyped<TItem, SchemaItemTypeProvider>::BagTyped(AggrInstance* defaultInstance)
    : Bag<TItem>(defaultInstance)
  {
  }

  template<typename TItem, class SchemaItemTypeProvider>
  SchemaItemTypeProvider* BagTyped<TItem, SchemaItemTypeProvider>::getItemSchemaTypeProvider()
  {
    return  Aggr::instance<BagTypedInstance<TItem, SchemaItemTypeProvider>*>()->getItemSchemaTypeProvider();
  }
}

//DOM-IGNORE-END

#endif // _DAI_BAG_TYPED_H
