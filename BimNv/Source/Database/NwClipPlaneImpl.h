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

#ifndef __NWCLIPPLANEIMPL_H__
#define __NWCLIPPLANEIMPL_H__

#include "NwClipPlane.h"
#include "RxSystemServices.h"
#include "NwObjectImpl.h"
#include "Ge/GePlane.h"

class NWDBEXPORT OdNwClipPlaneImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwClipPlane)
  ODRX_DECLARE_MEMBERS(OdNwClipPlaneImpl);
  OdNwClipPlaneImpl();
public:
  virtual ~OdNwClipPlaneImpl();

public:
  static OdNwClipPlaneImpl* getImpl(const OdNwClipPlane& NwClipPlane);

public:
  inline NwClipPlaneState::Enum getState() const { return m_state; }
  inline NwClipPlaneAlignment::Enum getAlignment() const { return m_alignment; }
  OdGePlane getPlane() const;

public:
  void setState(NwClipPlaneState::Enum state);
  void setAlignment(NwClipPlaneAlignment::Enum alignment);
  void setPlane(const OdGePlane& plane);

private:
  NwClipPlaneState::Enum m_state;
  NwClipPlaneAlignment::Enum m_alignment;
  OdGePlane m_plane;
};



#endif //__NWCLIPPLANEIMPL_H__
