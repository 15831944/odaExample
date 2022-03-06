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

#ifndef __NWPROPERTYVALUE_H__
#define __NWPROPERTYVALUE_H__

#include "NwPropertyImpl.h"

template <class T>
class OdNwPropertyValue : public OdNwPropertyImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwProperty)
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwCategory)
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwCategoryImpl)
public:
  ODRX_DECLARE_MEMBERS(OdNwPropertyValue<T>);

  OdNwPropertyValue()
    : OdNwPropertyImpl()
    , m_value()
  {
    setValueType(m_value);
  }
  OdNwPropertyValue(const OdString& name, const OdString& displayName, T value)
    : OdNwPropertyImpl(name, displayName)
    , m_value(value)
  {
    setValueType(m_value);
  }
  OdNwPropertyValue(OdNwPropertyImpl* pProp, T value)
    : OdNwPropertyImpl(pProp->getClassName(), pProp->getClassDisplayName())
    , m_value(value)
  {
    setValueType(m_value);
  }
  virtual ~OdNwPropertyValue() {}

  static OdNwPropertyPtr createProperty(const OdString& name, const OdString& dispName, T value)
  {
    return OdNwObjectImpl::createNwObject<OdNwProperty>(new OdNwPropertyValue<T>(name, dispName, value));
  }

public:
  virtual float ValueToFloat() const { return ToFloat(m_value); }
  virtual double ValueToDouble() const { return ToDouble(m_value); }
  virtual OdString ValueToString() const { return ToString(m_value); }
  virtual OdUInt32 ValueToUInt32() const { return ToUInt32(m_value); }
  virtual OdUInt64 ValueToUInt64() const { return ToUInt64(m_value); }
  virtual bool isEmpty() const { return isDefault(m_value); }

public:
  T m_value;
};

typedef OdNwPropertyValue<bool> OdNwPropertyBool;
typedef OdNwPropertyValue<double> OdNwPropertyDouble;
typedef OdNwPropertyValue<float> OdNwPropertyFloat;
typedef OdNwPropertyValue<OdInt32> OdNwPropertyOdInt32;
typedef OdNwPropertyValue<OdUInt32> OdNwPropertyOdUInt32;
typedef OdNwPropertyValue<OdInt8> OdNwPropertyOdInt8;
typedef OdNwPropertyValue<OdUInt8> OdNwPropertyOdUInt8;
typedef OdNwPropertyValue<OdString> OdNwPropertyString;
typedef OdNwPropertyValue<OdStringArray> OdNwPropertyStringArray;
typedef OdNwPropertyValue<OdGeVector3d> OdNwPropertyOdGeVector3d;
typedef OdNwPropertyValue<OdUInt64> OdNwPropertyOdUInt64;
typedef OdNwPropertyValue<OdNwColor> OdNwPropertyOdNwColor;
typedef OdNwPropertyValue<tm> OdNwPropertyTm;
typedef OdNwPropertyValue<OdGePoint3d> OdNwPropertyOdGePoint3d;
typedef OdNwPropertyValue<OdGePoint2d> OdNwPropertyOdGePoint2d;
typedef OdNwPropertyValue<OdGUID> OdNwPropertyGUID;
typedef OdNwPropertyValue<OdNwPropDefault> OdNwPropertyDefault;

#endif //__NWPROPERTYVALUE_H__
