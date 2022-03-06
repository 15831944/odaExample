
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

#ifndef _NW_PLOTPATHFIGURE2_IMPL_H_
#define _NW_PLOTPATHFIGURE2_IMPL_H_

#include "NwPlotPathFigure2.h"
#include "NwObjectImpl.h"
#include "Ge/GeVector3d.h"

class OdNwPlotPathFigure2Impl;


class OdNwPlotPathFigure2Impl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwPlotPathFigure2)
public:
  OdNwPlotPathFigure2Impl();
  virtual ~OdNwPlotPathFigure2Impl();
  ODRX_DECLARE_MEMBERS(OdNwPlotPathFigure2Impl);

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;
  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

public:
  static OdNwPlotPathFigure2Impl* getImpl(const OdNwPlotPathFigure2* pNwGeometry);
  static OdNwPlotPathFigure2Impl* getImpl(const OdRxObject* pRxGeometry);
};

#endif //_NW_PLOTPATHFIGURE2_IMPL_H_

