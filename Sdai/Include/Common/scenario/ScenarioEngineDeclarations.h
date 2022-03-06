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

// ScenarioEnginesDeclarations.h
//

#ifndef _SCENARIO_ENGINE_DECLARATIONS_H_
#define _SCENARIO_ENGINE_DECLARATIONS_H_

DBROOT_EXPORT void odDbRootInitialize();
DBROOT_EXPORT void odDbRootUninitialize();

#ifdef OD_BUILD_EXE_AS_LIBRARY
  #define test_od_main runTG_ScenarioEngine 
  #define test_arg_char char
#else
#if defined(OD_USE_WMAIN)
  #define test_od_main wmain
  #define test_arg_char wchar_t
#else
  #define test_od_main main
  #define test_arg_char char
#endif
#endif

#endif
