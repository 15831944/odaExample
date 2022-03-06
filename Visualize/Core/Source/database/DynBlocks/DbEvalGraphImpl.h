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
  return static_cast<ClassName##Impl*>( OdTvDbSystemInternals::getImpl( pObj ) );\
  }

class OdTvDbEvalGraphImpl : public OdTvDbObjectImpl
{
public:
  struct NodeInfo
  {
    NodeInfo();
    NodeInfo( const OdTvDbObjectId& exp, int id );
    OdTvDbEvalNodeId m_nId;
    OdTvDbHardOwnershipId m_pExprId;
    bool m_bActive;
    int m_nFirstIn;
    int m_nLastIn;
    int m_nFirstOut;
    int m_nLastOut;
  };
  OdArray<NodeInfo> m_Nodes;
  OdTvDbEvalNodeId m_nLastNode;
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
  OdTvDbObjectId m_DBROBlockId;
  OdTvDbObjectId getOwnerBlockId();

public:
  OdTvDbEvalNodeId getNodeIdInternal(int index){ return m_Nodes[index].m_nId; }
  //OdTvDbObjectId getNodeInternal(int index){ return m_Nodes[index].m_pExprId; }
  int getNodeIndex( OdTvDbEvalNodeId id) const;
  EdgeInfo* getEdgeInfoInternal(OdTvDbEvalNodeId from, OdTvDbEvalNodeId to);
  void rebuildTopology(); // rebuild lists
  bool addEdge( const OdTvDbEvalNodeId& idFrom, const OdTvDbEvalNodeId& idTo );
  void deactivate();
  bool activate( const OdTvDbEvalNodeIdArray& activatedNodes );
  bool hasActiveCycles( OdTvDbEvalNodeIdArray* pCycleNodes );
  void makeDBROList(OdTvDbDatabase* pDb);
  OdTvDbEvalGraphImpl() 
    : m_nLastNode(0)
    , m_isDBROContent(true)
  {
  }
  ~OdTvDbEvalGraphImpl();
  DECLARE_GET_IMPL(OdTvDbEvalGraph);

  virtual void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
};

class DYNBLOCKS_EXPORT OdTvDbEvalExprImpl : public OdTvDbObjectImpl
{
  friend class OdTvDbEvalGraph;
  friend class OdTvDbEvalExpr;
protected:
  int unkMinus1;
  OdTvDbEvalNodeId m_nNodeId;
  OdInt32 m_nVersionMajor;
  OdInt32 m_nVersionMinor;
  OdTvDbEvalGraph* m_pGraph;
public:
  OdTvDbEvalExprImpl() : m_pGraph(0), m_nNodeId(0) , m_nVersionMajor(OdDb::kDHL_CURRENT), m_nVersionMinor(OdDb::kMRelease1), unkMinus1(-1){}
  OdTvDbEvalGraphPtr getGraph( OdDb::OpenMode m = OdDb::kForRead ) const
  {
    if (isDBRO())
      return ownerId().safeOpenObject(m); 
    else
      return m_pGraph;
  }

  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion ver);

  DECLARE_GET_IMPL(OdTvDbEvalExpr);
};


#endif //_DbEvalGraphImpl_h_Included_
