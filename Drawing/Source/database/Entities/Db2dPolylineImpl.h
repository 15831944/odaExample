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


class OdDb2dPolylineCache : public OdDbObjectReactor
{
public:
  OdDb2dPolylineCache()
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

  void openedForModify(const OdDbObject* pObj);
};
typedef OdSmartPtr<OdDb2dPolylineCache> OdDb2dPolylineCachePtr;


class OdDb2dPolylineImpl : public OdPolylineBaseImpl, public OdDb2dEntityImpl
{
  static OdDb2dPolylineImpl* getImpl(const OdDb2dPolyline *pObj)
  { return (OdDb2dPolylineImpl*)OdDbSystemInternals::getImpl(pObj);}
public:
  static OdResult curveFitImpl(OdDb2dPolylinePtr pPoly, bool bSplineFitCaller = false);
  static void straighten(OdDb2dPolylinePtr pPoly, bool bResetBulges = true);

  OdDb2dPolylineImpl();
  ~OdDb2dPolylineImpl();

	double       m_dStartWidth;
	double       m_dEndWidth;
  double       m_dElevation;

  virtual double thickness() const {return m_dThickness;}
  virtual void setThickness(double val) { m_dThickness = val; }

  OdDbObjectId insertVertexAt(const OdDbEntity* pPrevVert, OdDbEntity* pVert);
  OdDbObjectId insertVertexAt(const OdDbEntity* pPrevVert, OdDbEntityPtrArray pVertArray);
  virtual bool isValidSubentityClass(OdRxClass* pClass) const;
  virtual void postProcessVertices();

  // OdDbObjectImpl overridden
  void audit(OdDbAuditInfo* pAuditInfo);
  void recvPropagateModify(OdDbObject* pOwner, const OdDbObject* pSubObj);
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdDbAuditInfo* pAuditInfo);

  void createCache(OdDb2dPolyline* p2dPline);
  static void clearCache(OdDb2dPolyline* p2dPline);
  static void updateCache(OdDb2dPolyline* pPline, OdDb2dVertex* pVert);
  static void convertCache(OdDbPolyline* pRes, const OdDb2dPolyline* p2dPline);
  OdDb2dPolylineCachePtr m_PlineCache;

  void checkVertsNumber(OdDbAuditInfo* pAuditInfo);

  //
  friend class OdDb2dPolyline;
  friend class OdDb2dVertex;
  friend class OdDb2dVertexImpl;
  friend class OdPlineCacheResolver;
};

#endif // _ODDB2dPOLYLINEIMPL_INCLUDED_
