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

#ifndef _ODSYSVARINFO_H_
#define _ODSYSVARINFO_H_

#include "TD_PackPush.h"

#include "RxObject.h"

class OdTvDbDatabase;
class OdTvDbCommandContext;


/** 
    <group Other_Classes>
*/
class OdTvSysVarInfo : public OdRxObject
{
protected:
  OdTvSysVarInfo()
    : m_getFn(0)
    , m_setFn(0)
    , m_mapTypeFn(0)
  {}
public:
  typedef OdTvResBufPtr (*GetFn)(const OdTvDbDatabase* pDb);
  typedef void (*SetFn)(OdTvDbDatabase* pDb, const OdTvResBuf* pRbValue);

  enum
  {
    kToAcadType = 0,
    kToDDType   = 1
  };
  typedef void (*MapTypeFn)(OdTvDbDatabase* pDb, OdTvResBuf* pVal, int opt);

  GetFn       m_getFn;
  SetFn       m_setFn;

  MapTypeFn   m_mapTypeFn;
};

/** 
    <group Other_Classes>
*/
class OdTvSetVarInfo : public OdRxObject
{
protected:
  OdTvSetVarInfo()
    : m_formatFn(0)
    , m_promptFn(0)
  {}
public:
  typedef OdString (*FormatFn)(OdTvDbDatabase* pDbCmdCtx, const OdTvResBuf* pRbValue);
  typedef void (*PromptFn)(OdTvDbCommandContext* pDbCmdCtx, const OdString& varName, OdTvResBuf* pVal);

  FormatFn  m_formatFn;
  PromptFn  m_promptFn;
};

#include "TD_PackPop.h"

#endif //#ifndef _ODSYSVARINFO_H_
