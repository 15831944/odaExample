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

#ifndef _AFX_ODAPRCAPPDOC__INCLUDED_
#define _AFX_ODAPRCAPPDOC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>
#include "PrcFile.h"
#include "ExPrcCommandContext.h"
#include "ExStringIO.h"

class CUserIOConsole;
class COdaPrcAppDoc;
class OdaPrcExViewer;

class OdPrcFileDoc : public OdPrcFile
{
  static  COdaPrcAppDoc*  g_pDoc;
  mutable COdaPrcAppDoc*  m_pDoc;
public:
  ODRX_DECLARE_MEMBERS(OdPrcFileDoc);

  OdPrcFileDoc();

  COdaPrcAppDoc* document() const;

  static void setDocToAssign(COdaPrcAppDoc* pDoc);
};

typedef OdSmartPtr<OdPrcFileDoc> OdPrcFileDocPtr;

class COdaPrcAppDocStaticRxObjects : //public OdDbLayoutManagerReactor, 
                                     public OdEdBaseIO
{
  ODRX_NO_HEAP_OPERATORS();
};

class COdaPrcAppDoc :
  public CDocument,//COleDocument,
  protected OdStaticRxObject<COdaPrcAppDocStaticRxObjects>
{
private:
  void createPreviewFile();

  // Constructor/destructor
protected:
  // create from serialization only
  using CDocument::operator new;
  using CDocument::operator delete;
  COdaPrcAppDoc();
  DECLARE_DYNCREATE(COdaPrcAppDoc)

  OdPrcCommandContextPtr cmdCtx();
  OdEdBaseIO* cmdIO();
  OdString commandPrompt();
  OdString recentCmd();
  OdString recentCmdName();
  CUserIOConsole* console();

  // OdEdBaseIO
  OdString getString(const OdString& prompt, int options, OdEdStringTracker* pTracker);
  void putString(const OdString& string);
  OdGePoint3d getPoint(const OdString& prompt, int options, OdEdPointTracker* pTracker);
  virtual OdUInt32 getKeyState();

  OdPrcCommandContextPtr      m_pCmdCtx;
  OdPrcFilePtr                m_pDb;
  OdaPrcExViewer*             m_pVectorizer;
  int                         m_nCmdActive;
  OdSmartPtr<CUserIOConsole>  m_pConsole;
  OdSmartPtr<ExStringIO>      m_pMacro;

  bool                        m_bConsole;
  bool                        m_bConsoleResponded;
  //OdPrcElementId m_vectorizedModelId;
  //OdPrcElementId m_vectorizedViewId;

  int m_SaveAsVer;
  int m_SaveAsType;

  const OdString kPreviewFileName;

  // Generated message map functions
protected:
  //{{AFX_MSG(COdaMfcAppDoc)
  afx_msg void OnVectorize();
  afx_msg void OnUpdateVectorize(CCmdUI* pCmdUI);
  afx_msg void OnViews();
  afx_msg void On3DViews(UINT nID);
  afx_msg void OnZoomExtents();
  afx_msg void OnEditConsole();
  afx_msg void OnOptionsTriangulationParams();
  afx_msg void OnEditRecentcommand();
  afx_msg void OnUpdateEditRecentcommand(CCmdUI* pCmdUI);
  afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
  afx_msg void OnFormatBackgroundColor();
  afx_msg void OnU3DImport();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
  
public:
  virtual ~COdaPrcAppDoc();

  // Attributes
  OdPrcFile* database() { return m_pDb; }
  //OdPrcElementId vectorizedViewId() { return m_vectorizedViewId; }
  //OdPrcElementId vectorizedModelId() { return m_vectorizedModelId; }

  // Operations
public:
  void OnCloseVectorizer(OdaPrcExViewer* pView);
  void OnVectorize(const OdString& sVectorizerPath);
  virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

  // Overrides
  virtual BOOL OnNewDocument();
  virtual void OnCloseDocument();
  virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
  virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
  virtual void Serialize(CArchive& ar);
  virtual BOOL CanCloseFrame(CFrameWnd* pFrame);

  // Implementation
  BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate);
  virtual BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace = TRUE);
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  OdaPrcExViewer* getViewer();
  void ExecuteCommand(const OdString& sCmd, bool bEcho = true);
  afx_msg void OnNamedViews();
};

#endif // _AFX_ODAPRCAPPDOC__INCLUDED_

