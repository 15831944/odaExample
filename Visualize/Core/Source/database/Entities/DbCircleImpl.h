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

#ifndef _ODDBCIRCLEIMPL_INCLUDED_
#define _ODDBCIRCLEIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "DbSystemInternals.h"
#include "DbCircle.h"

class OdTvDbCircleImpl : public OdTvDbEntityImpl, public OdTvDb2dEntityImpl
{
  static OdTvDbCircleImpl* getImpl(const OdTvDbCircle *pObj)
  { return (OdTvDbCircleImpl*)OdTvDbSystemInternals::getImpl(pObj);}

protected:
public:
  double        m_dRadius;

public:
  OdTvDbCircleImpl();

  ODIMPL_DEFINE_WCS_OCS_POINT(Center);
  virtual double thickness() const {return m_dThickness;}
  virtual void setThickness(double val) { m_dThickness = val; }

protected:
  virtual void audit(OdTvDbAuditInfo* pAuditInfo);
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  virtual OdResult transformBy(const OdGeMatrix3d& xform);
  OdResult getFirstDeriv( double param, OdGeVector3d& firstDeriv ) const;
  OdResult getSecondDeriv( double param, OdGeVector3d& secondDeriv ) const;
private:
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  friend class OdTvDbCircle;
};

#endif // _ODDBCIRCLEIMPL_INCLUDED_
