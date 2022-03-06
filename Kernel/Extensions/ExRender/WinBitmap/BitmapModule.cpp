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

// WinBitmapModule.cpp : Defines the initialization routines for the DLL.
//
#include "OdaCommon.h"
#include "GsBitmapVectorizer.h"
#include "CommonDeviceProps.h"
#include "RxDynamicModule.h"
#include "Gi/GiRasterWrappers.h"
#include "ExAlphaComp.h"

#if defined(_TOOLKIT_IN_DLL_) && defined(_MSC_VER)

extern "C" int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID )
{
  switch ( dwReason )
  {
  case DLL_PROCESS_ATTACH:
    // remove this if you need per-thread initialization
    DisableThreadLibraryCalls( (HMODULE)hInstance );
    break;
  }
  return TRUE;
}

#endif //_TOOLKIT_IN_DLL_

#if defined(ODA_WINDOWS) && !defined(_WINRT)

#include "win/ExGsScreenDevice.h"
#include "win/ExGsWin32Device.h"

class _ExBitmap2ScreenDevice : public ExGsWin32Device,
                               public OdGsBitmapVectorizeDevice
{
public:
  ODRX_USING_HEAP_OPERATORS(OdGsBitmapVectorizeDevice);
  virtual void createContext() {} // no any context creation required*/
  // virtual void deleteContext() {} // no any context deletion required*/
};

class ExBitmap2ScreenDevice : public ExGsScreenDevice<_ExBitmap2ScreenDevice>
{
public:
  static OdGsDevicePtr createObject()
  {
    return OdRxObjectImpl<ExBitmap2ScreenDevice, OdGsDevice>::createObject();
  }
  ODRX_DECLARE_PROPERTY(EnableSoftwareHLR)
  ODRX_DECLARE_PROPERTY(PrecisionMode)

  OdRxDictionaryPtr properties() { return this; }

  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(ExBitmap2ScreenDevice);

  void update(OdGsDCRect* pUpdatedRect)
  {
    ExGsScreenDevice<_ExBitmap2ScreenDevice>::update(pUpdatedRect);
    BITMAPINFO* pHeader;
    OdUInt8Array headerMemCont;
    headerMemCont.resize(sizeof(BITMAPINFOHEADER) /*+ pImg->paletteDataSize()*/);
    pHeader = (BITMAPINFO*)headerMemCont.getPtr();
    pHeader->bmiHeader.biBitCount = (WORD)colorDepth();
    pHeader->bmiHeader.biClrImportant = 0;
    pHeader->bmiHeader.biClrUsed = 0;
    pHeader->bmiHeader.biCompression = BI_RGB;
    pHeader->bmiHeader.biHeight = height();
    pHeader->bmiHeader.biPlanes = 1;
    pHeader->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pHeader->bmiHeader.biSizeImage = 0;
    pHeader->bmiHeader.biWidth = width();
    pHeader->bmiHeader.biXPelsPerMeter = 0;
    pHeader->bmiHeader.biYPelsPerMeter = 0;
    // pImg->paletteData((OdUInt8*)pHeader->bmiColors);

    OdUInt8* pBuf;
    HBITMAP hBmp = CreateDIBSection(NULL, pHeader, DIB_RGB_COLORS, (void**)&pBuf, NULL, 0);
    scanLines(pBuf, 0, height());

    HDC sourceDC = CreateCompatibleDC(m_hDC);
    SelectObject(sourceDC, hBmp);
    BitBlt(m_hDC, 0, 0, width(), height(), sourceDC, 0, 0, SRCCOPY);
    DeleteDC(sourceDC);
    DeleteObject(hBmp);
  }
};

#endif // defined(ODA_WINDOWS) && !defined(_WINRT)

// CORE-11600 problem with bmpout command of OLE on Linux ////#if defined(ODA_WINDOWS) && !defined(_WINRT)
//#ifndef _WIN32_WCE

#include "ExOwnerDrawDc.cpp"

class ExGsBitmapVectorizeView : public OdGsBitmapVectorizeView
{
  public:
    ExGsBitmapVectorizeView()
      : OdGsBitmapVectorizeView()
    {
    }
    ~ExGsBitmapVectorizeView()
    {
    }

    void ownerDrawDc(const OdGePoint3d& _origin,
                     const OdGeVector3d& _u,
                     const OdGeVector3d& _v,
                     const OdGiSelfGdiDrawable* pDrawable,
                     bool bDcAligned,
                     bool bAllowClipping)
    {
      //next is useless via code in OdGsBitmapVectorizeView::setMode
      //if (renderMode() >= OdGsView::kHiddenLine) 
      //  return;

      onTraitsModified();
      ::exOwnerDrawDc(_origin, _u, _v, pDrawable, (getRenderMode() == k2DOptimized) && bDcAligned, bAllowClipping, *this);
    }
};

//#else
//typedef OdGsBitmapVectorizeView ExGsBitmapVectorizeView;
//#endif
////#endif // defined(ODA_WINDOWS) && !defined(_WINRT)

#if !(defined(ODA_WINDOWS) && !defined(_WINRT)) // #else // WIN32

//DD:EXPORT_ON

class ExBitmap2ScreenDevice : public OdGsBitmapVectorizeDevice,
                              public OdCommonDeviceProps
{
  ODRX_USING_HEAP_OPERATORS(OdGsBitmapVectorizeDevice);
public:
  static OdGsDevicePtr createObject()
  {
    return OdRxObjectImpl<ExBitmap2ScreenDevice, OdGsDevice>::createObject();
  }
  ODRX_DECLARE_PROPERTY(EnableSoftwareHLR)
  ODRX_DECLARE_PROPERTY(PrecisionMode)

  OdRxDictionaryPtr properties() { return (OdRxDictionary*)this; }

  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(ExBitmap2ScreenDevice);
};

// CORE-11600 problem with bmpout of OLE on Linux //typedef OdGsBitmapVectorizeView ExGsBitmapVectorizeView;

#endif // WIN32

  ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(ExBitmap2ScreenDevice)
    #if defined(ODA_WINDOWS) && !defined(_WINRT) && !defined(ODA_WINDOWS_GCC)
    ODRX_INHERIT_PROPERTIES(ExGsScreenDevice<_ExBitmap2ScreenDevice>);
    #else
    ODRX_INHERIT_PROPERTIES(OdCommonDeviceProps);
    #endif
    ODRX_GENERATE_PROPERTY(EnableSoftwareHLR)
    ODRX_GENERATE_PROPERTY(PrecisionMode)
  ODRX_END_DYNAMIC_PROPERTY_MAP(ExBitmap2ScreenDevice)

ODRX_DEFINE_PROPERTY_PREFIX(ExBitmap2ScreenDevice::, EnableSoftwareHLR, ExBitmap2ScreenDevice, getBool)
ODRX_DEFINE_PROPERTY_PREFIX(ExBitmap2ScreenDevice::, PrecisionMode    , ExBitmap2ScreenDevice, getBool)

class ExBitmapDevice : public OdGsBitmapVectorizeDevice,
                       public OdCommonDeviceProps
{
  OdUInt32 m_outColDepth;
  OdGiPixelBGRA32Array m_bgraData;
  OdGiRasterImagePtr m_pTransparentImg;

  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(ExBitmapDevice);

  ODRX_DECLARE_PROPERTY(RasterImage)
  ODRX_DECLARE_PROPERTY(BitPerPixel)
  ODRX_DECLARE_PROPERTY(EnableSoftwareHLR)
  ODRX_DECLARE_PROPERTY(PrecisionMode)

  ODRX_USING_HEAP_OPERATORS(OdGsBitmapVectorizeDevice);

public:
  ExBitmapDevice() : m_outColDepth(24) {}
  virtual ~ExBitmapDevice() {}

  OdRxDictionaryPtr properties() { return (OdRxDictionary*)this; }

  static OdGsDevicePtr createObject()
  {
    return OdRxObjectImpl<ExBitmapDevice, OdGsDevice>::createObject();
  }

  OdGiRasterImagePtr getRasterImage()
  {
    if (m_outColDepth > 24)
      return m_pTransparentImg;
    else if (m_outColDepth == 24)
      return (OdGiRasterImage*)this;
    OdSmartPtr<OdGiRasterImageDesc> pDestDesc = OdRxObjectImpl<OdGiRasterImageDesc>::createObject();
    pDestDesc->setPixelWidth(pixelWidth());
    pDestDesc->setPixelHeight(pixelHeight());
    pDestDesc->setColorDepth(m_outColDepth);
    pDestDesc->pixelFormat().setBGRA();
    if (m_outColDepth > 4) // 256 color palette
      pDestDesc->setPalette(sizeof(ODCOLORREF)*m_logPalette.size(), (OdUInt8*)getPalette());
    else if (m_outColDepth > 1) // 16 color palette
    { const RGBQUAD pPal[16] = { { 0, 0, 0, 0 }, { 0, 0, 128, 0 }, { 0, 0, 255, 0 }, { 255, 0, 255, 0 }, { 128, 128, 0, 0 },
        { 0, 128, 0, 0 }, { 0, 255, 0, 0 }, { 255, 255, 0, 0 }, { 128, 0, 0, 0 }, { 128, 0, 128, 0 }, { 255, 0, 0, 0 },
        { 192, 192, 192, 0 }, { 128, 128, 128, 0 }, { 0, 128, 128, 0 }, { 0, 255, 255, 0 }, { 255, 255, 255, 0 } };
      pDestDesc->setPalette(sizeof(RGBQUAD) * 16 + 1, (OdUInt8*)pPal);
    } else // Monochrome palette
    { const RGBQUAD pPal[2] = { { 0, 0, 0, 0 }, { 255, 255, 255, 0 } };
      pDestDesc->setPalette(sizeof(RGBQUAD) * 2 + 1, (OdUInt8*)pPal);
    }
    pDestDesc->setScanLinesAlignment(scanLinesAlignment());
    return convert(false, 50.0, 50.0, 0.0, 0, false, false, false, pDestDesc);
  }
  void putRasterImage(OdGiRasterImage* ) {}

  OdUInt32 get_BitPerPixel() const
  {
    return m_outColDepth;
  }
  void put_BitPerPixel(OdUInt32 colDepth)
  {
    m_outColDepth = colDepth;
  }

  void update(OdGsDCRect *pUpdatedRect)
  { const ODCOLORREF bkColor = getBackgroundColor();
  const bool bTransparentBackground = (m_outColDepth == 32) && (ODGETALPHA(bkColor) < 255);
    if (bTransparentBackground)
      setBackgroundColor(ODRGBA(0, 0, 0, 255));
    OdGsBitmapVectorizeDevice::update(pUpdatedRect);
    if (m_outColDepth > 24)
    { const OdUInt32 nWidth = pixelWidth(), nHeight = pixelHeight(), nScanSize = scanLineSize();
      m_bgraData.resize(nWidth * nHeight);
      for (OdUInt32 nY = 0; nY < nHeight; nY++)
      { OdGiPixelBGRA32 *pOut = m_bgraData.asArrayPtr() + nY * nWidth;
        const OdUInt8 *pIn = scanLines() + nY * nScanSize;
        for (OdUInt32 nX = 0; nX < nWidth; nX++, pOut++, pIn += 3)
          pOut->setBGRA(pIn[0], pIn[1], pIn[2], 255);
      }
      if (bTransparentBackground)
      {
        setBackgroundColor(ODRGBA(255, 255, 255, 255));
        OdGsBitmapVectorizeDevice::update(pUpdatedRect);
        OdUInt8 *pBlackSrc = (OdUInt8*)m_bgraData.asArrayPtr();
        PixImageDescIn blackBg = { { pBlackSrc + 0, pBlackSrc + 1, pBlackSrc + 2, pBlackSrc + 3 }, 4, (OdInt32)nWidth * 4 };
        PixImageDescIn whiteBg = { { scanLines() + 0, scanLines() + 1, scanLines() + 2, NULL }, 3, (OdInt32)nScanSize };
        PixImageDescOut outImg = { { pBlackSrc + 0, pBlackSrc + 1, pBlackSrc + 2, pBlackSrc + 3 }, 4, (OdInt32)nWidth * 4 };
        ::computeAlphaTransparency(blackBg, whiteBg, nWidth, nHeight, outImg, bkColor);
        setBackgroundColor(bkColor);
      }
      OdGiImageBGRA32 bim(nWidth, nHeight, m_bgraData.asArrayPtr());
      m_pTransparentImg = OdGiRasterImageBGRA32Holder::createObject(&bim);
    }
  }
};

  ODRX_BEGIN_DYNAMIC_PROPERTY_MAP(ExBitmapDevice)
    ODRX_INHERIT_PROPERTIES(OdCommonDeviceProps);
    ODRX_GENERATE_PROPERTY(RasterImage)
    ODRX_GENERATE_PROPERTY(BitPerPixel)
    ODRX_GENERATE_PROPERTY(EnableSoftwareHLR)
    ODRX_GENERATE_PROPERTY(PrecisionMode)
  ODRX_END_DYNAMIC_PROPERTY_MAP(ExBitmapDevice)

ODRX_DEFINE_PROPERTY_OBJECT_PREFIX(ExBitmapDevice::, RasterImage, ExBitmapDevice, getRasterImage().get, putRasterImage, OdGiRasterImage)
ODRX_DEFINE_PROPERTY_PREFIX(ExBitmapDevice::, BitPerPixel, ExBitmapDevice, getInt32)
ODRX_DEFINE_PROPERTY_PREFIX(ExBitmapDevice::, EnableSoftwareHLR, ExBitmapDevice, getBool)
ODRX_DEFINE_PROPERTY_PREFIX(ExBitmapDevice::, PrecisionMode    , ExBitmapDevice, getBool)

class BitmapModule : public OdGsBaseModule
{
protected:
  void initApp()
  {
    OdGsBaseModule::initApp();
    // put your module initialization here
  }
  void uninitApp()
  {
    // put your module uninitialization (possible rxUninit) here
    OdGsBaseModule::uninitApp();
  }

  OdSmartPtr<OdGsBaseVectorizeDevice> createDeviceObject()
  {
    OdGsDevicePtr pDev = ExBitmap2ScreenDevice::createObject();
    return pDev;
  }

  OdSmartPtr<OdGsViewImpl> createViewObject()
  {
    return OdRxObjectImpl<ExGsBitmapVectorizeView, OdGsViewImpl>::createObject();
  }

  OdSmartPtr<OdGsBaseVectorizeDevice> createBitmapDeviceObject()
  {
    return ExBitmapDevice::createObject();
  }

  OdSmartPtr<OdGsViewImpl> createBitmapViewObject()
  {
    return OdRxObjectImpl<ExGsBitmapVectorizeView, OdGsViewImpl>::createObject();
  }
};

ODRX_DEFINE_DYNAMIC_MODULE(BitmapModule);

//DD:EXPORT_OFF
