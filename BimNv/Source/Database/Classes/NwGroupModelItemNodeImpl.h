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

#ifndef __NW_GROUP_MODEL_ITEM_NODE_IMPL_H__
#define __NW_GROUP_MODEL_ITEM_NODE_IMPL_H__

#include "NwGroupModelItemNode.h"
#include "NwModelItemNodeImpl.h"

class NWDBEXPORT OdNwGroupModelItemNodeImpl : public OdNwModelItemNodeImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGroupModelItemNode)
public:
  OdNwGroupModelItemNodeImpl();
  virtual ~OdNwGroupModelItemNodeImpl();
  ODRX_DECLARE_MEMBERS(OdNwGroupModelItemNodeImpl);

public:
  static OdNwGroupModelItemNodeImpl* getImpl(const OdNwGroupModelItemNode* pNwGMIN);
  static OdNwGroupModelItemNodeImpl* getImpl(const OdRxObject* pRxGMIN);

public:
  OdNwModelItemNodePtr addPartition(OdInt32 pos);
  OdNwModelItemNodePtr addGroup(OdInt32 pos);
  OdNwModelItemNodePtr addGeometry(OdInt32 pos);
private:
  template <typename T, typename U>
  OdNwModelItemNodePtr addNode(OdUInt32 pos);

public:
  std::vector<OdNwObjectPtr>& getChildren();

protected:
  std::vector<OdNwObjectPtr> m_vChildren;
};



#endif //__NW_GROUP_MODEL_ITEM_NODE_IMPL_H__
