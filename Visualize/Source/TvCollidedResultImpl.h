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

#ifndef _ODTV_COLLIDEDRESULTIMPL_H_INCLUDED_
#define _ODTV_COLLIDEDRESULTIMPL_H_INCLUDED_

#include "TD_PackPush.h"

//TV
#include "TvCollidedResult.h"
#include "TvSelectionImpl.h"

#include <list>

struct OdTvCollidedItem
{
  OdTvDbObjectId m_entityId;
  OdTvSubItemPath m_path;

  OdTvCollidedItem() : m_entityId(OdTvDbObjectId()), m_path(OdTvSubItemPath())
  {
  };

  OdTvCollidedItem(const OdTvDbObjectId& entityId, const OdTvSubItemPath path) : m_entityId(entityId), m_path(path)
  {
  };

  bool operator==(const OdTvCollidedItem& item) const
  {
    return m_entityId == item.m_entityId && m_path == item.m_path;
  }
};

/** \details
This template class is a specialization of the std::list for OdTvCollidedItem objects.
*/
typedef std::list<OdTvCollidedItem> OdTvCollidedItemsList;

class OdTvCollidedResultIteratorImpl;
class OdTvCollidedResultWrapper;

/** \details
This is an implementation of the collided result for the ODA Visualize SDK
*/
class OdTvCollidedResultImpl : public OdTvSelectionSetImpl
{
  friend class OdTvCollidedResultIteratorImpl;
  friend class OdTvCollidedResultWrapper;
public:

  OdTvCollidedResultImpl(const OdTvSelectionOptions::Level level);

  /** \details
  Returns an Iterator object that provides access to the items in this collided result Set (ONLY FOR INTERNAL USING);
  */
  OdTvCollidedResultIteratorImpl* getIteratorImpl(OdTvResult* rc = NULL) const;

  /** \details
  Returns an Iterator object that provides access to the items in this collided result.
  */
  virtual OdTvSelectionSetIteratorPtr getIterator(OdTvResult* rc = NULL) const;

  /** \details
  Returns the number of items from collided result
  */
  virtual OdUInt32 numItems(OdTvResult* rc = NULL) const;

  /** \details
  Retrieves the current selection level for the collided result.
  */
  virtual OdTvSelectionOptions::Level getLevel(OdTvResult* rc = NULL) const;

  /** \details
  Append entity with tv id
  */
  virtual OdTvResult appendEntity(const OdTvEntityId& id);

  /** \details
  Append subentity item (subEntity, geometry or subgeometry) by OdTvSubItemPath
  */
  virtual OdTvResult appendSubEntity(const OdTvEntityId& entityId, const OdTvSubItemPath& subItemPath);

  /** \details
  Removes the entity item from the selection set (all subentity pathesfor this entity also will be removed.
  */
  virtual OdTvResult removeEntity(const OdTvEntityId& id);

  /** \details
  Removes the sub-entity item (a sub-entity, geometry or sub-geometry entity) with a specified full path from the selection set.
  */
  virtual OdTvResult removeSubEntity(const OdTvEntityId& id, const OdTvSubItemPath& subItemPath);

  /** \details
  Removes all members of this collided result.
  */
  virtual OdTvResult clear();

  /** \details
  Append all members from incoming collided result to this collided results (results should have the same level - see getLevel method)
  */
  virtual OdTvResult append(const OdTvCollidedResultPtr& results);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

  virtual ~OdTvCollidedResultImpl();

  /** \details
  Append entity
  */
  void appendEntity(OdDbStub* entityId);

  /** \details
  Append subentity item (subEntity, geometry or subgeometry) by OdTvSubItemPath
  */
  void appendSubEntity(OdDbStub* entityId, const OdTvSubItemPath& subItemPath);

  /** \details
  Removes the entity item from the selection set (all subentity pathesfor this entity also will be removed.
  */
  void removeEntity(OdDbStub* entityId);

  /** \details
  Removes the sub-entity item (a sub-entity, geometry or sub-geometry entity) with a specified full path from the selection set.
  */
  void removeSubEntity(OdDbStub* entityId, const OdTvSubItemPath& subItemPath);

  /** \details
  Get selection set container entity
  */
  const OdTvCollidedItemsList* getCollidedItemsList() const;

private:
  // Array with collided items
  OdTvCollidedItemsList       m_collidedItemsList;

  // reference counter
  unsigned int                m_nRefCounter;
};

typedef OdTvSmartPtr<OdTvCollidedResultImpl> OdTvCollidedResultImplPtr;

class OdTvCollidedResultWrapper;
/** \details
This is an implementation of the iterator class for the collided result
*/
class OdTvCollidedResultIteratorImpl : public OdTvSelectionSetIterator
{
  friend class OdTvCollidedResultWrapper;
public:

  /** \details
  Returns true if and only if the traversal by this Iterator object is complete.
  */
  virtual bool done(OdTvResult* rc = NULL) const;

  /** \details
  Steps this Iterator object.
  */
  virtual OdTvResult step();

  /** \details
  Returns the full path to the item from collided result
  */
  OdTvResult getPath(OdTvSubItemPath& path) const;

  /** \details
  Returns the entity from collided result
  */
  virtual OdTvEntityId getEntity(OdTvResult* rc = NULL) const;

  /** \details
  Returns the subentity from collided result
  */
  virtual OdTvGeometryDataId getSubEntity(OdTvResult* rc = NULL) const;

  /** \details
  Returns the geometry data that was selected if using geometry or subgeometry selection.
  */
  virtual OdTvGeometryDataId getGeometryData(OdTvResult* rc = NULL) const;

  /** \details
  Returns the indices to the edges within a shell or mesh for the item that was selected if using subgeometry selection.
  */
  virtual OdTvResult getFaces(OdUInt32Array& indFaces);

  /** \details
  Returns the edges to the edges within a shell or mesh for the item that was selected if using subgeometry selection.
  */
  virtual OdTvResult getEdges(OdUInt32Array& indEdges);

  /** \details
  Returns the indices to the vertices within a shell or mesh for the item that was selected if using subgeometry selection.
  */
  virtual OdTvResult getVertices(OdUInt32Array& indVertices);

  /** \details
  Methods for creating the object
  */
  static OdTvSelectionSetIteratorPtr createObject(const OdTvCollidedResultImpl* pCollidedResult);

  /** \details
  ONLY for internal using
  */
  static OdTvCollidedResultIteratorImpl* createObjectImpl(const OdTvCollidedResultImpl* pCollidedResult);

  /** \details
  ONLY for internal using
  */
  OdTvResult getFacesMap(std::set<OdUInt32>& indFaces);

  /** \details
  ONLY for internal using
  */
  OdTvResult getEdgesMap(std::set<OdUInt32>& indEdges);

  /** \details
  ONLY for internal using
  */
  OdTvResult getVerticesMap(std::set<OdUInt32>& indVertices);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

  virtual ~OdTvCollidedResultIteratorImpl();

private:
  OdTvCollidedResultIteratorImpl();
  OdTvCollidedResultIteratorImpl(OdTvCollidedResultImpl* pCollidedResult);

  OdTvCollidedResultImplPtr m_pParentCollidedResult;

  OdTvCollidedItemsList::const_iterator m_pItem;
  OdTvCollidedItemsList::const_iterator m_pEndItem;

  // reference counter
  unsigned int                m_nRefCounter;
};

/** \details
  This is an wrapper of the interface class for OdTvCollidedResult object.

  \remarks
  The purpose of this class is to connect the internal collided result object with an interface object
*/
class OdTvCollidedResultWrapper : public OdTvCollidedResult
{
public:

  OdTvCollidedResultWrapper(const OdTvSelectionOptions::Level level);

  /** \details
  Retrieves the iterator for getting access to items that are contained in the collided result object.
  */
  virtual OdTvSelectionSetIteratorPtr getIterator(OdTvResult* rc = NULL) const;

  /** \details
  Retrieves the quantity of items that are contained in the collided result.
  */
  virtual OdUInt32 numItems(OdTvResult* rc = NULL) const;

  /** \details
  Retrieves the current selection level for the collided result.
  */
  virtual OdTvSelectionOptions::Level getLevel(OdTvResult* rc = NULL) const;

  /** \details
  Removes the entity item from the collided result (all subentity pathes for this entity also will be removed).
  */
  virtual OdTvResult removeEntity(const OdTvEntityId& id);

  /** \details
  Removes the sub-entity item (a sub-entity, geometry or sub-geometry entity) with a specified full path from the collided result.
  */
  virtual OdTvResult removeSubEntity(const OdTvEntityId& id, const OdTvSubItemPath& subItemPath);

  /** \details
  Removes all members of this collided result.
  */
  virtual OdTvResult clear();

  /** \details
  Append all members from incoming collided result to this collided results (results should have the same level - see getLevel method)
  */
  virtual OdTvResult append(const OdTvCollidedResultPtr& results);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

  virtual ~OdTvCollidedResultWrapper();

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Internal methods
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  OdTvCollidedResultImplPtr getUnderlyingCollidedResult() { return m_pUnderlyingCollidedResult; };
private:
  OdTvCollidedResultImplPtr m_pUnderlyingCollidedResult;

  // reference counter
  unsigned int                m_nRefCounter;
};

#endif //_ODTV_COLLIDEDRESULTIMPL_H_INCLUDED_
