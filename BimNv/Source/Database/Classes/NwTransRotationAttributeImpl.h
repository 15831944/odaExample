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

#ifndef __NW_TRANSROTATION_ATTRIBUTE_IMPL_H__
#define __NW_TRANSROTATION_ATTRIBUTE_IMPL_H__

#include "NwTransRotationAttribute.h"
#include "NwAttributeImpl.h"
#include "Ge/GeQuaternion.h"

class OdNwTransRotationAttributeImpl : public OdNwAttributeImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwTransRotationAttribute)
public:
  OdNwTransRotationAttributeImpl();
  virtual ~OdNwTransRotationAttributeImpl();
  ODRX_DECLARE_MEMBERS(OdNwTransRotationAttributeImpl);

public:
  static OdNwTransRotationAttributeImpl* getImpl(const OdNwTransRotationAttribute* pNwTransRot);
  static OdNwTransRotationAttributeImpl* getImpl(const OdRxObject* pRxTransRot);

public:
  const OdGeQuaternion& getRotation() const;
  const OdGeVector3d& getTranslation() const;

public:
  void setRotation(const OdGeQuaternion& rot);
  void setTranslation(const OdGeVector3d& trans);

protected:
  OdGeVector3d m_Translation;
  OdGeQuaternion m_Rotation;
};



#endif //__NW_TRANSROTATION_ATTRIBUTE_IMPL_H__
