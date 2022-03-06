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




#ifndef _ODDBOBJECTIDGRAPH_H_INCLUDED_
#define _ODDBOBJECTIDGRAPH_H_INCLUDED_

#include "TD_PackPush.h"

#include "OdaDefs.h"
#include "DbGraph.h"

class OdTvDbObjectIdGraphNode;
typedef OdSmartPtr<OdTvDbObjectIdGraphNode> OdTvDbObjectIdGraphNodePtr;

/** <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbObjectIdGraphNode : public OdTvDbGraphNode
{
  OdTvDbObjectId m_Id;
public:
  ODRX_DECLARE_MEMBERS(OdTvDbObjectIdGraphNode);
  OdTvDbObjectIdGraphNode() : OdTvDbGraphNode(){}
  virtual ~OdTvDbObjectIdGraphNode();
  OdTvDbObjectId id() const { return m_Id; }
  void setId(OdTvDbObjectId id){ m_Id = id;}
  static OdTvDbObjectIdGraphNodePtr createObject(OdTvDbObjectId id)
  {
    OdTvDbObjectIdGraphNodePtr res = createObject();
    res->setId(id);
    return res;
  }
};

/** <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbObjectIdGraph : public OdTvDbGraph
{
public:
  OdTvDbObjectIdGraph(){}
  virtual ~OdTvDbObjectIdGraph();
  OdTvDbObjectIdGraphNode* findNode(OdTvDbObjectId) const;
  OdTvDbObjectIdGraphNode* idNode(int idx) const { return (OdTvDbObjectIdGraphNode*)node(idx); }
};
#include "TD_PackPop.h"

#endif // _ODDBOBJECTIDGRAPH_H_INCLUDED_
