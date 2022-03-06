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

#ifndef  _DAI_WHERE_RULES_ATTRS_VALIDATION_TASK_H
#define _DAI_WHERE_RULES_ATTRS_VALIDATION_TASK_H

#include "OdaCommon.h"

#include "daiInstanceValidationTask.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details
  A class which validates the where rules of defied types for attributes of application instance.
  */
  class DAI_EXPORT WhereRulesAttrsValidationTask : public InstanceValidationTask
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(WhereRulesAttrsValidationTask);
    //DOM-IGNORE-END

  public:
    /** \details
    Checks entity instance against where rules of its attributes defined types.
    \param pInstanceCtx [in] A raw pointer to the validation context with validate entity instance.
    \param InvalidValidationParams [out] The struct with an array of pointers to Attribute instances and WhereRule instances which values are violationg where rules of their types.
    \returns True if all attributes with where rules are satisfied; otherwise, the method returns False.
    */
    virtual OdDAI::Logical validate(OdDAI::OdBaseInstanceValidationContext* pInstanceCtx, OdSharedPtr<InvalidValidationParamsBase>& invalidParams) override;
    /** \details
    Retrieves the description of validation task.
    \returns An ANSI string that contains the description of validation task.
    */
    virtual OdAnsiString description() const override;

  private:
    OdDAI::Logical entityValidate(OdDAI::ApplicationInstance* pInstance, const OdDAI::Entity* entity, InvalidValidationParams& invalidParams);
    OdDAI::Logical checkWhereRule(const OdRxValue& dlsoVal, const OdDAI::Entity* entity, const OdDAI::NamedType* namedType, WhereRulePtr& whereRule);

    template<class C, class T>
    OdDAI::Logical checkContainerData(const OdRxValue& dlsoVal, const OdDAI::Entity* entity, const OdDAI::NamedType* namedType, WhereRulePtr& whereRule)
    {
      C containerData;
      dlsoVal >> *reinterpret_cast<C*>(&containerData);
      const OdArray<T>& containerInArray = containerData.getArray();

      OdDAI::Logical result = OdDAI::Logical::True;
      for (auto it : containerInArray)
      {
        OdDAI::Logical checkResult = checkWhereRule(it, entity, namedType, whereRule);
        if (checkResult != result)
          return checkResult;
      }
      return result;
    }
  };
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::WhereRulesAttrsValidationTask, WhereRulesAttrsValidationTask> object.
  */
  typedef OdSmartPtr<WhereRulesAttrsValidationTask> WhereRulesAttrsValidationTaskPtr;
}

#endif //_DAI_INSTANCE_VALIDATION_TASKS_H
