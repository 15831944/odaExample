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

#if !defined(ODA_ODMVDXMLELEMENT_H_INCLUDED_)
#define ODA_ODMVDXMLELEMENT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MvdXmlCommon.h"
#include "OdString.h"
#include "StringArray.h"
#include "MvdXmlAuditInfo.h"
#include "tinyxml.h"

namespace OdMvdXml
{
  class OdMvdXmlRoot;
  SMARTPTR(OdMvdXmlElement);

  class MVDXML_EXPORT OdMvdXmlElement : public OdRxObject
  {
    ODRX_DECLARE_MEMBERS(OdMvdXmlElement);

  public:
    OdMvdXmlElement();

    /** \details
      Reads data from a xml element.

      \param pItem [in] Pointer to a xml element containing data.

      \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inFields(TiXmlElement* pItem);
    virtual OdResult outFields(TiXmlNode* pParent);
    OdMvdXmlRoot* getRoot() const;
    void appendXmlErrorMessage(TiXmlElement* pParent, const char* text, const char* caption = NULL, OdResult code = eOk);
    void appendXmlWarningMessage(TiXmlElement* pParent, const char* text, const char* caption = NULL, OdResult code = eOk);
    void appendErrorMessage(const char* text, const char* caption = NULL) const;
    void appendWarningMessage(const char* text, const char* caption = NULL) const;

    /** \details
      Assignment operator.

      \param other [in] Other OdMvdXmlElement object to be assigned.
    */
    OdMvdXmlElement& operator=(const OdMvdXmlElement& other);

  protected:
    /** \details
      Copy data from the other element.

      \param other [in] Object to copy from.
    */
    void assign(const OdMvdXmlElement* other);

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
    virtual OdResult inAttributes(TiXmlElement* pItem);

    /** \details
      Reads child element from a xml element.

      \param nodeName [in] The node name of the xml element containing the child data.
      \param pChild [in] Pointer to a xml element containing child data.

      \returns eOk if the data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inChildNode(const char *nodeName, TiXmlElement* pChild);

    /** \details
      Writing attributes to the xml element.

      \param pItem [in] Pointer to the xml element to which you want to add attributes.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outAttributes(TiXmlElement* pItem);

    /** \details
      Writing child elements to the xml element.

      \param pParent [in] Pointer to the xml element to which you want to add children.

      \returns eOk if the data was written successfully; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outChildNodes(TiXmlNode* pParent);

    OdString getString(const char* buffer, const OdString& lang);
    OdResult getText(TiXmlElement* pItem, OdAnsiString& result);
    OdResult getText(TiXmlElement* pItem, const OdString& lang, OdString& result);
    void setText(TiXmlElement* pItem, const OdString& lang, const OdString& value);
    void setText(TiXmlElement* pItem, const OdString& lang, const OdAnsiString& value);

    void SetAttribute(TiXmlElement* pItem, const char* attrName, const OdAnsiString& value, bool opt = false);
    void SetAttribute(TiXmlElement* pItem, const char* attrName, const OdString& value, bool opt = false);

    void SplitToArray(const char* buffer, const char separator, OdStringArray& items);
    void SplitToArray(const char* buffer, const char separator, OdAnsiStringArray& items);
    OdString ArrayToString(const char separator, const OdStringArray& items);
    OdAnsiString ArrayToAnsiString(const char separator, const OdAnsiStringArray& items);

    OdMvdXmlRoot* m_root;
  }; 
}

#endif // !defined(ODA_ODMVDXMLELEMENT_H_INCLUDED_)

