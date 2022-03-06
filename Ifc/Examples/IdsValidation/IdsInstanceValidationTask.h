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

#ifndef _IDS_INSTANCE_VALIDATION_TASK_H
#define _IDS_INSTANCE_VALIDATION_TASK_H

#include "OdaCommon.h"
#include "IdsValidationExport.h"
#include "IdsValidationCommon.h"
#include "daiInstanceValidationTask.h"

namespace OdIds
{
  class IDS_VALIDATION_EXPORT IdsInstanceValidationTask : public OdDAI::InstanceValidationTask
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(IdsInstanceValidationTask);
    //DOM-IGNORE-END

  public:
    IdsInstanceValidationTask();

    virtual OdDAI::Logical initializeValidation(OdSharedPtr<InvalidValidationParamsBase>& invalidParams) override;
    virtual OdDAI::Logical finishValidation(OdSharedPtr<InvalidValidationParamsBase>& invalidParams) override;
    /** \details
    Checks whether <link OdDAI::Model, model> class has more than one IfcProject instances.
    \param model [in] A raw pointer to the validate <link OdDAI::Model, Model> class.
    \param invalidInstances [out] An array of pointers to <link OdDAIObjectId, OdDAI object identifiers> that has IfcProject identifiers, if model class has ore than one IfcProject instance; otherwise, it's empty.
    \returns True <link OdDAI::Model, model> class has no more than one IfcProject instances; otherwise, the method returns False.
    */
    virtual OdDAI::Logical validate(OdDAI::OdBaseInstanceValidationContext* pInstanceCtx, OdSharedPtr<InvalidValidationParamsBase>& invalidParams) override;
    /** \details
    Retrieves the description of validation task.
    \returns An ANSI string that contains the description of validation task.
    */
    virtual OdAnsiString description() const override;

    virtual const std::map<OdAnsiString, OdAnsiString>* additionalInformation() const override;

    void loadData(OdSharedPtr<IdsSpecificationOptions> idsSpecification, OdSharedPtr<IdsOptions> findOptions, OdSharedPtr<IdsOptions> validationOptions);

  private:
    OdSharedPtr<IdsOptions> m_findOptions;
    OdSharedPtr<IdsOptions> m_validationOptions;
    OdSharedPtr<IdsSpecificationOptions> m_specificationOptions;
    int m_validationsCounter;
  };
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::SingleProjectInstanceValidationTask, SingleProjectInstanceValidationTask> object.
  */
  typedef OdSmartPtr<IdsInstanceValidationTask> IdsInstanceValidationTaskPtr;
}
#endif // _IDS_MODEL_VALIDATION_TASK_H
