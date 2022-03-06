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

#ifndef _BFC_POINT_H
#define _BFC_POINT_H

#include "BcfCommon.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  /** \details
  A class that represents a point object within the BCF format.
  */
  class BCF_EXPORT OdBcfPoint : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfPoint);
    //DOM-IGNORE-END

    /** \details
    Creates a new point object.
    \param x [in] A point coordinate along the X-axis.
    \param y [in] A point coordinate along the Y-axis.
    \param z [in] A point coordinate along the Z-axis.
    \returns A smart pointer to the created <link OdBcf::OdBcfPoint, OdBcfPoint> instance.
    */
    static OdSmartPtr<OdBcfPoint> createObject(double x, double y, double z);

    /** \details
    Creates a new point object with default parameters.
    */
    OdBcfPoint();

    /** \details
    Reads XML data into ODA data structures.
    \param pParent [in] A pointer to the parent element of the data structure.
    \returns eOk if data was successfully read; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult inFields(TiXmlElement *pParent) ODRX_OVERRIDE;

    /** \details
    Writes data into XML structures.
    \param pParent [in] A pointer to the parent element of the data structure.
    \returns Returns eOk if data was successfully written; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult outFields(TiXmlElement *pParent) const ODRX_OVERRIDE;

    /** \details
    Checks whether instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the X-axis coordinate of the point.
    \returns A double value that contains the X-axis coordinate of the point.
    \remarks 
    The coordinate value returned by the method can't be modified in the calling subroutine.
    */
    const double& getX() const;

    /** \details
    Defines whether the X-axis coordinate value is not initialized.
    \returns true if the coordinate value is not initialized; otherwise, the method returns false.
    */
    bool isXUnset() const;

    /** \details
    Retrieves the Y-axis coordinate of the point.
    \returns A double value that contains the Y-axis coordinate of the point.
    \remarks 
    The coordinate value returned by the method can't be modified in the calling subroutine.
    */
    const double& getY() const;

    /** \details
    Defines whether the Y-axis coordinate value is not initialized.
    \returns true if the coordinate value is not initialized; otherwise, the method returns false.
    */
    bool isYUnset() const;

    /** \details
    Retrieves the Z-axis coordinate of the point.
    \returns A double value that contains the Z-axis coordinate of the point.
    \remarks 
    The coordinate value returned by the method can't be modified in the calling subroutine.
    */
    const double& getZ() const;

    /** \details
    Defines whether the Z-axis coordinate value is not initialized.
    \returns true if the coordinate value is not initialized; otherwise, the method returns false.
    */
    bool isZUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    /**The X-axis coordinate of the point.*/
    double m_x;
    /**The Y-axis coordinate of the point.*/
    double m_y;
    /**The Z-axis coordinate of the point.*/
    double m_z;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfPoint, OdBcfPoint> object.
  */
  typedef OdSmartPtr<OdBcfPoint> OdBcfPointPtr;

} //namespace OdBcf

#endif // _BFC_POINT_H
