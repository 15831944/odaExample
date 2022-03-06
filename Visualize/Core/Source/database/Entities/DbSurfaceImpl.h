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

class OdTvDb3dPolyline;

class DBENT_EXPORT OdTvDbSurfaceImpl : public OdTvDbModelerGeometryImpl
{
  friend class OdTvDbBody;

  // NumIsolines comes from OdModelerGeometry. It has different meaning than  
  // DbSurface numIsolines. U and V should be swapped.
  OdModelerGeometry::NumIsolines m_numIsolines;

  static OdTvDbSurfaceImpl* getImpl(const OdTvDbSurface *pObj)
  { return (OdTvDbSurfaceImpl*)OdTvDbSystemInternals::getImpl(pObj);}
  friend class OdTvDbSurface;

  static void readSubEntityData(OdTvDbEntityPtr& ent, int dwgType, OdBinaryData& data, OdDb::DwgVersion ver);
  static void writeSubEntityData(const OdTvDbEntity& ent, int dwgType, OdBinaryData &data, OdDb::DwgVersion ver);
protected:
  virtual OdUInt32 isolinesMode() const { return BrepRenderModes::kSurfIsolines; }
  virtual const OdModelerGeometry::NumIsolines * numIsolines() const { return &m_numIsolines; }
public:
  OdTvDbSurfaceImpl()
  { m_numIsolines.numU = m_numIsolines.numV = 6; }

  virtual void composeForLoad(OdTvDbObject* pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  static OdTvDbEntityPtr buildEntity(const OdModelerGeometry *acis, OdInt32 dwgType);
  static OdResult convert3d2SAT(const OdTvDb3dPolyline *pPoly, OdModelerGeometryPtr &pSAT);
  static void copyEntityArray(const OdTvDbEntityPtrArray& from, OdTvDbEntityPtrArray& to);
  static OdTvDbEntityPtr copySubEntity(const OdTvDbEntity *ent);

  TOOLKIT_EXPORT static OdResult readSubEntity(OdTvDbDwgFiler* pFiler, OdTvDbEntityPtr& ent);
  TOOLKIT_EXPORT static void writeSubEntity(OdTvDbDwgFiler* pFiler, const OdTvDbEntity* ent, bool saveEmptyAllowed);
  TOOLKIT_EXPORT static OdResult readSubEntity(OdTvDbDxfFiler* pFiler, OdTvDbEntityPtr& ent, int gc = 90);
  TOOLKIT_EXPORT static void writeSubEntity(OdTvDbDxfFiler* pFiler, int gc, const OdTvDbEntity* ent, bool saveEmptyAllowed, int gcBType = 90);

  virtual OdResult convertToRegion ( OdTvDbEntityPtrArray& regions );
  virtual OdResult thicken(double thickness, bool bBothSides, OdTvDb3dSolidPtr& pSolid) const;

  virtual OdDbSubentId internalSubentId(void* ent) const;
  virtual void* internalSubentPtr(const OdDbSubentId& id) const;

  virtual OdResult sliceByPlane(const OdGePlane& slicePlane, OdTvDbSurfacePtr& pNegHalfSurface, OdTvDbSurfacePtr& pNewSurface, bool bNotModifyItself);
  virtual OdResult sliceBySurface(const OdTvDbSurfacePtr pSlicingSurface, OdTvDbSurfacePtr& pNegHalfSurface, OdTvDbSurfacePtr& pNewSurface, bool bNotModifyItself);

  virtual OdResult convertToNurbSurface(OdTvDbNurbSurfacePtrArray& nurbSurfaceArray);
};
#endif //_ODDB_SURFACE_IMPL_INCLUDED_
