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

#if !defined(ODA_ODMVDXMLLINK_H_INCLUDED_)
#define ODA_ODMVDXMLLINK_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MvdXmlElement.h"

namespace OdMvdXml
{
  SMARTPTR(OdMvdXmlLink);

  class MVDXML_EXPORT OdMvdXmlLink : public OdMvdXmlElement
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlLink);

  public:
    OdString& getLang() { return m_lang; };
    void setLang(OdString &value) { m_lang = value; };
    OdString& getTitle() { return m_title; };
    void setTitle(OdString &value) { m_title = value; };
    OdString& getCategory() { return m_category; };
    void setCategory(OdString &value) { m_category = value; };
    OdString& getHREF() { return m_href; };
    void setHREF(OdString &value) { m_href = value; };
    OdString& getValue() { return m_value; };
    void setValue(OdString &value) { m_value = value; };

    /** \details
      Assignment operator.

      \param other [in] Other OdMvdXmlLink object to be assigned.
    */
    OdMvdXmlLink& operator=(const OdMvdXmlLink& other);

  protected:
    /** \details
      Copy data from the other element.

      \param other [in] Object to copy from.
    */
    void assign(const OdMvdXmlLink* other);

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
      Locale identifier based on RFC 1766 language codes to indicate the default locale.
      Examples are ‘en’, ‘de’, ‘en - GB’, ’de - CH’.
    */
    OdString m_lang;
    /** \details
      Human readable name. This is used as the header of the link content and entry
      within table of contents when generating documentation.
    */
    OdString m_title;
    /** \details
      Indication about the category of the linked content.
    */
    OdString m_category;
    /** \details
      URL to referenced content.
    */
    OdString m_href;
    /** \details
      HTML-formatted description in specified language.
    */
    OdString m_value;
  };
}

#endif // !defined(ODA_ODMVDXMLLINK_H_INCLUDED_)

