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

#ifndef _EXAMPLE_SCENARIOS_ENGINE_H_
#define _EXAMPLE_SCENARIOS_ENGINE_H_


#include "IfcCore.h"
#include "ExSystemServices.h"
#include "ExIfcHostAppServices.h"

#include "scenario/ScenarioEngineIncludes.h"
#include "scenario/ScenarioEngineDeclarations.h"
#include "scenario/ScenarioEngineUtils.h"
#include "scenario/ScenarioEngineDataHandler.h"
#include "scenario/ScenarioEngineInitializer.h"

#include "scenario/EngineScenariosForPerfs.h"

#include "ExIfcModelFiller.h"

#include "Scenarios/ExampleAppServices.h"
#include "Scenarios/ExampleScenariosImpl.h"

// #define WIN_GDI_MODULE_ENABLE - GDI module in static mode
// #define WIN_OPENGL_MODULE_ENABLE - OpenGL module in static mode

// #define IFC_GEOM_MODULE_ENABLE - enable geom module in static mode
// #define IFC_BREP_BUILDER_MODULE_ENABLE - enable brepbuilder module in static mode
// #define IFC_FACET_MODELER_MODULE_ENABLE - enable IfcFacetModeler module in static mode
// #define IFC_BREP_MODELER_PE_MODULE_ENABLE - enable IfcBRep<odelerPE module in static mode
// #define IFC_BREP_MODELER_MODULE_ENABLE - enable IfcBRep<odeler module in static mode

#ifndef _TOOLKIT_IN_DLL_
  
 using namespace OdIfc;
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x3Module);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4Module);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4x3_RC4Module);

#ifdef WIN_GDI_MODULE_ENABLE
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(WinGDIModule);           
#endif

#ifdef WIN_OPENGL_MODULE_ENABLE
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(WinOpenGLModule);        
#endif

#ifdef BIMAP_MODULE_ENABLE
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(BitmapModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRasterProcessingServicesImpl);
#endif

#ifdef IFC_GEOM_MODULE_ENABLE
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcGeomModuleImpl);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcBrepBuilderModule);
#endif
#ifdef IFC_FACET_MODELER_MODULE_ENABLE
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcFacetModelerModule);
# ifdef IFC_BREP_MODELER_PE_MODULE_ENABLE
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcBrepModelerPEModule);
# endif
#endif
#ifdef IFC_BREP_MODELER_MODULE_ENABLE
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcBrepModelerModule);
#endif
#ifdef CDA_MODULES_ENABLE
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxCommonDataAccessModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxPropertiesModule);
#endif

  ODRX_BEGIN_STATIC_MODULE_MAP()
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x3ModuleName, OdIfc2x3Module)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc4ModuleName, OdIfc4Module)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc4x3RC4ModuleName, OdIfc4x3_RC4Module)

#ifdef WIN_GDI_MODULE_ENABLE
  #if defined(_WIN32)
      ODRX_DEFINE_STATIC_APPMODULE(OdWinGDIModuleName, WinGDIModule)
  #endif      
#endif

#ifdef WIN_OPENGL_MODULE_ENABLE
  #if defined(_WIN32)
      ODRX_DEFINE_STATIC_APPMODULE(OdWinOpenGLModuleName, WinOpenGLModule)
  #endif
#endif

#ifdef IFC_GEOM_MODULE_ENABLE
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcGeomModuleName, OdIfcGeomModuleImpl)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcBrepBuilderModuleName, OdIfcBrepBuilderModule)
#endif
#ifdef IFC_FACET_MODELER_MODULE_ENABLE
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcFacetModelerModuleName, OdIfcFacetModelerModule)
# ifdef IFC_BREP_MODELER_PE_MODULE_ENABLE
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcBrepModelerPEModuleName, OdIfcBrepModelerPEModule)
# endif
#endif
#ifdef IFC_BREP_MODELER_MODULE_ENABLE
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcBrepModelerModuleName, OdIfcBrepModelerModule)
#endif
#ifdef BIMAP_MODULE_ENABLE
    ODRX_DEFINE_STATIC_APPMODULE(OdWinBitmapModuleName, BitmapModule)
    ODRX_DEFINE_STATIC_APPLICATION(RX_RASTER_SERVICES_APPNAME, ExRasterModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName, OdRasterProcessingServicesImpl)
#endif
#ifdef CDA_MODULES_ENABLE
    ODRX_DEFINE_STATIC_APPMODULE(RxCommonDataAccessModuleName, OdRxCommonDataAccessModule)
    ODRX_DEFINE_STATIC_APPMODULE(RxPropertiesModuleName, OdRxPropertiesModule)
#endif
    ODRX_END_STATIC_MODULE_MAP()
#endif


namespace FileGeneratorExampleScenario
{
  namespace
  {//exclude from global namespace

    typedef void(*PScenarioFunc)(OdIfcHostAppServices* app, int curRun);

    struct ScenarioDef
    {
      PScenarioFunc pf;
      const wchar_t* testName;
      unsigned int runsNum;
    };
  }

  class FileGeneratorAppServices
    : public ExampleScenario::ExampleAppServices<OdExIfcHostAppServices>
  {
  public:

    OdIfcFilePtr readFile(const OdString& fileName)
    {
      OdString path = formatPathToBugDirectory(fileName);
      if (!odrxSystemServices()->accessFile(path, Oda::kFileRead))
      {
        throw L"File not found";
      }
      return OdExIfcHostAppServices::readFile(path /*, shareMode*/);
    }

    virtual OdString findFile(const OdString& filename, OdDbBaseDatabase* pDb = 0, FindFileHint hint = kDefault)
    {
      OdString found = OdIfcHostAppServices::findFile(filename, pDb, hint);
      if (!found.isEmpty())
        return found;
      found = formatPathToBugDirectory(filename);
      if (!odrxSystemServices()->accessFile(found, Oda::kFileRead))
        return OdString::kEmpty;
      return found;
    }
  };

  template<bool initGeom, ModelerType modelerType>
  class FileGeneratorEngineInitializer
    : public ScenarioEngine::ScenarioEngineInitializer<FileGeneratorAppServices>
  {
  public:
    FileGeneratorEngineInitializer()
      : ScenarioEngine::ScenarioEngineInitializer<FileGeneratorAppServices>()
    {
#ifndef _TOOLKIT_IN_DLL_
      ODRX_INIT_STATIC_MODULE_MAP();
#endif
    }

    virtual ~FileGeneratorEngineInitializer()
    {
      IfcPropertySetFiller::rxUninit();
      IfcProfileBuilder::rxUninit();
      IfcRepresentationBuilder::rxUninit();
      IfcIndexedPolycurveBuilder::rxUninit();
      IfcRailwayBuilder::rxUninit();
      IfcAlignmentBuilder::rxUninit();
      IfcBuilder::rxUninit();

      ::odrxDynamicLinker()->unloadModule(L"IfcCore.dll");
      odIfcUninitialize();
    }

  protected:
    virtual void onServiceInited(FileGeneratorAppServices& serviceInstance)
    {
      odIfcInitialize(false, initGeom, modelerType);
      ::odrxDynamicLinker()->loadModule(L"IfcCore.dll", false);

      IfcBuilder::rxInit();
      IfcAlignmentBuilder::rxInit();
      IfcRailwayBuilder::rxInit();
      IfcIndexedPolycurveBuilder::rxInit();
      IfcRepresentationBuilder::rxInit();
      IfcProfileBuilder::rxInit();
      IfcPropertySetFiller::rxInit();
    }
  };


  class FileGeneratorDataHandler
    : public ScenarioEngine::ScenarioDataHandler<ScenarioDef, FileGeneratorAppServices>
  {
  public:
    FileGeneratorDataHandler(ScenarioDef* scenarioDataArray, unsigned int scenarioDataArrayLength)
      : ScenarioEngine::ScenarioDataHandler<ScenarioDef, FileGeneratorAppServices>(scenarioDataArray, scenarioDataArrayLength)
    {
    }

    virtual int runScenarioImpl(const ScenarioDef& scenarioData, unsigned int runNumber, FileGeneratorAppServices& hostAppService)
    {
      if (runNumber > scenarioData.runsNum)
      {
        ODA_ASSERT(0);
        return -1;
      }
      
      OdString extension("ifc");
      if (!hostAppService.getBugDirectory().isEmpty())
      {
        hostAppService.setFileName(hostAppService.getBugDirectory() + OdString().format(L"%ls_%i.", scenarioData.testName, runNumber) + extension);
      }

      odPrintConsoleString(L"SCENARIO:%ls, run = %d\n", scenarioData.testName, runNumber);
      int res = ScenarioEngine::TestRun<PScenarioFunc, FileGeneratorAppServices>(scenarioData.pf, &hostAppService, runNumber);
      odPrintConsoleString(L"result = %d\n\n", res);

      return res;
    }
  };

  typedef ExampleScenario::ExampleScenarioGetNames<ScenarioDef, FileGeneratorAppServices> FileGeneratorScenarioGetNames;
  typedef ExampleScenario::ExampleScenarioRunByNumber<ScenarioDef, FileGeneratorAppServices, FileGeneratorEngineInitializer<true, kDefaultModeler> > FileGeneratorScenarioRunByNumber;
  typedef ExampleScenario::ExampleScenarioRunByName<ScenarioDef, FileGeneratorAppServices, FileGeneratorEngineInitializer<true, kDefaultModeler> > FileGeneratorScenarioRunByName;
  typedef ExampleScenario::ExampleScenarioRunAll<ScenarioDef, FileGeneratorAppServices, FileGeneratorEngineInitializer<true, kDefaultModeler> > FileGeneratorScenarioRunAll;

  typedef ExampleScenario::ExampleScenarioRunByNumber<ScenarioDef, FileGeneratorAppServices, FileGeneratorEngineInitializer<false, kDefaultModeler> > FileGeneratorScenarioRunByNumberWoGeom;
  typedef ExampleScenario::ExampleScenarioRunByName<ScenarioDef, FileGeneratorAppServices, FileGeneratorEngineInitializer<false, kDefaultModeler> > FileGeneratorScenarioRunByNameWoGeom;
  typedef ExampleScenario::ExampleScenarioRunAll<ScenarioDef, FileGeneratorAppServices, FileGeneratorEngineInitializer<false, kDefaultModeler> > FileGeneratorScenarioRunAllWoGeom;
}


#endif // _EXAMPLE_SCENARIOS_ENGINE_H_
