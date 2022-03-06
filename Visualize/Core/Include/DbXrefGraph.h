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




#ifndef _ODDBXREFGRAPH_H_INCLUDED_
#define _ODDBXREFGRAPH_H_INCLUDED_

#include "TD_PackPush.h"

#include "DbGraph.h"
#include "DbObjectId.h"
#include "OdString.h"

/** \details
  
    <group TD_Namespaces>
*/
namespace OdDb
{
  enum XrefStatus
  {
    kXrfNotAnXref     = 0,  // Not an Xref.
    kXrfResolved      = 1,  // Resolved.
    kXrfUnloaded      = 2,  // Unloaded.
    kXrfUnreferenced  = 3,  // Unreferenced.
    kXrfFileNotFound  = 4,  // File Not Found.
    kXrfUnresolved    = 5   // Unresolved.
  };  
}

class OdTvDbXrefGraphNode;
/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbXrefGraphNode object pointers.
*/
typedef OdSmartPtr<OdTvDbXrefGraphNode> OdTvDbXrefGraphNodePtr;

/** \details
    This class is a derived class for representing an Xref database.

    \remarks
    OdTvDbXrefGraph::getFrom() will populate an XrefGraph object with the Xref tree for a specified database.

    \sa
    * OdTvDbGraph
    * OdTvDbGraphStack
    * OdTvDbXrefGraph
    * OdTvDbXrefGraphNode

    Corresponding C++ library: TD_Db
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbXrefGraphNode : public OdTvDbGraphNode
{
protected:
  OdTvDbXrefGraphNode() : m_status(OdDb::kXrfNotAnXref) {}
public:

  ODRX_DECLARE_MEMBERS(OdTvDbXrefGraphNode);

  virtual ~OdTvDbXrefGraphNode();
  
  /** \details
    Returns the name associated with this XrefGraphNode object.
  */
  OdString name() const { return m_sName; }

  /** \details
    Returns the Object ID of the BlockTableRecord associated with this XrefGraphNode object.
  */
  OdTvDbObjectId blockId() const { return m_blockId; }

  /** \details
    Returns the database relevent to this XrefGraphNode object.
  */
  OdTvDbDatabase* database() const { return (OdTvDbDatabase*)data(); }
  
  /** \details
    Sets the name associated with this XrefGraphNode object.
    
    \param name [in]  Name.
  */
  void setName(
    const OdString& name) { m_sName = name; }
    
  /** \details
    Sets the Object ID of the BlockTableRecord associated with this XrefGraphNode object.

    \param blockId [in]  Object ID of BlockTableRecord.
  */
  void setBlockId(
    OdTvDbObjectId blockId) { m_blockId = blockId; }
   
  /** \details
    Sets the database relevent to this XrefGraphNode object.

    \param pDb [in]  Pointer to the database.
  */
  void setDatabase(
    OdTvDbDatabase* pDb) { setData(pDb); }
  
  /** \details
    Returns true if and only if this XrefGraphNode represents an Xref that is not directly referenced
    by the host drawing.
  */
  bool isNested() const { return !isMarkedAs(kFirstLevel); }

  /** \details
    Returns the status for this XrefGraphNode object.
    
    \remarks
    xrefStatus() returns one of the following:

    <table>
    Name                      Value   Description
    OdDb::kXrfNotAnXref       0       Not an Xref.
    OdDb::kXrfResolved        1       Resolved.
    OdDb::kXrfUnloaded        2       Unloaded.
    OdDb::kXrfUnreferenced    3       Unreferenced.
    OdDb::kXrfFileNotFound    4       File Not Found.
    OdDb::kXrfUnresolved      5       Unresolved.
    </table>
      
  */
    OdDb::XrefStatus xrefStatus() const { return m_status; }


  /** \details
    Sets the status for this XrefGraphNode object.
    
    \remarks
    xrefStatus must be one of the following:

    <table>
    Name                      Value   Description
    OdDb::kXrfNotAnXref       0       Not an Xref.
    OdDb::kXrfResolved        1       Resolved.
    OdDb::kXrfUnloaded        2       Unloaded.
    OdDb::kXrfUnreferenced    3       Unreferenced.
    OdDb::kXrfFileNotFound    4       File Not Found.
    OdDb::kXrfUnresolved      5       Unresolved.
    </table>
      
  */
    void setXrefStatus(
    OdDb::XrefStatus xrefStatus) { m_status = xrefStatus; }

  
private:
  OdString          m_sName;
  OdTvDbObjectId      m_blockId;
  OdDb::XrefStatus  m_status;
  // OdTvDbDatabase* uses base class data() member
};


/** \details
    This class is a derived class for representing the Xref tree of a database.
    
    \remarks
    This class uses XrefGraphNode objects to represent an Xref database at each node.

    \sa
    * OdTvDbGraph
    * OdTvDbGraphStack
    * OdTvDbXrefGraph
    * OdTvDbXrefGraphNode

    Corresponding C++ library: TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbXrefGraph : public OdTvDbGraph
{
  OdTvDbXrefGraph(const OdTvDbXrefGraph&);
  OdTvDbXrefGraph& operator =(const OdTvDbXrefGraph&);
public:
  OdTvDbXrefGraph() {}
  virtual ~OdTvDbXrefGraph();
  
  /** \details
    Returns the XrefGraphNode object corresponding to the specified parameter.
    
    \param name [in]  Name.
    
    \returns
    Return a null pointer if the specified node is not found.
    
    \remarks
    getFrom() will populate an XrefGraph object with the Xref tree of a specified database.
  */
  OdTvDbXrefGraphNode* xrefNode(
    const OdString& name) const;
  
  /** \details
    Returns the XrefGraphNode object corresponding to the specified parameter.
    
    \param blockId [in]  Object ID of BlockTableRecord.
    
    \returns
    Return a null pointer if the specified node is not found.
    
    \remarks
    getFrom() will populate an XrefGraph object with the Xref tree of a specified database.
  */
  OdTvDbXrefGraphNode* xrefNode(
    OdTvDbObjectId blockId) const;
  
  /** \details
    Returns the XrefGraphNode object corresponding to the specified parameter.
    
    \param pDb [in]  Pointer to the database.
    
    \returns
    Return a null pointer if the specified node is not found.
    
    \remarks
    getFrom() will populate an XrefGraph object with the Xref tree of a specified database.
  */
  OdTvDbXrefGraphNode* xrefNode(
    const OdTvDbDatabase* pDb) const;
  
  /** \details
    Returns the XrefGraphNode object corresponding to the specified parameter.
    
    \param nodeIndex [in]  Node index. 
    
    \returns
    Return a null pointer if the specified node is not found.
    
    \remarks
    getFrom() will populate an XrefGraph object with the Xref tree of a specified database.
  */
  OdTvDbXrefGraphNode* xrefNode(
    int nodeIndex) const { return(OdTvDbXrefGraphNode*)node(nodeIndex); }
    
  /** \details
    Returns the XrefGraphNode associated with the host drawing of this XrefGraph object.
    
    \remarks
    Returns rootNode().
  */
    OdTvDbXrefGraphNode* hostDwg() const { return(OdTvDbXrefGraphNode*)rootNode(); }  
  /** \details
    Marks the unresolved Xrefs in this XrefGraph object, and their nested Xrefs, with the kUnresTree flag.
    
    \remarks
    Not implemented, reserved.
    Returns true if and only if there are any unresolved Xrefs.
  */
  bool markUnresolvedTrees();
  
  // cycle detection
  
  // virtual bool findCycles(OdTvDbGraphNode* pStart = 0);

  /** \details
    Populate the specified XrefGraph object with the Xref tree of the specified database.
    
    \param pDb [in]  Pointer to the database.
    \param xrefGraph [out]  Receives the Xref tree. 
    \param includeGhosts [in]  Ignored.

    \remarks
    xrefGraph is reset at the start of this function.
  */
  static void getFrom(
    OdTvDbDatabase* pDb, 
    OdTvDbXrefGraph& xrefGraph, 
    bool includeGhosts = false);
};
#include "TD_PackPop.h"

#endif // _ODDBXREFGRAPH_H_INCLUDED_


