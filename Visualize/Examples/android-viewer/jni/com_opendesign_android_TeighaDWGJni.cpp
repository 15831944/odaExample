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

#include <jni.h>
#include <time.h>
#include <android/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <OdaCommon.h>
#include "RxInit.h"
#include <OdAnsiString.h>
#include <OdCharMapper.h>
#include <diagnostics.h>

#include <Gs/Gs.h>
#include <DbDatabase.h>
#include <GiContextForDbDatabase.h>
#include <DbGsManager.h>
#include "AndroidAppServices.h"
#include <Gs/GsBaseVectorizer.h>
#include <RxDynamicModule.h>
#include <ColorMapping.h>
#include <AbstractViewPE.h>
#include "TvCoreModulesNames.h"

#ifdef DWF_MODULES_ENABLED
// For DWFimport
#include "DwfImport.h"
using namespace TD_DWF_IMPORT;
#endif

#ifdef COLLADA_ENABLED
#include "ColladaImport.h"
using namespace TD_COLLADA_IMPORT;
#endif
#include "RxVariantValue.h"

// For rasterImport
#include "DbRasterImageDef.h"
#include "DbRasterImage.h"
#include "DbBlockTableRecord.h"
#include "DbDictionary.h"
#include "PreFileLoader.h"
#include "TvModuleNames.h"
#include "OdModuleNames.h"
#include <mutex>
#include "TvDatabase.h"
#include "TvFactory.h"
#include "TvError.h"
#include "TvGsView.h"
#include "Trackers.h"
#include "ObjectExplorerCreator.h"

// Visualize API
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxCommonDataAccessModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvDbIOModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ISMModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(SCENEOEModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvTfModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvDbPartialViewingModuleImpl);
//Visualize device
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(VisualizeDeviceModule);

//Raster images
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRasterProcessingServicesImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);
//Device
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTrGL2RenderModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(GLES2Module);

ODRX_BEGIN_STATIC_MODULE_MAP()
ODRX_DEFINE_STATIC_APPMODULE(OdTvModuleName, OdTvModule)
ODRX_DEFINE_STATIC_APPMODULE(RxCommonDataAccessModuleName, OdRxCommonDataAccessModule)
ODRX_DEFINE_STATIC_APPMODULE(L"TV_SCENEOE", SCENEOEModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvDbIOAppName, OdTvDbIOModule)
ODRX_DEFINE_STATIC_APPMODULE(L"TV_ISM", ISMModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvTfModuleName, OdTvTfModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvPartialViewingModuleName, OdTvDbPartialViewingModuleImpl)

ODRX_DEFINE_STATIC_APPMODULE(OdTvVisualizeDeviceModuleName, VisualizeDeviceModule)

ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName, OdRasterProcessingServicesImpl)
ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME, ExRasterModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTrGL2ModuleName, OdTrGL2RenderModule)
ODRX_DEFINE_STATIC_APPMODULE(OdWinGLES2ModuleName, GLES2Module)
ODRX_END_STATIC_MODULE_MAP()

#define LOG_TAG "TeighaDWGJni"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define LOG_EXCEPTION(e) LOGE("Exception Caught: %s\n", (const char *)e.description())

static void _MyAssert(const char *expression, const char *fileName, int nLineNo)
{
  LOGW("Assertion Failed: %s, File: %s, Line: %d\n", expression, fileName, nLineNo);
}

static OdString jstringToOdString(JNIEnv *pEnv, jstring javaString)
{
  jboolean isCopy = false;
  const char *pUTF = pEnv->GetStringUTFChars(javaString, &isCopy);
  OdCharArray unicodeBuf;
  OdCharMapper::utf8ToUnicode(pUTF, strlen(pUTF), unicodeBuf);
  pEnv->ReleaseStringUTFChars(javaString, pUTF);
  return OdString(unicodeBuf.getPtr());
}

static OdTvDatabaseId dbId;
//OdTvGsDeviceId deviceId;
static OdTvDCRect screenRect;
static OdString fileName;
static bool isGLUpdate = false;
static std::mutex m_UpdateBlock;
static SelectionFrame frame;
static ObjectExplorerCreator objectExplorer;
static ObjectNode* currentNode;

OdTvGsDeviceId getActiveDevice(const OdTvDatabaseId &dId)
{
  if (dId.isNull())
    return OdTvGsDeviceId();
  OdTvDevicesIteratorPtr pIt = dId.openObject()->getDevicesIterator();
  if (!pIt.isNull())
    return pIt->getDevice();
  return OdTvGsDeviceId();
}

OdGeExtents3d getActiveExtents()
{
  OdGeBoundBlock3d box;
  OdTvGsViewId vId = getActiveDevice(dbId).openObject()->getActiveView();
  OdTvGsViewPtr view = vId.openObject(OdTv::kForWrite);

  view->viewExtents(box);

  OdGeMatrix3d xWorldToEye = view->viewingMatrix();
  OdGeMatrix3d xEyeToWorld = xWorldToEye.invert();

  OdGePoint3d min = box.minPoint();
  OdGePoint3d max = box.maxPoint();

  min.transformBy(xEyeToWorld);
  max.transformBy(xEyeToWorld);

  return OdGeExtents3d(min, max);
}

OdGePoint3d screenToWorld(int x, int y) {
  OdGePoint3d wsc_point(x, y, 0.0);
  OdTvGsViewId vId = getActiveDevice(dbId).openObject()->getActiveView();
  OdTvGsViewPtr view = vId.openObject(OdTv::kForWrite);

  if (view->isPerspective()) {
    wsc_point.z = view->projectionMatrix()(2, 3);
  }
  wsc_point.transformBy((view->screenMatrix() * view->projectionMatrix()).inverse());
  wsc_point.z = 0;
  wsc_point.transformBy(view->eyeToWorldMatrix());
  return wsc_point;
}

enum DefaultViewPosition
{
  k3DViewTop,
  k3DViewBottom,
  k3DViewLeft,
  k3DViewRight,
  k3DViewFront,
  k3DViewBack,
  k3DViewSW,
  k3DViewSE,
  k3DViewNE,
  k3DViewNW
};

extern "C"
{

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_init(JNIEnv *env, jclass clazz)
  {
    ODRX_INIT_STATIC_MODULE_MAP();
    odSetAssertFunc(_MyAssert);
    odrxInitialize(AndroidAppServices::getInstance());

    odTvInitialize();

    // PreFileLoader::createSchema();

    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_finit(JNIEnv *, jclass)
  {
    odTvUninitialize();
    odrxUninitialize();
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_open(JNIEnv *env, jclass clazz, jstring filename)
  {

    //retrieve the factory id
    OdTvFactoryId factId = odTvInitialize();
    OdTvGsDeviceId deviceId;
    // Try to import file
    OdTvResult rc = tvOk;
    try
    {
      // Import database
      OdTvVsfImportParams params;
      params.setFilePath( jstringToOdString( env, filename ) );
      dbId = factId.importFile( &params );
    }
    catch (OdTvError &e)
    {
      LOG_EXCEPTION(e);
      return JNI_FALSE;
    }

    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_renderFrame(JNIEnv *, jclass)
  {
    try
    {
      if (getActiveDevice(dbId).isNull())
        return JNI_FALSE;
      m_UpdateBlock.lock();
      OdTvGsDevicePtr pDevice = getActiveDevice(dbId).openObject();
      if (!pDevice.isNull())
      {
        pDevice->update();
        isGLUpdate = false;
      }
      m_UpdateBlock.unlock();
    }
    catch (OdError &e)
    {
      LOG_EXCEPTION(e);
      return JNI_FALSE;
    }
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_createRenderer(JNIEnv *env, jclass clazz, jint xMin, jint xMax, jint yMin, jint yMax, jobject glContext)
  {

    if (dbId.isValid())
    {
      OdTvDatabasePtr pDb = dbId.openObject();
      if (!pDb.isNull())
      {
        OdTvDevicesIteratorPtr pIt = pDb->getDevicesIterator();
        if (!pIt.isNull())
        {
          OdTvGsDeviceId deviceId = pIt->getDevice();

          // Get rect from current window
          screenRect = OdTvDCRect(xMin, xMax, yMax, yMin);

          OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);

		  pDevice->setOption(OdTvGsDevice::kUseSceneGraph, false);
          pDevice->setOption(OdTvGsDevice::kUseVisualStyles, false);
		  pDevice->setOption(OdTvGsDevice::kCreateGLContext, false);
		  
          // Setup device
          pDevice->setupGsWithContext((OSWindowGLContext)glContext, screenRect, OdTvGsDevice::kOpenGLES2, NULL);
        }
      }
      frame.setMode(SelectionFrameMode::kFrame);
      frame.init(&dbId);
    }

    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_viewTranslate(JNIEnv *env, jclass clazz, jfloat xAxis, jfloat yAxis)
  {
    if (getActiveDevice(dbId).isNull())
      return JNI_FALSE;

    m_UpdateBlock.lock();
    OdTvGsViewId vId = getActiveDevice(dbId).openObject()->getActiveView();
    OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);
    OdGeVector3d vec(-xAxis, -yAxis, 0.0);

    vec.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
    pView->dolly(vec);

    m_UpdateBlock.unlock();
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_viewScale(JNIEnv *env, jclass clazz, jfloat sCoef)
  {
    if (getActiveDevice(dbId).isNull())
    {
      return JNI_FALSE;
    }
    m_UpdateBlock.lock();
    OdTvGsViewId vId = getActiveDevice(dbId).openObject()->getActiveView();
    OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);

    pView->zoom((double)sCoef);
    m_UpdateBlock.unlock();
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_viewOrbit(JNIEnv *env, jclass clazz, jfloat xAxis, jfloat yAxis)
  {
    if (getActiveDevice(dbId).isNull())
    {
      return JNI_FALSE;
    }
    m_UpdateBlock.lock();
    OdTvGsViewId vId = getActiveDevice(dbId).openObject()->getActiveView();
    OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);
    OdGeVector3d delta((double)xAxis, (double)yAxis, 0.0);
    pView->orbit(delta.x, delta.y);
    // pView->roll(zAng);
    m_UpdateBlock.unlock();
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_viewRotate(JNIEnv *env, jclass clazz, jfloat rAngle)
  {
    if (getActiveDevice(dbId).isNull())
    {
      return JNI_FALSE;
    }
    m_UpdateBlock.lock();
    OdTvGsViewId vId = getActiveDevice(dbId).openObject()->getActiveView();
    OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);
    pView->roll((double)rAngle);
    m_UpdateBlock.unlock();
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_setVisualStyle(JNIEnv *env, jclass clazz, jstring selectedStyle)
  {
    if (getActiveDevice(dbId).isNull())
    {
      return JNI_FALSE;
    }

    m_UpdateBlock.lock();

    OdString selectedStyleName = jstringToOdString(env, selectedStyle);

    OdTvVisualStylesIteratorPtr styles = dbId.openObject()->getVisualStylesIterator();
    for (; !styles->done(); styles->step())
    {
      OdTvVisualStyleId id = styles->getVisualStyle();
      OdTvVisualStylePtr ptr = id.openObject();
      if (!selectedStyleName.compare(ptr->getName()))
      {
        OdTvGsViewId vId = getActiveDevice(dbId).openObject()->getActiveView();
        OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);
        pView->setVisualStyle(id);
      }
    }
    m_UpdateBlock.unlock();
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_setRenderMode(JNIEnv *env, jclass clazz, jstring renderMode)
  {
    if (getActiveDevice(dbId).isNull())
    {
      return JNI_FALSE;
    }

    m_UpdateBlock.lock();

    OdTvGsViewId vId = getActiveDevice(dbId).openObject()->getActiveView();
    OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);
    OdString odRenderMode = jstringToOdString(env, renderMode);

    if (odRenderMode == L"2D Wireframe")
      pView->setMode(OdTvGsView::k2DOptimized);
    else if (odRenderMode == L"3D Wireframe")
      pView->setMode(OdTvGsView::kWireframe);
    else if (odRenderMode == L"HiddenLine")
      pView->setMode(OdTvGsView::kHiddenLine);
    else if (odRenderMode == L"Shaded")
      pView->setMode(OdTvGsView::kFlatShaded);
    else if (odRenderMode == L"Gouraud shaded")
      pView->setMode(OdTvGsView::kGouraudShaded);
    else if (odRenderMode == L"Shaded with edges")
      pView->setMode(OdTvGsView::kFlatShadedWithWireframe);
    else if (odRenderMode == L"Gouraud shaded with edges")
      pView->setMode(OdTvGsView::kGouraudShadedWithWireframe);

    m_UpdateBlock.unlock();
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_setViewPosition(JNIEnv *env, jclass clazz, jint pos)
  {

    if (getActiveDevice(dbId).isNull())
    {
      return JNI_FALSE;
    }

    m_UpdateBlock.lock();

    OdGePoint3d position, target = OdGePoint3d::kOrigin;
    OdGeVector3d axis;
    switch (pos)
    {
    case DefaultViewPosition::k3DViewTop:
      position = OdGePoint3d::kOrigin + OdGeVector3d::kZAxis;
      axis = OdGeVector3d::kYAxis;
      break;
    case DefaultViewPosition::k3DViewBottom:
      position = OdGePoint3d::kOrigin - OdGeVector3d::kZAxis;
      axis = OdGeVector3d::kYAxis;
      break;
    case DefaultViewPosition::k3DViewLeft:
      position = OdGePoint3d::kOrigin - OdGeVector3d::kXAxis;
      axis = OdGeVector3d::kZAxis;
      break;
    case DefaultViewPosition::k3DViewRight:
      position = OdGePoint3d::kOrigin + OdGeVector3d::kXAxis;
      axis = OdGeVector3d::kZAxis;
      break;
    case DefaultViewPosition::k3DViewFront:
      position = OdGePoint3d::kOrigin - OdGeVector3d::kYAxis;
      axis = OdGeVector3d::kZAxis;
      break;
    case DefaultViewPosition::k3DViewBack:
      position = OdGePoint3d::kOrigin + OdGeVector3d::kYAxis;
      axis = OdGeVector3d::kZAxis;
      break;
    case DefaultViewPosition::k3DViewSW:
      position = OdGePoint3d::kOrigin + OdGeVector3d(-1.0, -1.0, 1.0);
      axis = OdGeVector3d(0.5, 0.5, 1.0).normal();
      break;
    case DefaultViewPosition::k3DViewSE:
      position = OdGePoint3d::kOrigin + OdGeVector3d(1.0, -1.0, 1.0);
      axis = OdGeVector3d(-0.5, 0.5, 1.0).normal();
      break;
    case DefaultViewPosition::k3DViewNE:
      position = OdGePoint3d::kOrigin + OdGeVector3d(1.0, 1.0, 1.0);
      axis = OdGeVector3d(-0.5, -0.5, 1.0).normal();
      break;
    case DefaultViewPosition::k3DViewNW:
      position = OdGePoint3d::kOrigin + OdGeVector3d(-1.0, 1.0, 1.0);
      axis = OdGeVector3d(0.5, -0.5, 1.0).normal();
      break;
    };

    OdTvGsViewId vId = getActiveDevice(dbId).openObject()->getActiveView();
    OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);
    pView->setView(position, target, axis, pView->fieldWidth(), pView->fieldHeight(),
                   pView->isPerspective() ? OdTvGsView::kPerspective : OdTvGsView::kParallel);

    m_UpdateBlock.unlock();
    return JNI_TRUE;

    // if (!getWcsViewid().isNull()) {
    //   OdTvGsViewPtr pWCSView = getWcsViewid().openObject(OdTv::kForWrite);
    //   pWCSView->setView(position, target, axis, pWCSView->fieldWidth(), pWCSView->fieldHeight());
    // }
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_zoomWindow(JNIEnv *env, jclass clazz, jdouble xMin, jdouble yMin, jdouble xMax, jdouble yMax)
  {
    if (getActiveDevice(dbId).isNull())
    {
      return JNI_FALSE;
    }

    try {
    OdTvGsViewId vId = getActiveDevice(dbId).openObject()->getActiveView();
    OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);
    OdTvDCRect screen;

    pView->getViewport(screen);

    OdGePoint3d pOldCntr((screen.xmax + screen.xmin) / 2.0, (screen.ymax + screen.ymin) / 2.0, 0.0);
    OdGePoint3d pNewCntr((xMax + xMin) / 2.0, (yMax + yMin) / 2.0, 0.0);

    OdGeVector3d vec(pNewCntr.x - pOldCntr.x, pNewCntr.y - pOldCntr.y, 0.0);

    vec.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
    pView->dolly(vec);

    double w0 = (double)fabs((double)(screen.xmax - screen.xmin));
    double h0 = (double)fabs((double)(screen.ymax - screen.ymin));

    double dW = w0 / fabs(xMax - xMin);
    double dH = h0 / fabs(yMax - yMin);

    pView->zoom(odmin(dW, dH));
    frame.clear();
    } catch (OdError &e)
    {
      LOG_EXCEPTION(e);
      return JNI_FALSE;
    }
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_zoomExtents(JNIEnv *env, jclass clazz)
  {

    if (getActiveDevice(dbId).isNull())
    {
      return JNI_FALSE;
    }

    try
    {
      OdTvGsViewId vId = getActiveDevice(dbId).openObject()->getActiveView();
      OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);
      OdGeExtents3d extents = getActiveExtents();
      pView->zoomExtents(extents.minPoint(), extents.maxPoint());
    }
    catch (OdError &e)
    {
      LOG_EXCEPTION(e);
      return JNI_FALSE;
    }
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_regenVisible(JNIEnv *env, jclass clazz)
  {
    OdTvGsDevicePtr pDevice = getActiveDevice(dbId).openObject();
    if (!pDevice.isNull())
    {
      m_UpdateBlock.lock();
      pDevice->regen(OdTvGsDevice::kRegenVisible);
      pDevice->invalidate();
      pDevice->update();
      m_UpdateBlock.unlock();
    }
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_regenAll(JNIEnv *env, jclass clazz)
  {
    OdTvGsDevicePtr pDevice = getActiveDevice(dbId).openObject();
    if (!pDevice.isNull())
    {
      m_UpdateBlock.lock();
      pDevice->regen(OdTvGsDevice::kRegenAll);
      pDevice->invalidate();
      pDevice->update();
      m_UpdateBlock.unlock();
    }
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_regenActiveView(JNIEnv *env, jclass clazz)
  {
    OdTvGsDevicePtr pDevice = getActiveDevice(dbId).openObject();
    OdTvGsViewPtr pView = pDevice->getActiveView().openObject();
    if (!pView.isNull())
    {
      m_UpdateBlock.lock();
      pView->regen();
      pDevice->invalidate();
      pDevice->update();
      m_UpdateBlock.unlock();
    }
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_startSelectionFrame(JNIEnv *env, jclass clazz, jint x, jint y)
  {
    OdGePoint3d startPoint = screenToWorld(x, y);
    frame.setStartPoint(startPoint);
    return JNI_TRUE;
  }


  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_resizeSelectionFrame(JNIEnv *env, jclass clazz, jint x, jint y)
  {
    OdGePoint3d secondPoint = screenToWorld(x, y);
		frame.setValue(secondPoint);
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_setProjectionForActiveView(JNIEnv *env, jclass clazz, jint projection)
  {
    if (getActiveDevice(dbId).isNull())
    {
      return JNI_FALSE;
    }

    OdTvGsDevicePtr pDevice = getActiveDevice(dbId).openObject();
    OdTvGsViewPtr avp = pDevice->getActiveView().openObject(OdTv::kForWrite);

    if(projection) {
      avp->setView(avp->position(), avp->target(), avp->upVector(), avp->fieldWidth(), avp->fieldHeight(), OdTvGsView::Projection::kPerspective);
    } else {
      avp->setView(avp->position(), avp->target(), avp->upVector(), avp->fieldWidth(), avp->fieldHeight(), OdTvGsView::Projection::kParallel);
    }
    return JNI_TRUE;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_createObjectExplorer(JNIEnv *env, jclass clazz)
  {
    objectExplorer.create(dbId);
    currentNode = objectExplorer.getRoot().get();
    return JNI_TRUE;
  }

  JNIEXPORT jint JNICALL Java_com_opendesign_android_TeighaDWGJni_getChildrenCount(JNIEnv *env, jclass clazz, jint index)
  {
    return currentNode->children.at(index)->children.size();
  }

  JNIEXPORT jint JNICALL Java_com_opendesign_android_TeighaDWGJni_toParent(JNIEnv *env, jclass clazz)
  {
    if(currentNode->parent != NULL)
    {
      currentNode = currentNode->parent;
      return 0;
    }
    return 1;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_android_TeighaDWGJni_toChild(JNIEnv *env, jclass clazz, jint index)
  {
    try {
    currentNode = currentNode->children.at(index).get();
    } catch (std::out_of_range e) {
      return JNI_FALSE;
    }
    return JNI_TRUE;
  }

  JNIEXPORT jobjectArray JNICALL Java_com_opendesign_android_TeighaDWGJni_getCurrentObjects(JNIEnv *env, jclass clazz)
  {
    jobjectArray result = (jobjectArray)env->NewObjectArray(currentNode->children.size(),  
         env->FindClass("java/lang/String"),  
         env->NewStringUTF(""));;

    for(int i = 0; i < currentNode->children.size(); ++i) {
      jstring item = env->NewStringUTF(currentNode->children.at(i)->name.c_str());
      env->SetObjectArrayElement(result, i, item);
      env->DeleteLocalRef(item);
    }
    return result;
  }

} // extern "C"
