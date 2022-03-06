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

#include "stdafx.h"
#include "MergeDialog.h"
#include "odamfcapp.h"
#include "DbHistoryManager.h"
#include "DbIdMapping.h"
#include "GiContextForDbDatabase.h"
#include "ColorMapping.h"
#include "AbstractViewPE.h"
#include "RxRasterServices.h"
#include "DbSymbolTable.h"
#include "DbBlockTable.h"
#include "DbBlockTableRecord.h"
#include "DbLayerTable.h"
#include "DbLayerTableRecord.h"
#include "DbText.h"



// MergeDialog dialog

IMPLEMENT_DYNAMIC(MergeDialog, CDialog)

MergeDialog::MergeDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_MERGE, pParent), m_nSelected1(-1), m_nSelected2(-1), m_isCheckBoxEnable(false)
{

}

MergeDialog::~MergeDialog()
{
}

void MergeDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
}


BOOL MergeDialog::OnInitDialog()
{
  CDialog::OnInitDialog();
  m_pListBranches1 = (CListBox*)GetDlgItem(IDC_LIST_MERGE_BRANCHES_1);
  m_pListBranches2 = (CListBox*)GetDlgItem(IDC_LIST_MERGE_BRANCHES_2);
  m_pButtonAddBranch = (CButton*)GetDlgItem(ID_BUTTON_MERGE_OK);
  fillBranches();
  m_pButtonAddBranch->EnableWindow(FALSE);
  CPoint pt;
  GetCursorPos(&pt);
  SetWindowPos(NULL, pt.x, pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
  return TRUE;
}

BEGIN_MESSAGE_MAP(MergeDialog, CDialog)
  ON_BN_CLICKED(ID_BUTTON_MERGE_OK, &MergeDialog::OnBnClickedButtonMergeOk)
  ON_LBN_SELCHANGE(IDC_LIST_MERGE_BRANCHES_1, &MergeDialog::OnLbnSelchangeListMergeBranches1)
  ON_LBN_SELCHANGE(IDC_LIST_MERGE_BRANCHES_2, &MergeDialog::OnLbnSelchangeListMergeBranches2)
  ON_BN_CLICKED(IDC_CHECK_MERGE_MANUAL, &MergeDialog::OnBnClickedCheckMergeManual)
END_MESSAGE_MAP()


void MergeDialog::fillBranches()
{
  OdTfRevisionControl::ReferenceList branches;
  OdTfRevisionControl::getRepository(m_pDb)->getReferences(branches);
  std::map<OdString, OdTfDigest>::const_iterator it = branches.begin();
  std::map<OdString, OdTfDigest>::const_iterator itEnd = branches.end();
  size_t oldSize = m_branches.size();
  unsigned int i = 0;
  m_branches.clear();
  for (; it != itEnd; ++i, ++it)
  {
    m_pListBranches1->DeleteString(i);
    m_pListBranches1->InsertString(i, it->first.c_str());
    m_pListBranches2->DeleteString(i);
    m_pListBranches2->InsertString(i, it->first.c_str());
    m_branches.push_back(it->first);
  }
  while (i < oldSize)
  {
    m_pListBranches1->DeleteString(i++);
    m_pListBranches2->DeleteString(i++);
  }
}


void MergeDialog::OnBnClickedButtonMergeOk()
{
  if (m_nSelected1 == -1 || m_nSelected2 == -1)
    m_pButtonAddBranch->EnableWindow(FALSE);
  if (m_isCheckBoxEnable)
  {
    EndDialog(1);
    return;
  }
  OdHandleArray hArr;
  OdString currentBranch = OdTfRevisionControl::getLocalBranch(m_pDb);
  if (currentBranch == m_branches[m_nSelected1])
  {
    OdTfRevisionControl::merge(m_pDb, m_branches[m_nSelected2], OdTfFixedMergeHandler<>());
  }
  else if (currentBranch == m_branches[m_nSelected2])
  {
    OdTfRevisionControl::merge(m_pDb, m_branches[m_nSelected1], OdTfFixedMergeHandler<>());
  }
  else
  {
    OdTfRevisionControl::switchBranch(m_pDb, m_branches[m_nSelected1]);
    OdTfRevisionControl::merge(m_pDb, m_branches[m_nSelected2], OdTfFixedMergeHandler<>());
  }
  
  EndDialog(1);
}


void MergeDialog::OnLbnSelchangeListMergeBranches1()
{
  m_nSelected1 = m_pListBranches1->GetCurSel();
  if(m_nSelected2 != -1)
    m_pButtonAddBranch->EnableWindow(true);
}


void MergeDialog::OnLbnSelchangeListMergeBranches2()
{
  m_nSelected2 = m_pListBranches2->GetCurSel();
  if(m_nSelected1 != -1)
    m_pButtonAddBranch->EnableWindow(true);
}

void MergeDialog::OnBnClickedCheckMergeManual()
{
  CButton *pCheckBox = (CButton*)GetDlgItem(IDC_CHECK_MERGE_MANUAL);
  int ChkBox = pCheckBox->GetCheck();
  if (ChkBox == BST_UNCHECKED)
  {
    m_isCheckBoxEnable = false;
    fillBranches();
    m_nSelected1 = -1;
  }
  else if (ChkBox == BST_CHECKED)
  {
    m_isCheckBoxEnable = true;
    m_nSelected1 = 0;
    while (m_pListBranches1->GetCount())
      m_pListBranches1->DeleteString(0);
    m_pListBranches1->InsertString(0, L"runtime database");
  }
  if(m_nSelected1 != -1 && m_nSelected2 != -1)
    m_pButtonAddBranch->EnableWindow(true);
}



IMPLEMENT_DYNAMIC(MergeBmpView, CDialog)

MergeBmpView::MergeBmpView(CWnd* pParent /*=nullptr*/)
  : CDialog(IDD_MERGE_VIEWBMP, pParent)
{
  m_mergeResolution = OdTfRevisionControl::kMergeNoResolution;
}

MergeBmpView::~MergeBmpView()
{
#ifdef OD_HAVE_REMOVE_FUNC
  if (!m_sMineBMP.isEmpty())
    remove(m_sMineBMP);
  if (!m_sTheirBMP.isEmpty())
    remove(m_sTheirBMP);
  if (!m_sAncestorBMP.isEmpty())
    remove(m_sAncestorBMP);
#else
  if (!m_sMineBMP.isEmpty())
    DeleteFile(m_sMineBMP.c_str());
  if (!m_sTheirBMP.isEmpty())
    DeleteFile(m_sTheirBMP.c_str());
  if (!m_sAncestorBMP.isEmpty())
    DeleteFile(m_sAncestorBMP.c_str());
#endif
}


OdString exportToBmp(OdDbDatabasePtr ptrMyDatabaseOneEntity)
{
  OdString filePatchBMP;
  try
  {
    OdString sGS(/*OdWinOpenGLModuleName*/OdWinGLES2ModuleName); // *OdWinOpenGLModuleName - doesn't support transparency well
    OdDb::RenderMode rMode = OdDb::kFlatShaded;
    OdGsModulePtr pGsModule = ::odrxDynamicLinker()->loadModule(sGS);
    OdGsDevicePtr pBitmapDevice;
    if (pGsModule.get())
    {
      pBitmapDevice = pGsModule->createBitmapDevice();
    }
    if (!pBitmapDevice.get())
    {
      throw OdError(eDeviceNotFound);
    }

    OdGiContextForDbDatabasePtr pDwgContext = OdGiContextForDbDatabase::createObject();
    pDwgContext->setDatabase(ptrMyDatabaseOneEntity);
    pDwgContext->enableGsModel(false);
    OdGsDevicePtr pDevice = OdDbGsManager::setupActiveLayoutViews(pBitmapDevice, pDwgContext);
    ODCOLORREF bgColor = ODRGB(0, 0, 0); // set background color
    bool is_dark_palette = (ODGETRED(bgColor) < 140) && (ODGETGREEN(bgColor) < 140) && (ODGETBLUE(bgColor) < 140);
    pDevice->setLogicalPalette(is_dark_palette ? (::odcmAcadDarkPalette()) : (::odcmAcadLightPalette()), 256);
    pDevice->setBackgroundColor(bgColor);
    pDwgContext->setPaletteBackground(bgColor);

    // - setup output dims
    OdGsDCRect screenRect(OdGsDCPoint(0, 1000), OdGsDCPoint(1000, 0));
    pDevice->onSize(screenRect);

    // - zoom to extents
    OdGsView *pView = pDevice->viewAt(0);
    OdAbstractViewPEPtr(pView)->zoomExtents(pView);
    OdAbstractViewPEPtr(pView)->setRenderMode(pView, rMode);

    // - render image (internal)
    pDevice->update();

    // - save image
    // - NOTICE that type of raster file is deducted from example input (e.g. if output file is D:\picture.bmp image will be saved as .bmp)
    OdGiRasterImagePtr ptrImage = pDevice->properties()->getAt(OD_T("RasterImage"));
    OdRxRasterServicesPtr pRasSvcs = ::odrxDynamicLinker()->loadApp(RX_RASTER_SERVICES_APPNAME);
    if (pRasSvcs.get())
    {
      filePatchBMP = odrxSystemServices()->getTemporaryPath();
      filePatchBMP += odrxSystemServices()->getTempFileName();
      filePatchBMP += L".BMP";
      pRasSvcs->saveRasterImage(ptrImage, filePatchBMP);
    }
  }
  catch (...)
  {
    return OdString::kEmpty;
  }
  return filePatchBMP;
}

const wchar_t* mergeChangeTypeToString(OdTfRevisionControl::ChangeType mergeResolution, COLORREF& color)
{
  static const wchar_t* pCharAnswer[5] = { L"Object unmodified", L"Object added", L"Object deleted", L"Object modified", L"" };
  switch (mergeResolution)
  {
  case OdTfRevisionControl::kObjectUnmodified:
    return pCharAnswer[0];
    color = RGB(0, 0, 0);
    break;
  case OdTfRevisionControl::kObjectAdded:
    color = RGB(0, 160, 0);
    return pCharAnswer[1];
    break;
  case OdTfRevisionControl::kObjectDeleted:
    color = RGB(160, 0, 0);
    return pCharAnswer[2];
    break;
  case OdTfRevisionControl::kObjectModified:
    color = RGB(255, 127, 0);
    return pCharAnswer[3];
    break;
  default:
    break;
  }
  return pCharAnswer[4];
}


bool showChangeToBMP(const OdDbHandle h, OdDbDatabasePtr pDbToAppendChange, OdDbObjectId changedObjectId, OdDbDatabasePtr pDbOfChanges, OdString &pathToBMP)
{
  try
  {
    if (changedObjectId.isNull())
      return false;
    OdDbIdMappingPtr pMap = OdDbIdMapping::createObject();
    pMap->setDestDb(pDbToAppendChange);
    OdDbObjectIdArray objectIds;
    objectIds.push_back(changedObjectId);

    pDbOfChanges->startUndoRecord();
    OdDbLayerTableRecordPtr pTempLayer = OdDbLayerTableRecord::createObject();
    OdCmTransparency tr;
    tr.setAlpha(0);
    tr.setMethod(OdCmTransparency::kByAlpha);
    pTempLayer->setTransparency(tr);
    pDbOfChanges->addOdDbObject(pTempLayer);
    OdDbObjectId layerId = pTempLayer->objectId();
    OdDbBlockTablePtr pBlock = pDbOfChanges->getBlockTableId().safeOpenObject();
    OdDbSymbolTableIteratorPtr pBlockIt = pBlock->newIterator();
    while (!pBlockIt->done())
    {
      OdDbBlockTableRecordPtr pRec = pBlockIt->getRecordId().safeOpenObject();
      OdDbObjectIteratorPtr pObjIt = pRec->newIterator();
      while (!pObjIt->done())
      {
        OdDbObjectPtr obj = pObjIt->objectId().safeOpenObject(OdDb::kForWrite);
        if (obj->isKindOf(OdDbEntity::desc()) && obj->handle() != h)
          OdDbEntity::cast(obj)->setTransparency(tr);// setLayer(layerId);
        pObjIt->step();
      }
      pBlockIt->step();
    }
    pathToBMP = exportToBmp(pDbOfChanges);
    pDbOfChanges->undo();
    return !pathToBMP.isEmpty();
  }
  catch (...)
  {

  }
  return false;
}

struct OdTfMergeHandlerExample : public OdTfMergeHandler
{
  OdTfRevisionControl::MergeResolution resolveMerge(const OdDbHandle& h,
                                           OdTfRevisionControl::ChangeType myChange,
                                           OdTfRevisionControl::ChangeType theirChange,
                                           OdTfRevisionControl::MergeResolution autoResolution)
  {
    OdString mineStaticText(L"MINE: ");
    COLORREF mineColor;
    mineStaticText += mergeChangeTypeToString(myChange, mineColor);
    OdString theirStaticText(L"THEIR: ");
    COLORREF theirColor;
    theirStaticText += mergeChangeTypeToString(theirChange, theirColor);

    pView->setStaticTexts(mineStaticText, theirStaticText, mineColor, theirColor);


    bool bMyObjIsEntity = false;
    bool bTheirObjIsEntity = false;
    bool bAncestorObjIsEntity = false;
    ////////////////
    OdDbObjectId myId = pMyDatabase->getOdDbObjectId(h);
    OdDbObjectPtr pMyObj;
    if (!myId.isNull() && myId.isValid())
    {
      try
      {
        pMyObj = myId.safeOpenObject(OdDb::kForRead, true);
        if (!pMyObj.isNull())
          bMyObjIsEntity = pMyObj->isKindOf(OdDbEntity::desc());
      }
      catch (const OdError&  err)
      {
        ODA_ASSERT(err.code() == ePermanentlyErased);
      }
    }
    /////////////
    OdDbObjectId theirId = pTheirDatabase->getOdDbObjectId(h);
    OdDbObjectPtr pTheirObj;
    if (!theirId.isNull())
    {
      try
      {
        pTheirObj = theirId.safeOpenObject(OdDb::kForRead, true);
        if (!pTheirObj.isNull())
          bTheirObjIsEntity = pTheirObj->isKindOf(OdDbEntity::desc());
      }
      catch (const OdError&  err)
      {
        ODA_ASSERT(err.code() == ePermanentlyErased);
      }
    }
    /////////////////
    OdDbObjectId ancestorId = pAncestorDatabase->getOdDbObjectId(h);
    OdDbObjectPtr pAncestorObj;
    if (!pAncestorObj.isNull())
    {
      try
      {
        pAncestorObj = ancestorId.safeOpenObject(OdDb::kForRead, true);
        if (!pAncestorObj.isNull())
          bAncestorObjIsEntity = pAncestorObj->isKindOf(OdDbEntity::desc());
      }
      catch (const OdError&  err)
      {
        ODA_ASSERT(err.code() == ePermanentlyErased);
      }
    }
    //////////////////
    if ((bTheirObjIsEntity || bMyObjIsEntity) && (bTheirObjIsEntity || theirChange == OdTfRevisionControl::kObjectDeleted) && (bMyObjIsEntity || myChange == OdTfRevisionControl::kObjectDeleted))
    {

      OdString sMineBMP, sTheirBMP, sAncestorBMP;
      if (myChange != OdTfRevisionControl::kObjectDeleted && !showChangeToBMP(h, ptrMyDatabaseOneEntity, myId, pMyDatabase, sMineBMP))
        return autoResolution ? autoResolution : prepareResolution;

      if (theirChange != OdTfRevisionControl::kObjectDeleted && !showChangeToBMP(h, ptrMyDatabaseOneEntity, theirId, pTheirDatabase, sTheirBMP))
        return autoResolution ? autoResolution : prepareResolution;

      if (myChange != OdTfRevisionControl::kObjectAdded && theirChange != OdTfRevisionControl::kObjectAdded)
        showChangeToBMP(h, ptrMyDatabaseOneEntity, ancestorId, pAncestorDatabase, sAncestorBMP);

      pView->setBMPs(sMineBMP, sTheirBMP, sAncestorBMP);
      int result = pView->DoModal();
      if (result != IDOK)
        return autoResolution ? autoResolution : prepareResolution;
      if (pView->getMergeResolution() != OdTfRevisionControl::kMergeNoResolution)
        return pView->getMergeResolution();
      return autoResolution ? autoResolution : prepareResolution;
    }
    return autoResolution ? autoResolution : prepareResolution;
  }

  OdTfRevisionControl::MergeResolution operator()(const OdDbHandle& h,
    OdTfRevisionControl::ChangeType myChange,
    OdTfRevisionControl::ChangeType theirChange,
    OdTfRevisionControl::MergeResolution autoResolution) override
  {
    if (!bUsePreparedResolutions)
    {
      
      OdTfRevisionControl::MergeResolution resolution = resolveMerge(h, myChange, theirChange, autoResolution);
      preparedResolutions[h] = resolution;
      return resolution;
    }
    std::map<OdDbHandle, OdTfRevisionControl::MergeResolution>::const_iterator it = preparedResolutions.find(h);
    if (it != preparedResolutions.end())
      return it->second;
    return prepareResolution;
  }
  OdDbDatabasePtr ptrMyDatabaseOneEntity;
  OdDbDatabasePtr pMyDatabase;
  OdDbDatabasePtr pTheirDatabase;
  OdDbDatabasePtr pAncestorDatabase;
  MergeBmpView* pView;
  std::map<OdDbHandle, OdTfRevisionControl::MergeResolution> preparedResolutions;
  bool bUsePreparedResolutions;
  OdTfRevisionControl::MergeResolution prepareResolution;
  OdTfMergeHandlerExample():pView(NULL), bUsePreparedResolutions(false){};
};

bool MergeBmpView::doMerge(OdDbDatabase* pDb, const OdString& sOtherBranch)
{
  OdTfRepository* pRep = OdTfRevisionControl::getRepository(pDb);
  OdTfMergeHandlerExample handler;
  handler.prepareResolution = OdTfRevisionControl::kMergeTheirsConflict;
  handler.ptrMyDatabaseOneEntity = pDb->appServices()->createDatabase();
  handler.pView = this;
  handler.pMyDatabase = pDb;
  handler.pTheirDatabase = pRep->checkout(sOtherBranch);
  OdTfDigest ancestorSha, theirSha;
  if (!pRep->getReference(sOtherBranch, theirSha) || !OdTfRevisionControl::getCommonAncestor(pDb, theirSha, ancestorSha))
  {
    //TODO 
    return false;
  }
  handler.pAncestorDatabase = pRep->checkout(ancestorSha, L"TEMP_ANCESTOR");
  OdTfRevisionControl::dryMerge(pDb, sOtherBranch, handler); 
  handler.bUsePreparedResolutions = true;
  OdTfCommitInfo ancestorCommitInfo = pRep->getCommitInfo(ancestorSha);
  OdTfCommitInfo theirCommitInfo = pRep->getCommitInfo(theirSha);
  pRep->merge(pDb, theirCommitInfo.revision, ancestorCommitInfo.revision, handler);
  //OdTfRevisionControl::merge(pDb, sOtherBranch, handler);
  

  return false;
}

void MergeBmpView::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_MERGE_BMP1, MERGE_BMP1);
}


void MergeBmpView::setBMPs(const OdString& s1, const OdString& s2, const OdString& s3)
{
  m_sMineBMP = s1;
  m_sTheirBMP = s2;
  m_sAncestorBMP = s3;
}


void changeFont(MergeBmpView* pView)
{
  CStatic* pStaticTextMine = (CStatic*)pView->GetDlgItem(IDC_MERGE_TEXT_MINE);
  CStatic* pStaticTextTheir = (CStatic*)pView->GetDlgItem(IDC_MERGE_TEXT_THEIR);
  CStatic* pStaticTextAncestor = (CStatic*)pView->GetDlgItem(IDC_MERGE_TEXT_ANCESTOR);
  CFont* font;
  font = pStaticTextMine->GetFont();
  LOGFONT lf;
  font->GetLogFont(&lf);
  lf.lfHeight *= 2;
  lf.lfWeight = FW_BOLD;
  CFont* newFont = new CFont();
  newFont->CreateFontIndirectW(&lf);
  pStaticTextMine->SetFont(newFont);
  pStaticTextTheir->SetFont(newFont);
  pStaticTextAncestor->SetFont(newFont);
}

BOOL MergeBmpView::OnInitDialog()
{
  CDialog::OnInitDialog();

  HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
  SetIcon(hIcon, FALSE);
  changeFont(this);
  SetWindowPos(NULL, 50, 50, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
  CRect rc;
  GetWindowRect(&rc); // getting dialog coordinates
  int width = rc.Width()*1.8;
  int height = rc.Height()*2.;
  MoveWindow(rc.left, rc.top,width , height);
  return TRUE;
}

BEGIN_MESSAGE_MAP(MergeBmpView, CDialog)
  ON_WM_PAINT()
  ON_BN_CLICKED(IDC_MERGE_FULL_MINE, &MergeBmpView::OnBnClickedMergeFullMine)
  ON_BN_CLICKED(IDC_MERGE_PREFER_MINE, &MergeBmpView::OnBnClickedMergePreferMine)
  ON_BN_CLICKED(IDC_MERGE_REVERT, &MergeBmpView::OnBnClickedMergeRevert)
  ON_BN_CLICKED(IDC_MERGE_PREFER_THEIR, &MergeBmpView::OnBnClickedMergePreferTheir)
  ON_BN_CLICKED(IDC_MERGE_FULL_THEIR, &MergeBmpView::OnBnClickedMergeFullTheir)
  ON_WM_CTLCOLOR()
END_MESSAGE_MAP()






void MergeBmpView::OnPaint()
{
  CPaintDC dc(this); // device context for painting
                     // TODO: Add your message handler code here
                     // Do not call CDialog::OnPaint() for painting messages
  if(!m_sMineBMP.isEmpty())
    drawChanges(IDC_MERGE_BMP1, m_sMineBMP);
  if (!m_sTheirBMP.isEmpty())
    drawChanges(IDC_MERGE_BMP2, m_sTheirBMP);
  if (!m_sAncestorBMP.isEmpty())
    drawChanges(IDC_MERGE_BMP_ANCESTOR, m_sAncestorBMP);

  CStatic* pStaticTextMine = (CStatic*)GetDlgItem(IDC_MERGE_TEXT_MINE);
  CStatic* pStaticTextTheir = (CStatic*)GetDlgItem(IDC_MERGE_TEXT_THEIR);
  pStaticTextMine->SetWindowTextW(m_sStaticTextMine);
  pStaticTextTheir->SetWindowTextW(m_sStaticTextTheir);
}

void MergeBmpView::drawChanges(int IDC_pictureControl, LPCWSTR path)
{ 
  CWnd* pImage = GetDlgItem(IDC_pictureControl);
  CRect rc;
  pImage->GetWindowRect(rc);
  HRGN hRgn = CreateRoundRectRgn(0, 0, rc.Width(), rc.Height(), 40, 40);
  HBITMAP  hbp = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, rc.Width(), rc.Height(), LR_DEFAULTSIZE | LR_LOADFROMFILE);
  HBRUSH hBr = CreatePatternBrush(hbp);
  FillRgn(pImage->GetDC()->GetSafeHdc(), hRgn, hBr);
}




void MergeBmpView::OnBnClickedMergeFullMine()
{
  m_mergeResolution = OdTfRevisionControl::kMergeMineFull;
  EndDialog(IDOK);
}


void MergeBmpView::OnBnClickedMergePreferMine()
{
  m_mergeResolution = OdTfRevisionControl::kMergeMineConflict;
  EndDialog(IDOK);
}


void MergeBmpView::OnBnClickedMergeRevert()
{
  m_mergeResolution = OdTfRevisionControl::kMergeRevertFull;
  EndDialog(IDOK);
}


void MergeBmpView::OnBnClickedMergePreferTheir()
{
  m_mergeResolution = OdTfRevisionControl::kMergeTheirsConflict;
  EndDialog(IDOK);
}


void MergeBmpView::OnBnClickedMergeFullTheir()
{
  m_mergeResolution = OdTfRevisionControl::kMergeTheirsFull;
  EndDialog(IDOK);

}






HBRUSH MergeBmpView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
  HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
  if (pWnd->GetDlgCtrlID() == IDC_MERGE_TEXT_MINE)
    pDC->SetTextColor(m_mineColor);
  else if (pWnd->GetDlgCtrlID() == IDC_MERGE_TEXT_THEIR)
    pDC->SetTextColor(m_TheirColor);
  return hbr;
}
