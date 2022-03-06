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

#if !defined(ODA_ODMVDXMLATTRIBUTERULE_H_INCLUDED_)
#define ODA_ODMVDXMLATTRIBUTERULE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IfcEntity.h"
#include "MvdXmlRule.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlAttributeRule);
  SMARTPTR(OdMvdXmlEntityRule);
  SMARTPTR(OdMvdXmlConceptTemplate);

  class MVDXML_EXPORT OdMvdXmlAttributeRule : public OdMvdXmlRule
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlAttributeRule);

  public:
    const OdAnsiString& getAttributeName() const { return m_attributeName; };
    void setAttributeName(const OdAnsiString &value) { m_attributeName = value; };
    const OdAnsiString& getRuleID() const { return m_ruleID; };
    void setRuleID(const OdAnsiString &value) { m_ruleID = value; };
    const OdString& getDescription() const { return m_description; };
    void setDescription(const OdString &value) { m_description = value; };
    const OdMvdXmlEntityRulePtrArray& getEntityRules() const { return m_rules; };

    OdMvdXmlAttributeRule* getAttributeRuleByID(const char* ruleId);
    OdMvdXmlEntityRule* getEntityRuleByID(const char* ruleId);
    OdMvdXmlRule* getRuleByID(const char* ruleId);

    OdResult execute(const OdMvdXmlConceptTemplate* pTemplate, bool& result) const;

    /** \details
      Assignment operator.

      \param other [in] Other OdMvdXmlAttributeRule object to be assigned.
    */
    OdMvdXmlAttributeRule& operator=(const OdMvdXmlAttributeRule& other);

  protected:
    void assign(const OdMvdXmlAttributeRule* other);

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

    virtual OdResult outAttributes(TiXmlElement* pItem) override;

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
    virtual OdResult doCheckInstance(const OdDAI::ApplicationInstance* pInstance, bool& result) override;

    /** \details
      Clean the entities assigned to the EntityRules.
     */
    virtual void doCleanInstance() override;

  private:
    
    /** \details
      The case-sensitive name of the attribute relative to the enclosing
      EntityRule (if exists) or the enclosing applicableEntity of the
      ConceptTemplate.
    */
    OdAnsiString m_attributeName;
 
    /** \details
      An empty list indicates that any type may be used according to the
      schema.If one or more entities or types are defined, then instances must
      match one of the entries.The list of entries is expanded by each
      referencing TemplateRule defined at a Concept, where downstream rules
      apply according to the matching entity rule.
    */
    OdMvdXmlEntityRulePtrArray m_rules;
  }; 
}

#endif // !defined(ODA_ODMVDXMLATTRIBUTERULE_H_INCLUDED_)

