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
#if !defined(TEXT_EDITOR_INCLUDED_)
#define TEXT_EDITOR_INCLUDED_


// TextEditor dialog

class TextEditor : public CDialog
{
	DECLARE_DYNAMIC(TextEditor)
  OdString m_sText;
public:
	TextEditor(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TextEditor();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGBAR_TEXT_EDIT };
#endif

  void setText(const OdString& sText);
  OdString getText() const;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedButtonEditTextOk();
};
#endif

