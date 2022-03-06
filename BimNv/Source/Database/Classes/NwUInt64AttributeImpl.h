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

#ifndef __NW_UINT64_ATTRIBUTE_IMPL_H__
#define __NW_UINT64_ATTRIBUTE_IMPL_H__

#include "NwUInt64Attribute.h"
#include "NwAttributeImpl.h"

class OdNwUInt64AttributeImpl : public OdNwAttributeImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwUInt64Attribute)
public:
  OdNwUInt64AttributeImpl();
  virtual ~OdNwUInt64AttributeImpl();
  ODRX_DECLARE_MEMBERS(OdNwUInt64AttributeImpl);

public:
  static OdNwUInt64AttributeImpl* getImpl(const OdNwUInt64Attribute* pNwU64);
  static OdNwUInt64AttributeImpl* getImpl(const OdRxObject* pRxU64);

public:
  const OdUInt64& getValue() const;

  inline bool isStableId() const { return m_flags & 0xFF0000; }

public:
  void setValue(const OdUInt64& val);

protected:
  OdUInt64 m_value;
};



#endif //__NW_UINT64_ATTRIBUTE_IMPL_H__
