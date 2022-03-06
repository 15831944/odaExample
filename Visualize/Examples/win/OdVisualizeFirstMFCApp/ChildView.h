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

// ChildView.h : interface of the CChildView class
//


#pragma once

// ODA SDK
#include "OdaCommon.h"
#include "Rxinit.h"
// Visualize
#include "TvDatabase.h"
#include "TvFactory.h"
#include "TvError.h"
#include "OdModuleNames.h"
#include "RxDynamicModule.h"
#include "TvModuleNames.h"

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
  // fields for navigation
  enum NavigationCommands
  {
    kNone = 0,
    kPan = 1,
    kOrbit = 2
  };

  struct PanInfo
  {
    OdTvPoint curPos;
    OdTvPoint prevPos;
  };

  struct OrbitInfo
  {
    OdTvPoint prevPt;
    double delta;
    OdTvPoint viewCenter;
  };

	CChildView();

  // Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
  afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
  virtual void OnLButtonDown(UINT nFlags, CPoint point);
  virtual void OnLButtonUp(UINT nFlags, CPoint point);
  virtual void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
  BOOL PreTranslateMessage(MSG* pMsg);
public:
  afx_msg void OnFileOpen32771();
  afx_msg void OnFileGeneratesample();
  afx_msg void OnPanClick();
  afx_msg void OnOrbitClick();
  afx_msg void OnZoomExtCLick();

private:
  // oda activation
  void ODASdkActivate();
  void ODASdkDeactivate();
  void updateDevice();
  void clearData();
  bool generateSample();
  bool openFile();
  void processZoom(double delta);
  bool calculateViewExtents(OdGeBoundBlock3d& extents);
  void truncateHugeBelow(OdGePoint3d& pt);
  void truncateHugeAbove(OdGePoint3d& pt);
  void processZoomToExtents();
  OdTvPoint toEyeToWorld(int x, int y);
  void processPan(int x, int y);
  void processOrbit(int x, int y);
  void highlight(const OdTvSelectionSetPtr& pSSet, bool bDoIt);
  void processSelect(int x, int y);

private:
  OdTvDatabaseId m_dbId;
  OdTvGsDeviceId m_deviceId;
  OdTvGsViewId m_viewId;
  bool m_bIsLButtonDown;
  NavigationCommands m_navigationCommand;
  PanInfo m_panInfo;
  OrbitInfo m_orbitInfo;
  OdTvSelectionSetPtr m_pSSet;
};

