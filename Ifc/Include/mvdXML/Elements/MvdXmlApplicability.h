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

#if !defined(ODA_ODMVDXMLAPPLICABILITY_H_INCLUDED_)
#define ODA_ODMVDXMLAPPLICABILITY_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MvdXmlDefinition.h"
#include "MvdXmlTemplateRule.h"
#include "MvdXmlTemplateRules.h"
#include "MvdXmlTemplateRef.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlApplicability);

  /** \details
    This class defines those rules, being TemplateRules with a reference to a ConceptTemplate, that need 
    to be validated before the concepts associated to the ConceptRoot are checked.
  */
  class MVDXML_EXPORT OdMvdXmlApplicability : public OdMvdXmlDefinitions
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlApplicability);

  public:
    /** \details
      Reads data from a xml element.

      \param pItem [in] Pointer to a xml element containing data.

      \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inFields(TiXmlElement* pItem) override;

    /** \details
      Retrieves the reference to the ConceptTemplate by uuid,
      where such template may be defined within the same file.
    
      \returns
      GUID object containing uuid of the ConceptTemplate.
    */
    const OdGUID& getRef() const;

    /** \details
      Retrieves the tree structure of rules indicating how template applies to particular entity.
      Each TemplateRules element consists of a set of other TemplateRules or
      TemplateRule element and a logical operator. Each TemplateRule element
      defines the @Parameter that refer to the RuleID of the referenced Template.

      \returns
      Retrieves a SmartPointer to the tree structure of rules.
    */
    const OdMvdXmlTemplateRulesPtr getRules() const;

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

      \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inChildNode(const char *nodeName, TiXmlElement* pChild) override;

    /** \details
      Writing child elements to the xml element.

      \param pParent [in] Pointer to the xml element to which you want to add children.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outChildNodes(TiXmlNode* pParent) override;
  private:

    /** \details
      Mandatory reference to the ConceptTemplate by uuid, where such
      template may be defined within the same file(by @ref) or an external file
      (by @href).
    */
    OdMvdXmlTemplateRefPtr       m_pTempateRef;

    /** \details
      Tree structure of rules indicating how template applies to particular entity.
      Each TemplateRules element consists of a set of other TemplateRules or
      TemplateRule element and a logical operator. Each TemplateRule element
      defines the @Parameter that refer to the RuleID of the referenced Template.
      NOTE Added in mvdXML to define any logical combination of rules,
      allowing for AND, OR, NOT, NAND, NOR, XOR, and NXOR logic.
    */
    OdMvdXmlTemplateRulesPtr     m_rules;
  };
}

#endif // !defined(ODA_ODMVDXMLAPPLICABILITY_H_INCLUDED_)

