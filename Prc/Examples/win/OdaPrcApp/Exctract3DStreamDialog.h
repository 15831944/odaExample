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

#if !defined(AFX_EXTRACTSTREAMDIALOG_H__4AF80B03_7FB7_42D3_9281_E8A5F4FB9A36__INCLUDED_)
#define AFX_EXTRACTSTREAMDIALOG_H__4AF80B03_7FB7_42D3_9281_E8A5F4FB9A36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Extract3DStreamDialog.h : header file
//

#include "afxwin.h"

#ifdef PDFIUM_MODULE_ENABLED
#include "Pdf3DStreamExtractor.h"

/////////////////////////////////////////////////////////////////////////////
// Extract3DStreamDialog dialog

class Extract3DStreamDialog : public CDialog
{
public:

 OdStreamBufPtr getStream();
 OdString       getStreamName();

private:
  OdPdf3DStreamExtractorPtr m_OdPdf3DStreamExtractor;

  CString             m_Path;
  CString             m_FileName;
  CListBox            m_PageList;
  CListCtrl           m_StreamList;
  CStatic             m_Preview;
  int                 m_CurPage;
  int                 m_CurStreamIdx;
  OdStreamBufPtr      m_Stream;

  int                 m_DialogHeight;//Initial height

// Construction

public:

    Extract3DStreamDialog(CWnd* pParent);   // standard constructor

// Dialog Data
  //{{AFX_DATA(Extract3DStreamDialog)
  enum { IDD = IDD_Extract3D };
  //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(Extract3DStreamDialog)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();
  afx_msg void OnSelchangePageList();
  afx_msg void OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(Extract3DStreamDialog)
  afx_msg void OnBrowse();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

  void updatePreview();
  bool InitProperties();
  void OnError(CString str);
  void OnError(OdResult res);
  void FillPageList();
  void FillStreamList();

public:
};

#endif //PDFIUM_MODULE_ENABLED

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTRACTSTREAMDIALOG_H__4AF80B03_7FB7_42D3_9281_E8A5F4FB9A36__INCLUDED_)
