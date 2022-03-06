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

#ifndef _OD_BIM2PRC_EXPORT_MODULE_INCLUDED_
#define _OD_BIM2PRC_EXPORT_MODULE_INCLUDED_

#include "PrcExportDef.h"
#include "RxDynamicModule.h"
#include "Pdf2PrcExportParams.h"

/** \details
  The class implements a module for exporting a BimRv database to the PRC format.
 <group PRC_Export_Import_Classes>
*/
class OdPrcEXPORT_DLL OdBim2PrcExportModule : public OdRxModule
{
protected:
  /** \details
    Initializes the PRC export module.
  */
  void initApp();

  /** \details
    Uninitializes the PRC export module.
  */
  void uninitApp();
};

SMARTPTR(OdBim2PrcExportModule);

#endif //_OD_BIM2PRC_EXPORT_MODULE_INCLUDED_
