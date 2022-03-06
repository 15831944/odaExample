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


void _TESSDRAWMODE_func(OdEdCommandContext* pCmdCtx)
{
  OdPrcCommandContextPtr pDbCmdCtx(pCmdCtx);

  OdPrcFilePtr pDb = pDbCmdCtx->baseDatabase();
  OdInt16 defVal = pDb->getTESSDRAWMODE();
  OdUInt32 nKeyword = pDbCmdCtx->dbUserIO()->getKeyword(
    L"Select priority [Tess/Body] ",
    L"Tess Body", pDb->getTESSDRAWMODE()
    );

  switch (nKeyword)
  {
  case 0:
    pDb->setTESSDRAWMODE(0);
    break;
  case 1:
  default:
    pDb->setTESSDRAWMODE(1);
    break;
  }
}

void _BEHAVIORBITFIELDMODE_func(OdEdCommandContext* pCmdCtx)
{
  OdPrcCommandContextPtr pDbCmdCtx(pCmdCtx);

  OdPrcFilePtr pDb = pDbCmdCtx->baseDatabase();
  OdInt16 defVal = pDb->getBEHAVIORBITFIELDMODE();
  OdUInt32 nKeyword = pDbCmdCtx->dbUserIO()->getKeyword(
    L"Select behavior bit filed mode [Adobe11/Adobe9.1] ",
    L"Adobe11 Adobe9.1", pDb->getBEHAVIORBITFIELDMODE()
    );

  switch (nKeyword)
  {
  case 0:
    pDb->setBEHAVIORBITFIELDMODE(0);
    break;
  case 1:
  default:
    pDb->setBEHAVIORBITFIELDMODE(1);
    break;
  }
}
