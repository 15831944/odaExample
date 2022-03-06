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

#ifndef _IFC_RX_PROPERTIES_H
#define _IFC_RX_PROPERTIES_H

#include "OdaCommon.h"
#include "daiRxProperties.h"
#include "IfcValueTypes.h"

#undef ODRX_DECLARE_RX_PROPERTY_RO_TREE
#define ODRX_DECLARE_RX_PROPERTY_RO_TREE(Object, Name, Type, Category, Description, HierarchyLevel) \
struct Object ## Name ## Property : OdRxProperty {\
  static OdRxMemberPtr createObject(const OdRxClass* owner)\
  {\
    OdRxMemberPtr res = OdRxObjectImpl<Object ## Name ## Property>::createObject();\
    ((Object ## Name ## Property*)res.get())->init(__OD_T(#Name), &OdRxValueType::Desc<Type>::value(), owner);\
    if( OdString::kEmpty != Description ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdRxDescriptionAttribute::createObject(OD_T(Description))); \
    if( OdString::kEmpty != Category ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdRxUiPlacementAttribute::createObject(OD_T(Category), 1)); \
    if( OdString::kEmpty != HierarchyLevel ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdDAIRxHierarchyLevelAttribute::createObject()); \
    return res;\
  }\
  virtual OdResult subGetValue(const OdRxObject* pO, OdRxValue& value) const ODRX_OVERRIDE;\
  virtual bool isReadOnly(const OdRxObject*) const ODRX_OVERRIDE { return true; }\
}

#undef ODRX_DAI_DECLARE_RX_PROPERTY_COLLECTION_TREE
#define ODRX_DAI_DECLARE_RX_PROPERTY_COLLECTION_TREE(Object, Name, Type, Category, Description, HierarchyLevel) \
struct Object ## Name ## Property : OdRxCollectionProperty {\
  static OdRxMemberPtr createObject(const OdRxClass* owner)\
  {\
    OdRxMemberPtr res = OdRxObjectImpl<Object ## Name ## Property>::createObject();\
    ((Object ## Name ## Property*)res.get())->init(__OD_T(#Name), &OdRxValueType::Desc<Type>::value(), owner);\
    ((Object ## Name ## Property*)res.get())->attributes().add(OdIfcRxDisplayAsAttribute::createObject(false, true)); \
    if( OdString::kEmpty != Description ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdRxDescriptionAttribute::createObject(OD_T(Description))); \
    if( OdString::kEmpty != Category ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdRxUiPlacementAttribute::createObject(OD_T(Category), 1)); \
    if( OdString::kEmpty != HierarchyLevel ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdDAIRxHierarchyLevelAttribute::createObject()); \
    return res;\
  }\
  virtual OdRxValueIteratorPtr subNewValueIterator(const OdRxObject* pO) const ODRX_OVERRIDE;\
  virtual OdResult subTryGetCount(const OdRxObject* pO, int& count) const ODRX_OVERRIDE;\
}

#endif // _IFC_RX_PROPERTIES_H
