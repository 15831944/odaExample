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

#ifndef _TV_BIM2VISUALIZETHREADCONTEXT_H_
#define _TV_BIM2VISUALIZETHREADCONTEXT_H_

#include "TD_PackPush.h"

#include "Bim2Visualize.h"
#include "RxThreadPoolService.h"
#include "Gs/Gs.h"
#include "BmGsManager.h"
#include "RxSystemServices.h"
#include "Database/Entities/BmDBDrawing.h"

#include "TvFilerTimer.h"
#include "TvDatabase.h"
#include "../Extensions/ExVisualizeDevice/GsVisualizeVectorizer.h"

/**\details
This class describes singleton STQueue for background processes
*/
class OdTvThreadQueue
{
  static OdApcQueuePtr m_pMTQueue;
  static OdRxThreadPoolServicePtr m_pThreadPool;
  static OdUInt32 m_nref;
  /** \details
  Releases smart pointers
  */
  void reset()
  {
    m_pMTQueue = NULL;
    m_pThreadPool = NULL;
  }
  /** \details
  Releases OdTvThreadQueue instance
  */
  void release()
  {
    m_nref--;
    if (m_nref == 0) reset();
  }
public:
  /** \details
  Constructs OdTvThreadQueue instance
  */
  OdTvThreadQueue() { m_nref++; };
  /** \details
  Destroy OdTvThreadQueue instance
  */
  ~OdTvThreadQueue();
  /** \details
  Obtains STQueue instance
  \returns Smatr pointer to the STQueue
  */
  OdApcQueuePtr queue(OdUInt64 nViewsImportThreads);
};

/** \details
Context for Bim to visualize vectorization
*/
struct OdTvBim2VisualizeVecorizationContext
{
  OdTvBim2VisualizeVecorizationContext(OdGsModulePtr& pGs,
  OdTvDatabaseId& tvDbId,
  OdBmDatabasePtr& pDb,
  ODCOLORREF& background,
  OdBmObjectId bmObjectId,
  const BIM2Visualize::OdTvVisualizeBimFilerPropertiesPtr& properties,
    OdMutex* pDatabaseAccessMutex,
    OdMutex* pSetupDBDrawingViewsMutex,
    unsigned int nViewsImportThreads)
    : m_pGs(pGs)
    , m_tvDbId(tvDbId)
    , m_pDb(pDb)
    , m_background(background)
    , m_bmObjectId(bmObjectId)
    , m_properties(properties)
    , m_pDatabaseAccessMutex(pDatabaseAccessMutex)
    , m_pSetupDBDrawingViewsMutex(pSetupDBDrawingViewsMutex)
    , m_nViewsImportThreads(nViewsImportThreads)
  {
  };

  OdGsModulePtr m_pGs;
  OdTvDatabaseId& m_tvDbId;
  OdBmDatabasePtr& m_pDb;
  ODCOLORREF& m_background;
  OdBmObjectId m_bmObjectId;
  const BIM2Visualize::OdTvVisualizeBimFilerPropertiesPtr& m_properties;
  OdMutex* m_pDatabaseAccessMutex;
  OdMutex* m_pSetupDBDrawingViewsMutex;
  unsigned int m_nViewsImportThreads;
};

/** \details
Thread running method for vectorization
*/
class OdTvBim2VisualizeVecorizationCaller : public OdApcAtom
{
public:
  virtual void apcEntryPoint(OdApcParamType pMessage);
};

/** \details
Thread context for vectorization
*/
class OdTvBim2VisualizeVecorizationThreadContext;
typedef OdSmartPtr<OdTvBim2VisualizeVecorizationThreadContext> OdTvBim2VisualizeVecorizationThreadContextPtr;

class OdTvBim2VisualizeVecorizationThreadContext : public OdRxObject
{
public:
  static OdTvBim2VisualizeVecorizationThreadContextPtr createObject();

  void vectorizeDevice(OdTvBim2VisualizeVecorizationContext* pContext);
  void stop();
  void start();
  void wait();

private:
  OdTvThreadQueue m_backQueue;
  OdApcQueuePtr m_pMTQueue;
  bool m_bInterrupt;
  OdMutexPtr m_pInternalMutex;
};

/** \details
Some help functions
*/
void resetViewsModelsNames(OdTvGsDeviceId idTVDevice);
void setupExVisualizeDeviceProp(OdRxDictionaryPtr& pProperties, const OdTvDatabaseId& tvDbId, 
  const OdString& modelName, const BIM2Visualize::OdTvVisualizeBimFilerPropertiesPtr& importProperties,
  OdTvGsDeviceId& tvDeviceIdForAppend, bool bIs3DView, OdTvBim2VisualizeVecorizationContext* pContext);
int getViewId(OdGsDevice* pDevice, OdGsView* pView);
void setupConnectionsBetweenTvViews(OdBmObjectId idDBDrawing, OdGsDevice* pDevice, OdTvGsDeviceId idTVDevice);
#include "TD_PackPop.h"

#endif
