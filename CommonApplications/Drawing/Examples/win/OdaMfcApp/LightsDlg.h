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

#if !defined(AFX_LIGHTSDLG_H__BE71D082_70C8_4970_A251_6C8CC2B8D78A__INCLUDED_)
#define AFX_LIGHTSDLG_H__BE71D082_70C8_4970_A251_6C8CC2B8D78A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLightsDlg dialog

class CLightsDlg : public CDialog
{
// Construction
public:
	CLightsDlg(OdDbDatabase* pDb, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLightsDlg)
	enum { IDD = IDD_RENDER_LIGHTS };
	CListCtrl	m_LightsList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLightsDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
  OdDbDatabase* m_pDb;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTSDLG_H__BE71D082_70C8_4970_A251_6C8CC2B8D78A__INCLUDED_)
