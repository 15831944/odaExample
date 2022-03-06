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

#ifndef _BFC_ORTHOGONAL_CAMERA_H
#define _BFC_ORTHOGONAL_CAMERA_H

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
  A class that stores an orthogonal camera data within the BCF format.
  */
  class OdBcfOrthogonalCameraData
  {
  public:
  };

  /** \details
  A class that stores and operates an orthogonal camera data within the BCF format.
  */
  class BCF_EXPORT OdBcfOrthogonalCamera : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfOrthogonalCamera);
    //DOM-IGNORE-END

    /** \details
    Creates a new orthogonal camera object.
    \param pCameraViewPoint [in] A smart pointer to the object that represents the camera view point.
    \param pCameraDirection [in] A smart pointer to the object that represents the camera direction.
    \param pCameraUpVector  [in] A smart pointer to the object that represents the camera up vector.
    \param viewToWorldScale [in] A value of the view to world scale.
    \returns A smart pointer to the created <link OdBcf::OdBcfOrthogonalCamera, OdBcfOrthogonalCamera> instance.
    */
    static OdSmartPtr<OdBcfOrthogonalCamera> createObject(
      const OdBcfPointPtr     &pCameraViewPoint,
      const OdBcfDirectionPtr &pCameraDirection,
      const OdBcfDirectionPtr &pCameraUpVector,
      double                   viewToWorldScale);

    /** \details
    Creates a new orthogonal camera object with default parameters.
    */
    OdBcfOrthogonalCamera();

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
    Checks whether the orthogonal camera instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the camera viewpoint.
    \returns A smart pointer to the <link OdBcf::OdBcfPoint, OdBcfPoint> object that represents the camera viewpoint.
    \remarks 
    The point returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfPointPtr& getCameraViewPoint() const;

    /** \details
    Defines whether the camera viewpoint is not initialized.
    \returns true if the camera viewpoint is not initialized; otherwise, the method returns false.
    */
    bool isCameraViewPointUnset() const;

    /** \details
    Retrieves the camera direction.
    \returns A smart pointer to the <link OdBcf::OdBcfDirection, OdBcfDirection> object that represents the camera direction.
    \remarks 
    The direction object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfDirectionPtr& getCameraDirection() const;

    /** \details
    Defines whether the camera direction is not initialized.
    \returns true if the camera direction is not initialized; otherwise, the method returns false.
    */
    bool isCameraDirectionUnset() const;

    /** \details
    Retrieves the camera up-vector.
    \returns A smart pointer to the <link OdBcf::OdBcfDirection, OdBcfDirection> object that represents the camera up-vector.
    \remarks 
    The direction object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfDirectionPtr& getCameraUpVector() const;

    /** \details
    Defines whether the camera up-vector is not initialized.
    \returns true if the up-vector object is not initialized; otherwise, the method returns false.
    */
    bool isCameraUpVectorUnset() const;

    /** \details
    Retrieves the view-to-world scale of the camera.
    \returns A double value that contains the scale.
    \remarks 
    The scale value returned by the method can't be modified in the calling subroutine.
    */
    const double& getViewToWorldScale() const;

    /** \details
    Defines whether the view-to-world scale of the camera is not initialized.
    \returns true if the scale value is not initialized; otherwise, the method returns false.
    */
    bool isViewToWorldScaleUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    /**The camera view point.*/
    OdBcfPointPtr     m_pCameraViewPoint;
    /**The camera direction.*/
    OdBcfDirectionPtr m_pCameraDirection;
    /**The camera up-vector.*/
    OdBcfDirectionPtr m_pCameraUpVector;
    /**The view-to-world scale of the camera.*/
    double            m_viewToWorldScale;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfOrthogonalCamera, OdBcfOrthogonalCamera> object.
  */
  typedef OdSmartPtr<OdBcfOrthogonalCamera> OdBcfOrthogonalCameraPtr;

} //namespace OdBcf

#endif // _BFC_ORTHOGONAL_CAMERA_H
