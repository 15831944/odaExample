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

#ifndef _BFC_DOCUMENT_REFERENCE_GROUP_H
#define _BFC_DOCUMENT_REFERENCE_GROUP_H

#include "OdPlatformSettings.h"
#include "IfcBuildOptions.h"

#include "OdGUID.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  /** \details
  A class that stores and operates a document reference group data.
  */
  class BCF_EXPORT OdBcfDocumentReferenceGroup
  {
  public:
    /** \details 
    Creates a new document reference group object with default parameters.
    */
    OdBcfDocumentReferenceGroup();

    /** \details
   Checks whether the document reference group instance has all required fields initialized.
   \returns true if all required fields are initialized; otherwise the method returns false.
   */
    virtual bool validate() const;

    /** \details 
    A document reference group global unique identifier (GUID).
    */
    OdGUID m_guid;
    
    /** \details 
    A flag that determines whether the document reference group is an external one (if equals to true) or not (if equals to false).
    */
    bool   m_isExternal;
  };

} //namespace OdBcf

#endif // _BFC_DOCUMENT_REFERENCE_GROUP_H
