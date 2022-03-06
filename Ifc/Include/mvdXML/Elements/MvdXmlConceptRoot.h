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

#if !defined(ODA_ODMVDXMLCONCEPTROOT_H_INCLUDED_)
#define ODA_ODMVDXMLCONCEPTROOT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IfcEntity.h"
#include "MvdXmlIdentity.h"
#include "MvdXmlApplicability.h"
#include "MvdXmlConcept.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlConceptRoot);

  class MVDXML_EXPORT OdMvdXmlConceptRoot : public OdMvdXmlIdentityDefinitions
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlConceptRoot);

  public:
    const OdMvdXmlApplicabilityPtr getApplicability() const;
    const OdMvdXmlConceptPtrArray& getConcepts() const;
    const OdAnsiString& getApplicableRootEntity() const { return m_applicableRootEntity; };
    void setApplicableRootEntity(const OdAnsiString &value) { m_applicableRootEntity = value; };

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
      Identifies the class or data type of instance being described or validated,
      i.e.the IFC entity(deriving from IfcRoot) for which the concepts apply.The
      concepts apply to this IFC entity or its subtypes(respectively instances of
      those classes in case of validation).
    */
    OdAnsiString               m_applicableRootEntity;

    /** \details
      A set of TemplateRules, based on a concept template, which describe the
      conditions, under which the concepts apply to the applicableRootEntity.
      Those conditions need to validate to true as a prerequisite for checking the
      TemplateRules imposed at the concepts.
    */
    OdMvdXmlApplicabilityPtr   m_pApplicability;

    /** \details
      List of concepts for the applicable root entity. The order of elements 
      indicates the sequence displayed in generated documentation.
    */
    OdMvdXmlConceptPtrArray    m_concepts;
  }; 
}

#endif // !defined(ODA_ODMVDXMLCONCEPTROOT_H_INCLUDED_)

