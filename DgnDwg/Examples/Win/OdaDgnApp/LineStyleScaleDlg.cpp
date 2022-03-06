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
// ViewFlagsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OdaDgnApp.h"
#include "LineStyleScaleDlg.h"

// CLineStyleScaleDlg dialog

IMPLEMENT_DYNAMIC(CLineStyleScaleDlg, CDialog)

CLineStyleScaleDlg::CLineStyleScaleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLineStyleScaleDlg::IDD, pParent)
{
  m_iLineStyleScaleType = 0;
  m_dModelGlobalScale = 1.0;
  m_dModelAnnotationScale = 1.0;
  m_dDbGlobalScale = 1.0;
}

//=================================================================================

CLineStyleScaleDlg::~CLineStyleScaleDlg()
{
}

//=================================================================================

void CLineStyleScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

  DDX_CBIndex(pDX, IDC_COMBO_LINE_SCALE_TYPE, m_iLineStyleScaleType);
  DDX_Text(pDX, IDC_EDIT_MODEL_GLOBAL_LSSCALE, m_dModelGlobalScale);
  DDX_Text(pDX, IDC_EDIT_MODEL_ANNOTATION_SCALE, m_dModelAnnotationScale);
  DDX_Text(pDX, IDC_EDIT_DATABASE_LSSCALE, m_dDbGlobalScale);
}

//=================================================================================

BEGIN_MESSAGE_MAP(CLineStyleScaleDlg, CDialog)
END_MESSAGE_MAP()

//=================================================================================



