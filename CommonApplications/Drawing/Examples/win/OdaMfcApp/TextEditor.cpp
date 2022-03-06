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
// TextEditor.cpp : implementation file
//

#include "stdafx.h"
#include "odamfcapp.h"
#include "TextEditor.h"


// TextEditor dialog

IMPLEMENT_DYNAMIC(TextEditor, CDialog)

TextEditor::TextEditor(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOGBAR_TEXT_EDIT, pParent)
{

}

TextEditor::~TextEditor()
{
}

void TextEditor::setText(const OdString& sText)
{
  m_sText = sText;
}

OdString TextEditor::getText() const
{
  return m_sText;
}

BOOL TextEditor::OnInitDialog()
{
  CDialog::OnInitDialog();
  HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
  SetIcon(hIcon, FALSE);
  CEdit* editBox = (CEdit *)GetDlgItem(IDC_EDIT_TEXT);
  editBox->SetWindowTextW(m_sText);
  CPoint pt;
  GetCursorPos(&pt);
  SetWindowPos(NULL, pt.x, pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
  return TRUE;
}

void TextEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TextEditor, CDialog)
  ON_BN_CLICKED(IDC_BUTTON_EDIT_TEXT_OK, &TextEditor::OnBnClickedButtonEditTextOk)
END_MESSAGE_MAP()


// TextEditor message handlers


void TextEditor::OnBnClickedButtonEditTextOk()
{
  CString text;
  CEdit* editBox = (CEdit *)GetDlgItem(IDC_EDIT_TEXT);
  editBox->GetWindowTextW(text);
  m_sText = text;
  EndDialog(1);
}
