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
// TVisualizeFirstApp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "OdVisualizeFirstApp.h"
#include "OdVisualizeSamples.h"
#include "OdVisualizeAppStreaming.h"

// ODA SDK
#include "OdaCommon.h"
#include "Rxinit.h"
// Visualize
#include "TvDatabase.h"
#include "TvFactory.h"
#include "TvError.h"
#include "OdModuleNames.h"
#include "RxDynamicModule.h"
#include "TvModuleNames.h"
#include "TvCoreModulesNames.h"
#include <string>

#define MAX_LOADSTRING 100
#if (_MSC_VER < 1500) 
#define WM_MOUSEWHEEL                   0x020A
#define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))
#endif

#define PERSP_CONST 42.0

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

#if(_MSC_VER == 1400)
#define _SA_annotes3(n,pp1,pp2,pp3)
#define _Group_impl_(annos)
#define _SAL_nop_impl_ X
#define _Group_(annos)                 _Group_impl_(annos _SAL_nop_impl_)
#define _SAL2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _Group_(annotes _SAL_nop_impl_)
#define _Pre1_impl_(p1)
#define _Pre_valid_impl_
#define _Deref_pre1_impl_(p1)
#define _In_                            _SAL2_Source_(_In_, (), _Pre1_impl_(__notnull_impl_notref) _Pre_valid_impl_ _Deref_pre1_impl_(__readaccess_impl_notref))
#define _In_opt_                        _SAL2_Source_(_In_opt_, (), _Pre1_impl_(__maybenull_impl_notref) _Pre_valid_impl_ _Deref_pre_readonly_)
#endif

// Ifc
#ifdef IFC_MODULES_ENABLED
#include "../SDAI/Include/Common/daiModuleNames.h"
#include "../Ifc/Include/Common/ModuleNames.h"
#endif

#ifndef _TOOLKIT_IN_DLL_
// Visualize API
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxCommonDataAccessModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvDbCoreModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvDbIOModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TvISMModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TvSCENEOEModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvTfModule);
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

//DWG
#ifdef DWG_MODULES_ENABLED
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeDwgFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualize2DwgFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDbIOModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ISMModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(SCENEOEModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDbEntitiesModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRecomputeDimBlockModule);
#endif // DWG_MODULES_ENABLED

// IFC
#ifdef IFC_MODULES_ENABLED
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeIfcFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x3Module);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4Module);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcGeomModuleImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcFacetModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcBrepBuilderModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4x3_RC1Module);
#endif // IFC_MODULES_ENABLED
//TvCore
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvCoreDatabaseModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvCoreDatabaseIOModule );
//Vsf2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvVisualizeVsfFilerModule );

ODRX_BEGIN_STATIC_MODULE_MAP()
ODRX_DEFINE_STATIC_APPMODULE(OdTvModuleName, OdTvModule)
ODRX_DEFINE_STATIC_APPMODULE(RxCommonDataAccessModuleName, OdRxCommonDataAccessModule)
ODRX_DEFINE_STATIC_APPMODULE( OdTvDbCoreModuleName, OdTvDbCoreModule )
ODRX_DEFINE_STATIC_APPMODULE(L"TV_SCENEOE", TvSCENEOEModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvDbIOAppName, OdTvDbIOModule)
ODRX_DEFINE_STATIC_APPMODULE(L"TV_ISM", TvISMModule)
ODRX_DEFINE_STATIC_APPMODULE( OdTvTfModuleName, OdTvTfModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvPartialViewingModuleName, OdTvDbPartialViewingModuleImpl )

ODRX_DEFINE_STATIC_APPMODULE(OdTvVisualizeDeviceModuleName, VisualizeDeviceModule)

ODRX_DEFINE_STATIC_APPMODULE(OdTvObj2VisualizeModuleName, OdTvVisualizeObjFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdObjToolkitModuleName, OdObjToolkitModuleImpl)

ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName, OdRasterProcessingServicesImpl)
ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME, ExRasterModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTrGL2ModuleName, OdTrGL2RenderModule)
ODRX_DEFINE_STATIC_APPMODULE(OdWinGLES2ModuleName, GLES2Module)

//DWG
#ifdef DWG_MODULES_ENABLED
ODRX_DEFINE_STATIC_APPMODULE(OdTvDwg2VisualizeModuleName, OdTvVisualizeDwgFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvVisualize2DwgModuleName, OdTvVisualize2DwgFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdDbIOAppName, OdDbIOModule)
ODRX_DEFINE_STATIC_APPMODULE(L"ISM", ISMModule)
ODRX_DEFINE_STATIC_APPMODULE(L"SCENEOE", SCENEOEModule)
ODRX_DEFINE_STATIC_APPLICATION(OdModelerGeometryModuleName, ModelerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdDbEntitiesAppName, OdDbEntitiesModule)
ODRX_DEFINE_STATIC_APPLICATION(OdRecomputeDimBlockModuleName, OdRecomputeDimBlockModule)
#endif // DWG_MODULES_ENABLED

// IFC
#ifdef IFC_MODULES_ENABLED
ODRX_DEFINE_STATIC_APPMODULE(OdTvIfc2VisualizeModuleName, OdTvVisualizeIfcFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x3ModuleName, OdIfc2x3Module)
ODRX_DEFINE_STATIC_APPMODULE(OdIfc4ModuleName, OdIfc4Module)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcGeomModuleName, OdIfcGeomModuleImpl)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcFacetModelerModuleName, OdIfcFacetModelerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcBrepBuilderModuleName, OdIfcBrepBuilderModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfc4x3RC1ModuleName, OdIfc4x3_RC1Module)
#endif
//TvCore
ODRX_DEFINE_STATIC_APPMODULE( OdTvCoreDatabaseModuleName, OdTvCoreDatabaseModule )
ODRX_DEFINE_STATIC_APPMODULE( OdTvCoreDatabaseIOModuleName, OdTvCoreDatabaseIOModule )
//Vsf2Visualize
ODRX_DEFINE_STATIC_APPMODULE( OdTvVsf2VisualizeModuleName, OdTvVisualizeVsfFilerModule )

ODRX_END_STATIC_MODULE_MAP()

#endif

// Declare TV database and device
OdTvDatabaseId dbId;
OdTvGsDeviceId deviceId;
OdTvGsViewId viewId;
//Index of active view (viewId) in the list of device views
OdUInt8 activeView;
bool lMouseBtnIsPressed;
OdTvSelectionSetPtr pSSet;

void ClearData( bool bClearDbs );

// fields for navigation
enum NavigationCommands
{
  kNone  = 0,
  kPan   = 1,
  kOrbit = 2
} navigationController;

struct PanInfo
{
  OdTvPoint curPos;
  OdTvPoint prevPos;
} panInfo;

struct OrbitInfo
{
  OdTvPoint prevPt;
  double delta;
  OdTvPoint viewCenter;
} orbitInfo;

#ifdef OD_VISUALIZE_APP_ENABLE_STREAMING
CStreamingDialog* pStreamingDlg;

class CSimpleApplicationRender : public CApplicationBaseRender
{
protected:
  HWND m_hwnd;
  OdUInt32 m_nSchedulerDelay;
  bool m_bSchedulerOn;
  bool m_bUseSceneGraph;
public:
  CSimpleApplicationRender( HWND hwnd ) : m_hwnd( hwnd ) 
  {
    m_nSchedulerDelay = 0;
    m_bSchedulerOn = false;
    m_bUseSceneGraph = true;
  }

  virtual bool doRender( OdTvDatabaseId _dbId )
  {
    if( _dbId != dbId )
    {
      ClearData( false );
      dbId = _dbId;
    }
    if( dbId.isValid() )
    {
      OdTvDatabasePtr pDb = dbId.openObject();
      if( !pDb.isNull() )
      {
        OdTvDevicesIteratorPtr pIt = pDb->getDevicesIterator();
        if( !pIt.isNull() )
        {
          OdTvGsDeviceId newDevId = pIt->getDevice();
          if( deviceId != newDevId )
          {
            deviceId = pIt->getDevice();

            // Get rect from current window
            RECT clRect;
            GetClientRect( m_hwnd, &clRect );
            OdTvDCRect rect( (long)clRect.left, (long)clRect.right, (long)clRect.bottom, (long)clRect.top );

            OdTvGsDevicePtr pDevice = deviceId.openObject( OdTv::kForWrite );
            viewId = pDevice->getActiveView();
            // Setup device
            pDevice->setupGs( m_hwnd, rect, OdTvGsDevice::kOpenGLES2, NULL );

            //set option to use Scene Graph (performance optimization)
            pDevice->setOption( OdTvGsDevice::kUseSceneGraph, m_bUseSceneGraph );
            pDevice->setOption( OdTvGsDevice::kFXAAEnable, true );
            if( m_nSchedulerDelay > 0 )
            {
              pDevice->setSceneGraphCreationInteruptTime( m_nSchedulerDelay );
              switchScheduler( m_bSchedulerOn );
            }

            // Update device
            pDevice->onSize( rect );
            pDevice->update();
            activeView = 0;

            navigationController = kNone;
          }
          else
          {
            OdTvGsDevicePtr pDevice = deviceId.openObject( OdTv::kForWrite );
            pDevice->update();
          }
        }
      }
    }
    return true;
  }

  virtual void setupSceneGraphScheduler( OdUInt32 msec )
  {
    m_nSchedulerDelay = msec;
  }

  virtual void switchScheduler( bool bOn )
  {
    m_bSchedulerOn = bOn;
    if( !deviceId.isNull() )
    {
      OdTvGsDevicePtr pDevice = deviceId.openObject( OdTv::kForWrite );
      pDevice->setOption( OdTvGsDevice::kDelaySceneGraphProc, !bOn );
    }
  }

  virtual bool isSchedulerOn() const
  {
    return m_nSchedulerDelay > 0 && m_bSchedulerOn;
  }

  virtual void setUseSceneGraph( bool bUse )
  {
    m_bUseSceneGraph = bUse;
  }

  virtual bool getUseSceneGraph() const 
  { 
    return m_bUseSceneGraph;
  }
};

CSimpleApplicationRender* pSimpleRender;

#endif

/**
\details
An implementation of sample context
*/
class OdVisualizeAppSampleContext : public OdVisualizeSampleContext
{
  HWND m_hwnd;
public:
  OdVisualizeAppSampleContext( HWND hwnd ) : m_hwnd( hwnd )
  {
  }
  virtual OdString filePath( FileType type ) const
  {
    // Call open dialog and get file path
    OPENFILENAME ofn;
    char szFile[ 260 ];

    ZeroMemory( &ofn, sizeof( ofn ) );
    ofn.lStructSize = sizeof( ofn );
    ofn.hwndOwner = ::GetActiveWindow();
    ofn.lpstrFile = (LPWSTR)szFile;
    ofn.lpstrFile[ 0 ] = '\0';
    ofn.nMaxFile = sizeof( szFile );
    switch( type )
    {
    case kOBJ:
      ofn.lpstrFilter = L"*.obj\0*.obj\0\0";
      break;
    case kPNG:
      ofn.lpstrFilter = L"*.png\0*.png\0\0";
      break;
    default:
      ofn.lpstrFilter = NULL;
    }
    ofn.Flags = OFN_FILEMUSTEXIST;

    if( !GetOpenFileName( &ofn ) )
      return OdString::kEmpty;
    return OdString( ofn.lpstrFile );
  }

  virtual OdTvGsDeviceId createDevice( OdTvDatabaseId dbId )
  {
    // Get rect from current window
    RECT clRect;
    GetClientRect( m_hwnd, &clRect );
    OdTvDCRect rect( (long)clRect.left, (long)clRect.right, (long)clRect.bottom, (long)clRect.top );
    // Create device
    OdTvGsDeviceId devId = dbId.openObject( OdTv::kForWrite )->createDevice( "Device1", m_hwnd, rect, OdTvGsDevice::kOpenGLES2, NULL );
    return devId;
  }

  virtual OdTvDCRect setupDevice(OdTvGsDeviceId devId)
  {
    // Get rect from current window
    RECT clRect;
    GetClientRect(m_hwnd, &clRect);
    OdTvDCRect rect((long)clRect.left, (long)clRect.right, (long)clRect.bottom, (long)clRect.top);

    OdTvGsDevicePtr pDevice = devId.openObject(OdTv::kForWrite);

    // Setup device
    pDevice->setupGs(m_hwnd, rect, OdTvGsDevice::kOpenGLES2, NULL);

    return rect;
  }

  //setters
  virtual void setActiverDevice( OdTvGsDeviceId id ) const
  {
    deviceId = id;
  }
  virtual void setActiveDatabase( OdTvDatabaseId id ) const
  {
    dbId = id;
  }
  virtual void setActiveView( OdTvGsViewId id, OdUInt8 num ) const
  {
    viewId = id;
    activeView = num;
  }

  int showMessageBox(LPCTSTR lpText, LPCTSTR lpCaption, UINT uType)
  {
    return MessageBox(m_hwnd, lpText, lpCaption, uType);
  }

  static OdVisualizeSampleManager::Samples sampleFromId( int id )
  {
    switch (id)
    {
    case ID_SAMPLE_MULTIVIEW:
      return OdVisualizeSampleManager::kMultiViewSample;
    case ID_SAMPLE_WALKINGANIMATION:
      return OdVisualizeSampleManager::kWalkingAnimation;
    }
    return OdVisualizeSampleManager::kInvalidSample;
  }
};

// Method for the ODA SDK activation
void ODASdkActivate()
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
}

// Method for the ODA SDK deactivation
void ODASdkDeactivate()
{
  odCleanUpStaticData();
}

// update device
void updateDevice()
{
  OdTvGsDevicePtr pDevice = deviceId.openObject();
  if (!pDevice.isNull())
    pDevice->update();
}
// Method for remove data from database
void ClearData( bool bClearDbs )
{
  if (!pSSet.isNull())
    pSSet.release();

  if (dbId.isNull() && deviceId.isNull())
    return;

  //retrieve the factory id
  OdTvFactoryId factId = odTvGetFactory();

  //remove all
  if( bClearDbs )
    factId.clearDatabases();

  //flush id's
  dbId.setNull();
  deviceId.setNull();
  activeView = 0;
}

void setItemChecked(HWND hWnd)
{
  if (navigationController == kNone)
    return;

  HMENU hmenu = GetMenu(hWnd);
  MENUITEMINFO menuItem = { 0 };
  menuItem.cbSize = sizeof(MENUITEMINFO);
  menuItem.fMask = MIIM_STATE;
  if(navigationController == kPan)
  {
    GetMenuItemInfo(hmenu, ID_NAVIGATION_PAN, FALSE, &menuItem);
    menuItem.fState = MFS_CHECKED;
    SetMenuItemInfo(hmenu, ID_NAVIGATION_PAN, FALSE, &menuItem);

    GetMenuItemInfo(hmenu, ID_NAVIGATION_ORBIT, FALSE, &menuItem);
    menuItem.fState = MFS_UNCHECKED;
    SetMenuItemInfo(hmenu, ID_NAVIGATION_ORBIT, FALSE, &menuItem);
  }
  else if(navigationController == kOrbit)
  {
    GetMenuItemInfo(hmenu, ID_NAVIGATION_PAN, FALSE, &menuItem);
    menuItem.fState = MFS_UNCHECKED;
    SetMenuItemInfo(hmenu, ID_NAVIGATION_PAN, FALSE, &menuItem);

    GetMenuItemInfo(hmenu, ID_NAVIGATION_ORBIT, FALSE, &menuItem);
    menuItem.fState = MFS_CHECKED;
    SetMenuItemInfo(hmenu, ID_NAVIGATION_ORBIT, FALSE, &menuItem);
  }
}

void UnCheckHighlightMenuItems(HMENU hmenu, int wmCurId)
{
  MENUITEMINFO menuItem = { 0 };
  menuItem.cbSize = sizeof(MENUITEMINFO);
  menuItem.fMask = MIIM_STATE;

  GetMenuItemInfo(hmenu, ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_1, FALSE, &menuItem);
  if (wmCurId != ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_1)
  {
    menuItem.fState = MFS_UNCHECKED;
    SetMenuItemInfo(hmenu, ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_1, FALSE, &menuItem);
  }
  GetMenuItemInfo(hmenu, ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_2, FALSE, &menuItem);
  if (wmCurId != ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_2)
  {
    menuItem.fState = MFS_UNCHECKED;
    SetMenuItemInfo(hmenu, ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_2, FALSE, &menuItem);
  }
  GetMenuItemInfo(hmenu, ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_3, FALSE, &menuItem);
  if (wmCurId != ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_3)
  {
    menuItem.fState = MFS_UNCHECKED;
    SetMenuItemInfo(hmenu, ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_3, FALSE, &menuItem);
  }
}

// Visualize sample
void GenerateSample(HWND hWnd)
{
  // remove previous data from database
  ClearData( true );

  //retrieve the factory id
  OdTvFactoryId factId = odTvGetFactory();

  // Create tv database
  dbId = factId.createDatabase();

  OdTvModelId modelId;
  try
  {
    OdTvResult rc;
    OdTvDatabasePtr pDatabase = dbId.openObject(OdTv::kForWrite, &rc);

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
    GetClientRect(hWnd, &clRect);
    OdTvDCRect rect((long)clRect.left, (long)clRect.right, (long)clRect.bottom, (long)clRect.top);

    // Create device
    deviceId = pDatabase->createDevice("Device1", hWnd, rect, OdTvGsDevice::kOpenGLES2, NULL, &rc);

    if (rc != tvOk)
      MessageBox(NULL, (LPCWSTR)L"Device can not be created.", (LPCWSTR)L"Error.", MB_ICONWARNING);
  }
  catch (OdTvError& e)
  {
    OdString descr = e.description();
  }

  // Open device
  OdTvResult rc;
  OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite, &rc);
  if (rc != tvOk)
    return;

  // Create view
  viewId = pDevice->createView("View1", true, &rc);
  if (rc != tvOk)
    return;
  // Add view to device
  pDevice->addView(viewId);

  // Add current model to the view
  {
    OdTvGsViewPtr viewPtr = viewId.openObject();

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

  activeView = 0;
  
  navigationController = kNone;

  setItemChecked(hWnd);
}

// Method for open files with .OBJ extension
void OpenFile(HWND hWnd)
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

  ofn.lpstrFilter = L"ODA Visualize Stream Format (*.vsf)\0*.vsf\0OBJ files (*.obj)\0*.obj\0IFC (*.ifc)\0*.ifc\0Drawings files (*.dwg)\0*.dwg\0All files(*.*)\0*.*\0\0";
  ofn.Flags = OFN_FILEMUSTEXIST;

  if (!GetOpenFileName(&ofn))
    return;

  // If file path is valid, remove previous data and create new
  ClearData( true );

  //uncheck some menu items
  UnCheckHighlightMenuItems(GetMenu(hWnd), -1);

  //extract file extension
  std::wstring strFileW(ofn.lpstrFile);
  size_t pos = strFileW.find_last_of(L".");
  if (pos == std::wstring::npos)
    return;

  std::wstring strExt = strFileW.substr(pos + 1, strFileW.length() - pos);
  transform(strExt.begin(), strExt.end(), strExt.begin(), toupper);

  //retrieve the factory id
  OdTvFactoryId factId = odTvGetFactory();

  // Try to import file
  OdTvResult rc = tvOk;
  bool bSGEnabled = true;
  try
  {
    if (strExt == L"OBJ")
    {
      // Declare import parameters for .obj file and set file path
      OdTvObjImportParams  m_objImportParam;
      m_objImportParam.setFilePath(ofn.lpstrFile);

      // Import database
      dbId = factId.importFile(&m_objImportParam, &rc);

      bSGEnabled = false;
    }
    else if (strExt == L"IFC")
    {
      // Declare import parameters for .ifc file and set file path
      OdTvIfcImportParams m_ifcImportParam;
      m_ifcImportParam.setFilePath(ofn.lpstrFile);
      m_ifcImportParam.setEnableBGColor(false);

      // Import database
      dbId = factId.importFile(&m_ifcImportParam, &rc);
    }
    else if (strExt == L"DWG")
    {
      // Declare import parameters for .dwg file and set file path
      OdTvDwgImportParams m_dwgImportParam;
      m_dwgImportParam.setFilePath(ofn.lpstrFile);

      // Get rect from current window
      RECT clRect;
      GetClientRect(hWnd, &clRect);
      OdTvDCRect dcRect((long)clRect.left, (long)clRect.right, (long)clRect.bottom, (long)clRect.top);
      m_dwgImportParam.setDCRect(dcRect);

      // Import database
      dbId = factId.importFile(&m_dwgImportParam, &rc);
    }
    else
    {
      OdTvVsfImportParams params;
      params.setFilePath( ofn.lpstrFile );
      params.setMtImport( true );
      dbId = factId.importFile( &params, &rc );
    }

    if (rc != tvOk)
      MessageBox(NULL, (LPCWSTR)L"Loading of file was failed.", (LPCWSTR)L"Error", MB_ICONWARNING);
  }
  catch (OdTvError& e)
  {
    MessageBox(NULL, (LPCWSTR)L"Loading of file was failed.", (LPCWSTR)e.description(), MB_ICONWARNING);
  }

  // Get device (here it is always the first device) and setup
  if (dbId.isValid())
  {
    OdTvDatabasePtr pDb = dbId.openObject();
    if (!pDb.isNull())
    {
      OdTvDevicesIteratorPtr pIt = pDb->getDevicesIterator();
      if (!pIt.isNull())
      {
        deviceId = pIt->getDevice();

        // Get rect from current window
        RECT clRect;
        GetClientRect(hWnd, &clRect);
        OdTvDCRect rect((long)clRect.left, (long)clRect.right, (long)clRect.bottom, (long)clRect.top);

        OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);
        viewId = pDevice->getActiveView();
        // Setup device
        pDevice->setupGs(hWnd, rect, OdTvGsDevice::kOpenGLES2, NULL);

        //set option to use Scene Graph (performance optimization)
        pDevice->setOption(OdTvGsDevice::kUseSceneGraph, bSGEnabled);
        pDevice->setOption(OdTvGsDevice::kFXAAEnable, true);

        // Update device
        pDevice->onSize(rect);
        pDevice->update();
        activeView = 0;

        navigationController = kNone;
      }
    }
  }
}

void processZoom(HWND hWnd, double delta)
{
  // get the active view and perform zooming
  OdTvGsViewPtr pView = viewId.openObject();
  if (!pView.isNull())
  {
    OdGePoint3d pos(pView->position());
    pos.transformBy(pView->worldToDeviceMatrix());

    POINT p;
    OdTvPoint vpos;
    if (GetCursorPos(&p))
    { ScreenToClient(hWnd, &p);
      //cursor position now in p.x and p.y
      vpos = OdTvPoint(p.x, p.y, 0.);
      vpos.z = pView->projectionMatrix()(2, 3);
    }
    else
      vpos = OdTvPoint::kOrigin;

    int vx, vy;
    vx = (int)OdRound(pos.x);
    vy = (int)OdRound(pos.y);
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

    deviceId.openObject()->update();
  }
}

bool calculateViewExtents(OdGeBoundBlock3d& extents)
{
  // open tv view
  OdTvGsViewPtr pView = viewId.openObject(OdTv::kForWrite);
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

void processZoomToExtents()
{
  if (viewId.isNull())
    return;

  double fw;
  double fh;
  OdGePoint3d newTarg;
  double extCoef = 1.02; //in orthographic for not to be fully equal to the extents

  // open tv view
  OdTvGsViewPtr pView = viewId.openObject(OdTv::kForWrite);
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
  if (min.x < -10e100)
    min.x = -10e100;
  if (min.y < -10e100)
    min.y = -10e100;
  if (min.z < -10e100)
    min.z = -10e100;
  
  if (max.x > 10e100)
    max.x = 10e100;
  if (max.y > 10e100)
    max.y = 10e100;
  if (max.z > 10e100)
    max.z = 10e100;

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

OdTvPoint toEyeToWorld(int x, int y)
{
  //calculate point in world coordinate
  if (viewId.isNull())
    return OdTvPoint::kOrigin;

  OdTvGsViewPtr pView = viewId.openObject(OdTv::kForWrite);

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

void processPan(int x, int y)
{
  if (viewId.isNull())
    return;
  OdTvGsViewPtr pView = viewId.openObject();
  // calculate click point in WCS
  OdGePoint3d pt = toEyeToWorld(x, y);
  //obtain delta for dolly
  OdGeVector3d delta = (panInfo.prevPos - (pt - panInfo.curPos)).asVector();
  // transform delta to eye
  delta.transformBy(pView->viewingMatrix());
  // perform camera moving
  pView->dolly(delta.x, delta.y, delta.z);
  // remember the difference between click point in WCS and camera previous position
  panInfo.prevPos = pt - panInfo.curPos.asVector();
  // remember camera current position
  panInfo.curPos = pView->position();
  updateDevice();
}

void processOrbit(int x, int y)
{
  if (viewId.isNull())
    return;
  OdTvGsViewPtr pView = viewId.openObject();
  // calculate click point in WCS
  OdGePoint3d pt = toEyeToWorld(x, y);
  // transfer point to the eye coordinate system
  OdGePoint3d ptView = pView->viewingMatrix() * pt;

  // calculate the angles for the rotation about appropriate axes
  double distX = ptView.x - orbitInfo.prevPt.x; // around vertical
  double distY = ptView.y - orbitInfo.prevPt.y; // around horizontal

  distX *= -OdaPI / orbitInfo.delta;
  distY *= OdaPI / orbitInfo.delta;

  // perform camera orbiting
  OdGeVector3d delta;
  OdGeVector3d target = pView->target().asVector();
  delta = orbitInfo.viewCenter.asVector() - target;
  delta.transformBy(pView->viewingMatrix());

  // the rotation should be performed around the 'pt'.
  // That's why at first we should move the camera with purpose make target equal to the 'pt.
  // Then we should perform the rotation and finally we should to move the camera in opposite direction
  pView->dolly(delta);
  pView->orbit(distY, distX);
  pView->dolly(-delta);

  // store previous click point
  orbitInfo.prevPt = ptView;

  updateDevice();
}

void highlight(const OdTvSelectionSetPtr& pSSet, bool bDoIt)
{
  if (viewId.isNull())
    return;
  OdTvGsViewPtr pView = viewId.openObject();
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

void processSelect(int x, int y)
{
  if (viewId.isNull())
    return;
  OdTvGsViewPtr pView = viewId.openObject();
  if (pView.isNull())
    return;

  if (!pSSet.isNull() && pSSet->numItems() > 0)
  {
    highlight(pSSet, false);
    pSSet.release();
  }

  OdTvDCPoint pt(x, y);
  OdTvSelectionOptions opt;
  opt.setLevel(OdTvSelectionOptions::kEntity);
  pSSet = pView->select(&pt, 1, opt, OdTvModelId());
  if (pSSet.isNull() || pSSet->numItems() == 0)
    return;

  highlight(pSSet, true);
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifndef _TOOLKIT_IN_DLL_
    ODRX_INIT_STATIC_MODULE_MAP();
#endif

    lMouseBtnIsPressed = false;
    // Activate ODA SDK
    ODASdkActivate();

    // Initialize factory
    odTvInitialize();

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ODVISUALIZEFIRSTAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ODVISUALIZEFIRSTAPP));
#if defined( _DLL )
    AfxWinInit( ::GetModuleHandle( NULL ), NULL, ::GetCommandLine(), 0 );
#endif

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

#ifdef OD_VISUALIZE_APP_ENABLE_STREAMING
    if( pStreamingDlg ) delete pStreamingDlg;
    pStreamingDlg = NULL;
    if( pSimpleRender ) delete pSimpleRender;
    pSimpleRender = NULL;
#endif

    // Uninitialize factory
    odTvUninitialize();

    // Activate ODA SDK
    ODASdkDeactivate();

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ODVISUALIZEFIRSTAPP));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ODVISUALIZEFIRSTAPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

#ifdef OD_VISUALIZE_APP_ENABLE_STREAMING
   pStreamingDlg = NULL;
   pSimpleRender = new CSimpleApplicationRender( hWnd );
#endif

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
      int wmId = LOWORD(wParam);
      // Parse the menu selections:
      switch (wmId)
      {
      case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        break;
      case IDM_EXIT:
#ifdef OD_VISUALIZE_APP_ENABLE_STREAMING
        if( pStreamingDlg )
        {
          pStreamingDlg->ShowWindow( SW_HIDE );
          delete pStreamingDlg;
          pStreamingDlg = NULL;
        }
#endif
        DestroyWindow(hWnd);
        break;
      case ID_FILE_OPEN_CMD:
        OpenFile(hWnd);
        break;
      case ID_FILE_GENERATESAMPLE:
        GenerateSample(hWnd);
        break;
      case ID_ZOOMTOEXTENTS:
        processZoomToExtents();
        break;
      case ID_NAVIGATION_PAN:
        navigationController = kPan;
        setItemChecked(hWnd);
        break;
      case ID_NAVIGATION_ORBIT:
        navigationController = kOrbit;
        setItemChecked(hWnd);
        break;
      case ID_SAMPLE_MULTIVIEW:
      case ID_SAMPLE_WALKINGANIMATION:
      {
        //Clear data
        ClearData( true );
        //Create sample context instance
        OdVisualizeAppSampleContext ctx( hWnd );
        //Execute sample
        bool res = OdVisualizeSampleManager::run( ctx.sampleFromId( wmId ), &ctx );
        if (!res)
        {
          MessageBox( NULL, (LPCWSTR)L"Sample execution failed", (LPCWSTR)L"Error", MB_ICONWARNING | MB_OK );
        }
      }
      break;
      case ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_1:
      case ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_2:
      case ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_3:
      {
        if (!dbId.isNull())
        {
          HMENU hmenu = GetMenu(hWnd);
          MENUITEMINFO menuItem = { 0 };
          menuItem.cbSize = sizeof(MENUITEMINFO);
          menuItem.fMask = MIIM_STATE;

          GetMenuItemInfo(hmenu, wmId, FALSE, &menuItem);
          if (menuItem.fState != MFS_CHECKED)
          {
            menuItem.fState = MFS_CHECKED;

            UnCheckHighlightMenuItems(hmenu, wmId);

            OdTvDatabasePtr pTvDatabase = dbId.openObject();
            OdTvGsDevicePtr pTvDevice = deviceId.openObject();
            if (!pTvDatabase.isNull() && !pTvDevice.isNull())
            {
              OdTvHighlightStyleId hsId;
              if (wmId == ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_1)
                hsId = pTvDatabase->findHighlightStyle(OD_T("HighLight_customization_1"));
              else if (wmId == ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_2)
                hsId = pTvDatabase->findHighlightStyle(OD_T("HighLight_customization_2"));
              else
                hsId = pTvDatabase->findHighlightStyle(OD_T("HighLight_customization_3"));
              if (hsId.isNull())
              {
                if (wmId == ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_1 || wmId == ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_3)
                {
                  if (wmId == ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_1)
                    hsId = pTvDatabase->createHighlightStyle(OD_T("HighLight_customization_1"), pTvDatabase->findHighlightStyle(OD_T("Default: faces on top")));
                  else
                    hsId = pTvDatabase->createHighlightStyle(OD_T("HighLight_customization_3"), pTvDatabase->findHighlightStyle(OD_T("Default: faces on top")));

                  OdTvHighlightStylePtr pHlStyle = hsId.openObject(OdTv::kForWrite);
                  if (!pHlStyle.isNull())
                  {
                    pHlStyle->setEdgesDrawMode(OdTvHighlightStyle::k3D, OdTvHighlightStyle::EdgesDrawMode::kCountour);
                    pHlStyle->setEdgesColor(OdTvHighlightStyle::k3D, wmId == ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_1 ? OdTvRGBColorDef(195, 212, 245) : OdTvRGBColorDef(233, 239, 252));
                    pHlStyle->setEdgesLineweight(OdTvHighlightStyle::k3D, 3);

                    pHlStyle->setFacesVisibility(OdTvHighlightStyle::k3D | OdTvHighlightStyle::k3DTop, true);
                    pHlStyle->setFacesColor( OdTvHighlightStyle::k3D, OdTvRGBColorDef(118, 146, 213));
                    pHlStyle->setFacesColor(OdTvHighlightStyle::k3DTop, OdTvRGBColorDef(118, 146, 213));
                    pHlStyle->setFacesTransparency(OdTvHighlightStyle::k3D, 50);
                    pHlStyle->setFacesTransparency(OdTvHighlightStyle::k3DTop, 200);

                    if (wmId == ID_SAMPLE_HIGHLIGHTCUSTOMIZATION_3)
                    {
                      pHlStyle->setEdgesVisibility(OdTvHighlightStyle::Entry::k3DTop, true);
                      pHlStyle->setEdgesColor(OdTvHighlightStyle::k3DTop, OdTvRGBColorDef(195, 212, 245));
                      pHlStyle->setEdgesLineweight(OdTvHighlightStyle::k3DTop, 0);
                      pHlStyle->setEdgesDrawMode(OdTvHighlightStyle::Entry::k3DTop, OdTvHighlightStyle::EdgesDrawMode::kIsolines);
                      pHlStyle->setEdgesTransparency(OdTvHighlightStyle::k3DTop, 0);
                    }
                  }
                }
                else
                {
                  hsId = pTvDatabase->createHighlightStyle(OD_T("HighLight_customization_2"), pTvDatabase->findHighlightStyle(OD_T("Default: edges on top")));

                  OdTvHighlightStylePtr pHlStyle = hsId.openObject(OdTv::kForWrite);
                  if (!pHlStyle.isNull())
                  {
                    pHlStyle->setEdgesColor(OdTvHighlightStyle::Entry::k3DTop, OdTvRGBColorDef(0xFF, 0x98, 0x00));
                    pHlStyle->setFacesColor(OdTvHighlightStyle::Entry::k3D, OdTvRGBColorDef(0xFF, 0x98, 0x00));
                    pHlStyle->setFacesTransparency(OdTvHighlightStyle::Entry::k3D, 200);

                     pHlStyle->setFacesVisibility(OdTvHighlightStyle::Entry::k3DTop, true);
                     pHlStyle->setFacesTransparency(OdTvHighlightStyle::Entry::k3DTop, 245);
                     pHlStyle->setFacesColor(OdTvHighlightStyle::Entry::k3DTop, OdTvRGBColorDef(0xFF, 0x98, 0x00));

                    //May be need in CLOUD
                    //pHlStyle->setEdgesVisibility(OdTvHighlightStyle::Entry::k3D, true);
                    //pHlStyle->setEdgesColor(OdTvHighlightStyle::Entry::k3D, OdTvRGBColorDef(0xFF, 0x98, 0x00));
                    //pHlStyle->setEdgesDrawMode(OdTvHighlightStyle::Entry::k3D, OdTvHighlightStyle::EdgesDrawMode::kIsolines);
                    //pHlStyle->setEdgesTransparency(OdTvHighlightStyle::Entry::k3D, 255);
                    //pHlStyle->setEdgesLineweight(OdTvHighlightStyle::Entry::k3D, 0);

                    //pHlStyle->setEdgesVisibility(OdTvHighlightStyle::Entry::k2D, true);
                    //pHlStyle->setEdgesColor(OdTvHighlightStyle::Entry::k2D, OdTvRGBColorDef(0xFF, 0x98, 0x00));
                    //pHlStyle->setEdgesTransparency(OdTvHighlightStyle::Entry::k2D, 255);
                    //pHlStyle->setEdgesDrawMode(OdTvHighlightStyle::Entry::k2D, OdTvHighlightStyle::EdgesDrawMode::kIsolines);
                    //pHlStyle->setEdgesLineweight(OdTvHighlightStyle::Entry::k2D, 0);

                    pHlStyle->setFacesColor(OdTvHighlightStyle::Entry::k2D, OdTvRGBColorDef(0xFF, 0x98, 0x00));
                    pHlStyle->setEdgesColor(OdTvHighlightStyle::Entry::k2DTop, OdTvRGBColorDef(0xFF, 0x98, 0x00));
                  }
                }
              }

              pTvDevice->setHighlightStyle(hsId);
              pTvDevice->invalidate();
              pTvDevice->update();
            }
          }
          else
          {
            menuItem.fState = MF_UNCHECKED;

            OdTvDatabasePtr pTvDatabase = dbId.openObject();
            OdTvGsDevicePtr pTvDevice = deviceId.openObject();
            if (!pTvDatabase.isNull() && !pTvDevice.isNull())
            {
              OdTvHighlightStyleId hsId = pTvDatabase->findHighlightStyle(OD_T("Default"));
              if (!hsId.isNull())
              {
                pTvDevice->setHighlightStyle(hsId);
                pTvDevice->invalidate();
                pTvDevice->update();
              }
            }
          }
          SetMenuItemInfo(hmenu, wmId, FALSE, &menuItem);
        }
        break;
      }
      case ID_CHANGEACTIVEVIEW:
      {
        if (!deviceId.isNull())
        {
          //Changes viewId to the next of activeView
          OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForRead);
          activeView++;
          if (activeView >= pDevice->numViews()) activeView = 0;
          viewId = pDevice->viewAt(activeView);
        }
      }
      break;
#ifdef OD_VISUALIZE_APP_ENABLE_STREAMING
      case ID_DO_STREAM:
      {
        if( pStreamingDlg )
        {
          pStreamingDlg->ShowWindow( SW_HIDE );
          delete pStreamingDlg;
        }
        pStreamingDlg = new CStreamingDialog( pSimpleRender );
        pStreamingDlg->Create( CStreamingDialog::IDD, NULL );
        pStreamingDlg->ShowWindow( SW_NORMAL );
      }
      break;
#endif
      case ID_REGENALL_CMD:
      {
        if( !deviceId.isNull() )
        {
          OdTvGsDevicePtr pDevice = deviceId.openObject( OdTv::kForRead );
          pDevice->regen( OdTvGsDevice::kRegenAll );
        }
      }
      break;
      case ID_UPDATE_CMD:
      {
        if( !deviceId.isNull() )
        {
          OdTvGsDevicePtr pDevice = deviceId.openObject( OdTv::kForRead );
          pDevice->update();
        }
      }
      break;
      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
      }
    }
    break;
    case WM_PAINT:
    {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWnd, &ps);
      // TODO: Add any drawing code that uses hdc here...
      EndPaint(hWnd, &ps);

      // update device after paint event
      updateDevice();
    }
    break;
    case WM_SIZE:
    {
      // Update and resize device after resize event
      OdTvGsDevicePtr pDevice = deviceId.openObject();
      if (!pDevice.isNull())
      {
        RECT clRect;
        GetClientRect(hWnd, &clRect);
        OdTvDCRect rect((long)clRect.left, (long)clRect.right, (long)clRect.bottom, (long)clRect.top);
        pDevice->onSize(rect);
        pDevice->update();
      }
    }
    break;
    case WM_DESTROY:
      // Remove data before close
#ifdef OD_VISUALIZE_APP_ENABLE_STREAMING
      if( pStreamingDlg ) delete pStreamingDlg;
      pStreamingDlg = NULL;
      if( pSimpleRender ) delete pSimpleRender;
      pSimpleRender = NULL;
#endif
      ClearData( true );
      PostQuitMessage(0);
      break;

    case WM_MOUSEWHEEL:
    {
      short zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
      processZoom(hWnd, zDelta);
      break;
    }
    case WM_LBUTTONDOWN:
    {
      if (!dbId.isNull())
      {
        lMouseBtnIsPressed = true;
        SetCapture(hWnd);
      }

      if (navigationController == kNone)
        break;

      POINT p;
      if (GetCursorPos(&p) && !viewId.isNull())
      {
        if(navigationController == kPan)
        {
          panInfo.curPos = viewId.openObject()->position();
          panInfo.prevPos = toEyeToWorld(p.x, p.y) - panInfo.curPos.asVector();
        }
        else if (navigationController == kOrbit)
        {
          OdTvGsViewPtr pView = viewId.openObject();
          // calculate click point in WCS
          OdGePoint3d pt = toEyeToWorld(p.x, p.y);
          // transfer point to the eye coordinate system
          orbitInfo.prevPt = pView->viewingMatrix() * pt;
          // calculate mouse move to rotation angle conversion coefficient in base of viewport dc size
          OdGePoint3d pt1;
          OdGePoint2d pt2;
          pView->viewDcCorners((OdGePoint2d&)pt1, pt2);
          pt2.x -= pt1.x;
          pt2.y -= pt1.y;
          double r = odmin(pt2.x, pt2.y);
          orbitInfo.delta = r;

          OdGeBoundBlock3d extents;
          pView->viewExtents(extents);
          orbitInfo.viewCenter = extents.center();
          orbitInfo.viewCenter.transformBy(pView->eyeToWorldMatrix());
        }
      }
      break;
    }
    case WM_LBUTTONUP:
    {
      if (lMouseBtnIsPressed)
      { POINT p;
        if (navigationController == kNone && GetCursorPos(&p))
        {
          ScreenToClient(hWnd, &p);
          processSelect(p.x, p.y);
        }
        ::ReleaseCapture();
        lMouseBtnIsPressed = false;
      }
      break;
    }
    case WM_MOUSEMOVE:
    {
      if (navigationController == kNone || !lMouseBtnIsPressed)
        break;

      POINT p;
      if (GetCursorPos(&p))
      {
        if(navigationController == kPan)
          processPan(p.x, p.y);
        else if(navigationController == kOrbit)
          processOrbit(p.x, p.y);
      }
      break;
    }
    case WM_KEYDOWN:
    {
      if (wParam == VK_ESCAPE)
      {
        if (!pSSet.isNull() && pSSet->numItems() > 0)
        {
          highlight(pSSet, false);
          pSSet.release();
        }
        navigationController = kNone;

        HMENU hmenu = GetMenu(hWnd);
        MENUITEMINFO menuItem = { 0 };
        menuItem.cbSize = sizeof(MENUITEMINFO);
        menuItem.fMask = MIIM_STATE;

        GetMenuItemInfo(hmenu, ID_NAVIGATION_PAN, FALSE, &menuItem);
        menuItem.fState = MFS_UNCHECKED;
        SetMenuItemInfo(hmenu, ID_NAVIGATION_PAN, FALSE, &menuItem);

        GetMenuItemInfo(hmenu, ID_NAVIGATION_ORBIT, FALSE, &menuItem);
        menuItem.fState = MFS_UNCHECKED;
        SetMenuItemInfo(hmenu, ID_NAVIGATION_ORBIT, FALSE, &menuItem);
      }
      break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
