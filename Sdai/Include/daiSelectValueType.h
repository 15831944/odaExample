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

#ifndef _DAI_SELECT_VALUE_TYPE_H_
#define _DAI_SELECT_VALUE_TYPE_H_

#include "daiSelect.h"

#include "daiAttributeDataBlock.h"
#include "daiUtils/daiUnset.h"
#include "daiUtils/daiCustomCompare.h"

#include "daiAggr/daiTypedAggrItemManager.h"

namespace OdDAI {

  DAI_EXPORT bool _subFromValueType(const OdDAI::AttributeDataBlock* from, OdDAI::Select* select);
  DAI_EXPORT bool _subFromValueType(const OdRxValue& from, Select* select);
  DAI_EXPORT bool _subToValueType(const OdRxValueType& vt, const Select* from, OdRxValue& subVal);
  DAI_EXPORT bool _subToValueType(const Select* from, OdDAI::AttributeDataBlock* to);
  DAI_EXPORT OdString _subToString(const Select* select, OdRxValueType::StringFormat format);
}

DAI_EXPORT bool operator >> (const OdRxValue& valueFrom, OdDAI::Select& itemTo);

#define DAI_DECLARE_VT_SELECT(type_name, exp_attr)\
  template<> struct OdRxValueType::Desc< type_name >\
  {\
    exp_attr static const OdRxValueType& value() throw();\
    exp_attr static void del();\
  };\
  template<> OdRxValue::OdRxValue(type_name const &) throw();


DAI_DECLARE_VT_SELECT(OdDAI::Select*, DAI_EXPORT);
DAI_DECLARE_VT_SELECT(OdDAI::Select, DAI_EXPORT);

namespace OdDAI
{
  template<class SchemaItemTypeProvide>
  class TypedAggrItemManager<OdDAI::Select, SchemaItemTypeProvide>
  {
  public:
    static  bool translate(const OdRxValue& valueFrom, OdDAI::Select& itemTo)
    {
      itemTo = OdDAI::Select(SchemaItemTypeProvide::SchemaType());
      return valueFrom >> itemTo;
    }

    static bool checkType(const OdDAI::Select& itemTo)
    {
      return itemTo.getSchemaType() == SchemaItemTypeProvide::SchemaType();
    }
  };

}


#endif // _DAI_SELECT_VALUE_TYPE_H_
