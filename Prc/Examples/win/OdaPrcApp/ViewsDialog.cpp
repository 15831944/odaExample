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

#if 0

#include "stdafx.h"
#include "OdaPrcApp.h"
#include "ViewsDialog.h"
#include "OdaPrcExViewer.h"
#include "Gs/GsModel.h"

#include "Entities/BmDBDrawing.h"
#include "Entities/BmDBView.h"
#include "Entities/BmDBViewType.h"
#include "Entities/BmViewport.h"
#include "PrcFile.h"


// ViewsDialog
ViewsDialog::ViewsDialog(OdPrcFile* pDatabase)
  : CDialog(ViewsDialog::IDD)
{
  m_pDatabase = pDatabase;
  
//   if (!m_pDatabase.isNull())
//   {
//     OdPrcDBViewPtr pActiveView = m_pDatabase->getAppInfoManager()->getViewTable()->
//         getActiveViewId().safeOpenObject();
//     m_currentDBDrawingId = pActiveView->getDbDrawingId();
//   }
}

BOOL ViewsDialog::OnInitDialog() {
  if (m_pDatabase.isNull())
  {
    MessageBox(_T("ODA PRC SDK Initialization error"), 
        _T("Unable to fill ViewsDialog."), MB_OK | MB_ICONERROR);
    return false;
  }
  CDialog::OnInitDialog();
  
  const struct c_addView 
  {
    void operator()(OdDbStub* stub, const LPCTSTR& name,
      const HTREEITEM& node, CTreeCtrl& ViewsTree, bool bNeedSelect) const 
    {
      TVITEM item = { 0 };
      item.cChildren = 0;
      item.mask = TVIF_HANDLE | TVIF_CHILDREN | TVIF_PARAM;
      CString sName;
      sName.Format(_T("<%s>"), name);
      item.hItem = ViewsTree.InsertItem(sName, node, TVI_SORT);
      item.lParam = (LPARAM) stub;
      ViewsTree.SetItem(&item);

      if (bNeedSelect) ViewsTree.SelectItem(item.hItem);
    }
  } addView;
  
  TVITEM tvItem = { 0 };
  tvItem.mask = TVIF_HANDLE | TVIF_CHILDREN | TVIF_PARAM;
  tvItem.cChildren = 1;
  tvItem.lParam = 0;
  
  HTREEITEM hUnsupportedViewsNode = 0;
  typedef std::map<OdString, HTREEITEM> PlansMap;
  PlansMap mPlans;

  OdDbBaseDatabasePEPtr pDbPE(m_pDatabase);
  OdRxIteratorPtr pIt = pDbPE->layouts(m_pDatabase);

  for (; !pIt->done(); pIt->next())
  {
    OdPrcDBDrawingPtr pDBDrawing = pIt->object();
    OdDbStub* pStub(pDBDrawing->id());

    OdString sPlanName = pDBDrawing->getViewType();
    PlansMap::iterator itPlane = mPlans.find(sPlanName);
    HTREEITEM hParentNode;

    if (itPlane == mPlans.end())
    {
      hParentNode = m_ViewsTree.InsertItem(sPlanName, TVI_ROOT, TVI_SORT);
      tvItem.hItem = hParentNode;
      m_ViewsTree.SetItem(&tvItem);

      mPlans[sPlanName] = hParentNode;
    }
    else
    {
      hParentNode = itPlane->second;
    }
      
    addView(pStub, pDBDrawing->getName(), hParentNode, m_ViewsTree,
        m_currentDBDrawingId == OdPrcObjectId(pDBDrawing->id()));
  } // for

  for (PlansMap::iterator itPlans = mPlans.begin();
    itPlans != mPlans.end();
    ++itPlans)
  {
    m_ViewsTree.Expand(itPlans->second, TVE_EXPAND);
  }

  return TRUE;
}

void ViewsDialog::OnInitViews()
{

}


HTREEITEM ViewsDialog::addTreeItem( const CString& sName, bool bHasChildren, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
  HTREEITEM hItem = m_ViewsTree.InsertItem(sName, hParent, TVI_LAST);
  TVITEM item = { 0 };
  item.mask   = TVIF_HANDLE | TVIF_CHILDREN | TVIF_PARAM;
  item.hItem  = hItem;
  return hItem;
}


void ViewsDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_TREEVIEWS, m_ViewsTree);
}
 
OdPrcObjectId ViewsDialog::getDBDrawingId()
{
  return m_currentDBDrawingId;
}

void ViewsDialog::OnDblClickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
  HTREEITEM h = m_ViewsTree.GetSelectedItem();
  OdPrcObjectId selectedDbDrawingId = (OdDbStub*) m_ViewsTree.GetItemData(h);
  if (selectedDbDrawingId.isValid())
  {
    if (m_currentDBDrawingId == selectedDbDrawingId) EndDialog(IDCANCEL);
    else 
    {
      m_currentDBDrawingId = selectedDbDrawingId;
      EndDialog(IDOK);
    }
  }
}

void ViewsDialog::OnSelchangingOwnershiptree(NMHDR* pNMHDR, LRESULT* pResult)
{
  NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*) pNMHDR;
  HTREEITEM h = pNMTreeView->itemOld.hItem;
  if (h)
  {
    m_ViewsTree.SetItemState( h, ( m_ViewsTree.GetItemState( h, TVIS_BOLD ) ^ TVIS_BOLD ), TVIS_BOLD );
  }
  h = pNMTreeView->itemNew.hItem;
  m_ViewsTree.SetItemState( h, ( m_ViewsTree.GetItemState( h, TVIS_BOLD ) ^ TVIS_BOLD ), TVIS_BOLD );
}

BEGIN_MESSAGE_MAP(ViewsDialog, CDialog)
  ON_NOTIFY(TVN_SELCHANGING, IDC_TREEVIEWS, OnSelchangingOwnershiptree)
  ON_NOTIFY(NM_DBLCLK, IDC_TREEVIEWS, OnDblClickTree)
END_MESSAGE_MAP()
// ViewsDialog message handlers
#endif
