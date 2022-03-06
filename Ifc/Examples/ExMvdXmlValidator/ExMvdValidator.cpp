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
/* Simple application to load a mvdXML file and validate IFC files      */
/************************************************************************/

#include "OdaCommon.h"
#include "StaticRxObject.h"
#include "IfcExamplesCommon.h"
#include "IfcCore.h"
#include "ExIfcHostAppServices.h"
#include "RxVariantValue.h"
#include "ExPrintConsole.h"

#include "../Extensions/ExServices/ExMvdXmlHostAppServices.h"
#include "MvdXmlAuditInfo.h"

using namespace OdMvdXml;

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

class MvdXmlServices : public ExSystemServices, public OdExMvdXmlHostAppServices
{
protected:
  ODRX_USING_HEAP_OPERATORS(ExSystemServices);
  OdGsDevicePtr gsBitmapDevice(OdRxObject* /*pViewObj*/ = NULL,
    OdDbBaseDatabase* /*pDb*/ = NULL,
    OdUInt32 /*flags*/ = 0)
  {
    try
    {
      OdGsModulePtr pGsModule = ::odrxDynamicLinker()->loadModule(OdWinBitmapModuleName);
      return pGsModule->createBitmapDevice();
    }
    catch (const OdError&)
    {
}
    return OdGsDevicePtr();
  }

public:

  virtual OdString findFile(
    const OdString& filename,
    OdDbBaseDatabase* pDb,
    FindFileHint hint)
  {
    return filename;
  }

  virtual const OdString program()
  {
    return OdString::kEmpty;
  }

  virtual const OdString product()
  {
    return OdString::kEmpty;
  }

  virtual const OdString companyName()
  {
    return OdString::kEmpty;
  }

  virtual bool ttfFileNameByDescriptor(
    const OdTtfDescriptor& description,
    OdString& filename)
  {
    return false;
  }

  virtual OdString getAlternateFontName() const
  {
    return OdString::kEmpty;
  }

  virtual OdString getFontMapFileName() const
  {
    return OdString::kEmpty;
  }

  virtual OdString getPreferableFont(
    const OdString& fontName,
    OdFontType fontType)
  {
    return OdString::kEmpty;
  }

  virtual OdString getSubstituteFont(
    const OdString& fontName,
    OdFontType fontType)
  {
    return OdString::kEmpty;
  }
};

void printAudit(OdMvdXmlAuditInfo& audit)
{
  if (audit.numOfErrors() > 0)
  {
    const OdAnsiStringArray& arr = audit.getErrors();
    OdAnsiStringArray::const_iterator pIt, pEnd = arr.end();
    for (pIt = arr.begin(); pIt != pEnd; ++pIt)
    {
      odPrintConsoleString(OdString(*pIt));
      odPrintConsoleString(L"\n");
    }
  }
  if (audit.numOfWarnings() > 0)
  {
    const OdAnsiStringArray& arr = audit.getWarnings();
    OdAnsiStringArray::const_iterator pIt, pEnd = arr.end();
    for (pIt = arr.begin(); pIt != pEnd; ++pIt)
    {
      odPrintConsoleString(OdString(*pIt));
    }
  }
}

//
// Define module map for statically linked modules:
//
#if !defined(_TOOLKIT_IN_DLL_)
  #include "RxDynamicModule.h"

  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);                          
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdMvdXmlModule);
  ODRX_BEGIN_STATIC_MODULE_MAP()
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)                 
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)
    ODRX_DEFINE_STATIC_APPMODULE(OdMvdXmlModuleName, OdMvdXmlModule)
    ODRX_END_STATIC_MODULE_MAP()
#endif

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

#if defined(OD_USE_WMAIN)
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  int   nRes = 0;               // Return value for the function
  bool  disableOutput = false;  // Disable output if it is indicated in command line

#ifdef OD_HAVE_CCOMMAND_FUNC
  argc = ccommand(&argv);
#endif

  /********************************************************************/
  /* Create a Services object                                         */
  /********************************************************************/
  OdStaticRxObject<MyServices> svcs;
  OdStaticRxObject<MvdXmlServices> mvd_svcs;

  /**********************************************************************/
  /* Display the Product and Version that created the executable        */
  /**********************************************************************/
  odPrintConsoleString(L"\nExMvdValidator sample program. Copyright (c) 2022, Open Design Alliance\n");

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  bool bInvalidArgs = (argc < 3);
  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }

  if (bInvalidArgs)    
  {
    odPrintConsoleString(L"\n\tusage: ExMvdValidator <mvd file> <ifc file> [-DO]");
    odPrintConsoleString(L"\n\t-DO disables progress meter output.\n");
    return nRes;
  }

  /**********************************************************************/
  /* Disable progress meter                                             */
  /**********************************************************************/
  if (argc >= 4)
  {
    OdString argv2(argv[3]);
    if (!odStrICmp(argv2, OD_T("-DO")))
    {
      disableOutput = true;
    }
  }

  OdString srcFileName = argv[1];
  OdString dstFileName = argv[2];

  /************************************************************************/
  /* Disable/Enable progress meter                                       */
  /************************************************************************/
  svcs.disableProgressMeterOutput( disableOutput );
  mvd_svcs.disableProgressMeterOutput(disableOutput);

#if !defined(_TOOLKIT_IN_DLL_)
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  /**********************************************************************/
  /* Initialize ODA SDK                                                 */
  /**********************************************************************/
  odrxInitialize(&svcs);
  odrxInitialize(&mvd_svcs);

  odDbRootInitialize();

  /**********************************************************************/
  /* Initialize IfcCore                                                 */
  /**********************************************************************/

  odIfcInitialize(false, false);
  ::odrxDynamicLinker()->loadModule(OdMvdXmlModuleName);

  try
  {
    OdResult res;
    OdString mvdFileName(argv[1]);
    OdMvdXml::OdMvdXmlProcessorPtr pValidator = mvd_svcs.getProcessor(kValidator);
    if (pValidator.isNull())
      throw OdError(eNullPtr);

    OdMvdXmlAuditInfo audit;

    res = pValidator->readFile(mvdFileName, &audit, true);
    printAudit(audit);
    if (res)
    {
      throw OdError(res);
    }

    OdString ifcFileName(argv[2]);
    OdIfcFilePtr pDatabase = svcs.createDatabase();
    
    if (res = pDatabase->readFile(ifcFileName))
    {
      throw OdError( res );
    }
/*    if (res = pDatabase->composeEntities())
    {
      if (res == eFileInternalErr) {
        throw OdError( eFileInternalErr );
      }
      if (res == eNullPtr) {
        throw OdError( eNullPtr );
      }
    }*/

    audit.clear();
    res = pValidator->process(pDatabase, &audit);
    printAudit(audit);
    if (res)
    {
      throw OdError(res);
    }
  }
  catch (OdError& e)
  {
    odPrintConsoleString(L"\n\nError: %ls", e.description().c_str());
    nRes = -1;
  }
  catch (...)
  {
    odPrintConsoleString(L"\n\nUnexpected error.");
    nRes = -1;
    throw;
  }

  /**********************************************************************/
  /* Uninitialize IfcCore                                               */
  /**********************************************************************/
  ::odrxDynamicLinker()->unloadModule(OdMvdXmlModuleName);
  odIfcUninitialize();

  odDbRootUninitialize();
  /**********************************************************************/
  /* Uninitialize ODA SDK                                               */
  /**********************************************************************/
  odrxUninitialize();

  return nRes;
}
