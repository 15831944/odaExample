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

#ifndef _ODTV_GSVIEW_H_INCLUDED_
#define _ODTV_GSVIEW_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvModel.h"
#include "Ge/GeBoundBlock3d.h"
#include "TvUserData.h"
#include "TvSelection.h"
#include "TvVisualStyle.h"
#include "UInt32Array.h"
#include "TvGsViewBackground.h"
#include "TvCollidedResult.h"
#include "Gi/GiRasterImage.h"

class OdTvGsDeviceId;
class OdTvGsViewId;

/** \details
  This class is an interface class for the object that encapsulates a view object in GUI display windows.

  \remarks
  Each view object consists of a collection of objects to be viewed and camera parameters that define the view.
  \sa
  <link tv_working_with_base_classes_view, Work with Visualize Graphical Views>
*/
class ODTV_EXPORT OdTvGsView : public OdTvHandledIObject
{
public:

  /** \details
    Rendering modes.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#7">Managing Render Modes</EXTLINK>
  */
  enum RenderMode
  {
    k2DOptimized                    = 0,          // Standard display. Optimized for 2D.
    kWireframe                      = 1,          // Standard display. Uses 3D pipeline.
    kHiddenLine                     = 2,          // Wireframe display. Hidden lines removed.
    kFlatShaded                     = 3,          // Faceted display. One color per face.
    kGouraudShaded                  = 4,          // Smooth shaded display. Colors interpolated between vertices.
    kFlatShadedWithWireframe        = 5,          // Faceted display with wireframe overlay.
    kGouraudShadedWithWireframe     = 6,          // Smooth shaded display with wireframe overlay.
    kNone                                         // No rendering.
  };

  /** \details
    Projection types.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#12">Managing Projections</EXTLINK>
  */
  enum Projection
  {
    kParallel     = 0, //Parallel projection.
    kPerspective  = 1  //Perspective projection.
  };

  /** \details
    Lineweight modes.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#13">Managing Lineweight Display</EXTLINK>
  */
  enum LineWeightMode
  {
    kDeviceFixed             = 0, //Device fixed mode.
    kWorldFixed              = 1, //World fixed mode.
    kIndexed                 = 2  //Indexed lineweight mode.
  };

  /** \details
    Lighting types.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  enum DefaultLightingType
  {
    kOneLight = 0,  //One light mode.
    kTwoLights,     //Two lights mode.
    kBackLight,     //Back light.
    kUserDefined    //User defined light.
  };

  /** \details
    Cutting plane filling style.
    \sa
    <link tv_working_with_features_cutting_planes, Work with Cutting Planes>
  */
  enum CuttingPlaneFillStyle
  {
    kSolid = 0,          // Solid filling style
    kCheckerboard = 1,   // Checkerboard filling style
    kCrosshatch = 2,     // Crosshatch filling style
    kDiamonds = 3,       // Diamonds filling style
    kHorizontalBars = 4, // Horizontal bars filling style
    kSlantLeft = 5,      // Slant left filling style
    kSlantRight = 6,     // Slant right filling style
    kSquareDots = 7,     // Square dots filling style
    kVerticalBars = 8,   // Vertical bars filling style
  };

  /** \details
    The structure for storing viewport parameters.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#8">Managing Viewports</EXTLINK>
  */
  struct ViewportObjectInfo
  {
    OdTvPoint2d       m_wcsLowerLeft;   //WCS lower-left point of the viewport.
    OdTvPoint2d       m_wcsUpperRight;  //WCS upper-right point of the viewport.

    OdUInt32Array     m_numPtsInContours; //A quantity of points in contours.
    OdTvPoint2dArray  m_wcsCountoursPts;  //An array of points that form contours.

    /** \details
      Creates an instance of default viewport parameters.
      \sa
      <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#8">Managing Viewports</EXTLINK>
    */
    ViewportObjectInfo() {};
  };

  /** \details
    Retrieves the <link OdTvGsDevice, device> object that is associated with the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an identifier of the device associated with the view object. 
    \remarks 
    If the rc parameter is not null and the GS device identifier was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_base_classes_device, Work with Visualize Graphics Devices>
  */
  virtual OdTvGsDeviceId device(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the size and position of the view object.
    
    \param lowerLeft  [in] A point that represents the lower-left corner in normalized device coordinates ([0.0 .. 1.0]).
    \param upperRight [in] A point that represents the upper-right corner in normalized device coordinates ([0.0 .. 1.0]).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The point with coordinates (0,0) is the lower-left corner of the device object that owns the view. Coordinates increase upward and to the right.
    The view object can be allocated partly or completely off the screen.
    If the size and position of the view were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#8">Managing Viewports</EXTLINK>
  */
  virtual OdTvResult setViewport(const OdTvPoint2d& lowerLeft, const OdTvPoint2d& upperRight) = 0;
  
  /** \details
    Sets the size and position of the view object.
    
    \param screenRect [in]  A screen rectangle in the device coordinates (pixels).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The point with coordinates (0,0) is the lower-left corner of the device object that owns the view. Coordinates increase upward and to the right.
    The view object can be allocated partly or completely off the screen.
    If the size and position of the view were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#8">Managing Viewports</EXTLINK>
  */
  virtual OdTvResult setViewport(const OdTvDCRect& screenRect) = 0;

  /** \details
    Retrieves the current size and position of the view object.
    
    \param lowerLeft  [out] A placeholder for the point that represents the lower-left corner in normalized device coordinates ([0.0 .. 1.0]).
    \param upperRight [out] A placeholder for the point that represents the upper-right corner in normalized device coordinates ([0.0 .. 1.0]).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \remarks
    The point with coordinates (0,0) is the lower-left corner of the device object that owns the view. Coordinates increase upward and to the right.
    The view object can be allocated partly or completely off the screen.
    If the size and position of the view were successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#8">Managing Viewports</EXTLINK>
  */
  virtual OdTvResult getViewport(OdTvPoint2d& lowerLeft, OdTvPoint2d& upperRight) const = 0;
  
  /** \details
    Retrieves the size and position of the view object.
    
    \param screenRect [out] A placeholder for the screen rectangle object that represents the position and size of the view in the device coordinates (pixels).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \remarks
    The point with coordinates (0,0) is the lower-left corner of the device object that owns the view. Coordinates increase upward and to the right.
    The view object can be allocated partly or completely off the screen.
    If the rectangle object that represents the size and position of the view was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#8">Managing Viewports</EXTLINK>
  */
  virtual OdTvResult getViewport(OdTvDCRect& screenRect) const = 0;

  /** \details
    Sets new camera parameters for the view object.
    
    \param position       [in]  A new camera position.
    \param target         [in]  A new camera target.
    \param upVector       [in]  A new camera up vector.
    \param fieldWidth     [in]  A new projection plane (field) width.
    \param fieldHeight    [in]  A new projection plane (field) height.
    \param projectionType [in]  A new projection type.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    All parameters are represented in WCS coordinates.
    The projectionType parameter must accept one of the following values:
    <table>
    Name           Value
    kParallel      0
    kPerspective   1
    </table>
    The method defines a transformation from WCS coordinates to normalized device coordinates.
    If new view camera parameters were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    In perspective mode, Pair<fieldWidth, fieldHeight> and Position are co-dependent parameters, so they may conflict if lens length is fixed. 
    If such conflict happens Position will be used to define viewing direction only, to keep specified fieldWidth and fieldHeight unchanged. 
    However, setAdjustLensLength() method adjusts lens length so both actual Pair<fieldWidth, fieldHeight> and Position will be the same as the provided parameters.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual OdTvResult setView(
    const OdTvPoint& position,
    const OdTvPoint& target,
    const OdTvVector& upVector,
    double fieldWidth,
    double fieldHeight,
    Projection projectionType = kParallel) = 0;

  /** \details
    Retrieves the current camera position for the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a point object that represents the camera position for the view object in WCS coordinates.
    \remarks 
    If the rc parameter is not null and the view camera position was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual OdTvPoint position(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current camera target for the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a point object that represents the camera target for the view object in WCS coordinates.
    \remarks 
    If the rc parameter is not null and the view camera target was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual OdTvPoint target(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current camera's up vector for the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a vector object that represent the camera's up vector for the view object.
    \remarks 
    If the rc parameter is not null and the view camera's up vector was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual OdTvVector upVector(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current camera perspective lens length for the view object.
    
    \returns Returns a double value that represent the camera perspective lens length for the view object.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the rc parameter is not null and the camera perspective lens length was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#12">Managing Projections</EXTLINK>
  */
  virtual double lensLength(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the perspective lens length for the view object.
    
    \param lensLength [in]  A new value of the perspective lens length.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the new lens length was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#12">Managing Projections</EXTLINK>
  */
  virtual OdTvResult setLensLength(double lensLength) = 0;

  /** \details
    Retrieves the current value of the perspective projection flag for the view object. 
    
    The perspective projection flag is equal to true if the projection type is perspective; otherwise it is equal to false.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current value of the perspective projection. 
    \remarks 
    If the rc parameter is not null and the perspective projection flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#12">Managing Projections</EXTLINK>
  */
  virtual bool isPerspective(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current field width of the WCS projection plane for the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current WCS projection plane (field) width for the view object.
    \remarks 
    If the rc parameter is not null and the width of the projection plane field was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual double fieldWidth(OdTvResult* rc = NULL) const = 0;
  
  /** \details
    Retrieves the current field height of the WCS projection plane for the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current WCS projection plane (field) height for the view object.
    \remarks 
    If the rc parameter is not null and the height of the projection plane field was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual double fieldHeight(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves focal length of this View object.
    
    \param rc [out] [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns focal length of this View object.
    \remarks This method has no sense for the parallel View object. In this case return value is 0 and rc value is tvWarning.
  */
  virtual double focalLength( OdTvResult* rc = NULL ) const = 0;

  /** \details
    Retrieves the current extents of the eye coordinate system for the view object.
    
    \param extents  [out] A placeholder for the extents object. The method fills a passed object and returns it to a calling subroutine.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the extents are defined and the view of the device has an appropriate method; otherwise returns false.
    \remarks 
    If the rc parameter is not null and the extents object was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool viewExtents(OdGeBoundBlock3d& extents, OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current matrix for transformation from world space to view space.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the matrix that transforms world space to view space.
    \remarks 
    If the rc parameter is not null and the transformation matrix was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdGeMatrix3d viewingMatrix(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current matrix that transforms view space to the normalized device space associated with the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the matrix that transforms view space to normalized device space.
    \remarks 
    If the rc parameter is not null and the transformation matrix was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <exref target="CoordinateSystems.html">Coordinate Systems</exref>.
  */
  virtual OdGeMatrix3d projectionMatrix(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current matrix that transforms the normalized device space associated with the view object to screen space.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the matrix that transforms the normalized device space of the view to screen space.
    \remarks 
    If the rc parameter is not null and the transformation matrix was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <exref target="CoordinateSystems.html">Coordinate Systems</exref>.
  */
  virtual OdGeMatrix3d screenMatrix(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current matrix that transforms coordinates from world space to the screen space for the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the matrix that transforms coordinates from world space to screen space.
    \remarks 
    If the rc parameter is not null and the transformation matrix was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    The method returns the transformation matrix that is equal to the concatenation of matrices, which are returned by <link OdTvGsView::viewingMatrix@OdTvResult*@const, viewingMatrix()>, 
    <link OdTvGsView::projectionMatrix@OdTvResult*@const, projectionMatrix()> and <link OdTvGsView::screenMatrix@OdTvResult*@const, screenMatrix()> methods. 
    \sa
    <exref target="CoordinateSystems.html">Coordinate Systems</exref>.
  */
  virtual OdGeMatrix3d worldToDeviceMatrix(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current matrix that transforms view space to world space for the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the matrix that transforms coordinates from view space to world space.
    \remarks 
    If the rc parameter is not null and the transformation matrix was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <exref target="CoordinateSystems.html">Coordinate Systems</exref>.
  */
  virtual OdGeMatrix3d eyeToWorldMatrix(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current lower-left and upper-right corners of the view object in the associated device coordinates. 
    
    \param lower_left   [out] A placeholder for a point object that represents the lower-left corner of the view object.
    \param upper_right  [out] A placeholder for a point object that represents the upper-right corner of the view object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of retrieving the view corners.
    \remarks 
    If the view corners points were successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult viewDcCorners(OdGePoint2d& lower_left, OdGePoint2d& upper_right) const = 0;

  /** \details
    Sets a new render mode for the view object.
    
    \param mode [in] A new render mode value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting a new render mode operation.
    \remarks
    The render mode input parameter accepts one of the following values:
    <table>
    Name                            Value      Description
    k2DOptimized                    0          Standard display. Optimized for 2D.
    kWireframe                      1          Standard display. Uses 3D pipeline.
    kHiddenLine                     2          Wireframe display. Hidden lines removed.
    kFlatShaded                     3          Faceted display. One color per face.
    kGouraudShaded                  4          Smooth shaded display. Colors interpolated between vertices.
    kFlatShadedWithWireframe        5          Faceted display with wireframe overlay.
    kGouraudShadedWithWireframe     6          Smooth shaded display with wireframe overlay.
    </table>
    If the new render mode value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#7">Managing Render Modes</EXTLINK>
  */
  virtual OdTvResult setMode(RenderMode mode) = 0;

  /** \details
    Retrieves the current render mode for the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.    
    \returns Returns current render mode value. 
    \remarks
    The method returns one of the following values:
      
    <table>
    Name                            Value      Description
    k2DOptimized                    0          Standard display. Optimized for 2D.
    kWireframe                      1          Standard display. Uses 3D pipeline.
    kHiddenLine                     2          Wireframe display. Hidden lines removed.
    kFlatShaded                     3          Faceted display. One color per face.
    kGouraudShaded                  4          Smooth shaded display. Colors interpolated between vertices.
    kFlatShadedWithWireframe        5          Faceted display with wireframe overlay.
    kGouraudShadedWithWireframe     6          Smooth shaded display with wireframe overlay.
    </table>
    If the rc parameter is not null and the render mode value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#7">Managing Render Modes</EXTLINK>
  */
  virtual RenderMode mode(OdTvResult* rc = NULL) const = 0;

  /** \details
    Adds a specified scene model to the view object.
    
    \param sceneModelId [in] An identifier of a model object to be added.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if a specified scene model was added to the view; otherwise returns false.
    \remarks 
    If the rc parameter is not null and a new scene model was successfully added, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#3">Managing Model Collections</EXTLINK>
  */
  virtual bool addModel(const OdTvModelId& sceneModelId, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes a specified scene model from the view object.
    
    \param sceneModelId [in]  ID of the model object.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if a specified scene model was removed from the view; otherwise returns false.
    \remarks 
    If the rc parameter is not null and a scene model was successfully removed from the view, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#3">Managing Model Collections</EXTLINK>
  */
  virtual bool eraseModel(const OdTvModelId& sceneModelId, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes all scene models from the view object.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the model's remove operation.
    \remarks 
    If all models were successfully removed from the view, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#3">Managing Model Collections</EXTLINK>
  */
  virtual OdTvResult eraseAllModels() = 0;

  /** \details
    Retrieves the quantity of models associated with the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current quantity of models associated with the view object.
    \remarks 
    If the rc parameter is not null and the quantity of view models was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#3">Managing Model Collections</EXTLINK>
  */
  virtual int numModels(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves a view model with a specified index.
    
    \param modelIndex [in] A model index. 
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the identifier of a model object with a specified index. The model is represented with the <link OdTvModel, OdTvModel> object.
    \remarks 
    If the rc parameter is not null and the model object was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#3">Managing Model Collections</EXTLINK>
  */
  virtual OdTvModelId  modelAt(int modelIndex, OdTvResult* rc = NULL) = 0;

  /** \details
    Translates the view camera position and target according to a specified direction and distance.
    
    \param dollyVector [in] A camera coordinates dolly vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the translation operation.
    \remarks
    Camera coordinates are relative to the view of a target from a camera. 
    If the translation was successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#5">Managing Camera Transformation Actions</EXTLINK>
  */
  virtual OdTvResult dolly(const OdTvVector& dollyVector) = 0;
  
  /** \details
    Translates the view camera position and target according to a specified camera coordinates dolly amount.
    
    \param xDolly [in]  A camera coordinate X dolly amount.
    \param yDolly [in]  A camera coordinate Y dolly amount.
    \param zDolly [in]  A camera coordinate Z dolly amount.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the translation operation.
    \remarks
    Camera coordinates are relative to the view of a target from a camera. 
    * The Y-axis is along the up vector. 
    * The Z-axis is along the vector from the camera position to the target. 
    * The X-axis is the cross product of the Y-axis and the Z-axis.
    If the translation was successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#5">Managing Camera Transformation Actions</EXTLINK>
  */
  virtual OdTvResult dolly(double xDolly, double yDolly, double zDolly) = 0;

  /** \details
    Rotates the view camera about the eye vector according to a specified roll angle.
    
    \param rollAngle [in]  A camera counterclockwise roll angle.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the rotation.
    \remarks
    A positive angle leads to the camera counterclockwise rotation about the eye vector, when viewed from the camera position to the target. 
    This corresponds to a clockwise rotation of the up vector.
    Camera coordinates are relative to the view of a target from a camera. 
    * The Y-axis is along the up vector. 
    * The Z-axis (eye vector) is along the vector from the camera position to the target. 
    * The X-axis is the cross product of the Y-axis and the Z-axis.
    All angles are measured in radians.
    If the camera was successfully rotated, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#5">Managing Camera Transformation Actions</EXTLINK>
  */
    virtual OdTvResult roll(double rollAngle) = 0;

  /** \details
    Orbits the camera around the target according to specified angles.
    
    \param xOrbit [in]  An X-axis orbit value.
    \param yOrbit [in]  A Y-axis orbit value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The camera moves on the surface of a sphere with a center that is the camera target. The sphere radius is equal to the distance from the camera position to its target.
    * First the camera is rotated about an axis parallel to the X-axis and passing through the target.
    * Second the camera is rotated about an axis parallel to the Y-axis and passing through the target.
    The camera coordinates are relative to the view of a target from the camera. 
      
    * The Y-axis is along the up vector. 
    * The Z-axis (eye vector) is along the vector from the camera position to the target. 
    * The X-axis is the cross product of the Y-axis and the Z-axis.
    All angles are measured in radians.
    If the orbit operation was successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#5">Managing Camera Transformation Actions</EXTLINK>
  */
    virtual OdTvResult orbit(double xOrbit, double yOrbit) = 0;

  /** \details
    Scales the focal length of the camera according to a specified factor.
    
    \param zoomFactor [in]  A zoom factor value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the zoom operation.
    \remarks
    If the zoom operation was successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#5">Managing Camera Transformation Actions</EXTLINK>
  */
    virtual OdTvResult zoom(double zoomFactor) = 0;

  /** \details
    Rotates the target around the camera according to specified angles.
    
    \param xPan [in]  An X-axis pan angle.
    \param yPan [in]  A Y-axis pan angle.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the pan operation.
    \remarks
    The target moves on the surface a sphere with a center that is the camera position. The sphere radius is equal to the distance from the camera position to its target.

    * First the target is rotated about an axis parallel to the X-axis and passing through the camera.
    * Second the target is rotated about an axis parallel to the Y-axis and passing through the camera.
    The camera coordinates are relative to the view of a target from a camera.
    * The Y-axis is along the up vector. 
    * The Z-axis (eye vector) is along the vector from the camera position to the target. 
    * The X-axis is the cross product of the Y-axis and the Z-axis.
    All angles are measured in radians.
    If the pan operation was successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#5">Managing Camera Transformation Actions</EXTLINK>
  */
    virtual OdTvResult pan(double xPan, double yPan) = 0;

  /** \details
    Scales the camera to completely include a specified WCS box inside the view frustum.
    
    \param minPt            [in]  A minimal WCS box point.
    \param maxPt            [in]  A maximum WCS box point.
    \param bCacheIfNonSetup [in]  Indicates, that it is need to cache the input extent's parameters if the view is still "non-setup."
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the scale operation.
    \remarks 
    If the scale operation was successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#5">Managing Camera Transformation Actions</EXTLINK>
  */
  virtual OdTvResult zoomExtents(const OdTvPoint &minPt, const OdTvPoint &maxPt, bool bCacheIfNonSetup = false) = 0;

  /** \details
    Scales the camera to completely include a specified screen area.
    
    \param lowerLeft  [in] A point that represents the lower-left corner in normalized device coordinates ([0.0 .. 1.0]).
    \param upperRight [in] A point that represents the upper-right corner in normalized device coordinates ([0.0 .. 1.0]).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the scale operation.
    \remarks 
    If the scale operation was successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#5">Managing Camera Transformation Actions</EXTLINK>
  */
  virtual OdTvResult zoomWindow(const OdGePoint2d &lowerLeft, const OdGePoint2d &upperRight) = 0;

  /** \details
    Runs the selection procedure inside the view object.
    
    \param pts      [in] A pointer to an array of selection points in the device coordinate space (pixels).
    \param nPoints  [in] A quantity of selection points.
    \param options  [in] A set of selection options such as mode, level, pick box size.
    \param modelId  [in] An identifier of a model where the objects should be selected.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the selection operation.
    \returns Returns a smart pointer to the <link OdTvSelectionSet, selection set object>.
    \remarks 
    If the rc parameter is not null and the selection operation was successful, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_features_selections, Work with Selections>
  */
  virtual OdTvSelectionSetPtr select(const OdTvDCPoint* pts, int nPoints, const OdTvSelectionOptions& options, const OdTvModelId& modelId, OdTvResult* rc = NULL) = 0;

  /** \details
    Runs the collision detection 'all with all' procedure inside the view object.
    
    \param modelId           [in]  Model which contains objects to check.
    \param collidedWho       [out] A smart pointer to the set of objects who collided (first object in the collided pair).
    \param collidedWithWhom  [out] A smart pointer to the set of objects with whom collided (second object in the collided pair).
    \param level             [in]  The selection level.
    \param bIntersectionOnly [in]  Consider only intersections (not consider touches like between two sides of cube).
    \param tolerance         [in]  Collision tolerance; used in IntersectionsOnly case.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the collision operation.
    \remarks
    If the collision detection operation was successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
    This method should be used when it is need to find all collisions inside the input model. The selection level is need to define the level for the
    resulting selection sets. 'collidedWho' and 'collidedWithWhom' sets have equal length.
    \sa
    <link tv_working_with_features_collision_detection, Work with Collision Detection>
  */
  virtual OdTvResult collide(const OdTvModelId& modelId, OdTvCollidedResultPtr& collidedWho, OdTvCollidedResultPtr& collidedWithWhom,
                             OdTvSelectionOptions::Level level = OdTvSelectionOptions::kEntity, bool bIntersectionOnly = true, double tolerance = 1e-10 ) = 0;

  /** \details
    Runs the collision detection 'a few with all' procedure inside the view object.
    
    \param inputSet           [in] A smart pointer to the set of objects to check.
    \param modelId            [in] Model which contains objects to be checked with.
    \param collidedFromInput  [out] A smart pointer to the set of objects which are collided (first object in the collided pair). Can be NULL.
    \param level              [in] The selection level.
    \param bIntersectionOnly  [in] Consider only intersections (not consider touches like between two sides of cube).
    \param tolerance          [in]  Collision tolerance; used in IntersectionsOnly case.
    \param rc                 [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the <link OdTvResult, set> of colliding objects.
    \remarks
    If the rc parameter is not null and collision detection operation was successful, the method returns the tvOk value;
    otherwise it returns an appropriate error code. This method should be used when it is need to find all collisions between inputSet and all other objects.
    The selection level is need to define the level for the resulting selection set(s). The resulting and 'collidedWithWhom' sets have equal length. If the 'collidedFromInput'
    is NULL, then it is not need to collect the first objects in colliding pairs.
    \sa
    <link tv_working_with_features_collision_detection, Work with Collision Detection>
  */
  virtual OdTvCollidedResultPtr collide(const OdTvSelectionSetPtr& inputSet, const OdTvModelId& modelId, OdTvCollidedResultPtr& collidedFromInput,
                                      OdTvSelectionOptions::Level level = OdTvSelectionOptions::kEntity, bool bIntersectionOnly = true, double tolerance = 1e-10, OdTvResult* rc = NULL) = 0;

  /** \details
    Runs the collision detection 'a few with a few' procedure inside the view object.
    
    \param inputSet           [in]  A smart pointer to the set of objects to check.
    \param collisionWithSet   [in]  A smart pointer to the set of possible colliding objects.
    \param collidedFromInput  [out] A smart pointer to the set of objects which are collided (first object in the collided pair). Can be NULL.
    \param level              [in] The selection level.
    \param bIntersectionOnly  [in] Consider only intersections (not consider touches like between two sides of cube).
    \param tolerance          [in]  Collision tolerance; used in IntersectionsOnly case.
    \param rc                 [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the <link OdTvResult, set> of colliding objects.
    \remarks 
    If the rc parameter is not null and collision detection operation was successful, the method returns the tvOk value; 
    otherwise it returns an appropriate error code. This method should be used when it is need to find all collisions between 'inputSet' and 'collisionWithSet' set.
    The selection level is need to define the level for the resulting selection set(s). The resulting and 'collidedFromInput' sets have equal length. If the 'collidedFromInput'
    is NULL, then it is not need to collect the first objects in colliding pairs.
    \sa
    <link tv_working_with_features_collision_detection, Work with Collision Detection>
  */
  virtual OdTvCollidedResultPtr collide(const OdTvSelectionSetPtr& inputSet, const OdTvSelectionSetPtr& collisionWithSet, OdTvCollidedResultPtr& collidedFromInput,
                                        OdTvSelectionOptions::Level level = OdTvSelectionOptions::kEntity, bool bIntersectionOnly = true, double tolerance = 1e-10, OdTvResult* rc = NULL) = 0;

  /** \details
    Runs the collision detection 'all with all' procedure inside the view object.
    
    \param modelId           [in]  Model which contains objects to check.
    \param result            [out] A reference for the OdTvCollidedPairResult instance to store result.
    \param options           [in] Collision detection options.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the collision operation.
    \remarks
    If the collision detection operation is successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
    This method finds all collisions inside the input model.
    \sa
    <link tv_working_with_features_collision_detection, Work with Collision Detection>
  */
  virtual OdTvResult collide( const OdTvModelId& modelId, OdTvCollidedPairResult& result, const OdTvCollisionOptions& options = OdTvCollisionOptions() ) = 0;
  
  /** \details
    Runs the collision detection 'a few with a few' procedure inside the view object.
    
    \param inputSet           [in]  A smart pointer to the set of objects to check.
    \param collisionWithSet   [in]  A smart pointer to the set of possible colliding objects.
    \param result             [out]  A reference for the OdTvCollidedPairResult instance to store result.
    \param options            [in] Collision detection options.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the collision operation.
    \remarks
    If the collision detection operation is successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
    This method finds all collisions between 'inputSet' and 'collisionWithSet' set.
    \sa
    <link tv_working_with_features_collision_detection, Work with Collision Detection>
  */
  virtual OdTvResult collide( const OdTvSelectionSetPtr& inputSet, const OdTvSelectionSetPtr& collisionWithSet, OdTvCollidedPairResult& result, const OdTvCollisionOptions& options = OdTvCollisionOptions() ) = 0;
  
  /** \details
    Runs the collision detection 'a few with all' or 'a few with themselves' procedure inside the view object.
    
    \param inputSet           [in] A smart pointer to the set of objects to check.
    \param modelId            [in] Model which contains objects to be checked with.
    \param result             [out]  A reference for the OdTvCollidedPairResult instance to store result.
    \param options            [in] Collision detection options.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the collision operation.
    \remarks
    If modelId is valid, method detects collisions between list and all other entities from the model.
    If modelId is empty, method detects collisions between entities in list.
    If the collision detection operation is successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
    This method finds all collisions between 'inputSet' and all other objects or between all objects in 'inputSet'.
    \sa
    <link tv_working_with_features_collision_detection, Work with Collision Detection>
  */
  virtual OdTvResult collide( const OdTvSelectionSetPtr& inputSet, const OdTvModelId& modelId, OdTvCollidedPairResult& result, const OdTvCollisionOptions& options = OdTvCollisionOptions() ) = 0;

  /** \details
    Highlights a given item path.
    
    \param id                [in] An identifier of an entity that should be highlighted (or subitems that should be highlighted).
    \param path              [in] A path to subitems that should be highlighted (subentity, geometry, or subgeometry (face or edge) objects).
    \param bDoIt             [in] A flag value that determines whether highlighting is enabled (if true) or disabled (if false). This flag can switch the highlighting on or off.
    \param highLightStyleId  [in] A value that determines an index of highlight style in the array that was set to the device.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the highlighting operation.
    \remarks 
    If the highlighting operation was successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_features_highlighting, Work with Highlighting>
  */
  virtual OdTvResult highlight(const OdTvEntityId& id, const OdTvSubItemPath& path, bool bDoIt = true, OdUInt16 highLightStyleId = 0) = 0;

  /** \details
    Retrieves the current visible flag value for a specified point in the view object.
    
    \param pt [in] A point to check for visibility. The point coordinates are in WCS. 
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the specified point is visible inside the view; otherwise returns false.
    \remarks 
    If the rc parameter is not null and the visibility flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool isPointVisibleInView(const OdTvPoint &pt, OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves whether a specified point is inside the view area.
    
    \param screenPoint  [in] A point in the device coordinate space.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the specified point is inside the view area; otherwise returns false.
    \remarks 
    If the rc parameter is not null and the operation was successful, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool pointInView(const OdTvPoint2d& screenPoint, OdTvResult* rc = NULL) const = 0;

  /** \details
  Returns the display pixel density at the specified point for this view object.

  \param point [in]  WCS center of the unit square.
  \param pixelDensity [out]  Receives the pixel density.
  \param bUsePerspective [in]  Enable perspective inclusion into pixel density calculation.
  \remarks
  Pixel density is measured in pixels per WCS unit.
  This function can be used to determine if the geometry generated for an object will
  be smaller than the size of a pixel.
  */
  virtual OdTvResult getNumPixelsInUnitSquare(const OdTvPoint& point, OdTvPoint2d& pixelDensity, bool bUsePerspective = true) const = 0;

  /** \details
    Set a new lineweight mode to the view object.
    
    \param lwMode [in]  A new lineweight mode value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the new lineweight mode value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#13">Managing Lineweight Display</EXTLINK>
  */
  virtual OdTvResult setLineWeightMode(LineWeightMode lwMode) = 0;

  /** \details
    Retrieves the current lineweight mode value for the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current lineweight mode represented with a value of the <link OdTvGsView::LineWeightMode, LineWeightMode> enumeration.
    \remarks 
    If the rc parameter is not null and the lineweight mode value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#13">Managing Lineweight Display</EXTLINK>
  */
  virtual LineWeightMode getLineWeightMode(OdTvResult* rc = NULL) const = 0;

  /** \details
    Set a new lineweight scale value to the view object.
    
    \param dScale [in] A new lineweight scale value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the new lineweight scale value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#13">Managing Lineweight Display</EXTLINK>
  */
  virtual OdTvResult setLineWeightScale(double dScale) = 0;

  /** \details
    Retrieves the current lineweight scale value for the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns current lineweight scale value.
    \remarks 
    If the rc parameter is not null and the lineweight scale value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#13">Managing Lineweight Display</EXTLINK>
  */
  virtual double getLineWeightScale(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new array of lineweights for the view object.
    
    \param numLineweights [in] A quantity of lineweight values.
    \param lineweights    [in] A pointer to the lineweight values array.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the new array of lineweight values was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#13">Managing Lineweight Display</EXTLINK>
 */
  virtual OdTvResult setLineWeightEnum(int numLineweights, const OdUInt8* lineweights) = 0;

  /** \details
    Regenerates the contents of the view object.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the regeneration.
    \remarks 
    If the regeneration was successful, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult regen() = 0;

  /** \details
    Enables default lighting for the view object.
    
    \param bEnable    [in] A new default lighting flag value. If the flag value is equal to true, the lighting is enabled; otherwise it is disabled.
    \param lightType  [in] A new default lighting type.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the lighting flag was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual OdTvResult enableDefaultLighting(bool bEnable, DefaultLightingType lightType = kTwoLights) = 0;

  /** \details
    Retrieves the current value of the default lighting flag. If the flag is equal to true, the default lighting is enabled; otherwise it is disabled.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the default lighting is enabled; otherwise returns false.
    \remarks 
    If the rc parameter is not null and the current flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual bool defaultLightingEnabled(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the default lighting type for the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current default lighting type represented with a value of the <link OdTvGsView::DefaultLightingType, DefaultLightingType> enumeration.
    \remarks 
    If the rc parameter is not null and the current default lighting type was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual DefaultLightingType defaultLightingType(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new ambient light color for the view.
    
    \param color [in] A new ambient light color value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the new ambient light color value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual OdTvResult setAmbientLightColor(const OdTvColorDef& color) = 0;

  /** \details
    Retrieves the current ambient light color for the view.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current ambient light color for the view represented with an <link OdTvColorDef, OdTvColorDef> object.
    \remarks 
    If the rc parameter is not null and the current ambient light color value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual OdTvColorDef getAmbientLightColor(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current direction of the default user-defined light.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a <link OdTvVector, vector> object that represents the direction of the default user-defined light.
    \remarks 
    If the rc parameter is not null and the current user-defined light direction was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual OdTvVector userDefinedLightDirection(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new direction of the default user-defined light.
    
    \param lightDirection [in] A <link OdTvVector, vector> object that represents the new direction of the default user-defined light.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new light direction was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual OdTvResult setUserDefinedLightDirection(const OdTvVector& lightDirection) = 0;

  /** \details
    Retrieves the current intensity of the default light.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a double value that represents the current default light intensity.
    \remarks 
    If the rc parameter is not null and the current default light intensity was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual double defaultLightingIntensity(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new default light intensity for the view object.
    
    \param dIntensity [in] A double value that represents the new intensity of the default light.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new default light intensity was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual OdTvResult setDefaultLightingIntensity(double dIntensity) = 0;

  /** \details
    Retrieves the current default light color of the view object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a <link OdTvColorDef, color definition> object that represents the current default light color.
    \remarks 
    If the rc parameter is not null and the current default light color was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual OdTvColorDef defaultLightingColor(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new default light color for the view object.
    
    \param color [in] A <link OdTvColorDef, color definition> object that represents the new default light color.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new default light color was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual OdTvResult setDefaultLightingColor(const OdTvColorDef& color) = 0;

  /** \details
    Retrieves the current value of the save flag. The save flag determines whether the view content should be saved in a file (if true) or not (if false).
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the view should be saved in a file; otherwise returns false.
    \remarks 
    If the rc parameter is not null and the current value of the save flag was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getNeedSaveInFile(OdTvResult* rc = NULL) const = 0;

  /** \details
  Sets the view to be active or inactive.
  \param bIsActive [in] A new value of the active flag for the view. If the flag is equal to true, the view becomes active; otherwise the view becomes inactive.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of activating (or deactivating) the view.
  \remarks 
  If the view was successfully activated or deactivated, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual OdTvResult setActive(bool bIsActive) = 0;

  /** \details
    Retrieves the current value of the active flag for the view. If the view is active, the flag is equal to true; otherwise the flag is equal to false.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the view is active; otherwise returns false.
    \remarks 
    If the rc parameter is not null and the current value of the active flag was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#6">Managing View Lighting</EXTLINK>
  */
  virtual bool getActive(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new color and width of the border for the view object.
    
    \param color [in] A new border color value.
    \param width [in] A new border width in pixels.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the new border color and width were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#9">Managing View Borders</EXTLINK>
  */
  virtual OdTvResult setBorderProperties(ODCOLORREF color, OdUInt32 width) = 0;

  /** \details
    Retrieves the current border color and width for the view object.
    
    \param color [out] A placeholder for the border color value.
    \param width [out] A placeholder for the border width in pixels.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the current border color and width were successfully returned to a calling subroutine, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#9">Managing View Borders</EXTLINK>
  */
  virtual OdTvResult getBorderProperties(ODCOLORREF& color, OdUInt32& width) const = 0;

  /** \details
    Sets a new value of the border visibility flag. The border visibility flag determines whether the border of the view is visible (if true) or invisible (if false).
    
    \param bVisible [in] A new border visibility flag value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the new value of the border visibility flag was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#9">Managing View Borders</EXTLINK>
  */
  virtual OdTvResult setBorderVisibility(bool bVisible) = 0;

  /** \details
    Retrieves the current value of the border visibility flag value for the view object. The border visibility flag determines whether the border of the view is visible (if true) or invisible (if false).
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the border is visible for the view; otherwise returns false.
    \remarks 
    If the rc parameter is not null and the current value of the border visibility flag was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#9">Managing View Borders</EXTLINK>
  */
  virtual bool getBorderVisibility(OdTvResult *rc = NULL) const = 0;

  /** \details
    Defines a polygonal clip region for the view object.
    
    \param numContours  [in] A quantity of polygonal contours.
    \param numVertices  [in] An array of vertex quantities for each polygonal contour.
    \param vertices     [in] Array of the device coordinates (in pixels) or world (eye) coordinates of the vertices that define polygonal contours.
    \param bWCS         [in] A flag that determines whether vertices are represented in the WCS (eye) coordinates (if true). If the flag is equal to false, vertices are represented in the device coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    In the case of bWCS = true, the incoming WCS(ECS) contour's coordinates are automatically multiplied by 'worldToDevice' matrix during each update.
    If the clip region was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual OdTvResult setClipRegion(OdUInt32 numContours, OdUInt32 const* numVertices, OdTvPoint2d const* vertices, bool bWCS = false) = 0;

  /** \details
    Retrieves the current polygonal clip region for the view. 
    
    \param counts   [out] A placeholder for the array of the vertex quantities for each polygonal contour.
    \param vertices [out] A placeholder for the array of device coordinates (in pixels) or world (eye) coordinates of the vertices, which define polygonal contours.
    \param bWCS     [out] A placeholder for the WCS coordinates flag value. If the flag is equal to true, vertices are represented with WCS coordinates; otherwise vertices are represented in the device coordinates.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the clip region was successfully returned to a calling subroutine, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual OdTvResult getClipRegion(OdUInt32Array& counts, OdTvPoint2dArray& vertices, bool& bWCS) const = 0;

  /** \details
    Removes the current polygonal clip region from the view.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If current clip region was successfully removed, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual OdTvResult removeClipRegion() = 0;

  /** \details
    Sets a new name for the view.
    
    \param sName [in]  A view name represented with a string value up to 255 characters long.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    If the new name was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#1">Setting and Getting View Names</EXTLINK>
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
    Retrieves the current name of the view.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current name of the view object. 
    \remarks 
    If the rc parameter is not null and the view name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#1">Setting and Getting View Names</EXTLINK>
  */
  virtual OdString getName(OdTvResult* rc = NULL) const = 0;

  /** \details
    Adds a sibling view (parameters of the view are copied to the added sibling view).
    
    \param id [in] An identifier of a sibling view object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the new sibling view was successfully added, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult addSibling(const OdTvGsViewId& id) = 0;

  /** \details
    Removes view from the sibling list
    
    \param id [in] An identifier of a sibling view object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the view was successfully removed from te sibling list, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeSibling(const OdTvGsViewId& id) = 0;

  /** \details
  Retrieves the owner view object that controls the parameters of the view object. 
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the identifier of the owner view. If the view does not have an owner view, the isNull() method of the returned identifier returns true.
  \remarks 
  If the rc parameter is not null and the owner view identifier was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvGsViewId getSiblingOwner(OdTvResult *rc = NULL) const = 0;

  /** /details
    Adds a new viewport object to the view object (the view controls the screen rectangle of the added viewport).
    
    \param id           [in] An identifier of the added viewport. 
    \param viewportInfo [in] Viewport information. 
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the add viewport operation.
    \remarks 
    If the new viewport was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#8">Managing Viewports</EXTLINK>
  */
  virtual OdTvResult addViewportObject(const OdTvGsViewId &id, const ViewportObjectInfo& viewportInfo) = 0;

  /** \details
    Retrieves the view object that controls the current viewport. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the rc parameter is not null and the identifier of the viewport owner object was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \returns Returns an identifier of the owner view object.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#8">Managing Viewports</EXTLINK>
  */
  virtual OdTvGsViewId getViewportObjectOwner(OdTvResult *rc = NULL) const = 0;

  /** \details
    Sets a new value for the two-dimensional mode flag. If this flag is equal to true, the rotation, pan and orbit operations for the view are denied. If the flag value is equal to false, the view works in three-dimensional mode.
    
    \param b2dEnable [in]  A new two-dimensional mode flag value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the new flag value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set2dMode(bool b2dEnable) = 0;

  /** \details
    Retrieves the current value of the two-dimensional flag. 
    
    If this flag is equal to true, the rotation, pan and orbit operations for the view are denied. If the flag value is equal to false, the view works in three-dimensional mode.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the view is in two-dimensional mode; otherwise returns false.
    \remarks 
    If the rc parameter is not null and the value of the two-dimensional flag was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool get2dMode(OdTvResult *rc = NULL) const = 0;

  /** \details
    Sets a new visual style to the view.
    
    \param id [in] An identifier of the visual style object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting the visual style.
    \remarks 
    If the new visual style was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_visual_styles, Work with Visual Styles>
  */
  virtual OdTvResult setVisualStyle(const OdTvVisualStyleId& id) = 0;

  /** \details
    Retrieves the current visual style for the view.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier of the current visual style.
    \remarks 
    If the current visual style object was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_visual_styles, Work with Visual Styles>
  */
  virtual OdTvVisualStyleId getVisualStyle(OdTvResult *rc = NULL) const = 0;

  /** \details
    Hides a specified layer in the view.
    
    \param id [in] An identifier of the layer that should be hidden.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of hiding a layer.
    \remarks 
    If the specified layer was successfully hidden, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult hideLayer(const OdTvLayerId& id) = 0;

  /** \details
    Shows (unhides) a specified layer in the view.
    
    \param id [in] An identifier of the layer that should be shown.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of unhiding a layer.
    \remarks 
    If the specified layer was successfully shown, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult unhideLayer(const OdTvLayerId& id) = 0;

  /** \details
    Shows (unhides) all layers in the view.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of showing all layers.
    \remarks 
    If all layers were successfully shown, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvResult unhideAllLayers() = 0;

  /** \details
    Retrieves the current value of the hidden flag for a specified layer in the view. The hidden flag is equal to true if a specified layer is hidden; otherwise it is equal to false.
    
    \param id [in]  An identifier of a layer object.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the layer is hidden; otherwise the method returns false.
    \remarks 
    If the rc parameter is not null and the hidden flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual bool isLayerHidden(const OdTvLayerId& id, OdTvResult *rc = NULL) = 0;

  /** \details
    Retrieves all hidden layers from the view.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an array of identifiers of hidden layers.
    \remarks 
    If the rc parameter is not null and the array of identifiers of hidden layers was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_layers, Work with Layers>
  */
  virtual OdTvLayerIdsArray getHiddenLayers(OdTvResult *rc = NULL) = 0;

  /** \details
    Sets front clipping for the view and the front clipping distance from the camera target of the view.
    
    \param bEnable    [in]  A front clipping enable flag. If the flag is equal to true, front clipping is enabled; otherwise front clipping is disabled. 
    \param frontClip  [in]  A front clipping distance.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of enabling or disabling front clipping.
    \remarks 
    If front clipping was successfully enabled or disabled, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual OdTvResult setFrontClip(bool bEnable, double frontClip = 1.0) = 0;

  /** \details
    Retrieves the current front clipping flag value and the front clipping distance from the camera target. 
    
    If front clipping is enabled, the flag value is equal to true; otherwise the flag value is equal to false. 
    \param frontClip  [out] A placeholder for the front clipping distance value.
    \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if front clipping is enabled for the view; otherwise returns false.
    \remarks 
    If the rc parameter is not null and the information about front clipping for the view was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual bool getFrontClip(double& frontClip, OdTvResult *rc = NULL) const = 0;

  /** \details
    Sets back clipping for the view and the back clipping distance from the camera target of the view.
    
    \param bEnable   [in]  A back clipping enable flag. If the flag is equal to true, back clipping is enabled; otherwise back clipping is disabled. 
    \param backClip  [in]  A back clipping distance.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of enabling or disabling back clipping.
    \remarks 
    If back clipping was successfully enabled (or disabled), the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual OdTvResult setBackClip(bool bEnable, double backClip = 0.0) = 0;

  /** \details
    Retrieves the current back clipping flag value and the back clipping distance from the camera target. 
    
    If back clipping is enabled, the flag value is equal to true; otherwise the flag value is equal to false. 
    \param backClip [out] A placeholder for the back clipping distance value.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if back clipping is enabled for the view; otherwise returns false.
    \remarks 
    If the rc parameter is not null and the information about back clipping for the view was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#4">Managing Camera Parameters</EXTLINK>
  */
  virtual bool getBackClip(double& backClip, OdTvResult *rc = NULL) const = 0;

  /** \details
    Sets a new background object for the view.
    
    \param backgroundId [in] An identifier of the background object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting a background object.
    \remarks 
    If the new background object was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_attributes_view_backgrounds, Work with View Backgrounds>
  */
  virtual OdTvResult setBackground(const OdTvGsViewBackgroundId& backgroundId) = 0;

  /** \details
    Retrieves the current background object for the view.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier of the background object.
    \remarks 
    If the rc parameter is not null and the background object identifier was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <link tv_working_with_attributes_view_backgrounds, Work with View Backgrounds>
  */
  virtual OdTvGsViewBackgroundId getBackground(OdTvResult *rc = NULL) = 0;

  /** \details
    Starts the view interactivity mode. 
    
    \param frameRateInHz [in] A frame rate value (FPS).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The frame rate value defines the desired minimum number of frames shown per one second. 
    In other words, if you want to limit the time that each redraw operation takes (e.g., not more than X seconds),
    the frameRateInHz parameter value should be the inverse ratio of this time limit (1 / X).
    If the view interactivity mode is successfully started, the method returns tvOk value; otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#16">Using Interactivity Mode</EXTLINK>
  */
  virtual OdTvResult beginInteractivity(double frameRateInHz) = 0;

  /** \details
    Retrieves whether the view is currently in interactive mode.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the view is in interactivity mode; otherwise the method returns false.
    \remarks 
    If the rc parameter is not null and the interactivity mode flag value is successfully returned, 
    the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#16">Using Interactivity Mode</EXTLINK>
  */
  virtual bool isInInteractivity(OdTvResult *rc = NULL) const = 0;

  /** \details
    Retrieves the current frame rate value (FPS) for the view interactivity mode.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current frame rate value.
    \remarks
    The frame rate value can be specified through calling the 
    <link OdTvGsView::beginInteractivity@double, beginInteractivityMode()> method.
    If the rc parameter is not null and the frame rate value for the interactivity mode is successfully returned, 
    the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#16">Using Interactivity Mode</EXTLINK>
  */
  virtual double getInteractivityFrameRate(OdTvResult *rc = NULL) const = 0;

  /** \details
    Stops the view interactivity mode. 
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the view interactivity mode is successfully stopped, the method returns tvOk value; 
    otherwise it returns an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#16">Using Interactivity Mode</EXTLINK>
  */
  virtual OdTvResult endInteractivity() = 0;

  /** \details
    Retrieves the extents, which were returned by the last call of the 
    <link OdTvGsView::viewExtents@OdGeBoundBlock3d&@OdTvResult*@const, viewExtents()> method.
    
    \param extents [out] A placeholder for the extents object.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the last extents object is successfully returned; 
    otherwise the method returns false. 
    \remarks 
    If the rc parameter is not null and the method call is successful, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    If the <link OdTvGsView::viewExtents@OdGeBoundBlock3d&@OdTvResult*@const, viewExtents()> method was not called, 
    the method returns false. 
  */
  virtual bool getLastViewExtents(OdGeBoundBlock3d& extents, OdTvResult *rc = NULL) const = 0;

  /** \details
    Add cutting plane to the view.
    
    \param plane [in] Plane object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#17">Managing Cutting Planes</EXTLINK>
  */
  virtual OdTvResult  addCuttingPlane(const OdTvPlane& plane) = 0;

  /** \details
    Retrieves the plane object associated with the given cutting plane.
    
    \param idPlane  [in]  Index of the plane.
    \param plane    [out] Plane object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#17">Managing Cutting Planes</EXTLINK>
  */
  virtual OdTvResult  getCuttingPlane(OdUInt32 idPlane, OdTvPlane& plane) const = 0;

  /** \details
    Updates the plane object associated with the given cutting plane.
    
    \param idPlane  [in]  Index of the plane.
    \param plane    [in]  Plane object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#17">Managing Cutting Planes</EXTLINK>
  */
  virtual OdTvResult  updateCuttingPlane(OdUInt32 idPlane, const OdTvPlane& plane) = 0;

  /** \details
    Returns the number of cutting planes.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the number of cutting planes
    \remarks
    If the rc parameter is not null and the number of cutting planes is successfully returned,
    the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#17">Managing Cutting Planes</EXTLINK>
  */
  virtual OdUInt32    numCuttingPlanes(OdTvResult *rc = NULL) const = 0;

  /** \details
    Removes the cutting plane with the given plane index.
    
    \param idPlane [in]  Index of the plane.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#17">Managing Cutting Planes</EXTLINK>
  */
  virtual OdTvResult  removeCuttingPlane(OdUInt32 idPlane) = 0;

  /** \details
    Removes all cutting planes.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#17">Managing Cutting Planes</EXTLINK>
  */
  virtual OdTvResult  removeCuttingPlanes() = 0;

  /** \details
    Set filling parameters of the cutting planes.
    
    \param bEnable  [in] A filling enable flag. If the flag is equal to true, the filling is enabled; otherwise filling is disabled.
    \param color    [in] A filling color.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks The filling works fully correct only for the case of one cutting plane. In the case of the multiple cutting planes the artifacts is possible.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#17">Managing Cutting Planes</EXTLINK>
  */
  virtual OdTvResult setEnableCuttingPlaneFill(bool bEnable, ODCOLORREF color = ODRGBA(255, 0, 0, 255)) = 0;

  /** \details
    Returns the filling parameters of the cutting planes.
    
    \param color  [out] A filling color.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the filling is enabled and false otherwise.
    \remarks
    If the rc parameter is not null and the parameters of the cutting plane filling is successfully returned,
    the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#17">Managing Cutting Planes</EXTLINK>
  */
  virtual bool getCuttingPlaneFillEnabled(ODCOLORREF& color, OdTvResult *rc = NULL) const = 0;

  /** \details
    Set filling pattern parameters of the cutting planes.
    
    \param bEnable   [in] A filling pattern enable flag. If the flag is equal to true, the filling pattern is enabled; otherwise filling pattern is disabled.
    \param fillStyle [in] A filling pattern style.
    \param color     [in] A filling pattern color.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#17">Managing Cutting Planes</EXTLINK>
  */
  virtual OdTvResult setCuttingPlaneFillPatternEnabled(bool bEnable, OdTvGsView::CuttingPlaneFillStyle fillStyle, ODCOLORREF color = ODRGB(255, 0, 0)) = 0;

  /** \details
    Returns the filling pattern parameters of the cutting planes.
    
    \param fillStyle [out] A filling pattern color.
    \param color     [out] A filling pattern style.
    \param rc        [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if the filling pattern is enabled and false otherwise
    \remarks
    If the rc parameter is not null and the parameters of the cutting plane filling pattern is successfully returned,
    the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_view_functionality.html#17">Managing Cutting Planes</EXTLINK>
  */
  virtual bool getCuttingPlaneFillPatternEnabled(OdTvGsView::CuttingPlaneFillStyle& fillStyle, ODCOLORREF& color, OdTvResult *rc = NULL) const = 0;

  /** \details
    Saves an image of current view to the file by specified path.

    \param imagePath [in]  Path to the file for saving.
    \param region    [in]  Rectangle specifies the view's region to return.
    \remarks
    Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult getSnapShot(const OdString& imagePath, const OdTvDCRect& region) = 0;

  /** \details
    Returns the raster image object of the current view.
    
    \param region [in]  Rectangle specifies the view's region to return.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    Returns image of the current view.
  */
  virtual OdGiRasterImagePtr getSnapShot(const OdTvDCRect& region, OdTvResult* rc = NULL) = 0;

  /** \details
    Allows to overrule the anti-aliasing behavior in current View.

    \param overrule [in]  value in the range [0; 3]. 0 means nothing to overrule; 1 means disable interprocess AA (LineSmoothing);
    2 means disable postprocess AA (FXAA); 3 means disable both AA.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult setAntiAliasingOverrule(OdUInt32 overrule) = 0;

  /** \details
   Returns the overrule value for the anti-aliasing behavior in current View.

   \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
   \returns Returns value in the range [0; 3]. 0 means nothing to overrule; 1 means disable interprocess AA (LineSmoothing);
   2 means disable postprocess AA (FXAA); 3 means disable both AA.
  */
  virtual OdUInt32 getAntiAliasingOverrule(OdTvResult* rc = NULL) const = 0;

  /** \details
    Allows to overrule a screen-space ambient occlusion (SSAO) in current View.

    \param bEnable [in]  The flag that indicates whether ambient occlusion should be enabled in current view.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    This overrule will has an effect only of the SSAO is switched on in the parent's OdTvGsDevice
  */
  virtual OdTvResult setSSAOEnabled(bool bEnable) = 0;

  /** \details
    Returns the overrule flag for a screen-space ambient occlusion in current View.
  
    \param rc [out] The flag that indicates whether ambient occlusion is enabled in current view.
    \returns Returns true if the SSAO is enabled, false otherwise.
  */
  virtual bool getSSAOEnabled(OdTvResult* rc = NULL) const = 0;

  /** \details
    Returns the camera object that is assigned to this view.
  
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns Id of assigned camera object or empty Id if not camera assigned.
    \remarks
    View can be assigned with only one camera at the same time. Call TvCamera::unassignView before assigning another camera.
  */
  virtual OdTvEntityId assignedCamera( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Checks whether view should adjust lens length to match all parameters the setView() method.
    
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns true if view should adjust lens length, otherwise returns false.
  */
  virtual bool getAdjustLensLength( OdTvResult* rc = NULL ) const = 0;
  
  /** \details
    Specifies whether a view should adjust lens length to match all parameters in the setView() method.
    
    \param bAdjust [in] The flag that indicates whether a view should adjust lens length.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult setAdjustLensLength( bool bAdjust ) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvGsView, OdTvGsView> object.
*/
typedef OdTvSmartPtr<OdTvGsView> OdTvGsViewPtr;


/** \details
  The interface class for a view object identifier that allows access to the <link OdTvGsView, OdTvGsView> object.
*/
class ODTV_EXPORT OdTvGsViewId : public OdTvId
{
public:
  
  /** \details
    Opens the view determined with its identifier for a read or write operation. 
    
    \param mode [in]  An open mode value.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the view object.
    \remarks
    If the rc parameter is not null and the view object was successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvGsViewPtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

};

#endif //_ODTV_GSVIEW_H_INCLUDED_
