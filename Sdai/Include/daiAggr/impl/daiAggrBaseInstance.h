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

#ifndef _DAI_AGGR_INSTANCE_H_
#define _DAI_AGGR_INSTANCE_H_


#include "daiAggr/daiAggr.h"

//DOM-IGNORE-BEGIN

namespace OdDAI
{
  class DAI_EXPORT OrderedLogic
  {
  public:
    virtual OdRxValue getOdRxValueByIndex(int  index) const = 0; 
    virtual void putOdRxValueByIndex(int  index, const OdRxValue& element) = 0;
    virtual void insertOdRxValueByIndex(int  index, const OdRxValue& element) = 0;
    virtual bool removeOdRxValueByIndex(int index) = 0;

    virtual int getValueBoundByIndex(int index) = 0; 
    virtual void createAggrInstanceByIndex(int index, Aggr*& newAggr) = 0;
  };

  class DAI_EXPORT UnorderedLogic
  {
  public:
    virtual bool AddOdRxValue(const OdRxValue& element) = 0;
    virtual bool RemoveOdRxValue(const OdRxValue& anItem) = 0;
  };

  class DAI_EXPORT AggrInstance
  {
  public:
    virtual ~AggrInstance() {};

    virtual IteratorPtr createIterator(Aggr& aggrHolder) = 0;
    virtual ConstIteratorPtr createConstIterator(const Aggr& aggrHolder) const = 0;
    virtual const OdRxValueType& type() const = 0;

    virtual void copyFrom(const AggrInstance* from) = 0;
    virtual bool compareTo(const AggrInstance* to) const= 0;

    virtual Aggr* cloneAndCreateAggrFrom(bool withItems = true) const = 0;

    virtual int getMemberCount() const = 0;
    virtual int getLowerBound() const = 0;
    virtual int getUpperBound() const = 0;

    virtual bool isMember(const OdRxValue& itemToCheck) const = 0;

    virtual OrderedLogic* orderedLogic() = 0;
    virtual UnorderedLogic* unorderedLogic() = 0;

    virtual AggrType aggrType() const = 0;

    static AggrInstance*  create(const AggrInstance* createFrom);
    static bool remove(AggrInstance*& instanceToRemove, bool resetToDefault = true);

    static bool isDefault(const AggrInstance* aggrToTest);
    static bool isTheSameInstanceType(const AggrInstance* left, const AggrInstance* right);
  
  private:
    virtual AggrInstance* createEmpty() const  = 0;
    
    void  freeItself()
    {// can not use smartptr(to avoid increase size of AggrInstance in Aggr). 
      if (!isDefault(this))
      {
        delete this;
      }
    }
    
    virtual AggrInstance* defaultInstance() const = 0;

  private:
  };
}


namespace OdDAI
{
  template<class TWorkInstance>
  class AggrInstanceDefaultBase
    : public AggrInstance
    , public OrderedLogic
    , public UnorderedLogic
  {
  public:
    virtual IteratorPtr createIterator(Aggr& aggrHolder) ODRX_OVERRIDE { return NULL; }
    virtual ConstIteratorPtr createConstIterator(const Aggr& aggrHolder) const ODRX_OVERRIDE { return NULL; }
    virtual const OdRxValueType& type() const ODRX_OVERRIDE { return OdRxValueType::Desc<typename TWorkInstance::item_type>::value(); }
    virtual AggrType aggrType() const ODRX_OVERRIDE { return TWorkInstance::type_aggr; }

    void copyFrom(const AggrInstance*) override {}
    bool compareTo(const AggrInstance* to) const override { return to == this; }
    Aggr* cloneAndCreateAggrFrom(bool /*withItems*/) const override { return new typename TWorkInstance::container_type(); }

    virtual OrderedLogic* orderedLogic() { return this; }
    virtual UnorderedLogic* unorderedLogic() { return this; }

  protected:
    AggrInstanceDefaultBase() {}
    AggrInstanceDefaultBase(const AggrInstanceDefaultBase&) {}
    virtual ~AggrInstanceDefaultBase() {}

    AggrInstanceDefaultBase& operator=(const AggrInstanceDefaultBase&) { return *this; }

    virtual OdRxValue getOdRxValueByIndex(int  /*index*/) const { return OdRxValue(); }
    virtual void putOdRxValueByIndex(int  /*index*/, const OdRxValue& /*element*/) {}
    virtual void insertOdRxValueByIndex(int  /*index*/, const OdRxValue& /*element*/) {}
    virtual bool removeOdRxValueByIndex(int /*index*/) { return false; }

    virtual int getValueBoundByIndex(int /*index*/) { return 0; }
    virtual void createAggrInstanceByIndex(int /*index*/, Aggr*& /*newAggr*/) {}

    virtual bool AddOdRxValue(const OdRxValue& /*element*/) { return false; }
    virtual bool RemoveOdRxValue(const OdRxValue& /*anItem*/) { return false; }

    virtual int getMemberCount() const { return 0; }
    virtual int getLowerBound() const { return 0; }
    virtual int getUpperBound() const { return 0; }

    virtual bool isMember(const OdRxValue& itemToCheck) const { return false; }
  };

  template<class TWorkInstance>
  class AggrInstanceDefault
    : public AggrInstanceDefaultBase<TWorkInstance>
  {
  public:
    static AggrInstance& instance()
    {
      static AggrInstanceDefault<TWorkInstance> aggr_instance;
      return aggr_instance;
    }

  protected:
    AggrInstanceDefault() {}
    AggrInstanceDefault(const AggrInstanceDefault&) {}
    virtual ~AggrInstanceDefault() {}

    virtual AggrInstance* createEmpty() const  ODRX_OVERRIDE { return new TWorkInstance(); }
    virtual AggrInstance* defaultInstance() const  ODRX_OVERRIDE { return &instance(); }
  };


  template<class TWorkInstance>
  class TypedAggrInstanceDefault
    : public AggrInstanceDefaultBase<TWorkInstance>
  {
  public:
    TypedAggrInstanceDefault() {}

    virtual ~TypedAggrInstanceDefault() {}

    virtual AggrInstance* defaultInstance() const  ODRX_OVERRIDE { return this; }
    virtual AggrInstance* createEmpty() const  ODRX_OVERRIDE 
    {
      auto newInstance = new TWorkInstance(this);
      return newInstance;
    }
  };

} // namespace
//DOM-IGNORE-END

#endif // _DAI_AGGR_INSTANCE_H_
