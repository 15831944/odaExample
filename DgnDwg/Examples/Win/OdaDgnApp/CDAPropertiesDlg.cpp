/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2021, Open Design Alliance (the "Alliance"). 
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
//   Open Design Alliance Copyright (C) 2002-2021 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
// ViewFlagsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OdaDgnApp.h"
#include "CDAPropertiesDlg.h"

// CCDAPropertiesDlg dialog

IMPLEMENT_DYNAMIC(CCDAPropertiesDlg, CDialog)

CCDAPropertiesDlg::CCDAPropertiesDlg(CWnd* pParent, OdRxObject* pDb, OdRxObject* pObject, OdInt32 iSubPropertyIndex, const OdString& strPropName)
	: CDialog(CCDAPropertiesDlg::IDD, pParent)
{
  m_pDb = pDb;
  m_pObject = pObject;
  m_iSubPropertyIndex = iSubPropertyIndex;
  m_strPropName = strPropName;
}

//=================================================================================

CCDAPropertiesDlg::~CCDAPropertiesDlg()
{

}

//=================================================================================

void CCDAPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_PROP_LIST, m_listCtrl);
}

//=================================================================================

BOOL CCDAPropertiesDlg::OnInitDialog()
{
  BOOL bRet = CDialog::OnInitDialog();

  RECT wndRect;
  GetClientRect(&wndRect);

  m_listCtrl.initData(m_pDb, m_pObject, wndRect, m_iSubPropertyIndex, m_strPropName);

  if(!m_strPropName.isEmpty())
  {
    SetWindowText(m_strPropName + L" Property");
  }
  else
  {
    OdRxMemberPtr pProp = OdRxMemberQueryEngine::theEngine()->find(m_pObject, L"Name");

    if (!pProp.isNull() && pProp->isKindOf(OdRxProperty::desc()))
    {
      OdRxPropertyPtr pPropName = pProp;
      OdRxValue nameValue;

      if (!pPropName.isNull() && pPropName->getValue(m_pObject, nameValue) == eOk)
        SetWindowText(nameValue.toString() + L" Properties");
    }
  }

  return bRet;
}

//=================================================================================

void CCDAPropertiesDlg::OnSize(UINT nType, int cx, int cy)
{
  CDialog::OnSize(nType, cx, cy);
  m_listCtrl.onMoveOwner();
}

//=================================================================================

void CCDAPropertiesDlg::OnOk()
{}

//=================================================================================

BEGIN_MESSAGE_MAP(CCDAPropertiesDlg, CDialog)
  ON_WM_SIZE()
  ON_BN_CLICKED(IDOK, OnOk)
END_MESSAGE_MAP()

//=================================================================================



