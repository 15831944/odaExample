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
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QStandardPaths>
#include <QDir>

// ODA SDK
#include "OdaCommon.h"
#include "RxInit.h"
#include "StaticRxObject.h"
#include "RxDynamicModule.h"
#include "diagnostics.h"
#include "OdTimeStamp.h"
#include "OdCharMapper.h"
#include "RxVariantValue.h"

#include "TvModuleNames.h"
#include "PrcModuleNames.h"

#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a

// Visualize SDK
#include "TvFactory.h"

#include "tvicontroller.h"
#include "TviImportParamsController.h"

#ifndef _TOOLKIT_IN_DLL_
// Visualize API
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDbIOModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ISMModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(SCENEOEModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTfModule);

#if defined(DWFDB_ENABLED)
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(DwfUnderlayModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(DwfDbModule);
#endif

// Visualize models generator
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeSampleModelsFilerModule);
//Dwg2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeDwgFilerModule);
//Dgn2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDgnModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeDgnFilerModule);
//Rcs2Visualze
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeRcsFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(Dwf7ImportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExCustObjsModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExFieldEvaluatorModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(DbPointCloudObjModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExPointCloudHostModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(RcsFileServicesModule);
//Visualize device
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(VisualizeDeviceModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRecomputeDimBlockModule);
//Prc2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizePrcFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcModule);
//Obj2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeObjFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdObjToolkitModuleImpl);
//Stl2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeStlFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdStlImportModuleImpl);
//Raster images
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRasterProcessingServicesImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);
//Device
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTrGL2RenderModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(GLES2Module);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(WinOpenGLModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(DbCryptModule);

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxThreadPoolService);

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDbPartialViewingModuleImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxCommonDataAccessModule);
//Vsf2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvVisualizeVsfFilerModule );

ODRX_BEGIN_STATIC_MODULE_MAP()
#if defined(DWFDB_ENABLED)
  ODRX_DEFINE_STATIC_APPMODULE(OdDwfUnderlayModuleName,           DwfUnderlayModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdDwfDbModuleName,                 DwfDbModule)
#endif
ODRX_DEFINE_STATIC_APPMODULE(OdTvModuleName,                         OdTvModule)
ODRX_DEFINE_STATIC_APPMODULE(L"TV_SCENEOE",                             SCENEOEModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvDbIOAppName,                          OdDbIOModule)
ODRX_DEFINE_STATIC_APPMODULE(L"TV_ISM",                                 ISMModule)
ODRX_DEFINE_STATIC_APPLICATION(OdModelerGeometryModuleName,          ModelerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvTfModuleName,                           OdTfModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvModelsGeneratorModuleName,          OdTvVisualizeSampleModelsFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvDgn2VisualizeModuleName,            OdTvVisualizeDgnFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdDgnDbModuleName,                      OdDgnModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvDwg2VisualizeModuleName,            OdTvVisualizeDwgFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvVisualizeDeviceModuleName,          VisualizeDeviceModule)
ODRX_DEFINE_STATIC_APPLICATION(OdRecomputeDimBlockModuleName,        OdRecomputeDimBlockModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvPrc2VisualizeModuleName,            OdTvVisualizePrcFilerModule)
ODRX_DEFINE_STATIC_APPLICATION(OdPrcModuleName,                      OdPrcModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvObj2VisualizeModuleName,            OdTvVisualizeObjFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdObjToolkitModuleName,                 OdObjToolkitModuleImpl)
ODRX_DEFINE_STATIC_APPMODULE(OdTvRcs2VisualizeModuleName,            OdTvVisualizeRcsFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdDwf7ImportModuleName,                 Dwf7ImportModule)
ODRX_DEFINE_STATIC_APPMODULE(OdExCustObjsModuleName,                 ExCustObjsModule)
ODRX_DEFINE_STATIC_APPMODULE(OdExFieldEvaluatorModuleName,           ExFieldEvaluatorModule)
ODRX_DEFINE_STATIC_APPMODULE(DbPointCloudObjModuleName,              DbPointCloudObjModule)
ODRX_DEFINE_STATIC_APPMODULE(OdExPointCloudHostModuleName,           ExPointCloudHostModule)
ODRX_DEFINE_STATIC_APPMODULE(RX_RCS_FILE_SERVICES,                   RcsFileServicesModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvStl2VisualizeModuleName,            OdTvVisualizeStlFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdStlImportModuleName,                  OdStlImportModuleImpl)
ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName,            OdRasterProcessingServicesImpl)
ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME,             ExRasterModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTrGL2ModuleName,                      OdTrGL2RenderModule)
ODRX_DEFINE_STATIC_APPMODULE(OdWinGLES2ModuleName,                   GLES2Module)
ODRX_DEFINE_STATIC_APPMODULE(OdWinOpenGLModuleName,                  WinOpenGLModule)
ODRX_DEFINE_STATIC_APPMODULE(DbCryptModuleName,                      DbCryptModule)
ODRX_DEFINE_STATIC_APPLICATION(OdThreadPoolModuleName,               OdRxThreadPoolService)
ODRX_DEFINE_STATIC_APPMODULE(OdDbPartialViewingModuleName,           OdDbPartialViewingModuleImpl)
ODRX_DEFINE_STATIC_APPMODULE(RxCommonDataAccessModuleName,           OdRxCommonDataAccessModule)
//Vsf2Visualize
ODRX_DEFINE_STATIC_APPMODULE( OdTvVsf2VisualizeModuleName,           OdTvVisualizeVsfFilerModule )
ODRX_END_STATIC_MODULE_MAP()

#endif

#define ORGANIZATION_NAME   "Open Design Alliance"
#define ORGANIZATION_DOMAIN "www.opendesign.com"
#define APPLICATION_NAME    "IOS Visualize Viewer"


void activate()
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
    odActivate(OdAnsiString(ActInfo[0]), OdAnsiString(ActInfo[1]));
    odTvInitialize();
}

void deactivate()
{
    odTvUninitialize();
    odCleanUpStaticData();
}

#if defined(_MSC_VER)
inline void attuneLocale()
{
    setlocale(LC_NUMERIC, "C"); // saving doubles to dxf
    setlocale(LC_TIME, ""); // correct stvtime formatting
}
#else
#define attuneLocale()
#endif


int main(int argc, char *argv[])
{
    attuneLocale();

    ODRX_INIT_STATIC_MODULE_MAP();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    app.setOrganizationName(ORGANIZATION_NAME);
    app.setOrganizationDomain(ORGANIZATION_DOMAIN);
    app.setApplicationName(APPLICATION_NAME);

    activate();

    qmlRegisterType<TviController>("TvDeviceUnderQML", 1, 0, "TviController");


    QQmlApplicationEngine engine;

    // Add application data path
    QString mDataPath = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).value(0);
    QUrl appDataPath(QString("file://%1").arg(mDataPath));
    QUrl dirDataPath(QString("%1").arg(mDataPath));
    qDebug() << "Data Path: " << mDataPath;
    QDir myDir(mDataPath);
    if (!myDir.exists()) {
        bool ok = myDir.mkpath(mDataPath);
        if(!ok)
            qDebug() << "Couldn't create dir. " << mDataPath;
        else
        {
            qDebug() << "created directory path" << mDataPath;
            engine.rootContext()->setContextProperty("appDataPath", appDataPath);
            engine.rootContext()->setContextProperty("dirDataPath", dirDataPath);
        }
    }
    else
    {
        engine.rootContext()->setContextProperty("appDataPath", appDataPath);
        engine.rootContext()->setContextProperty("dirDataPath", dirDataPath);
    }

    TviImportParamsController *importController = TviImportParamsController::getInstance();
    engine.rootContext()->setContextProperty("importController", importController);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    // show QQuickWindow object
    QObject* root = engine.rootObjects().at(0);
    QWindow *pWnd = static_cast<QWindow*>(root);
    if(pWnd)
        pWnd->show();
    importController->setWindowSize( pWnd->size() * pWnd->devicePixelRatio() );

    QObject* pPage = root->findChild<QObject*>("renderPage");
    QObject* pTviController = root->findChild<QObject*>("tviController");
    if(pPage && pTviController) {
        QObject::connect(pPage, SIGNAL( panelButtonPressed(const QString&) ), pTviController, SLOT(onPanelButtonPressed(const QString&)));
        QObject::connect(pPage, SIGNAL( unblockRenderSg() ), pTviController, SLOT(unblockRenderSl()));

        QObject* pPinchArea = root->findChild<QObject*>("pinchArea");
        if(pPinchArea) {
            QObject::connect( pPinchArea, SIGNAL(onZoomSg(double, int, int)), pTviController, SLOT(onZoomSl(double, int, int)) );
            QObject::connect( pPinchArea, SIGNAL(onTouchStartSg(int, int)), pTviController, SLOT(onTouchStartSl(int, int)) );
            QObject::connect( pPinchArea, SIGNAL(onTouchUpdatedSg(int, int)), pTviController, SLOT(onTouchUpdatedSl(int, int)) );
            QObject::connect( pPinchArea, SIGNAL(onTouchReleasedSg(int, int)), pTviController, SLOT(onTouchReleasedSl(int, int)) );
        }

        engine.rootContext()->setContextProperty("tviController", pTviController);
    }

    int execCode = app.exec();

    delete importController;

    deactivate();

    return execCode;
}
