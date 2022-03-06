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

#ifndef _ODDB2dPOLYLINEIMPL_INCLUDED_
#define _ODDB2dPOLYLINEIMPL_INCLUDED_

#include "PolylineBaseImpl.h"
#include "Db2dPolyline.h"
#include "DbSystemInternals.h"
#include "DbPolyline.h"


class OdTvDb2dPolylineCache : public OdTvDbObjectReactor
{
public:
  OdTvDb2dPolylineCache()
    : m_constWidth(0.)
  {}
  OdBinaryData     m_flags;
  OdGePoint2dArray m_points;
  OdGeDoubleArray  m_elevations;
  OdGePoint2dArray m_widths;
  double           m_constWidth;
  OdGeDoubleArray  m_bulges;
  OdGeDoubleArray  m_tangents;
  OdInt32Array     m_identifiers;

  void openedForModify(const OdTvDbObject* pObj);
};
typedef OdSmartPtr<OdTvDb2dPolylineCache> OdTvDb2dPolylineCachePtr;


class OdTvDb2dPolylineImpl : public OdPolylineBaseImpl, public OdTvDb2dEntityImpl
{
  static OdTvDb2dPolylineImpl* getImpl(const OdTvDb2dPolyline *pObj)
  { return (OdTvDb2dPolylineImpl*)OdTvDbSystemInternals::getImpl(pObj);}
public:
  static OdResult curveFitImpl(OdTvDb2dPolylinePtr pPoly, bool bSplineFitCaller = false);
  static void straighten(OdTvDb2dPolylinePtr pPoly, bool bResetBulges = true);

  OdTvDb2dPolylineImpl();
  ~OdTvDb2dPolylineImpl();

	double       m_dStartWidth;
	double       m_dEndWidth;
  double       m_dElevation;

  virtual double thickness() const {return m_dThickness;}
  virtual void setThickness(double val) { m_dThickness = val; }

  OdTvDbObjectId insertVertexAt(const OdTvDbEntity* pPrevVert, OdTvDbEntity* pVert);
  OdTvDbObjectId insertVertexAt(const OdTvDbEntity* pPrevVert, OdTvDbEntityPtrArray pVertArray);
  virtual bool isValidSubentityClass(OdRxClass* pClass) const;
  virtual void postProcessVertices();

  // OdTvDbObjectImpl overridden
  void audit(OdTvDbAuditInfo* pAuditInfo);
  void recvPropagateModify(OdTvDbObject* pOwner, const OdTvDbObject* pSubObj);
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdTvDbAuditInfo* pAuditInfo);

  void createCache(OdTvDb2dPolyline* p2dPline);
  static void clearCache(OdTvDb2dPolyline* p2dPline);
  static void updateCache(OdTvDb2dPolyline* pPline, OdTvDb2dVertex* pVert);
  static void convertCache(OdTvDbPolyline* pRes, const OdTvDb2dPolyline* p2dPline);
  OdTvDb2dPolylineCachePtr m_PlineCache;

  void checkVertsNumber(OdTvDbAuditInfo* pAuditInfo);

  //
  friend class OdTvDb2dPolyline;
  friend class OdTvDb2dVertex;
  friend class OdTvDb2dVertexImpl;
  friend class OdPlineCacheResolver;
};

#endif // _ODDB2dPOLYLINEIMPL_INCLUDED_
