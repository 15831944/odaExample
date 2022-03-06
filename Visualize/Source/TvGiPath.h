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


#ifndef _ODTV_GIPATH_H_INCLUDED_
#define _ODTV_GIPATH_H_INCLUDED_

#include "TD_PackPush.h"

#include "GiPathNode.h"
#include "Gs/Gs.h"
#include "DbObject.h"

#include "TvEntity.h"
#include "TvSelection.h"
#include "TvBlockTableRecordImpl.h"
//***************************************************************************//
// 'OdTvGiPath' class
//***************************************************************************//

class OdTvGiPath
{
  struct Node : OdGiPathNode
  {
    const Node*       m_pParent;
    OdDbStub*         m_pId;
    OdGiDrawablePtr   m_pDrawable;
    OdGsMarker        m_gsMarker;

    const OdGiPathNode* parent() const { return m_pParent; }
    OdDbStub* persistentDrawableId() const { return m_pId; }
    const OdGiDrawable* transientDrawable() const { return m_pDrawable; }
    OdGsMarker selectionMarker() const { return m_gsMarker; }
  };
  const Node* m_pLeaf;

  void add(const OdGiDrawable* pDrawable, const OdTvDbObjectId& drawableId, OdGsMarker gsMarker = -1)
  {
    Node* pNode = new Node();
    pNode->m_pParent = m_pLeaf;
    m_pLeaf = pNode;

    pNode->m_pDrawable = pDrawable;
    pNode->m_pId = drawableId;
    pNode->m_gsMarker = gsMarker;
    m_depth++;
  }

  Node* addToBegin(Node* pBeginNode, const OdTvDbObjectId& drawableId, OdGsMarker gsMarker = -1)
  {
    Node* pNode = new Node();
    if (pBeginNode)
      pBeginNode->m_pParent = pNode;
    else
      m_pLeaf = pNode;

    pNode->m_pDrawable = 0;
    pNode->m_pId = drawableId;
    pNode->m_gsMarker = gsMarker;

    return pNode;
  }

  std::set< OdGsMarker > m_markers; //markers
  OdUInt32 m_depth;
public:
  OdTvGiPath();
  OdTvGiPath(const OdTvGiPath* pPath, OdUInt32 nOffset);
  ~OdTvGiPath();

  void clear()
  {
    while (m_pLeaf)
    {
      const Node* pNode = m_pLeaf;
      m_pLeaf = pNode->m_pParent;
      delete pNode;
    }
    m_pLeaf = NULL;
    m_depth = 0;
  }

  void addNode(const OdTvDbObjectId& drawableId, OdGsMarker gsMarker = kNullSubentIndex)
  {
    add(0, drawableId, gsMarker);
  }

  void removeLeafs(OdUInt32 nLevels)
  {
    if (nLevels == 0)
      return;

    m_depth -= nLevels;

    while (nLevels > 0 && m_pLeaf)
    {
      const Node* pNode = m_pLeaf;
      m_pLeaf = m_pLeaf->m_pParent;
      delete pNode;
      nLevels--;
    }
  }

  operator const OdGiPathNode&() const
  {
    return *m_pLeaf;
  }
  operator const OdGiPathNode*() const
  {
    return m_pLeaf;
  }

  OdGsMarker getLeafSelectionMarker() const
  {
    if (m_pLeaf)
      return m_pLeaf->m_gsMarker;

    return kNullSubentIndex;
  }

  OdUInt32 getDepth() const
  {
    return m_depth;
  }

  void setSelectionMarkerForLeaf(OdGsMarker marker)
  {
    if (m_pLeaf)
      const_cast<Node*>(m_pLeaf)->m_gsMarker = marker;
  }

  OdGsMarker resetSelectionMarkerForLeaf()
  {
    OdGsMarker res = 0;
    if (m_pLeaf)
    {
      res = m_pLeaf->m_gsMarker;
      const_cast<Node*>(m_pLeaf)->m_gsMarker = kNullSubentIndex;
    }

    return res;
  }

  bool operator <  (const OdTvGiPath* val) const
  {
    //here we will not take into account markers since we want ot accumulate them
    if (m_depth < val->m_depth) return true;
    if (m_depth > val->m_depth) return false;

    if (m_depth == 0 && val->m_depth == 0)
      return false;

    //we don't compare markers since we always suppose that marker is 0. All markers is placed at last node in std::set
    const OdTvGiPath::Node* pCurVal = val->m_pLeaf;
    const OdTvGiPath::Node* pCur = m_pLeaf;
    while (pCur && pCurVal)
    {
      if (pCur->m_pId < pCurVal->m_pId)
        return true;
      else if (pCur->m_pId == pCurVal->m_pId)
      {
        if (!pCur->m_pId && (pCur->m_pDrawable.get() < pCurVal->m_pDrawable.get()))
          return true;
      }
      pCur = pCur->m_pParent;
      pCurVal = pCurVal->m_pParent;
    }

    return false;
  }

  bool isEmpty() const { return m_pLeaf != NULL; }

  /** \details
  Converts subGeomIndexes to Gs markers
  */
  static bool convertSubGeomIndexesToMarkers(const OdTvSubItemPath& path, OdArray< OdGsMarker >& markers);
  /** \details
  Build OdTvGiPath from OdTvSubItemPath
  */
  static OdTvResult buildGiPath(const OdTvEntityId& id, const OdTvSubItemPath& path, OdTvGiPath* pGiPath, bool bForCollide = false);
  /** \details
  Build OdTvGiPath from OdTvSubItemPath with array of subgeometry indexes and retrun array of GsMarkers
  */
  static OdTvResult buildGiPathIndexes(const OdTvEntityId& id, const OdTvSubItemPath& path, OdTvGiPath* pGiPath, OdArray< OdGsMarker >& markers);
  /** \details
  Build OdTvGiPath from OdTvSubItemPath for collide
  */
  static OdTvResult buildGiPathForCollide(const OdTvEntityId& id, const OdTvSubItemPath& path, OdTvGiPath* pTvGiPath);
  /** \details
  Check OdTvSubItemPath
  */
  static OdTvBlockTableRecordPtr checkTvSubItemPath(const OdTvEntityId& id, const OdTvSubItemPath& path, OdTvResult* rc);

  static OdTvGiPath* createGiPath(OdDbStub* modelId, const OdTvEntityId& id, const OdTvSubItemPath& path, OdArray< OdGsMarker >& markers);

  std::set< OdGsMarker >& getMarkers() { return m_markers; }
  const   std::set< OdGsMarker >& getMarkers() const { return m_markers; }

  void getMarkersAsArray(OdArray< OdGsMarker >& markers)
  {
    markers.clear();
    if (m_markers.size() > 0)
    {
      markers.reserve((unsigned int)m_markers.size());
      for (std::set< OdGsMarker >::iterator markIt = m_markers.begin(); markIt != m_markers.end(); ++markIt)
      {
        markers.push_back(*markIt);
      }
    }
  }

  void addMarker(const OdGsMarker& marker)
  {
    m_markers.insert(marker);
  }

  void addMarkers(const OdArray< OdGsMarker >& markers)
  {
    for (OdUInt32 i = 0; i < markers.size(); i++)
      m_markers.insert(markers[i]);
  }

  bool removeMarker(const OdGsMarker& marker)
  {
    return m_markers.erase(marker) > 0;
  }

  OdUInt32 removeMarkers(const OdArray< OdGsMarker >& markers)
  {
    OdUInt32 nErased = 0;
    for (OdUInt32 i = 0; i < markers.size(); i++)
    {
      nErased += (OdUInt32)m_markers.erase(markers[i]);
    }
    return nErased;
  }

  void resetMarkers(const OdArray< OdGsMarker >& markers)
  {
    m_markers.clear();
    for (OdUInt32 i = 0; i < markers.size(); i++)
      m_markers.insert(markers[i]);
  }

  OdUInt64 getObjectSize() const
  {
    OdUInt64 res = 0;

    res += sizeof(*this);

    res += 56; //40 + 16 initial size for std::set

    res += 40 * m_markers.size(); // each add in the set is equal to 40 bytes

    const Node* pNode = m_pLeaf;
    while (pNode)
    {
      pNode = pNode->m_pParent;
      res += sizeof(Node);
    }

    return res;
  }
};

struct OdTvGiPathPtrCmp
{
  bool operator()(const OdTvGiPath* d1, const OdTvGiPath* d2) const
  {
    return d1->operator<(d2);
  }
};

typedef OdArray<OdTvGiPath*> OdTvGiPathArray;
typedef std::set<OdTvGiPath*, OdTvGiPathPtrCmp> OdTvGiPathSet;

#include "TD_PackPop.h"

#endif // _ODTV_GIPATH_H_INCLUDED_

