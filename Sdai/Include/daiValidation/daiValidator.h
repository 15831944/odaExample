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

#ifndef _DAI_VALIDATOR_H
#define _DAI_VALIDATOR_H

#include "OdaCommon.h"

#define STL_USING_MAP
#include "OdaSTL.h"

#include "daiModel.h"
#include "daiInstanceValidationTask.h"
#include "daiModelValidationTask.h"
#include "daiExtentValidationTask.h"
#include "daiValidationNotifier.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
  A class which implements functionality for working with validation classes.
  */
  class DAI_EXPORT Validator : public OdRxObject
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(Validator);
    //DOM-IGNORE-END

  public:
    /** \details
    Defines which validation results will be show by notifier classes.
    */
    enum PrintingResult
    {
      /**Validations with some error.*/
      kError = 0x0001,
      /**Validations with unknown result.*/
      kUnknown = 0x0002,
      /**Validations with unset result.*/
      kUnset = 0x0004,
      /**Validations without any troubles.*/
      kOk = 0x0008,

      /**Validations with any troubles.*/
      kNotOk = kError | kUnknown | kUnset,
      /**All validation results.*/
      kAll = kError | kUnknown | kUnset | kOk
    };

    /** \details
    Defines which validation types will be checked.
    */
    enum ValidationType
    {
      /**Instances validation types.*/
      kInstancesValidation = 0x0001,
      /**Model validation types.*/
      kModelValidation = 0x0002,
      /**Extents validation types.*/
      kExtentsValidation = 0x0004,

      /**All validation types.*/
      kFullValidation = kInstancesValidation | kModelValidation | kExtentsValidation
    };
    /**\details
    Creates a new validator definition with a specified <link OdDAI::Model, Model>.
    \param model [in] A raw pointer to the model for validation.
    \returns A smart pointer to the created validator.
    */
    static OdSmartPtr<Validator> createObject(OdDAI::Model* model);

    /**\details
    Creates a new validator with default parameters.
    */
    Validator();

    /** \details
    Sets a new <link OdDAI::Model, Model> for the validator class.
    \param model [in] A raw pointer to the model for validation.
    */
    void setModel(OdDAI::Model* model);
    /** \details
    Sets a new progress meter for the validator class.
    \param progressMeter [in] A raw pointer to the progress meter class definition.
    */
    void setProgressMeter(OdDbHostAppProgressMeter* progressMeter);
    /** \details
    Sets type of validation result which will be show by notifier classe.
    \param printingResult [in] Type of validation result.
    */
    void setPrintingResult(PrintingResult printingResult);

    /** \details
    Sets the list of instance validation tasks for validation.
    \param tasksList [in] The list of smart pointers to the <link OdDAI::InstanceValidationTask, InstanceValidationTask> class.
    */
    void setInstanceTasks(std::list<InstanceValidationTaskPtr> tasksList);
    /** \details
    Adds instanse validation task to list of validation tasks.
    \param task [in] A raw pointer to the instance validation task.
    */
    void addInstanceTask(InstanceValidationTask* task);
    /** \details
    Removes all instance validation tasks.
    */
    void clearInstanceTasks();
    /** \details
    Retrieves the count of instance validation tasks in validator.
    \returns An integer that contains the count of instance validation tasks in validaator.
    */
    int instanceTasksCount();

    /** \details
    Sets the list of model validation tasks for validation.
    \param tasksList [in] The list of smart pointers to the <link OdDAI::ModelValidationTask, ModelValidationTask> class.
    */
    void setModelTasks(std::list<ModelValidationTaskPtr> tasksList);
    /** \details
    Adds model validation task to list of validation tasks.
    \param task [in] A raw pointer to the model validation task.
    */
    void addModelTask(ModelValidationTask* task);
    /** \details
    Removes all model validation tasks.
    */
    void clearModelTasks();
    /** \details
    Retrieves the count of model validation tasks in validator.
    \returns An integer that contains the count of model validation tasks in validaator.
    */
    int modelTasksCount();

    /** \details
    Sets the list of extent validation tasks for validation.
    \param tasksList [in] The list of smart pointers to the <link OdDAI::ExtentValidationTask, ExtentValidationTask> class.
    */
    void setExtentTasks(std::list<ExtentValidationTaskPtr> tasksList);
    /** \details
    Adds extent validation task to list of validation tasks.
    \param task [in] A raw pointer to the extent validation task.
    */
    void addExtentTask(ExtentValidationTask* task);
    /** \details
    Removes all extent validation tasks.
    */
    void clearExtentTasks();
    /** \details
    Retrieves the count of extent validation tasks in validator.
    \returns An integer that contains the count of extent validation tasks in validaator.
    */
    int extentTasksCount();

    /** \details
    Adds instance, extent or model validation task to tasks list.
    \param task [in] A raw pointer to the validation task.
    */
    void addValidationTask(ValidationTask* task);
    /** \details
    Removes all instance and model validation tasks.
    */
    void clearValidationTasks();

    /** \details
    Sets the list of model validation notifiers.
    \param tasksList [in] The list of smart pointers to the <link OdDAI::ValidationNotifier, ValidationNotifier> class.
    */
    void setNotifiers(std::list<ValidationNotifierPtr> tasksList);
    /** \details
    Adds model validation notifier to list of notifiers.
    \param task [in] A raw pointer to the validation notifier.
    */
    void addNotifier(ValidationNotifier* task);
    /** \details
    Removes all notifiers.
    */
    void clearNotifiers();

    /** \details
    Sets <OdDAI::ValidationType, validation types> which will be checked on run.
    \param validationType [in] List of validation types.
    */
    void setValidationType(ValidationType validationType);
    /** \details
    Starts execution of validation tasks which assigned to validator.
    */
    void run();

    /** \details
    Retrieves is validation errors healing enable.
    \returns True if healing enable; otherwise False.
    */
    bool isHealingEnable();
    /** \details
    Sets the healing errors after validation.
    \param healingEnable [in] A boolean that switch healing.
    */
    void setHealingEnable(bool healingEnable);

    /** \details
    Sets new validation context for all instances and extents validations.
    \param pInstanceCtx [in] Shared pointer to the new instance context.
    */
    void setInstanceContext(OdBaseInstanceValidationContextPtr pInstanceCtx);
    /** \details
    Sets new validation context for all model validations.
    \param pInstanceCtx [in] Shared pointer to the new model context.
    */
    void setModelContext(OdBaseModelValidationContextPtr pModelCtx);
  private:

    void modelValidation();
    void instancesValidation();
    void extentsValidation();

    OdDAI::ModelPtr m_model;
    OdDbHostAppProgressMeter* m_progressMeter;
    bool m_healingEnable;

    ValidationType m_validationType;
    std::set<OdDAI::Logical> m_printingResults;
    std::list<InstanceValidationTaskPtr> m_instanceValidationTasks;
    std::list<ModelValidationTaskPtr> m_modelValidationTasks;
    std::map<OdAnsiString, std::list<ExtentValidationTaskPtr> > m_extentValidationTask;
    std::list<ValidationNotifierPtr> m_validationNotifiers;
    OdBaseInstanceValidationContextPtr m_pInstanceCtx;
    OdBaseModelValidationContextPtr m_pModelCtx;
  };
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::Validator, Validator> object.
  */
  typedef OdSmartPtr<Validator> ValidatorPtr;
}

#endif // _DAI_VALIDATOR_H
