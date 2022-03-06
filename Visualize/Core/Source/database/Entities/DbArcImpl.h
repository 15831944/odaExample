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

#ifndef _ODDBARCIMPL_INCLUDED_
#define _ODDBARCIMPL_INCLUDED_

#include "DbCircleImpl.h"
#include "Ge/GePoint3d.h"
#include "DbSystemInternals.h"
#include "DbArc.h"

class OdTvDbArcImpl : public OdTvDbCircleImpl
{
  static OdTvDbArcImpl* getImpl(const OdTvDbArc *pObj)
  { return (OdTvDbArcImpl*)OdTvDbSystemInternals::getImpl(pObj);}

public:
  double m_dStartAngle;
  double m_dEndAngle;

  OdTvDbArcImpl()
    : m_dStartAngle(0.)
    , m_dEndAngle(0.)
  {
  }

private:
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;  
  virtual OdResult transformBy(const OdGeMatrix3d& xform);

  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  friend class OdTvDbArc;
};

#endif // _ODDBARCIMPL_INCLUDED_
