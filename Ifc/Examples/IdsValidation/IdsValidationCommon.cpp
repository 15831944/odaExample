#include "IdsValidationCommon.h"
#include "IdsValidationCommon.h"
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

#include "IdsValidationCommon.h"
#include "daiApplicationInstance.h"
#include <regex>
#include <cctype>

using namespace OdIds;

IdsOptionsChecker::IdsOptionsChecker(OdSharedPtr<OdDAI::ValidationTask::InvalidValidationParamsBase>& invalidParams):
  m_invalidParamsBase(invalidParams),
  m_isValidation(false),
  m_invalidParams(nullptr)
{
}

void IdsOptionsChecker::setValidationRegime(bool isValidation)
{
  m_isValidation = isValidation;
  if (!m_invalidParams)
  {
    m_invalidParams = new OdDAI::ValidationTask::InvalidInstanceValidationParams();
    m_invalidParamsBase = m_invalidParams;
  }
}

namespace
{
  enum ComparisonOperators
  {
    kEqual,
    kMinInclusive,
    kMaxInclusive,
    kMinExclusive,
    kMaxExclusive
  };

  template<class T>
  OdDAI::Logical checkEquality(const OdRxValue& value, const OdRxValue& idsValue, ComparisonOperators comparison)
  {
    T valT;
    double idsValT;
    OdAnsiString idsValAnsi;
    value >> valT;
    idsValue >> idsValAnsi;
    idsValT = atof(idsValAnsi.c_str());
    switch (comparison)
    {
    case kEqual:
      if (valT == idsValT)
        return OdDAI::Logical::True;
      break;
    case kMinInclusive:
      if (valT >= idsValT)
        return OdDAI::Logical::True;
      break;
    case kMaxInclusive:
      if (valT <= idsValT)
        return OdDAI::Logical::True;
      break;
    case kMinExclusive:
      if (valT > idsValT)
        return OdDAI::Logical::True;
      break;
    case kMaxExclusive:
      if (valT < idsValT)
        return OdDAI::Logical::True;
      break;
    default:
      break;
    }

    return OdDAI::Logical::False;
  }
  template<>
  OdDAI::Logical checkEquality<OdAnsiString>(const OdRxValue& value, const OdRxValue& idsValue, ComparisonOperators comparison)
  {
    OdAnsiString valT;
    OdAnsiString idsValAnsi;
    value >> valT;
    idsValue >> idsValAnsi;

    switch (comparison)
    {
    case kEqual:
      if (valT == idsValAnsi)
        return OdDAI::Logical::True;
      break;
    case kMinInclusive:
      if (valT >= idsValAnsi)
        return OdDAI::Logical::True;
      break;
    case kMaxInclusive:
      if (valT <= idsValAnsi)
        return OdDAI::Logical::True;
      break;
    case kMinExclusive:
      if (valT > idsValAnsi)
        return OdDAI::Logical::True;
      break;
    case kMaxExclusive:
      if (valT < idsValAnsi)
        return OdDAI::Logical::True;
      break;
    default:
      break;
    }

    return OdDAI::Logical::False;
  }

  OdDAI::Logical checkTypeAndEquality(const OdRxValue& value, const OdRxValue& idsValue, int valueType, ComparisonOperators comparison)
  {
    if (valueType == IdsValue::kInteger)
    {
      if (checkEquality<int>(value, idsValue, comparison) == OdDAI::Logical::False)
        return OdDAI::Logical::False;
    }
    else if (valueType == IdsValue::kReal)
    {
      if (checkEquality<double>(value, idsValue, comparison) == OdDAI::Logical::False)
        return OdDAI::Logical::False;
    }
    else
    {
      if (checkEquality<OdAnsiString>(value, idsValue, comparison) == OdDAI::Logical::False)
        return OdDAI::Logical::False;
    }
    return OdDAI::Logical::True;
  }
}

OdDAI::Logical IdsOptionsChecker::checkIdsValue(OdRxValue value, const IdsValue& idsValue)
{
  const auto& whiteSpaceVal = idsValue.value.find(IdsValue::kWhiteSpace);
  if (whiteSpaceVal != idsValue.value.cend())
  {
    int wsInt;
    whiteSpaceVal->second >> wsInt;
    if (wsInt == IdsValue::kReplace || wsInt == IdsValue::kCollapse)
    {
      OdAnsiString strValue;
      value >> strValue;
      for (int i = 0 ; i< strValue.getLength(); ++i)
        if (std::isspace(strValue[i]))
        {
          strValue.setAt(i, ' ');
        }

      if (wsInt == IdsValue::kCollapse)
      {
        int spacesFinder = strValue.find(' ', 0);
        while (spacesFinder >= 0)
        {
          if (spacesFinder == 0)
          {
            strValue.trimLeft();
            spacesFinder = strValue.find(' ', spacesFinder);
          }
          else if (spacesFinder == strValue.getLength() - 1)
          {
            strValue.trimRight();
            spacesFinder = strValue.find(' ', spacesFinder);
          }
          else if (strValue[spacesFinder + 1] == ' ')
          {
            strValue.deleteChars(spacesFinder);
          }
          else
            spacesFinder = strValue.find(' ', spacesFinder+1);
        }
      }
      value = strValue;
    }
  }

  for (const auto& rule : idsValue.value)
  {
    switch (rule.first)
    {
    case IdsValue::kNone:
      if (checkTypeAndEquality(value, rule.second, idsValue.valueType, kEqual) == OdDAI::Logical::False)
        return OdDAI::Logical::False;
      break;
    case IdsValue::kEnumeration:
    {
      OdAnsiString strVal;
      OdAnsiStringArray arrayVal;
      value >> strVal;
      rule.second >> arrayVal;

      unsigned int index;
      if (!arrayVal.find(strVal, index))
        return OdDAI::Logical::False;
      break;
    }
    case IdsValue::kMinInclusive:
    {
      if (checkTypeAndEquality(value, rule.second, idsValue.valueType, kMinInclusive) == OdDAI::Logical::False)
        return OdDAI::Logical::False;
      break;
    }
    case IdsValue::kMaxInclusive:
    {
      if (checkTypeAndEquality(value, rule.second, idsValue.valueType, kMaxInclusive) == OdDAI::Logical::False)
        return OdDAI::Logical::False;
      break;
    }
    case IdsValue::kMinExclusive:
    {
      if (checkTypeAndEquality(value, rule.second, idsValue.valueType, kMinExclusive) == OdDAI::Logical::False)
        return OdDAI::Logical::False;
      break;
    }
    case IdsValue::kMaxExclusive:
    {
      if (checkTypeAndEquality(value, rule.second, idsValue.valueType, kMaxExclusive) == OdDAI::Logical::False)
        return OdDAI::Logical::False;
      break;
    }
    case IdsValue::kLength:
    {
      int length;
      rule.second >> length;
      if (value.toString().getLength() != length)
        return OdDAI::Logical::False;
      break;
    }
    case IdsValue::kMinLength:
    {
      int length;
      rule.second >> length;
      if (value.toString().getLength() < length)
        return OdDAI::Logical::False;
      break;
    }
    case IdsValue::kMaxLength:
    {
      int length;
      rule.second >> length;
      if (value.toString().getLength() > length)
        return OdDAI::Logical::False;
      break;
    }
    case IdsValue::kTotalDigits:
    {
      int length;
      rule.second >> length;
      OdString  strVal = value.toString();
      if (strVal.find('.') >= 0)
        ++length;
      if (value.toString().getLength() != length)
        return OdDAI::Logical::False;
      break;
    }
    case IdsValue::kFractionDigits:
    {
      int length;
      rule.second >> length;
      OdString  strVal = value.toString();
      int pointPos = strVal.find('.');
      int valLength = 0;
      if (pointPos >= 0)
        valLength = value.toString().getLength() - pointPos - 1;
      if (valLength != length)
        return OdDAI::Logical::False;
      break;
    }
    case IdsValue::kRegExp:
    {
      OdAnsiString strVal;
      OdAnsiString regExpAnsi;
      value >> strVal;
      rule.second >> regExpAnsi;

      std::regex regExp(regExpAnsi);
      if (!std::regex_match(strVal.c_str(), regExp))
        return OdDAI::Logical::False;
      break;
    }
    default:
      break;
    }
  }

  return OdDAI::Logical::True;
}

OdDAI::Logical IdsOptionsChecker::fullCheckIds(OdDAI::ApplicationInstance* pInstance, IdsOptions* option)
{
  if (checkIdsEntity(pInstance, option->entity) == OdDAI::Logical::False)
    return OdDAI::Logical::False;
  if (checkIdsClassification(pInstance, option->classification) == OdDAI::Logical::False)
    return OdDAI::Logical::False;
  if (checkIdsProperties(pInstance, option->property) == OdDAI::Logical::False)
    return OdDAI::Logical::False;
  if (checkIdsMaterial(pInstance, option->material) == OdDAI::Logical::False)
    return OdDAI::Logical::False;
  return OdDAI::Logical::True;
}

OdDAI::Logical IdsOptionsChecker::checkIdsEntity(OdDAI::ApplicationInstance* pInstance, IdsEntity* pEntity)
{
  if (pEntity)
  {
    if (!pEntity->name.value.empty() && !checkIdsValue(pInstance->getInstanceType()->originalName(), pEntity->name))
    {
      return OdDAI::Logical::False;
    }

    if (!pEntity->predefinedType.value.empty())
    {
      OdRxValue predefinedtypeRxValue;
      if (pInstance->testAttr("predefinedtype"))
      {
        predefinedtypeRxValue = pInstance->getAttr("predefinedtype");
      }
      else
        return OdDAI::Logical::False;
      
      if (!checkIdsValue(predefinedtypeRxValue, pEntity->predefinedType))
      {
        if (m_isValidation)
        {
          OdDAI::AttributePtr attr = pInstance->getInstanceType()->findAttribute("predefinedtype");
          m_invalidParams->addData(pInstance, attr, pEntity->instructions);
        }
        return OdDAI::Logical::False;
      }
    }
  }
  return OdDAI::Logical::True;
}

OdDAI::Logical IdsOptionsChecker::checkIdsClassification(OdDAI::ApplicationInstance* pInstance, IdsClassification* pClassification)
{
  if (pClassification)
  {
    OdRxValue instancesAssociations = pInstance->getInverseAttr("hasassociations");
    if (!instancesAssociations.isEmpty())
    {
      OdDAIObjectIds instanceAssociationsIds;
      instancesAssociations >> instanceAssociationsIds;
      for (auto it : instanceAssociationsIds)
      {
        if (it.getNested()->typeName() == "ifcrelassociatesclassification")
        {
          OdDAI::ApplicationInstancePtr instanceDefinesByProperties = it.getNested();
          OdRxValue relatedObject = instanceDefinesByProperties->getAttr("relatingclassification");
          OdDAI::Select* relatedObjectsSelect;
          relatedObject >> relatedObjectsSelect;

          OdDAI::ApplicationInstancePtr classificationInstance;
          if (relatedObjectsSelect->underlyingTypeName() == "ifcclassificationreference")
          {
            OdDAIObjectId classificationRefId;
            relatedObjectsSelect->getHandle(classificationRefId);
            if (classificationRefId.getNested()->testAttr("referencedsource"))
            {
              OdRxValue classificationRx = classificationRefId.getNested()->getAttr("referencedsource");
              OdDAIObjectId classificationInstanceId;
              classificationRx >> classificationInstanceId;
              classificationInstance = classificationInstanceId.getNested();
            }
          }
          else if (relatedObjectsSelect->underlyingTypeName() == "ifcclassification")
          {
            OdDAIObjectId classificationId;
            relatedObjectsSelect->getHandle(classificationId);
            if (classificationId.isValid())
            {
              classificationInstance = classificationId.getNested();
            }
          }
          if (!classificationInstance.isNull())
          {
            OdDAI::Logical validationResult = OdDAI::Logical::True;
            if (!pClassification->system.value.empty())
            {
              OdRxValue classificationNameRx = classificationInstance->getAttr("name");
              if (!checkIdsValue(classificationNameRx, pClassification->system))
              {
                validationResult = OdDAI::Logical::False;

                OdDAI::AttributePtr attr = classificationInstance->getInstanceType()->findAttribute("name");
                m_invalidParams->addData(classificationInstance, attr, pClassification->instructions);
              }
            }
              
            if (!pClassification->value.value.empty())
            {
              OdRxValue classificationEditionRx = classificationInstance->getAttr("edition");
              if (!checkIdsValue(classificationEditionRx, pClassification->value))
              {
                validationResult = OdDAI::Logical::False;

                if (m_isValidation && m_invalidParams)
                {
                  OdDAI::AttributePtr attr = classificationInstance->getInstanceType()->findAttribute("name");
                  m_invalidParams->addData(classificationInstance, attr, pClassification->instructions);
                }
              }
            }

            return validationResult;
          }
        }
      }
    }
    if (pClassification->use != kOptional)
    {
      if (m_isValidation && m_invalidParams)
      {
        m_invalidParams->addData(nullptr, nullptr, "Can't find classification instance");
      }

      return OdDAI::Logical::False;
    }
  }
  return OdDAI::Logical::True;
}

bool IdsOptionsChecker::compareSelectValue(OdDAI::Select* select, const IdsValue& value)
{
  if (select->exists())
  {
    switch (select->kind())
    {
    case tkLong:
    {
      int intVal;
      select->getInt32(intVal);
      return (checkIdsValue(intVal, value) == OdDAI::Logical::True);
    }
    case tkDouble:
    {
      double dblVal;
      select->getDouble(dblVal);
      return (checkIdsValue(dblVal, value) == OdDAI::Logical::True);
    }
/*    case tkBoolean:
    {
      OdDAI::Boolean boolVal;
      select->getBoolean(boolVal);
      if (boolVal == OdDAI::Boolean::False && value == ".F.")
        return true;
      if (boolVal == OdDAI::Boolean::True && value == ".T.")
        return true;
      if (boolVal == OdDAI::Boolean::Unset && value.isEmpty())
        return true;
      return false;
    }*/
    case tkString:
    {
      OdAnsiString strVal;
      select->getString(strVal);
      return (checkIdsValue(strVal, value) == OdDAI::Logical::True);
    }
    case tkObjectId:
    {
      OdDAIObjectId id;
      select->getHandle(id);
      return (checkIdsValue(id, value) == OdDAI::Logical::True);
    }
    default:
      ODA_ASSERT(0 && "New case should be appended!");
    }
  }
  return false;
}

OdDAI::Logical IdsOptionsChecker::checkIdsPropertyAttribute(OdDAI::ApplicationInstance* pInstance, const IdsProperty& property)
{
  OdDAI::EntityPtr pEntity = pInstance->getInstanceType();
  bool isChecked = false;
  if (checkIdsEntityAttribute(pInstance, pEntity, property, isChecked) == OdDAI::Logical::False)
    return OdDAI::Logical::False;

  if (!isChecked && property.use != kOptional)
  {
    if (m_isValidation && m_invalidParams)
    {
      m_invalidParams->addData(nullptr, nullptr, "Can't find attribute");
    }
    return OdDAI::Logical::False;
  }
  return OdDAI::Logical::True;
}

OdDAI::Logical OdIds::IdsOptionsChecker::checkIdsEntityAttribute(OdDAI::ApplicationInstance* pInstance, OdDAI::Entity* pEntity, const IdsProperty& property, bool& isChecked)
{
  const OdArray<OdDAI::AttributePtr>& instanceAttrs = pEntity->attributes().getArray();
  
  for (const auto& attr : instanceAttrs)
  {
    if (checkIdsValue(attr->originalName(), property.name))
    {
      if (pInstance->testAttr(attr->name()))
      {
        OdRxValue valueRx = pInstance->getAttr(attr->name());

        if (!checkIdsValue(valueRx, property.value))
        {
          if (m_isValidation && m_invalidParams)
          {
            OdDAI::AttributePtr attrError = pInstance->getInstanceType()->findAttribute(attr->name());
            m_invalidParams->addData(nullptr, attrError, property.instructions);
          }
          return OdDAI::Logical::False;
        }
        isChecked = true;
      }
    }
  }

  const OdDAI::List<OdDAI::Entity*>& supertypes = pEntity->supertypes();
  if (!supertypes.isNil())
  {
    const OdArray<OdDAI::Entity*>& supertypesArray = supertypes.getArray();
    for (const auto& supertype : supertypesArray)
    {
      if (checkIdsEntityAttribute(pInstance, supertype, property, isChecked) == OdDAI::Logical::False)
        return OdDAI::Logical::False;
    }
  }
  return OdDAI::Logical::True;
}

OdDAI::Logical IdsOptionsChecker::findPropertyForCheck(const OdRxValue& instancesDefinedBy, const IdsProperty& property)
{
  OdDAIObjectIds instanceDefinedByIds;
  instancesDefinedBy >> instanceDefinedByIds;
  for (auto it : instanceDefinedByIds)
  {
    if (it.getNested()->typeName() == "ifcreldefinesbyproperties")
    {
      OdDAI::ApplicationInstancePtr instanceDefinesByProperties = it.getNested();
      OdRxValue relatedObject = instanceDefinesByProperties->getAttr("relatingpropertydefinition");
      OdDAIObjectId relatedObjectsId;
      relatedObject >> relatedObjectsId;
      if (relatedObjectsId.getNested()->typeName() == "ifcpropertyset")
      {
        OdDAI::ApplicationInstancePtr prorertySet = relatedObjectsId.getNested();
        if (prorertySet->testAttr("name"))
        {
          OdRxValue propertyNameRx = prorertySet->getAttr("name");

          if (checkIdsValue(propertyNameRx, property.propertySetName))
          {
            return cheskPropertySet(prorertySet, property);
          }
        }
      }
    }
  }
  if (property.use == kOptional)
    return OdDAI::Logical::True;

  if (m_isValidation && m_invalidParams)
  {
    m_invalidParams->addData(nullptr, nullptr, "Can't find property for validation");
  }
  return OdDAI::Logical::False;
}

OdDAI::Logical IdsOptionsChecker::cheskPropertySet(OdDAI::ApplicationInstance* propertySet, const IdsProperty& property)
{
  OdDAI::Logical validationResult = OdDAI::Logical::True;
  OdRxValue propertiesInst = propertySet->getAttr("hasproperties");
  OdDAIObjectIds propertiesIds;
  propertiesInst >> propertiesIds;
  for (auto checkProperty : propertiesIds)
  {
    OdDAI::ApplicationInstancePtr propertyInstance = checkProperty.getNested();

    OdRxValue nameRx = propertyInstance->getAttr("name");
    if (checkIdsValue(nameRx, property.name))
    {
      OdRxValue valueRx = propertyInstance->getAttr("nominalvalue");
      OdDAI::Select* select;
      valueRx >> select;
      if (compareSelectValue(select, property.value))
        return OdDAI::Logical::True;

      if (m_isValidation && m_invalidParams)
      {
        OdDAI::AttributePtr attr = propertyInstance->getInstanceType()->findAttribute("nominalvalue");
        m_invalidParams->addData(propertyInstance, attr, property.instructions);
      }
      return OdDAI::Logical::False;
    }
  }
  if (property.use == kOptional)
    return OdDAI::Logical::True;

  if (m_isValidation && m_invalidParams)
  {
    OdDAI::AttributePtr attr = propertySet->getInstanceType()->findAttribute("hasproperties");
    m_invalidParams->addData(propertySet, attr, "Can't find property for validation");
  }
  validationResult = OdDAI::Logical::False;
}

OdDAI::Logical IdsOptionsChecker::checkIdsProperties(OdDAI::ApplicationInstance* pInstance, const OdArray<IdsProperty>& properties)
{
  OdDAI::Logical validationResult = OdDAI::Logical::True;
  if (properties.size() > 0)
  {
    OdRxValue instancesDefinedBy = pInstance->getInverseAttr("isdefinedby");
    for (const auto& prop : properties)
    {
      if (checkIdsValue(OdAnsiString("attribute"), prop.propertySetName))
      {
        if (checkIdsPropertyAttribute(pInstance, prop) == OdDAI::Logical::False && validationResult == OdDAI::Logical::True)
          validationResult = OdDAI::Logical::False;
      }
      else
      {
        if (!instancesDefinedBy.isEmpty())
        {
          if (findPropertyForCheck(instancesDefinedBy, prop) == OdDAI::Logical::False && validationResult == OdDAI::Logical::True)
            validationResult = OdDAI::Logical::False;
        }
        else if (prop.use != kOptional)
        {
          if (m_isValidation && m_invalidParams)
          {
            m_invalidParams->addData(nullptr, nullptr, "Can't find instancesDefinedBy in instance");
          }
          validationResult = OdDAI::Logical::False;
        }
      }
    }
  }
   return validationResult;
}

OdDAI::Logical IdsOptionsChecker::checkIdsMaterial(OdDAI::ApplicationInstance* pInstance, IdsMaterial* pMaterial)
{
  if (pMaterial)
  {
    OdRxValue instancesAssociations = pInstance->getInverseAttr("hasassociations");
    if (!instancesAssociations.isEmpty())
    {
      OdDAIObjectIds instanceAssociationsIds;
      instancesAssociations >> instanceAssociationsIds;
      for (auto it : instanceAssociationsIds)
      {
        if (it.getNested()->typeName() == "ifcrelassociatesmaterial")
        {
          OdDAI::ApplicationInstancePtr instanceDefinesByProperties = it.getNested();
          OdRxValue relatedObject = instanceDefinesByProperties->getAttr("relatingmaterial");
          OdDAI::Select* relatedObjectsSelect;
          relatedObject >> relatedObjectsSelect;
          OdAnsiString ss = relatedObjectsSelect->underlyingTypeName();
          OdDAIObjectId materialId;
          if (relatedObjectsSelect->underlyingTypeName() == "ifcmaterial")
          {
            relatedObjectsSelect->getHandle(materialId);
          }
          else if (relatedObjectsSelect->underlyingTypeName() == "ifcmateriallayer")
          {
            OdDAIObjectId materialLayerId;
            relatedObjectsSelect->getHandle(materialLayerId);
            OdDAI::ApplicationInstancePtr materialLayer = materialLayerId.getNested();
            if (materialLayer->testAttr("material"))
            {
              OdRxValue materialIdRx = materialLayer->getAttr("material");
              materialIdRx >> materialId;
            }
          }

          if (materialId.isValid())
          {
            OdDAI::ApplicationInstancePtr materialInstance = materialId.getNested();
            OdRxValue materialNameRx = materialInstance->getAttr("name");
            if (checkIdsValue(materialNameRx, pMaterial->value))
              return OdDAI::Logical::True;
            else
            {
              if (m_isValidation && m_invalidParams)
              {
                OdDAI::AttributePtr attr = materialInstance->getInstanceType()->findAttribute("name");
                m_invalidParams->addData(materialInstance, attr, pMaterial->instructions);
                return OdDAI::Logical::False;
              }
            }
          }
        }
      }
    }
    if (pMaterial->use != kOptional)
    {
      if (m_isValidation && m_invalidParams)
      {
        m_invalidParams->addData(nullptr, nullptr, "Can't find material instance");
      }
      return OdDAI::Logical::False;
    }
  }
  return OdDAI::Logical::True;
}
