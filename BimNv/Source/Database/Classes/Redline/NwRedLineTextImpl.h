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

#ifndef __NWREDLINETEXT_IMPL_
#define __NWREDLINETEXT_IMPL_

#include "Redline/NwRedLineText.h"
#include "NwRedLineImpl.h"
#include "Ge/GePoint2d.h"

class OdNwRedLineTextImpl;


class OdNwRedLineTextImpl : public OdNwRedLineImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwRedLineText)
public:
  ODRX_DECLARE_MEMBERS(OdNwRedLineTextImpl);
  OdNwRedLineTextImpl();
  virtual ~OdNwRedLineTextImpl();

public:
  virtual NwRedLineType::Enum getType() const;
  OdString getText() const;
  OdGePoint2d getLocation() const;

public:
  void setText(const OdString& val);
  void setLocation(const OdGePoint2d& val);

public:
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits* pTraits) const;
  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;
  virtual void subViewportDraw(OdGiViewportDraw* pVd) const;

public:
  static OdNwRedLineTextImpl* getImpl(const OdNwRedLineText* pObj);
  static OdNwRedLineTextImpl* getImpl(const OdRxObject* pObj);

protected:
  OdString m_text;
  OdGePoint2d m_location;
};

#endif //__NWREDLINETEXT_IMPL_
