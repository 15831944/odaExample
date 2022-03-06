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

#include "Visualize2PdfCommands.h"
#include "PrcCommon.h"
#include "Ed/EdCommandContext.h"
#include "DbAux/PrcCommandContext.h"
#include "DynamicLinker.h"
#include "MemoryStream.h"
#include "DbBaseHostAppServices.h"
#include "PrcPreviewGenerator.h"
#include "PrcExtentsCalculator.h"

// Ge
#include "Ge/GeBoundBlock3d.h"
#include "Ge/GeExtents2d.h"
#include "Ge/GeLine2d.h"
#include "Ge/GePlane.h"

#include "ExStringIO.h"
#include "ExPrcCommandContext.h"
#include "ExPrcHostAppServices.h"
#include "Ed/EdCommandStack.h"
#include "PdfPublish/PdfPublish.h"
#include "PdfExport.h"
#include "DbUserIO.h"
#include "PrcDefaultContextForTD.h"
#include "AppServices/PrcHostAppServices.h"
#include "TvDatabase.h"
#include "Tools/TvExtendedView.h"
#include "Gi/GiRasterWrappers.h"

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"

//#define ENABLE_PATH_OUTPUT

OdString getResPath(CFStringRef resName, CFStringRef subfolder = NULL)
{
  CFURLRef appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(), resName, NULL, subfolder);
  if (appUrlRef == NULL)
    return OdString::kEmpty;
  CFStringRef filePathRef = CFURLCreateStringByReplacingPercentEscapes(NULL, CFURLCopyPath(appUrlRef), CFSTR(""));
  if (filePathRef == NULL)
    return OdString::kEmpty;
  const char* filePath = CFStringGetCStringPtr(filePathRef, kCFStringEncodingUTF8);

#ifdef ENABLE_PATH_OUTPUT
  // create message box
  SInt32 dlgRes = 0;
  CFUserNotificationRef pDlg = NULL;
  const void* keys[] = { kCFUserNotificationAlertHeaderKey, kCFUserNotificationAlertMessageKey };
  const void* vals[] = {
      CFSTR("Absolute path"),
      filePathRef
    };
  CFDictionaryRef dict = CFDictionaryCreate(0, keys, vals,
    sizeof(keys) / sizeof(*keys),
    &kCFTypeDictionaryKeyCallBacks,
    &kCFTypeDictionaryValueCallBacks);

  pDlg = CFUserNotificationCreate(kCFAllocatorDefault, 0,
    kCFUserNotificationPlainAlertLevel,
    &dlgRes, dict);
#endif

  // Release references
  CFRelease(filePathRef);
  CFRelease(appUrlRef);
  return OdString(filePath);
}
#endif

using namespace OdPdfPublish;
using namespace TD_PDF_2D_EXPORT;

enum Command
{
  kNone           = 0,
  kOpenIfcViewer  = 1
} m_currentCommand;

void Publish3DCommon(OdEdCommandContext* pCmdCtx, const OdTvDatabaseId& tvDbId);

void _OpenIfcViewerTemplate_func(OdEdCommandContext* pCmdCtx, const OdTvDatabaseId& tvDbId)
{
  m_currentCommand = kOpenIfcViewer;
  Publish3DCommon(pCmdCtx, tvDbId);
}

OdString GetResourcesPath()
{
  switch (m_currentCommand)
  {
  case kOpenIfcViewer:
#ifndef __APPLE__
    return OD_T("icons\\");
#endif
    break;
  }

  return OdString::kEmpty;
}

OdString correctPath(const OdString& filePath);

void addView(OdArtworkPtr pArtwork, const OdGePoint3d& camPos, const OdGePoint3d& targPos, const OdGeVector3d& upVec,
  const OdString& extName, const OdString& intName,
  Camera::Projection proj, double f_w, double f_h,
  const OdGeExtents3d& extPrc,
  Rendering::Mode rMode = Rendering::kDefault,
  Lighting::Mode lMode = Lighting::kDefault, bool bDefault = false, double camera_roll_angle = 0);

void addPageHeader(OdPagePtr& pPage, const OdString& sOutPdf, const OdUInt8 page_index);
void addPageFooter(OdPagePtr& pPage, const OdRect& rect);


class OdCmdVisualize2PdfHostAppServices : public OdExPrcHostAppServices
{
public:
  OdCmdVisualize2PdfHostAppServices() :m_pHost(NULL)
  {

  }

  /** \details
    Sets a source application services object.
    \param pHostApp [in] A pointer to a database application services object.
  */
  virtual void setSourceHostAppServices(OdDbBaseHostAppServices* pHost)
  {
    m_pHost = pHost;
  }

  /** \details
  Returns the gsBitmapDevice.

  \param pViewObj [in]  OdAbstractViewPE compatible object (OdGsView, OdDbViewport or etc.).
  \param pDb [in]  Pointer to the database context.
  \param flags [in]  Bitmap device flags.

  \remarks
  Returns the gsBitmapDevice associated with this source object, if specified, in another case returns the gsBitmapDevice associated with this HostAppServices object.
  */
  virtual OdGsDevicePtr gsBitmapDevice(OdRxObject* pViewObj = NULL, OdDbBaseDatabase* pDb = NULL, OdUInt32 flags = 0)
  {
//     if (NULL != m_pHost)
//       return m_pHost->gsBitmapDevice(pViewObj, pDb, flags);
    
    try
    {
      OdGsModulePtr pGsModule = ::odrxDynamicLinker()->loadModule(OdWinGLES2ModuleName);
      if (pGsModule.isNull())
      {
        pGsModule = ::odrxDynamicLinker()->loadModule(OdWinBitmapModuleName);
      }
      if (!pGsModule.isNull())
      {
        return pGsModule->createBitmapDevice();
      }
    }
    catch (const OdError&)
    {
    }
    return OdGsDevicePtr();
  }

private:
  OdDbBaseHostAppServices* m_pHost;
};


class PrcPublish3DFilter : public OdPrcContextForPdfExport
{
private:
  OdDbStubPtrArray m_selectedItems;

public:
  ODRX_DECLARE_MEMBERS(PrcPublish3DFilter);

  void setSelectedItems(const OdDbStubPtrArray& selectedItems)
  {
    m_selectedItems = selectedItems;
  }

  virtual bool shouldExportAsPRC(const OdGiDrawable* pDrawable,
    const OdGiPathNode* entity,
    const OdGsClientViewInfo* pView,
    OdUInt32& viewportidx) const
  {
    viewportidx = 0;

    if (!pDrawable || !pDrawable->id())
      return false;

    for (OdUInt32 i = 0; i < m_selectedItems.size(); i++)
    {
      if (m_selectedItems[i] == pDrawable->id())
      {
        return true; // publish this item
      }
    }

    return false;
  }
};

ODRX_CONS_DEFINE_MEMBERS(PrcPublish3DFilter, OdPrcContextForPdfExport, RXIMPL_CONSTR);


class FilterInit
{
public:
  FilterInit() {
    ::odrxDynamicLinker()->loadApp(OdPrcModuleName, false);
    ::odrxDynamicLinker()->loadApp(OdPdfPublishModuleName, false);
    ::odrxDynamicLinker()->loadApp(OdPrcPublish3dCmdsModuleName, false);

    PrcPublish3DFilter::rxInit();
  }
  ~FilterInit()
  {
    PrcPublish3DFilter::rxUninit();

    ::odrxDynamicLinker()->unloadModule(OdPrcPublish3dCmdsModuleName);
    ::odrxDynamicLinker()->unloadModule(OdPdfPublishModuleName);
    ::odrxDynamicLinker()->unloadModule(OdTv2PrcExportModuleName);
    ::odrxDynamicLinker()->unloadModule(OdPrcModuleName);
  }
};

void OpenIfcViewerTemplate_func(const OdStreamBufPtr& pStreamPrc, const OdPrcFilePtr& pPrcDb, const OdString& sOutPdf, const OdTvDatabaseId& tvDbId);

void Publish3DCommon(OdEdCommandContext* pCmdCtx, const OdTvDatabaseId& tvDbId)
{
  {
    OdPdfExportModulePtr pModule = ::odrxDynamicLinker()->loadApp(OdPdfExportModuleName, false);

    OdDbBaseDatabasePtr pDb(pCmdCtx->baseDatabase());
    if (pDb.isNull())
      return;

    OdEdUserIO* pIO = pCmdCtx->userIO();
    ODA_VERIFY(pIO);

    bool bAllEnt = pIO->getKeyword(OD_T("Publish all geometry [Yes/No]"), OD_T("Yes No"), 0) == 0;
    bool bPrcMode = pIO->getKeyword(OD_T("Prc mode [Tess/Brep]"), OD_T("Tess Brep"), 0) == 0;
    OdDbStubPtrArray selectedItems;
    OdString tmp;
    tmp.format(L"Select entities for Publish 3D <done>:");

    OdSelectionSetIteratorPtr pIter;
    ::odrxDynamicLinker()->loadApp(OdTv2PrcExportModuleName, false);
    if (!bAllEnt)
      pIter = ((OdTvDbUserIO*)pIO)->select(tmp, OdEd::kSelDefault)->newIterator();

    if (!pIter.isNull())
    {
      for (; !pIter->done(); pIter->next())
      {
        selectedItems.append(pIter->id());
      }
    }

    FilterInit autoRx;

    OdPrcContextForPdfExportPtr pPrcContext;
    if (bAllEnt)
    {
        pPrcContext = odCreatePrcAllInSingleViewContextForTD();
    }
    else
    {
      pPrcContext = PrcPublish3DFilter::createObject();
      ((PrcPublish3DFilter*)pPrcContext.get())->setSelectedItems(selectedItems);
    }

    OdString pdfPath = pIO->getFilePath(L"PDF path", OdEd::kGfpForSave, L"PDF path", L"PDF", L"", L"PDF files (*.pdf)|*.pdf");

    {
      OdPdfExportPtr exporter = pModule->create();
      PRCStreamsMap outStreamsPRC;
      PDFExportParams publishParams;
      publishParams.setDatabase(pDb);
      publishParams.setPRCContext(pPrcContext);
      publishParams.setPRCMode(bPrcMode ? PDFExportParams::kAsMesh : PDFExportParams::kAsBrep);

      OdUInt32 errCode = exporter->publish3d(publishParams, outStreamsPRC);
      if (errCode != 0)
      {
        OdString errMes = exporter->exportPdfErrorCode(errCode);
        printf("\nexportPdf error returned : 0x%x. \n%s", (unsigned)errCode, (const char*)errMes);
      }

      if (outStreamsPRC.empty())
        return;

      OdStreamBufPtr pStreamPrc = outStreamsPRC.begin()->second;
      pStreamPrc->rewind();


      OdStaticRxObject<OdCmdVisualize2PdfHostAppServices> prcHostAppServ;

      OdDbBaseDatabasePEPtr pPE = OdDbBaseDatabasePE::cast(pDb);
      if (!pPE.isNull())
      {
        OdDbBaseHostAppServices* pHost = pPE->appServices(pDb);
        if (pHost != NULL)
          prcHostAppServ.setSourceHostAppServices(pHost);
      }

      OdPrcFilePtr pPrcFile = prcHostAppServ.readFile(pStreamPrc);

      switch (m_currentCommand)
      {
      case kOpenIfcViewer:
        OpenIfcViewerTemplate_func(pStreamPrc, pPrcFile, pdfPath, tvDbId);
        break;
      }
    }
  }
}

class OdTvPreviewGenerator
{
public:

  enum ViewType
  {
    kCurrent = -1,  // Current camera position
    kTop      = 0,  //Camera from the top.
    kBottom   = 1,  //Camera from the bottom.
    kLeft     = 2,  //Camera from the left.
    kRight    = 3,  //Camera from the right.
    kFront    = 4,  //Front camera mode.
    kBack     = 5,  //Back camera mode.
    kLast
  };

  OdTvPreviewGenerator(const OdTvDatabaseId& tvDbId) : m_tvDb(tvDbId), m_pExtView(NULL)
  {
    // find active device and view
    if (!m_tvDb.isNull())
    {
      m_tvDeviceId = m_tvDb.openObject(OdTv::kForWrite)->createBitmapDevice(OD_T("PublishPreviewDevice"));

      OdTvGsDevicePtr pDevice = m_tvDeviceId.openObject(OdTv::kForWrite);
      if (pDevice.isNull())
        return;

      //copy data from database device
      OdTvDevicesIteratorPtr pDevicesIterator = m_tvDb.openObject()->getDevicesIterator();
      OdTvGsDevice::Name devname = OdTvGsDevice::kOpenGLES2;
      while (!pDevicesIterator->done())
      {
        OdTvGsDeviceId tvDevId = pDevicesIterator->getDevice();

        if (tvDevId != m_tvDeviceId)
        {
          // update the background color in device options
          OdTvGsDevicePtr pDbDevice = tvDevId.openObject();
          if (!pDevice.isNull() && !pDbDevice.isNull() && pDbDevice->getActive())
          {
            devname = pDbDevice->getGsDeviceName();
            //copy background
            pDevice->setBackgroundColor(ODRGB(192, 220, 248));

            //copy palette
            int nColors;
            const ODCOLORREF* pPalette = pDbDevice->getLogicalPalette(nColors);
            if (nColors > 0 && pPalette)
              pDevice->setLogicalPalette(pPalette, nColors);

            //collect all views
            OdTvGsViewId viewId = pDbDevice->getActiveView();

            m_activeViewId = pDevice->createView(OD_T("PublishBimapView"), false);
            copyViews(viewId, m_activeViewId);
            pDevice->addView(m_activeViewId);

            m_pExtView = new OdTvExtendedView(m_activeViewId);

            bool bBlockCache = false, bUseDynSubEntHlt = false, bFXAA = false;
            OdUInt32 nVal = 4;
            pDbDevice->getOption(OdTvGsDevice::kBlocksCache, bBlockCache);
            pDbDevice->getOption(OdTvGsDevice::kUseDynamicSubEntHlt, bUseDynSubEntHlt);
            pDbDevice->getOption(OdTvGsDevice::kFXAAEnable, bFXAA);
            pDbDevice->getOption(OdTvGsDevice::kFXAAQuality, nVal);

            pDevice->setOption(OdTvGsDevice::kBlocksCache, bBlockCache);
            pDevice->setOption(OdTvGsDevice::kUseDynamicSubEntHlt, bUseDynSubEntHlt);
            pDevice->setOption(OdTvGsDevice::kFXAAEnable, bFXAA);
            if (bFXAA)
              pDevice->setOption(OdTvGsDevice::kFXAAQuality, nVal);

            // apply shadows
            OdTvVisualStyleId visId = m_activeViewId.openObject()->getVisualStyle();
            bool isShadowEnabled = false;
            visId.openObject()->getOption(OdTvVisualStyleOptions::kDisplayShadow, isShadowEnabled);
            if (isShadowEnabled)
            {
              OdString modelName = OD_T("$GROUNDPLANE_MODEL_") + viewId.openObject()->getName();
              OdTvModelId shadowModel = m_tvDb.openObject()->findModel(modelName);
              if (!shadowModel.isNull())
              {
                m_activeViewId.openObject()->addModel(shadowModel);
              }
            }

            break;
          }
        }
        pDevicesIterator->step();
      }

      //used some default size to have correct deviation (not to detail)
      pDevice->setupGsBitmap(100, 100, devname);
    }
  }

  ~OdTvPreviewGenerator()
  {
    if (m_pExtView)
    {
      delete m_pExtView;
      m_pExtView = NULL;
    }

    if (!m_tvDeviceId.isNull())
    {
      m_tvDb.openObject(OdTv::kForWrite)->removeDevice(m_tvDeviceId);
    }
  }

  OdTvDatabaseId getTvDatabaseId() const { return m_tvDb; }
  OdTvGsDeviceId getTvDeviceId() const { return m_tvDeviceId; }
  OdTvGsViewId getActiveViewId() const { return m_activeViewId; }

  OdGiRasterImagePtrArray generatePreviewSet()
  {
    OdGiRasterImagePtrArray arr;
    if (m_tvDb.isNull() || m_tvDeviceId.isNull() || m_activeViewId.isNull())
      return arr;

    arr.push_back(generateByViewType(kCurrent));
    arr.push_back(generateByViewType(kFront));
    arr.push_back(generateByViewType(kBack));
    arr.push_back(generateByViewType(kTop));
    arr.push_back(generateByViewType(kBottom));
    arr.push_back(generateByViewType(kRight));
    arr.push_back(generateByViewType(kLeft));

    return arr;
  }

  OdGiRasterImagePtr generateByViewType(ViewType type = kCurrent)
  {
    // set view position
    if (type != kCurrent)
    {
      m_pExtView->setViewType((OdTvExtendedView::e3DViewType)type, false);
      m_pExtView->zoomToExtents();
    }

    OdTvGsDevicePtr pDev = m_tvDeviceId.openObject();
    pDev->update();

    return OdGiRasterImageHolder::createObject(pDev->getRasterImage());
  }

  void setImageSize(int w, int h)
  {
    if (m_tvDeviceId.isNull())
      return;
    OdTvDCRect rect(0, w, h, 0);
    m_tvDeviceId.openObject()->onSize(rect);
  }

protected:
    void copyViews(const OdTvGsViewId& from, const OdTvGsViewId& to)
    {
      OdTvGsViewPtr pFrom = from.openObject();
      OdTvGsViewPtr pTo = to.openObject(OdTv::kForWrite);
      pTo->setView(pFrom->position(), pFrom->target(), pFrom->upVector(), pFrom->fieldWidth(), pFrom->fieldHeight()
        , pFrom->isPerspective() ? OdTvGsView::kPerspective : OdTvGsView::kParallel);

      for (int i = 0; i < pFrom->numModels(); i++)
      {
        OdTvModelId modelId = pFrom->modelAt(i);
        if (modelId.openObject()->getName()[0] == '$')
          continue;
        m_mainModelId = modelId;
        pTo->addModel(m_mainModelId);
      }

      // visual style
      if (!pFrom->getVisualStyle().isNull())
        pTo->setVisualStyle(pFrom->getVisualStyle());
      // light
      pTo->enableDefaultLighting(pFrom->defaultLightingEnabled(), pFrom->defaultLightingType());
      pTo->setAmbientLightColor(pFrom->getAmbientLightColor());
      pTo->setDefaultLightingColor(pFrom->defaultLightingColor());
      pTo->setDefaultLightingIntensity(pFrom->defaultLightingIntensity());

      pTo->setMode(pFrom->mode());
    }

private:
  OdTvDatabaseId m_tvDb;
  OdTvGsDeviceId m_tvDeviceId;
  OdTvGsViewId m_activeViewId;
  OdTvExtendedView* m_pExtView;
  OdTvModelId m_mainModelId;
};

void OpenIfcViewerTemplate_func(const OdStreamBufPtr& pStreamPrc, const OdPrcFilePtr& pPrcDb, const OdString& sOutPdf, const OdTvDatabaseId& tvDbId)
{
  OdGeExtents3d extPrc = OdPrcExtentsCalculator::calculateExtents(pPrcDb);

//#define USE_PRC_PREVIEW_GENERATOR

#ifdef USE_PRC_PREVIEW_GENERATOR

  OdPrcPreviewGeneratorPtr pPreviewGen = OdPrcPreviewGenerator::createObject();
  ODA_VERIFY(pPreviewGen->init(pPrcDb) == OdPdfPublish::eOk);

  pPreviewGen->setBackground(ODRGB(192, 220, 248));
  pPreviewGen->setBitmapSize(170, 150);

  OdGiRasterImagePtrArray arrRasImg;
  ODA_VERIFY(pPreviewGen->generatePreviewSet(arrRasImg) == OdPdfPublish::eOk);

  pPreviewGen->setBitmapSize(1920, 1080);
  OdGiRasterImagePtr pPosterImg = pPreviewGen->generateByView(PrcPreviewGenerator::kDefault);

#else


  OdTvPoint defCamPos(-0.90612681748501411, -0.37532908821626582, 0.19509553088993711);
  OdTvPoint defCamTarget;
  OdTvVector defUpVec(0.18024483319542611, 0.074659669699104828, 0.98078424427943056);
  double defWidth = 100., defHeight = 100.;
  OdGiRasterImagePtr pPosterImg;
  OdGiRasterImagePtrArray arrRasImg;

  {
    OdTvPreviewGenerator previewGen(tvDbId);
    OdTvGsViewId viewId = previewGen.getActiveViewId();
    if (!viewId.isNull())
    {
      OdTvGsViewPtr pView = viewId.openObject();
      defCamPos = pView->position();
      defCamTarget = pView->target();
      defUpVec = pView->upVector();
      defWidth = pView->fieldWidth();
      defHeight = pView->fieldHeight();
    }

    previewGen.setImageSize(1920, 1080);
    pPosterImg = previewGen.generateByViewType();

    previewGen.setImageSize(170, 150);
    arrRasImg = previewGen.generatePreviewSet();
  }

#endif

  if (pStreamPrc.isNull() || arrRasImg.size() != 7 || !extPrc.isValidExtents() || sOutPdf.isEmpty())
    return;

  OdFilePtr pPublisher = OdFile::createObject();
  if (pPublisher.isNull())
    return;

  OdDocumentPtr pDoc = OdDocument::createObject();
  OdString creatorStr = OdString(TD_PRODUCT_NAME_START_W) + L" Publish";
  pDoc->setInformation(creatorStr + L" Template Document", creatorStr, L" Template Document", creatorStr);
  pDoc->setHostServices(pPrcDb->getAppServices());

  OdPagePtr pPage1 = OdPage::createObject();
  pPage1->setOrientation(Page::kLandscape);
  pDoc->addPage(pPage1);

  double width = 0., height = 0.;
  pPage1->getPaperSize(Page::kPixels, width, height);

  // add geometry
  Od2dGeometryBlockPtr pGeom = Od2dGeometryBlock::createObject();
  OdGePoint2dArray backgroundRect;
  backgroundRect.append(OdGePoint2d(0, 0));
  backgroundRect.append(OdGePoint2d(0, height));
  backgroundRect.append(OdGePoint2d(width, height));
  backgroundRect.append(OdGePoint2d(width, 0));

  pGeom->putColor(ODRGB(242, 242, 242));
  pGeom->startContour();
  pGeom->addLine(backgroundRect);
  pGeom->finishContour(Geometry::kFillEvenOdd);

  Od2dGeometryReferencePtr pGeomRef = Od2dGeometryReference::createObject();
  pGeomRef->setGeometryBlock(pGeom);
  pPage1->add2dGeometry(pGeomRef);

  addPageHeader(pPage1, sOutPdf, 0);

  OdCADModelPtr pModel = OdCADModel::createObject();
  pModel->setSource(pStreamPrc);
  OdAnnotationPtr pAnnot = OdAnnotation::createObject();
  pAnnot->setSource(pModel);
  pAnnot->setTransparentBackground(false);
  pAnnot->setBorderWidth(2);
  pAnnot->setName("Test 3D Annotation");
  pAnnot->setModelTreeVisibility(true);
  OdRect rect(9, 832, 30, 530);

  // add background for carousel
  OdGePoint2dArray carouselRect;
  carouselRect.append(OdGePoint2d(rect.m_min.x, rect.m_min.y));
  carouselRect.append(OdGePoint2d(rect.m_min.x, 130));
  carouselRect.append(OdGePoint2d(rect.m_max.x, 130));
  carouselRect.append(OdGePoint2d(rect.m_max.x, rect.m_min.y));

  Od2dGeometryBlockPtr pGeom2 = Od2dGeometryBlock::createObject();
  pGeom2->putColor(ODRGB(254, 254, 254));
  pGeom2->startContour();
  pGeom2->addLine(carouselRect);
  pGeom2->finishContour(Geometry::kFillEvenOdd);

  Od2dGeometryReferencePtr pGeomRef2 = Od2dGeometryReference::createObject();
  pGeomRef2->setGeometryBlock(pGeom2);
  pPage1->add2dGeometry(pGeomRef2);

  OdImagePtr posterImg = OdImage::createObject();
  posterImg->setImage(pPosterImg);
  pAnnot->setPosterImage(posterImg);
  pAnnot->setActivation(Activation::kExplicit);

  pPage1->addAnnotation(pAnnot, rect);

  double field_w = 100;
  double field_h = 100;

  OdArtworkPtr pArtwork = OdArtwork::createObject();

  //Front
  addView(pArtwork, OdGePoint3d(0, -1, 0), OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, L"Front", L"Front", Camera::kOrthographic, field_w, field_h, extPrc/*, Rendering::kIllustration, Lighting::kNight*/);
  //Back
  addView(pArtwork, OdGePoint3d(0, 1, 0), OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, L"Back", L"Back", Camera::kOrthographic, field_w, field_h, extPrc);
  //Top
  addView(pArtwork, OdGePoint3d(0, 0, 1), OdGePoint3d::kOrigin, OdGeVector3d::kYAxis, L"Top", L"Top", Camera::kOrthographic, field_w, field_h, extPrc);
  //Bottom
  addView(pArtwork, OdGePoint3d(0, 0, -1), OdGePoint3d::kOrigin, -OdGeVector3d::kYAxis, L"Bottom", L"Bottom", Camera::kOrthographic, field_w, field_h, extPrc);
  //Right
  addView(pArtwork, OdGePoint3d(1, 0, 0), OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, L"Right", L"Right", Camera::kOrthographic, field_w, field_h, extPrc);
  //Left
  addView(pArtwork, OdGePoint3d(-1, 0, 0), OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, L"Left", L"Left", Camera::kOrthographic, field_w, field_h, extPrc);
  //Default View
#ifdef USE_PRC_PREVIEW_GENERATOR
  OdGePoint3d defCamPos(-0.90612681748501411, -0.37532908821626582, 0.19509553088993711);
  OdGeVector3d defUpVec(0.18024483319542611, 0.074659669699104828, 0.98078424427943056);
  addView(pArtwork, defCamPos, OdGePoint3d::kOrigin, defUpVec, L"Default", L"Default", Camera::kOrthographic, field_w, field_h, extPrc, Rendering::kDefault, Lighting::kDefault, true);
#else
  addView(pArtwork, defCamPos, defCamTarget, defUpVec, L"Default", L"Default", Camera::kOrthographic, defWidth, defHeight, extPrc, Rendering::kDefault, Lighting::kDefault, true);
#endif
  pAnnot->setArtwork(pArtwork);

  // set next and previous buttons image
  OdImagePtr prevImage = OdImage::createObject();
  OdImagePtr nextImage = OdImage::createObject();
#ifdef __APPLE__
  prevImage->setFile(getResPath(CFSTR("prev.jpg"), CFSTR("icons")));
  nextImage->setFile(getResPath(CFSTR("next.jpg"), CFSTR("icons")));
#else
  prevImage->setFile(correctPath("prev.jpg"));
  nextImage->setFile(correctPath("next.jpg"));
#endif
  pAnnot->setCarouselScrollButtonsImages(prevImage, nextImage);

  // set background
  pAnnot->setCarouselButtonsFillColor(ODRGB(254, 254, 254));
  // set offset
  pAnnot->setCarouselButtonsOffset(10);
  // set font
  pAnnot->setCarouselButtonsFont(Text::kTimesBold);
  pAnnot->setCarouselButtonsFontSize(9);

  OdStringArray buttonNames;
  buttonNames.push_back(L"Default");
  buttonNames.push_back(L"Front");
  buttonNames.push_back(L"Back");
  buttonNames.push_back(L"Top");
  buttonNames.push_back(L"Bottom");
  buttonNames.push_back(L"Right");
  buttonNames.push_back(L"Left");
  pAnnot->setCarouselButtons(buttonNames, OdString::kEmpty, OdString::kEmpty, 1);

  OdImagePtrArray images;
  OdUInt32Array indices;
  for (OdUInt32 i = 0; i < buttonNames.size(); ++i)
  {
    indices.push_back(i % 7);
    OdImagePtr image = OdImage::createObject();
    image->setImage(arrRasImg[i]);
    images.push_back(image);
  }

  pAnnot->setCarouselViews(indices, images);

  addPageFooter(pPage1, rect);

  pPublisher->exportPdf(pDoc, sOutPdf);
}

void calculateCameraHelper(const OdGeBoundBlock3d& extents, OdGePoint3d& camPos, OdGePoint3d& targPos, OdGeVector3d& upVec,
  Camera::Projection& proj, double& f_w, double& f_h)
{
  OdGeBoundBlock3d tmp_ext = extents;

  if ((proj != Camera::kPerspective) && !extents.isBox())
  {
    tmp_ext.setToBox(true);
  }

  //set target to center of the scene
  OdGePoint3d newTarg = tmp_ext.center();
  OdGeVector3d viewDir = camPos - targPos;
  OdGeMatrix3d xEyeToWorld;
  {
    OdGeVector3d yVector = upVec;
    yVector.normalize();
    OdGeVector3d zVector = (camPos - targPos).normalize();
    OdGeVector3d xVector = yVector.crossProduct(zVector);
    xEyeToWorld.setCoordSystem(newTarg, xVector, yVector, zVector);
  }

  //rotate extents
  tmp_ext.transformBy(xEyeToWorld);

  OdGePoint3d min_pt = tmp_ext.minPoint(), max_pt = tmp_ext.maxPoint();

  double distance(0.0);

  if (proj == Camera::kPerspective)
  {
    const OdGePoint3d cameraPos = newTarg;
    const OdGeVector3d cameraY = upVec.normal();
    const OdGeVector3d cameraZ = (camPos - targPos).normalize();
    const OdGeVector3d cameraX = cameraY.crossProduct(cameraZ);

    const OdGeVector3d boxVecX(max_pt.x - min_pt.x, 0.0, 0.0),
      boxVecY(0.0, max_pt.y - min_pt.y, 0.0),
      boxVecZ(0.0, 0.0, max_pt.z - min_pt.z);
    const OdGePoint3d boxPt[8] = { min_pt, min_pt + boxVecX, min_pt + boxVecY, min_pt + boxVecZ,
                                    max_pt, max_pt - boxVecX, max_pt - boxVecY, max_pt - boxVecZ };

    // Project extents onto view plane
    OdGeExtents2d projectedExt;
    {
      for (int nPt = 0; nPt < 8; nPt++)
        projectedExt.addPoint(OdGePoint2d((boxPt[nPt] - cameraPos).dotProduct(cameraX), (boxPt[nPt] - cameraPos).dotProduct(cameraY)));
    }
    // Compute center of extents
    const OdGePoint2d extCenter = projectedExt.minPoint() + (projectedExt.maxPoint() - projectedExt.minPoint()) * 0.5;

    f_w = 2.0 * (projectedExt.maxPoint().x - projectedExt.minPoint().x);
    f_h = 2.0 * (projectedExt.maxPoint().y - projectedExt.minPoint().y);

    distance = odmax(f_w / 2.0, f_h / 2.0) / ::tan(OdaPI / 6.0);
  }
  else
  {
    f_w = fabs(max_pt.x - min_pt.x);//use fabs(...) for the case if min and max points are swapped
    f_h = fabs(max_pt.y - min_pt.y);

    //move the camera outside the object extents
    distance = odmax(newTarg.distanceTo(tmp_ext.maxPoint()), newTarg.distanceTo(tmp_ext.minPoint()));
  }

  viewDir = distance * viewDir;

  camPos = newTarg + viewDir;
  targPos = newTarg;
}

void addView(OdArtworkPtr pArtwork, const OdGePoint3d& camPos, const OdGePoint3d& targPos, const OdGeVector3d& upVec,
  const OdString& extName, const OdString& intName,
  Camera::Projection proj, double f_w, double f_h,
  const OdGeExtents3d& extPrc,
  Rendering::Mode rMode, Lighting::Mode lMode, bool bDefault, double camera_roll_angle)
{
  OdGePoint3d tmpCamPos = camPos;
  OdGePoint3d tmpTargPos = targPos;
  OdGeVector3d tmpUpVec = upVec;

  OdGeBoundBlock3d bbox(extPrc.minPoint(), extPrc.maxPoint());
  calculateCameraHelper(bbox, tmpCamPos, tmpTargPos, tmpUpVec, proj, f_w, f_h);
  //////////////////////////////////////////////////////////////////////////

  OdCameraPtr pCamera = OdCamera::createObject();
  pCamera->setPosition(tmpCamPos);
  pCamera->setTarget(tmpTargPos);
  pCamera->setUpVector(tmpUpVec);
  pCamera->setField(f_w, f_h);
  pCamera->setProjection(proj);
  pCamera->zoom(0.8);

  if (camera_roll_angle)
    pCamera->roll(camera_roll_angle);

  OdViewPtr pView = OdView::createObject();

  pView->setCamera(pCamera);
  pView->setExternalName(extName);
  pView->setInternalName(intName);
  pView->setDefault(bDefault);
  pView->setBackgroundColor(ODRGB(192, 220, 248));
  pView->setLighting(lMode);
  pView->setRendering(rMode);
  pArtwork->addView(pView);
}

OdString correctPath(const OdString& filePath)
{
  OdRxSystemServices* pSs = odrxSystemServices();
  if (pSs)
  {
    OdString validPath = filePath;

    if (pSs->accessFile(validPath, Oda::kFileRead))
      return validPath; // Found path as is.
    validPath.insert(0, GetResourcesPath());

    if (pSs->accessFile(validPath, Oda::kFileRead))
      return validPath;
    for (OdUInt32 i = 0; i < 6; i++)
    {
#if defined(ODA_WINDOWS)
      validPath.insert(0, "..\\");
#else
      validPath.insert(0, "..//");
#endif
      if (pSs->accessFile(validPath, Oda::kFileRead))
        return validPath;
    }
  }
  return OdString::kEmpty; // not found

};

void addTextFields(OdUInt32 iStartIndex, const OdString& sOutPdf, OdRect topTextRect, OdRect fieldRect, OdPagePtr& pPage)
{
  for (OdUInt32 i = iStartIndex; i < iStartIndex + 3; ++i)
  {
    OdTextFieldPtr field = OdTextField::createObject();
    OdString fieldName;
    fieldName.format(L"Field%i", i);
    field->setName(fieldName);
    field->setBorder(false);
    field->setFont(Text::kTimesBold);
    field->setTextJustification(Text::kLeft);
    field->setReadOnly(true);

    OdTextPtr text = OdText::createObject();
    text->setSize(8);

    if (i == iStartIndex)
    {
      OdInt32 outPos = sOutPdf.reverseFind(L'\\');
      if (-1 == outPos)
        outPos = sOutPdf.reverseFind(L'/');
      OdString outFileName = sOutPdf;
      if (-1 != outPos)
        outFileName = sOutPdf.right(sOutPdf.getLength() - outPos - 1);
      field->setDefaultValue(outFileName);
      text->setText(L"FILE NAME");
    }
    else if (i == iStartIndex + 1)
    {
      OdTimeStamp date;
      date.getLocalTime();
      OdString dateStr;
      date.strftime(L"%x", dateStr);
      field->setDefaultValue(dateStr);
      text->setText(L"DATE CREATED");
    }
    else if (i == iStartIndex + 2)
    {
      field->setDefaultValue(OdString(TD_PRODUCT_NAME_START_W) + L" Publish");
      text->setText(L"AUTHOR");
    }

    pPage->addTextField(field, fieldRect);

    fieldRect.m_min.x = fieldRect.m_max.x + 10;
    fieldRect.m_max.x = fieldRect.m_min.x + 160;

    topTextRect.m_min.x += 2;
    pPage->addText(text, topTextRect);

    topTextRect.m_min.x = fieldRect.m_min.x;
    topTextRect.m_max.x = fieldRect.m_max.x;
  }
}

void addPageHeader(OdPagePtr& pPage, const OdString& sOutPdf, const OdUInt8 page_index)
{
  OdImagePtr topLogo = OdImage::createObject();
  OdString validPath;
    
#ifdef __APPLE__
  validPath = getResPath(CFSTR("logo.jpg"), CFSTR("icons"));
#else
  validPath = correctPath("logo.jpg");
#endif
    
  if (validPath.isEmpty())
  {
    validPath = "logo.jpg";
    ODA_VERIFY(!"File 'logo.jpg' not found! Please copy this file from 'CommonApplications/Visualize/Examples/Visualize2Pdf/OpenIfcViewerTemplateResources...' to the folder in the support path.");
  }
  topLogo->setFile(validPath);
  OdRect topLogoRect(9, 256, 540, 584);
  pPage->addImage(topLogo, topLogoRect);

  OdRect fieldRect(332, 492, 564, 584);

  OdRect topTextRect = fieldRect;
  topTextRect.m_max.y = fieldRect.m_min.y - 3;
  topTextRect.m_min.y = topTextRect.m_max.y - 10;

  addTextFields(page_index * 3, sOutPdf, topTextRect, fieldRect, pPage);
}

void addPageFooter(OdPagePtr& pPage, const OdRect& rect)
{
  OdInt32 secondLineTop = 18;
  OdRect leftBottomTextRect1 = rect;
  leftBottomTextRect1.m_max.y = rect.m_min.y - 5;
  leftBottomTextRect1.m_min.y = secondLineTop;
  leftBottomTextRect1.m_max.x = rect.m_min.x + 10;

  OdTextPtr copText = OdText::createObject();
  copText->setSize(8);
  copText->setFont(Text::kSymbol);
  char copyright_char = (char)211;
  OdString copStr(&copyright_char, 1, CP_ASCII);
  copText->setText(copStr);

  pPage->addText(copText, leftBottomTextRect1);

  leftBottomTextRect1.m_min.x = leftBottomTextRect1.m_max.x;
  leftBottomTextRect1.m_max.x = rect.m_max.x / 2;
  OdTextPtr leftBottomText1 = OdText::createObject();
  leftBottomText1->setSize(8);
  OdString copyrightStr(TD_COPYRIGHT_END_W);
  leftBottomText1->setText(copyrightStr.right(copyrightStr.getLength() - 1));
  pPage->addText(leftBottomText1, leftBottomTextRect1);

  leftBottomTextRect1.m_min.x = rect.m_min.x;
  leftBottomTextRect1.m_max.x = 220;
  leftBottomTextRect1.m_min.y = 9;
  leftBottomTextRect1.m_max.y = secondLineTop;
  OdTextPtr leftBottomText2 = OdText::createObject();
  leftBottomText2->setSize(8);
  leftBottomText2->setText(L"10115 E Bell Road, Suite 107 #447 Scottsdale, AZ 85260, USA. ");
  pPage->addText(leftBottomText2, leftBottomTextRect1);

  leftBottomTextRect1.m_min.x = 220;
  leftBottomTextRect1.m_max.x = rect.m_max.x / 2;
  leftBottomTextRect1.m_min.y = 9;
  leftBottomTextRect1.m_max.y = secondLineTop;
  OdTextPtr leftBottomText3 = OdText::createObject();
  leftBottomText3->setSize(8);
  leftBottomText3->setFont(Text::kTimesBold);
  leftBottomText3->setText(L"www.opendesign.com");
  pPage->addText(leftBottomText3, leftBottomTextRect1);

  OdImagePtr bottomLogo = OdImage::createObject();
  OdString validPath;
#ifdef __APPLE__
  validPath = getResPath(CFSTR("small.jpg"), CFSTR("icons"));
#else
  validPath = correctPath("small.jpg");
#endif
    
  if (validPath.isEmpty())
  {
    validPath = "small.jpg";
    ODA_VERIFY(!"File 'small.jpg' not found! Please copy this file from 'Visualize/Example/Visualize2Pdf/...' to the folder in the support path.");
  }
  bottomLogo->setFile(validPath);
  OdRect bottomLogoRect;
  bottomLogoRect.m_min.x = 742;
  bottomLogoRect.m_max.y = rect.m_min.y - 5;
  bottomLogoRect.m_min.y = 3;
  bottomLogoRect.m_max.x = bottomLogoRect.m_min.x + (bottomLogoRect.m_max.y - bottomLogoRect.m_min.y);
  pPage->addImage(bottomLogo, bottomLogoRect);

  OdRect rightBottomTextRect1 = OdRect(bottomLogoRect.m_max.x + 3, 832, secondLineTop, rect.m_min.y - 5);
  OdTextPtr rightBottomText1 = OdText::createObject();
  rightBottomText1->setSize(8);
  rightBottomText1->setText(L"Created with");
  pPage->addText(rightBottomText1, rightBottomTextRect1);

  rightBottomTextRect1.m_max.y = secondLineTop;
  rightBottomTextRect1.m_min.y = 9;
  OdTextPtr rightBottomText2 = OdText::createObject();
  rightBottomText2->setSize(8);
  rightBottomText2->setFont(Text::kTimesBold);
  rightBottomText2->setText(OdString(TD_PRODUCT_NAME_START_W) + L" Publish");
  pPage->addText(rightBottomText2, rightBottomTextRect1);
}

