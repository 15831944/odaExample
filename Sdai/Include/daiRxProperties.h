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

#ifndef _DAI_RXPROPERTIES_H_
#define _DAI_RXPROPERTIES_H_

#include "daiPlatform.h"
#include "daiObjectId.h"

#include "RxProperty.h"

struct DAI_EXPORT OdDAIObjectIdIterator : OdRxValueIterator
{
  ODRX_DECLARE_MEMBERS(OdDAIObjectIdIterator);

  /** \details
  Returns true if the iteration is ended.
  */
  virtual bool done();

  /** \details
  Step to the next item. Returns true if there actually was a next item.
  */
  virtual bool next();

  /** \details
  Returns the current item.
  */
  virtual OdRxValue current() const;

  void init(OdDAIObjectIds &ids);

protected:

  OdDAIObjectIds m_ids;
  OdDAIObjectIds::iterator m_pos;

};
typedef OdSmartPtr<OdDAIObjectIdIterator> OdDAIObjectIdIteratorPtr;

//

#define ODRX_DAI_DECLARE_RX_PROPERTY(Object, Name, Type, Category) struct Object ## Name ## Property : OdRxProperty {\
  static OdRxMemberPtr createObject(const OdRxClass* owner)\
  {\
    OdRxMemberPtr res = OdRxObjectImpl<Object ## Name ## Property>::createObject();\
    ((Object ## Name ## Property*)res.get())->init(__OD_T(#Name), &OdRxValueType::Desc<Type>::value(), owner);\
    if( OdString::kEmpty != Category ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdRxUiPlacementAttribute::createObject(OD_T(Category), 1)); \
    return res;\
  }\
  virtual OdResult subGetValue(const OdRxObject* pO, OdRxValue& value) const ODRX_OVERRIDE;\
  virtual OdResult subSetValue(OdRxObject* pO, const OdRxValue& value) const ODRX_OVERRIDE;\
}

#define ODRX_DAI_DECLARE_RX_ENUM_PROPERTY_UI(Object, Name, Type, Category) struct Object ## Name ## Property : OdRxProperty {\
  static OdRxMemberPtr createObject(const OdRxClass* owner)\
  {\
    OdRxMemberPtr res = OdRxObjectImpl<Object ## Name ## Property>::createObject();\
    const OdDAI::EnumerationType* enumerationType = Type##TypeProvider::instance().getSchemaType(); \
    const OdDAI::SpecifiedEnumPtrValueType* specEnumType = enumerationType ? enumerationType->getSpecifiedValueType() : nullptr; \
    ((Object ## Name ## Property*)res.get())->init(__OD_T(#Name), specEnumType, owner);\
    if( OdString::kEmpty != Category ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdRxUiPlacementAttribute::createObject(OD_T(Category), 1)); \
    return res;\
  }\
  virtual OdResult subGetValue(const OdRxObject* pO, OdRxValue& value) const ODRX_OVERRIDE;\
  virtual OdResult subSetValue(OdRxObject* pO, const OdRxValue& value) const ODRX_OVERRIDE;\
}


#define ODRX_DAI_DECLARE_ENUM_RX_PROPERTY(Object, Name, TypeName) struct Object ## Name ## Property : OdRxProperty {\
  static OdRxMemberPtr createObject(const OdRxClass* owner)\
  {\
    OdRxMemberPtr res = OdRxObjectImpl<Object ## Name ## Property>::createObject();\
    const OdDAI::EnumerationType* enumerationType = TypeName##TypeProvider::instance().getSchemaType(); \
    const OdDAI::SpecifiedEnumPtrValueType* specEnumType = enumerationType ? enumerationType->getSpecifiedValueType() : nullptr; \
    ((Object ## Name ## Property*)res.get())->init(__OD_T(#Name), specEnumType, owner);\
    return res;\
  }\
  virtual OdResult subGetValue(const OdRxObject* pO, OdRxValue& value) const ODRX_OVERRIDE;\
  virtual OdResult subSetValue(OdRxObject* pO, const OdRxValue& value) const ODRX_OVERRIDE;\
}


#define ODRX_DAI_DECLARE_RX_PROPERTY_UI(Object, Name, Type, Category) struct Object ## Name ## Property : OdRxProperty {\
  static OdRxMemberPtr createObject(const OdRxClass* owner)\
  {\
    OdRxMemberPtr res = OdRxObjectImpl<Object ## Name ## Property>::createObject();\
    ((Object ## Name ## Property*)res.get())->init(__OD_T(#Name), &OdRxValueType::Desc<Type>::value(), owner);\
    if( OdString::kEmpty != Category ) \
      ((Object ## Name ## Property*)res.get())->attributes().add(OdRxUiPlacementAttribute::createObject(OD_T(Category), 1)); \
    return res;\
  }\
  virtual OdResult subGetValue(const OdRxObject* pO, OdRxValue& value) const ODRX_OVERRIDE;\
  virtual OdResult subSetValue(OdRxObject* pO, const OdRxValue& value) const ODRX_OVERRIDE;\
}

#define OD_DAI_DEFINE_COLLECTION_TREE_PROPERTY_INTERMEDIARY(Object, Name, IntermediaryPropName) \
OdRxValueIteratorPtr Object ## Name ## Property::subNewValueIterator(const OdRxObject* pO) const\
{\
  OdRxValueIteratorPtr res;\
  OdDAI::ApplicationInstancePtr pEnt = OdDAI::ApplicationInstance::cast(pO);\
  if (!pEnt.isNull())\
  {\
    OdDAIObjectIds idsRel;\
    if (pEnt->getAttrCaseInsensitive( #Name ) >> idsRel) {\
      OdDAIObjectIds resIds;\
      OdDAI::ApplicationInstancePtr pIntermediary;\
      for (OdDAIObjectIds::iterator it = idsRel.begin(), end = idsRel.end(); it < end; ++it) {\
        pIntermediary = it->openObject(OdDAI::kForRead);\
        if (!pIntermediary.isNull()) {\
          OdDAIObjectIds idsIntermediary;\
          if (pIntermediary->getAttrCaseInsensitive( #IntermediaryPropName ) >> idsIntermediary) {\
            resIds.append(idsIntermediary);\
          }\
        }\
      }\
      if (resIds.size() > 0) {\
        res = OdRxObjectImpl<OdDAIObjectIdIterator>::createObject();\
        ((OdDAIObjectIdIterator*)res.get())->init(resIds);\
      }\
    }\
  }\
  return res;\
}\
OdResult Object ## Name ## Property::subTryGetCount(const OdRxObject* pO, int& count) const\
{\
  const OdDAI::ApplicationInstancePtr pEnt = OdDAI::ApplicationInstance::cast(pO);\
  if (pEnt.isNull())\
    return eNotApplicable;\
  count = 0;\
  OdDAIObjectIds idsRel;\
  if (pEnt->getAttrCaseInsensitive( #Name ) >> idsRel) {\
    OdDAI::ApplicationInstancePtr pIntermediary;\
    for (OdDAIObjectIds::iterator it = idsRel.begin(), end = idsRel.end(); it < end; ++it) {\
      pIntermediary = it->openObject(OdDAI::kForRead);\
      if (!pIntermediary.isNull()) {\
        OdDAIObjectIds idsIntermediary;\
        if (pIntermediary->getAttrCaseInsensitive( #IntermediaryPropName ) >> idsIntermediary) {\
          count += idsIntermediary.size();\
        }\
      }\
    }\
    return eOk;\
  }\
  return eInvalidProps;\
}\


#define OD_DAI_DEFINE_PRIMITIVE_PROPERTY(Object, Name, Type) \
OdResult Object ## Name ## Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const\
{\
  OdSmartPtr<Object> pObj = Object::cast(pO);\
  if (pObj.isNull())\
    return eNotApplicable;\
  value = pObj->get ## Name ();\
  return eOk;\
}\
OdResult Object ## Name ## Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const\
{\
  OdSmartPtr<Object> pObj = Object::cast(pO);\
  if (pObj.isNull())\
    return eNotApplicable;\
  const Type *pVal = rxvalue_cast<Type>(&value);\
  if (pVal)\
  {\
    pObj->set ## Name (*pVal);\
    return eOk;\
  }\
  return eNotApplicable;\
}

#define OD_DAI_DEFINE_PRIMITIVE_STRING_PROPERTY(Object, Name) \
OdResult Object ## Name ## Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const\
{\
  OdSmartPtr<Object> pObj = Object::cast(pO);\
  if (pObj.isNull())\
    return eNotApplicable;\
  \
  OdAnsiString valueConvert = pObj->get ##Name (); \
  value = OdString(valueConvert, CP_UTF_8);\
  \
  return eOk;\
}\
OdResult Object ## Name ## Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const\
{\
  OdSmartPtr<Object> pObj = Object::cast(pO);\
  if (pObj.isNull())\
    return eNotApplicable;\
  \
  const OdString *pVal = rxvalue_cast<OdString>(&value);\
  \
  pObj->set ## Name (OdAnsiString(*pVal, CP_UTF_8));\
  \
  return eNotApplicable;\
}


#define OD_DAI_DEFINE_PRIMITIVE_AGGR_PROPERTY(Object, Name, Type)\
OdResult Object ## Name ## Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const\
{\
  OdSmartPtr<Object> pObj = Object::cast(pO);\
  if (pObj.isNull())\
    return eNotApplicable;\
  Type arr;\
  pObj->get ## Name (arr);\
  value = arr;\
  return eOk;\
}\
OdResult Object ## Name ## Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const\
{\
  return eNotApplicable;\
}

/*
OdResult Object ## Name ## Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const\
{\
  OdSmartPtr<Object> pObj = Object::cast(pO);\
  if (pObj.isNull())\
    return eNotApplicable;\
  const Type *pVal = rxvalue_cast<Type>(&value);\
  if (pVal)\
  {\
    pObj->set ## Name (*pVal);\ // Interface changes
    return eOk;\
  }\
  return eNotApplicable;\
}
*/

#define OD_DAI_DEFINE_INV_PROPERTY(Object, Name)\
OdResult Object ## Name ## Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const\
{\
  OdSmartPtr<Object> pObj = Object::cast(pO);\
  if (pObj.isNull())\
    return eNotApplicable;\
  value = pObj->getInv ## Name(); \
  return eOk;\
}\
OdResult Object ## Name ## Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const\
{\
  return eNotApplicable;\
}

#define OD_DAI_DEFINE_INV_AGGR_PROPERTY(Object, Name)\
OdResult Object ## Name ## Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const\
{\
  OdSmartPtr<Object> pObj = Object::cast(pO);\
  if (pObj.isNull())\
    return eNotApplicable;\
  OdDAIObjectIds arr;\
  pObj->getInv ## Name (arr);\
  value = arr;\
  return eOk;\
}\
OdResult Object ## Name ## Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const\
{\
  return eNotApplicable;\
}

#define OD_DAI_DEFINE_ENUM_PROPERTY(Object, Name, Type)\
OdResult Object ## Name ## Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const\
{\
  OdSmartPtr<Object> pObj = Object::cast(pO);\
  if (pObj.isNull())\
    return eNotApplicable;\
  value = pObj->getAttrCaseInsensitive( #Name );\
  const OdDAI::EnumerationType* enumerationType = Type##TypeProvider::instance().getSchemaType(); \
  const OdDAI::SpecifiedEnumPtrValueType* specEnumType = enumerationType ? enumerationType->getSpecifiedValueType() : nullptr; \
  if (!specEnumType) return eNullHandle;\
  value = OdRxValue(*specEnumType, value); \
  return eOk;\
}\
OdResult Object ## Name ## Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const\
{\
  return eNotApplicable;\
}

#define OD_DAI_DEFINE_SELECT_PROPERTY(Object, Name, Type)\
OdResult Object ## Name ## Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const\
{\
  return eNotApplicable;\
}\
OdResult Object ## Name ## Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const\
{\
  return eNotApplicable;\
}

#define OD_DAI_DEFINE_SELECT_AGGR_PROPERTY(Object, Name, Type)\
OdResult Object ## Name ## Property::subGetValue(const OdRxObject* pO, OdRxValue& value) const\
{\
  return eNotApplicable;\
}\
OdResult Object ## Name ## Property::subSetValue(OdRxObject* pO, const OdRxValue& value) const\
{\
  return eNotApplicable;\
}

#endif // _DAI_RXPROPERTIES_H_
