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

#if !defined(ODA_ODMVDXMLDEFINITION_H_INCLUDED_)
#define ODA_ODMVDXMLDEFINITION_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MvdXmlElement.h"
#include "MvdXmlBody.h"
#include "MvdXmlLink.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlDefinition);

  class MVDXML_EXPORT OdMvdXmlDefinition : public OdMvdXmlElement
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlDefinition);

  public:
    const OdMvdXmlBodyPtr getBody() const;
    const OdMvdXmlLinkPtrArray& getLinks() const;

    /** \details
      Assignment operator.

      \param other [in] Other OdMvdXmlDefinition object to be assigned.
    */
    OdMvdXmlDefinition& operator=(const OdMvdXmlDefinition& other);

  protected:
    /** \details
      Copy data from the other object.

      \param other [in] Object to copy from.
    */
    void assign(const OdMvdXmlDefinition* other);

    /** \details
      Retrieves the name of the element. This name is used to write the element to a file.

      \returns The name of the element.
    */
    virtual OdAnsiString getElementName();

    /** \details
      Reads child element from a xml element.

      \param nodeName [in] The node name of the xml element containing the child data.
      \param pChild [in] Pointer to a xml element containing child data.

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
      HTML-formatted description of the concept in the default language.
    */
    OdMvdXmlBodyPtr      m_pBody;
    /** \details
      List of additional content, each of which may be in separate languages.
    */
    OdMvdXmlLinkPtrArray m_links;
  };

  class OdMvdXmlDefinitionsBase
  {
  public:
    const OdMvdXmlDefinitionPtrArray& getDefinitions() const;

  protected:
    /** \details
      Copy data from the other object.

      \param other [in] Object to copy from.
    */
    void assign(const OdMvdXmlDefinitionsBase* other);
    /** \details
      Reads definition elements from a xml element.

      \param pParent [in] Pointer to a xml element containing child data of definition.

      \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
    */
    OdResult inDefinitions(TiXmlElement* pParent);

    /** \details
      Writing definition elements to the xml element.

      \param pParent [in] Pointer to the xml element to which you want to add definition.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    OdResult outDefinitions(TiXmlNode* pParent);

    /** \details
      Groups definition text and links to additional figures,
      diagrams, examples, and other external documents.
    */
    OdMvdXmlDefinitionPtrArray m_definitions;
  };

  class MVDXML_EXPORT OdMvdXmlDefinitions : public OdMvdXmlElement, OdMvdXmlDefinitionsBase
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlDefinitions);

  protected:
    /** \details
      Copy data from the other object.

      \param other [in] Object to copy from.
    */
    void assign(const OdMvdXmlDefinitions* other);

    /** \details
      Reads child element from a xml element.

      \param nodeName [in] The node name of the xml element containing the child data.
      \param pChild [in] Pointer to a xml element containing child data.

      \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inChildNode(const char *nodeName, TiXmlElement* pChild) override;

    /** \details
      Writing child elements to the xml element.

      \param pParent [in] Pointer to the xml element to which you want to add children.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outChildNodes(TiXmlNode* pParent) override;

    friend class OdMvdXmlDefinitionsBase;
  };
}

#endif // !defined(ODA_ODMVDXMLDEFINITION_H_INCLUDED_)

