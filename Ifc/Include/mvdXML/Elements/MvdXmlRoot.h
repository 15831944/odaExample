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

#if !defined(ODA_ODMVDXMLROOT_H_INCLUDED_)
#define ODA_ODMVDXMLROOT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MvdXmlIdentity.h"
#include "MvdXmlConceptTemplate.h"
#include "MvdXmlModelView.h"
#include "MvdXmlAuditInfo.h"

namespace OdMvdXml
{
  /** \details
    Defines version of mvdXML.
  */
  enum mvdXmlVersion
  {
    /** Version unset. */
    mvdXmlUnset,
    /** mvdXML version 1.1. */
    mvdXml1dot1,
    /** mvdXML version 1.2. */
    mvdXml1dot2,
    /** mvdXML version 1-1. */
    mvdXml1_1
  };

  SMARTPTR(OdMvdXmlRoot);

  class MVDXML_EXPORT OdMvdXmlRoot : public OdMvdXmlIdentity
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlRoot);

  public:
    OdMvdXmlRoot();

    /** \details
      Add an element to an array of elements.
    */
    void addElement(OdMvdXmlIdentityPtr pElement);
    OdResult loadDocument(TiXmlDocument* pDocument, OdMvdXmlAuditInfo* audit);
    OdResult saveDocument(TiXmlDocument* pDocument, OdMvdXmlAuditInfo* audit);
    OdMvdXmlIdentityPtr getElement(const OdGUID& uuid) const;
    const OdMvdXmlModelViewPtrArray& getViews() const;
    const OdMvdXmlConceptTemplatePtrArray& getTemplates() const;
    int appendTemplate(OdMvdXmlConceptTemplatePtr item);
    OdMvdXmlAuditInfo* getAudit();
    void setAudit(OdMvdXmlAuditInfo* value);
    OdAnsiString getXmlns();
    void setXmlns(const OdAnsiString& value);
    OdAnsiString getXsi();
    void setXsi(const OdAnsiString& value);
    OdAnsiStringArray& getSchemaLocation();
    void setSchemaLocation(const OdAnsiStringArray& value);

    /** \details
      Returns the version of this mvdXml.
    */
    const mvdXmlVersion getVersion() const;

    /** \details
      Clear object.
    */
    void Clear();

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
      Set of templates, which may be exchanged with or without referencing model 
      view definitions.
    */
    OdMvdXmlConceptTemplatePtrArray m_templates;

    /** \details
      List of model view definitions, in order of listing in generated documentation.
      
      \remarks
      If empty, the mvdXML file is only used to exchange concept templates
      and cannot be used to fulfill other purposes such as data validation
    */
    OdMvdXmlModelViewPtrArray       m_views;

    /** \details
      List of identification elements. Used to search for items by their uuid.
    */
    OdMvdXmlIdentityPtrArray        m_elements;

    /** \details
      Pointer to an AuditInfo element. Used for logging.
    */
    OdMvdXmlAuditInfo*              m_audit;

    /*
     TODO Do I need to keep these values?
    */
    OdAnsiString                    m_xmlns;
    OdAnsiString                    m_xsi;
    OdAnsiStringArray               m_schemaLocation;
  };
}

#endif // !defined(ODA_ODMVDXMLROOT_H_INCLUDED_)

