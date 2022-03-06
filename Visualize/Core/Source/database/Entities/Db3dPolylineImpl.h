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

#ifndef _ODDB3dPOLYLINEIMPL_INCLUDED_
#define _ODDB3dPOLYLINEIMPL_INCLUDED_

#include "Db3dPolyline.h"
#include "PolylineBaseImpl.h"

class OdTvDb3dPolylineCache : public OdTvDbObjectReactor
{
public:
  OdTvDb3dPolylineCache()
  {}
  OdBinaryData     m_flags;
  OdGePoint3dArray m_points;

  void openedForModify(const OdTvDbObject* pObj);
};
typedef OdSmartPtr<OdTvDb3dPolylineCache> OdTvDb3dPolylineCachePtr;

class OdTvDb3dPolylineImpl : public OdPolylineBaseImpl
{
  static OdTvDb3dPolylineImpl* getImpl(const OdTvDb3dPolyline *pObj)
  { return (OdTvDb3dPolylineImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  void audit (OdTvDbAuditInfo* pAuditInfo);
  virtual bool isValidSubentityClass(OdRxClass* pClass) const;
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void recvPropagateModify(OdTvDbObject* pOwner, const OdTvDbObject* pSubObj);

  void createCache(OdTvDb3dPolyline* p3dPline);
  static void clearCache(OdTvDb3dPolyline* p3dPline);
  static void updateCache(OdTvDb3dPolyline* pPline, OdTvDb3dPolylineVertex* pVert);
  OdTvDb3dPolylineCachePtr m_PlineCache;

  friend class OdTvDb3dPolyline;
  friend class Od3dPolylineCacheResolver;
};

#endif // _ODDB3dPOLYLINEIMPL_INCLUDED_
