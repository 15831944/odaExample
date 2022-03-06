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

#ifndef  _DAI_INVERSE_ATTRS_VALIDATION_TASK_H
#define _DAI_INVERSE_ATTRS_VALIDATION_TASK_H

#include "OdaCommon.h"

#include "daiInstanceValidationTask.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
  A class which validates the inverse attributes of the instance.
  */
  class DAI_EXPORT InverseAttrsValidationTask : public InstanceValidationTask
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(InverseAttrsValidationTask);
    //DOM-IGNORE-END

  public:
    /** \details
    Checks whether the instance has inverse attributes with unsatisfied size constraints and retrieves the list of such attributes.
    \param pInstanceCtx [in] A raw pointer to the validation context with validate entity instance.
    \param invalidParams [out] The struct with an array of pointers to Attribute instances which have unsatisfied size constraints for the application instance.
    \returns True if all inverse attributes constraints are satisfied or if the instance has no inverse attributes; otherwise, the method returns False.
    */
    virtual OdDAI::Logical validate(OdDAI::OdBaseInstanceValidationContext* pInstanceCtx, OdSharedPtr<InvalidValidationParamsBase>& invalidParams) override;
    /** \details
    Retrieves the description of validation task.
    \returns An ANSI string that contains the description of validation task.
    */
    virtual OdAnsiString description() const override;
  };
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::InverseAttrsValidationTask, InverseAttrsValidationTask> object.
  */
  typedef OdSmartPtr<InverseAttrsValidationTask> InverseAttrsValidationTaskPtr;
}

#endif //_DAI_INVERSE_ATTRS_VALIDATION_TASK_H
