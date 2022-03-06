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

#ifndef _DAI_AGGR_INSTANCE_COMMON_H
#define _DAI_AGGR_INSTANCE_COMMON_H

#include "OdPlatformSettings.h"
#include "OdaCommon.h"

#include "daiBuildOptions.h"
#include "daiAggr/daiAggr.h"
#include "daiAggr/daiIterator.h"
#include "daiAggrBaseInstance.h"
#include "daiAggr/daiCollectionWrapper.h"

#include "daiUtils/daiUnset.h"
#include "daiUtils/daiCustomCompare.h"

template <typename T>
struct has_value_type
{
private:
  template <typename T1>
  static typename T1::value_type test(int);

  template <typename>
  static void test(...);

public:
  enum { value = !std::is_void<decltype(test<T>(0))>::value };
};


namespace OdDAI
{
  template<typename TItem>
  class DAI_EXPORT AggrInstanceCommonBase
    : public AggrInstance
  {
  public:
    using item_type = TItem;
    using value_type = TItem;

    virtual const OdRxValueType& type() const ODRX_OVERRIDE
    {
      return OdRxValueType::Desc<TItem>::value();
    }

    virtual int getMemberCount() const ODRX_OVERRIDE
    {
      return static_cast<unsigned int>(m_itemCollection.size());
    }

    virtual bool isMember(const OdRxValue& itemToCheck) const ODRX_OVERRIDE
    {
      TItem transitValue;

      if (itemToCheck >> transitValue == false)
      {
        return false;
      }

      return isMember(transitValue);
    }

    virtual bool isMember(const TItem& itemToCheck) const
    {
      return m_itemCollection.isContains(itemToCheck);
    }

    void copyFrom(const AggrInstance* from) override 
    {
      if (!from || from == this)
      {
        return;
      }

      const AggrInstanceCommonBase<TItem>* other = dynamic_cast<const AggrInstanceCommonBase<TItem>*>(from);
      if (!other)
      {
        return;
      }

      setArray(other->getArray());
    }

    virtual TItem   generateAggrItem() const
    {
      return Utils::getUnset<TItem>();
    }

    bool compareTo(const AggrInstance* to) const override
    {
      if (to == this) 
      { 
        return true; 
      }

      const AggrInstanceCommonBase<TItem>* other = dynamic_cast<const AggrInstanceCommonBase<TItem>*>(to);
      return other && OdDAI::compare::isEqual<TItem>(getArray(), other->getArray());
    }

    const OdArray<TItem>& getArray() const
    {
      return m_itemCollection.getCollection();
    }

    virtual void checkArrayBeforeSet(const OdArray<TItem>& newArray){}

    virtual void setArray(const OdArray<TItem>& newArray)
    {
      checkArrayBeforeSet(newArray);
      m_itemCollection.setCollection(newArray);
    }


    virtual bool read(IAggrReader<TItem>& aggrReader);
    bool write(IAggrWriter<TItem>& aggrWriter);

  protected:
    AggrInstanceCommonBase()
    {
    }

  protected:
    CollectionWrapper<TItem>   m_itemCollection;
  };
}

namespace OdDAI
{
  template<typename TItem>
  class DAI_EXPORT AggrInstanceCommon
    : public AggrInstanceCommonBase<TItem>
  {
  public:
    template<class TOtherItem>
    bool copyToArray(OdArray<TOtherItem>& copyTo) const
    {
      copyTo = this->m_itemCollection.getCollection();
      return true;
    }

    template<class TOtherItem>
    bool copyFromArray(OdArray<TOtherItem>& copyFrom) 
    {
      this->m_itemCollection.setCollection(copyFrom);
      return true;
    }

  protected:
    AggrInstanceCommon()
    {
    }
  };
}


template<class ValueToPut, bool isAggrValue = has_value_type<ValueToPut>::value>
class TypeDetect;

template<class ValueToPut>
class TypeDetect<ValueToPut, false>
{
public:
  using value_type = ValueToPut;
};

template<class ValueToPut>
class TypeDetect<ValueToPut, true>
{
public:
  using value_type = OdDAI::Aggr*;
};

namespace OdDAI
{
  template<>
  class DAI_EXPORT AggrInstanceCommon<Aggr*>
    : public AggrInstanceCommonBase<Aggr*>
  {
  public:
    virtual void setArray(const OdArray<Aggr*>& arrayFrom);

    template<class TOtherItem>
    bool copyToArray(OdArray<TOtherItem>& copyTo) const
    {
      copyTo.reserve(m_itemCollection.size());
      TOtherItem templateItem;

      for (auto& itemFrom : m_itemCollection.getCollection())
      {
        copyTo.push_back(templateItem);
        TOtherItem& lastOdArray = copyTo.last();

        if (!itemFrom->getArrayValues<typename TypeDetect<typename TOtherItem::value_type>::value_type, typename TOtherItem::value_type>(lastOdArray))
        {
          return false;
        }
      }

      return true;
    }

    template<class TOtherItem>
    bool copyFromArray(OdArray<TOtherItem>& copyFrom) 
    {
      m_itemCollection.clear();

      for (auto& copyItem : copyFrom)
      {
        auto newAggrItem = generateAggrItem();
        newAggrItem->setArrayValues<typename  TypeDetect<typename TOtherItem::value_type>::value_type, typename TOtherItem::value_type>(copyItem);
        m_itemCollection.pushBackValue(newAggrItem);
      }
      
      return true;
    }

  protected:
    AggrInstanceCommon(){}
  };
}


namespace  OdDAI
{

  template<typename TItem>
  inline bool AggrInstanceCommonBase<TItem>::read(IAggrReader<TItem>& aggrReader)
  {
    if (!aggrReader.skipUntil('('))
      throw OdError(eSyntaxError);

    if (aggrReader.skipUntilRet(')'))
      return true; // Empty aggregate, but not unset!
    
    {
      TItem val = generateAggrItem();

      if (eOk != aggrReader.rdPrimitive(val, false))
      {
        itemCleaner(val);
        throw OdError(eSyntaxError);
      }

      m_itemCollection.pushBackValue(val);
    }

    if (aggrReader.skipUntilRet(')'))
      return true;

    while (true)
    {
      TItem val = generateAggrItem();
      if (aggrReader.rdPrimitive(val, true) != eOk)
      {
        itemCleaner(val);
        break;
      }
      
      m_itemCollection.pushBackValue(val);

      if (aggrReader.skipUntilRet(')'))
        break;      
    }

    return true;
  }

  namespace{

    template<class TElement>
    bool shouldBeSkippedDuringStreamWrite(const TElement& element)
    {
      return false;
    }

    template<>
    bool shouldBeSkippedDuringStreamWrite<OdDAIObjectId>(const OdDAIObjectId& element)
    {
      return element.isErased();
    }
  }

  template<typename TItem>
  bool AggrInstanceCommonBase<TItem>::write(IAggrWriter<TItem>& aggrWriter)
  {
    aggrWriter.wrChar('(');

    char  delimeter = 0;
    
    const auto& collectionToWrite = m_itemCollection.getCollection();
    for (const auto& valueToWrite : collectionToWrite)
    {
      if (shouldBeSkippedDuringStreamWrite(valueToWrite))
      {
        continue;
      }

      if (delimeter)
      {
        aggrWriter.wrChar(delimeter);
      }
      else
      {
        delimeter = ',';
      }

      aggrWriter.wrPrimitive(*const_cast<TItem*>(&valueToWrite));
    }

    aggrWriter.wrChar(')');

    return true;
  }
}

//DOM-IGNORE-END

#endif // _DAI_AGGR_H
