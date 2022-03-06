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

#ifndef _ODDBPOINTIMPL_INCLUDED_
#define _ODDBPOINTIMPL_INCLUDED_

#include "DbEntityImpl.h"
#include "DbSystemInternals.h"
#include "DbPoint.h"

class OdGiGeometry;

class OdDbPointImpl : public OdDbEntityImpl, public OdDb2dEntityImpl
{
  static OdDbPointImpl* getImpl(const OdDbPoint *pObj)
  { return (OdDbPointImpl*)OdDbSystemInternals::getImpl(pObj);}

public:
  OdGePoint3d  m_Point;
  double       m_dUcsXAngle;

public:
  OdDbPointImpl()
    : m_dUcsXAngle(0.0)
  {}

  virtual double thickness() const {return m_dThickness;}
  virtual void setThickness(double val) { m_dThickness = val; }

  // common drawing point routine
  void drawPoint(OdGiGeometry& geom, double size, int mode) const;

private:
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  friend class OdDbPoint;
};

#endif // _ODDBPOINTIMPL_INCLUDED_
