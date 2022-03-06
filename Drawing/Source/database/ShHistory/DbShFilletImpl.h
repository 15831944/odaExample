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

#ifndef _OD_DB_SHFILLET_IMPL_
#define _OD_DB_SHFILLET_IMPL_

#include "ShHistory/DbShFillet.h"
#include "DbShHistoryNodeImpl.h"


class OdDbShFilletImpl : public OdDbShHistoryNodeImpl
{
  OdInt32 m_iTmp92;//id ????????

  OdInt32Array m_EdgeIdArr;
  OdDoubleArray m_RadiusArr;
  OdDoubleArray m_StartSetbackArr;
  OdDoubleArray m_EndSetbackArr;

  friend class OdDbShFillet;

public:
  OdDbShFilletImpl(){}

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  //OdResult connectOperand(unsigned long)
  //OdResult getFilletHandleData(int, OdGePoint3d &, OdGeVector3d &, OdGeVector3d &)
  //OdResult setEdges(BODY const *, OdDbVoidPtrArray const &)

  DECLARE_GET_IMPL(OdDbShFillet);

private:
  virtual OdResult transformBy(const OdGeMatrix3d& mat);
  virtual bool evaluate(OdDbEvalContext const* ctx);
};

#endif
