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

#ifndef __NW_REDLINE_IMPL_
#define __NW_REDLINE_IMPL_

#include "Redline/NwRedLineType.h"
#include "Redline/NwRedLine.h"
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "NwColor.h"
#include "NwObjectImpl.h"

class OdNwRedLineImpl;


class OdNwRedLineImpl: public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwRedLine)
public:
  ODRX_DECLARE_MEMBERS(OdNwRedLineImpl);
  OdNwRedLineImpl();
  virtual ~OdNwRedLineImpl();

public:
  virtual NwRedLineType::Enum getType() const = 0;
  OdUInt32 getLineThikness() const;
  OdUInt16 getLinePattern() const;
  OdNwColor getLineColor() const;

public:
  void setLineThikness(OdUInt32 val);
  void setLinePattern(OdUInt16 val);
  void setLineColor(const OdNwColor& val);

  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;
  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

public:
  static OdNwRedLineImpl* getImpl(const OdNwRedLine* pObj);
  static OdNwRedLineImpl* getImpl(const OdRxObject* pObj);

protected:
  OdUInt32 m_lineThikness;
  OdUInt16 m_linePattern;
  OdNwColor m_lineColor;
};

#endif //__NW_REDLINE_IMPL_
