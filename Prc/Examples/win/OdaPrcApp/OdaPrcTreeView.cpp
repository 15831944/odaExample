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
// COdaPrcTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "OdaPrcApp.h"
#include "OdaPrcTreeView.h"
#include "OdaPrcAppDoc.h"
#include "OdaPrcTreeFiller.h"
#include "MainFrm.h"
#include "FindObjectDlg.h"
#include "DecompressDlg.h"
#include "CompressDlg.h"

// COdaPrcTreeView

IMPLEMENT_DYNCREATE(COdaPrcTreeView, CFormView)

COdaPrcTreeView::COdaPrcTreeView()
  : CFormView(COdaPrcTreeView::IDD)
  , m_pTreeFiller(0)
  , m_pListFiller(0)
{
}

COdaPrcTreeView::~COdaPrcTreeView()
{
  if ( m_pTreeFiller )
  {
    delete m_pTreeFiller;
    m_pTreeFiller = 0;
  }
  if ( m_pListFiller )
  {
    delete m_pListFiller;
    m_pListFiller = 0;
  }
}

OdaPrcTreeFiller* COdaPrcTreeView::getTreeFiller()
{
  if ( !m_pTreeFiller )
  {
    OdPrcFile* pDb = GetDocument()->database();
    m_pTreeFiller = new OdaPrcTreeFiller( pDb, &m_ObjectTree );
  }
  return m_pTreeFiller;
}

OdaPrcListFiller* COdaPrcTreeView::getListFiller()
{
  if ( !m_pListFiller )
  {
    OdPrcFile* pDb = GetDocument()->database();
    m_pListFiller = new OdaPrcListFiller( pDb, &m_ObjectList );
  }
  return m_pListFiller;
}

BOOL COdaPrcTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
  cs.style |= WS_MAXIMIZE;
  return CFormView::PreCreateWindow(cs);
}

void COdaPrcTreeView::DoDataExchange(CDataExchange* pDX)
{
  CFormView::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_PRCTREEVIEW, m_ObjectTree);
  DDX_Control(pDX, IDC_ELEMENTDUMPLIST, m_ObjectList);
}

void COdaPrcTreeView::OnInitialUpdate()
{
  CFormView::OnInitialUpdate();
  ResizeParentToFit();
  SetControlFont();

  m_ObjectList.SetExtendedStyle(m_ObjectList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

  ResizeParentToFit();

  m_ObjectList.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 200);
  m_ObjectList.InsertColumn(1, _T("Value"), LVCFMT_LEFT, 200);
  m_ObjectList.InsertColumn(2, _T("Type"), LVCFMT_LEFT, 200);
  m_nTotalObjects = 0;
}

void COdaPrcTreeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
  fillTree();
}

void COdaPrcTreeView::SetControlFont()
{
  LOGFONT lf = {0};
  m_ObjectTree.GetFont()->GetLogFont(&lf);
  CString strFont = AfxGetApp()->GetProfileString(_T("options"), _T("List window font typeface"), _T("Microsoft Sans Serif"));
  _tcscpy(lf.lfFaceName, (LPCTSTR)strFont);
  m_font.CreateFontIndirect(&lf);

  // apply the font to the controls
  m_ObjectTree.SetFont(&m_font);
  m_ObjectList.SetFont(&m_font);
}

void COdaPrcTreeView::OnToolsDecompress()
{
  DecompressDlg decompressDlg(this);
  decompressDlg.DoModal();
  if (decompressDlg.isFileUpdated())
  {
    fillTree();
  }
}

void COdaPrcTreeView::OnToolsCompress()
{
  CompressDlg compressDlg(this);
  compressDlg.DoModal();
  if (compressDlg.isFileUpdated())
  {
    fillTree();
  }
}

BEGIN_MESSAGE_MAP(COdaPrcTreeView, CFormView)
  ON_NOTIFY(TVN_SELCHANGED, IDC_PRCTREEVIEW, OnTvnSelchangedTree)
  ON_WM_DESTROY()
  ON_WM_SIZE()
  ON_COMMAND(ID_EDIT_FIND, OnEditFind)
  ON_NOTIFY(TVN_ITEMEXPANDING, IDC_PRCTREEVIEW, OnTvnItemexpandingPrcTreeview)
  ON_NOTIFY(NM_DBLCLK, IDC_ELEMENTDUMPLIST, OnListDblClk)
  ON_COMMAND(ID_TOOLS_DECOMPRESS, OnToolsDecompress)
  ON_COMMAND(ID_TOOLS_COMPRESS, OnToolsCompress)
END_MESSAGE_MAP()


// COdaPrcTreeView diagnostics

#ifdef _DEBUG
void COdaPrcTreeView::AssertValid() const
{
  CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COdaPrcTreeView::Dump(CDumpContext& dc) const
{
  CFormView::Dump(dc);
}
#endif

COdaPrcAppDoc* COdaPrcTreeView::GetDocument() const // non-debug version is inline
{
  ODA_ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COdaPrcAppDoc)));
  return (COdaPrcAppDoc*)m_pDocument;
}
#endif //_DEBUG


// COdaPrcTreeView message handlers

void COdaPrcTreeView::OnDestroy()
{
  // Close vectorizer views
  COdaPrcAppDoc* pDoc = GetDocument();
  POSITION pos = pDoc->GetFirstViewPosition();
  while (pos != NULL)
  {
    CView* pView = pDoc->GetNextView(pos);
    if ( pView && pView != this )
    {
      pView->GetParent()->PostMessage(WM_CLOSE);
    }
  }

  CFormView::OnDestroy();
}
/*
BOOL COdaPrcTreeView::Find(HTREEITEM item, OdPrcElementId id)
{
  for(; item != NULL; item = m_ObjectTree.GetNextItem(item, TVGN_NEXT))
  {
    LPARAM data = m_ObjectTree.GetItemData(item);

    OdDbHandle h1 = id.getHandle();
    OdDbHandle h2 = OdPrcElementId((OdDbStub*)data).getHandle();
    if ( h1 == h2)
    {
      m_ObjectTree.SelectItem( item );
      return TRUE;
    }

    if (m_ObjectTree.ItemHasChildren( item ))
    {
      getTreeFiller()->explandItem(item);
      HTREEITEM subItem = m_ObjectTree.GetChildItem( item );
      if (subItem && Find(subItem, id))
      {
        m_ObjectTree.Expand( item, TVE_EXPAND );
        return TRUE;
      }
    }
  }

  return FALSE;
}

void COdaPrcTreeView::Find(const OdPrcElementId& targetId)
{
  // Building parentship queue
  OdArray<OdPrcElementId> parents;

  // Opening...
  HTREEITEM item = m_ObjectTree.GetChildItem( m_ObjectTree.GetRootItem() );
  Find(item, targetId);
}*/

void COdaPrcTreeView::OnEditFind()
{
 /* CFindObjectDlg fd;
  if(fd.DoModal()==IDOK)
  {
    // Calculating handle
    OdDbHandle han((LPCTSTR)fd.m_objHandle);

    // Requesting ObjectId
    OdPrcElementId targetId;
    OdPrcFile* pDb = GetDocument()->database();
    targetId = pDb->getElementId(han);
    if(targetId.isNull())
    {
      MessageBox(_T("Incorrect handle"), _T("Error"), MB_OK + MB_ICONSTOP);
      return;
    }
    COdaPrcTreeView::Find(targetId);
  }*/
}

OdPrcObjectId getObjectId(const OdRxObject *pObj)
{
  OdPrcReferencedBasePtr pRef = OdPrcReferencedBase::cast(pObj);
  if (!pRef.isNull())
  {
    return pRef->objectId();
  }

  OdPrcBodyPtr pBody = OdPrcBody::cast(pObj);
  if (!pBody.isNull())
  {
    return pBody->objectId();
  }

  OdPrcFileStructurePtr pFS = OdPrcFileStructure::cast(pObj);
  if (!pFS.isNull())
  {
    return pFS->objectId();
  }

  return OdPrcObjectId();
}

void COdaPrcTreeView::fillTree()
{
  OdaPrcTreeFiller* pTreeFiller = getTreeFiller();

  pTreeFiller->clear();

  OdPrcFile* pDb = GetDocument()->database();

  try
  {
    HTREEITEM hDbItem = pTreeFiller->getDbTreeItem();

    OdUInt32 f;
    
    const OdPrcModelFileData &modelFileData = pDb->modelFileData();
    const OdPrcSchema &schema = pDb->schema();
    const OdPrcFileStructurePtrArray &fileStructures = pDb->fileStructures();
    const OdPrcFile &header = *pDb;
    const OdPrcUncompressedFiles &uncompressedFiles = header.uncompressedFiles();

    HTREEITEM hUncompressedFilesItem = pTreeFiller->addTreeItem(L"UncompressedFiles", true, hDbItem);
    for(f=0; f<uncompressedFiles.fileContents().size(); ++f)
    {
      HTREEITEM hUncompressedFileItem = pTreeFiller->addTreeItem(L"UncompressedFile", true, hDbItem);
    }

    HTREEITEM hSchemaItem = pTreeFiller->addTreeItem(L"Schema", true, hDbItem);

    HTREEITEM hModelFileDataItem = pTreeFiller->addTreeItem(L"ModelFileData", true, hDbItem);
    pTreeFiller->addChilds(&pDb->modelFileData(), hModelFileDataItem, 1);

    HTREEITEM hFSItem = pTreeFiller->addTreeItem(L"FileStructures", true, hDbItem);
    for(f=0; f<fileStructures.size(); ++f)
    {
      OdString tmp = fileStructures[f]->isA()->name() + " (" + fileStructures[f]->objectId().getHandle().ascii() + ")";
      HTREEITEM hFileStructureItem = pTreeFiller->addTreeItemWithId(tmp.c_str(), fileStructures[f]->objectId(), true, hFSItem);
      pTreeFiller->addChilds(fileStructures[f], hFileStructureItem, 1);
    }
  }
  catch(OdError& e)
  {
    theApp.reportError(_T("Error reading DB..."), e);
  }
}

/*OdPrcElementId COdaPrcTreeView::curElementId()
{
  return OdPrcElementId::kNull;
}*/


void COdaPrcTreeView::OnSize(UINT nType, int cx, int cy)
{
  CFormView::OnSize(nType, cx, cy);
  if(cx > 10 && cy > 10 && m_ObjectTree.m_hWnd)
  {
    CRect crc;
    GetClientRect(&crc);
    crc.DeflateRect(2,2,2,2);
    m_ObjectTree.SetWindowPos(NULL, crc.left, crc.top, crc.Width()/2-1, crc.Height(), SWP_NOZORDER);
    m_ObjectList.SetWindowPos(NULL, crc.left+crc.Width()/2+1, crc.top, crc.Width()/2-1, crc.Height(), SWP_NOZORDER);
  }
}

void COdaPrcTreeView::OnTvnItemexpandingPrcTreeview(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

  // handle of selected item as tree member
  HTREEITEM hChild = m_ObjectTree.GetChildItem(pNMTreeView->itemNew.hItem);
  if(!hChild)
  {
    CMainFrame* pWnd = (CMainFrame*)theApp.GetMainWnd();
    pWnd->setStatusText(0, _T("Filling tree..."));

    HCURSOR cursor = GetCursor();
    SetCursor(LoadCursor(NULL, IDC_WAIT));
    try
    {
      m_pTreeFiller->expandItem(pNMTreeView->itemNew);
    }
    catch(const OdError& e)
    {
      theApp.reportError(_T("Filling tree..."), e);
    }
    catch(...)
    {
      theApp.reportError(_T("Filling tree..."), OdError(eInvalidInput));
    }
    SetCursor(cursor);
    pWnd->setStatusText(0, _T("Ready"));
  }

  *pResult = 0;
}

void COdaPrcTreeView::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
  getListFiller()->clear();

  LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

  try
  {
    m_ObjectList.SetRedraw(FALSE);

    OdRxObjectPtr pObj = getTreeFiller()->getObject(pNMTreeView->itemNew);
    if (pObj.get())
    {  
      getListFiller()->dump(pObj);  
    }
    else
    {
      OdString itemName = getTreeFiller()->getItemName(pNMTreeView->itemNew);
      getListFiller()->dumpByName(itemName);
    }

    m_ObjectList.SetRedraw(TRUE);
  }
  catch(const OdError& e)
  {
    int n = m_ObjectList.InsertItem(m_ObjectList.GetItemCount(), _T("OdError:"));
    m_ObjectList.SetItemText(n, 1, e.description());
  }
  catch(...)
  {
    int n = m_ObjectList.InsertItem(m_ObjectList.GetItemCount(), _T("ERROR:"));
    m_ObjectList.SetItemText(n, 1, _T("..."));
  }
  
  *pResult = 0;
}

void COdaPrcTreeView::OnListDblClk(NMHDR* pNMHDR, LRESULT* pResult) 
{ 
  CPoint pt; 
  GetCursorPos(&pt); 
  m_ObjectList.ScreenToClient(&pt); 
  UINT flags; 
  int hItem = m_ObjectList.HitTest(pt, &flags); 
  if (flags & LVHT_ONITEM) 
  {
    OdString trimmedPropertyType(m_ObjectList.GetItemText(hItem, 0));
    trimmedPropertyType.trimLeft();
    if (trimmedPropertyType.getLength() > 0) {
      if (trimmedPropertyType[0] == '+') expandElement(hItem);
      else if (trimmedPropertyType[0] == '-') collapseElement(hItem);
    }
  }
  *pResult = 0;
}

void COdaPrcTreeView::expandElement(int elementPos)
{
//   OdString propertyValue(m_ObjectList.GetItemText(elementPos, 2));
//   if ((propertyValue == L"[Object pointer]") || (propertyValue == L"[Array of properties]"))
//   {
//     OdString propertyType(m_ObjectList.GetItemText(elementPos, 0));
//     OdString trimmedPropertyType = propertyType;
//     trimmedPropertyType.trimLeft();
//     int indent = propertyType.getLength() - trimmedPropertyType.getLength();
// 
//     LVITEM lvi = {0};
//     lvi.mask = LVIF_PARAM;
//     lvi.iItem = elementPos;
// 
//     m_ObjectList.SetRedraw(FALSE);
//     if ((m_ObjectList.GetItem(&lvi)) && (lvi.lParam != 0))
//     {
//       if (propertyValue == L"[Object pointer]") {
//         OdPrcObjectPtr ptr((OdRxObject*) lvi.lParam);
//         if ( ptr.get() ) getListFiller()->dump(ptr, elementPos + 1, indent + 5);
//       } else if (propertyValue == L"[Array of properties]") {
//         const OdTfVariantArray& arr = (getListFiller()->getTfArraysMap())[lvi.lParam];
//         int insertPos = elementPos;
// 
//         for(OdUInt32 i = 0; i < arr.size(); ++i) {
//           OdTfVariant el = arr.at(i);
//           getListFiller()->dumpVariant(OdString().format(L"item[%d]", i),
//               el, ++insertPos, indent + 5);
//         }
//       }
//     }
//     m_ObjectList.SetRedraw(TRUE);
// 
//     propertyType.setAt(indent, '-');
//     m_ObjectList.SetItemText(elementPos, 0, propertyType.c_str());
//   }
}

void COdaPrcTreeView::collapseElement(int elementPos)
{
//   OdString propertyType = m_ObjectList.GetItemText(elementPos, 0);  
//   OdString trimmedPropertyType = propertyType;
//   trimmedPropertyType.trimLeft();
// 
//   int currentIndent = propertyType.getLength() - trimmedPropertyType.getLength();
//   
//   propertyType.setAt(currentIndent, '+');
//   m_ObjectList.SetItemText(elementPos, 0, propertyType.c_str());
//   
//   LVITEM lvi = {0};
//   lvi.mask = LVIF_PARAM;
//   lvi.iItem = elementPos + 1;
//   
//   m_ObjectList.SetRedraw(FALSE);
// 
//   for (++elementPos; elementPos < m_ObjectList.GetItemCount(); )
//   {
//     propertyType = m_ObjectList.GetItemText(elementPos, 0);
//     trimmedPropertyType = propertyType;
//     trimmedPropertyType.trimLeft();
// 
//     if (propertyType.getLength() - trimmedPropertyType.getLength() > currentIndent) {
//       if ((m_ObjectList.GetItemText(elementPos, 2) == L"[Array of properties]") &&
//           (m_ObjectList.GetItem(&lvi))) {
//         (getListFiller()->getTfArraysMap()).erase(lvi.lParam);
//       }
//       m_ObjectList.DeleteItem(elementPos);
//     } else {
//       break;
//     }
//   }
// 
//   m_ObjectList.SetRedraw(TRUE);
}
