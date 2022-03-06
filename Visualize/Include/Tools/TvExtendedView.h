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

#ifndef _ODTV_EXTENDED_H_INCLUDED_
#define _ODTV_EXTENDED_H_INCLUDED_

#include "TvToolsExport.h"
#include "TvGsView.h"

#include "Ge/GeQuaternion.h"
#include "TvViewCube.h"
#include "OdPerfTimer.h"

/** \details
  The abstract interface class that provides control of Visualize SDK animation.
  \sa
  <link tv_tools_animation, Work with Animation Tool>
*/
class ODTVTOOLS_EXPORT OdTvAnimation
{
public:

  /** \details
    Destroys the animation object.
  */
  virtual ~OdTvAnimation() {};

  /** \details 
    Starts the animation.
    
    \returns Returns true if the animation is started successfully; otherwise the method returns false.
  */
  virtual bool start() = 0;

  /** \details 
    Performs the next animation step.
    
    \returns Returns true if the animation step is performed successfully; otherwise the method returns false.
  */
  virtual bool step() = 0;

  /** \details
    Checks whether the animation is running.
    
    \returns Returns true if the animation is running; otherwise the method returns false.
  */
  virtual bool isRunning() = 0;

  /** \details
    Resets the animation.
  */
  virtual void reset() = 0;

  /** \details
    Checks whether the animation is ready.
    
    \returns Returns true if the animation is ready; otherwise the method returns false.
  */
  virtual bool isReady() = 0;
};


/** \details
  The base interface class for an extended <link OdTvGsView, view> object.
  \sa
  <link tv_tools_extended_views, Work with Extended Views>
*/
class ODTVTOOLS_EXPORT OdTvExtendedView
{
public:

  ODRX_HEAP_OPERATORS();

  /** \details
    Extended view types.
  */
  enum e3DViewType
  {
    kCustom = -1, // A custom view.
    kTop,         // A top view.
    kBottom,      // A bottom view.
    kLeft,        // A left view.
    kRight,       // A right view.
    kFront,       // A front view.
    kBack,        // A back view.
    kSW,          // A southwest view.
    kSE,          // A southeast view.
    kNE,          // A northeast view.
    kNW           // A northwest view.
  };

  /** \details
    Creates a new extended view object based on a specified <link OdTvGsView, view>.
    
    \param viewId [in] An identifier of a view object that is the base for the created object.
  */
  OdTvExtendedView(OdTvGsViewId viewId);

  /** \details
    Destroys an extended view object.
  */
  virtual ~OdTvExtendedView();

  /** \details
    Retrieves the identifier of the internal view object.
    
    \returns Returns the identifier of the internal <link OdTvGsView, view> object.
  */
  OdTvGsViewId getViewId() const { return m_tvViewId; }

  /** \details
    Sets a new view type for the extended view object.
    
    \param type           [in] A new view type value.
    \param zoomToExtents  [in] A flag that determines whether the view is zoomed to extents (if equal to true).
  */
  virtual void setViewType(e3DViewType type, bool zoomToExtents = true);

  /** \details
    Retrieves the current view type for the extended view object.
    
    \returns Returns the current view type.
    \remarks 
    The view type returned by the method defines the 2D plane that this view's camera is looking at. The default is kCustom.
  */
  e3DViewType getViewType() const { return m_ViewType; }

  /** \details
    Sets the camera parameters for the extended view object.
    
    \param position       [in] A new camera position.
    \param target         [in] A new camera target.
    \param upVector       [in] A new camera up vector.
    \param fieldWidth     [in] A new width of the projection plane (field).
    \param fieldHeight    [in] A new height of projection plane.
    \param projectionType [in] A new projection type.
    \remarks
    All parameters are represented in WCS coordinates.
    The method defines the transformation from WCS coordinates to normalized device coordinates.
  */
  virtual void setView(const OdTvPoint& position, const OdTvPoint& target, const OdTvVector& upVector, double fieldWidth,
                       double fieldHeight, OdTvGsView::Projection projectionType = OdTvGsView::kParallel);

  /** \details
    Rotates the camera by the specified angle about the eye vector.
    
    \param rollAngle [in] A new angle value of the camera CCW rolling.
    \param pt        [in] A raw pointer to the new target position for the operation.
    \remarks
    1. The method first translates the camera position and target by the 'pt + target'. 
    If the pt parameter is equal to NULL, no translation is applied.
    2. Positive roll angles lead to the camera rotating counterclockwise about the eye vector 
    when viewed from the camera position to the target. This rotation corresponds
    to a clockwise rotation of the up vector.
    3. Finally the method translates the camera position and target by the '-pt + target'. 
    If the pt parameter is NULL, no translation is applied.
    * The Y-axis is along the up-vector.
    * The Z-axis (eye vector) is along the vector from the camera position to the target.
    * The X-axis is the cross product of Y-axis x Z-axis.
    All angles are represented in radians.
  */
  virtual void roll(double rollAngle, const OdGePoint3d* pt = NULL);

  /** \details
    Orbits the camera about the specified point by the specified amounts.

    \param xOrbit [in] An X-axis orbit.
    \param yOrbit [in] A Y-axis orbit.
    \param pt     [in] A target position for the operation represented with a raw pointer to the point object.
    \remarks
    1. The method first translates the camera position and target by the 'pt - target'. 
    If the pt parameter is equal to NULL, no translation is applied.
    2. Then the camera moves on the surface of a sphere with the center in the target point and with the
       radius equal to the distance from the camera position to its target.
    3. Finally the method translates the camera position and target by the '-pt + target'. 
    If the pt parameter is NULL, no translation is applied.
    * The camera is first rotated about an axis parallel to the X-axis and passing through the target.
    * Next the camera is rotated about an axis parallel to the Y-axis and passing through the target.
    * The Y-axis is along the up-vector.
    * The Z-axis is along the vector from the camera position to the target.
    * The X-axis is the cross product of Y-axis X Z-axis.
    All angles are represented in radians.
  */
  virtual void orbit(double xOrbit, double yOrbit, const OdGePoint3d* pt = NULL);

  /** \details
    Scales the camera to completely include view extents inside a view frustum.
  */
  virtual void zoomToExtents();

  /** \details
    Scales the camera to completely include extents inside a view frustum.
  */
  virtual void zoomToExtents(const OdGePoint3d &minPt, const OdGePoint3d &maxPt);

  /** \details
    Scales the camera with a certain step forward.
  */
  virtual void zoomIn();

  /** \details
    Scales the camera with a certain step back.
  */
  virtual void zoomOut();

  /** \details
    Scales the camera to completely include a specified screen area.

    \param lowerLeft  [in] A lower-left corner in normalized device coordinates ([0.0 .. 1.0]).
    \param upperRight [in] An upper-right corner in normalized device coordinates ([0.0 .. 1.0]).
  */
  virtual void zoomToWindow(const OdTvPoint2d &lowerLeft, const OdTvPoint2d &upperRight);

  /** \details
    Notifies that the device size was changed (should be called after 'onSize' method of the device object
  */
  virtual void onResized();

  /** \details
    Switches on or off the WCS (the axis triad).
    
    \param bEnable [in] A boolean value that specifies whether the WCS axis triad is switched on (true).
  */
  virtual void setEnabledWCS(bool bEnable);

  /** \details
    Checks whether the WCS axis triad is switched on.
    
    \returns Returns true if the WCS axis triad is switched on; otherwise the method returns false.
  */
  bool getEnabledWCS() const { return m_bEnableWCS; }

  /** \details
    Switches on or off the View Cube.
    
    \param bEnable [in] A boolean value that specifies whether the View Cube is switched on (true).
  */
  virtual void setEnabledViewCube(bool bEnable);

  /** \details
    Checks whether the View Cube is switched on.
    
    \returns Returns true if the View Cube is switched on; otherwise the method returns false.
  */
  bool getEnabledViewCube() const;

  /** \details
    Performs mouse move action for the View Cube object and highlights the appropriate part of the view cube geometry.
    
    \param x [in] Coordinate by X axis in device coordinate space (pixels).
    \param y [in] Coordinate by Y axis in device coordinate space (pixels).
    \returns Returns true if the View Cube is selected; otherwise the method returns false.
  */
  bool viewCubeProcessHover(int x, int y);

  /** \details
    Processes mouse click action for the View Cube object and changes view parameters according to the view cube geometry.
    
    \param x [in] Coordinate by X axis in device coordinate space (pixels).
    \param y [in] Coordinate by Y axis in device coordinate space (pixels).
    \returns Returns true if the View Cube side is changed; otherwise the method returns false.
  */
  bool viewCubeProcessClick(int x, int y);

  /** \details
    Retrieves the current internal view for the WCS object.
    
    \returns Returns the identifier of the internal view object.
  */
  OdTvGsViewId getWCSViewId() const { return m_wcsViewId; }

  /** \details
    Sets a new render mode value for the extended view object.
    
    \param mode [in] A new render mode value to be set.
    \returns Returns true if the new render mode is successfully set; otherwise the method returns false.
  */
  virtual bool setRenderMode(OdTvGsView::RenderMode mode);

  /** \details
    Retrieves the current render mode for the extended view object.
    
    \returns Returns the current render mode represented with the <link OdTvGsView::RenderMode, RenderMode> enumeration value.
  */
  OdTvGsView::RenderMode getRenderMode();

  /** \details
    Sets a new zoom scale value. 
    
    \param zoomScale [in] A new zoom scale value to be set.
    \remarks
    The zoom scale value should be greater than 1.
  */
  virtual void setZoomScale(double zoomScale);

  /** \details
    Retrieves the current zoom scale value.
    
    \returns Returns the current zoom scale value.
    \remarks
    The zoom scale value is greater than 1.
  */
  double getZoomScale();

  /** \details
    Sets the extents (WCS) which would be cached for all operations, which involves extents 
    (for example, calling the  <link OdTvExtendedView::zoomToExtents, zoomToExtents()> method).
    
    \param pCachedExt [in] A raw pointer to the extents object.
    \returns Returns true if the cached extents were successfully set; otherwise the method returns false.
    \remarks
    The method allows to speed up some operations because the extents calculation can be a time-consuming operation.
    Setting a zero extents leads to the clearing of the cached extents.
  */
  void setViewExtentsForCaching(const OdGeBoundBlock3d* pCachedExt);

  /** \details
    Retrieves the currently cached extents. 
    
    \param extents [in] A placeholder for the extents object to be returned to a calling subroutine.
    \returns Returns true if the currently cached extents exist and successfully returned; otherwise, the method returns false.
    \remarks
    If no extents are cached the method returns false.
  */
  bool getCachedExtents(OdGeBoundBlock3d& extents) const;

  /** \details
    Sets a new visual style for the extended view object.
    
    \param visualStyleId [in] An identifier of the new visual style object to be set.
    \returns Returns true if the new visual style is successfully set; otherwise returns false.
  */
  virtual bool setVisualStyle(const OdTvVisualStyleId& visualStyleId);

  /** \details
    Enables or disables the animation of non-interactive view changes.
    
    \param enable [in] A flag value that determines whether the animation is enabled (if equal to true).
  */
  virtual void	setAnimationEnabled(bool enable);

  /** \details
    Sets the new duration of the animation for the extended view object.
    
    \param duration [in] A new duration value in seconds.
  */
  virtual void setAnimationDuration(double duration) { m_dAnimationDuration = duration; }

  /** \details
    Checks whether the animation for non-interactive view changes is enabled.
    
    \returns Returns true if the animation is enabled; otherwise the method returns false.
  */
  bool getAnimationEnabled() const { return m_bUseAnimation; }

  /** \details
    Retrieves the current duration of the animation for the extended view object.
    
    \returns Returns the current animation duration value in seconds.
  */
  double getAnimationDuration() const { return m_dAnimationDuration; }

  /** \details
    Retrieves the current animation associated with the extended view object.
    
    \returns Returns a raw pointer to the current <link OdTvAnimation, animation> object if it is ready; otherwise the method returns a NULL pointer.
  */
  OdTvAnimation* getAnimation() const;

  /** \details
    Resets the animation for the extended view object.
  */
  void resetAnimation();

  /** \details
    Rotates the camera around axis with a certain speed.
    
    \param axis               [in] Axis around which to rotate.
    \param speed              [in] Rotation speed.
    \param bCenterExtAsTarget [in] Flag that specifies whether to use center of extents as target.
  */
  virtual void rotate(const OdTvVector& axis, double speed, bool bCenterExtAsTarget);

  /** \details
    Gets WCS extents data from TV view.
    
    \param lastExt        [out] Receives extents data.
    \param viewId         [in] Identifier of a view that contains extents data.
    \param bNotUseCache   [in] Flag that specifies whether to get cached extents if they exist.
    \returns
    Returns true if extents data that can be successfully retrieved, false otherwise.
  */
  static bool getExtentsFromTvView(OdGeBoundBlock3d& lastExt, OdTvGsViewId viewId, bool bNotUseCache = false);

//DOM-IGNORE-BEGIN
protected:

  /** \details
    Performs zoom to extents (direct calculations).
    
    \param pExtWCS [out] A raw-pointer to a placeholder for the extents object (WCS).
    \remarks 
    If the pExtWCS parameter is not null, the method returns calculated extents to a calling subroutine.
  */
  void zoomToExtentsInternal(OdGeBoundBlock3d* pExtWCS = NULL);

  /** \details
    Sets the camera parameters for this object.
  */
  void setViewInternal(const OdTvPoint& position, const OdTvPoint& target, const OdTvVector& upVector, double fieldWidth,
                       double fieldHeight, OdTvGsView::Projection projectionType = OdTvGsView::kParallel);

  /** \details
    Prepares the animation between previous view parameters and current (which should be already set to the view). 
    The created animation object then can be retrieved via the 'getAnimation' method.

    \remarks  prevUp should be normalized.
  */
  bool prepareAnimation( const OdTvPoint& prevPos, const OdTvPoint& prevTarget, const OdTvVector& prevUp, double prevFW, double prevFH );

  /** \details
    Re-creates the geometry for the WCS axis triad.
  */
  void updateWCS();

  /** \details
    Setup viewport for WCS view.
  */
  void setupViewportForWCSView();

  /** \details
    Creates an axis entity.
    
    \param pWcs       [in] A smart pointer to the entity that represents the axis.
    \param color      [in] A color of the axis entity.
    \param startPoint [in] A start point of the axis entity.
    \param endPoint   [in] An end point of the axis entity.
    \param axisName   [in] A string that contains the name of the axis entity.
  */
  void createWcsAxis(OdTvEntityPtr pWcs, OdTvColorDef color, OdTvPoint startPoint, OdTvPoint endPoint, OdString axisName);

  /** \details
    Calculates or returns cached view extents.
    
    \param extents    [out] Receives calculated or cached extents.
    \returns
    true if the extents are successfully received, false otherwise.
  */
  bool calculateViewExtents(OdGeBoundBlock3d& extents);

protected:

  // Visualize gs view, associated with the current basic view
  OdTvGsViewId    m_tvViewId;

  // Current view type
  e3DViewType	    m_ViewType;

  // Enable WCS (axis triad)
  bool            m_bEnableWCS;

  // Switches on/off animation for non-interactive view changes
  bool            m_bUseAnimation;

  // Duration of the animation
  double          m_dAnimationDuration;

  // Animation object
  OdTvAnimation*   m_pAnimation;

  // Special model for WCS object
  OdTvModelId m_TvWcsModelId;

  // Special view for the WCS
  OdTvGsViewId m_wcsViewId;

  // Zoom in/out scale
  double m_zoomScale;

  // Cached view extents (WCS)
  OdGeBoundBlock3d               m_cachedExt;
  bool                           m_bCachedExtValid;

  // View cube object
  OdTvViewCube* m_pViewCube;

  // Flag indicates the visual style was set
  bool          m_bVisualStyleWasSet;

  friend class OdTvViewCube;

  //DOM-IGNORE-END
};


#include "TvAnimation.h"
/** \details
  The base camera animation class with connection to the Visualize Animation API.
  
  \remarks OdTvCameraAnimation manage registered camera, animation actions and animation container.
*/
class OdTvCameraAnimation : public OdTvAnimation
{
public:
  /** \details
    Constructs instance of OdTvCameraAnimation.
    
    \param dbId [in] Id of the database.
  */
  OdTvCameraAnimation( OdTvDatabaseId dbId );
  
  /** \details
    Destroys the instance of OdTvCameraAnimation.
  */
  virtual ~OdTvCameraAnimation();
  
  /** \details
    Retrieves assigned database id.
    
    \returns Returns database id.
  */
  OdTvDatabaseId database() { return m_dbId; }
  
  /** \details
    Retrieves animation container id.
    
    \returns Returns animation container id.
  */
  OdTvAnimationContainerId containerId() { return m_containerId; }
  
  /** \details
    Registers animation action.
    
    \param id [in] Animation action id.
    \returns Returns index of registered action.
    \remarks Registered actions managed by OdTvCameraAnimation.
  */
  OdUInt32 registerAction( OdTvAnimationActionId id ) { m_actions.push_back( id ); return m_actions.size() - 1; }
  
  /** \details
    Unregisters all registered actions.
  */
  void unregisterActions();
  
  /** \details
    Retrieves number of registered actions.
    
    \returns Returns number of registered actions.
  */
  OdUInt32 numRegisteredActions() const { return m_actions.size(); }
  
  /** \details
    Retrieves registered action by index.
    
    \param index [in] Index of registered action.
    \returns Returns registered action id.
  */
  OdTvAnimationActionId action( OdUInt32 index )
  {
    if( index >= m_actions.size() ) return OdTvAnimationActionId();
    return m_actions[ index ];
  }
  
  /** \details
    Specifies FPS for all registered actions.
    
    \param FPS [in] Desired FPS value.
  */
  void setFPS( OdUInt32 FPS );
  
  /** \details
    Creates and registers camera object.
    
    \param viewId  [in] Identifier of a View that should be saved as camera.
    \param modelId [in] Identifier of a Model where camera should be placed.
    \returns Returns Id of created camera.
    \remarks
    Only single camera can be registered. Additional call destroys registered camera and creates a new one.
    NULL viewId destroys registered camera without creating a new one (unregister).
  */
  OdTvEntityId registerCamera( OdTvGsViewId viewId, OdTvModelId modelId );
  
  /** \details
    Retrieves registered camera id.
    
    \returns Returns registered camera id.
  */
  OdTvEntityId cameraId() const;
  
  /** \details
    Retrieves custom actor basis.
    
    \returns Returns the reference to the custom actor basis.
  */
  OdTvAnimationContainer::OdTvActorBasis& basis() { return m_basis; }
  
  /** \details
    Retrieves custom actor basis.
    
    \returns Returns the custom actor basis.
  */
  const OdTvAnimationContainer::OdTvActorBasis& basis() const { return m_basis; }
  
  /** \details
    Checks whether animation playback is already completed.
    
    \returns Returns true if animation playback is already completed; otherwise returns false.
  */
  bool isPlayingDone() const;
  
  /** \details
    Retrieves time for the last step() call in milliseconds.
    
    \returns Returns time for the last step() call.
  */
  OdUInt32 lastStepTime() const { return m_lastStepTime; }
  
  /** \details
    Starts the animation.
    
    \returns Returns true if the animation is successfully started; otherwise the method returns false.
  */
  virtual bool start();
  
  /** \details
    Performs the next step of the animation.
    
    \returns Returns true if the animation step is successfully performed; otherwise the method returns false.
  */
  virtual bool step();
  
  /** \details
    Resets the animation.
  */
  virtual void reset();
  
  /** \details
    Retrieves specified action active frame data.
    
    \param kd       [in] KeyData channel.
    \param nAction  [in] Index of registered action, which frame data should be retrieved.
    \returns Returns action active frame data.
  */
  double activeFrameData( OdTvAnimationAction::Keydata kd, OdUInt32 nAction ) const;
//DOM-IGNORE-BEGIN
protected:
  OdTvDatabaseId m_dbId;
  OdVector< OdTvAnimationActionId > m_actions;
  OdTvAnimationContainerId m_containerId;

  OdTvGsViewId m_viewId;
  OdTvEntityId m_cameraId;
  OdTvModelId m_modelId;

  OdUInt32 m_startTime;
  OdUInt32 m_lastStepTime;

  OdTvAnimationContainer::OdTvActorBasis m_basis;
  OdPerfTimerBase* m_pTimer;
//DOM-IGNORE-END
};


/** \details
  The base interface class that provides access to the extended view rotation animation functionality.
*/
class OdTvExtendedViewAnimation : public OdTvCameraAnimation
{
public:

  /** \details
    Creates a new extended view animation object with default parameters.
    
    \param dbId [in] Id of current database.
  */
  OdTvExtendedViewAnimation( OdTvDatabaseId dbId );

  /** \details
    Destroys the extended view animation object.
  */
  virtual ~OdTvExtendedViewAnimation();

  /** \details
    Starts the animation.
    
    \returns Returns true if the animation is successfully started; otherwise the method returns false.
  */
  bool start();

  /** \details
    Performs the next step of the animation.
    
    \returns Returns true if the animation step is successfully performed; otherwise the method returns false.
  */
  bool step();

  /** \details
    Checks whether the animation is running.
    
    \returns Returns true if the animation is running; otherwise the method returns false.
  */
  bool isRunning();

  /** \details
    Checks whether the animation is ready.
    
    \returns Returns true if the animation is ready; otherwise the method returns false.
  */
  bool isReady();

  /** \details
    Resets the animation.
  */
  void reset();

  /** \details
    Prepares the full animation. 
    
    \param quat1      [in]  A first rotation quaternion.
    \param targ1      [in]  A first target.
    \param fW1        [in]  A width of the first camera field.
    \param fH1        [in]  A height of the first camera field.
    \param dirLength1 [in]  A first direction length.
    \param quat2      [in]  A second rotation quaternion.
    \param targ2      [in]  A second target.
    \param fW2        [in]  A width of the second camera field.
    \param fH2        [in]  A height of the second camera field.
    \param dirLength2 [in]  A second direction length.
    \param viewId     [out] A placeholder for the identifier of a base view object.
    \param wcsViewId  [out] A placeholder for the identifier of the WCS view object.
    \param viewCubeViewId  [out] A placeholder for the identifier of the View Cube view object.
    \param dDuration  [in]  An animation duration value.
  */
  void initFull(const OdGeQuaternion& quat1, const OdTvPoint& targ1, double fW1, double fH1, double dirLength1,
                const OdGeQuaternion& quat2, const OdTvPoint& targ2, double fW2, double fH2, double dirLength2,
                OdTvGsViewId& viewId, OdTvGsViewId& wcsViewId, OdTvGsViewId& viewCubeViewId, double dDuration);

  /** \details
    Prepares the translated animation.
    
    \param pos1       [in]  A first position.
    \param targ1      [in]  A first target.
    \param fW1        [in]  A width of the first camera field.
    \param fH1        [in]  A height of the first camera field.
    \param dirLength1 [in]  A first direction length.
    \param pos2       [in]  A second position.
    \param targ2      [in]  A second target.
    \param fW2        [in]  A width of the second camera field.
    \param fH2        [in]  A height of the second camera field.
    \param dirLength2 [in]  A second direction length.
    \param viewId     [out] A placeholder for the identifier of a base view object.
    \param wcsViewId  [out] A placeholder for the identifier of the WCS view object.
    \param viewCubeViewId  [out] A placeholder for the identifier of the View Cube view object.
    \param dDuration  [in]  An animation duration value.
  */
  void initTranslate(const OdTvPoint& pos1, const OdTvPoint& targ1, double fW1, double fH1,
                     const OdTvPoint& pos2, const OdTvPoint& targ2, double fW2, double fH2,
                     OdTvGsViewId& viewId, OdTvGsViewId& wcsViewId, OdTvGsViewId& viewCubeViewId, double dDuration);

//DOM-IGNORE-BEGIN
private:

  OdGeQuaternion m_quatSt;
  OdGeQuaternion m_quatFin;

  OdTvPoint m_targ1;
  OdTvPoint m_targ2;

  OdTvPoint m_pos1;
  OdTvPoint m_pos2;

  double m_fW1, m_fH1;
  double m_fW2, m_fH2;

  double m_dirLength1;
  double m_dDirLength;

  OdTvGsViewId m_viewId;
  OdTvGsViewId m_wcsviewId;
  OdTvGsViewId m_viewCubeViewId;

  bool m_bReady;
  bool m_bStarted;
  bool m_bIsClearTranslate;

  double m_dDuration;
  double m_dStartTime;

  bool initActions();
  OdTvAnimationActionId createAction( OdTvDatabaseId dbId, const OdString& str );
  enum AnimationAction
  {
    kActionPosition = 0,
    kActionTarget = 1,
    kActionUp = 2,
    kActionFields = 3
  };

  OdTvAnimationActionId m_animationActions[ 4 ];
  OdTvPoint m_storedPosition;
  OdTvPoint m_storedTarget;
  OdTvVector m_storedUp;
//DOM-IGNORE-END
};


/** \details
  The base interface class that provides access to the extended view rotation animation functionality.
*/
class OdTvRotationViewAnimation : public OdTvCameraAnimation
{
public:

  /** \details
    Creates a new rotation view animation object with default parameters.
    
    \param dbId               [in]  Database Id.
    \param rotationAxis       [in]  Axis around which to rotate.
    \param step               [in]  Rotation step.
    \param viewId             [in]  Gs graphics view Id.
    \param wcsViewId          [in]  Id of the view that contains the WCS tool.
    \param viewCubeViewId     [in]  Id of the view that contains the view cube.
    \param viewExt            [in]  View extents.
    \param centerExtAsTarget  [in]  Flag that specifies whether to use center of extents as target.
  */
  OdTvRotationViewAnimation(OdTvDatabaseId dbId, const OdTvVector& rotationAxis, double step, const OdTvGsViewId& viewId, const OdTvGsViewId& wcsViewId, const OdTvGsViewId& viewCubeViewId, const OdGeBoundBlock3d& viewExt, bool centerExtAsTarget);

  /** \details
    Destroys the rotation view animation object.
  */
  virtual ~OdTvRotationViewAnimation();

  /** \details
    Starts the animation.
    
    \returns Returns true if the animation is successfully started; otherwise the method returns false.
  */
  bool start();

  /** \details
    Performs the next step of the animation.
    
    \returns Returns true if the animation step is successfully performed; otherwise the method returns false.
  */
  bool step();

  /** \details
    Checks whether the animation is running.
    
    \returns Returns true if the animation is running; otherwise the method returns false.
  */
  bool isRunning();

  /** \details
    Resets the animation.
  */
  void reset();

  /** \details
    Checks whether the animation is ready.
    
    \returns Returns true if the animation is ready; otherwise the method returns false.
  */
  bool isReady();

  /** \details
    Sets new params for animation.
    
    \param rotationAxis       [in]  Axis around which to rotate.
    \param step               [in]  Rotation step.
    \param viewExt            [in]  View extents.
    \param centerExtAsTarget  [in]  Flag that specifies whether to use center of extents as target.
  */
  void setParams(const OdTvVector& rotationAxis, double step, const OdGeBoundBlock3d& viewExt, bool centerExtAsTarget);

  //DOM-IGNORE-BEGIN
private:
  OdTvGsViewId m_viewId;
  OdTvGsViewId m_wcsviewId;
  OdTvGsViewId m_viewCubeViewId;
  OdTvVector m_rotationAxis;
  double m_dStep;
  double m_prevAngle;
  bool m_bStarted;
  double m_dCoef;
  OdGeBoundBlock3d m_viewExt;
  bool m_bCenterExtAsTarget;
  bool m_bIsReady;

  bool initAction( OdTvAnimationActionId actionId, const OdTvPoint& target, const OdTvPoint& originalPosition );
  OdTvAnimationActionId m_animationAction;
  //DOM-IGNORE-END
};

#endif //_ODTV_EXTENDED_H_INCLUDED_
