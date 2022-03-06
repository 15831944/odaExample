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

#ifndef  _DAI_VALIDATION_NOTIFIER_H
#define _DAI_VALIDATION_NOTIFIER_H

#include "OdaCommon.h"
#include "daiInstanceValidationTask.h"

#include "daiApplicationInstance.h"
#include "daiObjectId.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
  A struct which stores extra information for notifier.
  */
  struct NotifierExtraInfo
  {
    /** \details
    Name of the validating file.
    */
    OdAnsiString fileName;
    /** \details
    Name of the model's underlying schema.
    */
    OdAnsiString schemaName;

    /** \details
    Default struct constructor.
    */
    NotifierExtraInfo() {}
    /** \details
    Struct constructor.
    \param _fileName   [in] Name of the validating file.
    \param _schemaType [in] Name of the model's underlying schema.
    */
    NotifierExtraInfo(const OdAnsiString& _fileName, const OdAnsiString& _schemaName) : fileName(_fileName), schemaName(_schemaName) {}
  };

  /** \details
  The base class for notifier of validation tasks.
  */
  class DAI_EXPORT ValidationNotifier : public OdRxObject
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(ValidationNotifier);
    //DOM-IGNORE-END

  public:
    /** \details
    Virtual class destructor
    */
    virtual ~ValidationNotifier();
    /** \details
    Notifies some validation information.
    \param instanceId [in] <link OdDAIObjectId, OdDAI object identifier> of the entity instance.
    \param validationTask [in] A smart pointer to validation class definition.
    \param invalidParams [in] The struct with an arrays of pointers to instances with validation problems.
    \param result [in] Result of validation.
    */
    virtual void onValidationResult(OdDAIObjectId instanceId, ValidationTaskPtr validationTask, OdSharedPtr<ValidationTask::InvalidValidationParamsBase> invalidParams, OdDAI::Logical result) = 0;
    /** \details
    Notifies some validation information.
    \param validationTask [in] A smart pointer to validation class definition.
    \param invalidObjects [in] An array of <link OdDAIObjectId, OdDAI object identifiers> of the entity instances with validation problems.
    \param result [in] Result of validation.
    */
    virtual void onValidationResult(ValidationTaskPtr validationTask, const OdDAIObjectIds& invalidObjects, OdDAI::Logical result) = 0;
    /** \details
    Notification which is called at the beginning of validation process.
    */
    virtual void onStartValidation();
    /** \details
    Notification which is called at the end of validation process.
    */
    virtual void onEndValidation();

    /** \details
    Sets a new extra information for the notifier.
    \param modelInfo [in] A raw pointer to the extra information.
    */
    void setModelInfo(NotifierExtraInfo* modelInfo);

    /** \details
    Retrieves an extra information for the notifier.
    \returns A raw pointer to an extra information for the notifier.
    */
    NotifierExtraInfo* getModelInfo();
  protected:
    OdAnsiString result2string(const OdDAI::Logical result) const;

    NotifierExtraInfo* m_extraInfo = nullptr;
  };
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::ValidationNotifier, ValidationNotifier> object.
  */
  typedef OdSmartPtr<ValidationNotifier> ValidationNotifierPtr;
}
#endif //_DAI_VALIDATION_NOTIFIER_H
