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

#ifndef __TNW_VIEWPOINT_H__
#define __TNW_VIEWPOINT_H__

#include "NwObject.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#include "NwCameraMode.h"
#include "NwLightType.h"
#include "NwModeType.h"
#include "NwViewType.h"

class OdGeQuaternion;
class OdGeVector3d;
class OdGePoint3d;

/** \details
  This class represents a view of models.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwViewpoint : public OdNwObject
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwViewpoint);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor. Creates a new object of the OdNwViewpoint class.
  */
  OdNwViewpoint();

public:
  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwViewpoint();

public:

  /** \details
    Returns the angular speed of the camera.

    \returns Angular speed of the camera as a double value.
  */
  double getAngularSpeed() const;

  /** \details
    Returns the distance from the eye point to the far plane along the view
    direction.

    \returns Distance from the eye point to the far plane as a double value.

    \remarks
    Must be greater than the near distance.
  */
  double getFarDistance() const;

  /** \details
    Returns the focal distance of the camera.

    \returns Focal distance of the camera as a double value.
  */
  double getFocalDistance() const;

  /** \details
    Indicates whether the AngularSpeed is set.

    \returns True if the AngularSpeed is set, or false otherwise.
  */
  bool hasAngularSpeed() const;

  /** \details
    Indicates whether the FocalDistance is set.

    \returns True if the FocalDistance is set, or false otherwise.
  */
  bool hasFocalDistance() const;

  /** \details
    Indicates whether the Lighting is set.

    \returns True if the Lighting is set, or false otherwise.
  */
  bool hasLighting() const;

  /** \details
    Indicates whether the LinearSpeed is set.

    \returns True if the LinearSpeed is set, or false otherwise.
  */
  bool hasLinearSpeed() const;

  /** \details
    Indicates whether the RenderStyle is set.

    \returns True if the RenderStyle is set, or false otherwise.
  */
  bool hasRenderStyle() const;

  /** \details
    Returns whether the WorldUpVector is set.

    \returns True if the WorldUpVector is set, or false otherwise.
  */
  bool hasWorldUpVector() const;

  /** \details
    Returns the defined camera's field of view in a combination with the aspect
    ratio.

    \returns Defined camera's field of view in a combination with the aspect
    ratio as a double value.

    \remarks
    For perspective, returns the vertical field of the view (the angle between
    the top and bottom planes of the camera view frustum).
    For orthographic, returns the distance between the top and bottom planes of
    the camera view frustum.
  */
  double getHeightField() const;

  /** \details
    Returns the required horizontal scaling of an image when adapting the camera
    view to the display window.

    \returns Required horizontal scaling of an image as a double value.
  */
  double getHorizontalScale() const;

  /** \details
    Returns the type of lighting used for this viewpoint.

    \returns Type of lighting used for this viewpoint.

    \remarks
    Returns one of the following:

    <table>
    Name                        Value   Description
    NwLightType::NO_LIGHT       0       Turns off lighting completely.
    NwLightType::SCENE_LIGHT    1       Lights from the user in the model.
    NwLightType::HEAD_LIGHT     2       An automatic headlight from the viewer.
    NwLightType::FULL_LIGHT     3       Advanced level of lighting from the application.
    </table>
  */
  NwLightType::Enum getLighting() const;

  /** \details
    Returns the linear speed of the camera.

    \returns Linear speed of the camera as a double value.
  */
  double getLinearSpeed() const;

  /** \details
    Returns the distance from the eye point to the near plane along the view
    direction.

    \returns Distance from the eye point to the near plane as a double value.

    \remarks
    Must be greater than zero.
  */
  double getNearDistance() const;

  /** \details
    Returns the position of the camera.

    \returns Position of the camera as an OdGePoint3d value.
  */
  OdGePoint3d getPosition() const;

  /** \details
    Returns the projection type of the current viewpoint.

    \returns Projection type of the current viewpoint.

    \remarks
    Returns one of the following:

    <table>
    Name                        Value   Description
    NwViewType::PERSPECTIVE     0       Perspective viewpoint.
    NwViewType::ORTHOGRAPHIC    1       Orthographic viewpoint.
    </table>
  */
  NwViewType::Enum getProjection() const;

  /** \details
    Returns the style used for rendering.

    \returns Style used for rendering.

    \remarks
    Returns one of the following:

    <table>
    Name                        Value   Description
    NwModeType::FULL_RENDER     0       Highest quality, as specified in the model.
    NwModeType::SHADED          1       Smooth shaded (simple shade model, no textures).
    NwModeType::WIREFRAME       2       Wireframe.
    NwModeType::HIDDEN_LINE     3       Hidden-line wireframe.
    </table>
  */
  NwModeType::Enum getRenderStyle() const;

  /** \details
    Returns the rotation of the camera from the base orientation.

    \returns Rotation of the camera from the base orientation as an
    OdGeQuaternion value.
  */
  OdGeQuaternion getRotation() const;

  /** \details
    Returns the avatar used for this viewpoint.

    \returns Avatar used for this viewpoint.
  */
  OdString getAvatar() const;

  /** \details
    Returns the type of avatar for this viewpoint.

    \returns Avatar type for this viewpoint.

    \remarks
    Returns one of the following:

    <table>
    Name                        Value   Description
    NwCameraMode::FIRST         0       First-person mode.
    NwCameraMode::THIRD         1       Third-person mode.
    </table>
  */
  NwCameraMode::Enum getViewerCameraMode() const;

  /** \details
    Returns the up vector.

    \returns Up vector as an OdGeVector3d value.
  */
  OdGeVector3d getWorldUpVector() const;

  /** \details
    Returns the aspect ratio of the camera (width/height).

    \returns Aspect ratio as a double value.
  */
  double getViewAspect() const;

public:
  /** \details
    Sets the projection type of the viewpoint.

    \param type [in] Projection type.
    \returns eOk if the type is set to the viewpoint, or an appropriate error
    code otherwise.

    \remarks
    The type must be one of the following:

    <table>
    Name                        Value   Description
    NwViewType::PERSPECTIVE     0       Perspective viewpoint.
    NwViewType::ORTHOGRAPHIC    1       Orthographic viewpoint.
    </table>
  */
  OdResult setProjection(NwViewType::Enum type);

  /** \details
    Sets the style used for rendering.

    \param style [in] Visual style for rendering.
    \returns eOk if the style is set to the viewpoint, or an appropriate error
    code otherwise.

    \remarks
    The style must be one of the following:

    <table>
    Name                        Value   Description
    NwModeType::FULL_RENDER     0       Highest quality, as specified in the model.
    NwModeType::SHADED          1       Smooth shaded (simple shade model, no textures).
    NwModeType::WIREFRAME       2       Wireframe.
    NwModeType::HIDDEN_LINE     3       Hidden-line wireframe.
    </table>
  */
  OdResult setRenderStyle(NwModeType::Enum style);

  /** \details
    Sets the focal distance of the camera.

    \param value [in] Focal distance value.
    \returns eOk if the focal distance is set to the viewpoint, or an
    appropriate error code otherwise.
  */
  OdResult setFocalDistance(double value);

  /** \details
    Sets the up vector of the viewpoint.

    \param up [in] Constant reference to the OdGeVector3d object with the up vector.
    \returns eOk if the up vector is set to the viewpoint, or an appropriate
    error code otherwise.
  */
  OdResult setWorldUpVector(const OdGeVector3d& up);

  /** \details
    Sets the position of the camera.

    \param pos [in] Constant reference to the OdGePoint3d object with the point of camera's position.
    \returns eOk if the position point is set to the viewpoint, or an
    appropriate error code otherwise.
  */
  OdResult setPosition(const OdGePoint3d& pos);

  /** \details
    Sets the rotation of the camera from the base orientation.

    \param rot [in] Constant reference to the OdGeQuaternion object with the rotation of the camera.
    \returns eOk if the rotation is set to the viewpoint, or an appropriate
    error code otherwise.
  */
  OdResult setRotation(const OdGeQuaternion& rot);

  /** \details
    Sets the defined camera's field of view in a combination with the aspect
    ratio.

    \param value [in] Camera's field of view.
    \returns eOk if the field of view is set to the viewpoint, or an appropriate
    error code otherwise.

    \remarks
    For perspective, this is the vertical field of view (the angle between the
    top and bottom planes of the camera's view frustum).
    For orthographic, this is the distance between the top and bottom planes of
    the camera's view frustum.
  */
  OdResult setHeightField(double value);

  /** \details
    Sets the aspect ratio of the camera (width/height).

    \param value [in] Aspect ratio of the camera value.
    \returns eOk if the view aspect ratio is set to the viewpoint, or an
    appropriate error code otherwise.
  */
  OdResult setViewAspect(double value);

  /** \details
    Sets the distance from the eye point to the near plane along the view
    direction.

    \param value [in] Near distance value.
    \returns eOk if the near distance is set to the viewpoint, or an appropriate
    error code otherwise.
  */
  OdResult setNearDistance(double value);

  /** \details
    Sets the distance from the eye point to the far plane along the view
    direction.

    \param value [in] Far distance value.
    \returns eOk if the far distance is set to the viewpoint, or an appropriate
    error code otherwise.
  */
  OdResult setFarDistance(double value);
};

/** \details
  This template class is a specialization of the OdSmartPtr class for
  OdNwViewpoint object pointers.
*/
typedef OdSmartPtr<OdNwViewpoint> OdNwViewpointPtr;

#endif //__TNW_VIEWPOINT_H__
