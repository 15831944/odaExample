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

#ifndef  _DAI_SESSION_VALIDATION_NOTIFIER_H
#define _DAI_SESSION_VALIDATION_NOTIFIER_H

#include "OdaCommon.h"
#include "daiValidationNotifier.h"
#include "daiSession.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
  A class which notifies validation tasks information to the <link OdDAI::Session, Session> class.
  */
  class DAI_EXPORT SessionValidationNotifier : public ValidationNotifier
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(SessionValidationNotifier);
    //DOM-IGNORE-END

  public:
    /**\details
    Creates a new SessionValidationNotifier definition with a specified <link OdDAI::Session, Session>.
    \param model [in] A raw pointer to the <link OdDAI::Session, Session> class.
    \returns A smart pointer to the created notifier.
    */
    static OdSmartPtr<SessionValidationNotifier> createObject(Session* session);

    /** \details
    Notifies some validation information to the <link OdDAI::Session, Session> class.
    \param instanceId [in] <link OdDAIObjectId, OdDAI object identifier> of the entity instance.
    \param validationTask [in] A smart pointer to validation class definition.
    \param invalidParams [in] The struct with arrays of pointers to instances with validation problems.
    \param result [in] Result of validation.
    */
    virtual void onValidationResult(OdDAIObjectId instanceId, ValidationTaskPtr validationTask, OdSharedPtr<ValidationTask::InvalidValidationParamsBase> invalidParams, Logical result);
    /** \details
    Notifies some validation information to the <link OdDAI::Session, Session> class.
    \param validationTask [in] A smart pointer to validation class definition.
    \param invalidObjects [in] An array of <link OdDAIObjectId, OdDAI object identifiers> of the entity instances with validation problems.
    \param result [in] Result of validation.
    */
    virtual void onValidationResult(ValidationTaskPtr validationTask, const OdDAIObjectIds& invalidObjects, Logical result);

    /** \details
    Sets a new <link OdDAI::Session, Session> for the notifier class.
    \param model [in] A raw pointer to the session.
    */
    void setSession(Session* session);
  private:
    SessionPtr m_session;

  };
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::ValidationNotifier, ValidationNotifier> object.
  */
  typedef OdSmartPtr<SessionValidationNotifier> SessionValidationNotifierPtr;
}
#endif //_DAI_SESSION_VALIDATION_NOTIFIER_H
