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


// DecompressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OdaPrcApp.h"
#include "DecompressDlg.h"
#include "OdaPrcAppDoc.h"

#include "Ge/GeBoundBlock3d.h"
#include "Gs/GsModel.h"


// DecompressDlg dialog

IMPLEMENT_DYNAMIC(DecompressDlg, CDialog)

DecompressDlg::DecompressDlg(COdaPrcTreeView * pPrcTreeView, CWnd* pParent /*=NULL*/)
	: CDialog(DecompressDlg::IDD, pParent), m_pPrcTreeView(pPrcTreeView), m_bIsFileUpdated(false)
{
}

DecompressDlg::~DecompressDlg()
{
}

void DecompressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL DecompressDlg::OnInitDialog()
{
  CButton * m_checkBoxBrep = (CButton*) GetDlgItem(IDC_CHECK_BREP_DECOMPRESSION);
  m_checkBoxBrep->SetCheck(BST_CHECKED);
  CButton *m_checkBoxTess = (CButton*) GetDlgItem(IDC_CHECK_TESS_DECOMPRESSION);
  m_checkBoxTess->SetCheck(BST_CHECKED);

  Decompress3dTessParams params;
  CButton *m_checkBoxTessStoreNormals = (CButton*)GetDlgItem(IDC_CHECK_TESS_STORE_NORMALS);
  m_checkBoxTessStoreNormals->SetCheck(params.bStoreNormals ? BST_CHECKED : BST_UNCHECKED);
  CButton *m_checkBoxTessOverwriteCreaseAngle = (CButton*)GetDlgItem(IDC_CHECK_TESS_OVERWRITE_CREASE_ANGLE);
  m_checkBoxTessOverwriteCreaseAngle->SetCheck(params.bOverwriteCreaseAngle ? BST_CHECKED : BST_UNCHECKED);
  SetDlgItemText(IDC_CREASE_ANGLE_VALUE, odDToStr(params.dCreaseAngle, 'g', 8).c_str());
  return TRUE;
}

BEGIN_MESSAGE_MAP(DecompressDlg, CDialog)
  ON_BN_CLICKED(IDOK, &DecompressDlg::OnBnClickedOk)
END_MESSAGE_MAP()

static bool preValidate(const OdString &pStr, const OdChar *syms)
{
  const OdChar *pIn = pStr.c_str();
  while (*pIn)
  {
    const OdChar *pOp = syms;
    while (*pOp)
    {
      if (*pIn == *pOp)
        break;
      pOp++;
    }
    if (!*pOp)
      return false;
    pIn++;
  }
  return true;
}

void DecompressDlg::OnBnClickedOk()
{
  m_bIsFileUpdated = false;
  OdPrcFilePtr pDb = m_pPrcTreeView->GetDocument()->database();
  
  CButton * m_checkBoxBrep = (CButton*) GetDlgItem(IDC_CHECK_BREP_DECOMPRESSION);
  if (m_checkBoxBrep->GetCheck() == BST_CHECKED)
  {
    OdPrcFile::decompressCompressedBreps(pDb);
    m_bIsFileUpdated = true;
  }

  CButton *m_checkBoxTess = (CButton*) GetDlgItem(IDC_CHECK_TESS_DECOMPRESSION);
  if (m_checkBoxTess->GetCheck() == BST_CHECKED)
  {
    Decompress3dTessParams params;

    CButton *m_checkBoxTessStoreNormals = (CButton*)GetDlgItem(IDC_CHECK_TESS_STORE_NORMALS);
    params.bStoreNormals = m_checkBoxTessStoreNormals->GetCheck() == BST_CHECKED;
    CButton *m_checkBoxTessOverwriteCreaseAngle = (CButton*)GetDlgItem(IDC_CHECK_TESS_OVERWRITE_CREASE_ANGLE);
    params.bOverwriteCreaseAngle = m_checkBoxTessOverwriteCreaseAngle->GetCheck() == BST_CHECKED;
    if (params.bOverwriteCreaseAngle)
    {
      bool bValid = false;
      CString tmpStr;
      GetDlgItemText(IDC_CREASE_ANGLE_VALUE, tmpStr);
      OdString sValIn(tmpStr);
      if (preValidate(sValIn, OD_T("-+.eE0123456789")))
      {
        double dVal = odStrToD(tmpStr.GetBuffer());
        if (dVal >= 0. && dVal <= 180.)
        {
          bValid = true;
          params.dCreaseAngle = dVal;
        }
      }
      if (!bValid)
      {
        MessageBox(OdString().format(OD_T("Crease angle must be a double in range %d to %d."), 0, 180).c_str(), OD_T("Input Validation Error"), MB_ICONWARNING);
        return;
      }
    }
    OdPrcFile::decompressCompressed3dTess(pDb, params);
    m_bIsFileUpdated = true;
  }
  CDialog::OnOK();
}

bool DecompressDlg::isFileUpdated()
{
  return m_bIsFileUpdated;
}
