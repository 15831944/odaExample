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

// SampleCommand.cpp: implementation of the SampleCommand function.
//
//////////////////////////////////////////////////////////////////////

#include "PrcCommon.h"
#include "Ed/EdCommandContext.h"
#include "DbAux/PrcCommandContext.h"
#include "MemoryStream.h"
#include "PrcWithTDExamplesCommon.h"
#include "OdPrcCreateStart.h"

#define ODPRCCREATECASE(a, b, c, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14) void c(OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pHostTD, OdPrcHostAppServices &pHostPrc);
#include "ExampleCases.h"

#define ODPRCCREATECASE(a, b, c, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14) \
  void _##a##_func(OdEdCommandContext* pCmdCtx)\
{\
  MyServices svcs;\
  {\
    OdPrcCommandContextPtr pDbCmdCtx(pCmdCtx);\
    OdPrcFilePtr pDb = pDbCmdCtx->database();\
    OdStreamBufPtr pPrcStream = OdMemoryStream::createNew();\
    odrxDynamicLinker()->loadModule(OdDbRootModuleName, false);\
    odrxDynamicLinker()->loadModule(OdDbModuleName, false);\
    pDb->initialize(true);\
    c(pPrcStream, k##a, svcs.hostTD(), *pDb->getAppServices());\
    pPrcStream->rewind();\
    pDb->readFile(pPrcStream);\
  }\
}
#include "ExampleCases.h"

