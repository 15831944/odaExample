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

#ifndef  _DAI_MODEL_VALIDATION_TASK_H
#define _DAI_MODEL_VALIDATION_TASK_H

#include "OdaCommon.h"
#include "daiValidationTask.h"
#include "daiModel.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
  The base class for whole model validation tasks.
  */
  class DAI_EXPORT ModelValidationTask : public ValidationTask
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(ModelValidationTask);
    //DOM-IGNORE-END

  public:
    /** \details
    Checks model by some rules and retrieves the list of instances which are not satisfying them.
    \param pModelCtx [in] A raw pointer to the validation context with validate model.
    \param invalidParams [out] A struct with invalid validation objects.
    \returns Result of validation.
    */
    virtual Logical validate(OdDAI::OdBaseModelValidationContext* pModelCtx, OdSharedPtr<InvalidValidationParamsBase>& invalidParams) = 0;
  };
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::ModelValidationTask, ModelValidationTask> object.
  */
  typedef OdSmartPtr<ModelValidationTask> ModelValidationTaskPtr;
}

#endif //_DAI_MODEL_VALIDATION_TASK_H
