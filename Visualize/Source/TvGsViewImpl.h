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

#ifndef _ODTV_GSVIEWIMPL_H_INCLUDED_
#define _ODTV_GSVIEWIMPL_H_INCLUDED_

#include "TD_PackPush.h"
#include "TvGsView.h"
#include "TvInterfaceWrappers.h"
#include "TvDataLink.h"
#include "TvEntityIteratorImpl.h"
#include "TvUserDataImpl.h"
#include "TvTraitsDefImpl.h"
#include "TvSelectionImpl.h"
#include "TvModelImpl.h"
#include "TvGiPath.h"

#include "Gs/Gs.h"
#include "Gs/GsModel.h"

//TD_DB
#include "DbObjectId.h"
#include "DbViewportTableRecord.h"
#include "Gs/GsFiler.h"
#include "../ExRender/ExHardwareSections.h"

#define VISUAL_STYLE_PREFIX  OD_T("$")

class OdGsDeviceForTvImpl;

/** \details
Method which returns the Gs render type of the model
*/
OdGsModel::RenderType GetGsRenderingType(OdTvModel::Type type);

/** \details
This structure stores the cutting plane parameters
*/
struct OdTvCuttingPlane
{
public:
  OdTvPoint                         m_position;
  OdTvVector                        m_normal;
  ODCOLORREF                        m_fillingColor;
  bool                              m_bFilled;
  bool                              m_bSetupToGs;
  bool                              m_bFillingPattern;
  ODCOLORREF                        m_fillingPatternColor;
  OdTvGsView::CuttingPlaneFillStyle m_fillingPatternStyle;

  OdTvCuttingPlane() : m_normal(OdTvVector::kZAxis), m_fillingColor(ODRGBA(255, 0, 0, 255)), m_bFilled(false)
    , m_bFillingPattern(false), m_fillingPatternColor(ODRGB(0, 0, 255)), m_fillingPatternStyle(OdTvGsView::kCheckerboard)
    , m_bSetupToGs(false)
  {
  }

  OdTvCuttingPlane(OdGePoint3d position, OdGeVector3d normal)
  {
    m_position = position;
    m_normal = normal;
    m_fillingColor = ODRGBA(255, 0, 0, 255);
    m_bFilled = false;
    m_bSetupToGs = false;
    m_bFillingPattern = false;
    m_fillingPatternColor = ODRGB(0, 0, 255);
    m_fillingPatternStyle = OdTvGsView::kCheckerboard;
  }
};
typedef OdArray<OdTvCuttingPlane, OdMemoryAllocator<OdTvCuttingPlane> > OdTvCuttingPlaneArray;

/** \details
    This class is a wrapper over the Gs View. This object is an inheritor of the 'OdTvDbViewportTableRecord'.
    Here it is important to note that 'assertWriteEnabled' not need here. 
*/
class OdTvGsViewImpl : public OdTvDbViewportTableRecord, public OdTvXDataStorage
{
  /** \details
  Defines flags for view object
  */
  enum ViewFlags
  {
    kNeedPerformZoomToExtents = 1, // this flag indicated, that inside first setupGs it is need to perform the zoom to extents
    kLwDataModified           = 2,
    kNeedSaveInFile           = 4,
    kInternal                 = 8, // means that it is an internal view (user couldn't get an access to it)
    kIsActiveView             = 16,
    kBordersVisibility        = 32,
    k2dMode                   = 64,
    kWCSClipping              = 128,
    kFrontClip                = 256,
    kBackClip                 = 512,
    kAdjustLensLength         = 1024,
    kSSAOEnable               = 2048,
  };

  OdTvGsViewImpl();

public:
  ODRX_DECLARE_MEMBERS(OdTvGsViewImpl);

  virtual ~OdTvGsViewImpl();

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Interface implementation
  //////////////////////////////////////////////////////////////////////////////////////////////////////

    /** \details
      Returns the TvGsDevice object associated with this View object.
    */
  OdTvGsDeviceId device(OdTvResult* rc = NULL) const;

  /** \details
  Sets the size and position of this Viewport object.
  \param lowerLeft [in]  Lower-left corner in nomalized device coordinates [0.0 .. 1.0].
  \param upperRight [in]  Upper-right corner in nomalized device coordinates [0.0 .. 1.0].
  \param screenRect [in]  Screen rectangle in device coordinates (pixels).

  \remarks
  (0,0) is the lower-left corner of the owning Device object. Coordinates increase upward and to the right.

  \remarks
  The View object can be partly or comp letely off screen.
*/
  OdTvResult setViewport(const OdGePoint2d& lowerLeft, const OdGePoint2d& upperRight, bool bFromInterface = false);
  OdTvResult setViewport(const OdTvDCRect& screenRect, bool bFromInterface = false);

  /** \details
    Returns the size and position of this Viewport object.
    \param lowerLeft [out]  Receives the lower-left corner in nomalized device coordinates [0.0 .. 1.0].
    \param upperRight [out]  Receives the upper-right corner in nomalized device coordinates [0.0 .. 1.0].
    \param screenRect [out]  Receives the screen rectangle in device coordinates (pixels).

    \remarks
    (0,0) is the lower-left corner of the owning Device object.  Coordinates increase upward and to the right.

    \remarks
    The View object may be partly or completely off screen.
  */
  OdTvResult getViewport(OdGePoint2d& lowerLeft, OdGePoint2d& upperRight) const;
  OdTvResult getViewport(OdTvDCRect& screenRect) const;

  /** \details
    Sets the camera parameters for this View object.

    \param position [in]  Camera position.
    \param target [in]  Camera target.
    \param upVector [in]  Camera up vector.
    \param fieldWidth [in]  Projection plane (field) width.
    \param fieldHeight [in]  Projection plane (field) height.
    \param projectionType [in]  Projection type.

    \remarks
    All parameters are in WCS coordinates.

    projectionType must be one of the following:

    <table>
    Name           Value
    kParallel      0
    kPerspective   1
    </table>

    \remarks
    This method defines the transfomation from WCS coordinates to normalized device coordinates.
  */
  OdTvResult setView(
    const OdTvPoint& position,
    const OdTvPoint& target,
    const OdTvVector& upVector,
    double fieldWidth,
    double fieldHeight,
    OdTvGsView::Projection projectionType = OdTvGsView::kParallel, bool bFromInterface = false);

  /** \details
    Returns the WCS camera position for this View object.
  */
  OdTvPoint position(OdTvResult* rc = NULL) const;

  /** \details
    Returns the WCS camera target for this View object.
  */
  OdTvPoint targetWrap(OdTvResult* rc = NULL) const;

  /** \details
    Returns the WCS camera up vector for this View object.
  */
  OdTvVector upVector(OdTvResult* rc = NULL) const;

  /** \details
    Returns the perspective lens length for this View object.
  */
  double lensLengthWrap(OdTvResult* rc = NULL) const;

  /** \details
    Sets the perspective lens length for this View object.
    \param lensLength [in]  Perspective lens length.
  */
  OdTvResult setLensLengthWrap(double lensLength, bool bFromInterface = false);

  /** \details
    Returns true if and only if the projection type for this View object is kPerspective.
  */
  bool isPerspective(OdTvResult* rc = NULL) const;

  /** \details
    Returns the WCS projection plane (field) width for this View object.
  */
  double fieldWidth(OdTvResult* rc = NULL) const;

  /** \details
    Returns the WCS projection plane (field) height for this View object.
  */
  double fieldHeight(OdTvResult* rc = NULL) const;

  double focalLength( OdTvResult* rc = NULL ) const;

  /** \details
    Returns the eye coordinate system extents of this view object.

    \param extents [out]  Receives the extents.

    \returns
    Returns true if and only if the extents are defined and view of the device has an appropriate method
  */
  bool viewExtents(OdGeBoundBlock3d& extents, OdTvResult* rc = NULL) const;

  /** \details
      Returns the matrix that transforms world space to view space for this View object.
  */
  OdGeMatrix3d viewingMatrix(OdTvResult* rc = NULL) const;

  /** \details
       Returns the matrix that transforms view space to normalized device space for this View object.

       \sa
       Coordinate Systems.
   */
  OdGeMatrix3d projectionMatrix(OdTvResult* rc = NULL) const;

  /** \details
      Returns the matrix that transforms normalized device space to screen space for this View object.

      \sa
      Coordinate Systems.
  */
  OdGeMatrix3d screenMatrix(OdTvResult* rc = NULL) const;

  /** \details
      Returns a matrix that transforms coordinates from world space to screen space for this View object.

      \remarks
      This is equivalent to the concatenation of the viewingMatrix,
      projectionMatrix, and screenMatrix.

      \sa
      Coordinate Systems.
  */
  OdGeMatrix3d worldToDeviceMatrix(OdTvResult* rc = NULL) const;

  /** \details
      Returns the matrix that transforms view space to the world space for this View object.
  */
  OdGeMatrix3d eyeToWorldMatrix(OdTvResult* rc = NULL) const;

  /** \details
      Returns lower left and upper right corners of the view object in device coordinates
  */
  OdTvResult viewDcCorners(OdGePoint2d& lower_left, OdGePoint2d& upper_right) const;

  /** \details
    Sets the render mode for this Viewport object.

    \param mode [in]  Render mode.

    \remarks
    mode must be one of the following:

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
  */
  OdTvResult setMode(OdTvGsView::RenderMode mode, bool bFromInterface = false);

  /** \details
    Sets the render mode for this Viewport object.

    \remarks
    mode must be one of the following:

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
  */
  OdTvGsView::RenderMode mode(OdTvResult* rc = NULL) const;

  /** /details
  Set visual style to the current view
  */
  OdTvResult setVisualStyleTv(const OdTvVisualStyleId& id);

  /** \details
  Returns the visual style of the current viewport object
  */
  OdTvVisualStyleId getVisualStyleTv(OdTvResult *rc = NULL) const;

  /** \details
    Adds the specified scene graph to this Viewport object.

    \param sceneModel [in]  Id of the model object.
  */
  bool addModel(const OdTvModelId& sceneModelId, OdTvResult* rc = NULL);

  /** \details
    Removes the specified scene model from this View object.

    \param sceneModel [in]  Id of the model object.
  */
  bool eraseModel(const OdTvModelId& sceneModelId, OdTvResult* rc = NULL);

  /** \details
    Removes all scene models from this View object.
  */
  OdTvResult eraseAllModels();

  /** \details
  Returns the number of models associated with this View object.
  */
  int numModels(OdTvResult* rc = NULL) const;

  /** \details
  Returns the specified OdTvModel object associated with this View object.
  \param modelIndex [in]  View index.
  */
  OdTvModelId  modelAt(int modelIndex, OdTvResult* rc = NULL);

  /** \details
    Translates the camera position and target by the specified Camera Coordinate dolly amount.

    \param dollyVector [in]  Camera Coordinate dolly vector.
    \param xDolly [in]  Camera Coordinate X dolly amount.
    \param yDolly [in]  Camera Coordinate Y dolly amount.
    \param zDolly [in]  Camera Coordinate Z dolly amount.

    \remarks
    Camera Coordinates are relative to the view of a target from a camera.

    * The Y-axis is along up vector.
    * The Z-axis is along the vector from camera position to the target.
    * The X-axis is the cross product Y-axis x Z-axis
  */
  OdTvResult dolly(const OdTvVector& dollyVector, bool bFromInterface = false);
  OdTvResult dolly(double xDolly, double yDolly, double zDolly, bool bFromInterface = false);

  /** \details
    Rotates the camera by the specified amount about the eye vector.

    \param rollAngle [in]  Camera CCW roll angle.

    \remarks
    Positive angles rotate the camera counterclockwise about the eye vector
    when viewed from the camera position to the target. This corresponds
    to a clockwise rotation of the up vector.

    \remarks
    Camera Coordinates are relative to the view of a target from a camera.

    * The Y-axis is along up-vector.
    * The Z-axis (eye vector) is along the vector from camera position to the target.
    * The X-axis is the cross product Y-axis x Z-axis.

    All angles are expressed in radians.
  */
  OdTvResult roll(double rollAngle, bool bFromInterface = false);

  /** \details
    Orbits the camera about the target by the specified amounts.

    \param xOrbit [in]  X-axis Orbit.
    \param yOrbit [in]  Y-axis Orbit.

    \remarks
    The camera moves on the surface a sphere whose center the camera target and whose
    radius is the distance from the camera position to its target

    * The camera is first rotated about an axis parallel to the X-axis and passing through the target.
    * The camera is next rotated about an axis parallel to the Y-axis and passing through the target

    \remarks
    Camera Coordinates are relative to the view of a target from a camera.

    * The Y-axis is along up vector.
    * The Z-axis is along the vector from camera position to the target.
    * The X-axis is the cross product Y-axis X Z-axis

    All angles are expressed in radians.
  */
  OdTvResult orbit(double xOrbit, double yOrbit, bool bFromInterface = false);

  /** \details
    Scales the focal length of the camera by the specified amount.

    \param zoomFactor [in]  Zoom factor.

  */
  OdTvResult zoom(double zoomFactor, bool bFromInterface = false);

  /** \details
    Rotates the target about the camera the specified amounts.

    \param xPan [in]  X-axis pan.
    \param yPan [in]  Y-axis pan.

    \remarks
    The target moves on the surface a sphere whose center the camera position and whose
    radius is the distance from the camera position to its target

    * The target is first rotated about an axis parallel to the X-axis and passing through the camera.
    * The target is next rotated about an axis parallel to the Y-axis and passing through the camera.

    \remarks
    Camera Coordinates are relative to the view of a target from a camera.

    * The Y-axis is along up vector.
    * The Z-axis is along the vector from camera position to the target.
    * The X-axis is the cross product Y-axis, Z-axis
    All angles are expressed in radians.
  */
  OdTvResult pan(double xPan, double yPan, bool bFromInterface = false);

  /** \details
    Scales the camera to completely include specified WCS box inside view frustum.

    \param minPt            [in]  minimal WCS box point.
    \param maxPt            [in]  maximal WCS box point.
    \param bCacheIfNonSetup [in]  Indicates, that it is need to cache the input extent's parameters if the view is still "non-setup."
  */
  OdTvResult zoomExtents(const OdTvPoint &minPt, const OdTvPoint &maxPt, bool bCacheIfNonSetup, bool bFromInterface = false);

  /** \details
    Scales the camera to completely include specified screen area.

    \param lowerLeft [in]  Lower-left corner in nomalized device coordinates [0.0 .. 1.0].
    \param upperRight [in]  Upper-right corner in nomalized device coordinates [0.0 .. 1.0].
  */
  OdTvResult zoomWindow(const OdGePoint2d &lowerLeft, const OdGePoint2d &upperRight, bool bFromInterface = false);

  /** \details
  Runs selection procedure inside this View object.

  \param pts [in]  Selection points in device coordinate space (pixels).
  \param nPoints [in]  Count of selection points.
  \param options [in]  Selection options like mode, level, pick box size.
  \param modelId [in]  Model in which we will find the objects.
  */
  OdTvSelectionSetPtr select(const OdTvDCPoint* pts, int nPoints, const OdTvSelectionOptions& options, const OdTvModelId& modelId, OdTvResult* rc = NULL);

  /** \details
  Runs collision detection procedure inside this View object (all with all)
  */
  OdTvResult collide(const OdTvDbObjectId& dbModelId, OdTvCollidedResultPtr& collidedWho, OdTvCollidedResultPtr& collidedWithWhom, OdTvSelectionOptions::Level level, bool bIntersectionOnly = true, const OdGeTol& tolerance = OdGeTol() );

  /** \details
  Runs collision detection procedure inside this View object (a few with a few of with all)
  */
  OdTvCollidedResultPtr collide(const OdTvSelectionSetPtr& inputSet, const OdTvSelectionSetPtr& collisionWithSet, const OdTvDbObjectId& dbModelId,
                              OdTvSelectionOptions::Level level, OdTvCollidedResultPtr& collidedWithWhom, bool bIntersectionOnly = true, const OdGeTol& tolerance = OdGeTol(), OdTvResult* rc = NULL);

  OdTvResult collide( const OdTvSelectionSetPtr& inputSet, const OdTvSelectionSetPtr& collisionWithSet, const OdTvDbObjectId& dbModelId, OdTvCollidedPairResult& result, const OdTvCollisionOptions& options = OdTvCollisionOptions() );

  /** \details
  Perform highlight of the given apth

  \param id               [in]    The id of the entity which shoudl be highlighted (or which subitem should be highlighted)
  \param path             [in]  The path to the subitem which should be highlighted (it could be subentity, geometry or subgeometry (face or edge))
  \param bDoIt            [in] Flag that indicates whether highlighting is enabled (true value) or disabled (false value).
  \param highLightStyleId  [in] A value that determines index of highlight style. This value need for multiple highlighting of objects.
  */
  OdTvResult highlight(const OdTvEntityId& id, const OdTvSubItemPath& path, bool bDoIt = true, OdUInt16 highLightStyleId = 0);

  /** \details
  Returns true if and only if specified point is visible inside current view frustum.

  \param pt [in]  WCS point for check.
  */
  bool isPointVisibleInView(const OdTvPoint &pt, OdTvResult* rc = NULL) const;

  /** \details
  Checks does specified point is inside viewport area.

  \param screenPoint [in]  Check point in device coordinate space.
  */
  bool pointInView(const OdTvPoint2d& screenPoint, OdTvResult* rc = NULL) const;

  /** \details
  Returns the display pixel density at the specified point for this view object.

  \param point [in]  WCS center of the unit square.
  \param pixelDensity [out]  Receives the pixel density.
  \param bUsePerspective [in]  Enable perspective inclusion into pixel density calculation.
  */
  OdTvResult getNumPixelsInUnitSquare(const OdTvPoint& point, OdTvPoint2d& pixelDensity, bool bUsePerspective = true) const;

  /** \details
    Set the lineWeight mode to this view object

    \param lwMode [in]  LineWeight mode.
  */
  OdTvResult setLineWeightMode(OdTvGsView::LineWeightMode lwMode, bool bFromInterface = false);

  /** \details
  Returns lineWeight mode
  */
  OdTvGsView::LineWeightMode getLineWeightMode(OdTvResult* rc = NULL) const;

  /** \details
    Set the lineWeight mode to this view object

    \param dScale [in]  Lineweight scale
  */
  OdTvResult setLineWeightScale(double dScale, bool bFromInterface = false);

  /** \details
  Returns lineWeight scale
  */
  double getLineWeightScale(OdTvResult* rc = NULL) const;

  /** \details
  Sets the lineweights for this Viewport object.

  \param numLineweights [in]  Number of Lineweights.
  \param lineweights [in]  Array of Lineweights.
 */
  OdTvResult setLineWeightEnum(int numLineweights, const OdUInt8* lineweights, bool bFromInterface = false);

  /** \details
    Regen the contents of view
  */
  OdTvResult regen();
  /** \details
  Enables default lighting for this view.

  \param bEnable [in]  New default lighting state.
  \param lightType [in]  New default lighting type.
  */
  OdTvResult enableDefaultLighting(bool bEnable, OdTvGsView::DefaultLightingType lightType = OdTvGsView::kTwoLights, bool bFromInterface = false);

  /** \details
  Returns true if default lighting is enabled
  */
  bool defaultLightingEnabled(OdTvResult* rc = NULL) const;

  /** \details
  Returns true if default lighting type
  */
  OdTvGsView::DefaultLightingType defaultLightingTypeWrap(OdTvResult* rc = NULL) const;

  /** \details
  Sets the ambient light color for the view.
  */
  OdTvResult setAmbientLightColorWrap(const OdTvColorDef& color);

  /** \details
  Returns the ambient light color for the view.
  */
  OdTvColorDef getAmbientLightColor(OdTvResult* rc = NULL) const;

  /** \details
  Returns the user defined default light direction
  */
  virtual OdTvVector userDefinedLightDirection(OdTvResult* rc = NULL) const;

  /** \details
  Sets the user defined default light direction
  */
  virtual OdTvResult setUserDefinedLightDirection(const OdTvVector& lightDirection);

  /** \details
  Returns the default light intensity
  */
  virtual double defaultLightingIntensity(OdTvResult* rc = NULL) const;

  /** \details
  Sets the default light intensity
  */
  virtual OdTvResult setDefaultLightingIntensity(double dIntensity);

  /** \details
  Returns the default light color
  */
  virtual OdTvColorDef defaultLightingColor(OdTvResult* rc = NULL) const;

  /** \details
  Sets the default light color
  */
  virtual OdTvResult setDefaultLightingColor(const OdTvColorDef& color);

  // re-implemented subSetAttributes
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;

  /** \details
  Set the true if and only if the view should be saved in the file
  */
  void setNeedSaveInFile(bool bNeed) { SETBIT(m_viewFlags, kNeedSaveInFile, bNeed); }

  /** \details
  Returns true if and only if the view should be saved in the file
  */
  bool getNeedSaveInFile() const { return GETBIT(m_viewFlags, kNeedSaveInFile); }

  /** \details
  Set the true if view must be is active
  */
  void setActive(bool bIsActive);

  /** \details
  Returns true if current view is active
  */
  bool getActive() const { return GETBIT(m_viewFlags, kIsActiveView) && m_bAdded; }

  /** \details
  Sets the color and width of the border for this View object.
  \param color [in]  Border color.
  \param width [in]  Border width in pixels.
  */
  OdTvResult setBorderProperties(ODCOLORREF color, OdUInt32 width);

  /** \details
  Returns the color and width of the border for this View object.
  \param color [out]  Receives the border color.
  \param width [out]  Receives the border width in pixels.
  */
  OdTvResult getBorderProperties(ODCOLORREF& color, OdUInt32& width) const;

  /** \details
  Controls the border visibility for this View object.
  \param visible [in]  Controls visibility.
  */
   OdTvResult setBorderVisibility(bool bVisible);

   /** \details
   Returns true if and  only if the border is visible for this View object.
   */
   bool getBorderVisibility(OdTvResult *rc = NULL) const;

   /** \details
   Defines a polygonal clip region.

   \param numCoutours  [in]  Number of polygonal contours.
   \param numVertices  [in]  Array of the number of vertices in each polygonal contour.
   \param vertices     [in]  Array of device coordinate (pixels) or world(eye) coordinates of the vertices defining the polygonal contours.
   \param bWCS         [in]  Indicate in what coordinates the vertices os present (device or world (eye))

   \remarks
   In the case of bWCS = true, the incoming WCS(ECS) contour's coordinates will be automatically multiplied on 'worldToDevice' matrix during each update
   */
   OdTvResult setClipRegion(OdUInt32 numContours, OdUInt32 const* numVertices, OdTvPoint2d const* vertices, bool bWCS = false);

   /** \details
   Returns a polygonal clip region.

   \param counts   [out]   Array of the number of vertices in each polygonal contour.
   \param vertices [out]   Array of device coordinate (pixel) or world(eye) coordinates of the vertices defining the polygonal contours.
   \param bWCS     [out]   True if and only if the coordinates are in world(eye) space
   */
   OdTvResult getClipRegion(OdUInt32Array& counts, OdTvPoint2dArray& vertices, bool& bWCS) const;

   /** \details
   Removes the polygonal clip region.
   */
   OdTvResult removeClipRegion();

   /** \details
   Deny rotation, pan and orbit if is true.
   \param b2dEnable [in]  Flag for 2d mode.
   */
   OdTvResult set2dMode(bool b2dEnable);

   /** \details
   Returns true if view is in 2d mode.
   */
   bool get2dMode() const;

   /** \details
   Returns true if view has WCS Clipping
   */
   bool hasWCSClipping() const;

   /** \details
   Update the clipping region
   */
   void updateClippingRegion();

   /** \details
   Controls the front clipping of this view and sets the front clip distance from the target of this view
   \param bEnable [in]    Enable front clipping.
   \param frontClip [in]  Front clip distance.
   */
   OdTvResult setFrontClip(bool bEnable, double frontClip = 1.0);

   /** \details
   Returns true if and only if front clipping is enabled for this view.
   Also returns the front clip distance from the target of this view.
   */
   bool getFrontClip(double& frontClip, OdTvResult *rc = NULL) const;

   /** \details
   Controls the back clipping of this view and sets the back clip distance from the target of this view
   \param bEnable [in]    Enable front clipping.
   \param frontClip [in]  Front clip distance.
   */
    OdTvResult setBackClip(bool bEnable, double backClip = 0.0);

   /** \details
   Returns true if and only if back clipping is enabled for this view.
   Also returns the back clip distance from the target of this view.
   */
   bool getBackClip(double& backClip, OdTvResult *rc = NULL) const;

   /** \details
   Set background to this view.
   \param backgroundId [in] View background id.
   */
   OdTvResult setBackgroundTv(const OdTvGsViewBackgroundId& backgroundId);

   /** \details
   Returns background of this view.
   */
   OdTvGsViewBackgroundId getBackgroundTv(OdTvResult *rc = NULL);

  /** \details
  Add cutting plane to the view.
  */
  OdTvResult  addCuttingPlane(const OdTvPlane& plane);

  /** \details
  Retrives the plane object associated with the given cutting plane
  */
  OdTvResult  getCuttingPlane(OdUInt32 idPlane, OdTvPlane& plane) const;

  /** \details
  Update the plane object associated with the given cutting plane
  */
  OdTvResult  updateCuttingPlane(OdUInt32 idPlane, const OdTvPlane& plane);

  /** \details
  Returns the number of cutting planes
  */
  OdUInt32    numCuttingPlanes(OdTvResult *rc = NULL) const;

  /** \details
  Remove the cutting plane with the given idPlane
  */
  OdTvResult  removeCuttingPlane(OdUInt32 idPlane);

  /** \details
  Remove all cutting planes
  */
  OdTvResult  removeCuttingPlanes();

  /** \details
  Set filling parameters of the cutting planes.
  */
  OdTvResult setEnableCuttingPlaneFill(bool bEnable, ODCOLORREF color);

  /** \details
  Returns the filling parameters of the cutting planes.
  */
  bool getCuttingPlaneFillEnabled(ODCOLORREF& color, OdTvResult *rc = NULL) const;

  /** \details
  Set filling pattern parameters of the cutting planes.
  */
  OdTvResult setCuttingPlaneFillPatternEnabled(bool bEnable, OdTvGsView::CuttingPlaneFillStyle fillStyle, ODCOLORREF color = ODRGB(255, 0, 0));

  /** \details
  Returns the filling pattern parameters of the cutting planes.
  */
  bool getCuttingPlaneFillPatternEnabled(OdTvGsView::CuttingPlaneFillStyle& fillStyle, ODCOLORREF& color, OdTvResult *rc = NULL) const;

  /** \details
  Retrieves the current raster image object of the view.
  */
  OdTvResult getSnapShot(const OdString& imagePath, const OdTvDCRect& region);

  /** \details
  Returns the current raster image object of the view.
  */
  OdGiRasterImagePtr getSnapShot(const OdTvDCRect& region, OdTvResult* rc = NULL);

  /** \details
  Allows to overrule the anti-aliasing behavior in current View.
  */
  OdTvResult setAntiAliasingOverrule(OdUInt32 overrule);

  /** \details
   Returns the overrule value for the anti-aliasing behavior in current View.
  */
  OdUInt32 getAntiAliasingOverrule(OdTvResult* rc = NULL) const;

  /** \details
   Set ambient occlusion flag in current view.
  */
  OdTvResult setSSAOEnabled(bool bEnable);

  /** \details
   Returns ambient occlusion flag in current view.
  */
  bool getSSAOEnabled(OdTvResult* rc = NULL) const;

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  //OdTvGsViewImpl own methods 
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Returns the models container
  */
  const OdTvEntityIdContainer* getModels() const;

  /** \details
  Reads the .dwg file data of this object.

  \param pFiler [in]  Filer object from which data are read.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  Writes the .dwg file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  re-implemented decomposeForSave
  */
  virtual OdTvDbObjectPtr decomposeForSave(OdDb::DwgVersion ver, OdTvDbObjectId& replaceId, bool& exchangeXData);

  /** \details
  Set the underlaying gs view
  */
  void setUnderlyingView(OdGsView* pView) { m_pView = pView; }

  /** \details
  Get the underlaying gs view
  */
  OdGsViewPtr getUnderlyingView() const
  {
    return m_pView;
  }

  /** \details
  Set parent db device object
  */
  void setDbDeviceObject(const OdTvDbObjectId& id) { m_dbDeviceId = id; }

  /** \details
  Get parent db device object
  */
  OdTvDbObjectId getDbDeviceObject() const { return m_dbDeviceId; }

  /** \details
  Set that the view was added to the device
  */
  void setAdded(bool bAdded = true) { m_bAdded = bAdded; }

  /** \details
  Get flag which indicates that the view was added to the device
  */
  bool getAdded() const
  {
    return m_bAdded;
  }

  // update views LwScale
  void updateViewsLwScale();

  /** \details
    Slot to receive the info from device about the database deleting
  */
  void goodbye();

  /** \details
  Add and setup underlaying gs view
  */
  OdTvResult setupGs();

  /** \details
  Remove underlaying gs view
  */
  OdTvResult unloadGs();

  /** \details
  Set that the view is internal
  */
  void setInternal(bool bInternal) { SETBIT(m_viewFlags, kInternal, bInternal); }

  /** \details
  Get flag which indicates that the view is internal
  */
  bool getInternal() const
  {
    return GETBIT(m_viewFlags, kInternal);
  }

  /** \details
  Add sibling view (the current view will copy own parameters to the added view)
  */
  OdTvResult addSibling(const OdTvGsViewId& id);

  /** \details
  Removes view from the sibling list
  */
  OdTvResult removeSibling(const OdTvGsViewId& id);

  /** \details
  Returns the view which controls the parameters of the current view
  */
  OdTvGsViewId getSiblingOwner(OdTvResult *rc = NULL) const;
  /** \details
  Retrives number of sibling views
  */
  OdUInt32 getNumSiblings( OdTvResult* rc = NULL ) const;
  /** \details
  Retrives sibling view with specified index
  */
  OdTvGsViewId getSibling( OdUInt32 index, OdTvResult* rc = NULL ) const;

  /** /details
  Add viewport object to the current view object (current view will control the screen rectangle of the added view)
  */
  OdTvResult addViewportObject(const OdTvGsViewId &id, const OdTvGsView::ViewportObjectInfo& viewportInfo);

  /** \details
  Returns the view which controls the parameters of the current viewport object
  */
  OdTvGsViewId getViewportObjectOwner(OdTvResult *rc = NULL) const;

  /** \details
  Update screen rect for all viewport objects
  */
  void updateAllViewportObjects();

  /** \details
  Set viewport object params
  */
  OdTvResult setViewportObjectParams(const OdTvGsView::ViewportObjectInfo& viewInfo);

  /** \details
  Get viewport object params
  */
  OdTvGsView::ViewportObjectInfo getViewportObjectParams(OdTvResult *rc = NULL) const;

  /** \details
  Returns the visual style of the current viewport object
  */
  OdTvVisualStyleId getVisualStyle(OdTvResult *rc = NULL) const;

  /** \details
  Hide layer in the current view
  */
  OdTvResult hideLayer(const OdTvLayerId& id);

  /** \details
  Unhide layer in the current view
  */
  OdTvResult unhideLayer(const OdTvLayerId& id);

  /** \details
  Unhide all layers at the the current view
  */
  OdTvResult unhideAllLayers();

  /** \details
  Returns true if layer is hidden in the current view
  */
  bool isLayerHidden(const OdTvLayerId& id, OdTvResult *rc = NULL);

  /** \details
  Returns layers which is hidden in the current view
  */
  virtual OdTvLayerIdsArray getHiddenLayers(OdTvResult *rc = NULL);

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;

  /** \details
 This method enables view interactivity mode. frameRateInHz specifies the desired frame rate (FPS).
 This value defines the desired minimum number of frames per second.
 In other words, if you want to limit the time that each redraw operation takes (e.g., “not more than X seconds”)
 frameRateInHz should be the inverse ratio of this time limit (1 / X).
 */
  OdTvResult beginInteractivity(double frameRateInHz);

  /** \details
  Returns true if this view is in interactivity mode.
  */
  bool isInInteractivity(OdTvResult *res = NULL) const;

  /** \details
  Returns the desired frame rate, which was specified in beginInteractivityMode().
  */
  double getInteractivityFrameRate(OdTvResult *res = NULL) const;

  /** \details
  This method disables view interactivity mode.
  */
  OdTvResult endInteractivity();

  /** \details
  This method returns the extents which was returned by the last call of the
  'viewExtents' method. If the was no call of 'viewExtents' method this method
  will return false.
  */
  bool getLastViewExtents(OdGeBoundBlock3d& extents) const;

  /** \details
  This method sets the Id of the view which was added for this view in the process of PE setupActiveLayoutView
  */
  void setPEId(OdInt32 id);

  /** \details
  This method returns the Id of the view which was added for this view in the process of PE setupActiveLayoutView
  */
  OdInt32 getPEId() const;

  /** \details
  Returns camera object assigned to this view
  */
  OdTvEntityId assignedCamera() const;
  /** \details
  Specifies camera object assigned to this view
  */
  void setAssignedCamera( OdTvEntityId );

  bool getAdjustLensLength() const { return GETBIT( m_viewFlags, kAdjustLensLength ); }
  void setAdjustLensLength( bool b ) { SETBIT( m_viewFlags, kAdjustLensLength, b ); }

  /** \details
  Checks whether underlying view properties were changed
  */
  bool isUnderlyingViewPropsValid() const;
private:
  /** \details
  Set sibling owner
  */
  void setSiblingOwner(const OdTvDbObjectId& id);

  /** \details
  Set viewport object owner
  */
  void setViewportObjectOwner(const OdTvDbObjectId& id);

  /** \details
  Retrieve the number of models that should be save in file
  */
  unsigned int getNumOfSavedModels() const;

  /** \details
  Update screen rect for the concreate viewport object
  */
  void updateViewportObject(OdTvGsViewImpl* pView, const OdTvGsView::ViewportObjectInfo& viewportInfo);

  /** \details
  Method for set db view from gs view
  */
  void setDbView();

  /** \details
  Check that 'block cache' option is switched on for the device
  */
  bool hasBlockCacheOption();

  /** \details
  Get OdHardwareSectionsInterface from gs view
  */
  OdHardwareSectionsInterface *hwSectionsIface(OdGsView *&pGsView) const;

  /** \details
  Collect gi path array. Thim method returns true, if selection set has geometries.
  */
  bool collectGiPath(OdArray< const OdGiPathNode* >& giPathArray, OdTvGiPathArray& tvGiPathArray, const OdTvSelectionSetPtr& pSSet, OdTvResult* rc = NULL) const;
private:

  OdGsViewPtr              m_pView;        // pointer to the wrapped gs view
  OdTvDbObjectId             m_dbDeviceId;   // Id of the parent DB device (tv layout) object (OdTvGsDeviceImpl)
  OdTvEntityIdContainer    m_models;       // container of the models, which are shown in this view
  bool                     m_bAdded;       // this flag indicated, that the view was added to the device

  //data for the lineWeight properties
  OdTvGsView::LineWeightMode  m_lwMode;
  double                      m_lwScale;
  OdUInt8Array                m_lweights;

  // relative boundaries of this view (usually between (0.0; 0.0) and (1.0; 1.0) BUT NOT NECESSARY)
  OdGePoint2d                 m_viewLowerLeft;
  OdGePoint2d                 m_viewUpperRight;

  //sibling information
  OdTvDbObjectId                m_siblingOwnerId;
  OdHardPtrIdArray            m_siblingList;

  //viewport information
  OdTvDbObjectId                              m_viewportOwnerId;
  OdTvGsView::ViewportObjectInfo            m_viewportObjectParam;
  OdHardPtrIdArray                          m_viewportList;

  //border functionality
  ODCOLORREF                  m_bordersColor;
  OdUInt32                    m_bordersWidth;

  //clipping contours
  OdIntArray                  m_nrcCounts;
  OdGePoint2dArray            m_nrcPoints;

  OdUInt16                    m_viewFlags;

  OdHardPtrIdArray            m_hiddenLayers;

  double                      m_frontClipDist;
  double                      m_backClipDist;

  //default lighting
  OdTvVector                  m_defLightDirection;
  double                      m_defLightInt;
  OdTvColorDef                m_defLightColor;
  bool                        m_bUserDefinedDefLight;

  // real time data (not saved in file). Extents which was returned via last call 'viewExtents' (in WCS)
  OdGeBoundBlock3d               m_cachedExt;
  bool                           m_bCachedExtValid;
  
  // real time data (not saved in file). Extents which was set when there is no Gs View (see flag 'kNeedPerformZoomToExtents')
  OdGeExtents3d                  m_cachedZoomExt;

  // Cutting planes
  OdTvCuttingPlaneArray         m_cuttingPlanes;

  //Anti-aliasing overrule
  OdUInt32                  m_AAOverrule;

  //not for write
  OdInt32                      m_PEId;     // Id of the view which was added for this view in the process of PE setupActiveLayoutView

  //Camera
  OdTvEntityId m_assignedCamera;
};
typedef OdSmartPtr<OdTvGsViewImpl> OdTvGsViewImplPtr;


/** \details
    This is a wrapper of the interface class for OdTvGsView object.

    \remarks
    The purpose of this class is to connect the internal view object with an interface object
*/
  
class OdTvGsViewWrapper : public OdTvGsView
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvGsView, OdTvGsViewImpl)

  friend class OdGsDeviceForTvImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
    Returns the TvGsDevice object associated with this View object.
  */
  virtual OdTvGsDeviceId device(OdTvResult* rc = NULL) const;

  /** \details
    Sets the size and position of this Viewport object.
    \param lowerLeft [in]  Lower-left corner in nomalized device coordinates [0.0 .. 1.0].
    \param upperRight [in]  Upper-right corner in nomalized device coordinates [0.0 .. 1.0].
    \param screenRect [in]  Screen rectangle in device coordinates (pixels).
    
    \remarks
    (0,0) is the lower-left corner of the owning Device object. Coordinates increase upward and to the right.
    
    \remarks
    The View object can be partly or comp letely off screen.    
  */
  virtual OdTvResult setViewport(const OdGePoint2d& lowerLeft, const OdGePoint2d& upperRight);
  virtual OdTvResult setViewport(const OdTvDCRect& screenRect);

  /** \details
    Returns the size and position of this Viewport object.
    \param lowerLeft [out]  Receives the lower-left corner in nomalized device coordinates [0.0 .. 1.0].
    \param upperRight [out]  Receives the upper-right corner in nomalized device coordinates [0.0 .. 1.0].
    \param screenRect [out]  Receives the screen rectangle in device coordinates (pixels).
    
    \remarks
    (0,0) is the lower-left corner of the owning Device object.  Coordinates increase upward and to the right.
    
    \remarks
    The View object may be partly or completely off screen.    
  */
  virtual OdTvResult getViewport(OdGePoint2d& lowerLeft, OdGePoint2d& upperRight) const;
  virtual OdTvResult getViewport(OdTvDCRect& screenRect) const;

  /** \details
    Sets the camera parameters for this View object.
    
    \param position [in]  Camera position.
    \param target [in]  Camera target.
    \param upVector [in]  Camera up vector.
    \param fieldWidth [in]  Projection plane (field) width.
    \param fieldHeight [in]  Projection plane (field) height.
    \param projectionType [in]  Projection type.
    
    \remarks
    All parameters are in WCS coordinates.

    projectionType must be one of the following:
    
    <table>
    Name           Value
    kParallel      0
    kPerspective   1
    </table>
    
    \remarks
    This method defines the transfomation from WCS coordinates to normalized device coordinates.
  */
  virtual OdTvResult setView(
    const OdTvPoint& position,
    const OdTvPoint& target,
    const OdTvVector& upVector,
    double fieldWidth,
    double fieldHeight,
    Projection projectionType = kParallel);

  /** \details
    Returns the WCS camera position for this View object.
  */
  virtual OdTvPoint position(OdTvResult* rc = NULL) const;

  /** \details
    Returns the WCS camera target for this View object.
  */
  virtual OdTvPoint target(OdTvResult* rc = NULL) const;

  /** \details
    Returns the WCS camera up vector for this View object.
  */
  virtual OdTvVector upVector(OdTvResult* rc = NULL) const;

 /** \details
    Returns the perspective lens length for this View object.
  */
  virtual double lensLength(OdTvResult* rc = NULL) const;

  /** \details
    Sets the perspective lens length for this View object.
    \param lensLength [in]  Perspective lens length.
  */
  virtual OdTvResult setLensLength(double lensLength);

  /** \details
    Returns true if and only if the projection type for this View object is kPerspective. 
  */
  virtual bool isPerspective(OdTvResult* rc = NULL) const;

  /** \details
    Returns the WCS projection plane (field) width for this View object.
  */
  virtual double fieldWidth(OdTvResult* rc = NULL) const;

  /** \details
    Returns the WCS projection plane (field) height for this View object.
  */
  virtual double fieldHeight(OdTvResult* rc = NULL) const;

  /** \details
  Retrives focal length of this View object.
  \param rc [out] [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns focal length of this View object.
  \remarks This method has no sense for the parallel camera. In this case return value will be 0 and rc value will be tvWarning.
  */
  double focalLength( OdTvResult* rc = NULL ) const;

  /** \details
    Returns the eye coordinate system extents of this view object.
    
    \param extents [out]  Receives the extents.

    \returns
    Returns true if and only if the extents are defined and view of the device has an appropriate method
  */
  virtual bool viewExtents(OdGeBoundBlock3d& extents, OdTvResult* rc = NULL) const;

  /** \details
      Returns the matrix that transforms world space to view space for this View object.
  */
  virtual OdGeMatrix3d viewingMatrix(OdTvResult* rc = NULL) const;

  /** \details
      Returns the matrix that transforms view space to normalized device space for this View object.

      \sa
      Coordinate Systems.
  */
  virtual OdGeMatrix3d projectionMatrix(OdTvResult* rc = NULL) const;

  /** \details
      Returns the matrix that transforms normalized device space to screen space for this View object.

      \sa
      Coordinate Systems.
  */
  virtual OdGeMatrix3d screenMatrix(OdTvResult* rc = NULL) const;

  /** \details
      Returns a matrix that transforms coordinates from world space to screen space for this View object. 
      
      \remarks
      This is equivalent to the concatenation of the viewingMatrix, 
      projectionMatrix, and screenMatrix.

      \sa
      Coordinate Systems.
  */
  virtual OdGeMatrix3d worldToDeviceMatrix(OdTvResult* rc = NULL) const;

  /** \details
      Returns the matrix that transforms view space to the world space for this View object.
  */
  virtual OdGeMatrix3d eyeToWorldMatrix(OdTvResult* rc = NULL) const;

  /** \details
      Returns lower left and upper right corners of the view object in device coordinates
  */
  virtual OdTvResult viewDcCorners(OdGePoint2d& lower_left, OdGePoint2d& upper_right) const;

  /** \details
    Sets the render mode for this Viewport object.
    
    \param mode [in]  Render mode.
    
    \remarks
    mode must be one of the following:
    
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
  */
  virtual OdTvResult setMode(RenderMode mode);

  /** \details
    Sets the render mode for this Viewport object.
    
    \remarks
    mode must be one of the following:
    
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
  */
  virtual RenderMode mode(OdTvResult* rc = NULL) const;

  /** \details
    Adds the specified scene graph to this Viewport object.
    
    \param sceneModel [in]  Id of the model object.
  */
  virtual bool addModel(const OdTvModelId& sceneModelId, OdTvResult* rc = NULL);

  /** \details
    Removes the specified scene model from this View object.
    
    \param sceneModel [in]  Id of the model object.
  */
  virtual bool eraseModel(const OdTvModelId& sceneModelId, OdTvResult* rc = NULL);

  /** \details
    Removes all scene models from this View object.
  */
  virtual OdTvResult eraseAllModels();

  /** \details
  Returns the number of models associated with this View object.
  */
  virtual int numModels(OdTvResult* rc = NULL) const;

  /** \details
  Returns the specified OdTvModel object associated with this View object.
  \param modelIndex [in]  View index.
  */
  virtual OdTvModelId  modelAt(int modelIndex, OdTvResult* rc = NULL);

  /** \details
    Translates the camera position and target by the specified Camera Coordinate dolly amount.
     
    \param dollyVector [in]  Camera Coordinate dolly vector.
    \param xDolly [in]  Camera Coordinate X dolly amount.
    \param yDolly [in]  Camera Coordinate Y dolly amount.
    \param zDolly [in]  Camera Coordinate Z dolly amount.
     
    \remarks
    Camera Coordinates are relative to the view of a target from a camera. 
    
    * The Y-axis is along up vector. 
    * The Z-axis is along the vector from camera position to the target. 
    * The X-axis is the cross product Y-axis x Z-axis 
  */
  virtual OdTvResult dolly(const OdTvVector& dollyVector);
  virtual OdTvResult dolly(double xDolly, double yDolly, double zDolly);

  /** \details
    Rotates the camera by the specified amount about the eye vector.
     
    \param rollAngle [in]  Camera CCW roll angle.
     
    \remarks
    Positive angles rotate the camera counterclockwise about the eye vector
    when viewed from the camera position to the target. This corresponds
    to a clockwise rotation of the up vector.
    
    \remarks
    Camera Coordinates are relative to the view of a target from a camera. 
    
    * The Y-axis is along up-vector. 
    * The Z-axis (eye vector) is along the vector from camera position to the target. 
    * The X-axis is the cross product Y-axis x Z-axis.
    
    All angles are expressed in radians.
  */
    virtual OdTvResult roll(double rollAngle);

  /** \details
    Orbits the camera about the target by the specified amounts.
     
    \param xOrbit [in]  X-axis Orbit.
    \param yOrbit [in]  Y-axis Orbit.
     
    \remarks
    The camera moves on the surface a sphere whose center the camera target and whose
    radius is the distance from the camera position to its target 
    
    * The camera is first rotated about an axis parallel to the X-axis and passing through the target.  
    * The camera is next rotated about an axis parallel to the Y-axis and passing through the target  
    
    \remarks
    Camera Coordinates are relative to the view of a target from a camera. 
    
    * The Y-axis is along up vector. 
    * The Z-axis is along the vector from camera position to the target. 
    * The X-axis is the cross product Y-axis X Z-axis 

    All angles are expressed in radians.
  */
    virtual OdTvResult orbit(double xOrbit, double yOrbit);

  /** \details
    Scales the focal length of the camera by the specified amount.
     
    \param zoomFactor [in]  Zoom factor.
     
  */
  virtual OdTvResult zoom(double zoomFactor);

  /** \details
    Rotates the target about the camera the specified amounts.

    \param xPan [in]  X-axis pan.
    \param yPan [in]  Y-axis pan.

    \remarks
    The target moves on the surface a sphere whose center the camera position and whose
    radius is the distance from the camera position to its target

    * The target is first rotated about an axis parallel to the X-axis and passing through the camera.
    * The target is next rotated about an axis parallel to the Y-axis and passing through the camera.

    \remarks
    Camera Coordinates are relative to the view of a target from a camera.

    * The Y-axis is along up vector.
    * The Z-axis is along the vector from camera position to the target.
    * The X-axis is the cross product Y-axis, Z-axis
    All angles are expressed in radians.
  */
  virtual OdTvResult pan(double xPan, double yPan);

  /** \details
    Scales the camera to completely include specified WCS box inside view frustum.

    \param minPt            [in]  minimal WCS box point.
    \param maxPt            [in]  maximal WCS box point.
    \param bCacheIfNonSetup [in]  Indicates, that it is need to cache the input extent's parameters if the view is still "non-setup."
  */
  virtual OdTvResult zoomExtents(const OdTvPoint &minPt, const OdTvPoint &maxPt, bool bCacheIfNonSetup = false);

  /** \details
    Scales the camera to completely include specified screen area.

    \param lowerLeft [in]  Lower-left corner in nomalized device coordinates [0.0 .. 1.0].
    \param upperRight [in]  Upper-right corner in nomalized device coordinates [0.0 .. 1.0].
  */
  virtual OdTvResult zoomWindow(const OdGePoint2d &lowerLeft, const OdGePoint2d &upperRight);

  /** \details
  Runs selection procedure inside this View object.

  \param pts [in]  Selection points in device coordinate space (pixels).
  \param nPoints [in]  Count of selection points.
  \param options [in]  Selection options like mode, level, pick box size.
  \param modelId [in]  Model in which we will find the objects.
  */
  virtual OdTvSelectionSetPtr select(const OdTvDCPoint* pts, int nPoints, const OdTvSelectionOptions& options, const OdTvModelId& modelId, OdTvResult* rc = NULL);

  /** \details
  Runs the collision detection 'all with all' procedure inside the view object.
  \param modelId           [in]  Model which contains objects to check.
  \param collidedWho       [out] A smart pointer to the set of objects who collided (first object in the collided pair).
  \param collidedWithWhom  [out] A smart pointer to the set of objects with whom collided (second object in the collided pair).
  \param level             [in]  The selection level.
  */
  virtual OdTvResult collide(const OdTvModelId& modelId, OdTvCollidedResultPtr& collidedWho, OdTvCollidedResultPtr& collidedWithWhom,
                             OdTvSelectionOptions::Level level = OdTvSelectionOptions::kEntity, bool bIntersectionOnly = true, double tolerance = 1e-10 );

  /** \details
  Runs the collision detection 'a few with all' procedure inside the view object.
  \param inputSet           [in] A smart pointer to the set of objects to check.
  \param modelId            [in] Model which contains objects to be checked with.
  \param collidedFromInput  [out] A smart pointer to the set of objects which are collided (first object in the collided pair). Can be NULL.
  \param level              [in] The selection level.
  \param rc                 [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvCollidedResultPtr collide(const OdTvSelectionSetPtr& inputSet, const OdTvModelId& modelId, OdTvCollidedResultPtr& collidedFromInput,
                                      OdTvSelectionOptions::Level level = OdTvSelectionOptions::kEntity, bool bIntersectionOnly = true, double tolerance = 1e-10, OdTvResult* rc = NULL);

  /** \details
  Runs the collision detection 'a few with a few' procedure inside the view object.
  \param inputSet           [in]  A smart pointer to the set of objects to check.
  \param collisionWithSet   [in]  A smart pointer to the set of possible colliding objects.
  \param collidedFromInput  [out] A smart pointer to the set of objects which are collided (first object in the collided pair). Can be NULL.
  \param level              [in] The selection level.
  \param rc                 [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvCollidedResultPtr collide(const OdTvSelectionSetPtr& inputSet, const OdTvSelectionSetPtr& collisionWithSet, OdTvCollidedResultPtr& collidedFromInput,
                                      OdTvSelectionOptions::Level level = OdTvSelectionOptions::kEntity, bool bIntersectionOnly = true, double tolerance = 1e-10, OdTvResult* rc = NULL);
  //all with all
  virtual OdTvResult collide( const OdTvModelId& modelId, OdTvCollidedPairResult& result, const OdTvCollisionOptions& options = OdTvCollisionOptions() );
  //list with list
  virtual OdTvResult collide( const OdTvSelectionSetPtr& inputSet, const OdTvSelectionSetPtr& collisionWithSet, OdTvCollidedPairResult& result, const OdTvCollisionOptions& options = OdTvCollisionOptions() );
  //list with model
  virtual OdTvResult collide( const OdTvSelectionSetPtr& inputSet, const OdTvModelId& modelId, OdTvCollidedPairResult& result, const OdTvCollisionOptions& options = OdTvCollisionOptions() );

  /** \details
  Perform highlight of the given apth

  \param id               [in]    The id of the entity which shoudl be highlighted (or which subitem should be highlighted)
  \param path             [in]  The path to the subitem which should be highlighted (it could be subentity, geometry or subgeometry (face or edge))
  \param bDoIt            [in] Flag that indicates whether highlighting is enabled (true value) or disabled (false value).
  \param highLightStyleId  [in] A value that determines index of highlight style. This value need for multiple highlighting of objects.
  */
  virtual OdTvResult highlight(const OdTvEntityId& id, const OdTvSubItemPath& path, bool bDoIt = true, OdUInt16 highLightStyleId = 0);

  /** \details
  Returns true if and only if specified point is visible inside current view frustum.

  \param pt [in]  WCS point for check.
  */
  virtual bool isPointVisibleInView(const OdTvPoint &pt, OdTvResult* rc = NULL) const;

  /** \details
  Checks does specified point is inside viewport area.

  \param screenPoint [in]  Check point in device coordinate space.
  */
  virtual bool pointInView(const OdTvPoint2d& screenPoint, OdTvResult* rc = NULL) const;

  /** \details
  Returns the display pixel density at the specified point for this view object.

  \param point [in]  WCS center of the unit square.
  \param pixelDensity [out]  Receives the pixel density.
  \param bUsePerspective [in]  Enable perspective inclusion into pixel density calculation.
  */
  virtual OdTvResult getNumPixelsInUnitSquare(const OdTvPoint& point, OdTvPoint2d& pixelDensity, bool bUsePerspective = true) const;

  /** \details
    Set the lineWeight mode to this view object

    \param lwMode [in]  LineWeight mode.
  */
  virtual OdTvResult setLineWeightMode(LineWeightMode lwMode);

  /** \details
  Returns lineWeight mode
  */
  virtual LineWeightMode getLineWeightMode(OdTvResult* rc = NULL) const;

  /** \details
    Set the lineWeight mode to this view object

    \param dScale [in]  Lineweight scale
  */
  virtual OdTvResult setLineWeightScale(double dScale);

  /** \details
  Returns lineWeight scale
  */
  virtual double getLineWeightScale(OdTvResult* rc = NULL) const;

  /** \details
   Sets the lineweights for this Viewport object.

   \param numLineweights [in]  Number of Lineweights.
   \param lineweights [in]  Array of Lineweights.
 */
  virtual OdTvResult setLineWeightEnum(int numLineweights, const OdUInt8* lineweights);

  /** \details
    Regen the contents of view
  */
  virtual OdTvResult regen();

  /** \details
  Enables default lighting for this view.

  \param bEnable [in]  New default lighting state.
  \param lightType [in]  New default lighting type.
  */
  virtual OdTvResult enableDefaultLighting(bool bEnable, DefaultLightingType lightType = kTwoLights);

  /** \details
  Returns true if default lighting is enabled
  */
  virtual bool defaultLightingEnabled(OdTvResult* rc = NULL) const;

  /** \details
  Returns true if default lighting type
  */
  virtual DefaultLightingType defaultLightingType(OdTvResult* rc = NULL) const;

  /** \details
  Sets the ambient light color for the view.
  */
  virtual OdTvResult setAmbientLightColor(const OdTvColorDef& color);

  /** \details
  Returns the ambient light color for the view.
  */
  virtual OdTvColorDef getAmbientLightColor(OdTvResult* rc = NULL) const;

  /** \details
  Returns the user defined default light direction
  */
  virtual OdTvVector userDefinedLightDirection(OdTvResult* rc = NULL) const;

  /** \details
  Sets the user defined default light direction
  */
  virtual OdTvResult setUserDefinedLightDirection(const OdTvVector& lightDirection);

  /** \details
  Returns the default light intensity
  */
  virtual double defaultLightingIntensity(OdTvResult* rc = NULL) const;

  /** \details
  Sets the default light intensity
  */
  virtual OdTvResult setDefaultLightingIntensity(double dIntensity);

  /** \details
  Returns the default light color
  */
  virtual OdTvColorDef defaultLightingColor(OdTvResult* rc = NULL) const;

  /** \details
  Sets the default light color
  */
  virtual OdTvResult setDefaultLightingColor(const OdTvColorDef& color);

  /** \details
  Returns true if and only if the view should be saved in the file
  */
  virtual bool getNeedSaveInFile(OdTvResult* rc = NULL) const;

  /** \details
  Set the true if view must be is active
  */
  virtual OdTvResult setActive(bool bIsActive);

  /** \details
  Returns true if current view is active
  */
  virtual bool getActive(OdTvResult* rc = NULL) const;

  /** \details
  Sets the color and width of the border for this View object.
  \param color [in]  Border color.
  \param width [in]  Border width in pixels.
  */
  virtual OdTvResult setBorderProperties(ODCOLORREF color, OdUInt32 width);

  /** \details
  Returns the color and width of the border for this View object.
  \param color [out]  Receives the border color.
  \param width [out]  Receives the border width in pixels.
  */
  virtual OdTvResult getBorderProperties(ODCOLORREF& color, OdUInt32& width) const;

  /** \details
  Controls the border visibility for this View object.
  \param visible [in]  Controls visibility.
  */
  virtual OdTvResult setBorderVisibility(bool bVisible);

  /** \details
  Returns true if and  only if the border is visible for this View object.
  */
  virtual bool getBorderVisibility(OdTvResult *rc = NULL) const;

  /** \details
  Defines a polygonal clip region.

  \param numCoutours  [in]  Number of polygonal contours.
  \param numVertices  [in]  Array of the number of vertices in each polygonal contour.
  \param vertices     [in]  Array of device coordinate (pixels) or world(eye) coordinates of the vertices defining the polygonal contours.
  \param bWCS         [in]  Indicate in what coordinates the vertices os present (device or world (eye))

  \remarks
  In the case of bWCS = true, the incoming WCS(ECS) contour's coordinates will be automatically multiplied on 'worldToDevice' matrix during each update
  */
  virtual OdTvResult setClipRegion(OdUInt32 numContours, OdUInt32 const* numVertices, OdTvPoint2d const* vertices, bool bWCS = false);

  /** \details
  Returns a polygonal clip region.

  \param counts   [out]   Array of the number of vertices in each polygonal contour.
  \param vertices [out]   Array of device coordinate (pixel) or world(eye) coordinates of the vertices defining the polygonal contours.
  \param bWCS     [out]   True if and only if the coordinates are in world(eye) space
  */
  virtual OdTvResult getClipRegion(OdUInt32Array& counts, OdTvPoint2dArray& vertices, bool& bWCS) const;

  /** \details
  Removes the polygonal clip region.
  */
  virtual OdTvResult removeClipRegion();

  /** \details
  Sets the name for the view.

  \param sName [in]  Layer name as a String value up to 255 characters long.

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdTvResult setName(const OdString& name);

  /** \details
  Returns the name for this view object
  */
  virtual OdString getName(OdTvResult* rc = NULL) const;

  /** \details
  Add sibling view (the current view will copy own parameters to the added view)
  */
  virtual OdTvResult addSibling(const OdTvGsViewId& id);

  /** \details
  Removes view from the sibling list
  */
  virtual OdTvResult removeSibling(const OdTvGsViewId& id);

  /** \details
  Returns the view which controls the parameters of the current view
  */
  virtual OdTvGsViewId getSiblingOwner(OdTvResult *rc = NULL) const;

  /** /details
  Add viewport object to the current view object (current view will control the screen rectangle of the added view)
  */
  virtual OdTvResult addViewportObject(const OdTvGsViewId &id, const ViewportObjectInfo& viewportInfo);

  /** \details
  Returns the view which controls the parameters of the current viewport object
  */
  virtual OdTvGsViewId getViewportObjectOwner(OdTvResult *rc = NULL) const;

  /** \details
  Deny rotation, pan and orbit if is true.
  */
  virtual OdTvResult set2dMode(bool b2dEnable);

  /** \details
  Returns true if view is in 2d mode.
  */
  virtual bool get2dMode(OdTvResult *rc = NULL) const;

  /** \details
  Set visual style to the current view
  */
  virtual OdTvResult setVisualStyle(const OdTvVisualStyleId& id);

  /** \details
  Returns the visual style of the current viewport object
  */
  virtual OdTvVisualStyleId getVisualStyle(OdTvResult *rc = NULL) const;

  /** \details
  Hide layer in the current view
  */
  virtual OdTvResult hideLayer(const OdTvLayerId& id);

  /** \details
  Unhide layer in the current view
  */
  virtual OdTvResult unhideLayer(const OdTvLayerId& id);

  /** \details
  Unhide all layers at the the current view
  */
  virtual OdTvResult unhideAllLayers();

  /** \details
  Returns true if layer is hidden in the current view
  */
  virtual bool isLayerHidden(const OdTvLayerId& id, OdTvResult *rc = NULL);

  /** \details
  Returns layers which is hidden in the current view
  */
  virtual OdTvLayerIdsArray getHiddenLayers(OdTvResult *rc = NULL);

  /** \details
  Controls the front clipping of this view and sets the front clip distance from the target of this view
  \param bEnable [in]    Enable front clipping.
  \param frontClip [in]  Front clip distance.
  */
  virtual OdTvResult setFrontClip(bool bEnable, double frontClip = 1.0);

  /** \details
  Returns true if and only if front clipping is enabled for this view.
  Also returns the front clip distance from the target of this view.
  */
  virtual bool getFrontClip(double& frontClip, OdTvResult *rc = NULL) const;

  /** \details
  Controls the back clipping of this view and sets the back clip distance from the target of this view
  \param bEnable [in]    Enable front clipping.
  \param frontClip [in]  Front clip distance.
  */
  virtual OdTvResult setBackClip(bool bEnable, double backClip = 0.0);

  /** \details
  Returns true if and only if back clipping is enabled for this view.
  Also returns the back clip distance from the target of this view.
  */
  virtual bool getBackClip(double& backClip, OdTvResult *rc = NULL) const;

  /** \details
  Set background to this view.
  \param backgroundId [in] View background id.
  */
  virtual OdTvResult setBackground(const OdTvGsViewBackgroundId& backgroundId);

  /** \details
  Returns background of this view.
  */
  virtual OdTvGsViewBackgroundId getBackground(OdTvResult *rc = NULL);

  /** \details
  This method enables view interactivity mode. frameRateInHz specifies the desired frame rate (FPS).
  This value defines the desired minimum number of frames per second.
  In other words, if you want to limit the time that each redraw operation takes (e.g., “not more than X seconds”)
  frameRateInHz should be the inverse ratio of this time limit (1 / X).
  */
  virtual OdTvResult beginInteractivity(double frameRateInHz);

  /** \details
  Returns true if this view is in interactivity mode.
  */
  virtual bool isInInteractivity(OdTvResult *rc = NULL) const;

  /** \details
  Returns the desired frame rate, which was specified in beginInteractivityMode().
  */
  virtual double getInteractivityFrameRate(OdTvResult *rc = NULL) const;

  /** \details
  This method disables view interactivity mode.
  */
  virtual OdTvResult endInteractivity();

  /** \details
  This method returns the extents which was returned by the last call of the
  'viewExtents' method. If the was no call of 'viewExtents' method this method
  will return false
  */
  virtual bool getLastViewExtents(OdGeBoundBlock3d& extents, OdTvResult *rc = NULL) const;

  /** \details
  Add cutting plane to the view.
  */
  virtual OdTvResult  addCuttingPlane(const OdTvPlane& plane);

  /** \details
  Retrives the plane object associated with the given cutting plane
  */
  virtual OdTvResult  getCuttingPlane(OdUInt32 idPlane, OdTvPlane& plane) const;

  /** \details
  Update the plane object associated with the given cutting plane
  */
  virtual OdTvResult  updateCuttingPlane(OdUInt32 idPlane, const OdTvPlane& plane);

  /** \details
  Returns the number of cutting planes
  */
  virtual OdUInt32    numCuttingPlanes(OdTvResult *rc = NULL) const;

  /** \details
  Remove the cutting plane with the given idPlane
  */
  virtual OdTvResult  removeCuttingPlane(OdUInt32 idPlane);

  /** \details
  Remove all cutting planes
  */
  virtual OdTvResult  removeCuttingPlanes();

  /** \details
  Set filling parameters of the cutting planes.
  */
  virtual OdTvResult setEnableCuttingPlaneFill(bool bEnable, ODCOLORREF color = ODRGBA(255, 0, 0, 255));

  /** \details
  Returns the filling parameters of the cutting planes.
  */
  virtual bool getCuttingPlaneFillEnabled(ODCOLORREF& color, OdTvResult *rc = NULL) const;

  /** \details
  Set filling pattern parameters of the cutting planes.
  */
  virtual OdTvResult setCuttingPlaneFillPatternEnabled(bool bEnable, OdTvGsView::CuttingPlaneFillStyle fillStyle, ODCOLORREF color = ODRGB(255, 0, 0));

  /** \details
  Returns the filling pattern parameters of the cutting planes.
  */
  virtual bool getCuttingPlaneFillPatternEnabled(OdTvGsView::CuttingPlaneFillStyle& fillStyle, ODCOLORREF& color, OdTvResult *rc = NULL) const;

  /** \details
  Returns image of current view by specified path.
  */
  virtual OdTvResult getSnapShot(const OdString& imagePath, const OdTvDCRect& region);

  /** \details
  Returns the current raster image object of the view.
  */
  virtual OdGiRasterImagePtr getSnapShot(const OdTvDCRect& region, OdTvResult* rc = NULL);

  /** \details
  Allows to overrule the anti-aliasing behavior in current View.
  */
  virtual OdTvResult setAntiAliasingOverrule(OdUInt32 overrule);

  /** \details
   Returns the overrule value for the anti-aliasing behavior in current View.
  */
  virtual OdUInt32 getAntiAliasingOverrule(OdTvResult* rc = NULL) const;

  /** \details
   Set ambient occlusion flag in current view.
  */
  OdTvResult setSSAOEnabled(bool bEnable);

  /** \details
   Returns ambient occlusion flag in current view.
  */
  bool getSSAOEnabled(OdTvResult* rc = NULL) const;

  /** \details
  Returns the camera object that assigned to this view or empty Id.
  */
  virtual OdTvEntityId assignedCamera( OdTvResult* rc = NULL ) const;

  virtual bool getAdjustLensLength( OdTvResult* rc = NULL ) const;
  virtual OdTvResult setAdjustLensLength( bool b );

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);
};

enum OdTvCollisionType
{
  kAllWithAll = 0,
  kAFewWithAll = 1,
  kAFewWithAFew = 2
};

class OdTvCollisionDetectionReactor : public OdGsCollisionDetectionReactor
{
public:
  OdTvCollisionDetectionReactor(OdTvSelectionSetImpl* pSelectionSetImpl, OdTvSelectionSetImpl* pSelectionSetImplWithWhom, OdTvCollisionType type, bool bNeedFilter, bool bNestedPossible, const OdTvDbObjectId& dbModelId);
  virtual ~OdTvCollisionDetectionReactor() {};
  virtual OdUInt32 collisionDetected(const OdGiPathNode* pPathNode1, const OdGiPathNode* pPathNode2);
public:

private:

  OdTvSelectionSetImpl* m_pSelectionSetImpl;
  OdTvSelectionSetImpl* m_pSelectionSetImplWithWhom;
  OdTvDbObjectId          m_dbModelId;
  bool                  m_bNeedFilter;
  bool                  m_bNestedPossible;
  OdTvCollisionType     m_type;

  OdDbStub* m_pLastPathNode1PersistentDrawableId;
  OdDbStub* m_pLastPathNode2PersistentDrawableId;
};

class OdTvCollisionPairDetectionReactor : public OdGsCollisionDetectionReactor
{
public:
  OdTvCollisionPairDetectionReactor( OdTvCollidedPairResult* pResult );
  virtual OdUInt32 collisionDetected( const OdGiPathNode* pPathNode1, const OdGiPathNode* pPathNode2 );
  virtual OdUInt32 collisionDetected( const OdGiPathNode* pPathNode1, const OdGiPathNode* pPathNode2, double dist );
  void setOptions( const OdTvCollisionOptions& opt ) { m_options = opt; }
protected:
  OdTvCollidedPairResult* m_pResult;
  OdTvCollisionOptions m_options;

  OdDbStub* m_pLastPathNode1PersistentDrawableId;
  OdDbStub* m_pLastPathNode2PersistentDrawableId;

 bool buildPath( const OdGiPathNode* pPathNode, OdTvSubItemPath& path, bool& bShouldImmediatelyReturn );
};

class OdTvCollisionPair : public OdTvSelectionSetImpl
{
public:
  OdTvCollisionPair(OdTvSelectionOptions::Level level);
  OdTvCollisionPair(const OdTvCollisionPair& pair);

  // Methods for implementation
  virtual OdTvResult appendEntity(const OdTvEntityId& id);
  virtual OdTvResult appendSubEntity(const OdTvEntityId& id, const OdTvSubItemPath& subItemPath);
  virtual void appendEntity(OdDbStub* entityId);
  virtual void appendSubEntity(OdDbStub* entityId, const OdTvSubItemPath& subItemPath);

  // Methods for supporting
  virtual OdTvSelectionSetIteratorPtr getIterator(OdTvResult* rc = NULL) const { return OdTvSelectionSetIteratorPtr(); };
  virtual OdUInt32 numItems(OdTvResult* rc = NULL) const { return 0; };
  virtual OdTvSelectionOptions getOptions(OdTvResult* rc = NULL) const { return OdTvSelectionOptions(); };
  virtual OdTvResult removeEntity(const OdTvEntityId& id) { return tvOk; };
  virtual OdTvResult removeSubEntity(const OdTvEntityId& id, const OdTvSubItemPath& subItemPath) { return tvOk; };
  virtual bool isMember(const OdTvEntityId& id, OdTvResult* rc = NULL) const { return false; };
  virtual bool isMember(const OdTvGeometryDataId& id, OdTvResult* rc = NULL) const { return false; };
  virtual OdUInt8Array isMember(const OdTvGeometryDataId& id, const OdUInt32Array& indexes, OdTv::SubGeometryType type = OdTv::kFaceSubGeometryType, OdTvResult* rc = NULL) const { return OdUInt8Array(); };
  virtual OdTvResult clear() { return tvOk; };
  virtual void removeEntity(OdDbStub* entityId) {};
  virtual void removeSubEntity(OdDbStub* entityId, const OdTvSubItemPath& subItemPath) {};

  // Own methods
  OdTvResult getASubEntity(OdTvEntityId& id, OdTvSubItemPath& subItemPath) const;
  OdTvResult getBSubEntity(OdTvEntityId& id, OdTvSubItemPath& subItemPath) const;
  virtual bool operator < (const OdTvCollisionPair& pair) const;
  virtual bool operator == (const OdTvCollisionPair& pair) const;

protected:
  bool needSwapSides() const;
  void swapSides();

  bool entitiesArraysAreEqual(const OdTvEntityIdsArray& entities, const OdTvEntityIdsArray& pairEntities) const;
  bool entitiesArraysAreLess(const OdTvEntityIdsArray& entities, const OdTvEntityIdsArray& pairEntities, bool& bEqual) const;
  bool geometriesArraysAreEqual(const OdTvGeometryDataIdsArray& geometries, const OdTvGeometryDataIdsArray& pairGeometries) const;
  bool geometriesArraysAreLess(const OdTvGeometryDataIdsArray& geometries, const OdTvGeometryDataIdsArray& pairGeometries, bool& bEqual) const;

protected:
  OdTvDbObjectId m_aEntityId;
  OdTvSubItemPath m_aSubItemsPath;
  OdTvDbObjectId m_bEntityId;
  OdTvSubItemPath m_bSubItemsPath;
};

typedef std::set<OdTvCollisionPair> OdTvCollisionPairContainer;

// Reactor a few with a few collision
class OdTvCheck4DuplicatesCollisionDetectionReactor : public OdGsCollisionDetectionReactor
{
public:
  OdTvCheck4DuplicatesCollisionDetectionReactor(OdTvSelectionOptions::Level level, bool bNeedFilter, bool bNestedPossible);

  virtual OdUInt32 collisionDetected(const OdGiPathNode* pPathNode1, const OdGiPathNode* pPathNode2);
  void fillCollisionResults(OdTvSelectionSetImpl* pWhoCollidedImpl, OdTvSelectionSetImpl* pWithWhomCollidedImpl) const;

protected:
  bool                        m_bNeedFilter;
  bool                        m_bNestedPossible;
  OdDbStub*                   m_pLastPathNode1PersistentDrawableId;
  OdDbStub*                   m_pLastPathNode2PersistentDrawableId;
  OdTvSelectionOptions::Level m_level;

  OdTvCollisionPairContainer m_set;
};

//***************************************************************************//
// A few helper functions
//***************************************************************************//

OdTvVisualStyleId       GetDefaultVisualStyleFromRenderMode(OdTvGsView::RenderMode renderMode, OdTvDbDatabase* pDb);
OdTvGsView::RenderMode  GetTVTDRenderMode(OdDb::RenderMode mode);
void                    AddOdGiPathToTvSelectionSet_entity(const OdGiPathNode& pathNode, OdTvSelectionSetImpl* pSelectionSetImpl, OdTvSelectionOptions::Level level, const OdTvDbObjectId& dbModelId);


#include "TD_PackPop.h"

#endif //_ODTV_GSVIEWIMPL_H_INCLUDED_
