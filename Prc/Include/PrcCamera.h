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

#ifndef _PRCCAMERA_INCLUDED_
#define _PRCCAMERA_INCLUDED_ 
 

#include "PrcBase.h"
SMARTPTR(OdPrcCamera);

/** \details 
<group PRC_Graphic_Classes> 

Class stores information about a camera.
*/
class PRC_TOOLKIT OdPrcCamera : public OdPrcReferencedBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcCamera)
  //DOM-IGNORE-END

  /** \details
  Returns the current location of the camera.
  The location is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new camera location.
  */
  OdGePoint3d &location();
  
  /** \details
  Returns the current location of the camera.
  */
  const OdGePoint3d &location() const;
  
  /** \details
  Returns the current position which the camera is looking at.
  The position is returned as a reference to an OdGePoint3d object, therefore it can be used to set a new position.
  */
  OdGePoint3d &lookAt();
  
  /** \details
  Returns the current position which the camera is looking at.
  */
  const OdGePoint3d &lookAt() const;
  
  /** \details
  Returns the current up-direction vector of the camera.
  The up-direction vector is returned as a reference to an OdGeVector3d object, therefore it can be used to set a new up-direction vector.
  */
  OdGeVector3d &up();
  
  /** \details
  Returns the current up-direction vector of the camera.
  */
  const OdGeVector3d &up() const;
  
  /** \details
  Sets a new value of the field angle on the y-direction of the camera.

  \param yFov [in] A new value of the field angle to be set. Must be specified in radians.
  */
  void setYFov(double yFov);
  
  /** \details
  Returns the current field angle on the y-direction of the camera.
  The angle is returned in radians.
  */
  double yFov() const;
  
  /** \details
  Sets a new value of the aspect ratio of X to Y.

  \param aspect_ratio [in] A new value of the aspect ratio to be set.
  */
  void setAspectRatio(double aspect_ratio);
  
  /** \details
  Returns the current aspect ratio of X to Y.
  */
  double aspectRatio() const;
  
  /** \details
  Sets a new value of the near clipping plane distance.

  \param zNear [in] A new value of the near clipping plane distance to be set.
  */
  void setZNear(double zNear);
  
  /** \details
  Returns the current near clipping plane distance.
  */
  double zNear() const;
  
  /** \details
  Sets a new value of the far clipping plane distance.

  \param zFar [in] A new value of the far clipping plane distance.
  */
  void setZFar(double zFar);
  
  /** \details
  Returns the current far clipping plane distance.
  */
  double zFar() const;
  
  /** \details
  Sets a new value of the zoom factor.

  \param zoom_factor [in] A new value of the zoom factor to be set.
  */
  void setZoomFactor(double zoom_factor);
  
  /** \details
  Returns the current zoom factor.
  */
  double zoomFactor() const;
  
  /** \details
  Sets a new value of the field angle on the x-direction.

  \param xFov [in] A new value of the field angle to be set in radians.
  */
  void setXFov(double xFov);
  
  /** \details
  Returns the current value of the field angle on the x-direction. 
  The field angle is returned in radians.
  */
  double xFov() const;
  
  /** \details
  Sets a new value of the orthographic flag.
  The orthographic flag determines whether the projection is orthographic (true) or perspective (false).

  \param orthographic [in] A new value of the orthographic flag.
  */
  void setOrthographic(bool orthographic);
  
  /** \details
  Returns the current value of the orthographic flag.
  The orthographic flag determines whether the projection is orthographic (true) or perspective (false).
  */
  bool orthographic() const;
};

#endif // _PRCCAMERA_INCLUDED_

