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

#ifndef _EXDGNPCLONINGMODULE_INCLUDED_
#define _EXDGNPCLONINGMODULE_INCLUDED_


#include "RxDynamicModule.h"
#include "Ed/EdCommandStack.h"
#include "StaticRxObject.h"


//
// Define classes for custom commands
//
#define CMD_DEF(CmdName, GroupName)           \
class _##CmdName##_cmd : public OdEdCommand   \
{                                             \
public:                                       \
  const OdString groupName() const;           \
  const OdString globalName() const;          \
  void execute(OdEdCommandContext* pCmdCtx);  \
};
#include "ExDgnCmdDefs.h"
#undef CMD_DEF


//
// Define TX module
//
class ExDgnCloningModule : public OdRxModule
{
public:
  void initApp();
  void uninitApp();

private:
#define CMD_DEF(CmdName, GroupName) \
  OdStaticRxObject<_##CmdName##_cmd> m_##CmdName##_cmd;
#include "ExDgnCmdDefs.h"
#undef CMD_DEF

private:
  OdRxModulePtr m_pExCustObjsModule;
};

#endif  // _EXDGNPCLONINGMODULE_INCLUDED_
