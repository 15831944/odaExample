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

#ifndef GAPS_TREE_H__INCLUDED
#define GAPS_TREE_H__INCLUDED

#include "GapsTreeNode.h"

namespace IncSaveNamespace
{
  class DBIO_EXPORT GapsTree
  {  
  public:
    GapsTree();
    virtual ~GapsTree();

    GapsTreeNode* insertNode(OdUInt32 key, const PagesMapEntryPtrsList::iterator& val);

    GapsTreeNode* findNodeIfGapSizeEqual(OdUInt32 gapSize) const;
    GapsTreeNode* findNodeIfGapSizeGreaterOrEqual(OdUInt32 newPageSize) const;
    
    void deleteNode(GapsTreeNode* pNode);

    GapsTreeNode* getRoot() const;
    OdUInt32 getNodesQty() const;
    OdUInt64 getTotalSizeOfGaps() const;

  private:
    GapsTree(const GapsTree& tree);
    GapsTree& operator= (const GapsTree& rhs);

  protected:  
    GapsTreeNode* createNode(OdUInt32 key, const PagesMapEntryPtrsList::iterator& val, 
      GapsTreeNode* pLeftNode = NULL, 
      GapsTreeNode* pRightNode = NULL, 
      GapsTreeNode* pParentNode = NULL);

    void freeNode(GapsTreeNode* pNode);
    void deleteTree(GapsTreeNode* pNode);

  public:
    void clear();

  protected:
    GapsTreeNode* m_pRoot;
    GapsTreeNode* m_pCurrent;
    OdUInt32 m_nodesQty;
  };
};

#endif
