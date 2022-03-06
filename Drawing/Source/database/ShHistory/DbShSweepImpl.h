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

#ifndef _OD_DB_SHSWEEP_IMPL_
#define _OD_DB_SHSWEEP_IMPL_

#include "ShHistory/DbShSweep.h"
#include "DbShPrimitiveImpl.h"
#include "DbSweepOptions.h"
#include "ShHistory/DbShExtrusion.h"

class OdDbShSweepImpl : public OdDbShPrimitiveImpl
{
  friend class OdDbShExtrusion;
  friend class OdDbShSweep;

  OdInt32 m_nVersionMajor;
  OdInt32 m_nVersionMinor;
protected:
  OdGeVector3d     m_pSweepVec;
  OdDbEntityPtr    m_pSweep;
  OdDbEntityPtr    m_pPath;
  OdDbSweepOptions m_pOptions;

public:
  OdDbShSweepImpl();

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler);

  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  OdResult getPathLength(double& dLen)const;

  OdDbEntityPtr sweepEntity() const;
  OdDbEntityPtr pathEntity() const;
  OdResult setPathEntity(OdDbEntity* pPathEnt);
  OdResult setSweepEntity(OdDbEntity* pSweepEnt);
  
  DECLARE_GET_IMPL(OdDbShSweep);

private:
  virtual OdResult transformBy(const OdGeMatrix3d& mat);
  virtual bool evaluate(OdDbEvalContext const* ctx);
};
#endif
