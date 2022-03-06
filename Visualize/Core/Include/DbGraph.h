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




#ifndef _ODDBGRAPH_H_INCLUDED_
#define _ODDBGRAPH_H_INCLUDED_

#include "TD_PackPush.h"

#include "OdaDefs.h"
#include "DbExport.h"
#include "RxObject.h"
#include "OdArray.h"

class OdTvDbGraph;
class OdTvDbGraphNode;

/** \details
    This template class is a specialization of the OdArray class for OdTvDbGraphNode object pointers.
*/
typedef OdArray<OdTvDbGraphNode*, OdMemoryAllocator<OdTvDbGraphNode*> > OdTvDbGraphNodeArray;

/** \details
    This class implements generic node objects for generic graphs.
    
    \remarks
    A graph consists of a collection of nodes bi-directionally linked by directional edges.
    
    An edge connected to a node is represented as a pointer or reference to the node at the other
    end of the edge.
 
    References are classified as either incoming or outgoing. Every incoming reference has
    a corresponding outgoing reference and vice versa.

    Each GraphNode object can have any number of references associated with it, enabling the
    implementation of any graph structure.

    \sa
    
    * OdTvDbGraph
    * OdTvDbGraphStack
    * OdTvDbXrefGraph
    * OdTvDbXrefGraphNode
    
    Corresponding C++ library: TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbGraphNode : public OdRxObject
{
  friend class OdTvDbGraph;
public:
  OdTvDbGraphNode() : m_pData(0), m_flags(0), m_pOwner(0) {}

  ODRX_DECLARE_MEMBERS(OdTvDbGraphNode);

  virtual ~OdTvDbGraphNode();
  
  enum Flags
  {
    kNone         = 0x00, // None.
    kVisited      = 0x01, // Used internally by OdTvDbGraph::findCycles() and while traversing a graphs with cycles.
    kOutsideRefed = 0x02, // Used internally by Xref detach.
    kSelected     = 0x04, // User selection. Set by getOutgoing.
    kInList       = 0x08, // Is *in* list. Set by getOutgoing.
    kListAll      = 0x0E, // Used to *clear* kSelected, kInList, and kOutsideRefed.
    kFirstLevel   = 0x10, // The *node* is connected to the root *node*. Read Only.
    kUnresTree    = 0x20, // The tree is unresolved.
    kAll          = 0x2F  // Used to *clear* all but kFirstLevel.
  };
  
  /** \details
    Returns the data associated with this GraphNode object.
  */
  void* data() const { return m_pData; }

  /** \details
    Sets the data associated with this GraphNode object.
    
    \param pData [in] Pointer to the data.
  */
  void setData(
    void* pData) { m_pData = pData; }
  
  /** \details
    Return the number of outgoing references associated with this GraphNode object.
  */
  int numOut() const { return m_outgoing.size(); }
  
  /** \details
    Return the number of incoming references associated with this GraphNode object.
  */
  int numIn() const { return m_incoming.size(); } 
   
  /** \details
    Returns the specified incoming reference of this GraphNode object.
    
    \param refIndex [in]  Reference index. 
    
    \remarks
    Returns a null pointer if and only if the index is not valid.
  */
  OdTvDbGraphNode* in(
    int refIndex) const { return m_incoming.at(refIndex); }

  /** \details
    Returns the specified outgoing reference of this GraphNode object.
    
    \param refIndex [in]  Reference index. 
    \remarks
    Returns a null pointer if and only if the index is not valid.
  */
  OdTvDbGraphNode* out(
    int refIndex) const { return m_outgoing.at(refIndex); }
  
  /** \details
    Creates an outgoing reference, in this GraphNode object, to the specified GraphNode object.  
    
    \param pTo [in]  Pointer to the outgoing GraphNode.

    \remarks
    Creates an incoming reference to this GraphNode object in *pTo.
    
    Throws:
    OdError(eInvalidOwnerObject) if the specified GraphNode object are not in the same Graph object as this
    GraphNode object.
    
    \sa
    OdTvDbGraph::addEdge
  */
  void addRefTo(
    OdTvDbGraphNode* pTo);
  
  /** \details
    Removes the outgoing reference, in this GraphNode object, to the specified GraphNode object.  
    
    \param pTo [in]  Pointer to the outgoing GraphNode.

    \remarks
    Removes the incoming reference to this GraphNode object in the outgoing GraphNode object.
    
    The specified GraphNode object must be part of the same graph as this GraphNode object.
  */
  void removeRefTo(
    OdTvDbGraphNode* pNode);

  /** \details
    Removes all references in and to this GraphNode object.  
    
    \remarks
    Always called by ~OdTvDbGraphNode().
  */
  void disconnectAll();
  
  /** \details
    Returns the Graph object to which this GraphNode object is attached.
  */
  OdTvDbGraph* owner() const { return m_pOwner; }
  
  /** \details
    Returns true if and only if the all the specified set flag bits are set in this GraphNode object.
    
    \param flags [in]  Flag bits.
    
    \remarks
    flags must be a combination of one or more of the following:
    
    <table>
    Name              Value    Description
    kNone             0x00     None.
    kVisited          0x01     Used internally by OdTvDbGraph::findCycles() and while traversing a graphs with cycles.
    kOutsideRefed     0x02     Used internally by Xref detach.
    kSelected         0x04     User selection. Set by getOutgoing.
    kInList           0x08     Is in list. Set by getOutgoing.
    kListAll          0x0E     Used to clear kSelected, kInList, kOutsideRefed.
    kFirstLevel       0x10     The node is connected to the root node. Read Only.
    kUnresTree        0x20     The tree is unresolved.
    kAll              0x2F     Used to clear all but kFirstLevel.
    </table>
  */
  bool isMarkedAs(
    OdUInt8 flags) const { return ((m_flags & flags)==flags); }
  
  /** \details
    Sets the specified set flag bits in this GraphNode object.
    
    \param flags [in]  Flag bits.
    
    \remarks
    flags must be a combination of one or more of the following:
    
    <table>
    Name              Value    Description
    kNone             0x00     None.
    kVisited          0x01     Used internally by OdTvDbGraph::findCycles() and while traversing a graphs with cycles.
    kOutsideRefed     0x02     Used internally by Xref detach.
    kSelected         0x04     User selection. Set by getOutgoing.
    kInList           0x08     Is in list. Set by getOutgoing.
    kListAll          0x0E     Used to clear kSelected, kInList, kOutsideRefed.
    kFirstLevel       0x10     The node is connected to the root node. Read Only.
    kUnresTree        0x20     The tree is unresolved.
    kAll              0x2F     Used to clear all but kFirstLevel.
    </table>
  */
  void markAs(
    OdUInt8 flags)
  {
    if(!GETBIT(flags, kFirstLevel))
    {
      m_flags |= flags;
    }
    else
    {
      throw OdError(eInvalidInput);
    }
  }

  /** \details
    Clears the specified set flag bits in this GraphNode object.
    
    \param flags [in]  Flag bits.
    
    \remarks
    flags must be a combination of one or more of the following:
    
    <table>
    Name              Value    Description
    kNone             0x00     None.
    kVisited          0x01     Used internally by OdTvDbGraph::findCycles() and while traversing a graphs with cycles.
    kOutsideRefed     0x02     Used internally by Xref detach.
    kSelected         0x04     User selection. Set by getOutgoing.
    kInList           0x08     Is in list. Set by getOutgoing.
    kListAll          0x0E     Used to clear kSelected, kInList, kOutsideRefed.
    kFirstLevel       0x10     The node is connected to the root node. Read Only.
    kUnresTree        0x20     The tree is unresolved.
    kAll              0x2F     Used to clear all but kFirstLevel.
    </table>
  */
  void clear(
    OdUInt8 flags)
  {
    if(!GETBIT(flags, kFirstLevel))
    {
      m_flags &= (~flags);
    }
    else
    {
      throw OdError(eInvalidInput);
    }
  }

    
  /** \details
    Marks this GraphNode object and all nested outgoing GraphNode objects with the specified flags.
    
    \param flags [in]  Flag bits.
    \param pNodeArray [in]  Pointer to a GraphNode array.  

    \remarks
    If pNodeArray is specified, this function appends this GraphNode object and all 
    nested outgoing GraphNode objects, to the specified array. While tranversing a branch,
    if any GraphNode object already has the flag bits set, the branch is no longer followed.

    The user must clear the flags with OdTvDbGraph::clearAll() or OdTvDbGraphNode::clear() when done with them.
    
    flags must be a combination of one or more of the following:
    
    <table>
    Name              Value    Description
    kNone             0x00     None.
    kVisited          0x01     Used internally by OdTvDbGraph::findCycles() and while traversing a graphs with cycles.
    kOutsideRefed     0x02     Used internally by Xref detach.
    kSelected         0x04     User selection. Set by getOutgoing.
    kInList           0x08     Is in list. Set by getOutgoing.
    kListAll          0x0E     Used to clear kSelected, kInList, kOutsideRefed.
    kFirstLevel       0x10     The node is connected to the root node. Read Only.
    kUnresTree        0x20     The tree is unresolved.
    kAll              0x2F     Used to clear all but kFirstLevel.
    </table>
    
    \remarks
    This function is not implemented, and will generate a link error if you reference it.
  */
  void markTree(
    OdUInt8 flags, 
    OdTvDbGraphNodeArray* pNodeArray = 0);
  
  // Circularity detection methods
  
  /** \details
    Returns the number of outgoing cyclical references associated with this GraphNode object.
    
    \remarks
    This function returns valid results only if OdTvDbGraph::findCycles() has been called
    with no intervening changes to the graph.
  */
  int numCycleOut() const { return m_cycleOut.size(); }

  /** \details
    Returns the number of incoming cyclical references associated with this GraphNode object.
    
    \remarks
    This function returns valid results only if OdTvDbGraph::findCycles() has been called
    with no intervening changes to the graph.
  */
  int numCycleIn() const { return m_cycleIn.size(); }
  
  /** \details
    Returns the specified incoming cyclical reference of this GraphNode object.
    
    \param refIndex [in]  Reference index. 

    \returns
    Returns a null pointer if and only if the index is not valid.

    \remarks
    This function returns valid results only if OdTvDbGraph::findCycles() has been called
    with no intervening changes to the graph.
  */
  OdTvDbGraphNode* cycleIn(
    int refIndex) const { return m_cycleIn[refIndex]; }

  /** \details
    Returns the specified outgoing cyclical reference of this GraphNode object.
    
    \param refIndex [in]  Reference index. 

    \returns
    Returns a null pointer if and only if the index is not valid.

    \remarks
    This function returns valid results only if OdTvDbGraph::findCycles() has been called
    with no intervening changes to the graph.
  */
  OdTvDbGraphNode* cycleOut(
    int refIndex) const  { return m_cycleOut[refIndex]; }
  
  /** \details
    Returns the next outgoing cyclical reference of this GraphNode object.
    
    \returns
    This function returns cycleOut(0). Returns a null pointer if cycleOut(0) == 0.

    \remarks
    This function returns valid results only if OdTvDbGraph::findCycles() has been called
    with no intervening changes to the graph.
  */
  OdTvDbGraphNode* nextCycleNode() const { return cycleOut(0); }
  
  /** \details
    Returns true if and only if this GraphNode object is part of a cyclical reference.

    \remarks
    This function returns valid results only if OdTvDbGraph::findCycles() has been called
    with no intervening changes to the graph.
  */
  bool isCycleNode() const { return (numCycleOut() != 0 || numCycleIn() != 0); }
  
private:
  void setOwner(
    OdTvDbGraph* pGraph) 
  {
    if(m_pOwner)
    {
      ODA_FAIL();
      throw OdError(eInvalidOwnerObject);
    }
    m_pOwner = pGraph;
  }
  
  friend struct if_leaf_push_to;
  friend struct clear_cycles;
  friend void break_edge(OdTvDbGraphNode* , OdTvDbGraphNode* );
  
  void*               m_pData;
  OdUInt8             m_flags;
  OdTvDbGraphNodeArray  m_outgoing;
  OdTvDbGraphNodeArray  m_incoming;
  OdTvDbGraph*          m_pOwner;
  OdTvDbGraphNodeArray  m_cycleOut;
  OdTvDbGraphNodeArray  m_cycleIn;
};
/** \details
    This template class is a specialization of the OdSmartPtr class template for OdTvDbGraphNode object pointers.
*/
typedef OdSmartPtr<OdTvDbGraphNode> OdTvDbGraphNodePtr;

/** \details
    This class implements stacks for OdTvDbGraphNode object pointers.
    Corresponding C++ library: TD_Db

    <group OdTvDb_Classes>
*/
class OdTvDbGraphStack
{
public:
  /** \param initPhysicalLength [in]  Initial Physical Length.
      \param initGrowLength [in]  Initial Grow Length.


    \remarks
    Physical Length is the maximum number of entries in this Stack object before it automatically grows.
    
    Grow Length is the number of entries by which the Physical Length will grow as required.
  */
  OdTvDbGraphStack(
    int initPhysicalLength = 0, 
    int initGrowLength = 8)
    : m_stack(initPhysicalLength, initGrowLength) {}

  ~OdTvDbGraphStack() {}

  /** \details
    Pushes the specified GraphNode onto this Stack object.
    
    \param pNode [in]  Pointer to the node to be pushed.
  */
  void push(
    OdTvDbGraphNode* pNode) { m_stack.push_back(pNode); }

  /** \details
    Pops and returns the GraphNode at the top of this Stack object.
    
    \remarks
    Returns a null pointer if this Stack object is empty.
  */
  OdTvDbGraphNode* pop()
  {
    if(!isEmpty())
    {
      OdTvDbGraphNode* pRes = top();
      m_stack.removeLast();
      return pRes;
    }
    return 0;
  }


  /** \details
    Returns the OdTvDbGraphNode at the top of this Stack object.

    \remarks
    Returns a null pointer if this Stack object is empty.
  */
  OdTvDbGraphNode* top() const { return isEmpty() ? 0 : m_stack.last(); }

  /** \details
    Returns true if and only if this Stack object is empty.
  */
  bool isEmpty() const { return m_stack.empty(); }
private:
  OdTvDbGraphNodeArray  m_stack;
};

/** \details
    This class implements generic graph objects.
    
    \remarks
    A graph consists of a collection of nodes bi-directionally linked by directional edges.
    
    An edge connected to a node is represented as a pointer or reference to the node at the other
    end of the edge.
 
    References are classified as either incoming or outgoing. Every incoming reference has
    a corresponding outgoing reference and vice versa.

    Each GraphNode object can have any number of references associated with it, enabling the
    implementation of any graph structure.

    \sa
    * OdTvDbGraphNode
    * OdTvDbGraphStack
    * OdTvDbXrefGraph
    * OdTvDbXrefGraphNode
    
    Corresponding C++ library: TD_Db
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbGraph
{
  friend class OdTvDbGraphNode;
public:
  OdTvDbGraph() : m_bDirty(false), m_nNonCycleNodes(0) {}
  virtual ~OdTvDbGraph();
  
  /** \details
    Returns the specified GraphNode object of this Graph object.
    
    \param nodeIndex [in]  Node index. 
  */
  OdTvDbGraphNode* node(
    int nodeIndex) const { return m_nodes.at(nodeIndex); }
  
  /** \details
    Returns the root (first) GraphNode object of this Graph object.
    
    \remarks
    Returns a null pointer if isEmpty().
  */
  OdTvDbGraphNode* rootNode() const;
  
  /** \details
    Returns the specified incoming reference of this Graph object.
    
    \param refIndex [in]  Reference index. 
  */
  int numNodes() const { return m_nodes.size(); }

  /** \details
    Returns true if and only if this Graph object is empty.
  */
  bool isEmpty() const { return numNodes() == 0; }
  
  /** \details
    Adds the specifed GraphNode object to this Graph object.
    
    \param pNode [in]  Pointer to the GraphNode object.
    
    \remarks
    *pNode must be created with new(), and should not be deleted once added to this Graph object; 
    This Graph object will delete the GraphNode when it is no longer needed.
    
    Throws:
    OdError(eInvalidOwnerObject) if the specified GraphNode object already has an owner.
  */
    void addNode(
    OdTvDbGraphNode* pNode);
  
  /** \details
    Adds the specified edge to this Graph object.

    \param pFrom [in]  Pointer to the GraphNode at the start of the edge.
    \param pTo [in]  Pointer to the GraphNode at the end of the edge.
    
    \remarks
    Creates an outgoing reference to *pTo in *pFrom, and an incoming reference to *pFrom in *pTo. 
        
    Throws:
    OdError(eInvalidOwnerObject) if the specified GraphNode objects are not in the same Graph object.
  */
    void addEdge(
    OdTvDbGraphNode* pFrom, 
    OdTvDbGraphNode* pTo);
  
  /** \details
    Removes the specified node from this GraphNode object, and all references to it. 

    \param pNode [in]  Pointer to the GraphNode object.
  */
    void delNode(
    OdTvDbGraphNode* pNode);
  
  /** \details
    Removes all nodes and cycle nodes from this Graph object.

    \remarks
    Always called by ~OdTvDbGraph().  
  */
  void reset();

  /** \details
    Clears the specified set flag bits in the GraphNode objects of this Graph object.
    
    \param flags [in]  Flag bits.
    
    \remarks
    flags must be a combination of one or more of the following:
    
    <table>
    Name                             Value    Description
    OdTvDbGraphNode::kNone             0x00     None.
    OdTvDbGraphNode::kVisited          0x01     Used internally by OdTvDbGraph::findCycles() and while traversing a graphs with cycles.
    OdTvDbGraphNode::kOutsideRefed     0x02     Used internally by Xref detach.
    OdTvDbGraphNode::kSelected         0x04     User selection. Set by getOutgoing.
    OdTvDbGraphNode::kInList           0x08     Is in list. Set by getOutgoing.
    OdTvDbGraphNode::kListAll          0x0E     Used to clear kSelected, kInList, kOutsideRefed.
    OdTvDbGraphNode::kFirstLevel       0x10     The node is connected to the root node. Read Only.
    OdTvDbGraphNode::kUnresTree        0x20     The tree is unresolved.
    OdTvDbGraphNode::kAll              0x2F     Used to clear all but kFirstLevel.
    </table>

    OdTvDbGraphNode::kListAll and OdTvDbGraphNode::kAll are intended to be used with this function.
  */
  void clearAll(
    OdUInt8 flags);
  
  /** \details
    Adds to the specified array, the nested outgoing GraphNode objects from the specified GraphNode objects.
    \param outgoing [in/out] Array of GraphNode objects. 

    \remarks
    The user must clear the kListAll flags with OdTvDbGraph::clearAll() or OdTvDbGraphNode::clear() when done with them.
  */
  void getOutgoing(
    OdTvDbGraphNodeArray& outgoing);
  
  /** \details
    Finds the cyclical nodes for this Graph object.
    \param pStart [in]  Pointer to the starting node from which to search. Usually defaulted.

    \returns
    Returns true if and only if there are any cyclical GraphNodes.
    
    \remarks
    This function must be called with no intervening changes to the graph, prior to querying cycle information.
  */
  virtual bool findCycles(
    OdTvDbGraphNode* pStart = 0);
  /** \remarks
    Removes the specified edge, and updates the cyclical information for this Graph object.

    \param pFrom [in]  Pointer to the GraphNode at the start of the edge.
    \param pTo [in]  Pointer to the GraphNode at the end of the edge.
  */
  void breakCycleEdge(
    OdTvDbGraphNode* pFrom, 
    OdTvDbGraphNode* pTo);
  
protected:
  /** \details
    Removes all cyclical information determined by findCycles.
    
    \ewmarks
    This function does not remove cyclical edges, and is intended
    only for error cleanup.
    
    \sa
    breakCycleEdge
  */
  void clearAllCycles();
private:
  OdTvDbGraph(
    const OdTvDbGraph&);
  OdTvDbGraph& operator =(
    const OdTvDbGraph&);
  
  void removeLeaves(
    OdTvDbGraphStack& stack);
  void setDirty() { m_bDirty = true; }
  bool isDirty() const { return m_bDirty; }
  bool m_bDirty;
  OdTvDbGraphNodeArray::size_type m_nNonCycleNodes;
  OdTvDbGraphNodeArray m_nodes;
};

#include "TD_PackPop.h"

#endif // _ODDBGRAPH_H_INCLUDED_
