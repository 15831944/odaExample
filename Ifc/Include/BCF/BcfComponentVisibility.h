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

#ifndef _BFC_COMPONENT_VISIBILITY_H
#define _BFC_COMPONENT_VISIBILITY_H

#include "BcfCommon.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfExceptions;
  typedef OdSmartPtr<OdBcfExceptions> OdBcfExceptionsPtr;

  class OdBcfSession;

  /** \details
  A class that stores data about component visibility.
  */
  class OdBcfComponentVisibilityData
  {
  protected:
    /**A smart pointer to visibility exceptions.*/
    OdBcfExceptionsPtr m_pExceptions;
    /**A boolean value that determines the default component visibility.*/
    bool               m_defaultVisibility;

    friend OdBcfSession;
  };

  /** \details
  A class that stores and operates component visibility data.
  */
  class BCF_EXPORT OdBcfComponentVisibility : public OdBcfElement, protected OdBcfComponentVisibilityData
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfComponentVisibility);
    //DOM-IGNORE-END

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
    Checks whether the component visibility instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the exceptions for the visibility of components.
    \returns A smart pointer to the <link OdBcf::OdBcfExceptions, OdBcfExceptions> object that represents the version.
    \remarks 
    The exceptions object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfExceptionsPtr& getExceptions() const;

    /** \details
    Defines whether the exceptions object is not initialized.
    \returns true if the exceptions object is not initialized; otherwise, the method returns false.
    */
    bool isExceptionsUnset() const;

    /** \details
    Retrieves whether the default visibility settings are applied.
    \returns A true if the default visibility settings are applied; otherwise, the method returns false.
    \remarks 
    The boolean value returned by the method can't be modified in the calling subroutine.
    */
    const bool& getDefaultVisibility() const;

    /** \details
    Defines whether the value of the flag that determines if the default visibility settings are applied or not is not initialized.
    \returns true if the flag value is not initialized; otherwise, the method returns false.
    */
    bool isDefaultVisibilityUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    OdBcfComponentVisibility& operator = (const OdBcfComponentVisibilityData &val);

    friend OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfComponentVisibility, OdBcfComponentVisibility> object.
  */
  typedef OdSmartPtr<OdBcfComponentVisibility> OdBcfComponentVisibilityPtr;

} //namespace OdBcf

#endif // _BFC_COMPONENT_VISIBILITY_H
