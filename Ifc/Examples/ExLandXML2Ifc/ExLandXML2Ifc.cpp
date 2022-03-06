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

#include "OdaCommon.h"
#include "StaticRxObject.h"
#include "RxDynamicModule.h"

#include "IfcExamplesCommon.h"
#include "IfcCore.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

using namespace OdIfc;

//
// Define module map for statically linked modules:
//
#if !defined(_TOOLKIT_IN_DLL_)
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4x3_RC4Module);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcGeomModuleImpl);
  ODRX_BEGIN_STATIC_MODULE_MAP()
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc4x3RC4ModuleName, OdIfc4x3_RC4Module)
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcGeomModuleName, OdIfcGeomModuleImpl)
  ODRX_END_STATIC_MODULE_MAP()
#endif

#include "ExLandXML2IfcConverter.h"
#include "ElementProcessor.h"

namespace OdLandXML2Ifc
{
  xmlSAXHandlerPtr saxHandler();
}

void appInit()
{
  IfcBuilder::rxInit();
    //IfcBuildingBuilder::rxInit();
    //IfcBridgeBuilder::rxInit();
    IfcRepresentationBuilder::rxInit();
    IfcProfileBuilder::rxInit();
    //IfcPropertySetFiller::rxInit();
    //IfcQuantitySetFiller::rxInit();
    IfcRailwayBuilder::rxInit();
}

void appUninit()
{
    IfcRailwayBuilder::rxUninit();
    //IfcQuantitySetFiller::rxUninit();
    //IfcPropertySetFiller::rxUninit();
    IfcProfileBuilder::rxUninit();
    IfcRepresentationBuilder::rxUninit();
    //IfcBridgeBuilder::rxUninit();
    //IfcBuildingBuilder::rxUninit();
  IfcBuilder::rxUninit();
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  int nRes = 0; // Return value for main

#if defined(TARGET_OS_MAC) && !defined(__MACH__)
  argc = ccommand(&argv);
#endif

  setlocale(LC_TIME, ""); // set current user locale (not OD_T("C")), for strftime

  /**********************************************************************/
  /* Create a Services object                                           */
  /**********************************************************************/
  OdStaticRxObject<MyServices> svcs;

  /**********************************************************************/
  /* Display the Product and Version that created the executable        */
  /**********************************************************************/
  odPrintConsoleString(L"\nExLandXML2Ifc developed using %ls ver %ls", 
    svcs.product().c_str(), svcs.versionString().c_str());

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  const int nMandatoryParameters = 3;
  bool bInvalidArgs = (argc < nMandatoryParameters);
  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }

  if (bInvalidArgs)    
  {
    odPrintConsoleString(L"\n\nusage: ExLandXML2Ifc <input_filename> <output_filename>");
    odPrintConsoleString(L"\n<input_filename> - input LandXML (.xml) file\n");
    odPrintConsoleString(L"\n<output_filename> - output .ifc file\n");
    odPrintConsoleString(L"\n[-nogeom] - no geometrical part generation\n");
    odPrintConsoleString(L"\n[-sweeps] - generate sweeps along geometric representations of alignments\n");
    return nRes;
  }

#if !defined(_TOOLKIT_IN_DLL_) 
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  /**********************************************************************/
  /* Initialize ODA SDK                                                 */
  /**********************************************************************/
  odrxInitialize(&svcs);
  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize IfcCore                                                 */
  /**********************************************************************/
  odIfcInitialize(false /* No CDA */, true /* No geometry calculation */);

  appInit();

  try
  {
    LIBXML_TEST_VERSION

    OdLandXML2IfcConverterOptions options;
    if (argc > nMandatoryParameters)
    {
      for (int i = nMandatoryParameters; i < argc; ++i)
      {
        OdString argvi(argv[i]);
        if (odStrICmp(argvi, OD_T("-nogeom")) == 0)
          options.generateGeometry = false;

        if (odStrICmp(argvi, OD_T("-sweepsGradientCurveBySSH")) == 0)
          options.generateSweeps = tSectionedSolidHorizontalWithGradientCurve;
        if (odStrICmp(argvi, OD_T("-sweepsSegmentedReferenceCurveBySSH")) == 0)
          options.generateSweeps = tSectionedSolidHorizontalWithSegmentedReferenceCurve;
        else if (odStrICmp(argvi, OD_T("-sweeps")) == 0)
          options.generateSweeps = tFixedReferenceSweptAreaSolid;
      }
    }

    OdIfcFilePtr ifcFile = svcs.createDatabase(kScmIfc4x3_RC4);
    
    OdLandXML2IfcConverterPtr converter = new OdLandXML2IfcConverter(ifcFile);
    converter->init(options);

    //
    // IFC file header creation
    //
    OdArray<OdIfcEntityPtr> units;
    units.append(converter->createSiUnit("LENGTHUNIT", nullptr /*"MILLI"*/, "METRE"));
    units.append(converter->createSiUnit("PLANEANGLEUNIT", nullptr, "RADIAN"));
    units.append(converter->createSiUnit("AREAUNIT", nullptr, "SQUARE_METRE"));
    units.append(converter->createSiUnit("VOLUMEUNIT", nullptr, "CUBIC_METRE"));
    converter->fromScratch("Open Design Alliance", "ExLandXML2Ifc", units);
    converter->site()->putAttr("name", OdAnsiString("Railway_Site"));
    converter->appendGeometricRepresentationContext("2D", "Plan", 2);
    converter->appendGeometricRepresentationContext("3D", "Model", 3, 1e-6);

    OdString wstrFileName = argv[1];
    OdAnsiString fileName(wstrFileName, CP_UTF_8);
    int res = xmlSAXUserParseFile(OdLandXML2Ifc::saxHandler(), converter.get(), fileName.c_str());
    if (res == 0)
      ifcFile->writeFile(argv[2]);
    else
      odPrintConsoleString(L"\nConversion error.\n");
  }
  catch(OdError& e)
  {
    odPrintConsoleString(L"\n\nError: %ls", e.description().c_str());
    nRes = -1;
  }
  catch(...)
  {
    odPrintConsoleString(L"\n\nUnexpected error.");
    nRes = -1;
    throw;
  }

  appUninit();

  /**********************************************************************/
  /* Uninitialize IfcCore                                               */
  /**********************************************************************/
  odIfcUninitialize();

  /**********************************************************************/
  /* Uninitialize ODA SDK                                               */
  /**********************************************************************/
  odDbRootUninitialize();
  odrxUninitialize();

  return nRes;
}

