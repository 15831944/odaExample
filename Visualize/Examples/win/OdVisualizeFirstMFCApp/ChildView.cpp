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

// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "OdVisualizeFirstMFCApp.h"
#include "ChildView.h"
#include "TvCoreModulesNames.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CChildView, CWnd)
  ON_WM_PAINT()
  ON_WM_SIZE()
  ON_WM_MOUSEWHEEL()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_MOUSEMOVE()
  ON_COMMAND(ID_FILE_OPEN32771, &CChildView::OnFileOpen32771)
  ON_COMMAND(ID_FILE_GENERATESAMPLE, &CChildView::OnFileGeneratesample)
  ON_COMMAND(ID_BUTTONPAN, &CChildView::OnPanClick)
  ON_COMMAND(ID_BUTTONORBIT, &CChildView::OnOrbitClick)
  ON_COMMAND(ID_BUTTONZOOMEXT, &CChildView::OnZoomExtCLick)
END_MESSAGE_MAP()

#ifndef _TOOLKIT_IN_DLL_
// Visualize API
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxCommonDataAccessModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvDbCoreModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvDbIOModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TvISMModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TvSCENEOEModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvTfModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvDbPartialViewingModuleImpl );
//Visualize device
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(VisualizeDeviceModule);

//Obj2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeObjFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdObjToolkitModuleImpl);

//Raster images
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRasterProcessingServicesImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);
//Device
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTrGL2RenderModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(GLES2Module);

//TvCore
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvCoreDatabaseModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvCoreDatabaseIOModule );

ODRX_BEGIN_STATIC_MODULE_MAP()
ODRX_DEFINE_STATIC_APPMODULE(OdTvModuleName, OdTvModule)
ODRX_DEFINE_STATIC_APPMODULE(RxCommonDataAccessModuleName, OdRxCommonDataAccessModule)
ODRX_DEFINE_STATIC_APPMODULE( OdTvDbCoreModuleName, OdTvDbCoreModule )
ODRX_DEFINE_STATIC_APPMODULE(L"TV_SCENEOE", TvSCENEOEModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvDbIOAppName, OdTvDbIOModule)
ODRX_DEFINE_STATIC_APPMODULE(L"TV_ISM", TvISMModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvTfModuleName, OdTvTfModule)
ODRX_DEFINE_STATIC_APPMODULE( OdTvPartialViewingModuleName, OdTvDbPartialViewingModuleImpl )

ODRX_DEFINE_STATIC_APPMODULE(OdTvVisualizeDeviceModuleName, VisualizeDeviceModule)

ODRX_DEFINE_STATIC_APPMODULE(OdTvObj2VisualizeModuleName, OdTvVisualizeObjFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdObjToolkitModuleName, OdObjToolkitModuleImpl)

ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName, OdRasterProcessingServicesImpl)
ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME, ExRasterModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTrGL2ModuleName, OdTrGL2RenderModule)
ODRX_DEFINE_STATIC_APPMODULE(OdWinGLES2ModuleName, GLES2Module)

//TvCore
ODRX_DEFINE_STATIC_APPMODULE( OdTvCoreDatabaseModuleName, OdTvCoreDatabaseModule )
ODRX_DEFINE_STATIC_APPMODULE( OdTvCoreDatabaseIOModuleName, OdTvCoreDatabaseIOModule )
ODRX_END_STATIC_MODULE_MAP()

#endif

void OnShowMessage(const LPCWSTR& text, const LPCWSTR& title)
{
  MessageBox(NULL, text, title, MB_ICONWARNING);
}

// Method for the ODA SDK activation
void CChildView::ODASdkActivate()
{
  static const char* ActInfo[] = {
#ifdef TEIGHA_TRIAL
    "", ""
#else
    //"UserInfo", "UserSignature" 

    // Before compiling, a ODA SDK activation file should be placed in a location that a compiler can access, 
    // otherwise you get a compiler error such as "Kernel/Extensions/ExServices/ExSystemServices.h:43:10: fatal error: 'OdActivationInfo' file not found". 
    // To learn about ODA SDK activation, see the activation guide at https://docs.opendesign.com/tkernel/oda_activation.html    
#include "OdActivationInfo"
#endif
  };

  odActivate(ActInfo[0], ActInfo[1]);
  odTvInitialize();
}

// Method for the ODA SDK deactivation
void CChildView::ODASdkDeactivate()
{
  odTvUninitialize();
  odCleanUpStaticData();
}

// update device
void CChildView::updateDevice()
{
  OdTvGsDevicePtr pDevice = m_deviceId.openObject();
  if (!pDevice.isNull())
    pDevice->update();
}
// Method for remove data from database
void CChildView::clearData()
{
  m_navigationCommand = kNone;
  if (m_dbId.isNull() && m_deviceId.isNull())
    return;

  //retrieve the factory id
  OdTvFactoryId factId = odTvGetFactory();

  //remove all
  factId.clearDatabases();

  //flush id's
  m_dbId.setNull();
  m_deviceId.setNull();
}

// Visualize sample
bool CChildView::generateSample()
{
  // remove previous data from database
  clearData();

  //retrieve the factory id
  OdTvFactoryId factId = odTvGetFactory();

  // Create tv database
  m_dbId = factId.createDatabase();

  OdTvModelId modelId;
  try
  {
    OdTvResult rc;
    OdTvDatabasePtr pDatabase = m_dbId.openObject(OdTv::kForWrite, &rc);

    // Create model
    modelId = pDatabase->createModel("Model");

    // Create entity
    OdTvEntityId enId = modelId.openObject(OdTv::kForWrite)->appendEntity("Entity");
    {
      // Create and setup text style in database
      OdTvTextStyleId textStyle = pDatabase->createTextStyle(OD_T("kMiddleCenter"));
      {
        OdTvTextStylePtr pTextStyle = textStyle.openObject(OdTv::kForWrite);

        OdString typeface = L"Algerian";
        OdInt16 charset = 0;
        OdInt16 family = 34;
        bool bold = true;
        bool italic = true;
        pTextStyle->setFont(typeface, bold, italic, charset, family);
        pTextStyle->setAlignmentMode(OdTvTextStyle::kMiddleCenter);
        pTextStyle->setTextSize(0.17);
      }

      OdTvEntityPtr pEn = enId.openObject(OdTv::kForWrite);
      // Create text geometry data
      OdTvGeometryDataId textId1 = pEn->appendText(OdTvPoint(-0.07, 0.1, 0.), "ODA");
      {
        // Set color for geometry data
        textId1.openObject()->setColor(OdTvColorDef(204, 0, 51));
        OdTvTextDataPtr ptxt = textId1.openAsText();
        // Set text style for text
        ptxt->setTextStyle(textStyle);
      }

      OdTvGeometryDataId textId2 = pEn->appendText(OdTvPoint(-0.07, -0.2, 0.), "VISUALIZE SDK");
      {
        textId2.openObject()->setColor(OdTvColorDef(51, 0, 204));
        OdTvTextDataPtr ptxt = textId2.openAsText();
        ptxt->setTextStyle(textStyle);
      }

      // Declare point array for polygon
      OdTvPointArray pnts;
      double xMin = -0.95, xMax = 0.95, yMin = -0.45, yMax = 0.45;
      pnts.append(OdTvPoint(xMin, yMin, 0.));
      pnts.append(OdTvPoint(xMin, yMax, 0.));
      pnts.append(OdTvPoint(xMax, yMax, 0.));
      pnts.append(OdTvPoint(xMax, yMin, 0.));
      // Create polygon geometry data
      OdTvGeometryDataId rectId = pEn->appendPolygon(pnts);
      {
        OdTvGeometryDataPtr pGeom = rectId.openObject();
        pGeom->setColor(OdTvColorDef(128, 0, 255));
        pGeom->setLineWeight(7);
      }
    }

    // Get rect from current window
    RECT clRect;
    GetClientRect(&clRect);
    OdTvDCRect rect((long)clRect.left, (long)clRect.right, (long)clRect.bottom, (long)clRect.top);

    // Create device
    m_deviceId = pDatabase->createDevice("Device1", m_hWnd, rect, OdTvGsDevice::kOpenGLES2, NULL, &rc);

    if (rc != tvOk)
    {
      OnShowMessage((LPCWSTR)L"Device can not be created.", (LPCWSTR)L"Error.");
      return false;
    }
  }
  catch (OdTvError&/* e*/)
  {
    return false;
  }

  // Open device
  OdTvResult rc;
  OdTvGsDevicePtr pDevice = m_deviceId.openObject(OdTv::kForWrite, &rc);
  if (rc != tvOk)
    return false;

  // Create view
  m_viewId = pDevice->createView("View1", true, &rc);
  if (rc != tvOk)
    return false;
  // Add view to device
  pDevice->addView(m_viewId);

  // Add current model to the view
  {
    OdTvGsViewPtr viewPtr = m_viewId.openObject();

    // Setup view to make it contr directional with the WCS normal
    viewPtr->setView(OdTvPoint(0., 0., 1.), OdTvPoint(0., 0., 0.), OdTvVector(0., 1., 0.), 1., 1.);

    // Add main model to the view
    viewPtr->addModel(modelId);

    // Set current view as active
    viewPtr->setActive(true);

    // Set the render mode
    viewPtr->setMode(OdTvGsView::k2DOptimized);
  }

  pDevice->update();

  return true;
}

// Method for open files with .OBJ extension
bool CChildView::openFile()
{
  // Call open dialog and get file path
  OPENFILENAME ofn;
  char szFile[260];

  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = ::GetActiveWindow();
  ofn.lpstrFile = (LPWSTR)szFile;
  ofn.lpstrFile[0] = '\0';
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter = L"Open Design Visualize Stream (*.vsf)\0*.vsf\0OBJ files(*.obj)\0*.obj\0All files(*.*)\0*.*\0\0";
  ofn.Flags = OFN_FILEMUSTEXIST;

  if (!GetOpenFileName(&ofn))
    return false;

  // If file path is valid, remove previous data and create new
  clearData();

  //extract file extension
  std::wstring strFileW(ofn.lpstrFile);
  size_t pos = strFileW.find_last_of(L".");
  if (pos == std::wstring::npos)
    return false;

  std::wstring strExt = strFileW.substr(pos + 1, strFileW.length() - pos);
  transform(strExt.begin(), strExt.end(), strExt.begin(), toupper);

  //retrieve the factory id
  OdTvFactoryId factId = odTvGetFactory();

  // Try to import file
  OdTvResult rc = tvOk;
  try
  {
    if (strExt != L"VSF")
    {
      // Declare import parameters for .obj file and set file path
      OdTvObjImportParams  m_objImportParam;
      m_objImportParam.setFilePath(ofn.lpstrFile);

      // Import database
      m_dbId = factId.importFile(&m_objImportParam, &rc);
    }
    else
    {
      OdTvVsfImportParams params;
      params.setFilePath( ofn.lpstrFile );
      params.setMtImport( true );
      m_dbId = factId.importFile( &params, &rc );
    }

    if (rc != tvOk)
    {
      OnShowMessage((LPCWSTR)L"Loading of file was failed.", (LPCWSTR)L"Error");
      return false;
    }
  }
  catch (OdTvError& e)
  {
    OnShowMessage((LPCWSTR)L"Loading of file was failed.", (LPCWSTR)e.description());
    return false;
  }

  // Get device (here it is always the first device) and setup
  if (m_dbId.isValid())
  {
    OdTvDatabasePtr pDb = m_dbId.openObject();
    if (!pDb.isNull())
    {
      OdTvDevicesIteratorPtr pIt = pDb->getDevicesIterator();
      if (!pIt.isNull())
      {
        m_deviceId = pIt->getDevice();

        // Get rect from current window
        RECT clRect;
        GetClientRect(&clRect);
        OdTvDCRect rect((long)clRect.left, (long)clRect.right, (long)clRect.bottom, (long)clRect.top);

        OdTvGsDevicePtr pDevice = m_deviceId.openObject(OdTv::kForWrite);
        m_viewId = pDevice->getActiveView();
        // Setup device
        pDevice->setupGs(m_hWnd, rect, OdTvGsDevice::kOpenGLES2, NULL);

        pDevice->setOption(OdTvGsDevice::kFXAAEnable, true);

        // Update device
        pDevice->onSize(rect);
        pDevice->update();

        return true;
      }
    }
  }
  return false;
}

double TvRound(double a)
{
  double aFloor = ::floor(a);
  if (a - aFloor >= 0.5)
    return aFloor + 1.0;
  return aFloor;
}

void CChildView::processZoom(double delta)
{
  // get the active view and perform zooming
  OdTvGsViewPtr pView = m_viewId.openObject();
  if (!pView.isNull())
  {
    OdGePoint3d pos(pView->position());
    pos.transformBy(pView->worldToDeviceMatrix());

    POINT p;
    OdTvPoint vpos;
    if (GetCursorPos(&p))
    {
      ScreenToClient(&p);
      //cursor position now in p.x and p.y
      vpos = OdTvPoint(p.x, p.y, 0.);
      vpos.z = pView->projectionMatrix()(2, 3);
    }
    else
      vpos = OdTvPoint::kOrigin;

    int vx, vy;
    vx = (int)TvRound(pos.x);
    vy = (int)TvRound(pos.y);
    vx = vpos.x - vx;
    vy = vpos.y - vy;

    double dScale = 0.9; //wheel DOWN
    if (delta > 0)
      dScale = 1.0 / dScale; //wheel UP

    OdTvVector vec(vx, vy, 0.0);
    vec.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
    pView->dolly(vec);

    pView->zoom(dScale);

    vec = OdTvVector(-vx, -vy, 0.0);
    vec.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
    pView->dolly(vec);

    m_deviceId.openObject()->update();
  }
}

bool CChildView::calculateViewExtents(OdGeBoundBlock3d& extents)
{
  // open tv view
  OdTvGsViewPtr pView = m_viewId.openObject(OdTv::kForWrite);
  if (pView.isNull())
    return false;

  OdGeBoundBlock3d pViewExt;
  if (pView->viewExtents(pViewExt))
  {
    if (!pView->isPerspective())
      pViewExt.setToBox(true);

    OdGeMatrix3d xWorldToEye = pView->viewingMatrix();
    OdGeMatrix3d xEyeToWorld = xWorldToEye.invert();

    //transfrom extents to WCS
    pViewExt.transformBy(xEyeToWorld);

    extents = pViewExt;

    return true;
  }

  return false;

}

void CChildView::truncateHugeBelow(OdGePoint3d& pt)
{
  if (pt.x < -10e100)
    pt.x = -10e100;
  if (pt.y < -10e100)
    pt.y = -10e100;
  if (pt.z < -10e100)
    pt.z = -10e100;
}

void CChildView::truncateHugeAbove(OdGePoint3d& pt)
{
  if (pt.x > 10e100)
    pt.x = 10e100;
  if (pt.y > 10e100)
    pt.y = 10e100;
  if (pt.z > 10e100)
    pt.z = 10e100;
}

void CChildView::processZoomToExtents()
{
  if (m_viewId.isNull())
    return;

  double fw;
  double fh;
  OdGePoint3d newTarg;
  double extCoef = 1.02; //in orthographic for not to be fully equal to the extents

  // open tv view
  OdTvGsViewPtr pView = m_viewId.openObject(OdTv::kForWrite);
  if (pView.isNull())
    return;

  bool bPerspective = pView->isPerspective();

  //0. Try to get the viewport extents
  OdGeBoundBlock3d wcsExt;
  bool bHasValidExtents = calculateViewExtents(wcsExt);

  OdGeBoundBlock3d pViewExt;
  if (bHasValidExtents)
  {
    wcsExt.transformBy(pView->viewingMatrix());
    pViewExt = wcsExt;
  }
  else
  {
    if (pView->viewExtents(pViewExt))
    {
      if (!bPerspective)
        pViewExt.setToBox(true);
    }
    else
      return;
  }

  //1. Get a few main params
  OdTvPoint viewTarg = pView->target();
  OdGeVector3d viewDir = pView->position() - viewTarg;

  //2. Get the Eye to World matrix
  OdGeMatrix3d xWorldToEye = pView->viewingMatrix();
  OdGeMatrix3d xEyeToWorld = xWorldToEye.invert();


  if (!pViewExt.isBox())
    pViewExt.setToBox(true);

  OdGePoint3d min = pViewExt.minPoint(), max = pViewExt.maxPoint();

  // clip huge extents
  truncateHugeBelow(min);
  truncateHugeAbove(max);

  // set target to center of the scene, keeping view direction:
  newTarg = xEyeToWorld * (min + (max - min) / 2.0);

  // keeping distance from target to front & back planes
  newTarg = newTarg.orthoProject(OdGePlane(viewTarg, viewDir));

  fw = pViewExt.maxPoint().x - pViewExt.minPoint().x;
  fh = pViewExt.maxPoint().y - pViewExt.minPoint().y;
  if (!OdEqual(extCoef, 1.0))
  {
    fw *= extCoef;
    fh *= extCoef;
  }

  // final setup of the view
  OdTvVector yVector = pView->upVector();
  OdTvVector xVector = yVector.crossProduct(viewDir);

  const double dirLen = viewDir.length(), tol = 10e-8;
  const double dirLenIdent = OdZero(dirLen, tol) ? 1.0 : dirLen;
  const double targetLen = newTarg.asVector().dotProduct(viewDir) / dirLenIdent;
  if (targetLen > 1. && OdZero(dirLenIdent / targetLen, tol))
  {
    const double precMult = (targetLen / dirLenIdent) * tol;
    pView->setView(newTarg + viewDir * precMult, newTarg, yVector, fw, fh, bPerspective ? OdTvGsView::kPerspective : OdTvGsView::kParallel);
  }
  else
    pView->setView(newTarg + viewDir, newTarg, yVector, fw, fh, bPerspective ? OdTvGsView::kPerspective : OdTvGsView::kParallel);

  updateDevice();
}

OdTvPoint CChildView::toEyeToWorld(int x, int y)
{
  //calculate point in world coordinate
  if (m_viewId.isNull())
    return OdTvPoint::kOrigin;

  OdTvGsViewPtr pView = m_viewId.openObject(OdTv::kForWrite);

  OdGePoint3d wcsPt(x, y, 0.0);
  if (pView->isPerspective())
  {
    wcsPt.z = pView->projectionMatrix()(2, 3);
  }
  wcsPt.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
  wcsPt.z = 0.;
  // eye CS at this point.

  //transform to world coordinate system
  wcsPt.transformBy(pView->eyeToWorldMatrix());

  return wcsPt;
}

void CChildView::processPan(int x, int y)
{
  if (m_viewId.isNull())
    return;
  OdTvGsViewPtr pView = m_viewId.openObject();
  // calculate click point in WCS
  OdGePoint3d pt = toEyeToWorld(x, y);
  //obtain delta for dolly
  OdGeVector3d delta = (m_panInfo.prevPos - (pt - m_panInfo.curPos)).asVector();
  // transform delta to eye
  delta.transformBy(pView->viewingMatrix());
  // perform camera moving
  pView->dolly(delta.x, delta.y, delta.z);
  // remember the difference between click point in WCS and camera previous position
  m_panInfo.prevPos = pt - m_panInfo.curPos.asVector();
  // remember camera current position
  m_panInfo.curPos = pView->position();
  updateDevice();
}

void CChildView::processOrbit(int x, int y)
{
  if (m_viewId.isNull())
    return;
  OdTvGsViewPtr pView = m_viewId.openObject();
  // calculate click point in WCS
  OdGePoint3d pt = toEyeToWorld(x, y);
  // transfer point to the eye coordinate system
  OdGePoint3d ptView = pView->viewingMatrix() * pt;

  // calculate the angles for the rotation about appropriate axes
  double distX = ptView.x - m_orbitInfo.prevPt.x; // around vertical
  double distY = ptView.y - m_orbitInfo.prevPt.y; // around horizontal

  distX *= -OdaPI / m_orbitInfo.delta;
  distY *= OdaPI / m_orbitInfo.delta;

  // perform camera orbiting
  OdGeVector3d delta;
  OdGeVector3d target = pView->target().asVector();
  delta = m_orbitInfo.viewCenter.asVector() - target;
  delta.transformBy(pView->viewingMatrix());

  // the rotation should be performed around the 'pt'.
  // That's why at first we should move the camera with purpose make target equal to the 'pt.
  // Then we should perform the rotation and finally we should to move the camera in opposite direction
  pView->dolly(delta);
  pView->orbit(distY, distX);
  pView->dolly(-delta);

  // store previous click point
  m_orbitInfo.prevPt = ptView;

  updateDevice();
}


void CChildView::highlight(const OdTvSelectionSetPtr& pSSet, bool bDoIt)
{
  if (m_viewId.isNull())
    return;
  OdTvGsViewPtr pView = m_viewId.openObject();
  if (pView.isNull())
    return;

  for (OdTvSelectionSetIteratorPtr pIter = pSSet->getIterator(); !pIter->done(); pIter->step())
  {
    //get entity
    OdTvEntityId id = pIter->getEntity();
    if (id.isNull())
      return;

    //get sub item
    OdTvSubItemPath path;
    pIter->getPath(path);
    //perform highlight
    pView->highlight(id, path, bDoIt);
  }

  updateDevice();
}

void CChildView::processSelect(int x, int y)
{
  if (m_viewId.isNull())
    return;
  OdTvGsViewPtr pView = m_viewId.openObject();
  if (pView.isNull())
    return;

  if (!m_pSSet.isNull() && m_pSSet->numItems() > 0)
  {
    highlight(m_pSSet, false);
    m_pSSet.release();
  }

  OdTvDCPoint pt(x, y);
  OdTvSelectionOptions opt;
  opt.setLevel(OdTvSelectionOptions::kEntity);
  m_pSSet = pView->select(&pt, 1, opt, OdTvModelId());
  if (m_pSSet.isNull() || m_pSSet->numItems() == 0)
    return;

  highlight(m_pSSet, true);
}

// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

// CChildView

CChildView::CChildView() : m_bIsLButtonDown(false), m_navigationCommand(kNone)
{
#ifndef _TOOLKIT_IN_DLL_
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  ODASdkActivate();
}

BOOL CChildView::PreTranslateMessage(MSG* pMsg)
{
  if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
  {
    if (!m_pSSet.isNull() && m_pSSet->numItems() > 0)
    {
      highlight(m_pSSet, false);
      m_pSSet.release();
    }
    m_navigationCommand = kNone;
  }

  return CWnd::PreTranslateMessage(pMsg);
}

CChildView::~CChildView()
{
  ODASdkDeactivate();
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
  updateDevice();
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
  // Update and resize device after resize event
  OdTvGsDevicePtr pDevice = m_deviceId.openObject();
  if (!pDevice.isNull())
  {
    OdTvDCRect rect(0, cx, cy, 0);
    pDevice->onSize(rect);
    pDevice->update();
  }
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
  if (m_viewId.isNull())
    return;
  if (m_navigationCommand == kPan)
  {
    m_panInfo.curPos = m_viewId.openObject()->position();
    m_panInfo.prevPos = toEyeToWorld(point.x, point.y) - m_panInfo.curPos.asVector();
  }
  else if (m_navigationCommand == kOrbit)
  {
    OdTvGsViewPtr pView = m_viewId.openObject();
    // calculate click point in WCS
    OdGePoint3d pt = toEyeToWorld(point.x, point.y);
    // transfer point to the eye coordinate system
    m_orbitInfo.prevPt = pView->viewingMatrix() * pt;
    // calculate mouse move to rotation angle conversion coefficient in base of viewport dc size
    OdGePoint3d pt1;
    OdGePoint2d pt2;
    pView->viewDcCorners((OdGePoint2d&)pt1, pt2);
    pt2.x -= pt1.x;
    pt2.y -= pt1.y;
    double r = odmin(pt2.x, pt2.y);
    m_orbitInfo.delta = r;

    OdGeBoundBlock3d extents;
    pView->viewExtents(extents);
    m_orbitInfo.viewCenter = extents.center();
    m_orbitInfo.viewCenter.transformBy(pView->eyeToWorldMatrix());
  }

  if(!m_dbId.isNull())
    m_bIsLButtonDown = true;
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
  if (m_bIsLButtonDown && m_navigationCommand == kNone)
  {
    processSelect(point.x, point.y);
  }

  m_bIsLButtonDown = false;
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
  if (m_navigationCommand == kNone || !m_bIsLButtonDown)
    return;
  if (m_navigationCommand == kPan)
    processPan(point.x, point.y);
  else if (m_navigationCommand == kOrbit)
    processOrbit(point.x, point.y);
}

BOOL CChildView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
  processZoom(zDelta);
  return TRUE;
}



void CChildView::OnFileOpen32771()
{
  openFile();
}


void CChildView::OnFileGeneratesample()
{
  generateSample();
}

void CChildView::OnPanClick()
{
  m_navigationCommand = kPan;
}

void CChildView::OnOrbitClick()
{
  m_navigationCommand = kOrbit;
}

void CChildView::OnZoomExtCLick()
{
  processZoomToExtents();
}
