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

#include "OdaCommon.h"
#include "Gs/Gs.h"
#include "RxDynamicModule.h"
#include "Gi/GiRasterImage.h"
#include "ExGsOpenGLVectorizeDevice.h"
#include "../../ExAlphaComp.h"
#include "../../ExBitsPerPixelConv.cpp"

class ExGsOpenGLBitmapVectorizeDevice : public ExGsOpenGLVectorizeDevice, OdGiRasterImage
{
ODRX_DECLARE_PROPERTY(RasterImage)
ODRX_DECLARE_PROPERTY(BitPerPixel)
protected:
  OdUInt8Array m_bits, m_bitsw;
  Pixmap m_xPixmap;
  GLXPixmap m_glPixmap;
  OdBitPerPixelConverter m_bpp;
public:
  ODRX_USING_HEAP_OPERATORS(ExGsOpenGLVectorizeDevice);

  ExGsOpenGLBitmapVectorizeDevice()
    : m_glPixmap(0)
  {
    m_bpp.init(this);
  }
  ~ExGsOpenGLBitmapVectorizeDevice()
  {
    if (m_bContextCreated)
      deleteContext();
  }

  static OdGsDevicePtr createObject()
  {
    return OdRxObjectImpl<ExGsOpenGLBitmapVectorizeDevice, OdGsDevice>::createObject();
  }
  
  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(ExGsOpenGLBitmapVectorizeDevice);
  
  bool supportPartialUpdate() const
  {
    return OdGsBaseVectorizeDevice::supportPartialUpdate();
  }

  void formatXError(const char *errStr)
  {
    OdString formatStr;
    formatStr.format(OD_T("X11: %s"), errStr);
    throw OdError(formatStr);
  }

  void createContext()
  {
    if (m_xConnection.display == NULL) // could be set outside
    {
      //m_xConnection.display = XOpenDisplay(getenv("DISPLAY"));
      m_xConnection.display = XOpenDisplay(NULL);
      if (m_xConnection.display == NULL)
        formatXError("XOpenDisplay failed");
    }
    m_bDoubleBufferEnabled = false;
    if (chooseVisual() == 0)
    {
      m_bDoubleBufferEnabled = true;
      chooseVisual();
    }
    ODA_ASSERT(m_xConnection.vinfo != NULL);
    if (m_xConnection.vinfo == NULL)
      formatXError("glXChooseVisual failed");
    m_xPixmap = XCreatePixmap(m_xConnection.display, DefaultRootWindow(m_xConnection.display), width(), height(), m_xConnection.vinfo->depth);
    m_glPixmap = glXCreateGLXPixmap(m_xConnection.display, m_xConnection.vinfo, m_xPixmap);
    m_xConnection.window = (Window)m_glPixmap;
    ExGsOpenGLVectorizeDevice::createContext();
  }
  void deleteContext()
  {
    ExGsOpenGLVectorizeDevice::deleteContext();
    if (m_glPixmap)
    {
      glXDestroyGLXPixmap(m_xConnection.display, m_glPixmap);
      XFreePixmap(m_xConnection.display, m_xPixmap);
      XCloseDisplay(m_xConnection.display);
      m_xConnection.display = NULL;
    }
  }

  void update(OdGsDCRect* pUpdatedRect = 0)
  {
    OdBitPerPixelConverter::TurnToOriginal _saveBPP(m_bpp);
    if (m_context != 0)
    {
      if (m_bits.size() != scanLineSize() * height())
      {
        deleteContext();
        createContext();
      }
    }
    m_bits.resize(scanLineSize() * height());
    const ODCOLORREF bkColor = getBackgroundColor();
    const bool bBGRA = colorDepth() == 32;
    const bool bTransparentBackground = bBGRA && (ODGETALPHA(bkColor) < 255);
    if (bTransparentBackground)
      setBackgroundColor(ODRGBA(255, 0, 255, 255));
    ExGsOpenGLVectorizeDevice::update(pUpdatedRect);
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    ::glPixelStorei(GL_PACK_ALIGNMENT  , 4);
    ::glReadPixels(0, 0, width(), height(), (!bBGRA) ? GL_BGR_EXT : GL_BGRA_EXT, GL_UNSIGNED_BYTE, m_bits.asArrayPtr());
    if (bTransparentBackground)
    { m_bitsw.resize(m_bits.size());
      setBackgroundColor(ODRGBA(0, 255, 0, 255));
      ExGsOpenGLVectorizeDevice::update(pUpdatedRect);
      ::glReadPixels(0, 0, width(), height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, m_bitsw.asArrayPtr());
      PixImageDescIn blackBg = { { m_bitsw.getPtr() + 0, m_bits.getPtr() + 1,
                                   m_bitsw.getPtr() + 2, m_bits.getPtr() + 3 }, 4, (OdInt32)scanLineSize() };
      PixImageDescIn whiteBg = { { m_bits.getPtr() + 0, m_bitsw.getPtr() + 1,
                                   m_bits.getPtr() + 2, m_bitsw.getPtr() + 3 }, 4, (OdInt32)scanLineSize() };
      PixImageDescOut outImg = { { m_bits.asArrayPtr() + 0, m_bits.asArrayPtr() + 1,
                                   m_bits.asArrayPtr() + 2, m_bits.asArrayPtr() + 3 }, 4, (OdInt32)scanLineSize() };
      ::computeAlphaTransparency(blackBg, whiteBg, width(), height(), outImg, bkColor);
      setBackgroundColor(bkColor);
    }
  }

  OdUInt32 get_BitPerPixel() const 
  { 
    return m_bpp.requestedBPP();
  }
  void put_BitPerPixel(OdUInt32 bitsPerPixel)
  {
    m_bpp.setRequestedBPP(bitsPerPixel);
  }

  // OdGiRasterImage interface

  OdUInt32 pixelWidth() const
  {
    return width();
  }
  OdUInt32 pixelHeight() const
  {
    return height();
  }
  OdUInt32 colorDepth() const
  {
    return odmax(24, m_bpp.getRequestedBPPValue());
  }
  OdUInt32 numColors() const
  {
    return 0;
  }
  ODCOLORREF color(OdUInt32 /*colorIndex*/) const
  {
    return ODRGB(0, 0, 0);
  }
  OdUInt32 paletteDataSize() const
  {
    return 0;
  }
  void paletteData(OdUInt8* /*pBytes*/) const
  {
  }
  void scanLines(OdUInt8* pBytes, OdUInt32 index, OdUInt32 numLines = 1) const
  {
    ::memcpy(pBytes, m_bits.asArrayPtr() + index * scanLineSize(), numLines * scanLineSize());
  }
  const OdUInt8* scanLines() const
  {
    return m_bits.getPtr();
  }
  PixelFormatInfo pixelFormat() const
  {
    OdGiRasterImage::PixelFormatInfo res;
    res.setBGRA();
    return res;
  }
  OdUInt32 scanLinesAlignment() const
  {
    return 4;
  }

  OdGiRasterImage *getRasterImage()
  {
    return m_bpp.getRasterImage(getBackgroundColor());
  }
  void putRasterImage(OdGiRasterImage* ) {}
};

ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(ExGsOpenGLBitmapVectorizeDevice)
  ODRX_INHERIT_PROPERTIES(ExGsOpenGLVectorizeDevice);
  ODRX_GENERATE_PROPERTY(RasterImage)
  ODRX_GENERATE_PROPERTY(BitPerPixel)
ODRX_END_DYNAMIC_PROPERTY_MAP(ExGsOpenGLBitmapVectorizeDevice)

ODRX_DEFINE_PROPERTY_OBJECT_PREFIX(ExGsOpenGLBitmapVectorizeDevice::, RasterImage, ExGsOpenGLBitmapVectorizeDevice, getRasterImage, putRasterImage, OdGiRasterImage)
ODRX_DEFINE_PROPERTY_PREFIX(ExGsOpenGLBitmapVectorizeDevice::, BitPerPixel, ExGsOpenGLBitmapVectorizeDevice, getInt32)

class WinOpenGLModule : public OdGsBaseModule
{
protected:
  void initApp()
  {
    OdGsBaseModule::initApp();
  }
  void uninitApp()
  {
    OdGsBaseModule::uninitApp();
  }

  OdSmartPtr<OdGsBaseVectorizeDevice> createDeviceObject()
  {
    return OdRxObjectImpl<ExGsOpenGLVectorizeDevice, OdGsBaseVectorizeDevice>::createObject();
  }

  OdSmartPtr<OdGsViewImpl> createViewObject()
  {
    return OdRxObjectImpl<ExGsOpenGLVectorizeView, OdGsViewImpl>::createObject();
  }

  OdSmartPtr<OdGsBaseVectorizeDevice> createBitmapDeviceObject()
  {
    return ExGsOpenGLBitmapVectorizeDevice::createObject();
  }

  OdSmartPtr<OdGsViewImpl> createBitmapViewObject()
  {
    return OdRxObjectImpl<ExGsOpenGLVectorizeView, OdGsViewImpl>::createObject();
  }
};

ODRX_DEFINE_DYNAMIC_MODULE(WinOpenGLModule);
