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

#ifndef _BFC_BITMAP_H
#define _BFC_BITMAP_H

#include "BcfCommon.h"
#include "OdGUID.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfPoint;
  typedef OdSmartPtr<OdBcfPoint> OdBcfPointPtr;

  class OdBcfDirection;
  typedef OdSmartPtr<OdBcfDirection> OdBcfDirectionPtr;

  class OdBcfSession;

  /** \details
  A class that contains information about the state of Bitmap data.
  */
  class OdBcfBitmapData
  {
  public:
    /**Bitmap data.*/
    OdString          m_bitmap;
    /**Bitmap data reference.*/
    OdString          m_reference;
    /**A smart pointer to the point object that define the bitmap location.*/
    OdBcfPointPtr     m_pLocation;
    /**A smart pointer to the bitmap direction vector.*/
    OdBcfDirectionPtr m_pNormal;
    /**A smart pointer to the bitmap up-vector.*/
    OdBcfDirectionPtr m_pUp;
    /**A bitmap's height value.*/
    double            m_height;
    /**A bitmap's global unique identifier (GUID).*/
    OdGUID            m_guid; //TODO: resolve documentation inconsistency
  };

  /** \details
  A class that implements storing and operating with a bitmap data type.
  */
  class BCF_EXPORT OdBcfBitmap : public OdBcfElement, protected OdBcfBitmapData
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfBitmap);
    //DOM-IGNORE-END

    /** \details
    Creates a new bitmap object with default parameters.
    */
    OdBcfBitmap();

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
    Checks whether the bitmap instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise, the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the bitmap data.
    \returns A string that contains the bitmap data.
    \remarks 
    The data returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getBitmap() const;

    /** \details
    Defines whether the bitmap object is not initialized.
    \returns true if the bitmap is not initialized; otherwise, the method returns false.
    */
    bool isBitmapUnset() const;

    /** \details
    Retrieves the bitmap's reference.
    \returns A string that contains the bitmap's reference.
    \remarks 
    The reference string returned by the method can't be modified in the calling subroutine.
    */
    const OdString& getReference() const;

    /** \details
    Defines whether the bitmap's reference is not initialized.
    \returns true if the reference is not initialized; otherwise, the method returns false.
    */
    bool isReferenceUnset() const;

    /** \details
    Retrieves the bitmap's location.
    \returns A smart pointer to the <link OdBcf::OdBcfPoint, OdBcfPoint> object that represents the location.
    \remarks 
    The location point returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfPointPtr& getLocation() const;

    /** \details
    Defines whether the bitmap's location is not initialized.
    \returns true if the location point is not initialized; otherwise, the method returns false.
    */
    bool isLocationUnset() const;

    /** \details
    Retrieves the bitmap's normal vector.
    \returns A smart pointer to the <link OdBcf::OdBcfDirection, OdBcfDirection> object that represents the normal vector.
    \remarks 
    The normal vector returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfDirectionPtr& getNormal() const;

    /** \details
    Defines whether the bitmap's normal vector is not initialized.
    \returns true if the normal vector is not initialized; otherwise, the method returns false.
    */
    bool isNormalUnset() const;

    /** \details
    Retrieves the bitmap's up-vector.
    \returns A smart pointer to the <link OdBcf::OdBcfDirection, OdBcfDirection> object that represents the up-vector.
    \remarks 
    The up-vector returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfDirectionPtr& getUp() const;

    /** \details
    Defines whether the bitmap's up-vector is not initialized.
    \returns true if the up-vector is not initialized; otherwise, the method returns false.
    */
    bool isUpUnset() const;

    /** \details
    Retrieves the bitmap's height.
    \returns A double value that contains the bitmap's height.
    \remarks 
    The height value returned by the method can't be modified in the calling subroutine.
    */
    const double& getHeight() const;

    /** \details
    Defines whether the bitmap's height is not initialized.
    \returns true if the height is not initialized; otherwise, the method returns false.
    */
    bool isHeightUnset() const;

    /** \details
    Retrieves the bitmap's global unique identifier (GUID).
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> object that contains the bitmap's GUID value.
    \remarks 
    The GUID returned by the method can't be modified in the calling subroutine.
    */
    const OdGUID& getGuid() const;

    /** \details
    Defines whether the bitmap's global unique identifier (GUID) is not initialized.
    \returns true if the GUID is not initialized; otherwise, the method returns false.
    */
    bool isGuidUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    /** \details
    Sets a new Guid value.
    \param guidValue [in] A new value to set.
    */
    void setGuid(const OdGUID &guidValue);

    /** \details
    An assignment operator for BCF bitmap objects.
    \param val [in] Another bitmap object (right-hand operand of the assignment operation).
    \returns The BCF bitmap object after assignment operation is done.
    */
    OdBcfBitmap& operator = (const OdBcfBitmapData& val);

    friend OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfBitmap, OdBcfBitmap> object.
  */
  typedef OdSmartPtr<OdBcfBitmap> OdBcfBitmapPtr;

} //namespace OdBcf

#endif // _BFC_BITMAP_H
