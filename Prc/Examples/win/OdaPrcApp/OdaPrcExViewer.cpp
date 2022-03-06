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

#include "stdafx.h"

#include <winspool.h>
#include "OdRound.h"
#include "RxVariantValue.h"
#include "Gi/GiDrawableImpl.h"
#include "Gi/GiRasterImage.h"
#include "Gi/GiWorldDraw.h"
#include "Gs/Gs.h"
#include "Gs/GsBaseVectorizer.h"
#include "Gs/GsModel.h"
#include "Gs/GsSelectionReactor.h"
#include "Ge/GeLineSeg2d.h"
#include "MainFrm.h"
#include "OdaPrcApp.h"
#include "OdaPrcAppDoc.h"
#include "OdaPrcExViewer.h"
#include "OdPlatformStreamer.h"
#include "Ps/PlotStyles.h"
#include "GiGs/PrcGsManager.h"

#include "GiGs/PrcGiContext.h"

#include "DynamicLinker.h"
#include "Gi/GiFastExtCalc.h"

#include "ColorMapping.h"

#include "AbstractViewPE.h"

#include <afxpriv.h>
#include <afxodlgs.h>
#include "ChildFrm.h"
#include "winuser.h"
#include "SaveState.h"

// #include "Managers/BmViewTable.h"
// #include "Entities/BmDBView.h"
// #include "Entities/BmViewer.h"
// #include "Entities/BmDBDrawing.h"
// #include "Entities/BmViewport.h"
// #include "Managers/BmFamilyMgr.h"

typedef OdArray<ODCOLORREF, OdMemoryAllocator<ODCOLORREF> > ODGSPALETTE;
void zoom_extents(OdGsView* pView, OdPrcReferencedBase* pVpObj);

extern COdaPrcApp theApp;
/////////////////////////////////////////////////////////////////////////////
// OdaPrcExViewer

IMPLEMENT_DYNCREATE(OdaPrcExViewer, CView)

OdaPrcExViewer::OdaPrcExViewer() 
  : m_hWindowDC(0)
  , m_mode(kQuiescent)
  , m_pTracker(0)
  , m_bTrackerHasDrawables(false)
  , m_bRegenAbort(false)
  , m_hCursor(0)
  , m_pBasePt(0)
  , m_bInRegen(false)
  , m_paintMode(PaintMode_Regen)
{
}

OdaPrcExViewer::~OdaPrcExViewer()
{
}

BEGIN_MESSAGE_MAP(OdaPrcExViewer, CView)
  ON_WM_PAINT()
  ON_WM_SIZE()
  ON_WM_MOUSEWHEEL()
  ON_WM_DESTROY()
  ON_WM_CREATE()
  ON_WM_SETCURSOR()

  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_MOUSEMOVE()
  ON_WM_KEYDOWN()
  ON_WM_CHAR()
  ON_COMMAND(ID_VIEW_3DORBIT, OnView3dorbit)
  ON_COMMAND(ID_VIEW_PAN, OnDrag)

  ON_COMMAND(ID_VIEW_ZOOM_WINDOW, OnViewZoomWindow)
  ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
  ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
  ON_COMMAND(ID_VIEW_ZOOMEXTENTS, OnViewZoomextents)

  ON_COMMAND(ID_VIEWER_REGEN,   OnViewerRegen)
  ON_COMMAND(ID_VIEWER_VPREGEN, OnViewerVpregen)
  ON_COMMAND_RANGE(ID_2DWIREFRAME, ID_GOURAUD_SHADED_EDGES_ON, OnSetRenderMode)
  ON_COMMAND(ID_REFRESH, OnRefresh)
  ON_UPDATE_COMMAND_UI(ID_VIEWER_REGEN,   OnUpdateViewerRegen)
  ON_UPDATE_COMMAND_UI(ID_VIEWER_VPREGEN, OnUpdateViewerRegen)

  ON_UPDATE_COMMAND_UI(ID_2DWIREFRAME, OnUpdate2dwireframe)
  ON_UPDATE_COMMAND_UI(ID_3DWIREFRAME, OnUpdate3dwireframe)
  ON_UPDATE_COMMAND_UI(ID_HIDDEN, OnUpdateHidden)
  ON_UPDATE_COMMAND_UI(ID_FLAT_SHADED, OnUpdateFlatShaded)
  ON_UPDATE_COMMAND_UI(ID_FLAT_SHADED_WITH_EDGES, OnUpdateFlatShadedWithEdges)
  ON_UPDATE_COMMAND_UI(ID_GOURAUD_SHADED, OnUpdateGouraudShaded)
  ON_UPDATE_COMMAND_UI(ID_GOURAUD_SHADED_EDGES_ON, OnUpdateGouraudShadedEdgesOn)

  ON_REGISTERED_MESSAGE(g_nRedrawMSG, OnRedraw)
END_MESSAGE_MAP()

UINT OdaPrcExViewer::g_nRedrawMSG = 0;

void OdaPrcExViewer::exeCmd(const OdString& szCmdStr)
{
  GetDocument()->ExecuteCommand(szCmdStr);
  propagateActiveViewChanges(true);
}

void OdaPrcExViewer::OnInitialUpdate()
{
  CView::OnInitialUpdate();
  COdaPrcAppDoc* pDoc = static_cast<COdaPrcAppDoc*>(GetDocument());
  OdPrcFile* pDb = pDoc->m_pDb;

  OdGiContextForPrcDatabase::setDatabase(pDb);
  m_hWindowDC = ::GetDC(m_hWnd);

  if(!g_nRedrawMSG)
    g_nRedrawMSG = ::RegisterWindowMessage(_T("OdaMfcApp::CDwgViewer::WM_REDRAW"));

  createDevice();
  if(m_pDevice.isNull())
  {
    GetParent()->PostMessage(WM_CLOSE);
    return;
  }
  
  m_pEditor.initialize(m_pDevice, static_cast<COdaPrcAppDoc*>(GetDocument())->cmdCtx() );

  setCursor(::LoadCursor(0, IDC_ARROW));
}

void OdaPrcExViewer::initDatabase()
{
  COdaPrcAppDoc* pDoc = GetDocument();
  ODA_ASSERT(pDoc);
  m_pDb = pDoc->database();
}

void OdaPrcExViewer::initDC()
{
  m_hWindowDC = ::GetDC(m_hWnd);
}

COdaPrcAppDoc* OdaPrcExViewer::GetDocument() const
{
  ODA_ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COdaPrcAppDoc)));
  return (COdaPrcAppDoc*)m_pDocument;
}


void OdaPrcExViewer::OnMouseMove(UINT nFlags, CPoint point) 
{
  CView::OnMouseMove(nFlags, point);
  if(point!=m_oldPoint)
  {
    m_oldPoint = point;
    switch(m_mode)
    {
    //case kQuiescent:
    //  m_editor.OnMouseMove(nFlags, point.x, point.y);
    //  break;
    case kGetPoint:
      {
        OdGePoint3d pt = m_pEditor.toEyeToWorld(point.x, point.y);
        //if(!GETBIT(m_inpOptions, OdEd::kGptNoUCS))
        //{
        //  if(!m_pEditor.toUcsToWorld(pt))
        //    return;
        //}
        bool bRegen = false;
        //if(!GETBIT(m_inpOptions, OdEd::kGptNoOSnap))
        //{
        //  bRegen = m_editor.snap(pt, m_pBasePt);
        //}
        if(m_pTracker)
        {
          static_cast<OdEdPointTracker*>(m_pTracker)->setValue(pt);
        }
      }
      break;
    }
    //if(!getActiveView()->isValid() || !getActiveTopView()->isValid())
    if(!getActiveView()->isValid() || !getActiveView()->isValid())
    {
      //getActiveView()->invalidate();
      PostMessage(WM_PAINT);
    }
  }
}

void OdaPrcExViewer::OnLButtonDown(UINT nFlags, CPoint point) 
{
  CView::OnLButtonDown(nFlags, point);
  switch(m_mode)
  {
  //case kQuiescent:
  //  if(m_pEditor.OnMouseLeftButtonClick(nFlags, point.x, point.y, this))
  //  {
  //    PostMessage(WM_PAINT);
  //  }
  //  break;

  case kGetPoint:
    m_response.m_point = m_pEditor.toEyeToWorld(point.x, point.y);
    //if(!GETBIT(m_inpOptions, OdEd::kGptNoUCS))
    //{
    //  if(!m_editor.toUcsToWorld(m_response.m_point))
    //    break;
    //}
    //m_editor.snap(m_response.m_point, m_pBasePt);
    m_response.m_type = Response::kPoint;
    break;
  }
}

void OdaPrcExViewer::OnLButtonUp(UINT nFlags, CPoint point) 
{
  CView::OnLButtonUp(nFlags, point);
  if(m_mode==kGetPoint && GetCapture()==this)
  {
    m_response.m_point = m_pEditor.toEyeToWorld(point.x, point.y);
    //if(!GETBIT(m_inpOptions, OdEd::kGptNoUCS))
    //{
    //  if(!m_editor.toUcsToWorld(m_response.m_point))
    //    return;
    //}
    m_response.m_type = Response::kPoint;
    ReleaseCapture();
  }
  //Update_Entity_centers();                                 // guv: calculation m_centers for all entitys
}

void OdaPrcExViewer::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  switch( nChar ) 
  {
  case VK_ESCAPE:
    break;

  case VK_F5:
    PostMessage(WM_PAINT);
    break;

  case VK_DELETE:
    //((COdaPrcAppDoc*)GetDocument())->DeleteSelection(false);
    PostMessage(WM_PAINT);
    break;
  }

  CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void OdaPrcExViewer::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  CView::OnChar(nChar, nRepCnt, nFlags);
  m_response.m_string = m_inpars.result();
  switch(nChar)
  {
  case VK_BACK:
    while(nRepCnt--)
      m_inpars.eraseChar();
    break;

  case VK_ESCAPE:
    m_response.m_type = Response::kCancel;
    m_inpars.reset(false);

    switch(m_mode)
    {
    //case kQuiescent:
    //  if(m_pEditor.unselect())
    //    PostMessage(WM_PAINT);
    //  break;

    case kGetPoint:
      // no op
      break;
    }
    break;

  default:
    while(nRepCnt--)
    {
      if(!m_inpars.addChar((OdChar)nChar))
      {
        m_inpars.reset(false);
        switch(m_mode)
        {
        case kQuiescent:
          if(m_response.m_string.isEmpty())
            GetDocument()->ExecuteCommand(GetDocument()->recentCmdName());
          else
            GetDocument()->ExecuteCommand(m_response.m_string);
          break;

        case kGetPoint:
        case kGetString:
          m_response.m_type = Response::kString;
          break;
        }
      }
    }
    break;
  }

  if(m_pTracker && m_mode==kGetString &&
    m_response.m_type != Response::kString &&
    m_inpars.result() != (LPCTSTR)m_response.m_string)
  {
    static_cast<OdEdStringTracker*>(m_pTracker)->setValue(m_inpars.result());
    if(m_bTrackerHasDrawables)
    {
      getActiveView()->invalidate();
      //getActiveTopView()->invalidate();
      PostMessage(WM_PAINT);
    }
  }

  if(m_sPrompt.IsEmpty())
    m_sPrompt = _T("command: ");
  else if(m_inpars.result().isEmpty())
    theApp.setStatusText(m_sPrompt);
  else
    theApp.setStatusText(m_inpars.result());
}

afx_msg LRESULT OdaPrcExViewer::OnRedraw(WPARAM wParam, LPARAM lParam)
{
  CView::OnPaint();

  if (m_bInRegen)
    return 1;
  m_bInRegen = true;
  m_bRegenAbort = false;

  CMainFrame* pMainFrame = (CMainFrame*)theApp.GetMainWnd();
  //if(!regenAbort())
  {
    try
    {
      pMainFrame->StartTimer();
      if(m_pDevice.get())
      {
        //setViewportBorderProperties();

        m_pDevice->update();
      }
      //if(!regenAbort())
      {
        pMainFrame->StopTimer((m_paintMode == PaintMode_Regen) ? _T("Regen") : ((m_paintMode == PaintMode_Redraw)?_T("Redraw"):_T("Switch RenderMode")));
      }
    }
    catch(const OdError& e)
    {
      theApp.reportError(0, _T("Rendering aborted"), e);
      GetParent()->PostMessage(WM_CLOSE);
    }
    catch(const COdaPrcAppUserBreak&)
    {
      theApp.reportError(0, _T("Rendering aborted"), OdError(eUserBreak));
      GetParent()->PostMessage(WM_CLOSE);
    }
#ifndef _DEBUG
    catch(...)
    {
      theApp.reportError(0, _T("Rendering aborted"), OdError(_T("Unknown exception is caught...")));
      GetParent()->PostMessage(WM_CLOSE);
    }
#endif //#ifndef _DEBUG
  }

  m_bRegenAbort = false;
  m_bInRegen = false;
  m_paintMode = PaintMode_Redraw;
  return 1;
}

void OdaPrcExViewer::OnPaint() 
{
  m_bRegenAbort = true;

  //Process WM_PAINT;
  PAINTSTRUCT paintStruct;
  BeginPaint(&paintStruct);
  EndPaint(&paintStruct);

  MSG msg;
  while(::PeekMessage(&msg, NULL, g_nRedrawMSG, g_nRedrawMSG, PM_REMOVE))
  {
    ;
  }
  PostMessage(g_nRedrawMSG);
}

void OdaPrcExViewer::setViewportBorderProperties() 
{
  //TODO Sheets support
  /*OdGsViewPtr pOverallView = overallView(m_pDevice);
  OdGsViewPtr pActiveView = activeView(m_pDevice);

  int n = m_pDevice->numViews();
  if(n>1)
  {
    for(int i = 0; i<n; ++i)
    {
      OdGsViewPtr pView = m_pDevice->viewAt(i);
      if((pView==pOverallView) || (OdGsPaperLayoutHelper::cast(m_pDevice).get() && (pView!=pActiveView)))
      {
        // no border
        pView->setViewportBorderVisibility(false);
      }
      else if(pView!=pActiveView)
      {
        pView->setViewportBorderVisibility(true);
        pView->setViewportBorderProperties(theApp.curPalette()[7], 2);
      }
      else
      {
        pView->setViewportBorderVisibility(true);
        // pView->setViewportBorderProperties(theApp.curPalette()[7], 5); - GU: todo (won't work after move clear to view::update)
        pView->setViewportBorderProperties(theApp.curPalette()[7], 2);
      }
    }
  }*/
}

void OdaPrcExViewer::OnSize(UINT nType, int cx, int cy) 
{
  CView::OnSize(nType, cx, cy);
  if(cx && cy)
  {
    if(m_pDevice.get())
    {
      CRect rc;
      GetClientRect(rc);
      OdGsDCRect outputRect(OdGsDCPoint(rc.left, rc.bottom), OdGsDCPoint(rc.right, rc.top));
      m_pDevice->onSize(outputRect);
    }
  }
}

int OdaPrcExViewer::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CView::OnCreate(lpCreateStruct) == -1)
    return -1;
  ((CMainFrame*)theApp.GetMainWnd())->createViewerBar();
  return 0;
}

void OdaPrcExViewer::createDevice(bool bRecreate)
{
  CRect rc;
  GetClientRect(&rc);
  try
  {
    OdArray<OdGsViewPtr> m_prevViews;
    OdGsModelPtr m_pModel;

    if (!bRecreate)
    {
      OdGsModulePtr pGs = ::odrxDynamicLinker()->loadModule(theApp.settings().getGsDevicePath(), false);
      OdGsDevicePtr pDevice = pGs->createDevice();
      OdRxDictionaryPtr pProperties = pDevice->properties();
      if(pProperties.get())
      {
        if(pProperties->has(OD_T("WindowHWND"))) // Check if property is supported
          pProperties->putAt(OD_T("WindowHWND"), OdRxVariantValue((OdIntPtr)m_hWnd)); // hWnd necessary for DirectX device
        if(pProperties->has(OD_T("WindowHDC"))) // Check if property is supported
          pProperties->putAt(OD_T("WindowHDC"),  OdRxVariantValue((OdIntPtr)m_hWindowDC)); // hWindowDC necessary for Bitmap device
        if(pProperties->has(OD_T("DiscardBackFaces"))) // Check if property is supported
          pProperties->putAt(OD_T("DiscardBackFaces"), OdRxVariantValue(theApp.settings().discardBackFaces()));
      }

      enableGsModel(theApp.settings().useGsModel());

      m_pDevice = OdPrcGsManager::setupActiveLayoutViews(pDevice, this);
      m_pDevice->activeView()->setMode(OdGsView::kGouraudShaded);
    }
    else
    {
//       OdGsLayoutHelperPtr pDeviceIn = m_pDevice;
//       // Store current device views to keep cache alive
//       for (int nView = 0; nView < pDeviceIn->numViews(); nView++)
//         m_prevViews.append(pDeviceIn->viewAt(nView));
//       // Store current device Gs model
//       m_pModel = pDeviceIn->gsModel();
//       // Detach views from exist device
//       pDeviceIn->eraseAllViews();
//       // Create new helper for exist device
//       OdGsLayoutHelperPtr pDeviceOut = OdDbGsManager::setupActiveLayoutViews(pDeviceIn->underlyingDevice(), this);
//       // Release exist helper device
//       m_pDevice = pDeviceOut; // 1st release
//       pDeviceIn.release(); // 2nd release
//       m_editor.initialize(m_pDevice, static_cast<COdaMfcAppDoc*>(GetDocument())->cmdCtx()); // 3rd release
    }

    //m_layoutId = m_pDevice->layoutId();
    
    const ODCOLORREF* palette = theApp.curPalette();
    ODGSPALETTE pPalCpy;
    pPalCpy.insert(pPalCpy.begin(), palette, palette+256);
    pPalCpy[0] = theApp.settings().getActiveBackground();
    m_pDevice->setLogicalPalette(pPalCpy.asArrayPtr(), 256);
    //OdGsPaperLayoutHelperPtr pPSHelper = OdGsPaperLayoutHelper::cast(m_pDevice);
    //if(pPSHelper.isNull())
    {
//      m_bPsOverall = false;
      //m_pDevice->setBackgroundColor(ODRGB(64, 64, 64)); // for model space. Calculated from Adobe.
      m_pDevice->setBackgroundColor(pPalCpy[0]); // for model space. Calculated from Adobe.
    }
    //else
    //{
//      m_bPsOverall = (pPSHelper->overallView().get() == pPSHelper->activeView().get());
     // m_pDevice->setBackgroundColor(ODRGB(173,174,173)); // ACAD's color for paper bg
    //}    
//    setPaletteBackground(theApp.activeBackground());

    setViewportBorderProperties();

    OdGsDCRect  gsRect(rc.left, rc.right, rc.bottom, rc.top);
    m_pDevice->onSize(gsRect);

    OdPrcFilePtr pDb = getDatabase();
    pDb->applyCurrentView();

    // Adding plotstyletable info
//    preparePlotstyles(NULL, bRecreate);

    if (bRecreate)
    {
      // Call update to share cache from exist views
      m_pDevice->update();
      // Invalidate views for exist Gs model (i. e. remove unused drawables and mark view props as invalid)
      if (!m_pModel.isNull())
      {
        OdGsViewPtr *pViews = m_prevViews.asArrayPtr();
        OdUInt32 nViews = m_prevViews.size();
        for (OdUInt32 nView = 0; nView < nViews; nView++)
          m_pModel->invalidate(pViews[nView]);
      }
      // Release exist views to detach from Gs and keep released slots free.
      m_prevViews.clear();
    }
  }
  catch(const OdError& e)
  {
    destroyDevice();
    theApp.reportError(_T("Graphic System Initialization Error"), e);
  }  
}

void OdaPrcExViewer::destroyDevice() 
{
  m_pDevice.release();
}

void OdaPrcExViewer::OnDestroy() 
{
  COdaPrcAppDoc* pDoc = GetDocument();
  pDoc->OnCloseVectorizer(this);

  OdPrcFilePtr pDb = getDatabase();
  pDb->setActiveView(NULL);
  destroyDevice();

  ::ReleaseDC(m_hWnd, m_hWindowDC);
  m_hWindowDC = 0;
  CView::OnDestroy();

  ((CMainFrame*)theApp.GetMainWnd())->releaseViewerBar();
}

CRect OdaPrcExViewer::viewportRect() const
{
  CRect rc;
  GetClientRect(&rc);
  return rc;
}

CRect OdaPrcExViewer::viewRect(OdGsView* pView)
{
  OdGePoint3d ll, ur;
  pView->getViewport((OdGePoint2d&)ll, (OdGePoint2d&)ur);
  OdGeMatrix3d x = pView->screenMatrix();
  ll.transformBy(x);
  ur.transformBy(x);
  return CRect(OdRoundToLong(ll.x), OdRoundToLong(ur.y), OdRoundToLong(ur.x), OdRoundToLong(ll.y));
}

OdGiContextForPrcDatabasePtr OdaPrcExViewer::createDbContext()
{
  OdGiContextForPrcDatabasePtr pResult = OdGiContextForPrcDatabase::createObject();
  pResult->setDatabase(m_pDb);
  return pResult;
}

void OdaPrcExViewer::OnDraw(CDC* /*pDC*/)
{
}

BOOL OdaPrcExViewer::PreCreateWindow(CREATESTRUCT& cs)
{
  HCURSOR cursor = LoadCursor( NULL, IDC_CROSS );
  cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW|CS_OWNDC, cursor );
  return CView::PreCreateWindow(cs);
} 

void OdaPrcExViewer::zoom( double steps )
{
  OdGsView* view = getActiveView();
  
  view->zoom(pow(1.11, double(steps)));

  PostMessage( WM_PAINT );
}

OdGsView* OdaPrcExViewer::getActiveView() const
{
  if( !m_pDevice.isNull() )
  {
    return m_pDevice->activeView();
  }

  return 0;
}

OdGePoint3d OdaPrcExViewer::getWorldCoordinateByScreen( const OdGePoint2d& screenPoint ) const
{
  OdGsViewPtr view = getActiveView();

  //directions, origin, etc
  OdGePoint3d target = view->target();
  OdGeVector3d xVector, yVector;
  {
    OdGeVector3d direction = target - view->position();
    yVector = view->upVector();
    xVector = direction.crossProduct( yVector ).normal();
  }

  //the simplest way I found is to make back calculations...
  OdGePoint3d center, stepX, stepY;
  {
    center = target;
    stepX = target + xVector;
    stepY = target + yVector;

    OdGeMatrix3d matrix = view->worldToDeviceMatrix();
    stepX.transformBy( matrix );
    stepY.transformBy( matrix );
    center.transformBy( matrix );
  }

  //make the calculation
  OdGePoint3d result;
  {
    double x, y;
    x = ( screenPoint.x - center.x ) / ( stepX.x - center.x );
    y = ( screenPoint.y - center.y ) / ( stepY.y - center.y );

    result = target + xVector * x + yVector * y;
  }

  return result;
}

void OdaPrcExViewer::dolly(int x, int y) 
{
  OdGsView* pView = m_pDevice->activeView();
  OdGeVector3d vec(-x, -y, 0.0);
  vec.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
  pView->dolly(vec);
}

BOOL OdaPrcExViewer::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
  ScreenToClient(&pt);
  OdGsView* pView = m_pDevice->activeView();

  OdGePoint3d pos(pView->position());
  pos.transformBy(pView->worldToDeviceMatrix());
  // In 2d mode perspective zoom change lens length instead of fieldWidth/fieldHeight. This is non-standart
  // mode. Practically 2d mode can't be perspective.
  if (pView->isPerspective() && pView->mode() == OdGsView::k2DOptimized)
    pos = OdGePoint3d(0.5, 0.5, 0.0).transformBy(pView->screenMatrix());
  int vx, vy;
  vx = (int)OdRound(pos.x);
  vy = (int)OdRound(pos.y);
  vx = pt.x - vx;
  vy = pt.y - vy;
  dolly(-vx, -vy);
  pView->zoom(zDelta > 0 ? 1./.9 : .9);
  dolly(vx, vy);

  PostMessage(WM_PAINT);
  propagateActiveViewChanges();

  return CView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL OdaPrcExViewer::OnIdle(LONG lCount)
{
  if(!m_pDevice->isValid())
    PostMessage(WM_PAINT);
  return TRUE;
}

void OdaPrcExViewer::OnViewerRegen() 
{
  m_pDevice->invalidate();
  if(m_pDevice->gsModel())
    m_pDevice->gsModel()->invalidate(OdGsModel::kInvalidateAll);
  m_paintMode = PaintMode_Regen;
  PostMessage(WM_PAINT);
}

void OdaPrcExViewer::OnViewerVpregen()
{
  m_pDevice->invalidate();
  if (m_pDevice->gsModel())
    m_pDevice->gsModel()->invalidate(getActiveView());
  m_paintMode = PaintMode_Regen;
  PostMessage(WM_PAINT);
}


struct OdExRegenCmd : OdEdCommand
{
 // OdGsLayoutHelper* m_pDevice;
  OdaPrcExViewer* m_pView;
  const OdString groupName() const { return L"REGEN"; }
  const OdString globalName() const { return L"REGEN"; }
  virtual OdInt32 flags() const
  {
    return OdEdCommand::flags() | OdEdCommand::kNoUndoMarker;
  }
  void execute(OdEdCommandContext* pCmdCtx)
  {
    m_pView->OnViewerRegen();
  }
};

OdEdCommandPtr OdaPrcExViewer::command(const OdString& commandName)
{
  if (commandName.iCompare(L"REGEN") == 0)
  {
    OdSmartPtr<OdExRegenCmd> c = OdRxObjectImpl<OdExRegenCmd>::createObject();
    c->m_pView   = this;
    //c->m_pDevice = m_pDevice;
    return c;
 }
  else
    return m_pEditor.command(commandName);
}

void OdaPrcExViewer::putString(const OdString& string)
{
  m_sPrompt = (LPCTSTR)string;
  int n = m_sPrompt.ReverseFind('\n');
  if (n >= 0)
  {
    theApp.setStatusText(((LPCTSTR)m_sPrompt) + n + 1);
  }
  else
    theApp.setStatusText(m_sPrompt);
}

HCURSOR OdaPrcExViewer::cursor() const
{
  return m_hCursor;
}

void OdaPrcExViewer::setCursor(HCURSOR hCursor)
{
  m_hCursor = hCursor;
  ::SetCursor(hCursor);
}

void OdaPrcExViewer::track(OdEdInputTracker* pTracker)
{
  if(m_pTracker)
    m_pTracker->removeDrawables(getActiveView());
    //m_pTracker->removeDrawables(getActiveTopView()); TD

  m_pTracker = pTracker;

  m_pBasePt = 0;
  if(pTracker)
  {
    //m_bTrackerHasDrawables = pTracker->addDrawables(getActiveTopView())!=0; TD
    m_bTrackerHasDrawables = pTracker->addDrawables(getActiveView())!=0;
    OdEdPointDefTrackerPtr pPointDefTracker = OdEdPointDefTracker::cast(m_pTracker);
    if(pPointDefTracker.get())
    {
      m_basePt = pPointDefTracker->basePoint();
      m_pBasePt = &m_basePt;
    }
  }
  else
    m_bTrackerHasDrawables = false;
}

class SaveViewParams
{
  OdaPrcExViewer*   m_pView;
  HCURSOR       m_hOldCursor;
public:
  SaveViewParams(OdaPrcExViewer* pView, OdEdInputTracker* pTracker, HCURSOR hCursor)
    : m_pView(pView)
    , m_hOldCursor(pView->cursor())
  {
    pView->track(pTracker);
    pView->setCursor(hCursor);
    //pView->m_editor.initSnapping(pView->getActiveTopView());
  }
  ~SaveViewParams()
  {
    m_pView->track(0);
    m_pView->setCursor(m_hOldCursor);
    //m_pView->m_editor.uninitSnapping(m_pView->getActiveTopView());
  }
};

OdString OdaPrcExViewer::getString(const OdString& prompt, int options, OdEdStringTracker* pTracker)
{
  m_sPrompt.Empty();
  OdSaveState<CString> savePrompt(m_sPrompt);
  putString(prompt);

  OdSaveState<Mode>     saved_m_mode(m_mode, kGetString);

  m_response.m_type = Response::kNone;

  if (pTracker)
    m_inpars.reset(true);                     // guv: allowSpaces in OdString

  m_inpOptions = options;

  SaveViewParams svp(this, pTracker, ::LoadCursor(0, IDC_IBEAM));

  while ( theApp.PumpMessage() )
  {
    switch(m_response.m_type)
    {
    case Response::kString:
      return m_response.m_string;

    case Response::kCancel:
      throw OdEdCancel();
      break;
    }
    // Mfc idle loop for toolbars and menus process
    LONG lIdle = 0;
    while (theApp.OnIdle(lIdle++)) ;  
  }

  throw OdEdCancel();
}

OdGePoint3d OdaPrcExViewer::getPoint(const OdString& prompt, int options, OdEdPointTracker* pTracker)
{
  m_sPrompt.Empty();
  OdSaveState<CString> savePrompt(m_sPrompt);
  putString(prompt);

  OdSaveState<Mode>     saved_m_mode(m_mode, kGetPoint);

  m_response.m_type = Response::kNone;

  m_inpOptions = options;

  SaveViewParams svp(this, pTracker, ::LoadCursor(0, IDC_CROSS));

  while ( theApp.PumpMessage() )
  {
    switch(m_response.m_type)
    {
    case Response::kPoint:
      if(GETBIT(m_inpOptions, OdEd::kGptBeginDrag))
        SetCapture();
      return m_response.m_point;

    case Response::kString:
      throw OdEdOtherInput(m_response.m_string);

    case Response::kCancel:
      throw OdEdCancel();
    }
    // Mfc idle loop for toolbars and menus process
    LONG lIdle = 0;
    while (theApp.OnIdle(lIdle++)) ;  
  }

  throw OdEdCancel();
}

bool OdaPrcExViewer::canClose() const
{
  if(m_mode != kQuiescent)
  {
    AfxMessageBox(_T("Can not exit while command is active."), MB_OK|MB_ICONEXCLAMATION);
    return false;
  }
  return true;
}

void OdaPrcExViewer::respond(const OdString& s)
{
  m_response.m_type = Response::kString;
  m_response.m_string = s;
}

//-------------------------------------------------------------------------------------------------------------------------------------------
// Blink cursor timer

BOOL OdaPrcExViewer::UpdateStringTrackerCursor(void)
{
  if (m_pTracker && m_mode==kGetString &&
    m_response.m_type != Response::kString)
  {
    static_cast<OdEdStringTracker*>(m_pTracker)->setValue(m_inpars.result());

    if(m_bTrackerHasDrawables)
    {
      //getActiveTopView()->invalidate();
      getActiveView()->invalidate();
      PostMessage(WM_PAINT);
      return TRUE;
    }
  }
  return FALSE;
}

void CALLBACK StringTrackerTimer(HWND hWnd, UINT nMsg, UINT nIDTimer, DWORD dwTime)
{
  try
  {
    OdaPrcExViewer* pViewer = (OdaPrcExViewer*)CWnd::FromHandle(hWnd);

    if (!pViewer->UpdateStringTrackerCursor())
      KillTimer(hWnd, nIDTimer);
  }
  catch(...)
  {
    KillTimer(hWnd, nIDTimer);
  }
}

void OdaPrcExViewer::OnView3dorbit() 
{
  exeCmd( OD_T("3dorbit ") );
}

void OdaPrcExViewer::OnDrag() 
{
  exeCmd( OD_T("dolly ") );
}

void OdaPrcExViewer::OnViewZoomWindow() 
{
  exeCmd( OD_T("zoom w ") );
}

void OdaPrcExViewer::OnViewZoomextents() 
{
  exeCmd( OD_T("zoom e ") );
}

void OdaPrcExViewer::OnViewZoomin() 
{
  exeCmd( OD_T("zoom 2x ") );
}

void OdaPrcExViewer::OnViewZoomout() 
{
  exeCmd( OD_T("zoom .5x ") );
}

void OdaPrcExViewer::OnUpdate2dwireframe(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(getActiveView()->mode() == OdGsView::k2DOptimized);
}

void OdaPrcExViewer::OnUpdate3dwireframe(CCmdUI* pCmdUI) 
{
  //pCmdUI->Enable(!m_bPsOverall);  
  pCmdUI->SetCheck(getActiveView()->mode() == OdGsView::kWireframe);
}

void OdaPrcExViewer::OnUpdateHidden(CCmdUI* pCmdUI)
{
  //pCmdUI->Enable(!m_bPsOverall);  
  pCmdUI->SetCheck(getActiveView()->mode() == OdGsView::kHiddenLine);
}

void OdaPrcExViewer::OnUpdateFlatShaded(CCmdUI* pCmdUI)
{
  //pCmdUI->Enable(!m_bPsOverall);  
  pCmdUI->SetCheck(getActiveView()->mode() == OdGsView::kFlatShaded);
}

void OdaPrcExViewer::OnUpdateFlatShadedWithEdges(CCmdUI* pCmdUI)
{
  //pCmdUI->Enable(!m_bPsOverall);  
  pCmdUI->SetCheck(getActiveView()->mode() == OdGsView::kFlatShadedWithWireframe);
}

void OdaPrcExViewer::OnUpdateGouraudShaded(CCmdUI* pCmdUI)
{
  //pCmdUI->Enable(!m_bPsOverall);  
  pCmdUI->SetCheck(getActiveView()->mode() == OdGsView::kGouraudShaded);
}

void OdaPrcExViewer::OnUpdateGouraudShadedEdgesOn(CCmdUI* pCmdUI)
{
  //pCmdUI->Enable(!m_bPsOverall);  
  pCmdUI->SetCheck(getActiveView()->mode() == OdGsView::kGouraudShadedWithWireframe);
}


void OdaPrcExViewer::OnUpdateViewerRegen(CCmdUI* pCmdUI)
{
  //pCmdUI->Enable(m_pDevice->gsModel() != 0);
}

void OdaPrcExViewer::OnSetRenderMode(UINT nID)
{
  ODA_ASSUME( (ID_2DWIREFRAME - ID_2DWIREFRAME) == OdGsView::k2DOptimized &&
              (ID_3DWIREFRAME - ID_2DWIREFRAME) == OdGsView::kWireframe &&
              (ID_HIDDEN - ID_2DWIREFRAME) == OdGsView::kHiddenLine &&
              (ID_FLAT_SHADED - ID_2DWIREFRAME) == OdGsView::kFlatShaded &&
              (ID_GOURAUD_SHADED - ID_2DWIREFRAME) == OdGsView::kGouraudShaded &&
              (ID_FLAT_SHADED_WITH_EDGES - ID_2DWIREFRAME) == OdGsView::kFlatShadedWithWireframe &&
              (ID_GOURAUD_SHADED_EDGES_ON - ID_2DWIREFRAME) == OdGsView::kGouraudShadedWithWireframe);

  OdGsView::RenderMode rm = OdGsView::RenderMode(OdGsView::k2DOptimized + (nID - ID_2DWIREFRAME));
  OdGsView* pView = getActiveView();
  if (pView->mode() != rm)
  {
    pView->setMode(rm);
    if (pView->mode() != rm)
    {
      theApp.messageBox(m_hWnd, _T("Rendering"), _T("Mode is not supported by current device."), MB_ICONWARNING);
    }
    else
    {
      m_paintMode = Switch_RenderMode;
      m_pDevice->invalidate();
      PostMessage(WM_PAINT);
    }
    propagateActiveViewChanges();
  }
}

void OdaPrcExViewer::OnRefresh()
{
  PostMessage(WM_PAINT);
}

BOOL OdaPrcExViewer::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
  ::SetCursor(m_hCursor);
  return true;
}

void OdaPrcExViewer::propagateActiveViewChanges(bool bForceAutoRegen) const
{
  //TODO
  // @@@ probably move this functionality into GsLayoutHelper's?
  /*OdGsViewPtr pView = getActiveView();
  OdGsClientViewInfo viewInfo;
  pView->clientViewInfo(viewInfo);
  OdRxObjectPtr pObj = OdPrcObjectId(viewInfo.viewportObjectId).openObject(kForWrite);
  OdAbstractViewPEPtr pVp(pObj);

  if (!pVp.isNull())
  {
    OdGePoint3d ptTarget(pView->target());
    OdGeVector3d vecDir(pView->position() - ptTarget);
    OdGeVector3d vecUp(pView->upVector());
    double dFieldWidth = pView->fieldWidth(), dFieldHeight = pView->fieldHeight();
    bool bPersp = pView->isPerspective();
    double dLensLength = pView->lensLength();
    if (vecDir.isZeroLength())
    {
      vecDir = pView->viewingMatrix().inverse().getCsZAxis();
      if (vecDir.isZeroLength())
        vecDir = OdGeVector3d::kZAxis;
      else
        vecDir.normalize();
    }
    if (!pVp->target(pObj).isEqualTo(ptTarget) ||
      !pVp->direction(pObj).isEqualTo(vecDir) ||
      !pVp->upVector(pObj).isEqualTo(vecUp) ||
      !OdEqual(pVp->fieldWidth(pObj), dFieldWidth) || !OdEqual(pVp->fieldHeight(pObj), dFieldHeight) ||
      pVp->isPerspective(pObj) != bPersp || !OdEqual(pVp->lensLength(pObj), dLensLength) || bForceAutoRegen)
    {
      OdGeVector2d viewOffset;
      if (pVp->direction(pObj).isEqualTo(vecDir) &&
        pVp->upVector(pObj).isEqualTo(vecUp) &&
        !bPersp && !pVp->isPerspective(pObj))
      {
        OdGeVector3d vecX = vecUp.crossProduct(vecDir).normal();
        viewOffset = pVp->viewOffset(pObj);
        OdGePoint3d prevTarg = pVp->target(pObj) - vecX * viewOffset.x - vecUp * viewOffset.y;
        viewOffset.x = vecX.dotProduct(ptTarget - prevTarg);
        viewOffset.y = vecUp.dotProduct(ptTarget - prevTarg);
      }
      pVp->setView(pObj, ptTarget, vecDir, vecUp, dFieldWidth, dFieldHeight, bPersp, viewOffset);
      pVp->setLensLength(pObj, dLensLength);
      // Auto regen
      if (requireAutoRegen(pView))
        const_cast<CDwgViewer*>(this)->OnViewerRegen();
    }
    OdDb::RenderMode rm = OdDb::k2DOptimized;
    switch (pView->mode())
    {
    case OdGsView::kWireframe:
      rm = OdDb::kWireframe;
      break;
    case OdGsView::kHiddenLine:
      rm = OdDb::kHiddenLine;
      break;
    case OdGsView::kFlatShaded:
      rm = OdDb::kFlatShaded;
      break;
    case OdGsView::kGouraudShaded:
      rm = OdDb::kGouraudShaded;
      break;
    case OdGsView::kFlatShadedWithWireframe:
      rm = OdDb::kFlatShadedWithWireframe;
      break;
    case OdGsView::kGouraudShadedWithWireframe:
      rm = OdDb::kGouraudShadedWithWireframe;
      break;
    }
    if (pVp->renderMode(pObj) != rm)
      pVp->setRenderMode(pObj, rm);
    OdPrcObjectId vs(pView->visualStyle());
    if ((pVp->visualStyle(pObj) != vs) && !vs.isNull())
      pVp->setVisualStyle(pObj, pView->visualStyle());
  }*/
}

