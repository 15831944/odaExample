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

#ifndef _ODDBARCDIMIMPL_INCLUDED_
#define _ODDBARCDIMIMPL_INCLUDED_

#include "DbDimensionImpl.h"
#include "DbSystemInternals.h"
#include "DbArcDimension.h"

class OdTvDbArcDimensionImpl : public OdTvDbDimensionImpl
{
  static OdTvDbArcDimensionImpl* getImpl(const OdTvDbArcDimension *pObj)
  { return (OdTvDbArcDimensionImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdGePoint3d  m_ArcPt;
  OdGePoint3d  m_xLine1Pt;
  OdGePoint3d  m_xLine2Pt;
  OdGePoint3d  m_CenterPt;
  bool   m_bIsPartial;
  double m_dStartParam;
  double m_dEndParam;
  bool   m_bHasLeader;
  
  OdGePoint3d  m_LeaderPt1;
  OdGePoint3d  m_LeaderPt2;

  OdUInt8 getDimTypeFlag() { return DimArcLen; }

  OdTvDbArcDimensionImpl();
  friend class OdTvDbArcDimension;

  virtual OdResult transformBy(const OdGeMatrix3d& xform, bool b2Copy);
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void copyFromContextData(OdTvDbObject* pObj, OdTvDbObjectContextData* pData, OdTvDbObjectContextData* pDefData);
  virtual OdGePoint3d getDimLineDefPt(OdTvDbObjectContextData* ctx);
  virtual void setDimLineDefPt(OdTvDbObjectContextData* ctx, OdGePoint3d point);

};

#endif //_ODDBARCDIMIMPL_INCLUDED_
