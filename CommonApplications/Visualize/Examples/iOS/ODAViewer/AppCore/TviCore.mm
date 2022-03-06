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

#include "TviCore.hpp"
#import <Foundation/Foundation.h>
#import "TviDraggers.hpp"
#import "TviTools.h"

#import "../MetalViewController.h"
#import "../RenderViewController.h"

#include "TviProgressMeter.hpp"

#include "TvError.h"
#include "TvExport.h"

#define OD_TV_APP_NAME OD_T("IOS ODA Viewer")

inline double TvRound(double a)
{
    double aFloor = ::floor(a);
    if (a - aFloor >= 0.5)
        return aFloor + 1.0;
    return aFloor;
};

TviCore::TviCore() : m_bIsBlocked(true), m_pGlobalParams(NULL), m_pAnimation(NULL), m_bIsInitialized(false), m_bRegenAbort(false), m_bLowMemory(false)
{
    m_sectioningOptions.setFillingColor(ODRGBA(255, 255, 0, 255));
    m_sectioningOptions.setFilled(true);
}

TviCore::~TviCore()
{
    release();
}

void TviCore::release()
{
    if(!m_TvDatabaseId.isNull())
    {
        try
        {
            // before remove databse, erase all views, otherwise the application may crash when removing a view
            if(!m_TvDeviceId.isNull()) {
                OdTvGsDevicePtr pDev = m_TvDeviceId.openObject(OdTv::kForWrite);
                pDev->setShowFPS(false);
                pDev->eraseAllViews();
            }
            odTvGetFactory().removeDatabase(m_TvDatabaseId);
        }
        catch(OdTvError& e)
        {
            NSLog(@"%@", [NSString stringWithFormat:@"Error during close:\n %@", OdString2NSString(e.description())]);
        }
        catch(const OdError& e)
        {
            NSLog(@"%@", [NSString stringWithFormat:@"Error during close:\n %@", OdString2NSString(e.description())]);
        }
    }
}

void TviCore::openFile(const OdString &filePath, OdTvBaseImportParams* pParams, bool bImport, NSObject* context, const OdTvDCRect& rect)
{    
    m_databaseInfo.setFilePath(filePath);
    if (!bImport)
        m_databaseInfo.setType(TviDatabaseInfo::kFromFile);
    else
        m_databaseInfo.setType(TviDatabaseInfo::kImport);
    
    if(pParams)
    {
        pParams->setFilePath(filePath);
        pParams->setProfiling(&m_databaseInfo);
    }
    
    
    OdTvResult rc = tvOk;
    
    m_bLowMemory = false;
    bool bPartial = false;
    if( m_fileExt == Vsf && m_pGlobalParams->getPartialOpen() )
    {
        if( m_pGlobalParams->getUseLimitManager() ) {
            m_limitator.setMemoryLimit((OdUInt64)m_pGlobalParams->getMemoryLimit() * 1024 * 1024);
            odTvGetFactory().setLimitManager( &m_limitator );
        }
        else
            odTvGetFactory().setLimitManager(NULL);
        bPartial = true;
    }
    else if(m_fileExt == Drw)
    {
        OdTvDwgImportParams* pDwg = dynamic_cast<OdTvDwgImportParams*>(pParams);
        if(pDwg && pDwg->getOpenSourcePartial()) {
            m_bLowMemory = true;
            bPartial = true;
            m_limitator.setMemoryLimit((OdUInt64)m_pGlobalParams->getMemoryLimit() * 1024 * 1024);
            odTvGetFactory().setLimitManager( &m_limitator );
        }
    }
    else
        odTvGetFactory().setLimitManager(NULL);
    
    if(bImport && pParams)
    {
        try
        {
            if(!m_bLowMemory)
                m_TvDatabaseId = odTvGetFactory().importFile(pParams, &rc);
            else
            {
                //create and set progress meter
                TviProgressMeter* pProgressMeter = new TviProgressMeter(m_pParentController.progressMeter);
                pParams->setProgressMeter(pProgressMeter);
                
                rc = odTvGetFactory().lowMemoryImportFile(pParams, filePath + L".vsf");
                
                pParams->setProgressMeter(NULL);
                delete pProgressMeter;
                
                if ( rc == tvOk )
                    m_TvDatabaseId = odTvGetFactory().readFile(filePath + L".vsf", false, true, &rc);
            }
            
            if(rc != tvOk)
                showMessage(@"Error", @"Import of file was failed");
        }
        catch(const OdError& e)
        {
            showMessage(@"Error", [NSString stringWithFormat:@"Import of file was failed: %@", OdString2NSString(e.description())]);
        }
        catch(OdTvError& e)
        {
            showMessage(@"Error", [NSString stringWithFormat:@"Import of file was failed: %@", OdString2NSString(e.description())]);
        }
    }
    else
    {
        try
        {
            NSDate *curDate = [NSDate date];
            m_TvDatabaseId = odTvGetFactory().readFile(filePath, !m_pGlobalParams->getPartialOpen(), m_pGlobalParams->getPartialOpen(), &rc);
            if(rc != tvOk)
                showMessage(@"Error", @"Read of file was failed");

            if(pParams->getProfiling()) {
                double readTime = [curDate timeIntervalSinceNow] * (-1000);
                pParams->getProfiling()->setImportTime(readTime);
            }
        }
        catch(const OdError& e)
        {
            showMessage(@"Error", [NSString stringWithFormat:@"Read of file was failed: %@", OdString2NSString(e.description())]);
        }
        catch(OdTvError& e)
        {
            showMessage(@"Error", [NSString stringWithFormat:@"Read of file was failed: %@", OdString2NSString(e.description())]);
        }
    }
    
    if(m_TvDatabaseId.isNull())
        return;
    
    OdTvDatabasePtr pDb = m_TvDatabaseId.openObject(OdTv::kForWrite);
    if(pDb.isNull())
        return;
    
    m_TvMainModelId = pDb->getModelsIterator()->getModel();
    if(!m_TvMainModelId.isNull())
        m_modelStat = m_TvMainModelId.openObject()->getStatistic();
    
    //create model for sectioning geometry
    static int cuttingPlaneModelNumber = 1;
    OdString strCuttingPlaneModelName;
    strCuttingPlaneModelName.format(L"$ODA_TVVIEWER_SECTIONING_MODEL_%d", cuttingPlaneModelNumber++);
    m_cuttingPlanesModelId = pDb->createModel(strCuttingPlaneModelName, OdTvModel::kMain, false);
    
    OdTvDevicesIteratorPtr pDevIt = pDb->getDevicesIterator();
    m_TvDeviceId = pDevIt->getDevice();
    if(bPartial && !m_TvDeviceId.isNull())
        m_TvDeviceId.openObject(OdTv::kForWrite)->setBackgroundPartialView(true);
    setupDevice(context, rect);
    
    // register app name (for user data)
    bool alreadyExist;
    m_appTvId = pDb->registerAppName(OD_TV_APP_NAME, alreadyExist);
    // find draggers model
    m_TvDraggersModelId = pDb->findModel(OD_T("$Draggers"));
    if (m_TvDraggersModelId.isNull())
        m_TvDraggersModelId = pDb->createModel(OD_T("$Draggers"), OdTvModel::kDirect, false);
    
    // apply global params
    if(m_pGlobalParams)
    {
        OdTvExtendedView *pExtView = getActiveTvExtendedView();
        if(pExtView)
        {
            pExtView->setAnimationEnabled(m_pGlobalParams->getAnimationEnabled());
            pExtView->setEnabledWCS(m_pGlobalParams->getWcsEnabled());
        }
        if(m_pGlobalParams->getFpsEnabled())
            m_TvDeviceId.openObject(OdTv::kForWrite)->setShowFPS(true);
    }
    
    // create default dragger (pan dragger)
    TviPanDragger *panDragger = new TviPanDragger(m_TvDeviceId, m_TvDraggersModelId, m_pGlobalParams);
    m_pActiveDragger = panDragger;
    eDraggerResult res = m_pActiveDragger->start(NULL, getActiveTvExtendedView());
    actionsAfterDragger(res);
    
    m_bIsBlocked = false;
}

void TviCore::update()
{
    if(m_bIsBlocked || m_TvDeviceId.isNull())
        return;
        
    try
    {
        OdTvGsDevicePtr pDev = m_TvDeviceId.openObject();
        if(pDev.isNull())
            return;
        
        bool viewParamsIsDiff = false;
        if(m_pGlobalParams->getPartialOpen() || m_bLowMemory)
        {
            TviDiffViewParams params(getActiveTvViewId());
            viewParamsIsDiff = m_viewParams != params;
            if(viewParamsIsDiff)
                m_viewParams = params;
        }
        
        NSDate* curDate = nil;
        if(!m_bIsInitialized) {
            curDate = [NSDate date];
            viewParamsIsDiff = true;
            m_viewParams = TviDiffViewParams();
        }
    
        
        TviRegenAbortImpl impl( this );
        pDev->setRegenAbort( &impl );
        pDev->invalidate();
        pDev->update(NULL, !viewParamsIsDiff);
        pDev->setRegenAbort(NULL);
        
        if(!m_bIsInitialized && curDate) {
            m_bIsInitialized = true;
            double firstUpdateTime = [curDate timeIntervalSinceNow] * (-1000);
            m_databaseInfo.setFirstUpdateTime(firstUpdateTime);
            curDate = nil;

            [m_pParentController stopLoadingIndicator: m_databaseInfo.getTotalTime() / 1000.];
        }
        
        if( pDev->getBackgroundPartialViewingInProgress() && m_pParentController)
        {
            [m_pParentController startTimer];
        }
    }
    catch(const OdError& e)
    {
        showMessage(@"Error", [NSString stringWithFormat:@"Paint was failed: %@", OdString2NSString(e.description())]);
    }
    catch(OdTvError& e)
    {
        showMessage(@"Error", [NSString stringWithFormat:@"Paint was failed: %@", OdString2NSString(e.description())]);
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

void TviCore::autoUpdate()
{
    OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject();
    if (pDevice.isNull())
        return;
    pDevice->update( NULL, true );
    if( pDevice->getBackgroundPartialViewingInProgress() && m_pParentController)
    {
        [m_pParentController startTimer];
    }
}

void TviCore::resizeDevice(long xMin, long xMax, long yMin, long yMax)
{
    if(m_TvDeviceId.isNull())
        return;
    OdTvGsDevicePtr pDev = m_TvDeviceId.openObject();
    pDev->onSize(OdTvDCRect(xMin, xMax, yMin, yMax));
}

void TviCore::applyGlobalParams()
{
    // apply global params
    if(m_pGlobalParams)
    {
        OdTvExtendedView *pExtView = getActiveTvExtendedView();
        if(pExtView)
        {
            pExtView->setAnimationEnabled(m_pGlobalParams->getAnimationEnabled());
            pExtView->setEnabledWCS(m_pGlobalParams->getWcsEnabled());
        }
        if(!m_TvDeviceId.isNull()) {
            OdTvGsDevicePtr pDev = m_TvDeviceId.openObject(OdTv::kForWrite);
            pDev->setShowFPS(m_pGlobalParams->getFpsEnabled());
            bool bUseFxaa = false;
            pDev->getOption(OdTvGsDevice::kFXAAEnable, bUseFxaa);
            if(bUseFxaa != m_pGlobalParams->getUseFXAA())
                pDev->setOption(OdTvGsDevice::kFXAAEnable, m_pGlobalParams->getUseFXAA());
            pDev->invalidate();
        }
    }
}

void TviCore::setupDevice(NSObject* context, const OdTvDCRect& rect)
{
    try
    {
        OdTvGsDevicePtr pDev = m_TvDeviceId.openObject(OdTv::kForWrite);
        if(m_pGlobalParams->getDevice() == TviGlobalParameters::Metal)
        {
            pDev->setupGs( (__bridge void*)context, rect, OdTvGsDevice::kMetal);
        }
        else if(m_pGlobalParams->getDevice() == TviGlobalParameters::OpenGLES2)
        {
            pDev->setupGsWithContext( (__bridge void*)context, rect, OdTvGsDevice::kOpenGLES2);
            pDev->setOption(OdTvGsDevice::kCreateGLContext, false);
            
        }
        pDev->setActive(true);
        pDev->setOption(OdTvGsDevice::kUseOverlayBuffers, false);
        if(m_pGlobalParams) {
            pDev->setOption(OdTvGsDevice::kUseSceneGraph, m_pGlobalParams->getUseSceneGraph());
            pDev->setOption(OdTvGsDevice::kFXAAEnable, m_pGlobalParams->getUseFXAA());
            pDev->setOption(OdTvGsDevice::kFXAAQuality, (OdUInt32)4);
        }
        
        //create sectioning view
        static int cuttingPlaneViewNumber = 1;
        
        OdString strCuttingPlaneViewName;
        strCuttingPlaneViewName.format(L"$ODA_TVVIEWER_SECTIONING_VIEW_%d", cuttingPlaneViewNumber++);
        m_cuttingPlanesViewId = pDev->createView(strCuttingPlaneViewName, false);
        OdTvGsViewPtr pVsectioningView = m_cuttingPlanesViewId.openObject(OdTv::kForWrite);
        pVsectioningView->addModel(m_cuttingPlanesModelId);
        pVsectioningView->setMode(OdTvGsView::kGouraudShaded);
    }
    catch(OdTvError& e)
    {
        NSLog(@"%@", [NSString stringWithFormat:@"Error during setup device:\n %@", OdString2NSString(e.description())]);
    }
    catch(const OdError& e)
    {
        NSLog(@"%@", [NSString stringWithFormat:@"Error during setup device:\n %@", OdString2NSString(e.description())]);
    }
}

// get active view id ot prt
OdTvGsViewId TviCore::getActiveTvViewId() const
{
    if (m_TvDeviceId.isNull())
        return OdTvGsViewId();
    OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject();
    OdTvGsViewId viewId = pDevice->getActiveView();
    if (viewId.isNull())
        viewId = pDevice->viewAt(0);
    return viewId;
}

OdTvGsViewPtr TviCore::getActiveTvViewPtr()
{
    if (getActiveTvViewId().isNull())
        return OdTvGsViewPtr();
    return getActiveTvViewId().openObject(OdTv::kForWrite);
}

// get extended view
OdTvExtendedView *TviCore::getActiveTvExtendedView()
{
    OdTvGsViewId viewId = getActiveTvViewId();
    if (viewId.isNull())
        return NULL;
    
    std::map < OdTvGsViewId, OdTvExtendedView* >::iterator iter = m_tvExtendedViewsMap.find(viewId);
    if (iter != m_tvExtendedViewsMap.end())
        return iter->second;
    else
    {
        OdTvExtendedView* pBasicView = new OdTvExtendedView(viewId);
        pBasicView->setAnimationEnabled(true);
        pBasicView->setZoomScale(2);
        pBasicView->setAnimationDuration(0.9);
        
        OdTvGsViewPtr pTvView = viewId.openObject();
        if (!pTvView.isNull())
        {
            OdGeBoundBlock3d lastExt;
            if ( pTvView->getLastViewExtents(lastExt) )
                pBasicView->setViewExtentsForCaching(&lastExt);
        }
        
        m_tvExtendedViewsMap.insert(std::pair<OdTvGsViewId, OdTvExtendedView*>(viewId, pBasicView));
        
        return pBasicView;
    }
    
    return NULL;
}

void TviCore::actionsAfterDragger(eDraggerResult res)
{
    if (res & kNeedUpdateView)
        update();
    
    if (res & kNeedFinishDragger)
        finishDragger();
}

void TviCore::finishDragger()
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
}

void TviCore::startDragger(OdTvDraggerPtr pNewDragger, bool bUseCurrentAsPrevious)
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

bool TviCore::exportToPdf(bool b3D) const
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

void TviCore::zoom(double delta, double x, double y)
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
    
    update();
}

void TviCore::screenDolly(int x, int y) {
    // get the active view and perform zooming
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if (pView.isNull())
        return;
    
    OdGeVector3d vec(x, y, 0.0);
    vec.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
    pView->dolly(vec);
}

void TviCore::runNavigationAction(TviCore::NavigationAction navAct)
{
    OdTvDraggerPtr pNewDragger;
    OdTvGsViewPtr pView = getActiveTvViewId().openObject();
    
    switch (navAct) {
        case Pan:
        {
            pNewDragger = new TviPanDragger(m_TvDeviceId, m_TvDraggersModelId, m_pGlobalParams);
            break;
        }
        case Orbit:
        {
            pNewDragger = new TviOrbitDragger(m_TvDeviceId, m_TvDraggersModelId, m_pGlobalParams);
            break;
        }
        case ZoomWindow:
        {
            pNewDragger = new TviZoomWindowDragger(m_TvDeviceId, m_TvDraggersModelId, this, m_pGlobalParams);
            break;
        }
        case ZoomExtents:
        {
            OdTvExtendedView* pBasicView = getActiveTvExtendedView();
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
            
            update();
            break;
        }
    }
    
    //start dragger
    if(!pNewDragger.isNull())
        startDragger(pNewDragger);
    
    getActiveTvExtendedView()->setViewType(OdTvExtendedView::kCustom);
}

void TviCore::set3DView(OdTvExtendedView::e3DViewType type)
{
    OdTvExtendedView* pBasicView = getActiveTvExtendedView();
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
    
    update();
    disableMarkups();
}

void TviCore::runRegenAction(TviCore::RegenAction regenAct)
{
    OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject(OdTv::kForWrite);
    if (pDevice.isNull())
        return;
    switch (regenAct)
    {
        case All:
        {
            pDevice->regen(OdTvGsDevice::kRegenAll);
            break;
        }
        case Visible:
        {
            pDevice->regen(OdTvGsDevice::kRegenVisible);
            break;
        }
        case View:
        {
            OdTvGsViewPtr pView = getActiveTvViewId().openObject();
            if (!pView.isNull())
                pView->regen();
            break;
        }
    }
    
    update();
}

void TviCore::runRenderMode(OdTvGsView::RenderMode newMode)
{
    OdTvExtendedView* pBasicView = getActiveTvExtendedView();
    if (pBasicView)
    {
        if (pBasicView->setRenderMode(newMode))
            update();
    }
}

void TviCore::runMarkupAction(TviCore::MarkupAction act)
{
    if (m_TvMarkupsModelId.isNull()) {
        OdTvDatabasePtr pDatabase = m_TvDatabaseId.openObject(OdTv::kForWrite);
        m_TvMarkupsModelId = pDatabase->findModel(OD_TV_MARKUP_MODEL);
        if(m_TvMarkupsModelId.isNull())
            m_TvMarkupsModelId = pDatabase->createModel(OD_TV_MARKUP_MODEL, OdTvModel::kDirect, true);
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
            //Check that we have an active markup entity (temporary or visible (loaded))
            if (m_TvMarkupsModelId.isNull())
            {
                showMessage(@"Error", @"Markup model is NULL");
                return;
            }
            
            OdTvEntitiesIteratorPtr pEnIt = m_TvMarkupsModelId.openObject()->getEntitiesIterator();
            if (pEnIt->done())
            {
                showMessage(@"Error", @"Markup model is empty");
                return;
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
                showMessage(@"Save markup", @"No one markup for save");
                return;
            }
            [m_pParentController showSaveMarkupDialog];
            break;
        }
        case Load:
        {
            //Check that we have an active markup entity (temporary or visible (loaded))
            if (m_TvMarkupsModelId.isNull())
            {
                showMessage(@"Error", @"Markup model is NULL");
                return;
            }
            
            OdTvEntitiesIteratorPtr pEnIt = m_TvMarkupsModelId.openObject()->getEntitiesIterator();
            if (pEnIt->done())
            {
                showMessage(@"Error", @"Markup model is empty");
                return;
            }
            
            [m_pParentController showLoadMarkupDialog];
            break;
        }
    }
    
    //start dragger
    if (!pNewDragger.isNull())
        startDragger(pNewDragger);
}

void TviCore::setProjection(TviCore::ProjectionType projType)
{
    OdTvGsViewPtr pView = getActiveTvViewId().isNull() ? OdTvGsViewPtr() : getActiveTvViewId().openObject(OdTv::kForWrite);
    if(pView.isNull())
        return;
    pView->setView( pView->position(), pView->target(), pView->upVector(), pView->fieldWidth(), pView->fieldHeight()
                   , (OdTvGsView::Projection)projType );
}

void TviCore::disableMarkups() {
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
                        OdTvByteUserData *oldData = dynamic_cast<OdTvByteUserData*>(geomId.openAsSubEntity()->getUserData(m_appTvId));
                        if (oldData)
                        {
                            bool flag = *(bool*)oldData->getData();
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

void TviCore::showMessage(NSString *title, NSString *msg)
{
    [m_pParentController showMessage:title message:msg];
}

bool TviCore::saveMarkup(NSString *markupName)
{
    OdString newMarkupName = NSString2OdString(markupName);
    OdTvEntityId activeEntityId;
    OdTvEntitiesIteratorPtr pEnIt = m_TvMarkupsModelId.openObject()->getEntitiesIterator();
    while (!pEnIt->done())
    {
        OdTvEntityId enId = pEnIt->getEntity();
        OdTvEntityPtr pEn = enId.openObject();
        
        if(!pEn->getName().compare(newMarkupName)) {
            showMessage(@"Error", @"Markup name already exist");
            return false;
        }
        
        if (pEn->getName().compare(OD_TV_MARKUP_TEMP_ENTITY) == 0 || pEn->getVisibility() != OdTvVisibilityDef::kInvisible)
            activeEntityId = enId;
        
        pEnIt->step();
    }
    
    if (activeEntityId.isNull())
    {
        showMessage(@"Error", @"No one markup for save");
        return false;
    }
    
    OdTvEntityPtr pEn = activeEntityId.openObject();
    pEn->setName(newMarkupName);
    
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
            OdTvByteUserData *oldData = dynamic_cast<OdTvByteUserData*>(pObj->getUserData(m_appTvId));
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
    
    return true;
}

bool TviCore::loadMarkup(NSString *markupName)
{
    OdTvEntityId entForLoadId;
    OdString loadName = NSString2OdString(markupName);
    for(OdTvEntitiesIteratorPtr pIt = m_TvMarkupsModelId.openObject()->getEntitiesIterator(); !pIt->done(); pIt->step())
    {
        OdTvEntityId enId = pIt->getEntity();
        OdTvEntityPtr pEn = enId.openObject(OdTv::kForWrite);
        if(pEn.isNull())
            continue;
        if(!pEn->getName().compare(loadName))
            entForLoadId = enId;
        else
            pEn->setVisibility(false);
    }
    
    if (!entForLoadId.isNull())
    {
        OdTvEntityPtr pEnt = entForLoadId.openObject(OdTv::kForWrite);
        
        OdTvUserData *usrData = pEnt->getUserData(m_appTvId);
        OdTvByteUserData *data = dynamic_cast<OdTvByteUserData*>(usrData);
        OdTvSaveViewParams *params = (OdTvSaveViewParams*)data->getData();
        if(!params)
        {
            return false;
        }
        
        // fill active and wcs view params from binary user data
        OdTvExtendedView* pExtView = getActiveTvExtendedView();
        if (pExtView)
        {
            pExtView->setEnabledWCS(m_pGlobalParams->getWcsEnabled());
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
        
        return true;
    }
    
    showMessage(@"Error", @"Entity for load not found");
    return false;
}

bool TviCore::removeMarkup(NSString *markupName)
{
    OdString enName = NSString2OdString(markupName);
    OdTvModelPtr pModel = m_TvMarkupsModelId.openObject(OdTv::kForWrite);
    OdTvEntityId enId;
    // find entity
    for( OdTvEntitiesIteratorPtr pIt = pModel->getEntitiesIterator(); !pIt->done(); pIt->step() )
    {
        if(!pIt->getEntity().openObject()->getName().compare(enName))
        {
            enId = pIt->getEntity();
            break;
        }
    }
    // remove entity
    if(!enId.isNull())
    {
        pModel->removeEntity(enId);
        return true;
    }
    return false;
}

bool TviCore::saveFile(NSString *filePath, bool bPartialIndexing)
{
    if(m_TvDatabaseId.isNull()) {
        showMessage(@"Error", @"Database for save file not exist");
        return false;
    }
    
    if(filePath.length == 0) {
        showMessage(@"Error", @"Filename is empty");
        return false;
    }
    
    OdTvDatabasePtr pDb = m_TvDatabaseId.openObject(OdTv::kForWrite);
    if(bPartialIndexing)
        pDb->addPartialViewIndexes();
    try
    {
        OdTvResult rc = pDb->writeFile(NSString2OdString(filePath));
        if(rc != tvOk) {
            showMessage(@"Error", @"Error during saving");
            return false;
        }
        
        showMessage(@"Save file", @"File saved successfully");
        return true;
    }
    catch(OdTvError& e)
    {
        showMessage(@"Error", [NSString stringWithFormat:@"Saving was failed:\n %@", OdString2NSString(e.description())]);
        return false;
    }
    catch(const OdError& e)
    {
        showMessage(@"Error", [NSString stringWithFormat:@"Saving was failed:\n %@", OdString2NSString(e.description())]);
        return false;
    }
    
    return false;
}

OdTvGeometryStatistic* TviCore::getModelStatistic()
{
    if(m_TvMainModelId.isNull()) {
        showMessage(@"Error", @"Model doesn't exist");
        return NULL;
    }
    return &m_modelStat;
}

void TviCore::performFixedFrameRate()
{
    if (m_pGlobalParams->getFixedFrameRate())
    {
        OdTvGsViewPtr pView = getActiveTvViewPtr();
        if (!pView.isNull() && !pView->isInInteractivity())
            pView->beginInteractivity(m_pGlobalParams->getFpsValue());
    }
}

void TviCore::finishFixedFrameRate()
{
    if (m_pGlobalParams->getFixedFrameRate())
    {
        OdTvGsViewPtr pView = getActiveTvViewPtr();
        if (!pView.isNull() && pView->isInInteractivity())
            pView->endInteractivity();
    }
}

// cutting plane methods

void TviCore::onAppearSectioningPanel(bool bAppear)
{
    if (bAppear)
    {
        bool bShow = m_sectioningOptions.getShown();
        if (bShow)
        {
            //checking just for safety
            TviCuttingPlaneDragger *cuttingPlaneDragger = dynamic_cast<TviCuttingPlaneDragger*>(m_pActiveDragger.get());
            if (!cuttingPlaneDragger)
            {
                OdTvDraggerPtr pNewDragger = new TviCuttingPlaneDragger(m_TvDeviceId, m_TvDraggersModelId, m_pGlobalParams, this);
                
                if (pNewDragger)
                    startDragger(pNewDragger, true);
                
                update();
            }
        }
    }
    else
    {
        TviCuttingPlaneDragger *cuttingPlaneDragger = dynamic_cast<TviCuttingPlaneDragger*>(m_pActiveDragger.get());
        if (cuttingPlaneDragger)
        {
            cuttingPlaneDragger->setCanBeFinished(true);
            finishDragger();
            
            update();
        }
    }
}

// Cutting plane methods
bool TviCore::setShowCuttingPlanes(bool bShow)
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
        OdTvDraggerPtr pNewDragger = new TviCuttingPlaneDragger(m_TvDeviceId, m_TvDraggersModelId, m_pGlobalParams, this);
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
        TviCuttingPlaneDragger *cuttingPlaneDragger = dynamic_cast<TviCuttingPlaneDragger*>(m_pActiveDragger.get());
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

bool TviCore::addCuttingPlane(const OdTvVector& axis, OdTvResult* rc)
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
    catch (std::bad_cast&/* e*/)
    {
    }
    return true;
}

void TviCore::setCuttingPlanesFilled(bool bFilled)
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

void TviCore::setCuttingPlanesFillingColor(OdUInt32 color)
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

void TviCore::removeCuttingPlanes()
{
    OdTvGsViewPtr pActiveView = getActiveTvViewPtr();
    if (pActiveView.isNull())
        return;
    
    try
    {
        if (m_sectioningOptions.getShown())
        {
            //notify dragger
            TviCuttingPlaneDragger *cuttingPlaneDragger = dynamic_cast<TviCuttingPlaneDragger*>(m_pActiveDragger.get());
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
    catch (std::bad_cast*)
    {
    }
}

void TviCore::onRemoveCuttingPlane(const OdTvEntityId& entId)
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
void TviCore::drawCuttingPlane(OdUInt32 index, bool bNeedNotifyDragger)
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
    TviCuttingPlaneDragger *cuttingPlaneDragger = dynamic_cast<TviCuttingPlaneDragger*>(m_pActiveDragger.get());
    if (cuttingPlaneDragger)
        cuttingPlaneDragger->onCuttingPlaneAdded(cuttingPlanesEntityId);
}

double TviCore::getMainModelExtentsDistance() const
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


bool TviCore::runCollide()
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
        {
            showMessage(@"Collide: Warning", @"Collide tool can not work in wireframe mode");
            return false;
        }
    }
    else
        return false;
    
    //create dragger
    TviCollideDragger* pNewDragger = new TviCollideDragger(m_TvDeviceId, m_TvMainModelId, m_TvDraggersModelId, m_pGlobalParams, this);
    //start dragger
    startDragger(pNewDragger, true);
    getActiveTvExtendedView()->setViewType(OdTvExtendedView::kCustom);
    
    return true;
}

void TviCore::resetDraggerIndicator()
{
    [m_pParentController addBottomBorder:nil];
}
