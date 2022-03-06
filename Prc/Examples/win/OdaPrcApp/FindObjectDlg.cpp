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
// FindObjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OdaPrcApp.h"
#include "FindObjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindObjectDlg dialog


CFindObjectDlg::CFindObjectDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CFindObjectDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CFindObjectDlg)
  m_objHandle = _T("");
  //}}AFX_DATA_INIT
}


void CFindObjectDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFindObjectDlg)
  DDX_Text(pDX, IDC_FIND_OBJECT, m_objHandle);
  DDV_MaxChars(pDX, m_objHandle, 16);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindObjectDlg, CDialog)
  //{{AFX_MSG_MAP(CFindObjectDlg)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindObjectDlg message handlers

BOOL CFindObjectDlg::OnInitDialog() 
{
  CDialog::OnInitDialog();
  GetDlgItem(IDC_FIND_OBJECT)->SetWindowText(theApp.GetProfileString(_T("options"), _T("handle to find"), _T("")));
  return FALSE;
}

BOOL CFindObjectDlg::DestroyWindow() 
{
  theApp.WriteProfileString(_T("options"), _T("handle to find"), m_objHandle);
  return CDialog::DestroyWindow();
}
