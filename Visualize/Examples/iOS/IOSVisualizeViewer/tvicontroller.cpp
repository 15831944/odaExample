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
#include "tvicontroller.h"

#include <QGuiApplication>
#include <QQmlEngine>

#include "TviImportParamsController.h"
#include "tviutils.h"

TviController::TviController() : m_filePath(""), m_pTviView(NULL), m_bIsFileLoaded(false), m_pStat(NULL)
{
    connect(this, &QQuickItem::windowChanged, this, &TviController::handleWindowChanged);
    m_pAppearanceParams = new TviAppearanceParams(this);
}

TviController::~TviController()
{
    if(m_pTviView){
        delete m_pTviView;
    }
}

bool TviController::closeFileEvent()
{
    if(m_pTviView){
        window()->scheduleRenderJob(new TviCleanRenderDataJob(this), QQuickWindow::AfterRenderingStage);
        return true;
    }
    return false;
}

void TviController::cleanRenderData()
{
    if(m_pTviView)
    {
        m_filePath = "";
        delete m_pTviView;
        m_pTviView = NULL;
        window()->resetOpenGLState();
        m_pStat = NULL;
    }
}

void TviController::onAcceptImportDlg(QObject *qParams)
{
    if(!m_pTviView || (!qParams && m_pTviView->getFileExtension() != TviView::kVsf) )
        return;

    switch (m_pTviView->getFileExtension()) {
    case TviView::kRcs:
    {
        TviRcsImportParams *pRcsParams = qobject_cast<TviRcsImportParams*>(qParams);
        if(pRcsParams)
            m_pTviView->getImportParameters().rcsImportParam = pRcsParams->getImportParams();
        break;
    }
    case TviView::kDrw:
    {
        TviDrwImportParams *pDrwParams = qobject_cast<TviDrwImportParams*>(qParams);
        if(pDrwParams)
            m_pTviView->getImportParameters().dwgImportParam = pDrwParams->getImportParams();
        break;
    }
    case TviView::kDgn:
    {
        TviDgnImportParams *pDgnParams = qobject_cast<TviDgnImportParams*>(qParams);
        if(pDgnParams)
            m_pTviView->getImportParameters().dgnImportParam = pDgnParams->getImportParams();
        break;
    }
    case TviView::kStl:
    {
        TviStlImportParams *pStlParams = qobject_cast<TviStlImportParams*>(qParams);
        if(pStlParams)
            m_pTviView->getImportParameters().stlImportParam = pStlParams->getImportParams();
        break;
    }
    case TviView::kObj:
    {
        TviObjImportParams *pObjParams = qobject_cast<TviObjImportParams*>(qParams);
        if(pObjParams)
            m_pTviView->getImportParameters().objImportParam = pObjParams->getImportParams();
        break;
    }
    case TviView::kPrc:
    {
        TviPrcImportParams *pPrcParams = qobject_cast<TviPrcImportParams*>(qParams);
        if(pPrcParams)
            m_pTviView->getImportParameters().prcImportParam = pPrcParams->getImportParams();
        break;
    }
    }

    m_pTviView->openFile();
}

void TviController::onRejectImportDlg()
{
    if(m_pTviView) {
        m_filePath = "";
        delete m_pTviView;
        m_pTviView = NULL;
    }
}

void TviController::applyAppearanceParams()
{
    if(m_pTviView)
        m_pTviView->applyAppearanceParams();

}

unsigned long TviController::getStatistic(int type)
{
    if(!m_pStat && m_pTviView) {
        m_pStat = m_pTviView->getStatistic();
    }

    if(m_pStat)
        return m_pStat->getCount( (OdTvGeometryStatistic::Types)type );

    return 0;
}

void TviController::saveFile(bool bPartialIndexes, const QString &fileName)
{
    if(!m_pTviView)
        return;
    m_pTviView->saveFile(bPartialIndexes, fileName);
}

void TviController::saveMarkup(const QString &name)
{
    if(m_pTviView)
        m_pTviView->saveMarkup(name);
}

void TviController::loadMarkup(const QString &name)
{
    if(m_pTviView)
        m_pTviView->loadMarkup(name);
}

void TviController::deleteMarkup(const QString &name)
{
    if(m_pTviView)
        m_pTviView->deleteMarkup(name);
}

void TviController::onDraggerDonePressed()
{
    if(!m_pTviView)
        return;
    OdTvDragger* pDragger = m_pTviView->getActiveDragger();
    if(!pDragger)
        return;
    eDraggerResult res = pDragger->processEnter();
    m_pTviView->actionsAfterDragger(res);
}

void TviController::onTextChanged(const QString& text)
{
    if(!m_pTviView)
        return;
    OdTvDragger* pDragger = m_pTviView->getActiveDragger();
    if(!pDragger)
        return;
    eDraggerResult res = pDragger->processText(toOdString(text));
    m_pTviView->actionsAfterDragger(res);
}

void TviController::onReturnPressed()
{
    if(!m_pTviView)
        return;
    OdTvDragger* pDragger = m_pTviView->getActiveDragger();
    if(!pDragger)
        return;
    eDraggerResult res = pDragger->processEnter();
    m_pTviView->actionsAfterDragger(res);
}

void TviController::onBackspacePressed()
{
    if(!m_pTviView)
        return;
    OdTvDragger* pDragger = m_pTviView->getActiveDragger();
    if(!pDragger)
        return;
    eDraggerResult res = pDragger->processBackspace();
    m_pTviView->actionsAfterDragger(res);
}

void TviController::setFilePath(const QString &filePath)
{
    if(!m_filePath.compare(filePath))
        return;
    
    m_filePath = filePath;
    emit filePathChanged();
    if (!m_pTviView) {
        m_pTviView = new TviView(m_pAppearanceParams);
        connect( m_pTviView, &TviView::loadDoneSg, this, &TviController::loadDoneSl );
        connect( m_pTviView, &TviView::showTotalTime, this, &TviController::showTotalTime );
        connect( m_pTviView, &TviView::showMessageSg, this, &TviController::showMessageSl );
        connect( m_pTviView, &TviView::resetSg, this, &TviController::resetSl );
        connect( m_pTviView, &TviView::showImportParamsDialog, this, &TviController::showImportParamsDialog );
        connect( m_pTviView, &TviView::showSaveMarkupDlg, this, &TviController::showSaveMarkupDlg );
        connect( m_pTviView, &TviView::showLoadMarkupDlg, this, &TviController::showLoadMarkupDlg );

        m_pTviView->setViewportSize( QSize( width() * window()->devicePixelRatio(), height() * window()->devicePixelRatio() ) );
        m_pTviView->setWindow(window());

        m_pTviView->setFilePath(m_filePath);
        //m_renderer->initializeTvDb();

        connect( window(), &QQuickWindow::beforeRendering, m_pTviView, &TviView::paint, Qt::DirectConnection );
    }
}

void TviController::sync()
{
    if(m_filePath.isEmpty())
        return;

}

void TviController::cleanup()
{
    if(m_pTviView)
    {
        if(!m_pTviView->getDeviceId().isNull())
            m_pTviView->getDeviceId().openObject(OdTv::kForWrite)->eraseAllViews();
    }
}

void TviController::loadDoneSl(bool isPerspective, const QString& renderMode)
{
    m_bIsFileLoaded = true;
    emit fileLoadDoneSg(isPerspective, renderMode);
    window()->update();
}

void TviController::showMessageSl(const QString &titleStr, const QString &msgStr)
{
    showMessageEvent(titleStr, msgStr);
}

void TviController::resetSl()
{
    resetSgEvent();
    m_filePath = "";
}

void TviController::onPanelButtonPressed(const QString &buttonName)
{
    if(buttonName.isEmpty() || !m_pTviView)
        return;

    if(buttonName == "pan") // navigation block
        m_pTviView->runNavigationAction(TviView::kPan);
    else if(buttonName == "orbit")
        m_pTviView->runNavigationAction(TviView::kOrbit);
    else if(buttonName == "zoomWindow")
        m_pTviView->runNavigationAction(TviView::kZoomWindow);
    else if(buttonName == "zoomExtents")
        m_pTviView->runNavigationAction(TviView::kZoomExtents);
    else if(buttonName == "viewTop") // view block
        m_pTviView->set3DView(OdTvExtendedView::kTop);
    else if(buttonName == "viewBottom")
        m_pTviView->set3DView(OdTvExtendedView::kBottom);
    else if(buttonName == "viewLeft")
        m_pTviView->set3DView(OdTvExtendedView::kLeft);
    else if(buttonName == "viewRight")
        m_pTviView->set3DView(OdTvExtendedView::kRight);
    else if(buttonName == "viewFront")
        m_pTviView->set3DView(OdTvExtendedView::kFront);
    else if(buttonName == "viewBack")
        m_pTviView->set3DView(OdTvExtendedView::kBack);
    else if(buttonName == "viewSW")
        m_pTviView->set3DView(OdTvExtendedView::kSW);
    else if(buttonName == "viewSE")
        m_pTviView->set3DView(OdTvExtendedView::kSE);
    else if(buttonName == "viewNW")
        m_pTviView->set3DView(OdTvExtendedView::kNW);
    else if(buttonName == "viewNE")
        m_pTviView->set3DView(OdTvExtendedView::kNE);
    else if(buttonName == "regenAll") // regen block
        m_pTviView->runRegenAction(TviView::kAll);
    else if(buttonName == "regenVisible")
        m_pTviView->runRegenAction(TviView::kVisible);
    else if(buttonName == "regenVp")
        m_pTviView->runRegenAction(TviView::kView);
    else if(buttonName == "2dwireframe") // render mode block
        m_pTviView->runRenderMode(OdTvGsView::k2DOptimized);
    else if(buttonName == "3dwireframe")
        m_pTviView->runRenderMode(OdTvGsView::kWireframe);
    else if(buttonName == "hiddenline")
        m_pTviView->runRenderMode(OdTvGsView::kHiddenLine);
    else if(buttonName == "shaded")
        m_pTviView->runRenderMode(OdTvGsView::kFlatShaded);
    else if(buttonName == "gouraudShaded")
        m_pTviView->runRenderMode(OdTvGsView::kGouraudShaded);
    else if(buttonName == "shadedWithEdges")
        m_pTviView->runRenderMode(OdTvGsView::kFlatShadedWithWireframe);
    else if(buttonName == "gouraudShadedWithEdges")
        m_pTviView->runRenderMode(OdTvGsView::kGouraudShadedWithWireframe);
    else if(buttonName == "isometric") // projection block
        m_pTviView->setProjection(TviView::kIsometric);
    else if(buttonName == "perspective")
        m_pTviView->setProjection(TviView::kPerspective);
    else if(buttonName == "markupRect")
        m_pTviView->runMarkupAction(TviView::kRectangle);
    else if(buttonName == "markupCirc")
        m_pTviView->runMarkupAction(TviView::kCircle);
    else if(buttonName == "markupHandle")
        m_pTviView->runMarkupAction(TviView::kHandle);
    else if(buttonName == "markupCloud")
        m_pTviView->runMarkupAction(TviView::kCloud);
    else if(buttonName == "markupText")
        m_pTviView->runMarkupAction(TviView::kText);
    else if(buttonName == "markupSave")
        m_pTviView->runMarkupAction(TviView::kSave);
    else if(buttonName == "markupLoad")
        m_pTviView->runMarkupAction(TviView::kLoad);
}

void TviController::unblockRenderSl()
{
    if(m_pTviView)
        m_pTviView->setRenderBlocked(false);
}

void TviController::onZoomSl(double delta, int x, int y)
{
    if (!m_pTviView || m_pTviView->isPainting())
       return;

    QPointF centerPt = QPointF( x,  y);
    centerPt *= window()->devicePixelRatio();

    m_pTviView->performZoomEvent(centerPt, delta);
}

OdGePoint3d toEyeToWorld(int x, int y, OdTvGsViewPtr pView)
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

void TviController::onTouchStartSl(int x, int y)
{
    if(!m_pTviView || m_pTviView->isPainting())
        return;
    OdTvDragger* pDragger = m_pTviView->getActiveDragger();
    if(!pDragger)
        return;
    eDraggerResult res = pDragger->activate();
    m_pTviView->actionsAfterDragger(res);

    // if text markup dragger not null, display virtual keyboard
    OdTvTextMarkupDragger *pTextMrkpDragger = dynamic_cast<OdTvTextMarkupDragger*>(pDragger);
    bool bExist = pTextMrkpDragger != NULL;
    if(bExist)
        emit displayVirtualKeyboard();

    QPointF pnt = QPointF(x * window()->devicePixelRatio(), y * window()->devicePixelRatio() );
    m_pTviView->adjustPointY(pnt);
    res = pDragger->nextpoint( pnt.x(), pnt.y() );
    if(res & kNeedFinishDragger)
        emit draggerFinished();

    // hide virtual keyboard
    if(bExist && res == kNeedFinishDragger) {
        emit hideVirtualKeyboard();
        OdTvGsViewPtr pView = m_pTviView->getActiveTvViewPtr();
        pView->dolly(m_backDelta.transformBy(pView->viewingMatrix()));
        m_backDelta.set(0., 0., 0.);
    }
    else if(bExist && res != kNeedFinishDragger) {
        OdTvGsViewPtr pView = m_pTviView->getActiveTvViewPtr();
        OdTvPoint screenPrevPt = pView->position().transformBy(pView->worldToDeviceMatrix());
        OdTvPoint prevPt = toEyeToWorld(screenPrevPt.x, screenPrevPt.y, pView) - pView->position().asVector();
        OdTvPoint curPt = toEyeToWorld(pnt.x(), pnt.y(), pView);
        OdTvVector delta = ( prevPt - (curPt - pView->position()) ).asVector();
        m_backDelta = ( prevPt + (pView->position() - curPt) ).asVector();
        pView->dolly(-delta.transformBy(pView->viewingMatrix()));
    }

    m_pTviView->actionsAfterDragger(res);
}

void TviController::onTouchUpdatedSl(int x, int y)
{
    if(!m_pTviView || m_pTviView->isPainting())
        return;
    OdTvDragger* pDragger = m_pTviView->getActiveDragger();
    if(!pDragger)
        return;
    QPointF pnt = QPointF(x * window()->devicePixelRatio(), y * window()->devicePixelRatio() );
    m_pTviView->adjustPointY(pnt);
    eDraggerResult res = pDragger->drag( pnt.x(), pnt.y() );
    m_pTviView->actionsAfterDragger(res);
}

void TviController::onTouchReleasedSl(int x, int y)
{
    if(!m_pTviView || m_pTviView->isPainting())
        return;
    OdTvDragger* pDragger = m_pTviView->getActiveDragger();
    if(!pDragger)
        return;
    QPointF pnt = QPointF(x * window()->devicePixelRatio(), y * window()->devicePixelRatio() );
    m_pTviView->adjustPointY(pnt);
    eDraggerResult res = pDragger->nextpointup( pnt.x(), pnt.y() );
    if(res & kNeedFinishDragger)
        emit draggerFinished();
    m_pTviView->actionsAfterDragger(res);
}

void TviController::handleWindowChanged(QQuickWindow *win)
{
    if (win)
    {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &TviController::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &TviController::cleanup, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}

// class for clean data after close file

TviCleanRenderDataJob::TviCleanRenderDataJob(TviController *pController)
{
    m_pController = pController;
}

void TviCleanRenderDataJob::run()
{
    if(m_pController)
        m_pController->cleanRenderData();
}
