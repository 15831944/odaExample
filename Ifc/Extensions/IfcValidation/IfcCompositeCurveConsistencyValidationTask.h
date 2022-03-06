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

#ifndef  _IFC_COMPOSITE_CURVE_CONSISTENCY_VALIDATION_TASK_H
#define _IFC_COMPOSITE_CURVE_CONSISTENCY_VALIDATION_TASK_H

#include "OdaCommon.h"
#include "daiExtentValidationTask.h"
#include "IfcValidationExport.h"

/** \details
Contains declarations related to working with IFC files content.
*/
namespace OdIfc
{
  /** \details
  A class which checks segments supertypes of IfcCompositeCurve on correctly consistency.
  */
  class IFC_VALIDATION_EXPORT CompositeCurveConsistencyValidationTask : public OdDAI::ExtentValidationTask
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(CompositeCurveConsistencyValidationTask);
    //DOM-IGNORE-END

  public:
    /**\details
   Creates a new CompositeCurveConsistencyValidationTask.
   */
    CompositeCurveConsistencyValidationTask();
    /** \details
    Checks segments of the Instance on correctly consistency.
    \param pInstanceCtx [in] A raw pointer to the validation context with validate entity instance.
    \param invalidParams [out] An array of pointers to invalid segments instances and error description.
    \returns True if all curve segments are correctly consistency; otherwise, the method returns False.
    */
    virtual OdDAI::Logical validate(OdDAI::OdBaseInstanceValidationContext* pInstanceCtx, OdSharedPtr<InvalidValidationParamsBase>& invalidParams) override;
    /** \details
    Retrieves the description of validation task.
    \returns An ANSI string that contains the description of validation task.
    */
    virtual OdAnsiString description() const override;
  };
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::CompositeCurveConsistencyValidationTask, CompositeCurveConsistencyValidationTask> object.
  */
  typedef OdSmartPtr<CompositeCurveConsistencyValidationTask> CompositeCurveConsistencyValidationTaskPtr;
}

#endif //_IFC_COMPOSITE_CURVE_CONSISTENCY_VALIDATION_TASK_H
