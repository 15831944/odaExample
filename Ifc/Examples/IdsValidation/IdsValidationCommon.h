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

#ifndef _IDS_VALIDATION_COMMON_H
#define _IDS_VALIDATION_COMMON_H

#include "OdaCommon.h"
#include "IdsValidationExport.h"
#include "daiValidationTask.h"
#include "SharedPtr.h"
#include "daiPrimitive.h"
#include "daiAttribute.h"

namespace OdIds
{
  using IdsFileInfo = std::map<OdAnsiString, OdAnsiString>;
  using IdsFileInfoPtr = OdSharedPtr<std::map<OdAnsiString, OdAnsiString> >;

  enum IdsUse
  {
    kOptional = 1
  };

  enum IdsNecessity
  {
    kRequired = 1
  };

  struct IdsValue
  {
    enum IdsValueType
    {
      kInteger = 1,
      kString = 2,
      kReal = 3
    };
    enum IdsValueRestructions
    {
      kNone,
      kEnumeration,
      kMinInclusive,
      kMaxInclusive,
      kMinExclusive,
      kMaxExclusive,
      kLength,
      kMinLength,
      kMaxLength,
      kTotalDigits,
      kFractionDigits,
      kRegExp,
      kWhiteSpace
    };

    enum IdsWhiteSpaces {
      kPreserve = 1,
      kReplace  = 2,
      kCollapse = 3
    };

    int valueType = kString;

    std::map<int, OdRxValue> value;
  };

  struct IdsEntity
  {
    IdsValue name;
    IdsValue predefinedType;
    OdAnsiString instructions; //???
  };

  struct IdsClassification
  {
    IdsValue system;
    IdsValue value;
    int use;
    OdAnsiString instructions;
  };

  struct IdsProperty
  {
    IdsValue name;
    IdsValue propertySetName;
    IdsValue value;
    OdAnsiString location;
    int use;
    OdAnsiString instructions;
  };

  struct IdsMaterial
  {
    IdsValue value;
    int use;
    OdAnsiString instructions;
  };

  struct IdsOptions
  {
    OdSharedPtr<IdsEntity> entity;
    OdSharedPtr<IdsClassification> classification;
    OdArray<IdsProperty> property;
    OdSharedPtr<IdsMaterial> material;
  };

  struct IdsSpecificationOptions
  {
    OdAnsiString name;
    int necessity = 0;

    IdsFileInfoPtr fileInfo;
  };

  class IdsOptionsChecker
  {
  public:
    IdsOptionsChecker(OdSharedPtr<OdDAI::ValidationTask::InvalidValidationParamsBase>& invalidAttributes);

    void setValidationRegime(bool isValidation);

    OdDAI::Logical checkIdsValue(OdRxValue value, const IdsValue& idsValue);

    OdDAI::Logical fullCheckIds(OdDAI::ApplicationInstance* pInstance, IdsOptions* option);
    OdDAI::Logical checkIdsEntity(OdDAI::ApplicationInstance* pInstance, IdsEntity* pEntity);
    OdDAI::Logical checkIdsClassification(OdDAI::ApplicationInstance* pInstance, IdsClassification* pClassification);
    OdDAI::Logical checkIdsProperties(OdDAI::ApplicationInstance* pInstance, const OdArray<IdsProperty>& properties);
    OdDAI::Logical checkIdsMaterial(OdDAI::ApplicationInstance* pInstance, IdsMaterial* pMaterial);

    IdsProperty* findIdsProperty(OdAnsiString propertySetName, const OdArray<IdsProperty>& properties);

  private:
    bool compareSelectValue(OdDAI::Select* select, const IdsValue& value);
    OdDAI::Logical checkIdsPropertyAttribute(OdDAI::ApplicationInstance* pInstance, const IdsProperty& property);
    OdDAI::Logical checkIdsEntityAttribute(OdDAI::ApplicationInstance* pInstance, OdDAI::Entity* pEntity, const IdsProperty& property, bool& isChecked);
    OdDAI::Logical findPropertyForCheck(const OdRxValue& instancesDefinedBy, const IdsProperty& property);
    OdDAI::Logical cheskPropertySet(OdDAI::ApplicationInstance* propertySet, const IdsProperty& property);

    bool m_isValidation;
    OdSharedPtr<OdDAI::ValidationTask::InvalidValidationParamsBase>& m_invalidParamsBase;
    OdDAI::ValidationTask::InvalidInstanceValidationParams* m_invalidParams;
  };
}
ODRX_DECLARE_VALUE_TYPE(OdArray<OdIds::IdsProperty>, IDS_VALIDATION_EXPORT)
#endif  //_IDS_VALIDATION_COMMON_H
