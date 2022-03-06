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

#ifndef __NW_BINARY_ATTRIBUTE_IMPL_H__
#define __NW_BINARY_ATTRIBUTE_IMPL_H__

#include "NwBinaryAttribute.h"
#include "NwAttributeImpl.h"
#include "OdBinaryData.h"

class OdNwBinaryAttributeImpl : public OdNwAttributeImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwBinaryAttribute)
public:
  OdNwBinaryAttributeImpl();
  virtual ~OdNwBinaryAttributeImpl();
  ODRX_DECLARE_MEMBERS(OdNwBinaryAttributeImpl);

public:
  static OdNwBinaryAttributeImpl* getImpl(const OdNwBinaryAttribute* pNwU64);
  static OdNwBinaryAttributeImpl* getImpl(const OdRxObject* pRxU64);

public:
  inline void setData(const OdBinaryData& binData) { m_aBinaryData = binData; }
  inline OdBinaryData& getData() { return m_aBinaryData; }
  OdResult getData(OdBinaryData& aBinData) const;

private:
  OdBinaryData m_aBinaryData;
};



#endif //__NW_BINARY_ATTRIBUTE_IMPL_H__
