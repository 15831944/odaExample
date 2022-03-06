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

#if !defined(ODA_ODMVDXMLCONCEPTTEMPLATE_H_INCLUDED_)
#define ODA_ODMVDXMLCONCEPTTEMPLATE_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StringArray.h"
#include "IfcEntity.h"
#include "MvdXmlRule.h"
#include "MvdXmlIdentity.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlConceptTemplate);
  SMARTPTR(OdMvdXmlAttributeRule);
  SMARTPTR(OdMvdXmlEntityRule);

  class MVDXML_EXPORT OdMvdXmlConceptTemplate : public OdMvdXmlIdentityDefinitions
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlConceptTemplate);

  public:
    OdMvdXmlConceptTemplate();

    const OdAnsiString& getApplicableSchema() const { return m_applicableSchema; };
    void setApplicableSchema(const OdAnsiString &value) { m_applicableSchema = value; };
    OdAnsiString& getApplicableEntity() { return m_applicableEntities; };
    void setApplicableEntity(const OdAnsiString& value) { m_applicableEntities = value; };
    const bool getIsPartial() const { return m_isPartial; };
    void setIsPartial(const bool value) { m_isPartial = value; };

    const OdMvdXmlAttributeRulePtrArray& getRules() const { return m_rules; };
    const OdMvdXmlConceptTemplatePtrArray& getSubTemplates() const { return m_subTemplates; };

    OdMvdXmlAttributeRule* getAttributeRuleByID(const char* ruleId);
    OdMvdXmlEntityRule* getEntityRuleByID(const char* ruleId);
    OdMvdXmlRule* getRuleByID(const char* ruleId);

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
    OdResult checkInstance(const OdDAI::ApplicationInstance* pInstance, bool& result) const;

    /** \details
      Clean the entities assigned to the EntityRules.
     */
    void cleanInstance();

    /** \details
      Assignment operator.

      \param other [in] Other OdMvdXmlConceptTemplate object to be assigned.
    */
    OdMvdXmlConceptTemplate& operator=(const OdMvdXmlConceptTemplate& other);

  protected:
    /** \details
      Copy data from the other object.

      \param other [in] Object to copy from.
    */
    void assign(const OdMvdXmlConceptTemplate* other);

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

  private:
    // TODO: In future change to OdStringArray
    /** \details
      Identifies the default schema for which the template applies, such as
      IFC2X_FINAL, IFC2X2_FINAL, IFC2X3, or IFC4.The template may be
      used for model views of other schemas, if all enclosed rules resolve to
      available attributes and types.
      NOTE: In future versions it might be of interest to support more than one
            IFC release. This can be supported by using a semicolon as schema
            name delimiter.
    */
    OdAnsiString                    m_applicableSchema;

    /** \details
      Indicates the IfcRoot-based entities, including all derived entities, for
      which the concept applies. It is recommended to use a single base class
      (e.g. IfcElement). This value provides the context for any attribute rules
      and is used within MVD tools to filter the list of available templates for
      particular entities. For a sub-template, the applicable entity must be the
      same type or a subtype of the outer template. This value may be blank to
      indicate an abstract template that cannot be instantiated,
      containing subtemplates for specific entities.
    */
    OdAnsiString                    m_applicableEntities;

    /** \details
      A flag, indicating whether the concept template is a partial template,
      which shall only be used inside another concept template, or not.
    */
    bool                            m_isPartial;

    /** \details
      Set of sub-templates, having a subset of applicable entities, which further
      define a concept template for particular usage. For example, a template
      for material usage may have sub-templates for material layer sets,
      material profile sets, and material constituent sets.
    */
    OdMvdXmlConceptTemplatePtrArray m_subTemplates;

    /** \details
      Set of attributes defined at applicableEntity, where each attribute may
      have value constraints and/or graphs of object instances defined.If an
      attribute is not defined, then the requirements are the same as indicated
      for the schema.
    */
    OdMvdXmlAttributeRulePtrArray   m_rules;
  };
}

#endif // !defined(ODA_ODMVDXMLCONCEPTTEMPLATE_H_INCLUDED_)

