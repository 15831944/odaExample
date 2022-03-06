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

/************************************************************************/
/* This console application reads a VSF file and dumps its contents     */
/* to the console.                                                      */
/************************************************************************/

// ODA SDK
#include "OdaCommon.h"
#include "diagnostics.h"

#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a

#ifdef OD_HAVE_CONSOLE_H_FILE
#include <console.h>
#endif

#include "DynamicLinker.h"
#include "ExPrintConsole.h"
#include "RxInit.h"
#include "RxDynamicModule.h"

// Visualize
#include "TvDatabase.h"
#include "TvFactory.h"
#include "TvInsert.h"
#include "TvModuleNames.h"
#include "TvError.h"
#include "TvCoreModulesNames.h"

#ifndef _TOOLKIT_IN_DLL_
// Visualize API
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvDbIOModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvDbCoreModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TvISMModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TvSCENEOEModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvTfModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvDbPartialViewingModuleImpl );
//TvCore
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvCoreDatabaseModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvCoreDatabaseIOModule );
// Visualize models generator
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeSampleModelsFilerModule);
//Visualize device
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(VisualizeDeviceModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRecomputeDimBlockModule);
//Raster images
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRasterProcessingServicesImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);
//Device
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTrGL2RenderModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(GLES2Module);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(DbCryptModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxCommonDataAccessModule);

ODRX_BEGIN_STATIC_MODULE_MAP()
ODRX_DEFINE_STATIC_APPMODULE(OdTvModuleName, OdTvModule)
ODRX_DEFINE_STATIC_APPMODULE(L"TV_SCENEOE", TvSCENEOEModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvDbCoreModuleName, OdTvDbCoreModule )
ODRX_DEFINE_STATIC_APPMODULE(OdTvDbIOAppName, OdTvDbIOModule)
ODRX_DEFINE_STATIC_APPMODULE(L"TV_ISM", TvISMModule)
ODRX_DEFINE_STATIC_APPLICATION(OdModelerGeometryModuleName, ModelerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvTfModuleName, OdTvTfModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvPartialViewingModuleName, OdTvDbPartialViewingModuleImpl )
//TvCore
ODRX_DEFINE_STATIC_APPMODULE( OdTvCoreDatabaseModuleName, OdTvCoreDatabaseModule )
ODRX_DEFINE_STATIC_APPMODULE( OdTvCoreDatabaseIOModuleName, OdTvCoreDatabaseIOModule )

ODRX_DEFINE_STATIC_APPMODULE(OdTvVisualizeDeviceModuleName, VisualizeDeviceModule)
ODRX_DEFINE_STATIC_APPLICATION(OdRecomputeDimBlockModuleName, OdRecomputeDimBlockModule)

ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName, OdRasterProcessingServicesImpl)
ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME, ExRasterModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTrGL2ModuleName, OdTrGL2RenderModule)
ODRX_DEFINE_STATIC_APPMODULE(OdWinGLES2ModuleName, GLES2Module)
ODRX_DEFINE_STATIC_APPMODULE(DbCryptModuleName, DbCryptModule)
ODRX_DEFINE_STATIC_APPMODULE(RxCommonDataAccessModuleName, OdRxCommonDataAccessModule)
ODRX_END_STATIC_MODULE_MAP()

#endif

static const char cUsage[] =
{
  "VisualizeDatabaseDumper sample program. Copyright (C) " TD_COPYRIGHT_START_YEAR_S  TD_COPYRIGHT_END_S "\n"
  "Usage: VisualizeDatabaseDumper Filename.vsf [MT] [DD]\n"
  "  Output is written to stdout, redirect if necessary.\n"
  "    MT - loading using multithreaded mode\n"
  "    DD - only load, completely disable dump\n"
  "\nPress ENTER to continue...\n"
};


/********************************************************************************/
/* Define Assert function to not crash Debug application if assertion is fired. */
/********************************************************************************/
static void MyAssert(const char* expression, const char* fileName, int nLineNo)
{
  OdString message;
  message.format(L"\n!!! Assertion failed: \"%ls\"\n    file: %ls, line %d\n", OdString(expression).c_str(), OdString(fileName).c_str(), nLineNo);
  odPrintConsoleString(message);
}

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

// method for print
void printText(int indent = 0, OdString leftString = OdString::kEmpty, OdString rightString = OdString::kEmpty, int colWidth = 20
  , bool isProperty = false)
{
  OdString spaces(OD_T("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "));
  OdString leader(OD_T(". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . "));
  OdString buffer;
  const int tabSize = 2;
  /**********************************************************************/
  /* Indent leftString with spaces characters                           */
  /**********************************************************************/
  if (isProperty)
  {
    spaces = OD_T("                                                            ");
    leftString.insert(0, "[");
  }
  leftString = spaces.left(tabSize*indent) + leftString;

  /**********************************************************************/
  /* If rightString is not specified, just output the indented          */
  /* leftString. Otherwise, fill the space between leftString and       */
  /* rightString with leader characters.                                */
  /**********************************************************************/
  if (rightString.isEmpty())
  {
    if (!isProperty)
      buffer = leftString;
    else
      buffer = leftString + OD_T("]");
  }
  else
  {
    if (isProperty)
      rightString = rightString + "]";
    int leaders = colWidth - leftString.getLength();
    if (leaders > 0) {
      buffer = leftString + leader.mid(leftString.getLength(), leaders) + rightString;
    }
    else
    {
      buffer = leftString + L' ' + rightString;
    }
  }

  odPrintConsoleString(L"%ls\n", buffer.c_str());
}

OdString toString(bool val)
{
  return (val ? OD_T("true") : OD_T("false"));
}

#if OD_SIZEOF_LONG == 4
OdString toString(OdInt32 val)
{
  OdString buffer;
  buffer.format(OD_T("%ld"), val);
  return buffer;
}
#endif

OdString toString(int val)
{
  OdString buffer;
  buffer.format(OD_T("%d"), val);
  return buffer;
}

OdString toString(OdUInt64 val)
{
  OdString buffer;
  buffer.format(OD_T("%llu"), val);
  return buffer;
}

static double FixNZ(double dVal, double dTol = 5.1e-2)
{
  return OdZero(dVal, dTol) ? 0. : dVal;
}

OdString toString(double val)
{
  OdString temp;
  double _val = FixNZ(val, 5.1e-5);

  if (fabs(_val) < 1e6)
  {
    temp.format(OD_T("%.4f"), _val);

    /***********************************************************************/
    /* Strip all but one trailing zero from buffer                         */
    /***********************************************************************/
    for (int n = temp.getLength(); ((temp[n - 2] != '.') && (temp[n - 1] == '0')); n--)
      temp = temp.left(temp.getLength() - 1);
  }
  else
    temp.format(OD_T("%.4E"), _val);

  return temp;
}

OdString toString(const OdTvPoint& pnt)
{
  return OD_T("( ") + toString(pnt.x) + OD_T(" , ") + toString(pnt.y) + OD_T(" , ") + toString(pnt.z) + OD_T(" )");
}

OdString toString(const OdTvVector& vec)
{
  return OD_T("( ") + toString(vec.x) + OD_T(" , ") + toString(vec.y) + OD_T(" , ") + toString(vec.z) + OD_T(" )");
}

OdString toString(ODCOLORREF color)
{
  OdUInt8 r = ODGETRED(color), g = ODGETGREEN(color), b = ODGETBLUE(color);
  OdString buffer;
  buffer.format(OD_T("(%d, %d, %d"), r, g, b);
  return buffer;
}

OdString toString(const OdTvColorDef& color)
{
  OdString buffer;

  switch (color.getType())
  {
  case OdTvColorDef::kDefault:
    buffer = OD_T("Default");
    break;
  case OdTvColorDef::kColor:
    OdUInt8 r, g, b;
    color.getColor(r, g, b);
    buffer.format(OD_T("(%d, %d, %d"), r, g, b);
    break;
  case OdTvColorDef::kInherited:
    if(color.getInheritedColor() == OdTv::kByBlock)
      buffer = OD_T("ByBlock");
    else
      buffer = OD_T("ByLayer");
    break;
  case OdTvColorDef::kIndexed:
    buffer.format(OD_T("%u"), color.getIndexedColor());
    break;
  }

  return buffer;
}

OdString toString(const OdTvLineWeightDef& lw)
{
  OdString buffer;

  switch (lw.getType())
  {
  case OdTvLineWeightDef::kDefault:
    buffer = OD_T("Default");
    break;
  case OdTvLineWeightDef::kValue:
    buffer.format(OD_T("%u"), lw.getValue());
    break;
  case OdTvLineWeightDef::kInherited:
    if (lw.getInheritedLineWeight() == OdTv::kByBlock)
      buffer = OD_T("ByBlock");
    else
      buffer = OD_T("ByLayer");
    break;
  }

  return buffer;
}

OdString toString(const OdTvLinetypeDef& lt)
{
  OdString buffer;

  switch (lt.getType())
  {
  case OdTvLinetypeDef::kDefault:
  {
    buffer = OD_T("Default");
    break;
  }
  case OdTvLinetypeDef::kId:
  {
    OdTvLinetypeId id = lt.getLinetype();
    if (!id.isNull())
      buffer = id.openObject()->getName();
    break;
  }
  case OdTvLinetypeDef::kPredefined:
  {
    switch (lt.getPredefinedLinetype())
    {
    case OdTvLinetype::kDash2Dot: 
      buffer = OD_T("Dash2Dot"); 
      break;
    case OdTvLinetype::kDash3Dot: buffer = OD_T("Dash3Dot"); break;
    case OdTvLinetype::kDashDot: buffer = OD_T("DashDot"); break;
    case OdTvLinetype::kDashed : buffer = OD_T("Dashed"); break;
    case OdTvLinetype::kDotted: buffer = OD_T("Dotted"); break;
    case OdTvLinetype::kLongDash: buffer = OD_T("LongDash"); break;
    case OdTvLinetype::kLongDash2ShortDash: buffer = OD_T("LongDash2ShortDash"); break;
    case OdTvLinetype::kLongDashShortDash: buffer = OD_T("LongDashShortDash"); break;
    case OdTvLinetype::kSolid: buffer = OD_T("Solid"); break;
    }
    break;
  }
  case OdTvLinetypeDef::kInherited:
  {
    if (lt.getInheritedLinetype() == OdTv::kByBlock)
      buffer = OD_T("ByBlock");
    else
      buffer = OD_T("ByLayer");
    break;
  }
  }

  return buffer;
}

OdString toString(const OdTvTransparencyDef& tr)
{
  OdString buffer;

  switch (tr.getType())
  {
  case OdTvTransparencyDef::kDefault:
    buffer = OD_T("Default");
    break;
  case OdTvTransparencyDef::kValue:
    buffer.format(OD_T("%lf"), tr.getValue());
    break;
  case OdTvTransparencyDef::kInherited:
    if (tr.getInheritedTransparency() == OdTv::kByBlock)
      buffer = OD_T("ByBlock");
    else
      buffer = OD_T("ByLayer");
    break;
  }

  return buffer;
}

OdString toString(const OdTvLayerDef& layer)
{
  OdString buffer;

  switch (layer.getType())
  {
  case OdTvLayerDef::kDefault:
    buffer = OD_T("Default");
    break;
  case OdTvLayerDef::kId:
    OdTvLayerId lyId = layer.getLayer();
    if (!lyId.isNull())
      buffer = lyId.openObject()->getName();
    break;
  }

  return buffer;
}

OdString toString(const OdTvTextStyleDef& txtDef)
{
  OdString buffer;

  switch (txtDef.getType())
  {
  case OdTvLayerDef::kDefault:
    buffer = OD_T("Default");
    break;
  case OdTvLayerDef::kId:
    OdTvTextStyleId id = txtDef.getTextStyle();
    if (!id.isNull())
      buffer = id.openObject()->getName();
    break;
  }

  return buffer;
}

OdString toString(const OdTvMaterialDef& matDef)
{
  OdString buffer;

  switch (matDef.getType())
  {
  case OdTvMaterialDef::kDefault:
  {
    buffer = OD_T("Default");
    break;
  }
  case OdTvMaterialDef::kId:
  {
    OdTvMaterialId id = matDef.getMaterial();
    if (!id.isNull())
      buffer = id.openObject()->getName();
    break;
  }
  case OdTvMaterialDef::kInherited:
  {
    if (matDef.getInheritedMaterial() == OdTv::kByBlock)
      buffer = OD_T("ByBlock");
    else
      buffer = OD_T("ByLayer");
    break;
  }
  }

  return buffer;
}

OdString toString(const OdTvVisibilityDef& visDef)
{
  OdString buffer;

  switch (visDef.getType())
  {
  case OdTvVisibilityDef::kInvisible:
    buffer = "Invisible";
    break;
  case OdTvVisibilityDef::kVisible:
    buffer = "Visible";
    break;
  case OdTvVisibilityDef::kDefault:
    buffer = "Default";
    break;
  }

  return buffer;
}


void dumbDatabase(const OdTvDatabaseId& dbId);
void dumpDevices(OdTvDevicesIteratorPtr pIt, int indent);
void dumpModels(OdTvModelsIteratorPtr pIt, int indent);
void dumpBlocks(OdTvBlocksIteratorPtr pIt, int indent);
void dumpEntities(OdTvEntitiesIteratorPtr pIt, int indent);
void dumpGeometries(OdTvGeometryDataIteratorPtr pIt, int indent);
void dumpLinetypes(OdTvLinetypesIteratorPtr pIt, int indent);
void dumpTextStyles(OdTvTextStylesIteratorPtr pIt, int indent);
void dumpRasterImages(OdTvRasterImagesIteratorPtr pIt, int indent);
void dumpLayers(OdTvLayersIteratorPtr pIt, int indent);
void dumpMaterials(OdTvMaterialsIteratorPtr pIt, int indent);
void dumpBackgrounds(OdTvGsViewBackgroundsIteratorPtr pIt, int indent);

const char * geomTypes[] = { "Undefinied", "Polyline", "Circle", "CircleWedge", "CircularArc", "Ellipse"
                           , "EllipticArc", "Polygon", "Text", "Shell", "Sphere", "Cylinder"
                           , "SubInsert", "SubEntity", "Nurbs", "RasterImage", "InfiniteLine"
                           , "Mesh", "PointCloud", "Grid", "ColoredShape", "Box", "Brep" };


/************************************************************************/
/* Main                                                                 */
/************************************************************************/
#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#ifdef OD_HAVE_CCOMMAND_FUNC
  argc = ccommand(&argv);
#endif
  
  /**********************************************************************/
  /* Verify the argument count and display an error message as required */
  /**********************************************************************/
  if (argc < 2) 
  {
    STD(cout) << cUsage;
    STD(cin).get();
    return 1;
  }
  else
  {

    bool isMTMode = false;
    bool disableDump = false;
    bool disablePressAnyKey = false;
    for (int i = 2; i < argc; ++i)
    {
      /**********************************************************************/
      /* Use MT loading mode                                                */
      /**********************************************************************/
      if (!OdString(argv[i]).iCompare(L"MT"))
        isMTMode = true;
      /**********************************************************************/
      /* Disable dump                                                       */
      /**********************************************************************/
      else if (!OdString(argv[i]).iCompare(L"DD"))
          disableDump = true;
      /**********************************************************************/
      /* Disable press any key                                              */
      /**********************************************************************/
      else if (!OdString(argv[i]).iCompare(L"-NoWait"))
        disablePressAnyKey = true;
    }

    /**********************************************************************/
    /* Set customized assert function                                     */
    /**********************************************************************/
    odSetAssertFunc(MyAssert);

    /********************************************************************/
    /* Initialize ODA and Visualize SDK.                                */
    /********************************************************************/

#ifndef _TOOLKIT_IN_DLL_
    ODRX_INIT_STATIC_MODULE_MAP();
#endif

    ODASdkActivate();
    odPrintConsoleString(L"ODA SDK initialized.\n");
    odTvInitialize();
    odPrintConsoleString(L"Visualize SDK initialized.\n");

#if defined(_MSC_VER) && !defined(_WINRT)

    /********************************************************************/
    /* Initialize Encryption/Decryption                      */
    /********************************************************************/
    ::odrxDynamicLinker()->loadModule( OdDbCoreModuleName );
    ::odrxDynamicLinker()->loadModule(DbCryptModuleName);
#endif


    bool bSuccess = true;
    try 
    {
      OdString f(argv[1]); // for UNIX UNICODE support
      OdTvVsfImportParams params;
      params.setFilePath( f.c_str() );
      params.setMtImport( isMTMode );
      OdTvDatabaseId dbId = odTvGetFactory().importFile(&params);
      if (dbId.isNull() || !dbId.isValid())
      {
        odPrintConsoleString(L"Read of file failed.\n");
        return 0;
      }

      /****************************************************************/
      /* Dump the database                                            */
      /****************************************************************/
      if(!disableDump)
      {
        odPrintConsoleString(L"\nStart dumping...\n\n");
        dumbDatabase(dbId);
        odPrintConsoleString(L"\nDumping finished.\n\n");
      }
    }
    /********************************************************************/
    /* Display the error                                                */
    /********************************************************************/
    catch (OdTvError& e)
    {
      odPrintConsoleString(L"\nVisualize Error: %ls\n", e.description().c_str());
      bSuccess = false;
    }
    catch (OdError& e)
    {
      odPrintConsoleString(L"\nODA Error: %ls\n", e.description().c_str());
      bSuccess = false;
    }
    catch (...)
    {
      odPrintConsoleString(L"\nUnknown Error.\nPress ENTER to continue...\n");
      STD(cin).get();
      return 0;
    }

    /********************************************************************/
    /* Uninitialize ODA and Visualize SDK                               */
    /********************************************************************/
    
    try
    {
      ODASdkDeactivate();
      odPrintConsoleString(L"ODA SDK uninitialized.\n");
      odTvUninitialize();
      odPrintConsoleString(L"Visualize SDK uninitialized.\n");
      if (bSuccess)
      {
        if (!disablePressAnyKey)
        {
          odPrintConsoleString(L"VisualizeDatabaseDumper finished successfully.\n\nPress any key for exit...");
          getchar();
        }
        else
          odPrintConsoleString(L"VisualizeDatabaseDumper finished successfully.\n");
      }
    }
    catch(OdError& e)
    {
      odPrintConsoleString(L"Uninitialization failed.\n");
      odPrintConsoleString(L"OdError description:\n%ls\n", e.description().c_str());
    }
    catch(...)
    {
      odPrintConsoleString(L"Uninitialization failed.\n");
    }
    
    return 0;
  }
}


void dumbDatabase(const OdTvDatabaseId& dbId)
{
  if (dbId.isNull())
    return;

  OdTvDatabasePtr pDb = dbId.openObject();
  if (pDb.isNull())
    return;

  int indent = 0;
  // print database
  printText(indent++, "Database:", pDb->getFilename(), 20);
  dumpDevices(pDb->getDevicesIterator(), indent);
  dumpModels(pDb->getModelsIterator(), indent);
  dumpBlocks(pDb->getBlocksIterator(), indent);
  dumpLinetypes(pDb->getLinetypesIterator(), indent);
  dumpTextStyles(pDb->getTextStylesIterator(), indent);
  dumpRasterImages(pDb->getRasterImagesIterator(), indent);
  dumpLayers(pDb->getLayersIterator(), indent);
  dumpMaterials(pDb->getMaterialsIterator(), indent);
  dumpBackgrounds(pDb->getBackgroundsIterator(), indent);
}

void dumpDevices(OdTvDevicesIteratorPtr pIt, int indent)
{
  if (pIt.isNull() || pIt->done())
    return;

  printText(indent++, "Devices:");

  for (; !pIt->done(); pIt->step())
  {
    OdTvGsDevicePtr pDev = pIt->getDevice().openObject();
    printText(indent, "Device<" + pDev->getName() + ">");
    // properties
    printText(indent, "Database handle:", toString(pDev->getDatabaseHandle()), 0, true);
    printText(indent, "Is active:", toString(pDev->getActive()), 0, true);
    printText(indent, "Number of views:", toString(pDev->numViews()), 0, true);
    printText(indent, "Background color:", toString((ODCOLORREF)pDev->getBackgroundColor()), 0, true);
    bool flag = false;
    OdInt16 sVal = 0;
    OdInt32 iVal = 0;
    pDev->getOption(OdTvGsDevice::kDoubleBufferEnabled, flag);
    printText(indent, "DoubleBufferEnabled:", toString(flag), 0, true);
    pDev->getOption(OdTvGsDevice::kBlocksCache, flag);
    printText(indent, "BlocksCache:", toString(flag), 0, true);
    pDev->getOption(OdTvGsDevice::kEnableMultithread, flag);
    printText(indent, "EnableMultithread:", toString(flag), 0, true);
    pDev->getOption(OdTvGsDevice::kMaxRegenThreads, sVal);
    printText(indent, "MaxRegenThreads:", toString((int)sVal), 0, true);
    pDev->getOption(OdTvGsDevice::kUseDynamicSubEntHlt, flag);
    printText(indent, "UseDynamicSubEntHlt:", toString(flag), 0, true);
    pDev->getOption(OdTvGsDevice::kDiscardBackFaces, flag);
    printText(indent, "DiscardBackFaces:", toString(flag), 0, true);
    pDev->getOption(OdTvGsDevice::kUseTTFCache, flag);
    printText(indent, "UseTTFCache:", toString(flag), 0, true);
    pDev->getOption(OdTvGsDevice::kUseVisualStyles, flag);
    printText(indent, "UseVisualStyles:", toString(flag), 0, true);
    pDev->getOption(OdTvGsDevice::kUseOverlayBuffers, flag);
    printText(indent, "UseOverlayBuffers:", toString(flag), 0, true);
    pDev->getOption(OdTvGsDevice::kUseLutPalette, iVal);
    printText(indent, "LutMonochrome:", toString(GETBIT(iVal, 0x1)), 0, true);
    printText(indent, "LutPalette:", toString(GETBIT(iVal, 0x2)), 0, true);

    // add views
    for (int i = 0; i < pDev->numViews(); i++)
    {
      OdTvGsViewPtr pView = pDev->viewAt(i).openObject();
      printText(++indent, "View<" + pView->getName() + ">");
      printText(indent, "Database handle:", toString(pView->getDatabaseHandle()), 0, true);
      printText(indent, "Is active:", toString(pView->getActive()), 0, true);
      printText(indent, "Position:", toString(pView->position()), 0, true);
      printText(indent, "Target:", toString(pView->target()), 0, true);
      printText(indent, "Up vector:", toString(pView->upVector()), 0, true);
      printText(indent, "Field width:", toString(pView->fieldWidth()), 0, true);
      printText(indent, "Field height:", toString(pView->fieldHeight()), 0, true);
      OdTvVisualStyleId vsId = pView->getVisualStyle();
      if(!vsId.isNull())
        printText(indent, "Visual style:", vsId.openObject()->getName(), 0, true);
      printText(indent, "Is perspective:", toString(pView->isPerspective()), 0, true);
      printText(indent, "Lens lenght:", toString(pView->lensLength()), 0, true);
    }
  }
}

void dumpModels(OdTvModelsIteratorPtr pIt, int indent)
{
  if (pIt.isNull() || pIt->done())
    return;

  printText(indent++, "Models:");

  for (; !pIt->done(); pIt->step())
  {
    OdTvModelPtr pModel = pIt->getModel().openObject();
    printText(indent, "Model<" + pModel->getName() + ">");
    printText(indent, "Database handle:", toString(pModel->getDatabaseHandle()), 0, true);
    dumpEntities(pModel->getEntitiesIterator(), indent + 1);
  }
}

void dumpBlocks(OdTvBlocksIteratorPtr pIt, int indent)
{
  if (pIt.isNull() || pIt->done())
    return;

  printText(indent++, "Blocks:");

  for (; !pIt->done(); pIt->step())
  {
    OdTvBlockPtr pBlock = pIt->getBlock().openObject();
    printText(indent, "Block<" + pBlock->getName() + ">");
    printText(indent, "Database handle:", toString(pBlock->getDatabaseHandle()), 0, true);
    dumpEntities(pBlock->getEntitiesIterator(), indent + 1);
  }
}

void printEntityProperties(OdTvEntityPtr pEn, int indent)
{
  printText(indent, "Database handle:", toString(pEn->getDatabaseHandle()), 0, true);
  printText(indent, "Color:", toString(pEn->getColor()), 0, true);
  printText(indent, "Lineweight:", toString(pEn->getLineWeight()), 0, true);
  printText(indent, "Linetype:", toString(pEn->getLinetype()), 0, true);
  printText(indent, "Transparency:", toString(pEn->getTransparency()), 0, true);
  printText(indent, "Layer:", toString(pEn->getLayer()), 0, true);
  printText(indent, "TextStyle:", toString(pEn->getTextStyle()), 0, true);
  printText(indent, "Material:", toString(pEn->getMaterial()), 0, true);
  printText(indent, "Visibility:", toString(pEn->getVisibility()), 0, true);
  printText(indent, "Linetype scale:", toString(pEn->getLinetypeScale()), 0, true);
  printText(indent, "Auto regen:", toString(pEn->getAutoRegen()), 0, true);
}

void dumpEntities(OdTvEntitiesIteratorPtr pIt, int indent)
{
  if (pIt.isNull() || pIt->done())
    return;

  for (; !pIt->done(); pIt->step())
  {
    OdTvEntityId id = pIt->getEntity();
    switch (id.getType())
    {
    case OdTvEntityId::kEntity:
    {
      OdTvEntityPtr pEn = id.openObject();
      printText(indent, "Entity<" + pEn->getName() + ">");
      printEntityProperties(pEn, indent);

      dumpGeometries(pEn->getGeometryDataIterator(), indent + 1);
      break;
    }
    case OdTvEntityId::kInsert:
    {
      OdTvInsertPtr pIns = id.openObjectAsInsert();
      printText(indent, "Insert<" + pIns->getName() + ">");
      break;
    }
    case OdTvEntityId::kLight:
    {
      OdTvLightPtr pLight = id.openObjectAsLight();
      printText(indent, "Light<" + pLight->getName() + ">");
      break;
    }
    }
  }
}

void printGeometryProperties(const OdTvGeometryDataId& id, int indent)
{
  switch (id.getType())
  {
  case OdTv::kPolyline:
  {
    OdTvPolylineDataPtr pLine = id.openAsPolyline();
    printText(indent, "Points count:", toString(pLine->getPointsCount()), 0, true);
    OdTvVector norm;
    pLine->getNormal(norm);
    printText(indent, "Normal:", toString(norm), 0, true);
    bool bFilled;
    printText(indent, "Thickness:", toString(pLine->getThickness(bFilled)), 0, true);
    printText(indent, "Filled:", toString(bFilled), 0, true);
    break;
  }
  case OdTv::kCircle:
  {
    OdTvCircleDataPtr pCirc = id.openAsCircle();
    printText(indent, "Center:", toString(pCirc->getCenter()), 0, true);
    printText(indent, "Radius:", toString(pCirc->getRadius()), 0, true);
    printText(indent, "Normal:", toString(pCirc->getNormal()), 0, true);
    printText(indent, "Thickness:", toString(pCirc->getThickness()), 0, true);
    printText(indent, "Filled:", toString(pCirc->getFilled()), 0, true);
    break;
  }
  case OdTv::kCircleWedge:
  { 
    OdTvCircleWedgeDataPtr pWedge = id.openAsCircleWedge();
    printText(indent, "Start:", toString(pWedge->getStart()), 0, true);
    printText(indent, "Middle:", toString(pWedge->getMiddle()), 0, true);
    printText(indent, "End:", toString(pWedge->getEnd()), 0, true);
    printText(indent, "Thickness:", toString(pWedge->getThickness()), 0, true);
    printText(indent, "Filled:", toString(pWedge->getFilled()), 0, true);
    break;
  }
  case OdTv::kCircularArc:
  {
    OdTvCircleArcDataPtr pArc = id.openAsCircleArc();
    printText(indent, "Start:", toString(pArc->getStart()), 0, true);
    printText(indent, "Middle:", toString(pArc->getMiddle()), 0, true);
    printText(indent, "End:", toString(pArc->getEnd()), 0, true);
    printText(indent, "Thickness:", toString(pArc->getThickness()), 0, true);
    printText(indent, "Filled:", toString(pArc->getFilled()), 0, true);
    break;
  }
  case OdTv::kEllipse:
  {
    OdTvEllipseDataPtr pEllip = id.openAsEllipse();
    printText(indent, "Center:", toString(pEllip->getCenter()), 0, true);
    printText(indent, "Major:", toString(pEllip->getMajor()), 0, true);
    printText(indent, "Minor:", toString(pEllip->getMinor()), 0, true);
    printText(indent, "Thickness:", toString(pEllip->getThickness()), 0, true);
    printText(indent, "Filled:", toString(pEllip->getFilled()), 0, true);
    break;
  }
  case OdTv::kEllipticArc:
  {
    OdTvEllipticArcDataPtr pEllipArc = id.openAsEllipticArc();
    printText(indent, "Center:", toString(pEllipArc->getCenter()), 0, true);
    printText(indent, "Major:", toString(pEllipArc->getMajor()), 0, true);
    printText(indent, "Minor:", toString(pEllipArc->getMinor()), 0, true);
    printText(indent, "Thickness:", toString(pEllipArc->getThickness()), 0, true);
    printText(indent, "Filled:", toString(pEllipArc->getFilled()), 0, true);
    break;
  }
  case OdTv::kPolygon:
  {
    OdTvPolygonDataPtr pPolygon = id.openAsPolygon();
    printText(indent, "Points count:", toString(pPolygon->getPointsCount()), 0, true);
    printText(indent, "Filled:", toString(pPolygon->getFilled()), 0, true);
    printText(indent, "Use inverse normal:", toString(pPolygon->getUseInverseNormal()), 0, true);
    break;
  }
  case OdTv::kText:
  {
    const char *alignModes[] = { "Left", "Center", "Right", "Aligned", "Middle", "Fit", "TopLeft", "TopCenter", "TopRight", "MiddleLeft"
  , "MiddleCenter", "MiddleRight", "BottomLeft", "BottomCenter", "BottomRight" };
    OdTvTextDataPtr pTxt = id.openAsText();
    printText(indent, "String:", pTxt->getString(), 0, true);
    printText(indent, "Position:", toString(pTxt->getPosition()), 0, true);
    printText(indent, "Rotation:", toString(pTxt->getRotation()), 0, true);
    printText(indent, "Normal:", toString(pTxt->getNormal()), 0, true);
    printText(indent, "Text size:", toString(pTxt->getTextSize()), 0, true);
    printText(indent, "TextStyle:", toString(pTxt->getTextStyle()), 0, true);
    printText(indent, "Alignment mode:", alignModes[pTxt->getAlignmentMode()], 0, true);
    printText(indent, "Alignment point:", toString(pTxt->getAlignmentPoint()), 0, true);
    printText(indent, "Overlined:", toString(pTxt->getOverlined()), 0, true);
    printText(indent, "Underlined:", toString(pTxt->getUnderlined()), 0, true);
    printText(indent, "Striked:", toString(pTxt->getStriked()), 0, true);
    printText(indent, "Non rotatable:", toString(pTxt->getNonRotatable()), 0, true);
    break;
  }
  case OdTv::kShell:
  {
    OdTvShellDataPtr pShell = id.openAsShell();
    printText(indent, "Vertices count:", toString(pShell->getVerticesCount()), 0, true);
    printText(indent, "Faces count:", toString(pShell->getFacesCount()), 0, true);
    printText(indent, "Edges count:", toString(pShell->getEdgesCount()), 0, true);
    printText(indent, "Disable lighting:", toString(pShell->getDisableLighting()), 0, true);
    break;
  }
  case OdTv::kSphere:
  {
    OdTvSphereDataPtr pSphere = id.openAsSphere();
    printText(indent, "Center:", toString(pSphere->getCenter()), 0, true);
    printText(indent, "Radius:", toString(pSphere->getRadius()), 0, true);
    OdTvVector axis, primeMeridian;
    pSphere->getBasis(axis, primeMeridian);
    printText(indent, "Axis:", toString(axis), 0, true);
    printText(indent, "Prime meridian:", toString(primeMeridian), 0, true);
    break;
  }
  case OdTv::kCylinder:
  {
    OdTvCylinderDataPtr pCyl = id.openAsCylinder();
    const char * capsArr[] = { "None", "First", "Second", "Both" };
    printText(indent, "Count of points:", toString((int)pCyl->getPoints().size()), 0, true);
    printText(indent, "Count of radii:", toString((int)pCyl->getRadii().size()), 0, true);
    printText(indent, "Capping:", capsArr[pCyl->getCaps()], 0, true);
    break;
  }
  case OdTv::kSubInsert:
  {
    OdTvInsertDataPtr pIns = id.openAsInsert();
    printText(indent, "Block:", pIns->getBlock().openObject()->getName(), 0, true);
    break;
  }
  case OdTv::kSubEntity:
  {
    OdTvEntityPtr pEn = id.openAsSubEntity();
    printEntityProperties(pEn, indent);
    break;
  }
  case OdTv::kNurbs:
  {
    OdTvNurbsDataPtr pNurbs = id.openAsNurbs();
    printText(indent, "Degree:", toString((int)pNurbs->getDegree()), 0, true);
    printText(indent, "Count of control points:", toString((int)pNurbs->getControlPoints().size()), 0, true);
    printText(indent, "Count of weights:", toString((int)pNurbs->getWeights().size()), 0, true);
    printText(indent, "Count of knots:", toString((int)pNurbs->getKnots().size()), 0, true);
    double start = 0., end = 0.;
    pNurbs->getStartEnd(start, end);
    printText(indent, "Start:", toString(start), 0, true);
    printText(indent, "End:", toString(end), 0, true);
    bool bFilled = false;
    printText(indent, "Thickness:", toString(pNurbs->getThickness(bFilled)), 0, true);
    printText(indent, "Filled:", toString(bFilled), 0, true);
    break;
  }
  case OdTv::kRasterImage:
  {
    OdTvRasterImageDataPtr pRasterImg = id.openAsRasterImage();
    printText(indent, "Size:", toString(OdTvVector(pRasterImg->getImageSize().x, pRasterImg->getImageSize().y, 0.)), 0, true);
    printText(indent, "Brightness:", toString((int)pRasterImg->getBrightness()), 0, true);
    printText(indent, "Contrast:", toString((int)pRasterImg->getContrast()), 0, true);
    printText(indent, "Fade:", toString((int)pRasterImg->getFade()), 0, true);
    printText(indent, "MonochromeBackgroundColor:", toString(pRasterImg->getMonochromeBackgroundColor()), 0, true);
    printText(indent, "Clip inverted:", toString(pRasterImg->getClipInverted()), 0, true);
    printText(indent, "Clipped:", toString(pRasterImg->getClipped()), 0, true);
    OdTvPoint origin;
    OdTvVector u, v;
    pRasterImg->getOrientation(origin, u, v);
    printText(indent, "Origin:", toString(origin), 0, true);
    printText(indent, "Direction and width:", toString(u), 0, true);
    printText(indent, "Direction and height:", toString(v), 0, true);
    break;
  }
  case OdTv::kInfiniteLine:
  {
    OdTvInfiniteLineDataPtr pLine = id.openAsInfiniteLine();
    printText(indent, "First:", toString(pLine->getFirst()), 0, true);
    printText(indent, "First:", toString(pLine->getSecond()), 0, true);
    if (pLine->getType() == OdTvInfiniteLineData::kLine)
      printText(indent, "Type:", OD_T("Line"), 0, true);
    else
      printText(indent, "Type:", OD_T("Ray"), 0, true);
    break;
  }
  case OdTv::kMesh:
  {
    OdTvMeshDataPtr pMesh = id.openAsMesh();
    printText(indent, "Vertices count:", toString(pMesh->getVerticesCount()), 0, true);
    printText(indent, "Faces count:", toString(pMesh->getFacesCount()), 0, true);
    printText(indent, "Edges count:", toString(pMesh->getEdgesCount()), 0, true);
    printText(indent, "Columns count:", toString(pMesh->getColumnsCount()), 0, true);
    printText(indent, "Rows count:", toString(pMesh->getRowsCount()), 0, true);
    break;
  }
  case OdTv::kPointCloud:
  {
    OdTvPointCloudDataPtr pCloud = id.openAsPointCloud();
    printText(indent, "Points count:", toString((int)pCloud->getPointsCount()), 0, true);
    printText(indent, "Points size:", toString((int)pCloud->getPointSize()), 0, true);
    break;
  }
  case OdTv::kGrid:
  {
    OdTvGridDataPtr pGrid = id.openAsGrid();
    printText(indent, "Origin:", toString(pGrid->getOrigin()), 0, true);
    printText(indent, "First point:", toString(pGrid->getFirstPoint()), 0, true);
    printText(indent, "Second point:", toString(pGrid->getSecondPoint()), 0, true);
    printText(indent, "First count:", toString(pGrid->getFirstCount()), 0, true);
    printText(indent, "Second count:", toString(pGrid->getSecondCount()), 0, true);
    printText(indent, "Crosses size:", toString((int)pGrid->getCrossesSize()), 0, true);
    if (pGrid->getStyle() == OdTvGridData::kCrosses)
      printText(indent, "Style:", OD_T("Crosses"), 0, true);
    else
      printText(indent, "Style:", OD_T("Lines"), 0, true);
    if (pGrid->getType() == OdTvGridData::kQuadratic)

      printText(indent, "Type:", OD_T("Quadratic"), 0, true);
    else
      printText(indent, "Type:", OD_T("Radial"), 0, true);
    break;
  }
  case OdTv::kColoredShape:
  {
    OdTvColoredShapeDataPtr pShape = id.openAsColoredShape();
    printText(indent, "Vertices count:", toString(pShape->getVerticesCount()), 0, true);
    printText(indent, "Faces count:", toString(pShape->getFacesCount()), 0, true);
    printText(indent, "Edges count:", toString(pShape->getEdgesCount()), 0, true);
    printText(indent, "Draw contour:", toString(pShape->getDrawContour()), 0, true);
    break;
  }
  case OdTv::kBox:
  {
    OdTvBoxDataPtr pBox = id.openAsBox();
    printText(indent, "Center:", toString(pBox->getCenterPoint()), 0, true);
    printText(indent, "Length:", toString(pBox->getLength()), 0, true);
    printText(indent, "Width:", toString(pBox->getWidth()), 0, true);
    printText(indent, "Height:", toString(pBox->getHeight()), 0, true);
    printText(indent, "Base normal:", toString(pBox->getBaseNormal()), 0, true);
    printText(indent, "Length direction:", toString(pBox->getLengthDirection()), 0, true);
    break;
  }
  case OdTv::kBrep:
  {
    OdTvGeometryDataPtr pGeom = id.openObject();
    OdTvBrepDataPtr pBrep = pGeom->getAsBrep();
    printText(indent, "Faces resolution:", toString(pBrep->getFacetRes()), 0, true);
    break;
  }
  }
}

void dumpGeometries(OdTvGeometryDataIteratorPtr pIt, int indent)
{
  if (pIt.isNull() || pIt->done())
    return;

  for (; !pIt->done(); pIt->step())
  {
    OdTvGeometryDataId id = pIt->getGeometryData();

    if (id.getType() == OdTv::kSubEntity)
    {
      OdTvEntityPtr pSubEn = id.openAsSubEntity();
      printText(indent, "SubEntity<" + pSubEn->getName() + ">");
      printEntityProperties(pSubEn, indent);
      dumpGeometries(pSubEn->getGeometryDataIterator(), indent + 1);
    }
    else
    {
      printText(indent, geomTypes[(int)id.getType()]);
      printGeometryProperties(id, indent);
    }

  }
}

void dumpLinetypes(OdTvLinetypesIteratorPtr pIt, int indent)
{
  if (pIt.isNull() || pIt->done())
    return;

  printText(indent++, "Linetypes:");

  for (; !pIt->done(); pIt->step())
  {
    OdTvLinetypePtr pLt = pIt->getLinetype().openObject();
    printText(indent, "Linetype<" + pLt->getName() + ">");
    printText(indent, "Database handle:", toString(pLt->getDatabaseHandle()), 0, true);
    printText(indent, "Description:", pLt->getDescription(), 0, true);
    printText(indent, "Scaled to fit:", toString(pLt->getScaledToFit()), 0, true);
  }
}

void dumpTextStyles(OdTvTextStylesIteratorPtr pIt, int indent)
{
  if (pIt.isNull() || pIt->done())
    return;

  printText(indent++, "TextStyles:");

  const char *alignModes[] = { "Left", "Center", "Right", "Aligned", "Middle", "Fit", "TopLeft", "TopCenter", "TopRight", "MiddleLeft"
, "MiddleCenter", "MiddleRight", "BottomLeft", "BottomCenter", "BottomRight" };

  for (; !pIt->done(); pIt->step())
  {
    OdTvTextStylePtr pTxtStl = pIt->getTextStyle().openObject();
    printText(indent, "TextStyle<" + pTxtStl->getName() + ">");
    printText(indent, "Database handle:", toString(pTxtStl->getDatabaseHandle()), 0, true);
    printText(indent, "Filename:", pTxtStl->getFileName(), 0, true);
    printText(indent, "Big font filename:", pTxtStl->getBigFontFileName(), 0, true);
    printText(indent, "Alignment mode:", alignModes[pTxtStl->getAlignmentMode()], 0, true);
    printText(indent, "Backwards:", toString(pTxtStl->getBackwards()), 0, true);
    printText(indent, "Obliquing angle:", toString(pTxtStl->getObliquingAngle()), 0, true);
    printText(indent, "Shape status:", toString(pTxtStl->getShapeStatus()), 0, true);
    printText(indent, "Upside down:", toString(pTxtStl->getUpsideDown()), 0, true);
    printText(indent, "Vertical:", toString(pTxtStl->getVertical()), 0, true);
    printText(indent, "Text size:", toString(pTxtStl->textSize()), 0, true);
    printText(indent, "Width factor:", toString(pTxtStl->widthFactor()), 0, true);
    printText(indent, "Underlined:", toString(pTxtStl->getUnderlined()), 0, true);
    printText(indent, "Overlined:", toString(pTxtStl->getOverlined()), 0, true);
    printText(indent, "Striked:", toString(pTxtStl->getStriked()), 0, true);
  }
}

void dumpRasterImages(OdTvRasterImagesIteratorPtr pIt, int indent)
{
  if (pIt.isNull() || pIt->done())
    return;

  printText(indent++, "RasterImages:");

  const char * types[] = { "File", "Binary", "PaletteBased", "Monochrome" };

  for (; !pIt->done(); pIt->step())
  {
    OdTvRasterImagePtr pImg = pIt->getRasterImage().openObject();
    printText(indent, "RasterImage<" + pImg->getSourceFileName() + ">");
    printText(indent, "Database handle:", toString(pImg->getDatabaseHandle()), 0, true);
    printText(indent, "Type:", types[pImg->getType()], 0, true);
    printText(indent, "Filepath:", pImg->getSourceFileName(), 0, true);
    printText(indent, "Loaded:", toString(pImg->isLoaded()), 0, true);
    printText(indent, "Size:", toString( OdTvVector(pImg->getSize().x, pImg->getSize().y, 0.) ), 0, true);
    printText(indent, "Inverted:", toString(pImg->getInverted()), 0, true);
  }
}

void dumpLayers(OdTvLayersIteratorPtr pIt, int indent)
{
  if (pIt.isNull() || pIt->done())
    return;

  printText(indent++, "Layers:");

  for (; !pIt->done(); pIt->step())
  {
    OdTvLayerPtr pLyr = pIt->getLayer().openObject();
    printText(indent, "Layer<" + pLyr->getName() + ">");
    printText(indent, "Database handle:", toString(pLyr->getDatabaseHandle()), 0, true);
    printText(indent, "Description:", pLyr->getDescription(), 0, true);
    printText(indent, "Color:", toString(pLyr->getColor()), 0, true);
    printText(indent, "Linetype:", toString(pLyr->getLinetype()), 0, true);
    printText(indent, "Lineweight:", toString(pLyr->getLineWeight()), 0, true);
    printText(indent, "Transparency:", toString(pLyr->getTransparency()), 0, true);
    printText(indent, "Visible:", toString(pLyr->getVisible()), 0, true);
    printText(indent, "Material:", toString(pLyr->getMaterial()), 0, true);
    printText(indent, "By block:", toString(pLyr->getIsByBlock()), 0, true);
  }
}

void dumpMaterials(OdTvMaterialsIteratorPtr pIt, int indent)
{
  if (pIt.isNull() || pIt->done())
    return;

  printText(indent++, "Materials:");

  for (; !pIt->done(); pIt->step())
  {
    OdTvMaterialPtr pMat = pIt->getMaterial().openObject();
    double dOpacityPercentage = 0.;
    OdTvMaterialMap map;
    pMat->getOpacity(dOpacityPercentage, map);

    printText(indent, "Material<" + pMat->getName() + ">");
    printText(indent, "Database handle:", toString( pMat->getDatabaseHandle() ), 0, true);
    printText(indent, "Description:", pMat->getDescription(), 0, true);
    printText(indent, "Opacity:", toString(dOpacityPercentage), 0, true);
    printText(indent, "Secondary opacity:", toString(pMat->getSecondaryOpacity()), 0, true);
    printText(indent, "Support non-texture mode:", toString(pMat->getSupportNonTextureMode()), 0, true);
  }
}

void dumpBackgrounds(OdTvGsViewBackgroundsIteratorPtr pIt, int indent)
{
  if (pIt.isNull() || pIt->done())
    return;

  printText(indent++, "Backgrounds:");

  for (; !pIt->done(); pIt->step())
  {
    OdTvGsViewBackgroundId id = pIt->getGsViewBackground();
    switch (id.getType())
    {
    case OdTvGsViewBackgroundId::kSolid:
    {
      OdTvGsViewSolidBackgroundPtr pBg = id.openAsSolidBackground();
      printText(indent, "Background<" + pBg->getName() + ">");
      printText(indent, "Database handle:", toString(pBg->getDatabaseHandle()), 0, true);
      printText(indent, "Type:", OD_T("Solid background"), 0, true);
      printText(indent, "Color:", toString(pBg->getColorSolid()), 0, true);
      break;
    }
    case OdTvGsViewBackgroundId::kGradient:
    {
      OdTvGsViewGradientBackgroundPtr pBg = id.openAsGradientBackground();
      printText(indent, "Background<" + pBg->getName() + ">");
      printText(indent, "Database handle:", toString(pBg->getDatabaseHandle()), 0, true);
      printText(indent, "Type:", OD_T("Gradient background"), 0, true);
      printText(indent, "Top color:", toString(pBg->getColorTop()), 0, true);
      printText(indent, "Middle color:", toString(pBg->getColorMiddle()), 0, true);
      printText(indent, "Bottom color:", toString(pBg->getColorBottom()), 0, true);
      printText(indent, "Height:", toString(pBg->getHeight()), 0, true);
      printText(indent, "Horizon:", toString(pBg->getHorizon()), 0, true);
      printText(indent, "Rotation:", toString(pBg->getRotation()), 0, true);
      break;
    }
    case OdTvGsViewBackgroundId::kImage:
    {
      OdTvGsViewImageBackgroundPtr pBg = id.openAsImageBackground();
      printText(indent, "Background<" + pBg->getName() + ">");
      printText(indent, "Database handle:", toString(pBg->getDatabaseHandle()), 0, true);
      printText(indent, "Type:", OD_T("Image background"), 0, true);
      printText(indent, "Image filename:", pBg->getImageFilename(), 0, true);
      printText(indent, "Fit to screen:", toString(pBg->getFitToScreen()), 0, true);
      printText(indent, "Maintain aspect ratio:", toString(pBg->getMaintainAspectRatio()), 0, true);
      printText(indent, "Use tilling:", toString(pBg->getUseTiling()), 0, true);
      printText(indent, "X offset:", toString(pBg->getXOffset()), 0, true);
      printText(indent, "Y offset:", toString(pBg->getYOffset()), 0, true);
      printText(indent, "X scale:", toString(pBg->getXScale()), 0, true);
      printText(indent, "Y scale:", toString(pBg->getYScale()), 0, true);
      break;
    }
    }
  }
}

