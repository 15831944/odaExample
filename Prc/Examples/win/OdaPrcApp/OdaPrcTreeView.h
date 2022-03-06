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
#pragma once

class OdaPrcTreeFiller;
class OdaPrcListFiller;
class COdaPrcAppDoc;

// COdaPrcTreeView form view

class COdaPrcTreeView : public CFormView
{
  DECLARE_DYNCREATE(COdaPrcTreeView)

protected:
  COdaPrcTreeView();           // protected constructor used by dynamic creation
  virtual ~COdaPrcTreeView();

  // Attributes
public:
  COdaPrcAppDoc* GetDocument() const;

  //OdPrcElementId curElementId();

protected:
  int m_nTotalObjects;
  inline void setStatusText(LPCTSTR msg) { theApp.setStatusText(msg); }
  CFont m_font;

  OdaPrcTreeFiller* m_pTreeFiller;
  OdaPrcListFiller* m_pListFiller;

  OdaPrcTreeFiller* getTreeFiller();
  OdaPrcListFiller* getListFiller();

  void SetControlFont();
  void fillTree();

public:
  enum { IDD = IDD_ODAPRCTREEVIEW };
  CTreeCtrl  m_ObjectTree;
  CListCtrl  m_ObjectList;
#ifdef _DEBUG
  virtual void AssertValid() const;
#ifndef _WIN32_WCE
  virtual void Dump(CDumpContext& dc) const;
#endif
#endif

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual void OnInitialUpdate(); // called first time after construct
  virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

  //BOOL Find(HTREEITEM item, OdPrcElementId id);
  //void Find(const OdPrcElementId& targetId);

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnDestroy();
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnTvnItemexpandingPrcTreeview(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnEditFind();
  afx_msg void OnListDblClk(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnToolsDecompress();
  afx_msg void OnToolsCompress();

private:
  void expandElement(int elementPos);
  void collapseElement(int elementPos);
};


#ifndef _DEBUG  // debug version in OdaPrcAppView.cpp
inline COdaPrcAppDoc* COdaPrcTreeView::GetDocument() const
{
  return reinterpret_cast<COdaPrcAppDoc*>(m_pDocument);
}
#endif
