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
/* This console application reads a DWG file and dumps its contents     */
/* to the console.                                                      */
/************************************************************************/

#define ODCDADUMPEX_S "OdCdaDumpEx"

#include "OdaCommon.h"

static const char cUsage[] =
{
  ODCDADUMPEX_S " sample program. Copyright (C) " TD_COPYRIGHT_START_YEAR_S  TD_COPYRIGHT_END_S "\n"
  "Usage: " ODCDADUMPEX_S " filename [CACHE]\n"
  "  Output XML file is written to the same directory as the input file.\n"
  "    CACHE - dump properties cache\n"
  "\nPress ENTER to continue...\n"
};


#include "diagnostics.h"
#include "DbDatabase.h"
#include "DbEntity.h"
#include "DbDimAssoc.h"

#include "OdCharMapper.h"
#include "RxObjectImpl.h"

#include "ExSystemServices.h"
#include "ExHostAppServices.h"
#include "OdFileBuf.h"
#include "RxDynamicModule.h"
#include "FdField.h"
#include "XRefMan.h"

#define STL_USING_IOSTREAM
#include "OdaSTL.h"
#define  STD(a)  std:: a


#ifdef OD_HAVE_CONSOLE_H_FILE
#include <console.h>
#endif

/************************************************************************/
/* Compile password support for R18 Drawings                            */
/************************************************************************/

#define ODCDADUMPEX_STR L"OdCdaDumpEx"


void DumpToXML(const OdRxObject* pDb, const OdString& file_name, const bool create_properties_cache,
  const bool class_dependent_hierarchy = false, const bool class_dependent_property = false);

/************************************************************************/
/* Freeze a local time                                                  */
/************************************************************************/
typedef void (*PgetLocalTime)( OdTimeStamp& ts );
extern FIRSTDLL_EXPORT_STATIC PgetLocalTime g_pLocalTimeFunc; // global variable defined in TD_Root
static void getLocalTime(OdTimeStamp &localTime)
{
  localTime.setDate(12, 22, 2009);
  localTime.setTime(18, 0, 0, 0);
}

/************************************************************************/
/* Define a Custom Services class.                                      */
/*                                                                      */
/* Combines the platform dependent functionality of                     */
/* ExSystemServices and ExHostAppServices                               */ 
/************************************************************************/
class MyServices : public ExSystemServices, public ExHostAppServices
{
protected:
  ODRX_USING_HEAP_OPERATORS(ExSystemServices);

private:

#ifdef _MSC_VER

  /**********************************************************************/
  /* Define a console interface for password support.                   */
  /**********************************************************************/
  bool getPassword(const OdString& dwgName, bool /*isXref*/, OdPassword& password)
  {
    odPrintConsoleString(L"Enter password to open drawing: %ls\n", dwgName.c_str());
    wchar_t pwdBuff[_MAX_PATH] = {0};
    STD(wcin).get(pwdBuff, L'\n').get();
#ifndef _WINRT
    ::CharUpperW(pwdBuff);
#else
    ::Od_struprW(pwdBuff);
#endif
    password = pwdBuff;
    return !password.isEmpty();
  }
#endif
};

/************************************************************************/
/* Define a module map for statically linked modules:                   */
/************************************************************************/
#ifndef _TOOLKIT_IN_DLL_

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRecomputeDimBlockModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExFieldEvaluatorModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TD_3DSolidHistoryModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TD_DynBlocksModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(DbCryptModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTfModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDbPropertiesModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxPropertiesModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxCommonDataAccessModule);

ODRX_BEGIN_STATIC_MODULE_MAP()
  ODRX_DEFINE_STATIC_APPLICATION(OdModelerGeometryModuleName,   ModelerModule)
  ODRX_DEFINE_STATIC_APPLICATION(OdRecomputeDimBlockModuleName, OdRecomputeDimBlockModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdDynBlocksModuleName, TD_DynBlocksModule)
  ODRX_DEFINE_STATIC_APPMODULE(OdExFieldEvaluatorModuleName, ExFieldEvaluatorModule)
  ODRX_DEFINE_STATIC_APPMODULE(Od3DSolidHistoryTxModuleName, TD_3DSolidHistoryModule)
  ODRX_DEFINE_STATIC_APPMODULE(DbCryptModuleName,            DbCryptModule)
  ODRX_DEFINE_STATIC_APPMODULE(TfModuleName,                    OdTfModule)
  ODRX_DEFINE_STATIC_APPMODULE(L"RxProperties", OdRxPropertiesModule)
  ODRX_DEFINE_STATIC_APPMODULE(L"DbProperties", OdDbPropertiesModule)
  ODRX_DEFINE_STATIC_APPMODULE(RxCommonDataAccessModuleName, OdRxCommonDataAccessModule)

ODRX_END_STATIC_MODULE_MAP()

#endif

/********************************************************************************/
/* Define Assert function to not crash Debug application if assertion is fired. */
/********************************************************************************/
static void MyAssert(const char* expression, const char* fileName, int nLineNo)
{
  OdString message;
  message.format(L"/!\\ Assertion failed: \"%ls\" in file: \"%ls\", line: %d\n", OdString(expression).c_str(), OdString(fileName).c_str(), nLineNo);
  odPrintConsoleString(message);
}

/********************************************************************************/
/* Define Trace function to dump trace messages in Debug configuration.         */
/********************************************************************************/
void MyTraceFn(const OdChar* debugString)
{
  odPrintConsoleString(L"Trace: %ls\n", debugString);
}
/********************************************************************************/
/* Define Ge error handler to not crash OdReadEx application and dump errors.   */
/********************************************************************************/
static void MyGeError(OdResult res)
{
  OdString message;
  message.format(L"\n!!! Ge error: \"%ls\"\n", OdError(res).description().c_str());
  odPrintConsoleString(message);
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
#ifndef _TOOLKIT_IN_DLL_
    ODRX_INIT_STATIC_MODULE_MAP();
#endif

    bool dumpCache = false;

    for (int i = 2; i < argc; ++i)
    {
      /**********************************************************************/
      /* Need to dump the cache                                                */
      /**********************************************************************/
      if (!OdString(argv[i]).iCompare(L"CACHE"))
        dumpCache = true;
    }

    /********************************************************************/
    /* Create a custom Services instance.                               */
    /********************************************************************/
    OdStaticRxObject<MyServices> svcs;

    /**********************************************************************/
    /* Overload OdTimeStamp::getLocalTime internal implementation         */
    /**********************************************************************/
    g_pLocalTimeFunc = getLocalTime;

    /**********************************************************************/
    /* Set customized assert function                                     */
    /**********************************************************************/
    odSetAssertFunc(MyAssert);

    /**********************************************************************/
    /* Set customized Ge exception processing                             */
    /**********************************************************************/
    OdGeContext::gErrorFunc = MyGeError;

    /********************************************************************/
    /* Initialize the Drawings SDK.                                     */
    /********************************************************************/
    odInitialize(&svcs);
    /********************************************************************/
    /* Initialize Encription/Decription                      */
    /********************************************************************/
    ::odrxDynamicLinker()->loadModule(DbCryptModuleName);
	
#ifndef _MSC_VER

    /********************************************************************/
    /* Find the data file and and initialize the character mapper       */
    /********************************************************************/
    odPrintConsoleString(L"Initializing OdCharMapper: ");
    OdString iniFile = svcs.findFile(OD_T("adinit.dat"));
    if (!iniFile.isEmpty()) {
      OdCharMapper::initialize(iniFile);
      odPrintConsoleString(L"ok\n");
    } else
      odPrintConsoleString(L"\"adinit.dat\" is not found. String CP conversion is not supported in this run.\n");
#endif

    /********************************************************************/
    /* Display the Product and Version that created the executable      */
    /********************************************************************/
    odPrintConsoleString(L"\n" ODCDADUMPEX_STR L" developed using %ls ver %ls\n",
      svcs.product().c_str(), svcs.versionString().c_str());

    bool bSuccess = true;
    try 
    {
      ::odrxDynamicLinker()->loadModule(OdExFieldEvaluatorModuleName, false);
      ::odrxDynamicLinker()->loadModule(Od3DSolidHistoryTxModuleName, false);
      ::odrxDynamicLinker()->loadModule(OdDynBlocksModuleName, false);
      
      /****************************************************************/
      /* Load Common Data Access (CDA) modules:                       */
      /* RxPropertiesModule       - main RxProperties module          */
      /* DbPropertiesModule       - DWG properties module             */
      /* RxCommonDataAccessModule - CDA Tree generation module        */
      /****************************************************************/
      ::odrxDynamicLinker()->loadModule(RxPropertiesModuleName, false);
      ::odrxDynamicLinker()->loadModule(DbPropertiesModuleName, false);
      ::odrxDynamicLinker()->loadModule(RxCommonDataAccessModuleName, false);

      /******************************************************************/
      /* Create a database and load the drawing into it.                */
      /* readFile() allways should return loaded database.              */
      /* It throws OdError() exception if an error occurred.            */
      /* Specified arguments are as followed:                           */
      /*     filename, allowCPConversion, partialLoad, openMode         */      
      /******************************************************************/
      OdString file_name(argv[1]); // for UNIX UNICODE support
      OdDbDatabasePtr pDb = svcs.readFile(file_name.c_str());
     
      /****************************************************************/
      /* Load external referenced databases                           */
      /****************************************************************/
      OdDbXRefMan::loadAll(pDb);

      oddbEvaluateFields(pDb, OdDbField::kOpen);

      /****************************************************************/
      /* Display the File Name and Version                            */
      /****************************************************************/
      odPrintConsoleString(L"\nFile Name:   \"%ls\"", pDb->getFilename().c_str());
      odPrintConsoleString(L"\nFile Version: %d\n", pDb->originalFileVersion()); 

      /****************************************************************/
      /* Dump CDA Tree and properties to XML                          */
      /****************************************************************/
      DumpToXML(pDb, file_name, dumpCache);

    }
    /********************************************************************/
    /* Display the error                                                */
    /********************************************************************/
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
    /* Uninitialize the Drawings SDK                                    */
    /********************************************************************/
    
    try
    {
      odUninitialize();
      odPrintConsoleString(L"ODA uninitialized\n");
      if (bSuccess)
        odPrintConsoleString(ODCDADUMPEX_STR L" Finished Successfully\n");
    }
    catch(OdError& e)
    {
      odPrintConsoleString(L"odUninitialize() failed\n");
      odPrintConsoleString(L"OdError description:\n%ls\n", e.description().c_str());
    }
    catch(...)
    {
      odPrintConsoleString(L"odUninitialize() failed\n");
    }
    
    return 0;
  }
}
