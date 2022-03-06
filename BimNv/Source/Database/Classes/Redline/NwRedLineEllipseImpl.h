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

#ifndef __NWREDLINEELLIPSE_IMPL_
#define __NWREDLINEELLIPSE_IMPL_

#include "Redline/NwRedLineEllipse.h"
#include "NwRedLineImpl.h"
#include "Ge/GePoint2d.h"

class OdNwRedLineEllipseImpl;


class OdNwRedLineEllipseImpl : public OdNwRedLineImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwRedLineEllipse)
public:
  ODRX_DECLARE_MEMBERS(OdNwRedLineEllipseImpl);
  OdNwRedLineEllipseImpl();
  virtual ~OdNwRedLineEllipseImpl();

public:
  NwRedLineType::Enum getType() const override;
  OdGePoint2d getMin() const;
  OdGePoint2d getMax() const;

public:
  void setMin(const OdGePoint2d& val);
  void setMax(const OdGePoint2d& val);

public:
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;
  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

public:
  static OdNwRedLineEllipseImpl* getImpl(const OdNwRedLineEllipse* pObj);
  static OdNwRedLineEllipseImpl* getImpl(const OdRxObject* pObj);

protected:
  OdGePoint2d m_min;
  OdGePoint2d m_max;
};

#endif //__NWREDLINEELLIPSE_IMPL_
