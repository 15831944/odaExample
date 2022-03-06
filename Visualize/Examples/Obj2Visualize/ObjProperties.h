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

#ifndef OBJPROPERTIES_H
#define OBJPROPERTIES_H

#include "OdaCommon.h"
#include "RxProperty.h"
#include "RxValueTypeUtil.h"
#include "RxValueType.h"
#include "RxAttribute.h"
#include "RxCategory.h"
#include "OBJToolkit.h"
#include "RxValue.h"
#include <set>
using namespace OBJToolkit;

/** \details
Protocol extension to handle loading strings from resources (CDA properties)
*/
class OdTvVisualizeObjFilerPropResourceLoaderPE : public OdRxResourceLoader
{
protected:
  /** \details
  Load the string identified by the id and hint. Implementation is up to the application.
  */
  virtual OdResult subLoadString(unsigned int id, unsigned int sourceHint, OdString& result);
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdTvVisualizeObjFilerPropResourceLoaderPE);
  //DOM-IGNORE-END
};



/** \details
Just for more accurate working with PE of ResourceLoader
*/
class OdTvVisualizeObjFilerPropertyWithResLoader : public OdRxProperty
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdTvVisualizeObjFilerPropertyWithResLoader);
  //DOM-IGNORE-END
};



/**  \details
Create database properties and it them to the list
*/
extern void createOdObjDatabaseProperties(OdArray<OdRxMemberPtr>& properties, OdRxMemberCollectionBuilder& b, void*);


/** \details
Set of defines
*/
#undef ODRX_DECLARE_RX_PROPERTY_OBJ
#define ODRX_DECLARE_RX_PROPERTY_OBJ(Object, Name, Type, Category, Weight, Description, LocStrId) \
struct Object ## Name ## Property : OdTvVisualizeObjFilerPropertyWithResLoader {\
  static OdRxMemberPtr createObject(const OdRxClass* owner)\
  {\
    OdRxMemberPtr res = OdRxObjectImpl<Object ## Name ## Property>::createObject();\
    ((Object ## Name ## Property*)res.get())->init(__OD_T(#Name), &OdRxValueType::Desc<Type>::value(), owner);\
    ((Object ## Name ## Property*)res.get())->attributes().add(OdRxLocalizedNameAttribute::createObject(LocStrId)); \
    if( OdString::kEmpty != Description ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdRxDescriptionAttribute::createObject(OD_T(Description))); \
    if( OdString::kEmpty != Category ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdRxUiPlacementAttribute::createObject(OD_T(Category), Weight)); \
    return res;\
  }\
  virtual OdResult subGetValue(const OdRxObject* pO, OdRxValue& value) const ODRX_OVERRIDE;\
  virtual bool isReadOnly(const OdRxObject*) const ODRX_OVERRIDE { return true; }\
}

#undef ODRX_DECLARE_RX_PROPERTY_HIERARCHY
#define ODRX_DECLARE_RX_PROPERTY_HIERARCHY(Object, Name, Type, Category, Weight, Description, HierarchyLevel) \
struct Object ## Name ## Property : OdRxProperty {\
  static OdRxMemberPtr createObject(const OdRxClass* owner)\
  {\
    OdRxMemberPtr res = OdRxObjectImpl<Object ## Name ## Property>::createObject();\
    ((Object ## Name ## Property*)res.get())->init(__OD_T(#Name), &OdRxValueType::Desc<Type>::value(), owner);\
    ((Object ## Name ## Property*)res.get())->attributes().add(OdRxDisplayAsAttribute::createObject(L"Name")); \
    if( OdString::kEmpty != Description ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdRxDescriptionAttribute::createObject(OD_T(Description))); \
    if( OdString::kEmpty != HierarchyLevel ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdRxHierarchyLevelAttribute::createObject()); \
    return res;\
  }\
  virtual OdResult subGetValue(const OdRxObject* pO, OdRxValue& value) const ODRX_OVERRIDE;\
  virtual bool isReadOnly(const OdRxObject*) const ODRX_OVERRIDE { return true; }\
}


/** \details
Properties for the database
*/
ODRX_DECLARE_RX_PROPERTY_HIERARCHY(OdObjDb, Groups, OdString, "Contents", 1, "Contents of the database", "Group");
ODRX_DECLARE_RX_PROPERTY_OBJ(OdObjDb, ObjectsNum, OdUInt32, "Contents", 1, "Number of the database objects", 0);
ODRX_DECLARE_RX_PROPERTY_OBJ(OdObjDb, MaterialsNum, OdUInt32, "Contents", 2, "Number of the database materials", 1);

#endif // OBJPROPERTIES_H
