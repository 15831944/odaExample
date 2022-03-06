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

#ifndef _ODTV_RASTERIMAGEIMPL_H_INCLUDED_
#define _ODTV_RASTERIMAGEIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "OdDbStub.h"

#include "TvRasterImage.h"
#include "TvGeometryData.h"
#include "TvInterfaceWrappers.h"
#include "TvUserDataImpl.h"

#include "DbDictionary.h"
#include "DbRasterImageDef.h"

typedef OdArray<OdTvGeometryDataId> OdTvGeometryDataIdArray;


/** \details
This class is the internal implementation of the raster image. Such implementation is need
because of special storing of the referencies
*/
class OdTvRasterImageImpl : public OdTvDbRasterImageDef, public OdTvXDataStorage
{
  OdTvRasterImageImpl();
  
  virtual ~OdTvRasterImageImpl();

public:
  ODRX_DECLARE_MEMBERS(OdTvRasterImageImpl);

  // add and remove references on image geometry data
  void addReference(OdTvGeometryDataId imageData);
  void removeReference(OdTvGeometryDataId imageData);
  void updateReferencies();

  // for loading from VSF file
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  // for saving in VSF file
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  bool isBinary() const;
  OdTvRasterImage::Type getType() const;
  OdTvRasterImage::Format getFormat() const;
  OdUInt32 getAlignment() const;
  const OdUInt8* getBinaryData() const;
  OdUInt32 getPaletteSize() const;
  void getPalette(OdUInt8* bytes) const;
  OdTvRasterImage::BitPerIndex getBitPerIndex() const;
  bool getInverted() const;
  OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;

  virtual OdGiRasterImagePtr getAsGiRasterImage() const;

private:

  // array of the referencies
  OdTvGeometryDataIdArray m_referencies;
};

typedef OdSmartPtr<OdTvRasterImageImpl> OdTvRasterImageImplPtr;


/** \details
This is an wrapper of the interface class for OdTvRasterImage object.

\remarks
The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvRasterImageWrapper : public OdTvRasterImage
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvRasterImage, OdTvRasterImageImpl)

  friend class OdTvDatabaseImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

  /** \details
  Return true if and only if this is the binary raster image. Otherwise it is a
  raster image based on the specified image file.
  */
  virtual bool isBinary(OdTvResult* rc = NULL) const;

  /** \details
  Return the type of the raster image
  */
  virtual Type getType(OdTvResult* rc = NULL) const;

  /** \details
  Returns the XY pixel size of the image for this object.
  */
  virtual OdTvVector2d getSize(OdTvResult* rc = NULL) const;

  /** \details
  Set the binary data for the raster image. The raster image object starts to be the binary

  \param format       [in]  A description of how data in the data array is packed
  \param width        [in]  The number of columns of pixels in this image
  \param height       [in]  The number of rows of pixels in this image
  \param data         [in]  An array of bytes, packed in accordance with format, that describes the colors of each pixel in the image.
  \param iAlignment   [in]  The scanline alignment in bytes.
  \param rc           [out] The code of the success or an error
  */
  virtual OdTvResult setBinaryData(OdTvRasterImage::Format format, OdUInt32 width, OdUInt32 height, const OdUInt8* data, OdUInt32 iAlignment = 4);

  /** \details
  Set the data for the palette based raster image. The raster image object starts to be the palette based

  \param paletteformat [in]  A description of how color data in the palette data array is packed
  \param paletteSize   [in]  The number of colors in palette
  \param paletteData   [in]  An array of bytes, packed in accordance with format, that describes the colors palette.
  \param bpi           [in]  A description of how an indexes in the data array is packed
  \param width         [in]  The number of columns of pixels in this image
  \param height        [in]  The number of rows of pixels in this image
  \param data          [in]  An array of bytes, packed in accordance with format, that describes the index in the palette for each pixel in the image.
  \param iAlignment    [in]  The scanline alignment in bytes.
  \param rc            [out] The code of the success or an error
  */
  virtual OdTvResult setPaletteData(OdTvRasterImage::Format paletteformat, OdUInt32 paletteSize, OdUInt8* paletteData,
                                    OdTvRasterImage::BitPerIndex bpi, OdUInt32 width, OdUInt32 height, const OdUInt8* data, OdUInt32 iAlignment = 4);

  /** \details
  Set the monochrome data for the raster image. The raster image object starts to be the monochrome based

  \param width        [in]  The number of columns of pixels in this image
  \param height       [in]  The number of rows of pixels in this image
  \param data         [in]  An array of bytes that describes the precense of the main color at each pixel in the image.
  \param bInverted    [in]  If true use background as main color.
  \param iAlignment   [in]  The scanline alignment in bytes.
  \param rc           [out] The code of the success or an error
  */
  virtual OdTvResult setMonochromeData(OdUInt32 width, OdUInt32 height, const OdUInt8* data, bool bInverted = false, OdUInt32 iAlignment = 4);

  /** \details
  Returns the format of the binary image data. In the case of source file based image
  this function returns kRGB and appropriate error code
  */
  virtual OdTvRasterImage::Format getFormat(OdTvResult* rc = NULL) const;

  /** \details
  Returns the alignment of the binary image data. In the case of source file based image this function returns 0 and appropriate error code
  */
  virtual OdUInt32 getAlignment(OdTvResult* rc = NULL) const;

  /** \details
  Returns the array of bytes, packed in accordance with format, that describes the colors of each pixel in the image.
  In the case of source file based image this function returns 0 and appropriate eerror code
  */
  virtual const OdUInt8* getBinaryData(OdTvResult* rc = NULL) const;

  /** \details
  Returns palette as palette size.
  In the case of image is not palette based image this function returns 0 and appropriate error code
  */
  virtual OdUInt32 getPaletteSize(OdTvResult* rc = NULL) const;

  /** \details
  Returns palette as the array of bytes, packed in accordance with palette format.
  In the case of image is not palette based image this function returns error code
  */
  virtual OdTvResult getPalette(OdUInt8* bytes) const;

  /** \details
  Returns number of bits for index in palette.
  In the case of image is not palette based image this function returns kFourBits and appropriate error code
  */
  virtual OdTvRasterImage::BitPerIndex getBitPerIndex(OdTvResult* rc = NULL) const;

  /** \details
  Returns true if monochrome colors are inverted.
  In the case of image is not monochrome based image this function returns false and appropriate error code
  */
  virtual bool getInverted(OdTvResult* rc = NULL) const;

  /** \details
  Sets the name of the source file containing the raster image
  */
  virtual OdTvResult setSourceFileName(const OdString& pathName);

  /** \details
  Returns the name of the source file containing the raster image
  */
  virtual OdString getSourceFileName(OdTvResult* rc = NULL) const;

  /** \details
  Loads the source image file for this object

  \remarks
  If the image file is currently loaded, the file will not be read.
  "Lazy loading" implies that the image file will not be loaded until it is required.
  */
  virtual OdTvResult load();

  /** \details
  Unloads the image for this object.
  */
  virtual OdTvResult unload();

  /** \details
  Returns true if and only if the image file for this object is loaded.
  */
  virtual bool isLoaded(OdTvResult* rc = NULL) const;
  /** \details
  Interpretates instance of OdTvRasterImage as OdGiRasterImage.
  */
  virtual OdGiRasterImagePtr getAsGiRasterImage( OdTvResult* rc = NULL ) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Internal methods
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  void updateReferencies();
};


/** \details
    This is an implementation of the iterator class for the raster images
*/
class ODTV_EXPORT OdTvRasterImagesIteratorImpl : public OdTvRasterImagesIterator
{
  friend class OdTvDatabaseImpl;
public:

  /** \details
    Returns true if and only if the traversal by this Iterator object is complete.
  */
  virtual bool done(OdTvResult* rc = NULL) const;

  /** \details
    Steps this Iterator object.
  */
  virtual OdTvResult step();

  /** \details
  Returns the raster image currently referenced by this Iterator object.
  */
  virtual OdTvRasterImageId getRasterImage(OdTvResult* rc = NULL) const;

  /** \details
  Positions this Iterator object at the specified linetype.
  \param objectId [in]  Linetype ID.
  */
  virtual OdTvResult seek(const OdTvRasterImageId& ImageId);

  /** \details
    Methods for creating the object
  */
  static OdTvRasterImagesIteratorPtr createObject(OdTvDbDictionaryIterator* pDbIterator);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvRasterImagesIteratorImpl();
  OdTvRasterImagesIteratorImpl(OdTvDbDictionaryIterator* pDbIterator);

  virtual ~OdTvRasterImagesIteratorImpl();

  // Db iterator
  OdTvDbDictionaryIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;
};

#include "TD_PackPop.h"

#endif //_ODTV_RASTERIMAGEIMPL_H_INCLUDED_
