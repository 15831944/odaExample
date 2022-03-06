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

#include "DgElementProperties.h"

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ElementId
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementElementIdProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgElementPtr pObj = OdDgElement::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = pObj->elementId();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ODAUniqueID
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementODAUniqueIDProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgElementPtr pObj = OdDgElement::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = (OdUInt64)(pObj->elementId().getHandle());
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ElementType
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementElementTypeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgElementPtr pObj = OdDgElement::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = pObj->getElementType();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ElementSubType
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementElementSubTypeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgElementPtr pObj = OdDgElement::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = pObj->getElementSubType();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ModificationTime
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementModificationTimeProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgElementPtr pObj = OdDgElement::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  OdTimeStamp tmp;
  tmp.setPackedValue( (OdUInt64)(pObj->getLastModifiedTime())/1000);
  value = tmp;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: New
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementNewProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgElementPtr pObj = OdDgElement::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = pObj->isNewObject();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Modified
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementModifiedProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgElementPtr pObj = OdDgElement::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = pObj->isModifiedGraphics();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Locked
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementLockedProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgElementPtr pObj = OdDgElement::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;
  value = pObj->getLockedFlag();
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementLockedProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgElementPtr pObj = OdDgElement::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  const bool* pValue = rxvalue_cast<bool>(&value);

  if( pValue )
  {
    pObj->setLockedFlag(*pValue);
    return eOk;
  }

  return eNotThatKindOfClass;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Name
//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementNameProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgElementPtr pObj = OdDgElement::cast(pO);
  if (pObj.isNull())
    return eNotApplicable;

  OdString strName = pObj->isA()->name().c_str();
  value = strName;
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: ECClassInstances
//-----------------------------------------------------------------------------------------------------------------------

ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(OdRxObjectPtr);

OdRxValueIteratorPtr OdDgElementECClassInstancesProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr res;

  OdDgElementPtr pObj = OdDgElement::cast(pO);

  if (pObj.isNull())
    return res;

  OdDgECClassInstanceElementPEPtr pItemTypePE = OdDgECClassInstanceElementPE::cast(pObj);

  if (pItemTypePE.isNull())
    return res;

  res = OdRxObjectImpl<OdRxOdRxObjectPtrValueIterator>::createObject();

  if (!pObj.isNull())
  {
    OdArray<OdRxObjectPtr> arrECClassItems;

    for (OdUInt32 i = 0; i < pItemTypePE->getECClassInstanceCount(pObj); i++)
    {
      OdDgECClassInstancePtr pCurInstance = pItemTypePE->getECClassInstance(pObj, i);

      if( pCurInstance.isNull() )
        continue;

      arrECClassItems.push_back(pCurInstance);
    }

    ((OdRxOdRxObjectPtrValueIterator*)res.get())->init(arrECClassItems, 0);
  }

  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementECClassInstancesProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdDgECClassInstanceElementPEPtr pItemTypePE = OdDgECClassInstanceElementPE::cast(pObj);

  if (pItemTypePE.isNull())
    return eNotApplicable;

  count = 0;

  for (OdUInt32 i = 0; i < pItemTypePE->getECClassInstanceCount(pObj); i++)
  {
    OdDgECClassInstancePtr pCurInstance = pItemTypePE->getECClassInstance(pObj, i);

    if( pCurInstance.isNull() )
      continue;

    count++;
  }

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementECClassInstancesProperty::subGetValue(const OdRxObject* pO, int index, OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdDgECClassInstanceElementPEPtr pItemTypePE = OdDgECClassInstanceElementPE::cast(pObj);

  if (pItemTypePE.isNull())
    return eNotApplicable;

  if( index < 0 )
    return eInvalidIndex;

  int			 iCurCount = 0;
  bool		 bSetValue = false;

  for (OdUInt32 i = 0; i < pItemTypePE->getECClassInstanceCount(pObj); i++)
  {
    OdDgECClassInstancePtr pCurInstance = pItemTypePE->getECClassInstance(pObj, i);

    if( pCurInstance.isNull() )
      continue;

    if( iCurCount == index )
    {
      OdRxObjectPtr pRet = pCurInstance;
      value = pRet;
      bSetValue = true;
      break;
    }

    iCurCount++;
  }

  if( bSetValue )
    return eOk;

  return eInvalidIndex;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementECClassInstancesProperty::subSetValue(OdRxObject* pO, int index, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdDgECClassInstanceElementPEPtr pItemTypePE = OdDgECClassInstanceElementPE::cast(pObj);

  if (pItemTypePE.isNull())
    return eNotApplicable;

  const OdRxObjectPtr* pValue = rxvalue_cast<OdRxObjectPtr>(&value);

  if( pValue && (*pValue)->isKindOf(OdDgECClassInstance::desc()) )
  {
    int			 iCurCount = 0;

    bool bSetValue = false;

    for (OdUInt32 i = 0; i < pItemTypePE->getECClassInstanceCount(pObj); i++)
    {
      OdDgECClassInstancePtr pCurInstance = pItemTypePE->getECClassInstance(pObj, i);

      if( pCurInstance.isNull() )
        continue;

      if( iCurCount == index )
      {
        OdDgECClassInstancePtr pClass = *pValue;
        pItemTypePE->setECClassInstance(pObj, i, pClass);
        bSetValue = true;
        break;
      }

      iCurCount++;
    }

    if (bSetValue)
      return eOk;
    else
      return eInvalidIndex;
  }

  return eNotThatKindOfClass;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementECClassInstancesProperty::subInsertValue(OdRxObject* pO, int index, const OdRxValue& value) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdDgECClassInstanceElementPEPtr pItemTypePE = OdDgECClassInstanceElementPE::cast(pObj);

  if (pItemTypePE.isNull())
    return eNotApplicable;

  const OdRxObjectPtr* pValue = rxvalue_cast<OdRxObjectPtr>(&value);

  if( pValue && (*pValue)->isKindOf(OdDgECClassInstance::desc()) )
  {
    bool bAddInstance = false;

    OdDgECClassInstancePtr pCurInstance = *pValue;

    pItemTypePE->addECClassInstance(pObj, pCurInstance);
    return eOk;
  }

  return eNotThatKindOfClass;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementECClassInstancesProperty::subRemoveValue(OdRxObject* pO, int index) const
{
  OdDgGraphicsElementPtr pObj = OdDgGraphicsElement::cast(pO);

  if (pObj.isNull())
    return eNotApplicable;

  OdDgECClassInstanceElementPEPtr pItemTypePE = OdDgECClassInstanceElementPE::cast(pObj);

  if (pItemTypePE.isNull())
    return eNotApplicable;

  int			 iCurCount = 0;
  bool		 bSetValue = false;

  for (OdUInt32 i = 0; i < pItemTypePE->getECClassInstanceCount(pObj); i++)
  {
    OdDgECClassInstancePtr pCurInstance = pItemTypePE->getECClassInstance(pObj, i);

    if( pCurInstance.isNull() )
      continue;

    if (iCurCount == index)
    {
      pItemTypePE->deleteECClassInstance(pObj, i);
      bSetValue = true;
      break;
    }

    iCurCount++;
  }

  if (bSetValue)
    return eOk;
  else
    return eInvalidIndex;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementECClassInstancesProperty::subChildren(OdArray<OdRxMemberPtr>& children) const
{
  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: array Metadata properties
//-----------------------------------------------------------------------------------------------------------------------

OdRxMemberPtr OdDgElementArrayECProperty::createObject(const OdString& strName, const OdDgECPropertyInstance& propInstance, const OdDgECClassReference& classRef, OdUInt32 uWeight, const OdRxClass* owner)
{
  OdRxMemberPtr res = OdRxObjectImpl<OdDgElementArrayECProperty>::createObject();

  switch (propInstance.getType())
  {
    case OdDgECPropertyInstance::kBoolArray:
    {
      ((OdDgElementArrayECProperty*)res.get())->init(strName, &OdRxValueType::Desc<bool>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kByteArray:
    {
      ((OdDgElementArrayECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdInt8>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kShortArray:
    {
      ((OdDgElementArrayECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdInt16>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kInt32Array:
    {
      ((OdDgElementArrayECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdInt32>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kInt64Array:
    {
      ((OdDgElementArrayECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdInt64>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kDoubleArray:
    {
      ((OdDgElementArrayECProperty*)res.get())->init(strName, &OdRxValueType::Desc<double>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kStringArray:
    {
      ((OdDgElementArrayECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdString>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kPoint3dArray:
    {
      ((OdDgElementArrayECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdGePoint3d>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kDateTimeArray:
    {
      ((OdDgElementArrayECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdTimeStamp>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kECClassInstanceArray:
    {
      ((OdDgElementArrayECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdRxObjectPtr>::value(), owner);
      ((OdDgElementArrayECProperty*)res.get())->attributes().add(OdRxUnionTypeAttribute::createObject(OD_T("OdDgECClassInstancePtr")));
    } break;

    default:
      res = NULL;
  }

  if (!res.isNull())
  {
    ((OdDgElementArrayECProperty*)res.get())->attributes().add(OdRxUiPlacementAttribute::createObject(convertECSchemaItemNameToString(classRef.getClassName()), uWeight));
    ((OdDgElementArrayECProperty*)res.get())->m_classRef = classRef;
    ((OdDgElementArrayECProperty*)res.get())->m_propertyName = propInstance.getName();
  }

  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult getECPropertyInstanceArrayRxValue(const OdDgECPropertyInstance& propInstance, int index, OdRxValue& value)
{
  switch (propInstance.getType())
  {
    case OdDgECPropertyInstance::kBoolArray:
    {
      OdArray<bool> arrValues = propInstance.getBoolArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        value = arrValues[index];
      else
        return eInvalidIndex;
    } break;
    case OdDgECPropertyInstance::kByteArray:
    {
      OdArray<OdInt8> arrValues = propInstance.getByteArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        value = arrValues[index];
      else
        return eInvalidIndex;
    } break;

    case OdDgECPropertyInstance::kShortArray:
    {
      OdArray<OdInt16> arrValues = propInstance.getShortArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        value = arrValues[index];
      else
        return eInvalidIndex;
    } break;

    case OdDgECPropertyInstance::kInt32Array:
    {
      OdArray<OdInt32> arrValues = propInstance.getIntArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        value = arrValues[index];
      else
        return eInvalidIndex;
    } break;

    case OdDgECPropertyInstance::kInt64Array:
    {
      OdArray<OdInt64> arrValues = propInstance.getInt64ArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        value = arrValues[index];
      else
        return eInvalidIndex;
    } break;

    case OdDgECPropertyInstance::kDoubleArray:
    {
      OdArray<double> arrValues = propInstance.getDoubleArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        value = arrValues[index];
      else
        return eInvalidIndex;
    } break;

    case OdDgECPropertyInstance::kStringArray:
    {
      OdArray<OdString> arrValues = propInstance.getStringArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        value = arrValues[index];
      else
        return eInvalidIndex;
    } break;

    case OdDgECPropertyInstance::kPoint3dArray:
    {
      OdArray<OdGePoint3d> arrValues = propInstance.getPoint3dArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        value = arrValues[index];
      else
        return eInvalidIndex;
    } break;

    case OdDgECPropertyInstance::kDateTimeArray:
    {
      OdArray<OdTimeStamp> arrValues = propInstance.getDateTimeArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        value = arrValues[index];
      else
        return eInvalidIndex;
    } break;

    case OdDgECPropertyInstance::kECClassInstanceArray:
    {
      const OdArray<OdDgECClassInstancePtr> arrValues = propInstance.getClassInstanceArrayValue();

      if (arrValues.size() > (OdUInt32)index)
      {
        OdRxObjectPtr pObj = arrValues[index];
        value = pObj;
      }
      else
        return eInvalidIndex;
    } break;

    default:
      return eNotApplicable;
  }

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult setECPropertyInstanceArrayRxValue( OdDgECClassInstancePtr& pClassInstance, const OdString& strPropertyName, int index, const OdRxValue& value)
{
  if (pClassInstance.isNull())
    return eNotApplicable;

  OdDgECPropertyInstance propInstance = pClassInstance->getPropertyInstance(strPropertyName);

  switch (propInstance.getType())
  {
    case OdDgECPropertyInstance::kBoolArray:
    {
      const bool* pValue = rxvalue_cast<bool>(&value);

      if (pValue)
      {
        OdArray<bool> arrValues = propInstance.getBoolArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues[index] = *pValue;
        else
          return eInvalidIndex;

        propInstance.setBoolArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kByteArray:
    {
      const OdInt8* pValue = rxvalue_cast<OdInt8>(&value);

      if (pValue)
      {
        OdArray<OdInt8> arrValues = propInstance.getByteArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues[index] = *pValue;
        else
          return eInvalidIndex;

        propInstance.setByteArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kShortArray:
    {
      const OdInt16* pValue = rxvalue_cast<OdInt16>(&value);

      if (pValue)
      {
        OdArray<OdInt16> arrValues = propInstance.getShortArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues[index] = *pValue;
        else
          return eInvalidIndex;

        propInstance.setShortArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kInt32Array:
    {
      const OdInt32* pValue = rxvalue_cast<OdInt32>(&value);

      if (pValue)
      {
        OdArray<OdInt32> arrValues = propInstance.getIntArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues[index] = *pValue;
        else
          return eInvalidIndex;

        propInstance.setIntArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kInt64Array:
    {
      const OdInt64* pValue = rxvalue_cast<OdInt64>(&value);

      if (pValue)
      {
        OdArray<OdInt64> arrValues = propInstance.getInt64ArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues[index] = *pValue;
        else
          return eInvalidIndex;

        propInstance.setInt64ArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kDoubleArray:
    {
      const double* pValue = rxvalue_cast<double>(&value);

      if (pValue)
      {
        OdArray<double> arrValues = propInstance.getDoubleArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues[index] = *pValue;
        else
          return eInvalidIndex;

        propInstance.setDoubleArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kStringArray:
    {
      const OdString* pValue = rxvalue_cast<OdString>(&value);

      if (pValue)
      {
        OdArray<OdString> arrValues = propInstance.getStringArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues[index] = *pValue;
        else
          return eInvalidIndex;

        propInstance.setStringArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kPoint3dArray:
    {
      const OdGePoint3d* pValue = rxvalue_cast<OdGePoint3d>(&value);

      if (pValue)
      {
        OdArray<OdGePoint3d> arrValues = propInstance.getPoint3dArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues[index] = *pValue;
        else
          return eInvalidIndex;

        propInstance.setPoint3dArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kDateTimeArray:
    {
      const OdTimeStamp* pValue = rxvalue_cast<OdTimeStamp>(&value);

      if (pValue)
      {
        OdArray<OdTimeStamp> arrValues = propInstance.getDateTimeArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues[index] = *pValue;
        else
          return eInvalidIndex;

        propInstance.setDateTimeArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kECClassInstanceArray:
    {
      const OdRxObjectPtr* pValue = rxvalue_cast<OdRxObjectPtr>(&value);

      if (pValue && (*pValue)->isKindOf(OdDgECClassInstance::desc()))
      {
        const OdDgECClassInstancePtr pInstanceValue = (const OdDgECClassInstancePtr)(*pValue);

        OdArray<OdDgECClassInstancePtr> arrValues = propInstance.getClassInstanceArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues[index] = pInstanceValue;
        else
          return eInvalidIndex;

        propInstance.setClassInstanceArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    default:
      return eNotApplicable;
  }

  pClassInstance->setPropertyInstance(propInstance);

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult insertECPropertyInstanceArrayRxValue(OdDgECClassInstancePtr& pClassInstance, const OdString& strPropertyName, int index, const OdRxValue& value)
{
  if (pClassInstance.isNull())
    return eNotApplicable;

  OdDgECPropertyInstance propInstance = pClassInstance->getPropertyInstance(strPropertyName);

  switch (propInstance.getType())
  {
    case OdDgECPropertyInstance::kBoolArray:
    {
      const bool* pValue = rxvalue_cast<bool>(&value);

      if (pValue)
      {
        OdArray<bool> arrValues = propInstance.getBoolArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues.insert(arrValues.begin() + index, *pValue);
        else
          arrValues.push_back(*pValue);

        propInstance.setBoolArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kByteArray:
    {
      const OdInt8* pValue = rxvalue_cast<OdInt8>(&value);

      if (pValue)
      {
        OdArray<OdInt8> arrValues = propInstance.getByteArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues.insert(arrValues.begin() + index, *pValue);
        else
          arrValues.push_back(*pValue);

        propInstance.setByteArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kShortArray:
    {
      const OdInt16* pValue = rxvalue_cast<OdInt16>(&value);

      if (pValue)
      {
        OdArray<OdInt16> arrValues = propInstance.getShortArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues.insert(arrValues.begin() + index, *pValue);
        else
          arrValues.push_back(*pValue);

        propInstance.setShortArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kInt32Array:
    {
      const OdInt32* pValue = rxvalue_cast<OdInt32>(&value);

      if (pValue)
      {
        OdArray<OdInt32> arrValues = propInstance.getIntArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues.insert(arrValues.begin() + index, *pValue);
        else
          arrValues.push_back(*pValue);

        propInstance.setIntArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kInt64Array:
    {
      const OdInt64* pValue = rxvalue_cast<OdInt64>(&value);

      if (pValue)
      {
        OdArray<OdInt64> arrValues = propInstance.getInt64ArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues.insert(arrValues.begin() + index, *pValue);
        else
          arrValues.push_back(*pValue);

        propInstance.setInt64ArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kDoubleArray:
    {
      const double* pValue = rxvalue_cast<double>(&value);

      if (pValue)
      {
        OdArray<double> arrValues = propInstance.getDoubleArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues.insert(arrValues.begin() + index, *pValue);
        else
          arrValues.push_back(*pValue);

        propInstance.setDoubleArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kStringArray:
    {
      const OdString* pValue = rxvalue_cast<OdString>(&value);

      if (pValue)
      {
        OdArray<OdString> arrValues = propInstance.getStringArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues.insert(arrValues.begin() + index, *pValue);
        else
          arrValues.push_back(*pValue);

        propInstance.setStringArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kPoint3dArray:
    {
      const OdGePoint3d* pValue = rxvalue_cast<OdGePoint3d>(&value);

      if (pValue)
      {
        OdArray<OdGePoint3d> arrValues = propInstance.getPoint3dArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues.insert(arrValues.begin() + index, *pValue);
        else
          arrValues.push_back(*pValue);

        propInstance.setPoint3dArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kDateTimeArray:
    {
      const OdTimeStamp* pValue = rxvalue_cast<OdTimeStamp>(&value);

      if (pValue)
      {
        OdArray<OdTimeStamp> arrValues = propInstance.getDateTimeArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues.insert(arrValues.begin() + index, *pValue);
        else
          arrValues.push_back(*pValue);

        propInstance.setDateTimeArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kECClassInstanceArray:
    {
      const OdRxObjectPtr* pValue = rxvalue_cast<OdRxObjectPtr>(&value);

      if (pValue && (*pValue)->isKindOf(OdDgECClassInstance::desc()))
      {
        const OdDgECClassInstancePtr pInstanceValue = (const OdDgECClassInstancePtr)(*pValue);

        OdArray<OdDgECClassInstancePtr> arrValues = propInstance.getClassInstanceArrayValue();

        if (arrValues.size() > (OdUInt32)index)
          arrValues.insert(arrValues.begin() + index, *pValue);
        else
          arrValues.push_back(*pValue);

        propInstance.setClassInstanceArrayValue(arrValues);
      }
      else
        return eNotThatKindOfClass;
    } break;

    default:
      return eNotApplicable;
  }

  pClassInstance->setPropertyInstance(propInstance);

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult removeECPropertyInstanceArrayRxValue(OdDgECClassInstancePtr& pClassInstance, const OdString& strPropertyName, int index)
{
  if (pClassInstance.isNull())
    return eNotApplicable;

  OdDgECPropertyInstance propInstance = pClassInstance->getPropertyInstance(strPropertyName);

  switch (propInstance.getType())
  {
    case OdDgECPropertyInstance::kBoolArray:
    {
      OdArray<bool> arrValues = propInstance.getBoolArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        arrValues.removeAt(index);
      else
        return eInvalidIndex;

      propInstance.setBoolArrayValue(arrValues);
    } break;

    case OdDgECPropertyInstance::kByteArray:
    {
      OdArray<OdInt8> arrValues = propInstance.getByteArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        arrValues.removeAt(index);
      else
        return eInvalidIndex;

      propInstance.setByteArrayValue(arrValues);
    } break;

    case OdDgECPropertyInstance::kShortArray:
    {
      OdArray<OdInt16> arrValues = propInstance.getShortArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        arrValues.removeAt(index);
      else
        return eInvalidIndex;

      propInstance.setShortArrayValue(arrValues);
    } break;

    case OdDgECPropertyInstance::kInt32Array:
    {
      OdArray<OdInt32> arrValues = propInstance.getIntArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        arrValues.removeAt(index);
      else
        return eInvalidIndex;

      propInstance.setIntArrayValue(arrValues);
    } break;

    case OdDgECPropertyInstance::kInt64Array:
    {
      OdArray<OdInt64> arrValues = propInstance.getInt64ArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        arrValues.removeAt(index);
      else
        return eInvalidIndex;

      propInstance.setInt64ArrayValue(arrValues);
    } break;

    case OdDgECPropertyInstance::kDoubleArray:
    {
      OdArray<double> arrValues = propInstance.getDoubleArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        arrValues.removeAt(index);
      else
        return eInvalidIndex;

      propInstance.setDoubleArrayValue(arrValues);
    } break;

    case OdDgECPropertyInstance::kStringArray:
    {
      OdArray<OdString> arrValues = propInstance.getStringArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        arrValues.removeAt(index);
      else
        return eInvalidIndex;

      propInstance.setStringArrayValue(arrValues);
    } break;

    case OdDgECPropertyInstance::kPoint3dArray:
    {
      OdArray<OdGePoint3d> arrValues = propInstance.getPoint3dArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        arrValues.removeAt(index);
      else
        return eInvalidIndex;

      propInstance.setPoint3dArrayValue(arrValues);
    } break;

    case OdDgECPropertyInstance::kDateTimeArray:
    {
      OdArray<OdTimeStamp> arrValues = propInstance.getDateTimeArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        arrValues.removeAt(index);
      else
        return eInvalidIndex;

      propInstance.setDateTimeArrayValue(arrValues);
    } break;

    case OdDgECPropertyInstance::kECClassInstanceArray:
    {
      OdArray<OdDgECClassInstancePtr> arrValues = propInstance.getClassInstanceArrayValue();

      if (arrValues.size() > (OdUInt32)index)
        arrValues.removeAt(index);
      else
        return eInvalidIndex;

      propInstance.setClassInstanceArrayValue(arrValues);
    } break;

    default:
      return eNotApplicable;
  }

  pClassInstance->setPropertyInstance(propInstance);

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(bool);
ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(OdInt8);
ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(OdInt16);
ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(OdInt32);
ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(OdInt64);
ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(double);
ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(OdString);
ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(OdGePoint3d);
ODDG_DEFINE_RX_VALUE_ARRAY_ITERATOR(OdTimeStamp);

//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr createECClassInstanceRXValueIterator(OdDgECClassInstancePtr& pClassInstance, const OdString& strPropertyName)
{
  OdRxValueIteratorPtr pIter;

  if (pClassInstance.isNull())
    return pIter;

  OdDgECPropertyInstance propInstance = pClassInstance->getPropertyInstance(strPropertyName);

  switch (propInstance.getType())
  {
    case OdDgECPropertyInstance::kBoolArray:
    {
      OdArray<bool> arrValues = propInstance.getBoolArrayValue();
      pIter = OdRxObjectImpl<OdRxboolValueIterator>::createObject();
      ((OdRxboolValueIterator*)pIter.get())->init(arrValues, 0);
    } break;

    case OdDgECPropertyInstance::kByteArray:
    {
      OdArray<OdInt8> arrValues = propInstance.getByteArrayValue();
      pIter = OdRxObjectImpl<OdRxOdInt8ValueIterator>::createObject();
      ((OdRxOdInt8ValueIterator*)pIter.get())->init(arrValues, 0);
    } break;

    case OdDgECPropertyInstance::kShortArray:
    {
      OdArray<OdInt16> arrValues = propInstance.getShortArrayValue();
      pIter = OdRxObjectImpl<OdRxOdInt16ValueIterator>::createObject();
      ((OdRxOdInt16ValueIterator*)pIter.get())->init(arrValues, 0);
    } break;

    case OdDgECPropertyInstance::kInt32Array:
    {
      OdArray<OdInt32> arrValues = propInstance.getIntArrayValue();
      pIter = OdRxObjectImpl<OdRxOdInt32ValueIterator>::createObject();
      ((OdRxOdInt32ValueIterator*)pIter.get())->init(arrValues, 0);
    } break;

    case OdDgECPropertyInstance::kInt64Array:
    {
      OdArray<OdInt64> arrValues = propInstance.getInt64ArrayValue();
      pIter = OdRxObjectImpl<OdRxOdInt64ValueIterator>::createObject();
      ((OdRxOdInt64ValueIterator*)pIter.get())->init(arrValues, 0);
    } break;

    case OdDgECPropertyInstance::kDoubleArray:
    {
      OdArray<double> arrValues = propInstance.getDoubleArrayValue();
      pIter = OdRxObjectImpl<OdRxdoubleValueIterator>::createObject();
      ((OdRxdoubleValueIterator*)pIter.get())->init(arrValues, 0);
    } break;

    case OdDgECPropertyInstance::kStringArray:
    {
      OdArray<OdString> arrValues = propInstance.getStringArrayValue();
      pIter = OdRxObjectImpl<OdRxOdStringValueIterator>::createObject();
      ((OdRxOdStringValueIterator*)pIter.get())->init(arrValues, 0);
    } break;

    case OdDgECPropertyInstance::kPoint3dArray:
    {
      OdArray<OdGePoint3d> arrValues = propInstance.getPoint3dArrayValue();
      pIter = OdRxObjectImpl<OdRxOdGePoint3dValueIterator>::createObject();
      ((OdRxOdGePoint3dValueIterator*)pIter.get())->init(arrValues, 0);
    } break;

    case OdDgECPropertyInstance::kDateTimeArray:
    {
      OdArray<OdTimeStamp> arrValues = propInstance.getDateTimeArrayValue();
      pIter = OdRxObjectImpl<OdRxOdTimeStampValueIterator>::createObject();
      ((OdRxOdTimeStampValueIterator*)pIter.get())->init(arrValues, 0);
    } break;

    case OdDgECPropertyInstance::kECClassInstanceArray:
    {
      OdArray<OdDgECClassInstancePtr> arrValues = propInstance.getClassInstanceArrayValue();
      OdArray<OdRxObjectPtr>  arrObjs;

      for (OdUInt32 i = 0; i < arrValues.size(); i++)
        arrObjs.push_back(arrValues[i]);

      pIter = OdRxObjectImpl<OdRxOdRxObjectPtrValueIterator>::createObject();
      ((OdRxOdRxObjectPtrValueIterator*)pIter.get())->init(arrObjs, 0);
    } break;

    default:
      return pIter;
  }

  return pIter;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult getECClassInstanceArrayRXValueCount(OdDgECClassInstancePtr& pClassInstance, const OdString& strPropertyName, int& count )
{
  if (pClassInstance.isNull())
    return eNotApplicable;

  OdDgECPropertyInstance propInstance = pClassInstance->getPropertyInstance(strPropertyName);

  switch (propInstance.getType())
  {
    case OdDgECPropertyInstance::kBoolArray:
    {
      OdArray<bool> arrValues = propInstance.getBoolArrayValue();
      count = arrValues.size();
    } break;

    case OdDgECPropertyInstance::kByteArray:
    {
      OdArray<OdInt8> arrValues = propInstance.getByteArrayValue();
      count = arrValues.size();
    } break;

    case OdDgECPropertyInstance::kShortArray:
    {
      OdArray<OdInt16> arrValues = propInstance.getShortArrayValue();
      count = arrValues.size();
    } break;

    case OdDgECPropertyInstance::kInt32Array:
    {
      OdArray<OdInt32> arrValues = propInstance.getIntArrayValue();
      count = arrValues.size();
    } break;

    case OdDgECPropertyInstance::kInt64Array:
    {
      OdArray<OdInt64> arrValues = propInstance.getInt64ArrayValue();
      count = arrValues.size();
    } break;

    case OdDgECPropertyInstance::kDoubleArray:
    {
      OdArray<double> arrValues = propInstance.getDoubleArrayValue();
      count = arrValues.size();
    } break;

    case OdDgECPropertyInstance::kStringArray:
    {
      OdArray<OdString> arrValues = propInstance.getStringArrayValue();
      count = arrValues.size();
    } break;

    case OdDgECPropertyInstance::kPoint3dArray:
    {
      OdArray<OdGePoint3d> arrValues = propInstance.getPoint3dArrayValue();
      count = arrValues.size();
    } break;

    case OdDgECPropertyInstance::kDateTimeArray:
    {
      OdArray<OdTimeStamp> arrValues = propInstance.getDateTimeArrayValue();
      count = arrValues.size();
    } break;

    case OdDgECPropertyInstance::kECClassInstanceArray:
    {
      OdArray<OdDgECClassInstancePtr> arrValues = propInstance.getClassInstanceArrayValue();
      count = arrValues.size();
    } break;

    default:
      return eNotApplicable;
  }

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementArrayECProperty::subGetValue(const OdRxObject* pO, int index, OdRxValue& value) const
{
  OdDgECClassInstancePtr pClassInstance;

  OdDgElementPtr pObj = OdDgElement::cast(pO);

  if (pObj.isNull())
    pClassInstance = OdDgECClassInstance::cast(pO);
  else
  {
    OdDgECClassInstanceElementPEPtr pECClassInstance = pObj;

    if (pECClassInstance.isNull())
      return eNotApplicable;

    pClassInstance = pECClassInstance->getECClassInstance(pObj, m_classRef);
  }

  if (pClassInstance.isNull())
    return eNotApplicable;

  OdDgECPropertyInstance propInstance = pClassInstance->getPropertyInstance(m_propertyName);

  return getECPropertyInstanceArrayRxValue(propInstance, index, value);
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementArrayECProperty::subSetValue(OdRxObject* pO, int index, const OdRxValue& value) const
{
  OdDgECClassInstancePtr pClassInstance;

  OdDgElementPtr pObj = OdDgElement::cast(pO);

  if (pObj.isNull())
    pClassInstance = OdDgECClassInstance::cast(pO);
  else
  {
    OdDgECClassInstanceElementPEPtr pECClassInstance = pObj;

    if (pECClassInstance.isNull())
      return eNotApplicable;

    pClassInstance = pECClassInstance->getECClassInstance(pObj, m_classRef);
  }

  return setECPropertyInstanceArrayRxValue(pClassInstance, m_propertyName, index, value);
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementArrayECProperty::subInsertValue(OdRxObject* pO, int index, const OdRxValue& value) const
{
  OdDgECClassInstancePtr pClassInstance;

  OdDgElementPtr pObj = OdDgElement::cast(pO);

  if (pObj.isNull())
    pClassInstance = OdDgECClassInstance::cast(pO);
  else
  {
    OdDgECClassInstanceElementPEPtr pECClassInstance = pObj;

    if (pECClassInstance.isNull())
      return eNotApplicable;

    pClassInstance = pECClassInstance->getECClassInstance(pObj, m_classRef);
  }

  return insertECPropertyInstanceArrayRxValue(pClassInstance, m_propertyName, index, value);
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementArrayECProperty::subRemoveValue(OdRxObject* pO, int index) const
{
  OdDgECClassInstancePtr pClassInstance;

  OdDgElementPtr pObj = OdDgElement::cast(pO);

  if (pObj.isNull())
    pClassInstance = OdDgECClassInstance::cast(pO);
  else
  {
    OdDgECClassInstanceElementPEPtr pECClassInstance = pObj;

    if (pECClassInstance.isNull())
      return eNotApplicable;

    pClassInstance = pECClassInstance->getECClassInstance(pObj, m_classRef);
  }

  return removeECPropertyInstanceArrayRxValue(pClassInstance, m_propertyName, index);
}

//-----------------------------------------------------------------------------------------------------------------------

OdRxValueIteratorPtr OdDgElementArrayECProperty::subNewValueIterator(const OdRxObject* pO) const
{
  OdRxValueIteratorPtr pIter;
  OdDgECClassInstancePtr pClassInstance;

  OdDgElementPtr pObj = OdDgElement::cast(pO);

  if (pObj.isNull())
    pClassInstance = OdDgECClassInstance::cast(pO);
  else
  {
    OdDgECClassInstanceElementPEPtr pECClassInstance = pObj;

    if (pECClassInstance.isNull())
      return pIter;

    pClassInstance = pECClassInstance->getECClassInstance(pObj, m_classRef);
  }

  return createECClassInstanceRXValueIterator(pClassInstance, m_propertyName);
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementArrayECProperty::subTryGetCount(const OdRxObject* pO, int& count) const
{
  OdDgECClassInstancePtr pClassInstance;

  OdDgElementPtr pObj = OdDgElement::cast(pO);

  if (pObj.isNull())
    pClassInstance = OdDgECClassInstance::cast(pO);
  else
  {
    OdDgECClassInstanceElementPEPtr pECClassInstance = pObj;

    if (pECClassInstance.isNull())
      return eNotApplicable;

    pClassInstance = pECClassInstance->getECClassInstance(pObj, m_classRef);
  }

  return getECClassInstanceArrayRXValueCount(pClassInstance, m_propertyName, count);
}

//-----------------------------------------------------------------------------------------------------------------------
//                                          property: Metadata properties
//-----------------------------------------------------------------------------------------------------------------------

OdRxMemberPtr OdDgElementECProperty::createObject(const OdString& strName, 
                                                    const OdDgECPropertyInstance& propInstance,
                                                      const OdDgECClassReference& classRef, 
                                                        OdUInt32 uWeight,
                                                          const OdRxClass* owner)
{
  OdRxMemberPtr res = OdRxObjectImpl<OdDgElementECProperty>::createObject();

  switch( propInstance.getType() )
  {
    case OdDgECPropertyInstance::kBool:
    {
      ((OdDgElementECProperty*)res.get())->init(strName, &OdRxValueType::Desc<bool>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kByte:
    {
      ((OdDgElementECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdInt8>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kShort:
    {
      ((OdDgElementECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdInt16>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kInt32:
    {
      ((OdDgElementECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdInt32>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kInt64:
    {
      ((OdDgElementECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdInt64>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kDouble:
    {
      ((OdDgElementECProperty*)res.get())->init(strName, &OdRxValueType::Desc<double>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kString:
    {
      ((OdDgElementECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdString>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kPoint3d:
    {
      ((OdDgElementECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdGePoint3d>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kDateAndTime:
    {
      ((OdDgElementECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdTimeStamp>::value(), owner);
    } break;

    case OdDgECPropertyInstance::kECClassInstance:
    {
      ((OdDgElementECProperty*)res.get())->init(strName, &OdRxValueType::Desc<OdRxObjectPtr>::value(), owner);
      ((OdDgElementECProperty*)res.get())->attributes().add(OdRxUnionTypeAttribute::createObject(OD_T("OdDgECClassInstancePtr")));
    } break;

    default:
      res = NULL;
  }

  if( !res.isNull() )
  {
    ((OdDgElementECProperty*)res.get())->attributes().add(OdRxUiPlacementAttribute::createObject(convertECSchemaItemNameToString(classRef.getClassName()), uWeight));
    ((OdDgElementECProperty*)res.get())->m_classRef         = classRef;
    ((OdDgElementECProperty*)res.get())->m_propertyName     = propInstance.getName();
  }

  return res;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult getECPropertyRxValue(const OdDgECClassInstancePtr& pClassInstance, const OdString& strPropertyName, OdRxValue& value)
{
  if (pClassInstance.isNull())
    return eNotApplicable;

  OdDgECPropertyInstance propInstance = pClassInstance->getPropertyInstance(strPropertyName);

  switch (propInstance.getType())
  {
    case OdDgECPropertyInstance::kBool:            value = propInstance.getBoolValue(); break;
    case OdDgECPropertyInstance::kByte:            value = propInstance.getByteValue(); break;
    case OdDgECPropertyInstance::kShort:           value = propInstance.getShortValue(); break;
    case OdDgECPropertyInstance::kInt32:           value = propInstance.getIntValue(); break;
    case OdDgECPropertyInstance::kInt64:           value = propInstance.getInt64Value(); break;
    case OdDgECPropertyInstance::kDouble:          value = propInstance.getDoubleValue(); break;
    case OdDgECPropertyInstance::kString:          value = propInstance.getStringValue(); break;
    case OdDgECPropertyInstance::kPoint3d:         value = propInstance.getPoint3dValue(); break;
    case OdDgECPropertyInstance::kDateAndTime:     value = propInstance.getDateTimeValue(); break;
    case OdDgECPropertyInstance::kECClassInstance: 
    {
      OdDgECClassInstancePtr pClassInstance = propInstance.getClassInstanceValue();

      if( !pClassInstance.isNull() )
      {
        OdRxObjectPtr pObj = pClassInstance;
        value = pObj;
      }
    } break;
    default:
      return eNotApplicable;
  }

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------


OdResult setECPropertyRxValue(OdDgECClassInstancePtr& pClassInstance, const OdString& strPropertyName, const OdRxValue& value)
{

  if (pClassInstance.isNull())
    return eNotApplicable;

  OdDgECPropertyInstance propInstance = pClassInstance->getPropertyInstance(strPropertyName);

  switch (propInstance.getType())
  {
    case OdDgECPropertyInstance::kBool:
    {
      const bool* pValue = rxvalue_cast<bool>(&value);

      if (pValue)
        propInstance.setBoolValue(*pValue);
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kByte:
    {
      const OdInt8* pValue = rxvalue_cast<OdInt8>(&value);

      if (pValue)
        propInstance.setByteValue(*pValue);
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kShort:
    {
      const OdInt16* pValue = rxvalue_cast<OdInt16>(&value);

      if (pValue)
        propInstance.setShortValue(*pValue);
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kInt32:
    {
      const OdInt32* pValue = rxvalue_cast<OdInt32>(&value);

      if (pValue)
        propInstance.setIntValue(*pValue);
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kInt64:
    {
      const OdInt64* pValue = rxvalue_cast<OdInt64>(&value);

      if (pValue)
        propInstance.setInt64Value(*pValue);
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kDouble:
    {
      const double* pValue = rxvalue_cast<double>(&value);

      if (pValue)
        propInstance.setDoubleValue(*pValue);
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kString:
    {
      const OdString* pValue = rxvalue_cast<OdString>(&value);

      if (pValue)
        propInstance.setStringValue(*pValue);
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kPoint3d:
    {
      const OdGePoint3d* pValue = rxvalue_cast<OdGePoint3d>(&value);

      if (pValue)
        propInstance.setPoint3dValue(*pValue);
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kDateAndTime:
    {
      const OdTimeStamp* pValue = rxvalue_cast<OdTimeStamp>(&value);

      if (pValue)
        propInstance.setDateTimeValue(*pValue);
      else
        return eNotThatKindOfClass;
    } break;

    case OdDgECPropertyInstance::kECClassInstance:
    {
      const OdRxObjectPtr* pValue = rxvalue_cast<OdRxObjectPtr>(&value);

      if (pValue && (*pValue)->isKindOf(OdDgECClassInstance::desc()))
      {
        propInstance.setClassInstanceValue(*pValue);
      }
      else
        return eNotThatKindOfClass;
    } break;

    default:
      return eNotApplicable;
  }

  pClassInstance->setPropertyInstance(propInstance);

  return eOk;
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementECProperty::subGetValue(const OdRxObject* pO, OdRxValue& value) const
{
  OdDgECClassInstancePtr pClassInstance;

  OdDgElementPtr pObj = OdDgElement::cast(pO);

  if( pObj.isNull() )
    pClassInstance = OdDgECClassInstance::cast(pO);
  else
  {
    OdDgECClassInstanceElementPEPtr pECClassInstance = pObj;

    if (pECClassInstance.isNull())
      return eNotApplicable;

    pClassInstance = pECClassInstance->getECClassInstance(pObj, m_classRef);
  }

  return getECPropertyRxValue(pClassInstance, m_propertyName, value);
}

//-----------------------------------------------------------------------------------------------------------------------

OdResult OdDgElementECProperty::subSetValue(OdRxObject* pO, const OdRxValue& value) const
{
  OdDgECClassInstancePtr pClassInstance;

  OdDgElementPtr pObj = OdDgElement::cast(pO);

  if (pObj.isNull())
    pClassInstance = OdDgECClassInstance::cast(pO);
  else
  {
    OdDgECClassInstanceElementPEPtr pECClassInstance = pObj;

    if (pECClassInstance.isNull())
      return eNotApplicable;

    pClassInstance = pECClassInstance->getECClassInstance(pObj, m_classRef);
  }

  return setECPropertyRxValue(pClassInstance, m_propertyName, value);
}

//-----------------------------------------------------------------------------------------------------------------------



