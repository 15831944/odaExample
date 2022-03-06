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

#ifndef __NW_TEST_STYLE_IMPL_H__
#define __NW_TEST_STYLE_IMPL_H__

#include "NwTextStyle.h"
#include "NwObjectImpl.h"

class OdNwTextStyleImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwTextStyle)
public:
  OdNwTextStyleImpl();
  virtual ~OdNwTextStyleImpl();
  ODRX_DECLARE_MEMBERS(OdNwTextStyleImpl);

public:
  static OdNwTextStyleImpl* getImpl(const OdNwTextStyle* pNwBck);
  static OdNwTextStyleImpl* getImpl(const OdRxObject* pRxBck);

public:
  const OdString& getTypeFace() const;
  const double& getFontHeight() const;
  OdUInt32 getPointSize() const;
  OdUInt32 getFontWeight() const;
  OdUInt32 getStyle() const;
  OdUInt32 getRenderStyle() const;

public:
  void setTypeFace(const OdString& val);
  void setFontHeight(const double& val);
  void setPointSize(OdUInt32 val);
  void setFontWeight(OdUInt32 val);
  void setStyle(OdUInt32 val);
  void setRenderStyle(OdUInt32 val);

protected:
  OdString m_typeFace;
  double m_fontHeight;
  OdUInt32 m_pointSize;
  OdUInt32 m_fontWeight;
  OdUInt32 m_style;
  OdUInt32 m_renderStyle;
};



#endif //__NW_TEST_STYLE_IMPL_H__
