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
// OdaPrcApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "OdaPrcApp.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "resource.h"
#include "OdaPrcAppDoc.h"
#include "OdaPrcTreeView.h"
#include "LoadApps.h"
#include "RegKey.h"

#include "diagnostics.h"
#include "ColorMapping.h"
#include "DynamicLinker.h"
#include "RxDynamicModule.h"
#include "DbLibraryInfo.h"
#include "PrcModuleNames.h"
#include "TDVersion.h"
#include "PrcDumpModule.h"
#include "Ed/EdCommandStack.h"
#include "PrcAuditInfoImpl.h"
#include "Exctract3DStreamDialog.h"

#include "OdToolKit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef _TOOLKIT_IN_DLL_
#include "StaticAppSelDlg.h"
#endif

// COdaPrcApp

BEGIN_MESSAGE_MAP(COdaPrcApp, CWinApp)
  //{{AFX_MSG_MAP(COdaPrcApp)
  ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
  // Standard file based document commands
  ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
  ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
  ON_COMMAND(ID_FILE_RECOVER, OnFileRecover)
  ON_COMMAND(ID_TOOLS_LOADAPPLICATIONS, OnToolsLoadapplications)
  ON_COMMAND(ID_VECTORIZE_ADDVECTORIZERDLL, OnVectorizeAddvectorizerdll)
#ifdef PDFIUM_MODULE_ENABLED
  ON_COMMAND(ID_EXTRACT_3D_STREAM, OnExtract3DStream)
#endif // PDFIUM_MODULE_ENABLED

  ON_UPDATE_COMMAND_UI(ID_VECTORIZE_ADDVECTORIZERDLL, OnUpdateVectorizeAddvectorizerdll)
  ON_COMMAND(ID_VECTORIZE_CLEARMENU, OnVectorizeClearmenu)
  ON_UPDATE_COMMAND_UI_RANGE(ID_VECTORIZER_FIRST, ID_VECTORIZER_LAST, OnUpdateGsDevices)
  ON_UPDATE_COMMAND_UI(ID_VECTORIZE_CLEARMENU, OnUpdateVectorizeClearmenu)
  ON_UPDATE_COMMAND_UI(ID_VECTORIZE, OnUpdateVectorize)
  ON_COMMAND(ID_OPTIONS_DISCARDBACKFACES, OnOptionsDiscardbackfaces)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_DISCARDBACKFACES, OnUpdateOptionsDiscardbackfaces)
  ON_COMMAND(ID_OPTIONS_USEGSMODELGEOMETRYCACHE, OnOptionsUseGsModel)
  ON_UPDATE_COMMAND_UI(ID_OPTIONS_USEGSMODELGEOMETRYCACHE, OnUpdateOptionsUseGsModel)

  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define AppRegistryKey _T("Open Design Alliance")

// Define module map for statically linked modules:

#ifndef _TOOLKIT_IN_DLL_
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(WinGDIModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(WinOpenGLModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(BitmapModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcDumpModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRasterProcessingServicesImpl);
#ifdef U3D_MODULE_ENABLED
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(U3D2PrcImportModule);
#endif
#ifdef PDFIUM_MODULE_ENABLED
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(Pdf3DStreamExtractorModule);
#endif

ODRX_BEGIN_STATIC_MODULE_MAP()
  ODRX_DEFINE_STATIC_APPMODULE(OdWinGDIModuleName,             WinGDIModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdWinOpenGLModuleName,          WinOpenGLModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdWinBitmapModuleName,          BitmapModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdPrcModuleName,                OdPrcModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdPrcDumpModuleName,            OdPrcDumpModule)
  ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME,     ExRasterModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName,    OdRasterProcessingServicesImpl)
#ifdef U3D_MODULE_ENABLED
  ODRX_DEFINE_STATIC_APPMODULE(OdU3D2PrcImportModuleName,      U3D2PrcImportModule)
#endif  
#ifdef PDFIUM_MODULE_ENABLED
  ODRX_DEFINE_STATIC_APPMODULE(OdPdf3DStreamExtractorModuleName, Pdf3DStreamExtractorModule)
#endif
ODRX_END_STATIC_MODULE_MAP()
#endif


// COdaPrcApp construction

COdaPrcApp::COdaPrcApp()
  : m_bLoading(false)
  , m_bRecover(false)
  , m_numCustomCommands(0)
  , m_pDwgHostApp(0)
{
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
}


const int nCommandMenuIndex = 8;

CMenu* COdaPrcApp::CommandMenu(CMenu** ppEditMenu)
{
  // Locate the edit submenu
  CMenu* pEditMenu = NULL;
  CMenu* pTopMenu = GetMainWnd()->GetMenu();
  int n = pTopMenu->GetMenuItemCount();
  for (int i = 0; i < n; ++i)
  {
    CMenu* pMenu = pTopMenu->GetSubMenu(i);
    if (pMenu && pMenu->GetMenuItemID(0) == ID_EDIT_UNDO)
    {
      pEditMenu = pMenu;
      break;
    }
  }
  ASSERT(pEditMenu != NULL);
  if(ppEditMenu)
  {
    *ppEditMenu = pEditMenu;
  }

  CMenu* pCommandMenu = pEditMenu->GetSubMenu(nCommandMenuIndex);

  ASSERT(pCommandMenu != NULL);

  return pCommandMenu;
}

void COdaPrcApp::RefreshCommandMenu()
{
  MENUITEMINFO menuItemInfo;
  menuItemInfo.cbSize = sizeof(menuItemInfo);
  menuItemInfo.fMask = MIIM_DATA;

  CMenu* pEditMenu = NULL;
  CMenu* pCommandMenu = CommandMenu(&pEditMenu);

  int i;
  for(i = pCommandMenu->GetMenuItemCount()-1; i >= 0; i--)
  {
    CMenu* pSubMenu = pCommandMenu->GetSubMenu(i);
    if(pSubMenu)
    {
      pSubMenu->DestroyMenu();
    }
    pCommandMenu->DeleteMenu(i, MF_BYPOSITION);
  }

  // Then add an item for each available command
  OdEdCommandStackPtr pCommandStack = ::odedRegCmds();
  bool bHasNoCommand = pCommandStack->newIterator()->done();
  pEditMenu->EnableMenuItem(nCommandMenuIndex, MF_BYPOSITION|(bHasNoCommand ? MF_GRAYED : MF_ENABLED));
  i = _APS_NEXT_COMMAND_VALUE + 100; // leave 100 ids for scales
  if(!bHasNoCommand)
  {
    OdRxIteratorPtr pGroups = pCommandStack->newGroupIterator();
    while(!pGroups->done())
    {
      OdRxDictionaryPtr pGroup = pGroups->object();
      CMenu groupMenu;
      groupMenu.CreateMenu();
      OdRxIteratorPtr pCommandIter = pGroup->newIterator(OdRx::kDictSorted);
      OdString groupName;
      while(!pCommandIter->done())
      {
        OdEdCommandPtr pCmd = pCommandIter->object().get();
        if (groupName.isEmpty())
        {
          groupName = pCmd->groupName();
        }
        groupMenu.AppendMenu(MF_STRING, i, OdString(pCmd->globalName()));
        menuItemInfo.dwItemData = (LPARAM)pCmd.get();
        VERIFY(::SetMenuItemInfo(groupMenu.m_hMenu, i, FALSE, &menuItemInfo));

        pCommandIter->next();
        ++i;
      }
      pCommandMenu->AppendMenu(MF_STRING|MF_POPUP, (LPARAM)groupMenu.Detach(), groupName);
      pGroups->next();
      groupName.empty();
    }
    pEditMenu->EnableMenuItem(nCommandMenuIndex, MF_BYPOSITION|(bHasNoCommand ? MF_GRAYED : MF_ENABLED));
  }
  m_numCustomCommands = i - _APS_NEXT_COMMAND_VALUE - 100;
}


// The one and only COdaPrcApp object
COdaPrcApp theApp;
/************************************************************************/
/* Create a Custom Dwg HostAppServices class                            */
/************************************************************************/
//OdStaticRxObject<MyDwgHostAppServices> dwgSvcs;


/************************************************************************/
/* Simple trace function                                                */
/************************************************************************/
static void myTrace(const OdChar* debugString)
{
#ifndef NDEBUG
  OutputDebugStringW((LPCWSTR)debugString);
#endif
}

/************************************************************************/
/* Displays MessageBox for Assertion failure                            */
/************************************************************************/
static void myAssert(const char* expr, const char* fileName, int nLine)
{
  USES_CONVERSION;
  char sMsg[MAX_PATH*3];
  sprintf(sMsg, "expression: \"%s\"\n\nfile: \"%s\"\nline: %d",
    expr, fileName, nLine);

  switch(MessageBox(NULL, A2CT(sMsg), _T("Assertion failed!"), MB_ICONWARNING|MB_ABORTRETRYIGNORE))
  {
  case IDABORT:
    exit(0);
    break;
  case IDRETRY:
    DebugBreak();
    break;
  case IDIGNORE:
  default:
    break;
  }
}

// COdaPrcApp initialization

BOOL COdaPrcApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
  //_set_sbh_threshold(1016); //It is not supported start from VS2010

  setlocale( LC_NUMERIC, "C" ); // saving doubles to dxf
  setlocale( LC_TIME, "" ); // correct strftime formatting

  // Change the registry key under which our settings are stored.
  SetRegistryKey(AppRegistryKey);

  settings().load(this);

  // Customize diagnostics:
  ::odSetTraceFunc(myTrace);
  ::odSetAssertFunc(myAssert);
  try
  {
#ifdef _DEBUG
    // This will cause OdaMfcApp to crash if it will perform illegal FP operation
    //_clear87();
    //_control87(
    //  //              off on
    //  //_EM_INVALID       |
    //  //_EM_DENORMAL      |
    //  //_EM_ZERODIVIDE    |
    //  //_EM_OVERFLOW      |
    //  //_EM_UNDERFLOW     |
    //  //_EM_INEXACT       ,
    //  //_MCW_EM
    //  );
#endif

#ifndef _TOOLKIT_IN_DLL_
    ODRX_INIT_STATIC_MODULE_MAP();
#endif

    // Initialize Runtime Extension environment
    odrxInitialize(this);

    CLoadApps::rxInit();

    // Register ODA PRC SDK
    ::odrxDynamicLinker()->loadModule(OdPrcModuleName, false)->addRef();
    ::odrxDynamicLinker()->loadModule(OdPrcDumpModuleName, false)->addRef();
    ::odrxDynamicLinker()->loadModule("OdPrcExCommands", true);
    ::odrxDynamicLinker()->loadModule("OdPrcCommands", true);
    ::odrxDynamicLinker()->loadModule(OdPrcPublish3dCmdsModuleName, true);

    OdPrcFileDoc::rxInit();

    m_dumper.init();
  }
  catch (OdError& err)
  {
    reportError(_T("ODA PRC SDK Initialization error"), err);
    return FALSE;
  }
#ifndef _DEBUG
  catch (...)
  {
    OdError err(eNotHandled);
    reportError(_T("ODA PRC SDK Initialization error"), err);
    return FALSE;
  }
#endif

  // InitCommonControlsEx() is required on Windows XP if an application
  // manifest specifies use of ComCtl32.dll version 6 or later to enable
  // visual styles.  Otherwise, any window creation will fail.
  INITCOMMONCONTROLSEX InitCtrls;
  InitCtrls.dwSize = sizeof(InitCtrls);
  // Set this to include all the common control classes you want to use
  // in your application.
  InitCtrls.dwICC = ICC_WIN95_CLASSES;
  InitCommonControlsEx(&InitCtrls);

  CWinApp::InitInstance();

  AfxEnableControlContainer();
  // Standard initialization
  // If you are not using these features and wish to reduce the size
  // of your final executable, you should remove from the following
  // the specific initialization routines you do not need

  LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views
  CMultiDocTemplate* pDocTemplate;
  pDocTemplate = new CMultiDocTemplate(IDR_ODAPRCAPPTYPE,
    RUNTIME_CLASS(COdaPrcAppDoc),
    RUNTIME_CLASS(CChildFrame), // custom MDI child frame
    RUNTIME_CLASS(COdaPrcTreeView));
  if (!pDocTemplate)
    return FALSE;
  AddDocTemplate(pDocTemplate);

  // create main MDI Frame window
  CMainFrame* pMainFrame = new CMainFrame;
  if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
  {
    delete pMainFrame;
    return FALSE;
  }
  m_pMainWnd = pMainFrame;
  // call DragAcceptFiles only if there's a suffix
  //  In an MDI app, this should occur immediately after setting m_pMainWnd


  // Parse command line for standard shell commands, DDE, file open
  CCommandLineInfo cmdInfo;
  ParseCommandLine(cmdInfo);
  if ( cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew ) 
    cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;


  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.
  if (!ProcessShellCommand(cmdInfo))
    return FALSE;

  WINDOWPLACEMENT wp;
  BOOL bRes = pMainFrame->GetWindowPlacement(&wp);

  wp.flags                  = GetProfileInt(_T("MainFrame"), _T("flags"),   wp.flags                  );
  wp.showCmd                = GetProfileInt(_T("MainFrame"), _T("showCmd"), wp.showCmd                );
  wp.rcNormalPosition.left  = GetProfileInt(_T("MainFrame"), _T("left"),    wp.rcNormalPosition.left  );
  wp.rcNormalPosition.top   = GetProfileInt(_T("MainFrame"), _T("top"),     wp.rcNormalPosition.top   );
  wp.rcNormalPosition.bottom= GetProfileInt(_T("MainFrame"), _T("bottom"),  wp.rcNormalPosition.bottom);
  wp.rcNormalPosition.right = GetProfileInt(_T("MainFrame"), _T("right"),   wp.rcNormalPosition.right );

  wp.ptMinPosition.x        = GetProfileInt(_T("MainFrame"), _T("Min.x"),   wp.ptMinPosition.x        );
  wp.ptMinPosition.y        = GetProfileInt(_T("MainFrame"), _T("Min.y"),   wp.ptMinPosition.y        );

  wp.ptMaxPosition.x        = GetProfileInt(_T("MainFrame"), _T("Max.x"),   wp.ptMaxPosition.x        );
  wp.ptMaxPosition.y        = GetProfileInt(_T("MainFrame"), _T("Max.y"),   wp.ptMaxPosition.y        );

  bRes = pMainFrame->SetWindowPlacement(&wp);

  // The main window has been initialized, so show and update it
  pMainFrame->ShowWindow(wp.showCmd);
  pMainFrame->UpdateWindow();

  return TRUE;
}

int COdaPrcApp::ExitInstance()
{
  try
  {
    m_dumper.uninit();

    settings().save(this);

    OdPrcFileDoc::rxUninit();
    
    
    {
      OdRxModulePtr pModule = ::odrxDynamicLinker()->getModule(OdPrcDumpModuleName);
      if (pModule.get())
      {
        pModule->release();
      }
    }
    {
      OdRxModulePtr pModule = ::odrxDynamicLinker()->getModule(OdPrcModuleName);
      if (pModule.get())
      {
        pModule->release();
      }
    }
    
    CLoadApps::rxUninit();
    ::odrxUninitialize();
  }
  catch(const OdError& e)
  {
    theApp.reportError(_T(""), e);
  }
  return CWinApp::ExitInstance();
}

/************************************************************************/
/* Returns the static OdRxClass description object associated with the  */
/* database                                                             */
/************************************************************************/
OdRxClass* COdaPrcApp::databaseClass() const
{
  return OdPrcFileDoc::desc();
}

OdPrcFilePtr COdaPrcApp::openFile(LPCTSTR lpszPathName)
{
  // Open an existing document
  OdPrcFilePtr pDb;
  CMainFrame* pMFrame = (CMainFrame*)GetMainWnd();
  pMFrame->StartTimer();
  try
  {
    CWaitCursor wait;
    OdPrcAuditInfoImplPtr auditInfo;
    if (m_bRecover)
    {
      auditInfo = OdPrcAuditInfoImpl::createObject();
      auditInfo->setFixErrors(true);
    }
    pDb = createDatabase();
    m_bLoading = true;
    pDb->readFile(OdString(lpszPathName), auditInfo.get());
    m_bLoading = false;
    pMFrame->StopTimer(_T("Loading"));
  }
  catch(const OdError& e)
  {
    setStatusText(0, _T(""));
    pDb = 0;
    reportError(_T("Loading Error..."), e);
  }
  catch(const COdaPrcAppUserBreak&)
  {
    setStatusText(0, _T(""));
    setStatusText(_T("Operation was canceled by user."));
  }
  m_bLoading = false;

  return pDb;
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
  CAboutDlg();

// Dialog Data
  enum { IDD = IDD_ABOUTBOX };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();

// Implementation
protected:
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}


OdDbLibraryInfo* odprcGetLibraryInfo();

BOOL CAboutDlg::OnInitDialog()
{
  OdDbLibraryInfo*  libInfo = odprcGetLibraryInfo();
//  OdString  sCompany = libInfo->getCompanyName();
  OdString  sLib = libInfo->getBuildComments();
  OdString  sCopyright = libInfo->getCopyright();

  CDialog::OnInitDialog();

  SetDlgItemText(IDC_INF_COPYRIGHT, sCopyright);
//  SetDlgItemText(IDC_INF_COMPANY, sCompany.c_str());
  SetDlgItemText(IDC_INF_LIBRARY, sLib);

  return TRUE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void COdaPrcApp::OnAppAbout()
{
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();
}


// COdaPrcApp message handlers


void COdaPrcApp::OnFileOpen()
{
  CString sPath = BrowseWithPreview(GetMainWnd()->GetSafeHwnd(),
    _T(".prc (*.prc)|*.prc|All Files (*.*)|*.*||"));
  if ( sPath.GetLength() )
  {
    OpenDocumentFile(sPath);
  }
}

void COdaPrcApp::OnFileRecover()
{
  theApp.setRecoverOption(true);
  theApp.OnFileOpen();
  theApp.setRecoverOption(false);
}

void COdaPrcPreviewDIB::SetPreviewFile(LPCTSTR lpFileName)
{
//   CString  csFileName(lpFileName);
// 
//   m_odImage.header.clear();
//   m_odImage.bmp.clear();
//   m_odImage.wmf.clear();
//   m_odImage.png.clear();
// 
//   if (!csFileName.GetLength())
//     return;
// 
//   CString ext = csFileName.Right(4);
//   ext.MakeLower();
// 
//   if (ext == _T(".rfa") || ext == _T(".rvt"))
//   {
//     OdStreamBufPtr pFile;
//     try
//     {
// //       theApp.getPreviewImage(OdString(csFileName), m_odImage);
// //       m_odImage.convPngToBmp();
//     }
//     catch (...)
//     {
//       return;
//     }
//   }
}

CRect COdaPrcPreviewDIB::Calc(int bmpWid, int bmpDep, int wndWid, int wndDep)
{
  int d, w, x, y;
  if (bmpDep > bmpWid)
  {
    d = __min(bmpDep, wndDep);
    w = (bmpWid*d) / bmpDep;
    if (w > wndWid)
    {
      d = (d*wndWid) / w;
      w = wndWid;
    }
  }
  else
  {
    w = __min(bmpWid, wndWid);
    d = (bmpDep*w) / bmpWid;
    if (d > wndDep)
    {
      w = (w*wndDep) / d;
      d = wndDep;
    }
  }
  x = (wndWid - w) / 2;
  y = (wndDep - d) / 2;
  return CRect(x, y, x + w, y + d);
}
// Placeable metafile data definitions
typedef struct tagOLDRECT
{
  short left;
  short top;
  short right;
  short bottom;
} OLDRECT;

// Placeable metafile header
typedef struct {
  DWORD   key;
  WORD    hmf;
  OLDRECT bbox;
  WORD    inch;
  DWORD   reserved;
  WORD    checksum;
} ALDUSMFHEADER;

#define METAFILE_VERSION    1
#define ALDUSKEY            0x9AC6CDD7
#define ALDUSMFHEADERSIZE   22  // Avoid sizeof is struct alignment >1

void COdaPrcPreviewDIB::DrawPreview(HDC dc, int X, int Y, int width, int height)
{
  CRect   cr;

  if (m_odImage.hasBmp())
  {
    BITMAPINFOHEADER *pHeader;
    pHeader = (BITMAPINFOHEADER *)(m_odImage.bmp.begin());

    cr = Calc(pHeader->biWidth, pHeader->biHeight, width, height);

    unsigned char *p = (unsigned char*)pHeader;
    p += pHeader->biSize;
    switch (pHeader->biBitCount)
    {
    case 1:
      p += sizeof(RGBQUAD)* 2;
      break;
    case 4:
      p += sizeof(RGBQUAD)* 16;
      break;
    case 8:
      p += sizeof(RGBQUAD)* 256;
      break;
    }

    StretchDIBits(dc, cr.left + X, cr.top + Y, cr.Width(), cr.Height(), 0, 0,
      pHeader->biWidth, pHeader->biHeight, (const void *)p,
      (CONST BITMAPINFO *)pHeader, DIB_RGB_COLORS, SRCCOPY);
  }
  else if (m_odImage.hasWmf())
  {
    CDC     newDC;
    DWORD   dwIsAldus;
    METAHEADER*    mfHeader = NULL;
    ALDUSMFHEADER* aldusMFHeader = NULL;

    DWORD dwSize;
    DWORD seekpos;

    newDC.Attach(dc);
    dwIsAldus = *((DWORD*)m_odImage.wmf.begin());
    if (dwIsAldus != ALDUSKEY)
    {
      seekpos = 0;
    }
    else
    {
      aldusMFHeader = (ALDUSMFHEADER*)m_odImage.wmf.begin();
      seekpos = ALDUSMFHEADERSIZE;
    }
    BYTE *p = (BYTE *)m_odImage.wmf.begin();
    mfHeader = (METAHEADER*)(p + seekpos);

    if ((mfHeader->mtType != 1) && (mfHeader->mtType != 2))
      return;

    dwSize = mfHeader->mtSize * 2;
    // Create the enhanced metafile
    HENHMETAFILE m_emf;
    m_emf = ::SetWinMetaFileBits(dwSize, (const BYTE*)mfHeader, NULL, NULL);

    CSize size(0, 0);
    if (aldusMFHeader)
    {
      size.cx = 254 * (aldusMFHeader->bbox.right - aldusMFHeader->bbox.left)
        / aldusMFHeader->inch;
      size.cy = 254 * (aldusMFHeader->bbox.bottom - aldusMFHeader->bbox.top)
        / aldusMFHeader->inch;
    }

    cr = Calc(size.cx, size.cy, width, height);
    cr.OffsetRect(X, Y);
    newDC.PlayMetaFile(m_emf, &cr);

  }
}

#if !defined(TD_DLL_VERSION_SUFFIX_STR)
#define TD_DLL_VERSION_SUFFIX_STR L""
#endif

CString COdaPrcApp::BrowseWithPreview(HWND hWndParent, LPCTSTR caFilter)
{
  CString sFileBuff;
  HINSTANCE hinstLib = LoadLibrary(OdString(_T("FileDlgExt"))
#ifndef _UNICODE
    + "Ansi"
#endif
    + OdString(TD_DLL_VERSION_SUFFIX_STR) + OdString(_T(".dll")));

  if (NULL != hinstLib)
  {
    ODA_OPEN_DLGPROC fpDlgProc = (ODA_OPEN_DLGPROC)GetProcAddress(hinstLib, "CreateOpenWithPreviewDlg");
    if (NULL != fpDlgProc)
    {
      COdaPrcPreviewDIB statDib;
      OpenWithPreviewDlg *pDlg;
      (fpDlgProc)(&statDib, hWndParent, NULL, caFilter,
        OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR |OFN_PATHMUSTEXIST,
        &pDlg);
      if (IDOK == pDlg->ShowModal())
      {
        long nSize = _MAX_PATH;

        pDlg->GetFullFileName(sFileBuff.GetBuffer(nSize), nSize);
        sFileBuff.ReleaseBuffer();
      }
      pDlg->ReleaseDlg();
    }
    FreeLibrary(hinstLib);
  }
  else
  {    // use alternate method for OpenFile dialog
    OPENFILENAME  ofn;

    // replace the '|' character with '\0'
    CString filter;
    long l = (long)_tcslen(caFilter), l2 = l;
    LPTSTR buff = filter.GetBuffer(l);
    while (--l >= 0)
    {
      if (caFilter[l] == '|')
        buff[l] = '\0';
      else
        buff[l] = caFilter[l];
    }
    filter.ReleaseBuffer(l2);

    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = hWndParent;
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = sFileBuff.GetBuffer(_MAX_PATH);
    ofn.nMaxFile = _MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR |OFN_PATHMUSTEXIST;

    GetOpenFileName(&ofn);
    sFileBuff.ReleaseBuffer();
  }
  return sFileBuff;
}

void COdaPrcApp::OnToolsLoadapplications()
{
  CLoadApps appDlg;
  appDlg.DoModal();
}

CMenu* getVectorizeMenu2(CMenu* pMainMenu) 
{
  unsigned menuPos = 3;
  MENUITEMINFO menuItemInfo;
  menuItemInfo.cbSize = sizeof(menuItemInfo);
  menuItemInfo.fMask = MIIM_TYPE;
  menuItemInfo.fType = MFT_STRING;
  menuItemInfo.dwTypeData = 0;
  pMainMenu->GetMenuItemInfo(menuPos, &menuItemInfo, TRUE);
  if ( menuItemInfo.cch != odStrLenA("Vectorize") )
    menuPos = 4;
  return pMainMenu->GetSubMenu(menuPos);
}

bool AddGsMenuItem(CMenu* pVectorizeMenu, DWORD& nIndex, LPCTSTR szPath) 
{
  if(ID_VECTORIZER_FIRST + nIndex <= ID_VECTORIZER_LAST)
  {
    MENUITEMINFO menuItemInfo;
    menuItemInfo.cbSize = sizeof(menuItemInfo);
    menuItemInfo.fMask = MIIM_DATA;

    pVectorizeMenu->InsertMenu(nIndex, MF_BYPOSITION, ID_VECTORIZER_FIRST + nIndex, szPath);

    menuItemInfo.dwItemData = theApp.getGSMenuItemMarker();
    VERIFY(::SetMenuItemInfo(pVectorizeMenu->m_hMenu, nIndex, TRUE, &menuItemInfo));

    if ( theApp.settings().getGsDevicePath().iCompare( OdString(szPath) ) == 0 )
    {
      pVectorizeMenu->CheckMenuItem(nIndex, MF_BYPOSITION|MF_CHECKED);
    }
    ++nIndex;
    return true;
  }
  return false;
}

CString COdaPrcApp::getApplicationPath()
{
  TCHAR path[MAX_PATH];
  ::GetModuleFileName(::GetModuleHandle(0), path, MAX_PATH);
  CString s_path(path);
  int nLen = s_path.ReverseFind('\\');
  s_path = s_path.Left(nLen);
  return s_path;
}

void COdaPrcApp::OnVectorizeAddvectorizerdll()
{
  CMenu* pVectorizeMenu = getVectorizeMenu2(GetMainWnd()->GetMenu());

#ifdef _TOOLKIT_IN_DLL_
  CFileDialog dlg( TRUE, _T("gs"), _T(""),
    OFN_HIDEREADONLY | OFN_EXPLORER | OFN_PATHMUSTEXIST,
    _T("Graphic System DLL (*.txv)|*.txv|Windows DLL (*.dll)|*.dll||"), ::AfxGetMainWnd() );

  dlg.m_ofn.lpstrTitle = _T("Select Graphic System DLL");

  CString s_path = getApplicationPath();
  dlg.m_ofn.lpstrInitialDir = s_path.GetBuffer(s_path.GetLength());

#else
  CStaticAppSelDlg dlg(::AfxGetMainWnd());
#endif //#ifdef _TOOLKIT_IN_DLL_

  if ( dlg.DoModal() == IDOK )
  {
    OdString path(dlg.GetFileName());
#ifdef _TOOLKIT_IN_DLL_
    path.replace(TD_DLL_VERSION_SUFFIX_STR, "");
#endif
    DWORD nIndex = settings().getNumGSMenuItems();
    //if ( nIndex == 0 || settings().getGsDevicePath().isEmpty())
    settings().setGsDevicePath( path );

    AddGsMenuItem(pVectorizeMenu, nIndex, path );
    settings().setNumGSMenuItems(nIndex);
    WriteProfileString(_T("options\\vectorizers"), settings().getGsDevicePath(), _T(""));
    GetMainWnd()->SendMessage(WM_COMMAND, ID_VECTORIZE);
  }
}

void COdaPrcApp::OnUpdateVectorizeAddvectorizerdll(CCmdUI *pCmdUI)
{
  if (settings().getNumGSMenuItems() != 0) return;
  CMenu* pVectorizeMenu = getVectorizeMenu2(GetMainWnd()->GetMenu());
  TP_CRegKey rk;
  rk.Create(HKEY_CURRENT_USER, _T("Software\\") AppRegistryKey _T("\\OdaPrcApp\\options\\vectorizers"));

  CString path;
  DWORD pathSize;
  for(;;) {
    pathSize = _MAX_FNAME + _MAX_EXT;
    DWORD err = ::RegEnumValue(rk, settings().getNumGSMenuItems(),
      path.GetBuffer(pathSize), &pathSize, NULL, NULL, NULL, NULL);
    path.ReleaseBuffer();
    if ( err != ERROR_SUCCESS ) break;
    DWORD nIndex = settings().getNumGSMenuItems();
    if ( settings().getGsDevicePath().isEmpty() ) {
      OdString sPath = path;
      settings().setGsDevicePath( OdString(sPath) );
    }

    if ( AddGsMenuItem(pVectorizeMenu, nIndex, path) ) {
      settings().setNumGSMenuItems(nIndex);
    }
    else
    {
      break;
    }
  }
}

void COdaPrcApp::OnVectorizeClearmenu()
{
  CMenu* pVectorizeMenu = getVectorizeMenu2(GetMainWnd()->GetMenu());
  while ( pVectorizeMenu->GetMenuItemCount() > 3 )
  {
    pVectorizeMenu->RemoveMenu(0, MF_BYPOSITION);
  }
  TP_CRegKey rk;
  rk.Create(HKEY_CURRENT_USER, _T("Software\\") AppRegistryKey _T("\\OdaPrcApp\\options"));
  rk.RecurseDeleteKey(_T("vectorizers"));
  settings().setGsDevicePath(OdString::kEmpty);
  settings().setNumGSMenuItems(0);
}

void COdaPrcApp::OnUpdateGsDevices(CCmdUI *pCmdUI) {
  CString str;
  pCmdUI->Enable(TRUE);

  if (pCmdUI->m_pMenu == NULL) return;

  pCmdUI->m_pMenu->GetMenuString(pCmdUI->m_nIndex, str, MF_BYPOSITION);
  BOOL b = str.CompareNoCase(settings().getGsDevicePath().c_str()) == 0;
  pCmdUI->SetCheck(b);
}

void COdaPrcApp::OnUpdateVectorizeClearmenu(CCmdUI *pCmdUI)
{
  pCmdUI->Enable(settings().getNumGSMenuItems() > 0);
}

void COdaPrcApp::OnUpdateVectorize(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable(FALSE); // Always false, because only OdaMfcAppDoc can start vectorization
}

const ODCOLORREF* COdaPrcApp::curPalette() const
{
  return odcmAcadPalette(settings().getActiveBackground());
}

void COdaPrcApp::setStatusText(LPCTSTR msg)
{
  ((CMainFrame*)GetMainWnd())->setStatusText(msg);
}

void COdaPrcApp::setStatusText(int nCol, LPCTSTR msg)
{
  ((CMainFrame*)GetMainWnd())->setStatusText(nCol, msg);
}

void COdaPrcApp::warning(const OdString& sm)
{
  if ( m_bLoading )
  {
    OdString sMsg(sm);
    sMsg += _T("\n\nDo you want to proceed ?");
    if (MessageBox (NULL, sMsg, _T("Warning!"), MB_ICONWARNING|MB_YESNO) == IDNO )
      throw COdaPrcAppUserBreak();
  }
}

void COdaPrcApp::OnOptionsDiscardbackfaces() 
{
  settings().setDiscardBackFaces(!settings().discardBackFaces());
}

void COdaPrcApp::OnUpdateOptionsDiscardbackfaces(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(settings().discardBackFaces());
}

void COdaPrcApp::OnOptionsUseGsModel()
{
  settings().setUseGsModel(!settings().useGsModel());
}

void COdaPrcApp::OnUpdateOptionsUseGsModel(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(settings().useGsModel());
}

#ifdef PDFIUM_MODULE_ENABLED
void COdaPrcApp::OnExtract3DStream()
{
  Extract3DStreamDialog dlg(theApp.GetMainWnd());
  if (dlg.DoModal() == IDOK)
  {
    CMainFrame* pMFrame = (CMainFrame*)GetMainWnd();
    pMFrame->StartTimer();
    OnFileNew();
    COdaPrcAppDoc* pDoc;
    CMDIChildWnd* pWnd;
    pWnd = pMFrame->MDIGetActive();
    if (pWnd)
    {
      pDoc = (COdaPrcAppDoc*)pWnd->GetActiveDocument();
      if (pDoc)
      {
        OdStreamBufPtr stream = dlg.getStream();
        stream->rewind();
        pDoc->m_pDb->readFile(stream);
        pDoc->SetTitle(dlg.getStreamName());
        pDoc->UpdateAllViews(0);
      }
    }
    pMFrame->StopTimer(_T("Extracting"));
  }
}
#endif // PDFIUM_MODULE_ENABLED

/////////////////////////////////////////////////////////////////////////////
#ifdef _MT
#ifndef _DLL

// For MT configurations only
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
extern "C" {

  ALLOCDLL_EXPORT void* odrxAlloc(size_t s)
  {
    return ::malloc(s);
  }

  ALLOCDLL_EXPORT void* odrxRealloc(void* p, size_t new_size, size_t /*old_size*/)
  {
    return ::realloc(p, new_size);
  }

  ALLOCDLL_EXPORT void odrxFree(void* p) 
  {
    ::free(p);
  }

} // extern "C"
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#endif
#endif
