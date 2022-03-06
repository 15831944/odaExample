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

#ifndef _ODTV_DATABASERECEIVER_IMPL_H_INCLUDED_
#define _ODTV_DATABASERECEIVER_IMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvDatabaseReceiver.h"
#include "TvHostAppServices.h"
#include "TvCoreDatabaseSection.h"
#include "TvDatabaseImpl.h"
#include "TvFactoryImpl.h"
#include "TvGsDeviceImpl.h"

#define STL_USING_MAP
#include "OdaSTL.h"

class OdTvStatisticToolImpl : public OdTvDatabaseReceiver::StatisticTool
{
  OdUInt64 m_parsedObj;
  OdUInt64 m_parsedL;
  OdUInt64 m_unloadedObj;
  OdUInt64 m_unloadedL;
  bool m_bOnlyRequest;
public:
  OdTvStatisticToolImpl()
  {
    m_parsedObj = 0;
    m_parsedL = 0;
    m_unloadedObj = 0;
    m_unloadedL = 0;
    m_bOnlyRequest = true;
  }
  ~OdTvStatisticToolImpl() {}
  virtual OdUInt64 numParsedObjects() const { return m_parsedObj; }
  virtual OdUInt64 numUnloadedObjects() const { return m_unloadedObj; }
  virtual OdUInt64 lengthParsedObjects() const { return m_parsedL; }
  virtual OdUInt64 lengthUnloadedObjects() const { return m_unloadedL; }
  virtual bool isOnlyRequestedItems() const { return m_bOnlyRequest;  }
  virtual void setOnlyRequestedItems( bool b ) { m_bOnlyRequest = b; }
  virtual void reset()
  {
    m_parsedObj = 0;
    m_parsedL = 0;
    m_unloadedObj = 0;
    m_unloadedL = 0;
  }
  void objectParsed( OdUInt64 l )
  {
    m_parsedObj++;
    m_parsedL += l;
  }
  void addUnloadStatistic( OdUInt64 nObjects, OdUInt64 nLength )
  {
    m_unloadedObj += nObjects;
    m_unloadedL += nLength;
  }
};

class OdTvDatabaseReceiverImpl : public OdTvDatabaseReceiver
{
  friend class OdTvFactoryImpl;
  typedef std::set< OdTvDbObjectId > OdTvObjectIdSet;

  class OdTvDatabaseReceiverObjectsCollector : public OdTvVSFXObjectsCollector
  {
    OdTvDatabaseReceiverImpl* m_pReceiver;
    OdGsDevice* m_pDevice;
    OdUInt64 m_estimatedMemUsage;

    OdTvObjectIdSet m_delayedUnloadObjects;
  public:
    OdTvDatabaseReceiverObjectsCollector();
    ~OdTvDatabaseReceiverObjectsCollector();
    void initialize( OdTvDatabaseReceiverImpl* pReceiver );
    bool isInitialized( OdTvDatabaseReceiverImpl* pReceiver ) const { return m_pReceiver == pReceiver; }

    virtual bool beginCollection( OdGsDevice* pDevice = NULL );
    virtual bool endCollection( OdGsDevice* pDevice = NULL );
    virtual bool collectObject( OdUInt64 handle, OdUInt64 offset, OdUInt64 length );
    virtual bool collectionStarted( OdGsDevice* pDevice );
    virtual bool collectLoadedInsert( OdTvDbObjectId id );

    virtual bool collectUnloadingObjects( OdTvDbObjectIterator& unloadingList );
    virtual bool hasDelayedUnloadingObjects() const { return !m_delayedUnloadObjects.empty(); }
    virtual void removeDelayedObject( OdTvDbObjectId id );

    void doUnloadObject( OdTvDbObjectId id );
  };

  class OdTvDatabaseReceiverRequest
  {
    OdTvVSFXDatabase::OdTvVSFXContext* m_pContext;
    OdUInt64 m_secOffset;
    struct RequestRecord
    {
      OdVector< OdUInt64 >* m_pHandles;
      RequestRecord()
      {
        m_pHandles = NULL;
      }

      ~RequestRecord()
      {
        if( m_pHandles )
        {
          m_pHandles->clear();
          delete m_pHandles;
          m_pHandles = NULL;
        }
      }

      void add( OdUInt64 handle )
      {
        if( !m_pHandles ) m_pHandles = new OdVector< OdUInt64 >;
        m_pHandles->push_back( handle );
      }
    };
    OdUInt32 m_id;
    OdVector< RequestRecord* > m_handleRecords;
    OdVector< OdTvDatabaseReceiverReactor::OdTvRequestRecord > m_records;
    OdVector< OdUInt32 > m_lastPages;
    std::set< OdUInt64 > m_collectedHandles;
    struct RegisteredPage
    {
      OdUInt32 nPage;
      OdUInt32 nRecord;

      RegisteredPage( OdUInt32 nP, OdUInt32 nRec ) : nPage( nP ), nRecord( nRec )
      {

      }

      bool operator < ( const RegisteredPage& reg ) const
      {
        return nPage < reg.nPage;
      }
    };

    std::set< RegisteredPage > m_registeredPages;
#ifdef _DEBUG
  public:
    OdUInt32 m_totalRequests;
    OdUInt32 m_combinedSinglePages;
    OdUInt32 m_extendedRecords;
    OdUInt32 m_rejectedObjects;
#endif
    //parsing
    OdUInt32 m_curParsingRec;
    OdUInt64 m_curParsingOffset;
    //additional
    OdGsDevice* m_pDevice;
    //sub-request
    OdTvDatabaseReceiverRequest* m_pSubRequest;
    OdUInt32 m_nRecordsLimit;
  public:
    OdTvDatabaseReceiverRequest( OdUInt32 id, OdTvVSFXDatabase::OdTvVSFXContext* pContext, OdUInt32 nRecordsLimit );
    ~OdTvDatabaseReceiverRequest();

    bool addRequestItem( OdUInt64 handle, OdUInt64 offset, OdUInt64 length );

    OdUInt32 id() const { return m_id; }
    OdUInt32 numRecords() const { return m_records.size(); }
    const OdTvDatabaseReceiverReactor::OdTvRequestRecord* records() const { return m_records.asArrayPtr(); }

    bool isParsed() const
    {
      return m_curParsingRec == m_records.size();
    }

    bool collectRecordObjects( std::map< OdUInt64, OdUInt64 >& handles );

    const OdTvDatabaseReceiverReactor::OdTvRequestRecord& currentParsingRecord() const { return m_records[ m_curParsingRec ]; }
    void nextParsingRecord() 
    {
      if( isParsed() ) return;
      m_curParsingRec++;
    }
    OdUInt64 nextParsingRecordIndex() const { return m_curParsingRec; }
    OdUInt64 currentParsingOffset() const { return m_curParsingOffset; }
    void setCurrentParsingOffset( OdUInt64 off ) { m_curParsingOffset = off; }

    OdGsDevice* device() { return m_pDevice; }
    OdGsDevice* device() const { return m_pDevice; }
    void setDevice( OdGsDevice* pDev ) { m_pDevice = pDev; }

    OdTvDatabaseReceiverRequest* createSubRequest();
    void removeSubRequest();
    OdTvDatabaseReceiverRequest* subRequest();
    const OdTvDatabaseReceiverRequest* subRequest() const;
    OdUInt32 lastUsedId() const;

    void setRecordsLimit( OdUInt32 nLimit );
    OdUInt32 recordsLimit() const;

  protected:
    inline OdUInt64 sectionOffset() const { return m_secOffset; }
    inline OdUInt32 getPageNumber( OdUInt64 offset ) const { return (OdUInt32)( offset / pageSize() ); }
    inline OdUInt64 pageSize() const { return m_pContext->m_pagingOptions.pageSize; }
    inline OdUInt64 pageRealOffset( OdUInt32 nPage ) const;
    inline OdUInt64 pageRealOffsetByObjectOffset( OdUInt64 offset ) const;

    enum PagesCompatibility
    {
      /* Pages are incompatible */
      kIncompatible,
      /* New page are the same as last processed page */
      kCompatible_Same,
      /* New page are the same as end page */
      kCompatible_Next
    };
    inline PagesCompatibility isCompatibleLast( OdUInt32 nPage ) const;
    bool addToLast( PagesCompatibility comp, OdUInt32 nPageBegin, OdUInt32 nPageEnd, OdUInt64 handle );
    void registerPages( OdUInt32 nPageBegin, OdUInt32 nPageEnd, OdUInt32 nRecord );

    inline bool isConsistent() const
    {
#ifdef _DEBUG
      OdUInt32 sz = m_records.size();
      if( sz != m_handleRecords.size() ) return false;
      if( sz != m_lastPages.size() ) return false;
#endif
      return true;
    }
  };

public:
  OdTvDatabaseReceiverImpl();
  virtual ~OdTvDatabaseReceiverImpl();

  virtual OdTvDatabaseReceiver::DatabaseReceivingState state() const { return m_state; }
  virtual OdTvDatabaseId database() const { return m_databaseId; };
  virtual bool doReceive( const OdUInt8* pData, OdUInt32 nSize, OdTvResult* rc = NULL );
  virtual void reset();

  virtual OdUInt64 numExpectedObjects() const { return m_nNumExpectedObjects; }
  virtual OdUInt64 numReceivedObjects() const { return m_nNumReceivedObjects; }

  virtual bool isStreamingFriendlySource() const { return m_bIsStreamingFriendly; }
  virtual bool isDatabaseRenderable() const;

  virtual void enablePartialMode( bool bEnable, OdTvDatabaseReceiverReactor* pReactor );
  virtual bool isPartialMode() const;
  virtual OdTvDatabaseReceiverReactor* partialModeReactor() const;

  virtual bool doReceiveResponse( OdUInt32 requestID, const OdUInt8* pData, OdUInt32 nSize, OdTvResult* rc = NULL );

  void requestMissingObjects();

protected:
  OdTvDatabaseReceiver::DatabaseReceivingState m_state;
  OdTvDatabaseId m_databaseId;
  enum DatabaseReceivingStatus
  {
    kDRC_Nothing = 0,
    kDRC_Header = 1,
    kDRC_Sections = 1 << 1,
    kDRC_PageMap = 1 << 2,
    kDRC_HandlesMap = 1 << 3,
    kDRC_ClassMap =  1 << 4,
    kDRC_Database = 1 << 5,
    kDRC_Objects = 1 << 6,
    kDRC_RequestMode = 1 << 7
  };

  OdUInt8 m_receivingStatus;

  void setReceivingStatus( DatabaseReceivingStatus status ) { SETBIT_1( m_receivingStatus, status ); }
  bool receivingStatus( DatabaseReceivingStatus status ) { return GETBIT( m_receivingStatus, status ); }

  bool isSectionReceived( OdTvCoreDatabaseSection::DatabaseSection section );
  void setSectionReceived( OdTvCoreDatabaseSection::DatabaseSection section );

  OdBinaryData m_memoryStream;
  const OdUInt8* m_pReceivedData;
  OdUInt32 m_nReceivedSize;
  OdUInt64 m_memoryStartOffset;

  bool createNewStreamingDatabase();

  std::map< OdUInt64, OdTvCoreDatabaseSection::DatabaseSection > m_emptySections;

  bool parseServiceSection( OdTvCoreDatabaseSection* pSection, OdStreamBufPtr pStream, OdTvDatabaseImpl* pTvDbImpl );

  OdUInt64 m_nNumExpectedObjects;
  OdUInt64 m_nNumReceivedObjects;

  std::map< OdUInt64, OdUInt64 > m_emptyObjects;
  std::set< OdUInt64 > m_dependencySet;
  bool parseObject( OdUInt64 handle, const OdTvVSFXHandleTreeItem& item, OdTvCoreDatabaseSection* pSection, OdTvCoreFilerWrapperPtr pPagedFiler, OdTvCorePageAccessorPtr pAcc, OdTvDatabaseImpl* pTvDbImpl );

  bool m_bDBInitialized;
  bool m_bIsStreamingFriendly;
  OdUInt64 m_lastServiceHandle;
  bool m_bHasPartialIndex;
  mutable bool m_bRenderAble;

  OdTvDatabaseReceiverReactor* m_pReactor;
  bool m_bPartialMode;
  OdTvDatabaseReceiverObjectsCollector m_objectsCollector;
  void initCollector( OdTvDatabaseImpl* pTvDbImpl );
  void uninitCollector( OdTvDatabaseImpl* pTvDbImpl );
  typedef std::map< OdGsDevice*, OdTvDatabaseReceiverRequest* > OdTvRequestMap;
  typedef std::set< OdUInt64 > OdTvHandlesSet;
  OdTvRequestMap m_pRequests;
  OdUInt32 m_nRequestCounter;
  class OdTvNextPassObjects
  {
  public:
    OdTvNextPassObjects() { m_bUseFirstSet = true; m_bUseFirstHandles = true; }
    ~OdTvNextPassObjects() {}

    void clear();
    void nextPassForInsert( OdTvDbObjectId id );
    void nextPassForHandle( OdUInt64 h );
    void generateNextPassRequest( OdTvDatabaseImpl* pTvDbImpl, OdTvDatabaseReceiverImpl* pReceiver, OdGsDevice* pDevice );
    bool empty() const { return handlesSet().empty() && insertsSet().empty(); }
  protected:
    bool m_bUseFirstSet;
    bool m_bUseFirstHandles;
    inline OdTvObjectIdSet& insertsSet()
    {
      if( m_bUseFirstSet ) return m_firstSet;
      return m_secondSet;
    }
    inline const OdTvObjectIdSet& insertsSet() const
    {
      if( m_bUseFirstSet ) return m_firstSet;
      return m_secondSet;
    }
    inline void switchSet()
    {
      m_bUseFirstSet = !m_bUseFirstSet;
      insertsSet().clear();
    }
    inline OdTvObjectIdSet& secondSet()
    {
      if( m_bUseFirstSet ) return m_secondSet;
      return m_firstSet;
    }
    inline const OdTvObjectIdSet& secondSet() const
    {
      if( m_bUseFirstSet ) return m_secondSet;
      return m_firstSet;
    }

    inline OdTvHandlesSet& handlesSet()
    {
      if( m_bUseFirstHandles ) return m_priorityItemsFirst;
      return m_priorityItemsSecond;
    }
    inline const OdTvHandlesSet& handlesSet() const
    {
      if( m_bUseFirstHandles ) return m_priorityItemsFirst;
      return m_priorityItemsSecond;
    }
    inline void switchHandlesSet()
    {
      m_bUseFirstHandles = !m_bUseFirstHandles;
      handlesSet().clear();
    }
    inline OdTvHandlesSet& secondHandlesSet()
    {
      if( m_bUseFirstHandles ) return m_priorityItemsSecond;
      return m_priorityItemsFirst;
    }
    inline const OdTvHandlesSet& secondHandlesSet() const
    {
      if( m_bUseFirstHandles ) return m_priorityItemsSecond;
      return m_priorityItemsFirst;
    }

    OdTvObjectIdSet m_firstSet;
    OdTvObjectIdSet m_secondSet;
    OdTvHandlesSet m_priorityItemsFirst;
    OdTvHandlesSet m_priorityItemsSecond;
  };
  OdTvNextPassObjects m_nextPassObjects;

public:
  OdTvDatabaseReceiverRequest* createRequest( OdGsDevice* pDevice, OdUInt32 id, OdTvVSFXDatabase::OdTvVSFXContext* pContext )
  {
    OdTvRequestMap::iterator it = m_pRequests.find( pDevice );
    if( it == m_pRequests.end() )
    {
      OdTvDatabaseReceiverRequest* pReq = new OdTvDatabaseReceiverRequest( id, pContext, managementOptions().requestRecordsLimit() );
      pReq->setDevice( pDevice );
      m_pRequests[ pDevice ] = pReq;
      return pReq;
    }
    ODA_FAIL();
    return it->second;
  }
  void deleteRequest( OdGsDevice* pDevice, bool bDeleteSubRequests = false )
  {
    OdTvRequestMap::iterator it = m_pRequests.find( pDevice );
    if( it != m_pRequests.end() )
    {
      if( bDeleteSubRequests )
      {
        it->second->removeSubRequest();
      }
      delete it->second;
      m_pRequests.erase( it );
    }
  }
  void switchToSubRequest( OdTvDatabaseReceiverRequest* pCurRequest );

  OdTvDatabaseReceiverRequest* activeRequest( OdGsDevice* pDevice ) 
  { 
    OdTvRequestMap::iterator it = m_pRequests.find( pDevice );
    if( it != m_pRequests.end() )
    {
      return it->second;
    }
    return NULL;
  }
  const OdTvDatabaseReceiverRequest* activeRequest( OdGsDevice* pDevice ) const
  {
    OdTvRequestMap::const_iterator it = m_pRequests.find( pDevice );
    if( it != m_pRequests.end() )
    {
      return it->second;
    }
    return NULL;
  }

  OdTvDatabaseReceiverRequest* requestById( OdUInt32 ID )
  {
    for( OdTvRequestMap::iterator it = m_pRequests.begin(); it != m_pRequests.end(); ++it )
    {
      if( it->second->id() == ID ) return it->second;
    }
    return NULL;
  }

protected:
  OdTvDatabaseReceiverManagementOptions m_managementOptions;
  OdTvStatisticToolImpl m_statisticTool;
public:
  virtual void setManagementOptions( const OdTvDatabaseReceiverManagementOptions& options ) 
  { 
    m_managementOptions = options;
    m_statisticTool.setOnlyRequestedItems( options.isStatisticOnlyRequestItems() );
  }
  virtual const OdTvDatabaseReceiverManagementOptions& managementOptions() const { return m_managementOptions; }
  virtual OdTvDatabaseReceiverManagementOptions& managementOptions() { return m_managementOptions; }

  virtual const OdTvDatabaseReceiver::StatisticTool* statisticTool() const
  { 
    if( m_managementOptions.enableStatistic() ) return &m_statisticTool;
    return NULL;
  }

  virtual OdTvDatabaseReceiver::StatisticTool* statisticTool()
  {
    if( m_managementOptions.enableStatistic() ) return &m_statisticTool;
    return NULL;
  }

protected:
  OdTvDbDatabase* internalDB();
  OdUInt64 findObjectLength( OdUInt64 handle ) const;
  void addUnloadObjectsStatistic( OdUInt64 nObjects, OdUInt64 nLength );

  OdTvTimedSchedulerPtr m_pScheduler;
public:
  OdTvTimedScheduler* getScheduler() { return m_pScheduler.get(); }
  //OdTvIObject implementation
public:
  virtual void addRef() { ++m_nRefCounter; }
  virtual void release()
  {
    if( m_nRefCounter == 1 )
    {
      delete this;
    }
    else
      --m_nRefCounter;
  }
  virtual long numRefs() const { return m_nRefCounter; }
protected:
  unsigned int                m_nRefCounter;
};



#endif //_ODTV_DATABASERECEIVER_IMPL_H_INCLUDED_
