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

#ifndef _OD_DB_SHBOOLEAN_IMPL_
#define _OD_DB_SHBOOLEAN_IMPL_

#include <ShHistory/DbShBoolean.h>
#include "DbShHistoryNodeImpl.h"


class OdDbShBooleanImpl : public OdDbShHistoryNodeImpl
{
  //OdDb::BoolOperType
  // 0 - union
  // 1 - intersect
  // 2 - subtract
  OdInt8 m_iBoolType;
  OdInt32 m_iNodeId1; //OdDbEvalExpr::nodeId()
  OdInt32 m_iNodeId2; //OdDbEvalExpr::nodeId()

  friend class OdDbShBoolean;

public:
  OdDbShBooleanImpl() : m_iBoolType(-1)
                      , m_iNodeId1(-1)
                      , m_iNodeId2(-1){}

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  OdResult connectOperands(OdInt32 op1, OdInt32 op2);

  DECLARE_GET_IMPL(OdDbShBoolean);

private:
  virtual bool evaluate(OdDbEvalContext const* ctx);
};

#endif
