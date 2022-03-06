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

#ifndef _ODTV_ENTITYGEOMETRYMISC_H_INCLUDED_
#define _ODTV_ENTITYGEOMETRYMISC_H_INCLUDED_

#include "Tv.h"
#include "TvGeometryData.h"
#include "TvRasterImage.h"

class OdTvBlockId;

/** \details
  This is an interface class for an OdTvTextData object.
  \sa
  <link tv_geometry_text, Work with Text Entities>
*/ 
class ODTV_EXPORT OdTvTextData : public OdTvIObject
{
public:

  /** \details
    Underlined/overlined/striked states.
  */
  enum StrokeState
  {
    kInherit = 0, // Inherited from the text style.
    kOn = 1,      // Underlined/overlined/striked is on.
    kOff = 2      // Underlined/overlined/striked is off.
  };

  /** \details
    Retrieves the position (in WCS) of this text.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getPosition(OdTvResult* rc = NULL) const = 0;
  
  /** \details
    Sets the position (in WCS) of this text.
    
    \param position 	[in] An instance of the OdTvPoint class that defines a position for this text.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the position for this text is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPosition(const OdTvPoint& position) = 0;

  /** \details
    Retrieves the alignment point (in WCS) of this text.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvPoint class that represents a point in 3D space.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvPoint getAlignmentPoint(OdTvResult* rc = NULL) const = 0;
  
  /** \details
    Sets the alignment point (in WCS) of this text.
    
    \param alignment 	[in] An instance of the OdTvPoint class that defines an alignment point for this text.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the alignment point for this text is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setAlignmentPoint(const OdTvPoint& alignment) = 0;

  /** \details
    Retrieves the normal vector of this text.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvVector class that represents a vector in 3D space.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvVector getNormal(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the normal vector for this text.
    
    \param normal 	[in] An instance of the OdTvVector class that defines a normal vector for this text.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the normal for this text is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setNormal(const OdTvVector& normal) = 0;

  /** \details
    Retrieves the rotation angle of this text.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a rotation angle in radians as a double value.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual double getRotation(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the rotation angle in radians for this text.
    
    \param rotation 	[in] A double value representing an angle of rotation in radians.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the rotation for this text is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setRotation(double rotation) = 0;

   /** \details
    Retrieves the string of this text.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an OdString value that contains a string of the given text object.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdString getString (OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the string for this text.
    
    \param msg 		[in] OdString value representing a string for this text object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the string for this text is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setString (const OdString& msg) = 0;

  /** \details
    Retrieves the alignment mode of this text.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an OdTvTextStyle::AlignmentType value that represents a type of alignment.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvTextStyle::AlignmentType getAlignmentMode(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the alignment mode.
    
    \param alignMode	[in] An OdTvTextStyle::AlignmentType value that represents one of the alignment modes.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the alignment mode is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setAlignmentMode(OdTvTextStyle::AlignmentType alignMode) = 0;

  /** \details
    Retrieves the text style of this text.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvTextStyleDef class that represents a text style.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvTextStyleDef getTextStyle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the text style for this text.
    
    \param textStyle 	[in] An instance of the OdTvTextStyleDef class that represents a text style.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the text style is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setTextStyle(const OdTvTextStyleDef& textStyle) = 0;

  /** \details
    Retrieves the height scale factor of the text boundary. This factor influences the width
    
    and height together and is used for proportional scaling of letters, spaces, and the text boundary.
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a text size as a double value.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual double getTextSize(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the text size which is the height scale factor of the text boundary. This factor
    influences the text width and text height together and is used for proportional scaling of
    letters, spaces, and the text boundary. A value less than 1.0 decreases the text. A value
    greater than 1.0 increases the text. The initial value is 0.0 by default, which means that the 
    text size from the text style is used.
    
    \param dSize 		[in] Text size as a positive double value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the text size is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setTextSize(double dSize) = 0;

  /** \details
    Retrieves the width scale factor of the text boundary. This factor influences only the
    width and is used for scaling letters and spaces when the height is constant.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the width factor of text as a double value.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual double getWidthFactor(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the width scale factor of the text boundary. This factor influences only the
    text width and is used for scaling letters and spaces when the height is constant. A value
    less than 1.0 condenses the text. A value greater than 1.0 expands the text. The initial value
    is 0.0 by default, which means that it uses the 
    width factor from the text style.
    
    \param widthFactor [in]  Width factor as a positive double value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the width factor of text is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setWidthFactor(double widthFactor) = 0;

  /** \details
  Retrieves true if non-rotatable.
  \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns the bool value that shows if text is rotatable or not.
  \remarks
  If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getNonRotatable(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the non-rotatable property for all text inside an entity.
    
    \param bNonRotatable 	[out] A bool value which specifies that text is rotatable (if set to false) or non-rotatable (if set to true).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setNonRotatable(bool bNonRotatable) = 0;

  /** \details
    Sets the underlined stroke state for this text.
    
    \param underlined [in]  Controls underlining of text.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setUnderlined(StrokeState underlined) = 0;

  /** \details
    Retrieves the state of underlining the text.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the StrokeState value that represents a state of the stroke.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual StrokeState getUnderlined(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the overlined stroke state for this text.
    
    \param overlined [in]  Controls over-lining of text.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setOverlined(StrokeState overlined) = 0;

  /** \details
    Retrieves the state of over-lining the text.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the StrokeState value that represents a state of the stroke.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual StrokeState getOverlined(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the striked stroke state for this text.
    
    \param striked [in]  Controls striking of text.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setStriked(StrokeState striked) = 0;

  /** \details
    Retrieves the state of striking the text.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the StrokeState value that represents a state of the stroke.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual StrokeState getStriked(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves an array with bounding points.
    
    \param array [out]
    Top left is array[0].
    Top right is array[1].
    Bottom left is array[2].
    Bottom right is array[3].
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the bounding points are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getBoundingPoints(OdTvPointArray& array) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the OdTvTextData class and used for storing and passing references to the text object.
*/
typedef OdTvSmartPtr<OdTvTextData> OdTvTextDataPtr;


/** \details
  This is an interface class for an OdTvTextData object.
  \sa
  <link tv_geometry_sub_inserts, Work with Sub-Inserts>
*/
class ODTV_EXPORT OdTvInsertData : public OdTvIObject
{
public:

  /** \details
    Retrieves the ID of the block associated with this insert.
    
    \param rc 	[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvBlockId class that represents an identifier of a block.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvBlockId getBlock(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the ID of the block associated with this insert.
    
    \param blockId [in]  Object ID of the block.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setBlock(const OdTvBlockId& blockId) = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the OdTvInsertData class and used for storing and passing references to the insert object.
*/
typedef OdTvSmartPtr<OdTvInsertData> OdTvInsertDataPtr;


/** \details
  This is an interface class for an OdTvRasterImageData object.
  \sa
  <link tv_geometry_raster_images, Work with Raster Image Geometry Data>
*/
class ODTV_EXPORT OdTvRasterImageData : public OdTvIObject
{
public:

  /** \details
    Sets the ID of the OdTvRasterImage object.
    
    \param imageId 	[in]  Object ID of image to be displayed.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the object ID of the image is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setImageId(OdTvRasterImageId imageId) = 0;

  /** \details
    Retrieves the ID of the OdTvRasterImage object.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvRasterImageId class that represents an identifier of a raster image.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvRasterImageId getImageId(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the orientation and origin of this raster image data.
    
    \param origin 	[in] Lower-left corner.
    \param u 			[in] Image width vector.
    \param v 			[in] Image height vector.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The actual height of the image is determined by the width and aspect ratio of the original image.
    If the orientation of the raster image is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setOrientation(const OdTvPoint& origin, const OdTvVector& u, const OdTvVector& v) = 0;

  /** \details
    Retrieves the orientation and origin of this raster image data.
    
    \param origin 	[out]  Receives the point for the lower-left corner.
    \param u 			[out]  Receives the vector defining the image direction and width.
    \param v 			[out]  Receives the vector defining the direction of the height of the image.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the orientation of the raster image is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getOrientation(OdTvPoint& origin, OdTvVector& u, OdTvVector& v) const = 0;

  /** \details
    Sets the clipping boundary for this raster image data.
    
    \param clipPoints [in]  An array of 2D points that define the clipping boundary.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    The array of 2D points should be in pixel coordinates.
    If the size == 2, it is a rectangular boundary; it is polygonal otherwise.
    If the clipping boundary of the raster image is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.  
  */
  virtual OdTvResult setClipBoundary(const OdTvPoint2dArray& clipPoints) = 0;

  /** \details
    Retrieves the clipping boundary for this raster image data.
    
    \param clipPoints [out]  An array of 2D points that represents the clipping boundary.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The clipping boundary is specified in pixel coordinates.
    If the points that define the clipping boundary of the raster image are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getClipBoundary(OdTvPoint2dArray& clipPoints) const = 0;

  /** \details
    Retrieves the clipping state for this raster image data.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the bool value that shows if the raster image is clipped or not.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getClipped(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the ClipInverted flag value for this raster image data.
    
    \param val 		[in]  The ClipInverted flag value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the ClipInverted flag of the raster image is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setClipInverted(bool val) = 0;

  /** \details
    Retrieves the ClipInverted flag value for this raster image data.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the bool value that shows if the raster image is clipped or not.
    \remarks
    If the method finished successfully, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual bool getClipInverted(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the brightness value for this raster image data.
    
    \param brightness [in]  Image brightness in the range [0.0 .. 100.0].
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the brightness parameter is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setBrightness(OdInt8 brightness) = 0;

  /** \details
    Retrieves the brightness value for this raster image data.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value in the range [0.0 .. 100.0].
    \remarks
    If the brightness value is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdInt8 getBrightness(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the contrast value for this raster image data.
    
    \param contrast 	[in] Image contrast in the range [0.0 .. 100.0]
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the contrast parameter is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setContrast(OdInt8 contrast) = 0;

  /** \details
    Retrieves the contrast value for this raster image data.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value in the range [0.0 .. 100.0].
    \remarks
    If the contrast value is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdInt8 getContrast(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the fade value for this raster image data.
    
    \param fade 		[in] Image fade in the range [0.0 .. 100.0].
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the fade parameter is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFade(OdInt8 fade) = 0;

  /** \details
    Retrieves the fade value for this raster image data.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a value in the range [0.0 .. 100.0].
    \remarks
    If the fade value is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdInt8 getFade(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the size in pixels of this raster image data.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvVector2d class that stores the corresponding width and height sizes of the image.
    \remarks
    If the image size is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvVector2d getImageSize(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the background color for this raster image data if it is monochrome.
    
    \param backgroundColor [in]  Background color.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the background color for the monochrome raster image is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMonochromeBackgroundColor(const OdTvColorDef& backgroundColor) = 0;

  /** \details
    Retrieves the background color for this raster image data.
    
    \param rc 		[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an instance of the OdTvColorDef class that represents color data.
    \remarks
    If the background color data is successfully retrieved, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  */
  virtual OdTvColorDef getMonochromeBackgroundColor(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the OdTvRasterImageData class and used for storing and passing references to the raster image data object.
*/
typedef OdTvSmartPtr<OdTvRasterImageData> OdTvRasterImageDataPtr;



/** \details
  This is an interface class for an OdTvColoredShapeData object.
*/
class ODTV_EXPORT OdTvColoredShapeData : public OdTvIObject
{
public:

  /** \details
    Sets the geometry data of a plane's colored area.
    
    \param verticesArray 	[in] An array of vertices.
    \param faces 			[in] An array of faces.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameters of this colored shape are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set(const OdTvPointArray& verticesArray, const OdInt32Array& faces) = 0;

  /** \details
    Sets the geometry data of a plane's colored area.
    
    \param nVertices 		[in] A quantity of vertices.
    \param vertices 		[in] An array of vertices represented with a pointer to the first array element.
    \param faceListSize 	[in] A quantity of faces.
    \param faces 			[in] An array of faces represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameters of this colored shape are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult set(OdInt32 nVertices, const OdTvPoint* vertices, OdInt32 faceListSize, const OdInt32* faces) = 0;

  /** \details
    Sets the vertices colors of a plane's colored area.
    
    \param colors 		[in] An array of color definition objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color definitions for this colored shape are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexColors(const OdTvRGBColorDef* colors) = 0;

  /** \details
    Sets the vertex colors of a plane's colored area.
    
    \param colors 		[in] An array of color definition objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the color definitions for this colored shape are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertexColors(const OdTvRGBColorDefArray& colors) = 0;

  /** \details
    Sets edge visibility of a plane's colored area.
    
    \param visibilities 	[in] An array of visibility data objects represented with a pointer to the first array element.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visibility data objects for this colored shape are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgesVisibilities(const OdTvVisibilityDef* visibilities) = 0;

  /** \details
    Sets edge visibility of a plane's colored area.
    
    \param visibilities 	[in] An array of visibility data objects.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the visibility data objects for this colored shape are successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setEdgesVisibilities(const OdTvVisibilityDefArray& visibilities) = 0;

  /** \details
    Sets true if and only if the contour should be drawn.
    
    \param bDraw 			[in] A bool value specifying if the contour is drawn.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the specified parameter is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setDrawContour(bool bDraw) = 0;

  /** \details
  Retrieves the geometry data of a plane's colored area.
  \param verticesArray 	[out] An array of vertices to be filled.
  \param faces 			[out] An array of faces to be filled.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks
  If the specified parameters of this colored shape are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult get(OdTvPointArray& verticesArray, OdInt32Array& faces) const = 0;

  /** \details
    Retrieves the vertex colors of a plane's colored area.
    
    \param colors 		[out] An array of color definition objects to be filled.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the vertex colors of this colored shape are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getVertexColors(OdTvRGBColorDefArray& colors) const = 0;

  /** \details
    Retrieves the visibility values of edges.
    
    \param visibilities 	[out] An array of visibility data objects to be filled.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the edge visibility values of this colored shape are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getEdgesVisibilities(OdTvVisibilityDefArray& visibilities) const = 0;

  /** \details
    Returns true if and only if the contour should be drawn.
    
    \param rc 			[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the bool value that shows the contour is drawn or not.
    \remarks
    If the edge visibility values of this colored shape are successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual bool getDrawContour(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the quantity of vertices in the plane's colored area.
    
    \param rc 			[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an OdUInt32 value that represents a quantity of vertices in this colored shape.
    \remarks
    If the quantity of vertices of this colored shape is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdUInt32 getVerticesCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the quantity of faces in a plane's colored area.
    
    \param rc 			[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an OdUInt32 value that represents a quantity of faces in this colored shape.
    \remarks
    If the quantity of faces of this colored shape is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdUInt32 getFacesCount(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the quantity of edges in a plane's colored area.
    
    \param rc 			[out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an OdUInt32 value that represents a quantity of edges in this colored shape.
    \remarks
    If the quantity of edges of this colored shape is successfully retrieved, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdUInt32 getEdgesCount(OdTvResult* rc = NULL) const = 0;

  /** \details
  Sets a hatch pattern for the colored shape object.
  \param def   [in] An instance of OdTvHatchPatternDef that represents a definition for a hatch pattern.
  \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks
  If the hatch pattern is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
  \sa
  <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvResult setHatchPattern(const OdTvHatchPatternDef& def) = 0;

  /** \details
  Retrieves a hatch pattern object for the colored shape object.
  \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns an instance of the OdTvHatchPatternDef class that represents a definition for a hatch pattern.
  \remarks
  If the hatch pattern is successfully returned, the rc parameter is set to tvOk; otherwise it holds an appropriate error code.
  \sa
  <link tv_working_with_attributes_fill_patterns, Work with Fill Patterns>
  */
  virtual OdTvHatchPatternDef getHatchPattern(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an instance of the OdTvColoredShapeData class and used for storing and passing references to the colored shape object.
*/
typedef OdTvSmartPtr<OdTvColoredShapeData> OdTvColoredShapeDataPtr;


#endif // _ODTV_ENTITYGEOMETRYMISC_H_INCLUDED_

