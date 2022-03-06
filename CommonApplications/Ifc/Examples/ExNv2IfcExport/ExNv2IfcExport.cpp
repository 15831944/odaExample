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
#include "NwHostAppServices.h"
#include "StaticRxObject.h"
#include "NwDatabase.h"
#include "RxDynamicModule.h"
#include "DynamicLinker.h"
#include "ExSystemServices.h"
#include "diagnostics.h"
#include "ExPrintConsole.h"

#include "ModuleNames.h"

#include "../Exchange/Exports/Nv2Ifc/Include/IfcExport.h"
#include "../Exchange/Exports/Nv2Ifc/Include/IfcExportProperties.h"

#define STL_USING_STREAM
#define OD_HAVE_FSTREAM_FILE
#define STL_USING_STRING
#include "OdaSTL.h"

static OdString sNwDbModuleName = L"TNW_Db";
static OdString OdNw2IfcModuleName = L"Nv2Ifc";
static OdString sDwg2IfcModuleName = L"Dwg2Ifc";

/************************************************************************/
/* Define a module map for statically linked modules                    */
/************************************************************************/
#if !defined(_TOOLKIT_IN_DLL_)
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDbRootModuleObject);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(NwDbModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc4Module);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcGeomModuleImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcBrepBuilderModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdNv2IfcModuleImpl);
ODRX_BEGIN_STATIC_MODULE_MAP()
ODRX_DEFINE_STATIC_APPMODULE(OdDbRootModuleName, OdDbRootModuleObject)
ODRX_DEFINE_STATIC_APPMODULE(sNwDbModuleName, NwDbModule)
ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)
ODRX_DEFINE_STATIC_APPMODULE(OdIfc4ModuleName, OdIfc4Module)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcGeomModuleName, OdIfcGeomModuleImpl)
ODRX_DEFINE_STATIC_APPMODULE(OdIfcBrepBuilderModuleName, OdIfcBrepBuilderModule)
ODRX_DEFINE_STATIC_APPMODULE(OdNw2IfcModuleName, OdNv2IfcModuleImpl)
ODRX_END_STATIC_MODULE_MAP() 
#endif

class OdExNwSystemServices : public ExSystemServices
{
public:
  OdExNwSystemServices() {}
};

class MyNwServices : public OdExNwSystemServices, public OdNwHostAppServices
{
protected:
  ODRX_USING_HEAP_OPERATORS(OdExNwSystemServices);
};

OdResult initDictionary(const OdString& dictionaryFilePath, std::map<OdString, OdString>& dictionary)
{
  if (dictionaryFilePath.isEmpty())
    return eNoFileName;

  std::ifstream dictionaryFile(dictionaryFilePath.operator const char* ());
  std::string key, value;
  while (dictionaryFile)
  {
    if (dictionaryFile >> key)
    {
      if (dictionaryFile >> value)
      {
        dictionary[key.c_str()] = value.c_str();
      }
    }
  }
  return eOk;
}

static int LoadNwdEx(const OdString& sNvSource, const OdString& sDictionarySource, const OdString& sIfcDestination)
{
  int nRes = 0;
  odPrintConsoleString(OD_T("\nExNv2IfcExport sample program\n"));

  /********************************************************************/
  /* Create a custom Services instance.                               */
  /********************************************************************/
  OdStaticRxObject<MyNwServices> svcs;

#if !defined(_TOOLKIT_IN_DLL_) 
  ODRX_INIT_STATIC_MODULE_MAP();
#endif
  /**********************************************************************/
  /* Initialize ODA BimNv SDK                                           */
  /**********************************************************************/
  odrxInitialize(&svcs);
  ::odrxDynamicLinker()->loadModule(sNwDbModuleName, false);


  /**********************************************************************/

  try {

    //need to read file by path from sNvSource
    OdNwDatabasePtr pNwDb = svcs.readFile(sNvSource);

    NV_IFC_EXPORT::OdNv2IfcModulePtr pModule = ::odrxDynamicLinker()->loadModule(OdNw2IfcModuleName, false);
    auto pExport = pModule->create();
    std::map<OdString, OdString> dictionary;
    initDictionary(sDictionarySource, dictionary);
    NV_IFC_EXPORT::OdIfcExportPropertiesPtr pProperties = pExport->properties();
    pProperties->put_SchemaVersion((OdInt16)kScmIfc4);
    pProperties->put_Database(pNwDb);
    pProperties->put_IfcFilePath(sIfcDestination);
    pProperties->put_Dictionary(createRxWrapper(dictionary));
    pExport->doExport();
  }
  catch (const OdError& e) {
    nRes++;
    odPrintConsoleString(L"\nException Caught: %ls\n", e.description().c_str());
  }
  catch (...)
  {
    nRes += 2;
    odPrintConsoleString(L"\nUnknown Exception Caught\n");
  }

  /**********************************************************************/
  /* Uninitialize Initialize ODA BimNv SDK                              */
  /**********************************************************************/

  ::odrxDynamicLinker()->unloadUnreferenced();
  ::odrxUninitialize();

  return nRes;
}
////////////////////////////////////////////////////////////////////////////////////

static void MyAssert(const char* expr, const char* fileName, int nLine)
{
  OdString sMsg, sExpr(expr), sFileName(fileName);
  sMsg.format(L"assertion expression: \"%ls\"\nfile: \"%ls\"\nline: %d", sExpr.c_str(), sFileName.c_str(), nLine);
  odPrintConsoleString(sMsg.c_str());
}

static bool MyCheckAssertGroup(const char* pGroup)
{
  return !pGroup || !*pGroup; // asserts of base group are enabled only (default)
                              //return true; // asserts of all groups are enabled
}

#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  /**********************************************************************/
  /* Set customized assert function                                     */
  /**********************************************************************/
  odSetAssertFunc(MyAssert);
  odSetCheckAssertGroupFunc(MyCheckAssertGroup);

  /**********************************************************************/
  /* Parse Command Line strings                                         */
  /**********************************************************************/

  bool bNothingToConvert = argc < 3 ? true : false;
  int nRes = 0;

  if (bNothingToConvert)
    odPrintConsoleString(L"Use as: ExNv2IfcExport.exe path_to_nwd_file.nwd path_to_ifc_file.ifc path_to_dictionary_file.txt\n");
  else
  {
    OdString sNvFile = argv[1];
    OdString sIfcFile = argv[2];
    OdString sDictionaryFile;
    if (argc > 3)
      sDictionaryFile = argv[3];
    nRes = LoadNwdEx(sNvFile, sDictionaryFile, sIfcFile);
  }

  return nRes;
}
