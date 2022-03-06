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


#ifndef _ODTV_MODELIMPL_H_INCLUDED_
#define _ODTV_MODELIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvModel.h"
#include "TvInterfaceWrappers.h"
#include "TvBlockTableRecordImpl.h"
#include "TvEntityImpl.h"
#include "TvSelectionImpl.h"
#include "DbPartialViewing.h"
#include "TvGiPath.h"

#define STL_USING_QUEUE
#include "OdaSTL.h"
#include "TvCommonDataAccessTreeNode.h"
#include "TvCommonDataAccessTree.h"

class OdTvModelStatisticImpl;

typedef std::map<OdTvDbObjectId, OdTvGiPathSet> OdTvEntityTvGiPathMap;

/** \details
Get OdTvEntityId from sub entity as OdTvGeometryDataId
*/
OdTvEntityId getOdTvEntityIdFromOdTvGeometryDataId(OdTvGeometryDataId geometryDataId);


/** \details
This class is the internal implementation of the block.
*/
class OdTvModelImpl : public OdTvBlockTableRecord
{
  OdTvModelImpl();

public:
  ODRX_DECLARE_MEMBERS(OdTvModelImpl);

  virtual ~OdTvModelImpl();

  enum modFlags
  {
    kNeedSaveInFile  = 1,
    kInternal        = 2,  // means that it is an internal model (user couldn't get an access to it)
    kFastTransformed = 4,
    kSectionable     = 8
  };

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface implementation
//////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Set the true if and only if the model should be saved in the file
  */
  void setNeedSaveInFile(bool bNeed) { SETBIT(m_flags, kNeedSaveInFile, bNeed); m_bSelectable = bNeed; }

  /** \details
  Returns true if and only if the model should be saved in the file (stored via xData)
  */
  bool getNeedSaveInFile() const { return GETBIT(m_flags, kNeedSaveInFile); }

  /** \details
  Isolate entity from this model
  */
  OdTvResult isolate(const OdTvEntityId& entityId, bool bPerSession = true);

  /** \details
  Hide entity from this model
  */
  OdTvResult hide(const OdTvEntityId& entityId, bool bPerSession = true);

  /** \details
  Unhides a specified entity in the model.
  */
  OdTvResult unHide(const OdTvEntityId& entityId, bool bApplyToChilds = true, bool bPerSession = true);

  /** \details
  Isolate geometry (or subentity) from descendants of this model
  */
  OdTvResult isolate(const OdTvGeometryDataId& geometryId, bool bPerSession = true);

  /** \details
  Hide geometry (or subentity) from descendants of this model
  */
  OdTvResult hide(const OdTvGeometryDataId& geometryId, bool bPerSession = true);

  /** \details
  Unhides specified geometry (or a sub-entity) in descendants of the model.
  */
  OdTvResult unHide(const OdTvGeometryDataId& geometryId, bool bApplyToChilds = true, bool bPerSession = true);

  /** \details
  Isolates objects form this selection set from the model.
  */
  OdTvResult isolate(const OdTvSelectionSetPtr selectionSetPtr, bool bPerSession = true);

  /** \details
  Hides objects form this selection set from descendants of the model.
  */
  OdTvResult hide(const OdTvSelectionSetPtr selectionSetPtr, bool bPerSession = true);

  /** \details
  Unhides objects in a selection set of descendants of the model.
  */
  OdTvResult unHide(const OdTvSelectionSetPtr selectionSetPtr, bool bApplyToChilds = true, bool bPerSession = true);

  /** \details
  Unisolate entity from this model
  */
  OdTvResult unIsolate(bool bPerSession = true);

  /** \details
  Sets a new transformation matrix that can rotate, translate (move) and scale the whole model.
  */
  OdTvResult setModelingMatrix(const OdTvMatrix& matrix, bool bFastMode);

  /** \details
  Retrieves the current transformation matrix for the model.
  A transformation matrix can rotate, translate (move) and scale the whole model.
  */
  OdTvMatrix getModelingMatrix(bool* bFastMode = NULL) const;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//OdTvModelImpl own methods 
//////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Set the type of the TV model
  */
  void setModelType(OdTvModel::Type type) { m_modelType = type;}

  /** \details
  Get the type of the TV model
  */
  OdTvModel::Type getModelType() const {return m_modelType;}

  /** \details
  For loading from VSF file
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  For saving in VSF file
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  re-implemented decomposeForSave
 */
  virtual OdTvDbObjectPtr decomposeForSave(OdDb::DwgVersion ver, OdTvDbObjectId& replaceId, bool& exchangeXData);

  /** \details
  Set that the view is internal
  */
  void setInternal(bool bInternal) { SETBIT(m_flags, kInternal, bInternal); }

  /** \details
  Get flag which indicates that the view is internal
  */
  bool getInternal() const { return GETBIT(m_flags, kInternal); }

  /** \details
  hide entity persistent
  */
  OdTvResult hideEntityPersistent(const OdTvEntityId& entityId);

  /** \details
  unhide geometries (should return > 0 only if bSeparateCall == false). In this case the return value means the depth for which it is need to check the geometry visibility
  */
  OdUInt32 unHidePersistent(const OdTvEntityId& entityId, const OdTvGeometryDataIdsArray& geometriesDataArray, bool bApplyToChilds, bool bSeparateCall = true);

  /** \details
  hide entity using GiPath, per session only
  */
  OdTvResult hideEntityPerSession(const OdTvEntityId& entityId, bool bForIsolate, bool bDoHide, const OdTvSubItemPath* pSubPath = NULL, bool bApplyToChilds = false);

  /** \details
  isolate inserts route
  */
  void isolateInsertsRoute(const OdTvEntityId& topLevelEntId, const OdTvEntityIdsArray& fullInsertsRoute, OdUInt32 idStartFrom = 0);

  /** \details
  Get direct pointer the internal transform
  */
  OdTvMatrix* getModelingMatrixInternal() const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  /** \details
  Returns true if the model has partial view index
  */
  bool hasPartialViewIndex( bool bCheckExtents = false );

  /** \details
  Calculate and add partial view indexes to the model
  */
  OdTvResult addPartialViewIndex(bool bUpdateExisting = true);

  /** \details
  Extents model partial view indexes.
  */
  OdTvResult extendPartialViewIndex( const OdTvEntityId& id );

  /** \details
  Sets the CDA (Common Data Access) tree storage for this model.
  */
  OdTvResult setCDATreeStorage(const OdTvCDATreeStorageId& treeStorageId);

  /** \details
  Returns the CDA (Common Data Access) tree storage for this model.
  */
  OdTvCDATreeStorageId getCDATreeStorage(OdTvResult* rc = NULL);

  /** \details
  Sets the sectionable property to the model. This mean, that all entities and geometry in this model can be cut via cutting plane.
  */
  OdTvResult setSectionable(bool bVal);

  /** \details
  Retrieves the current value of the sectionable property for the model.
  */
  bool getSectionable(OdTvResult* rc = NULL) const;

  /** \details
  Retrieves the current value of the selectable property for the model.
  */
  bool getSelectable(OdTvResult* rc = NULL) const;

  /** \details
  Copies all model's data to a specified model (attributes, entities etc).
  All current data in the target model will be deleted or overwrited.
  */
  OdTvResult copyTo(OdTvModelId& targetModelId, bool bFromInterface = true) const;

  /** \details
  Copies all model's data to a specified model (attributes, entities etc).
  All current data in the target model will be deleted or overwrited.
  */
  OdTvResult copyTo(OdTvModelId& targetModelId, OdTvAttributeResolverPtr pResolver, bool bFromInterface = true) const;

  /** \details
  Sets the measuring units for this model.
  */
  OdTvResult setUnits(OdTv::Units units, double userDefCoefToMeters = 1.);

  virtual OdTvResult moveToFront( const OdTvEntityId& entityId );
  virtual OdTvResult moveToBottom( const OdTvEntityId& entityId );
  virtual OdTvResult moveAfter( const OdTvEntityId& entityId, const OdTvEntityId& prevEntityId );

  /** \details
  Returns the measuring units set for this model.
  */
  OdTv::Units getUnits(double* userDefCoefToMeters = NULL, OdTvResult* rc = NULL) const;

  /** \details
  Sets the database units.
  */
  void setDbUnits(OdTv::Units units);

  /** \details
  Returns the database units.
  */
  OdTv::Units getDbUnits() const;

  /** \details
  Returns true if the measuring units for this model should be inherited from the database drawing units.
  */
  bool getUnitsInherited() const { return m_bUnitsInherited; }

  /** \details
  Get fast transform matrix for this model
  */
  OdTvMatrix getFastTransform() const;

  /** \details
  Get units scale matrix for this model
  */
  OdTvMatrix getUnitsScaleTransform() const;

private:

  /** \details
  Copy common properties to target model
  */
  void copyToInternal(OdTvModelId& targetModelId) const;

  OdTvDbObjectId getTvDbObjectId(const OdTvEntityId& id) const;
  bool isMineTopLevelObject(const OdTvEntityId& id) const;

private:

  OdTvModel::Type   m_modelType;
  OdUInt8           m_flags;

  // transform matrix (NULL by default)
  OdTvMatrix*       m_pTransform;

  // data for isolate/hide, unisolate
  OdTvHidedObjectsSet m_persistentInvisEntitiesArray;
  OdTvHidedObjectsSet m_entitiesWithPersistentInvisGeometry;

  // new data for isolate/hide
  OdTvEntityTvGiPathMap m_temporaryHiddenObjects;

  //partial viewing module
  OdTvDbPartialViewingModulePtr m_pPartialViewingModule;

  //common data access tree
  OdTvDbObjectId m_CDATreeStorageId;

  // model is selectable
  bool m_bSelectable;

  //units of the model
  OdTv::Units m_Units;

  //units of the database (the same for all models. Stored here since it is problematic to store it in database)
  OdTv::Units m_dbUnits;

  //indicates that units should be inherited from database
  bool        m_bUnitsInherited;

  //user defined coefficient to meters conversion
  double m_dUserDefCoefToMeters;
};

typedef OdSmartPtr<OdTvModelImpl> OdTvModelImplPtr;


/** \details
    This is an wrapper of the interface class for OdTvModelRootEntity object.

    \remarks
    The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvModelWrapper : public OdTvModel
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvModel, OdTvModelImpl)

  friend class OdTvDatabaseImpl;
  friend class OdTvGsViewImpl;
  friend class OdTvModelsIteratorImpl;

protected:
  ODRX_HEAP_OPERATORS();

public:

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface implementation
//////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Creates an entity object and returns the appropriate ID
  */
  virtual OdTvEntityId appendEntity(OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Appends an view dependent entity object to the model and returns identifier of the appended entity.
  \param name   [in] A name of the entity.
  \param viewId [in] View, in which this entity will be drawn.
  \param rc     [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \remarks
  If rc parameter is not null and the entity has been created and added to the model, rc parameter accepts tvOk value,
  otherwise it contains an appropriate error code.
  */
  virtual OdTvEntityId appendViewDependentEntity(const OdTvGsViewId& viewId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Appends an insert entity object and returns the appropriate ID
  */
  virtual OdTvEntityId appendInsert(const OdTvBlockId& blockId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Appends an insert entity object to the model and returns identifier of the appended insert entity.
  \param viewId   [in] View, in which this insert will be drawn.
  \param blockId  [in] An identifier of the block that should contain appended insert object.
  \param name     [in] A name of the insert object.
  \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  \returns Returns an identifier for the appended insert entity if it has been successfully added, otherwise returns a null identifier.
  \remarks
  If rc parameter is not null and the insert entity has been created and added to the model, rc parameter accepts tvOk value,
  otherwise it contains an appropriate error code.
  */
  virtual OdTvEntityId appendViewDependentInsert(const OdTvGsViewId& viewId, const OdTvBlockId& blockId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Appends a light entity object and returns the appropriate ID
  */
  virtual OdTvEntityId appendLight(OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Appends a camera entity object and returns the appropriate ID
  */
  virtual OdTvEntityId appendCamera( OdString name = OdString::kEmpty, OdTvResult* rc = NULL );

  /** \details
  Remove an entity object with the given ID
  */
  virtual OdTvResult removeEntity(const OdTvEntityId& id);

  /** \details
  Remove all entities
  */
  virtual OdTvResult clearEntities();

  /** \details
  Set the name of the model

  \remarks
  The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
  underscores, and some special characters, but cannot contain inadmissible letters
  ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).

  Also there are 3 forbidden names: "*Model_Space", "*Paper_Space", "*Paper_Space0"
  */
  virtual OdTvResult setName(const OdString& sName);

  /** \details
  Returns the name of the model
  */
  virtual OdString getName(OdTvResult* rc = NULL);

  /** \details
  Set extents to the block
  */
  virtual OdTvResult setExtents(const OdTvExtents3d& ext);

  /** \details
  Get 'eType' extents from this block
  */
  virtual OdTvResult getExtents(OdTvExtents3d& ext, OdTv::ExtentsType eType = OdTv::kPreferred) const;

  /** \details
  Returns the pointer to the entity iterator object
  */
  virtual OdTvEntitiesIteratorPtr getEntitiesIterator(OdTvResult* rc = NULL) const;

  /** \details
  Find an entity by name, and return OdTvEntityId
  */
  virtual OdTvEntityId findEntity(const OdUInt64 h, OdTvResult* rc = NULL);

  /** \details
  Returns true if and only if the model should be saved in the file
  */
  virtual bool getNeedSaveInFile(OdTvResult* rc = NULL) const;

  /** \details
  Isolate entity from this model
  */
  virtual OdTvResult isolate(const OdTvEntityId& entityId, bool bPerSession = true);

  /** \details
  Hide entity from this model
  */
  virtual OdTvResult hide(const OdTvEntityId& entityId, bool bPerSession = true);

  /** \details
  Unhides a specified entity in the model.
  */
  virtual OdTvResult unHide(const OdTvEntityId& entityId, bool bApplyToChilds = true, bool bPerSession = true);

  /** \details
  Isolate geometry (or subentity) from descendants of this model
  */
  virtual OdTvResult isolate(const OdTvGeometryDataId& geometryId, bool bPerSession = true);

  /** \details
  Hide geometry (or subentity) from descendants of this model
  */
  virtual OdTvResult hide(const OdTvGeometryDataId& geometryId, bool bPerSession = true);

  /** \details
  Unhides specified geometry (or a sub-entity) in descendants of the model.
  */
  virtual OdTvResult unHide(const OdTvGeometryDataId& geometryId, bool bApplyToChilds = true, bool bPerSession = true);

  /** \details
  Isolates objects form this selection set from the model.
  */
  virtual OdTvResult isolate(const OdTvSelectionSetPtr selectionSetPtr, bool bPerSession = true);

  /** \details
  Hides objects form this selection set from descendants of the model.
  */
  virtual OdTvResult hide(const OdTvSelectionSetPtr selectionSetPtr, bool bPerSession = true);

  /** \details
  Unhides objects in a selection set of descendants of the model.
  */
  virtual OdTvResult unHide(const OdTvSelectionSetPtr selectionSetPtr, bool bApplyToChilds = true, bool bPerSession = true);

  /** \details
  Unisolate entity from this model
  */
  virtual OdTvResult unIsolate(bool bPerSession = true);

  /** \details
  Sets the selectability to the model
  */
  virtual OdTvResult setSelectability(const OdTvSelectabilityDef& selectability, bool bRecursive);

  /** \details
  Returns OdTvSelectabilityDef of the model
  */
  virtual OdTvSelectabilityDef getSelectability(OdTvResult* rc = NULL) const;

  /** \details
  Sets the insert contents selectable value
  */
  virtual OdTvResult setInsertsContentsSelectable(bool bSelectable);

  /** \details
  Sets a new transformation matrix that can rotate, translate (move) and scale the whole model.
  */
  virtual OdTvResult setModelingMatrix(const OdTvMatrix& matrix, bool bFastMode = false);

  /** \details
  Retrieves the current transformation matrix for the model.
  A transformation matrix can rotate, translate (move) and scale the whole model.
  */
  virtual OdTvMatrix getModelingMatrix(bool* bFastMode = NULL, OdTvResult* rc = NULL) const;

  /** \details
  Returns statistic for current model
  */
  virtual OdTvGeometryStatistic getStatistic(OdTvResult* rc = NULL);

  /** \details
  Copies all model's data to a specified model (attributes, entities etc).
  All current data in the target model will be deleted or overwrited.
  */
  virtual OdTvResult copyTo(OdTvModelId& targetModelId) const;

  /** \details
  Copies all model's data to a specified model (attributes, entities etc).
  All current data in the target model will be deleted or overwrited.
  */
  virtual OdTvResult copyTo(OdTvModelId& targetModelId, OdTvAttributeResolverPtr pResolver) const;

  //**************************************************************************************
  // OdTvIObject methods implementation
  //**************************************************************************************

  /** \details
  Returns true if the model has partial view index
  */
  virtual bool hasPartialViewIndex( bool bCheckExtents = false, OdTvResult* rc = NULL);

  /** \details
  Calculate and add partial view indexes to the model
  */
  virtual OdTvResult addPartialViewIndex(bool bUpdateExisting = true);

  /** \details
  */
  virtual OdTvResult extendPartialViewIndex( const OdTvEntityId& id );

  /** \details
  Sets the CDA (Common Data Access) tree storage for this model.
  */
  virtual OdTvResult setCDATreeStorage(const OdTvCDATreeStorageId& treeStorageId);

  /** \details
  Returns the CDA (Common Data Access) tree storage for this model.
  */
  virtual OdTvCDATreeStorageId getCDATreeStorage(OdTvResult* rc = NULL);

  /** \details
  Sets the sectionable property to the model. This mean, that all entities and geometry in this model can be cut via cutting plane.
  */
  virtual OdTvResult setSectionable(bool bVal);

  /** \details
  Retrieves the current value of the sectionable property for the model.
  */
  virtual bool getSectionable(OdTvResult* rc = NULL) const;

  /** \details
  Inserts an entity object to the model after the 'prevEntityId' and returns the identifier of the inserted entity.
  */
  virtual OdTvEntityId insertEntityAt(const OdTvEntityId& prevEntityId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Inserts a view-dependent entity object to the model after the 'prevEntityId' and returns the identifier of the inserted entity.
  */
  virtual OdTvEntityId insertViewDependentEntityAt(const OdTvEntityId& prevEntityId, const OdTvGsViewId& viewId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Adds an insert entity object to the model after the 'prevEntityId' and returns the identifier of the inserted entity.
  */
  virtual OdTvEntityId addInsertAt(const OdTvEntityId& prevEntityId, const OdTvBlockId& blockId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Adds a view-dependent insert entity object to the model after the 'prevEntityId' and returns the identifier of the inserted entity.
  */
  virtual OdTvEntityId addViewDependentInsertAt(const OdTvEntityId& prevEntityId, const OdTvGsViewId& viewId, const OdTvBlockId& blockId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  virtual OdTvResult moveToFront( const OdTvEntityId& entityId );
  virtual OdTvResult moveToBottom( const OdTvEntityId& entityId );
  virtual OdTvResult moveAfter( const OdTvEntityId& entityId, const OdTvEntityId& prevEntityId );

  /** \details
  Sets the measuring units for this model.
  */
  virtual OdTvResult setUnits(OdTv::Units units, double userDefCoefToMeters = 1.);

  /** \details
  Returns the measuring units set for this model.
  */
  virtual OdTv::Units getUnits(double* userDefCoefToMeters = NULL, OdTvResult* rc = NULL) const;

  /** \details
  Retrieves the units transformation matrix for the model.
  A transformation matrix scale the whole model.
  */
  virtual OdTvMatrix getUnitsMatrix(OdTvResult* rc = NULL) const;

  /** \details
    Retrieves the type of the model.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the type of the model.
  */
  virtual OdTvModel::Type getModelType( OdTvResult* rc = NULL ) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Internal methods
//////////////////////////////////////////////////////////////////////////////////////////////////////

private:
  /** \details
  Returns the rendering type of the model
  */
  OdTvModel::Type getModelType();
};



/** \details
    This is an implementation of the iterator class for the models
*/
class ODTV_EXPORT OdTvModelsIteratorImpl : public OdTvModelsIterator
{
  friend class OdTvDatabaseImpl;
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
    Returns the model currently referenced by this Iterator object.
  */
  virtual OdTvModelId getModel(OdTvResult* rc = NULL) const;

  /** \details
    Positions this Iterator object at the specified model.
    \param objectId [in]  Model ID.
  */
  virtual OdTvResult seek(const OdTvModelId& ModelId);

  /** \details
    Methods for creating the object
  */
  static OdTvModelsIteratorPtr createObject(OdTvDbSymbolTableIterator* pDbIterator);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:

  OdTvModelsIteratorImpl();
  OdTvModelsIteratorImpl(OdTvDbSymbolTableIterator* pDbIterator);

  virtual ~OdTvModelsIteratorImpl();

  // Db iterator
  OdTvDbSymbolTableIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;
};


#include "TD_PackPop.h"

#endif // _ODTV_MODELIMPL_H_INCLUDED_

