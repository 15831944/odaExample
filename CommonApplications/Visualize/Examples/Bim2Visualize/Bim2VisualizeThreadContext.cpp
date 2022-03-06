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

#include "Bim2VisualizeThreadContext.h"
#include "RxVariantValue.h"
#include "GiContextForBmDatabase.h"
#include "ColorMapping.h"
#include "BmGsManager.h"
#include "OdaDefs.h"
#include "TvImport.h"
#include "../Extensions/ExVisualizeDevice/GsVisualizeVectorizer.h"
#include "Entities/BmViewport.h"
#include "Gs/GsCacheRedirection.h"

//***************************************************************************//
// 'OdTvThreadQueue' methods implementation
//***************************************************************************//

OdApcQueuePtr OdTvThreadQueue::m_pMTQueue = OdApcQueuePtr();
OdRxThreadPoolServicePtr OdTvThreadQueue::m_pThreadPool = OdRxThreadPoolServicePtr();
OdUInt32 OdTvThreadQueue::m_nref = 0;

OdTvThreadQueue::~OdTvThreadQueue()
{
  // Release pointer but do not unload app (it will be unloaded after all modules unloading)
  if (!m_pThreadPool.isNull())
    m_pThreadPool.release();
  release();
}

OdApcQueuePtr OdTvThreadQueue::queue(OdUInt64 nViewsImportThreads)
{
  if (!m_pMTQueue.isNull())
  {
    return m_pMTQueue;
  }
  if (m_pThreadPool.isNull())
  {
    m_pThreadPool = ::odrxDynamicLinker()->loadApp(OdThreadPoolModuleName);
  }
  if (m_pThreadPool.isNull())
  {
    ODA_FAIL();
    return OdApcQueuePtr();
  }
  m_pMTQueue = m_pThreadPool->newMTQueue(ThreadsCounter::kAllAttributes, nViewsImportThreads);
  return m_pMTQueue;
}

/** \details
Notifier for tv device creation
*/
class OdTvDeviceCreationNotifier : public ExGsVisualizeDeviceNotifier
{
public:
  //entities
  virtual void entityVectorizationDone(const OdTvEntityId& entityId) {};
  virtual void insertVectorizationDone(const OdTvEntityId& insertId) {};
  virtual void lightVectorizationDone(const OdTvEntityId& lightId) {};

  virtual void entityRemoved(const OdTvEntityId& entityId) {};
  virtual void insertRemoved(const OdTvEntityId& insertId) {};
  virtual void lightRemoved(const OdTvEntityId& insertId) {};

  //view
  virtual void viewCreated(const OdTvGsViewId& viewId) {};
  virtual void viewModified(const OdTvGsViewId& viewId) {};

  //Table records
  virtual void layerCreated(const OdTvLayerId& layerId) {};
  virtual void layerModified(const OdTvLayerId& layerId) {};

  virtual void materialCreated(const OdTvMaterialId& materialId) {};

  virtual void imageCreated(const OdTvRasterImageId& iamgeId) {};

  virtual void blockCreated(const OdTvBlockId& blockId) {};
  virtual void blockVectorizationBegin(const OdTvBlockId& blockId) {};
  virtual void blockVectorizationDone(const OdTvBlockId& blockId) {};

  virtual void linetypeCreated(const OdTvLinetypeId& linetypeId) {};

  virtual void textStyleCreated(const OdTvTextStyleId& textStyleId) {};

  //Models
  virtual void modelCreated(const OdTvModelId& modelId) {};
  virtual void modelActivated(const OdTvModelId& modelId) {};

  //update
  virtual void updateBegins() {};
  virtual void updateEnds() {};

  virtual void tvDeviceCreated(const OdTvGsDeviceId& tvDeviceId)
  {
    m_tvDeviceId = tvDeviceId;
  };

  OdTvGsDeviceId getTvDevice() const
  {
    return m_tvDeviceId;
  };

private:
  OdTvGsDeviceId m_tvDeviceId;
};

//***************************************************************************//
// 'OdTvBim2VisualizeVecorizationCaller' methods implementation
//***************************************************************************//

void OdTvBim2VisualizeVecorizationCaller::apcEntryPoint(OdApcParamType pMessage)
{
  OdTvBim2VisualizeVecorizationContext* pContext = (OdTvBim2VisualizeVecorizationContext*)pMessage;

  OdBmDBDrawingPtr pDBDrawing = pContext->m_bmObjectId.openObject();
  //create Ex Visualize device
  pContext->m_pDatabaseAccessMutex->lock();

  OdGsCacheRedirectionManager* pRedirectionManager = odgsGetGsCacheRedirectionManager();
  {
    OdGsDevicePtr pDevice = pContext->m_pGs->createDevice();

    OdTvDeviceCreationNotifier notifier;
    // setup ExVisualize device properties
    OdRxDictionaryPtr pProperties = pDevice->properties();

    // Disable DisplayViaGLES2
    if (pProperties->has(OD_T("DisplayViaGLES2")))
      pProperties->putAt(OD_T("DisplayViaGLES2"), OdRxVariantValue(false));

    if (pProperties->has(OD_T("DatabaseMutex")))
      pProperties->putAt(OD_T("DatabaseMutex"), OdRxVariantValue((OdIntPtr)(pContext->m_pDatabaseAccessMutex)));
    if (pProperties->has(OD_T("DeviceNotifier")))
      pProperties->putAt(OD_T("DeviceNotifier"), OdRxVariantValue((OdIntPtr)(&notifier)));

    OdTvGsDeviceId activeTvDeviceId = OdTvGsDeviceId();
    OdString tvModelName = OdString();
    setupExVisualizeDeviceProp(pProperties, pContext->m_tvDbId, tvModelName, pContext->m_properties, activeTvDeviceId
      , pDBDrawing->getBaseViewNameFormat() == OdBm::ViewType::_3d, pContext);
    pContext->m_pDatabaseAccessMutex->unlock();

    //setup bim context
    OdGiContextForBmDatabasePtr pBmContext = OdGiContextForBmDatabase::createObject();
    pBmContext->enableGsModel(true);
    pBmContext->setDatabase(pContext->m_pDb);

    //set the palette
    const ODCOLORREF* palette = odcmAcadPalette(pContext->m_background);

    OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;
    pPalCpy.insert(pPalCpy.begin(), palette, palette + 256);
    pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

    //set the background
    pDevice->setBackgroundColor(pContext->m_background);
    pBmContext->setPaletteBackground(pContext->m_background);

    //setup layout
    pContext->m_pSetupDBDrawingViewsMutex->lock(); // VIS-1826: temporary solution
    OdGsBmDBDrawingHelperPtr pDrawingHelper = OdGsBmDBDrawingHelper::setupDBDrawingViews(pContext->m_bmObjectId, pDevice, pBmContext);
    pContext->m_pSetupDBDrawingViewsMutex->unlock(); // VIS-1826: temporary solution

    //set thin mode
    pDrawingHelper->setThinLinesMode(pContext->m_properties->getThinLines());

    //call onsize
    OdTvDCRect* pRect = (OdTvDCRect*)pContext->m_properties->getDCRect();
    if (pRect && (pRect->xmax > 0 || pRect->xmin > 0 || pRect->ymax > 0 || pRect->ymin > 0))
    {
      OdGsDCRect  gsRect(pRect->xmin, pRect->xmax, pRect->ymin, pRect->ymax);
      pDrawingHelper->onSize(gsRect);
    }

    //call update (vectorization)
    pDrawingHelper->update();

    //setup connections between views in device and append non db lights
    if (pContext->m_tvDbId.isValid())
    {
      pContext->m_pDatabaseAccessMutex->lock();

      OdTvGsDeviceId tvDeviceId = notifier.getTvDevice();
      if (!tvDeviceId.isNull())
      {
        setupConnectionsBetweenTvViews(pContext->m_bmObjectId, pDevice, tvDeviceId);
        resetViewsModelsNames(tvDeviceId);
      }

      pContext->m_pDatabaseAccessMutex->unlock();
    }

    pRedirectionManager->getProtectionMutex().lock();
  }
  pRedirectionManager->getProtectionMutex().unlock();

  delete pContext;
}

//***************************************************************************//
// 'OdTvBim2VisualizeVecorizationThreadContext' methods implementation
//***************************************************************************//

OdTvBim2VisualizeVecorizationThreadContextPtr OdTvBim2VisualizeVecorizationThreadContext::createObject()
{
  return OdRxObjectImpl<OdTvBim2VisualizeVecorizationThreadContext>::createObject();
}

void OdTvBim2VisualizeVecorizationThreadContext::vectorizeDevice(OdTvBim2VisualizeVecorizationContext* pContext)
{
  if (m_bInterrupt)
    start();
  if (m_pMTQueue.isNull())
    m_pMTQueue = m_backQueue.queue(pContext->m_nViewsImportThreads);

  if (!m_pMTQueue.isNull())
    m_pMTQueue->addEntryPoint(OdRxObjectImpl< OdTvBim2VisualizeVecorizationCaller >::createObject(), (OdApcParamType)pContext);
}

void OdTvBim2VisualizeVecorizationThreadContext::stop()
{
  m_pInternalMutex.get()->lock();
  m_bInterrupt = true;
  m_pInternalMutex.get()->unlock();
  m_pMTQueue->wait();
}

void OdTvBim2VisualizeVecorizationThreadContext::start()
{
  m_pInternalMutex.get()->lock();
  m_bInterrupt = false;
  m_pInternalMutex.get()->unlock();
}

void OdTvBim2VisualizeVecorizationThreadContext::wait()
{
  if (!m_pMTQueue.isNull())
    m_pMTQueue->wait();
}

//***************************************************************************//
// Other functions implementation
//***************************************************************************//

void resetViewsModelsNames(OdTvGsDeviceId idTVDevice)
{
  OdTvGsDevicePtr pDevice = idTVDevice.openObject();

  for (int i = 0; i < pDevice->numViews(); i++)
  {
    OdTvGsViewId viewId = pDevice->viewAt(i);
    OdTvGsViewPtr pView = viewId.openObject();
    if (pView.isNull())
      continue;

    OdString viewName = pView->getName();
    int nModels = pView->numModels();

    for (int j = 0; j < nModels; j++)
    {
      OdTvModelId modelId = pView->modelAt(j);
      OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);

      if (!pModel.isNull())
      {
        if (nModels == 1)
          pModel->setName(viewName);
        else
        {
          OdString modelName;
          modelName.format(L"%s_%d", viewName.c_str(), j + 1);
        }
      }
    }
  }
  return;
}

void setupExVisualizeDeviceProp(OdRxDictionaryPtr& pProperties, const OdTvDatabaseId& tvDbId,
  const OdString& modelName, const BIM2Visualize::OdTvVisualizeBimFilerPropertiesPtr& importProperties,
  OdTvGsDeviceId& tvDeviceIdForAppend, bool bIs3DView, OdTvBim2VisualizeVecorizationContext* pContext)
{
  if (pProperties.get())
  {
    if (pProperties->has(OD_T("DisplayViaGLES2")))
      pProperties->putAt(OD_T("DisplayViaGLES2"), OdRxVariantValue(false));
    if (pProperties->has(OD_T("AllowNonPersistentObjects")))
      pProperties->putAt(OD_T("AllowNonPersistentObjects"), OdRxVariantValue(false));
    if (pProperties->has(OD_T("TvDatabaseID")))
      pProperties->putAt(OD_T("TvDatabaseID"), OdRxVariantValue((OdIntPtr)(&tvDbId)));

    if (pProperties->has(OD_T("WriteUserData")))
      pProperties->putAt(OD_T("WriteUserData"), OdRxVariantValue(importProperties->getStoreSourceObjects()));
    if (pProperties->has(OD_T("GenerateEntityNames")))
      pProperties->putAt(OD_T("GenerateEntityNames"), OdRxVariantValue(importProperties->getObjectNaming()));

    if (pProperties->has(OD_T("PerModelViews")))
      pProperties->putAt(OD_T("PerModelViews"), OdRxVariantValue(true));
    if (pProperties->has(OD_T("CompareUnnamedImages")))
      pProperties->putAt(OD_T("CompareUnnamedImages"), OdRxVariantValue(true));

    if (bIs3DView)
    {
      if (pProperties->has(OD_T("IgnoreColoredShape")))
        pProperties->putAt(OD_T("IgnoreColoredShape"), OdRxVariantValue(true));
    }

    if (pProperties->has(OD_T("ModelName")))
      pProperties->putAt(OD_T("ModelName"), OdRxVariantValue(modelName));

    if (!tvDeviceIdForAppend.isNull())
    {
      if (pProperties->has(OD_T("IgnoreViewInfoFlags")))
        pProperties->putAt(OD_T("IgnoreViewInfoFlags"), OdRxVariantValue(true));
      if (pProperties->has(OD_T("NamePrefix")))
        pProperties->putAt(OD_T("NamePrefix"), OdRxVariantValue(modelName));
      if (pProperties->has(OD_T("TvDeviceDAM")))
        pProperties->putAt(OD_T("TvDeviceDAM"), OdRxVariantValue((OdIntPtr)(&tvDeviceIdForAppend)));

      OdTvGsViewId viewId = tvDeviceIdForAppend.openObject()->getActiveView();
      OdString name = viewId.openObject()->getName();
      if (pProperties->has(OD_T("TvViewDAM")))
        pProperties->putAt(OD_T("TvViewDAM"), OdRxVariantValue((OdIntPtr)(&viewId)));
    }
    //Write font file path as user data
    if (pProperties->has(OD_T("WriteFontFilePath")))
      pProperties->putAt(OD_T("WriteFontFilePath"), OdRxVariantValue(true));

    if (pProperties->has(OD_T("IgnoreFlags")))
    {
      OdUInt16 flags = OdRxVariantValue(pProperties->getAt(OD_T("IgnoreFlags")).get())->getUInt16();
      SETBIT(flags, DeviceIgnoreFlags::kIgnoreEdgesColors, pContext->m_properties->getIgnoreEdgesColors());
      pProperties->putAt(OD_T("IgnoreFlags"), OdRxVariantValue(flags));
    }
  }
}

int getViewId(OdGsDevice* pDevice, OdGsView* pView)
{
  if (!pDevice || !pView)
    return -1;

  int num = pDevice->numViews();
  int iViewId = -1;
  for (int i = 0; i < num; ++i)
  {
    OdGsView* pViewForFind = pDevice->viewAt(i);
    if (pViewForFind == pView)
    {
      iViewId = i;
      break;
    }
  }

  return iViewId;
}

void applyClipping(OdTvGsViewPtr pTvView, OdGsView* pGsView, const OdGeMatrix3d& mDevToWorld, bool bIs3DView)
{
  if (pGsView == 0 || pTvView.isNull())
    return;

  //get clipping parameters
  OdIntArray counts;
  OdGePoint2dArray vertices;
  pGsView->viewportClipRegion(counts, vertices);

  if (counts.size() == 0) //there is no clipping
    return;

  OdUInt32Array     numPtsInContours;
  numPtsInContours.resize(counts.size());
  for (unsigned int i = 0; i < counts.size(); i++)
  {
    numPtsInContours[i] = OdUInt32(counts[i]);
  }

  OdTvPoint2dArray wcsPoints;
  wcsPoints.resize(vertices.size());
  for (unsigned int i = 0; i < vertices.size(); i++)
  {
    OdGePoint3d vertices3d = OdGePoint3d(vertices[i].x, vertices[i].y, 0.);
    if (!bIs3DView)
      vertices3d.transformBy(mDevToWorld);
    wcsPoints[i] = OdTvPoint2d(vertices3d.x, vertices3d.y);
  }

  pTvView->setClipRegion(int(counts.size()), numPtsInContours.getPtr(), wcsPoints.getPtr(), true);
}

void setupConnectionsBetweenTvViews(OdBmObjectId idDBDrawing, OdGsDevice* pDevice, OdTvGsDeviceId idTVDevice)
{
  //check existance of the tv device
  OdTvGsDevicePtr pTvDevice = idTVDevice.openObject(OdTv::kForWrite);
  if (pTvDevice.isNull())
    return;

  OdBmDBDrawingPtr pDBDrawing = idDBDrawing.safeOpenObject();
  OdBmObjectIdArray vpsArray;
  pDBDrawing->getViewports(vpsArray);
  ODA_ASSERT(0 != vpsArray.size());
  if (vpsArray.size() == 0)
    return;

  //set name to the device
  pTvDevice->setName(pDBDrawing->getName());

  //get main view (gs views and names)
  OdBmViewportPtr pViewport = vpsArray.getAt(0).safeOpenObject();

  OdBmObjectId idDBMainView = pViewport->getDbViewId();
  OdBmDBViewPtr pDBMainView = idDBMainView.safeOpenObject();
  OdString strMainViewName = correctName(pDBMainView->getViewName());
  OdString strMainViewNameFront = strMainViewName + OD_T("_Front");

  OdGsView* pMainView = pViewport->gsView();
  OdGsView* pMainViewFront = pViewport->gsFrontView();
  if (!pMainView || !pMainViewFront)
    return;

  //get world to Device matrix from main view
  OdGeMatrix3d matr = pMainView->worldToDeviceMatrix();
  matr.invert();

  //get appropriate Visualize main and front main views
  int mainViewId = getViewId(pDevice, pMainView);
  int mainFrontViewId = getViewId(pDevice, pMainViewFront);

  OdTvGsViewId idTvMainView = pTvDevice->viewAt(mainViewId);
  OdTvGsViewId idTvMainFrontView = pTvDevice->viewAt(mainFrontViewId);
  if (idTvMainView.isNull() || idTvMainFrontView.isNull())
    return;

  OdTvGsViewPtr pTVViewMain = idTvMainView.openObject(OdTv::kForWrite);
  pTVViewMain->setActive(true);
  pTVViewMain->setName(strMainViewName);
  pTVViewMain->addSibling(idTvMainFrontView);

  OdTvGsViewPtr pTVViewMainFront = idTvMainFrontView.openObject(OdTv::kForWrite);
  pTVViewMainFront->setName(strMainViewNameFront);

  if (pDBDrawing->getBaseViewNameFormat() != OdBm::ViewType::_3d)
  {
    pTVViewMain->set2dMode(true);
    pTVViewMainFront->set2dMode(true);
  }

  //apply clipping 
  applyClipping(pTVViewMain, pMainView, matr, pDBDrawing->getBaseViewNameFormat() == OdBm::ViewType::_3d);
  applyClipping(pTVViewMainFront, pMainViewFront, matr, pDBDrawing->getBaseViewNameFormat() == OdBm::ViewType::_3d);

  // Set of viewports for a sheet. OdGsPaperLayoutHelper is an example.
  OdUInt32 iArrSize = vpsArray.size();
  if (iArrSize > 1) // Sheets has more than 1 viewport
  {
    for (OdUInt32 i = 1; i < iArrSize; ++i)
    {
      OdBmViewportPtr pEmbeddedViewport = vpsArray.getAt(i).safeOpenObject();

      OdBmObjectId idDBView = pEmbeddedViewport->getDbViewId();
      OdBmDBViewPtr pDBView = idDBView.safeOpenObject();
      OdString strName = correctName(pDBView->getViewName());

      OdGsView* pGsView = pEmbeddedViewport->gsView();
      OdGsView* pGsFrontView = pEmbeddedViewport->gsFrontView();

      int embeddedViewId = getViewId(pDevice, pGsView);
      int embeddedFrontViewId = getViewId(pDevice, pGsFrontView);
      OdTvGsViewId idTvEmbeddedView = idTVDevice.openObject()->viewAt(embeddedViewId);
      OdTvGsViewId idTvEmbeddedFrontView = idTVDevice.openObject()->viewAt(embeddedFrontViewId);
      if (!idTvEmbeddedView.isNull() && !idTvEmbeddedFrontView.isNull())
      {
        OdTvGsViewPtr pTVViewEmbedded = idTvEmbeddedView.openObject(OdTv::kForWrite);
        OdTvGsViewPtr pTVViewEmbeddedFront = idTvEmbeddedFrontView.openObject(OdTv::kForWrite);

        OdString strNameFront = strName + OD_T("_Front");
        pTVViewEmbedded->setName(strName);
        pTVViewEmbeddedFront->setName(strNameFront);

        if (pDBDrawing->getBaseViewNameFormat() != OdBm::ViewType::_3d)
        {
          pTVViewEmbedded->set2dMode(true);
          pTVViewEmbeddedFront->set2dMode(true);
        }

        OdTvGsView::ViewportObjectInfo vi;

        //get viewport parameters
        OdGsDCRect rect;
        pGsView->getViewport(rect);

        OdTvPoint ll, ur;
        ll.set(rect.m_min.x, rect.m_min.y, 0.);
        ur.set(rect.m_max.x, rect.m_max.y, 0.);

        ll.transformBy(matr);
        ur.transformBy(matr);

        vi.m_wcsLowerLeft = OdTvPoint2d(ll.x, ll.y);
        vi.m_wcsUpperRight = OdTvPoint2d(ur.x, ur.y);

        //get clipping parameters
        OdIntArray counts;
        OdGePoint2dArray vertices;
        pGsView->viewportClipRegion(counts, vertices);

        vi.m_numPtsInContours.resize(counts.size());
        for (unsigned int i = 0; i < counts.size(); i++)
        {
          vi.m_numPtsInContours[i] = OdUInt32(counts[i]);
        }

        vi.m_wcsCountoursPts.resize(vertices.size());
        for (unsigned int i = 0; i < vertices.size(); i++)
        {
          OdTvPoint vertices3d = OdTvPoint(vertices[i].x, vertices[i].y, 0.);
          vertices3d.transformBy(matr);
          vi.m_wcsCountoursPts[i] = OdTvPoint2d(vertices3d.x, vertices3d.y);
        }

        //add view as a viewport object
        pTVViewMain->addViewportObject(idTvEmbeddedView, vi);

        vi.m_wcsCountoursPts.clear();
        vi.m_numPtsInContours.clear();
        pTVViewMain->addViewportObject(idTvEmbeddedFrontView, vi);
      }
    }
  }

  return;
}
