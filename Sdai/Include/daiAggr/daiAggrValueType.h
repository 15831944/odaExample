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

#ifndef _DAI_AGGR_VALUE_TYPE_H_
#define _DAI_AGGR_VALUE_TYPE_H_
#if 0
namespace OdDAI {
  class Aggr;
  template<class T>
  class Aggr;
}

#define DAI_DECLARE_VT_AGGR(type_name, exp_attr)\
template<> struct OdRxValueType::Desc<type_name>\
{\
  exp_attr static const OdRxValueType& value() throw();\
  exp_attr static void del();\
};\
template<> OdRxValue::OdRxValue(type_name const &) throw();

DAI_DECLARE_VT_AGGR(OdDAI::Aggr*, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::Aggr<bool>*, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::Aggr<int>*, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::Aggr<double>*, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::Aggr<OdDAIObjectId>*, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::Aggr<OdAnsiString>*, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::Aggr<OdDAI::Aggr<OdDAIObjectId> >*, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::Aggr<OdDAI::Aggr<int> >*, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::Aggr<OdDAI::Aggr<double> >*, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::Aggr<OdDAIObjectId>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::Aggr<int>, DAI_EXPORT);
DAI_DECLARE_VT_AGGR(OdDAI::Aggr<double>, DAI_EXPORT);

/** \details
Template class represents value type for pointer to aggregate.
*/
template<typename ValueType, typename SubValueType>
class AggrPtrValueTypePOD : public OdRxValueTypePOD<ValueType>
{
public:

  AggrPtrValueTypePOD(const OdChar* name, OdRxMemberCollectionConstructorPtr memberConstruct = NULL, void* userData = NULL)
    : OdRxValueTypePOD<ValueType>(name, memberConstruct, userData) {};

  virtual bool subToValueType(const OdRxValueType &vt, const OdRxValue &instance, OdRxValue &subVal) const ODRX_OVERRIDE
  {
    if (vt == OdRxValueType::Desc< OdArray< SubValueType > >::value())
    {
      ValueType inst = *rxvalue_cast<ValueType>(&instance);
      subVal = inst->getArray();
      return true;
    }
    if (vt == OdRxValueType::Desc<OdDAI::Aggr*>::value())
    {
      OdDAI::Aggr* pAggrBase = *rxvalue_cast<ValueType>(&instance);
      subVal = pAggrBase;
      return true;
    }
    return false;
  };

  virtual bool subFromValueType(const OdRxValue& from, OdRxValue &instance) const
  {
    if (from.type() == OdRxValueType::Desc< OdArray< SubValueType > >::value())
    {
      
      return true;
    }
    return false;
  };

  /*virtual const OdAnsiString subTypePath(const OdRxValue& instance) const
  {
    return "";
    const OdDAI::Select *pSel = rxvalue_cast<ValueType>(&instance);
    if (!pSel)
      throw OdError(L"Can not convert instance to value type");
    return pSel->underlyingTypeName();
  };*/

  virtual bool subEqualTo(const void* a, const void* b) const ODRX_OVERRIDE
  {
    const OdDAI::Aggr *aggrA = *reinterpret_cast<const OdDAI::Aggr* const *>(a);
    const OdDAI::Aggr *aggrB = *reinterpret_cast<const OdDAI::Aggr* const *>(b);
    if (aggrA == aggrB)
      return true;
    ODA_ASSERT_ONCE(0 && "RxValue with nested Aggr compare not implemented yet."); // TODO
    return false;
  }

};

/** \details
Template class represents value type for pointer to 2d aggregate.
*/
template<typename ValueType, typename SubValueType>
class Aggr2DPtrValueTypePOD : public OdRxValueTypePOD<ValueType>
{
public:

  typedef const OdArray<OdDAI::Aggr<SubValueType> > array_type;

  Aggr2DPtrValueTypePOD(const OdChar* name, OdRxMemberCollectionConstructorPtr memberConstruct = NULL, void* userData = NULL)
    : OdRxValueTypePOD<ValueType>(name, memberConstruct, userData) {};

  virtual bool subToValueType(const OdRxValueType &vt, const OdRxValue &instance, OdRxValue &subVal) const ODRX_OVERRIDE
  {
    if (vt == OdRxValueType::Desc< OdArray< OdArray< SubValueType > > >::value())
    {
      ValueType inst = *rxvalue_cast<ValueType>(&instance);
      array_type &arr = inst->getArray();

      OdArray<OdArray<SubValueType> > res(arr.size());

      for (typename array_type::const_iterator it = arr.begin(), end = arr.end(); it < end; ++it)
      {
        res.push_back(it->getArray());
      }

      subVal = res;
      return true;
    }
    if (vt == OdRxValueType::Desc<OdDAI::Aggr*>::value())
    {
      OdDAI::Aggr* pAggrBase = *rxvalue_cast<ValueType>(&instance);
      subVal = pAggrBase;
      return true;
    }
    return false;
  };

  virtual bool subFromValueType(const OdRxValue& from, OdRxValue &instance) const
  {
    /*if (from.type() == OdRxValueType::Desc< OdArray< OdArray< SubValueType > > >::value())
    {

      return true;
    }*/
    return false;
  };

  /*virtual const OdAnsiString subTypePath(const OdRxValue& instance) const
  {
  return "";
  const OdDAI::Select *pSel = rxvalue_cast<ValueType>(&instance);
  if (!pSel)
  throw OdError(L"Can not convert instance to value type");
  return pSel->underlyingTypeName();
  };*/

  virtual bool subEqualTo(const void* a, const void* b) const ODRX_OVERRIDE
  {
    return false;
    /*const OdDAI::Select *aSel = reinterpret_cast<const ValueType*>(a);
    const OdDAI::Select *bSel = reinterpret_cast<const ValueType*>(b);
    return (*aSel == *bSel);*/
  }

};

/** \details
Template class represents value type for aggregate.
*/
template<typename ValueType, typename SubValueType>
class AggrValueTypePOD : public OdRxValueTypePOD<ValueType>
{
public:

  AggrValueTypePOD(const OdChar* name, OdRxMemberCollectionConstructorPtr memberConstruct = NULL, void* userData = NULL)
    : OdRxValueTypePOD<ValueType>(name, memberConstruct, userData) {};

  virtual bool subToValueType(const OdRxValueType &vt, const OdRxValue &instance, OdRxValue &subVal) const ODRX_OVERRIDE
  {
    if (vt == OdRxValueType::Desc< OdArray< SubValueType > >::value())
    {
      const ValueType* inst = rxvalue_cast<ValueType>(&instance);
      subVal = inst->getArray();
      return true;
    }
    /*if (vt == OdRxValueType::Desc<const OdDAI::Aggr*>::value())
    {
      const OdDAI::Aggr* pAggrBase = rxvalue_cast<ValueType>(&instance);
      subVal = pAggrBase;
      return true;
    }*/
    return false;
  };

  virtual bool subFromValueType(const OdRxValue& from, OdRxValue &instance) const
  {
    if (from.type() == OdRxValueType::Desc< OdArray< SubValueType > >::value())
    {
      const OdArray<SubValueType> *pArr = rxvalue_cast< OdArray< SubValueType > >(&from);
      if (pArr)
      {
        ValueType aggr;
        aggr = *pArr;
        instance = aggr;
        return true;
      }
    }
    return false;
  };

  /*virtual const OdAnsiString subTypePath(const OdRxValue& instance) const
  {
  return "";
  const OdDAI::Select *pSel = rxvalue_cast<ValueType>(&instance);
  if (!pSel)
  throw OdError(L"Can not convert instance to value type");
  return pSel->underlyingTypeName();
  };*/

  virtual bool subEqualTo(const void* a, const void* b) const ODRX_OVERRIDE
  {
    return false;
    /*const OdDAI::Select *aSel = reinterpret_cast<const ValueType*>(a);
    const OdDAI::Select *bSel = reinterpret_cast<const ValueType*>(b);
    return (*aSel == *bSel);*/
  }

};

#endif

#endif // _DAI_AGGR_VALUE_TYPE_H_
