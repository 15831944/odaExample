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

#ifndef __NWPROPERTYIMPL_INCLUDED__
#define __NWPROPERTYIMPL_INCLUDED__

#include "NwProperty.h"
#include "NwModelBaseImpl.h"
#include "OdDToStr.h"
#include "Ge/GeVector3d.h"
#include "Ge/GePoint3d.h"
#include "Ge/GePoint2d.h"
#include "NwColor.h"

class OdNwPropDefault {};

class OdNwPropertyImpl;


class OdNwPropertyImpl : public OdNwModelBaseImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwProperty)
public:
  OdNwPropertyImpl();
  OdNwPropertyImpl(const OdString& name, const OdString& displayName);
  virtual ~OdNwPropertyImpl();
  ODRX_DECLARE_MEMBERS(OdNwPropertyImpl);

public:
  static OdNwPropertyImpl* getImpl(const OdNwProperty* pNwProperty);
  static OdNwPropertyImpl* getImpl(const OdRxObject* pRxProperty);

public:
  //public impelementation's methods
  NwPropertyValueType::Enum getValueType() const;

protected:
  template <typename T> void setValueType(T param);
  void setValueType(const bool& param) { m_ValueType = NwPropertyValueType::value_type_bool; }
  void setValueType(const double& param) { m_ValueType = NwPropertyValueType::value_type_double; }
  void setValueType(const float& param) { m_ValueType = NwPropertyValueType::value_type_float; }
  void setValueType(const OdInt32& param) { m_ValueType = NwPropertyValueType::value_type_OdInt32; }
  void setValueType(const OdInt8& param) { m_ValueType = NwPropertyValueType::value_type_OdInt8; }
  void setValueType(const OdUInt32& param) { m_ValueType = NwPropertyValueType::value_type_OdUInt32; }
  void setValueType(const OdUInt8& param) { m_ValueType = NwPropertyValueType::value_type_OdUInt8; }
  void setValueType(const OdString& param) { m_ValueType = NwPropertyValueType::value_type_OdString; }
  void setValueType(const OdStringArray& param) { m_ValueType = NwPropertyValueType::value_type_OdStringArray; }
  void setValueType(const OdGeVector3d& param) { m_ValueType = NwPropertyValueType::value_type_OdGeVector3d; }
  void setValueType(const OdUInt64& param) { m_ValueType = NwPropertyValueType::value_type_OdUInt64; }
  void setValueType(const OdNwColor& param) { m_ValueType = NwPropertyValueType::value_type_OdNwColor; }
  void setValueType(const tm& param) { m_ValueType = NwPropertyValueType::value_type_tm; }
  void setValueType(const OdNwPropDefault& param) { m_ValueType = NwPropertyValueType::value_type_default; }
  void setValueType(const OdGUID& param) { m_ValueType = NwPropertyValueType::value_type_GUID; }
  void setValueType(const OdGePoint3d& param) { m_ValueType = NwPropertyValueType::value_type_OdGePoint3d; }
  void setValueType(const OdGePoint2d& param) { m_ValueType = NwPropertyValueType::value_type_OdGePoint2d; }

public:
  virtual float ValueToFloat() const = 0;
  virtual double ValueToDouble() const = 0;
  virtual OdString ValueToString() const = 0;
  virtual OdUInt32 ValueToUInt32() const = 0;
  virtual OdUInt64 ValueToUInt64() const = 0;
  virtual bool isEmpty() const = 0;

protected:
  template <typename T> bool isDefault(T value) const { return value ? false : true; }
  bool isDefault(const OdString& value) const { return value.isEmpty(); }
  bool isDefault(const OdStringArray& value) const { return value.isEmpty(); }
  bool isDefault(const OdGeVector3d& value) const { return value == OdGeVector3d(0,0,0); }
  bool isDefault(const OdNwColor& value) const { return OdEqual(value.A(), 1.0) && OdEqual(value.R(), 0.0) && OdEqual(value.G(), 0.0) && OdEqual(value.B(), 0.0); }
  bool isDefault(const tm& value) const { return false; }
  bool isDefault(const OdNwPropDefault& value) const { return false; }
  bool isDefault(const OdGUID& value) const { return false; }
  bool isDefault(const OdGePoint3d& value) const { return value == OdGePoint3d(0, 0, 0); }
  bool isDefault(const OdGePoint2d& value) const { return value == OdGePoint2d(0, 0); }

  template <typename T> double ToDouble(T value) const { return static_cast<double>(value); }
  double ToDouble(const OdString& value) const { return odStrToD(value); }
  double ToDouble(const OdStringArray& value) const { return 0; }
  double ToDouble(const OdGeVector3d& value) const { return 0; }
  double ToDouble(const OdNwColor& value) const { return 0; }
  double ToDouble(const tm& value) const { return 0; }
  double ToDouble(const OdNwPropDefault& value) const { return 0; }
  double ToDouble(const OdGUID& value) const { return 0; }
  double ToDouble(const OdGePoint3d& value) const { return 0; }
  double ToDouble(const OdGePoint2d& value) const { return 0; }

  template <typename T> OdUInt32 ToUInt32(T value) const { return static_cast<OdUInt32>(value); }
  OdUInt32 ToUInt32(const OdString& value) const { return odStrToUInt(value); }
  OdUInt32 ToUInt32(const OdStringArray& value) const { return 0; }
  OdUInt32 ToUInt32(const OdGeVector3d& value) const { return 0; }
  OdUInt32 ToUInt32(const OdNwColor& value) const { return 0; }
  OdUInt32 ToUInt32(const tm& value) const { return 0; }
  OdUInt32 ToUInt32(const OdNwPropDefault& value) const { return 0; }
  OdUInt32 ToUInt32(const OdGUID& value) const { return 0; }
  OdUInt32 ToUInt32(const OdGePoint3d& value) const { return 0; }
  OdUInt32 ToUInt32(const OdGePoint2d& value) const { return 0; }

  template <typename T> OdUInt64 ToUInt64(T value) const { return static_cast<OdUInt64>(value); }
  OdUInt64 ToUInt64(const OdString& value) const { return odStrToUInt(value); }
  OdUInt64 ToUInt64(const OdStringArray& value) const { return 0; }
  OdUInt64 ToUInt64(const OdGeVector3d& value) const { return 0; }
  OdUInt64 ToUInt64(const OdNwColor& value) const { return 0; }
  OdUInt64 ToUInt64(const tm& value) const { return 0; }
  OdUInt64 ToUInt64(const OdNwPropDefault& value) const { return 0; }
  OdUInt64 ToUInt64(const OdGUID& value) const { return 0; }
  OdUInt64 ToUInt64(const OdGePoint3d& value) const { return 0; }
  OdUInt64 ToUInt64(const OdGePoint2d& value) const { return 0; }

  template <typename T> float ToFloat(T value) const { return static_cast<float>(value); }
  float ToFloat(const OdString& value) const { return odStrToF(value); }
  float ToFloat(const OdStringArray& value) const { return 0; }
  float ToFloat(const OdGeVector3d& value) const { return 0; }
  float ToFloat(const OdNwColor& value) const { return 0; }
  float ToFloat(const tm& value) const { return 0; }
  float ToFloat(const OdNwPropDefault& value) const { return 0; }
  float ToFloat(const OdGUID& value) const { return 0; }
  float ToFloat(const OdGePoint3d& value) const { return 0; }
  float ToFloat(const OdGePoint2d& value) const { return 0; }

  template <typename T> OdString ToString(T value) const;
  OdString ToString(const OdString& value) const { return value; }
  OdString ToString(const OdStringArray& value) const { return OD_T(""); }
  OdString ToString(const OdGeVector3d& value) const { return OD_T(""); }
  OdString ToString(const OdNwColor& value) const { return OD_T(""); }
  OdString ToString(const tm& value) const { return OD_T(""); }
  OdString ToString(const bool& value) const { return OdString().format(OD_T("%d"), value); }
  OdString ToString(const double& value) const { return OdString().format(OD_T("%f"), value); }
  OdString ToString(const float& value) const { return OdString().format(OD_T("%f"), value); }
  OdString ToString(const OdInt32& value) const { return OdString().format(OD_T("%d"), value); }
  OdString ToString(const OdInt8& value) const { return OdString().format(OD_T("%d"), value); }
  OdString ToString(const OdUInt32& value) const { return OdString().format(OD_T("%u"), value); }
  OdString ToString(const OdUInt8& value) const { return OdString().format(OD_T("%u"), value); }
  OdString ToString(const OdUInt64& value) const { return OdString().format(OD_T("%u"), value); }
  OdString ToString(const OdNwPropDefault& value) const { return OD_T(""); }
  OdString ToString(const OdGUID& value) const { return value.toString(); }
  OdString ToString(const OdGePoint3d& value) const { return OdString().format(OD_T("%f;%f;%f"), value.x, value.y, value.z); }
  OdString ToString(const OdGePoint2d& value) const { return OdString().format(OD_T("%f;%f"), value.x, value.y); }
protected:
  NwPropertyValueType::Enum m_ValueType;
};

#endif //__NWPROPERTYIMPL_INCLUDED__
