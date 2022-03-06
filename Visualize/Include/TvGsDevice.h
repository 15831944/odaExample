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

#ifndef _ODTV_GSDEVICE_H_INCLUDED_
#define _ODTV_GSDEVICE_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvGsView.h"
#include "TvUserData.h"

#include "Gi/GiRasterImage.h"
#include "TvHighlightStyle.h"

/** \details
  A data type that represents a window handle.
*/
typedef void* OSWindowHandle;

/** \details
  A data type that represents a window GL context.
*/
typedef void* OSWindowGLContext;

/** \details
This class is a functor used by OdTvGsDevice for checking that the vectorization process should be aborted
*/
class ODTV_EXPORT OdTvRegenAbort
{
public:

  /** \details
  Returns true if and only if the vectorization process should be aborted.
  */
  virtual bool regenAbort() const = 0;

  /** \details
  Application operator
  */
  bool operator()() const { return regenAbort();  }
};


/** \details
    This class is an interface for the object that encapsulates GUI display windows.

    \remarks
    OdTvGsDevice objects own, update, and refresh one or more 'OdTvGsView' objects.
    
    In addition, they respond to operating system notifications,
    such as a window resize, forwarded by the graphics system client.
    \sa
    <link tv_working_with_base_classes_device, Work with Visualize Graphics Devices>
*/
class ODTV_EXPORT OdTvGsDevice : public OdTvHandledIObject
{
public:

  /** \details
    Defines the device names.
  */
  enum Name
  {
    kOpenGLES2           = 0,  // OpenGL ES2 device.
    kOpenGL              = 1,  // OpenGL device.
    kBitmap              = 2,  // Bitmap device.
    kDirectX             = 3,  // DirectX device (Windows only).
    kGDI                 = 4,  // GDI device (Windows only).
    kMetal               = 5,  // Metal device (MacOS/iOS only).
    kCustom              = 6   // Any custom device.
  };

  /** \details
    Defines the get/set properties for a device object.
    \sa
    <link tv_working_with_base_classes_device_options, Work with Options of Visualize Graphics Devices>
  */
  enum Options
  {
    kBadOption                    = -1, // Bad (invalid) option. 

    // Common options

    kDoubleBufferEnabled          = 0, // Boolean value. The option enables an additional intermediate off-screen buffer to avoid a blinking effect during on-screen rendering.
    kBlocksCache                  = 1, // Boolean value. The option enables caching of a hierarchical block structure. 
    kEnableMultithread            = 2, // Boolean value. The option enables multithreading.
    kMaxRegenThreads              = 3, // Int value. This property can be used to specify the number of threads for multithread vectorization.
    kEnableSoftwareHLR            = 4, // Boolean value. 2D vectorization devices support HiddenLine rendering mode using the software hidden lines removal algorithm.
                                       // This property enables vectorization of viewports with HiddenLine rendering mode using its algorithm.
    kDiscardBackFaces             = 5, // Boolean value. This property enables back-face culling.
    kUseTTFCache                  = 6, // Boolean value. TrueType fonts cache is useful for rendering drawings that contain a lot of text. 
                                       // If TrueType fonts cache is enabled, each font character used inside the drawing is cached as a separate metafile.
    kUseDynamicSubEntHlt          = 7, // Boolean value. The subentity highlighting mode enables the ability to cache geometry markers for entity geometry parts.
    kForcePartialUpdate           = 8, // Boolean value. Off-screen vectorization devices disable partial update mode. This property can be used to turn on partial update mode in this case.
                                       // Forcing of partial update is useful for tests, and in the case of multithread vectorization it is necessary for off-screen rendering.
    kClearScreen                  = 9, // Boolean value. This property can be set to "false" to prevent surface filling by the background color.
    kRegenCoef                    = 10, // Double value (read only). An application can use this device property to detect if truncation (64-bit floating to 32-bit floating) 
                                        // takes place and initiate geometry regeneration. The truncation coefficient is returned in pixels. 
    kUseLutPalette                = 11, // Int value. Sets bit flags that instruct a vectorization device how to process raster images with a palette.

    //GLES2 and OpenGL specific options
    kUseVisualStyles              = 12, // Boolean value. The option enables the usage of visual styles during vectorization and rendering processes.
                                        // If visual styles usage is disabled, the renderer uses the Render Mode setting instead.
    kUseOverlayBuffers            = 13, // Boolean value. The option enables the usage of overlay buffers during rendering processes.

    kAlternativeHlt               = 14, // UInt value. Sets bit flags that set a highlighting mode.
    kAlternativeHltColor          = 15, // UInt value. Sets bit flags that set a highlighting color.

    kUseSceneGraph                = 16, // Boolean value. Sets bit flags that set using a scene graph.

    kUseCompositeMetafiles        = 17, // Boolean value. Sets bit flags that set using composite metafiles.
    kGeometryShaderUsage          = 18, // Boolean value. Sets bit flags that set using geometry shaders.
    kCreateGLContext              = 19, // Boolean value. Set to 'false' to set using an externally created current GL context.
    kBlendingMode                 = 20, // Int value. Blending Mode value.
    kDelaySceneGraphProc          = 21, // Boolean value. Indicates that it is need to delay the processing of the scene graph until this flag will be changed to false. Default value - false. 

    kAntiAliasLevel               = 22, // Double value. Anti-aliasing level.
    kAntiAliasLevelExt            = 23, // Double value. Anti-aliasing level multiplier.

    kShadowsRenderMode            = 24, //UInt value. Sets bit flags that enables/disables shadow generation features
    kVsmShadowsAmount             = 25, //Double value. Gives the ability to minimize the light-bleeding effect caused by edges of occlusion objects displaced a large length from other occlusion objects inside a scene.
    kShadowMapSoftnessOverride    = 26, //UInt value. Overrides light softness property.
    kShadowMapSizeOverride        = 27, //UInt value. Overrides light shadow map size property.

    kFXAAEnable                   = 28, // Boolean value. Sets bit flags that set FXAA enabled.
    kFXAAQuality                  = 29, // UInt value. Overrides FXAA quality property. From 0 to 5
    kFXAA2dEnable                 = 30, // Boolean value. Sets bit flags that set FXAA for 2d enabled.
    kSSAOEnable                   = 31, // Boolean value. Sets bit flags that set using SSAO.
    kSSAOLoops                    = 32, // Int value. SSAO loops value.
    kSSAORadius                   = 33, // Double value. SSAO radius value. In the case of 'kSSAODynamicRadius = false', the right way is to make it dependent from the models extents.
    kSSAOPower                    = 34, // Double value. SSAO power value.
    kSSAOBlurRadius               = 35, // Int value. SSAO blur radius value.
    kUseGPUSelection              = 36, // Boolean value. Enables GPU selection
    kSceneGraphCachesMode         = 37, // UInt value. Sets Block and TTF caches supporting mode for the Scene Graph 
                                        //( 0 - none; 1 - Support Block Cache; 2 - Support TTF Cache; 3 - Support both ) (only GLES2).
    kSSAODynamicRadius            = 38, // Boolean value. Sets bit flag that set SSAO dynamic radius computation enabled. Is 'On' by default.
    kD3DSurface                   = 39, // OdIntPtr value. D3DSurface value. Only for DirectX device.
    kOptionCount                        // The number of GS device options. 
  };

  /** \details
  Highlight modes for a device object.
  \sa
  <link tv_working_with_features_highlighting, Work with Highlighting>
  */
  enum HltMode
  {
    kHltStippleMode = 0,  // A stipple mode highlight.
    kHltColorMode = 1     // A color mode highlight.
  };

  /** \details
  Defines the regeneration options for a device object.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#5">Redrawing Content of a Device</EXTLINK>
  */
  enum RegenMode
  {
    kRegenAll                = 0,  // Regenerate all.
    kRegenVisible            = 1   // Regenerate only visible.
  };

  /** \details
  Lineweight styles.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#9">Managing Lineweight Configurations</EXTLINK>
  */
  enum LineWeightStyle
  {
    kPointLineWeight = 0,   // Point lineweight style.
    kLineCapStyle = 1,      // Line cap style.
    kLineJoinStyle = 2      // Line join style.
  };

  /** \details
  Line end styles.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#9">Managing Lineweight Configurations</EXTLINK>
  */
  enum LineEndStyle
  {
    kLesButt = 0,       // The line ends with a butt.
    kLesSquare = 1,     // The line ends with a square.
    kLesRound = 2,      // The line ends with an arc of a circle with the diameter equal to the line width.
    kLesDiamond = 3,    // The line ends with a diamond.
    kLesUseObject = 4   // The line ends with a specified object.
  };

  /** \details
  Line joining styles.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#9">Managing Lineweight Configurations</EXTLINK>
  */
  enum LineJoinStyle
  {
    kLjsMiter = 0,    // Lines are joined with miters.
    kLjsBevel = 1,    // Lines are joined with caps. 
    kLjsRound = 2,    // An arc of a circle with the diameter equal to the line width is displayed at the place where two lines are joined.  
    kLjsDiamond = 3,  // Lines are joined with a diamond. 
    kLjsUseObject = 5 // Lines are joined with a specified object. 
  };

  /** \details
  TTF Draw mode
  */
  enum TTFDrawMode
  {
    /** Curves inside TrueType fonts are tessellated by default, so characters are drawn as simple shell primitives with a constant number of vertices. */
    kConstant = 0,
   /** Bezier curve information is additionally passed to the geometry conveyor. This mode can increase or decrease text rendering quality depending on zoom level. Currently supported only for desktop Windows operating systems. */
    kDynamic  = 1
  };

  /** \details
  Retrieves the current name of the GS device.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the current name of the GS Device.
  \remarks 
  If the rc parameter is not null and the GS device name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvGsDevice::Name getGsDeviceName(OdTvResult* rc = NULL) = 0;

  /** \details
  Sets a new name for the device.
  \param sName [in] A string that contains the new name. 
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the renaming.
  \remarks 
  If the new name was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
  Retrieves the current name of the device.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the current name of the device.
  \remarks 
  If the rc parameter is not null and the device name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getName(OdTvResult* rc = NULL) const = 0;

  /** \details
  Retrieves the current value of the bitmap flag for the device. The bitmap flag determines whether the device is a bitmap device. 
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns true if the device is a bitmap device, otherwise returns false. 
  \remarks 
  If the rc parameter is not null and the bitmap flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool isBitmap(OdTvResult* rc = NULL) const = 0;

  /** \details
  Sets up the device object if it was created as "non-setup." Otherwise does nothing.

  \param wnd_handle        [in]  An operating system window handle.
  \param wndRect           [in]  A window rectangle.
  \param device            [in]  A device name (GLES2, OpenGL, etc.).
  \param strVectorizerName [in]  A path to the custom device module (used only when the device name is equal to the kCustom value).
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting up the device.
  \remarks 
  If the device was successfully set up, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#2">Setting and Unloading Device Vectorizers</EXTLINK>
  */
  virtual OdTvResult setupGs(OSWindowHandle wnd_handle, const OdTvDCRect &wndRect, OdTvGsDevice::Name device, OdString* strVectorizerName = 0) = 0;

  /** \details
  Sets up the device object if it was created as "non-setup." Otherwise does nothing.

  \param wnd_context       [in]  An operating system window GL context object.
  \param wndRect           [in]  A window rectangle.
  \param device            [in]  A device name (GLES2, OpenGL, etc.).
  \param strVectorizerName [in]  A path to the custom device module (used only when the device name is equal to the kCustom value).
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting up the device.
  \remarks 
  If the device was successfully set up, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#2">Setting and Unloading Device Vectorizers</EXTLINK>
  */
  virtual OdTvResult setupGsWithContext(OSWindowGLContext wnd_context, const OdTvDCRect &wndRect, OdTvGsDevice::Name device, OdString* strVectorizerName = 0) = 0;

  /** \details
  Sets up the device object if it was created as "non-setup." Otherwise does nothing.

  \param x                 [in]  The output image dimension along the X-axis.
  \param y                 [in]  The output image dimension along the Y-axis.
  \param device            [in]  A device name (GLES2, OpenGL, etc.).
  \param strVectorizerName [in]  A path to the custom device module (used only when the device name is equal to the kCustom value).
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting up the device.
  \remarks 
  If the device was successfully set up, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#2">Setting and Unloading Device Vectorizers</EXTLINK>
  */
  virtual OdTvResult setupGsBitmap(long x, long y, OdTvGsDevice::Name device, OdString* strVectorizerName = 0) = 0;

  /** \details
  Retrieves the current value of the GS load flag for the device. The GS load flag determines whether the GS part (vectorizer) for the device object is loaded.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns true if the GS load part of the device is loaded, otherwise returns false.
  \remarks 
  If the rc parameter is not null and the GS load flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#2">Setting and Unloading Device Vectorizers</EXTLINK>
  */
  virtual bool isGsLoaded(OdTvResult* rc = NULL) = 0;

  /** \details
  Unloads the GS part (vectorizer) of the device.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the unloading.
  \remarks 
  If the GS part of the device was successfully unloaded, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#2">Setting and Unloading Device Vectorizers</EXTLINK>
  */
  virtual OdTvResult unloadGs() = 0;

  /** \details
  Retrieves the current raster image object of the device.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns a smart pointer to an OdGiRasterImage object that represents a raster image.
  \remarks 
  If the rc parameter is not null and the raster image object was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  The method works correctly only for a bitmap device that was previously set.
  \sa
  <link tv_working_with_base_classes_raster_images, Work with Raster Images>
  */
  virtual OdGiRasterImagePtr getRasterImage(OdTvResult* rc = NULL) = 0;

  /** \details
  Marks for refresh the GUI window related to the device.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks 
  If the GUI window was successfully marked for refresh, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#5">Redrawing Content of a Device</EXTLINK>
  */
  virtual OdTvResult invalidate() = 0;

  /** \details
  Marks for refresh a specified region of the GUI window related to the device.
  \param screenRect [in]  A rectangle that specifies the window region to be refreshed.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks 
  If the GUI window region was successfully marked for refresh, the method returns the tvOk value; otherwise it returns an appropriate error code.
  If the window region (parameter screenRect value) is not specified, the whole GUI window is marked for refresh.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#5">Redrawing Content of a Device</EXTLINK>
  */
  virtual OdTvResult invalidate(const OdTvDCRect &screenRect) = 0;

  /** \details
  Retrieves whether the device GUI window shows a correct image. 
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the current value of the correct image flag. The correct image flag determines whether the device GUI window shows a correct raster image (if true) or not (if false). 
  \remarks
  The correct image flag is equal to true when the following conditions are met: 
  * No part of the GUI window area is flagged for refresh.
  * All rasterization processes are complete.
  * The rendering pipeline has been flushed.
  If the rc parameter is not null and the device GUI window displays a correct raster image, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool isValid(OdTvResult* rc = NULL) const = 0;

  /** \details
  Updates the GUI window (or its region) associated with the device object.
  \param pUpdatedRect         [in] A pointer to the rectangle object that represents the window region to be updated.
  \param bSkipPartialRequest  [in] A partial viewing flag value. If equal to true, partial viewing is disabled during the method call.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the update operation.
  \remarks
  The method affects all OdGsView objects owned by the device object, and so it displays the correct image on the GUI window (or its region).
  If the pointer to a window region (the pUpdatedRect parameter value) is NULL, the whole window is updated.
  If the GUI window (or its region) was successfully updated, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#5">Redrawing Content of a Device</EXTLINK>
  */
  virtual OdTvResult update(OdTvDCRect* pUpdatedRect = 0, bool bSkipPartialRequest = false) = 0;

  /** \details
  The handler for the resize event for a GUI window associated with the device object. 
  The method is called whenever the size of the GUI window is changed. 
  \param outputRect [in]  A new size of the output rectangle in device coordinates (pixels).
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the resize event processing.
  \remarks
  If the resize event was successfully processed, the method returns the tvOk value; otherwise it returns an appropriate error code.
  This method should not be called if the device object has zero width and (or) height.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#5">Redrawing Content of a Device</EXTLINK>
  */
  virtual OdTvResult onSize(const OdTvDCRect& outputRect) = 0;

  /** \details
  Retrieves the device output rectangle. The method fills the passed rectangle object with the data of the device output rectangle and returns it to a calling subroutine.
  \param outputRect [out]  A placeholder for the device's output rectangle object. Size of the rectangle is represented in the device coordinates (pixels).
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks
  If the device output rectangle was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getSize(OdTvDCRect& outputRect) const = 0;

  /** \details
  Regenerates the contents of the device object according to the specified regeneration mode.
  \param regenMode [in] A regeneration mode value.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the regeneration.
  \remarks
  If the device content was successfully regenerated, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#5">Redrawing Content of a Device</EXTLINK>
  */
  virtual OdTvResult regen(RegenMode regenMode) = 0;

  /** \details
  The handler for the display settings change event for the device object. 
  The method is called whenever the operating system screen resolution and (or) color depth are changed. 
  \param bitsPerPixel [in]  A new screen color depth.
  \param xPixels      [in]  A new screen resolution along the X-axis (in pixels).
  \param yPixels      [in]  A new screen resolution along the Y-axis (in pixels).
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the event processing.
  \remarks
  If the event was successfully processed, the method returns the tvOk value; otherwise it returns an appropriate error code.
  This method is called after the display settings are changed.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#5">Redrawing Content of a Device</EXTLINK>
  */
  virtual OdTvResult onDisplayChange(int bitsPerPixel, int xPixels, int yPixels) = 0;

  /** \details
  Creates a new view represented with an OdTvGsView object and associates it with the device object. 
  \param name             [in]  A new screen color depth.
  \param bNeedSaveInFile  [in]  A new screen resolution along the X-axis (in pixels).
  \param rc               [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the view object creation.
  \returns Returns the identifier of the newly created view object.
  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).

  If the device is "non-setup," the created view also becomes a "non-setup" view and only a few methods can be called:
* <link OdTvGsView::setView@OdTvPoint&@OdTvPoint&@OdTvVector&@double@double@Projection, setView ()> 
* <link OdTvGsView::setMode@RenderMode, setMode()>
* <link !!OVERLOADED_setViewport_OdTvGsView, setViewport()>
  Any other method returns an error.
  If the rc parameter is not null and a new view object was successfully created, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#4">Managing Views</EXTLINK>
  */
  virtual OdTvGsViewId createView(const OdString& name, bool bNeedSaveInFile = true, OdTvResult* rc = NULL) = 0;

  /** \details
  Inserts a specified view object to the tail of the device's view object collection.
  \param viewId [in]  An identifier of a view object represented with an <link OdTvGsView ,OdTvGsView> object.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of adding a view to the device.
  \remarks 
  If the new view object was successfully added to the device, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#4">Managing Views</EXTLINK>
  */
  virtual OdTvResult addView(const OdTvGsViewId& viewId) = 0;

  /** \details
  Inserts a specified view object to a specified position of the device's view object collection.
  \param viewIndex  [in]  An index of the device's view object collection that specifies the position for the newly inserted view.
  \param viewId     [in]  An identifier of a view object represented with an <link OdTvGsView ,OdTvGsView> object.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of adding a view to the device.
  \remarks 
  If the new view object was successfully added to the device, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#4">Managing Views</EXTLINK>
  */
  virtual OdTvResult insertView(int viewIndex, const OdTvGsViewId& viewId) = 0;

  /** \details
  Removes a specified view object from the device's view object collection and erases the view object itself.
  \param viewId [in]  An identifier of a view object represented with an <link OdTvGsView ,OdTvGsView> object.
  \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns true if the view object was successfully removed from the device and destroyed, otherwise returns false. 
  \remarks 
  If the rc parameter is not null and the view was successfully removed from the device and destroyed, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#4">Managing Views</EXTLINK>
  */
  virtual bool eraseView(const OdTvGsViewId& viewId, OdTvResult* rc = NULL) = 0;
  
  /** \details
  Removes a view object from the specified position of the device's view object collection and erases the view object itself.
  \param viewIndex  [in]  An index of the device's view object collection that specifies the position of the view to be removed and destroyed.
  \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns true if the view object was successfully removed from the device and destroyed, otherwise returns false. 
  \remarks 
  If the rc parameter is not null and the view was successfully removed from the device and destroyed, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#4">Managing Views</EXTLINK>
  */  
  virtual bool eraseView(int viewIndex, OdTvResult* rc = NULL) = 0;

  /** \details
  Removes a specified view object from the device's view object collection.
  \param viewId [in]  An identifier of a view object represented with an <link OdTvGsView ,OdTvGsView> object.
  \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns true if the view object was successfully removed from the device, otherwise returns false. 
  \remarks 
  If the rc parameter is not null and the view was successfully removed from the device, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#4">Managing Views</EXTLINK>
  */
  virtual bool removeView(const OdTvGsViewId& viewId, OdTvResult* rc = NULL) = 0;

  /** \details
  Removes all views from the device and erases them.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of erasing the views.
  \remarks 
  If all views were successfully removed from the device and destroyed, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#4">Managing Views</EXTLINK>
  */
  virtual OdTvResult eraseAllViews() = 0;

  /** \details
  Retrieves the quantity of view objects associated with the device.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the number of views associated with the device object.
  \remarks 
  If the rc parameter is not null and the view quantity was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#4">Managing Views</EXTLINK>
  */
  virtual int numViews(OdTvResult* rc = NULL) const = 0;

  /** \details
  Retrieves the view object located at a specified position in the list of views associated with the device. 
  \param viewIndex  [in]  A position in the list of views associated with the device.
  \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the identifier of the view object. 
  \remarks 
  If the view object was found and its identifier was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#4">Managing Views</EXTLINK>
  */
  virtual OdTvGsViewId viewAt(int viewIndex, OdTvResult* rc = NULL) = 0;

  /** \details
  Retrieves the view object located at a specified screen position. 
  \param screenPoint [in]  A screen position represented with a two-dimensional point in the device coordinate space.
  \param rc          [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the identifier of the view object. 
  \remarks 
  If the view object was found and its identifier was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#4">Managing Views</EXTLINK>
  */
  virtual OdTvGsViewId viewAt(const OdTvPoint2d &screenPoint, OdTvResult* rc = NULL) = 0;

  /** \details
  Retrieves the active view of the device object. 
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the identifier of the active view object. 
  \remarks 
  If there is no active view, the method returns the first view object associated with the device.
  If the view object was found and its identifier was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#4">Managing Views</EXTLINK>
  */
  virtual OdTvGsViewId getActiveView(OdTvResult* rc = NULL) = 0;

  /** \details
  Sets a new background color for the GUI window associated with the device object.
  \param backgroundColor [in] A new background color value.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting a new background color.
  \remarks 
  If a new background color was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#7">Managing a Background Color</EXTLINK>
  */
  virtual OdTvResult setBackgroundColor(ODCOLORREF backgroundColor) = 0;

  /** \details
  Retrieves the current background color value for the GUI window associated with the device object.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the background color of the GUI window associated with the device object.
  \remarks 
  If the rc parameter is not null and the background color value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#7">Managing a Background Color</EXTLINK>
  */
  virtual ODCOLORREF getBackgroundColor(OdTvResult* rc = NULL) = 0;

  /** \details
  Sets a new logical palette for the device object.
  \param logicalPalette [in] A pointer to the color definitions that form the logical palette.
  \param numColors      [in] A quantity of colors in the palette.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting the palette.
  \remarks 
  If the new palette was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  The logical palette is used when index colors are used.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#6">Managing a Logical Palette</EXTLINK>
  */
  virtual OdTvResult setLogicalPalette(const ODCOLORREF* logicalPalette, int numColors) = 0;

  /** \details
    Retrieves the current logical palette used by the device object.
    \param numColors  [out] A placeholder for storing and returning the quantity of colors in the palette.
    \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a pointer to the color definitions array that represents the current logical palette.
    \remarks 
    If the rc parameter is not null and the logical palette was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    The logical palette can be retrieved when index colors are used.
    \sa
    <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#6">Managing a Logical Palette</EXTLINK>
  */
  virtual const ODCOLORREF* getLogicalPalette(int &numColors, OdTvResult* rc = NULL) const = 0;

  /** \details
  Sets a boolean <link OdTvGsDevice::Options, property> value of the device.
  \param opt  [in]  A property to be set.
  \param bVal [in]  A boolean value of the property.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting a value for the property.
  \remarks 
  If the new property value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <link tv_working_with_base_classes_device_options, Work with Options of Visualize Graphics Devices>
  */
  virtual OdTvResult setOption(Options opt, bool bVal) = 0;

  /** \details
  Sets a 16-bit integer <link OdTvGsDevice::Options, property> value of the device.
  \param opt  [in]  A property to be set.
  \param nVal [in]  An integer value of the property.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting a value for the property.
  \remarks 
  If the new property value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <link tv_working_with_base_classes_device_options, Work with Options of Visualize Graphics Devices>
  */
  virtual OdTvResult setOption(Options opt, OdInt16 nVal) = 0;

  /** \details
  Sets a 32-bit integer <link OdTvGsDevice::Options, property> value of the device.
  \param opt  [in]  A property to be set.
  \param nVal [in]  An integer value of the property.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting a value for the property.
  \remarks 
  If the new property value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <link tv_working_with_base_classes_device_options, Work with Options of Visualize Graphics Devices>
  */
  virtual OdTvResult setOption(Options opt, OdInt32 nVal) = 0;

  /** \details
  Sets a double <link OdTvGsDevice::Options, property> value of the device.
  \param opt  [in]  A property to be set.
  \param dVal [in]  A double value of the property.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting a value for the property.
  \remarks 
  If the new property value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <link tv_working_with_base_classes_device_options, Work with Options of Visualize Graphics Devices>
  */
  virtual OdTvResult setOption(Options opt, double dVal) = 0;

  /** \details
  Sets a 32-bit unsigned integer <link OdTvGsDevice::Options, property> value of the device.
  \param opt  [in]  A property to be set.
  \param nVal [in]  An unsigned integer value of the property.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting a value for the property.
  \remarks 
  If the new property value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <link tv_working_with_base_classes_device_options, Work with Options of Visualize Graphics Devices>
  */
  virtual OdTvResult setOption(Options opt, OdUInt32 nVal) = 0;

   /** \details
  Retrieves the current value of a boolean device <link OdTvGsDevice::Options, property>.
  \param opt  [in]  A property with a value to be retrieved.
  \param bVal [out] A placeholder for the boolean device property value.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of retrieving a specified property value.
  \remarks 
  If the property value was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  If the device doesn't have the requested option or the option has another type, the method returns an error; therefore the reference to the value passed to the method is not changed. 
  \sa
  <link tv_working_with_base_classes_device_options, Work with Options of Visualize Graphics Devices>
  */
  virtual OdTvResult getOption(Options opt, bool& bVal) = 0;

  /** \details
  Retrieves the current value of a 16-bit integer device <link OdTvGsDevice::Options, property>.
  \param opt  [in]  A property with a value to be retrieved.
  \param nVal [out] A placeholder for the integer device property value.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of retrieving a specified property value.
  \remarks 
  If the property value was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  If the device doesn't have the requested option or the option has another type, the method returns an error; therefore the reference to the value passed to the method is not changed. 
  \sa
  <link tv_working_with_base_classes_device_options, Work with Options of Visualize Graphics Devices>
  */
  virtual OdTvResult getOption(Options opt, OdInt16& nVal) = 0;

  /** \details
  Retrieves the current value of a 32-bit integer device <link OdTvGsDevice::Options, property>.
  \param opt  [in]  A property with a value to be retrieved.
  \param nVal [out] A placeholder for the integer device property value.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of retrieving a specified property value.
  \remarks 
  If the property value was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  If the device doesn't have the requested option or the option has another type, the method returns an error; therefore the reference to the value passed to the method is not changed. 
  \sa
  <link tv_working_with_base_classes_device_options, Work with Options of Visualize Graphics Devices>
  */
  virtual OdTvResult getOption(Options opt, OdInt32& nVal) = 0;

  /** \details
  Retrieves the current value of a double device <link OdTvGsDevice::Options, property>.
  \param opt  [in]  A property with a value to be retrieved.
  \param dVal [out] A placeholder for the double device property value.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of retrieving a specified property value.
  \remarks 
  If the property value was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  If the device doesn't have the requested option or the option has another type, the method returns an error; therefore the reference to the value passed to the method is not changed. 
  \sa
  <link tv_working_with_base_classes_device_options, Work with Options of Visualize Graphics Devices>
  */
  virtual OdTvResult getOption(Options opt, double& dVal) = 0;

  /** \details
  Retrieves the current value of a 32-bit unsigned integer device <link OdTvGsDevice::Options, property>.
  \param opt  [in]  A property with a value to be retrieved.
  \param nVal [out] A placeholder for the unsigned integer device property value.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of retrieving a specified property value.
  \remarks 
  If the property value was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  If the device doesn't have the requested option or the option has another type, the method returns an error; therefore the reference to the value passed to the method is not changed. 
  \sa
  <link tv_working_with_base_classes_device_options, Work with Options of Visualize Graphics Devices>
  */
  virtual OdTvResult getOption(Options opt, OdUInt32& nVal) = 0;

  /** \details
  Retrieves the current value of a OdIntPtr device <link OdTvGsDevice::Options, property>.
  \param opt  [in]  A property with a value to be retrieved.
  \param pVal [out] A placeholder for the OdIntPtr device property value.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of retrieving a specified property value.
  \remarks
  If the property value was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  If the device doesn't have the requested option or the option has another type, the method returns an error; therefore the reference to the value passed to the method is not changed.
  \sa
  <link tv_working_with_base_classes_device_options, Work with Options of Visualize Graphics Devices>
  */
  virtual OdTvResult getOption(Options opt, OdIntPtr& pVal) = 0;

  /** \details
  Sets a new value of the FPS show flag, which determines whether FPS information is displayed while rendering (if true) or not (if false).
  \param bShow [in] A new flag value.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting the flag value.
  \remarks 
  If the new flag value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#8">Displaying FPS Data</EXTLINK>
  */
  virtual OdTvResult setShowFPS(bool bShow) = 0;

  /** \details
  Retrieves the current value of the FPS show flag, which determines whether the FPS information is displayed while rendering (if true) or not (if false).
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
  \returns Returns true if the FPS information is displayed while rendering; otherwise returns false.
  \remarks 
  If the rc parameter is not null and the flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#8">Displaying FPS Data</EXTLINK>
  */
  virtual bool getShowFPS(OdTvResult* rc = 0) const = 0;

  /** \details
  Sets a new lineweight display style configuration for the device object.
  \param styleEntry [in] A lineweight style entry for which the current setting will be set.
  \param uValue     [in] A lineweight style value.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks 
  If the new lineweight style value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#9">Managing Lineweight Configurations</EXTLINK>
  */
  virtual OdTvResult setLineWeightConfiguration(LineWeightStyle styleEntry, OdUInt8 uValue) = 0;

  /** \details
  Retrieves the current lineweight display style configuration of the device object.
  \param styleEntry [in] A lineweight style entry for which the current setting is retrieved.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the current lineweight display style value. 
  \remarks 
  For the <link OdTvGsDevice::LineWeightStyle::kPointLineWeight, kPointLineWeight> style, the method returns 0 if the point lineweight is disabled; otherwise the method returns 1.
  For the <link OdTvGsDevice::LineWeightStyle::kLineCapStyle, kLineCapStyle> style, the method returns an entry that is represented with a value of the <link OdTvGsDevice::LineEndStyle, LineEndStyle enumeration>.
  For the <link OdTvGsDevice::LineWeightStyle::kLineJoinStyle, kLineJoinStyle> style, the method returns an entry that is represented with a value of the <link OdTvGsDevice::LineJoinStyle, LineJoinStyle enumeration>.
  If the rc parameter is not null and the lineweight style value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#9">Managing Lineweight Configurations</EXTLINK>
  */
  virtual OdUInt8 getLineWeightConfiguration(LineWeightStyle styleEntry, OdTvResult* rc = NULL) const = 0;

  /** \details
  Makes the device object active or inactive.
  \param bIsActive [in] A flag that determines whether the device is active (if true) or not (if false).
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the device activation or deactivation.
  \remarks 
  If the device was successfully activated or deactivated, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#3">Activating a Device</EXTLINK>
  */
  virtual OdTvResult setActive(bool bIsActive) = 0;

  /** \details
  Retrieves whether the device is active. 
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns true if the device is active; otherwise returns false.
  \remarks 
  If the rc parameter is not null and the active flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#3">Activating a Device</EXTLINK>
  */
  virtual bool getActive(OdTvResult* rc = NULL) const = 0;

  /** \details
  Switches the background partial viewing mode on or off for the device.
  The background partial viewing mode assumes that the loading of objects runs in a separate background thread.
  \param bIsInBackground [in] A new value of the background partial viewing mode.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  If the method input parameter is equal to true, the device starts to work in background partial viewing mode; 
  otherwise (if is equal to false) the background partial viewing mode is disabled.
  The method call is relevant only for a database opened in partial load mode.
  If the background partial viewing mode is successfully switched on or off, the method returns the tvOk; otherwise it returns an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#10">Making Partial Viewing a Background Process</EXTLINK>
  */
  virtual OdTvResult setBackgroundPartialView(bool bIsInBackground) = 0;

  /** \details
  Retrieves whether the background partial viewing mode is enabled or disabled.
  The background partial viewing mode assumes that the loading of objects runs in a separate background thread.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns true if the background partial view mode is enabled for the device; otherwise the method returns false.
  \remarks 
  If the database the device belongs to is not opened in the partial load mode, the method also returns false.
  If the rc parameter is not null and the background partial viewing mode's state was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#10">Making Partial Viewing a Background Process</EXTLINK>
  */
  virtual bool getBackgroundPartialView(OdTvResult* rc = NULL) const = 0;

  /** \details
  Retrieves whether the background partial viewing mode is enabled for the device and the partial loading task is in progress.
  The background partial viewing mode assumes that the loading of objects runs in a separate background thread.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns true if the device is in the background partial viewing mode and the partial loading task is in progress; otherwise returns false.
  \remarks 
  If the database the device belongs to is not opened in the partial load mode or the partial viewing mode is disabled for the device, the method also returns false.
  If the rc parameter is not null and the state value of the partial loading progress was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <EXTLINK https://docs.opendesign.com/tv/tv_working_with_base_classes_device_functionality.html#10">Making Partial Viewing a Background Process</EXTLINK>
  */
  virtual bool getBackgroundPartialViewingInProgress(OdTvResult* rc = NULL) const = 0;

  /** \details
  Assigns the OdTvRegenAbort to the device
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks
  If the regenAbort functor was successfully assign, the method returns tvOk; otherwise it returns an appropriate error code.
  Such functor can be used in partial viewing mode or (in the future) during low memory import functionality
  */
  virtual OdTvResult setRegenAbort(OdTvRegenAbort* pRegenAbort) = 0;

  /** \details
  Returns the assigned OdTvRegenAbort instance
  \param rc         [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvRegenAbort* getRegenAbort(OdTvResult* rc = NULL) const = 0;

  /** \details
  Sets a new value of the line smoothing flag, which determines whether anti-aliasing is switched on while rendering (if true) or not (if false).
  \param bOn [in] A flag that determines whether anti-aliasing is switched on while rendering (if true) or not (if false).
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting the flag value.
  \remarks
  If the new flag value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  \sa
  <link tv_working_with_features_anti-aliasing, Work with Anti-Aliasing>
  */
  virtual OdTvResult setLineSmoothing(bool bOn) = 0;

  /** \details
  Retrieves the current value of the line smoothing flag, which determines whether anti-aliasing is switched on while rendering (if true) or not (if false).
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
  \returns Returns true if the anti-aliasing is switched on; otherwise returns false.
  \remarks
  If the rc parameter is not null and the flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  \sa
  <link tv_working_with_features_anti-aliasing, Work with Anti-Aliasing>
  */
  virtual bool getLineSmoothing(OdTvResult* rc = 0) const = 0;

  /** \details
  Specifies the time frame within one 'update' call after which the scene graph building operations should be interrupted.
  \param mSec [in] Time frame in milliseconds.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks
  The time frame value defines the time which device can spent for the scene graph creation within one 'update' call.
  This feature is useful for the case of single-thread mode because normally scene graph building is performed in
  the background threads. Thus, in the case if only one thread is available, the scene graph building procedure
  will also work in this thread and can significantly freeze the 'update' method.
  Set zero as an input time frame if you want to remove the time frame.
  If the time frame is successfully set, the method returns tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setSceneGraphCreationInteruptTime(OdUInt32 mSec) = 0;

  /** \details
  Sets a new TTF Draw mode for the device object.
  \param mode         [in] A TTF Draw mode value.
  \param textQuality  [in] A text quality [0-100] (only for TTFDrawMode::kConstant mode).
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks
  If the new TTF Draw mode value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setTTFDrawMode(TTFDrawMode mode, OdUInt32* textQuality = NULL) = 0;

  /** \details
  Retrieves the current TTF Draw mode of the device object.
  \param textQuality [out] A pointer to text quality value is retrieved (only for TTFDrawMode::kConstant mode).
  \param rc          [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the current TTF Draw mode value.
  \remarks
  If the rc parameter is not null and the TTF Draw mode value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual TTFDrawMode getTTFDrawMode(OdUInt32* textQuality = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
  Sets a new highlight style to the device.
  \param highlightStyleId [in] An identifier of the highlight style object.
  \param bAutoRegen [in] An auto regeneration flag value. If it is equal to true, in some cases the regeneration will be performed automatically after applying the style.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting the highlight style.
  \remarks
  If the new highlight style was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setHighlightStyle(const OdTvHighlightStyleId& highlightStyleId, bool bAutoRegen = true) = 0;

  /** \details
  Retrieves the current highlight style for the device.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns an identifier of the current highlight style.
  \remarks
  If the current highlight style object was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvHighlightStyleId getHighlightStyle(OdTvResult* rc = NULL) const = 0;

  /** \details
  Sets an array of highlight styles to the device. Different objects can be highlighted with different styles from this array.
  \param styles     [in] An array of the highlight styles objects.
  \param bAutoRegen [in] An auto regeneration flag value. If it is equal to true, in some cases the regeneration will be performed automatically after applying the styles.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of setting the highlight styles array.
  \remarks
  If the new highlight styles array was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setHighlightStyles(const OdArray<OdTvHighlightStyleId>& styles, bool bAutoRegen = true) = 0;

  /** \details
  Retrieves the array of highlight styles for the device.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns an array of highlight styles that are used for highlight objects.
  \remarks
  If the current highlight style object was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdArray<OdTvHighlightStyleId> getHighlightStyles(OdTvResult* rc = NULL) const = 0;
};

/** \details
A data type that represents a smart pointer to an <link OdTvGsDevice, OdTvGsDevice> object.
*/
typedef OdTvSmartPtr<OdTvGsDevice> OdTvGsDevicePtr;



/** \details
The interface class for a database object identifier that allows access to the <link OdTvGsDevice, OdTvGsDevice> object.
*/
class ODTV_EXPORT OdTvGsDeviceId : public OdTvId
{
public:
  
  /** \details
  Opens the device determined with its identifier for a read or write operation. 
  \param mode [in] An open mode value.
  \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
  \returns Returns a smart pointer to the device object.
  \remarks
  If the rc parameter is not null and the device is successfully opened, the rc parameter accepts the tvOk value;
  otherwise it contains an appropriate error code.
  */
  OdTvGsDevicePtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;
};


/** \details
The interface class for the iterator of <link OdTvGsDevice, OdTvGsDevice> objects.
An iterator object provides sequential access to a collection of devices. 
*/
class ODTV_EXPORT OdTvDevicesIterator : public OdTvIterator, public OdTvIObject
{
public:

  /** \details
  Retrieves the device that is currently referenced by the iterator object.
  \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the device identifier if the iterator refers to a device; otherwise it returns a null value identifier.
  \remarks 
  If the rc parameter is not null and the device identifier is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
  appropriate error code.
  If the iterator refers to a device, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvGsDeviceId getDevice(OdTvResult* rc = NULL) const = 0;

  /** \details
  Searches the device defined through its identifier and moves the iterator to this device if found.
  \param deviceId [in] A device identifier.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks 
  If the device specified through its identifier is found, the method returns the tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek(const OdTvGsDeviceId& deviceId) = 0;
};

/** \details
A data type that represents a smart pointer to an <link OdTvDevicesIterator, OdTvDevicesIterator> object.
*/
typedef OdTvSmartPtr<OdTvDevicesIterator> OdTvDevicesIteratorPtr;

#endif //_ODTV_GSDEVICE_H_INCLUDED_
