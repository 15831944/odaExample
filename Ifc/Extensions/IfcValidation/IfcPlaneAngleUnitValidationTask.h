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

#ifndef  _IFC_PLANE_ANGLE_UNIT_VALIDATION_TASK_H
#define _IFC_PLANE_ANGLE_UNIT_VALIDATION_TASK_H

#include "OdaCommon.h"
#include "IfcValidationExport.h"

#include "daiModelValidationTask.h"
#include "daiModelValidationHealer.h"

/** \details
Contains declarations related to working with IFC files content.
*/
namespace OdIfc
{
  /** \details
  A class which checks that IfcProject instance has assignment of PLANEANGLEUNIT.
  */
  class IFC_VALIDATION_EXPORT PlaneAngleUnitValidationTask : public OdDAI::ModelValidationTask
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(PlaneAngleUnitValidationTask);
    //DOM-IGNORE-END

  public:
    /** \details
    Checks whether IfcProject instance has assignment of PLANEANGLEUNIT.
    \param pModelCtx [in] A raw pointer to the validation context with validate model.
    \param invalidParams [out] A struct with array of <link OdDAIObjectId, OdDAI object identifiers> that has IfcProject identifier, if it hasn't assignment of PLANEANGLEUNIT; otherwise, it's empty.
    \returns True IfcProject instance has assignment of PLANEANGLEUNIT; otherwise, the method returns False.
    */
    virtual OdDAI::Logical validate(OdDAI::OdBaseModelValidationContext* pCtx, OdSharedPtr<InvalidValidationParamsBase>& invalidParams) override;
    /** \details
    Retrieves the description of validation task.
    \returns An ANSI string that contains the description of validation task.
    */
    virtual OdAnsiString description() const override;
  };
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::PlaneAngleUnitValidationTask, PlaneAngleUnitValidationTask> object.
  */
  typedef OdSmartPtr<PlaneAngleUnitValidationTask> PlaneAngleUnitValidationTaskPtr;

  /** \details
  A class which fixs problem with missed IfcProject instance assignment of PLANEANGLEUNIT.
  */
  class IFC_VALIDATION_EXPORT PlaneAngleUnitValidationHealer : public OdDAI::ModelValidationHealer
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(PlaneAngleUnitValidationHealer);
    //DOM-IGNORE-END

  public:
    /** \details
    Fixs problem with missed IfcProject instance assignment of PLANEANGLEUNIT.
    \param model [in] A raw pointer to the <link OdDAI::Model, model> class to be healing.
    \param invalidParams [in] A pointer to the struct with invalid <link OdDAIObjectId, OdDAI object identifiers> of the entity instances.
    \returns Result of healing. Returns True if healing is successful.
    */
    virtual OdDAI::Logical heal(OdDAI::Model* model, OdDAI::ValidationTask::InvalidValidationParamsBase* invalidParams) override;

  private:
    bool checkAngleAttribute(OdDAI::Attribute* attr, OdAnsiString& name);
    bool checkRadianAngleFromDouble(const OdRxValue& angle);
    bool checkRadianAngleFromSelect(const OdRxValue& angle, const std::set<OdAnsiString>& selectNames);

    bool isRadianAngle = true;
  };

  /** \details
A data type that represents a smart pointer to an <link OdDAI::PlaneAngleUnitValidationHealer, PlaneAngleUnitValidationHealer> object.
*/
  typedef OdSmartPtr<PlaneAngleUnitValidationHealer> PlaneAngleUnitValidationHealerPtr;
}

#endif //_IFC_PLANE_ANGLE_UNIT_VALIDATION_TASK_H
