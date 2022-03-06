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

#ifndef _OD_DB_SHEXTRUSION_IMPL_
#define _OD_DB_SHEXTRUSION_IMPL_

#include "ShHistory/DbShExtrusion.h"
#include "DbShSweepImpl.h"


class OdDbShExtrusionImpl : public OdDbShSweepImpl
{
  friend class OdDbShExtrusion;
public:
  OdDbShExtrusionImpl() {}

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler);

  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  OdResult getPathLength(double& dLen)const;
  OdResult setTaperAngle(double dtaperAng);
  double taperAngle();

  DECLARE_GET_IMPL(OdDbShExtrusion);

private:
  virtual bool evaluate(OdDbEvalContext const* ctx);
};
#endif
