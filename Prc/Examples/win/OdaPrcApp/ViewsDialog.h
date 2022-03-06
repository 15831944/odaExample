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

#pragma once


#include "Managers/BmViewTable.h"
#include "Entities/BmDBView.h"
// ViewsDialog form view

class OdaPrcExViewer;

class CBmViewTreeCtrl : public CTreeCtrl
{
  void setViewId(int nItem, const OdPrcObjectId& id);
  void setView(int nItem, const OdPrcDBView* pView);
public:
  OdPrcObjectId viewId(int n) const;
  OdPrcDBViewPtr view(int n);
  void InsertItem(int i, const OdPrcDBView* pView);
};



class ViewsDialog : public CDialog
{
  OdPrcFilePtr m_pDatabase;
  CTreeCtrl m_ViewsTree;
  OdPrcObjectId m_currentDBDrawingId;
public:
  OdPrcObjectId getDBDrawingId();

  ViewsDialog(OdPrcFile* pDatabase);

  enum { IDD = IDD_VIEWS };

  HTREEITEM addTreeItem( const CString& sName, bool bHasChildren = true, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST );

  afx_msg void OnSelchangingOwnershiptree(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnDblClickTree(NMHDR *pNMHDR, LRESULT *pResult);
protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual BOOL OnInitDialog();
  void OnInitViews();

  DECLARE_MESSAGE_MAP()

};

#endif
