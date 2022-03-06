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

#ifndef _BFC_PERSPECTIVE_CAMERA_H
#define _BFC_PERSPECTIVE_CAMERA_H

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
  A class that stores and operates a perspective camera data within the BCF format.
  */
  class BCF_EXPORT OdBcfPerspectiveCamera : public OdBcfElement
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfPerspectiveCamera);
    //DOM-IGNORE-END

    /** \details
    Creates a new perspective camera object.
    \param pCameraViewPoint [in] A smart pointer to the object that represents the camera's view point.
    \param pCameraDirection [in] A smart pointer to the object that represents the camera direction.
    \param pCameraUpVector  [in] A smart pointer to the object that represents the camera's up vector.
    \param fieldOfView      [in] A value of the camera field of view.
    \returns A smart pointer to the created <link OdBcf::OdBcfPerspectiveCamera, OdBcfPerspectiveCamera> instance.
    */
    static OdSmartPtr<OdBcfPerspectiveCamera> createObject(
      const OdBcfPointPtr     &pCameraViewPoint,
      const OdBcfDirectionPtr &pCameraDirection,
      const OdBcfDirectionPtr &pCameraUpVector,
      double                   fieldOfView);

    /** \details
    Creates a new perspective camera object with default parameters.
    */
    OdBcfPerspectiveCamera();

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
    Checks whether the perspective camera instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const ODRX_OVERRIDE;

    /** \details
    Retrieves the perspective camera viewpoint.
    \returns A smart pointer to the <link OdBcf::OdBcfPoint, OdBcfPoint> object that represents the camera viewpoint.
    \remarks 
    The point returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfPointPtr& getCameraViewPoint() const;

    /** \details
    Defines whether the perspective camera viewpoint is not initialized.
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
    Retrieves the perspective camera's field of view.
    \returns A double value that contains the field of view.
    \remarks 
    The field view value returned by the method can't be modified in the calling subroutine.
    */
    const double& getFieldOfView() const;

    /** \details
    Defines whether the perspective camera's field of view is not initialized. 
    \returns true if the field of value is not initialized; otherwise, the method returns false.
    */
    bool isFieldOfViewUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    OdBcfPointPtr     m_pCameraViewPoint;
    OdBcfDirectionPtr m_pCameraDirection;
    OdBcfDirectionPtr m_pCameraUpVector;
    double            m_fieldOfView;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfPerspectiveCamera, OdBcfPerspectiveCamera> object.
  */
  typedef OdSmartPtr<OdBcfPerspectiveCamera> OdBcfPerspectiveCameraPtr;

} //namespace OdBcf

#endif // _BFC_PERSPECTIVE_CAMERA_H
