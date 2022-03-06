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

#if !defined(ODA_ODMVDXMLTEMPLATEREF_H_INCLUDED_)
#define ODA_ODMVDXMLTEMPLATEREF_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IfcEntity.h"
#include "MvdXmlElement.h"
#include "MvdXmlConceptTemplate.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlTemplateRef);

  class MVDXML_EXPORT OdMvdXmlTemplateRef : public OdMvdXmlElement
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlTemplateRef);

  public:
    const OdGUID& getRef() const;
    const OdAnsiString& getHref() const;
    void setHref(const OdAnsiString& value);
    const OdAnsiString& getIdPrefix() const;
    void setIdPrefix(const OdAnsiString& value);
    const bool isEmpty() const;
    const bool isExternalLink() const;

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
    OdResult checkInstance(const OdDAI::ApplicationInstance* pInstance, bool& result);

    /** \details
      Clean the entities assigned to the EntityRules.
     */
    void cleanInstance();

    /** \details
      Assignment operator.

      \param other [in] Other OdMvdXmlTemplateRef object to be assigned.
    */
    OdMvdXmlTemplateRef& operator=(const OdMvdXmlTemplateRef& other);

  protected:
    /** \details
      Copy data from the other element.

      \param other [in] Object to copy from.
    */
    void assign(const OdMvdXmlTemplateRef* other);

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
      Writing attributes to the xml element.

      \param pItem [in] Pointer to the xml element to which you want to add attributes.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outAttributes(TiXmlElement* pItem) override;

  private:
    /** \details
      Mandatory reference to the ConceptTemplate by uuid, where such 
      template may be defined within the same file.
    */
    OdGUID m_ref;
    /** \details
      Mandatory reference to the ConceptTemplate by uuid, where template defined on external file.

    \remarks
      Current usage of mvdXML imposes the inclusion off all concept
      templates within the same data file. The external reference by @href is
      reserved for future usage.
    */
    OdAnsiString m_href;
    /** \details
      IdPrefix - an optional prefix for the RuleId name, used to prevent ambiguous RuleId,
      if the same partial template is referenced twice in a concept template tree.
    */
    OdAnsiString m_idPrefix;

    /** \details
      Reference to the OdMvdXmlConceptTemplate class.
    */
    OdMvdXmlConceptTemplatePtr m_template;
  };
}

#endif // !defined(ODA_ODMVDXMLTEMPLATEREF_H_INCLUDED_)

