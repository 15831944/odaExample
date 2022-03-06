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
#ifndef __NW_SPATIALHIERARCHYSTREAMSAVER_H__
#define __NW_SPATIALHIERARCHYSTREAMSAVER_H__

#include "NwStreamSaver.h"
#include "NwStreamContext.h"
#include "TD_PackPush.h"

class OdNwTreeItem;
typedef OdSmartPtr<OdNwTreeItem> OdNwTreeItemPtr;

class OdNwSpatialHierarchyStreamSaver : public OdNwStreamSaver
{
public:
  OdNwSpatialHierarchyStreamSaver(const OdNwStreamContextPtr& ctx);
  virtual ~OdNwSpatialHierarchyStreamSaver();
  virtual OdResult saveToStream();

public:
  void setRootTreeItem(OdNwTreeItemPtr pRoot);
  void setFragmentIndexes(std::map<OdNwObjectId, OdUInt32>&& mFragmentIndexes);

private:
  OdNwTreeItemPtr m_pRootTreeItem;
  std::map<OdNwObjectId, OdUInt32> m_mFragmentIndexes;
};

typedef std::shared_ptr<OdNwSpatialHierarchyStreamSaver> OdNwSpatialHierarchyStreamSaverPtr;
typedef std::weak_ptr<OdNwSpatialHierarchyStreamSaver> OdNwSpatialHierarchyStreamSaverWeakPtr;

#include "TD_PackPop.h"

#endif // __NW_SPATIALHIERARCHYSTREAMSAVER_H__
