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

#include "IfcExamplesCommon.h"
#include "IfcCore.h"

#include "OdaCommon.h"
#include "StaticRxObject.h"
#include "RxDynamicModule.h"

#include "ExIfcTutorial_01.h"
#include "ExIfcTutorial_02.h"
#include "ExIfcTutorial_03.h"
#include "ExIfcTutorial_05.h"

#include "DerivedAttributes.h"

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

using namespace OdIfc;

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
  odPrintConsoleString(L"\nExIfcTutorials developed using %ls ver %ls", 
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
    odPrintConsoleString(L"\n\nusage: ExIfcTutorials <tutorial_number> <filename>");
    odPrintConsoleString(L"\n<tutorial_number> - number of tutorial\n");
    odPrintConsoleString(L"\n<filename> - input/output .ifc file\n");
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
    int tutorNum = atoi(OdString(argv[1]));
    switch (tutorNum)
    {
    case 1:
      // Tutorial 1: Fill model with IfcColumn and its IfcExtrudedAreaSolid representation.
      nRes = Tutorial_01(argc, argv, svcs);
      break;
    case 2:
      // Tutorial 2: Work with IfcProducts and IfcPropertySet.
      nRes = Tutorial_02(argc, argv, svcs);
      break;
    case 3:
      // Tutorial 3: Early-bound creation of IfcIndexedPolycurve.
      nRes = Tutorial_03(argc, argv, svcs);
    break;
    case 4:
      // Tutorial 4: Derived attributes/Where rules evaluation
      nRes = DerivedAttributes(argc, argv, svcs);
    break;
    case 5:
      // Tutorial 5: Print IFC file dump
      nRes = Tutorial_05(argc, argv, svcs);
    break;
    default:
      odPrintConsoleString(L"Invalid tutorial number");
      return -1;
    }
    std::cout << "\nPress any key.";
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
