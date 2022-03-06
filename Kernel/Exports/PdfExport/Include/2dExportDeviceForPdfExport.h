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

//////////////////////////////////////////////////////////////////////
//
// 2dExportDevice.h: definition of the Od2dExportDevice, Od2dExportDevice classes.
//                    These are base classes for 2d export.
//
//////////////////////////////////////////////////////////////////////

#ifndef _2DEXPORTDEVICE_INCLUDED_
#define _2DEXPORTDEVICE_INCLUDED_

#if _MSC_VER > 1000
#pragma once 
#endif // _MSC_VER > 1000

#include "Gs/GsBaseInclude.h"
#include "Gi/GiGeometrySimplifier.h"
#include "Gi/GiRasterImage.h"
#include "Gi/GiSpatialFilter.h"
#include "Gi/GiPerspectivePreprocessor.h"
#include "Gi/GiHLRemover.h"
#include "Gi/GiPlaneProjector.h"
#include "Gi/GiOrthoClipperEx.h"
#include "Gi/GiMetafiler.h"
#include "../Extensions/ExRender/MetafileTransformStack.h"
#include "BoolArray.h"
#include "2dExportUtils.h"

/** \details
  Contains declarations for 2D PDF Export.
  <group OdExport_Classes> 
*/
namespace TD_PDF_2D_EXPORT
{

/** \details
  A class that implements font parameters for two-dimensional export in PDF format.
*/
class Od2dFont
{
public:
  /** \details 
    Creates a new instance of font parameters set with default values.
  */
  Od2dFont()
    : m_bold(false)
    , m_italic(false)
    , m_underline(false)
    , m_charset(1)
    , m_pitch(0)
    , m_family(0)
    , m_height(1.0)
    , m_rotation(0)
    , m_width_scale(1.0)
    , m_oblique(0)
    , m_spacing(1024)
    , m_flags(0)
  {}

  /** A string that contains the font name. */
  OdString m_font_name; 
  /** A flag that determines the boldface option of the font. If it is equal to true, symbols are bold; otherwise, they are not. */
  bool     m_bold; 
  /** A flag that determines the italic option of the font. If it is equal to true, symbols are italic; otherwise, they are not. */
  bool     m_italic; 
  /** A flag that determines the underline option of the font. If it is equal to true, symbols are underlined; otherwise, they are not. */
  bool     m_underline; 
  /** A code of the character set of the font symbols. */
  int      m_charset; 
  /** A pitch bitmask of the font. */
  int      m_pitch; 
  /** A code of the font family. */
  int      m_family; 
  /** A height of symbols. */
  double   m_height;
  /** An angle of symbols rotation. */
  double   m_rotation;
  /** A width scale value. */
  double   m_width_scale;
  /** An angle of obliqueness for the font symbols. */
  double   m_oblique;
  /** A value of spacing between symbols. */
  double   m_spacing;

  /** \details 
    Defines type of font.
  */
  enum
  {
      /** TVERT*/
    VERTICAL        = 0x0001, 
      /** TXMIR*/
    MIRROR_X        = 0x0002, 
      /** TYMIR*/
    MIRROR_Y        = 0x0004, 
      /** TUNDER*/
    UNDERSCORE      = 0x0008, 
      /** TOVER*/
    OVERSCORE       = 0x0010, 
      /** TMSTART*/
    MTEXT_START     = 0x0020, 
      /** TMEND*/
    MTEXT_END       = 0x0040, 
      /** TMTEXT*/
    MTEXT           = 0x0080, 
      /** Whip and GDI font engine only*/
    GREEK_TEXT      = 0x1000, 
      /** Whip and GDI font engine only*/
    PATH_TEXT       = 0x2000, 
      /** Outline Text Only*/
    OUTLINE_TEXT    = 0x4000
  };

  /** A set of flag values related to the font.*/
  long                        m_flags;
};

//////////////////////////////////////////////////////////////////////   {filename:Od2dExportDevice_Definition}

/** \details
  A class that implements storing and handling of the destination geometry for the two-dimensional export in PDF format.
*/
class Od2dExportGeometry: public OdGiGeometrySimplifier
{
public:

  /**
   Defines types of export devices. A type definition depends on what primitives are supported.
  */
  enum DeviceType
  {
    /** A device supports nothing.*/
    kSupportNothing = 0,

    /** A value for an internal usage. Don't use it in your ODA-based applications.*/
    kFirstFlag = 1,

    /** A device supports two-dimensional polylines.*/
    kSupport2dPolyline = kFirstFlag << 0,
    /** A device supports two-dimensional circles.*/
    kSupport2dCircle = kFirstFlag << 1,
    /** A device supports two-dimensional ellipses.*/
    kSupport2dEllipse = kFirstFlag << 2,
    /** A device supports NRC clipping.*/
    kSupportNrcClip = kFirstFlag << 3,
    /** A device supports only Unicode text.*/
    kUnicodeOnly = kFirstFlag << 4,
    /** A device supports contours filling.*/
    kSupportContourFill = kFirstFlag << 5,

    /** A value for an internal usage. Don't use it in your ODA-based applications.*/
    kLastFlag = kSupportContourFill,

    /** A set of options for a DWF export device.*/
    kDWFDevice = kSupport2dPolyline | kSupport2dCircle | kSupport2dEllipse,
    /** A set of options for a PDF export device.*/
    kPDFDevice = kSupport2dPolyline | kUnicodeOnly | kSupportNrcClip | kSupportContourFill
  };

  /** \details
    Requests the export device type.
    \returns A signed 32-bit integer that represents a set of options that defines the export device type.
  */
  virtual OdUInt32 getDeviceType() const = 0;

  /** \details 
    Sets the text for the export device. 
    \param position   [in] A point that represents the text position.
    \param u          [in] The u-vector of the text label.
    \param v          [in] The v-vector of the text label.
    \param msg        [in] A null-terminated string that contains the text. 
    \param length     [in] A text length.
    \param raw        [in] A raw flag value.
    \param pTextStyle [in] A raw pointer to the text style object.
    \param bBox       [in] A box flag value.
    \param pFont      [in] A raw pointer to the text font object.
    \param pUnicode   [in] An array that contains the unicode representation of the text.    
  */
  virtual void setText(const OdGePoint3d& position,
    const OdGeVector3d& u,
    const OdGeVector3d& v,
    const OdChar* msg, OdInt32 length, bool raw,
    const OdGiTextStyle* pTextStyle,
    bool  bBox,
    const Od2dFont* pFont = NULL,
    const OdArray<OdUInt16>* pUnicode = NULL)
  {}

  // output into device context

  /** \details
    Writes a polyline into the export device.
    \param nPts   [in] A number of points that represent verticies of the polyline.
    \param points [in] A raw pointer to the array of points that represent verticies of the polyline.
  */
  virtual void dc_polyline(OdUInt32 nPts, const OdGePoint2d* points);

  /** \details
    Writes a polygon into the export device.
    \param nPts   [in] A number of points that represent verticies of the polygon.
    \param points [in] A raw pointer to the array of points that represent verticies of the polygon.
  */
  virtual void dc_polygon(OdUInt32 nPts, const OdGePoint2d* points);

  /** \details
    Writes a circle into the export device.
    \param ellipse [in] An OdGeEllipArc3d object that represents the circle.
  */
  virtual void dc_circle(const OdGeEllipArc3d& ellipse);

  /** \details
    Writes an ellipse into the export device.
    \param ellipse [in] An OdGeEllipArc3d object that represents the ellipse.
  */
  virtual void dc_ellipse(const OdGeEllipArc3d& ellipse);

  /** \details
    Writes a gouraud polytriangle into the export device.
    \param pVertexList  [in] A raw pointer to the array of points that represent verticies.
    \param faceListSize [in] A size of the list of faces.
    \param pFaceList    [in] A raw pointer to the array of face veticies indexes.
    \param pColors      [in] A raw pointer to the array of colors. 
  */
  virtual void dc_gouraud_polytriangle(
    const OdGePoint3d* pVertexList,
    OdInt32 faceListSize,
    const OdInt32* pFaceList,
    const OdCmEntityColor* pColors);
  
  /** \details
    Writes a raster image into the export device.
    \param pRaster  [in] A smart pointer to a raster image.
    \param imgExts  [in] A raster image extents.
  */
  virtual void dc_raster_image(OdGiRasterImagePtr pRaster, 
    const OdGeExtents2d& imgExts);

  /** \details
    Writes a color value into the export device.
    \param rgb [in] A color value.
  */ 
  virtual void dc_color(ODCOLORREF rgb);

  /** \details
    Writes a layer into the export device.
    \param idx        [in] An index of the layer.
    \param layer_name [in] A string that contains the layer name.
  */ 
  virtual void dc_layer(int idx, const OdString& layer_name);

  /** \details
    Pushes a clip into the export device.
    \param nrcContours  [in] A number of contours.
    \param pNrcCounts   [in] A raw pointer to an array that contains count of points for each contour.
    \param nrcPoints    [in] An array of points that form contours.
  */
  virtual void dc_pushClip(int nrcContours, const int* pNrcCounts, const OdGsDCPointArray &nrcPoints);

  /** \details
    Pops a clip from the export device.
  */
  virtual void dc_popClip();

  /** \details
    Sets the deviation.
    \param dev [in] A raw pointer to an OdGiDeviation object that contains the deviation information.
  */
  virtual void setupSimplifier(const OdGiDeviation* dev)
  {
    OdGiGeometrySimplifier::setDeviation(dev);
  }

  // ----- The Overrides of OdGiGeometrySimplifier (OdGiConveyorGeometry) -----
  
  /** \details
    Writes a triangle into the export device. 
    \param vertices [in] A raw pointer to the list that contains indicies of the triangle verticies.
    \param pNormal  [in] An OdGeVector3d object that represents the normal vector for the triangle.
  */
  virtual void triangleOut(const OdInt32* vertices, const OdGeVector3d* pNormal) ODRX_OVERRIDE;

  /** \details
    Writes a polyline into the export device.
    \param numPoints   [in] A number of points in the polyline.
    \param pVertexList [in] A raw pointer to an array of OdGePoint3d object. These objects represents verticies in the polyline.
  */
  virtual void polylineOut(OdInt32 numPoints, const OdGePoint3d* pVertexList) ODRX_OVERRIDE;

  /** \details 
    Processes a circle data within the export device.
    \param center      [in] A center of the circle.
    \param radius      [in] A radius value.
    \param normal      [in] A normal vector for the circle.
    \param startVector [in] A start vector.
    \param pExtrusion  [in] A raw pointer to the extrusion vector.
  */
  void circleProc2(
    const OdGePoint3d& center,
    double radius,
    const OdGeVector3d& normal,
    const OdGeVector3d& startVector,
    const OdGeVector3d* pExtrusion = 0) ODRX_OVERRIDE;

  /** \details 
    Processes a circle data within the export device.
    \param center      [in] A center of the circle.
    \param radius      [in] A radius value.
    \param normal      [in] A normal vector for the circle.
    \param pExtrusion  [in] A raw pointer to the extrusion vector.
  */
  void circleProc(
            const OdGePoint3d& center, 
            double radius, 
            const OdGeVector3d& normal, 
            const OdGeVector3d* pExtrusion = 0) ODRX_OVERRIDE;
  
  /** \details 
    Processes a circle data within the export device.
    \param firstPoint  [in] A first point of the circle.
    \param secondPoint [in] A second point of the circle.
    \param thirdPoint  [in] A third point of the circle.
    \param pExtrusion  [in] A raw pointer to the extrusion vector.
  */
  void circleProc(
            const OdGePoint3d& firstPoint, 
            const OdGePoint3d& secondPoint, 
            const OdGePoint3d& thirdPoint, 
            const OdGeVector3d* pExtrusion = 0) ODRX_OVERRIDE;
  
  /** \details 
    Processes a circular arc within the export device. 
    \param center       [in] A center of the circular arc.
    \param radius       [in] A double value that contains the circular arc radius. 
    \param normal       [in] A normal vector of the circular arc.
    \param startVector  [in] A starting vector.
    \param sweepAngle   [in] A sweeping angle. 
    \param arcType      [in] An arc type.
    \param pExtrusion   [in] A raw pointer to an extrusion vector.
  */
  void circularArcProc(
            const OdGePoint3d& center,
            double radius,
            const OdGeVector3d& normal,
            const OdGeVector3d& startVector,
            double sweepAngle,
            OdGiArcType arcType = kOdGiArcSimple, 
            const OdGeVector3d* pExtrusion = 0) ODRX_OVERRIDE;
  
  /** \details 
    Processes a circular arc within the export device. 
    \param start      [in] A starting point of the circular arc.
    \param point      [in] A second point of the circular arc.
    \param end        [in] An ending point of the circular arc.
    \param arcType    [in] An arc type.
    \param pExtrusion [in] A raw pointer to an extrusion vector.
  */
  void circularArcProc(
            const OdGePoint3d& start,
            const OdGePoint3d& point,
            const OdGePoint3d& end,
            OdGiArcType arcType = kOdGiArcSimple, 
            const OdGeVector3d* pExtrusion = 0) ODRX_OVERRIDE;
  
  /** \details 
    Processes a polygon within the export device. 
    \param nbPoints     [in] A number of polygon points
    \param pVertexList  [in] A raw pointer to the array of verticies.
    \param pNormal      [in] An raw pointer to the normal vector.
    \param pExtrusion   [in] A raw pointer to an extrusion vector.
  */
  void polygonProc(
            OdInt32 nbPoints, 
            const OdGePoint3d* pVertexList,
            const OdGeVector3d* pNormal = 0,
            const OdGeVector3d* pExtrusion = 0) ODRX_OVERRIDE;

  /** \details 
    Processes a text within the export device. 
    \param position   [in] A point that represents the text position.
    \param u          [in] The u-vector of the text label.
    \param v          [in] The v-vector of the text label.
    \param msg        [in] A null-terminated string that contains the text. 
    \param length     [in] A text length.
    \param raw        [in] A raw flag value.
    \param pTextStyle [in] A raw pointer to the text style object.
    \param pExtrusion [in] A raw pointer to an extrusion vector.
  */
  void textProc(
            const OdGePoint3d& position,
            const OdGeVector3d& u, 
            const OdGeVector3d& v,
            const OdChar* msg, 
            OdInt32 length, 
            bool raw, 
            const OdGiTextStyle* pTextStyle,
            const OdGeVector3d* pExtrusion = 0) ODRX_OVERRIDE;

  /** \details 
    Processes an x-line within the export device. 
    \param firstPoint  [in] The first point.
    \param secondPoint [in] The second pont.
  */
  void xlineProc(
            const OdGePoint3d& firstPoint, 
            const OdGePoint3d& secondPoint) ODRX_OVERRIDE;

  /** \details 
    Processes a ray within the export device. 
    \param basePoint      [in] A first ray point.
    \param throughtPoint  [in] A through ray point.
  */
  void rayProc(
            const OdGePoint3d& basePoint, 
            const OdGePoint3d& throughtPoint) ODRX_OVERRIDE;

  /** \details 
    Processes an elliptical arc within the export device. 
    \param arc                  [in] An elliptic arc to be processed.
    \param pEndPointsOverrides  [in] A raw pointer to an array of points to be used as the first and last points of the vectorized arc.
    \param arcType              [in] An arc type.
    \param pExtrusion           [in] A raw pointer to an extrusion vector.
  */  
  void ellipArcProc(
            const OdGeEllipArc3d& arc,
            const OdGePoint3d* pEndPointsOverrides,
            OdGiArcType arcType,
            const OdGeVector3d* pExtrusion) ODRX_OVERRIDE;

  // Utilitary functions
  /** \details 
    Writes an ellipse to the export device.
    \param ellipse [in] An ellipse object to be written.
  */
  virtual void putEllipse(OdGeEllipArc3d& ellipse);
  
  /** \details
    Processes a specified SHX text within the export device.
    
    \param position   [in]  A starting point.
    \param u          [in] An X-axis for the export device.
    \param v          [in] An Y-axis for the export device.
    \param msg        [in] An array of OdChar symbols that represents the text of the message to be processed.
    \param length     [in] A length of the message.
    \param raw        [in] A raw flag value.
    \param pStyle     [in] A raw pointer to the text style object associated with the text.
    \param pExtrusion [in] A raw pointer to the vector object that defines the direction of the text extrusion.
  */
  virtual void shxText(const OdGePoint3d& position,
    const OdGeVector3d& u,
    const OdGeVector3d& v,
    const OdChar* msg,
    OdInt32 length,
    bool raw,
    const OdGiTextStyle* pStyle,
    const OdGeVector3d* pExtrusion)
  {
    // Here is the place for additional processing of SHX text in case of a need
  }
  
  /** \details
    Retrieves the result of the text processing within the export device.

    \param position          [in] A starting point.
    \param u                 [in] An X-axis for the export device.
    \param v                 [in] An Y-axis for the export device.
    \param msg               [in] A raw pointer to an array of OdChar symbols that contains the text of the message.
    \param length            [in] A length of the text message.
    \param raw               [in] A raw flag value.
    \param pStyle            [in] A raw pointer to the text style object associated with the text.
    \param pProcessedText    [out] A placeholder for the processed text (an OdString object). 
    \param arrayUnicode      [out] A placeholder for the processed text (an arrayo of Unicode symbol codes).
    \param bASCII            [in] A flag value that determines whether the text contains only ASCII symbols.
    \param isInBigFont       [out] An array of boolean that contains big font flags.
    \param pArrayRealUnicode [out] An array of real codes for the symbols.
    \param pAdvances         [out] An array of advanced points.
    
    \returns true if the text processing was successful; otherwise the method returns false.
  */
  bool textProcessing(const OdGePoint3d& position,
    const OdGeVector3d& u,
    const OdGeVector3d& v,
    const OdChar* msg,
    OdInt32 length,
    bool raw,
    const OdGiTextStyle* pStyle,
    OdString& pProcessedText,
    OdArray<OdUInt16>& arrayUnicode,
    bool bASCII,
    OdBoolArray *isInBigFont = NULL,
    OdArray<OdUInt16>* pArrayRealUnicode = NULL,
    OdGePoint2dArray *pAdvances = NULL);

  /** \details 
    A callback method that is called when an entity's traits are changed. 
    \param traits [in] An entity's traits.
  */
  virtual void onTraitsModified(const OdGiSubEntityTraitsData& traits);
  
  /** \details 
    Transforms a raster image.
    
    \param pRastIn          [in] A smart pointer to an input raster image. 
    \param pRastOut         [in] A placeholder for an output rster image that is got after the transformation represented with a smart pointer. 
    \param backgroundColor  [in] A background color value to be implemented.
    
    \return true if the raster image was transformed successfully; otherwise, the method returns false.
  */
  virtual bool transformImage(OdGiRasterImagePtr pRastIn, OdGiRasterImagePtr& pRastOut, ODCOLORREF backgroundColor) const;

protected:
    OdGiSubEntityTraitsData m_effTraits;
}; // end Od2dExportGeometry

/** \details
  A class that implements a device for the two-dimensional export in PDF format.
*/
class Od2dExportDevice: public OdGsBaseVectorizeDevice
{
public:

  /** \details 
    Defines a type of image formats details. 
  */
  enum ImageOrg
  {
    /**1 bit per pixel.*/
    orgBitonal = 1, 
    /** 8 bits per pixel, paletted.*/
    orgMapped = 8, 
    /** 24 bits per pixel. Red-green-blue color scheme.*/
    orgRGB = 24, 
    /** 32 bits per pixel. Blue-green-red-alpha color scheme.*/
    orgBGRA = 32     
  };

  /** \details
    Defines shaded viewport export policies.
  */
  enum ShadedViewportExportMode
  {
    /** Shaded Viewports will be exported as one-piece image with low resolution.*/
    kOnePiece = 0,
    /** Shaded Viewports will be exported as tiled images according to vector resolution (geometry DPI).*/
    kAsTiles = 1,
    /** Shaded Viewports will be exported as striped images according to vector resolution (geometry DPI).*/
    kAsStrips = 2
  };

  /** \details
     Creates a new export object device with default parameters.
  */
  Od2dExportDevice();
  
  /** \details 
    Destroys the export device object and frees the memory occupied by the device.
  */
  ~Od2dExportDevice();

  /** \details
    Requests the current value of the multithreaded vectorization option.
    \returns true if the multithreaded vectorization is enabled; otherwise, the method returns false.
  */
  bool supportParallelVect() const { return GETBIT(m_vectPerfData.m_options, eEnableParallelVectorization); }

  /** \details
  Sets the multithreaded vectorization option.
  \param bOn [in] An option value. If the value is equal to true, the multithreaded vectorization is enabled. To switch off the option set this parameter to false.
  */
  void setSupportParallelVect(bool bOn) { SETBIT(m_vectPerfData.m_options, eEnableParallelVectorization, bOn); }

  /** \details 
    Requests the flag value that determines whether the searchable text is exported in rendered views (if the flag value is equal to true) 
    or not (if the flag value is equal to false). 
    \returns true of the searchable text is exported in rendered views; otherwise the method returns false.
  */
  bool exportSearchableTextInRenderedViews() const { return GETBIT(OdGsBaseVectorizeDevice::m_flags, kExportSearchableTextInRenderedViews); }
  
  /** \details 
    Set a new value of the flag that determines whether the searchable text is exported in rendered views (if the flag value is equal to true) 
    or not (if the flag value is equal to false).
    \param bOn [in] A new value of the flag to be set.
  */
  void setExportSearchableTextInRenderedViews(bool bOn) { SETBIT(OdGsBaseVectorizeDevice::m_flags, kExportSearchableTextInRenderedViews, bOn); }

  /** \details 
    Requests the flag value that determines whether the searchable text is exported as hidden text (if the flag value is equal to true) 
    or not (if the flag value is equal to false). 
    \returns true of the searchable text is exported as hidden text; otherwise the method returns false.
  */
  bool exportSearchableTextAsHiddenText() const { return GETBIT(OdGsBaseVectorizeDevice::m_flags, kExportSearchableTextAsHiddenText); }
  
  /** \details 
    Set a new value of the flag that determines whether the searchable text is exported as hidden text (if the flag value is equal to true) 
    or not (if the flag value is equal to false).
    \param bOn [in] A new value of the flag to be set.
  */
  void setExportSearchableTextAsHiddenText(bool bOn) { SETBIT(OdGsBaseVectorizeDevice::m_flags, kExportSearchableTextAsHiddenText, bOn); }

  // Set the target data stream and the type.  
  //static OdGsDevicePtr createObject(DeviceType type = /*Od2dExportDevice::*/k3dDevice);

  /** \details
    Creates a new export device instance with default parameters (pseudo-constructor). 
    \returns A smart pointer to the created device instance.
  */
  static OdGsDevicePtr createObject();

  /** \details
    Enables or disables rendering devices for the export device.
    \param bEnable [in] A new flag value to be set. If it is equal to true rendering devices are enabled; otherwise rendering devices are disabled.
  */
  virtual void setRenderDevice(bool bEnable);
  
  /** \details
    Creates a rendering device compatible with a specified OdGsView object.
    \param pView [in] A raw pointer to the Gs view object.
    \returns A smart pointer to the created Gs device object.
  */
  virtual OdGsDevicePtr createRenderDevice(OdGsView* pView);
  
  /** \details
    Requests a flag that determines whether a rendering device should be created for a specified Gs view object.
    \param view [in] A Gs view object. 
    \return true if a rendering device is required; otherwise the method returns false.
  */
  virtual bool isRenderDeviceRequired(const OdGsView& view) const;
  
  /** \details
    Requests the number of render devices.
    \returns A unsigned integer value that contains the number of render devices.
  */
  virtual int numRenderDevices() { return static_cast<int>(m_renderDevices.size()); }
  
  /** \details
    Requests a rendering device with a specified index.
    \param i [in] A rendering device index.
    \returns A raw pointer to the render device at the specified index.
  */
  virtual OdGsDevice* renderDeviceAt(int i) { return m_renderDevices[i].m_pDevice; }
  
  /** \details
    Requests a layout helper object for a rendering device with a specified index.
    \param i [in] A rendering device index.
    \returns A raw pointer to the layout helper for the rendering device at the specified index.
  */
  virtual OdGsDevice* renderLayoutHelperAt(int i)
  {
    return m_renderDevices[i].m_pLayout;
  }
  
  /** \details
    Sets a new layout helper object for a render device with a specified index.
    \param i              [in] A rendering device index.
    \param pLayoutHelper  [out] A raw pointer to the placeholder for the OdGsDevice object that represents the layout helper. 
  */
  virtual void setRenderLayoutHelperAt(int i, OdGsDevice* pLayoutHelper)
  {
    m_renderDevices[i].m_pLayout = pLayoutHelper;
  }

  /** \details
    Checks whether the hidden line remove mode is on.
    \returns true if the hidden line remove mode is on; otherwise, the method returns false.
    \remarks 
    This method can be overriden in derived devices.
  */
  virtual bool isUseHLR() const { return m_bUseHLR; } 

  /** \details
    Enables/disables the hidden line remove mode.
    \param val [in] A value of the hidden remove mode to be set. If it is equal to true, the hidden line remove mode is on; otherwise the mode if off.
  */
  void setUseHLR(bool val) { m_bUseHLR = val; }

  //#9843 : Override it to modify output rendering area dimensions for shaded viewports rendering precision
  /** \details 
    Requests the current value of the render area multiplier. 
    \param width  [in] An unsigned 32-bit integer that contains the width value.
    \param height [in] An unsigned 32-bit integer that contains the height value.
    \param mode   [in] A shaded viewport export policy value. 
    \returns A double value that contains the current value of the render area multiplier. 
  */
  virtual double renderAreaMultiplier(OdUInt32 width, OdUInt32 height, ShadedViewportExportMode& mode) const;

  // Attention: there is a need to call own device methods for setting of context 
  //            before setupActiveLayoutViews() or setupLayoutViews() not after! 
  //            Only base interface methods could be called after them.

  // Called by the ODA visualization framework before rendering this view.
  // The override should call the parent version of this function, OdGsBaseVectorizeDevice::update().
  //DOM-IGNORE-BEGIN
  virtual void update(OdGsDCRect* pUpdatedRect) ODRX_OVERRIDE;
  //DOM-IGNORE-END

  /** \details
    Requests the number of bits per pixel.
    \param nColorBits     [in] A number of bits per color.
    \param bTransparency  [in] A value of the transparency flag.
    \returns A signed integer value that contains the supported number of bits per pixel.
  */
  virtual int getSupportedColorBits( int nColorBits, bool bTransparency ) const;

protected:
  ODRX_USING_HEAP_OPERATORS(OdGsBaseVectorizeDevice);
  Od2dExportGeometry& geom()
  {
    if(!m_geom)
      m_geom = createGeometry();
    ODA_ASSERT(m_geom);
    return *m_geom;
  }
  const Od2dExportGeometry& geom() const
  {
    if(!m_geom)
      m_geom = createGeometry();
    ODA_ASSERT(m_geom);
    return *m_geom;
  }
  virtual Od2dExportGeometry* createGeometry() const = 0;
  //update() helper
  virtual void calculateRenderDeviceClipping(OdGsDevice *pRenderDevice, OdGeExtents3d& ext2d, OdGeExtents3d& extDevice,
    OdIntArray& nrcCounts, OdGsDCPointArray& nrcPoints, int nDevice, bool& bDrawPicture) const;
  int unionNrcClips(int nrcContours1, const int* pNrcCounts1, const OdGsDCPointArray &nrcPoints1, int nrcContours2,
    const int* pNrcCounts2, const OdGsDCPointArray &nrcPoints2, OdIntArray &nrcCounts, OdGsDCPointArray &nrcPoints) const;
  virtual bool createRenderDevices(const OdRxObjectPtrArray& aView) { return false; }

private:
  //update() helper
  void exportAsPicture(OdGsDevice *pRenderDevice, const OdGeExtents3d& ext2d, const OdGeExtents3d& extDevice,
    const OdIntArray& nrcCounts, const OdGsDCPointArray& nrcPoints, OdUInt32 wholeWidth, OdUInt32 wholeHeight, ShadedViewportExportMode exMode);

  bool viewHasMatchingRenderDevice(const OdGsView* pView, OdUInt32 deviceIdx) const;
  void setupViewsVisibility();
 void adjustRenderMode();
  void updateRenderedViews(OdGsDCRect* pUpdatedRect);

protected:
  // Types
  enum
  {
    kExportSearchableTextInRenderedViews = OdGsBaseVectorizeDevice::kLastFlag << 1,
    kExportSearchableTextAsHiddenText = OdGsBaseVectorizeDevice::kLastFlag << 2
  };
  struct RenderDeviceInfo
  {
    OdGsDevicePtr m_pDevice;
    OdGsDevicePtr m_pLayout;
    SavedGsModelData m_data;
    RenderDeviceInfo() { }
   RenderDeviceInfo(OdGsDevice* pDevice): m_pDevice(pDevice){ }
  };
  // Members
  OdArray<RenderDeviceInfo> m_renderDevices;
  mutable Od2dExportGeometry* m_geom;
  
  /** \details 
    A data type definition of a map that stores associations between viewport stubs and rendering devices.
  */
  typedef std::map<OdDbStub *, OdUInt32> ViewportStubToRenderDeviceIdx;
  ViewportStubToRenderDeviceIdx m_arrViewports;
  bool                      m_bUseHLR;


}; // end Od2dExportDevice

/** \details
   A class that implements a view for the two-dimensional export in PDF format.
*/
class Od2dExportView :   public OdGsBaseVectorizeViewMT
{
  /** A data type definition that represents the parent class.*/
  typedef OdGsBaseVectorizeViewMT super;

public:
  /** \details 
    Definitions related to a view, not to a vectorizer.
  */
  enum 
  {
    /** An option that defines whether only the searchable text is exported.*/
    kExportSearchableTextOnly = OdGsClientViewInfo::kSetViewportId << 1,
  };

  /** \details
    Creates a new export view object with default parameters. 
  */  
  Od2dExportView();

  
  /** \details 
    Requests a device object that owns the view. 
    \returns A raw pointer to an Od2dExportDevice object.
    \remarks 
    An ExGsSimpleDevice instance that owns this view is returned through a raw pointer. 
  */
  Od2dExportDevice* device()
  {
    return (Od2dExportDevice*)super::device();
  }

  /** \details 
    Requests a device object that owns the view. 
    \returns A raw pointer to an Od2dExportDevice object.
    \remarks 
    An ExGsSimpleDevice instance that owns this view is returned through a raw pointer. 
  */
  Od2dExportDevice* device() const
  {
    return (Od2dExportDevice*)super::device();
  }

  /** \details 
    Requests a device geometry object from the view. 
    \returns A raw pointer to an Od2dExportGeometry object.
  */
  Od2dExportGeometry* deviceGeom() { return m_deviceGeom; }
  
  /** \details 
    Sets the device geometry for the view. 
    \param pGeom [in] A raw pointer to an Od2dExportGeometry object that contains the export geometry to be set to the view.
  */
  void setDeviceGeom(Od2dExportGeometry* pGeom) { m_deviceGeom = pGeom; }

  /** \details 
    Requests the output from the view object.
    \returns A reference to a geometry conveyor output object.
  */
  OdGiConveyorOutput& screenOutput() { return m_pXYProjector->output(); }

  /** \details 
    Determine whether the view is used only to output hidden searchable text.
    \returns true if the view is used only to output hidden searchable text; otherwise, the method returns false.
    \remarks 
    If only hidden searchable text is used for the output, the rest content is rendered by a rendering device and exported as a part of the viewport's image
  */
  bool exportSearchableTextOnly() const;

  /** \details 
    Sets the hidden searchable text flag value.
    This flag determines whether the view is used only to output hidden searchable text.
    \remarks 
    If only hidden searchable text is used for the output, the rest content is rendered by a rendering device and exported as a part of the viewport's image
  */
  void setExportSearchableTextOnly();

  /** \details 
    Sets view parameters. 
    \param position     [in] A camera position.
    \param target       [in] A camera target.
    \param upVector     [in] An up-vector.
    \param fieldWidth   [in] A width of the field of view.
    \param fieldHeight  [in] A height of the field of view.
    \param projection   [in] A vector that represents the projection vector.
    \remarks 
    Call this method to update conveyor if the view is perspective.
  */
  virtual void setView(const OdGePoint3d & position,
    const OdGePoint3d& target,
    const OdGeVector3d& upVector,
    double fieldWidth,
    double fieldHeight,
    Projection projection = kParallel) ODRX_OVERRIDE;

  /** \details 
    Updates the view object.
  */
  virtual void update() ODRX_OVERRIDE;

protected:
  // Called by the ODA visualization framework to give the 
  // client application a chance to terminate the current 
  // rendering process.  Returning true from this function will 
  // stop the current rendering operation. 
  bool regenAbort() const ODRX_OVERRIDE;

  // --------  Od2dExportView  --------
  //
  virtual void onTraitsModified() ODRX_OVERRIDE;

  // Retrieves the current rendering traits (color, linewidth, etc.) 
  //  and sets these properties in this device. 

  virtual void beginViewVectorization() ODRX_OVERRIDE;
  virtual void endViewVectorization() ODRX_OVERRIDE;
  virtual void loadViewport() ODRX_OVERRIDE;

  virtual bool isTransparency(OdGeVector3d screenU, OdGeVector3d screenV);

  virtual void ownerDrawDc(
    const OdGePoint3d& origin,
    const OdGeVector3d& u,
    const OdGeVector3d& v,
    const OdGiSelfGdiDrawable* pDrawable,
    bool bDcAligned = true,
    bool bAllowClipping = false) ODRX_OVERRIDE;

  virtual OdUInt32 numVectorizers() const ODRX_OVERRIDE;

  // caching

  /** \details
  Creates a new GsMetafile (cache) object.
  \remarks
  Returns a SmartPointer to the newly created object.
  */
  OdRxObjectPtr newGsMetafile() ODRX_OVERRIDE;
  /** \details
    Begins vectorization to the specified GsMetafile (cache) object.
    \param pMetafile [in]  Pointer to the metafile.
  */
  void beginMetafile(OdRxObject* pMetafile) ODRX_OVERRIDE;
  /** \details
    Ends vectorization to the specified GsMetafile (cache) object.
    \param pMetafile [in]  Pointer to the metafile.
  */
  void endMetafile(OdRxObject* pMetafile) ODRX_OVERRIDE;
  /** \details
    Plays (draws) the specified Metafile (cache) object.
    \param pMetafile [in]  Pointer to the metafile.
  */
  void playMetafile(const OdRxObject* pMetafile) ODRX_OVERRIDE;

  /** \details
    Pushes transformation matrix into MetafileTransformStack.
    \param mtx [in]  matrix.
    \param uFlags [in]  MetafileTransformFlags.
  */
  void pushMetafileTransform(const OdGeMatrix3d& mtx, OdUInt32 uFlags = 0) ODRX_OVERRIDE;
  /** \details
    Pop transformation matrix from MetafileTransformStack.
    \param uFlags [in]  MetafileTransformFlags.
  */
  void popMetafileTransform(OdUInt32 uFlags = 0) ODRX_OVERRIDE;
  /** \details
  Returns transformation matrix from metafile.
  */
  virtual const OdGeMatrix3d &metafileTransform() const { return (!m_metafileTransfStack.isEmpty()) ? OdGsBaseVectorizer::metafileTransform()
                                                                                                    : m_mfTransformStack.metafileTransform(); };
  virtual const OdGeMatrix3d &getMetafileTransform() const { return m_mfTransformStack.metafileTransform(); };

  /** \details
  Returns output for metafile.
  */
  virtual OdGiConveyorOutput& outputForMetafileGeometry() { return m_pMfPlay->output(); }
  /** \details
    Set transformation matrix for metafile output.
    \param mtx [in]  matrix.
  */
  virtual void setTransformForMetafileGeometry(const OdGeMatrix3d& mtx);
  /** \details
  Returns transformation matrix for metafile output.
  */
  virtual OdGeMatrix3d getTransformForMetafileGeometry() const;

  /** \details
  Returns if model cache is enabled.
  */
  inline bool isGsCacheEnabled() const
  {
    return (view().cachedDrawables() != 0 && device()->supportBlocks());
  };

  bool isPlayingMetafile() const { return m_bPlayingMetafile; }

  /** \details
  Adjusts RenderMode for current View
  */
  virtual void adjustRenderMode();

  /** \details
  Returns if metafile used for geometry
  */
  virtual bool useMetafileAsGeometry() const { return isGsCacheEnabled(); }

public:
  /**Perspective clipper object.*/
  OdGiOrthoClipperExPtr   m_pPerspPrepClip;
  /**Viewport clipper object.*/
  OdGiOrthoClipperExPtr   m_pViewportClip;
  /**Projection on the XY plane.*/
  OdGiXYProjectorPtr      m_pXYProjector;
  
  /** A Xform object for the perspective camera.*/
  OdGiXformPtr                   m_pPerspXform;
  /**  Perspective processor object.*/
  OdGiPerspectivePreprocessorPtr m_pPerspPrepr;

  /** Hidden lines remover object.*/
  OdGiHLRemoverPtr m_pHLRemover;

protected:
  OdGiMetafilerPtr           m_pMetafiler;
  OdGiXformPtr               m_pMfPlay;
  OdGiConveyorConnector      m_mfPlayEntryPoint;
  MetafileTransformStack     m_mfTransformStack;
  Od2dExportGeometry* m_deviceGeom;
  bool m_bPlayingMetafile;
  friend class Od2dExportDevice; //??
}; // end Od2dExportView 

} // TD_PDF_2D_EXPORT namespace

#endif  // _2DEXPORTDEVICE_INCLUDED_
