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

#ifndef __NW_SAVEDANIMKEYFRAME_H__
#define __NW_SAVEDANIMKEYFRAME_H__

#include "NwSavedGroupItem.h"
#include "NwViewType.h"

class OdGeQuaternion;

/**
 This class represents animation camera key frame.
 
 <group OdNw_Classes>
*/
class NWDBEXPORT OdNwSavedAnimKeyFrame : public OdNwSavedGroupItem
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwSavedAnimKeyFrame);
  //DOM-IGNORE-END
public:
  /** \details
    Default constructor.
  */
  OdNwSavedAnimKeyFrame();

  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwSavedAnimKeyFrame();
  
  /** \details
    Returns current position in the playback.
    
    \returns The value of the playback positions in double.
  */
  double getTime() const;
  
  /** \details
   Determines whether values are automatically interpolated between the current and the last keyframes.
  
   \returns True if values are automatically interpolated between the current and the last keyframes successfully, or false otherwise.
  */
  bool isInterpolation() const;
  
  /** \details
    Returns focal length of the camera.
    
    \returns A value of focal length of the camera lens.
   */
  double getFocalDistance() const;
  
  /** \details
    Returns the projection type of the camera.

    \returns
    Projection type of the camera that can be one of the following:

    <table>
    Name                        Value   Description
    NwViewType::PERSPECTIVE     0       Perspective viewpoint.
    NwViewType::ORTHOGRAPHIC    1       Orthographic viewpoint.
    </table>
  */
  NwViewType::Enum getCameraProjection() const;
  
  /** \details
    Returns the position of the camera.

    \returns Position of the camera as an OdGePoint3d value.
  */
  const OdGePoint3d& getCameraPosition() const;
  
  /** \details
    Returns the rotation of the camera from the base orientation.

    \returns Rotation of the camera from the base orientation as an
    OdGeQuaternion value.
  */
  const OdGeQuaternion& getCameraRotation() const;
  
  /** \details
    Returns the aspect ratio of the camera (width/height).

    \returns Aspect ratio as a double value.
  */
  double getCameraViewAspect() const;
  
  /** \details
    Returns the defined camera's field of view in a combination with the aspect
    ratio.

    \returns Defined camera's field of view in a combination with the aspect
    ratio as a double value.

    \remarks
    For perspective, returns the vertical field of the view (the angle in radians
    between the top and bottom planes of the camera view frustum).
    For orthographic, returns the distance between the top and bottom planes of
    the camera view frustum.
  */
  double getCameraHeightField() const;

  /** \details
    Returns the distance from the eye point to the near plane along the view
    direction.

    \returns Distance from the eye point to the near plane as a double value.

    \remarks
    Must be greater than zero.
  */
  double getCameraNearDistance() const;

  /** \details
    Returns the distance from the eye point to the far plane along the view
    direction.

    \returns Distance from the eye point to the far plane as a double value.

    \remarks
    Must be greater than the near distance.
  */
  double getCameraFarDistance() const;
  
  /** \details
    Returns the required vertical scaling of an image when adapting the camera
    view to the display window.

    \returns Required vertical scaling of an image as a double value.
  */
  double getCameraVerticalScale() const;
  
  /** \details
    Returns the required horizontal scaling of an image when adapting the camera
    view to the display window.

    \returns Required horizontal scaling of an image as a double value.
  */
  double getCameraHorizontalScale() const;

};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwSavedAnimKeyFrame object pointers.
*/
typedef OdSmartPtr<OdNwSavedAnimKeyFrame> OdNwSavedAnimKeyFramePtr;

#endif /* __NW_SAVEDANIMKEYFRAME_H__ */
