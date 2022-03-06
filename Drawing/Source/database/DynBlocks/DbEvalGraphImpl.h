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

#ifndef _DbEvalGraphImpl_h_Included_
#define _DbEvalGraphImpl_h_Included_

#include "../Objects/DbObjectImpl.h"
#include "DbEvalGraph.h"
#include "Ge/GePoint3dArray.h"
#include "IntArray.h"

#define DECLARE_GET_IMPL(ClassName)\
  static ClassName##Impl* getImpl( const ClassName* pObj )\
  {\
  return static_cast<ClassName##Impl*>( OdDbSystemInternals::getImpl( pObj ) );\
  }

class OdDbEvalIdMapImpl :  public OdDbEvalIdMap
{
public:
  OdDbEvalIdMapImpl() {};
  ~OdDbEvalIdMapImpl() {};

  virtual OdDbEvalNodeId find(const OdDbEvalNodeId& key);
  virtual void kill();
  void insert(unsigned int nFirst, unsigned int nSecond);

private:
  std::map <unsigned int, unsigned int> m_mapId;
};

class OdDbEvalGraphImpl : public OdDbObjectImpl
{
public:
  struct NodeInfo
  {
    NodeInfo();
    NodeInfo( const OdDbObjectId& exp, int id );
    OdDbEvalNodeId m_nId;
    OdDbHardOwnershipId m_pExprId;
    bool m_bActive;
    int m_nFirstIn;
    int m_nLastIn;
    int m_nFirstOut;
    int m_nLastOut;
  };
  OdArray<NodeInfo> m_Nodes;
  OdDbEvalNodeId m_nLastNode;
  enum EdgeFlags{ kSuppressed = 2, kInvertible = 4 };
  struct EdgeInfo
  {
    EdgeInfo();
    int m_nIdFrom;
    int m_nIdTo;
    long m_nFlags;
    unsigned long m_nRefCount;
    int m_nPrevIn;
    int m_nNextIn;
    int m_nPrevOut;
    int m_nNextOut;
    int m_nReverse;
  };
  OdArray<EdgeInfo> m_Edges;
  OdIntArray m_pActiveSubgraph;
  bool m_isDBROContent;
  OdDbObjectId m_DBROBlockId;
  OdDbObjectId getOwnerBlockId();

public:
  OdDbEvalNodeId getNodeIdInternal(int index){ return m_Nodes[index].m_nId; }
  //OdDbObjectId getNodeInternal(int index){ return m_Nodes[index].m_pExprId; }
  int getNodeIndex( OdDbEvalNodeId id) const;
  EdgeInfo* getEdgeInfoInternal(OdDbEvalNodeId from, OdDbEvalNodeId to);
  void rebuildTopology(); // rebuild lists
  bool addEdge( const OdDbEvalNodeId& idFrom, const OdDbEvalNodeId& idTo );
  void deactivate();
  bool activate( const OdDbEvalNodeIdArray& activatedNodes );
  bool hasActiveCycles( OdDbEvalNodeIdArray* pCycleNodes );
  void makeDBROList(OdDbDatabase* pDb);
  OdDbEvalGraphImpl() 
    : m_nLastNode(0)
    , m_isDBROContent(true)
  {
  }
  ~OdDbEvalGraphImpl();
  DECLARE_GET_IMPL(OdDbEvalGraph);

  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
};

class DYNBLOCKS_EXPORT OdDbEvalExprImpl : public OdDbObjectImpl
{
  friend class OdDbEvalGraph;
  friend class OdDbEvalExpr;
protected:
  int unkMinus1;
  OdDbEvalNodeId m_nNodeId;
  OdInt32 m_nVersionMajor;
  OdInt32 m_nVersionMinor;
  OdDbEvalGraph* m_pGraph;
public:
  OdDbEvalExprImpl() : m_pGraph(0), m_nNodeId(0) , m_nVersionMajor(OdDb::kDHL_CURRENT), m_nVersionMinor(OdDb::kMRelease1), unkMinus1(-1){}
  OdDbEvalGraphPtr getGraph( OdDb::OpenMode m = OdDb::kForRead ) const
  {
    if (isDBRO())
      return ownerId().safeOpenObject(m); 
    else
      return m_pGraph;
  }

  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion ver);
  void remappedNodeIds(OdDbEvalIdMap& idMap) { return; };
  DECLARE_GET_IMPL(OdDbEvalExpr);
};


#endif //_DbEvalGraphImpl_h_Included_
