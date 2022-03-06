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

#ifndef _BFC_VISUALIZATION_INFO_H
#define _BFC_VISUALIZATION_INFO_H

#include "BcfCommon.h"
#include "OdArray.h"
#include "OdGUID.h"

#include "BcfElement.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfComponents;
  typedef OdSmartPtr<OdBcfComponents> OdBcfComponentsPtr;

  class OdBcfOrthogonalCamera;
  typedef OdSmartPtr<OdBcfOrthogonalCamera> OdBcfOrthogonalCameraPtr;

  class OdBcfPerspectiveCamera;
  typedef OdSmartPtr<OdBcfPerspectiveCamera> OdBcfPerspectiveCameraPtr;

  class OdBcfLines;
  typedef OdSmartPtr<OdBcfLines> OdBcfLinesPtr;

  class OdBcfClippingPlanes;
  typedef OdSmartPtr<OdBcfClippingPlanes> OdBcfClippingPlanesPtr;

  class OdBcfBitmap;
  typedef OdSmartPtr<OdBcfBitmap> OdBcfBitmapPtr;
  
    /** \details 
  A data type that represents an array of smart pointers to <link OdBcf::OdBcfBitmap, OdBcfBitmap> objects.
  */
  typedef OdArray<OdBcfBitmapPtr> OdBcfBitmapArray;

  class OdBcfSession;

  /** \details
  A class that stores visualization information within the BCF format.
  */
  class OdBcfVisualizationInfoData
  {
  public:
    /** \details 
    A smart pointer to BCF components related to the visualization information.
    */
    OdBcfComponentsPtr        m_pComponents;
    
    /** \details 
    A smart pointer to a BCF orthogonal camera object.
    */
    OdBcfOrthogonalCameraPtr  m_pOrthogonalCamera;
    
    /** \details 
    A smart pointer to a BCF perspective camera object.
    */
    OdBcfPerspectiveCameraPtr m_pPerspectiveCamera;
    
    /** \details 
    A smart pointer to a BCF array of markup lines.
    */
    OdBcfLinesPtr             m_pLines;
    
    /** \details 
    A smart pointer to a BCF array of clipping planes.
    */
    OdBcfClippingPlanesPtr    m_pClippingPlanes;
    
    /** \details 
    A smart pointer to a BCF array of bitmaps.
    */
    OdBcfBitmapArray          m_bitmap;
  protected:
  
    /** \details 
    A global unique identifier of the visualization information object.
    */
    OdGUID                    m_guid;
  };

  /** \details
  A class that stores and operates the visualization information within the BCF format.
  */
  class BCF_EXPORT OdBcfVisualizationInfo : public OdBcfElement, protected OdBcfVisualizationInfoData
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfVisualizationInfo);
    //DOM-IGNORE-END

    /** \details
    Creates a new visualization information object with default parameters.
    */
    OdBcfVisualizationInfo();

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
    Checks whether the visualization information instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the visualization info components.
    \returns A smart pointer to the <link OdBcf::OdBcfComponents, OdBcfComponents> object associated with the visualization info.
    \remarks 
    The components object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfComponentsPtr& getComponents() const;

    /** \details
    Defines whether the components of the visualization info are not initialized.
    \returns true if the components are not initialized; otherwise, the method returns false.
    */
    bool isComponentsUnset() const;

    /** \details
    Retrieves the orthogonal camera object from the visualization information instance.
    \returns A smart pointer to the <link OdBcf::OdBcfOrthogonalCamera, OdBcfOrthogonalCamera> object.
    \remarks 
    The <link OdBcf::OdBcfOrthogonalCamera, OdBcfOrthogonalCamera> object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfOrthogonalCameraPtr& getOrthogonalCamera() const;

    /** \details
    Defines whether the orthogonal camera object within the visualization information is not initialized.
    \returns true if the orthogonal camera object is not initialized; otherwise, the method returns false.
    */
    bool isOrthogonalCameraUnset() const;

    /** \details
    Retrieves the perspective camera object from the visualization information instance.
    \returns A smart pointer to the <link OdBcf::OdBcfPerspectiveCamera, OdBcfPerspectiveCamera> object.
    \remarks 
    The <link OdBcf::OdBcfPerspectiveCamera, OdBcfPerspectiveCamera> object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfPerspectiveCameraPtr& getPerspectiveCamera() const;

    /** \details
    Defines whether the perspective camera object within the visualization information is not initialized.
    \returns true if the perspective camera object is not initialized; otherwise, the method returns false.
    */
    bool isPerspectiveCameraUnset() const;

    /** \details
    Retrieves the lines object from the visualization information instance.
    \returns A smart pointer to the <link OdBcf::OdBcfLines, OdBcfLines> object.
    \remarks 
    The <link OdBcf::OdBcfLines, OdBcfLines> object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfLinesPtr& getLines() const;

    /** \details
    Defines whether the lines object within the visualization information is not initialized.
    \returns true if the lines object is not initialized; otherwise, the method returns false.
    */
    bool isLinesUnset() const;

    /** \details
    Retrieves the clipping planes from the visualization information instance.
    \returns A smart pointer to the <link OdBcf::OdBcfClippingPlanes, OdBcfClippingPlanes> object.
    \remarks 
    The <link OdBcf::OdBcfClippingPlanes, OdBcfClippingPlanes> object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfClippingPlanesPtr& getClippingPlanes() const;

    /** \details
    Defines whether the clipping planes object within the visualization information is not initialized.
    \returns true if the clipping planes object is not initialized; otherwise, the method returns false.
    */
    bool isClippingPlanesUnset() const;

    /** \details
    Retrieves bitmaps from the visualization information instance.
    \returns An array of smart pointers to <link OdBcf::OdBcfBitmap, OdBcfBitmap> objects.
    \remarks 
    The <link OdBcf::OdBcfBitmap, OdBcfBitmap> objects array returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfBitmapArray& getBitmap() const;

    /** \details
    Defines whether the array of bitmap objects within the visualization information is not initialized.
    \returns true if the bitmap objects array is not initialized; otherwise, the method returns false.
    */
    bool isBitmapUnset() const;

    /** \details
    Retrieves the global unique identifier (GUID) of the visualization information object.
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> object that contains the visualization info GUID.
    \remarks 
    The GUID returned by the method can't be modified in the calling subroutine.
    */
    const OdGUID& getGuid() const;

    /** \details
    Defines whether the global unique identifier (GUID) of the visualization info object is not initialized.
    \returns true if the GUID is not initialized; otherwise, the method returns false.
    */
    bool isGuidUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    /** \details
    Sets the global unique identifier (GUID) of the visualization info object.
    \param guidValue [in] An <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> object that represents the GUID to be set.
    */
    void setGuid(const OdGUID &guidValue);

    /** \details 
    An assignment operator for the visualizaion info objects.
    \param val [in] Another visualization info object to be assigned (right-hand operand of the assignment operation).
    \returns The reference to the visualization info object modified with the assignment operation.
    */
    OdBcfVisualizationInfo& operator = (const OdBcfVisualizationInfoData& val);

    friend class OdBcfSession;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfVisualizationInfo, OdBcfVisualizationInfo> object.
  */
  typedef OdSmartPtr<OdBcfVisualizationInfo> OdBcfVisualizationInfoPtr;

} //namespace OdBcf

#endif // _BFC_VISUALIZATION_INFO_H
