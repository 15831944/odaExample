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

#ifndef _DAI_BASE2D_VALUE_TYPE_IMPL_H_
#define _DAI_BASE2D_VALUE_TYPE_IMPL_H_

#include "RxValue.h"
#include "daiAggr/daiArray.h"
#include "daiAggr/daiAggrUtils.h"

namespace OdDAI
{
  template<template<class> typename ValueType, typename OdArrayValueType>
  class Base2dPtrValueTypePOD
    : public OdRxValueTypePOD<ValueType<OdDAI::Aggr*>*>
  {
  public:

    Base2dPtrValueTypePOD(const OdChar* name, OdRxMemberCollectionConstructorPtr memberConstruct = NULL, void* userData = NULL)
      : OdRxValueTypePOD<ValueType<OdDAI::Aggr*>*>(name, memberConstruct, userData)
    {
    };

    bool subToValueType(const OdRxValueType& vt, const OdRxValue& instance, OdRxValue& subVal) const override
    {
      if (vt == OdRxValueType::Desc<OdDAI::Aggr*>::value())
      {
        OdDAI::Aggr* pAggrBase = *rxvalue_cast<ValueType<OdDAI::Aggr*>*>(&instance);
        subVal = pAggrBase;
        return true;
      }
      else if (vt == OdRxValueType::Desc<OdArrayValueType>::value())
      {
        OdDAI::Aggr* aggrFrom = *rxvalue_cast<ValueType<OdDAI::Aggr*>*>(&instance);
        subVal = OdArrayValueType();
        OdArrayValueType* arrayTo = rxvalue_cast<OdArrayValueType>(&subVal);
        return aggrFrom->getArrayValues<Aggr*, OdArrayValueType::value_type>(*arrayTo);
      }
      else if (vt == OdRxValueType::Desc<ValueType<OdDAI::Aggr*>>::value())
      {
        ValueType<OdDAI::Aggr*>* pAggrBase = *rxvalue_cast<ValueType<OdDAI::Aggr*>*>(&instance);
        subVal = *pAggrBase;
        return true;
      }

      return false;
    };

    bool subEqualTo(const void* a, const void* b) const override
    {
      const OdDAI::Aggr* aggrA = *reinterpret_cast<const OdDAI::Aggr* const*>(a);
      const OdDAI::Aggr* aggrB = *reinterpret_cast<const OdDAI::Aggr* const*>(b);

      return *aggrA == *aggrB;
    }

    virtual bool isAggregate() const
    {
      return true;
    }
  };

  template<typename OdArrayValueType>
  class Base2dValueTypePOD
    : public OdRxValueTypePOD<OdArrayValueType>
  {
  public:

    Base2dValueTypePOD(const OdChar* name, OdRxMemberCollectionConstructorPtr memberConstruct = NULL, void* userData = NULL)
      : OdRxValueTypePOD<OdArrayValueType>(name, memberConstruct, userData)
    {
    }

    virtual bool subFromValueType(const OdRxValue& from, OdRxValue& instance) const 
    {
      if ((from.type() == OdRxValueType::Desc<OdDAI::Array<Aggr*> >::value()) || 
          (from.type() == OdRxValueType::Desc<OdDAI::List<Aggr*> >::value()))
      {
        const OdDAI::Aggr* aggrFrom = *rxvalue_cast<OdDAI::Aggr*>(&from);
        //OdArrayValueType* arrayTo = *rxvalue_cast<OdArrayValueType*>(&instance);
        //return aggrFrom->getArrayValues<OdDAI::Aggr*, OdArrayValueType::value_type>(*arrayTo);;

      }
      else if (from.type() == OdRxValueType::Desc<OdDAI::Array<OdDAI::Aggr*>* >::value())
      {
        const OdDAI::Array<OdDAI::Aggr*>* aggrFrom = *rxvalue_cast<OdDAI::Array<OdDAI::Aggr*>*>(&from);
        OdArrayValueType arrayTo;
        if (!aggrFrom->getArrayValues<OdDAI::Aggr*, OdArrayValueType::value_type>(arrayTo))
        {
          return false;
        }

        instance = arrayTo;
        return true;
      }
      else if (from.type() == OdRxValueType::Desc<OdDAI::List<OdDAI::Aggr*>* >::value())
      {
        const OdDAI::List<OdDAI::Aggr*>* aggrFrom = *rxvalue_cast<OdDAI::List<OdDAI::Aggr*>*>(&from);
        OdArrayValueType arrayTo;
        
        if (!aggrFrom->getArrayValues<OdDAI::Aggr*, OdArrayValueType::value_type>(arrayTo))
        {
          return false;
        }

        instance = arrayTo;
        return true;
      }

      return false;
    }

    virtual bool subToValueType(const OdRxValueType& vt, const OdRxValue& instance, OdRxValue& subVal) const ODRX_OVERRIDE
    {
      return false;
    }


    virtual bool subEqualTo(const void* a, const void* b) const ODRX_OVERRIDE
    {
      const OdDAI::Aggr* aggrA = reinterpret_cast<const OdDAI::Aggr*>(a);
      const OdDAI::Aggr* aggrB = reinterpret_cast<const OdDAI::Aggr*>(b);

      return *aggrA == *aggrB;
    }

  };
}

#endif // _DAI_ARRAY_VALUE_TYPE_H_
