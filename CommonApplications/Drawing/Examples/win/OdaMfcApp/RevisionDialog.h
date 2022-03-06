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
#include "afxcmn.h"
#include "afxwin.h"
#include "Tf/TfRevisionControl.h"


// CRevisionDialog dialog

class CRevisionDialog : public CDialog
{
	DECLARE_DYNAMIC(CRevisionDialog)
  OdArray<OdTfCommitInfo> commitList;
public:
	CRevisionDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRevisionDialog();
  OdDbDatabasePtr m_pDb;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REVISIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  CListCtrl m_LogList;
  CEdit m_LogMessage;
  afx_msg void OnLvnItemchangedListLog(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnNMDblclkListLog(NMHDR *pNMHDR, LRESULT *pResult);
};
