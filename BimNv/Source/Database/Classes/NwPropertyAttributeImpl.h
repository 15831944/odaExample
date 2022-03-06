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

#ifndef __NW_PROPERTY_ATTRIBUTE_IMPL_H__
#define __NW_PROPERTY_ATTRIBUTE_IMPL_H__

#include "NwPropertyAttribute.h"
#include "NwAttributeImpl.h"
#define STL_USING_VECTOR
#define STL_USING_MEMORY
#include "OdaSTL.h"

class OdNwData;
typedef std::shared_ptr<OdNwData> OdNwDataPtr;

class NWDBEXPORT OdNwPropertyAttributeImpl : public OdNwAttributeImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwPropertyAttribute)
  using OdNwDataNamePropetry = std::pair<OdNwNamePtr, OdNwDataPtr>;
public:
  OdNwPropertyAttributeImpl();
  virtual ~OdNwPropertyAttributeImpl();
  ODRX_DECLARE_MEMBERS(OdNwPropertyAttributeImpl);

public:
  static OdNwPropertyAttributeImpl* getImpl(const OdNwPropertyAttribute* pNwPropAttr);
  static OdNwPropertyAttributeImpl* getImpl(const OdRxObject* pRxPropAttr);

public:
  inline std::vector<OdNwDataNamePropetry>& getProperties() { return m_vProperty; }
  OdResult getProperties(OdArray<OdNwPropertyPtr>& aProperties);

protected:
  std::vector<OdNwDataNamePropetry> m_vProperty;
};

typedef OdSmartPtr<OdNwPropertyAttributeImpl> OdNwPropertyAttributeImplPtr;

#endif //__NW_PROPERTY_ATTRIBUTE_IMPL_H__
