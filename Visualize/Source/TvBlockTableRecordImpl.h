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


#ifndef _ODTV_BLOCKTABLERECORD_H_INCLUDED_
#define _ODTV_BLOCKTABLERECORD_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvBlock.h"
#include "TvEntity.h"
#include "TvInterfaceWrappers.h"
#include "TvUserDataImpl.h"
#include "TvStatisticsImpl.h"
#include "TvCommonDataAccessTreeNode.h"

#include "DbSymbolTable.h"
#include "DbBlockTableRecord.h"

#define  STL_USING_MAP
#include <map>

class OdTvGsViewId;

/** \details
This class is the TV implementation of the block table record which is the mother class
for the TV implementation of the model and block 
*/
class OdTvBlockTableRecord : public OdTvDbBlockTableRecord, public OdTvXDataStorage
{
protected:

  OdTvBlockTableRecord();

  virtual ~OdTvBlockTableRecord();

  virtual bool subWorldDraw(OdGiWorldDraw* pWd) const;

public:

  ODRX_DECLARE_MEMBERS(OdTvBlockTableRecord);

  /** \details
  Defines the type of the block table recoed
  */
  enum Type
  {
    kModel = 0,  
    kBlock = 1
  };

  /** \details
  read from file/stream
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  write to file/stream
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  Creates an entity object and returns the appropriate ID
  */
  virtual OdTvEntityId appendEntity(const OdString& name, OdTvResult* rc = NULL);

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
  virtual OdTvEntityId appendInsert(const OdTvBlockId& blockId, const OdString& name, OdTvResult* rc = NULL);

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
  virtual OdTvEntityId appendLight(const OdString& name, OdTvResult* rc = NULL);

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

  virtual OdTvResult moveAfter( const OdTvEntityId& entityId, const OdTvEntityId& prevEntityId );
  virtual OdTvResult moveAfterLast( const OdTvEntityId& entityId );

  /** \details
  Appends a camera entity object and returns the appropriate ID
  */
  virtual OdTvEntityId appendCamera( const OdString& name, OdTvResult* rc = NULL );

  /** \details
  Remove an entity object with the given ID
  */
  virtual OdTvResult removeEntity(const OdTvEntityId& id);

  /** \details
  Remove all entities
  */
  virtual OdTvResult clearEntities();

  /** \details
  Returns the pointer to the entity iterator object
  */
  virtual  OdTvEntitiesIteratorPtr getEntitiesIterator(OdTvResult* rc = NULL) const;

  /** \details
  Set extents to the entity
  */
  virtual OdTvResult setExtents(const OdTvExtents3d& ext);

  /** \details
  Get 'eType' extents from this entity
  */
  virtual OdTvResult getExtents(OdTvExtents3d& ext, OdTv::ExtentsType eType = OdTv::kPreferred) const;

  /** \details
  Find an entity by name, and return OdTvEntityId
  */
  virtual OdTvEntityId findEntity(const OdUInt64 h, OdTvResult* rc = NULL);

  /** \details
  Perform actions after reading the file
  */
  virtual void afterReadFile();

  /** \details
  Return the type of the table record (model or block)
  */
  Type getType() { return m_type;}

  /** \details
  Retrieves the statistics for the block.
  */
  virtual OdTvGeometryStatistic getStatistic(OdTvResult* rc = NULL);

  /** \details
  Return the value of memory, which this object takes up.
  */
  virtual OdUInt64 getSizeOfDynamicData(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  /** \details
  Sets the selectability to the model
  */
  OdTvResult setSelectability(const OdTvSelectabilityDef& selectability, bool bRecursive);

  /** \details
  Returns OdTvSelectabilityDef of the model
  */
  OdTvSelectabilityDef getSelectability(OdTvResult* rc = NULL) const;

  /** \details
  Sets the insert contents selectable value
  */
  OdTvResult setInsertsContentsSelectable(bool bSelectable);

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  //OdTvBlockTableRecord own methods 
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Get statistic from block
  */
  void getBlockStatistic(OdTvEntitiesIteratorPtr pIt, OdTvGeometryStatisticImpl& stat);

  /** \details
  Get statistic from entity
  */
  void getEntityStatistic(OdTvGeometryDataIteratorPtr pIt, OdTvGeometryStatisticImpl& stat);

  /** \details
  Get entities count
  */
  OdUInt32 getEntitiesCount() const;

  /** \details
  Clear vertices spatial tree in all entities in block
  */
  virtual void clearSpatialTreeCacheInEntities();

protected:

  /** \details
  Get statistic from brep
  */
  void getBrepContent(OdTvGeometryDataId& brepGeomId, OdTvGeometryStatisticImpl& stat) const;

  /** \details
  Fill multimap with entities and their unique source ID for Common Access Data tree
  */
  virtual void collectEntitiesForCDA(std::multimap<OdUInt64, OdTvEntityId>& entitiesMap, bool bIsForBlock = false);

  /** \details
  Fill common data access tree by Visualize Ids
  */
  void fillCDANodesByVisualizeIds(OdTvCDATreeNodePtr pNode);

  /** \details
  Inserts an entity object to the model after the 'prevEntityId' and returns the identifier of the inserted entity.
  */
  OdTvEntityId insertEntityAt_internal(const OdTvEntityId& prevEntityId, const OdTvGsViewId& viewId, OdString name, OdTvResult* rc);

  /** \details
  Inserts an entity object to the model after the 'prevEntityId' and returns the identifier of the inserted entity.
  */
  OdTvEntityId addInsertAt_internal(const OdTvEntityId& prevEntityId, const OdTvGsViewId& viewId, const OdTvBlockId& blockId, OdString name, OdTvResult* rc);

  OdTvResult moveAfter_internal( const OdTvEntityId& entityId, const OdTvEntityId& prevEntityId );
  OdTvResult moveAfterLast_internal( const OdTvEntityId& entityId );

protected:

  // type block or model
  Type  m_type;

  // selectability flags
  OdUInt8          m_selectability;

  // extents of the block in the OCS (object (entity coordinate system) with taking into account local transform
  // (NULL by default) Not saved in file
  OdTvExtents3d*            m_pExtents;

  // Multimap with entities and their unique source ID for Common Access Data tree
  std::multimap<OdUInt64, OdTvEntityId> m_entitiesMap;
};

typedef OdSmartPtr<OdTvBlockTableRecord> OdTvBlockTableRecordPtr;


#include "TD_PackPop.h"

#endif // _ODTV_BLOCKTABLERECORD_H_INCLUDED_

