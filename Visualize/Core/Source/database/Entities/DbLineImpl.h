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

#ifndef _ODDBLINEIMPL_INCLUDED_
#define _ODDBLINEIMPL_INCLUDED_

#include "DbCurveImpl.h"
#include "Ge/GePoint3d.h"
#include "../DbSystemInternals.h"
#include "DbLine.h"

class OdTvDbLineImpl : public OdTvDbEntityImpl, public OdTvDb2dEntityImpl
{
  static OdTvDbLineImpl* getImpl(const OdTvDbLine *pObj)
  { return (OdTvDbLineImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  ODRX_HEAP_OPERATORS();  // ODRX_USING_HEAP_OPERATORS() causes mac compiler error

  OdTvDbLineImpl();

  virtual double thickness() const {return m_dThickness;}
  virtual void setThickness(double val) { m_dThickness = val; }
  void setStartPoint(const OdGePoint3d& pnt)
  {
    m_startPoint = pnt;
  }
  void setEndPoint(const OdGePoint3d& pnt)
  {
    m_endPoint = pnt;
  }

  OdGePoint3d startPoint() const
  {
    return m_startPoint;
  }

  OdGePoint3d endPoint() const
  {
    return m_endPoint;
  }

  void set(const OdGePoint3d& start, const OdGePoint3d& end)
  {
    m_startPoint = start;
    m_endPoint = end;
  }

  OdResult transformBy(const OdGeMatrix3d& trans)
  {
    m_startPoint.transformBy(trans);
    m_endPoint.transformBy(trans);
    return OdTvDb2dEntityImpl::transformBy(trans);
  }

private:
  OdGePoint3d m_startPoint;
  OdGePoint3d m_endPoint;

  friend class OdTvDbLine;
  friend struct OdTvDbLineTfPE;
};

#endif // _ODDBLINEIMPL_INCLUDED_
