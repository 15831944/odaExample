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

//
// CPDFSecurityOptionsDialog.h : header file
//
#include "resource.h"

#include "PdfExportParams.h"


#ifndef PDF_SECURITY_DLG_DEFINED
#define PDF_SECURITY_DLG_DEFINED

class CPDFSecurityOptionsDialog : public CDialog
{
  CString       m_sUserPassword;
  CString       m_sOwnerPassword;

  BOOL          m_bAllowExtract;
  BOOL          m_bAllowAssemble;
  BOOL          m_bAllowAnnotateAndForm;
  BOOL          m_bAllowFormFilling;
  BOOL          m_bAllowModifyOther;
  BOOL          m_bAllowPrintAll;
  BOOL          m_bAllowPrintLow;

  OdString& m_UserPassword;
  OdString& m_OwnerPassword;
  TD_PDF_2D_EXPORT::PDFExportParams::PDFAccessPermissionsFlags& m_AccessPermissionFlags;

public:
  CPDFSecurityOptionsDialog(OdString& UserPassword, OdString& OwnerPassword, 
    TD_PDF_2D_EXPORT::PDFExportParams::PDFAccessPermissionsFlags& AccessPermissionFlags, CWnd* pParent = NULL); //constructor
	virtual ~CPDFSecurityOptionsDialog();

// Dialog Data
  enum { IDD = IDD_PDF_SECURITY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();
  afx_msg void OnOk();

	DECLARE_MESSAGE_MAP()
};

#endif //PDF_SECURITY_DLG_DEFINED
