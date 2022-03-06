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

#ifndef  _DAI_MODEL_VALIDATION_HEALER_H
#define _DAI_MODEL_VALIDATION_HEALER_H

#include "OdaCommon.h"
#include "daiBuildOptions.h"
#include "RxObject.h"
#include "daiLogicalType.h"
#include "daiValidationTask.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
  An abstract class which describes the interface for model validation healer.
  */
  class DAI_EXPORT ModelValidationHealer : public OdRxObject
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(ModelValidationHealer);
    //DOM-IGNORE-END
  public:
    /** \details
    Healing model and its ivalid instances.
    \param model [in] A raw pointer to the model to be healing.
    \param invalidParams [in] A pointer to the struct with invalid validation objects.
    \returns Result of healing. Returns True if healing is successful.
    */
    virtual Logical heal(OdDAI::Model* model, ValidationTask::InvalidValidationParamsBase* invalidParams) = 0;
  };
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::ModelValidationHealer, ModelValidationHealer> object.
  */
  typedef OdSmartPtr<ModelValidationHealer> ModelValidationHealerPtr;
}
#endif // _DAI_MODEL_VALIDATION_HEALER_H
