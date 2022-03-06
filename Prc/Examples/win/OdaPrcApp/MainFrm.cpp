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
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "OdaPrcApp.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
  ON_WM_CREATE()
  ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
  ID_SEPARATOR,           // status line indicator
  0,
  0,
  ID_INDICATOR_CAPS,
  ID_INDICATOR_NUM,
  ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame() : m_pViewerBar(0)
{
  // TODO: add member initialization code here
  m_pc0.QuadPart = 0;
  m_pc0.QuadPart = 0;
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
  
  if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
    | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
    !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
  {
    TRACE0("Failed to create toolbar\n");
    return -1;      // fail to create
  }

  // TODO: Delete these three lines if you don't want the toolbar to be dockable
  m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
  EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_wndToolBar);

  if (!m_wndStatusBar.Create(this) ||
    !m_wndStatusBar.SetIndicators(indicators,
      sizeof(indicators)/sizeof(UINT)))
  {
    TRACE0("Failed to create status bar\n");
    return -1;      // fail to create
  }

  return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  if( !CMDIFrameWnd::PreCreateWindow(cs) )
    return FALSE;
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs

  return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
  CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
  CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

void CMainFrame::OnClose() 
{
  POSITION pos = theApp.GetFirstDocTemplatePosition();
  CDocTemplate* pDocTempl = theApp.GetNextDocTemplate(pos);
  pos = pDocTempl->GetFirstDocPosition();
  while(pos)
  {
    CDocument* pDoc = pDocTempl->GetNextDoc(pos);
    POSITION pos = pDoc->GetFirstViewPosition();
    while (pos)
    {
      if(!pDoc->CanCloseFrame(pDoc->GetNextView(pos)->GetParentFrame()))
        return;
    }
  }

  WINDOWPLACEMENT wp;
  GetWindowPlacement(&wp);

  theApp.WriteProfileInt(_T("MainFrame"), _T("flags"), wp.flags);
  theApp.WriteProfileInt(_T("MainFrame"), _T("showCmd"), wp.showCmd);
  theApp.WriteProfileInt(_T("MainFrame"), _T("left"),  wp.rcNormalPosition.left);
  theApp.WriteProfileInt(_T("MainFrame"), _T("top"),   wp.rcNormalPosition.top);
  theApp.WriteProfileInt(_T("MainFrame"), _T("bottom"),wp.rcNormalPosition.bottom);
  theApp.WriteProfileInt(_T("MainFrame"), _T("right"), wp.rcNormalPosition.right);

  theApp.WriteProfileInt(_T("MainFrame"), _T("Min.x"), wp.ptMinPosition.x);
  theApp.WriteProfileInt(_T("MainFrame"), _T("Min.y"), wp.ptMinPosition.y);

  theApp.WriteProfileInt(_T("MainFrame"), _T("Max.x"), wp.ptMaxPosition.x);
  theApp.WriteProfileInt(_T("MainFrame"), _T("Max.y"), wp.ptMaxPosition.y);

  CMDIFrameWnd::OnClose();
}

BOOL CMainFrame::ViewerBar::Create(CWnd* pParentWnd)
{
  UINT nStyle = theApp.GetProfileInt(_T("ViewerBar"), _T("style"),
    CBRS_TOP|CBRS_GRIPPER|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC);

  if (!CreateEx(pParentWnd, TBSTYLE_FLAT, WS_CHILD|WS_VISIBLE|nStyle ) ||
    !LoadToolBar(IDR_VIEWER))
  {
    TRACE0("Failed to create toolbar\n");
    return FALSE;
  }
  EnableDocking(CBRS_ALIGN_ANY);
  return TRUE;
}

void CMainFrame::createViewerBar()
{
  if(!m_pViewerBar)
  {
    m_pViewerBar = OdRxObjectImpl<ViewerBar>::createObject().detach();
    m_pViewerBar->Create(this);
    RECT rc;
    rc.left   = theApp.GetProfileInt(_T("ViewerBar"), _T("left"),   310);
    rc.right  = theApp.GetProfileInt(_T("ViewerBar"), _T("right"),  517);
    rc.top    = theApp.GetProfileInt(_T("ViewerBar"), _T("top"),    0);
    rc.bottom = theApp.GetProfileInt(_T("ViewerBar"), _T("bottom"), 26);
    ClientToScreen(&rc);
    DockControlBar(m_pViewerBar, UINT(0), rc.left!=rc.right && rc.top!=rc.bottom ? &rc : 0);
  }
  else
  {
    m_pViewerBar->addRef();
  }
}

void CMainFrame::releaseViewerBar()
{
  if(m_pViewerBar)
  {
    int n = m_pViewerBar->numRefs();
    if(n==1)
    {
      RECT rc;
      m_pViewerBar->GetWindowRect(&rc);
      ScreenToClient(&rc);
      theApp.WriteProfileInt(_T("ViewerBar"), _T("left"),  rc.left   );
      theApp.WriteProfileInt(_T("ViewerBar"), _T("right"), rc.right  );
      theApp.WriteProfileInt(_T("ViewerBar"), _T("top"),   rc.top    );
      theApp.WriteProfileInt(_T("ViewerBar"), _T("bottom"),rc.bottom );
      //      UINT nAlignMask = CBRS_LEFT|CBRS_TOP|CBRS_RIGHT|CBRS_BOTTOM;
      theApp.WriteProfileInt(_T("ViewerBar"), _T("style"), m_pViewerBar->GetBarStyle());
      m_pViewerBar->release();
      m_pViewerBar = 0;
    }
    else
    {
      m_pViewerBar->release();
    }
  }
}

// CMainFrame message handlers



