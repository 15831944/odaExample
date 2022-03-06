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

#ifndef _ODTV_RASTERIMAGE_H_INCLUDED_
#define _ODTV_RASTERIMAGE_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvUserData.h"
#include "Gi/GiRasterImage.h"

/** \details
  The abstract interface class for working with raster images in Visualize SDK.
  \sa
  <link tv_working_with_base_classes_raster_images, Work with Raster Images>
*/
class ODTV_EXPORT OdTvRasterImage : public OdTvHandledIObject
{
public:

  /** \details
    Supported formats of binary image data.
  */
  enum Format
  {
    kRGB = 0,   // RGB format.
    kRGBA = 1,  // RGB with alpha channel format.
    kBGR = 2,   // BGR format.
    kBGRA = 3,  // BGR with alpha channel format.
    kBGR_16 = 4 // 16-bit BGR format.
  };

  /** \details
    Bits per index for palette binary image data.
  */
  enum BitPerIndex
  {
    kFourBits = 0,  // Four bits per index.
    kEightBits = 1, // Eight bits per index.
  };

  /** \details
    Types of image data.
  */
  enum Type
  {
    kFile = 0,          // An image file.
    kBinary = 1,        // A binary array of an image file.
    kPaletteBased = 2,  // Palette-based data.
    kMonochrome         // A monochrome image.
  };

  /** \details
    Retrieves whether the raster image object is binary. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the raster image is a binary image; otherwise the raster image is based on a specified image file, and the method returns false.
    \remarks 
    If the rc parameter is not null and the binary flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool isBinary(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current <link OdTvRasterImage::Type, type> of the raster image. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current type of the raster image represented with a value of the <link OdTvRasterImage::Type, Type> enumeration.
    \remarks 
    If the rc parameter is not null and the current image type was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual Type getType(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current size of the raster image object in pixels.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a <link OdTvVector2d, two-dimensional vector> that represents the raster image dimensions along the X- and Y-axes in pixels.
    \remarks 
    If the rc parameter is not null and current image size was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvVector2d getSize(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets binary data for the raster image object. The raster image object becomes a binary one.
    
    \param format       [in] A binary data format. It describes how the data is packed in the specified array.
    \param width        [in] A number of pixel columns for the image.
    \param height       [in] A number of pixel rows for the image.
    \param data         [in] A pointer to the binary data (array of bytes) packed according to the format. The data describes colors of each pixel of the image.
    \param iAlignment   [in] A byte alignment value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new binary data was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setBinaryData(OdTvRasterImage::Format format, OdUInt32 width, OdUInt32 height, const OdUInt8* data, OdUInt32 iAlignment = 4) = 0;

  /** \details
    Sets new data for the palette-based raster image. The raster image object becomes a palette-based one.
    
    \param paletteformat [in] A palette format. It describes how the color data is packed in the specified array.
    \param paletteSize   [in] A number of colors in the palette.
    \param paletteData   [in] A pointer to the palette data (array of bytes) packed according to the format. The data describes the palette colors.
    \param bpi           [in] A new value of bits per index. This value describes how indexes are packed in the data array.
    \param width         [in] A number of pixel columns for the image.
    \param height        [in] A number of pixel rows for the image.
    \param data          [in] A pointer to the binary data (array of bytes) packed according to the format. The data describes indexes in the palette for each pixel of the image.
    \param iAlignment    [in] A byte alignment value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new palette data was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setPaletteData(OdTvRasterImage::Format paletteformat, OdUInt32 paletteSize, OdUInt8* paletteData,
                                    OdTvRasterImage::BitPerIndex bpi, OdUInt32 width, OdUInt32 height, const OdUInt8* data, OdUInt32 iAlignment = 4) = 0;

  /** \details
    Sets new monochrome data for the raster image. The raster image object becomes a monochrome-based one.
    
    \param width         [in] A number of pixel columns for the image.
    \param height        [in] A number of pixel rows for the image.
    \param data          [in] A pointer to the binary data (array of bytes) that describes the presence of the main color for each image pixel.
    \param bInverted    [in]  A flag that determines whether the background color is used as the main color (if true) or not (if false).
    \param iAlignment   [in]  The byte alignment value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new monochrome data was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setMonochromeData(OdUInt32 width, OdUInt32 height, const OdUInt8* data, bool bInverted = false, OdUInt32 iAlignment = 4) = 0;

  /** \details
    Retrieves the current format of the binary image data.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current format represented with the <link OdTvRasterImage::Format, Format> enumeration value.
    \remarks 
    If the rc parameter is not null and the current format value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    If the raster image object is based on a source file, the method returns the <link OdTvRasterImage::Format::kRGB, kRGB> value 
    and an appropriate error code in the rc output parameter (if the pointer passed in the rc parameter is not null).
  */
  virtual Format getFormat(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current alignment of the binary image data. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current byte alignment value.
    \remarks 
    If the rc parameter is not null and the current alignment value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    If the raster image object is based on a source file, the method returns the zero value 
    and an appropriate error code in the rc output parameter (if the pointer passed in the rc parameter is not null).
  */
  virtual OdUInt32 getAlignment(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current array of the binary image data. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a raw pointer to the binary data array.
    \remarks 
    If the rc parameter is not null and the current array of binary data was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    If the raster image object is based on a source file, the method returns a NULL pointer 
    and an appropriate error code in the rc output parameter (if the pointer passed in the rc parameter is not null).
  */
  virtual const OdUInt8* getBinaryData(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current palette size of the raster image object. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current palette size.
    \remarks 
    If the rc parameter is not null and the current palette size was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    If the raster image object is not a palette-based image, the method returns a zero value 
    and an appropriate error code in the rc output parameter (if the pointer passed in the rc parameter is not null).
  */
  virtual OdUInt32 getPaletteSize(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current array of the palette image data. 
    
    \param bytes [out] A pointer to a byte array of palette data.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The method fills the byte array specified with the pointer passed in the bytes parameter and returns it to a calling subroutine.
    If the palette data array was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
    If the raster image object is not a palette-based image, the method changes the pointer value passed within the bytes output parameter to NULL 
    and returns an appropriate error code.
  */
  virtual OdTvResult getPalette(OdUInt8* bytes) const = 0;

  /** \details
    Retrieves the current bits-per-index value of the raster image object. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current bits-per-index value.
    \remarks 
    If the rc parameter is not null and the current bits-per-index value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    If the raster image object is not a palette-based image, the method returns the <link OdTvRasterImage::BitPerIndex::kFourBits, kFourBits> value 
    and an appropriate error code in the rc output parameter (if the pointer passed in the rc parameter is not null).
  */
  virtual OdTvRasterImage::BitPerIndex getBitPerIndex(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current inverse flag value for the raster image object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if monochrome colors are inverted; otherwise the method returns false.
    \remarks
    If the rc parameter is not null and the current inverse flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    If the raster image is not a monochrome-based image, the method returns false 
    and an appropriate error code in the rc output parameter (if the pointer passed in the rc parameter is not null).
  */
  virtual bool getInverted(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new name of the source file that contains the raster image. The raster image object becomes an image based on a source file.
    
    \param pathName [in] A string that contains the full path to the source file.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new name of the source file was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setSourceFileName(const OdString& pathName) = 0;

  /** \details
    Retrieves the current source file name of the raster image object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the string that contains the current source file name for the raster image object.
    \remarks
    If the rc parameter is not null and the current source file name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    If the raster image is a binary image, the method returns an empty string
    and an appropriate error code in the rc output parameter (if the pointer passed in the rc parameter is not null).
  */
  virtual OdString getSourceFileName(OdTvResult* rc = NULL) const = 0;

  /** \details
    Loads the content of the source image file for the raster image object.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the load operation.
    \remarks
    If the the source image file was successfully loaded, the method returns the tvOk value; otherwise it returns an appropriate error code.
    If the image file has already loaded, the source file is not read.
    A lazy load mode implies that the image file is not loaded until it is required.
    If the raster image is a binary image, the method does not load the source image file and returns an appropriate error code.
  */
  virtual OdTvResult load() = 0;

  /** \details
    Unloads the content of the source image file from the raster image object.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the unloading operation.
    \remarks
    If the the source image file was successfully unloaded, the method returns the tvOk value; otherwise it returns an appropriate error code.
    If the raster image is a binary image, the method returns an appropriate error code.
  */
  virtual OdTvResult unload() = 0;

  /** \details
    Retrieves the current value of the load flag. The load flag determines whether a source image file was loaded (if true) or not (if false).
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the source image file for the raster image object was loaded; otherwise the method returns false.
    \remarks 
    In the case of a binary raster image, returns true and an appropriate error code in the rc output parameter 
    (if the pointer passed in the rc parameter is not null).
  */
  virtual bool isLoaded(OdTvResult* rc = NULL) const = 0;

  /** \details
    Interprets instance of OdTvRasterImage as OdGiRasterImage.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns smart-pointer to the instance of OdGiRasterImage.
  */
  virtual OdGiRasterImagePtr getAsGiRasterImage( OdTvResult* rc = NULL ) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvRasterImage, OdTvRasterImage> object.
*/
typedef OdTvSmartPtr<OdTvRasterImage> OdTvRasterImagePtr;


/** \details
  The interface class for a raster image object identifier that allows access to the <link OdTvRasterImage, OdTvRasterImage> object.
*/
class ODTV_EXPORT OdTvRasterImageId : public OdTvId
{
public:

  /** \details
    Opens the raster image object determined with its identifier for a read or write operation. 
    
    \param mode [in] An open mode value.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the raster image object.
    \remarks
    If the rc parameter is not null and the raster image object is successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvRasterImagePtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;
};


/** \details
  The base interface class for the iterator of Visualize SDK raster image objects.
  An iterator object provides sequential access to a collection of raster images.
*/
class ODTV_EXPORT OdTvRasterImagesIterator : public OdTvIterator, public OdTvIObject
{
public:

  /** \details
    Retrieves the raster image that is currently referenced by the iterator object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the raster image object's identifier if the iterator refers to a raster image; otherwise it returns an identifier with a null value.
    \remarks 
    If the rc parameter is not null and the raster image object's identifier is successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    If the iterator refers to a raster image object, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvRasterImageId getRasterImage(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches for the raster image object defined by its identifier and moves the iterator to this raster image object if found.
    
    \param imageId [in] A raster image object's identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the raster image object specified by its identifier is found, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek(const OdTvRasterImageId& imageId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvRasterImagesIterator, raster images iterator> object.
*/
typedef OdTvSmartPtr<OdTvRasterImagesIterator> OdTvRasterImagesIteratorPtr;


#endif // _ODTV_RASTERIMAGE_H_INCLUDED_
