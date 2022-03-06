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

#include "TvAndCore.h"

#include "TvError.h"
#include "TvAndDraggers.h"
#include "TvAndMemoryStatus.h"
#include "TvAndTools.h"
#include "TvExport.h"

inline double TvRound(double a)
{
    double aFloor = ::floor(a);
    if (a - aFloor >= 0.5)
        return aFloor + 1.0;
    return aFloor;
};

OdGePoint3d ToEyeToWorld(int x, int y, const OdTvGsViewPtr& pView)
{
  OdGePoint3d wcsPt(x, y, 0.0);
  
  if (pView->isPerspective())
  {
    wcsPt.z = pView->projectionMatrix()(2,3);
  }
  wcsPt.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
  wcsPt.z = 0.;
  // eye CS at this point.

  //transform to world coordinate system
  wcsPt.transformBy(pView->eyeToWorldMatrix());

  return wcsPt;
}

TvAndCore::TvAndCore()
     : m_bIsBlocked(true)
     , m_pAnimation(NULL)
     , m_bIsInitialized(false)
     , m_bRegenAbort(false)
     , m_bLowMemory(false)
     , m_bPartial(false)
     , m_pProgressMeter(NULL)
{
    m_sectioningOptions.setFillingColor(ODRGBA(255, 255, 0, 255));
    m_sectioningOptions.setFilled(true);

    m_groundShadow.options().m_diagMult = 1.2;
    m_groundShadow.options().m_lightIntensity = 0.01;
    m_groundShadow.options().m_groundOffset = 0.1;
}

TvAndCore::~TvAndCore()
{
    release();
}

void TvAndCore::release()
{
    if (!m_TvDatabaseId.isNull())
    {
        // before remove databse, erase all views, otherwise the application may crash when removing a view
        OdTvGsDevicePtr pDev = m_TvDeviceId.openObject(OdTv::kForWrite);
        pDev->setShowFPS(false);
        pDev->eraseAllViews();
        odTvGetFactory().removeDatabase(m_TvDatabaseId);
    }
    m_bIsBlocked = true;
    if (m_pAnimation)
    {
        delete m_pAnimation;
        m_pAnimation = NULL;
    }
}

void TvAndCore::syncParams(OdTvBaseImportParams *pParams)
{
    switch (m_fileExt)
    {
    case Drw:
    {
        OdTvDwgImportParams *pDwg = dynamic_cast<OdTvDwgImportParams *>(pParams);
        if (!pDwg)
            return;
        
        pDwg->setStoreSourceObjects(m_globalParams.m_importContainer.m_dwgParams.m_bStoreSource);
        pDwg->setClearEmptyObjects(m_globalParams.m_importContainer.m_dwgParams.m_bClearEmptyObjects);
        pDwg->setMultithreading(m_globalParams.m_importContainer.m_dwgParams.m_bEnableMT);
        pDwg->setCountOfThreads(m_globalParams.m_importContainer.m_dwgParams.m_iThreadsCount);
        pDwg->setImportBrepAsBrep(m_globalParams.m_importContainer.m_dwgParams.m_bImportBrepAsBrep);
        pDwg->setOpenSourcePartial(m_globalParams.m_importContainer.m_dwgParams.m_bLowMemoryImport);
        pDwg->setBackground(m_globalParams.m_importContainer.m_dwgParams.m_iBackgroundColor);

        break;
    }
    case Dgn:
    {
        OdTvDgnImportParams *pDgn = dynamic_cast<OdTvDgnImportParams *>(pParams);
        if (!pDgn)
            return;

        pDgn->setStoreSourceObjects(m_globalParams.m_importContainer.m_dgnParams.m_bStoreSource);
        pDgn->setClearEmptyObjects(m_globalParams.m_importContainer.m_dgnParams.m_bClearEmptyObjects);
        pDgn->setUseIsolinesFor3DObjects(m_globalParams.m_importContainer.m_dgnParams.m_bUseIsolinesFor3DObjects);

        break;
    }
    case Prc:
    {
        OdTvPrcImportParams *pPrc = dynamic_cast<OdTvPrcImportParams *>(pParams);
        if (!pPrc)
            return;

        pPrc->setStoreSourceObjects(m_globalParams.m_importContainer.m_prcParams.m_bStoreSource);
        pPrc->setClearEmptyObjects(m_globalParams.m_importContainer.m_prcParams.m_bClearEmptyObjects);
        pPrc->setRearrangeObjects(m_globalParams.m_importContainer.m_prcParams.m_bRearrangeObjects);
        pPrc->setImportBrepAsBrep(m_globalParams.m_importContainer.m_prcParams.m_bImportBrepAsBrep);

        break;
    }
    case Obj:
    {
        OdTvObjImportParams *pObj = dynamic_cast<OdTvObjImportParams *>(pParams);
        if (!pObj)
            return;
        
        pObj->setCalculateNormals(m_globalParams.m_importContainer.m_objParams.m_bCalculateNormalsAtVertices);
        pObj->setBrepFlipUVCoordinates(m_globalParams.m_importContainer.m_objParams.m_bFlipUVCoordinateSystem);
        pObj->setImportBrepAsBrep(m_globalParams.m_importContainer.m_objParams.m_bImportBrepAsBrep);

        break;
    }
    case Stl:
    {
        OdTvStlImportParams *pStl = dynamic_cast<OdTvStlImportParams *>(pParams);
        if (!pStl)
            return;
        
        pStl->setFixNormals(m_globalParams.m_importContainer.m_stlParams.m_bFixNormals);
        pStl->setUnifyDuplicatedVertices(m_globalParams.m_importContainer.m_stlParams.m_bUnifyDuplicatedVertices);
        pStl->setCalcNormalsAtVertices(m_globalParams.m_importContainer.m_stlParams.m_bCalcNormalsAtVertices);

        break;
    }
    case Rcs:
    {

        break;
    }
    case Ifc:
    {
        OdTvIfcImportParams *pIfc = dynamic_cast<OdTvIfcImportParams *>(pParams);
        if (!pIfc)
            return;

        pIfc->setThreadsCount((OdUInt16)4);
        pIfc->setEnableMultithreading(true);

        break;
    }
    }
}

OdString TvAndCore::openFile(const OdString &filePath)
{
    OdString errStr;
    m_databaseInfo.setFilePath(filePath);

    OdTvBaseImportParams* pParams = NULL;

    //get file extension
    OdString strExt = filePath.mid(filePath.reverseFind('.') + 1);
    strExt.makeUpper();
    OdTvDCRect defRect(0, 1024, 768, 0);
    if (strExt == OD_T("VSF"))
    {
        m_fileExt = Vsf;
        pParams = &m_importParamsContainer.baseParams;
    }
    else if (strExt == OD_T("DWG"))
    {
        m_fileExt = Drw;
        m_importParamsContainer.dwgParams.setDCRect(defRect);
        pParams = &m_importParamsContainer.dwgParams;
    }
    else if (strExt == OD_T("DGN"))
    {
        m_fileExt = Dgn;
        m_importParamsContainer.dgnParams.setDCRect(defRect);
        pParams = &m_importParamsContainer.dgnParams;
    }
    else if (strExt == OD_T("PRC"))
    {
        m_fileExt = Prc;
        m_importParamsContainer.prcParams.setDCRect(defRect);
        pParams = &m_importParamsContainer.prcParams;
    }
    else if (strExt == OD_T("OBJ"))
    {
        m_fileExt = Obj;
        pParams = &m_importParamsContainer.objParams;
    }
    else if (strExt == OD_T("STL"))
    {
        m_fileExt = Stl;
        pParams = &m_importParamsContainer.stlParams;
    }
    else if (strExt == OD_T("RCS"))
    {
        m_fileExt = Rcs;
        pParams = &m_importParamsContainer.rcsParams;
    }
    else if (strExt == OD_T("IFC"))
    {
        m_fileExt = Ifc;
        pParams = &m_importParamsContainer.ifcParams;
    }

    syncParams(pParams);
    pParams->setFilePath(filePath);

    bool bImport = m_fileExt != Vsf;
    if (!bImport)
        m_databaseInfo.setType(TvAndDatabaseInfo::kFromFile);
    else
        m_databaseInfo.setType(TvAndDatabaseInfo::kImport);

    if (pParams)
    {
        pParams->setFilePath(filePath);
        pParams->setProfiling(&m_databaseInfo);
    }

    OdTvResult rc = tvOk;

    if (m_fileExt == Vsf && m_globalParams.getPartialOpen())
    {
        if (m_globalParams.getUseLimitManager())
        {
            m_limitator.setMemoryLimit((OdUInt64)m_globalParams.getMemoryLimit() * 1024);
            odTvGetFactory().setLimitManager( &m_limitator );
        }
        else
            odTvGetFactory().setLimitManager(NULL);
        m_bPartial = true;
    }
    else if (m_fileExt == Drw)
    {
        OdTvDwgImportParams *pDwg = dynamic_cast<OdTvDwgImportParams *>(pParams);
        if (pDwg && pDwg->getOpenSourcePartial())
        {
            m_bLowMemory = true;
            m_bPartial = true;
            m_limitator.setMemoryLimit((OdUInt64)m_globalParams.getMemoryLimit() * 1024);
            odTvGetFactory().setLimitManager( &m_limitator );
        }
        else
            odTvGetFactory().setLimitManager(NULL);
    }
    else
        odTvGetFactory().setLimitManager(NULL);

    if (bImport && pParams)
    {
        try
        {
            if (!m_bLowMemory)
                m_TvDatabaseId = odTvGetFactory().importFile(pParams, &rc);
            else
            {
                //create and set progress meter
                if(m_pProgressMeter)
                    pParams->setProgressMeter(m_pProgressMeter);

                rc = odTvGetFactory().lowMemoryImportFile(pParams, filePath + L".vsf");

                // release progress meter
                if(m_pProgressMeter)
                {
                    pParams->setProgressMeter(NULL);
                    delete m_pProgressMeter;
                    m_pProgressMeter = NULL;
                }

                if( rc == tvOk )
                {
                  OdTvVsfImportParams params;
                  params.setFilePath( filePath + L".vsf" );
                  params.setMtImport( false );
                  m_TvDatabaseId = odTvGetFactory().importFile( &params, &rc );
                }
            }

            if (rc != tvOk)
            {
                return OD_T("Import of file was failed");
            }
        }
        catch (const OdError& e)
        {
            LOG_EXCEPTION(e);
            errStr = OD_T("Import of file was failed: ") + e.description();
        }
        catch (OdTvError &e)
        {
            LOG_EXCEPTION(e);
            errStr = OD_T("Import of file was failed: ") + e.description();
        }
        catch(...)
        {
            __android_log_print(ANDROID_LOG_ERROR, "Error", "Import of file was failed");
        }
    }
    else
    {
        try
        {
            OdPerfTimerBase* pTimer = NULL;
            if(pParams->getProfiling())
            {
                pTimer = OdPerfTimerBase::createTiming();
                pTimer->start();
            }
            OdTvVsfImportParams params;
            params.setFilePath( filePath );
            params.setMtImport( !m_globalParams.getPartialOpen() );
            m_TvDatabaseId = odTvGetFactory().importFile(&params, &rc);
            if(rc != tvOk)
            {
                return OD_T("Read of file was failed");
            }

            if(pParams->getProfiling()) 
            {
                pParams->getProfiling()->setImportTime(pTimer->permanentMSec());
                pTimer->stop();
            }
        }
        catch (const OdError& e)
        {
            LOG_EXCEPTION(e);
            errStr = OD_T("Read of file was failed: ") + e.description();
        }
        catch (OdTvError &e)
        {
            LOG_EXCEPTION(e);
            errStr = OD_T("Read of file was failed: ") + e.description();
        }
        catch(...)
        {
            __android_log_print(ANDROID_LOG_ERROR, "Error", "Read of file was failed");
        }
    }

    if (m_TvDatabaseId.isNull())
        return OD_T("Visualize database is NULL");

    OdTvDatabasePtr pDb = m_TvDatabaseId.openObject(OdTv::kForWrite);
    if (pDb.isNull())
        return OD_T("Visualize database is NULL");

    m_TvMainModelId = pDb->getModelsIterator()->getModel();
    if (!m_TvMainModelId.isNull())
        m_modelStat = m_TvMainModelId.openObject()->getStatistic();

    OdTvDevicesIteratorPtr pDevIt = pDb->getDevicesIterator();
    m_TvDeviceId = pDevIt->getDevice();

    return errStr;
}

OdString TvAndCore::setupDevice(OSWindowGLContext context, const OdTvDCRect &rect)
{
    OdString errStr;
    try
    {
        OdTvGsDevicePtr pDev = m_TvDeviceId.openObject(OdTv::kForWrite);
        pDev->setOption(OdTvGsDevice::kCreateGLContext, false);
        pDev->setOption(OdTvGsDevice::kBlendingMode, (OdUInt32)0);
        pDev->setActive(true);
        pDev->setOption(OdTvGsDevice::kUseOverlayBuffers, false);
        pDev->setOption(OdTvGsDevice::kUseSceneGraph, m_globalParams.getUseSceneGraph());

        // enable FXAA
        pDev->setOption(OdTvGsDevice::kFXAAEnable, true);
        pDev->setOption(OdTvGsDevice::kFXAAQuality, (OdUInt32)4);

        if(m_bPartial)
            pDev->setBackgroundPartialView(true);

        pDev->setupGsWithContext(context, rect, OdTvGsDevice::kOpenGLES2);

        init();
    }
    catch (OdTvError &e)
    {
        LOG_EXCEPTION(e);
        errStr = OD_T("Error during setup device:\n: ") + e.description();
    }
    catch (const OdError& e)
    {
        LOG_EXCEPTION(e);
        errStr = OD_T("Error during setup device:\n: ") + e.description();
    }
    catch(...)
    {
        __android_log_print(ANDROID_LOG_ERROR, "Error", "Error during setup device");
    }

    return errStr;
}

void TvAndCore::update()
{
    if (m_bIsBlocked || m_TvDeviceId.isNull())
        return;

    try
    {
        OdTvResult rc = tvOk;
        OdTvGsDevicePtr pDev = m_TvDeviceId.openObject(OdTv::kForWrite, &rc);
        if (pDev.isNull())
            return;

        bool viewParamsIsDiff = false;
        if (m_globalParams.getPartialOpen() || m_bLowMemory)
        {
            TvAndViewParamsComparator params(getActiveTvViewId());
            viewParamsIsDiff = m_viewParams != params;
            if (viewParamsIsDiff)
                m_viewParams = params;
        }

        OdPerfTimerBase* pTimer = NULL;
        if(!m_bIsInitialized) 
        {
            pTimer = OdPerfTimerBase::createTiming();
            pTimer->start();
            viewParamsIsDiff = true;
            m_viewParams = TvAndViewParamsComparator();
        }

        
        TvAndRegenAbortImpl impl;
        pDev->setRegenAbort( &impl );
        pDev->invalidate();
        pDev->update(NULL, !viewParamsIsDiff);
        pDev->setRegenAbort(NULL);

        if(!m_bIsInitialized) 
        {
            m_bIsInitialized = true;
            m_databaseInfo.setFirstUpdateTime(pTimer->permanentMSec());
            pTimer->stop();
        }
    }
    catch (const OdError& e)
    {
        LOG_EXCEPTION(e);
        return;
    }
    catch (OdTvError &e)
    {
        LOG_EXCEPTION(e);
        return;
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_ERROR, "Update error", "Error during update device");
        return;
    }

    //perform animation
    if (m_pAnimation && m_pAnimation->isRunning())
    {
        m_pAnimation->step();
        if (!m_pActiveDragger.isNull() && !m_pAnimation->isRunning())
        {
            m_pActiveDragger->notifyAboutViewChange(kViewChangeFull);
            finishFixedFrameRate();
        }
    }
}

bool TvAndCore::exportToPdf(bool b3D) const
{
    if (m_TvDatabaseId.isNull())
        return -1;

    OdTvDatabasePtr pDb = m_TvDatabaseId.openObject(OdTv::kForWrite);
    if (pDb.isNull())
        return -1;

    OdTvPdfExportParams params;
    params.set3DPdf(b3D);
    OdString path = m_databaseInfo.getFilePath();
    path = path.mid(0, path.reverseFind('.')) + OD_T(".pdf");
    params.setFilePath(path);
    return pDb->exportTo(&params) == tvOk;
}

void TvAndCore::init()
{
    if (m_TvDatabaseId.isNull() || m_TvDeviceId.isNull())
        return;

    OdTvDatabasePtr pDb = m_TvDatabaseId.openObject(OdTv::kForWrite);
    if (pDb.isNull())
        return;

    OdTvGsDevicePtr pDev = m_TvDeviceId.openObject(OdTv::kForWrite);
    if(pDev.isNull())
        return;

    //create model for sectioning geometry
    static int cuttingPlaneModelNumber = 1;
    OdString strCuttingPlaneModelName;
    strCuttingPlaneModelName.format(L"$ODA_TVVIEWER_SECTIONING_MODEL_%d", cuttingPlaneModelNumber++);
    m_cuttingPlanesModelId = pDb->createModel(strCuttingPlaneModelName, OdTvModel::kMain, false);

    // register app name (for user data)
    bool alreadyExist;
    m_appTvId = pDb->registerAppName(OD_TV_APP_NAME, alreadyExist);
    // find draggers model
    m_TvDraggersModelId = pDb->findModel(OD_T("$Draggers"));
    if (m_TvDraggersModelId.isNull())
        m_TvDraggersModelId = pDb->createModel(OD_T("$Draggers"), OdTvModel::kDirect, false);

    // apply global params
    OdTvExtendedView *pExtView = getActiveTvExtendedView();
    if (pExtView)
    {
        pExtView->setAnimationEnabled(m_globalParams.getAnimationEnabled());
        pExtView->setEnabledWCS(m_globalParams.getWcsEnabled());
    }
    if (m_globalParams.getFpsEnabled())
        pDev->setShowFPS(true);

    //create sectioning view
    static int cuttingPlaneViewNumber = 1;

    OdString strCuttingPlaneViewName;
    strCuttingPlaneViewName.format(L"$ODA_TVVIEWER_SECTIONING_VIEW_%d", cuttingPlaneViewNumber++);
    m_cuttingPlanesViewId = pDev->createView(strCuttingPlaneViewName, false);
    OdTvGsViewPtr pVsectioningView = m_cuttingPlanesViewId.openObject(OdTv::kForWrite);
    pVsectioningView->addModel(m_cuttingPlanesModelId);
    pVsectioningView->setMode(OdTvGsView::kGouraudShaded);

    // create default dragger (pan dragger)
    TvAndPanDragger *panDragger = new TvAndPanDragger(m_TvDeviceId, m_TvDraggersModelId, &m_globalParams);
    m_pActiveDragger = panDragger;
    eDraggerResult res = m_pActiveDragger->start(NULL, getActiveTvExtendedView());
    actionsAfterDragger(res);

    // set light
    if (m_fileExt == Drw)
    {
        OdTvGsViewPtr pView = getActiveTvViewPtr();
        if (!pView.isNull())
        {
            pView->enableDefaultLighting(true);
            pView->setDefaultLightingIntensity(0.8);
        }
    }

    m_bIsBlocked = false;
}

void TvAndCore::resizeDevice(int xMin, int xMax, int yMin, int yMax)
{
    if (m_bIsBlocked || m_TvDeviceId.isNull())
        return;
    OdTvGsDevicePtr pDev = m_TvDeviceId.openObject();
    pDev->onSize(OdTvDCRect(xMin, xMax, yMin, yMax));
}

// get active view id ot prt
OdTvGsViewId TvAndCore::getActiveTvViewId() const
{
    if (m_TvDeviceId.isNull())
        return OdTvGsViewId();
    OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject();
    OdTvGsViewId viewId = pDevice->getActiveView();
    if (viewId.isNull())
        viewId = pDevice->viewAt(0);
    return viewId;
}

OdTvGsViewPtr TvAndCore::getActiveTvViewPtr() const
{
    if (getActiveTvViewId().isNull())
        return OdTvGsViewPtr();
    return getActiveTvViewId().openObject(OdTv::kForWrite);
}

// get extended view
OdTvExtendedView *TvAndCore::getActiveTvExtendedView()
{
    OdTvGsViewId viewId = getActiveTvViewId();
    if (viewId.isNull())
        return NULL;

    std::map<OdTvGsViewId, OdTvExtendedView *>::iterator iter = m_tvExtendedViewsMap.find(viewId);
    if (iter != m_tvExtendedViewsMap.end())
        return iter->second;
    else
    {
        OdTvExtendedView *pBasicView = new OdTvExtendedView(viewId);
        pBasicView->setAnimationEnabled(true);
        pBasicView->setZoomScale(2);
        pBasicView->setAnimationDuration(0.9);

        OdTvGsViewPtr pTvView = viewId.openObject();
        if (!pTvView.isNull())
        {
            OdGeBoundBlock3d lastExt;
            if (pTvView->getLastViewExtents(lastExt))
                pBasicView->setViewExtentsForCaching(&lastExt);
        }

        m_tvExtendedViewsMap.insert(std::pair<OdTvGsViewId, OdTvExtendedView *>(viewId, pBasicView));

        return pBasicView;
    }

    return NULL;
}

void TvAndCore::startDragger(OdTvDraggerPtr pNewDragger, bool bUseCurrentAsPrevious)
{
    eDraggerResult res = kNothingToDo;
    if (m_pActiveDragger.isNull())
        res = pNewDragger->start(NULL, getActiveTvExtendedView());
    else
    {
        OdTvDraggerPtr pPrevDragger = m_pActiveDragger;
        if (m_pActiveDragger->hasPrevious())
        {
            eDraggerResult res_prev;
            if (bUseCurrentAsPrevious)
                m_pActiveDragger->finish(res_prev);
            else
                pPrevDragger = m_pActiveDragger->finish(res_prev);
            actionsAfterDragger(res_prev);
        }

        res = pNewDragger->start(pPrevDragger, getActiveTvExtendedView());
    }
    // need update active dragger before calling action
    m_pActiveDragger = pNewDragger;
    actionsAfterDragger(res);
}

void TvAndCore::finishDragger()
{
    if (m_pActiveDragger.isNull())
        return;

    if (m_pActiveDragger->hasPrevious() && m_pActiveDragger->canFinish())
    {
        // release current dragger
        eDraggerResult res;
        OdTvDraggerPtr pPrevDragger = m_pActiveDragger->finish(res);
        actionsAfterDragger(res);

        // activate previous dragger
        m_pActiveDragger = pPrevDragger;
        res = m_pActiveDragger->start(NULL, getActiveTvExtendedView()); /*here we use NULL since the previous dragger already was set (if exist)*/
        actionsAfterDragger(res);
    }

    if(m_backDelta != OdTvVector::kIdentity)
    {
        OdTvGsViewPtr pView = getActiveTvViewPtr();
        if(!pView.isNull())
        {
            pView->dolly(m_backDelta.transformBy(pView->viewingMatrix()));
            m_backDelta = OdTvVector::kIdentity;
        }
    }
}

void TvAndCore::actionsAfterDragger(eDraggerResult res)
{
    // if (res & kNeedUpdateView)
    //     update();

    if (res & kNeedFinishDragger)
        finishDragger();
}

eDraggerResult TvAndCore::onTouchDown(int x, int y)
{
    if (!m_pActiveDragger.isNull())
    {
        // activation first
        eDraggerResult res = m_pActiveDragger->activate();
        actionsAfterDragger(res);

        // next point after
        res = m_pActiveDragger->nextpoint(x, y);
        actionsAfterDragger(res);

        OdTvTextMarkupDragger* pTxtDragger = dynamic_cast<OdTvTextMarkupDragger*>(m_pActiveDragger.get());
        if(pTxtDragger)
        {
            OdTvGsViewPtr pView = getActiveTvViewPtr();
            if(!pView.isNull())
            {
                OdTvPoint screenPrevPt = pView->position().transformBy(pView->worldToDeviceMatrix());
                OdGePoint3d prevPt = ToEyeToWorld(screenPrevPt.x, screenPrevPt.y, pView) - pView->position().asVector();
                OdGePoint3d curPt = ToEyeToWorld(x, y, pView);
                OdTvVector delta = ( prevPt - (curPt - pView->position()) ).asVector();
                m_backDelta = ( prevPt + (pView->position() - curPt) ).asVector();
                pView->dolly(-delta.transformBy(pView->viewingMatrix()));
            }
        }

        return res;
    }

    return kNothingToDo;
}

void TvAndCore::onTouchMove(int x, int y)
{
    if (!m_pActiveDragger.isNull())
    {
        eDraggerResult res = m_pActiveDragger->drag(x, y);
        actionsAfterDragger(res);
    }
}

eDraggerResult TvAndCore::onTouchUp(int x, int y)
{
    if (!m_pActiveDragger.isNull())
    {
        eDraggerResult res = m_pActiveDragger->nextpointup(x, y);
        actionsAfterDragger(res);
        return res;
    }

    return kNothingToDo;
}

eDraggerResult TvAndCore::onProcessEnter()
{
    if (!m_pActiveDragger.isNull())
    {
        eDraggerResult res = m_pActiveDragger->processEnter();
        actionsAfterDragger(res);
        return res;
    }

    return kNothingToDo;
}

void TvAndCore::onProcessBackspace()
{
    if (!m_pActiveDragger.isNull())
    {
        eDraggerResult res = m_pActiveDragger->processBackspace();
        actionsAfterDragger(res);
    }
}

void TvAndCore::onProcessText(const OdString &text)
{
    if (!m_pActiveDragger.isNull())
    {
        eDraggerResult res = m_pActiveDragger->processText(text);
        actionsAfterDragger(res);
    }
}

void TvAndCore::zoom(double delta, double x, double y)
{
    // get the active view and perform zooming
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if (pView.isNull())
        return;

    OdGePoint3d pos(pView->position());
    pos.transformBy(pView->worldToDeviceMatrix());

    int vx, vy;
    vx = (int)TvRound(pos.x);
    vy = (int)TvRound(pos.y);
    vx = x - vx;
    vy = y - vy;

    screenDolly(vx, vy);
    pView->zoom(delta);
    screenDolly(-vx, -vy);

    //notify the dragger
    if (!m_pActiveDragger.isNull())
        m_pActiveDragger->notifyAboutViewChange(kViewChangeZoom);
}

void TvAndCore::screenDolly(int x, int y)
{
    // get the active view and perform zooming
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if (pView.isNull())
        return;

    OdGeVector3d vec(x, y, 0.0);
    vec.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
    pView->dolly(vec);
}

void TvAndCore::runNavigationAction(TvAndCore::NavigationAction navAct)
{
    OdTvDraggerPtr pNewDragger;
    OdTvGsViewPtr pView = getActiveTvViewId().openObject();

    switch (navAct)
    {
    case Pan:
    {
        pNewDragger = new TvAndPanDragger(m_TvDeviceId, m_TvDraggersModelId, &m_globalParams);
        break;
    }
    case Orbit:
    {
        pNewDragger = new TvAndOrbitDragger(m_TvDeviceId, m_TvDraggersModelId, &m_globalParams);
        disableMarkups();
        break;
    }
    case ZoomWindow:
    {
        pNewDragger = new TvAndZoomWindowDragger(m_TvDeviceId, m_TvDraggersModelId, this, &m_globalParams);
        break;
    }
    case ZoomExtents:
    {
        OdTvExtendedView *pBasicView = getActiveTvExtendedView();
        if (!pBasicView)
            return;
        //set view type
        pBasicView->zoomToExtents();

        //update cached extents if need
        OdGeBoundBlock3d lastExt;
        if (!pBasicView->getCachedExtents(lastExt))
        {
            OdTvGsViewPtr ptvView = pBasicView->getViewId().openObject();
            if (ptvView->getLastViewExtents(lastExt))
                pBasicView->setViewExtentsForCaching(&lastExt);
        }

        //check existance of the animation
        m_pAnimation = pBasicView->getAnimation();
        if (m_pAnimation)
        {
            m_pAnimation->start();
            performFixedFrameRate();
        }
        else if (!m_pActiveDragger.isNull())
            m_pActiveDragger->notifyAboutViewChange(kViewChangeZoom);
        break;
    }
    }

    //start dragger
    if (!pNewDragger.isNull())
        startDragger(pNewDragger);

    getActiveTvExtendedView()->setViewType(OdTvExtendedView::kCustom);
}

void TvAndCore::set3DView(OdTvExtendedView::e3DViewType type)
{
    OdTvExtendedView *pBasicView = getActiveTvExtendedView();
    if (!pBasicView)
        return;
    //set view type
    pBasicView->setViewType(type);
    //update cached extents if need
    OdGeBoundBlock3d lastExt;
    if (!pBasicView->getCachedExtents(lastExt))
    {
        OdTvGsViewPtr ptvView = pBasicView->getViewId().openObject();
        if (ptvView->getLastViewExtents(lastExt))
            pBasicView->setViewExtentsForCaching(&lastExt);
    }
    //check existance of the animation
    m_pAnimation = pBasicView->getAnimation();
    if (m_pAnimation)
    {
        m_pAnimation->start();
        performFixedFrameRate();
    }
    else if (!m_pActiveDragger.isNull())
        m_pActiveDragger->notifyAboutViewChange(kViewChangeFull);

    disableMarkups();
}

void TvAndCore::regenVisible()
{
    OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject(OdTv::kForWrite);
    if (pDevice.isNull())
        return;
    pDevice->regen(OdTvGsDevice::kRegenVisible);
}

bool TvAndCore::isPerspective() const
{
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if (pView.isNull())
        return false;
    return pView->isPerspective();
}

void TvAndCore::setProjection(OdTvGsView::Projection projType)
{
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if (pView.isNull())
        return;
    pView->setView(pView->position(), pView->target(), pView->upVector(), pView->fieldWidth(), pView->fieldHeight(), projType);
}

void TvAndCore::runRenderMode(OdTvGsView::RenderMode newMode)
{
    OdTvExtendedView *pBasicView = getActiveTvExtendedView();
    if (pBasicView)
    {
        pBasicView->setRenderMode(newMode);
        if (m_groundShadow.isAdded() && !isViewAllowGroundShadow())
            m_groundShadow.remove();
    }
}

OdTvGsView::RenderMode TvAndCore::getRenderMode()
{
    OdTvExtendedView *pBasicView = getActiveTvExtendedView();
    if (pBasicView)
        return pBasicView->getRenderMode();
    return OdTvGsView::kNone;
}

void TvAndCore::runMarkupAction(TvAndCore::MarkupAction act)
{
    if (m_TvMarkupsModelId.isNull())
    {
        OdTvDatabasePtr pDatabase = m_TvDatabaseId.openObject(OdTv::kForWrite);
        m_TvMarkupsModelId = pDatabase->findModel(OD_TV_MARKUP_MODEL);
        if (m_TvMarkupsModelId.isNull())
            m_TvMarkupsModelId = pDatabase->createModel(OD_TV_MARKUP_MODEL, OdTvModel::kDirect, false);
    }

    OdTvDraggerPtr pNewDragger;
    switch (act)
    {
    case Rectangle:
        pNewDragger = new OdTvRectangleMarkupDragger(m_TvDeviceId, m_TvMarkupsModelId, m_appTvId, OdTvColorDef(255, 0, 0), 3);
        break;
    case Circle:
        pNewDragger = new OdTvCircleMarkupDragger(m_TvDeviceId, m_TvMarkupsModelId, m_appTvId, OdTvColorDef(255, 0, 0), 3);
        break;
    case Handle:
        pNewDragger = new OdTvHandleMarkupDragger(m_TvDeviceId, m_TvMarkupsModelId, m_appTvId, OdTvColorDef(255, 0, 0), 3);
        break;
    case Cloud:
        pNewDragger = new OdTvCloudMarkupDragger(m_TvDeviceId, m_TvMarkupsModelId, m_appTvId, OdTvColorDef(255, 0, 0), 3);
        break;
    case Text:
        pNewDragger = new OdTvTextMarkupDragger(m_TvDeviceId, m_TvMarkupsModelId, m_appTvId, OdTvColorDef(255, 0, 0), 3);
        break;
    case Save:
    {
        break;
    }
    case Load:
    {
        break;
    }
    }

    //start dragger
    if (!pNewDragger.isNull())
        startDragger(pNewDragger);
}

void TvAndCore::disableMarkups()
{
    if (m_TvMarkupsModelId.isNull())
        return;
    OdTvModelPtr pMarkupModel = m_TvMarkupsModelId.openObject(OdTv::kForWrite);
    OdTvEntitiesIteratorPtr pIt = pMarkupModel->getEntitiesIterator();
    if (!pIt->done())
    {
        while (!pIt->done())
        {
            OdTvEntityId entityId = pIt->getEntity();
            OdTvEntityPtr pEn = entityId.openObject(OdTv::kForWrite);
            if (pEn->getName().compare(OD_TV_MARKUP_TEMP_ENTITY) == 0) // if temp entity
                pMarkupModel->removeEntity(entityId);
            else if (pEn->getVisibility().getType() != OdTvVisibilityDef::kInvisible)
            {
                OdTvGeometryDataIteratorPtr pItF = pEn->getGeometryDataIterator();
                // folds
                while (!pItF->done())
                {
                    // objects
                    OdTvEntityPtr pFold = pItF->getGeometryData().openAsSubEntity();
                    OdTvGeometryDataIteratorPtr pItO = pFold->getGeometryDataIterator();

                    while (!pItO->done())
                    {
                        OdTvGeometryDataId geomId = pItO->getGeometryData();
                        OdTvByteUserData *oldData = dynamic_cast<OdTvByteUserData *>(geomId.openAsSubEntity()->getUserData(m_appTvId));
                        if (oldData)
                        {
                            bool flag = *(bool *)oldData->getData();
                            if (!flag)
                                pFold->removeGeometryData(geomId);
                        }
                        pItO->step();
                    }

                    pItF->step();
                }
                pEn->setVisibility(false);
            }

            pIt->step();
        }
    }
}

OdString TvAndCore::isSaveMarkupAvaliable() const
{
    //Check that we have an active markup entity (temporary or visible (loaded))
    if (m_TvMarkupsModelId.isNull())
    {
        return OD_T("Markup model is NULL");
    }

    OdTvEntitiesIteratorPtr pEnIt = m_TvMarkupsModelId.openObject()->getEntitiesIterator();
    if (pEnIt->done())
    {
        return OD_T("Markup model is empty");
    }

    OdTvEntityId activeEntityId;
    while (!pEnIt->done())
    {
        OdTvEntityId enId = pEnIt->getEntity();
        OdTvEntityPtr pEn = enId.openObject();
        if (pEn->getName().compare(OD_TV_MARKUP_TEMP_ENTITY) == 0 || pEn->getVisibility() != OdTvVisibilityDef::kInvisible)
        {
            activeEntityId = enId;
            break;
        }
        pEnIt->step();
    }

    if (activeEntityId.isNull())
    {
        return OD_T("No one markup for save");
    }

    return OD_T("");
}

OdString TvAndCore::saveMarkup(const OdString &markupName)
{
    OdTvEntityId activeEntityId;
    OdTvEntitiesIteratorPtr pEnIt = m_TvMarkupsModelId.openObject()->getEntitiesIterator();
    while (!pEnIt->done())
    {
        OdTvEntityId enId = pEnIt->getEntity();
        OdTvEntityPtr pEn = enId.openObject();

        if (!pEn->getName().compare(markupName))
        {
            return OD_T("Markup name already exist");
        }

        if (pEn->getName().compare(OD_TV_MARKUP_TEMP_ENTITY) == 0 || pEn->getVisibility() != OdTvVisibilityDef::kInvisible)
            activeEntityId = enId;

        pEnIt->step();
    }

    if (activeEntityId.isNull())
    {
        return OD_T("No one markup for save");
    }

    OdTvEntityPtr pEn = activeEntityId.openObject();
    pEn->setName(markupName);

    // Remove user data flag
    OdTvGeometryDataIteratorPtr pIt = pEn->getGeometryDataIterator();
    // folders
    while (!pIt->done())
    {
        OdTvEntityPtr pSubEn = pIt->getGeometryData().openAsSubEntity();
        OdTvGeometryDataIteratorPtr pIt2 = pSubEn->getGeometryDataIterator();
        // objects
        while (!pIt2->done())
        {
            OdTvEntityPtr pObj = pIt2->getGeometryData().openAsSubEntity(OdTv::kForWrite);
            OdTvByteUserData *oldData = dynamic_cast<OdTvByteUserData *>(pObj->getUserData(m_appTvId));
            if (oldData)
                pObj->removeUserData(m_appTvId);
            pIt2->step();
        }
        pIt->step();
    }

    // fill active and wcs view parameters
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if (!pView.isNull())
    {
        OdTvSaveViewParams *params = new OdTvSaveViewParams();
        params->m_pos = pView->position();
        params->m_target = pView->target();
        params->m_up = pView->upVector();
        params->m_proj = pView->isPerspective() ? OdTvGsView::kPerspective : OdTvGsView::kParallel;
        params->m_mode = pView->mode();
        params->m_width = pView->fieldWidth();
        params->m_height = pView->fieldHeight();

        // create and append the binary data to the entity
        OdTvByteUserData *data = new OdTvByteUserData(params, sizeof(class OdTvSaveViewParams), OdTvByteUserData::kOwn, true);
        pEn->appendUserData(data, m_appTvId);
    }

    return OD_T("");
}

OdString TvAndCore::isLoadMarkupAvaliable() const
{
    //Check that we have an active markup entity (temporary or visible (loaded))
    if (m_TvMarkupsModelId.isNull())
    {
        return OD_T("Markup model is NULL");
    }

    OdTvEntitiesIteratorPtr pEnIt = m_TvMarkupsModelId.openObject()->getEntitiesIterator();
    if (pEnIt->done())
    {
        return OD_T("Markup model is empty");
    }

    return OD_T("");
}

OdString TvAndCore::loadMarkup(const OdString &markupName)
{
    OdTvEntityId entForLoadId;
    for (OdTvEntitiesIteratorPtr pIt = m_TvMarkupsModelId.openObject()->getEntitiesIterator(); !pIt->done(); pIt->step())
    {
        OdTvEntityId enId = pIt->getEntity();
        OdTvEntityPtr pEn = enId.openObject(OdTv::kForWrite);
        if (pEn.isNull())
            continue;
        if (!pEn->getName().compare(markupName))
            entForLoadId = enId;
        else
            pEn->setVisibility(false);
    }

    if (!entForLoadId.isNull())
    {
        OdTvEntityPtr pEnt = entForLoadId.openObject(OdTv::kForWrite);

        OdTvUserData *usrData = pEnt->getUserData(m_appTvId);
        OdTvByteUserData *data = dynamic_cast<OdTvByteUserData *>(usrData);
        OdTvSaveViewParams *params = (OdTvSaveViewParams *)data->getData();
        if (!params)
        {
            return OD_T("Missing view params for load");
        }

        // fill active and wcs view params from binary user data
        OdTvExtendedView *pExtView = getActiveTvExtendedView();
        if (pExtView)
        {
            pExtView->setEnabledWCS(m_globalParams.getWcsEnabled());
            pExtView->setView(params->m_pos, params->m_target, params->m_up, params->m_width, params->m_height, params->m_proj);
            pExtView->setRenderMode(params->m_mode);
            m_pAnimation = pExtView->getAnimation();
            if (m_pAnimation)
            {
                m_pAnimation->start();
                performFixedFrameRate();
            }
            else if (!m_pActiveDragger.isNull())
                m_pActiveDragger->notifyAboutViewChange(kViewChangeZoom);
        }

        pEnt->setVisibility(true);

        return OD_T("");
    }

    return OD_T("Entity for load not found");
}

void TvAndCore::applyGlobalParams()
{
    OdTvExtendedView *pExtView = getActiveTvExtendedView();
    if(pExtView)
    {
        pExtView->setAnimationEnabled(m_globalParams.getAnimationEnabled());
        pExtView->setEnabledWCS(m_globalParams.getWcsEnabled());
    }
    if(!m_TvDeviceId.isNull())
        m_TvDeviceId.openObject(OdTv::kForWrite)->setShowFPS(m_globalParams.getFpsEnabled());
}

void TvAndCore::performFixedFrameRate()
{
    if (m_globalParams.getFixedFrameRate())
    {
        OdTvGsViewPtr pView = getActiveTvViewPtr();
        if (!pView.isNull() && !pView->isInInteractivity())
            pView->beginInteractivity(m_globalParams.getFpsValue());
    }
}

void TvAndCore::finishFixedFrameRate()
{
    if (m_globalParams.getFixedFrameRate())
    {
        OdTvGsViewPtr pView = getActiveTvViewPtr();
        if (!pView.isNull() && pView->isInInteractivity())
            pView->endInteractivity();
    }
}

// cutting plane methods

void TvAndCore::onAppearSectioningPanel(bool bAppear)
{
    if (bAppear)
    {
        bool bShow = m_sectioningOptions.getShown();
        if (bShow)
        {
            //checking just for safety
            TvAndCuttingPlaneDragger *cuttingPlaneDragger = dynamic_cast<TvAndCuttingPlaneDragger*>(m_pActiveDragger.get());
            if (!cuttingPlaneDragger)
            {
                OdTvDraggerPtr pNewDragger = new TvAndCuttingPlaneDragger(m_TvDeviceId, m_TvDraggersModelId, &m_globalParams, this);
                
                if (pNewDragger)
                    startDragger(pNewDragger, true);
                
                update();
            }
        }
    }
    else
    {
        TvAndCuttingPlaneDragger *cuttingPlaneDragger = dynamic_cast<TvAndCuttingPlaneDragger*>(m_pActiveDragger.get());
        if (cuttingPlaneDragger)
        {
            cuttingPlaneDragger->setCanBeFinished(true);
            finishDragger();
            
            update();
        }
    }
}

// Cutting plane methods
bool TvAndCore::setShowCuttingPlanes(bool bShow)
{
    OdTvGsViewPtr pActiveView = getActiveTvViewPtr();
    if (pActiveView.isNull())
    {
        return false;
    }
    
    m_sectioningOptions.setShown(bShow);
    
    if (bShow)
    {
        //here we should add the view to the device and to the active view
        {
            OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject(OdTv::kForWrite);
            pDevice->addView(m_cuttingPlanesViewId);
        }
        
        //add view as sibling to an active
        pActiveView->addSibling(m_cuttingPlanesViewId);
        
        //create sectiong planes geometry
        for (OdUInt32 i = 0; i < pActiveView->numCuttingPlanes(); i++)
        {
            drawCuttingPlane(i);
        }
        
        //create and start new dragger
        OdTvDraggerPtr pNewDragger = new TvAndCuttingPlaneDragger(m_TvDeviceId, m_TvDraggersModelId, &m_globalParams, this);
        if (pNewDragger)
            startDragger(pNewDragger, true);
        
        //invalidate device
        OdTvGsDevicePtr pDevice = pActiveView->device().openObject();
        if (!pDevice.isNull())
            pDevice->invalidate();
        
        //call redraw
        update();
        
        return true;
    }
    else
    {
        //finish the dragger
        TvAndCuttingPlaneDragger *cuttingPlaneDragger = dynamic_cast<TvAndCuttingPlaneDragger*>(m_pActiveDragger.get());
        if (cuttingPlaneDragger)
        {
            cuttingPlaneDragger->setCanBeFinished(true);
            finishDragger();
        }
        
        //remove geometry for the sectioning planes
        if (!m_cuttingPlanesModelId.isNull())
        {
            OdTvModelPtr pMoveModel = m_cuttingPlanesModelId.openObject(OdTv::kForWrite);
            if (!pMoveModel.isNull())
                pMoveModel->clearEntities();
        }
        
        if(!m_cuttingPlanesViewId.isNull())
        {
            //remove view as sibling from an active
            pActiveView->removeSibling(m_cuttingPlanesViewId);
            //remove view from device
            OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject(OdTv::kForWrite);
            pDevice->removeView(m_cuttingPlanesViewId);
        }
        
        //call redraw
        update();
        
        return false;
    }
}

void TvAndCore::onAddCuttingPlane(const OdTvVector& axis)
{
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if(pView.isNull())
        return;
    OdTvVector viewVector = pView->position() - pView->target();
    double dot = viewVector.dotProduct(axis);
    if (OdZero(dot))
        dot = 1.;
    
    OdTvVector byAxis = axis;
    byAxis *= -dot;
    byAxis.normalize();
    addCuttingPlane(byAxis);
}

bool TvAndCore::addCuttingPlane(const OdTvVector& axis, OdTvResult* rc)
{
    OdTvGsViewPtr pActiveView = getActiveTvViewPtr();
    if (pActiveView.isNull())
    {
        if (rc)
            *rc = tvThereIsNoActiveView;
        return false;
    }
    
    OdUInt32 nPlanes = pActiveView->numCuttingPlanes();
    if (nPlanes >= ODTVUI_CUTTINGPLANESMAXNUM)
        return false;
    
    if (axis.isZeroLength())
    {
        if (rc)
            *rc = tvCuttingPlaneZeroNormal;
        return false;
    }
    OdTvExtendedView* pExtendedView = getActiveTvExtendedView();
    if (!pExtendedView)
        return false;
    
    OdGeBoundBlock3d extents;
    if (!pExtendedView->getCachedExtents(extents))
    {
        if (pActiveView->viewExtents(extents))
        {
            if (!pActiveView->isPerspective())
                extents.setToBox(true);
            
            OdGeMatrix3d xWorldToEye = pActiveView->viewingMatrix();
            OdGeMatrix3d xEyeToWorld = xWorldToEye.invert();
            
            //transform extents to WCS
            extents.transformBy(xEyeToWorld);
        }
    }
    
    OdTvPoint center = extents.center();
    OdTvPlane plane(center, axis);
    
    //add cutting plane
    pActiveView->addCuttingPlane(plane);
    
    //update filling parameters first time
    if ( nPlanes == 0 )
        pActiveView->setEnableCuttingPlaneFill(m_sectioningOptions.getFilled(), m_sectioningOptions.getFillingColor());
    
    try
    {
        if (m_sectioningOptions.getShown())
        {
            if (nPlanes == 0) // if it is the first added object
            {
                //here we should add the view to the device and to the active view
                {
                    OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject(OdTv::kForWrite);
                    pDevice->addView(m_cuttingPlanesViewId);
                }
                
                //add view as sibling to an active
                pActiveView->addSibling(m_cuttingPlanesViewId);
            }
            
            //create geometry for the new sectioning plane
            drawCuttingPlane(pActiveView->numCuttingPlanes() - 1, true);
        }
        
        //invalidate device
        OdTvGsDevicePtr pDevice = pActiveView->device().openObject();
        if (!pDevice.isNull())
            pDevice->invalidate();
        
        //call redraw
        update();
    }
    catch (const OdError& e)
    {
        LOG_EXCEPTION(e);
    }
    catch(OdTvError& e)
    {
        LOG_EXCEPTION(e);
    }
    catch(...)
    {
        __android_log_print(ANDROID_LOG_ERROR, "Error", "Error during adding cutting plane");
    }
    return true;
}

void TvAndCore::setCuttingPlanesFilled(bool bFilled)
{
    m_sectioningOptions.setFilled(bFilled);
    
    OdTvGsViewPtr pActiveView = getActiveTvViewPtr();
    if (pActiveView.isNull())
        return;
    
    pActiveView->setEnableCuttingPlaneFill(bFilled, m_sectioningOptions.getFillingColor());
    
    OdTvGsDevicePtr pDevice = pActiveView->device().openObject();
    if (!pDevice.isNull())
        pDevice->invalidate();
    
    update();
}

void TvAndCore::setCuttingPlanesFillingColor(OdUInt32 color)
{
    m_sectioningOptions.setFillingColor(color);
    
    OdTvGsViewPtr pActiveView = getActiveTvViewPtr();
    if (pActiveView.isNull())
        return;
    
    pActiveView->setEnableCuttingPlaneFill(m_sectioningOptions.getFilled(), color);
    
    OdTvGsDevicePtr pDevice = pActiveView->device().openObject();
    if (!pDevice.isNull())
        pDevice->invalidate();
    
    update();
}

void TvAndCore::removeCuttingPlanes()
{
    OdTvGsViewPtr pActiveView = getActiveTvViewPtr();
    if (pActiveView.isNull())
        return;
    
    try
    {
        if (m_sectioningOptions.getShown())
        {
            //notify dragger
            TvAndCuttingPlaneDragger *cuttingPlaneDragger = dynamic_cast<TvAndCuttingPlaneDragger*>(m_pActiveDragger.get());
            if (cuttingPlaneDragger)
                cuttingPlaneDragger->onRemoveCuttingPlanes();
            
            
            //remove geometry for the sectioning planes
            if (!m_cuttingPlanesModelId.isNull())
            {
                OdTvModelPtr pMoveModel = m_cuttingPlanesModelId.openObject(OdTv::kForWrite);
                if (!pMoveModel.isNull())
                    pMoveModel->clearEntities();
            }
            
            //remove view as sibling from an active
            pActiveView->removeSibling(m_cuttingPlanesViewId);
            
            //remove view from device
            {
                OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject(OdTv::kForWrite);
                pDevice->removeView(m_cuttingPlanesViewId);
            }
        }
        
        //remove cutting planes
        pActiveView->removeCuttingPlanes();
        
        OdTvGsDevicePtr pDevice = pActiveView->device().openObject();
        if (!pDevice.isNull())
            pDevice->invalidate();
        
        //call redraw
        update();
    }
    catch (const OdError& e)
    {
        LOG_EXCEPTION(e);
    }
    catch(OdTvError& e)
    {
        LOG_EXCEPTION(e);
    }
    catch(...)
    {
        __android_log_print(ANDROID_LOG_ERROR, "Error", "Error during remove cutting plane");
    }
}

void TvAndCore::onRemoveCuttingPlane(const OdTvEntityId& entId)
{
    // Remove cutting plane geometries
    if (!m_cuttingPlanesModelId.isNull())
    {
        OdTvModelPtr pCuttingPlanesModel = m_cuttingPlanesModelId.openObject(OdTv::kForWrite);
        pCuttingPlanesModel->removeEntity(entId);
    }
    
    OdTvGsViewPtr pActiveView = getActiveTvViewPtr();
    if (pActiveView.isNull())
        return;
    
    if (pActiveView->numCuttingPlanes() == 0)
    {
        //model already should be empty
        
        //remove view as sibling from an active
        pActiveView->removeSibling(m_cuttingPlanesViewId);
        
        //remove view from device
        {
            OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject(OdTv::kForWrite);
            pDevice->removeView(m_cuttingPlanesViewId);
        }
    }
}

//draw visual representation of the cutting plane
void TvAndCore::drawCuttingPlane(OdUInt32 index, bool bNeedNotifyDragger)
{
    OdTvGsViewId pActiveTvViewId = getActiveTvViewId();
    OdTvGsViewPtr pActiveView = pActiveTvViewId.openObject();
    if (pActiveView.isNull())
        return;
    
    // Get cutting plane
    OdTvPlane cuttingPlane;
    OdTvResult res = pActiveView->getCuttingPlane(index, cuttingPlane);
    
    // Create entity for cutting plane
    OdTvModelPtr pCuttingPlanesModel = m_cuttingPlanesModelId.openObject(OdTv::kForWrite);
    
    // create cutting plane entity
    OdString strCuttingPlaneEntityName;
    strCuttingPlaneEntityName.format(OD_T("$_CUTTINGPLANE_ENTITY%d"), index);
    OdTvEntityId cuttingPlanesEntityId = pCuttingPlanesModel->appendEntity(strCuttingPlaneEntityName);
    
    //set a few parameters to the cutting plane
    OdTvEntityPtr pCuttingPlanesEntity = cuttingPlanesEntityId.openObject(OdTv::kForWrite);
    pCuttingPlanesEntity->setColor(OdTvColorDef(175, 175, 175));
    pCuttingPlanesEntity->setLineWeight(OD_TV_CUTTINGPLANE_EDGE_DEFAULT_LINEWEIGHT);
    pCuttingPlanesEntity->setTransparency(0.8);
    pCuttingPlanesEntity->addViewDependency(m_cuttingPlanesViewId);   // may be it is not strongly need now but it is very usefull for testing
    
    OdTvByteUserData *data = new OdTvByteUserData(&index, sizeof(OdUInt32), OdTvByteUserData::kCopyOwn, false);
    pCuttingPlanesEntity->appendUserData(data, m_appTvId);
    
    if (res != tvOk)
        return;
    
    // Calculate points for cutting plane shell
    OdTvPoint origin;
    OdTvVector uAxis, vAxis;
    cuttingPlane.get(origin, uAxis, vAxis);
    
    // Get max distance between extents
    double cuttingPlaneSize = getMainModelExtentsDistance() / 2.;
    
    OdTvPointArray points;
    points.resize(4);
    
    OdTvMatrix transformMatrix;
    // 0
    OdTvVector moveVector0 = -vAxis - uAxis;
    moveVector0 = moveVector0 * cuttingPlaneSize * OD_TV_CUTTINGPLANE_SIZE_COEFF;
    transformMatrix.setToIdentity();
    transformMatrix.setToTranslation(moveVector0);
    OdTvPoint point0 = origin;
    point0.transformBy(transformMatrix);
    points[0] = point0;
    
    // 1
    OdTvVector moveVector1 = vAxis - uAxis;
    moveVector1 = moveVector1 * cuttingPlaneSize * OD_TV_CUTTINGPLANE_SIZE_COEFF;
    transformMatrix.setToIdentity();
    transformMatrix.setToTranslation(moveVector1);
    OdTvPoint point1 = origin;
    point1.transformBy(transformMatrix);
    points[1] = point1;
    
    // 2
    OdTvVector moveVector2 = vAxis + uAxis;
    moveVector2 = moveVector2 * cuttingPlaneSize * OD_TV_CUTTINGPLANE_SIZE_COEFF;
    transformMatrix.setToIdentity();
    transformMatrix.setToTranslation(moveVector2);
    OdTvPoint point2 = origin;
    point2.transformBy(transformMatrix);
    points[2] = point2;
    
    // 3
    OdTvVector moveVector3 = uAxis - vAxis;
    moveVector3 = moveVector3 * cuttingPlaneSize * OD_TV_CUTTINGPLANE_SIZE_COEFF;
    transformMatrix.setToIdentity();
    transformMatrix.setToTranslation(moveVector3);
    OdTvPoint point3 = origin;
    point3.transformBy(transformMatrix);
    points[3] = point3;
    
    OdInt32Array faces;
    faces.append(4);
    faces.append(0);
    faces.append(1);
    faces.append(2);
    faces.append(3);
    
    // append shell to cutting plane entity
    OdTvGeometryDataId cuttingPlaneShellId = pCuttingPlanesEntity->appendShell(points, faces);
    cuttingPlaneShellId.openAsShell()->setDisableLighting(true);
    
    // append boundary polyline to cutting plane entity
    points.append(point0);
    pCuttingPlanesEntity->appendPolyline(points);
    
    //notify dragger that cutting plane was added
    TvAndCuttingPlaneDragger *cuttingPlaneDragger = dynamic_cast<TvAndCuttingPlaneDragger*>(m_pActiveDragger.get());
    if (cuttingPlaneDragger)
        cuttingPlaneDragger->onCuttingPlaneAdded(cuttingPlanesEntityId);
}

double TvAndCore::getMainModelExtentsDistance() const
{
    OdTvModelPtr pModel = m_TvMainModelId.openObject();
    
    // Get extents
    OdTvExtents3d extents;
    OdTvResult res = pModel->getExtents(extents);
    if (res != tvOk)
        return 0.;
    // Get max distance between extents
    OdTvPoint minPoint = extents.minPoint();
    OdTvPoint maxPoint = extents.maxPoint();
    
    double maxDistance = 0.;
    if ((maxPoint.x - minPoint.x < maxPoint.y - minPoint.y) && (maxPoint.x - minPoint.x < maxPoint.z - minPoint.z))
        maxDistance = maxPoint.x - minPoint.x;
    else if ((maxPoint.y - minPoint.y < maxPoint.x - minPoint.x) && (maxPoint.y - minPoint.y < maxPoint.z - minPoint.z))
        maxDistance = maxPoint.y - minPoint.y;
    else if ((maxPoint.z - minPoint.z < maxPoint.x - minPoint.x) && (maxPoint.z - minPoint.z < maxPoint.y - minPoint.y))
        maxDistance = maxPoint.z - minPoint.z;
    else
        maxDistance = maxPoint.x - minPoint.x;
    
    return maxDistance;
}

OdString TvAndCore::runCollide()
{
    //check visual style of render mode
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if (!pView.isNull())
    {
        bool bWire = false;
        if(pView->mode() == OdTvGsView::k2DOptimized || pView->mode() == OdTvGsView::kWireframe)
            bWire = true;
        
        bool bRes;
        if (m_TvDeviceId.openObject()->getOption(OdTvGsDevice::kUseVisualStyles, bRes) == tvOk)
        {
            if (bRes)
            {
                OdTvVisualStyleId visId = pView->getVisualStyle();
                OdTvVisualStylePtr pStyle = visId.openObject();
                if (!pStyle.isNull())
                {
                    bool bUseDrawOrder;
                    pStyle->getOption(OdTvVisualStyleOptions::kUseDrawOrder, bUseDrawOrder);
                    if (bUseDrawOrder)
                        bWire = true;
                    else
                    {
                        OdInt32 nVal;
                        pStyle->getOption(OdTvVisualStyleOptions::kFaceLightingModel, nVal);
                        if (nVal == (OdInt32)OdTvVisualStyleOptions::kInvisible)
                            bWire = true;
                    }
                }
            }
        }
        
        if(bWire)
            return OD_T("Collide tool can not work in wireframe mode");
    }
    else
        return OD_T("View is NULL");
    
    //create dragger
    TvAndCollideDragger* pNewDragger = new TvAndCollideDragger(m_TvDeviceId, m_TvMainModelId, m_TvDraggersModelId, &m_globalParams, this);
    //start dragger
    startDragger(pNewDragger, true);
    getActiveTvExtendedView()->setViewType(OdTvExtendedView::kCustom);

    return OD_T("");
}

void TvAndCore::save(const OdString& fileName, bool bPartialIndexing)
{
    if(m_TvDatabaseId.isNull()) 
    {
        __android_log_print(ANDROID_LOG_ERROR, "Error", "Database for save not exist");
        return;
    }
    
    if(fileName.isEmpty()) 
    {
        __android_log_print(ANDROID_LOG_ERROR, "Error", "Filename is empty");
        return;
    }

    m_bIsBlocked = true;
    
    OdTvDatabasePtr pDb = m_TvDatabaseId.openObject();
    if(bPartialIndexing)
        pDb->addPartialViewIndexes();

    try
    {
        OdTvResult rc = OdTvDeprecated::writeFile( m_TvDatabaseId, fileName);
        if(rc != tvOk) 
        {
            __android_log_print(ANDROID_LOG_ERROR, "Error", "Error during saving");
        }
    }
    catch(OdTvError& e)
    {
        LOG_EXCEPTION(e);
    }
    catch(const OdError& e)
    {
        LOG_EXCEPTION(e);
    }
    catch(...)
    {
        __android_log_print(ANDROID_LOG_ERROR, "Error", "Save of file was failed");
    }

    m_bIsBlocked = false;
}

bool TvAndCore::isViewAllowGroundShadow()
{
    OdTvGsViewId viewId = getActiveTvViewId();
    if(viewId.isNull())
        return false;

    OdTvGsViewPtr pView = getActiveTvViewPtr();
    OdTvGsView::RenderMode rm = pView->mode();

    return rm != OdTvGsView::k2DOptimized && rm != OdTvGsView::kWireframe && rm != OdTvGsView::kHiddenLine;
}

bool TvAndCore::addGroundShadow()
{
    if (m_TvDeviceId.isNull() || getActiveTvViewId().isNull())
        return false;

    OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject(OdTv::kForWrite);
    if (pDevice.isNull())
        return false;

    //check that device is OpenGLES2
    if (pDevice->getGsDeviceName() != OdTvGsDevice::kOpenGLES2)
    {
        __android_log_print(ANDROID_LOG_ERROR, "Ground Shadow: wrong device", "Ground shadow feture is present only in OpenGL ES2 device");
        return false;
    }

    try
    {
        OdTvGsViewId viewId = getActiveTvViewId();
        OdTvVisualStyleId visStId = viewId.openObject()->getVisualStyle();
        if (!visStId.isNull())
        {
            OdTvVisualStylePtr pStyle = visStId.openObject(OdTv::kForWrite);
            if (!pStyle.isNull())
            {
                OdInt32 nVal;
                pStyle->getOption(OdTvVisualStyleOptions::kFaceLightingModel, nVal);
                if (nVal == (OdInt32)OdTvVisualStyleOptions::kPhong)
                {
                    if (!m_groundShadow.isAdded())
                        pStyle->setOption(OdTvVisualStyleOptions::kDisplayShadow, true);
                    else
                        pStyle->setOption(OdTvVisualStyleOptions::kDisplayShadow, false);
                }
            }
        }

        if (!m_groundShadow.isAdded() && !m_groundShadow.isViewAllowGroundShadow(viewId))
        {
            __android_log_print(ANDROID_LOG_ERROR, "Ground Shadow:", "Ground shadow can not be added to the wireframe of hidden line views");
            return m_groundShadow.isAdded();
        }

        //add or remove the ground shadow
        if (m_groundShadow.isAdded())
            m_groundShadow.remove();
        else
            m_groundShadow.add(m_TvMainModelId, viewId, OdTvGroundShadow::kZMin, 0.25);

        pDevice->invalidate();
    }
    catch (OdTvError &e)
    {
        LOG_EXCEPTION(e);
    }
    catch (const OdError &e)
    {
        LOG_EXCEPTION(e);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_ERROR, "Ground Shadow:", "Error during adding shadow.");
    }

    return m_groundShadow.isAdded();
}
