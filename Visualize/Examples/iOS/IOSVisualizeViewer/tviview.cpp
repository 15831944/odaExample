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
#include "tviview.h"

#include "TvFactory.h"
#include "TvError.h"
#include "OdError.h"
#include "tvidatabaseinfo.h"
#include "Draggers/tvizoomwindowdragger.h"
#include "TviImportParamsController.h"
#include "TvDeprecated.h""

#include <QElapsedTimer>

//#include <Foundation/Foundation.h>
//#include <UIKit/UIView.h>

#include <DbDatabase.h>
#include <QDir>
#include <QElapsedTimer>
#include <QFileInfo>
#include <QStandardPaths>

#include "tviutils.h"

#if defined(__APPLE__)
#include "TviMemoryStatus.h"
#define OD_TV_APP_NAME OD_T("IOS Visualize Viewer")
#else
#define OD_TV_APP_NAME OD_T("Visualize Viewer")
#endif

std::wstring getExtensionFromFile(const QString& fileName, bool retUpper = true)
{
    QString2WString q2w( fileName );
    size_t pos = q2w.wstr().find_last_of(L".");
    if (pos == std::wstring::npos)
        return std::wstring();

    std::wstring strExt = q2w.wstr().substr(pos + 1, q2w.wstr().length() - pos);
    if(retUpper)
        transform(strExt.begin(), strExt.end(), strExt.begin(), toupper);
    return strExt;
}

inline double TvRound(double a)
{
    double aFloor = ::floor(a);
    if (a - aFloor >= 0.5)
        return aFloor + 1.0;
    return aFloor;
};

TviView::TviView(TviAppearanceParams *pAppearanceParams) : m_bInitialized(false), m_pAnimation(NULL), m_pFileOpenTask(NULL), m_bIsBlocked(true), m_bIsPainting(false)
  , m_iFooterHeight(0), m_iHeaderHeight(0), m_fileExt(kNone), m_pAppearanceParams(pAppearanceParams)
  , m_afterPaintActions(kNothing)
{
    m_pThreadController = new TviThreadController();
    connect(m_pThreadController, SIGNAL(resultReady()), this, SLOT(onDatabaseLoadDone()), Qt::QueuedConnection);
    connect(m_pThreadController, SIGNAL(error(const QString&)), this, SLOT(onErrorHandle(const QString&)), Qt::QueuedConnection);
    connect(m_pThreadController, SIGNAL(unexpectedError()), this, SLOT(onUnexpectedError()), Qt::QueuedConnection);
    connect( &m_autoUpdateTimer, &QTimer::timeout, this, &TviView::autoUpdateTimeout );
}

TviView::~TviView()
{
    if(m_pFileOpenTask)
        delete m_pFileOpenTask;
    if(m_pThreadController)
        delete m_pThreadController;

    if(!m_TvDatabaseId.isNull())
    {
        //free all extended basic views
        std::map < OdTvGsViewId, OdTvExtendedView* >::iterator iter = m_tvExtendedViewsMap.begin(), end = m_tvExtendedViewsMap.end();
        while (iter != end)
        {
            if (iter->second)
                delete iter->second;
            ++iter;
        }
        m_tvExtendedViewsMap.clear();

        if(!m_TvDeviceId.isNull())
            m_TvDeviceId.openObject(OdTv::kForWrite)->eraseAllViews();

        odTvGetFactory().removeDatabase(m_TvDatabaseId);
    }
}

void TviView::setFilePath(const QString &filePath)
{
    QFileInfo info(filePath);
    if (filePath.isEmpty() || !info.exists() || (info.exists() && !info.isReadable()))
    {
        if(filePath.isEmpty())
            emit showMessageSg("Error", "Filepath is empty");
        else if(!info.exists())
            emit showMessageSg("Error", "Filepath is not exist");
        else if(info.exists() && !info.isReadable())
            emit showMessageSg("Error", "File " + filePath + " is not accessible to read");
        emit resetSg();
        return;
    }

    m_filePath = filePath;

    //0. get file extension
    std::wstring strExt = getExtensionFromFile(filePath);
    setImportParams(strExt.c_str());
}

void TviView::paint()
{
    try{
        if(m_TvDeviceId.isNull() || m_bIsBlocked)
        {
            return;
        }
        m_bIsPainting = true;

        OdTvGsDevicePtr pDev = m_TvDeviceId.openObject();

        // get first update tiem
        QElapsedTimer *pTimer = NULL;
        if (!m_bInitialized)
        {
            pTimer = new QElapsedTimer;
            pTimer->start();
        }

        pDev->invalidate();
        pDev->update();

        if (!m_bInitialized)
        {
            OdInt64 nElapsedTime = OdInt64(pTimer->elapsed());
            m_databaseInfo.setFirstUpdateTime(nElapsedTime);
            delete pTimer;
            m_bInitialized = true;
            emit showTotalTime(m_databaseInfo.getTotalTime());
        }

        if( pDev->getBackgroundPartialViewingInProgress() )
        {
            m_autoUpdateTimer.start( 1000 );
        }

        //perform animation
        if (m_pAnimation && m_pAnimation->isRunning())
        {
            m_pAnimation->step();
            m_window->resetOpenGLState();
            m_window->update();
        }

        m_window->resetOpenGLState();

        m_bIsPainting = false;
        actionAfterPaint();
    }
    catch(OdError odErr)
    {
        emit showMessageSg("Error", toQString(odErr.description()));
    }
    catch(OdTvError &tvErr)
    {
        emit showMessageSg("Error", toQString(tvErr.description()));
    }
}

void TviView::autoUpdateTimeout()
{
    m_autoUpdateTimer.stop();
    OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject();
    if (pDevice.isNull())
        return;
    pDevice->update( NULL, true );
    if( pDevice->getBackgroundPartialViewingInProgress() )
    {
        m_autoUpdateTimer.start( 1000 );
    }
}

void TviView::onErrorHandle(const QString &msg)
{
    if(m_pFileOpenTask)
        delete m_pFileOpenTask;
    emit showMessageSg( "Error", msg );
    emit resetSg();
}

void TviView::onUnexpectedError()
{
    if(m_pFileOpenTask)
        delete m_pFileOpenTask;
    emit showMessageSg( "Error", "Unexpected error" );
    emit resetSg();
}

void TviView::onDatabaseLoadDone()
{
    if(!m_pFileOpenTask)
        return;

    m_TvDatabaseId = m_pFileOpenTask->getTvDatabase();

    delete  m_pFileOpenTask;
    m_pFileOpenTask = NULL;

    if(m_TvDatabaseId.isNull() || !m_TvDatabaseId.isValid())
        return;

    OdTvDatabasePtr pDb = m_TvDatabaseId.openObject(OdTv::kForWrite);
    if (!pDb.isNull())
    {
        OdTvDevicesIteratorPtr pDevIt = pDb->getDevicesIterator();
        // create own device if noone
        if(pDevIt->done())
            createTvDevice();
        else
        {
            m_TvDeviceId = pDevIt->getDevice();
            setupGs();
        }

        if(!initialize())
            return;

        OdTvGsViewPtr pView = getActiveTvViewPtr();
        if(pView.isNull())
            return;
        OdTvExtendedView *pExtView = getActiveTvExtendedView();
        if(!pExtView)
            return;
        QString renderMode;
        switch ( pExtView->getRenderMode() ) {
        case OdTvGsView::k2DOptimized:
            renderMode = "2DOptimized";
            break;
        case OdTvGsView::kWireframe:
            renderMode = "Wireframe";
            break;
        case OdTvGsView::kHiddenLine:
            renderMode = "HiddenLine";
            break;
        case OdTvGsView::kFlatShaded:
            renderMode = "FlatShaded";
            break;
        case OdTvGsView::kGouraudShaded:
            renderMode = "GouraudShaded";
            break;
        case OdTvGsView::kFlatShadedWithWireframe:
            renderMode = "FlatShadedWithWireframe";
            break;
        case OdTvGsView::kGouraudShadedWithWireframe:
            renderMode = "GouraudShadedWithWireframe";
            break;
        }

        emit loadDoneSg(pView->isPerspective(), renderMode);
    }
}

void TviView::setImportParams(const OdString &strExt)
{
    if (strExt == OD_T("DWG") || strExt == OD_T("DXF") || strExt == OD_T("DGN") || strExt == OD_T("PRC")
            || strExt == OD_T("DSF"))
    {
        OdTvDCRect dcRect(0, m_viewportSize.width(), m_viewportSize.height(), 0);
        m_importParams.dwgImportParam.setDCRect(dcRect);
        m_importParams.dgnImportParam.setDCRect(dcRect);
        m_importParams.prcImportParam.setDCRect(dcRect);
    }

    QString qExt =toQString(strExt);

    if( strExt == OD_T("VSF") )
    {
        m_fileExt = kVsf;
        emit showImportParamsDialog(qExt);
    }
    else if( strExt == OD_T("RCS") )
    {
        m_fileExt = kRcs;
        emit showImportParamsDialog(qExt);
    }
    else if( strExt == OD_T("DWG") || strExt == OD_T("DXF") || strExt == OD_T("DSF") )
    {
        m_fileExt = kDrw;
        emit showImportParamsDialog("DRW");
    }
    else if( strExt == OD_T("DGN") )
    {
        m_fileExt = kDgn;
        emit showImportParamsDialog(qExt);
    }
    else if( strExt == OD_T("STL") )
    {
        m_fileExt = kStl;
        emit showImportParamsDialog(qExt);
    }
    else if( strExt == OD_T("OBJ") )
    {
        m_fileExt = kObj;
        emit showImportParamsDialog(qExt);
    }
    else if( strExt == OD_T("PRC") )
    {
        m_fileExt = kPrc;
        emit showImportParamsDialog(qExt);
    }
}

OdTvModelId TviView::loadTvDatabase(OdTvBaseImportParams *pImportParam, TviView::LoadMode loadMode)
{
    OdTvModelId modelId;
    OdTvFactoryId id = odTvGetFactory();
    if(id.isNull())
        return  modelId;

    if (loadMode == kRead)
    {
        //read database
        OdTvResult rc = tvOk;

        try
        {
            QElapsedTimer timer;
            timer.start();

            // read the file
            OdTvVsfImportParams params;
            params.setFilePath( pImportParam->getFilePath() );
            params.setMtImport( false );
            m_TvDatabaseId = id.importFile(&params, &rc);

            // fill profiling info
            if (pImportParam->getProfiling())
                pImportParam->getProfiling()->setImportTime(OdInt64(timer.elapsed()));
        }
        catch (OdTvError& e)
        {
            OdString descr = e.description();
            QString filePath = toQString( pImportParam->getFilePath() );
            emit showMessageSg("Error", "Reading of file " + filePath + " was failed (" + toQString(descr) + ").");
            emit resetSg();
            return modelId;
        }
    }
    else if (loadMode == kImport)
    {
        //import to database
        OdTvResult rc = tvOk;

        try
        {
            m_TvDatabaseId = id.importFile(pImportParam, &rc);

            if (rc != tvOk)
            {
                QString msg;
                if (rc == tvMissingFilerModule)
                    msg = "Missing filer module.";
                else
                    msg = "Error during open file.";
                emit showMessageSg("Error", msg);
                emit resetSg();
            }

        }
        catch (OdTvError& e)
        {
            OdString descr = e.description();
            QString filePath = toQString( pImportParam->getFilePath() );
            emit showMessageSg("Error", "Importing of file " + filePath + " was failed (" + toQString(descr) + ").");
            emit resetSg();
            return modelId;
        }
    }

    //get active model (now it is always the first model)
    if (m_TvDatabaseId.isValid())
    {
        OdTvDatabasePtr pDb = m_TvDatabaseId.openObject();
        if (!pDb.isNull())
        {
            OdTvModelsIteratorPtr pModelsIterator = pDb->getModelsIterator();
            modelId = pModelsIterator->getModel();
        }
    }

    return modelId;
}

void TviView::setupGs()
{
    if(m_TvDeviceId.isNull())
        return;

    OdTvGsDevicePtr pDev = m_TvDeviceId.openObject(OdTv::kForWrite);

    QObject *pHeader = m_window->findChild<QObject*>("headerToolBar");
    QObject *pFooter = m_window->findChild<QObject*>("footerToolBar");
    if(pHeader && pFooter)
    {
        m_iHeaderHeight = pHeader->property("height").toInt() * m_window->devicePixelRatio();
        m_iFooterHeight = pFooter->property("height").toInt() * m_window->devicePixelRatio();
    }

    if( (m_fileExt == kVsf)
        || (m_fileExt == kDrw && m_importParams.dwgImportParam.getOpenSourcePartial()) ) {
        pDev->setBackgroundPartialView(true);
    }

    OdTvResult res = tvOk;

    res = pDev->setupGsWithContext(m_window->openglContext(), OdTvDCRect(0, m_window->width() * m_window->devicePixelRatio()
                                                                   , m_window->height() * m_window->devicePixelRatio() - (m_iHeaderHeight - m_iFooterHeight)
                                                                   , m_iFooterHeight), OdTvGsDevice::kOpenGLES2);
    if(res != tvOk) {
        emit showMessageSg("Error", "Setup of device failed");
        return;
    }
    pDev->setOption(OdTvGsDevice::kUseOverlayBuffers, false);
    pDev->setOption(OdTvGsDevice::kCreateGLContext, false);
    //pDev->setOption(OdTvGsDevice::kBlendingMode, 0);
    pDev->setOption(OdTvGsDevice::kUseSceneGraph, m_pAppearanceParams->getUseSceneGraph());
    pDev->setActive(true);
}

bool TviView::initialize()
{
    OdTvDatabasePtr pDatabase = m_TvDatabaseId.openObject(OdTv::kForWrite);

    // get main model
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if(pView.isNull()) {
        emit showMessageSg("Error", "Active view is null");
        return false;
    }

    m_TvMainModel = pView->modelAt(0);
    if(m_TvMainModel.isNull()) {
        emit showMessageSg("Error", "Main model is null");
        return false;
    }

    //create model for the temporary objects (for draggers )
    m_TvDraggersModelId = pDatabase->findModel(OD_T("$Draggers"));
    if (m_TvDraggersModelId.isNull())
        m_TvDraggersModelId = pDatabase->createModel(OD_T("$Draggers"), OdTvModel::kDirect, false);

    // register app name (for user data)
    bool alreadyExist;
    m_appTvId = m_TvDatabaseId.openObject()->registerAppName(OD_TV_APP_NAME, alreadyExist);

    if(m_pAppearanceParams)
    {
        OdTvExtendedView *pExtView = getActiveTvExtendedView();
        if(pExtView)
        {
            m_afterPaintActions = m_afterPaintActions | kSetWcs;
            pExtView->setAnimationEnabled(m_pAppearanceParams->getAnimationEnabled());
        }

        m_afterPaintActions = m_afterPaintActions | kSetFps;
    }

    // create default dragger (pan dragger)
    TviPanDragger *panDragger = new TviPanDragger(m_TvDeviceId, m_TvDraggersModelId);
    m_pActiveDragger = panDragger;
    eDraggerResult res = m_pActiveDragger->start(NULL, getActiveTvExtendedView());
    actionsAfterDragger(res);

    return true;
}

void TviView::finishDragger()
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

void TviView::startDragger(OdTvDraggerPtr pNewDragger, bool bUseCurrentAsPrevious)
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

void TviView::screenDolly(int x, int y)
{
    // get the active view and perform zooming
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if (pView.isNull())
        return;

    OdGeVector3d vec(x, y, 0.0);
    vec.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
    pView->dolly(vec);
}

void TviView::actionsAfterDragger(eDraggerResult res)
{
    if (res & kNeedUpdateView)
        m_window->update();

    if (res & kNeedFinishDragger)
        finishDragger();
}

void TviView::runNavigationAction(TviView::NavigationAction navAct)
{
    OdTvDraggerPtr pNewDragger;
    OdTvGsViewPtr pView = getActiveTvViewId().openObject();

    switch (navAct) {
    case kPan:
    {
        pNewDragger = new TviPanDragger(m_TvDeviceId, m_TvDraggersModelId);
        break;
    }
    case kOrbit:
    {
        pNewDragger = new TviOrbitDragger(m_TvDeviceId, m_TvDraggersModelId);
        disableMarkups();
        break;
    }
    case kZoomWindow:
    {
        pNewDragger = new TviZoomWindowDragger(m_TvDeviceId, m_TvDraggersModelId, this);
        break;
    }
    case kZoomExtents:
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
            m_pAnimation->start();

        m_window->update();

        break;
    }
    }

    //start dragger
    if(!pNewDragger.isNull())
        startDragger(pNewDragger);

    getActiveTvExtendedView()->setViewType(OdTvExtendedView::kCustom);
}

void TviView::set3DView(OdTvExtendedView::e3DViewType type)
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
        m_pAnimation->start();

    disableMarkups();

    // update the widget
    m_window->update();
}

void TviView::runRegenAction(TviView::RegenAction regenAct)
{
    OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject(OdTv::kForWrite);
    if (pDevice.isNull())
        return;
    switch (regenAct)
    {
    case kAll:
    {
        pDevice->regen(OdTvGsDevice::kRegenAll);
        break;
    }
    case kVisible:
    {
        pDevice->regen(OdTvGsDevice::kRegenVisible);
        break;
    }
    case kView:
    {
        OdTvGsViewPtr pView = getActiveTvViewId().openObject();
        if (!pView.isNull())
            pView->regen();
        break;
    }
    }

    m_window->update();
}

void TviView::runRenderMode(OdTvGsView::RenderMode newMode)
{
    OdTvExtendedView* pBasicView = getActiveTvExtendedView();
    if (pBasicView)
    {
        if (pBasicView->setRenderMode(newMode))
            m_window->update();
    }
}

void TviView::runMarkupAction(TviView::MarkupAction act)
{
    if (m_TvMarkupsModelId.isNull()) {
        OdTvDatabasePtr pDatabase = m_TvDatabaseId.openObject(OdTv::kForWrite);
        m_TvMarkupsModelId = pDatabase->findModel(OD_TV_MARKUP_MODEL);
        if(m_TvMarkupsModelId.isNull())
            m_TvMarkupsModelId = pDatabase->createModel(OD_TV_MARKUP_MODEL, OdTvModel::kDirect, false);
    }

    OdTvDraggerPtr pNewDragger;
    switch (act)
    {
    case kRectangle:
        pNewDragger = new OdTvRectangleMarkupDragger(m_TvDeviceId, m_TvMarkupsModelId, m_appTvId, OdTvColorDef(255, 0, 0), 3);
        break;
    case kCircle:
        pNewDragger = new OdTvCircleMarkupDragger(m_TvDeviceId, m_TvMarkupsModelId, m_appTvId, OdTvColorDef(255, 0, 0), 3);
        break;
    case kHandle:
        pNewDragger = new OdTvHandleMarkupDragger(m_TvDeviceId, m_TvMarkupsModelId, m_appTvId, OdTvColorDef(255, 0, 0), 3);
        break;
    case kCloud:
        pNewDragger = new OdTvCloudMarkupDragger(m_TvDeviceId, m_TvMarkupsModelId, m_appTvId, OdTvColorDef(255, 0, 0), 3);
        break;
    case kText:
        pNewDragger = new OdTvTextMarkupDragger(m_TvDeviceId, m_TvMarkupsModelId, m_appTvId, OdTvColorDef(255, 0, 0), 3);
        break;
    case kSave:
        markupSaveView();
        break;
    case kLoad:
        markupLoadView();
        break;
    }

    //start dragger
    if (!pNewDragger.isNull())
        startDragger(pNewDragger);
}

void TviView::setProjection(TviView::ProjectionType projType)
{
    OdTvGsViewPtr pView = getActiveTvViewId().isNull() ? OdTvGsViewPtr() : getActiveTvViewId().openObject(OdTv::kForWrite);
    if(pView.isNull())
        return;
    pView->setView( pView->position(), pView->target(), pView->upVector(), pView->fieldWidth(), pView->fieldHeight()
                    , (OdTvGsView::Projection)projType );
}

void TviView::performZoomEvent(const QPointF &pnt, double delta)
{
    // get the active view and perform zooming
    OdTvGsViewPtr pView = getActiveTvViewPtr();
    if (pView.isNull() || qAbs(delta) < 0.003)
        return;

    OdGePoint3d pos(pView->position());
    pos.transformBy(pView->worldToDeviceMatrix());

    int vx, vy;
    vx = (int)TvRound(pos.x);
    vy = (int)TvRound(pos.y);
    vx = pnt.x() - vx;
    vy = pnt.y() - vy;

    double dScale = 0.965;
    if (delta > 0)
        dScale = 1.0 / dScale;

    screenDolly(vx, vy);
    pView->zoom(dScale);
    screenDolly(-vx, -vy);

    m_window->update();
}

void TviView::setRenderBlocked(bool isBlocked)
{
    m_bIsBlocked = isBlocked;
}

void TviView::createTvDevice()
{
    if(m_TvDatabaseId.isNull())
        return;
    OdTvDatabasePtr pDb = m_TvDatabaseId.openObject(OdTv::kForWrite);
    //WId id = m_window->winId();
    //    UIView *parentView = reinterpret_cast<UIView *>(id);
    //    CAEAGLLayer *caeaglLayer = static_cast<CAEAGLLayer *>( parentView.layer );
    OdTvResult rc = tvDevicesIsEmpty;
    pDb->createDeviceWithContext( OD_T("Device"), m_window->openglContext()
                                  , OdTvDCRect(0, m_window->width() * m_window->devicePixelRatio(), m_window->height() * m_window->devicePixelRatio(), 0)
                                  , OdTvGsDevice::kOpenGLES2, NULL, &rc);
    //    m_TvDeviceId = pDb->createDevice(OD_T("Device"), caeaglLayer
    //                                     , OdTvDCRect(0, m_window->width() * m_window->devicePixelRatio(), m_window->height() * m_window->devicePixelRatio(), 0)
    //                                     , OdTvGsDevice::kOpenGLES2, NULL, &rc);

    if(!m_TvDeviceId.isNull())
    {
        OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject(OdTv::kForWrite);
        pDevice->setOption(OdTvGsDevice::kCreateGLContext, false);
        pDevice->setActive(true);
        // create view
        OdTvGsViewId newViewId = pDevice->createView(OD_T("MyView"), true);
        pDevice->addView(newViewId);

        // add current model to the view
        {
            OdTvGsViewPtr viewPtr = newViewId.openObject(OdTv::kForWrite);

            //setup view to make it contr directional with the WCS normal
            viewPtr->setView(OdTvPoint(0., 0., 1.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 1., 1.);

            //add main model to the view
            viewPtr->addModel(m_TvMainModel);

            // set current view as active
            viewPtr->setActive(true);

            //set the render mode
            viewPtr->setMode(OdTvGsView::k2DOptimized);

            //try to make zoom to extents here
            //1. Try to get the viewport extents
            OdGeBoundBlock3d pViewExt;
            if (viewPtr->viewExtents(pViewExt))
            {
                bool bPerspective = viewPtr->isPerspective();
                if (!bPerspective)
                    pViewExt.setToBox(true);

                //2. Get the Eye to World matrix
                OdGeMatrix3d xWorldToEye = viewPtr->viewingMatrix();
                OdGeMatrix3d xEyeToWorld = xWorldToEye.invert();

                //3. Transform extents to WCS
                OdGePoint3d min = pViewExt.minPoint();
                OdGePoint3d max = pViewExt.maxPoint();

                min.transformBy(xEyeToWorld);
                max.transformBy(xEyeToWorld);

                //call view method
                viewPtr->zoomExtents(min, max);
            }
        }
    }
}

OdTvGsViewId TviView::getActiveTvViewId() const
{
    if (m_TvDeviceId.isNull())
        return OdTvGsViewId();
    OdTvGsDevicePtr pDevice = m_TvDeviceId.openObject();
    OdTvGsViewId viewId = pDevice->getActiveView();
    if (viewId.isNull())
        viewId = pDevice->viewAt(0);
    return viewId;
}

OdTvGsViewPtr TviView::getActiveTvViewPtr()
{
    if (getActiveTvViewId().isNull())
        return OdTvGsViewPtr();
    return getActiveTvViewId().openObject(OdTv::kForWrite);
}

OdTvExtendedView *TviView::getActiveTvExtendedView()
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

void TviView::adjustPointY(QPointF &pnt) {
    pnt.setY(pnt.y() + m_iHeaderHeight + m_iFooterHeight);
}

void TviView::openFile()
{
    // transform to OdString
    QString2WString q2w( m_filePath );
    m_databaseInfo.setFilePath(q2w.wstr().c_str());
    if (m_fileExt == kVsf)
        m_databaseInfo.setType(TviDatabaseInfo::kFromFile);
    else
        m_databaseInfo.setType(TviDatabaseInfo::kImport);

    OdTvBaseImportParams *params;
    switch (m_fileExt) {
    case kVsf:
        params = &m_importParams.vsfReadParam;
        break;
    case kRcs:
        params = &m_importParams.rcsImportParam;
        break;
    case kDrw:
        params = &m_importParams.dwgImportParam;
        break;
    case kDgn:
        params = &m_importParams.dgnImportParam;
        break;
    case kStl:
        params = &m_importParams.stlImportParam;
        break;
    case kObj:
        params = &m_importParams.objImportParam;
        break;
    case kPrc:
        params = &m_importParams.prcImportParam;
        break;
    }

    //3. fill base fields in param
    params->setFilePath(q2w.wstr().c_str());
    params->setProfiling(&m_databaseInfo);

    //SEA enable limitator if need
    bool bLowMemory = false;
    if( (m_pAppearanceParams->getUseLimitManager() &&  m_fileExt == kVsf)
            || (m_fileExt == kDrw && m_importParams.dwgImportParam.getOpenSourcePartial()) )
    {
        bLowMemory = true;
        odTvGetFactory().setLimitManager( &m_limitator );
    }

    m_pFileOpenTask = new TviFileOpenThreadTask( params, m_databaseInfo, q2w.wstr().c_str(), m_pAppearanceParams, bLowMemory );
    m_pThreadController->setTask(m_pFileOpenTask);
    m_pThreadController->start();
}

void TviView::applyAppearanceParams()
{
    OdTvExtendedView *pExtView = getActiveTvExtendedView();
    if(!pExtView)
        return;
    pExtView->setAnimationEnabled(m_pAppearanceParams->getAnimationEnabled());
    m_afterPaintActions = m_afterPaintActions | kSetWcs;
    m_afterPaintActions = m_afterPaintActions | kSetFps;
}

OdTvGeometryStatistic* TviView::getStatistic()
{
    if(m_TvMainModel.isNull())
        return  NULL;
    m_modelStat = m_TvMainModel.openObject()->getStatistic();
    return  &m_modelStat;
}

void TviView::saveFile(bool bPartialIndexes, const QString &fileName)
{
    if(m_TvDatabaseId.isNull()) {
        emit showMessageSg("Error", "Database for save file not exist");
        return;
    }

    if(m_filePath.isEmpty()) {
        emit showMessageSg("Error", "Filepath is empty");
        return;
    }

    QFileInfo fInfo(m_filePath);
    QString saveFileName = fInfo.absolutePath() + "/" + fileName;

    OdTvDatabasePtr pDb = m_TvDatabaseId.openObject(OdTv::kForWrite);
    if(bPartialIndexes)
        pDb->addPartialViewIndexes();
    OdTvResult rc = OdTvDeprecated::writeFile( m_TvDatabaseId, toOdString(saveFileName));
    if(rc != tvOk) {
        emit showMessageSg("Error", "Filepath is empty");
        return;
    }
    else
        emit showMessageSg("Save file", QString("File ") + fileName + QString(" saved successfully"));
}

void TviView::saveMarkup(const QString &name)
{
    if(name.isEmpty()) {
        emit showMessageSg("Error", "Markup name is empty");
        emit showSaveMarkupDlg();
    }

    OdString newMarkupName = toOdString(name);
    OdTvEntityId activeEntityId;
    OdTvEntitiesIteratorPtr pEnIt = m_TvMarkupsModelId.openObject()->getEntitiesIterator();
    while (!pEnIt->done())
    {
        OdTvEntityId enId = pEnIt->getEntity();
        OdTvEntityPtr pEn = enId.openObject();

        if(!pEn->getName().compare(newMarkupName)) {
            emit showMessageSg("Error", "Markup name already exist");
            emit showSaveMarkupDlg();
            return;
        }

        if (pEn->getName().compare(OD_TV_MARKUP_TEMP_ENTITY) == 0 || pEn->getVisibility() != OdTvVisibilityDef::kInvisible)
            activeEntityId = enId;

        pEnIt->step();
    }

    if (activeEntityId.isNull())
    {
        emit showMessageSg("Error", "No one markup for save");
        return;
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
}

void TviView::loadMarkup(const QString &name)
{
    if(name.isEmpty()) {
        emit showMessageSg("Error", "Markup name is empty");
        return;
    }

    OdTvEntityId entForLoadId;
    OdString loadName = toOdString(name);
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
            return;

        // fill active and wcs view params from binary user data
        OdTvExtendedView* pExtView = getActiveTvExtendedView();
        if (pExtView)
        {
            pExtView->setEnabledWCS(m_pAppearanceParams->getWcsEnabled());
            pExtView->setView(params->m_pos, params->m_target, params->m_up, params->m_width, params->m_height, params->m_proj);
            pExtView->setRenderMode(params->m_mode);
            m_pAnimation = pExtView->getAnimation();
            if (m_pAnimation)
                m_pAnimation->start();
        }

        pEnt->setVisibility(true);
    }
}

void TviView::deleteMarkup(const QString &name)
{
    if(name.isEmpty() || m_TvMarkupsModelId.isNull())
        return;
    OdString enName = toOdString(name);
    OdTvModelPtr pModel = m_TvMarkupsModelId.openObject(OdTv::kForWrite);
    OdTvEntityId id;
    // find entity
    for( OdTvEntitiesIteratorPtr pIt = pModel->getEntitiesIterator(); !pIt->done(); pIt->step() ) {
        if(!pIt->getEntity().openObject()->getName().compare(enName)) {
            id = pIt->getEntity();
            break;
        }
    }
    // remove entity
    if(!id.isNull())
        pModel->removeEntity(id);

    if(m_savedMarkups.contains(name)) {
        m_savedMarkups.removeAt( m_savedMarkups.indexOf(name) );
        emit showLoadMarkupDlg(m_savedMarkups);
    }
}

void TviView::actionAfterPaint()
{
    bool bNeedUpdate = m_afterPaintActions != kNothing;

    if(m_afterPaintActions & kSetFps)
    {
        if(!m_TvDeviceId.isNull())
            m_TvDeviceId.openObject(OdTv::kForWrite)->setShowFPS(m_pAppearanceParams->getFpsEnabled());
    }

    if(m_afterPaintActions & kSetWcs)
    {
        OdTvExtendedView *pExtView = getActiveTvExtendedView();
        if(pExtView)
            pExtView->setEnabledWCS(m_pAppearanceParams->getWcsEnabled());
    }

    m_afterPaintActions = kNothing;
    if(bNeedUpdate)
        m_window->update();
}

void TviView::disableMarkups()
{
    if (!m_TvMarkupsModelId.isNull())
    {
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
}

void TviView::markupSaveView()
{
    //Check that we have an active markup entity (temporary or visible (loaded))
    if (m_TvMarkupsModelId.isNull())
    {
        emit showMessageSg("Error", "Markup model is NULL");
        return;
    }

    OdTvEntitiesIteratorPtr pEnIt = m_TvMarkupsModelId.openObject()->getEntitiesIterator();
    if (pEnIt->done())
    {
        emit showMessageSg("Error", "Markup model is empty");
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
        emit showMessageSg("Save markup", "No one markup for save");
        return;
    }

    emit showSaveMarkupDlg();
}

void TviView::markupLoadView()
{
    //Check that we have an active markup entity (temporary or visible (loaded))
    if (m_TvMarkupsModelId.isNull())
    {
        emit showMessageSg("Error", "Markup model is NULL");
        return;
    }

    m_savedMarkups.clear();

    OdTvEntitiesIteratorPtr pEnIt = m_TvMarkupsModelId.openObject()->getEntitiesIterator();
    if (pEnIt->done())
    {
        emit showMessageSg("Load markup", "Markup model is empty");
        return;
    }

    // fill list
    while(!pEnIt->done())
    {
        OdTvEntityId entId = pEnIt->getEntity();
        if (!entId.isNull() && entId.openObject()->getName().compare(OD_TV_MARKUP_TEMP_ENTITY) != 0)
            m_savedMarkups << toQString( pEnIt->getEntity().openObject()->getName() );
        pEnIt->step();
    }

    if(m_savedMarkups.length() == 0)
    {
        emit showMessageSg("Load markup", "No one markup for load");
        return;
    }

    emit showLoadMarkupDlg(m_savedMarkups);
}



