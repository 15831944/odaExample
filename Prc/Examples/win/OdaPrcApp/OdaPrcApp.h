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
// OdaPrcApp.h : main header file for the OdaPrcApp application
//
#pragma once

#ifndef __AFXWIN_H__
  #error "include 'stdafx.h' before including this file for PCH"
#endif

#ifndef APSTUDIO_INVOKED
#define DOUNDEF_APSTUDIO_INVOKED
#endif
#ifdef APSTUDIO_READONLY_SYMBOLS
#define DODEF_APSTUDIO_READONLY_SYMBOLS
#endif

#define APSTUDIO_INVOKED
#undef APSTUDIO_READONLY_SYMBOLS

#include "Resource.h"

#include "ExPrcServices.h"
#include "ExPrcHostAppServices.h"
#include "PrcFile.h"
#include "ExPrcElementDumperPE.h"
#include "ThumbnailImage.h"
#include "TDVersion.h"
#include "FileDlgExt.h"

#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a

class COdaPrcAppUserBreak
{
};

class COdaPrcPreviewDIB : public CAbstractPreview
{
public:
  void  SetPreviewFile(LPCTSTR lpFileName);
  void  DrawPreview(HDC dc, int x, int y, int width, int height);
  CRect Calc(int bmpWid, int bmpDep, int wndWid, int wndDep);

  OdThumbnailImage m_odImage;
};

// COdaPrcApp:
// See OdaPrcApp.cpp for the implementation of this class
//

class COdaPrcAppSettings
{
public:
  COdaPrcAppSettings()
    : m_background(ODRGB(64, 64, 64))
    , m_numGSMenuItems(0)
    , m_bDiscardBackFaces(TRUE)
    , m_bUseGsModel(TRUE)
  {}

  void load(CWinApp* pApp)
  {
    m_bDiscardBackFaces   = pApp->GetProfileInt   (_T("options"), _T("Discard Back Faces"),   TRUE);
    //// m_bEnableDoubleBuffer = GetProfileInt   (_T("options"), _T("Enable Double Buffer"),        1);
    //m_bEnableDoubleBuffer = 1; // m_bEnableDoubleBuffer = 0 is for debug use only
    //m_bEnablePrintPreviewViaBitmap = GetProfileInt   (_T("options"), _T("Print/Preview via bitmap device"), 1);
    m_bUseGsModel         = pApp->GetProfileInt   (_T("options"), _T("UseGsModel"),           TRUE);
    //m_bEnableHLR          = GetProfileInt   (_T("options"), _T("Enable Software HLR"),         0);
    //m_isDwgOut            = GetProfileInt   (_T("options"), _T("View object in DWG format"),   0);
    //m_bSaveRoundTrip      = GetProfileInt   (_T("options"), _T("Save round trip information"), 1);
    //m_bSavePreview        = GetProfileInt   (_T("options"), _T("Save Preview"),                0);
    m_background =          pApp->GetProfileInt   (_T("format"), _T("Background colour"), ODRGB(64, 64, 64));
    //m_bSaveWithPassword   = GetProfileInt   (_T("options"), _T("Save DWG with password"),      0);
    m_vectorizerPath     = pApp->GetProfileString(_T("options"), _T("recent GS"), _T(""));
    m_sRecentCmd          = pApp->GetProfileString(_T("options"), _T("Recent Command"),              _T(""));
    //int nFillTtf          = GetProfileInt   (_T("options"), _T("Fill TTF text"),               1);
  }

  void save(CWinApp* pApp)
  {
    pApp->WriteProfileInt(_T("format"), _T("Background colour"), m_background);
    pApp->WriteProfileString(_T("options"), _T("recent GS"), m_vectorizerPath);
    pApp->WriteProfileString(_T("options"), _T("Recent Command"), m_sRecentCmd);
    pApp->WriteProfileInt(_T("options"), _T("Discard Back Faces"), m_bDiscardBackFaces);
    pApp->WriteProfileInt(_T("options"), _T("UseGsModel"), m_bUseGsModel);
  }

  OdString getGsDevicePath() const
  {
    return m_vectorizerPath;
  }
  void setGsDevicePath(const OdString& vectorizerPath)
  {
    m_vectorizerPath = vectorizerPath;
  }

  const OdString& getRecentCmd() { return m_sRecentCmd; }

  void setRecentCmd(const OdString& cmd)
  {
    if ( !cmd.isEmpty() && cmd != m_sRecentCmd )
    {
      m_sRecentCmd = cmd;
    }
  }

  const ODCOLORREF  getActiveBackground() const { return m_background; }
  void setActiveBackground(const ODCOLORREF &color) { m_background = color&0xffffff;}

  DWORD getNumGSMenuItems() { return m_numGSMenuItems; }
  void setNumGSMenuItems(DWORD val) { m_numGSMenuItems = val; }

  bool discardBackFaces() const { return m_bDiscardBackFaces!=0; }
  void setDiscardBackFaces(bool discardBF) { m_bDiscardBackFaces=discardBF ? TRUE : FALSE; }

  bool useGsModel() const { return m_bUseGsModel!=0; }
  void setUseGsModel(bool useGsMod) { m_bUseGsModel=useGsMod ? TRUE : FALSE; }

private:
  OdString   m_vectorizerPath;
  ODCOLORREF m_background;
  DWORD      m_numGSMenuItems;
  OdString   m_sRecentCmd;
  BOOL       m_bDiscardBackFaces;
  BOOL       m_bUseGsModel;
};


class COdaPrcApp : public CWinApp
                 , public OdRxObjectImpl<OdExPrcSystemServices>
                 , public OdRxObjectImpl<OdExPrcHostAppServices>
{
protected:
  using CWinApp::operator new;
  using CWinApp::operator delete;
public:
  COdaPrcApp();

  CMenu* CommandMenu(CMenu** ppEditMenu);
  void RefreshCommandMenu();
  UINT numCustomCommands() const { return m_numCustomCommands; }


  OdPrcFilePtr openFile(LPCTSTR lpszPathName);

  COdaPrcAppSettings& settings() { return m_settings; }
  const COdaPrcAppSettings& settings() const { return m_settings; }

  OdGsMarker getGSMenuItemMarker() const { return (OdGsMarker)this; }

  // OdRxSystemServices overridden
  virtual void warning(const OdString& message);

private:
  CString BrowseWithPreview(HWND hWndParent, LPCTSTR caFilter);

  OdPrcDumper           m_dumper;

public:
  static int messageBox(HWND hParent, LPCTSTR lpCaption, LPCTSTR lpText, UINT uType)
  {
    return ::MessageBox(hParent, lpText, lpCaption, uType);
  }
  int messageBox(LPCTSTR lpCaption, LPCTSTR lpText, UINT uType)
  {
    CWnd* pMainWnd = GetMainWnd();
    HWND hWnd = 0;
    if(pMainWnd)
      hWnd = pMainWnd->m_hWnd;
    return messageBox(hWnd, lpCaption, lpText, uType);
  }
  void reportError(HWND hParent, LPCTSTR szContextMsg, const OdError& e)
  {
    messageBox(hParent, szContextMsg, (LPCTSTR)e.description(), MB_OK|MB_ICONERROR);
  }
  void reportError(LPCTSTR szContextMsg, const OdError& e)
  {
    messageBox(szContextMsg, (LPCTSTR)e.description(), MB_OK|MB_ICONERROR);
  }
  //void reportError(LPCTSTR szContextMsg, unsigned int eCode)
  //{
  //  messageBox(szContextMsg, (LPCTSTR)getErrorDescription(eCode), MB_OK|MB_ICONERROR);
  //}
  OdRxClass* databaseClass() const;

  const ODCOLORREF* curPalette() const;

  void setStatusText(LPCTSTR msg);
  void setStatusText(int nCol, LPCTSTR msg);

  CString getApplicationPath();

private:
  COdaPrcAppSettings m_settings;
  bool               m_bLoading;
  bool               m_bRecover;
  UINT       m_numCustomCommands;
  
  OdDbBaseHostAppServices* m_pDwgHostApp;

// Overrides
public:
  virtual BOOL InitInstance();
  virtual int ExitInstance();

  void setRecoverOption(bool val) { m_bRecover = val; }

  //{{AFX_MSG(COdaPrcApp)
  afx_msg void OnAppAbout();
  afx_msg void OnFileOpen();
  afx_msg void OnFileRecover();
  afx_msg void OnViews();
  afx_msg void OnToolsLoadapplications();
  afx_msg void OnToolsModelerOptions();
  afx_msg void OnVectorizeAddvectorizerdll();
  afx_msg void OnUpdateVectorizeAddvectorizerdll(CCmdUI *pCmdUI);
  afx_msg void OnUpdateGsDevices(CCmdUI *pCmdUI);
  afx_msg void OnVectorizeClearmenu();
  afx_msg void OnUpdateVectorizeClearmenu(CCmdUI *pCmdUI);
  afx_msg void OnUpdateVectorize(CCmdUI* pCmdUI);
  afx_msg void OnOptionsDiscardbackfaces();
  afx_msg void OnUpdateOptionsDiscardbackfaces(CCmdUI* pCmdUI);
  afx_msg void OnOptionsUseGsModel();
  afx_msg void OnUpdateOptionsUseGsModel(CCmdUI* pCmdUI);
#ifdef PDFIUM_MODULE_ENABLED
  afx_msg void OnExtract3DStream();
#endif //PDFIUM_MODULE_ENABLED
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

extern COdaPrcApp theApp;
