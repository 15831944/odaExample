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

#if !defined(ODA_ODMVDXMLCONCEPT_H_INCLUDED_)
#define ODA_ODMVDXMLCONCEPT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MvdXmlIdentity.h"
#include "MvdXmlTemplateRule.h"
#include "MvdXmlTemplateRef.h"
#include "MvdXmlRequirement.h"
#include "MvdXmlTemplateRules.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlConcept);

  class MVDXML_EXPORT OdMvdXmlConcept : public OdMvdXmlIdentityDefinitions
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlConcept);

    OdMvdXmlConcept();

    /** \details
      Retrieves the TemplateRef object - reference to the ConceptTemplate by uuid.
    
      \returns
      Retrieves a SmartPointer to the TemplateRef object (reference to the ConceptTemplate by uuid).
    */
    const OdMvdXmlTemplateRefPtr& getTempateRef() const { return m_pTempateRef; };

    /** \details
      Retrieves the set of requirements which describe applicability of the concept to particular
      exchanges for import, export or both.

      \returns
      Retrieves a set of the Requirement objects.
    */
    const OdMvdXmlRequirementPtrArray& getRequirements() const { return m_requirements; };
    /** \details

      \returns
    */
    const OdMvdXmlTemplateRulesPtr& getRules() const { return m_rules; };
    /** \details

      \returns
    */
    const OdMvdXmlConceptTemplate* getConceptTemplate() const;

    /** \details

      \returns eOk if the instance was successfully checked; otherwise, the method returns an appropriate error code.
    */
    OdResult checkInstance(const OdDAI::ApplicationInstance* pInstance, bool& result) const;

  protected:
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
    /** \details
      Enables to select a concept definition that shall either be reused or redefined.
      This feature depends on the inheritance tree of the underlying schema. 
    */
    OdGUID m_baseConcept;
    /** \details
      This value must be defined if a BaseConcept is selected.  
      If Override = false then the Concept is reused without changes.  
      If true then the Concept from the super type is redefined by this Concept.
    */
    bool m_override;
    /** \details
      Mandatory reference to the ConceptTemplate by uuid, where such
      template may be defined within the same file(by @ref) or an external file
      (by @href).
    */
    OdMvdXmlTemplateRefPtr m_pTempateRef;
    /** \details
      Set of requirements which describe applicability of the concept to particular
      exchanges for import, export or both.
    */
    OdMvdXmlRequirementPtrArray m_requirements;
    /** \details
      Tree structure of rules indicating how template applies to particular entity.
      Each TemplateRules element consists of a set of other TemplateRules or
      TemplateRule element and a logical operator. Each TemplateRule element
      defines the @Parameter that refer to the RuleID of the referenced Template.
    */
    OdMvdXmlTemplateRulesPtr m_rules;
  };
}

#endif // !defined(ODA_ODMVDXMLCONCEPT_H_INCLUDED_)

