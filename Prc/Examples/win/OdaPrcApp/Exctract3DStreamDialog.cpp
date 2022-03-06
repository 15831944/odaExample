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

// Extract3DStreamDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OdaPrcApp.h"
#include "Exctract3DStreamDialog.h"
#include "PasswordDlg.h"
#include "MemoryStream.h"
#include "PrcPreviewGenerator.h"
#include "Gi/GiRasterWrappers.h"
#include "RxVariantValue.h"
#include "RxDispatchImpl.h"
#ifdef U3D_MODULE_ENABLED
#include "U3D2PrcImport.h"
#endif

#if _MSC_VER < 1400
#include <atlbase.h>
#include <atlwin.h>
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Extract3DStreamDialog dialog

#ifdef PDFIUM_MODULE_ENABLED

Extract3DStreamDialog::Extract3DStreamDialog(CWnd* pParent /*=NULL*/)
	: CDialog(Extract3DStreamDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(Extract3DStreamDialog)
  m_Path = _T("");
  m_FileName = _T("");
  m_CurPage = -1;
  m_CurStreamIdx = -1;
	//}}AFX_DATA_INIT
}


void Extract3DStreamDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(Extract3DStreamDialog)
  DDX_Text(pDX, IDC_EDIT_FILENAME, m_Path);
  DDX_Control(pDX, IDC_LIST_PAGE, m_PageList);
  DDX_Control(pDX, IDC_LIST_STREAMS, m_StreamList);
  DDX_Control(pDX, IDC_PREVIEW, m_Preview);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Extract3DStreamDialog, CDialog)
	//{{AFX_MSG_MAP(CDwfUnderlayDialog)
  ON_WM_DRAWITEM()
  ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnBrowse)
  ON_CBN_SELCHANGE(IDC_LIST_PAGE, OnSelchangePageList)
  ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STREAMS, OnItemchangedList2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Extract3DStreamDialog message handlers

BOOL Extract3DStreamDialog::OnInitDialog()
{
  CDialog::OnInitDialog();
  CenterWindow();

  CRect rect, rectButton;
  GetWindowRect(&rect);
  GetDlgItem(IDCANCEL)->GetWindowRect(&rectButton);
  m_DialogHeight = rect.Height();
  rect.bottom = rectButton.bottom + 20;
  MoveWindow(&rect);

  m_StreamList.DeleteAllItems();
  m_StreamList.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 130);
  m_StreamList.InsertColumn(1, _T("Type"), LVCFMT_LEFT, 50);

  GetDlgItem(IDC_LIST_PAGE)->EnableWindow( FALSE );
  GetDlgItem(IDC_LIST_STREAMS)->EnableWindow( FALSE );

  m_StreamList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

  m_CurPage = -1;
  m_CurStreamIdx = -1;

  return TRUE;
}

void Extract3DStreamDialog::OnBrowse() 
{
  UpdateData(true); // save and validate

  CFileDialog dlgFile(true);

  dlgFile.m_ofn.Flags |= OFN_HIDEREADONLY | OFN_EXPLORER | OFN_FILEMUSTEXIST;


  dlgFile.m_ofn.lpstrFilter = _T("PDF files (*.pdf)\0*.pdf\0");
  dlgFile.m_ofn.lpstrDefExt = _T("pdf");
  dlgFile.m_ofn.lpstrTitle = _T("Select pdf file");

  if (dlgFile.DoModal() == IDOK)
  {
    GetDlgItem(IDC_LIST_PAGE)->EnableWindow( FALSE );
    GetDlgItem(IDC_LIST_STREAMS)->EnableWindow( FALSE );

    m_Path = dlgFile.GetPathName();
    m_FileName = dlgFile.GetFileName();

    bool bInit = InitProperties();

    if (bInit)
    {
      GetDlgItem(IDC_DU_PROPERTIES)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_SDWFSHEETNAME)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_LIST_PAGE)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_LIST_STREAMS)->ShowWindow(SW_SHOW);

      GetDlgItem(IDOK)->EnableWindow(TRUE);

      CRect rect;
      GetWindowRect(&rect);
      rect.bottom = rect.top + m_DialogHeight;
      m_DialogHeight = 0;
      MoveWindow(&rect);
    }
  }
}

void Extract3DStreamDialog::OnError(CString str)
{
  MessageBox(str, CString("Error"));
}

void Extract3DStreamDialog::OnError(OdResult res)
{
  OdError err(res);
  CString str((LPCTSTR)err.description());
  OnError(str);
}

bool Extract3DStreamDialog::InitProperties()
{
  m_Stream.release();

  OdPdf3DStreamExtractorModulePtr pModule;
  try
  {
    pModule = ::odrxDynamicLinker()->loadModule(OdPdf3DStreamExtractorModuleName, false);
  }
  catch (OdError& err)
  {
    OnError(err.description().c_str());
    return false;
  }

  m_OdPdf3DStreamExtractor = pModule->create();

  if (m_OdPdf3DStreamExtractor.isNull())
  {
    OnError(OD_T("Unable to create OdPdf3DStreamExtractor"));
    return false;
  }

  OdString password;
  OdString path(m_Path.GetString());
  OdPdf3DStreamExtractor::ExtractResult res = m_OdPdf3DStreamExtractor->openPdfDocument(path, password);

  if (OdPdf3DStreamExtractor::bad_password == res)
  {
    CPasswordDlg pwdDlg;
    pwdDlg.m_sFileName = m_Path;
    if (pwdDlg.DoModal() == IDOK)
    {
      password = pwdDlg.m_password;
      
      res = m_OdPdf3DStreamExtractor->openPdfDocument(path, password);
      if(OdPdf3DStreamExtractor::success != res)
        return false;
    }
    else
      return false;
  }

  FillPageList();
  FillStreamList();

  UpdateData(false); // save and validate
  GetDlgItem(IDC_LIST_PAGE)->EnableWindow(m_PageList.GetCount() != 0);
  GetDlgItem(IDC_LIST_STREAMS)->EnableWindow(m_StreamList.GetItemCount() != 0);

  return true;
}

void Extract3DStreamDialog::FillPageList()
{
  m_PageList.ResetContent();
  OdPdf3DStreamExtractor::ExtractResult res;
  size_t page_count = m_OdPdf3DStreamExtractor->getPageCount(res);
  if (OdPdf3DStreamExtractor::success != res)
  {
    OnError(OD_T("Error in getting the number of pages.")); 
    return;
  }
  
  if ( 0 == page_count)
  {
    OnError(OD_T("Zero number of pages in the document."));
    return;
  }

  for (size_t i = 0; i < page_count; ++i)
  {
    m_PageList.InsertString((int)i, (LPCTSTR)OdString().format(OD_T("%d"), (int)(i + 1)));
  }
  m_PageList.SetCurSel(0);
  m_CurPage = 0;
}

void Extract3DStreamDialog::FillStreamList()
{
  m_StreamList.DeleteAllItems();

  int page_idx = m_PageList.GetCurSel();
  if (page_idx == -1)
    return;

  OdPdf3DStreamExtractor::ExtractResult res;
  size_t stream_count = m_OdPdf3DStreamExtractor->getCount3DStreamForPage(page_idx, res);

  if (OdPdf3DStreamExtractor::success != res)
  {
    OnError(OD_T("Error in getting the number of stream."));
    return;
  }

  for (size_t i = 0; i < stream_count; ++i)
  {
    OdString name = m_OdPdf3DStreamExtractor->Get3DStreamName(page_idx, (int)i, res);
    if (OdPdf3DStreamExtractor::success != res)
    {
      OnError(OD_T("Error in getting the name of stream."));
      return;
    }

    m_StreamList.InsertItem((int)i, (LPCTSTR)name);

    OdPdf3DStreamExtractor::StreamType type = m_OdPdf3DStreamExtractor->Get3DStreamType(page_idx, (int)i, res);
    if (OdPdf3DStreamExtractor::success != res)
    {
      OnError(OD_T("Error in getting the type of stream."));
      return;
    }
    switch (type)
    {
    case OdPdf3DStreamExtractor::ePRC:
      m_StreamList.SetItemText((int)i, 1, OD_T("PRC"));
      break;
    case OdPdf3DStreamExtractor::eU3D:
      m_StreamList.SetItemText((int)i, 1, OD_T("U3D"));
      break;
    default:
      break;
    }
  }
  m_StreamList.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
}

void Extract3DStreamDialog::updatePreview()
{
  OdResult od_res = eOk;
  OdPdf3DStreamExtractor::ExtractResult res;
  OdPdf3DStreamExtractor::StreamType type = m_OdPdf3DStreamExtractor->Get3DStreamType(m_CurPage, m_CurStreamIdx, res);
  if (OdPdf3DStreamExtractor::success != res)
  {
    OnError(OD_T("Error in getting the type of stream."));
    return;
  }

  m_Stream = OdMemoryStream::createNew();

  res = m_OdPdf3DStreamExtractor->fill3DStream(m_CurPage, m_CurStreamIdx, m_Stream);
  m_Stream->rewind();

  OdPrcFilePtr pDb = theApp.createDatabase();
  pDb->setVersions(8137, 8137);
  pDb->fileStructureId() = OdPrcUniqueId::generateUID();

  if (OdPdf3DStreamExtractor::eU3D == type)
  {
#ifdef U3D_MODULE_ENABLED
    OdU3D2PrcImportModulePtr pModule;
    try
    {
      pModule = ::odrxDynamicLinker()->loadModule(OdU3D2PrcImportModuleName, false);
    }
    catch (OdError& err)
    {
      OnError(err.description().c_str());
      return;
    }

    OdU3D2PrcImportPtr importer = pModule->create();

    importer->properties()->putAt(L"Database", pDb);
    importer->properties()->putAt(L"SourceType", OdRxVariantValue((OdUInt8)1));
    importer->properties()->putAt(L"InputStream", m_Stream);

    od_res  = importer->import();

    m_Stream->rewind();
    pDb->writeFile(m_Stream);
#else
    OnError(OD_T("The module OdU3D2PrcImport is missing"));
#endif
  }
  else
  {
    pDb->readFile(m_Stream);
  }

  OdPrcPreviewGeneratorPtr pPreviewGen = OdPrcPreviewGenerator::createObject();
  ODA_VERIFY(pPreviewGen->init(pDb) == eOk);

  pPreviewGen->setBackground(ODRGB(255, 255, 255));
  pPreviewGen->setBitmapSize(392, 255);

  OdGiRasterImagePtr pImage = pPreviewGen->generateByView(PrcPreviewGenerator::kDefault, &od_res);

  if (!pImage.isNull())
  {
    OdSmartPtr<OdGiRasterImageDesc> pDesc = OdRxObjectImpl<OdGiRasterImageDesc>::createObject();
    pDesc->setPixelWidth(pImage->pixelWidth());
    pDesc->setPixelHeight(pImage->pixelHeight());
    pDesc->setColorDepth(24);
    pDesc->pixelFormat().setBGR();
    pDesc->setScanLinesAlignment(4);
    OdGiRasterImagePtr pCopyImg;
    pCopyImg = pImage->convert(true, 50.0, 50.0, 0.0, 0, false, false, false, pDesc);
    if (!pCopyImg.isNull())
    {
      BITMAPINFO* pHeader;
      OdUInt8Array headerMemCont;
      headerMemCont.resize(sizeof(BITMAPINFOHEADER) + pCopyImg->paletteDataSize());
      pHeader = (BITMAPINFO*)headerMemCont.getPtr();
      pHeader->bmiHeader.biBitCount = (WORD)pCopyImg->colorDepth();
      pHeader->bmiHeader.biClrImportant = 0;
      pHeader->bmiHeader.biClrUsed = 0;
      pHeader->bmiHeader.biCompression = BI_RGB;
      pHeader->bmiHeader.biHeight = pCopyImg->pixelHeight();
      pHeader->bmiHeader.biPlanes = 1;
      pHeader->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      pHeader->bmiHeader.biSizeImage = 0;
      pHeader->bmiHeader.biWidth = pCopyImg->pixelWidth();
      pHeader->bmiHeader.biXPelsPerMeter = 0;
      pHeader->bmiHeader.biYPelsPerMeter = 0;
      pCopyImg->paletteData((OdUInt8*)pHeader->bmiColors);

      OdUInt8* pBuf;
      HBITMAP hBmp = CreateDIBSection(NULL, pHeader, DIB_RGB_COLORS, (void**)&pBuf, NULL, 0);

      if (pCopyImg->scanLineSize())
        pCopyImg->scanLines(pBuf, 0, pCopyImg->pixelHeight());

      DeleteObject(m_Preview.SetBitmap(hBmp));
    }

    RECT Rect;
    m_Preview.GetWindowRect(&Rect);
    m_Preview.GetOwner()->ScreenToClient(&Rect);
    m_Preview.MoveWindow(Rect.left,Rect.top,pImage->pixelWidth(), pImage->pixelHeight());  
  }

  m_Preview.ShowWindow(pImage.isNull() ? SW_HIDE : SW_SHOW);
}

void Extract3DStreamDialog::OnSelchangePageList()
{
  UpdateData( FALSE );

  int page_num = m_PageList.GetCurSel();

  if (m_CurPage != page_num)
  {
    FillStreamList();

    updatePreview();

    m_CurPage = page_num;
  }
  UpdateData( TRUE );
}

void Extract3DStreamDialog::OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
  NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

  if ((pNMListView->uChanged & LVIF_STATE)
    && (pNMListView->uNewState & LVIS_SELECTED))
  {
    if (m_CurStreamIdx != pNMListView->iItem)
    {
      m_CurStreamIdx = pNMListView->iItem;
      updatePreview();
    }
  }
}

OdStreamBufPtr Extract3DStreamDialog::getStream()
{
  return m_Stream;
}

OdString Extract3DStreamDialog::getStreamName()
{
  OdPdf3DStreamExtractor::ExtractResult res;
  OdString name = m_OdPdf3DStreamExtractor->Get3DStreamName(m_CurPage, m_CurStreamIdx, res);
  if (OdPdf3DStreamExtractor::success != res)
  {
    OnError(OD_T("Error in getting the name of stream."));
  }
  return name;
}

#endif // PDFIUM_MODULE_ENABLED
