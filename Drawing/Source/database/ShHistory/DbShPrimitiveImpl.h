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

#ifndef _OD_DB_SHPRIMITIVE_IMPL_
#define _OD_DB_SHPRIMITIVE_IMPL_

#include "ShHistory/DbShPrimitive.h"
#include "DbShHistoryNodeImpl.h"
#include "DbSurfaceImpl.h"

class OdDbShPrimitiveImpl : public OdDbShHistoryNodeImpl
{
  friend class OdDbShPrimitive;
public:
  OdDbShPrimitiveImpl();

  OdResult dxfInFields(OdDbDxfFiler* pFiler);
  void dxfOutFields(OdDbDxfFiler* pFiler);  

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  /*OdDbSubentId acisSubentId(ENTITY *)
  ENTITY * acisSubentPtr(OdDbSubentId const &)
  ENTITY * getEntityAtGsMarker(OdGsMarker)
  OdResult getGsMarkersAtSubentPath(OdDbFullSubentPath const &, OdGsMarkerArray &, unsigned long)
  OdResult getSubentPathsAtGsMarker(unsigned long, OdGsMarker, OdGePoint3d const &, OdGeMatrix3d const &, int &, OdDbFullSubentPath * &, int, OdDbObjectId *)
  void list()
  void modified()
  OdGePoint3d position()
  void resolve(OdDbShSubents &)
  double rotation()
  OdResult setPosition(OdGePoint3d const &)
  OdDbEntity * subentPtr(OdDbSubentId const &)
  OdResult synch()
  void viewportDraw(OdGiViewportDraw *, unsigned long)
  int worldDraw(OdGiWorldDraw *,unsigned long)*/

  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;
  virtual bool evaluate(OdDbEvalContext const* ctx) = 0;
  DECLARE_GET_IMPL(OdDbShPrimitive);
protected:
  void writeSubEntityCatched(OdDbDwgFiler* pFiler, const OdDbEntity* ent, bool saveEmptyAllowed) const
  {
    try
    {
      OdDbSurfaceImpl::writeSubEntity(pFiler, ent, saveEmptyAllowed);
    }
    catch (const OdError& e)
    {
      if (e.code() == eEmptyAcisFile)
      {
        throw OdEmptyAcisError(objectId());
      }
      throw e;
    }
  }

  void writeSubEntityCatchedDxf(OdDbDxfFiler* pFiler, int gc, const OdDbEntity* ent, bool saveEmptyAllowed, int gcBType) const
  {
    try
    {
      OdDbSurfaceImpl::writeSubEntity(pFiler, gc, ent, saveEmptyAllowed, gcBType);
    }
    catch (const OdError& e)
    {
      if (e.code() == eEmptyAcisFile)
      {
        throw OdEmptyAcisError(objectId());
      }
      throw e;
    }
  }

  void writeAcisDataCatched(OdDbDxfFiler* pFiler, OdModelerGeometry* pAcisData, bool saveEmptyAllowed) const
  {
    try
    {
      OdDbModelerGeometryImpl::writeAcisData(pFiler, pAcisData, saveEmptyAllowed);
    }
    catch (const OdError& e)
    {
      if (e.code() == eEmptyAcisFile)
      {
        throw OdEmptyAcisError(objectId());
      }
      throw e;
    }
  }
};

#endif
