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

#ifndef _ODDBRADDIMIMPL_INCLUDED_
#define _ODDBRADDIMIMPL_INCLUDED_

#include "DbDimensionImpl.h"
#include "DbSystemInternals.h"
#include "DbRadialDimension.h"

class OdTvDbRadialDimensionImpl : public OdTvDbDimensionImpl
{
  static OdTvDbRadialDimensionImpl* getImpl(const OdTvDbRadialDimension *pObj)
  { return (OdTvDbRadialDimensionImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  OdGePoint3d m_DefPointCenter;
  double      m_dLeaderLen;

  OdTvDbRadialDimensionImpl()
    : m_dLeaderLen(0.0)
  { }

  virtual OdUInt8 getDimTypeFlag() { return OdTvDbDimensionImpl::DimRadial; }

  /** Transforms this entity by the specified matrix.
  */
  OdResult transformBy(const OdGeMatrix3d& xform, bool b2Copy);
  virtual void copyFromContextData(OdTvDbObject *pObj,OdTvDbObjectContextData*,OdTvDbObjectContextData*);
  virtual OdGePoint3d getDimLineDefPt(OdTvDbObjectContextData* ctx);
  virtual void setDimLineDefPt(OdTvDbObjectContextData* ctx, OdGePoint3d point);

  friend class OdTvDbRadialDimension;
  friend class OdTvDwgR12FileLoader;

  virtual void setElevation(double elevation, const OdGeMatrix3d& world2Plane, const OdGeMatrix3d& plane2World);
};

#endif // _ODDBRADDIMIMPL_INCLUDED_
