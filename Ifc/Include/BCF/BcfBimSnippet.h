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

#ifndef _BFC_BIM_SNIPPET_H
#define _BFC_BIM_SNIPPET_H

#include "BcfCommon.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  /** \details
  A class that implements working with the BimSnippet data type.
  */
  class BCF_EXPORT OdBcfBimSnippet : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfBimSnippet);
    //DOM-IGNORE-END

    /** \details
    Creates a new BimSnippet object with default parameters.
    */
    OdBcfBimSnippet();

    /** \details
    Reads specified XML data into ODA data structures.
    \param pParent [in] A pointer to the parent element of the data structure.
    \returns eOk if data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inFields(TiXmlElement *pParent) ODRX_OVERRIDE;

    /** \details
    Writes data into XML structures.
    \param pParent [in] A pointer to the parent element of the data structure.
    \returns eOk if data was successfully written; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outFields(TiXmlElement *pParent) const ODRX_OVERRIDE;

    /** \details
    Checks whether the instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise, the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    //DOM-IGNORE-BEGIN
  protected:
    OdString m_reference;
    OdString m_referenceSchema;
    OdString m_snippetType;
    bool     m_isExternal;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfBimSnippet, OdBcfBimSnippet> object.
  */
  typedef OdSmartPtr<OdBcfBimSnippet> OdBcfBimSnippetPtr;

} //namespace OdBcf

#endif // _BFC_BIM_SNIPPET_H
