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
//   This application incorporates Open Design Alliance software pursuant to a
//   license agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance.
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
#include "DwgHelper/DwgHelper.hpp"

#include "OdaCommon.h"
#include "RxDynamicModule.h"
#include "RxObject.h"
#include "RxVariantValue.h"
#include "DbGsManager.h"
#include "ColorMapping.h"
#include "TvModuleNames.h"
#include "DbBlockTableRecord.h"
#include "DbDatabase.h"
#include "../../../../CommonApplications/Visualize/Examples/Dwg2Visualize/Dwg2Visualize.h"
#include "GiContextForDbDatabase.h"
#include "Ed/EdCommandContext.h"
#include "IStreamOutput.hpp"
#include "TvInsert.h"


void setupTvViews(OdDbObjectId layoutId, OdGsLayoutHelper* pLayoutHelper, OdTvGsDeviceId idTVDevice,
                  const ODCOLORREF& borderColor, OdString* pNewModelName);

void setViewBorderProperties(OdGsDevice* pDevice, const ODCOLORREF& color);

int getActiveViewId(OdGsLayoutHelper* pLayoutHelper, int& iPaperViewId);

void setViewAndModelNames(const OdTvGsViewId& viewId, const OdString& deviceName,
                          const OdGsClientViewInfo& viewInfo, OdString* pNewModelName);

std::tuple<OdTvDatabaseId*, OdGsDevice*> DwgHelper::setupRuntimeImportDwgToVsf(OdDbDatabase* pDb, ODCOLORREF background)
{
  OdDbObjectId activeLayoutId;

  {
    OdDbBlockTableRecordPtr pBr = pDb->getActiveLayoutBTRId().openObject();
    activeLayoutId = pBr->getLayoutId();
  }

  // load visualize transform device
  OdGsModulePtr pGs = ::odrxDynamicLinker()->loadModule(OdTvVisualizeDeviceModuleName, false);
  if (pGs.isNull()) {
    throw OdError("Fail load OdTvVisualizeDeviceModule");
  }

  //SEA name for ModelSpace
  OdString modelSpaceName = OdString::kEmpty;

  //create empty tv database.
  OdTvFactoryId tvFactoryId = odTvGetFactory();
  OdTvDatabaseId tvDbId = tvFactoryId.createDatabase();

  //SEA cache layout helper to share GsModel
  OdGsLayoutHelperPtr pCachedLayoutHelper;

  OdGsDevicePtr pDevice = pGs->createDevice();

  OdRxDictionaryPtr pProperties = pDevice->properties();
  OdTvGsDeviceId activeTvDeviceId = OdTvGsDeviceId();

  // TODO setup prop
  if (pProperties.get())
  {
    if (pProperties->has(OD_T("DisplayViaGLES2")))
      pProperties->putAt(OD_T("DisplayViaGLES2"), OdRxVariantValue(false));
    if (pProperties->has(OD_T("AllowNonPersistentObjects")))
      pProperties->putAt(OD_T("AllowNonPersistentObjects"), OdRxVariantValue(false));
    if (pProperties->has(OD_T("EnableTiming")))
      pProperties->putAt(OD_T("EnableTiming"), OdRxVariantValue(false));
    if (pProperties->has(OD_T("TvDatabaseID")))
      pProperties->putAt(OD_T("TvDatabaseID"), OdRxVariantValue((OdIntPtr)(&tvDbId)));
    if (pProperties->has(OD_T("DisableEntitiesRemoving")))
      pProperties->putAt(OD_T("DisableEntitiesRemoving"), OdRxVariantValue(false));
    if (pProperties->has(OD_T("EnableMultithread")))
      pProperties->putAt(OD_T("EnableMultithread"), OdRxVariantValue(true));
    if (pProperties->has(OD_T("MaxRegenThreads")))
      pProperties->putAt(OD_T("MaxRegenThreads"), OdRxVariantValue((OdUInt16)2));
    if (pProperties->has(OD_T("WriteUserData")))
      pProperties->putAt(OD_T("WriteUserData"), OdRxVariantValue(true));
    if (pProperties->has(OD_T("WriteFontFilePath")))
      pProperties->putAt(OD_T("WriteFontFilePath"), OdRxVariantValue(true));
    if (pProperties->has(OD_T("ImportFrozenLayers")))
      pProperties->putAt(OD_T("ImportFrozenLayers"), OdRxVariantValue(true));
  }
  //setup dwg context
  OdGiContextForDbDatabasePtr pDwgContext = OdGiContextForDbDatabase::createObject();
  pDwgContext->enableGsModel(true);
  pDwgContext->setDatabase(pDb);

  OdGsLayoutHelperPtr pLayoutHelper = OdDbGsManager::setupLayoutViews(activeLayoutId, pDevice, pDwgContext);
  if (pCachedLayoutHelper.isNull())
  {
    pCachedLayoutHelper = pLayoutHelper;
  }

  const ODCOLORREF* palette = odcmAcadPalette(background);

  OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > pPalCpy;
  pPalCpy.insert(pPalCpy.begin(), palette, palette + 256);

  pPalCpy[0] = background;
  pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);

  OdGsPaperLayoutHelperPtr pPSHelper = OdGsPaperLayoutHelper::cast(pLayoutHelper);
  if (pPSHelper.isNull())
    pDevice->setBackgroundColor(background); // for model space
  else
    pDevice->setBackgroundColor(ODRGB(173, 174, 173)); // ACAD's color for paper bg

  pDwgContext->setPaletteBackground(background);

  //set view border properties
  if (pPSHelper.isNull())
    setViewBorderProperties(pDevice.get(), pPalCpy[7]);

  OdGsDCRect  gsRect(0, 1920, 1080, 0);
  pDevice->onSize(gsRect);

  pLayoutHelper->update();

  if (tvDbId.isValid())
  {

    OdTvDevicesIteratorPtr pDevicesIterator = tvDbId.openObject()->getDevicesIterator();
    if (!pDevicesIterator.isNull()) // here we have O(n^2) but ut us not a problem
    {
      unsigned int nCount = 0;
      while (!pDevicesIterator->done())
      {
        OdTvGsDeviceId tvDeviceId = pDevicesIterator->getDevice();
        if (nCount == 0)
        {
          if (pLayoutHelper->layoutId() == activeLayoutId && !tvDeviceId.isNull())
            tvDeviceId.openObject(OdTv::kForWrite)->setActive(true);

          if (!tvDeviceId.isNull())
            tvDeviceId.openObject(OdTv::kForWrite)->setOption(OdTvGsDevice::kUseVisualStyles, true);

          setupTvViews(pLayoutHelper->layoutId(), pLayoutHelper.get(), tvDeviceId, pPalCpy[7], &modelSpaceName);
          break;
        }
        nCount++;
        pDevicesIterator->step();
      }
    }
  }

  pLayoutHelper->addRef();

  return std::make_tuple<OdTvDatabaseId*, OdGsDevice*>(new OdTvDatabaseId(tvDbId), pLayoutHelper.get());
}

OdDbDatabase* DwgHelper::getDwgDatabase(OdEdCommandContext* pCtx)
{
  OdRxVariantValue value = (OdRxVariantValue)pCtx->arbitraryData("NativeDatabase");
  OdDbDatabase* pDb = (OdDbDatabase*)value->getIntPtr();
  return pDb;
}

OdGsDevice* DwgHelper::getImportDevice(OdEdCommandContext* pCtx)
{
  OdRxVariantValue value = (OdRxVariantValue)pCtx->arbitraryData("Dwg2Visualize");
  OdGsDevice* pGs = (OdGsDevice*)value->getIntPtr();
  return pGs;
}

OdTvDatabaseId* DwgHelper::getVisualizeDbId(OdEdCommandContext* pCtx)
{
  OdRxVariantValue value = (OdRxVariantValue)pCtx->arbitraryData("TvDatabaseID");
  OdTvDatabaseId* pDbId = (OdTvDatabaseId*)value->getIntPtr();
  return pDbId;
}

void DwgHelper::setDwgDatabase(OdEdCommandContext* pCtx, OdDbDatabase* pDb)
{
  pCtx->setArbitraryData("NativeDatabase", OdRxVariantValue((OdIntPtr)(pDb)));
}

void DwgHelper::setImportDevice(OdEdCommandContext* pCtx, OdGsDevice* pGs)
{
  pCtx->setArbitraryData("Dwg2Visualize", OdRxVariantValue((OdIntPtr)(pGs)));
}

void DwgHelper::setVisualizeDbId(OdEdCommandContext* pCtx, OdTvDatabaseId* pVsDbId)
{
  pCtx->setArbitraryData("TvDatabaseID", OdRxVariantValue((OdIntPtr)(pVsDbId)));
}

void DwgHelper::invalidateAndUpdate(OdEdCommandContext* pCtx)
{
  OdGsDevice* pDevice = getImportDevice(pCtx);
  if (pDevice)
  {
    pDevice->invalidate();
    pDevice->update();
  }
}

void DwgHelper::invalidateWithRegenerationAndUpdate(OdEdCommandContext* pCtx)
{
  OdGsLayoutHelper* pDevice = static_cast<OdGsLayoutHelper*>(getImportDevice(pCtx));
  if (pDevice)
  {
    pDevice->invalidate();
    if (pDevice->gsModel())
      pDevice->gsModel()->invalidate(OdGsModel::kInvalidateAll);
    pDevice->update();
  }
}

IStreamOutput* DwgHelper::getStreamOutput(OdEdCommandContext* pCtx) 
{
  OdRxVariantValue value = (OdRxVariantValue)pCtx->arbitraryData(OD_STREAM_OUTPUT_ATTRIBUTE_NAME);
  IStreamOutput* pStreamOut = (IStreamOutput*)value->getIntPtr();
  return pStreamOut;
}

INativeHandleEntityStore* DwgHelper::getNativeHandleEntityStore(OdEdCommandContext* pCtx)
{
  OdRxVariantValue value = (OdRxVariantValue)pCtx->arbitraryData(OD_NATIVE_HANDLE_ENTITY_STORE);
  return (INativeHandleEntityStore*)value->getIntPtr();
}

void DwgHelper::bindNativeHandlesWithVisualizeEntities(OdEdCommandContext* pCtx)
{
  OdTvDatabaseId* dbId = getVisualizeDbId(pCtx);
  INativeHandleEntityStore* entityStore = getNativeHandleEntityStore(pCtx);
  OdDbHandle handle = 0;

  auto modeIterator = dbId->openObject()->getModelsIterator();
  for (; !modeIterator->done(); modeIterator->step())
  {
    auto modelId = modeIterator->getModel();
    auto entitiesIterator = modelId.openObject()->getEntitiesIterator();
    for (; !entitiesIterator->done(); entitiesIterator->step())
    {
      auto entityId = entitiesIterator->getEntity();
      if (entityId.getType() == OdTvEntityId::kEntity)
      {
        handle = entityId.openObject()->getNativeDatabaseHandle();
      }
      else if (entityId.getType() == OdTvEntityId::kInsert)
      {
        handle = entityId.openObjectAsInsert()->getNativeDatabaseHandle();
      }
      else if (entityId.getType() == OdTvEntityId::kLight)
      {
        handle = entityId.openObjectAsLight()->getNativeDatabaseHandle();
      }
      else
      {
        throw OdError("Wrong entity type");
      }
      entityStore->bind(handle, entityId);
    }
  }
}

void setViewBorderProperties(OdGsDevice* pDevice, const ODCOLORREF& color)
{
  int n = pDevice->numViews();
  if (n > 1)
  {
    for (int i = 0; i < n; ++i)
    {
      OdGsViewPtr pView = pDevice->viewAt(i);
      pView->setViewportBorderVisibility(true);
      pView->setViewportBorderProperties(color, 1);
    }
  }
}

int getActiveViewId(OdGsLayoutHelper* pLayoutHelper, int& iPaperViewId)
{
  if (!pLayoutHelper)
    return 0;

  iPaperViewId = -1;
  bool bPaperSpace = false;
  if (pLayoutHelper->isA() == OdGsPaperLayoutHelper::desc())
    bPaperSpace = true;

  OdGsViewPtr pActiveView = pLayoutHelper->activeView();
  int num = pLayoutHelper->numViews();
  int iActViewViewInd = 0;
  for (int i = 0; i < num; ++i)
  {
    OdGsView* pView = pLayoutHelper->viewAt(i);
    OdGsClientViewInfo viewInfo;
    pView->clientViewInfo(viewInfo);

    if (!bPaperSpace)
    {
      if (pView == pActiveView.get())
      {
        iActViewViewInd = i;
        break;
      }
    }
    else
    {
      if (viewInfo.viewportFlags & OdGsClientViewInfo::kHelperView)
      {
        iActViewViewInd = i;
      }
      else if (pView == pActiveView.get())
        iPaperViewId = i;
    }
  }

  return iActViewViewInd;
}

void setViewAndModelNames(
  const OdTvGsViewId& viewId,
  const OdString& deviceName,
  const OdGsClientViewInfo& viewInfo,
  OdString* pNewModelName)
{
  OdTvGsViewPtr pView = viewId.openObject(OdTv::kForWrite);
  OdString viewName = pView->getName();
  int nModels = pView->numModels();
  for (int j = 0; j < nModels; j++)
  {
    OdTvModelId modelId = pView->modelAt(j);
    OdTvModelPtr pModel = modelId.openObject(OdTv::kForWrite);
    if (!pModel.isNull())
    {
      if (nModels == 1)
      {
        if (viewInfo.viewportFlags & OdGsClientViewInfo::kHelperView)
        {
          OdString nameForPaper = deviceName;
          pModel->setName(nameForPaper);
          pView->setName(nameForPaper);
        }
        else if (viewInfo.viewportFlags & OdGsClientViewInfo::kDependentGeometry)
        {
          OdString paperOnlyName = deviceName + "_Paper";
          pModel->setName(paperOnlyName);
          pView->setName(paperOnlyName);
        }
        else
        {
          OdString modelName = L"Model";
          OdString viewportName;
          viewportName.format(L"%s_View_%d", deviceName.c_str(), (int)viewInfo.viewportId);
          pModel->setName(modelName);
          pView->setName(viewportName);
          if (pNewModelName)
          {
            *pNewModelName = modelName;
          }
        }
      }
      else
      {
        OdString modelName;
        modelName.format(L"%s_%d", viewName.c_str(), j + 1);
        pModel->setName(modelName);
      }
    }
  }
}

void setViewportConfiguration(
  const OdTvGsViewId& viewId,
  const OdTvGsViewId& activeViewId,
  OdGsLayoutHelperPtr pLayoutHelper,
  int iActViewInd,
  int ind)
{
  OdGeMatrix3d matr = pLayoutHelper->viewAt(iActViewInd)->worldToDeviceMatrix();
  matr.invert();

  OdTvGsViewPtr pViewportObject = viewId.openObject();

  if (!pViewportObject.isNull())
  {
    OdTvGsView::ViewportObjectInfo vi;

    //get viewport parameters
    OdGsView* pGsView = pLayoutHelper->viewAt(ind);
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
    OdTvGsViewPtr pActiveTvView = activeViewId.openObject(OdTv::kForWrite);
    pActiveTvView->addViewportObject(viewId, vi);
  }
}

void setupTvViews(
  OdDbObjectId layoutId,
  OdGsLayoutHelper* pLayoutHelper,
  OdTvGsDeviceId idTVDevice,
  const ODCOLORREF& borderColor,
  OdString* pNewModelName)
{
  //check existance of the tv device
  OdTvGsDevicePtr pTvDevice = idTVDevice.openObject(OdTv::kForWrite);
  if (pTvDevice.isNull())
    return;

  //check that the layout helper is paper space
  bool bPaperSpace = false;
  if (pLayoutHelper->isA() == OdGsPaperLayoutHelper::desc())
    bPaperSpace = true;

  //setup active view
  int iPaperViewInd = -1;
  int iActViewViewInd = getActiveViewId(pLayoutHelper, iPaperViewInd);
  OdTvGsViewId tvActiveViewId = pTvDevice->viewAt(iActViewViewInd);
  if (tvActiveViewId.isNull())
    return;

  OdTvGsViewPtr pTvActiveView = tvActiveViewId.openObject(OdTv::kForWrite);
  pTvActiveView->setActive(true);
  if (pTvActiveView->getBorderVisibility())
  {
    pTvActiveView->setBorderProperties(borderColor, 2);
  }

  //get DB layout helper
  OdDbLayoutPtr pLayout = layoutId.safeOpenObject();

  //set device name
  pTvDevice->setName(pLayout->getLayoutName());

  //setup views
  for (int i = 0; i < pTvDevice->numViews(); i++)
  {
    OdGsView* pGsView = pLayoutHelper->viewAt(i);
    OdGsClientViewInfo viewInfo;
    pGsView->clientViewInfo(viewInfo);

    // set new name for view and models
    OdTvGsViewId tvViewId = pTvDevice->viewAt(i);
    if (tvViewId.isNull())
      continue;

    //setup model and view name
    setViewAndModelNames(tvViewId, pTvDevice->getName(), viewInfo, pNewModelName);

    //setup view connection
    if (bPaperSpace)
    {
      if (i == iActViewViewInd)
        continue;

      if (i == iPaperViewInd)
        pTvActiveView->addSibling(tvViewId);
      else
        setViewportConfiguration(tvViewId, tvActiveViewId, pLayoutHelper, iActViewViewInd, i);
    }
  }
}
