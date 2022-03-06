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

#include "IdsInstanceValidationTask.h"

#define IDS_EXTENT_VALIDATION_TASK_DESC "Instance validation according IDS requirements"

using namespace OdIds;

ODRX_CONS_DEFINE_MEMBERS(IdsInstanceValidationTask, OdDAI::InstanceValidationTask, RXIMPL_CONSTR);

OdIds::IdsInstanceValidationTask::IdsInstanceValidationTask() : InstanceValidationTask()
{
}

OdDAI::Logical OdIds::IdsInstanceValidationTask::initializeValidation(OdSharedPtr<InvalidValidationParamsBase>& invalidParams)
{
  if (m_specificationOptions->necessity == OdIds::kRequired)
    m_validationsCounter = 0;
  return OdDAI::Logical::True;
}

OdDAI::Logical OdIds::IdsInstanceValidationTask::finishValidation(OdSharedPtr<InvalidValidationParamsBase>& invalidParams)
{
  if (m_specificationOptions->necessity == OdIds::kRequired && m_validationsCounter == 0)
  {
    InvalidInstanceValidationParams* invalidInstanceParams = new OdDAI::ValidationTask::InvalidInstanceValidationParams();
    invalidParams = invalidInstanceParams;
    invalidInstanceParams->addData(nullptr, nullptr, "No validations passed the required fields");
    return OdDAI::Logical::False;
  }
  return OdDAI::Logical::True;
}

OdDAI::Logical IdsInstanceValidationTask::validate(OdDAI::OdBaseInstanceValidationContext* pInstanceCtx, OdSharedPtr<InvalidValidationParamsBase>& invalidParams)
{
  IdsOptionsChecker optionsChecker(invalidParams);

  if (optionsChecker.fullCheckIds(pInstanceCtx->pInstance, m_findOptions) == OdDAI::Logical::False)
    return OdDAI::Logical::True;

  optionsChecker.setValidationRegime(true);

  OdDAI::Logical validationResult = OdDAI::Logical::True;
  if (optionsChecker.checkIdsEntity(pInstanceCtx->pInstance, m_validationOptions->entity) == OdDAI::Logical::False)
  {
    validationResult = OdDAI::Logical::False;
  }
  if (optionsChecker.checkIdsClassification(pInstanceCtx->pInstance, m_validationOptions->classification) == OdDAI::Logical::False && validationResult == OdDAI::Logical::True)
  {
    validationResult = OdDAI::Logical::False;
  }
  if (optionsChecker.checkIdsProperties(pInstanceCtx->pInstance, m_validationOptions->property) == OdDAI::Logical::False && validationResult == OdDAI::Logical::True)
  {
    validationResult = OdDAI::Logical::False;
  }
  if (optionsChecker.checkIdsMaterial(pInstanceCtx->pInstance, m_validationOptions->material) == OdDAI::Logical::False && validationResult == OdDAI::Logical::True)
  {
    validationResult = OdDAI::Logical::False;
  }

  return validationResult;

/*  OdDAI::Logical validationResult = OdDAI::Logical::True;
  if (!m_findOptions.entity.isNull())
  {
    OdAnsiString predefinedTypeValue;
    if (pInstance->testAttr("predefinedtype"))
    {
      OdRxValue predefinedtypeRxValue = pInstance->getAttr("predefinedtype");
      predefinedtypeRxValue >> predefinedTypeValue;
    }

    if (!m_findOptions.entity->predefinedType.isEmpty() && m_findOptions.entity->predefinedType != predefinedTypeValue)
      return validationResult;
    if (!m_validationOptions.entity.isNull())
    {
      if (!m_validationOptions.entity->name.isEmpty() && pInstance->getInstanceType()->originalName() != m_validationOptions.entity->name)
      {
        validationResult = OdDAI::Logical::False;
        return validationResult;
      }

      if (!m_validationOptions.entity->predefinedType.isEmpty() && m_validationOptions.entity->predefinedType != predefinedTypeValue)
      {
        validationResult = OdDAI::Logical::False;

        OdDAI::AttributePtr attr = pInstance->getInstanceType()->findAttribute("predefinedtype");;
        invalidAttributes.push_back(attr);
        return validationResult;
      }
    }

    
          if (m_findOptions.entity->predefinedType.isEmpty() || (pInstance->testAttr("predefinedtype") && pInstance->getAttr("predefinedtype") == m_findOptions.entity->predefinedType))
          {
            if (m_validationOptions.property.size()>0)
            {
              pInstance->getInstanceType();
            }
          }
    */

//  }
//  return validationResult;
}

OdAnsiString IdsInstanceValidationTask::description() const
{
  if (m_specificationOptions->name.isEmpty())
    return IDS_EXTENT_VALIDATION_TASK_DESC;
  return m_specificationOptions->name;
}

const std::map<OdAnsiString, OdAnsiString>* OdIds::IdsInstanceValidationTask::additionalInformation() const
{
  return m_specificationOptions->fileInfo;
}

void IdsInstanceValidationTask::loadData(OdSharedPtr<IdsSpecificationOptions> idsSpecification, OdSharedPtr<IdsOptions> findOptions, OdSharedPtr<IdsOptions> validationOptions)
{
  m_findOptions = findOptions;
  m_validationOptions = validationOptions;
  m_specificationOptions = idsSpecification;
}
