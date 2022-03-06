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

// ViewsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OdaPrcApp.h"
#include "ViewsDlg.h"
#include "OdaPrcApp.h"
#include "OdaPrcAppDoc.h"
#include "OdaPrcExViewer.h"

///////////////////////////////////////
#include "PrcCommon.h"
#include "Ed/EdCommandContext.h"
#include "DbAux/PrcCommandContext.h"

#include "Gs/Gs.h"
#include "AbstractViewPE.h"
#include "Ge/GeBoundBlock3d.h"
#include "Gs/GsModel.h"

///////////////////////////////////////

// ViewsDlg dialog

IMPLEMENT_DYNAMIC(ViewsDlg, CDialog)

ViewsDlg::ViewsDlg(COdaPrcAppDoc * pPrcAppDoc, CWnd* pParent /*=NULL*/)
: CDialog(ViewsDlg::IDD, pParent), m_pPrcAppDoc(pPrcAppDoc)
{
}

ViewsDlg::~ViewsDlg()
{
}

void ViewsDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ViewsDlg, CDialog)
  ON_CBN_SELCHANGE(IDC_VIEW_COMBO_BOX, &ViewsDlg::OnCbnSelchangeViewComboBox)
END_MESSAGE_MAP()


// ViewsDlg message handlers


void ViewsDlg::OnCbnSelchangeViewComboBox()
{
  if (!m_pPrcAppDoc->database())
  {
    MessageBox(_T("ODA PRC SDK database error"), _T("Null database."), MB_OK | MB_ICONERROR);
    return;
  }
  CComboBox *m_comboBox = (CComboBox*) GetDlgItem(IDC_VIEW_COMBO_BOX);
  OdInt32 nViewIndex = m_comboBox->GetCurSel();
  OdPrcFilePtr pDb = m_pPrcAppDoc->database();
  --nViewIndex; //default view
  if (pDb->setViewNode(nViewIndex) && pDb->applyCurrentView())
  {
    m_pPrcAppDoc->ExecuteCommand("REGEN");
  }
  PostMessage(WM_CLOSE);
}

BOOL ViewsDlg::OnInitDialog()
{
  CDialog::OnInitDialog();
  if (!m_pPrcAppDoc->database())
  {
    MessageBox(_T("ODA PRC SDK Initialization error"), 
        _T("Unable to fill ViewsDialog."), MB_OK | MB_ICONERROR);
    return FALSE;
  }
  CComboBox *m_comboBox = (CComboBox*) GetDlgItem(IDC_VIEW_COMBO_BOX);
  m_comboBox->AddString(OdString(L"Default View[-1]").c_str());

  OdPrcFilePtr pDb = m_pPrcAppDoc->database();
  const OdArray<OdPrcViewNode> & views = pDb->getViewNodes();
  for (OdUInt32 i = 0; i < views.size(); ++i)
  {
    OdPrcViewPtr pView = views[i].view.openObject();
    m_comboBox->AddString(pView->name().name() + OdString().format(L"[%d]", i));
  }
  m_comboBox->SetCurSel(pDb->getCurrentViewNode() + 1);
  return TRUE;
}
