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

#if !defined(ODA_ODMVDXMLENTITYRULE_H_INCLUDED_)
#define ODA_ODMVDXMLENTITYRULE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IfcEntity.h"
#include "MvdXmlRule.h"
#include "MvdXmlTemplateRef.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlEntityRule);
  SMARTPTR(OdMvdXmlAttributeRule);
  SMARTPTR(OdMvdXmlConceptTemplate);

  class MVDXML_EXPORT OdMvdXmlEntityRule : public OdMvdXmlRule
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlEntityRule);

  public:
    const OdAnsiString& getEntityName() const { return m_entityName; };
    void setEntityName(const OdAnsiString &value) { m_entityName = value; };
    const OdAnsiString& getRuleID() const { return m_ruleID; };
    void setRuleID(const OdAnsiString &value) { m_ruleID = value; };
    const OdString& getDescription() const { return m_description; };
    void setDescription(const OdString &value) { m_description = value; };
    const OdMvdXmlTemplateRefPtr getTemplateRef() { return m_pTemplateRef; };
    void setTemplateRef(OdMvdXmlTemplateRefPtr value) { m_pTemplateRef = value; };
    const OdMvdXmlAttributeRulePtrArray& getEntityRules() const { return m_rules; };

    OdMvdXmlAttributeRule* getAttributeRuleByID(const char* ruleId);
    OdMvdXmlEntityRule* getEntityRuleByID(const char* ruleId);
    OdMvdXmlRule* getRuleByID(const char* ruleId);
    OdResult execute(const OdMvdXmlConceptTemplate* pTemplate, bool& result) const;

    /** \details
      Assignment operator.

      \param other [in] Other OdMvdXmlEntityRule object to be assigned.
    */
    OdMvdXmlEntityRule& operator=(const OdMvdXmlEntityRule& other);

  protected:
    /** \details
      Copy data from the other element.

      \param other [in] Object to copy from.
    */
    void assign(const OdMvdXmlEntityRule* other);

    /** \details
      Retrieves the name of the element. This name is used to write the element to a file.

      \returns The name of the element.
    */
    virtual OdAnsiString getElementName();

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
    virtual OdResult doCheckInstance(const OdDAI::ApplicationInstance* pInstance, bool& result) override;

    /** \details
      Clean the entities assigned to the EntityRules.
     */
    virtual void doCleanInstance() override;

  private:
    /** \details
      The case-sensitive name of the entity(e.g.“IfcBeam”) which must be
      assignable to the enclosing AttributeRule
      (i.e.entity subtype or select member).
    */
    OdAnsiString m_entityName;
    /** \details
      Optional reference to a partial template. An optional attribute “IdPrefix” can
      be given to ensure that RuleIDs of partial templates are unique within the
      scope of its usage. This attribute is used as a prefix for all referenced RuleIDs. 
    */
    OdMvdXmlTemplateRefPtr m_pTemplateRef;
    /** \details
      Indicates a list of attributes included in the concept template and
      potentially constrained on the referenced entity.
    */
    OdMvdXmlAttributeRulePtrArray m_rules;
  }; 
}

#endif // !defined(ODA_ODMVDXMLENTITYRULE_H_INCLUDED_)

