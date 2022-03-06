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

#ifndef _ODTV_BLOCK_H_INCLUDED_
#define _ODTV_BLOCK_H_INCLUDED_

#include "Tv.h"
#include "TvEntity.h"
#include "TvIObject.h"
#include "TvStatistics.h"

class OdTvDatabaseId;
class OdTvInsertId;

class OdTvBlock;

/** \details
  A data type that represents a smart pointer to an <link OdTvBlock, OdTvBlock> object.
*/
typedef OdTvSmartPtr<OdTvBlock> OdTvBlockPtr;

/** \details
  This class defines the interface for a block identifier object. The identifier allows access to an <link OdTvBlock, OdTvBlock> object.
  
  \sa
  <link tv_working_with_base_classes_reference_geometry, Work with Reference Geometry>
*/
class ODTV_EXPORT OdTvBlockId : public OdTvId
{
public:

  /** \details
    Opens the block for read or write operations. 
    
    \param mode [in]  Open mode. The object can be opened either for read or for write operations.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns the smart pointer to the opened block.
    \remarks 
    If the block was successfully opened, the method returns tvOk in the rc output parameter, otherwise it returns an appropriate error code.   
  */
  OdTvBlockPtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;

};


/** \details
  This is an abstract class that represents the interface for a block object. 
*/  
class ODTV_EXPORT OdTvBlock : public OdTvHandledIObject
{  
public:

  /** \details
    Creates an entity object and appends it to the block.
    
    \param name [in]  A name of the appended entity.
    \param rc [out]   A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the append operation.
    \returns Returns the appended entity identifier.
    \remarks
    If the rc parameter value is not NULL and the entity was created and appended successfully,
    the rc parameter accepts the tvOk value; otherwise it contains an error code.
  */
  virtual OdTvEntityId appendEntity(OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0; 

  /** \details
    Creates an insert entity object and appends it to the block.
    
    \param blockId  [in]  An identifier name of the appended entity.
    \param name     [in]  A name of the appended insert entity.
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the append operation.
    \returns Returns the identifier of the appended insert entity.
    \remarks
    If the rc parameter value is not NULL and the insert entity was created and appended successfully,
    the rc parameter accepts the tvOk value; otherwise it contains an error code.
  */
  virtual OdTvEntityId appendInsert(const OdTvBlockId& blockId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;

  /** \details
    Appends a light entity object and returns the appropriate ID.
    
    \param name [in] A light entity name. 
    \param rc       [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the append operation.
    \returns Returns the identifier of the appended light entity.
    \remarks
    If the rc parameter value is not NULL and the light entity was created and appended successfully,
    the rc parameter accepts the tvOk value; otherwise it contains an error code.
  */
  virtual OdTvEntityId appendLight(OdString name = OdString::kEmpty, OdTvResult* rc = NULL) = 0;

  /** \details
    Removes an entity object with the given identifier from the block.
    
    \param id [in] An object's identifier.
    \returns Returns the result of the remove operation as an <link OdTvResult, OdTvResult> value.
    If the entity object was successfully removed from the block, returns tvOk; otherwise returns the appropriate error code.
  */
  virtual OdTvResult removeEntity(const OdTvEntityId& id) = 0;

  /** \details
    Removes all entities contained in the block.
    
    \returns Returns the result of the remove operation as an <link OdTvResult, OdTvResult> value.
    If entities were successfully removed from the block, returns tvOk; otherwise returns the appropriate error code.
  */
  virtual OdTvResult clearEntities() = 0;

  /** \details
    Returns the current name of the block.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a string that contains the block name. 
    \remarks
    If the name was successfully returned and the rc parameter is not NULL, it accepts the tvOk value;
    otherwise it contains an error code.
  */
  virtual OdString getName(OdTvResult* rc = NULL) = 0;

  /** \details
    Returns the iterator object for accessing objects that the block contains.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns a smart pointer to the iterator. 
    \remarks 
    If the method returns the correct smart pointer and the rc parameter is not NULL, it accepts the tvOk value;
    otherwise it contains an error code.
  */
  virtual OdTvEntitiesIteratorPtr getEntitiesIterator(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets extents for the block.
    
    \param ext [in] An instance of the <link OdTvExtents3d, OdTvExtents3d> class that represents the block's extents.
    \returns Returns the result of the operation as an <link OdTvResult, OdTvResult> value.
    \remarks
    If the extents object was successfully applied to the block, the method returns tvOk; otherwise it returns the appropriate error code.
  */
  virtual OdTvResult setExtents(const OdTvExtents3d& ext) = 0;

  /** \details
    Retrieves the specified type of the block's extents.
    
    \param ext    [out] A placeholder for the extents object.
    \param eType  [in] A type of extents to retrieve.
    \returns Returns the result of the operation as an <link OdTvResult, OdTvResult> value.
    \remarks 
    If the extents object was successfully returned from the block, the method returns tvOk; otherwise it returns the appropriate error code.
  */
  virtual OdTvResult getExtents(OdTvExtents3d& ext, OdTv::ExtentsType eType = OdTv::kPreferred) const = 0;

  /** \details
    Finds an entity by name.
    
    \param h  [in] An entity handler.
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the entity's identifier. If the entity is not found, the isNull() method of the returned OdTvEntityId returns true.
    \remarks 
    If the entity was successfully found and the rc parameter is not NULL, it accepts the tvOk value; 
    otherwise it contains an error code.
  */
  virtual OdTvEntityId findEntity(const OdUInt64 h, OdTvResult* rc = NULL) = 0;

  /** \details
    Retrieves the statistics for the block.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the statistics object for the block.
    \remarks
    If the rc parameter is not null and the statistics object was successfully retrieved, the rc parameter accepts tvOk the value, otherwise it contains an
    appropriate error code.
  */
  virtual OdTvGeometryStatistic getStatistic(OdTvResult* rc = NULL) = 0;

  /** \details
    Calculates and adds partial view index to the block.
    
    \param bUpdateExisting [in] A flag that determines whether existing partial view index should be updated (true) or not (false).
    \returns Returns the result of the operation as an <link OdTvResult, OdTvResult> value.
    \remarks 
    If the partial view index was successfully calculated and added to the block, the method returns tvOk; otherwise it returns the appropriate error code.
  */
  virtual OdTvResult addPartialViewIndex(bool bUpdateExisting = true) = 0;

  /** \details
    Extents model partial view indexes.
    
    \param id [in] Instance of OdTvEntityId that should be added to partial index
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual OdTvResult extendPartialViewIndex( const OdTvEntityId& id ) = 0;

  /** \details
    Returns true if the model has partial view index
    
    \param bCheckExtents [in] If true, method will also check that index has valid extents
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
  */
  virtual bool hasPartialViewIndex(bool bCheckExtents = false, OdTvResult* rc = NULL) = 0;

  /** \details
    Sets the selectability property value for the block.
    
    \param selectability [in] A new selectability property value.
    \param bRecursive    [in] If true, the same selectability will be set for all blocks that has references in this block.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new selectability property value was successfully set, the method returns tvOk, otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setSelectability(const OdTvSelectabilityDef& selectability, bool bRecursive = true) = 0;

  /** \details
    Retrieves the current selectability property value for the block.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the current value of the selectability property.
    \remarks
    If the rc parameter is not null and the selectability property value was successfully retrieved, the rc parameter accepts tvOk value, otherwise it contains an
    appropriate error code.
  */
  virtual OdTvSelectabilityDef getSelectability(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets the contents selectable property value for the all inserts in block.
    
    \param bValue [in] A new insert contents selectable property value.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    OBSOLETE. Insert's content is always selectable. Selectability of insert's content depends on the 'kBlocksCache' option of the device and on the selection level.
  */
  virtual OdTvResult setInsertsContentsSelectable(bool bValue) = 0;

  /** \details
    Copies all block's data to a specified block (attributes, entities etc).
    All current data in the target block will be deleted or overwritten.
    
    \param targetBlockId [in] A target <link OdTvBlockId, block identifier>. The data will be copied to the block the identifier refers.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the operation was successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
    This function is designed for copying blocks within the same database. If source and destination blocks belong to different databases
    default OdTvAttributeResolver will be created and used. Using copyTo(OdTvBlockId& targetBlockId, OdTvAttributeResolverPtr pResolver) will be
    more optimal in this case.
  */
  virtual OdTvResult copyTo(OdTvBlockId& targetBlockId) const = 0;

  /** \details
    Copies all block's data to a specified block (attributes, entities etc).
    All current data in the target block will be deleted or overwritten.
    
    \param targetBlockId [in] A target <link OdTvBlockId, block identifier>. The data will be copied to the block the identifier refers.
    \param pResolver [in] A smart pointer to the instance of OdTvAttributeResolver
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the operation was successfully performed, the method returns tvOk; otherwise it returns an appropriate error code.
    This function is designed for copying blocks from different databases. If source and destination blocks belong to the same database using
    copyTo(OdTvBlockId& targetBlockId) is more optimal.
  */
  virtual OdTvResult copyTo(OdTvBlockId& targetBlockId, OdTvAttributeResolverPtr pResolver) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvBlock, OdTvBlock> object.
*/
typedef OdTvSmartPtr<OdTvBlock> OdTvBlockPtr;


/** \details
  An abstract class that provides an interface for the block's iterator object.
  The objects of classes inherited from this class can be used to access blocks that the model contains one-by-one.
*/
class ODTV_EXPORT OdTvBlocksIterator : public OdTvIterator, public OdTvIObject
{
public:

  /** \details
    Gets the block currently referenced by the iterator.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the identifier of the block that the iterator references.
    \remarks
    If the method successfully gets access to the referenced block and the rc parameter is not NULL, it accepts the tvOk value; 
    otherwise it contains an error code.
  */
  virtual OdTvBlockId getBlock(OdTvResult* rc = NULL) const = 0;

  /** \details
    Searches the block specified with its identifier through the iterator object.
    
    \param blockId [in]  A block identifier to search for.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the search operation.
    If the block with the specified identifier was found, the method returns tvOk value; otherwise it returns an error code.
    \remarks
    If the block was found, the method changes the iterator position,
    therefore the iterator references the found block in this case.
  */
  virtual OdTvResult seek(const OdTvBlockId& blockId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvBlocksIterator, OdTvBlocksIterator> object.
*/
typedef OdTvSmartPtr<OdTvBlocksIterator> OdTvBlocksIteratorPtr;


#endif //_ODTV_BLOCK_H_INCLUDED_
