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

#include "TviActivator.hpp"
#include "TvCoreModulesNames.h"

#ifdef POINTCLOUD_ENABLED
#include "RcsFileServices/RxRcsFileServices.h"
#endif

#ifdef PRC_ENABLED
#include "PrcModuleNames.h"
#endif

#ifdef IFC_ENABLED
#include "Common/ModuleNames.h"
#endif

#ifndef _TOOLKIT_IN_DLL_
// Visualize API
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvDbIOModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvDbCoreModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdDbCoreModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TvISMModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TvSCENEOEModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvTfModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvCoreDatabaseModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvCoreDatabaseIOModule );

//Visualize device
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(VisualizeDeviceModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRecomputeDimBlockModule);

//Dwg2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeDwgFilerModule);

#ifdef DGN_ENABLED
//Dgn2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeDgnFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDgnModule);
#endif

#ifdef POINTCLOUD_ENABLED
//Rcs2Visualze
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeRcsFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExFieldEvaluatorModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(DbPointCloudObjModule);
//ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExPointCloudHostModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(RcsFileServicesModule);
#endif

#ifdef PRC_ENABLED
//Prc2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizePrcFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcModule);

#ifdef PDF_EXPORT_ENABLED
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualize2PdfFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdVisualize2PrcExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPdfExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcBaseExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcPublish3dCmdsModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(PdfPublishModule);
#endif

#endif

#ifdef COMPONENTS_IMPORTS_ENABLED
//Obj2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeObjFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdObjToolkitModuleImpl);
//Stl2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeStlFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdStlImportModuleImpl);
#endif
//Raster images
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRasterProcessingServicesImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);
//Device
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTrGL2RenderModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(GLES2Module);
//ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(WinOpenGLModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(DbCryptModule);
#ifdef METAL_ENABLED
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTrMetalRenderModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(MetalModule);
#endif

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxThreadPoolService);

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvDbPartialViewingModuleImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxCommonDataAccessModule);

#ifdef IFC_ENABLED
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeIfcFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x3Module);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4Module);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4x3_RC4Module);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x_FinalModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x2_FinalModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcFacetModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcGeomModuleImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcBrepBuilderModule);
#endif

ODRX_BEGIN_STATIC_MODULE_MAP()
ODRX_DEFINE_STATIC_APPMODULE(OdTvModuleName,                         OdTvModule)
ODRX_DEFINE_STATIC_APPMODULE(L"TV_SCENEOE",                          TvSCENEOEModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvDbIOAppName,                        OdTvDbIOModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvDbCoreModuleName,                   OdTvDbCoreModule )
ODRX_DEFINE_STATIC_APPMODULE(OdDbCoreModuleName,                     OdDbCoreModule )
ODRX_DEFINE_STATIC_APPMODULE(L"TV_ISM",                              TvISMModule)
ODRX_DEFINE_STATIC_APPLICATION(OdModelerGeometryModuleName,          ModelerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvTfModuleName,                       OdTvTfModule)
ODRX_DEFINE_STATIC_APPMODULE( OdTvCoreDatabaseModuleName, OdTvCoreDatabaseModule )
ODRX_DEFINE_STATIC_APPMODULE( OdTvCoreDatabaseIOModuleName, OdTvCoreDatabaseIOModule )

#ifdef DGN_ENABLED
ODRX_DEFINE_STATIC_APPMODULE(OdTvDgn2VisualizeModuleName,            OdTvVisualizeDgnFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdDgnDbModuleName,                      OdDgnModule)
#endif

ODRX_DEFINE_STATIC_APPMODULE(OdTvDwg2VisualizeModuleName,            OdTvVisualizeDwgFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvVisualizeDeviceModuleName,          VisualizeDeviceModule)
ODRX_DEFINE_STATIC_APPLICATION(OdRecomputeDimBlockModuleName,        OdRecomputeDimBlockModule)

#ifdef PRC_ENABLED
ODRX_DEFINE_STATIC_APPMODULE(OdTvPrc2VisualizeModuleName,            OdTvVisualizePrcFilerModule)
ODRX_DEFINE_STATIC_APPLICATION(OdPrcModuleName,                      OdPrcModule)

#ifdef PDF_EXPORT_ENABLED
ODRX_DEFINE_STATIC_APPMODULE(OdTvVisualize2PdfModuleName,          OdTvVisualize2PdfFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTv2PrcExportModuleName,             OdVisualize2PrcExportModule)
ODRX_DEFINE_STATIC_APPMODULE(OdPdfExportModuleName,                OdPdfExportModule)
ODRX_DEFINE_STATIC_APPLICATION(OdPrcBaseExportModuleName,          OdPrcBaseExportModule)
ODRX_DEFINE_STATIC_APPLICATION(OdPrcPublish3dCmdsModuleName,       OdPrcPublish3dCmdsModule)
ODRX_DEFINE_STATIC_APPMODULE(OdPdfPublishModuleName,               PdfPublishModule)
#endif

#endif

#ifdef COMPONENTS_IMPORTS_ENABLED
ODRX_DEFINE_STATIC_APPMODULE(OdTvObj2VisualizeModuleName,            OdTvVisualizeObjFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdObjToolkitModuleName,                 OdObjToolkitModuleImpl)
ODRX_DEFINE_STATIC_APPMODULE(OdTvStl2VisualizeModuleName,            OdTvVisualizeStlFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdStlImportModuleName,                  OdStlImportModuleImpl)
#endif

#ifdef POINTCLOUD_ENABLED
ODRX_DEFINE_STATIC_APPMODULE(OdTvRcs2VisualizeModuleName,            OdTvVisualizeRcsFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdExFieldEvaluatorModuleName,           ExFieldEvaluatorModule)
ODRX_DEFINE_STATIC_APPMODULE(DbPointCloudObjModuleName,              DbPointCloudObjModule)
//ODRX_DEFINE_STATIC_APPMODULE(OdExPointCloudHostModuleName,           ExPointCloudHostModule)
ODRX_DEFINE_STATIC_APPMODULE(RX_RCS_FILE_SERVICES,                   RcsFileServicesModule)
ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName,            OdRasterProcessingServicesImpl)
ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME,             ExRasterModule)
#endif

ODRX_DEFINE_STATIC_APPMODULE(OdTrGL2ModuleName,                      OdTrGL2RenderModule)
ODRX_DEFINE_STATIC_APPMODULE(OdWinGLES2ModuleName,                   GLES2Module)
//ODRX_DEFINE_STATIC_APPMODULE(OdWinOpenGLModuleName,                  WinOpenGLModule)
ODRX_DEFINE_STATIC_APPMODULE(DbCryptModuleName,                      DbCryptModule)
#ifdef METAL_ENABLED
ODRX_DEFINE_STATIC_APPLICATION(OdTrMetalModuleName,                  OdTrMetalRenderModule)
ODRX_DEFINE_STATIC_APPLICATION(OdWinMetalModuleName,                 MetalModule)
#endif
ODRX_DEFINE_STATIC_APPLICATION(OdThreadPoolModuleName,               OdRxThreadPoolService)
ODRX_DEFINE_STATIC_APPMODULE(OdTvPartialViewingModuleName,           OdTvDbPartialViewingModuleImpl)
ODRX_DEFINE_STATIC_APPMODULE(RxCommonDataAccessModuleName,           OdRxCommonDataAccessModule)

#ifdef IFC_ENABLED
ODRX_DEFINE_STATIC_APPMODULE(OdTvIfc2VisualizeModuleName,            OdTvVisualizeIfcFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName,                    OdIfcCoreModule)
ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName,                       OdSDAIModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x3ModuleName,                     OdIfc2x3Module)
ODRX_DEFINE_STATIC_APPMODULE(OdIfc4ModuleName,                       OdIfc4Module)
ODRX_DEFINE_STATIC_APPMODULE(OdIfc4x3RC4ModuleName,                  OdIfc4x3_RC4Module)
ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x_FinalModuleName,                OdIfc2x_FinalModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x2_FinalModuleName,               OdIfc2x2_FinalModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcFacetModelerModuleName,            OdIfcFacetModelerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcGeomModuleName,                    OdIfcGeomModuleImpl)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcBrepBuilderModuleName,             OdIfcBrepBuilderModule)
#endif

ODRX_END_STATIC_MODULE_MAP()

#endif

TviActivator::TviActivator() {
    ODRX_INIT_STATIC_MODULE_MAP();
}

TviActivator::~TviActivator() {
}

void TviActivator::activate() {
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

void TviActivator::deactivate() {
    odTvUninitialize();
    odCleanUpStaticData();
}
