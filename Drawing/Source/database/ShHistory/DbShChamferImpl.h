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

#ifndef _OD_DB_SHCHAMFER_IMPL_
#define _OD_DB_SHCHAMFER_IMPL_

#include "ShHistory/DbShChamfer.h"
#include "DbShHistoryNodeImpl.h"


class OdDbShChamferImpl : public OdDbShHistoryNodeImpl
{
  OdInt32 m_iTmp92;//id ????????
  double m_dFirstDist;
  double m_dSecondDist;
  OdInt32Array m_EdgeIdArr;
  OdInt32 m_iFaceId; //??

  friend class OdDbShChamfer;

public:
  OdDbShChamferImpl(): m_iTmp92(0)
                     , m_iFaceId(-1)
                     , m_dFirstDist(0)
                     , m_dSecondDist(0) {}
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler) const;

  //OdResult setFace(BODY const *, FACE *)
  //OdResult setEdges(BODY const *, OdDbVoidPtrArray const &)
  //OdResult connectOperand(unsigned long)
  //OdResult getChamferHandleData(int,class OdGePoint3d &,class OdGeVector3d &,class OdGeVector3d &)

  DECLARE_GET_IMPL(OdDbShChamfer);

private:
  virtual OdResult transformBy(const OdGeMatrix3d& mat);
  virtual bool evaluate(OdDbEvalContext const* ctx);
};

#endif
