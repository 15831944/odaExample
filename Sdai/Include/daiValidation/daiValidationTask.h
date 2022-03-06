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

#ifndef  _DAI_VALIDATION_TASK_H
#define _DAI_VALIDATION_TASK_H

#include "OdaCommon.h"
#include "daiBuildOptions.h"
#include "RxObject.h"
#include "daiAttribute.h"
#include "daiRules/daiWhereRule.h"

class ApplicationInstance;
class Model;

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
  The base struct which contains validation context for instances and extents validations.
  */
  struct OdBaseInstanceValidationContext
  {
    /**A pointer to the ApplicationInstance for validation task.*/
    OdDAI::ApplicationInstance* pInstance;

    /** \details
    Struct constructor.
    */
    OdBaseInstanceValidationContext() {}
    /** \details
    Struct constructor.
    \param _pInstance [in] A raw pointer to <link OdDAI::ApplicationInstance, ApplicationInstance> object.
    */
    OdBaseInstanceValidationContext(OdDAI::ApplicationInstance* _pInstance):pInstance(_pInstance) {}
    /** \details
    Struct virtual destructor.
    */
    virtual ~OdBaseInstanceValidationContext() {}
  };

  /** \details
  The base struct which contains validation context for model validations.
  */
  struct OdBaseModelValidationContext
  {
    /**A pointer to the Model for validation task.*/
    OdDAI::Model* pModel;

    /** \details
    Struct constructor.
    \param _pModel [in] A raw pointer to <link OdDAI::Model, Model> object which used for validation.
    */
    OdBaseModelValidationContext(OdDAI::Model* _pModel) :pModel(_pModel) {}
    /** \details
    Struct virtual destructor.
    */
    virtual ~OdBaseModelValidationContext() {}
  };
  /** \details
  A data type that represents a shared pointer to an <link OdDAI::OdBaseInstanceValidationContext, OdBaseInstanceValidationContext> object.
  */
  typedef OdSharedPtr<OdBaseInstanceValidationContext> OdBaseInstanceValidationContextPtr;
  /** \details
  A data type that represents a shared pointer to an <link OdDAI::OdBaseModelValidationContext, OdBaseModelValidationContext> object.
  */
  typedef OdSharedPtr<OdBaseModelValidationContext> OdBaseModelValidationContextPtr;

  /** \details
  An abstract class which describes the interface for validation tasks.
  */
  class DAI_EXPORT ValidationTask : public OdRxObject
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(ValidationTask);
    //DOM-IGNORE-END

  public:
    /** \details
    The base struct which contains problem classes and some information about validation issues.
    */
    struct InvalidValidationParamsBase
    {
      /** \details
      Struct virtual destructor.
      */
      virtual ~InvalidValidationParamsBase() {};
      /** \details
      Retrieves the count of invalid items in struct.
      \returns An integer value that represents the count of invalid items in the struct.
      */
      virtual int invalidItemsCount() = 0;
    };
    /** \details
    The struct which contains an arrays of attributes and WR with validation problems.
    */
    struct InvalidValidationParams : InvalidValidationParamsBase
    {
      /**An array of pointers to Attribute instances.*/
      OdArray<Attribute*> invalidAttributes;
      /**An array of pointers to WhereRule instances.*/
      OdArray<WhereRule*> invalidWhereRules;
      /** \details
      Retrieves the count of invalid items in struct.
      \returns An integer value that represents the count of invalid items in the struct.
      */
      virtual int invalidItemsCount() override { return invalidAttributes.size(); }
    };
    /** \details
    The struct which contains an arrays of instances, attributes and some text with validation problems.
    */
    struct InvalidInstanceValidationParams : InvalidValidationParamsBase
    {
      /** \details
      The auxiliary struct which contains informational data received during validation task execution.
      */
      struct InvalidParams
      {
        /**A pointer to the ApplicationInstance.*/
        OdDAI::ApplicationInstance* invalidInstance;
        /**A pointer to the Attribute.*/
        OdDAI::Attribute* invalidAttribute;
        /**A text with some information.*/
        OdAnsiString instruction;
      };
      /**An array of pointers to InvalidParams.*/
      OdArray<InvalidParams> invalidParams;

      /**Adds new items to struct.*/
      void addData(OdDAI::ApplicationInstance* inst, OdDAI::Attribute* attr, const OdAnsiString& instr)
      {
        invalidParams.push_back(InvalidParams({ inst, attr, instr }));
      }
      /** \details
      Retrieves the count of invalid items in struct.
      \returns An integer value that represents the count of invalid items in the struct.
      */
      virtual int invalidItemsCount() override { return invalidParams.size(); }
    };

    /** \details
    The struct which contains an array of pointers to OdRxObject instances with validation problems.
    */
    struct InvalidRxObjectsValidationParams : InvalidValidationParamsBase
    {
      /**An array to the OdRxObject instances which may contain <OdDAI::ApplicalionInstance, ApplicalionInstance> class instance, <OdDAI::WhereRule, WhereRule> class instance, <OdDAI::Select, Select> class instance or something else.*/
      OdRxObjectPtrArray invalidObjects;
      /**A text with some information.*/
      OdAnsiString textMessage;
      /**Result of validation.*/
      OdDAI::Logical validationResult;

      /** \details
      Struct constructor.
      \param objects [in] Initializer list with smart pointers to invalid objects.
      \param message [in] Some text information about invalid objects or validation task.
      \param result  [in] Result of validation.
      */
      InvalidRxObjectsValidationParams(std::initializer_list<OdRxObjectPtr> objects, const OdAnsiString& message, OdDAI::Logical result) :textMessage(message), validationResult(result)
      {
        invalidObjects.reserve((unsigned int)objects.size());
        for (auto obj : objects)
          invalidObjects.push_back(obj);
      }

      /** \details
      Retrieves the count of invalid items in struct.
      \returns An integer value that represents the count of invalid items in the struct.
      */
      virtual int invalidItemsCount() override { return invalidObjects.size(); }
    };
    /** \details
    The struct which contains an array with information about several validation results.
    */
    struct InvalidRxArrayValidationParams : InvalidValidationParamsBase
    {
      /**An array of validation results.*/
      OdArray<InvalidRxObjectsValidationParams> invalidParams;

      /** \details
      Adds new validation items to struct.
      \param invalidObjects [in] Struct with some validation result.
      */
      void addData(const InvalidRxObjectsValidationParams& invalidObjects)
      {
        invalidParams.push_back(invalidObjects);
      }

      /** \details
      Retrieves the count of invalid items in struct.
      \returns An integer value that represents the count of invalid items in the struct.
      */
      virtual int invalidItemsCount() override { return invalidParams.size(); }
    };

    /** \details
    The struct which contains an array of object ids with validation problems.
    */
    struct InvalidObjectIdsValidationParams : InvalidValidationParamsBase
    {
      /**An array of objects id.*/
      OdDAIObjectIds invalidObjects;

      /** \details
      Default struct constructor.
      */
      InvalidObjectIdsValidationParams() {}
      /** \details
      Struct constructor.
      \param _invalidObjects [in] Array of object ids.
      */
      InvalidObjectIdsValidationParams(OdDAIObjectIds _invalidObjects) : invalidObjects(_invalidObjects) {}

      /** \details
      Adds invalid object id into the struct.
      \param id [in] Invalid object id.
      */
      void addData(OdDAIObjectId id)
      {
        invalidObjects.push_back(id);
      }

      /** \details
      Retrieves the count of invalid items in struct.
      \returns An integer value that represents the count of invalid objects in the struct.
      */
      virtual int invalidItemsCount() override { return invalidObjects.size(); }
    };

    /** \details
    Class constructor.
    */
    ValidationTask();

    /** \details
    Class virtual destructor.
    */
    virtual ~ValidationTask();

    /** \details
    Virtual function which is called by Validator before validation process starts.
    \param invalidParams [out] A struct which contains elements with validation problems.
    \returns OdDAI::Logical::True (by default) if validation initialization is successful; returns OdDAI::Logical::False if validation initialization failed; otherwise returns OdDAI::Logical::Unknown.
    */
    virtual OdDAI::Logical initializeValidation(OdSharedPtr<InvalidValidationParamsBase>& invalidParams);
    /** \details
    Virtual function which is called by Validator after validation process ends.
    \param invalidParams [out] A struct which contains elements with validation problems.
    \returns OdDAI::Logical::True (by default) if validation finish is successful; returns OdDAI::Logical::False if validation finish failed; otherwise returns OdDAI::Logical::Unknown.
    */
    virtual OdDAI::Logical finishValidation(OdSharedPtr<InvalidValidationParamsBase>& invalidParams);
    /** \details
    Retrieves the description of validation task.
    \returns An ANSI string that contains the description of validation task.
    */
    virtual OdAnsiString description() const = 0;

    /** \details
    Retrieves some additional information about the validation task (date, author, copyright, version, etc).
    \returns A pointer to Map that contains additional information in pair of ANSI strings where fist is name of this data and second is it description.
    */
    virtual const std::map<OdAnsiString, OdAnsiString>* additionalInformation() const;
    /** \details
    Retrieves that class try to heal validation errors (if it has healer class).
    \returns True if class try to heal validation errors; otherwise False.
    */
    bool isHealingEnable();
    /** \details
    Sets the healing errors after validation.
    \param healingEnable [in] A boolean that switch healing.
    */
    void setHealingEnable(bool healingEnable);

  protected:
    bool m_healingEnable;
  };
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::ValidationTask, ValidationTask> object.
  */
  typedef OdSmartPtr<ValidationTask> ValidationTaskPtr;
}

#endif //_DAI_VALIDATION_TASK_H
