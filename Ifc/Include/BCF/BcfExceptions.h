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

#ifndef _BFC_EXCEPTIONS_H
#define _BFC_EXCEPTIONS_H

#include "BcfCommon.h"
#include "OdArray.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfComponent;
  typedef OdSmartPtr<OdBcfComponent> OdBcfComponentPtr;
  typedef OdArray<OdBcfComponentPtr> OdBcfComponentArray;

  class OdBcfSession;

  /** \details
  A class that stores and operates BCF exceptions data.
  */
  class BCF_EXPORT OdBcfExceptions : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfExceptions);
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
    Checks whether the exception instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the array of components associated with the exceptions.
    \returns An array of smart pointers to <link OdBcf::OdBcfComponent, OdBcfComponent> objects.
    \remarks 
    The array of components returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfComponentArray& getComponent() const;

    /** \details
    Defines whether the array of components associated with the exceptions is not initialized.
    \returns true if the array of components is not initialized; otherwise, the method returns false.
    */
    bool isComponentUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    OdBcfComponentArray m_component;

    static OdSmartPtr<OdBcfExceptions> createObject(const OdBcfComponentArray &component);

    friend OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfExceptions, OdBcfExceptions> object.
  */
  typedef OdSmartPtr<OdBcfExceptions> OdBcfExceptionsPtr;

} //namespace OdBcf

#endif // _BFC_EXCEPTIONS_H
