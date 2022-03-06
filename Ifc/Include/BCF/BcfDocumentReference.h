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

#ifndef _BFC_DOCUMENT_REFERENCE_H
#define _BFC_DOCUMENT_REFERENCE_H

#include "BcfCommon.h"

#include "BcfElement.h"
#include "BcfDocumentReferenceGroup.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  /** \details
  A class that stores and operates a document reference data.
  */
  class BCF_EXPORT OdBcfDocumentReference : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfDocumentReference);
    //DOM-IGNORE-END

    /** \details
    Creates a new document reference object with default parameters.
    */
    OdBcfDocumentReference();

    /** \details
    Reads XML data into ODA data structures.
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
    Checks whether the document reference instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    //DOM-IGNORE-BEGIN
  protected:
    OdString                    m_referencedDocument;
    OdString                    m_description;
    OdBcfDocumentReferenceGroup m_documentReference;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfDocumentReference, OdBcfDocumentReference> object.
  */
  typedef OdSmartPtr<OdBcfDocumentReference> OdBcfDocumentReferencePtr;

} //namespace OdBcf

#endif // _BFC_DOCUMENT_REFERENCE_H
