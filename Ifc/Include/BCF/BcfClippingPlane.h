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

#ifndef _BFC_CLIPPING_PLANE_H
#define _BFC_CLIPPING_PLANE_H

#include "BcfCommon.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfPoint;
  typedef OdSmartPtr<OdBcfPoint> OdBcfPointPtr;

  class OdBcfDirection;
  typedef OdSmartPtr<OdBcfDirection> OdBcfDirectionPtr;

  /** \details
  A class that stores and operates the information about a clipping plane.
  */
  class BCF_EXPORT OdBcfClippingPlane : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfClippingPlane);
    //DOM-IGNORE-END

    /** \details
    Creates a new clipping plane object.
    \param pLocation  [in] A pointer to the location that defines the clipping plane.
    \param pDirection [in] A pointer to the direction that defines the clipping plane.
    \returns A smart pointer to the created <link OdBcf::OdBcfClippingPlane, OdBcfClippingPlane> instance.
    */
    static OdSmartPtr<OdBcfClippingPlane> createObject(
      const OdBcfPointPtr     &pLocation,
      const OdBcfDirectionPtr &pDirection);

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
    Checks whether the instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise, the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the location of the clipping plane object.
    \returns A smart pointer to the <link OdBcf::OdBcfPoint, OdBcfPoint> object that represents the location.
    \remarks 
    The location point returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfPointPtr& getLocation() const;

    /** \details
    Defines whether the clipping plane's location is not initialized.
    \returns true if the location is not initialized; otherwise, the method returns false.
    */
    bool isLocationUnset() const;

    /** \details
    Retrieves the direction of the clipping plane object.
    \returns A smart pointer to the <link OdBcf::OdBcfDirection, OdBcfDirection> object that represents the direction.
    \remarks 
    The direction object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfDirectionPtr& getDirection() const;

    /** \details
    Defines whether the clipping plane's direction is not initialized.
    \returns true if the direction is not initialized; otherwise, the method returns false.
    */
    bool isDirectionUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    OdBcfPointPtr     m_pLocation;
    OdBcfDirectionPtr m_pDirection;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfClippingPlane, OdBcfClippingPlane> object.
  */
  typedef OdSmartPtr<OdBcfClippingPlane> OdBcfClippingPlanePtr;

} //namespace OdBcf

#endif // _BFC_CLIPPING_PLANE_H
