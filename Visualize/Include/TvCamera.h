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

#ifndef _ODTV_CAMERA_H_INCLUDED_
#define _ODTV_CAMERA_H_INCLUDED_

#include "OdaCommon.h"

#include "Tv.h"
#include "TvIObject.h"
#include "TvTraitsDef.h"
#include "TvUserData.h"
#include "TvGeometryData.h"

class OdTvGsViewId;

/** \details
The abstract interface class for a Visualize SDK camera object.
*/
class ODTV_EXPORT OdTvCamera : public OdTvHandledIObject
{
public:

  /** \details
    Specifies the name for the camera.
    
    \param sName [in]  Camera name as a String value up to 255 characters long.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult setName( OdString sName ) = 0;
  
  /** \details
    Retrieves the name of the camera.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current entity name.
  */
  virtual OdString getName( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies camera orientation in space.
    
    \param position   [in] Position of camera.
    \param direction  [in] Camera view direction.
    \param upVector   [in] Camera up vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
    \remarks
    If direction and up vectors is not perpendicular, returns tvInvalidInput but applies changes.
  */
  virtual OdTvResult setupCamera( const OdTvPoint& position, const OdTvVector& direction, const OdTvVector& upVector ) = 0;
  
  /** \details
    Specifies camera orientation in space.
    
    \param position [in] Position of camera.
    \param target   [in] Camera viewing target.
    \param upVector [in] Camera up vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
    \remarks
    If direction = ( target - position ) and up vectors is not perpendicular, returns tvInvalidInput but applies changes.
  */
  virtual OdTvResult setupCamera( const OdTvPoint& position, const OdTvPoint& target, const OdTvVector& upVector ) = 0;
  
  /** \details
    Retrieves camera position.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera position.
  */
  virtual OdTvPoint position( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies new camera position.
    
    \param position [in] Position of camera.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
    \remarks This method changes camera position and up vector, but keeps target unchanged.
  */
  virtual OdTvResult setPosition( const OdTvPoint& position ) = 0;
  
  /** \details
    Retrieves camera viewing direction.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera viewing direction.
  */
  virtual OdTvVector direction( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves camera up vector.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera up vector.
  */
  virtual OdTvVector upVector( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies new camera up vector.
    
    \param upVector [in] Camera up vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
    \remarks This method changes camera up vector.
  */
  virtual OdTvResult setUpVector( const OdTvVector& upVector ) = 0;
  
  /** \details
    Retrieves camera viewing target.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera viewing target.
  */
  virtual OdTvPoint target( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies new camera target.
    
    \param target [in] Camera viewing target.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
    \remarks This method changes camera target and up vector, but keeps position unchanged.
  */
  virtual OdTvResult setTarget( const OdTvPoint& target ) = 0;
  
  /** \details
    Specifies camera viewing parameters.
    
    \param fWidth [in] Field width of the WCS projection plane for the view object.
    \param fHeight   [in] field height of the WCS projection plane for the view object.
    \param bPrespective [in] Camera projection type: true for perspective and false for parallel.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
  */
  virtual OdTvResult setViewParameters( double fWidth, double fHeight, bool bPrespective = false ) = 0;
  
  /** \details
    Retrieves camera field width.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera field width.
  */
  virtual double fieldWidth( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves camera filed height.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera field height.
  */
  virtual double fieldHeight( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Checks whether the camera has a perspective projection type.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if camera is perspective and false if camera is parallel.
  */
  virtual bool isPerspective( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies camera near (front) clipping.
    
    \param bClip    [in] A near clipping enable flag. If the flag is equal to true, near clipping is enabled; otherwise near clipping is disabled.
    \param dNear    [in] A near clipping distance.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
  */
  virtual OdTvResult setNearClip( bool bClip, double dNear = 1.0 ) = 0;
  
  /** \details
    Specifies camera far (back) clipping.
    
    \param bClip    [in] A far clipping enable flag. If the flag is equal to true, far clipping is enabled; otherwise far clipping is disabled.
    \param dFar    [in] A far clipping distance.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
  */
  virtual OdTvResult setFarClip( bool bClip, double dFar = 0.0 ) = 0;
  
  /** \details
    Checks whether camera near (front) clipping is enabled.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if near clipping is enabled and false otherwise.
  */
  virtual bool isNearClippingEnabled( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves camera near (front) clipping distance.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera near clipping distance.
  */
  virtual double nearClippingDistance( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Checks whether camera far (back) clipping is enabled.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if far clipping is enabled and false otherwise.
  */
  virtual bool isFarClippingEnabled( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves camera far (back) clipping distance.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera far clipping distance.
  */
  virtual double farClippingDistance( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies camera glyph size.
    
    \param sz     [in] Camera glyph size (in pixels).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
  */
  virtual OdTvResult setGlyphSize( OdUInt32 sz ) = 0;
  
  /** \details
    Retrieves camera glyph size.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera glyph size (in pixels).
  */
  virtual OdUInt32 glyphSize( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies whether the camera should display the glyph.
    
    \param on     [in] A display glyph flag.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
  */
  virtual OdTvResult setDisplayGlyph( bool on ) = 0;
  
  /** \details
    Checks whether the camera should display the glyph.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if camera should display glyph; returns false otherwise.
  */
  virtual bool displayGlyph( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies whether the camera should display target in addition to the glyph display.
    
    \param on     [in] A display target flag.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
    \remarks Target is displayed only if DisplayGlyph is ON.
  */
  virtual OdTvResult setDisplayTarget( bool on ) = 0;
  
  /** \details
    Checks whether the camera should display a target.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if camera should display target; returns false otherwise.
  */
  virtual bool displayTarget( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Assigns the specified view to the camera. Assigned view use camera viewing options; also it handles all camera viewing options changes.
    
    \param viewId   [in] Id of the OdGsView object that should be assigned to camera.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
    \remarks
    View can be assigned to only one camera at the same time. If the specified view is already assigned to another camera, tvAlreadyInUse is returned.
  */
  virtual OdTvResult assignView( const OdTvGsViewId& viewId ) = 0;
  
  /** \details
    Checks whether the camera has assigned views.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if camera have at least one assigned view; otherwise returns false.
  */
  virtual bool hasAssignedViews( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Checks whether the specified view is assigned to this camera.
    
    \param viewId   [in] Id of the OdGsView object that should be checked.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if this camera is assigned to the specified view; otherwise returns false.
  */
  virtual bool isViewAssigned( const OdTvGsViewId& viewId, OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Unassigns the specified view from camera.
    
    \param viewId   [in] Id of the OdGsView object that should be unassigned from camera.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
    \remarks
    Camera can unassign view only if it was assigned to this camera, not with another. In other case tvInvalidInput is returned.
  */
  virtual OdTvResult unassignView( const OdTvGsViewId& viewId ) = 0;
  
  /** \details
    Retrieves camera position as OdTvGeometryDataId.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera position as OdTvGeometryDataId.
  */
  virtual OdTvGeometryDataId positionId( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves camera target as OdTvGeometryDataId.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera target as OdTvGeometryDataId.
  */
  virtual OdTvGeometryDataId targetId( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves camera up vector as OdTvGeometryDataId.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera up vector as OdTvGeometryDataId.
  */
  virtual OdTvGeometryDataId upId( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves camera fields (fieldWidth and fieldHeight) as OdTvGeometryDataId.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera position as OdTvGeometryDataId.
  */
  virtual OdTvGeometryDataId fieldsId( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Checks whether the camera will automatically adjust co-dependent parameters when one of them are changed or not.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns flag that indicates whether the camera automatically adjusts co-dependent parameters when one of them are changed.
  */
  virtual bool isAutoAdjust( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies, should camera automatically adjust co-dependent parameters when one of them are changed or not.
    
    \param bAdjust [in] Flag that indicates should the camera automatically adjust co-dependent parameters when one of them are changed or not.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
    \remarks
    This flag is real-time only and not saved in file. Default value is "TRUE".
    Position, target and Up vector are co-dependent parameters. Viewing direction (target - position) and up vector have to be perpendicular, so 
    changing one of them (e.g. setTarget) require re-calculation of others. However, in some cases (e.g. Animation) all parameters may be manually changed
    not using setupCamera(), but using setPosition(), setTarget() and setUpVector(). In this case disabled AutoAdjust is more preferred.
  */
  virtual OdTvResult setAutoAdjust( bool bAdjust ) = 0;
  
  /** \details
    Checks whether the camera will automatically adjust lens length to keep consistent target, position and field settings or not.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns flag that indicates whether the camera automatically adjusts lens length.
  */
  virtual bool isAdjustLensLength( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies, should camera automatically adjust lens length to keep consistent target, position and field settings or not.
    
    \param bAdjust [in] Flag that indicates should the camera automatically adjust lens length to keep consistent target, position and field settings or not.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
    \remarks
    In perspective case, pair <Target, Position> and pair <Field width, Field height> depend on lens length. So, when both pairs
    are specified manually they may conflict if lens length is fixed. This option adjust lens length so conflict becomes solved.
    The default value of this parameter is "TRUE".
  */
  virtual OdTvResult setAdjustLensLength( bool bAdjust ) = 0;
  
  /** \details
    Copies camera parameters from the specified view.
    
    \param viewId   [in] Id of the OdGsView object that should contains parameters to be copied.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
    \remarks In perspective case, this method adjusts camera position so it corresponds to the camera focal length, field width and height.
  */
  virtual OdTvResult setupCameraFromView( const OdTvGsViewId& viewId ) = 0;
  
  /** \details
    Retrieves camera lens length.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera lens length.
  */
  virtual double lensLength( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies camera lens length.
    
    \param l        [in] A new lens length value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of operation.
  */
  virtual OdTvResult setLensLength( double l ) = 0;
  
  /** \details
    Retrieves camera focal length.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera focal length.
    \remarks This method has no sense for the parallel camera. In this case return value is 0 and rc value is tvWarning.
  */
  virtual double focalLength( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves camera vertical viewing angle.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera vertical viewing angle.
    \remarks This method has no sense for the parallel camera. In this case return value is 0 and rc value is tvWarning.
  */
  virtual double perspectiveVerticalViewAngle( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Retrieves camera horizontal viewing angle.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns camera horizontal viewing angle.
    \remarks This method has no sense for the parallel camera. In this case return value is 0 and rc value is tvWarning.
  */
  virtual double perspectiveHorizontalViewAngle( OdTvResult* rc = NULL ) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvCamera, OdTvCamera> object.
*/
typedef OdTvSmartPtr<OdTvCamera> OdTvCameraPtr;

#endif //_ODTV_CAMERA_H_INCLUDED_
