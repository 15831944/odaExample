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
// OdaPrcAppDoc.cpp : implementation of the COdaPrcAppDoc class
//

#include "stdafx.h"
#include "OdaPrcApp.h"
#include "OdaPrcAppDoc.h"
#include "OdaPrcTreeView.h"
#include "OdaPrcExViewer.h"
#include "MainFrm.h"
#include "ViewsDialog.h"
#include "OdStreamBuf.h"
#include "GiGs/PrcGiContext.h"
#include "Gs/GsModel.h"
#include "SaveState.h"
#include "Ed/EdCommandStack.h"
#include "ExPrcCommandContext.h"
#include "UserIOConsole.h"
#include "Gs/Gs.h"
#include "Gs/GsViewImpl.h"
#include "SmartClsIdPtr.h"
#include "Wr/wrTriangulationParams.h"
#include "AbstractViewPE.h"
#include "OdaTrianParamsDlg.h"
#include "ViewsDlg.h"
#include "ColorPickerDlg.h"

#define NEW_CONSTR(CLASS) OdRxObjectImpl<OdPrcFileDoc>::createObject()

ODRX_CONS_DEFINE_MEMBERS(OdPrcFileDoc, OdPrcFile, NEW_CONSTR);

COdaPrcAppDoc* OdPrcFileDoc::g_pDoc = 0;

OdPrcFileDoc::OdPrcFileDoc() : m_pDoc(g_pDoc)
{
  g_pDoc = 0;
}

COdaPrcAppDoc* OdPrcFileDoc::document() const
{
  return m_pDoc;
}

void OdPrcFileDoc::setDocToAssign(COdaPrcAppDoc* pDoc)
{
  g_pDoc = pDoc;
}


void COdaPrcAppDoc::OnEditRecentcommand() 
{
  ExecuteCommand(theApp.settings().getRecentCmd());
}


void COdaPrcAppDoc::OnUpdateEditRecentcommand(CCmdUI* pCmdUI) 
{
  OdString sTxt;
  OdString sRecentCmd = theApp.settings().getRecentCmd();
  OdEdCommandPtr pCmd;
  if (!sRecentCmd.isEmpty())
    pCmd = ::odedRegCmds()->lookupCmd(sRecentCmd.spanExcluding(L" \n"));
  if (pCmd.get())
  {
    pCmdUI->Enable(TRUE);
    sRecentCmd.replace(L"\n",L"\\n");
    sTxt.format(L"ExecuteCommand \"%s\"", sRecentCmd.c_str());
  }
  else
  {
    pCmdUI->Enable(FALSE);
    sTxt = L"Recent command";
  }
  pCmdUI->SetText(sTxt);
}


// COdaPrcAppDoc

IMPLEMENT_DYNCREATE(COdaPrcAppDoc, CDocument)

BEGIN_MESSAGE_MAP(COdaPrcAppDoc, CDocument)
  //{{AFX_MSG_MAP(COdaPrcAppDoc)
  ON_COMMAND(ID_VECTORIZE, OnVectorize)
  ON_UPDATE_COMMAND_UI(ID_VECTORIZE, OnUpdateVectorize)
  ON_COMMAND( ID_EDIT_ZOOMEXTENTS, OnZoomExtents )
  //ON_COMMAND( ID_VIEWS, OnViews )
  ON_COMMAND_RANGE(ID_3DVIEWS_TOP, ID_3DVIEWS_BACK, On3DViews)
  ON_COMMAND( ID_EDIT_CONSOLE, OnEditConsole)
  ON_COMMAND(ID_OPTIONS_TRIANGULATION_PARAMS, OnOptionsTriangulationParams)
  ON_COMMAND(ID_EDIT_RECENTCOMMAND, OnEditRecentcommand)
  ON_UPDATE_COMMAND_UI(ID_EDIT_RECENTCOMMAND, OnUpdateEditRecentcommand)
  ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
  //}}AFX_MSG_MAP
  ON_COMMAND(ID_NAMED_VIEWS, OnNamedViews)
  ON_COMMAND(ID_FORMAT_BACKGROUNDCOLOR, OnFormatBackgroundColor)
  ON_COMMAND(ID_U3D_IMPORT, OnU3DImport)
END_MESSAGE_MAP()


// COdaPrcAppDoc construction/destruction

COdaPrcAppDoc::COdaPrcAppDoc()
    : m_SaveAsVer(0)
    , m_SaveAsType(0)
    , kPreviewFileName(L"Preview.png")
    , m_pVectorizer(NULL)
    , m_nCmdActive(0)
    , m_bConsole(false)
{
  // TODO: add one-time construction code here
}

COdaPrcAppDoc::~COdaPrcAppDoc()
{
}

void COdaPrcAppDoc::OnCloseDocument( )
{
  CDocument::OnCloseDocument();
}

BOOL COdaPrcAppDoc::OnNewDocument()
{
  if (!CDocument::OnNewDocument())
    return FALSE;

  OdPrcFileDoc::setDocToAssign(this);

  m_pDb = theApp.createDatabase();
  m_pDb->setVersions(8137, 8137);
  m_pDb->fileStructureId() = OdPrcUniqueId::generateUID();
  theApp.setStatusText(_T("Default Database Created."));
  return TRUE;
}

void COdaPrcAppDoc::createPreviewFile()
{
  if (m_pDb.isNull())
    return;

  //TODO: prewiev
  /*OdStreamBufPtr pFile = theApp.createFile(OdString(kPreviewFileName),Oda::kFileWrite, Oda::kShareDenyNo, Oda::kCreateAlways);
  const OdBinaryData& imageData = m_pDb->getPreviewImageData();
  
  pFile->seek(0, OdDb::FilerSeekType::kSeekFromStart);
  pFile->putBytes(imageData.asArrayPtr(), imageData.size());*/
}

BOOL COdaPrcAppDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
  OdPrcFileDoc::setDocToAssign(this);
  m_pDb = theApp.openFile(lpszPathName);
  //createPreviewFile();
  return !m_pDb.isNull();
}

BOOL COdaPrcAppDoc::DoPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* /*pTemplate*/)
{
  //OdDb::DwgVersion dwgver = m_pDb->getOriginalFileVersion();
  CString ext = fileName.Right(3);

  CFileDialog dlgFile(bOpenFileDialog);

  CString title;
  VERIFY(title.LoadString(nIDSTitle));

  dlgFile.m_ofn.Flags |= lFlags;

  CString strFilter;
  CString strDefault;

  strFilter = _T(".prc file format (*.prc)");
  strFilter += (TCHAR)'\0';   // next string please
  strFilter += _T("*.prc");
  strFilter += (TCHAR)'\0';   // last string
  dlgFile.m_ofn.nMaxCustFilter++;

  dlgFile.m_ofn.nFilterIndex = 1;

  if (fileName.Find('.') != -1)
  {
    fileName = fileName.Left(fileName.Find('.'));
  }

  dlgFile.m_ofn.lpstrFilter = strFilter;
  dlgFile.m_ofn.lpstrTitle = title;
  dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

  INT_PTR nResult = dlgFile.DoModal();
  fileName.ReleaseBuffer();

  if (fileName.Find('.') == -1)
  {
    fileName += _T(".prc");
  }

  m_SaveAsType = 0;
  switch ( dlgFile.m_ofn.nFilterIndex )
  {
  case 1:
    m_SaveAsVer = 0;
    break;
  case 2:
    m_SaveAsVer = 1;
    break;
  default:
    m_SaveAsVer = 0;
    //m_SaveAsVer = m_pDb->getOriginalFileVersion();
  };

  return nResult == IDOK;
}

BOOL COdaPrcAppDoc::DoSave(LPCTSTR lpszPathName, BOOL bReplace)
// Save the document data to a file
// lpszPathName = path name where to save document file
// if lpszPathName is NULL then the user will be prompted (SaveAs)
// note: lpszPathName can be different than 'm_strPathName'
// if 'bReplace' is TRUE will change file name if successful (SaveAs)
// if 'bReplace' is FALSE will not change path name (SaveCopyAs)
{
  //m_SaveAsVer = m_pDb->getOriginalFileVersion();

  CString newName = lpszPathName;
  if (newName.IsEmpty())
  {
    CDocTemplate* pTemplate = GetDocTemplate();
    ODA_ASSERT(pTemplate != NULL);

    newName = m_strPathName;
    if (bReplace && newName.IsEmpty())
    {
      newName = m_strTitle;
      // check for dubious filename
      int iBad = newName.FindOneOf(_T(" #%;/\\"));
      if (iBad != -1)
        newName.ReleaseBuffer(iBad);

      // append the default suffix if there is one
      CString strExt;
      if (pTemplate->GetDocString(strExt, CDocTemplate::filterExt) &&
        !strExt.IsEmpty())
      {
        ODA_ASSERT(strExt[0] == '.');
        newName += strExt;
      }
    }

    if (!DoPromptFileName(newName,
      bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
      OFN_HIDEREADONLY | OFN_EXPLORER | OFN_PATHMUSTEXIST, FALSE, pTemplate))
      return FALSE;       // don't even attempt to save

  }

  CWaitCursor wait;

  if (!OnSaveDocument(newName))
  {
    if (lpszPathName == NULL)
    {
      // be sure to delete the file
      TRY
      {
        CFile::Remove(newName);
      }
      CATCH_ALL(e)
      {
        TRACE0("Warning: failed to delete file after failed SaveAs.\n");
        do { e->Delete(); } while (0);
      }
      END_CATCH_ALL
    }
    return FALSE;
  }

  // reset the title and change the document name
  if (bReplace)
    SetPathName(newName);

  return TRUE;        // success
}

BOOL COdaPrcAppDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
  OdString strFileName(lpszPathName);
  int extPos = strFileName.reverseFind('.');
  OdString strExt = strFileName.mid(extPos + 1);
  CMainFrame* pMFrame = (CMainFrame*)theApp.GetMainWnd();
  bool bError = false;
  try
  {
    pMFrame->StartTimer();
    OdStreamBufPtr pOut = odrxSystemServices()->createFile(strFileName, Oda::kFileWrite, Oda::kShareDenyNo, Oda::kCreateAlways);
    m_pDb->writeFile(pOut);
  }
  catch(const OdError& e)
  {
    theApp.reportError(_T("Error Saving Document..."), e);
    bError = true;
  }
#ifndef _DEBUG
  catch(...)
  {
    AfxMessageBox(_T("Error while writing DB."), MB_ICONERROR);
    bError = true;
  }
#endif // #ifndef _DEBUG
  pMFrame->StopTimer(_T("Writing"));
  if ( bError )
  {
    AfxThrowUserException( );
    return FALSE;
  }

  UpdateAllViews(NULL);
  return TRUE;
}


// COdaPrcAppDoc serialization

void COdaPrcAppDoc::Serialize(CArchive& ar)
{
  if (ar.IsStoring())
  {
    // TODO: add storing code here
  }
  else
  {
    // TODO: add loading code here
  }
}



// COdaPrcAppDoc diagnostics

#ifdef _DEBUG
void COdaPrcAppDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void COdaPrcAppDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG


#pragma warning(push)
#pragma warning(disable:4510)
#pragma warning(disable:4610)

// COdaPrcAppDoc commands
void COdaPrcAppDoc::OnVectorize(const OdString& sVectorizerPath) 
{
  theApp.settings().setGsDevicePath(sVectorizerPath);

  struct CDocTemplateEx : CMultiDocTemplate
  {
    void SetViewToCreate(CRuntimeClass* pViewClass)
    {
      m_pViewClass = pViewClass;
    }
  };
  CDocTemplateEx* pTemplate = (CDocTemplateEx*)GetDocTemplate();
  ASSERT_VALID(pTemplate);
  pTemplate->SetViewToCreate(RUNTIME_CLASS(OdaPrcExViewer));

  CFrameWnd* pFrame = pTemplate->CreateNewFrame(this, NULL);  
  pTemplate->SetViewToCreate(RUNTIME_CLASS(COdaPrcTreeView));

  pFrame->InitialUpdateFrame(this, TRUE);
  
  //OdaPrcExViewer* pVectorizer = static_cast<OdaPrcExViewer*>(pFrame->GetActiveView());
  //m_pVectorizers.insert(pVectorizer);
  m_pVectorizer = static_cast<OdaPrcExViewer*>(pFrame->GetActiveView());

  //pFrame->MoveWindow( low.x, hi.y, hi.x - low.x, low.y - hi.y );
  pFrame->EnableDocking( CBRS_ALIGN_ANY );
}

#pragma warning(pop)

CMenu* getVectorizeMenu2(CMenu* pMainMenu);

BOOL COdaPrcAppDoc::OnCmdMsg(UINT nID, int nCode, void* pExtra,
                             AFX_CMDHANDLERINFO* pHandlerInfo) 
{
  // If pHandlerInfo is NULL, then handle the message
  if (pHandlerInfo == NULL)
  {
    CMenu* pTopMenu = theApp.GetMainWnd()->GetMenu();
    if(pTopMenu)
    {
      // Check if it is a OdaMfcApp's dynamic menu item:
      MENUITEMINFO menuItemInfo;
      menuItemInfo.cbSize = sizeof(menuItemInfo);
      menuItemInfo.fMask = MIIM_DATA;
      if(pTopMenu->GetMenuItemInfo(nID, &menuItemInfo, FALSE)) // command from menu
      {
        if(menuItemInfo.dwItemData == theApp.getGSMenuItemMarker())
        {
          CString s;
          pTopMenu->GetSubMenu(4)->GetMenuString(nID, s, MF_BYCOMMAND);
          if (nCode == CN_COMMAND)
          {
            OnVectorize((LPCTSTR)s);
          }
          else if (nCode == CN_UPDATE_COMMAND_UI)
          {
            ((CCmdUI*)pExtra)->Enable(m_pVectorizer==0);
            ((CCmdUI*)pExtra)->SetCheck(s==(LPCTSTR)theApp.settings().getGsDevicePath());
          }
          return TRUE;
        }
        if (nID >= _APS_NEXT_COMMAND_VALUE + 100 && nID <= _APS_NEXT_COMMAND_VALUE + theApp.numCustomCommands() + 100) // custom commands
        {
          OdRxObjectPtr pData(reinterpret_cast<OdRxObject*>(menuItemInfo.dwItemData));
          if(pData.get()) // dynamic
          {
            if (nCode == CN_COMMAND)
            {
              OdEdCommandPtr pCmd = OdEdCommand::cast(pData);
              if(pCmd.get())
              {
                ExecuteCommand(pCmd->globalName());
                return TRUE;
              }
            }
            else if (nCode == CN_UPDATE_COMMAND_UI)
            {
              ((CCmdUI*)pExtra)->Enable(TRUE);
            }
            return TRUE;
          }
        }
        else if (nID >= _APS_NEXT_COMMAND_VALUE && nID < _APS_NEXT_COMMAND_VALUE + 100) // scales
        {
          if (nCode == CN_UPDATE_COMMAND_UI)
          {
            ((CCmdUI*)pExtra)->Enable(TRUE);
          }
          return TRUE;
        }
      }
    }
  }

  // If we didn't process the command, call the base class
  // version of OnCmdMsg so the message-map can handle the message
  return CDocument::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void COdaPrcAppDoc::OnCloseVectorizer(OdaPrcExViewer* pVectorizer)
{
  m_pVectorizer = 0;
  //m_pVectorizer.OnClose();

  //std::set< OdaPrcExViewer* >::iterator iterator = m_pVectorizers.find( pVectorizer );

  //ODA_ASSERT( iterator != m_pVectorizers.end() );
  //m_pVectorizers.erase( iterator );
}

void COdaPrcAppDoc::OnVectorize() {
  OnVectorize(theApp.settings().getGsDevicePath());
}

void COdaPrcAppDoc::OnUpdateVectorize(CCmdUI* pCmdUI) {
  pCmdUI->Enable((NULL == m_pVectorizer) && !theApp.settings().getGsDevicePath().isEmpty());
}

void COdaPrcAppDoc::OnViews() {
//   ViewsDialog viewsDialog(database());
//   if (viewsDialog.DoModal() == IDOK)
//   {
//     OdPrcObjectId selectedDbDrawingId(viewsDialog.getDBDrawingId());
//     if (!selectedDbDrawingId.isNull())
//     {
//       OdPrcDBDrawingPtr pDBDrawing = selectedDbDrawingId.safeOpenObject();
//       OdDbBaseDatabasePEPtr pDbPE(database());
//       pDbPE->setCurrentLayout(database(), pDBDrawing->getUniqueName());      
//       OnVectorize();
// 
//       m_pVectorizer->OnViewZoomextents();
//     }
//   }
}

void COdaPrcAppDoc::On3DViews(UINT nID)
{
  if (!m_pVectorizer)
  {
    return;
  }
  OdGsViewPtr pView = m_pVectorizer->getActiveView();
  OdGePoint3d position, target = OdGePoint3d::kOrigin;
  OdGeVector3d axis;
  switch (nID)
  {
  case ID_3DVIEWS_TOP:
    position = OdGePoint3d::kOrigin + OdGeVector3d::kZAxis;
    axis = OdGeVector3d::kYAxis;
    break;
  case ID_3DVIEWS_BOTTOM:
    position = OdGePoint3d::kOrigin - OdGeVector3d::kZAxis;
    axis = -OdGeVector3d::kYAxis; // minus here
    break;
  case ID_3DVIEWS_LEFT:
    position = OdGePoint3d::kOrigin - OdGeVector3d::kXAxis;
    axis = OdGeVector3d::kZAxis;
    break;
  case ID_3DVIEWS_RIGHT:
    position = OdGePoint3d::kOrigin + OdGeVector3d::kXAxis;
    axis = OdGeVector3d::kZAxis;
    break;
  case ID_3DVIEWS_FRONT:
    position = OdGePoint3d::kOrigin - OdGeVector3d::kYAxis;
    axis = OdGeVector3d::kZAxis;
    break;
  case ID_3DVIEWS_BACK:
    position = OdGePoint3d::kOrigin + OdGeVector3d::kYAxis;
    axis = OdGeVector3d::kZAxis;
    break;
  };

  pView->setView(position, target, axis, pView->fieldWidth(), pView->fieldHeight());
  OnZoomExtents();
}

ODRX_DEFINE_CLSID_SMARTPTR(OdGsViewImpl);
void COdaPrcAppDoc::OnZoomExtents()
{
  if (!m_pVectorizer)
  { 
    OnVectorize();
  }
  OdGsViewPtr pView = m_pVectorizer->getActiveView();
  OdAbstractViewPEPtr pVpPE(pView);
  OdGeBoundBlock3d bbox;
  pVpPE->viewExtents(pView, bbox);
  pVpPE->zoomExtents(pView, &bbox);
}

OdEdBaseIO* COdaPrcAppDoc::cmdIO()
{
  return this;
}

inline CUserIOConsole* COdaPrcAppDoc::console()
{
  if(m_pConsole.isNull())
    m_pConsole = CUserIOConsole::create(theApp.GetMainWnd());
  return m_pConsole;
}

OdPrcCommandContextPtr COdaPrcAppDoc::cmdCtx()
{
  if(m_pCmdCtx.isNull())
  {
    m_pCmdCtx = ExPrcCommandContext::createObject(cmdIO(), m_pDb);
  }
  return m_pCmdCtx;
}

OdaPrcExViewer* COdaPrcAppDoc::getViewer() 
{
  return m_pVectorizer;
}

BOOL COdaPrcAppDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
  CView* pView = pFrame->GetActiveView();
  if(pView->IsKindOf(&OdaPrcExViewer::classOdaPrcExViewer))
  {
    if(!static_cast<OdaPrcExViewer*>(pView)->canClose())
      return FALSE;
  }
  return CDocument::CanCloseFrame(pFrame);
}

class CmdReactor : public OdStaticRxObject<OdEdCommandStackReactor>//,
//                   public OdStaticRxObject<OdPrcFileReactor>
{
  ODRX_NO_HEAP_OPERATORS();
  OdPrcCommandContext* m_pCmdCtx;
  bool                m_bModified;
  OdString            m_sLastInput;

  void setModified()
  {
    m_bModified = true;
//    m_pCmdCtx->database()->removeReactor(this);
  }
public:
  CmdReactor(OdPrcCommandContext* pCmdCtx) 
    : m_pCmdCtx(pCmdCtx)
    , m_bModified(false)
  {
    ODA_ASSERT(m_pCmdCtx);
    ::odedRegCmds()->addReactor(this);
    //m_pCmdCtx->database()->addReactor(this);
  }
  ~CmdReactor()
  {
    ::odedRegCmds()->removeReactor(this);
    //if(!m_bModified)
    //  m_pCmdCtx->database()->removeReactor(this);
  }

  void setLastInput(const OdString& sLastInput)
  {
    m_sLastInput = sLastInput;
  }
  const OdString &lastInput() const
  {
    return m_sLastInput;
  }
  bool isDatabaseModified() const { return m_bModified; }

  void objectOpenedForModify(const OdPrcFile*, const OdPrcBase*)
  {
    setModified();
  }

  void headerSysVarWillChange(const OdPrcFile*, const char*)
  {
    setModified();
  }

  OdEdCommandPtr unknownCommand(const OdString& sCmdName, OdEdCommandContext* /*pCmdCtx*/)
  {
    OdaPrcExViewer* pViewer = OdPrcFileDocPtr(m_pCmdCtx->database())->document()->getViewer();
    if(pViewer)
    {
      OdEdCommandPtr pRes = pViewer->command(sCmdName);
      if(pRes.get())
        return pRes;
    }
    OdString sMsg;
    sMsg.format(L"Unknown command \"%ls\".", sCmdName.c_str());
    m_pCmdCtx->userIO()->putString(sMsg);
    return OdEdCommandPtr();
  }

  void commandWillStart(OdEdCommand* pCmd, OdEdCommandContext* /*pCmdCtx*/)
  {
    m_sLastInput.makeUpper();
    if ( !GETBIT(pCmd->flags(), OdEdCommand::kNoHistory) )
     theApp.settings().setRecentCmd(m_sLastInput);

    //TODO: It requires "undo" support
    //if ( !GETBIT(pCmd->flags(), OdEdCommand::kNoUndoMarker) )
    // m_pCmdCtx->database()->startUndoRecord();
  }
  void commandCancelled(OdEdCommand*, OdEdCommandContext* )
  {
    undoCmd();
  }
  void commandFailed(OdEdCommand*, OdEdCommandContext* )
  {
    undoCmd();
  }

private:
  void undoCmd()
  {
    OdPrcFile* pDb = m_pCmdCtx->database();
    try
    {
      //TODO: It requires "undo" support
      //pDb->disableUndoRecording(true);
      //pDb->undo();
      //pDb->disableUndoRecording(false);
    }
    catch(const OdError& err)
    {
      theApp.reportError(_T("Can't repair database"), err);
    }
#ifndef _DEBUG
    catch(...)
    {
      ::MessageBox(NULL, _T("Unknown error occurred..."),
        _T("Can't repair database"), MB_OK|MB_ICONERROR);
    }
#endif //_DEBUG
  }
};

OdString COdaPrcAppDoc::recentCmd()
{
  return theApp.settings().getRecentCmd();
}

OdString COdaPrcAppDoc::recentCmdName()
{
  return theApp.settings().getRecentCmd().spanExcluding(L" \n");
}

OdString COdaPrcAppDoc::commandPrompt()
{
  return _T("Command:");
}

OdString commandMessageCaption(const OdString& sCmd)
{
  OdString sCaption;
  sCaption.format(L"Command: %ls", sCmd.c_str());
  return sCaption;
}

void COdaPrcAppDoc::ExecuteCommand(const OdString& sCmd, bool bEcho) 
{
  OdSaveState<int> save_m_nCmdActive(m_nCmdActive);
  ++m_nCmdActive;

  OdPrcCommandContextPtr pCmdCtx = cmdCtx();
  CmdReactor cr(pCmdCtx);
  
  try
  {
    OdEdCommandStackPtr pCommands = ::odedRegCmds();
    ExPrcCommandContext *pExCmdCtx = static_cast<ExPrcCommandContext*>(pCmdCtx.get());
    //if(m_pDb->appServices()->getPICKFIRST())
    //  pExCmdCtx->setPickfirst(selectionSet());

    //if (sCmd[0]=='(')
    //{
    //  OdEdLispModulePtr lspMod = odrxDynamicLinker()->loadApp(OdLspModuleName);
    //  if (!lspMod.isNull())
    //    lspMod->createLispEngine()->execute(pExCmdCtx, sCmd);
    //}
    //else
    //{
      OdString s = sCmd.spanExcluding(L" \t\r\n");
      if(s.getLength() == sCmd.getLength())
      {
        if(bEcho)
          pCmdCtx->userIO()->putString(commandPrompt() + L" " + s);
        s.makeUpper();
        theApp.settings().setRecentCmd(s);
        pCommands->executeCommand(s, pCmdCtx);
      }
      else
      {
        m_pMacro = ExStringIO::create(sCmd);
        while(!m_pMacro->isEof())
        {
          try
          {
            s = pCmdCtx->userIO()->getString(commandPrompt());
            s.makeUpper();
            theApp.settings().setRecentCmd(s);
          }
          catch(const OdEdEmptyInput)
          {
            s = recentCmdName();
          }

          pCommands->executeCommand(s, pCmdCtx);
        }
      }
    //}

    if (getViewer())
    {
      getViewer()->Invalidate();

      getViewer()->propagateActiveViewChanges();
    }
  }
  catch(const OdEdEmptyInput )
  {
  }
  catch(const OdEdCancel )
  {
  }
  catch(const OdError& err)
  {
    if(!m_bConsole)
    {
      theApp.reportError(commandMessageCaption(sCmd), err);
    }
    cmdIO()->putString(err.description());
  }
  //TODO: SelectionSet
  /*if ((cr.isDatabaseModified() || selectionSet()->numEntities()) )
  {
    // Call here OdExPrcEditorObject::unselect() instead sset->clear(), if you want affect changes on grip points and etc.
    if (0 != cr.lastInput().iCompare(_T("SELECT")) || pCmdCtx->database()->appServices()->getPICKADD() != 2)
      OnEditClearselection();
    UpdateAllViews(0);
  }*/
  //static_cast<ExDbCommandContext*>(pCmdCtx.get())->setMacroIOPresent(false);

  UpdateAllViews(0);
}

#define BLINK_CURSOR_TIMER 888
#define BLINK_CURSOR_RATE  GetCaretBlinkTime()
void CALLBACK StringTrackerTimer(HWND hWnd, UINT  nMsg, UINT  nIDTimer, DWORD dwTime);

OdString COdaPrcAppDoc::getString(const OdString& prompt, int options, OdEdStringTracker* pTracker)
{
  OdString sRes;
  if(m_pMacro.get() && !m_pMacro->isEof())
  {
    sRes = m_pMacro->getString(prompt, options, pTracker);
    putString(OdString(prompt) + L" " + sRes);
    return sRes;
  }

  if(m_pVectorizer && pTracker)
  {
    pTracker->setCursor(true);
    SetTimer(getViewer()->m_hWnd, BLINK_CURSOR_TIMER, BLINK_CURSOR_RATE, (TIMERPROC)StringTrackerTimer);
    sRes = m_pVectorizer->getString(prompt, options, pTracker);
    KillTimer(getViewer()->m_hWnd, BLINK_CURSOR_TIMER);

    putString(OdString(prompt) + L" " + sRes);
    return sRes;
  }

  if(m_bConsole)
    return console()->getString(prompt, options, pTracker);

  if(m_pVectorizer)
  {
    m_bConsoleResponded = prompt.isEmpty();
    sRes = m_pVectorizer->getString(prompt, options, pTracker);
    if(!m_bConsoleResponded)
      putString(OdString(prompt) + L" " + sRes);
    return sRes;
  }

  return console()->getString(prompt, options, pTracker);
}

void COdaPrcAppDoc::OnEditConsole() 
{
  OdEdCommandPtr pCommand;
  OdEdCommandStackPtr pCommands = ::odedRegCmds();
  OdPrcCommandContextPtr pCmdCtx = cmdCtx();
  OdSaveState<bool> saveConsoleMode(m_bConsole, true);
  try
  {
    if(m_pVectorizer && m_pVectorizer->isGettingString())
    {
      m_pVectorizer->respond(console()->getString(m_pVectorizer->prompt(), m_pVectorizer->inpOptions(), 0));
      m_bConsoleResponded = true;
    }
    else
    {
      for(;;)
      {
        OdString s = pCmdCtx->userIO()->getString(commandPrompt(), 0, L"");
        if(s.isEmpty())
        {
          s = recentCmdName();
          if(!s.isEmpty())
          {
            pCmdCtx->userIO()->putString(s);
            ExecuteCommand(s, false);
          }
        }
        else
        {
          ExecuteCommand(s, false);
        }
      }
    }
  }
  catch(const OdEdCancel& )
  {
  }
}

void COdaPrcAppDoc::OnOptionsTriangulationParams() 
{
  wrTriangulationParams TriangulationParams;
  theApp.getTriangulationParams(TriangulationParams);

  double facetRes = 0.5; // pDb->getFACETRES();

  OdaTrianParamsDlg triangulationParametersDlg(NULL, &TriangulationParams, &facetRes);

  LPARAM nResult = triangulationParametersDlg.DoModal();
  if (nResult == IDOK)
  {
    theApp.setTriangulationParams(TriangulationParams);
  }
}


void COdaPrcAppDoc::putString(const OdString& string)
{
  if(m_pVectorizer)
    m_pVectorizer->putString(string);

  console()->putString(string);
}

OdGePoint3d COdaPrcAppDoc::getPoint(const OdString& prompt, int options, OdEdPointTracker* pTracker)
{
  if(m_pMacro.get() && !m_pMacro->isEof())
  {
    console()->putString(prompt);
    return m_pMacro->getPoint(prompt, options, pTracker);
  }

  if(m_bConsole)
    return m_pConsole->getPoint(prompt, options, pTracker);

  if(m_pVectorizer)
  {
    console()->putString(prompt);
    return m_pVectorizer->getPoint(prompt, options, pTracker);
  }

  return console()->getPoint(prompt, options, pTracker);
}

OdUInt32 COdaPrcAppDoc::getKeyState()
{
  OdUInt32 res = 0;
  if (::GetKeyState(VK_CONTROL) != 0)
    res |= MK_CONTROL;
  if (::GetKeyState(VK_SHIFT) != 0)
    res |= MK_SHIFT;
  return res;
}

void COdaPrcAppDoc::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
  theApp.RefreshCommandMenu();
  pCmdUI->Enable(/*m_pDb->hasUndo() ? TRUE :*/ FALSE);
}

void COdaPrcAppDoc::OnNamedViews()
{
  ViewsDlg viewsDlg(this);
  viewsDlg.DoModal();
}

void COdaPrcAppDoc::OnFormatBackgroundColor()
{
  CColorPickerDlg dlg;
  dlg.SetColor((ODCOLORREF)theApp.settings().getActiveBackground());

  if (dlg.DoModal() == IDOK)
  {
    COLORREF color = (COLORREF)dlg.GetColor();
    theApp.settings().setActiveBackground(color);
    theApp.WriteProfileInt(_T("format"), _T("Background colour"), color);
  }
}

void COdaPrcAppDoc::OnU3DImport()
{
  OdRxModulePtr pModule = ::odrxDynamicLinker()->loadModule(OdU3D2PrcImportModuleName);

  if (pModule.isNull())
  {
    AfxMessageBox(OdU3D2PrcImportModuleName L" is missing");
  }
  else
  {
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER | OFN_PATHMUSTEXIST,
      _T("Universal 3D Format (*.u3d)|*.u3d|U3D file (*.u3d)||"));

    dlg.m_ofn.lpstrTitle = _T("U3D file to load");
    if (dlg.DoModal() == IDOK)
    {
      OdString promt = OdString().format(L"u3dImport %ls \n", OdString((LPCTSTR)dlg.GetPathName()).c_str());
      ExecuteCommand(promt);
    }

  }
}
