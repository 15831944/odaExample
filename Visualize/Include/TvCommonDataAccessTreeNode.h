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

#ifndef _ODTV_COMMONDATAACCESS_TREE_NODE_H_INCLUDED_ 
#define _ODTV_COMMONDATAACCESS_TREE_NODE_H_INCLUDED_

#include "Tv.h"
#include "RxModelTreeBaseNode.h"
#include "SmartPtr.h"
#include "TvEntity.h"
#include "TvSelection.h"

class OdTvCDATreeNode;

/** \details
  A data type that represents a smart pointer to an <link OdTvCDATreeNode, OdTvCDATreeNode> object.
*/
typedef OdSmartPtr<OdTvCDATreeNode> OdTvCDATreeNodePtr;

/** \details
  A data type that represents an array of smart pointers to an<link OdTvCDATreeNode, OdTvCDATreeNode> object.
*/
typedef OdArray<OdTvCDATreeNodePtr> OdTvCDATreeNodePtrArray;

/** \details
  This class implements the hierarchy tree node for the Common Data Access mechanism specific for using with Visualize SDK
  This implementation provides a link between hierarchy tree node and the appropriate Visualize entity
*/
class ODTV_EXPORT OdTvCDATreeNode : public OdRxModelTreeBaseNode
{
public:
  ODRX_DECLARE_MEMBERS(OdTvCDATreeNode);
  ODRX_HEAP_OPERATORS();

  /** \details
    Node options.
  */
  enum Options
  {
    kInvisible  = 1,          // Node should be invisible.
    kExploded   = 2,          // Node should be exploded.
    kShouldGroup = 4,         // Child nodes should be group.
    kShouldAlwaysGroup = 8    // Child nodes always should be group (even one child).
  };

  /** \details
    Returns the tv entities from this node.
    
    \returns Returns an array of <link OdTvEntityId, OdTvEntityId> Visualize entities ids.
  */
  virtual OdTvEntityIdsArray getTvEntitiesIds() const;

  /** \details
    Returns the tv entity from this node which is visible in the view.
    
    \param viewId       [in] Identifier of the view.
    \returns Returns a value of <link OdTvEntityId, OdTvEntityId> Visualize entity id.
    \remarks
    If viewId is null, this method will return the first entity from this node
  */
  virtual OdTvEntityId getTvEntityId(const OdTvGsViewId& viewId) const;

  /** \details
    Adds the tv entity to this tree node.
    
    \param id  [in] A Visualize entity id.
    \remarks
    If the specified entity was successfully add, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult addTvEntityId(OdTvEntityId id);

  /** \details
    Returns the selection set, which contains the visualize entities from this and all children nodes which is visible in the view.
    
    \param viewId       [in] Identifier of the view in which visualize entities should be visible.
    \param parentsPath  [in] Pointer to an array that contains the parents nodes from the first parent to the top parent database node.
    \returns Returns a smart pointer to the <link OdTvSelectionSet, selection set object>.
    \remarks
    parentsPath can be null in most cases since this parameter make sense in the case of blocks/insertions when one node can have multiple parents
    If viewId is null, this method will return all entities from this and all children nodes.
  */
  virtual OdTvSelectionSetPtr select(const OdTvGsViewId& viewId, const OdTvCDATreeNodePtrArray* parentsPath = NULL);

  /** \details
    Isolates node with all children.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult isolate(const OdTvGsViewId& viewId);

  /** \details
    Hides node with all children.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult hide(const OdTvGsViewId& viewId);

  /** \details
    Adds the property to the property's cache.
    
    \param info  [in] Property info for adding
    \remarks
    If the property was successfully added, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult addProperty(PropertyInfo& info);

  /** \details
    Sets the visibility to this tree node.
    
    \param bInvisible  [in] A visibility flag.
  */
  virtual void setInvisible(bool bInvisible);

  /** \details
    Returns the visibility for this node.
    
    \returns
    True if this node is invisible, false otherwise.
  */
  virtual bool getInvisible() const;

  /** \details
    Specifies whether the current node should be exploded.
    
    \param bIsExploded  [in] Explode flag.
  */
  virtual void setExploded(bool bExploded);

  /** \details
    Returns the explode flag for this node.
    
    \returns
    True if the flag is enabled, false otherwise.
  */
  virtual bool getExploded() const;

  /** \details
    Specifies whether that the childs of the current node should be grouped.
    
    \param bNeedGroup  [in] A 'need group' flag.
  */
  virtual void setNeedGroup(bool bNeedGroup);

  /** \details
    Returns the 'need group' flag for this node.
    
    \returns
    True if the flag is enabled, false otherwise.
  */
  virtual bool getNeedGroup() const;

  /** \details
    Specifies that the current node should always group their childs (even one child).
    
    \param bShouldGroup  [in] A 'should always group' flag.
  */
  virtual void setAlwaysGroup(bool bShouldGroup);

  /** \details
    Returns the 'always group' flag for this node.
    
    \returns
    True if the flag is enabled, false otherwise.
  */
  virtual bool getAlwaysGroup() const;

  /** \details
    Specifies the name for node.
    
    \param name  [in] New name for the node.
  */
  virtual void setNodeName(const OdString& name);

  /** \details
    Specifies that the current node has viewport.
    
    \param viewportId  [in] A viewport id.
  */
  virtual void setViewportObject(const OdTvGsViewId& viewportId);

  /** \details
    Returns the viewport id.
    
    \returns
    Identifier of the viewport.
  */
  virtual OdTvGsViewId getViewportObject() const;

  /** \details
    Specifies that the current node has sibling node.
    
    \param pNode  [in] A sibling node.
  */
  virtual void setSiblingNode(const OdTvCDATreeNodePtr& pNode);

  /** \details
    Returns the sibling node.
  
    \returns
    Smart pointer to the sibling node.
  */
  virtual OdTvCDATreeNodePtr getSiblingNode() const;

  /** \details
    Returns the tv model from this node.
    
    \returns Returns a value of <link OdTvModelId, OdTvModelId> Visualize model id.
  */
  virtual OdTvModelId getTvModelId() const;

  /** \details
    Set the tv model to this tree node.
    
    \param id  [in] A Visualize model id.
  */
  virtual void setTvModelId(const OdTvModelId& id);

protected:
  /** \details
    Default constructor for the OdTvCDATreeNode class.
  */
  OdTvCDATreeNode();

  /** \details
    Writes the .vsf file data of this object.
  
    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  void outFields(OdBaseHierarchyTreeFiler* pFiler) const;

  /** \details
    Reads the .vsf file data of this object.
  
    \param pFiler [in]  Filer object from which data are read.
  */
  OdResult inFields(OdBaseHierarchyTreeFiler* pFiler, std::set<OdString>& string_storage);
};

#endif //_ODTV_COMMONDATAACCESS_TREE_NODE_H_INCLUDED_

