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

#if !defined(ODA_ODMVDXMLIDENTITY_H_INCLUDED_)
#define ODA_ODMVDXMLIDENTITY_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MvdXmlDefinition.h"
#include "StringArray.h"

namespace OdMvdXml
{

  SMARTPTR(OdMvdXmlIdentity);

  class MVDXML_EXPORT OdMvdXmlIdentity : public OdMvdXmlElement
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlIdentity);

  public:
    OdMvdXmlIdentity();
    virtual OdResult inFields(TiXmlElement* pParent) override;

    OdStringArray& getAutors();
    OdString& getCode();
    void setCode(const OdString& value);
    OdString& getCopyright();
    void setCopyright(const OdString& value);
    OdString& getName();
    void setName(const OdString& value);
    OdString& getOwner();
    void setOwner(const OdString& value);
    OdMvdStatus getStatus();
    void setStatus(const OdMvdStatus value);
    const OdGUID& getUuid() const;
    void setUuid(const OdGUID& value);
    OdString& getVersion();
    void setVersion(const OdString& value);

  protected:
    /** \details
      Copy data from the other element.

      \param other [in] Object to copy from.
    */
    void assign(const OdMvdXmlIdentity* other);

    /** \details
      Reads attributes from a xml element.

      \param pItem [in] Pointer to a xml element containing attributes.

      \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inAttributes(TiXmlElement* pParent) override;

    /** \details
      Writing attributes to the xml element.

      \param pItem [in] Pointer to the xml element to which you want to add attributes.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outAttributes(TiXmlElement* pItem) override;

    /** \details
      Universally unique identifier. This is used as a persistent identifier, and must
      never change.It is string type with a fixed length of 36 characters, which should
      follow a specific pattern.
    */
    OdGUID m_uuid;
    /** \details
      Human readable name.This is used as the header of the section and entry
      within table of contents when generating documentation.The name is also
      reported for a validation against this MVD, if assigned to concepts checked
      against the MVD.
    */
    OdString m_name;
    /** \details
      Human readable reference value of this element of the MVD definition.
    */
    OdString m_code;
    /** \details
      Sequential version number of this element of the MVD definition.
    */
    OdString m_version;
    /** \details
      The status information of this element of the MVD definition.
      It has the following enumerators :
       - Sample
       - Proposal
       - Draft
       - Candidate
       - Final
       - Deprecated
    */
    OdMvdStatus m_status;
    /** \details
      The author(s) of his element of the MVD definition.
      Authors are separated by semicolon.
    */
    OdStringArray m_autors;
    /** \details
      The legal owner of this element of the MVD definition
      NOTE Official Model View Definitions by buildingSMART International shall
       have ownership assigned to buildingSMART or another accepted
       standardization organization.
     */
    OdString m_owner;
    /** \details
      The copyright under which the work is published.
     */
    OdString m_copyright;
  };

  class MVDXML_EXPORT OdMvdXmlIdentityDefinitions : public OdMvdXmlIdentity, OdMvdXmlDefinitionsBase
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlIdentityDefinitions);

  protected:
    /** \details
      Copy data from the other element.

      \param other [in] Object to copy from.
    */
    void assign(const OdMvdXmlIdentityDefinitions* other);

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
  };
}

#endif // !defined(ODA_ODMVDXMLIDENTITY_H_INCLUDED_)
