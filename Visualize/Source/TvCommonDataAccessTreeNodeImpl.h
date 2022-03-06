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

#ifndef _ODTV_COMMONDATAACCESS_TREE_NODE_IMPL_H_INCLUDED_ 
#define _ODTV_COMMONDATAACCESS_TREE_NODE_IMPL_H_INCLUDED_

#include "OdaCommon.h"

#include "TvCommonDataAccessTreeNode.h"
#include "RxModelTreeBaseNodeImpl.h"
#include "RxModelTreeBaseNode.h"
#include "TvSelection.h"
#include "TvEntityImpl.h"
#include "TvCommonDataAccessTreeImpl.h"


class OdTvModelTreeNodeImpl : public OdRxModelTreeBaseNodeImpl
{
public:
  OdTvModelTreeNodeImpl()
    : OdRxModelTreeBaseNodeImpl()
    , m_iFlag(OdTvCDATreeNode::kShouldGroup)
    , m_pTree(NULL)
  {

  }

  virtual ~OdTvModelTreeNodeImpl()
  {
  }

  virtual OdTvEntityIdsArray  getTvEntitiesIds() const;
  virtual OdTvEntityId        getTvEntityId(const OdTvGsViewId& viewId) const;
  virtual OdTvResult          addTvEntityId(OdTvEntityId id);

  void outFields(OdBaseHierarchyTreeFiler* pFiler) const;
  OdResult inFields(OdBaseHierarchyTreeFiler* pFiler, std::set<OdString>& string_storage);

  virtual OdTvSelectionSetPtr select(const OdTvGsViewId& viewId, const OdTvCDATreeNodePtrArray* parentsPath = NULL);
  virtual OdTvResult isolate(const OdTvGsViewId& viewId);
  virtual OdTvResult hide(const OdTvGsViewId& viewId);

  virtual void setInvisible(bool bInvisible);
  virtual bool getInvisible() const;
  virtual void setExploded(bool bExploded);
  virtual bool getExploded() const;
  virtual void setNeedGroup(bool bNeedGroup);
  virtual bool getNeedGroup() const;
  virtual void setAlwaysGroup(bool bShouldGroup);
  virtual bool getAlwaysGroup() const;

  virtual void setViewportObject(const OdTvGsViewId& viewportId);
  virtual OdTvGsViewId getViewportObject() const;

  virtual void setSiblingNode(const OdTvCDATreeNodePtr& pNode);
  virtual OdTvCDATreeNodePtr getSiblingNode() const;

  virtual OdTvModelId getTvModelId() const;
  virtual void setTvModelId(const OdTvModelId& id);

  void setTree(OdTvCDATreeImpl* pTree) { m_pTree = pTree; }

protected:

  virtual bool operator ==(const OdTvModelTreeNodeImpl* other);
  void addChildrenToSelectionSet(OdTvSelectionSetPtr& pSSet) const;
  
  //for block/inserts
  bool                    isEntityFromBlock(OdTvEntityId id) const;
  bool                    isEntityVisibleInView(OdTvEntityId id, OdTvGsViewId viewId) const;
  void                    getFullEntitiesPath(OdTvEntityIdsArray& entitesIds, const OdTvCDATreeNodePtrArray* parentsPath = NULL);
  OdTvModelTreeNodeImpl*  getParentInsertNode(const OdTvCDATreeNodePtrArray* parentsPath, int& curPatPathInd);

protected:

  OdTvEntityIdsArray      m_tvEntitiesIds;
  OdUInt8                 m_iFlag;
  OdTvGsViewId            m_viewportId;
  OdTvModelId             m_modelId;
  OdTvCDATreeImpl*        m_pTree;
  OdTvCDATreeNodePtr      m_pSiblingNode;
};


#endif // _ODTV_COMMONDATAACCESS_TREE_NODE_IMPL_H_INCLUDED_
