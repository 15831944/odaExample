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
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "OdaCommon.h"
#include "RxInit.h"
#include "OdMutex.h"
#include <OdAnsiString.h>
#include <OdCharMapper.h>
#include <diagnostics.h>

#include "TvImport.h"
#include "TvAndTools.h"
#include "TvAndCore.h"
#include "TvAndActivator.h"
#include "TvAndGlobalParameters.h"

#define LOG_TAG "VisualizeSdkJni"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define LOG_EXCEPTION(e) LOGE("Exception Caught: %s\n", (const char *)e.description())

static void _MyAssert(const char *expression, const char *fileName, int nLineNo)
{
  LOGW("Assertion Failed: %s, File: %s, Line: %d\n", expression, fileName, nLineNo);
}

static TvAndActivator activator;
static std::mutex mutex;
static TvAndGlobalParameters globalParams;

class CoreManager {
public:
  CoreManager() { m_pCore = NULL; }
  ~CoreManager() { if(m_pCore) delete m_pCore; }

  TvAndCore* getCore() 
  { 
    if(m_pCore == NULL)
    {
      createCore();
      m_pCore->setGlobalParams(globalParams);
    }
    return m_pCore; 
  }

  void createCore() { if(!m_pCore) m_pCore = new TvAndCore(); }

  void releaseCore() 
  {
    if(m_pCore) {
      delete m_pCore;
      m_pCore = NULL;
    }
  }

  bool isNull() const { return m_pCore == NULL; }
  bool isBlocked() const { return m_pCore && m_pCore->isBlocked(); }

private:
  TvAndCore* m_pCore;
};
static CoreManager cm;

extern "C"
{

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_activate(JNIEnv *env, jclass clazz)
  {
    activator.activate();
    odSetAssertFunc(_MyAssert);
  }
  
  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_deactivate(JNIEnv *env, jclass clazz)
  {
    activator.deactivate();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_release(JNIEnv *env, jclass clazz)
  {
    cm.releaseCore();
  }

  JNIEXPORT jstring JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_openFile(JNIEnv *env, jclass clazz, jstring filePath)
  {
    mutex.lock();
    OdString odFilePath = jstringToOdString(env, filePath);
    OdString res = cm.getCore()->openFile(odFilePath);
    mutex.unlock();
    return odStringTojstring(env, res);
  }

  JNIEXPORT jstring JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_lowMemoryOpenFile(JNIEnv *env, jclass clazz, jstring filePath, jobject progressMeterController)
  {
    mutex.lock();

    cm.getCore()->setProgressMeter(new TvAndProgressMeter(new TvAndJniProgressMeter(env, progressMeterController)));

    OdString odFilePath = jstringToOdString(env, filePath);
    OdString res = cm.getCore()->openFile(odFilePath);
    
    mutex.unlock();
    return odStringTojstring(env, res);
  }
  
  JNIEXPORT jstring JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_setupDevice(JNIEnv *env, jclass clazz, jobject context, jint w, jint h)
  {
    if(cm.isNull())
      return odStringTojstring(env, OD_T("Core is NULL"));
    mutex.lock();
    OdString res = cm.getCore()->setupDevice(context, OdTvDCRect(0, w, h, 0));
    mutex.unlock();
    return odStringTojstring(env, res);
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_update(JNIEnv *env, jclass clazz)
  {
    if ( cm.isBlocked() )
      return;

    mutex.lock();
    cm.getCore()->update();
    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_resizeDevice(JNIEnv *env, jclass clazz, jint xMin, jint xMax, jint yMin, jint yMax)
  {
    if ( cm.isBlocked() )
      return;

    mutex.lock();
    cm.getCore()->resizeDevice(xMin, xMax, yMin, yMax);
    mutex.unlock();
  }

  JNIEXPORT jint JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_onTouchDown(JNIEnv *env, jclass clazz, jint x, jint y)
  {
    mutex.lock();
    jint res = (jint)cm.getCore()->onTouchDown(x, y);
    mutex.unlock();
    return res;
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_onTouchMove(JNIEnv *env, jclass clazz, jint x, jint y)
  {
    mutex.lock();
    cm.getCore()->onTouchMove(x, y);
    mutex.unlock();
  }

  JNIEXPORT jint JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_onTouchUp(JNIEnv *env, jclass clazz, jint x, jint y)
  {
    mutex.lock();
    jint res = (jint)cm.getCore()->onTouchUp(x, y);
    mutex.unlock();
    return res;
  }

  JNIEXPORT jint JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_onProcessEnter(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    jint res = (jint)cm.getCore()->onProcessEnter();
    mutex.unlock();
    return res;
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_onProcessBackspace(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    cm.getCore()->onProcessBackspace();
    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_onProcessText(JNIEnv *env, jclass clazz, jstring text)
  {
    mutex.lock();
    OdString odText = jstringToOdString(env, text);
    cm.getCore()->onProcessText(odText);
    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_zoom(JNIEnv *env, jclass clazz, jdouble delta, jint x, jint y)
  {
    mutex.lock();
    cm.getCore()->zoom(delta, x, y);
    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_runNavigationAction(JNIEnv *env, jclass clazz, jint navAction)
  {
    mutex.lock();
    cm.getCore()->runNavigationAction((TvAndCore::NavigationAction)navAction);
    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_set3DView(JNIEnv *env, jclass clazz, jint viewType)
  {
    mutex.lock();
    cm.getCore()->set3DView((OdTvExtendedView::e3DViewType)viewType);
    mutex.unlock();
  }

  
  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_regenVisible(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    cm.getCore()->regenVisible();
    mutex.unlock();
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_isPerspective(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    jboolean isPersp = cm.getCore()->isPerspective();
    mutex.unlock();
    return isPersp;
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_setProjection(JNIEnv *env, jclass clazz, jint projType)
  {
    mutex.lock();
    cm.getCore()->setProjection((OdTvGsView::Projection)projType);
    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_runRenderMode(JNIEnv *env, jclass clazz, jint renderMode)
  {
    mutex.lock();
    cm.getCore()->runRenderMode((OdTvGsView::RenderMode)renderMode);
    mutex.unlock();
  }

  JNIEXPORT jint JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_getRenderMode(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    jint iMode = (jint)cm.getCore()->getRenderMode();
    mutex.unlock();
    return iMode;
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_runMarkupAction(JNIEnv *env, jclass clazz, jint markupCmd)
  {
    mutex.lock();
    cm.getCore()->runMarkupAction((TvAndCore::MarkupAction)markupCmd);
    mutex.unlock();
  }

  JNIEXPORT jstring JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_isSaveMarkupAvaliable(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    OdString res = cm.getCore()->isSaveMarkupAvaliable();
    mutex.unlock();
    return odStringTojstring(env, res);
  }

  JNIEXPORT jstring JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_saveMarkup(JNIEnv *env, jclass clazz, jstring markupName)
  {
    mutex.lock();
    OdString res = cm.getCore()->saveMarkup(jstringToOdString(env, markupName));
    mutex.unlock();
    return odStringTojstring(env, res);
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_saveFile(JNIEnv *env, jclass clazz, jstring fileName, jboolean bPartialIndexing)
  {
    mutex.lock();
    cm.getCore()->save(jstringToOdString(env, fileName), bPartialIndexing);
    mutex.unlock();
  }

  JNIEXPORT jstring JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_isLoadMarkupAvaliable(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    OdString res = cm.getCore()->isLoadMarkupAvaliable();
    mutex.unlock();
    return odStringTojstring(env, res);
  }

  JNIEXPORT jstring JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_loadMarkup(JNIEnv *env, jclass clazz, jstring markupName)
  {
    mutex.lock();
    OdString res = cm.getCore()->loadMarkup(jstringToOdString(env, markupName));
    mutex.unlock();
    return odStringTojstring(env, res);
  }

/* For accessing primitive types from class use
           following field descriptors

           +---+---------+
           | Z | boolean |
           | B | byte    |
           | C | char    |
           | S | short   |
           | I | int     |
           | J | long    |
           | F | float   |
           | D | double  |
           +-------------+
*/

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_getGlobalParams(JNIEnv *env, jclass clazz, jobject jParams)
  {
    mutex.lock();

    jclass cls = env->GetObjectClass(jParams);
    // WCS
    jfieldID wcsFieldId = env->GetFieldID(cls, "WcsEnabled", "Z");
    env->SetBooleanField(jParams, wcsFieldId, globalParams.getWcsEnabled());
    // FPS
    jfieldID fpsFieldId = env->GetFieldID(cls, "FpsEnabled", "Z");
    env->SetBooleanField(jParams, fpsFieldId, globalParams.getFpsEnabled());
    // Animation
    jfieldID animFieldId = env->GetFieldID(cls, "AnimationEnabled", "Z");
    env->SetBooleanField(jParams, animFieldId, globalParams.getAnimationEnabled());
    // Partial open
    jfieldID partialFieldId = env->GetFieldID(cls, "PartialOpenEnabled", "Z");
    env->SetBooleanField(jParams, partialFieldId, globalParams.getPartialOpen());
    // Use limit manager
    jfieldID limitFieldId = env->GetFieldID(cls, "UseLimitManager", "Z");
    env->SetBooleanField(jParams, limitFieldId, globalParams.getUseLimitManager());
    // LimitValue
    jfieldID limitValFieldId = env->GetFieldID(cls, "LimitValue", "J");
    env->SetLongField(jParams, limitValFieldId, (jlong)globalParams.getMemoryLimit());
    // Scene graph
    jfieldID sceneGraphFieldId = env->GetFieldID(cls, "SceneGraphEnabled", "Z");
    env->SetBooleanField(jParams, sceneGraphFieldId, globalParams.getUseSceneGraph());
    // fixed ferame rate enabled
    jfieldID ffrFieldId = env->GetFieldID(cls, "FixedFrameRateEnabled", "Z");
    env->SetBooleanField(jParams, ffrFieldId, globalParams.getFixedFrameRate());
    // fixed frame rate value
    jfieldID ffrValFieldId = env->GetFieldID(cls, "FixedFrameRateValue", "I");
    env->SetIntField(jParams, ffrValFieldId, (jint)globalParams.getFpsValue());
    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_setGlobalParams(JNIEnv *env, jclass clazz, jobject jParams)
  {
    mutex.lock();

    jclass cls = env->GetObjectClass(jParams);
    // WCS
    jfieldID wcsFieldId = env->GetFieldID(cls, "WcsEnabled", "Z");
    globalParams.setWcsEnabled( env->GetBooleanField(jParams, wcsFieldId) );
    // FPS
    jfieldID fpsFieldId = env->GetFieldID(cls, "FpsEnabled", "Z");
    globalParams.setFpsEnabled( env->GetBooleanField(jParams, fpsFieldId) );
    // Animation
    jfieldID animFieldId = env->GetFieldID(cls, "AnimationEnabled", "Z");
    globalParams.setAnimationEnabled( env->GetBooleanField(jParams, animFieldId) );
    // Partial open
    jfieldID partialFieldId = env->GetFieldID(cls, "PartialOpenEnabled", "Z");
    globalParams.setPartialOpen( env->GetBooleanField(jParams, partialFieldId) );
    // Use limit manager
    jfieldID limitFieldId = env->GetFieldID(cls, "UseLimitManager", "Z");
    globalParams.setUseLimitManager( env->GetBooleanField(jParams, limitFieldId) );
    // LimitValue
    jfieldID limitValFieldId = env->GetFieldID(cls, "LimitValue", "J");
    globalParams.setMemoryLimit( env->GetLongField(jParams, limitValFieldId) );
    // Scene graph
    jfieldID sceneGraphFieldId = env->GetFieldID(cls, "SceneGraphEnabled", "Z");
    globalParams.setUseSceneGraph( env->GetBooleanField(jParams, sceneGraphFieldId) );
    // fixed ferame rate enabled
    jfieldID ffrFieldId = env->GetFieldID(cls, "FixedFrameRateEnabled", "Z");
    globalParams.setFixedFrameRate( env->GetBooleanField(jParams, ffrFieldId) );
    // fixed frame rate value
    jfieldID ffrValFieldId = env->GetFieldID(cls, "FixedFrameRateValue", "I");
    globalParams.setFpsValue( (double)env->GetIntField(jParams, ffrValFieldId) );

    if(!cm.isNull())
      cm.getCore()->setGlobalParams(globalParams);

    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_getDwgImportParams(JNIEnv *env, jclass clazz, jobject jParams)
  {
    mutex.lock();

    jclass cls = env->GetObjectClass(jParams);
    // StoreSource
    jfieldID storeSourceFieldId = env->GetFieldID(cls, "StoreSource", "Z");
    env->SetBooleanField(jParams, storeSourceFieldId, globalParams.m_importContainer.m_dwgParams.m_bStoreSource);
    // Clear empty objects
    jfieldID ceoFieldId = env->GetFieldID(cls, "ClearEmptyObjects", "Z");
    env->SetBooleanField(jParams, ceoFieldId, globalParams.m_importContainer.m_dwgParams.m_bClearEmptyObjects);
    // Enable MT
    jfieldID mtFieldId = env->GetFieldID(cls, "EnableMT", "Z");
    env->SetBooleanField(jParams, mtFieldId, globalParams.m_importContainer.m_dwgParams.m_bEnableMT);
    // Threads count
    jfieldID thcValFieldId = env->GetFieldID(cls, "ThreadsCount", "I");
    env->SetIntField(jParams, thcValFieldId, (jint)globalParams.m_importContainer.m_dwgParams.m_iThreadsCount);
    // Import Brep as Brep
    jfieldID brepFieldId = env->GetFieldID(cls, "ImportBrepAsBrep", "Z");
    env->SetBooleanField(jParams, brepFieldId, globalParams.m_importContainer.m_dwgParams.m_bImportBrepAsBrep);
    // Low memory import
    jfieldID lowmFieldId = env->GetFieldID(cls, "LowMemoryImport", "Z");
    env->SetBooleanField(jParams, lowmFieldId, globalParams.m_importContainer.m_dwgParams.m_bLowMemoryImport);
    // Background color
    jfieldID bgColorFieldId = env->GetFieldID(cls, "BackgroundColor", "I");
    env->SetIntField(jParams, bgColorFieldId, (jint)globalParams.m_importContainer.m_dwgParams.m_iBackgroundColor);

    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_setDwgImportParams(JNIEnv *env, jclass clazz, jobject jParams)
  {
    mutex.lock();

    jclass cls = env->GetObjectClass(jParams);
    // StoreSource
    jfieldID storeSourceFieldID = env->GetFieldID(cls, "StoreSource", "Z");
    globalParams.m_importContainer.m_dwgParams.m_bStoreSource = env->GetBooleanField(jParams, storeSourceFieldID);
    // Clear empty objects
    jfieldID ceoFieldID = env->GetFieldID(cls, "ClearEmptyObjects", "Z");
    globalParams.m_importContainer.m_dwgParams.m_bClearEmptyObjects = env->GetBooleanField(jParams, ceoFieldID);
    // Enable MT
    jfieldID mtFieldID = env->GetFieldID(cls, "EnableMT", "Z");
    globalParams.m_importContainer.m_dwgParams.m_bEnableMT = env->GetBooleanField(jParams, mtFieldID);
    // Threads count
    jfieldID thcFieldID = env->GetFieldID(cls, "ThreadsCount", "I");
    globalParams.m_importContainer.m_dwgParams.m_iThreadsCount = (int)env->GetIntField(jParams, thcFieldID);   
    // Import Brep as Brep
    jfieldID brepFieldID = env->GetFieldID(cls, "ImportBrepAsBrep", "Z");
    globalParams.m_importContainer.m_dwgParams.m_bImportBrepAsBrep = env->GetBooleanField(jParams, brepFieldID);
    // Low memory import
    jfieldID lowmFieldId = env->GetFieldID(cls, "LowMemoryImport", "Z");
    globalParams.m_importContainer.m_dwgParams.m_bLowMemoryImport = env->GetBooleanField(jParams, lowmFieldId);
    // Background color
    jfieldID bgColorFieldId = env->GetFieldID(cls, "BackgroundColor", "I");
    globalParams.m_importContainer.m_dwgParams.m_iBackgroundColor = (int)env->GetIntField(jParams, bgColorFieldId);
    
    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_getStlImportParams(JNIEnv *env, jclass clazz, jobject jParams)
  {
    mutex.lock();

    jclass cls = env->GetObjectClass(jParams);
    // Fix normals
    jfieldID fixNormalsFieldId = env->GetFieldID(cls, "FixNormals", "Z");
    env->SetBooleanField(jParams, fixNormalsFieldId, globalParams.m_importContainer.m_stlParams.m_bFixNormals);
    // Unify duplicated vertices
    jfieldID unifyDuplVertFieldId = env->GetFieldID(cls, "UnifyDuplicatedVertices", "Z");
    env->SetBooleanField(jParams, unifyDuplVertFieldId, globalParams.m_importContainer.m_stlParams.m_bUnifyDuplicatedVertices);
    // Calculate normals at vertices
    jfieldID calcNormalsFieldId = env->GetFieldID(cls, "CalculateNormalsAtVertices", "Z");
    env->SetBooleanField(jParams, calcNormalsFieldId, globalParams.m_importContainer.m_stlParams.m_bCalcNormalsAtVertices);

    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_setStlImportParams(JNIEnv *env, jclass clazz, jobject jParams)
  {
    mutex.lock();

    jclass cls = env->GetObjectClass(jParams);
    // Fix normals
    jfieldID fixNormalsFieldId = env->GetFieldID(cls, "FixNormals", "Z");
    globalParams.m_importContainer.m_stlParams.m_bFixNormals = env->GetBooleanField(jParams, fixNormalsFieldId);
    // Unify duplicated vertices
    jfieldID unifyDuplVertFieldId = env->GetFieldID(cls, "UnifyDuplicatedVertices", "Z");
    globalParams.m_importContainer.m_stlParams.m_bUnifyDuplicatedVertices = env->GetBooleanField(jParams, unifyDuplVertFieldId);
    // Calculate normals at vertices
    jfieldID calcNormalsFieldId = env->GetFieldID(cls, "CalculateNormalsAtVertices", "Z");
    globalParams.m_importContainer.m_stlParams.m_bCalcNormalsAtVertices = env->GetBooleanField(jParams, calcNormalsFieldId);

    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_getPrcImportParams(JNIEnv *env, jclass clazz, jobject jParams)
  {
    mutex.lock();

    jclass cls = env->GetObjectClass(jParams);
    // Store source
    jfieldID storeSourceFieldId = env->GetFieldID(cls, "StoreSource", "Z");
    env->SetBooleanField(jParams, storeSourceFieldId, globalParams.m_importContainer.m_prcParams.m_bStoreSource);
    // ClearEmptyObjects
    jfieldID clearEmptyObjectsFieldId = env->GetFieldID(cls, "ClearEmptyObjects", "Z");
    env->SetBooleanField(jParams, clearEmptyObjectsFieldId, globalParams.m_importContainer.m_prcParams.m_bClearEmptyObjects);
    // RearrangeObjects
    jfieldID rearrangeObjectsFieldId = env->GetFieldID(cls, "RearrangeObjects", "Z");
    env->SetBooleanField(jParams, rearrangeObjectsFieldId, globalParams.m_importContainer.m_prcParams.m_bRearrangeObjects);
    // ImportBrepAsBrep
    jfieldID importBrepAsBrepFieldId = env->GetFieldID(cls, "ImportBrepAsBrep", "Z");
    env->SetBooleanField(jParams, importBrepAsBrepFieldId, globalParams.m_importContainer.m_prcParams.m_bImportBrepAsBrep);

    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_setPrcImportParams(JNIEnv *env, jclass clazz, jobject jParams)
  {
    mutex.lock();

    jclass cls = env->GetObjectClass(jParams);
    // Store source
    jfieldID storeSourceFieldId = env->GetFieldID(cls, "StoreSource", "Z");
    globalParams.m_importContainer.m_prcParams.m_bStoreSource = env->GetBooleanField(jParams, storeSourceFieldId);
    // ClearEmptyObjects
    jfieldID clearEmptyObjectsFieldId = env->GetFieldID(cls, "ClearEmptyObjects", "Z");
    globalParams.m_importContainer.m_prcParams.m_bClearEmptyObjects = env->GetBooleanField(jParams, clearEmptyObjectsFieldId);
    // RearrangeObjects
    jfieldID rearrangeObjectsFieldId = env->GetFieldID(cls, "RearrangeObjects", "Z");
    globalParams.m_importContainer.m_prcParams.m_bRearrangeObjects = env->GetBooleanField(jParams, rearrangeObjectsFieldId);
    // ImportBrepAsBrep
    jfieldID importBrepAsBrepFieldId = env->GetFieldID(cls, "ImportBrepAsBrep", "Z");
    globalParams.m_importContainer.m_prcParams.m_bImportBrepAsBrep = env->GetBooleanField(jParams, importBrepAsBrepFieldId);

    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_getDgnImportParams(JNIEnv *env, jclass clazz, jobject jParams)
  {
    mutex.lock();

    jclass cls = env->GetObjectClass(jParams);
    // Store source
    jfieldID storeSourceFieldId = env->GetFieldID(cls, "StoreSource", "Z");
    env->SetBooleanField(jParams, storeSourceFieldId, globalParams.m_importContainer.m_dgnParams.m_bStoreSource);
    // ClearEmptyObjects
    jfieldID clearEmptyObjectsFieldId = env->GetFieldID(cls, "ClearEmptyObjects", "Z");
    env->SetBooleanField(jParams, clearEmptyObjectsFieldId, globalParams.m_importContainer.m_dgnParams.m_bClearEmptyObjects);
    // UseIsolinesFor3DObjects
    jfieldID useIsolinesFor3DObjectsFieldId = env->GetFieldID(cls, "UseIsolinesFor3DObjects", "Z");
    env->SetBooleanField(jParams, useIsolinesFor3DObjectsFieldId, globalParams.m_importContainer.m_dgnParams.m_bUseIsolinesFor3DObjects);

    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_setDgnImportParams(JNIEnv *env, jclass clazz, jobject jParams)
  {
    mutex.lock();

    jclass cls = env->GetObjectClass(jParams);
    // Store source
    jfieldID storeSourceFieldId = env->GetFieldID(cls, "StoreSource", "Z");
    globalParams.m_importContainer.m_dgnParams.m_bStoreSource = env->GetBooleanField(jParams, storeSourceFieldId);
    // ClearEmptyObjects
    jfieldID clearEmptyObjectsFieldId = env->GetFieldID(cls, "ClearEmptyObjects", "Z");
    globalParams.m_importContainer.m_dgnParams.m_bClearEmptyObjects = env->GetBooleanField(jParams, clearEmptyObjectsFieldId);
    // UseIsolinesFor3DObjects
    jfieldID useIsolinesFor3DObjectsFieldId = env->GetFieldID(cls, "UseIsolinesFor3DObjects", "Z");
    globalParams.m_importContainer.m_dgnParams.m_bUseIsolinesFor3DObjects = env->GetBooleanField(jParams, useIsolinesFor3DObjectsFieldId);

    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_getObjImportParams(JNIEnv *env, jclass clazz, jobject jParams)
  {
    mutex.lock();

    jclass cls = env->GetObjectClass(jParams);
    // CalculateNormalsAtVertices
    jfieldID calculateNormalsAtVerticesFieldId = env->GetFieldID(cls, "CalculateNormalsAtVertices", "Z");
    env->SetBooleanField(jParams, calculateNormalsAtVerticesFieldId, globalParams.m_importContainer.m_objParams.m_bCalculateNormalsAtVertices);
    // FlipUVCoordinateSystem
    jfieldID flipUVCoordinateSystemFieldId = env->GetFieldID(cls, "FlipUVCoordinateSystem", "Z");
    env->SetBooleanField(jParams, flipUVCoordinateSystemFieldId, globalParams.m_importContainer.m_objParams.m_bFlipUVCoordinateSystem);
    // ImportBrepAsBrep
    jfieldID importBrepAsBrepFieldId = env->GetFieldID(cls, "ImportBrepAsBrep", "Z");
    env->SetBooleanField(jParams, importBrepAsBrepFieldId, globalParams.m_importContainer.m_objParams.m_bImportBrepAsBrep);

    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_setObjImportParams(JNIEnv *env, jclass clazz, jobject jParams)
  {
    mutex.lock();

    jclass cls = env->GetObjectClass(jParams);
    // CalculateNormalsAtVertices
    jfieldID calculateNormalsAtVerticesFieldId = env->GetFieldID(cls, "CalculateNormalsAtVertices", "Z");
    globalParams.m_importContainer.m_objParams.m_bCalculateNormalsAtVertices = env->GetBooleanField(jParams, calculateNormalsAtVerticesFieldId);
    // FlipUVCoordinateSystem
    jfieldID flipUVCoordinateSystemFieldId = env->GetFieldID(cls, "FlipUVCoordinateSystem", "Z");
    globalParams.m_importContainer.m_objParams.m_bFlipUVCoordinateSystem = env->GetBooleanField(jParams, flipUVCoordinateSystemFieldId);
    // ImportBrepAsBrep
    jfieldID importBrepAsBrepFieldId = env->GetFieldID(cls, "ImportBrepAsBrep", "Z");
    globalParams.m_importContainer.m_objParams.m_bImportBrepAsBrep = env->GetBooleanField(jParams, importBrepAsBrepFieldId);

    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_applyGlobalParams(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    cm.getCore()->applyGlobalParams();
    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_onAppearSectioningPanel(JNIEnv *env, jclass clazz, jboolean bAppear)
  {
    mutex.lock();
    cm.getCore()->onAppearSectioningPanel(bAppear);
    mutex.unlock();
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_isCuttingPlanesVisible(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    jboolean flag = cm.getCore()->isCuttingPlanesVisible();
    mutex.unlock();
    return flag;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_isCuttingPlanesFilled(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    jboolean flag = cm.getCore()->isCuttingPlanesFilled();
    mutex.unlock();
    return flag;
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_onShowCuttingPlanes(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    cm.getCore()->setShowCuttingPlanes( !cm.getCore()->isCuttingPlanesVisible() );
    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_onAddCuttingPlanes(JNIEnv *env, jclass clazz, jint x, jint y, jint z)
  {
    mutex.lock();
    cm.getCore()->onAddCuttingPlane( OdTvVector(x, y, z) );
    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_onFillCuttingPlanes(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    cm.getCore()->setCuttingPlanesFilled( !cm.getCore()->isCuttingPlanesFilled() );
    mutex.unlock();
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_onRemoveCuttingPlanes(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    cm.getCore()->removeCuttingPlanes();
    mutex.unlock();
  }

  JNIEXPORT jstring JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_runCollide(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    OdString res = cm.getCore()->runCollide();
    mutex.unlock();
    return odStringTojstring(env, res);
  }

  JNIEXPORT void JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_finishDragger(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    cm.getCore()->finishDragger();
    mutex.unlock();
  }

  JNIEXPORT jlong JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_getTotalTime(JNIEnv *env, jclass clazz)
  {
    jlong time = 0.;
    mutex.lock();
    time = cm.getCore()->getTotalTime();
    mutex.unlock();
    return time;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_addGroundShadow(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    jboolean res = cm.getCore()->addGroundShadow();
    mutex.unlock();
    return res;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_isViewAllowGroundShadow(JNIEnv *env, jclass clazz)
  {
    mutex.lock();
    jboolean res = cm.getCore()->isViewAllowGroundShadow();
    mutex.unlock();
    return res;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_isPdfExportEnabled(JNIEnv *env, jclass clazz)
  {
    jboolean res = false;
#ifdef PDF_EXPORT_ENABLED
    res = true;
#endif
    return res;
  }

  JNIEXPORT jboolean JNICALL Java_com_opendesign_odaviewer_VisualizeSdkJni_exportToPdf(JNIEnv *env, jclass clazz, jboolean b3D)
  {
    mutex.lock();
    jboolean res = cm.getCore()->exportToPdf(b3D);
    mutex.unlock();
    return res;
  }

} // extern "C"
