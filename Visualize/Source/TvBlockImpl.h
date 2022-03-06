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


#ifndef _ODTV_BLOCKIMPL_H_INCLUDED_
#define _ODTV_BLOCKIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvBlock.h"
#include "TvInterfaceWrappers.h"
#include "TvBlockTableRecordImpl.h"
#include "DbPartialViewing.h"

/** \details
This class is the internal implementation of the block.
*/
class OdTvBlockImpl : public OdTvBlockTableRecord
{
  OdTvBlockImpl();

  virtual ~OdTvBlockImpl();
public:

  ODRX_DECLARE_MEMBERS(OdTvBlockImpl);

  /** \details
  For loading from VSF file
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  For saving in VSF file
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(bool bIncludeDataFromOwnHeap = false, OdTvResult* rc = NULL) const;

  /** \details
  Calculate and add partial view indexes to the block
  */
  virtual OdTvResult addPartialViewIndex(bool bUpdateExisting = true);

  /** \details
  Extents model partial view indexes.
  */
  virtual OdTvResult extendPartialViewIndex( const OdTvEntityId& id );

  /** \details
  Returns true if the model has partial view index
  */
  virtual bool hasPartialViewIndex(bool bCheckExtents = false, OdTvResult* rc = NULL);

  /** \details
  Check if entity (and sub entities inside) has geometry.
  */
  bool hasGeometry() const;

  /** \details
  Copies all block's data to a specified block (attributes, entities etc).
  All current data in the target block will be deleted or overwrited.
  */
  OdTvResult copyTo(OdTvBlockId& targetBlockId, bool bFromInterface = true) const;

  /** \details
  Copies all block's data to a specified block (attributes, entities etc).
  All current data in the target block will be deleted or overwrited.
  */
  OdTvResult copyTo(OdTvBlockId& targetBlockId, OdTvAttributeResolverPtr pResolver, bool bFromInterface = true) const;

private:
  //partial viewing module
  OdTvDbPartialViewingModulePtr m_pPartialViewingModule;
};

typedef OdSmartPtr<OdTvBlockImpl> OdTvBlockImplPtr;



/** \details
    This is an wrapper of the interface class for OdTvDbBlockTableRecord object.

    \remarks
    The purpose of this class is to connect the internal entity object with an interface object
*/
class OdTvBlockWrapper : public OdTvBlock
{
  ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvBlock, OdTvBlockImpl)

protected:
  ODRX_HEAP_OPERATORS();

public:

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface implementation
//////////////////////////////////////////////////////////////////////////////////////////////////////

  /** \details
  Appends an entity object and returns the appropriate ID
  */
  virtual OdTvEntityId appendEntity(OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Appends an insert entity object and returns the appropriate ID
  */
  virtual OdTvEntityId appendInsert(const OdTvBlockId& blockId, OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Appends a light entity object and returns the appropriate ID
  */
  virtual OdTvEntityId appendLight(OdString name = OdString::kEmpty, OdTvResult* rc = NULL);

  /** \details
  Remove an entity object with the given ID
  */
  virtual OdTvResult removeEntity(const OdTvEntityId& id);

  /** \details
  Remove all entites
  */
  virtual OdTvResult clearEntities();

  /** \details
  Returns the name of the model
  */
  virtual OdString getName(OdTvResult* rc = NULL);

  /** \details
  Returns the pointer to the entity iterator object
  */
  virtual OdTvEntitiesIteratorPtr getEntitiesIterator(OdTvResult* rc = NULL) const;

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
  Retrieves the statistics for the block.
  */
  virtual OdTvGeometryStatistic getStatistic(OdTvResult* rc = NULL);

  /** \details
  Calculate and add partial view indexes to the block
  */
  virtual OdTvResult addPartialViewIndex(bool bUpdateExisting = true);

  /** \details
  Extents model partial view indexes.
  */
  virtual OdTvResult extendPartialViewIndex( const OdTvEntityId& id );

  /** \details
  Returns true if the model has partial view index
  */
  virtual bool hasPartialViewIndex(bool bCheckExtents = false, OdTvResult* rc = NULL);

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
  Copies all block's data to a specified block (attributes, entities etc).
  All current data in the target block will be deleted or overwrited.
  */
  virtual OdTvResult copyTo(OdTvBlockId& targetBlockId) const;

  /** \details
  Copies all block's data to a specified block (attributes, entities etc).
  All current data in the target block will be deleted or overwrited.
  */
  virtual OdTvResult copyTo(OdTvBlockId& targetBlockId, OdTvAttributeResolverPtr pResolver) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);
};


/** \details
This is an implementation of the iterator class for the models
*/
class OdTvBlocksIteratorImpl : public OdTvBlocksIterator
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
  Returns the block currently referenced by this Iterator object.
  */
  virtual OdTvBlockId getBlock(OdTvResult* rc = NULL) const;

  /** \details
  Positions this Iterator object at the specified block.
  \param objectId [in]  Block ID.
  */
  virtual OdTvResult seek(const OdTvBlockId& BlockId);

  /** \details
  Methods for creating the object
  */
  static OdTvBlocksIteratorPtr createObject(OdTvDbSymbolTableIterator* pDbIterator);

  ODTV_WRAPPERS_REFERENCE_MEMBERS()

  virtual ~OdTvBlocksIteratorImpl();

private:

  OdTvBlocksIteratorImpl();
  OdTvBlocksIteratorImpl(OdTvDbSymbolTableIterator* pDbIterator);

  // Db iterator
  OdTvDbSymbolTableIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int                m_nRefCounter;
};


#include "TD_PackPop.h"

#endif // _ODTV_BLOCKIMPL_H_INCLUDED_

