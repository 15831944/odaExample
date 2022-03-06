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

#ifndef _ODTV_MODEL_H_INCLUDED_
#define _ODTV_MODEL_H_INCLUDED_

#include "Tv.h"
#include "TvEntity.h"
#include "TvBlock.h"
#include "TvIObject.h"
#include "TvLight.h"
#include "TvUserData.h"
#include "UInt64Array.h"
#include "TvSelection.h"
#include "TvStatistics.h"
#include "TvCommonDataAccessTree.h"

class OdTvGsViewId;

/** \details
  The base interface class for getting access to Visualize SDK model objects.
  \sa
  <link tv_working_with_base_classes_model, Overview of Models>
*/
class ODTV_EXPORT OdTvModel : public OdTvHandledIObject
{  
public:

  /** \details
    Enumerates the model rendering types.
  */
  enum Type
  {
    kBackgroundZ    = -1, // The model is drawn before the main scene, using the Z-buffer.
    kMain           = 0,  // The model is included in the main scene.
    kDirect         = 1   // The model is drawn over the main scene, skipping the Z-buffer.
  };

  /** \details
    Appends an entity object to the model and returns the identifier of the appended entity.
    
    \param name [in] A name of the entity.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the appended entity if it is successfully added, otherwise returns a null identifier.
    \remarks
    If the rc parameter is not null and the entity is created and added to the model, the rc parameter accepts the tvOk value,
    otherwise it contains an appropriate error code.
  */
  virtual OdTvEntityId appendEntity(OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;

  /** \details
    Appends a view-dependent entity object to the model and returns the identifier of the appended entity.
    
    \param viewId [in] View in which this entity will be drawn.
    \param name   [in] A name of the entity.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier of the appended entity.
    \remarks
    If the rc parameter is not null and the entity is created and added to the model, the rc parameter accepts the tvOk value,
    otherwise it contains an appropriate error code.
  */
  virtual OdTvEntityId appendViewDependentEntity(const OdTvGsViewId& viewId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;

  /** \details
    Appends an insert entity object to the model and returns the identifier of the appended insert entity.
    
    \param blockId  [in] An identifier of the block that should contain the appended insert object.
    \param name     [in] A name of the insert object.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the appended insert entity if it is successfully added, otherwise returns a null identifier.
    \remarks
    If the rc parameter is not null and the insert entity is created and added to the model, the rc parameter accepts the tvOk value,
    otherwise it contains an appropriate error code.
  */
  virtual OdTvEntityId appendInsert(const OdTvBlockId& blockId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;

  /** \details
    Appends an insert entity object to the model and returns the identifier of the appended insert entity.
    
    \param viewId   [in] View in which this insert will be drawn.
    \param blockId  [in] An identifier of the block that should contain the appended insert object.
    \param name     [in] A name of the insert object.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the appended insert entity if it is successfully added, otherwise returns a null identifier.
    \remarks
    If the rc parameter is not null and the insert entity is created and added to the model, the rc parameter accepts the tvOk value,
    otherwise it contains an appropriate error code.
  */
  virtual OdTvEntityId appendViewDependentInsert(const OdTvGsViewId& viewId, const OdTvBlockId& blockId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;

  /** \details
    Appends a light object to the model and returns the identifier of the appended light object.
    
    \param name [in] A name of the light object.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the appended light object if it is successfully added, otherwise returns a null identifier.
    \remarks
    If the rc parameter is not null and the light object is created and added to the model, the rc parameter accepts the tvOk value,
    otherwise it contains an appropriate error code.
  */
  virtual OdTvEntityId appendLight(OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;

  /** \details
    Appends a camera object to the model and returns the identifier of the appended camera object.
    
    \param name [in] A name of the camera object.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the appended camera object if it is successfully added, otherwise returns a null identifier.
    \remarks
    If the rc parameter is not null and the camera object is created and added to the model, the rc parameter accepts the tvOk value,
    otherwise it contains an appropriate error code.
  */
  virtual OdTvEntityId appendCamera( OdString name = OdString::kEmpty, OdTvResult* rc = NULL ) = 0;

  /** \details
    Removes an entity object, specified by its identifier, from the model.
    
    \param id [in] An identifier of the entity object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the entity specified by its identifier is found and removed from the model, the method returns the tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeEntity(const OdTvEntityId& id) = 0;

  /** \details
    Removes all entities that the model contains.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If all entities are successfully removed from the model, the method returns the tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult clearEntities() = 0;

  /** \details
    Sets the name of the model.
    
    \param sName [in] A string that contains the model's name.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the model's name is successfully set, the method returns the tvOk, otherwise it returns an appropriate error code.  
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    Also there are 3 forbidden names: "*Model_Space", "*Paper_Space", "*Paper_Space0", which can not be used as model names.
  */
  virtual OdTvResult setName(const OdString& sName) = 0;

  /** \details
    Retrieves the name of the model.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current model's name.
    \remarks 
    If the rc parameter is not null and the model's name is successfully returned, the rc parameter accepts the tvOk value, otherwise it contains an
    appropriate error code.
  */
  virtual OdString getName(OdTvResult* rc = NULL) = 0;

  /** \details
    Sets new extents for the model.
    
    \param ext [in] An object of the <link OdTvExtents3d, OdTvExtents3d> class that represents new extents for the model.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks  
    If the new extents are successfully set, the method returns tvOk, otherwise it returns an appropriate error code. 
  */
  virtual OdTvResult setExtents(const OdTvExtents3d& ext) = 0;

  /** \details
    Retrieves the current extents of the specified type for the model. 
    
    \param ext    [out] A placeholder for the extents object.
    \param eType  [in] A type of extents to retrieve.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the extents are successfully returned, the method returns tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getExtents(OdTvExtents3d& ext, OdTv::ExtentsType eType = OdTv::kPreferred) const = 0;

  /** \details
    Retrieves a smart pointer to the entities iterator. 
    The entities iterator provides sequential access to entities that the model contains.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the entities iterator. If the model contains no entities, the method returns a null smart pointer.
    \remarks 
    If the rc parameter is not null and the smart pointer to the entities iterator is successfully returned, the rc parameter accepts the tvOk value, otherwise it contains an
    appropriate error code.
  */
  virtual OdTvEntitiesIteratorPtr getEntitiesIterator(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches for an entity using an entity handle.
    
    \param h [in] An entity handle.
    \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier of the found entity.
    \remarks 
    If the rc parameter is not null and the entity is found, the rc parameter accepts the tvOk value, otherwise it contains an
    appropriate error code.
    If the entity is not found, the method returns a null identifier (i.e. the isNull() method of the identifier returns true).
  */
  virtual OdTvEntityId findEntity(const OdUInt64 h, OdTvResult* rc = NULL) = 0;

  /** \details
    Retrieves the current value of the save flag.
    
    The save flag determines whether the model should be saved in a file.
    If the model data should be saved in a file, the flag value is equal to true, otherwise the flag value is false.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current value of the save flag.
    \remarks
    If the rc parameter is not null and the save flag value is successfully retrieved, the rc parameter accepts the tvOk value, otherwise it contains an
    appropriate error code.
  */
  virtual bool getNeedSaveInFile(OdTvResult* rc = NULL) const = 0;

  /** \details
    Isolates a specified entity in the model.
    
    \param entityId     [in] An entity identifier.
    \param bPerSession  [in] A flag that determines whether the entity should be isolated in the model only during the current session (if true) 
    or until the method unisolate() is called (if false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the entity is successfully isolated in the model, the method returns tvOk, otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_features_display_of_model_content, Manage Display of a Model Content>
  */
  virtual OdTvResult isolate(const OdTvEntityId& entityId, bool bPerSession = true) = 0;

  /** \details
    Hides a specified entity in the model.
    
    \param entityId     [in] An entity identifier.
    \param bPerSession  [in] A flag that determines whether the entity should be hidden in the model only during the current session (if true) or not (if false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the entity is successfully hidden in the model, the method returns tvOk, otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_features_display_of_model_content, Manage Display of a Model Content>
  */
  virtual OdTvResult hide(const OdTvEntityId& entityId, bool bPerSession = true) = 0;

  /** \details
    Unhides a specified entity in the model.
    
    \param entityId     [in] An entity identifier.
    \param bApplyToChilds  [in] A flag that determines whether the descendants of the entity should be unhidden regardless of whether the entity itself was hidden.
    \param bPerSession  [in] A flag that determines whether the entity should be unhidden in the model only during the current session (if true) or not (if false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the entity is successfully unhidden in the model, the method returns tvOk, otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_features_display_of_model_content, Manage Display of a Model Content>
  */
  virtual OdTvResult unHide(const OdTvEntityId& entityId, bool bApplyToChilds = true, bool bPerSession = true) = 0;

  /** \details
    Isolates specified geometry (or a sub-entity) in the model.
    
    \param geometryId   [in] An identifier of the geometry.
    \param bPerSession  [in] A flag that determines whether the geometry should be isolated in the descendants of the model
    only during the current session (if true) or not (if false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the geometry or sub-entity is successfully isolated, the method returns tvOk, otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_features_display_of_model_content, Manage Display of a Model Content>
  */
  virtual OdTvResult isolate(const OdTvGeometryDataId& geometryId, bool bPerSession = true) = 0;

  /** \details
    Hides specified geometry (or a sub-entity) in descendants of the model.
    
    \param geometryId   [in] An identifier of the geometry.
    \param bPerSession  [in] A flag that determines whether the geometry should be hidden in the descendants of the model only during the current session (if true) or not (if false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the geometry or sub-entity is successfully hidden, the method returns tvOk, otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_features_display_of_model_content, Manage Display of a Model Content>
  */
  virtual OdTvResult hide(const OdTvGeometryDataId& geometryId, bool bPerSession = true) = 0;

  /** \details
    Unhides specified geometry (or a sub-entity) in descendants of the model.
    
    \param geometryId   [in] An identifier of the geometry.
    \param bApplyToChilds  [in] A flag that determines whether the descendants of the geometry should be unhidden regardless of whether the geometry itself was hidden.
    \param bPerSession  [in] A flag that determines whether the geometry should be unhidden in the descendants of the model only during the current session (if true) or not (if false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the geometry or sub-entity is successfully unhidden, the method returns tvOk, otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_features_display_of_model_content, Manage Display of a Model Content>
  */
  virtual OdTvResult unHide(const OdTvGeometryDataId& geometryId, bool bApplyToChilds = true, bool bPerSession = true) = 0;

  /** \details
    Isolates objects in a selection set of the model.
    
    \param selectionSetPtr   [in] A selection set with selected objects for isolation.
    \param bPerSession  [in] A flag that determines whether objects should be isolated in the descendants of the model
    only during the current session (if true) or not (if false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_working_with_features_display_of_model_content, Manage Display of a Model Content>
  */
  virtual OdTvResult isolate(const OdTvSelectionSetPtr selectionSetPtr, bool bPerSession = true) = 0;

  /** \details
    Hides objects in a selection set of descendants of the model.
    
    \param selectionSetPtr   [in] A selection set with selected objects for hiding.
    \param bPerSession  [in] A flag that determines whether objects should be hidden in the descendants of the model only during the current session (if true) or not (if false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_working_with_features_display_of_model_content, Manage Display of a Model Content>
  */
  virtual OdTvResult hide(const OdTvSelectionSetPtr selectionSetPtr, bool bPerSession = true) = 0;

  /** \details
    Unhides objects in a selection set of descendants of the model.
    
    \param selectionSetPtr   [in] A selection set with selected objects for unhiding.
    \param bApplyToChilds       [in] A flag that determines whether the descendants should be unhidden regardless of whether the selection set item itself was hidden
    \param bPerSession    [in] A flag that determines which objects should be unhidden in the descendants of the model: which were hided only during the current session (if true) or not (if false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_working_with_features_display_of_model_content, Manage Display of a Model Content>
  */
  virtual OdTvResult unHide(const OdTvSelectionSetPtr selectionSetPtr, bool bApplyToChilds = true, bool bPerSession = true) = 0;

  /** \details
    Unisolates objects in the model.
    
    \param bPerSession  [in] A flag that determines which objects should be unhidden in the descendants of the model: which were hided only during the current session (if true) or not (if false).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If objects were successfully unisolated, the method returns tvOk, otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_features_display_of_model_content, Manage Display of a Model Content>
  */
  virtual OdTvResult unIsolate(bool bPerSession = true) = 0;

  /** \details
    Sets the selectability property value for the model. 
    
    \param selectability [in] A new selectability property value.
    \param bRecursive    [in] If true, the same selectability will be set for all blocks that has references in this model.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the new selectability property value is successfully set, the method returns tvOk, otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_features_selections, Work with Selections>
  */
  virtual OdTvResult setSelectability(const OdTvSelectabilityDef& selectability, bool bRecursive = true) = 0;

  /** \details
    Retrieves the current selectability property value for the model. 
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current value of the selectability property.
    \remarks 
    If the rc parameter is not null and the selectability property value has been successfully retrieved, the rc parameter accepts the tvOk value, otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_features_selections, Work with Selections>
  */
  virtual OdTvSelectabilityDef getSelectability(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new value of the content selectable property for all insert objects in the model.
    
    \param bSelectable [in] A new value of the content selectable property to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    OBSOLETE. Insert's content is always selectable and all depends from the 'kBlocksCache' option of the device and from the selection level.
  */
  virtual OdTvResult setInsertsContentsSelectable(bool bSelectable) = 0;

  /** \details
    Sets a new transformation matrix that can rotate, translate (move) and scale the whole model.
    
    \param matrix [in] A transformation matrix object.
    \param bFastMode [in] If true, the fast transformation mode will be used.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the transformation matrix is successfully set, the method returns tvOk; otherwise it returns an appropriate error code.
    The fast transformation mode is provided mainly for the temporary transformations which can be used in different tools.
  */
  virtual OdTvResult setModelingMatrix(const OdTvMatrix& matrix, bool bFastMode = false) = 0;

  /** \details
    Retrieves the current transformation matrix for the model.
    A transformation matrix can rotate, translate (move) and scale the whole model.

    \param bFastMode [out] Flag indicating that the fast mode is used.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the transformation matrix represented as an instance of the <link OdTvMatrix, OdTvMatrix> class.
    \remarks
    If the rc parameter is not null and the transformation matrix is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    If the transformation matrix is identity, the bFastMode will be always false.
  */
  virtual OdTvMatrix getModelingMatrix(bool* bFastMode = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the statistics for the model.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the statistics object for the model.
    \remarks 
    If the rc parameter is not null and the statistics object is successfully retrieved, the rc parameter accepts the tvOk value, otherwise it contains an
    appropriate error code.
  */
  virtual OdTvGeometryStatistic getStatistic(OdTvResult* rc = NULL) = 0;

  /** \details
    Calculates and adds partial view indexes to the model.
    
    \param bUpdateExisting [in] A flag that determines whether partial view indexes already exist in the model; the method updates them (if the value is equal to true).
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If partial view indexes are successfully calculated and added to the model, the method returns tvOk; 
    otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_features_partial_viewing, Work with Partial Viewing>
  */
  virtual OdTvResult addPartialViewIndex(bool bUpdateExisting = true) = 0;

  /** \details
    Extents model partial view indexes.
    
    \param id [in] Instance of OdTvEntityId that should be added to partial index.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_working_with_features_partial_viewing, Work with Partial Viewing>
  */
  virtual OdTvResult extendPartialViewIndex( const OdTvEntityId& id ) = 0;

  /** \details
    Returns true if the model has partial view index.
    
    \param bCheckExtents [in] If true, method will also check that index has valid extents.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \sa
    <link tv_working_with_features_partial_viewing, Work with Partial Viewing>
  */
  virtual bool hasPartialViewIndex( bool bCheckExtents = false, OdTvResult* rc = NULL) = 0;

  /** \details
    Sets the CDA (Common Data Access) tree storage for this model.
    
    \param treeStorageId [in] An identifier of the CDA tree storage.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the tree is successfully set, the method returns tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setCDATreeStorage(const OdTvCDATreeStorageId& treeStorageId) = 0;

  /** \details
    Returns the CDA (Common Data Access) tree storage for this model.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier of the CDA (Common Data Access ) tree storage.
    \remarks
    If the rc parameter is not null and the CDA tree storage ID has been successfully retrieved, the rc parameter accepts the tvOk value, otherwise it contains an
    appropriate error code.
  */
  virtual OdTvCDATreeStorageId getCDATreeStorage(OdTvResult* rc = NULL) = 0;

  /** \details
    Sets the sectionable property to the model. This mean, that all entities and geometry in this model can be cut via cutting plane.
    
    \param bVal [in] A flag that specify if sectionable is enabled.
    \remarks
    If the sectionable property value has been successfully changed, the method returns tvOk; otherwise it returns an appropriate error code.
    \sa
    <link tv_working_with_features_cutting_planes, Work with Cutting Planes>
  */
  virtual OdTvResult setSectionable(bool bVal) = 0;

  /** \details
    Retrieves the current value of the sectionable property for the model.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current sectionable property.
    \remarks
    If the rc parameter is not null and the sectionable property was returned successfully, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
    \sa
    <link tv_working_with_features_cutting_planes, Work with Cutting Planes>
  */
  virtual bool getSectionable(OdTvResult* rc = NULL) const = 0;

  /** \details
    Copies all model's data to a specified model (attributes, entities etc).
    All current data in the target model will be deleted or overwritten.
    
    \param targetModelId [in] A target <link OdTvModelId, model identifier>. The data will be copied to the model the identifier refers.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the operation was successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
    This function is designed for copying models within the same database. If source and destination models belong to different databases
    default OdTvAttributeResolver will be created and used. Using copyTo(OdTvModelId& targetModelId, OdTvAttributeResolverPtr pResolver) will be
    more optimal in this case.
  */
  virtual OdTvResult copyTo(OdTvModelId& targetModelId) const = 0;

  /** \details
    Copies all model's data to a specified model (attributes, entities etc).
    All current data in the target model will be deleted or overwritten.
    
    \param targetModelId [in] A target <link OdTvModelId, model identifier>. The data will be copied to the model the identifier refers.
    \param pResolver [in] A smart pointer to the instance of OdTvAttributeResolver
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the operation was successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
    This function is designed for copying models from different databases. If source and destination models belong to the same database using
    copyTo(OdTvModelId& targetModelId) will be more optimal.
  */
  virtual OdTvResult copyTo(OdTvModelId& targetModelId, OdTvAttributeResolverPtr pResolver) const = 0;

  /** \details
    Inserts an entity object to the model after the 'prevEntityId' and returns the identifier of the inserted entity.
    
    \param prevEntityId [in] Identifier of the entity after which to insert a new entity.
    \param name         [in] A name of the entity.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the inserted entity if it is successfully inserted, otherwise returns a null identifier.
    \remarks
    If the 'rc' parameter is not null and the entity is created and inserted to the model, the 'rc' parameter accepts the tvOk value,
    otherwise it contains an appropriate error code. Such method can be used when the draw order is important. In other cases it is better 
    to use the 'appendEntity' method.
  */
  virtual OdTvEntityId insertEntityAt(const OdTvEntityId& prevEntityId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;
  
  /** \details
    Moves the specified object that belongs to the model to the end of entities list.
    
    \param entityId     [in] Object to be moved.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    Position in entities list defines objects draw order.
    Object have to be the top-level object of this model.
  */
  virtual OdTvResult moveToFront( const OdTvEntityId& entityId ) = 0;
  
  /** \details
    Moves the specified object that belongs to the model to the beginning of entities list.
    
    \param entityId     [in] Object to be moved.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    Position in entities list defines objects draw order.
    Object have to be the top-level object of this model.
  */
  virtual OdTvResult moveToBottom( const OdTvEntityId& entityId ) = 0;
  
  /** \details
    Moves the specified object that belongs to the model after the 'prevEntityId' in entities list.
    
    \param entityId     [in] Object to be moved.
    \param prevEntityId [in] Identifier of the entity after which to move a new entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    Position in entities list defines objects draw order.
    Object have to be the top-level object of this model.
  */
  virtual OdTvResult moveAfter( const OdTvEntityId& entityId, const OdTvEntityId& prevEntityId ) = 0;

  /** \details
    Inserts a view-dependent entity object to the model after the 'prevEntityId' and returns the identifier of the inserted entity.
    
    \param prevEntityId [in] Identifier of the entity after which to insert a new entity.
    \param viewId       [in] View in which to draw the appended entity.
    \param name         [in] A name of the entity.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier of the inserted entity.
    \remarks
    If the 'rc' parameter is not null and the entity is created and inserted to the model, the 'rc' parameter accepts the tvOk value,
    otherwise it contains an appropriate error code. Such method can be used when the draw order is important. In other cases it is better 
    to use the 'appendViewDependentEntity' method.
  */
  virtual OdTvEntityId insertViewDependentEntityAt(const OdTvEntityId& prevEntityId, const OdTvGsViewId& viewId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds an insert entity object to the model after the 'prevEntityId' and returns the identifier of the inserted entity.
    
    \param prevEntityId [in] Identifier of the entity after which to add a new insert entity.
    \param blockId      [in] An identifier of the block that should contain the appended insert object.
    \param name         [in] A name of the insert object.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the added insert entity if it is successfully added, otherwise returns a null identifier.
    \remarks
    If the 'rc' parameter is not null and the insert entity is created and added to the model, the 'rc' parameter accepts the tvOk value,
    otherwise it contains an appropriate error code. Such method can be used when the draw order is important. In other cases it is better 
    to use the 'appendInsert' method.
  */
  virtual OdTvEntityId addInsertAt(const OdTvEntityId& prevEntityId, const OdTvBlockId& blockId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;

  /** \details
    Adds a view-dependent insert entity object to the model after the 'prevEntityId' and returns the identifier of the inserted entity.
    
    \param prevEntityId [in] Identifier of the entity after which to add a new insert entity.
    \param viewId       [in] View in which this insert will be drawn.
    \param blockId      [in] An identifier of the block that should contain the appended insert object.
    \param name         [in] A name of the insert object.
    \param rc           [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns an identifier for the added insert entity if it is successfully added, otherwise returns a null identifier.
    \remarks
    If the 'rc' parameter is not null and the insert entity is created and added to the model, the 'rc' parameter accepts the tvOk value,
    otherwise it contains an appropriate error code. Such method can be used when the draw order is important. In other cases it is better 
    to use the 'appendViewDependentInsert' method.
  */
  virtual OdTvEntityId addViewDependentInsertAt(const OdTvEntityId& prevEntityId, const OdTvGsViewId& viewId, const OdTvBlockId& blockId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;

  /** \details
    Sets the measuring units for this model.
    
    \param units [in] Measuring units to set.
    \param userDefCoefToMeters [in] User defined coefficient to meters transform. Actual only for 'kUserDefined' units.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the operation was successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setUnits(OdTv::Units units, double userDefCoefToMeters = 1.) = 0;

  /** \details
    Returns the measuring units set for this model.
    
    \param userDefCoefToMeters[out] User defined coefficient to meters transform. Actual only for 'kUserDefined' units.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Measuring units set for this model.
    \remarks
    If the 'rc' parameter is not null and the units was successfully returned, the 'rc' parameter accepts the tvOk value,
    otherwise it contains an appropriate error code.
  */
  virtual OdTv::Units getUnits(double* userDefCoefToMeters = NULL, OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the units transformation matrix for the model. This matrix is present when the database drawing units is not equal to the model's units.
    
    This transformation matrix scale the whole model.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the units transformation matrix represented as an instance of the <link OdTvMatrix, OdTvMatrix> class.
    \remarks
    If the rc parameter is not null and the units transformation matrix is successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an
    appropriate error code.
  */
  virtual OdTvMatrix getUnitsMatrix(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the type of the model.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the type of the model.
  */
  virtual OdTvModel::Type getModelType( OdTvResult* rc = NULL ) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvModel, OdTvModel> object.
*/
typedef OdTvSmartPtr<OdTvModel> OdTvModelPtr;


/** \details
  The base interface class for a Visualize SDK model identifier. 
  The model identifier interface provides access to the model object.
*/
class ODTV_EXPORT OdTvModelId : public OdTvId
{
public:
  
  /** \details
    Opens the model for reading or writing. 
    
    \param mode [in] An access mode (read, write, or read-write).
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the model object. 
    \remarks 
    If the rc parameter is not null and the model is successfully opened, the rc parameter accepts the tvOk value, otherwise it contains an
    appropriate error code.
  */
  OdTvModelPtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;
};


/** \details
  The base interface class for the iterator of Visualize SDK models.
  An iterator object provides sequential access to a collection of model objects. 
*/
class ODTV_EXPORT OdTvModelsIterator : public OdTvIterator, public OdTvIObject
{
public:
  
  /** \details
    Retrieves the model that is currently referenced by the iterator object.
    
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the model identifier if the iterator refers to a model, otherwise returns an identifier with a null value.
    \remarks 
    If the rc parameter is not null and the model identifier is successfully returned, the rc parameter accepts the tvOk value, otherwise it contains an
    appropriate error code.
    If the iterator refers to a model, the identifier that the method returns is not null (i.e. the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvModelId getModel(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches for a model defined by its identifier and moves the iterator to this model if found.
    
    \param modelId [in]  A model identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the model specified by its identifier is found, the method returns tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek(const OdTvModelId& modelId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvModelsIterator, OdTvModelsIterator> object.
*/
typedef OdTvSmartPtr<OdTvModelsIterator> OdTvModelsIteratorPtr;

#endif //_ODTV_MODEL_H_INCLUDED_
