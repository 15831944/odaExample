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

#include "TvAndActivator.h"

#include <stdio.h>
#include "OdaCommon.h"
#include "RxInit.h"
#include "StaticRxObject.h"
#include "RxDynamicModule.h"
#include "diagnostics.h"
#include "OdTimeStamp.h"
#include "OdCharMapper.h"
#include "TvModuleNames.h"
#include "PrcModuleNames.h"
#include "TvCoreModulesNames.h"

#include "RcsFileServices/RxRcsFileServices.h"

#include "TvFactory.h"

#ifdef IFC_ENABLED
#include "Common/ModuleNames.h"
#endif

#include "TvVisualizeFiler.h"

#ifndef _TOOLKIT_IN_DLL_
// Visualize API
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvDbIOModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvDbCoreModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdDbCoreModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TvISMModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TvSCENEOEModule);;
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvTfModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvCoreDatabaseModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvCoreDatabaseIOModule );

//Dwg2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeDwgFilerModule);
//Dgn2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeDgnFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDgnModule);
//Rcs2Visualze
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeRcsFilerModule);
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
#ifdef PDF_EXPORT_ENABLED
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualize2PdfFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdVisualize2PrcExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPdfExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcBaseExportModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdPrcPublish3dCmdsModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(PdfPublishModule);
#endif

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
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(DbCryptModule);

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxThreadPoolService);

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvDbPartialViewingModuleImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxCommonDataAccessModule);
//Vsf2Visualize
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvVisualizeVsfFilerModule );

#ifdef IFC_ENABLED
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeIfcFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x3Module);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4Module);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcFacetModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcGeomModuleImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcBrepBuilderModule);
#endif

ODRX_BEGIN_STATIC_MODULE_MAP()
ODRX_DEFINE_STATIC_APPMODULE(OdTvModuleName,                         OdTvModule)
ODRX_DEFINE_STATIC_APPMODULE(L"TV_SCENEOE", 						TvSCENEOEModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvDbIOAppName,                          OdTvDbIOModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvDbCoreModuleName, 					OdTvDbCoreModule )
ODRX_DEFINE_STATIC_APPMODULE(OdDbCoreModuleName, 					OdDbCoreModule )
ODRX_DEFINE_STATIC_APPMODULE(L"TV_ISM", 							TvISMModule)
ODRX_DEFINE_STATIC_APPLICATION(OdModelerGeometryModuleName,          ModelerModule)
ODRX_DEFINE_STATIC_APPMODULE( OdTvTfModuleName,                           OdTvTfModule)
ODRX_DEFINE_STATIC_APPMODULE( OdTvCoreDatabaseModuleName, 			 OdTvCoreDatabaseModule )
ODRX_DEFINE_STATIC_APPMODULE( OdTvCoreDatabaseIOModuleName, 		 OdTvCoreDatabaseIOModule )

ODRX_DEFINE_STATIC_APPMODULE(OdTvDgn2VisualizeModuleName,            OdTvVisualizeDgnFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdDgnDbModuleName,                      OdDgnModule)

ODRX_DEFINE_STATIC_APPMODULE(OdTvDwg2VisualizeModuleName,            OdTvVisualizeDwgFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvVisualizeDeviceModuleName,          VisualizeDeviceModule)
ODRX_DEFINE_STATIC_APPLICATION(OdRecomputeDimBlockModuleName,        OdRecomputeDimBlockModule)

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

ODRX_DEFINE_STATIC_APPMODULE(OdTvObj2VisualizeModuleName,            OdTvVisualizeObjFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdObjToolkitModuleName,                 OdObjToolkitModuleImpl)
ODRX_DEFINE_STATIC_APPMODULE(OdTvStl2VisualizeModuleName,            OdTvVisualizeStlFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdStlImportModuleName,                  OdStlImportModuleImpl)

ODRX_DEFINE_STATIC_APPMODULE(OdTvRcs2VisualizeModuleName,            OdTvVisualizeRcsFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdExFieldEvaluatorModuleName,           ExFieldEvaluatorModule)
ODRX_DEFINE_STATIC_APPMODULE(DbPointCloudObjModuleName,              DbPointCloudObjModule)
ODRX_DEFINE_STATIC_APPMODULE(OdExPointCloudHostModuleName,           ExPointCloudHostModule)
ODRX_DEFINE_STATIC_APPMODULE(RX_RCS_FILE_SERVICES,                   RcsFileServicesModule)
ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName,            OdRasterProcessingServicesImpl)
ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME,             ExRasterModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTrGL2ModuleName,                      OdTrGL2RenderModule)
ODRX_DEFINE_STATIC_APPMODULE(OdWinGLES2ModuleName,                   GLES2Module)
ODRX_DEFINE_STATIC_APPMODULE(DbCryptModuleName,                      DbCryptModule)
ODRX_DEFINE_STATIC_APPLICATION(OdThreadPoolModuleName,               OdRxThreadPoolService)
ODRX_DEFINE_STATIC_APPMODULE(OdTvPartialViewingModuleName,           OdTvDbPartialViewingModuleImpl)
ODRX_DEFINE_STATIC_APPMODULE(RxCommonDataAccessModuleName,           OdRxCommonDataAccessModule)


#ifdef IFC_ENABLED
ODRX_DEFINE_STATIC_APPMODULE(OdTvIfc2VisualizeModuleName,            OdTvVisualizeIfcFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName,                    OdIfcCoreModule)
ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName,                       OdSDAIModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x3ModuleName,                     OdIfc2x3Module)
ODRX_DEFINE_STATIC_APPMODULE(OdIfc4ModuleName,                       OdIfc4Module)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcFacetModelerModuleName,            OdIfcFacetModelerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcGeomModuleName,                    OdIfcGeomModuleImpl)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcBrepBuilderModuleName,             OdIfcBrepBuilderModule)
#endif

//Vsf2Visualize
ODRX_DEFINE_STATIC_APPMODULE( OdTvVsf2VisualizeModuleName, OdTvVisualizeVsfFilerModule )
ODRX_END_STATIC_MODULE_MAP()

#endif

TvAndActivator::TvAndActivator() {
    ODRX_INIT_STATIC_MODULE_MAP();
}

TvAndActivator::~TvAndActivator() {
}

void TvAndActivator::activate() {
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

void TvAndActivator::deactivate() {
    odTvUninitialize();
    odCleanUpStaticData();
}
