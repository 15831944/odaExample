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

#if !defined(ODA_ODMVDXMLRULE_H_INCLUDED_)
#define ODA_ODMVDXMLRULE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IfcEntity.h"
#include "MvdXmlElement.h"
#include "MvdXmlConstraint.h"

namespace OdMvdXml
{
  /** \details
    OdMvdXmlRule - base class for rules of concept.
  */
  class MVDXML_EXPORT OdMvdXmlRule : public OdMvdXmlElement
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlRule);

  public:
    const OdAnsiString& getRuleID() const { return m_ruleID; };
    void setRuleID(const OdAnsiString &value) { m_ruleID = value; };
    const OdString& getDescription() const { return m_description; };
    void setDescription(const OdString &value) { m_description = value; };
    const OdMvdXmlConstraintPtrArray& getConstraints() const { return m_constraints; };
    const OdDAI::ApplicationInstance* getEntity() const { return m_instance; };

    /** \details
      Data validation checks if a instance data set fulfils all constraints of an exchange requirement.
      If required data is missing or  wrong then the check fails.

      \param pInstance [in] Pointer to instance object for validation.
      \param result [out] This value is set to true if the instance dataset meets all the restrictions of the exchange request,
      otherwise this value is set to false.

      \returns eOk if the instance was successfully checked; otherwise, the method returns an appropriate error code.

      \remarks
      If return value is not eOk - value of 'result' parameter is undefined.
    */
    OdResult checkInstance(const OdDAI::ApplicationInstance* pInstance, bool& result);

    /** \details
      Clean the entities assigned to the EntityRules.
     */
    void cleanInstance();

  protected:
    /** \details
      Copy data from the other element.

      \param other [in] Object to copy from.
    */
    void assign(const OdMvdXmlRule* other);

    /** \details
      Reads attributes from a xml element.

      \param pItem [in] Pointer to a xml element containing attributes.

      \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inAttributes(TiXmlElement* pItem) override;

    /** \details
      Reads child element from a xml element.

      \param nodeName [in] The node name of the xml element containing the child data.
      \param pChild [in] Pointer to a xml element containing child data.

      \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inChildNode(const char *nodeName, TiXmlElement* pChild) override;

    /** \details
      Writing attributes to the xml element.

      \param pItem [in] Pointer to the xml element to which you want to add attributes.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outAttributes(TiXmlElement* pItem) override;

    /** \details
      Writing child elements to the xml element.

      \param pParent [in] Pointer to the xml element to which you want to add children.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outChildNodes(TiXmlNode* pParent) override;

    /** \details
      Data validation checks if a instance data set fulfils all constraints of an exchange requirement.
      If required data is missing or  wrong then the check fails.

      \param pInstance [in] Pointer to instance object for validation.
      \param result [out] This value is set to true if the instance dataset meets all the restrictions of the exchange request,
      otherwise this value is set to false.

      \returns eOk if the instance was successfully checked; otherwise, the method returns an appropriate error code.

      \remarks
      If return value is not eOk - value of 'result' parameter is undefined.
    */
    virtual OdResult doCheckInstance(const OdDAI::ApplicationInstance* pInstance, bool& result);
    /** \details
      Clean the entities assigned to the EntityRules.
     */
    virtual void doCleanInstance();

    /** \details
      Identifies the rule for referencing at template rules defined within concepts,
      where specific parameters are applied for this rule.
        NOTE: The same RuleID might be used multiple times within a concept
        template definition, but it must be unique within the scope of its usage.
        EXAMPLE : If two AttributeRules are defined within different EntityRules, for
        instance one for IfcPropertySingleValue and the other one for
        IfcPropertyEnumeratedValue, then the same RuleID can be used because
        they are used in different scopes.
    */
    OdAnsiString m_ruleID;
    /** \details
      Optional description of the rule.
    */
    OdString m_description;
    /** \details
      Set of expressions, which all must evaluate to True for the referenced entity.
      This implies a Boolean AND combination. 
    */
    OdMvdXmlConstraintPtrArray m_constraints;
    /** \details
      The instance assigned to the rule for testing.
    */
    OdDAI::ApplicationInstancePtr m_instance;
  };
}

#endif // !defined(ODA_ODMVDXMLRULE_H_INCLUDED_)

