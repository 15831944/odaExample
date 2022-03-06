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

#ifndef _ODTV_SELECTIONIMPL_H_INCLUDED_
#define _ODTV_SELECTIONIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "IdArrays.h"
#include "Gs/GsSelectionReactor.h"
#include "Gs/Gs.h"

//TV
#include "TvSelection.h"
#include "TvInterfaceWrappers.h"

#define STL_USING_MAP
#define STL_USING_VECTOR
#include "OdaSTL.h"
#include "TvGeometryDataImpl.h"

/** \details
This template class is a specialization of the OdArray class for OdTvSubItemPath objects.
*/
typedef OdArray<OdTvSubItemPath> OdTvSubItemPathArray;

/** \details
Map for storing the relation between the top-level entity and array of the subitems path
*/
typedef std::map<OdTvDbObjectId, OdTvSubItemPathArray> OdTvSelectionSetContainer;


class OdTvSelectionSetIteratorImpl;


/** \details
This is an implementation of the selection set for the Visualize API
*/
class OdTvSelectionSetImpl : public OdTvSelectionSet
{
  friend class OdTvSelectionSetIteratorImpl;
public:

  OdTvSelectionSetImpl(const OdTvSelectionOptions& opt);

  OdTvSelectionSetImpl(const OdTvSelectionOptions::Level level);

  /** \details
  Returns an Iterator object that provides access to the items in this Selection Set (ONLY FOR INTERNAL USING);
  */
  OdTvSelectionSetIteratorImpl* getIteratorImpl(OdTvResult* rc = NULL) const;

  /** \details
  Returns an Iterator object that provides access to the items in this Selection Set.
  */
  virtual OdTvSelectionSetIteratorPtr getIterator(OdTvResult* rc = NULL) const;

  /** \details
  Returns the number of selected items
  */
  virtual OdUInt32 numItems(OdTvResult* rc = NULL) const;

  /** \details
  Returns the options that was used for the selection procedure
  */
  virtual OdTvSelectionOptions getOptions(OdTvResult* rc = NULL) const;

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
  Check that entity exists in the selection set
  */
  virtual bool isMember(const OdTvEntityId& id, OdTvResult* rc = NULL) const;

  /** \details
  Check that entity with subitem path is exists in the selection set
  */
  virtual bool isMember(const OdTvEntityId& id, const OdTvSubItemPath& subItemPath, OdTvResult* rc) const;

  /** \details
  Check that geometry data exists in the selection set
  */
  virtual bool isMember(const OdTvGeometryDataId& id, OdTvResult* rc = NULL) const;

  /** \details
  Retrieves whether a specified subgeometry indexes from the specified geometry data (shell or mesh) are contained in the selection set.
  */
  virtual OdUInt8Array isMember(const OdTvGeometryDataId& id, const OdUInt32Array& indexes, OdTv::SubGeometryType type = OdTv::kFaceSubGeometryType, OdTvResult* rc = NULL) const;

  /** \details
  Removes all members of this selection set.
  */
  virtual OdTvResult clear();

  /** \details
  Methods for creating the object
  */
  //static OdTvSelectionSetPtr createObject(const OdTvSelectionOptions& opt);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

  virtual ~OdTvSelectionSetImpl();

  /** \details
  Append entity
  */
  virtual void appendEntity(OdDbStub* entityId);

  /** \details
  Append subentity item (subEntity, geometry or subgeometry) by OdTvSubItemPath
  */
  virtual void appendSubEntity(OdDbStub* entityId, const OdTvSubItemPath& subItemPath);

  /** \details
  Removes the entity item from the selection set (all subentity pathesfor this entity also will be removed.
  */
  virtual void removeEntity(OdDbStub* entityId);

  /** \details
  Removes the sub-entity item (a sub-entity, geometry or sub-geometry entity) with a specified full path from the selection set.
  */
  virtual void removeSubEntity(OdDbStub* entityId, const OdTvSubItemPath& subItemPath);

  /** \details
  Returns the number of subentities pathes inside the entity with the given id.
  \param entityId [in]  entity id for the parent of the subentity

  */
  OdUInt32 getNumPathes(const OdTvDbObjectId& entityId) const;

  /** \details
  Returns the given subentity path inside the entity with the given id.
  \param entityId [in]  entity id for the parent of the subentity
  \param i [in]  index of the subentity.
  \param path [out]  Path to the subentity.

  \returns
  Returns true if and only if "i" is valid index in the subentities array.
  */
  bool getPath(const OdTvDbObjectId& entityId, OdUInt32 i, OdTvSubItemPath& path) const;

  /** \details
  Returns the subentity inside the entity with the given id.
  */
  OdTvGeometryDataId getSubEntity(const OdTvDbObjectId& entityId, OdUInt32 i) const;

  /** \details
  Returns the geometry data inside the entity with the given id.
  */
  OdTvGeometryDataId getGeometryData(const OdTvDbObjectId& entityId, OdUInt32 i) const;

  /** \details
  Returns the indices to the faces within a shell or mesh inside the entity with the given id.
  */
  void getFaces(const OdTvDbObjectId& entityId, OdUInt32 i, OdUInt32Array& indFaces);

  /** \details
  Returns the edges to the edges within a shell or mesh inside the entity with the given id.
  */
  void getEdges(const OdTvDbObjectId& entityId, OdUInt32 i, OdUInt32Array& indEdges);

  /** \details
  Returns the vertices to the vertices within a shell or mesh inside the entity with the given id.
  */
  void getVertices(const OdTvDbObjectId& entityId, OdUInt32 i, OdUInt32Array& indVertices);

  /** \details
  Checks that incoming indexes are already member of the appropritate item in the selection sets 
  */
  void isMember(const OdTvDbObjectId& entityId, OdUInt32 i, OdTv::SubGeometryType type, const OdUInt32Array& indexes, OdUInt8Array& members) const;

  /** \details
  Get selection set container entity
  */
  const OdTvSelectionSetContainer* getSelectionSetContainer() const;

  /** \details
  Get selection set container entity
  */
  const OdTvDbObjectIdArray* getSelectedDbIdsArray() const;

private:
  OdTvSelectionOptions m_opt;         //options

  OdTvSelectionSetContainer     m_map;
  OdTvDbObjectIdArray             m_idArray; //NS: the class should preserve order of elements added to it,
                                          //so 2 storages are required: map for effective search, array for order

  // reference counter
  unsigned int                m_nRefCounter;

private:
  bool isMember(const OdTvDbObjectId& objId) const;
  bool isMember(OdDbStub* objId) const;
};

typedef OdTvSmartPtr<OdTvSelectionSetImpl> OdTvSelectionSetImplPtr;


/* \details 
This is a specific class which implements cache for selection reactor for some case
*/

class OdTvSelectionReactorCache
{
  //cached top level entity
  OdTvDbObjectId m_cachedEntity;

  //*******************cache for the gemetry selection level (too much geometries in one entity) *****************//
  //contains geometry by marker
  std::vector<OdTvGeometryDataImpl*> m_cachedGeometriesByMarker;

  //*******************cache for the subgeometry selection level (shell or mesh) *****************//
  // Cached geometry (shell or mesh)
  OdTvGeometryDataImpl* m_pCachedGeometry;
  // first marker in the cached geometry
  OdGsMarker            m_firstSubGeometryMarker;
  // last marker in the cached geometry
  OdGsMarker            m_lastSubGeometryMarker;
  // current path data
  OdTvEntityIdsArray m_entitiesArray;
  OdTvGeometryDataIdsArray m_geometriesDataArray;
  OdUInt32Array           m_subGeometryIds[3];

public:
  OdTvSelectionReactorCache();
  ~OdTvSelectionReactorCache();

  //////////////////////////////////////////////// FOR GEOMETRY LEVEL ////////////////////////////////////////////////////
  void                  createGeometryLevelCache(OdTvDbObjectId dbTopLevelEntity);
  OdTvGeometryDataImpl* getGeometryByGsMarker(const OdGsMarker& marker, OdTv::SubGeometryType& type, OdInt64& subGeomId) const;

  //////////////////////////////////////////////// FOR SUBGEOMETRY LEVEL ////////////////////////////////////////////////////
  void                  createSubGeometryLevelCache(OdTvDbObjectId dbTopLevelEntity, OdTvGeometryDataImpl* pGeomDataImpl,
                                                    const OdTvEntityIdsArray& entitiesIds, const OdTvGeometryDataIdsArray& geometryData);

  //returns true if we are successfully update the cache by new data
  bool                  addGiPathToSSetForSubgeometry(OdTvSelectionSetImpl* pSSet, const OdGiPathNode& pathNode);

  void                  flushSubgeometryCache(OdTvSelectionSetImpl* pSSet);

  void                  addSubGeometry( OdUInt32 subGeomId, OdTv::SubGeometryType type );

private:
  bool                  inspectPathForCachedTopLevelEntity(const OdGiPathNode& pathNode) const;
  void                  clearSubGeometryData();
};

/** \details
This is an implementation of the selection reactor
*/
class OdTvSelectionReactor : public OdGsSelectionReactor
{
public:
  OdTvSelectionOptions                      m_opt;
  OdTvDbObjectId                            m_modelId;
  OdArray<OdTvDbObjectId>                   m_models;
  OdTvSelectionSetImpl*                     m_pSSet;
  bool                                      m_BlockCacheIsOn;

  OdTvSelectionReactor(OdTvSelectionSetImpl* pSSet, OdTvDbObjectId modelId, const OdTvSelectionOptions& opt, bool bBloclCacheIsOn);
  OdTvSelectionReactor(OdTvSelectionSetImpl* pSSet, const OdArray<OdTvDbObjectId>& models, const OdTvSelectionOptions& opt, bool bBloclCacheIsOn);

  void                  flushSubgeometryCache(OdTvSelectionSetImpl* pSSet);

  bool selectedWithInserts(const OdGiDrawableDesc& drawableDesc);
  virtual bool selected(const OdGiDrawableDesc& drawableDesc);
  virtual OdUInt32 selected(const OdGiPathNode& pathNode, const OdGiViewport& viewInfo);

private:

  OdTvSelectionReactorCache          m_cache;
};

/** \details
This is an implementation of the iterator class for the selection set
*/
class OdTvSelectionSetIteratorImpl : public OdTvSelectionSetIterator
{
  friend class OdTvModelImpl;
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
  Returns the full path to the selected item
  */
  OdTvResult getPath(OdTvSubItemPath& path) const;

  /** \details
  Returns the entity that was selected
  */
  virtual OdTvEntityId getEntity(OdTvResult* rc = NULL) const;

  /** \details
  Returns the subentity that was selected if using subentity, geometry or subgeometry selection.
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
  static OdTvSelectionSetIteratorPtr createObject(const OdTvSelectionSetImpl* pSSet);

  /** \details
  ONLY for internal using
  */
  static OdTvSelectionSetIteratorImpl* createObjectImpl(const OdTvSelectionSetImpl* pSSet);

  /** \details
  ONLY for internal using
  */
  void isMember(OdTv::SubGeometryType type, const OdUInt32Array& indexes, OdUInt8Array& members) const;

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

  virtual ~OdTvSelectionSetIteratorImpl();

private:
  OdTvSelectionSetIteratorImpl();
  OdTvSelectionSetIteratorImpl(OdTvSelectionSetImpl* pSSet);

  OdTvSmartPtr<OdTvSelectionSetImpl> m_pParentSSet;
  OdTvDbObjectIdArray::const_iterator m_pItem;
  OdTvDbObjectIdArray::const_iterator m_pEndItem;

  OdUInt32 m_nSubEntityPathInd;
  OdUInt32 m_nSubEntityTotalPathes;

  // reference counter
  unsigned int                m_nRefCounter;
};


/** \details
Method which add the data from GiPathNode to the selection set
*/
OdUInt32  AddOdGiPathNodeToTvSelectionSet(const OdGiPathNode& pathNode, OdTvSelectionSetImpl* pSelectionSetImpl,
                                          OdTvSelectionOptions::Level level, const OdTvDbObjectId & dbModelId,
                                          bool& bShouldImmediatelyReturn, OdTvSelectionReactorCache* pCache = NULL, bool bIsBlockCacheOn = true);

/** \details
Fill tv subentity path for the case of inserts from the IDS array and tol level entity
IMPORTANT: one of the parameters pNode should be not NULL. 
*/
bool FillTvSubEntityPath(const OdGiPathNode* pNode, const OdGiDrawableDesc* pDesc, OdTvSelectionOptions::Mode selMode,
                         OdTvDbObjectIdArray& idsPath, OdTvSelectionSetImpl* pSelectionSetImpl, const OdGiDrawableDesc* pIncomingDesc = NULL);


#include "TD_PackPop.h"

#endif //_ODTV_SELECTIONIMPL_H_INCLUDED_
