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

#ifndef _BFC_DIRECTION_H
#define _BFC_DIRECTION_H

#include "BcfCommon.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  /** \details
  A class that stores and operates a direction data.
  */
  class BCF_EXPORT OdBcfDirection : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfDirection);
    //DOM-IGNORE-END

    /** \details
    Creates a new direction object.
    \param x [in] A x-component of the direction object.
    \param y [in] A y-component of the direction object.
    \param z [in] A z-component of the direction object.
    \returns A smart pointer to the created <link OdBcf::OdBcfDirection, OdBcfDirection> instance.
    */
    static OdSmartPtr<OdBcfDirection> createObject(double x, double y, double z);

    /** \details
    Creates a new direction object with default parameters.
    \remarks
    The direction object's components are unset after using this constructor for instance creation.
    */
    OdBcfDirection();

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
    Checks whether the direction instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the X-axis coordinate of the direction object.
    \returns A double value that represents the X-axis coordinate.
    \remarks 
    The coordinate value returned by the method can't be modified in the calling subroutine.
    */
    const double& getX() const;

    /** \details
    Defines whether the X-axis coordinate of the direction object is not initialized.
    \returns true if the X-axis coordinate is not initialized; otherwise, the method returns false.
    */
    bool isXUnset() const;

    /** \details
    Retrieves the Y-axis coordinate of the direction object.
    \returns A double value that represents the Y-axis coordinate.
    \remarks 
    The coordinate value returned by the method can't be modified in the calling subroutine.
    */
    const double& getY() const;

    /** \details
    Defines whether the Y-axis coordinate of the direction object is not initialized.
    \returns true if the Y-axis coordinate is not initialized; otherwise, the method returns false.
    */
    bool isYUnset() const;

    /** \details
    Retrieves the Z-axis coordinate of the direction object.
    \returns A double value that represents the Z-axis coordinate.
    \remarks 
    The coordinate value returned by the method can't be modified in the calling subroutine.
    */
    const double& getZ() const;

    /** \details
    Defines whether the Z-axis coordinate of the direction object is not initialized.
    \returns true if the Z-axis coordinate is not initialized; otherwise, the method returns false.
    */
    bool isZUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    double m_x;
    double m_y;
    double m_z;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfDirection, OdBcfDirection> object.
  */
  typedef OdSmartPtr<OdBcfDirection> OdBcfDirectionPtr;

} //namespace OdBcf

#endif // _BFC_DIRECTION_H
