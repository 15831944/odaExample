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

#ifndef _AFX_ODAPRCEXVIEWER__INCLUDED_
#define _AFX_ODAPRCEXVIEWER__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ge/GeMatrix3d.h"
#include "Gi/Gi.h"
#include "GiGs/PrcGiContext.h"
#include <afxole.h>
#include "ExPrcCommandContext.h"
#include "Ed/EdCommandStack.h"
#include "ExEdInputParser.h"
#include "ExPrcEditorObject.h"
#include "GiGs/PrcGsManager.h"

class COdaPrcAppDoc;

class OdaPrcExViewer : public CView
                     , public OdGiContextForPrcDatabase
{
  ExEdInputParser   m_inpars;

  static UINT       g_nRedrawMSG;
  mutable bool      m_bRegenAbort;
  mutable bool      m_bInRegen; // flag to avoid reentrancy in regen, if new redraw message is received while regen is incomplete (e.g. when assert pops up)
  enum PaintMode {
    PaintMode_Redraw,
    PaintMode_Regen,
    Switch_RenderMode
  }                 m_paintMode;
  enum Mode
  {
    kQuiescent,
    kGetPoint,
    kGetString,
    kDragDrop
  }
  m_mode;

  struct Response
  {
  public:
    enum Type
    {
      kNone,
      kPoint,
      kString,
      kCancel
    };
    Type            m_type;
    OdGePoint3d     m_point;
    OdString        m_string;
  };
  Response          m_response;
  CPoint            m_oldPoint;

  void exeCmd(const OdString& szCmdStr);
  void destroyDevice();

  OdEdInputTracker* m_pTracker;
protected:
  using CView::operator new;
  using CView::operator delete;

  OdaPrcExViewer();
  virtual ~OdaPrcExViewer();

  DECLARE_MESSAGE_MAP()
  DECLARE_DYNCREATE(OdaPrcExViewer);

  afx_msg void OnPaint();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnDestroy();
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
  afx_msg void OnViewerRegen();
  afx_msg void OnViewZoomextents();

protected:
  afx_msg void OnView3dorbit();
  afx_msg void OnDrag();
  afx_msg void OnViewZoomWindow();
  afx_msg void OnViewZoomin();
  afx_msg void OnViewZoomout();
  afx_msg LRESULT OnRedraw(WPARAM wParam, LPARAM lParam);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnViewerVpregen();
  afx_msg void OnUpdateViewerRegen(CCmdUI* pCmdUI);
  afx_msg void OnUpdate2dwireframe(CCmdUI* pCmdUI);
  afx_msg void OnUpdate3dwireframe(CCmdUI* pCmdUI);
  afx_msg void OnUpdateHidden(CCmdUI* pCmdUI);
  afx_msg void OnUpdateFlatShaded(CCmdUI* pCmdUI);
  afx_msg void OnUpdateFlatShadedWithEdges(CCmdUI* pCmdUI);
  afx_msg void OnUpdateGouraudShaded(CCmdUI* pCmdUI);
  afx_msg void OnUpdateGouraudShadedEdgesOn(CCmdUI* pCmdUI);

  afx_msg void OnSetRenderMode(UINT nID);
  afx_msg void OnRefresh();

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  COdaPrcAppDoc* GetDocument() const;
  CRect viewportRect() const;
  static CRect viewRect(OdGsView*);

  void initDatabase();
  void initDC();
  void initDevice();
  OdGiContextForPrcDatabasePtr createDbContext();
  void zoom(double steps);
  void dolly(int x, int y);
  OdGePoint3d getWorldCoordinateByScreen(const OdGePoint2d& screenPoint) const;

public:
  bool canClose() const;
protected:
  OdExPrcEditorObject      m_pEditor;
  OdGsPrcLayoutHelperPtr   m_pDevice;
  OdPrcFilePtr             m_pDb;
  HDC                      m_hWindowDC;
  CString                  m_sPrompt;
  HCURSOR                  m_hCursor;
  int                      m_inpOptions;
  bool                     m_bTrackerHasDrawables;

  OdGePoint3d              m_basePt;
  const OdGePoint3d*       m_pBasePt;

  void createDevice(bool bRecreate = false);
public:
  OdGsView* getActiveView() const;
  virtual void OnDraw(CDC* pDC);
  virtual void OnInitialUpdate();

  // Implementation
  void addRef() {}
  void release() {}

  BOOL OnIdle(LONG lCount);

  void propagateActiveViewChanges(bool bForceAutoRegen = false) const;

  OdEdCommandPtr command(const OdString& commandName);

  OdGePoint3d getPoint(const OdString& prompt, int options, OdEdPointTracker* pTracker);
  OdString getString(const OdString& prompt, int options, OdEdStringTracker* pTracker);
  void putString(const OdString& string);
  bool isGettingString() const { return m_mode!= kQuiescent; }
  OdString prompt() const { return (LPCTSTR)m_sPrompt; }
  int inpOptions() const { return m_inpOptions; }
  void respond(const OdString& s);

  BOOL UpdateStringTrackerCursor(void);

  void track(OdEdInputTracker* pTracker);
  void setCursor(HCURSOR hCursor);
  HCURSOR cursor() const;

  void setViewportBorderProperties();
};

/////////////////////////////////////////////////////////////////////////////
#endif // _AFX_ODAPRCEXVIEWER__INCLUDED_
