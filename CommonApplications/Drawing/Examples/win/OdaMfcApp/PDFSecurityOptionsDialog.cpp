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

// CPDFSecurityOptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PDFSecurityOptionsDialog.h"

using namespace TD_PDF_2D_EXPORT;

CPDFSecurityOptionsDialog::CPDFSecurityOptionsDialog(OdString& UserPassword, OdString& OwnerPassword,
  PDFExportParams::PDFAccessPermissionsFlags& AccessPermissionFlags, CWnd* pParent /*=NULL*/)
  : CDialog(CPDFSecurityOptionsDialog::IDD, pParent)
  , m_UserPassword(UserPassword)
  , m_OwnerPassword(OwnerPassword)
  , m_AccessPermissionFlags(AccessPermissionFlags)
{
  m_sUserPassword = m_UserPassword.c_str();
  m_sOwnerPassword = m_OwnerPassword.c_str();

  m_bAllowExtract = GETBIT(m_AccessPermissionFlags, PDFExportParams::kAllowExtract);
  m_bAllowAssemble = GETBIT(m_AccessPermissionFlags, PDFExportParams::kAllowAssemble);
  m_bAllowAnnotateAndForm = GETBIT(m_AccessPermissionFlags, PDFExportParams::kAllowAnnotateAndForm);
  m_bAllowFormFilling = GETBIT(m_AccessPermissionFlags, PDFExportParams::kAllowFormFilling);
  m_bAllowModifyOther = GETBIT(m_AccessPermissionFlags, PDFExportParams::kAllowModifyOther);
  m_bAllowPrintAll = GETBIT(m_AccessPermissionFlags, PDFExportParams::kAllowPrintAll);
  m_bAllowPrintLow = GETBIT(m_AccessPermissionFlags, PDFExportParams::kAllowPrintLow);
}

CPDFSecurityOptionsDialog::~CPDFSecurityOptionsDialog()
{
}

void CPDFSecurityOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

  DDX_Text(pDX, IDC_EDIT_USER_PASSWORD, m_sUserPassword);
  DDX_Text(pDX, IDC_EDIT_OWNER_PASSWORD, m_sOwnerPassword);

  DDX_Check(pDX, IDC_PDF_SC_ALLOW_EXTRACT, m_bAllowExtract);
  DDX_Check(pDX, IDC_PDF_SC_ALLOW_ASSEMBLE, m_bAllowAssemble);
  DDX_Check(pDX, IDC_PDF_SC_ALLOW_ANNOTATE, m_bAllowAnnotateAndForm);
  DDX_Check(pDX, IDC_PDF_SC_ALLOW_FORM_FILL, m_bAllowFormFilling);
  DDX_Check(pDX, IDC_PDF_SC_ALLOW_MODIFY, m_bAllowModifyOther);
  DDX_Check(pDX, IDC_PDF_SC_ALLOW_PRINT_ALL, m_bAllowPrintAll);
  DDX_Check(pDX, IDC_PDF_SC_ALLOW_PRINT_LOW, m_bAllowPrintLow);
}


BEGIN_MESSAGE_MAP(CPDFSecurityOptionsDialog, CDialog)
  ON_BN_CLICKED(IDOK, OnOk)
END_MESSAGE_MAP()


// CPDFSecurityOptionsDialog message handlers
BOOL CPDFSecurityOptionsDialog::OnInitDialog()
{
  if (!CDialog::OnInitDialog())
    return FALSE;
  UpdateData(FALSE);
  return TRUE;
}

void CPDFSecurityOptionsDialog::OnOk()
{
  UpdateData(TRUE);

  m_UserPassword = m_sUserPassword;
  m_OwnerPassword = m_sOwnerPassword;

  m_bAllowExtract = GETBIT(m_AccessPermissionFlags, PDFExportParams::kAllowExtract);


  unsigned int tmp_flag = m_AccessPermissionFlags;

  SETBIT(tmp_flag, PDFExportParams::kAllowExtract, m_bAllowExtract);
  SETBIT(tmp_flag, PDFExportParams::kAllowAssemble, m_bAllowAssemble);
  SETBIT(tmp_flag, PDFExportParams::kAllowAnnotateAndForm, m_bAllowAnnotateAndForm);
  SETBIT(tmp_flag, PDFExportParams::kAllowFormFilling, m_bAllowFormFilling);
  SETBIT(tmp_flag, PDFExportParams::kAllowModifyOther, m_bAllowModifyOther);
  SETBIT(tmp_flag, PDFExportParams::kAllowPrintAll, m_bAllowPrintAll);
  SETBIT(tmp_flag, PDFExportParams::kAllowPrintLow, m_bAllowPrintLow);

  m_AccessPermissionFlags = (PDFExportParams::PDFAccessPermissionsFlags)tmp_flag;

  CDialog::OnOK();
  
}
