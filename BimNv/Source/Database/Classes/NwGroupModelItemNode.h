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

#ifndef __TNW_GROUP_MODEL_ITEM_NODE_H__
#define __TNW_GROUP_MODEL_ITEM_NODE_H__

#include "NwModelItemNode.h"

class NWDBEXPORT OdNwGroupModelItemNode : public OdNwModelItemNode
{
  ODRX_DECLARE_MEMBERS(OdNwGroupModelItemNode);

public:
  OdNwGroupModelItemNode();
  explicit OdNwGroupModelItemNode(OdNwObjectImpl* pImpl);

public:
  virtual ~OdNwGroupModelItemNode();

public:
  //VAS: those methods is add new modelitemnode to childrens array with pos value, if pos is -1 - then adding will be in the end of array
  OdNwModelItemNodePtr addPartition(OdInt32 pos = -1);
  OdNwModelItemNodePtr addGroup(OdInt32 pos = -1);
  OdNwModelItemNodePtr addGeometry(OdInt32 pos = -1);
};

typedef OdSmartPtr<OdNwGroupModelItemNode> OdNwGroupModelItemPtr;

#endif //__TNW_GROUP_MODEL_ITEM_NODE_H__
