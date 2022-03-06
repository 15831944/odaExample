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

#ifndef _ODTV_RAWRASTERIMAGE_H_INCLUDED_
#define _ODTV_RAWRASTERIMAGE_H_INCLUDED_

#include "TD_PackPush.h"

#include "OdDbStub.h"
#include "TvRasterImage.h"
#include "GiRasterImage.h"


/** \details
This class implement the binary image
*/
class OdTvRawRasterImage : public OdGiRasterImage
{
protected:

  OdUInt32                m_Width;
  OdUInt32                m_Height;
  OdArray<OdUInt8>        m_Data;
  OdTvRasterImage::Format m_Format;
  OdUInt32                m_Alignment;
  
  OdUInt32                m_BytesPerPixel;
  OdUInt32                m_OneLineWidth;
  OdTvRasterImage::Type   m_type;
  TransparencyMode        m_transparencyMode;

  virtual void calcOneLineWidth();

public:

  ODRX_DECLARE_MEMBERS(OdTvRawRasterImage);

  OdTvRawRasterImage();
  virtual ~OdTvRawRasterImage();

  void initialize(OdTvRasterImage::Format format, OdUInt32 width, OdUInt32 height, const OdUInt8* data, OdUInt32 iAlignment);

  OdTvRasterImage::Type getType() {return m_type;}

  //**************************
  // OdGiRasterImage interface
  //**************************
  virtual OdUInt32 pixelWidth() const { return m_Width; }
  virtual OdUInt32 pixelHeight() const { return m_Height; }
  virtual OdUInt32 colorDepth() const { return m_BytesPerPixel * 8; }
  virtual OdUInt32 numColors() const { return 0; }
  virtual ODCOLORREF color(OdUInt32 /*colorIndex*/) const { return 0; }
  virtual OdUInt32 paletteDataSize() const { return 0; }
  virtual void paletteData(OdUInt8* /*bytes*/) const { }
  virtual OdTvRasterImage::Format format() const { return m_Format; }
  virtual PixelFormatInfo pixelFormat() const
  {
    PixelFormatInfo pf;
    switch (m_Format)
    {
    case OdTvRasterImage::kRGB:   pf.setRGB();      break;
    case OdTvRasterImage::kRGBA:  pf.setRGBA();     break;
    case OdTvRasterImage::kBGR:    pf.setBGR();      break;
    case OdTvRasterImage::kBGRA:   pf.setBGRA();     break;
    case OdTvRasterImage::kBGR_16: pf.set16bitBGR(); break;
    }
    return pf;
  }
  virtual OdUInt32 scanLinesAlignment() const { return m_Alignment; }
  virtual const OdUInt8* scanLines() const { return m_Data.getPtr(); }
  virtual void scanLines(OdUInt8* scnLines, OdUInt32 firstScanline, OdUInt32 numLines = 1) const
  {
    const OdUInt8 *Data = m_Data.getPtr();
    if (firstScanline)
      Data += firstScanline * m_OneLineWidth;
    if (numLines)
      memcpy(scnLines, Data, numLines * m_OneLineWidth);
  }
  virtual TransparencyMode transparencyMode() const;


  //**************************
  // read/write interface (loading/saving from/to VSF file)
  //**************************
  virtual OdResult read(OdDbDwgFiler* pFiler, OdTvVSFVersion ver);
  virtual void write(OdDbDwgFiler* pFiler, OdTvVSFVersion ver) const;

  virtual unsigned int getInternalObjectSize(OdTvResult* rc) const;
};
typedef OdSmartPtr<OdTvRawRasterImage> OdTvRawRasterImagePtr;


/** \details
This class implement the binary image based on the palette
*/
class OdTvRawPaletteRasterImage : public OdTvRawRasterImage
{
protected:

  OdArray<OdUInt8>                 m_PaletteData;
  OdTvRasterImage::BitPerIndex     m_bpi;

  OdUInt32 getBPI() const
  {
    if (m_bpi == OdTvRasterImage::kFourBits)
      return 4;

    return 8;
  }

  virtual void calcOneLineWidth();

public:

  ODRX_DECLARE_MEMBERS(OdTvRawPaletteRasterImage);

  OdTvRawPaletteRasterImage();
  virtual ~OdTvRawPaletteRasterImage();

  void initialize(OdTvRasterImage::Format paletteformat, OdUInt32 paletteSize, OdUInt8* paletteData,
    OdTvRasterImage::BitPerIndex bpi, OdUInt32 width, OdUInt32 height, const OdUInt8* data, OdUInt32 iAlignment);

  OdTvRasterImage::BitPerIndex getBitPerIndex() { return m_bpi;}

  //**************************
  // OdGiRasterImage interface
  //**************************
  virtual OdUInt32 colorDepth() const { return getBPI(); }
  virtual OdUInt32 numColors() const { return m_PaletteData.size() / m_BytesPerPixel; }
  virtual ODCOLORREF color(OdUInt32 colorIndex) const;
  virtual OdUInt32 paletteDataSize() const { return m_PaletteData.size(); }
  virtual void paletteData(OdUInt8* bytes) const { ::memcpy(bytes, m_PaletteData.getPtr(), m_PaletteData.size()); }

  //**************************
  // read/write interface (loading/saving from/to VSF file)
  //**************************
  virtual OdResult read(OdDbDwgFiler* pFiler, OdTvVSFVersion ver);
  virtual void write(OdDbDwgFiler* pFiler, OdTvVSFVersion ver) const;

  virtual unsigned int getInternalObjectSize(OdTvResult* rc) const;
};
typedef OdSmartPtr<OdTvRawPaletteRasterImage> OdTvRawPaletteRasterImagePtr;


/** \details
This class implement the monochrome binary image
*/
class OdTvRawMonochromeRasterImage : public OdTvRawPaletteRasterImage
{
protected:

  bool m_bInverted;

  virtual void calcOneLineWidth();

public:

  ODRX_DECLARE_MEMBERS(OdTvRawMonochromeRasterImage);

  OdTvRawMonochromeRasterImage();
  virtual ~OdTvRawMonochromeRasterImage();

  void initialize(OdUInt32 width, OdUInt32 height, const OdUInt8* data, bool bInverted, OdUInt32 iAlignment);

  //**************************
  // OdGiRasterImage interface
  //**************************
  virtual OdUInt32 colorDepth() const { return 1; }
  virtual bool inverted() const { return m_bInverted; }

  //**************************
  // read/write interface (loading/saving from/to VSF file)
  //**************************
  virtual OdResult read(OdDbDwgFiler* pFiler, OdTvVSFVersion ver);
  virtual void write(OdDbDwgFiler* pFiler, OdTvVSFVersion ver) const;

  virtual unsigned int getInternalObjectSize(OdTvResult* rc) const;
};
typedef OdSmartPtr<OdTvRawMonochromeRasterImage> OdTvRawMonochromeRasterImagePtr;


#include "TD_PackPop.h"

#endif //_ODTV_RAWRASTERIMAGE_H_INCLUDED_
