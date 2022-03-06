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
#include "OdPerfTimer.h"

#include "IfcCore.h"
#include "IfcExamplesCommon.h"

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

//
// Define module map for statically linked modules:
//
#if !defined(_TOOLKIT_IN_DLL_)
  INIT_IFC_STATIC_MODULES_NO_GEOM;
#endif

#include <iostream>
#include <cstdlib>

namespace
{
  const OdString  logErrorKeyword = "readErrorLogIsOn";

  const OdString  actionNameErrorEvent      = "[ERROR EVENT             ]";
  const OdString  actionNameBlank           = "[                        ]";
  const OdString  actionNameErrorEventList  = "[ERROR EVENT LIST        ]";
  const OdString  actionNameSessionEventRec = "[SESSION EVENT RECORDING ]";
  const OdString  actionNameEventParamRead  = "[EVENT PARAM READ        ]";
  /*const OdString  actionNameEventError = "[ERROR EVENT]";
  const OdString  actionNameEventError = "[ERROR EVENT]";
  const OdString  actionNameEventError = "[ERROR EVENT]";
  const OdString  actionNameEventError = "[ERROR EVENT]";*/


  void errorEventListOutput(OdDAI::List<OdDAI::ErrorEventPtr>* errorsList)
  {
    ODA_ASSERT(errorsList);

    if (!errorsList)
    {
      return;
    }

    const OdArray<OdDAI::ErrorEventPtr>& errorsArray = errorsList->getArray();
    if (errorsArray.isEmpty())
    {
      odPrintConsoleString(L"%s - there is not any error events.\n", actionNameErrorEventList.c_str());
    }


    for (auto& error : errorsArray)
    {
      OdString    description(error->description());
      description.remove('\n');

      odPrintConsoleString(L"\n%s - error event detected, see information below\n%s     Error Id: %d (%hs) \n%s     Description: \'%s\' \n%s     Function: \'%s\'",
                            actionNameErrorEvent.c_str(),
                            actionNameBlank.c_str(),
                            error->error(),
                            OdDAI::errorCodeToStr(error->error()),
                            actionNameBlank.c_str(),
                            description.c_str(),
                            actionNameBlank.c_str(),
                            OdString(error->functionId()).c_str());
    }

    odPrintConsoleString(L"\n");
  }
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
  odPrintConsoleString(L"\nOdIfcReadFile developed using %ls ver %ls", 
    svcs.product().c_str(), svcs.versionString().c_str());

  /**********************************************************************/
  /* Parse Command Line inputs                                          */
  /**********************************************************************/
  bool bInvalidArgs = (argc != 2 && argc != 3 && argc != 4);
  if (bInvalidArgs)
  {
    bInvalidArgs = true;
    nRes  = 1;
  }
  
  if (bInvalidArgs)    
  {
    odPrintConsoleString(L"\n\nusage: ExIfcReadFile <in filename> [out filename]");
    odPrintConsoleString(L"\n<filename> - input .ifc or .ifczip file\n");
    odPrintConsoleString(L"\n[out filename] - optional output .ifc or .ifczip file\n");
    odPrintConsoleString(L"\n[%s] - optional turn on error log during file reading\n", logErrorKeyword.c_str());
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
    OdString ifcInFileName(argv[1]);
    OdString ifcOutFileName;

    bool  readErrorLogOn = false;
    
    for (int argIndex = 2; argIndex < 3; ++argIndex)
    {
      if (argc > argIndex)
      {
        if (logErrorKeyword == argv[argIndex])
        {
          readErrorLogOn = true;
        }
        else
        {
          ifcOutFileName = argv[argIndex];
        }
      }
    }

    OdIfcFilePtr pDatabase;
    
    {
      OdPerfTimerWrapper timerWrapper;
      timerWrapper.getTimer()->start();
      OdResult res;

      pDatabase = svcs.createDatabase();

      OdDAI::SessionPtr session = readErrorLogOn ? oddaiSession() : OdDAI::SessionPtr();
      OdDAI::List<OdDAI::ErrorEventPtr>* errorsList = nullptr;

      if (!session.isNull())
      {
        odPrintConsoleString(L"\n%s - error events recording is active: \n", actionNameEventParamRead.c_str());
        session->startEventRecording();
        odPrintConsoleString(L"%s - is turned on \n", actionNameSessionEventRec.c_str());

        if (session->getAttrCaseInsensitive("errors") >> errorsList && errorsList)
        {
          odPrintConsoleString(L"%s - the list was get successfuly. Lets check this list on errors before read.\n", actionNameErrorEventList.c_str());
          errorEventListOutput(errorsList);
        }
        else
        {
          odPrintConsoleString(L"%s - cant get list. Error events recording is not available.\n", actionNameErrorEventList.c_str());
        }
      }

      res = pDatabase->readFile(ifcInFileName);

      if (errorsList)
      {
        odPrintConsoleString(L"%s - the file reading was finished. Lets check for new errors after read:\n", actionNameErrorEventList.c_str());
        errorEventListOutput(errorsList);
      }
      
      timerWrapper.getTimer()->stop();
      if (res == eOk)
      {
        odPrintConsoleString(L"\nFile opened successfully.");
      }
      else
      {
        odPrintConsoleString(L"\nFile open error.");
      }
      odPrintConsoleString(L"\nOpening time: %d msec", timerWrapper.getTimer()->countedMSec());
    }

    if (!ifcOutFileName.isEmpty())
    {
      OdPerfTimerWrapper timerWrapper;
      timerWrapper.getTimer()->start();
      OdResult res = pDatabase->writeFile(ifcOutFileName);
      timerWrapper.getTimer()->stop();
      if (res == eOk)
      {
        odPrintConsoleString(L"\nFile writed successfully.");
      }
      else
      {
        odPrintConsoleString(L"\nFile writing error.");
      }
      odPrintConsoleString(L"\nWriting time: %d msec", timerWrapper.getTimer()->countedMSec());
    }

    odPrintConsoleString(L"\nPress any key.\n");
    getchar();
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
