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



#ifndef OD_LOADMODULEINTERNAL_DEFINED
#define OD_LOADMODULEINTERNAL_DEFINED

#include "RxDynamicModule.h"
#include "RxSystemServices.h"

FIRSTDLL_EXPORT OdRxModule* odrxLoadModuleInternal(const OdString& szName, StaticModuleEntryPoint ep);


#if defined(_TOOLKIT_IN_DLL_)

inline OdRxModule* odrxLoadGsModuleInternal()
{
  return odrxLoadModuleInternal(OdGsModuleName, 0);
}

inline OdRxModule* odrxLoadDbCoreModuleInternal()
{
  OdRxModule* pDbModule = odrxLoadModuleInternal(OdDbCoreModuleName, 0);
  if (!pDbModule)
  {
    throw OdError_FileNotFound(OdDbCoreModuleName);
  }
  return pDbModule;
}

inline OdRxModule* odrxLoadGiModuleInternal()
{
  return odrxLoadModuleInternal(OdGiModuleName, 0);
}

#else //#if defined(_TOOLKIT_IN_DLL_)

ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDbCoreModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdGiModuleObject);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdGsModuleObject);

inline OdRxModule* odrxLoadGsModuleInternal()
{
  return odrxLoadModuleInternal(OdGsModuleName, ODRX_STATIC_MODULE_ENTRY_POINT(OdGsModuleObject));
}

inline OdRxModule* odrxLoadDbCoreModuleInternal()
{
  return odrxLoadModuleInternal(OdDbCoreModuleName, ODRX_STATIC_MODULE_ENTRY_POINT(OdDbCoreModule));
}

inline OdRxModule* odrxLoadGiModuleInternal()
{
  return odrxLoadModuleInternal(OdGiModuleName, ODRX_STATIC_MODULE_ENTRY_POINT(OdGiModuleObject));
}

#endif //#if defined(_TOOLKIT_IN_DLL_)


#endif  // #ifndef OD_LOADMODULEINTERNAL_DEFINED

