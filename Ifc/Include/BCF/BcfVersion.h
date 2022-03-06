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

#ifndef _BFC_VERSION_H
#define _BFC_VERSION_H

#include "BcfCommon.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfSession;

  /** \details
  A class that stores and operates the information about a version.
  */
  class BCF_EXPORT OdBcfVersion : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfVersion);
    //DOM-IGNORE-END

    /** \details
    Creates a new version object with default parameters.
    */
    OdBcfVersion();

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
    Checks whether the version instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    //DOM-IGNORE-BEGIN
  protected:
    /**The detailed version.*/
    OdString m_detailedVersion;
    /**The identifier of the version.*/
    OdString m_versionId;

    /** \details
    Sets the detailed version information.
    \param detailedVersionValue [in] A string that contains the detailed version information.
    */
    void setDetailedVersion(const OdString &detailedVersionValue);

    /** \details
    Retrieves the detailed version information.
    \returns A string that contains the detailed version information.
    \remarks 
    The string object returned by the method can be modified in the calling subroutine.
    */
    OdString& getDetailedVersion();

    /** \details
    Retrieves the detailed version information.
    \returns A string that contains the detailed version information.
    \remarks 
    The string object returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getDetailedVersion() const;

    /** \details
    Defines whether the detailed version information is not initialized.
    \returns true if the detailed version information is not initialized; otherwise, the method returns false.
    */
    bool isDetailedVersionUnset() const;

    /** \details
    Sets the identifier of the version.
    \param versionIdValue [in] A string that contains the identifier of the version.
    */
    void setVersionId(const OdString &versionIdValue);

    /** \details
    Retrieves the version identifier.
    \returns A string that contains the version identifier.
    \remarks 
    The identifier value returned by the method can be modified in the calling subroutine.
    */
    OdString& getVersionId();

    /** \details
    Retrieves the version identifier.
    \returns A string that contains the version identifier.
    \remarks 
    The identifier value returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getVersionId() const;

    /** \details
    Defines whether the version identifier is not initialized.
    \returns true if the version identifier is not initialized; otherwise, the method returns false.
    */
    bool isVersionIdUnset() const;


    friend OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfVersion, OdBcfVersion> object.
  */
  typedef OdSmartPtr<OdBcfVersion> OdBcfVersionPtr;

} //namespace OdBcf

#endif // _BFC_VERSION_H
