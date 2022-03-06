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

#ifndef _ODTV_PARTIALVIEWING_H_INCLUDED_
#define _ODTV_PARTIALVIEWING_H_INCLUDED_

#include "TD_PackPush.h"

#include "Tv.h"

#include "DbPartialViewing.h"
#include "Tf/TfRevisionControl.h"

#include "TvBackgroundQueue.h"
#include "TvDatabaseImpl.h"

class OdTvGsDeviceDataManagerContext;
typedef OdSmartPtr<OdTvGsDeviceDataManagerContext> OdTvGsDeviceDataManagerContextPtr;

/** \details
This class is the implementation of the object 'OdTvGsDeviceDataManagerContext'.
This object is needed for partial view load/unload objects of TV database.
*/
class OdTvGsDeviceDataManagerContext : public OdTvDbPartialViewingModule::DataManagerContext
{
public:

  static OdTvGsDeviceDataManagerContextPtr createObject( OdTvDbDatabase* pDb, bool bUseMT = false, bool bUnloadObjects = false, OdTvDatabaseImpl* pTvDb = NULL );

  virtual OdTvDbObjectIteratorPtr currentSet() { return m_itCurrent; };
  virtual void manageData (OdTvDbObjectIterator& willBeShown, OdTvDbObjectIterator& mayBeUnloaded);

  void filterViewingData(OdGsDeviceForTvImplPtr &pDevice);

  virtual ~OdTvGsDeviceDataManagerContext();

  void setIgnoreMode( bool b ) { m_bIgnoreAll = b; }
  bool getIgnoreMode() const { return m_bIgnoreAll; }

  bool getThreadRunning() const
  {
    TD_AUTOLOCK_P_DEF( m_internalMutex );
    return m_bThreadRunning;
  }
  void setThreadRunning( bool b ) 
  { 
    TD_AUTOLOCK_P_DEF( m_internalMutex );
    m_bThreadRunning = b; 
  }

  bool getUnloadObjects() const
  {
    TD_AUTOLOCK_P_DEF( m_internalMutex );
    return m_bUnloadObjects;
  }

  bool getAllObjectsLoaded() const
  {
    TD_AUTOLOCK_P_DEF( m_internalMutex );
    return m_bAllObjectsLoaded;
  }
  void setAllObjectsLoaded( bool b ) 
  { 
    TD_AUTOLOCK_P_DEF( m_internalMutex );
    m_bAllObjectsLoaded = b; 
  }

  bool getAllBlockContentLoaded() const
  {
    TD_AUTOLOCK_P_DEF( m_internalMutex );
    return m_bAllBlockContentLoaded;
  }
  void setAllBlockContentLoaded( bool b ) 
  { 
    TD_AUTOLOCK_P_DEF( m_internalMutex );
    m_bAllBlockContentLoaded = b; 
  }

  bool getIsVSFX() const
  {
    TD_AUTOLOCK_P_DEF( m_internalMutex );
    return m_bIsVSFX;
  }
  void setIsVSFX( bool b )
  {
    TD_AUTOLOCK_P_DEF( m_internalMutex );
    m_bIsVSFX = b;
  }

  OdMTLoadReactor* getBackgroundReactor()
  {
    return m_pReactor;
  }

  OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;

  void stop();
  void start();

protected:

  OdTvGsDeviceDataManagerContext();

  bool                    m_bUseMT;
  bool                    m_bUnloadObjects;
  bool                    m_bAllObjectsLoaded;
  bool                    m_bAllBlockContentLoaded;
  bool                    m_bIsVSFX;
  OdTvDatabaseImpl*       m_pTvDb;

  OdTvDbDatabase*           m_pDb;
  OdTvDbObjectIteratorPtr   m_itCurrent;

  OdTvResult unloadObject (OdTvDbObjectId &id);
  void eraseGsCache       (const OdTvDbObjectId& id);

private:

  OdTvDbPartialViewingModulePtr m_pPVModue;

  //SEA Multithread support
private:
  OdTvBackgroundQueue m_backQueue;
  OdApcQueuePtr m_pSTQueue;
  OdMutexPtr m_pMutex;
  bool       m_bInterrupt;

  mutable OdMutexPtr m_internalMutex;
  bool       m_bThreadRunning;
  bool       m_bIgnoreAll;

  OdMTLoadReactor* m_pReactor;

  OdGsDevice* m_pActiveDevice;

protected:
  void manageDataMT (OdTvDbObjectIterator& willBeShown, OdTvDbObjectIterator& mayBeUnloaded);

  void filterViewingDataInBackground(OdGsDeviceForTvImplPtr &pDevice);

public:
  bool isUseMT() const { return m_bUseMT; }
  void setUseMT( bool b );

  OdMutex* accessMutex() { return m_pMutex.get(); }

  bool interrupt() const { return m_bInterrupt; }

  void pushDetectedInsert( OdTvDbObjectId id );

  void resetActiveDevice()
  {
    TD_AUTOLOCK_P_DEF( m_internalMutex );
    m_pActiveDevice = NULL;
  }

  void manageInsertsData( const std::set< OdTvDbObjectId >& detectedInserts );
protected:
  struct IndexedViewInfo
  {
    OdGsView* m_pView;
    OdTvDbObjectId m_rootId;
  };
  OdArray< IndexedViewInfo > m_indexedViewInfo;
  struct IndexedReferenceInfo
  {
    OdArray< OdGsView* > m_views;
    OdGeMatrix3d m_matrix;
    OdGsCache* m_pParentCache;
    OdTvDbObjectId m_id;
    OdTvDbObjectId m_ownerId;
    OdGiDrawablePtr m_pDrawable;

    IndexedReferenceInfo()
    {
      m_matrix = OdGeMatrix3d::kIdentity;
      m_pParentCache = NULL;
    }

    IndexedReferenceInfo( OdTvDbObjectId id )
    {
      m_id = id;
      m_matrix = OdGeMatrix3d::kIdentity;
      m_pParentCache = NULL;
    }

    IndexedReferenceInfo( OdTvDbObjectId id, IndexedReferenceInfo* pParent )
    {
      m_id = id;
      m_matrix = pParent->m_matrix;
      m_pParentCache = pParent->m_pParentCache;
      m_views = pParent->m_views;
      m_ownerId = pParent->m_ownerId;
      m_pDrawable = pParent->m_pDrawable;
    }
  };
  IndexedReferenceInfo* m_pCurrentReferenceInfo;
  OdArray< IndexedReferenceInfo > m_detectedInserts;
  struct IndexedBlockInfo
  {
    bool m_bInvalid;
    OdArray< IndexedReferenceInfo > m_refInfo;
    IndexedBlockInfo()
    {
      m_bInvalid = false;
    }
  };
  std::map< OdTvDbObjectId, IndexedBlockInfo > m_blockInfo;
  void addBlockInfo( const OdTvDbObjectId& id, const IndexedReferenceInfo& info );
  void markBlockInfoInvalid( const OdTvDbObjectId& id )
  {
    std::map< OdTvDbObjectId, IndexedBlockInfo >::iterator it = m_blockInfo.find( id );
    if( it != m_blockInfo.end() ) it->second.m_bInvalid = true;
  }
};


#include "TD_PackPop.h"

#endif //_ODTV_PARTIALVIEWING_H_INCLUDED_
