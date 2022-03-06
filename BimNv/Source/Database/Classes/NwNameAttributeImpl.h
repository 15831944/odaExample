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

#ifndef __NW_NAME_ATTRIBUTE_IMPL_H__
#define __NW_NAME_ATTRIBUTE_IMPL_H__

#include "NwNameAttribute.h"
#include "NwAttributeImpl.h"

class OdNwNameAttributeImpl : public OdNwAttributeImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwNameAttribute)
public:
  OdNwNameAttributeImpl();
  virtual ~OdNwNameAttributeImpl();
  ODRX_DECLARE_MEMBERS(OdNwNameAttributeImpl);

public:
  static OdNwNameAttributeImpl* getImpl(const OdNwNameAttribute* pNwU64);
  static OdNwNameAttributeImpl* getImpl(const OdRxObject* pRxU64);

public:
  inline bool isStableId() const { return m_flags & 0xFF0000; }
};



#endif //__NW_NAME_ATTRIBUTE_IMPL_H__
