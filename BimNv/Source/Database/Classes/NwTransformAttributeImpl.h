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

#ifndef __NW_TRANSFORM_ATTRIBUTE_IMPL_H__
#define __NW_TRANSFORM_ATTRIBUTE_IMPL_H__

#include "NwTransformAttribute.h"
#include "NwAttributeImpl.h"
#include "Ge/GeMatrix3d.h"

class OdNwTransformAttributeImpl : public OdNwAttributeImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwTransformAttribute)
public:
  OdNwTransformAttributeImpl();
  virtual ~OdNwTransformAttributeImpl();
  ODRX_DECLARE_MEMBERS(OdNwTransformAttributeImpl);

public:
  static OdNwTransformAttributeImpl* getImpl(const OdNwTransformAttribute* pNwTrans);
  static OdNwTransformAttributeImpl* getImpl(const OdRxObject* pRxTrans);

public:
  const OdGeMatrix3d& getTransform() const;
  bool isReverse() const;

public:
  void setTransform(const OdGeMatrix3d& tr);
  void setReverse(bool val);

protected:
  bool m_bIsReverse;
  OdGeMatrix3d m_transform;
};



#endif //__NW_TRANSFORM_ATTRIBUTE_IMPL_H__
