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

#ifndef __NW_GEOMETRY_MODEL_ITEM_NODE_IMPL_H__
#define __NW_GEOMETRY_MODEL_ITEM_NODE_IMPL_H__

#include "NwGeometryModelItemNode.h"
#include "NwModelItemNodeImpl.h"

class NWDBEXPORT OdNwGeometryModelItemNodeImpl : public OdNwModelItemNodeImpl
{
  ODNW_DECLARE_FRIEND_FOR_IMPL(OdNwGeometryModelItemNode)
public:
  OdNwGeometryModelItemNodeImpl();
  virtual ~OdNwGeometryModelItemNodeImpl();
  ODRX_DECLARE_MEMBERS(OdNwGeometryModelItemNodeImpl);

public:
  static OdNwGeometryModelItemNodeImpl* getImpl(const OdNwGeometryModelItemNode* pNwGeom);
  static OdNwGeometryModelItemNodeImpl* getImpl(const OdRxObject* pRxGeom);
};



#endif //__NW_GEOMETRY_MODEL_ITEM_NODE_IMPL_H__