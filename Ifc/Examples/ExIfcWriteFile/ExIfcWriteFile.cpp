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
#include "MemoryStream.h"

#include "IfcExamplesCommon.h"
#include "ModelCompare.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

//
// Define module map for statically linked modules:
//
#if !defined(_TOOLKIT_IN_DLL_) 
  using namespace OdIfc;                                                             \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdSDAIModule);                              \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfcCoreModule);                           \
  ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdIfc2x3Module);                            \
  ODRX_BEGIN_STATIC_MODULE_MAP()                                                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdSDAIModuleName, OdSDAIModule)                     \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfcCoreModuleName, OdIfcCoreModule)               \
    ODRX_DEFINE_STATIC_APPMODULE(OdIfc2x3ModuleName, OdIfc2x3Module)                 \
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
  odPrintConsoleString(L"\nOdIfcReadFile developed using %ls ver %ls", 
    svcs.product().c_str(), svcs.versionString().c_str());

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  bool bInvalidArgs = (argc != 3);
  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }

  if (bInvalidArgs)    
  {
    odPrintConsoleString(L"\n\nusage: OdIfcWriteFile <file_read_from> <file_write_to>");
    odPrintConsoleString(L"\n<file_read_from> - input .ifc file to read from\n");
    odPrintConsoleString(L"\n<file_write_to> - output .ifc file to write to\n");
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
  odIfcInitialize(false /* No CDA */, false /* No geometry calculation needed */);

  try
  {
    OdString ifcFileNameFrom(argv[1]);
    OdString ifcFileNameTo(argv[2]);

    OdIfcFilePtr pFileOrigin = svcs.createDatabase();
    OdResult res = pFileOrigin->readFile(ifcFileNameFrom);

    if (pFileOrigin.isNull())
    {
      odPrintConsoleString(L"\nRead file error.");
    }

    if (pFileOrigin->writeFile(ifcFileNameTo) != eOk)
    {
      odPrintConsoleString(L"\nWrite file error.");
    }

    OdStreamBufPtr fileStreamCopy = odrxSystemServices()->createFile(ifcFileNameTo, Oda::kFileRead);

    if (fileStreamCopy.isNull())
    {
      odPrintConsoleString(L"\nCannot create a stream copy.");
    }

    OdMemoryStreamPtr memoryStreamCopy = OdMemoryStream::createNew();
    fileStreamCopy->rewind();
    fileStreamCopy->copyDataTo(memoryStreamCopy);

    OdIfcFilePtr pFileCopy = svcs.createDatabase();
    pFileCopy->readFile(fileStreamCopy);

    bool compareResult = true;

    odPrintConsoleString(L"\n\n[begin] header compare.");

    if (!CompareHeaders(pFileOrigin->getHeaderSection(), pFileCopy->getHeaderSection()))
    {
      odPrintConsoleString(L"\nHeader section data has a difference.");
      compareResult = false;
    }
    else
    {
      odPrintConsoleString(L"\n[end] header compare.");
      odPrintConsoleString(L"\n\n[begin] models compare.");

      OdIfcModelPtr pModelOrig = pFileOrigin->getModel();
      OdIfcModelPtr pModelCopy = pFileCopy->getModel();

      if (!CompareModels(pModelOrig, pModelCopy))
      {
        odPrintConsoleString(L"\nEntity section data has a difference.");
        compareResult = false;
      }
      else
      {
        odPrintConsoleString(L"\n[end] models compare.");
      }
    }
    
    if (compareResult)
    {
      odPrintConsoleString(L"\n\n[result] Rewrited file is equal to original.\n");
    }
    else
    {
      odPrintConsoleString(L"\n\n[result] Rewrited file is NOT equal to original.\n");
    }
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

  /**********************************************************************/
  /* Uninitialize IfcCore                                               */
  /**********************************************************************/
  odIfcUninitialize();

  odDbRootUninitialize();
  
  /**********************************************************************/
  /* Uninitialize ODA SDK                                               */
  /**********************************************************************/
  odrxUninitialize();
  return nRes;
}
