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

#ifndef _ODDBSORTENSTABLEIMPL_INCLUDED_
#define _ODDBSORTENSTABLEIMPL_INCLUDED_


#include "IdArrays.h"
#include "DbSystemInternals.h"
#include "DbSortentsTable.h"
#include "DbObjectIterator.h"
#include "DbObjectImpl.h"

#define STL_USING_MAP
#include "OdaSTL.h"

// OdDbSortentsTable entries are saved in std::map. 
// OdDbObjectId-s are compared by OdDbStub* so order of entries is different each time.
// Therefore DD produces different file while saving.
// The next predicate is used to sort ids by handle in OdDbSortentsTable.
struct ObjectIdPred
{
  bool operator()(const OdDbObjectId& x, const OdDbObjectId& y) const
  {
    return x.getHandle() < y.getHandle();
  }
};

// here objectId (its handle) is key, Handle is value
typedef std::map<OdDbSoftPointerId, OdDbHandle, ObjectIdPred>  IdHandleMap;
#ifdef OD_USE_STD_LIST
// Custom allocator in nested container cannot be used for WinCE and sparc/gcc configurations
typedef std::list<OdDbSoftPointerId> SoftPointerIdList;
#else
typedef OdList<OdDbSoftPointerId> SoftPointerIdList;
#endif
typedef std::map<OdDbHandle, SoftPointerIdList> HandleIdMultiMap;

class OdDbSortentsTableImpl : public OdDbObjectImpl
{
  static OdDbSortentsTableImpl* getImpl(const OdDbSortentsTable *pObj)
  { return (OdDbSortentsTableImpl*)OdDbSystemInternals::getImpl(pObj);}

public:  
  OdDbSortentsTableImpl() : m_bValidMaps(false) {}
  // map containing data
  mutable IdHandleMap m_idHandleMap;
  mutable HandleIdMultiMap m_handleIdMap;
  mutable bool m_bValidMaps;

  // array - cache for different operations
  mutable HandlePairsArray m_handlePairs;

  // fills m_handlePairs if it is empty
  void updateHandlePairs();
  void updateMapFromHandlePairs() const;
  void updateHandleMaps(const OdDbHandle& h, const OdDbSoftPointerId& id) const;
  void invalidateMaps();

  void audit(OdDbAuditInfo* pAuditInfo);

  OdDbSoftPointerId getOwnerBlockId();
  OdDbSoftPointerId getOwnerBlockId() const
  {
    return m_OwnerBlockId;
  }

  void setOwnerBlockId(OdDbSoftPointerId id)
  {
    m_OwnerBlockId = id;
  }
  OdUInt32 findHandleIndex(OdDbObjectId);
private:
  void setValidMaps() const { m_bValidMaps = true; }
  OdDbSoftPointerId m_OwnerBlockId;                             // MKU 10.12.2004 - it became private

  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;

  friend class OdDbSortentsTable;
  friend class OdDbSortedEntitiesIterator;
};

class OdDbSortedEntitiesIterator : public OdRxObjectImpl<OdDbObjectIterator>
{
  OdDbSortentsTablePtr m_pSET;
  HandlePairsArray::iterator m_curItem;
  bool m_bForward, m_bSkipDeleted;
  void skipDummyItems(bool atBeginning, bool bSkipDeleted);
public:

  /** Constructor
  */
  OdDbSortedEntitiesIterator(OdDbSortentsTable* pSET, 
    const OdDbBlockTableRecord* pBTR,
    bool atBeginning,
    bool bSkipDeleted);

  static OdDbObjectIteratorPtr createObject(
    OdDbSortentsTable* pSET, 
    const OdDbBlockTableRecord* pBTR,
    bool atBeginning,
    bool bSkipDeleted)
  {
    return OdDbObjectIteratorPtr((OdDbObjectIterator*)new OdDbSortedEntitiesIterator(pSET, pBTR, 
      atBeginning, bSkipDeleted), kOdRxObjAttach);
  }

  /** Reset the iterator's current position to the specified object in the list.
      @param idFrom (I) Object ID of the object to which this iterator should point to.
      @param bForward (I) If true, this iterator will proceed forward through the list, otherwise
             it will proceed backwards.
      @param bSkipDeleted (I) If true, this iterator will skip deleted entities, otherwise
             it will not skip deleted entities.
  */
  virtual void start(OdDbObjectId idFrom, bool bForward = true, bool bSkipDeleted = true);
  virtual void start(bool bForward = true, bool bSkipDeleted = true);

  /** Returns true if the current position of this iterator is past either end of the 
      entity list, false otherwise.
  */
  virtual bool done() const;

  /** Returns the Object ID of the entity referenced by the current position of this
      iterator.
  */
  virtual OdDbObjectId objectId() const;

  /** Opens and returns the entity referenced by the current position of this
      iterator.
      @param openMode (I) Mode in which to open the entity.
      @param openErasedEntity (I) If true, open the current entity even if it is erased, 
      otherwise do not open an erased entity.
      @return pointer to the entity if it successfully opened, otherwise NULL.
  */
  virtual OdDbEntityPtr entity(OdDb::OpenMode openMode = OdDb::kForRead, 
    bool openErasedEntity = false);

  /** Increments or decrements the current position of this iterator by one.
      @param bForward (I) If true, increment the current position, otherwise decrement it.
      @param bSkipDeleted (I) If true, skip deleted entities, otherwise do not skip them.
  */
  virtual void step(bool bForward = true, bool bSkipDeleted = true);

  /** Sets the current position of this iterator to the location of the specified entity.
      @param id Object ID at of entity at which to set the current position.
  */
  virtual bool seek(OdDbObjectId id);

  /** Sets the current position of this iterator to the location of the specified entity.
      @param pEntity Entity at which to set the current position.
  */
  virtual bool seek(const OdDbEntity* pEntity);
};

class HandlePairsCompare
{
public:
  bool operator()(const HandlePair& a1, const HandlePair& a2)
  {
    if (a1.first != a2.first)
      return (a1.first < a2.first);

    const OdDbHandle& a1sec = a1.second.getHandle();
    const OdDbHandle& a2sec = a2.second.getHandle();

    // If one of the objectIds is 0 -- means predicate is called from
    // place where ObjectId is unknown
    if(a1sec.isNull() || a2sec.isNull())
      return false;

    // Code below serves the situation if entities have the same draw order.
    // Entity which does not have explicitly specified draw order is drawn first
    // (Fix for CR1864
    const OdDbHandle h1 = (a1.first == a1sec) ? static_cast<const OdDbHandle>(a1.first - 1) : a1.first;
    const OdDbHandle h2 = (a2.first == a2sec) ? static_cast<const OdDbHandle>(a2.first - 1) : a2.first;

    return h1 < h2;
  }
};

// static member containing no data
extern HandlePairsCompare handlePairsCompare;

#endif // _ODDBSORTENSTABLEIMPL_INCLUDED_
