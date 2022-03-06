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
#pragma once


// LayerStatesDialog dialog

class LayerStatesDialog : public CDialog
{
	DECLARE_DYNAMIC(LayerStatesDialog)
  OdDbDatabase* m_pDb;
public:
	LayerStatesDialog(OdDbDatabase*, CWnd* pParent = NULL);   // standard constructor
	virtual ~LayerStatesDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LAYER_STATES };
#endif

  virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedNew();
  afx_msg void OnBnClickedDelete();
  afx_msg void OnBnClickedUpdate();
  afx_msg void OnBnClickedExport();
  afx_msg void OnBnClickedImport();
  afx_msg void OnBnClickedRestore();
  afx_msg void OnBnClickedClose();
  CListCtrl m_List;
};
