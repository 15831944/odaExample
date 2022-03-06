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


#ifndef _DBVIEWERSTREAMER_API_H_
#define _DBVIEWERSTREAMER_API_H_

#include "RxObject.h"
#include "DbIndex.h"
#include "Si/SiSpatialIndex.h"
#include "Gs/GsSpatialQuery.h"
#include "Gs/Gs.h"

#include "TD_PackPush.h"

#include "DbObjectIterator.h"
#include "DbBlockIterator.h"

struct IWeightCalculator {
  virtual float calculateVisualWeight(const OdGsView* pView, const OdGeExtents3d& extents) = 0;
};

struct DefaultWeightCalculatorImpl : public IWeightCalculator {
  virtual float calculateVisualWeight(const OdGsView* pView, const OdGeExtents3d& extents);
};

/** \details
  Library:  OdTvDbPartialViewing
  <group OdTvDb_Classes>
*/
class OdTvDbPartialViewingIndex : public OdTvDbIndex {
public:
  struct Entry : OdSiEntity {
    OdGePoint3d  pt1, pt2;
    OdTvDbObjectId dbentity;
    OdUInt32     dataSize;
    Entry*       pNext[2];
    Entry*       pPrev[2];

    bool extents(OdGeExtents3d& extents) const {
      extents.set(pt1, pt2);
      return extents.isValidExtents();
    }

    static Entry* cast(OdSiEntity *siEntity) {
      return static_cast<Entry*>(siEntity);
    }

    Entry()
    {
      pNext[ 0 ] = NULL; pNext[ 1 ] = NULL;
      pPrev[ 0 ] = NULL; pPrev[ 1 ] = NULL;
    }
  };

private:
  OdArray<Entry>  buffer;
  bool            isPlanar;
  OdSiSpatialIndexPtr si;
  mutable DefaultWeightCalculatorImpl weightCalculator;

  void compute(OdTvDbBlockTableRecord* pBlock);

  void reset(OdUInt32 n, bool isPlanar = false) {
    buffer.clear();
    buffer.resize(n);
    if (si.isNull() || this->isPlanar != isPlanar)
      si = OdSiSpatialIndex::createObject(isPlanar, n);
    else
      si->clear();
    this->isPlanar = isPlanar;
  }

  void clear() {
    buffer.clear();
    if (si.get())
      si->clear();
    isPlanar = false;
  }
public:
  ODDB_DECLARE_MEMBERS(OdTvDbPartialViewingIndex);

  OdTvDbPartialViewingIndex();

  virtual OdTvDbFilteredBlockIteratorPtr newIterator(const OdTvDbFilter* pFilter) const;

  virtual void rebuildFull(OdTvDbIndexUpdateData* pIdxData);
  virtual void rebuildModified(OdTvDbBlockChangeIterator* iterator);

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  void query(const OdSiShape& query, OdSiVisitor& visitor);

  inline bool getWorldExtents(OdGeExtents3d& ext) const {
    return si->extents(ext);
  }

  virtual void extend( OdTvDbObjectId entId, const OdGeExtents3d& extents );
};

typedef OdSmartPtr<OdTvDbPartialViewingIndex> OdTvDbPartialViewingIndexPtr;

/** \details
  Library:  OdTvDbPartialViewing.
  <group OdTvDb_Classes>
*/
class OdTvDbPartialViewingFilter : public OdTvDbFilter {
  OdGsViewPtr view;
public:
  ODDB_DECLARE_MEMBERS(OdTvDbPartialViewingFilter);

  OdTvDbPartialViewingFilter();

  virtual OdRxClass* indexClass() const;

  void set(const OdGsView* view);

  const OdGsView* get() const;
};

typedef OdSmartPtr<OdTvDbPartialViewingFilter> OdTvDbPartialViewingFilterPtr;

/** \details
  Library:  OdTvDbPartialViewing
  <group OdTvDb_Classes>
*/
class OdTvDbPartialViewingModule : public OdRxModule {
public:
  class DataManagerContext;

  /** \details
    Attaches Db/Gs data manager that filters (unloads/pages/markup/erase) offscreen data
    when entire drawing file is too big to be loaded completely into run-time.

    \returns
    Returns OdGsDevice-based wrapper that implements entity filtering.

    \param gs [in]  Input GS to be managed.
    \param queryFilter [in, optional]  interface object for filtering control.
    \param mgrCtx [in, optional]  hook for custom data management.

    \sa
    *  OdTvDbPartialViewingFilter
    *  OdTvDbPartialViewingIndex
    *  OdGsDevice
  */
  virtual OdGsDevicePtr attachDataManagerTo(OdGsDevice* gs, DataManagerContext* mgrCtx) = 0;

  class DataManagerContext : public OdRxObject {
  public:
    virtual OdTvDbObjectIteratorPtr currentSet() = 0;
    virtual void manageData(OdTvDbObjectIterator& willBeShown, OdTvDbObjectIterator& mayBeUnloaded) = 0;
    virtual OdMutex* accessMutex() { return NULL; }
  };
  typedef OdSmartPtr<DataManagerContext> DataManagerContextPtr;

  virtual void filterViewingData(OdGsDevice* filterSettings, 
      DataManagerContext* dataManager, OdArray<OdTvDbFilterPtr>* pFilters = 0,
      bool bForceCreateIndexes = false, bool bEnableUnload = true, 
      IWeightCalculator* pWeightCalculator = NULL) = 0;

  virtual void addIndex(OdGsDevice* filterSettings) = 0;

  virtual void addIndex(OdTvDbBlockTableRecord* pBTR, bool bUpdate = true) = 0;

  virtual bool hasIndex(OdTvDbBlockTableRecord *pBTR, bool bCheckExtents = false) = 0;

  virtual void extendIndex( OdTvDbBlockTableRecord* pBTR, OdDbStub* id, const OdGeExtents3d& ext ) = 0;

  virtual OdTvDbObjectIteratorPtr getUnloadedObjects(OdTvDbObjectIterator& objects) = 0;

  virtual OdTvDbObjectIteratorPtr filterCustomViewingData( 
    OdTvDbObjectId blockId, 
    OdTvDbDatabase* pDb, 
    OdGsView* pGsView, 
    const OdGeMatrix3d& transformMatrix, 
    bool bForceCreateIndexes = false, 
    IWeightCalculator* pWeightCalculator = NULL) = 0;

  virtual OdUInt64 countUnloadedEntries( OdGsDevice* filterSettings ) = 0;
  virtual OdUInt64 countUnloadedEntries( OdTvDbBlockTableRecord* pBTR ) = 0;
};

typedef OdSmartPtr<OdTvDbPartialViewingModule> OdTvDbPartialViewingModulePtr;


#include "TD_PackPop.h"

#endif // _DBVIEWERSTREAMER_API_H_
