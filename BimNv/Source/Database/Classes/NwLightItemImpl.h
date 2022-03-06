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

#ifndef __NWLIGHTITEMIMPL_H__
#define __NWLIGHTITEMIMPL_H__

#include "NwLightItem.h"
#include "NwSavedItemImpl.h"

class OdNwLightItemImpl : public OdNwSavedItemImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwLightItem)
public:
  ODRX_DECLARE_MEMBERS(OdNwLightItemImpl);

public:
  OdNwLightItemImpl();
  virtual ~OdNwLightItemImpl();

public:
  static OdNwLightItemImpl* getImpl(const OdNwLightItem* pNwLI);
  static OdNwLightItemImpl* getImpl(const OdRxObject* pRxLI);
  static OdNwObjectId createLightItemByLight(OdNwObjectId lightId);

public:
  OdNwObjectId getLight() const;
  OdGePoint3d getPosition() const;
  OdGePoint3d getTarget() const;

public:
  void setLight(OdNwObjectId lightId);
  void setPosition(const OdGePoint3d& pos);
  void setTarget(const OdGePoint3d& targ);

private:
  OdNwObjectId m_lightId;
  OdGePoint3d  m_position;
  OdGePoint3d  m_target;
};



#endif // __NWLIGHTITEMIMPL_H__
