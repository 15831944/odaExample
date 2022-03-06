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

#ifndef __NWGRAPHICPROPERTY_INCLUDED_
#define __NWGRAPHICPROPERTY_INCLUDED_

#include "NwVariant.h"
#include "NwGraphicPropertyModelUnits.h"
#include "NwGraphicPropertyType.h"
#define STL_USING_MEMORY
#define STL_USING_VECTOR
#include "OdaSTL.h"

class OdNwGraphicBundle;
typedef OdSmartPtr<OdNwGraphicBundle> OdNwGraphicBundlePtr;
class OdBinaryData;

//traits for checking is class template
template <typename> struct is_template : std::false_type {};

template <template <typename...> class Tmpl, typename ...Args>
struct is_template<Tmpl<Args...> > : std::true_type {};

class OdNwGraphicProperty
{
public:
  OdNwGraphicProperty(const OdString& identifier, NwGraphicPropertyType::Enum type);
  OdNwGraphicProperty();
  ~OdNwGraphicProperty() = default;

public:
  NwGraphicPropertyType::Enum getType() const;
  NwGraphicPropertyModelUnits::Enum getUnits() const;
  bool isConnectionBundleEnable() const;
  const OdString& getIdentifier() const;
  const std::vector<OdNwGraphicBundlePtr>& getConnectedBundles() const;
  const OdNwVariant& getValue() const;

public:
  void setType(NwGraphicPropertyType::Enum val);
  void setUnits(NwGraphicPropertyModelUnits::Enum val);
  void setIsConnectionBundleEnable(bool val);
  void setIdentifier(const OdString& val);
  void addConnectedBundle(OdNwGraphicBundlePtr pConnectBundle);
  template <typename T>
  typename std::enable_if<!is_template<T>::value>::type setValue(T val)
  {
    m_value = OdNwVariant(val);
  }
  template <typename T>
  typename std::enable_if<is_template<T>::value && std::is_same<T, OdArray<OdNwColor> >::value>::type setValue(T val)
  {
    m_value.setColorArray(val);
  }
  template <typename T>
  typename std::enable_if<is_template<T>::value && std::is_same<T, OdDoubleArray>::value>::type setValue(T val)
  {
    m_value.setDoubleArray(val);
  }
  template <typename T>
  typename std::enable_if<is_template<T>::value && std::is_same<T, OdArray<OdUInt8> >::value>::type setValue(T val)
  {
    m_value.setUInt8Array(val);
  }
  template <typename T>
  typename std::enable_if<is_template<T>::value && std::is_same<T, OdUInt32Array>::value>::type setValue(T val)
  {
    m_value.setUInt32Array(val);
  }
  template <typename T>
  typename std::enable_if<is_template<T>::value && std::is_same<T, OdStringArray>::value>::type setValue(T val)
  {
    m_value.setStringArray(val);
  }

protected:
  NwGraphicPropertyType::Enum m_type;
  NwGraphicPropertyModelUnits::Enum m_units;
  bool m_bIsConnectionBundleEnable;
  OdString m_identifier;
  std::vector<OdNwGraphicBundlePtr> m_vConnectedBundle;
  OdNwVariant m_value;
};

typedef std::shared_ptr<OdNwGraphicProperty> OdNwGraphicPropertyPtr;
typedef std::weak_ptr<OdNwGraphicProperty> OdNwGraphicPropertyWeakPtr;

#endif //__NWGRAPHICPROPERTY_INCLUDED_
