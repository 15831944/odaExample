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

#ifndef _DAI_SET_VALUE_TYPE_IMPL_H_
#define _DAI_SET_VALUE_TYPE_IMPL_H_

#include "RxValue.h"
#include "daiAggr/daiSet.h"
#include "daiAggr/daiAggrUtils.h"


namespace OdDAI
{
  /** \details
  Template class represents value type for pointer to aggregate.
  */
  template<typename ValueType, typename SubValueType>
  class SetPtrValueTypePOD : public OdRxValueTypePOD<ValueType*>
  {
  public:

    SetPtrValueTypePOD(const OdChar* name, OdRxMemberCollectionConstructorPtr memberConstruct = NULL, void* userData = NULL)
      : OdRxValueTypePOD<ValueType*>(name, memberConstruct, userData)
    {
    };

    virtual bool subToValueType(const OdRxValueType& vt, const OdRxValue& instance, OdRxValue& subVal) const ODRX_OVERRIDE
    {
      if (vt == OdRxValueType::Desc<OdArray<SubValueType> >::value())
      {
        ValueType* inst = *rxvalue_cast<ValueType*>(&instance);
        if (!inst->isNil())
        {
          return OdDAI::Utils::copyTo<SubValueType, OdRxValue>(*inst, subVal);
        }
        else
        {
          static const OdArray<SubValueType> emptyValue;
          subVal = OdRxValue(emptyValue);
        }
        return true;
      }
      if (vt == OdRxValueType::Desc<OdArray<OdRxValue> >::value())
      {
        ValueType*   inst = *rxvalue_cast<ValueType*>(&instance);
        if (!inst->isNil())
        {
          OdArray<OdRxValue>  selectsArray;
          OdDAI::copyFromAggrToRxValueArray(*inst, selectsArray);
          subVal = selectsArray;
        }
        return true;
      }
      if (vt == OdRxValueType::Desc<OdDAI::Aggr*>::value())
      {
        OdDAI::Aggr* pAggrBase = *rxvalue_cast<ValueType*>(&instance);
        subVal = pAggrBase;
        return true;
      }
      return false;
    };

    virtual bool subFromValueType(const OdRxValue& from, OdRxValue& instance) const
    {
      if (from.type() == OdRxValueType::Desc<OdArray<SubValueType> >::value())
      {
        return true;
      }
      return false;
    };

    virtual bool subEqualTo(const void* a, const void* b) const ODRX_OVERRIDE
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


  /** \details
  Template class represents value type for aggregate.
  */
  template<typename ValueType, typename SubValueType>
  class SetValueTypePOD : public OdRxValueTypePOD<ValueType>
  {
  public:

    SetValueTypePOD(const OdChar* name, OdRxMemberCollectionConstructorPtr memberConstruct = NULL, void* userData = NULL)
      : OdRxValueTypePOD<ValueType>(name, memberConstruct, userData)
    {
    };

    virtual bool subToValueType(const OdRxValueType& vt, const OdRxValue& instance, OdRxValue& subVal) const ODRX_OVERRIDE
    {
      if (vt == OdRxValueType::Desc< OdArray< SubValueType > >::value())
      {
        const ValueType* inst = rxvalue_cast<ValueType>(&instance);

        if (!inst->isNil())
        {
          return OdDAI::Utils::copyTo<SubValueType>(*inst, subVal);
        }
        else
        {
          static const OdArray<SubValueType> emptyValue;
          subVal = OdRxValue(emptyValue);
        }

        return true;
      }

      if (vt == OdRxValueType::Desc<OdArray<OdRxValue> >::value())
      {
        const ValueType*  inst = rxvalue_cast<ValueType>(&instance);
        if (!inst->isNil())
        {
          OdArray<OdRxValue>  selectsArray;
          OdDAI::copyFromAggrToRxValueArray(*inst, selectsArray);
          subVal = selectsArray;
        }
        return true;
      }


      return false;
    };

    virtual bool subFromValueType(const OdRxValue& from, OdRxValue& instance) const
    {
      if (from.type() == OdRxValueType::Desc< OdArray< SubValueType > >::value())
      {
        const OdArray<SubValueType>* pArr = rxvalue_cast<OdArray< SubValueType > >(&from);
        if (pArr)
        {
          ODA_ASSERT(0 && "Copy from pArr.");

          //ValueType aggr;
          //aggr = *pArr;
          //instance = aggr;
          return true;
        }
      }
      return false;
    };


    virtual bool subEqualTo(const void* a, const void* b) const ODRX_OVERRIDE
    {
      return false;
    }

  };
}


#endif // _DAI_SET_VALUE_TYPE_IMPL_H_
