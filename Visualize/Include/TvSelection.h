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

#ifndef _ODTV_SELECTION_H_INCLUDED_
#define _ODTV_SELECTION_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvEntity.h"
#include "UInt32Array.h"

#define STL_USING_SET
#include "OdaSTL.h"

/** \details
  A data type that represents an array of geometry entity identifiers.
*/
typedef OdArray<OdTvGeometryDataId> OdTvGeometryDataIdsArray;


/** \details
  The base interface class that implements functionality for working with identifiers of sub-geometry entities supported by ODA Visualize SDK.
  
  \remarks
  First of all, this container should provide a good performance for copying since this object as a part of more complex object that participates in the copying 
  operations quite often. That's why sub-geometry IDs are stored in 'OdArray' since it allows to share the buffer. The second important operation is a search operation.
  That's why sorted array is used. The adding operation is not so important because first of all it is assumed that this container will be fulfilled 
  inside the SDK where it will perform optimally (as much as possible). Use the 'addIndex' method of this container to add elements to this container.
  This method has a good performance for adding elements to the end but bad performance for adding to the beginning or middle. That's why 
  this method should be used only for a small amount of insertions. For adding a big number of sorted items it is recommended to use the 'addIndexes' method. 
  The relative performance of this method grows together with the number of inserted elements. It has linear complexity in the size of the container plus 
  number of inserted elements (or O(N + K*log(K)) for the unsorted inserted elements). To search one element, use the 'isMember' method.
  This method has logarithmic complexity. But if you need to search a significant number of elements, there is the another variation of the 'isMember' method.
  The relative performance of this method grows together with the number of searched elements. It has linear complexity in the size of the container
  regardless of the number of the searched elements.
  \sa
  <link tv_working_with_features_selections, Work with Selections>
*/
class ODTV_EXPORT OdTvSubGeometryId
{
public:
  /** \details 
    Creates a new sub-geometry identifier object with default options.
  */
  OdTvSubGeometryId();
  
  /** \details 
    Creates a new sub-geometry identifier object with a specified geometry type and data.
    
    \param type     [in] A sub-geometry type for the created identifier object.
    \param indexes  [in] An array of sub-geometry indexes for the created identifier object.
  */
  OdTvSubGeometryId(OdTv::SubGeometryType type, const OdUInt32Array& indexes);

  /** \details
    The equal operator for two sub-geometry identifiers. 
    
    \param subItemId [in] Another identifier object to be compared with.
    \returns Returns true if the identifier object is equal to the other identifier object specified with the subItemId parameter; otherwise returns false.
  */
  bool operator ==(const OdTvSubGeometryId& subItemId) const;
  
  /** \details
    The non-equal operator for two sub-geometry identifiers. 
    
    \param subItemId [in] Another identifier object to be compared with.
    \returns Returns true if the identifier object is not equal to the other identifier object specified with the subItemId parameter; otherwise returns false.
  */
  bool operator !=(const OdTvSubGeometryId& subItemId) const;

  /** \details
    Retrieves the current sub-geometry type. 
    
    \returns Returns the current type of the sub-geometry.
  */
  OdTv::SubGeometryType type() const;

  /** \details
    Sets a new sub-geometry type of the identifier object.
    
    \param type [in] A new sub-geometry type to be set.
  */
  void setType(OdTv::SubGeometryType type);

  /** \details
    Retrieves the current indexes of the identifier object.
    
    \returns Returns the current indexes.
  */
  const OdUInt32Array& indexes() const;

  /** \details
    Retrieves the current indexes of the identifier object. 
    
    \returns Returns the current indexes.
  */
  OdUInt32Array& indexes();

  /** \details
    Retrieves the current indexes map of the identifier object.
    
    \returns Returns the current indexes map.
    \remarks
    OBSOLETE. It is better not to use this method due to performance and memory consumption reason.
  */
  const std::set<OdUInt32>& indexesMap() const;

  /** \details
    Retrieves the current indexes map of the identifier object.
    
    \returns Returns the current indexes map.
    \remarks
    OBSOLETE. It is better not to use this method due to performance and memory consumption reason.
  */
  std::set<OdUInt32>& indexesMap();

  /** \details
    Sets new indexes to the identifier object.
    
    \param indexes [in] A new index array. 
  */
  void setIndexes(const OdUInt32Array& indexes);

  /** \details
    Adds a new index to the index array of the identifier object.
    
    \param index [in] A new index to be added.
    \param bCheckDuplication [in] OBSOLETE: A duplication check flag value. 
  */
  void addIndex(OdUInt32 index, bool bCheckDuplication = false);

  /** \details
    Adds a new index array to the index array of the identifier object.
    
    \param indexes            [in] A new index array to be added.
    \param bCheckDuplication  [in] OBSOLETE: A duplication check flag value.
  */
  void addIndexes(const OdUInt32Array& indexes, bool bCheckDuplication = false);

  /** \details
    Retrieves whether a specified index is contained in the identifier object.
    
    \param ind       [in] An index for checking.
    \returns Returns true if the specified index is contained in the identifier object, otherwise returns false.
  */
  bool isMember(const OdUInt32& ind) const;

  /** \details
    Retrieves whether a specified indexes are contained in the identifier object.
    
    \param indexes  [in]  A placeholder for an array that contains indexes for checking.
    \param members  [out] A placeholder for an array of the same length as 'indexes' which will contain 1 on i-th place if the indexes[i] is contained in the identifier object and 0 otherwise.
    \remarks
    From the performance point of view it will be better if the indexes in the input array will be sort in the ascending order.
  */
  void isMember(const OdUInt32Array& indexes, OdUInt8Array& members) const;

  /** \details
    Removes all members of this subgeometryId.
  */
  void clear();
  
  /** \details
    Checks that subgeometryId is empty.
    
    \returns true if and only if the object is empty (doesn't contain any indexes).
  */
  bool isEmpty() const;

  private:

  /** \details
    Insert element in the ordered array.
    
    \returns true if the index was inserted, false otherwise.
  */
  bool insert(const OdUInt32& ind);

  /** \details
    A recursive binary search function.
    
    \returns location of ind in this identifier object
             otherwise returns -1 if bNeedPos == false or the last location when index in identifier object is less than ind if bNeedPos == true.
  */
  OdInt32 search(const OdInt32& left, const OdInt32& right, const OdUInt32& ind, bool bNeedPos = false) const;

//DOM-IGNORE-BEGIN
private:
  OdTv::SubGeometryType   m_Type;
  OdUInt32Array           m_Indexes;    //ascending ordered

  //OBSOLETE: Usually empty. Will be filled only due to calling methods 'indexesMap()' which are also obsolete
  std::set<OdUInt32>      m_mapIndexes;
//DOM-IGNORE-END
};



/** \details
  The base class that implements the definition and handling of a full path to a Visualize SDK sub-item entity.
  
  \remarks
  Each sub-item path object consists of a sub-item object identifier object and an ordered array of entity identifiers and geometry data identifiers.
  The <link OdTvSubGeometryId, sub-geometry identifier> consists of indexes and a type of sub-geometry object.
  Arrays, entity identifiers, and geometry data identifiers define the path from the sub-item to the outermost entity that contains the sub-item.
  \sa
  <link tv_working_with_features_selections, Work with Selections>
*/
class ODTV_EXPORT OdTvSubItemPath
{
public:
  
  /** \details 
    Creates a new instance of the sub-item full path with an empty path.
  */
  OdTvSubItemPath()
  {}

  /** \details 
    Creates a new instance of the sub-item full path with specified parameters.
    
    \param entitiesIds  [in] An array of entity identifiers.
    \param geometryData [in] An array of geometry data identifiers. 
    \param subGeomId    [in] An identifier of a sub-geometry entity.
  */
  OdTvSubItemPath(const OdTvEntityIdsArray& entitiesIds, const OdTvGeometryDataIdsArray& geometryData, const OdTvSubGeometryId& subGeomId)
    : m_EntitesIds(entitiesIds)
    , m_GeometryDataIds(geometryData)
    , m_SubGeometryId(subGeomId)
  {
  }
  
  /** \details 
    The assignment operator for the sub-item full path object. 
    
    \param subItemPath [in] Another sub-item full path object that represents the second operand of the assignment operation.
    \returns Returns the reference to the sub-item full path modified after the assignment operation.
  */
  OdTvSubItemPath& operator =(const OdTvSubItemPath& subItemPath)
  {
    m_EntitesIds = subItemPath.entitiesIds();
    m_GeometryDataIds = subItemPath.geometryDatasIds();
    m_SubGeometryId = subItemPath.subGeometryId();
    return *this;
  }

  /** \details 
    The equal operator for two sub-item full path objects. 
    
    \param subItemPath [in] Another sub-item full path object to be compared with.
    \returns Returns true if the sub-item full path object is equal to the other one; otherwise the method returns false.
  */
  bool operator==(const OdTvSubItemPath& subItemPath) const
  {
    return m_EntitesIds == subItemPath.entitiesIds() && m_SubGeometryId == subItemPath.subGeometryId() && m_GeometryDataIds == subItemPath.geometryDatasIds();
  }

  /** \details
    Retrieves the current array of entity identifiers of the sub-item full path object. 
    
    \returns Returns a reference to the <link OdTvEntityIdsArray, entity identifier array> contained in the sub-item path object. 
    \remarks 
    The returned array is read-only and can not be modified.
  */
  const OdTvEntityIdsArray& entitiesIds() const
  {
    return m_EntitesIds;
  }

  /** \details
    Retrieves the current array of entity identifiers of the sub-item full path object. 
    
    \returns Returns a reference to the <link OdTvEntityIdsArray, entity identifier array> contained in the sub-item path object. 
    \remarks 
    The returned array can be modified.
  */
  OdTvEntityIdsArray& entitiesIds()
  {
    return m_EntitesIds;
  }

  /** \details
    Retrieves the current array of geometry data identifiers of the sub-item full path object. 
    
    \returns Returns a reference to the <link OdTvGeometryDataIdsArray, geometry data identifier array> contained in the sub-item path object. 
    \remarks 
    The returned array is read-only and can not be modified.
  */
  const OdTvGeometryDataIdsArray& geometryDatasIds() const
  {
    return m_GeometryDataIds;
  }

  /** \details
    Retrieves the current array of geometry data identifiers of the sub-item full path object. 
    
    \returns Returns a reference to the <link OdTvGeometryDataIdsArray, geometry data identifier array> contained in the sub-item path object. 
    \remarks 
    The returned array can be modified.
  */
  OdTvGeometryDataIdsArray& geometryDatasIds()
  {
    return m_GeometryDataIds;
  }

  /** \details
    Retrieves the current sub-geometry identifiers of the sub-item full path object. 
    
    \returns Returns a copy of the <link OdTvSubGeometryId, sub-geometry identifier> contained in the sub-item path object. 
  */
  const OdTvSubGeometryId& subGeometryId() const
  {
    return m_SubGeometryId;
  }

  /** \details
    Retrieves the current sub-geometry identifiers of the sub-item full path object. 
    
    \returns Returns a reference to the <link OdTvSubGeometryId, sub-geometry identifier> contained in the sub-item path object. 
    \remarks 
    The identifier be modified.
  */
  OdTvSubGeometryId& subGeometryId()
  {
    return m_SubGeometryId;
  }

//DOM-IGNORE-BEGIN
protected:
  OdTvEntityIdsArray            m_EntitesIds;
  OdTvGeometryDataIdsArray      m_GeometryDataIds;
  OdTvSubGeometryId             m_SubGeometryId;
//DOM-IGNORE-END
};



/** \details
  The base class that implements the definition and handling of selection options for entities supported by Visualize SDK.
  \sa
  <link tv_working_with_features_selections, Work with Selections>
*/
class ODTV_EXPORT OdTvSelectionOptions
{
public:

  /** \details
    Entity selection levels.
  */
  enum Level
  {
    kEntity       = 0, // An entity selection level.
    kNestedEntity = 1, // A nested entity selection level.
    kGeometry     = 2, // A geometry selection level.
    kSubGeometry  = 3  // A sub-geometry selection level.
  };

  /** \details 
    Selection modes.
  */
  enum Mode
  {
    kWindow       = 0, // Selection is defined with two points that represent a rectangle. Only those objects are selected that are located entirely inside the selection area.
    kCrossing     = 1, // Selection is defined with two points that represent a rectangle. Only those objects are selected that are located either entirely inside the selection area or intersect it.
    kFence        = 2, // Selection is defined with two or more points that represent a polyline. Only those objects are selected that intersect the selection polyline.
    kWPoly        = 3, // Selection is defined with three or more points that represent a polygon. Only those objects are selected that are located entirely inside the selection polygon.
    kCPoly        = 4, // Selection is defined with three or more points that represent a polygon. Only those objects are selected that are located entirely inside the selection polygon or intersect it.
    kPoint        = 5  // Same as kCrossing, but returns only a single selected object: the top object for 3D render modes or the first object for 2D render mode.
  };

  /** \details
    Creates a new instance of the selection options with default parameters.
  */
  OdTvSelectionOptions();
  
  /** \details
    Creates a new instance of the selection options as a copy of an already existing options object (a copy constructor).
    
    \param options [in] Another selection options object to be copied.
  */
  OdTvSelectionOptions(const OdTvSelectionOptions& options);
  
  /** \details
    Destroys the selection options object.
  */
  virtual ~OdTvSelectionOptions() {};

  /** \details
    The assignment operator for the selection options object. 
    
    \param options [in] Another selection options object that represents the right-hand operand of the assignment operation.
    \returns Returns the reference to the selection options object modified after the assignment operation.
  */
  OdTvSelectionOptions& operator =(const OdTvSelectionOptions& options);
  
  /** \details
    The equal operator that compares two selection options objects. 
    
    \param options [in] Another selection options object to compare with this object.
    \returns Returns true if the selection options object is equal to the other object; otherwise returns false.
  */
  bool operator ==(const OdTvSelectionOptions& options) const;
  
  /** \details
    The non-equal operator that compares two selection options objects. 
    
    \param options [in] Another selection options object to compare with this object.
    \returns Returns true if the selection options object is not equal to the other object; otherwise returns false.
  */
  bool operator !=(const OdTvSelectionOptions& options) const;

  /** \details
    Retrieves the current selection level.
    
    \returns Returns the value of the <link OdTvSelectionOptions::Level, Level> enumeration that contains the current selection level.
  */
  Level getLevel() const;

  /** \details
    Retrieves the current selection mode.
    
    \returns Returns the value of the <link OdTvSelectionOptions::Mode, Mode> enumeration that contains the current selection mode.
  */
  Mode getMode() const;

  /** \details
    Retrieves the current pick box size. 
    Applicable only for the <link OdTvSelectionOptions::Mode::kPoint, kPoint> selection mode. 
    
    \returns Returns the current pick box size.
  */
  OdUInt16 getPickBoxSize() const;

  /** \details
    Sets a new selection level.
    
    \param level [in] A new level to be set.
  */
  void setLevel(Level level);

  /** \details
    Sets a new selection mode.
    
    \param mode [in] A new mode value to be set.
  */
  void setMode(Mode mode);

  /** \details
    Sets a new pick box size. 
    The pick box size is applicable only for the <link OdTvSelectionOptions::Mode::kPoint, kPoint> selection mode. 
    
    \param size [in] A new size value to be set.
  */
  void setPickBoxSize(OdUInt16 size);

  /** \details
    Sets the default selection parameters.
  */
  void setDefault();

//DOM-IGNORE-BEGIN
private:

  //data
  Level     m_level;
  Mode      m_mode;
  OdUInt16  m_pickBoxSize;
//DOM-IGNORE-END
};



/** \details
  The abstract interface class for the iterator of Visualize SDK selected objects.
  An iterator object provides sequential access to a collection of selected objects.
  \sa
  <link tv_working_with_features_selections, Work with Selections>
*/
class ODTV_EXPORT OdTvSelectionSetIterator : public OdTvIterator, public OdTvIObject
{
public:

  /** \details
    Returns the current full path to the selected item.
    
    \param path [out] A placeholder for the path to the selected item.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the current path to the selected item was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getPath(OdTvSubItemPath& path) const = 0;

  /** \details
    Retrieves the selected entity.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the <link OdTvEntityId, identifier> of the selected entity.
    \remarks 
    If the rc parameter is not null and the <link OdTvEntityId, identifier> of the selected entity was successfully returned, 
    the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvEntityId getEntity(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the currently selected sub-entity (this method is not implemented yet)
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the <link OdTvGeometryDataId, geometry data identifier> for the selected sub-entity.
    \remarks 
    If the rc parameter is not null and the <link OdTvGeometryDataId, geometry data identifier> was successfully returned, 
    the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    The method is applicable only when using a sub-entity, geometry or sub-geometry selection.
  */
  virtual OdTvGeometryDataId getSubEntity(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the currently selected geometry data entity.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the <link OdTvGeometryDataId, geometry data identifier> for the selected geometry data entity.
    \remarks 
    If the rc parameter is not null and the <link OdTvGeometryDataId, geometry data identifier> was successfully returned, 
    the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
    The method is applicable only when using a geometry or sub-geometry selection.
  */
  virtual OdTvGeometryDataId getGeometryData(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves selected faces for a selected shell or mesh entity.
    
    \param indFaces [out] A placeholder for an array that contains face indexes of the selected shell or mesh entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the face index array was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
    The method is applicable only when using a sub-geometry selection.
  */
  virtual OdTvResult getFaces(OdUInt32Array& indFaces) = 0;

  /** \details
    Retrieves selected edges for a selected shell or mesh entity.
    
    \param indEdges [out] A placeholder for an array that contains edge indexes of the selected shell or mesh entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the edge index array was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
    The method is applicable only when using a sub-geometry selection.
  */
  virtual OdTvResult getEdges(OdUInt32Array& indEdges) = 0;

  /** \details
    Retrieves selected vertices for a selected shell or mesh entity.
    
    \param indVertices [out] A placeholder for an array that contains vertex indexes of the selected shell or mesh entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the vertex index array was successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
    The method is applicable only when using a sub-geometry selection.
  */
  virtual OdTvResult getVertices(OdUInt32Array& indVertices) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvSelectionSetIterator, OdTvSelectionSetIterator> object.
*/
typedef OdTvSmartPtr<OdTvSelectionSetIterator> OdTvSelectionSetIteratorPtr;

class OdTvSelectionSet;

/** \details
  A data type that represents a smart pointer to an <link OdTvSelectionSet, OdTvSelectionSet> object.
*/
typedef OdTvSmartPtr<OdTvSelectionSet> OdTvSelectionSetPtr;

/** \details
  The abstract interface class for managing a set of selected Visualize SDK objects.
  \sa
  <link tv_working_with_features_selections, Work with Selections>
*/
class ODTV_EXPORT OdTvSelectionSet : public OdTvIObject
{
public:

  /** \details
    Creates a new selection set object with specified selection options. 
    
    \param opt [in] An <link OdTvSelectionOptions, OdTvSelectionOptions> object that contains selection parameters.
    \returns Returns a smart pointer to the created selection set object.
  */
  static OdTvSelectionSetPtr createObject(const OdTvSelectionOptions& opt);

  /** \details
    Retrieves the iterator for getting access to items that are contained in the selection set object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a smart pointer to the <link OdTvSelectionSetIterator, iterator> object. 
    \remarks 
    If the rc parameter is not null and the iterator object was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvSelectionSetIteratorPtr getIterator(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the quantity of items that are contained in the selection set.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the number of currently selected items.
    \remarks 
    If the rc parameter is not null and the quantity of selected items was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 numItems(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current selection options for the selection set.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an instance of the <link OdTvSelectionOptions, OdTvSelectionOptions> class that contains the current selection options.
    \remarks 
    If the rc parameter is not null and the current selection options were successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvSelectionOptions getOptions(OdTvResult* rc = NULL) const = 0;

  /** \details
    Appends a new entity item to the selection set.
    
    \param id [in] An identifier of an entity to be appended.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new entity was successfully appended to the selection set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult appendEntity(const OdTvEntityId& id) = 0;

  /** \details
    Appends a new sub-entity item (a sub-entity, geometry or sub-geometry entity) with a specified full path.
    
    \param entityId     [in] An identifier of the appended entity.
    \param subItemPath  [in] A sub-item path object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new sub-entity item was successfully appended to the selection set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult appendSubEntity(const OdTvEntityId& id, const OdTvSubItemPath& subItemPath) = 0;

  /** \details
    Removes the entity item from the selection set (all subentity paths for this entity also will be removed).
    
    \param id     [in] An identifier of the removed entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the entity item was successfully removed from the selection set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeEntity(const OdTvEntityId& id) = 0;

  /** \details
    Removes the sub-entity item (a sub-entity, geometry or sub-geometry entity) with a specified full path from the selection set.
    
    \param id           [in] An identifier of the removed entity.
    \param subItemPath  [in] A sub-item path object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the sub-entity item was successfully removed from the selection set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeSubEntity(const OdTvEntityId& id, const OdTvSubItemPath& subItemPath) = 0;

  /** \details
    Retrieves whether a specified entity is contained in the selection set.
    
    \param id [in] An identifier of the entity.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the specified entity is contained in the selection set; otherwise the method returns false.
    \remarks 
    If the rc parameter is not null and the existence check was successful, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool isMember(const OdTvEntityId& id, OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves whether a specified subitem path of the specified entity is contained in the selection set.
    
    \param id           [in] An identifier of the entity.
    \param subItemPath  [in] A sub-item path object.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if a specified subitem path of the specified entity is contained in the selection set; otherwise the method returns false.
    \remarks
    If the rc parameter is not null and the existence check was successful, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool isMember(const OdTvEntityId& id, const OdTvSubItemPath& subItemPath, OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves whether a specified geometry data entity is contained in the selection set.
    
    \param id [in] An identifier of the geometry data entity.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the specified geometry data entity is contained in the selection set; otherwise the method returns false.
    \remarks 
    If the rc parameter is not null and the existence check was successful, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool isMember(const OdTvGeometryDataId& id, OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves whether a specified faces from the specified geometry data (shell or mesh) are contained in the selection set.
    
    \param id       [in] An identifier of the geometry data entity.
    \param indexes  [in] A placeholder for an array that contains indexes (faces, edge or vertex depends from 'type') of the selected shell or mesh entity.
    \param type     [in] Type of the sub-geometry. 
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns an array that contains 1 on i-th place if the indexes[i] is contained in the selection set and 0 otherwise.
    \remarks
    If the rc parameter is not null and the existence check was successful, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt8Array isMember(const OdTvGeometryDataId& id, const OdUInt32Array& indexes, OdTv::SubGeometryType type = OdTv::kFaceSubGeometryType, OdTvResult* rc = NULL) const = 0;

  /** \details
    Removes all members of this selection set.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the selection set was successfully cleared, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult clear() = 0;
};

#endif // _ODTV_SELECTION_H_INCLUDED_
