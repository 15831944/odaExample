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
#ifndef _ODDB_SURFACE_IMPL_INCLUDED_
#define _ODDB_SURFACE_IMPL_INCLUDED_
#include "DbSurface.h"
#include "DbModelerGeometryImpl.h"

class OdDb3dPolyline;

class DBENT_EXPORT OdDbSurfaceImpl : public OdDbModelerGeometryImpl
{
  // NumIsolines comes from OdModelerGeometry. It has different meaning than  
  // DbSurface numIsolines. U and V should be swapped.
  OdModelerGeometry::NumIsolines m_numIsolines;

  friend class OdDbSurface;

  static void readSubEntityData(OdDbEntityPtr& ent, int dwgType, OdBinaryData& data, OdDb::DwgVersion ver);
  static void writeSubEntityData(const OdDbEntity& ent, int dwgType, OdBinaryData &data, OdDb::DwgVersion ver);
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
  virtual OdUInt32 isolinesMode() const { return BrepRenderModes::kSurfIsolines; }
  virtual const OdModelerGeometry::NumIsolines* numIsolines() const { return &m_numIsolines; }
public:
  static OdDbSurfaceImpl* getImpl(const OdDbSurface *pObj)
  { return static_cast<OdDbSurfaceImpl*>(OdDbSystemInternals::getImpl(pObj)); }
  OdDbSurfaceImpl()
  { m_numIsolines.numU = m_numIsolines.numV = 6; }

  TD_USING(OdDbModelerGeometryImpl::booleanOper);
  template <class DbEntity>
  OdResult booleanOper(OdDb::BoolOperType operation, bool isDerived, const DbEntity* pEntity, OdDbSurfacePtr& pNewSurface);
  template <class DbEntity>
  OdResult booleanOper(OdDb::BoolOperType operation, bool isDerived, const DbEntity* pEntity, OdDbEntityPtrArray& intersectionEntities);

  virtual void composeForLoad(OdDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  static OdDbEntityPtr buildEntity(const OdModelerGeometry *acis, OdInt32 dwgType);
  static OdResult convert3d2SAT(const OdDb3dPolyline *pPoly, OdModelerGeometryPtr &pSAT);
  static void copyEntityArray(const OdDbEntityPtrArray& from, OdDbEntityPtrArray& to);
  static OdDbEntityPtr copySubEntity(const OdDbEntity *ent);

  TOOLKIT_EXPORT static OdResult readSubEntity(OdDbDwgFiler* pFiler, OdDbEntityPtr& ent);
  TOOLKIT_EXPORT static void writeSubEntity(OdDbDwgFiler* pFiler, const OdDbEntity* ent, bool saveEmptyAllowed);
  TOOLKIT_EXPORT static OdResult readSubEntity(OdDbDxfFiler* pFiler, OdDbEntityPtr& ent, int gc = 90);
  TOOLKIT_EXPORT static void writeSubEntity(OdDbDxfFiler* pFiler, int gc, const OdDbEntity* ent, bool saveEmptyAllowed, int gcBType = 90);

  virtual OdResult convertToRegion(OdDbEntityPtrArray& regions);
  virtual OdResult thicken(double thickness, bool bBothSides, OdDb3dSolidPtr& pSolid) const;

  virtual OdResult sliceByPlane(const OdGePlane& slicePlane, OdDbSurfacePtr& pNegHalfSurface, OdDbSurfacePtr& pNewSurface, bool bNotModifyItself);
  virtual OdResult sliceBySurface(const OdDbSurfacePtr pSlicingSurface, OdDbSurfacePtr& pNegHalfSurface, OdDbSurfacePtr& pNewSurface, bool bNotModifyItself);

  virtual OdResult convertToNurbSurface(OdDbNurbSurfacePtrArray& nurbSurfaceArray);
};
#endif //_ODDB_SURFACE_IMPL_INCLUDED_
