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

#ifndef __NW_NODE_OVERRIDES_ELEMENT_IMPL_H__
#define __NW_NODE_OVERRIDES_ELEMENT_IMPL_H__

#include "NwNodeOverridesElement.h"
#include "NwObjectImpl.h"
#include <unordered_map>

namespace std
{
  template<> struct hash<OdNwObjectId>
  {
    std::size_t operator()(OdNwObjectId const& objectId) const noexcept
    {
      return std::hash<OdUInt64>{}(objectId.getHandle());
    }
  };
}

class OdNwNodeOverridesElementImpl : public OdNwObjectImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwNodeOverridesElement)
public:
  OdNwNodeOverridesElementImpl();
  virtual ~OdNwNodeOverridesElementImpl();
  ODRX_DECLARE_MEMBERS(OdNwNodeOverridesElementImpl);

public:
  static OdNwNodeOverridesElementImpl* getImpl(const OdNwNodeOverridesElement* pNwNode);
  static OdNwNodeOverridesElementImpl* getImpl(const OdRxObject* pRxNode);

public:
  OdResult getHiddens(OdNwObjectIdArray& aHidenNodes) const;
  OdResult getRequireds(OdNwObjectIdArray& aReqNodes) const;
  bool isNodeHidden(const OdNwObjectId& miId) const;
  bool isNodeRequired(const OdNwObjectId& miId) const;

public:
  void setIsNodeHidden(const OdNwObjectId& miId, bool isHidden);

public:
  inline std::unordered_map<OdNwObjectId, OdUInt32>& getPathLinkBitFields() { return m_umPathLinkBitFields; }

private:
  std::unordered_map<OdNwObjectId, OdUInt32> m_umPathLinkBitFields;
};



#endif //__NW_NODE_OVERRIDES_ELEMENT_IMPL_H__
