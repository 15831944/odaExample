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

#if !defined(ODA_ODMVDXMLBODY_H_INCLUDED_)
#define ODA_ODMVDXMLBODY_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MvdXmlElement.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlBody);

  class MVDXML_EXPORT OdMvdXmlBody : public OdMvdXmlElement
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlBody);

  public:
    /** \details
      Retrieves the

      \returns

    */
    OdAnsiString& getLang() { return m_lang; };
    void setLang(OdAnsiString&value) { m_lang = value; };
    /** \details
      Retrieves the

      \returns

    */
    OdAnsiString& getTags() { return m_tags; };
    void setTags(OdAnsiString&value) { m_tags = value; };
    /** \details
      Retrieves the

      \returns

    */
    OdAnsiString& getValue() { return m_value; };
    void SetValue(OdAnsiString&value) { m_value = value; };

    /** \details
      Assignment operator.

      \param other [in] Other OdMvdXmlBody object to be assigned.
    */
    OdMvdXmlBody& operator=(const OdMvdXmlBody& other);

  protected:
    /** \details
      Copy data from the other object.

      \param other [in] Object to copy from.
    */
    void assign(const OdMvdXmlBody* other);

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

    virtual OdResult outAttributes(TiXmlElement* pItem) override;

  private:
    
    /** \details
      Locale identifier based on RFC 1766 language codes to indicate the default locale.
      Examples are ‘en’, ‘de’, ‘en - GB’, ’de - CH’.
    */
    OdAnsiString m_lang;

    /** \details
      List of tags that classify the element. All tags are separated through whitespaces
      per default. A semicolon must be used if given tags consists of multiple words.
    */
    OdAnsiString m_tags;
    /** \details
      HTML-formatted content for generating documentation.
    */
    OdAnsiString m_value;
  };
}

#endif // !defined(ODA_ODMVDXMLBODY_H_INCLUDED_)

