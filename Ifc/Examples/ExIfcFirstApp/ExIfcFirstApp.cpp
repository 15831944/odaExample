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

/**<snippet name="ifc_first_app_full_code" lang="cpp">*/
/**<snippet name="ifc_first_app_includes" lang="cpp">*/

// ODA SDK includes
#include <OdaCommon.h>
#include <StaticRxObject.h>
#include <RxDynamicModule.h>

// System includes
#include <iostream>
#include <cstdlib>

// SDAI includes
#include <daiHeaderSection.h>
#include <daiHeader/daiHeaderEntities.h>

// IFC SDK includes
#include <IfcExamplesCommon.h>
#include <IfcCore.h>

/**</snippet>*/

/**<snippet name="ifc_first_app_init_deinit_functions" lang="cpp">*/
DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();
/**</snippet>*/

//
// Define module map for statically linked modules:
//
#if !defined(_TOOLKIT_IN_DLL_)
INIT_IFC_STATIC_MODULES_NO_GEOM;
#endif

/**<snippet name="ifc_first_app_init_result_enumeration" lang="cpp">*/
enum AppResult
{
  arOk = 0,
  arIncorrectUsage,
  arFileOpenError,
  arEmptySectionHeader,
  arInvalidSchema,
  arUnsupportedSchema,
  arEmptyModel,
  arOdError,
  arUnexpectedError
};
/**</snippet>*/

struct ServiceHolder {
  OdStaticRxObject< MyServices > svcs;
  ServiceHolder() {
#if !defined(_TOOLKIT_IN_DLL_)
    ODRX_INIT_STATIC_MODULE_MAP();
#endif
    odrxInitialize(&svcs);
    odDbRootInitialize();
    odIfcInitialize(false, false);
  }
  void write(const std::string &fileName) {
    OdIfcFilePtr file = svcs.createDatabase(kScmIfc2x3);
    OdIfcModelPtr model = file->getModel(sdaiRW);
    OdDAI::ApplicationInstancePtr inst = model->createEntityInstance("ifcwall");
    model->appendEntityInstance(inst);
    file->writeFile(fileName.c_str());
  }
  ~ServiceHolder() {
    odIfcUninitialize();
    odDbRootUninitialize();
    odrxUninitialize();
  }
};

/**<snippet name="ifc_first_app_main_initial_1" lang="cpp">*/
int main(int argc, char* argv[])
{
  setlocale(LC_TIME, ""); // set current user locale (not OD_T("C")), for strftime

#if !defined(_TOOLKIT_IN_DLL_) 
  ODRX_INIT_STATIC_MODULE_MAP();
#endif

  // This works.
  ServiceHolder writer{};
  writer.write("d:/test1.ifc");
  writer.write("d:/test2.ifc");

  // This works
  ServiceHolder writer1{};
  writer1.write("d:/test3.ifc");
  ServiceHolder writer2{};
  writer2.write("d:/test4.ifc");


  // This fails for writer4
  {
    ServiceHolder writer3{};
    writer3.write("d:/test5.ifc");
  }
  
  {
    ServiceHolder writer4{};
    writer4.write("d:/test6.ifc");
  }

  return arOk;
}
  /**</snippet>*/
/**</snippet>*/
