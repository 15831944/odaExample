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




#ifndef OD_DBINDEX_H
#define OD_DBINDEX_H

#include "TD_PackPush.h"

class OdTvDbDate;
class OdTvDbIndexIterator; 
class OdTvDbFilter;
class OdTvDbIndexUpdateData;
class OdTvDbBlockChangeIterator;
class OdTvDbFilter;
class OdTvDbBlockTableRecord;
class OdTvDbBlockChangeIterator;
class OdTvDbIndexUpdateData;
class OdTvDbBlockChangeIteratorImpl;
class OdTvDbIndexUpdateDataImpl;
class OdTvDbIndexUpdateDataIteratorImpl;
class OdTvDbFilteredBlockIterator;

#include "DbFilter.h"

/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbFilteredBlockIterator object pointers.
*/
typedef OdSmartPtr<OdTvDbFilteredBlockIterator> OdTvDbFilteredBlockIteratorPtr;

extern void processBTRIndexObjects(
  OdTvDbBlockTableRecord* pBlock, 
  int indexCtlVal,
  OdTvDbBlockChangeIterator* pBlkChgIter,
  OdTvDbIndexUpdateData* pIdxUpdData);


/** \details
    This class iterates through changed entities in an OdTvDbBlockTableRecord instance.
    
    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbBlockChangeIterator
{
private:
  friend class OdTvDbBlockChangeIteratorImpl;
  OdTvDbBlockChangeIteratorImpl* m_pImpl;
  OdTvDbBlockChangeIterator() : m_pImpl(0) {}
  OdTvDbBlockChangeIterator(
    const OdTvDbBlockChangeIterator&);
public:

  /** \details
    Sets this Iterator object to reference the entity that it would normally return first.
     
    \remarks
    Allows multiple traversals of the iterator list.
  */
    void start();

  /** \details
    Returns the Object ID of the entity currently referenced by this Iterator object.
  */
    OdTvDbObjectId id() const;
  
  /** \details
    Sets this Iterator object to reference the entity following the current entity.
  */
    void next();

  /** \details
    Returns true if and only if the traversal by this Iterator object is complete.
  */
    bool done(); 
  
  /** \details
    Returns the Object ID of the entity currently referenced by this Iterator object, 
    and the flags and data associated with it.
    
    \param currentId [out]  Receives the current Object ID.
    \param flags [out]  Receives the 8-bit flags.
    \param data [out]  Receives the 32-bit data
  */
    void curIdInfo(
    OdTvDbObjectId& currentId, 
    OdUInt8& flags, 
    OdUInt32& data) const;
    
  /** \details
    Sets the flags and data associated with the object currently referenced by this Iterator object.
    
    \param flags [in]  Current object 8-bit flags.
    \param data [in]  Current object 32-bit data
  */
    void setCurIdInfo(
    OdUInt8 flags, 
    OdUInt32 data);
  
  /** \details
    Returns the OdTvDbIndexUpdateData object associating Object IDs to data and flags. 
  */
  OdTvDbIndexUpdateData* updateData() const;
  
  /** \details
    Clears the processed bit (0x04) of the flags of entities being traversed.
  */
  void clearProcessedFlags();
};

/** \details
    This class associates Index specific flags and data with an OdTvDbObjectId. 
    
    \sa
    TD_Db
    
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbIndexUpdateData 
{
  friend class OdTvDbIndexUpdateDataImpl;
  OdTvDbIndexUpdateDataImpl* m_pImpl;
  OdTvDbIndexUpdateData() : m_pImpl(0) {}
  OdTvDbIndexUpdateData(
    const OdTvDbIndexUpdateData&);
public:
  enum UpdateFlags 
  { 
    kModified   = 1, // Modified RO
    kDeleted    = 2, // Deleted RO
    kProcessed  = 4, // Processed RW
    kUnknownKey = 8  // Unknown key
  };
  /** \details
    Returns the Object ID of the OdTvDbBlockTableRecord instance that owns this OdTvDbIndexUpdateData object.
  */
  OdTvDbObjectId objectBeingIndexedId() const;

  
  /** \details
    Adds the specified Object ID to this OdTvDbIndexUpdateData object.

    \param Object ID [in] Object ID to be added.
  */
  void addId(
    OdTvDbObjectId objectId);
  
  /** \details
    Sets the flags associated with the specified Object ID in this OdTvDbIndexUpdateData object.
    
    \param objectID [in]  Object ID.
    \param flags [in]  8-bit flags.
    
    \remarks
    Returns true if and only if successful.
  */
  bool setIdFlags(
    OdTvDbObjectId objectId, 
    OdUInt8 flags);

  /** \details
    Sets the data associated with the specified Object ID in this OdTvDbIndexUpdateData object.
    
    \param objectID [in]  Object ID.
    \param data [in]  32-bit data.
    
    \remarks
    Returns true if and only if successful.
  */
  bool setIdData(
    OdTvDbObjectId objectId, 
    OdUInt32 data);

  /** \details
    Returns the data associated with the specified Object ID in this OdTvDbIndexUpdateData object.
    
    \param objectID [in]  Object ID.
    \param data [out]  32-bit data.
    
    \remarks
    Returns true if and only if successful.
  */
  bool getIdData(
    OdTvDbObjectId objectId, 
    OdUInt32& data) const;

  /** \details
    Returns the flags associated with the specified Object ID in this OdTvDbIndexUpdateData object.
    
    \param objectID [in]  Object ID.
    \param flags [out]  Receives the 8-bit flags.
    
    \remarks
    Returns true if and only if successful.
  */
  bool getIdFlags(
    OdTvDbObjectId objectId, 
    OdUInt8& flags) const; 

  /** \details
    Returns the flags and data associated with the specified Object ID in this OdTvDbIndexUpdateData object.
    
    \param objectID [in]  Object ID.
    \param flags [out]  Receives the 8-bit flags.
    \param data [out]  Receives the 32-bit data.
    
    \remarks
    Returns true if and only if successful.
  */
  bool getFlagsAndData(
    OdTvDbObjectId objectId, 
    OdUInt8& flags, 
    OdUInt32& data) const;
};

/** \details
    This class iterates through OdTvDbIndexUpdateData instances.    

    \sa
    TD_Db

    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbIndexUpdateDataIterator
{
  friend class OdTvDbIndexUpdateDataIteratorImpl;
  OdTvDbIndexUpdateDataIteratorImpl* m_pImpl;
public:
  OdTvDbIndexUpdateDataIterator(
    const OdTvDbIndexUpdateData* pIndexUpdateData);
  
  /** \details
    Sets this Iterator object to reference the entity that it would normally return first.
     
    \remarks
    Allows multiple traversals of the iterator list.
  */
    void start();

  /** \details
    Returns the Object ID of the entity currently referenced by this Iterator object.
  */
    OdTvDbObjectId id() const;
  
 /** \details
    Sets this Iterator object to reference the entity following the current entity.
 */
    void next();

  /** \details
    Returns true if and only if the traversal by this Iterator object is complete.
  */
    bool done(); 
  
  /** \details
    Returns the Object ID of the entity currently referenced by this Iterator object, 
    and the flags and data associated with it.
    
    \param currentId [out]  Receives the current Object ID.
    \param flags [out]  Receives the 8-bit flags.
    \param data [out]  Receives the 32-bit data
  */
    void currentData(
    OdTvDbObjectId& currentId, 
    OdUInt8& flags, 
    OdUInt32& data) const;
};


/** \details
    The class is the base class for all OdDb Index objects.

    \sa
    TD_Db
    
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbIndex : public OdTvDbObject
{
public:
  ODDB_DECLARE_MEMBERS(OdTvDbIndex);

  OdTvDbIndex();
  
  
  /** \details
    Creates an Iterator object that provides access to the entities in this Index object.
    
    \param pFilter [in]  Pointer to the filter to be applied to this Index object.
  */
   virtual OdTvDbFilteredBlockIteratorPtr newIterator(
    const OdTvDbFilter* pFilter) const;
 
  /** \details
    Fully rebuilds this Index object from the entities in the block table record object.
    \param pIdxData [in]  Pointer to the OdTvDbIndexUpdateData object to be used in the rebuild. 
  */
   virtual void rebuildFull(
    OdTvDbIndexUpdateData* pIdxData);
  
  /** \details
    Sets the Julian lastUpdatedAt timestamp for this Index object.
    
    \param time [in]  Julian date.
  */
  void setLastUpdatedAt(
    const OdTvDbDate& time);
    
  /** \details
    Returns the Julian lastUpdatedAt timestamp for this Index object.
  */
  OdTvDbDate lastUpdatedAt() const;
  
  /** \details
    Sets the UT lastUpdatedAt timestamp for this Index object.
    
    \param time [in]  UT date.
  */
  void setLastUpdatedAtU(
    const OdTvDbDate& time);
    
  /** \details
    Returns the UT lastUpdatedAt timestamp for this Index object.
  */
  OdTvDbDate lastUpdatedAtU() const;
  
  /** \details
    Returns true if and only if this Index object is up to date.
  */
  bool isUptoDate() const; 
  
  virtual OdResult dwgInFields(
    OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(
    OdTvDbDwgFiler* pFiler) const;

  virtual OdResult dxfInFields(
    OdTvDbDxfFiler* pFiler);

  virtual void dxfOutFields(
    OdTvDbDxfFiler* pFiler) const;

protected:
 
  /** \details
    Called by OdTvDbIndexFilterManager::updateIndexes() when only modifications are being registered. 

    \param iterator [in]  Iterator of modified entities.
    
    \remarks
    Modified entities includes added, deleted, and changed entities.
    
    \remarks
    This class must be implemented in custom classes derived from OdTvDbIndex. A full rebuild may be performed if desired.
  */
 virtual void rebuildModified(
    OdTvDbBlockChangeIterator* iterator);
  
  friend class OdTvDbIndexImpl;
  friend void processBTRIndexObjects(
    OdTvDbBlockTableRecord* pBTR, 
    int indexCtlVal, 
    OdTvDbBlockChangeIterator* pBlkChgIter, 
    OdTvDbIndexUpdateData* pIdxUpdData );
};
/** \details
  This template class is a specialization of the OdSmartPtr class for OdTvDbIndex object pointers.
*/
typedef OdSmartPtr<OdTvDbIndex> OdTvDbIndexPtr;

class OdTvDbBlockTableRecord;
class OdTvDbBlockReference;

/** \details
    This namespace provides functions pertaining to indices and filters.
    
    \sa
    TD_Db
    
    <group TD_Namespaces>
*/
namespace OdTvDbIndexFilterManager
{
  /** \details
    Updates all Index objects associated with all block table record objects in the specified
    OdTvDbDatabase object.
    
    \param pDb [in]  Pointer to the database object.
  */
  TOOLKIT_EXPORT void updateIndexes(
    OdTvDbDatabase* pDb);

  /** \details
  Updates all Index objects associated with specified block table record object in the specified
  OdTvDbDatabase object.
  \param pBTR [in] Pointer to the Block Table Record.
  \param pDb [in]  Pointer to the database object.
*/
  TOOLKIT_EXPORT void updateIndex(
    OdTvDbBlockTableRecord* pBTR,
    OdTvDbDatabase* pDb );
  
  /** \details
    Adds the specified Index object to the specified block table record object.
    
    \param pBTR [in]  Pointer to the block table record object.
    \param pIndex [in]  Pointer to the Index object.
    
    \remarks
    An index of the same OdRxClass as the specified index will be deleted.
  */
  TOOLKIT_EXPORT void addIndex(
    OdTvDbBlockTableRecord* pBTR, 
    OdTvDbIndex* pIndex);
  
  /** \details
    Removes the specified Index object from the specified block table record object.
    
    \param pBTR [in]  Pointer to the Block Table Record.
    \param key [in]  Class descriptor to specify the index.
  */
  TOOLKIT_EXPORT void removeIndex(
    OdTvDbBlockTableRecord* pBTR, 
    const OdRxClass* key);

  
  /** \details
    Returns the specified Index object.
    
    \param pBTR [in]  Pointer to the block table record object.
    \param key [in]  Class descriptor to specify the index object.
    \param readOrWrite [in]  Mode in which to open the index object.
  */
  TOOLKIT_EXPORT OdTvDbIndexPtr getIndex(
    const OdTvDbBlockTableRecord* pBTR, 
    const OdRxClass* key, 
    OdDb::OpenMode readOrWrite = OdDb::kForRead);

  /** \param btrIndex [in]  Position of the Index object within the block table record object.
  */
    TOOLKIT_EXPORT OdTvDbIndexPtr getIndex(
    const OdTvDbBlockTableRecord* pBTR, 
    int btrIndex, 
    OdDb::OpenMode readOrWrite = OdDb::kForRead);
  
  /** \details
    Returns the number of indices associated with the block table record object.
    
    \param pBTR [in]  Pointer to the block table record object.
  */
  TOOLKIT_EXPORT int numIndexes(
    const OdTvDbBlockTableRecord* pBTR);
  
  /** \details
    Adds the specified Filter object to the specified block reference entity.
    
    \param pBlkRef [in]  Pointer to the block reference entity.
    \param pFilter [in]  Pointer to the Filter object.
    
    \remarks
    An filter of the same OdRxClass as the specified filter will be deleted.
  */
  TOOLKIT_EXPORT void addFilter(
    OdTvDbBlockReference* pBlkRef, 
    OdTvDbFilter* pFilter);
  
  /** \details
    Removes the specified Filter object from the specified block reference entity.
    
    \param pBlkRef [in]  Pointer to the block reference entity.
    \param key [in]  Class descriptor to specify the filter.
  */
  TOOLKIT_EXPORT void removeFilter(
    OdTvDbBlockReference* pBlkRef, 
    const OdRxClass* key);
  
  /** \details
    Returns the specified Filter object.
    
    \param pBlkRef [in]  Pointer to the block reference entity.
    \param key [in]  Class descriptor to specify the filter object.
    \param readOrWrite [in]  Mode in which to open the filter object.
  */
  TOOLKIT_EXPORT OdTvDbFilterPtr getFilter(
    const OdTvDbBlockReference* pBlkRef, 
    const OdRxClass* key, 
    OdDb::OpenMode readOrWrite);
  
  /** \param btrIndex [in]  Position of the Index object within the block table record object.
  */
    TOOLKIT_EXPORT OdTvDbFilterPtr getFilter(
    const OdTvDbBlockReference* pBlkRef, 
    int btrIndex, 
    OdDb::OpenMode readOrWrite);
  
  /** \details
    Returns the number of indices associated with the block reference entity.
    
    \param pBlkRef [in]  Pointer to the block reference entity.
  */
  TOOLKIT_EXPORT int numFilters(
    const OdTvDbBlockReference* pBlkRef);
}

#include "TD_PackPop.h"

#endif // OD_DBINDEX_H

