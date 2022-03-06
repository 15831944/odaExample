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

// sdai_ScenarioEnginesMain.cpp : Defines the entry point for the console application.
//

#ifndef _SCENARIO_ENGINE_INCLUDES_H_
#define _SCENARIO_ENGINE_INCLUDES_H_

#include <OdaCommon.h>
#include "StaticRxObject.h"
#include "RxInit.h"
#include "RxObjectImpl.h"
#include "RxDynamicModule.h"
#include "DynamicLinker.h"

#include "diagnostics.h"
#if defined(_WIN32)
#include <tchar.h>
#endif

#ifdef OD_HAVE_CONSOLE_H_FILE
#include <console.h>
#endif

#if defined (_MSC_VER) && (_MSC_VER > 1300)
#include <psapi.h>
#pragma comment(linker, "/DEFAULTLIB:psapi.lib")
#endif

#endif
