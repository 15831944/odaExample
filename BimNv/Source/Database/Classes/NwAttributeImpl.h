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

#ifndef __NW_ATTRIBUTE_IMPL_H__
#define __NW_ATTRIBUTE_IMPL_H__

#include "NwAttribute.h"
#include "NwModelBaseImpl.h"
#include "SharedPtr.h"

class NWDBEXPORT OdNwAttributeImpl : public OdNwModelBaseImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwAttribute)
public:
  OdNwAttributeImpl();
  virtual ~OdNwAttributeImpl();
  ODRX_DECLARE_MEMBERS(OdNwAttributeImpl);

public:
  static OdNwAttributeImpl* getImpl(const OdNwAttribute* pNwAttr);
  static OdNwAttributeImpl* getImpl(const OdRxObject* pRxAttr);

public:
  inline OdUInt32& getAttrFlags() { return m_flags; }
  inline OdSharedPtr<OdArray<OdNwModelBasePtr> >& getOwners() { return m_pOwners; }
  inline OdUInt32& getPartPropsRefCount() { return m_partPropsRefCount; }

  inline const OdNwObjectImpl* getOwnerModelItemNode() const { return m_pTempOwner; }
  inline void setOwnerModelItemNode(const OdNwObjectImpl* pOwner) { m_pTempOwner = pOwner; }

  //flags methods:
  inline bool isInternal() const               { return m_flags & 0x2000000; }
  inline bool isRenderAttribute() const        { return m_flags & 0x1000000; }
  inline bool isDynamicRenderAttribute() const { return m_flags & 0x1000000 && !m_pOwners.isNull(); }
  //render attribute flags methods:
  inline bool isDynamic() const                { return !m_pOwners.isNull(); }
  inline bool isModified() const               { return m_flags & 0xFFFF; }

protected:
  OdUInt32 m_partPropsRefCount;
  OdUInt32 m_flags;
  OdSharedPtr<OdArray<OdNwModelBasePtr> > m_pOwners;
  const OdNwObjectImpl* m_pTempOwner;//it's member is not a part of attribute structure, it's temporary solution for make link between attribute object and model item node
};



#endif //__NW_ATTRIBUTE_IMPL_H__
