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
// Pdf2dExportDevice.h: definition of the PDF2dExportGeometry, PDF2dExportDevice classes.
//
//////////////////////////////////////////////////////////////////////

#ifndef _PDF_2D_EXPORT_DEVICE_INCLUDED_
#define _PDF_2D_EXPORT_DEVICE_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "2dExportDeviceForPdfExport.h"
#include "OdPlatform.h"
#include "Gi/GiPlotGenerator.h"
#include "Gs/GsBlockRefNodeDesc.h"

#include "PdfExportParamsHolder.h"
#include "PdfFont.h"
#include "PdfAnnotationDictionary.h"
#include "Pdf2PrcExportParams.h"
#include "DbBaseHostAppServices.h"

//////////////////////////////////////////////////////////////////////
/** \details
  Contains declarations for 2D PDF Export.
  <group OdExport_Classes> 
*/
namespace TD_PDF_2D_EXPORT
{

#define PDF_FROZEN_LAYER "||frozen"
#define PDF_FROZEN_LAYER_SIZE 8

/** \details
  A structure that stores the device point information.
*/
struct PDFDevicePoint {
  /**X coordinate of the device point.*/
  double x; 
  /**Y coordinate of the device point.*/
  double y; 
};

/** \details 
  A structure that stores information about view extents.
*/
struct ViewExtents {
  /**An index of the view.*/
  int m_viewIdx;
  /**An object that represents the view extents.*/
  OdGeExtents3d m_extents;
};

/** \details 
A structure that stores data about current and previous 2D PDF traits.
*/
struct PDF2dTraitsSaver
{
public:
  /**A set of traits flags.*/
  OdUInt32 m_traitsFlags;
  /**Current traits: color reference.*/
  ODCOLORREF  m_curRGB;
  /**Current traits: color index.*/
  OdUInt16    m_curColorIndex;
  /**Current traits: layer name.*/
  OdString    m_curLayerName;
  /**Current traits: cap style.*/
  PDFLineCap  m_curCapStyle;
  /**Current traits: join style.*/
  PDFLineJoin m_curJoinStyle;
  /**Current traits: line weight.*/
  double      m_curLineWeight;
  /**Previous traits: color reference.*/
  ODCOLORREF  m_prevRGB;
  /**Previous traits: color index.*/
  OdUInt16    m_prevColorIndex;
  /**Previous traits: layer name.*/
  OdString    m_prevLayerName;
  /**Previous traits: cap style.*/
  PDFLineCap  m_prevCapStyle;
  /**Previous traits: join style.*/
  PDFLineJoin m_prevJoinStyle;
  /**Previous traits: line weight.*/
  double      m_prevLineWeight;
};

/** \details
  This class implements the two-dimensional export geometry.
*/
class PDF2dExportGeometry: public Od2dExportGeometry, public OdGiPlotGenerator::EllipseOut
{
  //DOM-IGNORE-BEGIN
  typedef Od2dExportGeometry super;
  // Members
  //
private:

  PdfExportParamsHolderPointer       m_pParamsHolder; // Reference to the /PdfExportParamsHolder/ class instance, used for creating PDF document.
  PDFIContentCommands               *m_OutputCCStream; // Pointer to the /content commands stream/ for the PDF document
  static PDFDummyContentStream       m_DummyCCStream; // Pointer to the /content stream/ for the PDF document
  PDFPageDictionary                 *m_currentPdfPage;
  bool                               m_bDarkenGSSet;
//DOM-IGNORE-END

public:
  /**Added to unconditional clipping of 3d solids which cannot be exported via vectorizer.*/
  bool                               m_bRasterClipping; 
  /**Calculated from m_clipPoints.*/
  OdGeExtents2d                      m_paperClip; 
  /**lineweight multiplier for Z2E mode.*/
  double                             m_LwToDcScale; 
  /**A prc export context.*/
  std::map<OdUInt32, std::pair<OdRxObjectPtr, ViewExtents> >  m_prc_context; 

  /** \details
    Returns the pointer to the content commands stream for the export device.
    \returns A raw pointer to the object that represents the content commands stream.
  */
  PDFIContentCommands *cc() { return m_OutputCCStream; }

  /** \details
    Returns the pointer to the current page.
    \returns A raw pointer to the page dictionary object.
  */
  PDFPageDictionary *currentPdfPage() { return m_currentPdfPage; }

  /** \details
    Retrieves the PDF document associated with the export device.
    \returns A reference to the document that is associated with the export device. The document can be modified in the calling subroutine.
    \remarks
    The PDF document reference is returned from the CPdfExportImpl class instance incapsulated into the export device.
  */
  PDFDocument &document() { return m_pParamsHolder->document(); }
  
  /** \details
    Retrieves the PDFType3Optimizer object associated with the export device.
    \returns A non-constant reference to the PDFType3Optimizer object therefore it can be modified in the calling subroutine.
    \remarks
    Type optimization options for the PDF export are stored in the CPdfExportImpl class instance incapsulated into the export device.
  */
  PDFType3Optimizer &getFontType3Optimizer() { return m_pParamsHolder->getType3Optimizer(); }

  /** \details 
    Outputs the face of a tessellated shell within the export device. 
    \param faceListSize [in] A number of entries in the face list.
    \param pFaceList    [in] A raw pointer to the list of numbers that define the face.  
    \param pNormal      [in] A raw pointer to the normal vector for the face. 
  */
  virtual void shellFaceOut( OdInt32 faceListSize, const OdInt32* pFaceList, const OdGeVector3d* pNormal ) ODRX_OVERRIDE;
  
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
    const OdGeVector3d& u,      // normal
    const OdGeVector3d& v,      // direction
    const OdChar* msg, OdInt32 length, bool raw,
    const OdGiTextStyle* pTextStyle,
    bool  bBox,
    const Od2dFont* pFont,
    const OdArray<OdUInt16> *pUnicode) ODRX_OVERRIDE;
  
  /** \details 
    Crops a specified image.
    \param pImg         [in] A raw pointer to a raster image object to be cropped.
    \param u            [in] A u-vector. 
    \param v            [in] A v-vector.
    \param cropArea     [in] A crop area. 
    \param originPoint  [in] An origin point.
    \returns A smart pointer to a raster object that is created as a result of the cropping operation.
  */
  OdGiRasterImagePtr cropImage(const OdGiRasterImage* pImg, const OdGeVector2d& u, const OdGeVector2d& v, OdGeExtents2d& cropArea, OdGePoint2d& originPoint);
  
  /** \details 
    Rotates a specified image.
    \param angRad   [in] A rotation angle in radians.
    \param pImg     [in] A raw pointer to a raster image. 
    \param moveOrig [in] A rotation vector.
    \returns A smart pointer to a raster object that represents the rotated image.
  */
  OdGiRasterImagePtr rotateImage(double angRad, const OdGiRasterImage* pImg, OdGeVector2d& moveOrig);
  
  /** \details 
    Sets the paper box for the export device.
    \param box [in] A rectangle object that represents the paper box to be set.
  */
  void setPaperBox(const OdGsDCRect& box);

  /** \details 
    Starts the output of the geometry information into the export device. 
    \param bg [in] A background color that is used for the output.
    \remarks 
    This method is called by the export device object.
  */
  void beginOutput(ODCOLORREF bg);
  
  /** \details 
    Finishes the output of the geometry information into the export device. 
    \remarks 
    This method is called by the export device object.
  */
  void endOutput();

public:

  /** \details
    Retrieves the font optimizer object for the export device.
    \returns A non-constant reference to the PDFFontOptimizer object associated with the export device.
    \remarks
    Font optimizer object is stored in the CPdfExportImpl class instance encapsulated into the export device.
    Since the optimizer object returns through a non-constant reference the optimizer object can be modified within a calling subroutine.
  */
  PDFFontOptimizer &getFontOptimizer() { return m_pParamsHolder->getFontOptimizer(); }

  /** \details
    Defines blend modes and transparency.
  */
  enum BlendMode
  {
    /**Default mode - overwrite colors.*/
    kUndefined     = 0x0000, 
    /**Set merge lines mode.*/
    kDarken        = 0x0001, 
    /**Restore merge lines mode.*/
    kRestoreDarken = 0x0002, 
    /**Transparency mode.*/
    kTransparency  = 0x0004, 
  };

  /** \details
    Defines acceptable polygon fill rules.
  */
  enum PolygonFillRules
  {
    /**Default value. Fill the path, using the nonzero winding number rule to determine the region to fill. 
    Any subpaths that are open are implicitly closed before being filled.
    */
    kFillNonzeroRule     = 0x0000, 
    /**Even-odd fill rule - "f*" Fill the path, using the even-odd rule to determine the region to fill.*/
    kFillEvenOddRule     = 0x0001, 
    /**No fill.*/
    kNoFill              = 0x0002, 
    /**Close, fill, and then stroke the path, using the nonzero winding number rule to determine the region to fill.*/
    kFillStrokeCloseRule = 0x0004  
  };

  /** \details
    Retrieves the default fill rule for the polygons that can be output to the export device.
    \returns A value of the PolygonFillRules enumeration that represents the default fill rule for the polygons.
  */
  static PolygonFillRules defaultFillRule() { return kFillStrokeCloseRule; }

//DOM-IGNORE-BEGIN
private:
  bool              m_bGraphStateFixed; // Shows if the graph state is fixed.

  bool              m_bOnePointPoly; // Shows if the polygon consists of one point.
  PDFDevicePoint    m_LastPoint; // Last point processed by the export device.
  OdUInt32          m_num; // Points count.
  PDFDevicePoint    m_points[6]; // Static array of the points which the polygon consists of

  PDFNamePtr        DWG_PALETTE_NAME; // Name of the pallete currently used by the export device.
  PDFNamePtr        PDF_OC_NAME; // Name of the PDF document used by the export device.
  bool              m_bDwgPaletteNeeded;//shows if indexed dwg palette is necessary

  bool              m_bRGBActive; // Shows if the RGB mode is active.
  ODCOLORREF        m_curRGB; // Contains the current RGB scheme used for export device.
  OdUInt16          m_curColorIndex; // Current colour index used for export device.
  ODCOLORREF        m_curSecondaryColorRGB; // Contains the current secondary color RGB scheme used for export device.
  OdUInt16          m_curSecondaryColorIndex; // Current secondary color index used for export device.

  OdUInt16          m_hatchDPI;       // Export device resolution for hatch exported as bitmap(dot per inch).
  OdUInt16          m_bwBitmapDPI;    // Export device resolution for bw bitmap(dot per inch).
  OdUInt16          m_colorBitmapDPI; // Export device resolution for color bitmap(dot per inch).
  
  // layers support functionality
  OdString          m_curLayerName; // Name of the current layer used by the export device.
  bool              m_LayerOpen; // Shows if the current layer is open.

  bool              m_stubLayerCreated;//create stub layer if pdf has hyperlinks to avoid incorrect work of Adobe Reader (workaround)

  double            m_lineWeight; // Weight of the line used for painting by the export device.
  double            m_savedLineWeight; // Lineweight to keep before draw hatch contour.
  PDFLineCap        m_CapStyle;   // Line cap style
  PDFLineJoin       m_JoinStyle;  // Line join style

  PolygonFillRules  m_fillRule; // Polygon fill rules used for painting by the export device.
  FrozenLayerMap m_frozenLayers;

  int m_stateDrawingContour; // the contour drawing is in progress, don't finish each curve with 'S' command

  bool              m_bHatchDrawingMode; //set for draw hatch, to avoid downscaling if hatchDPI > bitmapDPI
  OdAnsiString      m_currentTransparencyState;//current transparency graphic state
  OdGsDCRect        m_paperBox; //size of the paper (now using for filling pdf page background as application background);
  bool              m_bRecordingEnabled;
protected:

  virtual bool transformImage(OdGiRasterImagePtr pRastIn, OdGiRasterImagePtr& pRastOut,
    ODCOLORREF backgroundColor) const ODRX_OVERRIDE;
  OdResult makeBgTransparent(OdUInt8Array &buffer, OdInt32 width, OdInt32 height, ODCOLORREF backgroundColor, OdGiRasterImagePtr &pRast) const;
  bool applyLayerToAnnotation(const OdString& layer, PDFAnnotationDictionaryPtr pDict);

  /** \details
    Returns if it is needed to start new polyline for rendering polygone.

    \remarks
    Returns true if new polyline is needed, false if the other case.
  */
  bool needNewPolyline() const;
  
  /** \details
    Determines whether the /segment of polygone/ represented by the specified point is duplicate.

    \remarks
    Returns true if the segment is dublicated and false in the other case.

    \param LastPoint [in]  A reference to the PDFDevicePoint class instance representing the point.
  */
  bool isDublicatedSegment(const PDFDevicePoint &LastPoint) const;
  
  /** \details
    Continues the polyline starting from the specified point.

    \remarks
    Polyline is continued from the specified instance of the PDFDevicePoint class.

    \param LastPoint [in]  A point from which the polyline should be continued.
  */
  void ContinuePolyline(const PDFDevicePoint &LastPoint);
  
  /** \details
    Saves the current state of the graph.

    \remarks
    Parameter value determines to what point the graph should be saved.

    \param LastPoint [in]  A point for saving.
  */
  void saveGraphState(const PDFDevicePoint& LastPoint);
  
  /** \details
    Saves last point of the polyline.

    \param LastPoint [in]  A point to save.
  */
  void saveLastPoint(const PDFDevicePoint& LastPoint);

  /** \details
    Converts color to grayscale.

    \param rgb [in]  color to convert.
  */
  void convertColorToGrayscale(ODCOLORREF& rgb);
  
  /** \details
    Processing the changing of the graph state.

    \remarks
    Returns true if and only if successful.
    The /dictionary key/ is the string that is the combination of the /book name and colour name/ joined by the dollar '$' symbol

    \param dictionaryKey [in]  Dictionary keyword.   
  */
  void GraphStateChanged();
  
  /** \details
    Sets the /book name and colour name/ for the /dictionary keyword/.

    \remarks
    Returns true if and only if successful.
    The /dictionary key/ is the string that is the combination of the /book name and colour name/ joined by the dollar '$' symbol

    \param dictionaryKey [in]  Dictionary keyword.   
  */
  void StartNewPolyline(const PDFDevicePoint &LastPoint);
  
  /** \details
    Sets the /book name and color name/ for the /dictionary keyword/.

    \remarks
    Returns true if and only if successful.
    The /dictionary key/ is the string that is the combination of the /book name and colour name/ joined by the dollar '$' symbol

    \param dictionaryKey [in]  Dictionary keyword.   
  */
  void ClosePolyline();

  /** \details
    Transoforms clip of the raster image into the instance of the OdGeMatrix2d class.

    \remarks
    Transforms specified raster image starting from the origin point using two vectors, representing X-axis and Y-axis of the coordinate system. Transformation can be translation, rotation and scaling. 

    \param pImg [in]  Pointer to raster image (OdGiRasterImage) that should be transformed.
    \param origin [in]  Point from which transformation starts.
    \param u [in]  Vector, representing X-axis.
    \param v [in]  Vector, representing X-axis.
  */
  OdGeMatrix2d createImageClipTransform( const OdGiRasterImage* pImg 
    ,const OdGePoint3d& origin
    ,const OdGeVector3d& u
    ,const OdGeVector3d& v
    );
	
  /** \details
    Transforms the raster image into the instance of the OdGeMatrix2d class.

    \remarks
    Transforms specified raster image starting from the origin point using two vectors, representing X-axis and Y-axis of the coordinate system. Transformation can be translation, rotation and scaling. 

    \param pImg [in]  Pointer to raster image (OdGiRasterImage) that should be transformed.
    \param origin [in]  Point from which transformation starts.
    \param u [in]  Vector, representing X-axis.
    \param v [in]  Vector, representing X-axis.
  */
  OdGeMatrix2d createImageTransform( const OdGiRasterImage* pImg 
    ,const OdGePoint3d& origin
    ,const OdGeVector3d& u
    ,const OdGeVector3d& v
    );

  /** \details
    Open /layer's bracket/ with the specified name.

    \param layer_name [in]  Name of the layer.
  */
  void OpenLayerBracket(const OdString &layer_name);
  
  /** \details
    Close /layer's bracket/, previously opened with the /OpenLayerBracket()/.
  */
  void CloseLayerBracket();

  PDFResourceDictionaryPtr getResourceDictionary();
//DOM-IGNORE-END

public:
  /** \details 
    Put the transformation matrix into the content stream to set the necessary vector resolution.
  */
  void dc_mx();
  
  /** \details 
    Opens a frozen layer with a specified name.
    \param layer_name [in] A string that contains the layer name.
  */
  void open_Frozen_Layer(const OdString &layer_name);
  
  /** \details 
    Closes the frozen layer.;
  */
  void close_Frozen_Layer();

  /** \details 
    Create a new instance of the export geometry with a specified Gs device. 
    \param refDevice [in] A Gs device object associated with the geometry object.
  */
  PDF2dExportGeometry(const OdGsBaseVectorizeDevice& refDevice);

  /** \details 
    Retrieves the type of export device the geometry object is associated with. 
    \returns An unsigned 32-bit integer value that represents the device type.
  */
  virtual OdUInt32 getDeviceType() const ODRX_OVERRIDE
  {
    return DeviceType(kPDFDevice | kSupport2dCircle | kSupport2dEllipse);
  }

  /** \details
    Enables or disables output methods.
    \param bEnable [in]  A flag that determines whether the output methods are enabled (if true) or disabled (if false). By default the value is true.
    \param bZ2E    [in]  A flag that determines whether the method is called for the Zoom to Extents case.
    \remarks
    This method is used to prevent a duplication of traits data in the case of Zoom to Extents call and other cases.
  */
  void enableRecording(bool bEnable = true, bool bZ2E = true);

  /** \details 
    Sets PDF content stream. 
    \param pStream [in] A raw pointer to the stream object.
    \returns A raw pointer to the PDF content stream object.
  */
  PDFIContentCommands* setPdfContentStream(PDFIContentCommands* pStream);
//   PDFIContentCommands* getPdfContentStream()
//   {
//     return m_pParamsHolder->ContentCommands();
//   };

  /** \details 
    Retrieves whether output methods are enabled or disabled.
    \returns true if output methods are enabled; otherwise, the method returns false.
  */
  bool recordingEnabled();

  /** \details
    Retrieves a PDF block with a specified name. 
    \param blockName [in] A string that contains the block name.
    \returns A smart pointer to the found block.
    \remarks
    If the block has not been found the method returns the null pointer.
  */
  PDFXObjectFormPtr findBlock(const OdString& blockName);

  /** \details
    Creates a new PDF block with a specified name. 
    \param blockName [in] A string that contains the block name.
    \returns A smart pointer to the created block.
    \remarks
    If the block has not been created the method returns the null pointer.
  */
  PDFXObjectFormPtr createBlock(const OdString& blockName);

  /** \details
    Places a block into the document.
    \param blockName  [in] A string that contains the block name.
    \param mat        [in] A transformation matrix.
    \param pXobj      [in] A smart pointer to the parent block.
    \returns true if the block has been added successfully; otherwise, the method returns false.
  */
  bool placeBlock(const OdString& blockName, const OdGeMatrix3d& mat, PDFXObjectFormPtr pXobj);

  /** \details
    Sets the image resolution for hatches exported as bitmaps.
    \param dpi [in]  A resolution value to be set.
    \remarks
    Resolution is represented in pixels per inch (dpi) units.
  */
  void setHatchDPI(OdUInt16 dpi) {
    m_hatchDPI = dpi;
  }

  /** \details
    Sets a new value of the hatch drawing mode.
    \param bMode [in] A new value of the mode to be set. If it is equal to true, the hatch drawing mode is enabled; otherwise it is disabled.
  */
  void setHatchDrawingMode(bool bMode) {
    m_bHatchDrawingMode = bMode;
  }

  /** \details
    Sets the image resolution for monchrome (black-white) bitmaps.
    \param dpi [in]  A resolution value to be set.
    \remarks
    Resolution is represented in pixels per inch (dpi) units.
  */
  void setBwBitmapDPI(OdUInt16 dpi) {
    m_bwBitmapDPI = dpi;
  }

  /** \details
    Sets the image resolution for color bitmaps.
    \param dpi [in]  A resolution value to be set.
    \remarks
    Resolution is represented in pixels per inch (dpi) units.
  */
  void setColorBitmapDPI(OdUInt16 dpi) {
    m_colorBitmapDPI = dpi;
  }

  /** \details 
    Checks whether a specified layer is frozen.
    \param layerName [in] A string that contains the layer name.
    \returns true if the layer is frozen; otherwise, the method returns false.
  */
  bool isFrozenLayer(const OdString &layerName) const;

  /** \details 
    Sets frozen layers. 
    \param frozenLayers [in] A map that contains layers, which are frozen.
  */
  void setFrozenLayers(const FrozenLayerMap &frozenLayers) {
    m_frozenLayers = frozenLayers;
  }

  /** \details
    Returns the image resolution for hatches exported as bitmaps.
    \returns An unsigned 16-bit integer that contains the dot-per-inch (dpi) resolution.
  */
  OdUInt16 getHatchDPI() const {
    return m_hatchDPI;
  }

  /** \details
    Returns the image resolution for monochrome (black and white) bitmaps.
    \returns An unsigned 16-bit integer that contains the dot-per-inch (dpi) resolution.
  */
  OdUInt16 getBwBimapDPI() const {
    return m_bwBitmapDPI;
  }

  /** \details
    Returns the image resolution for color bitmaps.
    \returns An unsigned 16-bit integer that contains the dot-per-inch (dpi) resolution.
  */
  OdUInt16 getColorBimapDPI() const {
    return m_colorBitmapDPI;
  }

  /** \details
    Requests PDF export parameters.
    \returns An instance of the PDFExportParams class that contains export parameters;
    \remarks 
    The method returns a constant reference to the export parameters object therefore it can't be modified.
  */
  const PDFExportParams& exportParams() const
  {
    return m_pParamsHolder->getParams();
  }

  /** \details
    Requests PDF export parameters.
    \returns An instance of the PDFExportParams class that contains export parameters;
    \remarks 
    The method returns a reference to the export parameters object therefore it can be modified.
  */  
  PDFExportParams& exportParams()
  {
    return m_pParamsHolder->getParams();
  }

  // pdf input flags auxiliary methods
  /** \details
    Determines if the output PDF document allows embedded True Type fonts.
    \returns true if the document associated with the export device supports embedded True Type fonts and false in the other case.
  */
  bool AllowEmbededFonts() const 
  {
    return !isTTFTextGeometry() && GETBIT(m_pParamsHolder->getParams().exportFlags(), PDFExportParams::kEmbededTTF);
  }

  /** \details
    Determines if the output PDF document allows embedded True Type fonts optimization.
    \returns true if the document associated with the export device supports optimized embedded True Type fonts and false in the other case.
  */
  bool AllowEmbededOptimizedFonts() const 
  {
    return !isTTFTextGeometry() && GETBIT(m_pParamsHolder->getParams().exportFlags(), PDFExportParams::kEmbededOptimizedTTF);
  }

  /** \details
    Determines if the text with True Type fonts should be represented with simple geometry primitives in the output PDF document. 
    \returns true if the text with True Type fonts is represented with simple geometry primitives and false in the other case.
  */
  bool isTTFTextGeometry() const
  {
    return GETBIT(m_pParamsHolder->getParams().exportFlags(), PDFExportParams::kTTFTextAsGeometry);
  }

  /** \details
    Determines if the text with Shape File Index (SHX) fonts should be represented with simple geometry primitives in the output PDF document. 
    \returns true if the text with Shape File Index (SHX) fonts is represented with simple geometry primitives and false in the other case.
  */
  bool isSHXTextGeometry() const
  {
    return GETBIT(m_pParamsHolder->getParams().exportFlags(), PDFExportParams::kSHXTextAsGeometry);
  }
  
  /** \details
    Determines if the geometry is simplified to reduce the output file size.
    \returns true if the export device optimizes geometry and false in the other case.
  */
  bool isSimpleGeomOptimizationEnabled() const
  {
    return GETBIT(m_pParamsHolder->getParams().exportFlags(), PDFExportParams::kSimpleGeomOptimization);
  }

  /** \details
    Determines whether the simulation of frozen layers is applied in the output PDF document.
    \returns true if the frozen layers simulation is enabled; otherwise, the method returns false.
  */
  bool frozenLayerSimulationEnabled() const
  {
    return m_frozenLayers.size() != 0;
  }

  /** \details
    Determines if layers are supported by the export device.
    \returns true if layers are supported by the export device or false in the other case.
  */
  bool isLayersSupported() const
  {
    return GETBIT(m_pParamsHolder->getParams().exportFlags(), PDFExportParams::kEnableLayers);
  }

  /** \details
    Determines if inactive ("off") layers are supported by the export device.
    \returns true if inactive layers are supported and false in the other case.
  */
  bool isOffLayersEnabled() const
  {
    return GETBIT(m_pParamsHolder->getParams().exportFlags(), PDFExportParams::kIncludeOffLayers);
  }

  /** \details
    Determines if the &quot;global&quot; indexed palette is required in the output PDF document.
    \returns true if the &quot;global&quot; indexed palette is required and false in the other case.
  */
  bool isDWGPaletteNeeded() const
  {
    return m_bDwgPaletteNeeded;
  }


  //  ----- Od2dExportGeometry methods -----

  // writing process
  
  /** \details
    Pushes a clip into the export device.
    \param nrcContours  [in] A number of contours.
    \param pNrcCounts   [in] A raw pointer to an array that contains count of points for each contour.
    \param nrcPoints    [in] An array of points that form contours.
  */
  void dc_pushClip(int nrcContours, const int* pNrcCounts, const OdGsDCPointArray &nrcPoints);
  
  /** \details
    Pops a clip from the export device.
  */
  void dc_popClip();
  
  /** \details
    Writes a polyline into the export device.
    \param nPts   [in] A number of points that represent verticies of the polyline.
    \param points [in] A raw pointer to the array of points that represent verticies of the polyline.
  */
  void dc_polyline( OdUInt32 nPts, const OdGePoint2d* points );
  
  /** \details
    Writes a polygon into the export device.
    \param nPts   [in] A number of points that represent verticies of the polygon.
    \param points [in] A raw pointer to the array of points that represent verticies of the polygon.
  */
  void dc_polygon ( OdUInt32 nPts, const OdGePoint2d* points );
  
  /** \details
    Fills polygons that were written into the export device according to the fill rule.
    To set the fill rule, use the setFillRule() method.
  */  
  void dc_fill();
  
  /** \details
    Writes a circle into the export device.
    \param ellipse [in] An OdGeEllipArc3d object that represents the circle.
  */
  void dc_circle  ( const OdGeEllipArc3d& ellipse );
  
  /** \details
    Writes an ellipse into the export device.
    \param ellipse [in] An OdGeEllipArc3d object that represents the ellipse.
  */
  void dc_ellipse ( const OdGeEllipArc3d& ellipse );
  
  /** \details
    Writes a non-uniform rational B-splines (NURBS) into the export device.
    \param nurb [in] An OdGeNurbCurve2d class instance that contains NURBS data.
  */
  void dc_nurb(const OdGeNurbCurve2d& nurb );
  
  /** \details
    Writes a gouraud polytriangle into the export device.
    \param pVertexList  [in] A raw pointer to the array of points that represent verticies.
    \param faceListSize [in] A size of the list of faces.
    \param pFaceList    [in] A raw pointer to the array of face veticies indexes.
    \param pColors      [in] A raw pointer to the array of colors. 
  */
  void dc_gouraud_polytriangle(
                        const OdGePoint3d* pVertexList,
                        OdInt32 faceListSize,
                        const OdInt32* pFaceList,
                        const OdCmEntityColor* pColors );

  /** \details
    Writes a raster image into the export device.
    \param origin       [in] An origin point of the raster image.
    \param u            [in] A vector that represens the X-axis.
    \param v            [in] A vector that represens the Y-axis.
    \param pImg         [in] A raw pointer to the image object. 
    \param uvBoundary   [in] A raster image boundary represented with a raw pointer to an array of points. This parameter may not be NULL.
    \param numBoundPts  [in] A number of boundary points.
    \param transparency [in] A transparency flag for the image object.
    \param brightness   [in] A brightness value.
    \param contrast     [in] A contrast value.
    \param fade         [in] A fade value.
    \param entityColor  [in] An entity color.
  */
  void dc_raster_image( 
          const OdGePoint3d& origin,
          const OdGeVector3d& u,
          const OdGeVector3d& v,
          const OdGiRasterImage* pImg, // image object
          const OdGePoint2d* uvBoundary, // may not be null
          OdUInt32 numBoundPts,
          bool transparency,
          double brightness,
          double contrast,
          double fade,
          ODCOLORREF entityColor);
    
  /** \details
    Writes a raster image into the export device.
    \param pRaster  [in] A smart pointer to a raster image.
    \param imgExts  [in] A raster image extents.
  */
  void dc_raster_image( OdGiRasterImagePtr pRaster, 
                        const OdGeExtents2d& imgExts);

  /** \details
    Writes a line weight value into the export device.
    \param lineWeight [in]  A width of the line.
  */ 
  void dc_lineWeight (double lineWeight);
  
  /** \details
    Writes a color value into the export device.
    \param rgb [in] A color value.
  */ 
  void dc_color(ODCOLORREF rgb);
  
  /** \details
    Writes a color value into the export device.
    \param index [in] A color index.
  */ 
  void dc_color(OdUInt16 index);
  
  /** \details
    Writes a layer into the export device.
    \param layer_name [in]  A string that contains the layer name.
    \param bClose     [in] A close flag value.
  */ 
  void dc_layer(const OdString &layer_name, bool bClose);

  // OdAnsiString dc_shx_font(const OdGiTextStyle& pTextStyle, PDFFontPtr *pOutFont);
  
  /** \details
    Writes a true type font data into the export device.
    \param pTextStyle [in]  A text style object.
    \param pOutFont   [in] A PDF font object represented with a raw pointer to the smart pointer to a PDFFont object.
    \returns A string that contains the font name.
  */ 
  OdAnsiString dc_truetype_font(const OdGiTextStyle& pTextStyle, PDFFontPtr *pOutFont);
  
  /** \details
    Writes a specified text into the export device according to passed parameters.
    \param fontName   [in] An ANSI string that contains the name of the font, used for drawing the text.
    \param position   [in] A position where the drawing of the text starts.
    \param u          [in] A vector that represens the X-axis.
    \param v          [in] A vector that represens the Y-axis.
    \param msg        [in] A text message to be written.
    \param length     [in] A length of the drawing message.
    \param pTextStyle [in] A text style object to applied for the drawing of the text.
    \param charSpaces [in] A double array that contains char spaces.
  */
    void dc_drawtext(const OdAnsiString &fontName, const OdGePoint2d& position, const OdGeVector2d& u, const OdGeVector2d& v, const char& msg, OdInt32 length, const OdGiTextStyle& pTextStyle, const OdDoubleArray& charSpaces);
  
  /** \details
    Writes a specified Unicode text into the export device according to passed parameters.
    \param fontName   [in] An ANSI string that contains the name of the font, used for drawing the text.
    \param pos        [in] A position where the drawing of the text starts.
    \param u          [in] A vector that represens the X-axis.
    \param v          [in] A vector that represens the Y-axis.
    \param pUnicode   [in] A raw pointer to the array of symbol codes. This array represents the Unicode text message to be written.
    \param pTextStyle [in] A text style object to applied for the drawing of the text.
    \param raw        [in] A raw flag value.
  */
  void dc_drawunicodetext(const OdAnsiString &fontName, const OdGePoint2d& pos, const OdGeVector2d& u, const OdGeVector2d& v, OdArray<OdUInt16>* pUnicode, const OdGiTextStyle& pTextStyle, bool raw);

  /** \details
    Sets the line cap and line join styles for the export device.
    \param linecap  [in] A line cap style to be set.
    \param linejoin [in] A line join style to be set.
  */
  void setCapJoin(PDFLineCap linecap, PDFLineJoin linejoin);

  //  ----- PDF2dExportDevice methods -----

  /** \details
    Sets a export device parameters that defines the export device context.
    \param params_holder [in]  A pointer to a PdfExportParamsHolder class instance that stores parameter values to be used for the context installation.
    \remarks
    It is necessary to call own device methods for setting of context BEFORE (but not after) call of the setupActiveLayoutViews() or the setupLayoutViews() methods.
    Only methods of the base interface class can be called after.
  */
  void setParams(PdfExportParamsHolderPointer params_holder);

  /** \details
    Starts the optimization of the graphical primitives for the export device.
  */
  virtual void StartOptimizator();

  /** \details
    Stops the optimization of the graphical primitives for the export device.
  */
  virtual void StopOptimizator();

  /** \details
    Sets the secondary color for the export device.
    \param rgb [in] An ODCOLORREF value that contains the secondary color value to be set.
  */  
  void set_SecondaryColor(ODCOLORREF rgb);
  
  /** \details
    Sets the secondary color for the export device.
    \param colorIndex [in] A color index value that contains the secondary color value to be set.
  */
  void set_SecondaryColorIndex(OdUInt16 colorIndex);

  /** \details
    Sets the color for the export device.
    \param rgb [in] An ODCOLORREF value that contains the color value to be set.
  */  
  void set_Color(ODCOLORREF rgb);
  
  /** \details
    Sets the color for the export device.
    \param colorIndex [in] A color index value that contains the color value to be set.
  */
  void set_ColorIndex(OdUInt16 colorIndex);
  
  /** \details
    Sets the line weight for the export device.
    \param lineWeight [in] A line weight value to be set.
  */
  void set_LineWeight(double lineWeight);
  
  /** \details
    Sets the layer for the export device.
    \param layer [in] A layer to be set represented with a raw pointer to a stub object.
    \param pCtx  [in] A raw pointer to the context object.
  */
  void set_Layer(OdDbStub* layer, OdGiContext* pCtx);

  /** \details
    Processes a specified raster image by the export device.
    
    \param origin       [in] A starting point.
    \param u            [in] An X-axis vector.
    \param v            [in] An Y-axis vector.
    \param pImg         [in]  A raw pointer to the raster image object.
    \param uvBoundary   [in]  Boundary of the processing area (may not be null).
    \param numBoundPts  [in] A raw pointer to point object that defines the bounds of the image.
    \param transparency [in] An image transparency flag value (by default image is not transparent, i.e. the value is false).
    \param brightness   [in] A brightness value of the image (by default the value is equal to 50.0).
    \param contrast     [in] A contrast value of the image (by default the value is equal to 50.0).
    \param fade         [in] A fading level of the image (by default the value is equal to 0.0).

    \remarks
    The method processes the raster image starting from the specified point, using two OdGeVector instancies as X-axis and Y-axis according to other specified parameters.
  */
  void rasterImageProc(
            const OdGePoint3d& origin,
            const OdGeVector3d& u,
            const OdGeVector3d& v,
            const OdGiRasterImage* pImg, 
            const OdGePoint2d* uvBoundary, 
            OdUInt32 numBoundPts,
            bool transparency = false,
            double brightness = 50.0,
            double contrast = 50.0,
            double fade = 0.0);

  /** \details
    Processes a specified meta file by the export device.
    
    \param origin         [in] A starting point.
    \param u              [in] An X-axis vector.
    \param v              [in] An Y-axis vector.
    \param pMetafile      [in] A raw pointer to the meta file object.
    \param bDcAligned     [in] A parameter that is reserved for future use.
    \param bAllowClipping [in] A parameter that is reserved for future use.
    
    \remarks
    The method processes the meta file starting from the specified point, using two OdGeVector instancies as X-axis and Y-axis according to other specified parameters.
  */
	void metafileProc(
            const OdGePoint3d& origin,
            const OdGeVector3d& u,
            const OdGeVector3d& v,
            const OdGiMetafile* pMetafile,
            bool bDcAligned = true,       
            bool bAllowClipping = false); 

  /** \details
    Processes a specified text by the export device.
    
    \param position   [in] A starting point.
    \param u          [in] An X-axis vector.
    \param v          [in] An Y-axis vector.
    \param msg        [in] A text to process.
    \param length     [in] A text message length.
    \param raw        [in] A raw flag value. 
    \param pTextStyle [in] A raw pointer to the text style object associated with the text.
    \param pExtrusion [in] A raw pointer to the text extrusion object.
    
    \remarks
    The method processes the text starting from the specified point, using two OdGeVector instancies as X-axis and Y-axis according to other specified parameters.
  */
  virtual void textProc(
            const OdGePoint3d& position,
            const OdGeVector3d& u, 
            const OdGeVector3d& v,
            const OdChar* msg, 
            OdInt32 length, 
            bool raw, 
            const OdGiTextStyle* pTextStyle,
            const OdGeVector3d* pExtrusion = 0) ODRX_OVERRIDE;

  /** \details
    Processes a non-uniform rational B-splines (NURBS) by the export device.
    \param nurbsCurve [in] A OdGeNurbCurve class instance that represents the NURBS object to be processed by the export device.
  */
  virtual void nurbsProc(const OdGeNurbCurve3d& nurbsCurve) ODRX_OVERRIDE;

  /** \details
    Processes a specified Shape file Index text by the export device.
    
    \param position   [in]  A starting point.
    \param u          [in] An X-axis for the export device.
    \param v          [in] An Y-axis for the export device.
    \param msg        [in] An array of OdChar symbols that represents the text of the message to be processed.
    \param length     [in] A length of the message.
    \param raw        [in] A raw flag value.
    \param pStyle     [in] A raw pointer to the text style object associated with the text.
    \param pExtrusion [in] A raw pointer to the vector object that defines the direction of the text extrusion.
  
    \remarks
    The method process the Shape file Index text starting from the specified point, using two OdGeVector instancies as X-axis and Y-axis according to other specified parameters.
  */
  virtual void shxText( const OdGePoint3d& position,
                        const OdGeVector3d& u,
                        const OdGeVector3d& v,
                        const OdChar* msg,
                        OdInt32 length,
                        bool raw,
                        const OdGiTextStyle* pStyle,
                        const OdGeVector3d* pExtrusion ) ODRX_OVERRIDE;
						
  /** \details
    Sets a Shape file Index text to the export device.

    \param position     [in] A starting point.
    \param u            [in] An X-axis for the export device.
    \param v            [in] An Y-axis for the export device.
    \param msg          [in] A raw pointer to an array of OdChar symbols that contains the text of the message.
    \param length       [in] A length of the text message.
    \param raw          [in] A raw flag value.
    \param pTextStyle   [in] A raw pointer to the text style object associated with the text.
    \param pUnicode     [in] A string that contains the Unicode representation of the text message.
    \param isInBigFont  [in] An array of boolean that contains big font flags.
    \param realUnicode  [in] An array of real codes for symbols.
    \param Advances     [in] An array of advanced points.
    
    \remarks
    The method sets the Shape file Index text starting from the specified point, using two OdGeVector instancies as X-axis and Y-axis according to other specified parameters.
  */
  void setSHXText(const OdGePoint3d& position,
                          const OdGeVector3d& u,      
                          const OdGeVector3d& v,      
                          const OdChar* msg, OdInt32 length, bool raw,
                          const OdGiTextStyle* pTextStyle,
                          const OdString &pUnicode,
                          const OdBoolArray &isInBigFont,
                          const OdArray<OdUInt16>& realUnicode,
                          const OdGePoint2dArray &Advances);

  /** \details
    Writes a specified polygon to the export device.

    \param nbPoints     [in]  A number of the polygon points.
    \param pVertexList  [in] A raw pointer to the list of the polygon verticies.
    \param pNormal      [in] A raw pointer to the  list of normal vectors of the polygon.
  */
  virtual void polygonOut( OdInt32 nbPoints, 
                   const OdGePoint3d* pVertexList, 
                   const OdGeVector3d* pNormal = NULL) ODRX_OVERRIDE;

  /** \details
    Sets the fill rule for polygons that can be written (drawn) to the export device.
    \param fillRule [in] An object that contains the polygon's fill rule to be set.
    \returns A new poligon fill rule.
  */
  PolygonFillRules setFillRule(PolygonFillRules fillRule) 
  {
    PolygonFillRules tmp = m_fillRule;
    m_fillRule = fillRule;
    return tmp;
  }

  /** \details 
    Defines whether hidden text is exported.
    \returns true if the hidden text is exported; otherwise the method returns false.
  */
  bool exportHiddenText() const { return m_bExportHiddenText; }
  
  /** \details 
    Sets a new value of the hidden text export flag.
    This flag determines whether hidden text is exported (if is equal to true) or not (if is equal to false).
    \param bOn [in] A new value of the flag to be set.
  */
  void setExportHiddenText(bool bOn) { m_bExportHiddenText = bOn; }

#ifdef BR_CR_10507
  /** \details 
    Processes a shell by the export device. 
    
    \param nbVertex     [in] A number of the shell verticies.
    \param pVertexList  [in] A raw pointer to the verticies array.
    \param faceListSize [in] A number of faces.
    \param pFaceList    [in] A raw pointer to a list of indexes of verticies, which form faces.
    \param pEdgeData    [in] A raw pointer to a list of indexes of vertices, which form faces.
    \param pFaceData    [in] A raw pointer to a face data object.
    \param pVertexData  [in] A raw pointer to verticies data object.
  */
  virtual void shellProc(OdInt32 nbVertex,
    const OdGePoint3d* pVertexList,
    OdInt32 faceListSize,
    const OdInt32* pFaceList,
    const OdGiEdgeData* pEdgeData,
    const OdGiFaceData* pFaceData,
    const OdGiVertexData* pVertexData) ODRX_OVERRIDE;
#endif

  /** \details 
    Processes an ellipse arc by the export device.
    \param ellipArc [in] An OdGeEllipArc3d object that represents the ellipse arc.
    \param width [in] A double value that represents the width of the arc.
    \returns true if the ellipse arc has been processed successfully; otherwise, the method returns false.
  */
  virtual bool ellipArcProc(const OdGeEllipArc3d& ellipArc, double width) ODRX_OVERRIDE;
  
  /** \details 
    Processes an ellipse by the export device with the plot generator.
    \param arc    [in] An OdGeEllipArc3d object that represents the ellipse arc.
    \param width  [in] A double value that represents the width of the arc.
    \returns true if the ellipse arc has been processed successfully; otherwise, the method returns false.
  */
  virtual bool plotGeneratorEllipseOut(const OdGeEllipArc3d& arc, double width) ODRX_OVERRIDE;

  /** \details 
    Writes a drawable data to the export device with specified parameters. 
    \param pDrawable  [in] A raw pointer to a drawable entity to be exported.
    \param params     [in] Export parameters.
    \returns eOk if the export was successful; otherwise, the method returns an appropriate error code.
  */
  OdResult dc_prc(const OdGiDrawable* pDrawable, 
    const PDF2PRCExportParams &params);

  /** \details 
    Writes PRC data from a specified stream to the export device with specified parameters. 
    \param pOut             [in] A raw pointer to a data buffer for writing.
    \param extents2d        [in] An extents object to be used for the export.
    \param center           [in] A center vector.
    \param x                [in] A vector that represents the X-axis.
    \param y                [in] A vector that represents the Y-axis.
    \param z                [in] A vector that represents the Z-axis.
    \param distanceToTarget [in] A distance to the target.
    \param scale            [in] A scale value.
    \param pMatr            [in] A raw pointer to the transformation matrix.
    \returns eOk if the export was successful; otherwise, the method returns an appropriate error code.
  */
  OdResult dc_prc(OdStreamBuf *pOut, 
    const OdGeExtents2d &extents2d, 
    const OdGeVector3d &center, 
    const OdGeVector3d &x, 
    const OdGeVector3d &y, 
    const OdGeVector3d &z, 
    double distanceToTarget, 
    double scale, 
    OdGeMatrix3d *pMatr = NULL);

  /** \details 
    Writes a hyperlink to the export device. 
    
    \param extents2d      [in] An extents object.
    \param link           [in] A string that contains the link URL.
    \param layer          [in] A string that contains the layer.
    \param bInternalLink  [in] A flag value that determines whether the link is an internal link (if is equal to true) or an external one (if is equal to false).
    \param pageIndex      [in] An index of the PDF document's page.
  */
  void dc_hyperlink(const OdGeExtents2d &extents2d, const OdString &link, const OdString &layer, bool bInternalLink, OdInt32 pageIndex = -1);
  
  /** \details 
    Writes a text annotation to the export device. 
    
    \param extents2d  [in] An extents object.
    \param title      [in] A string that contains the annotation title.
    \param content    [in] A string that contains the annotation text.
    \param layer      [in] A string that contains the annotation layer.
  */
  void dc_textAnnot(const OdGeExtents2d &extents2d, const OdString &title, const OdString &content, const OdString &layer);
  
  /** \details 
    Writes the transparency data to the export device.
    
    \param alphaPercent [in] An alpha percent value.
    \param alpha        [in] An alpha value of the transparency.
    \param mode         [in] A transparency mode.
  */
  void dc_transparency(double alphaPercent, OdUInt8 alpha, BlendMode mode);

  /** \details 
    Starts the drawing of a contour at the export device.
  */
  void startDrawingContour();
  
  /** \details 
    Finishes the drawing of a contour at the export device.
  */
  void endDrawingContour();
  
  /** \details 
    Checks whether the drawing of a contour is in progress.
    \returns true of the drawing of a contour is in progress; otherwise, the method returns false.
  */
  bool isDrawingContour();

  /** \details 
    Processes modified traits.
  */
  void processModifiedTraits();
  
  //flush traits into stream and reset all traits
  //TODO: move trait processing into content stream, because of traits have point for stream, not for device
  
  /** \details 
    Saves traits. 
    \param store [out] A placeholder for traits to be saved.
  */
  void saveTraits(PDF2dTraitsSaver& store);
  
  /** \details 
    Restores traits. 
    \param store [in] A traits to be restored.
  */
  void restoreTraits(const PDF2dTraitsSaver& store);
  
  /** \details 
    Flushes traits into a stream and resets all traits. 
    \param store [in] A traits to be flushed.
  */
  void flushTraits(const PDF2dTraitsSaver& store);
//DOM-IGNORE-BEGIN
private:
  /** \details
    Enumeration of modified traits
  */
  enum ModifiedTraits
  {
    kNothingModified = 0,
    kColorModified = 1,       //Color
    kColorIndexModified = 2,  //Color index
    kLayerModified = 4,       //Layer
    kLineCapsModified = 8,    //Line caps
    kLineJoinsModified = 16,  //Line joins
    kLineWeightModified = 32  //Lineweight
  };
  ModifiedTraits m_traitsFlags;
  void traitsChanged(ModifiedTraits trId);
  void resetTraits(bool bAll = false);

  const OdGsBaseVectorizeDevice& m_refDevice;

  //previous traits
  ODCOLORREF  m_prevRGB;
  OdUInt16    m_prevColorIndex;
  OdString    m_prevLayerName;
  PDFLineCap  m_prevCapStyle;
  PDFLineJoin m_prevJoinStyle;
  double      m_prevLineWeight;
  bool        m_bExportHiddenText;
//DOM-IGNORE-END
};

/** \details 
  A data type definition that stores a representation of a layout as a &quot;key-value&quot;. This data type stores a key and a name of the layout represented as strings.
*/
typedef std::pair<OdString, OdString> DwgLayoutKey;

/** \details 
  A class that stores the association between source PDF document's pages and target database layout.
*/
class DbLayout2Page
{
public:
  /** \details 
    Creates a new instance of the layouts-pages association with specified parameters.
    \param prms [in] An instance of the PDFExportParams class that contains the import parameters.
  */
  DbLayout2Page(const PDFExportParams& prms);
  
  /** \details 
    Searches for a corresponding page index by a layout name. 
    \param dwg    [in] A string that contains the full path to the drawing database file.
    \param layout [in] A string that contains the layout name. 
    \param pCurDb [in] A raw pointer to the drawing database object.
    \returns An unsigned integer value that represents the page index if it was found; otherwise, the method returns -1.
  */
  int findPage(const OdString& dwg, const OdString& layout, OdDbBaseDatabase* pCurDb) //-1 if not found
  {
    if(!m_bInitialized)
      init();
    const OdString fullName = getFullPath(dwg, pCurDb);
    _mmap::const_iterator it = m_map.find(DwgLayoutKey(fullName, layout));
    if(it == m_map.end())
      return -1;
    return (int)it->second;
  }

//DOM-IGNORE-BEGIN
protected:
  void init();
  OdString getFullPath(const OdString& dwgName, OdDbBaseDatabase* pCurDb);

protected:
  typedef std::map<DwgLayoutKey, unsigned> _mmap;
  _mmap m_map;
  const PDFExportParams& m_prms;
  OdDbBaseHostAppServicesPtr m_hostApp;
  OdMutex m_mt;
  OdVolatile m_bInitialized;
//DOM-IGNORE-END
};

/** \details 
  A data type definition that represents a smart pointer to a <link TD_PDF_2D_EXPORT::DbLayout2Page, DbLayout2Page> object.
*/
typedef OdSharedPtr<DbLayout2Page> DbLayout2PagePtr;

/** \details
  A class that implements a two-dimensional export device for the PDF export purpose.
*/
class PDF2dExportDevice: public Od2dExportDevice
{
  /** \details 
    A data type definition that represents the parent class for the PDF2dExportDevice class.
  */
  typedef Od2dExportDevice super;
public:
  /** \details 
    Creates a new instance of the PDF export device with default parameters. 
  */
  PDF2dExportDevice() :
    m_obscuredColor(0)
  , m_obscuredLtype(0)
  {};
  
  /** \details 
    Sets export parameters for the export device.
    \param params_holder [in] An instance of the class that stores export parameters to be set.
  */
  void setParams(PdfExportParamsHolderPointer params_holder);
  
  /** \details 
    Determines whether the export device supports the partial update. 
    \returns true if the export device supports the partial update; otherwise, the method returns false.
  */
  virtual bool supportPartialUpdate() const ODRX_OVERRIDE;
  
  /** \details 
    Retrieves the current value of the render area multiplier. 
    \param width  [in] An unsigned 32-bit integer that contains the width value.
    \param height [in] An unsigned 32-bit integer that contains the height value.
    \param mode   [in] A shaded viewport export policy value. 
    \returns A double value that contains the current value of the render area multiplier. 
  */
  virtual double renderAreaMultiplier(OdUInt32 width, OdUInt32 height, ShadedViewportExportMode& mode) const;

  /** \details
    Determines whether a rendering device is required to export the given view.
    \param view [in] A Gs view object.
    \returns true if a rendering device is required; otherwise, the method returns false.
  */
  virtual bool isRenderDeviceRequired(const OdGsView& view) const ODRX_OVERRIDE;
  
  /** \details 
    Calculates the rendering device clipping.
    \param pRenderDevice [in] A raw pointer to the Gs device object.
    \param ext2d         [in] An extents object.
    \param extDevice     [in] An extents device.
    \param nrcCounts     [in] An array with numbers of points, which bound clipping areas.
    \param nrcPoints     [in] An array of clipping areas points. 
    \param nDevice       [in] A device index.
    \param bDrawPicture  [in] A flag that determines whether the picture should be drawn.
  */
  virtual void calculateRenderDeviceClipping(OdGsDevice *pRenderDevice, OdGeExtents3d& ext2d, OdGeExtents3d& extDevice,
    OdIntArray& nrcCounts, OdGsDCPointArray& nrcPoints, int nDevice, bool& bDrawPicture) const;
    
  /** \details
    Updates the export device at the specified rectangle.
    \param pUpdatedRect [in] A raw pointer to the rectangle object that needs to be updated.
    \remarks
    The method repaints the PDF document associated with the export device inside the borders of the specified rectangle.
  */
  virtual void update(OdGsDCRect* pUpdatedRect);
  
  // Set the target data stream and the type.  
  //static OdGsDevicePtr createObject(DeviceType type = /*Od2dExportDevice::*/k3dDevice);
  
  /** \details
    Creates the target data stream for the export device.
    \returns A smart pointer to OdGsDevice class instance if the target data stream was successfully created.
  */
  static OdGsDevicePtr createObject();

  //  to create an instance 
  // of the desired OdGsView subclass. 
  /** \details
    Creates an instance of the OdGsView subclass.
    \param pInfo                          [in] A raw pointer to OdGsClientViewInfo class instance.
    \param bEnableLayerVisibilityPerView  [in] Determines if the layer visibility is switched on (true) or off (false) for the created view. Default value is false.
    \returns A smart pointer to OdGsView class instance if view was successfully created.
    \remarks
    The method is invoked by the visualization framework. 
  */
  virtual OdGsViewPtr createView(const OdGsClientViewInfo* pInfo = 0,
    bool bEnableLayerVisibilityPerView = false) ODRX_OVERRIDE;

  /** \details 
    Creates geometry for the export device.
    \returns A raw pointer to the export geometry object.
  */
  virtual Od2dExportGeometry* createGeometry() const ODRX_OVERRIDE;

  /** \details
    Blocks or unblocks the GsCache support for the export device.
    \param bEnable [in]  A block flag value. If it is equal to true, the GsCache support is enabled; if it is equal to false, the GsCache support is disabled.
  */
  void enableBlockCachSupport(bool bEnable);

  /** \details 
    Requests the export parameters.
    \returns An instance of the PDFExportParams class that contains export parameters.
  */
  const PDFExportParams& exportParams() const
  {
    return geom().exportParams();
  }
  
  /** \details 
    Determines whether the support of layers is enabled for the export device.
    \returns true if layers are supported; otherwise, the method returns false.
  */
  bool isLayersSupported() const
  {
    return GETBIT(exportParams().exportFlags(), PDFExportParams::kEnableLayers);
  }
  
  /** \details
    Determines whether the support of inactive layers (layers, which are &quot;off&quot;) is enabled for the export device.
    \returns true if inactive (&quot;off&quot;) layers are supported; otherwise, the method returns false.
  */
  bool isOffLayersEnabled() const
  {
    return GETBIT(exportParams().exportFlags(), PDFExportParams::kIncludeOffLayers);
  }

  /** \details
    Determines whether the support of frozen layers simulation is enabled for the export device.
    \returns true if frozen layers simulation is supported; otherwise, the method returns false.
  */
  bool frozenLayerSimulationEnabled() const
  {
    return geom().frozenLayerSimulationEnabled();
  }

  /** \details
    Determines whether is a layer specified with its name is frozen.
    \param layerName [in] A string that contains the layer name.
    \returns true if the specified layer is frozen; otherwise, the method returns false.
  */
  bool isFrozenLayer(const OdString &layerName) const
  {
    return geom().isFrozenLayer(layerName); //NS TODO: why OdString and not OdDbStub?
  }

  /** \details 
    Sets the paper box for the export device. 
    \param box [in] An OdGsDCRect object that represents the paper box to be set.
  */
  void setPaperBox(const OdGsDCRect& box)
  {
    geom().setPaperBox(box);
  }

  /** \details 
    Sets a new value of the LwToDc scale. 
    \param val [in] A scale value.
  */
  void setLwToDcScale(double val)
  {
    geom().m_LwToDcScale = val;
  }

  /** \details
    Determines whether the &quot;global&quot; indexed palette is required in a PDF document.
    \returns true if the &quot;global&quot; indexed palette is required in a PDF document; otherwise, the method returns false.
  */
  bool isDWGPaletteNeeded() const
  {
    return geom().isDWGPaletteNeeded();
  }

  /** \details 
    Requests the resolution for color bitmaps. The resolution is represented in dot-per-inch (DPI) units.
    \returns An unsigned 16-bit integer that represents the resolution value.
  */
  OdUInt16 getColorBimapDPI() const { return geom().getColorBimapDPI(); }
  
  /** \details 
    Requests the resolution for hatches. The resolution is represented in dot-per-inch (DPI) units.
    \returns An unsigned 16-bit integer that represents the resolution value.
  */
  OdUInt16 getHatchDPI() const { return geom().getHatchDPI(); }

  /** \details 
    Requests the geometry for the output. 
    \returns A raw pointer to a PDF2dExportGeometry object.
  */
  PDF2dExportGeometry* getGeomForOutput() { return &geom(); }
  
  /** \details 
    Requests the rendering Gs model for the export device. 
    \param i [in] A requested model's index.
    \returns A reference to a SavedGsModelData object.
  */
  SavedGsModelData& renderDeviceGsModelAt(int i)
  {
    return m_renderDevices[i].m_data;
  }
  
  /** \details 
    Updates the geometry for the export device. 
  */
  void doUpdateGeometry();

  /** \details 
    Requests the association between drawing database layouts and PDF pages.
    \returns A raw pointer to the DbLayout2Page object. 
  */
  DbLayout2Page* dbLayoutToPage() { return m_dbLayout2Page.get(); }
  
  /** \details 
    Sets the association between drawing database layouts and PDF pages.
    \param ptr [in] A smart pointer to the DbLayout2Page object to be set. 
  */  
  void setDbLayoutToPage(const DbLayout2PagePtr& ptr) { m_dbLayout2Page = ptr; }

  /** \details 
    Sets a transformation matrix for a specified block.
    \param blockName [in] A string that contains the block name.
    \param mat       [in] A transformation matrix to be set.
  */
  void setPdfBlockTransform(const OdString& blockName, const OdGeMatrix3d& mat) { m_blockParams[blockName].transform = mat; }
  
  /** \details 
    Retrieves the current transformation matrix for a specified block.
    \param blockName [in] A string that contains the block name.
    \returns An OdGeMatrix3d object that represents the transformation matrix associated with the block.
  */
  OdGeMatrix3d getPdfBlockTransform(const OdString& blockName) { return m_blockParams[blockName].transform; }
  
  /** \details 
    Searches a block name by the block node description. 
    \param blockName [out] A placeholder for a string that contains the found block name.
    \param desc [in] A block node description.
    \param matr [in] A transformation matrix.
    \returns true if the block name was found; otherwise, the method returns false.
  */
  bool findBlockNameByDesc(OdString& blockName, const OdGsBlockRefNodeDesc& desc, const OdGeMatrix3d& matr);

  /** \details
    Retrieves the current obscured color value for the processing of hidden lines.
    \returns An integer value that represents the color value.
  */
  int obscuredColor() const { return m_obscuredColor; }
  
  /** \details
    Retrieves the current value of the obscured line type for the processing of hidden lines.
    \returns An integer value that represents the line type value.
  */
  int obscuredLtype() const { return m_obscuredLtype; }

//DOM-IGNORE-BEGIN
protected:
  PDF2dExportGeometry& geom() { return (PDF2dExportGeometry&)super::geom(); }
  const PDF2dExportGeometry& geom() const { return (const PDF2dExportGeometry&)super::geom(); }
  void finishPRCVectorization();
  virtual bool createRenderDevices(const OdRxObjectPtrArray& aView) ODRX_OVERRIDE;
  void setObscuredGraphicsParams();

  DbLayout2PagePtr m_dbLayout2Page;
  int m_obscuredColor;
  int m_obscuredLtype;

  struct PDFBlockParams {
    OdGeMatrix3d transform;
    OdGsBlockRefNodeDesc desc;
  };
  std::map<OdString, PDFBlockParams> m_blockParams;
//DOM-IGNORE-END

public:
  /** Clipping area based on device restrictions.*/
  OdGePoint2dArray                   m_clipPoints;  
};

}
#endif // #ifndef _PDF_2D_EXPORT_DEVICE_INCLUDED_
