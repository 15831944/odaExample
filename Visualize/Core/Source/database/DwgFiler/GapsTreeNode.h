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

#ifndef GAPS_TREE_NODE_H__INCLUDED
#define GAPS_TREE_NODE_H__INCLUDED

#include "PagesMapEntry.h"

#define STL_USING_VECTOR
#include "OdaSTL.h"

namespace TvIncSaveNamespace
{
  class GapsTree;

  class GapsTreeNode
  {
  public:
    GapsTreeNode(OdUInt32 key, const PagesMapEntryPtrsList::iterator& val, 
      GapsTreeNode* pLeftNode, GapsTreeNode* pRightNode, GapsTreeNode* pParentNode)
      : m_key(key), m_val(val)
      , m_pLeftNode(pLeftNode), m_pRightNode(pRightNode), m_pParentNode(pParentNode)
    {}

    GapsTreeNode* getLeftmostNodeOfSubtree();
    GapsTreeNode* getRightmostNodeOfSubtree();
        
    OdUInt64 getTotalSizeOfSubtreeGaps() const;

    const PagesMapEntryPtrsList::iterator& getNodeValue() const;

    GapsTreeNode* getLeft() const;
    GapsTreeNode* getRight() const;
    GapsTreeNode* getParent() const;

  private:
    OdUInt32 m_key;
    PagesMapEntryPtrsList::iterator m_val;

    GapsTreeNode* m_pLeftNode;
    GapsTreeNode* m_pRightNode;
    GapsTreeNode* m_pParentNode;

    friend class GapsTree;
  };
};

#endif
