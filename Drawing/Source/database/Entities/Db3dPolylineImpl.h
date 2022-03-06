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

class OdDb3dPolylineCache : public OdDbObjectReactor
{
public:
  OdDb3dPolylineCache()
  {}
  OdBinaryData     m_flags;
  OdGePoint3dArray m_points;

  void openedForModify(const OdDbObject* pObj);
};
typedef OdSmartPtr<OdDb3dPolylineCache> OdDb3dPolylineCachePtr;

class OdDb3dPolylineImpl : public OdPolylineBaseImpl
{
  static OdDb3dPolylineImpl* getImpl(const OdDb3dPolyline *pObj)
  { return (OdDb3dPolylineImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  void audit (OdDbAuditInfo* pAuditInfo);
  virtual bool isValidSubentityClass(OdRxClass* pClass) const;
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void recvPropagateModify(OdDbObject* pOwner, const OdDbObject* pSubObj);

  void createCache(OdDb3dPolyline* p3dPline);
  static void clearCache(OdDb3dPolyline* p3dPline);
  static void updateCache(OdDb3dPolyline* pPline, OdDb3dPolylineVertex* pVert);
  OdDb3dPolylineCachePtr m_PlineCache;

  friend class OdDb3dPolyline;
  friend class Od3dPolylineCacheResolver;
};

#endif // _ODDB3dPOLYLINEIMPL_INCLUDED_
