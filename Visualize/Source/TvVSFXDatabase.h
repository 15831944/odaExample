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


#ifndef _ODTV_VSFXDATABASE_H_INCLUDED_
#define _ODTV_VSFXDATABASE_H_INCLUDED_

#include "TD_PackPush.h"

#define STL_USING_MAP
#define STL_USING_SET
#include "OdaSTL.h"

#include "TvFilerWrapper.h"
#include "../../TvCore/Include/TvCoreDatabaseSection.h"

#include "TvDatabase.h"
//VIS-2348: not a good time for C++11
#define NO_CPP_11 1
#ifndef NO_CPP_11
#include <tuple>  
#endif

class OdTvBinaryBufferAllocator;
class OdTvBinaryDataBufferImpl
{
  friend class OdTvBinaryBufferAllocator;
public:
  OdTvBinaryDataBufferImpl() { m_pNext = NULL; }
  ~OdTvBinaryDataBufferImpl() { m_buffer.clear(); m_pNext = NULL; }
  OdVector< OdUInt8 >& buffer() { return m_buffer; }
  const OdVector< OdUInt8 >& buffer() const { return m_buffer; }
protected:
  OdVector< OdUInt8 > m_buffer;
  OdTvBinaryDataBufferImpl* m_pNext;
};

class OdTvBinaryBufferAllocator
{
public:
  OdTvBinaryBufferAllocator( OdUInt32 nPreAllocated = 16 );
  ~OdTvBinaryBufferAllocator();

  OdTvBinaryDataBufferImpl* allocate();
  void release( OdTvBinaryDataBufferImpl* );

  void clear();
protected:
  OdMutexPtr m_mutex;
  OdTvBinaryDataBufferImpl* m_pQueue;
  void push( OdTvBinaryDataBufferImpl* pBuffer );
  OdTvBinaryDataBufferImpl* pop();
};

class OdTvBinaryBuffer
{
public:
  OdTvBinaryBuffer( OdTvBinaryBufferAllocator*, OdUInt32 nSize = 0 );
  ~OdTvBinaryBuffer();
  OdVector< OdUInt8 >& buffer() { return m_pBuffer->buffer(); }
  const OdVector< OdUInt8 >& buffer() const { return m_pBuffer->buffer(); }
protected:
  OdTvBinaryBufferAllocator* m_pAllocator;
  OdTvBinaryDataBufferImpl* m_pBuffer;
};

class OdTvVSFXFilerDef
{
  friend class OdTvVSFXFilerAllocator;
public:
  OdTvVSFXFilerDef() { m_pNext = NULL; }
  ~OdTvVSFXFilerDef() { m_pNext = NULL; m_pFiler = NULL; }
  void init( OdTvCorePageAccessorPtr pAccessor, const OdTvCorePagingOptions& options, OdStreamBufPtr pBuffer, OdTvDbDatabase* pDb );
  OdTvCoreFilerWrapper* filer() { return m_pFiler.get(); }
protected:
  OdTvCoreFilerWrapperPtr m_pFiler;
  OdTvVSFXFilerDef* m_pNext;
};

class OdTvVSFXFilerAllocator
{
public:
  OdTvVSFXFilerAllocator();
  ~OdTvVSFXFilerAllocator();
  void reset();
  void init( OdUInt32 nFilers, OdTvCorePageAccessorPtr pAccessor, const OdTvCorePagingOptions& options, OdStreamBufPtr pBuffer, OdTvDbDatabase* pDb );

  OdTvVSFXFilerDef* allocate();
  void release( OdTvVSFXFilerDef* );

  OdTvVSFXFilerDef* allocate( int index );
  void releaseForIndex( int index );
protected:
  OdTvVSFXFilerDef* m_pHead;
  OdMutexPtr m_pMutex;
  std::map< int, OdTvVSFXFilerDef* > m_indexedFilers;
};


struct OdTvVSFXHandleTreeItem
{
  OdUInt64 offset;
  OdUInt64 length;
  OdTvVSFXHandleTreeItem()
  {
    offset = 0;
    length = 0;
  }
  OdTvVSFXHandleTreeItem( OdUInt64 o, OdUInt64 l )
  {
    offset = o;
    length = l;
  }
};

typedef std::map< OdUInt64, OdTvVSFXHandleTreeItem > OdTvVSFXHandleMap;


class OdDbDatabaseTv;
class OdTvDbDatabaseImpl;

#ifdef NO_CPP_11
class OdTvInternalDatabase
{
  OdDbDatabaseTv* m_pDb;
  OdTvDbDatabaseImpl* m_pDbImpl;
public:
  OdTvInternalDatabase( OdDbDatabaseTv* pDb, OdTvDbDatabaseImpl* pDbImpl ) : m_pDb( pDb ), m_pDbImpl( pDbImpl )
  {
  }
  OdDbDatabaseTv* database() const { return m_pDb; }
  OdTvDbDatabaseImpl* databaseImpl() const { return m_pDbImpl; }
};
#else
typedef std::tuple< OdDbDatabaseTv*, OdTvDbDatabaseImpl* > OdTvInternalDatabase;
#endif
class OdTvDatabaseReceiverImpl;

class OdTvVSFXObjectsCollector
{
public:
  virtual bool beginCollection( OdGsDevice* pDevice = NULL ) = 0;
  virtual bool endCollection( OdGsDevice* pDevice = NULL ) = 0;
  virtual bool collectObject( OdUInt64 handle, OdUInt64 offset, OdUInt64 length ) = 0;
  virtual bool collectionStarted( OdGsDevice* pDevice = NULL ) = 0;
  virtual bool collectLoadedInsert( OdTvDbObjectId id ) = 0;

  virtual bool collectUnloadingObjects( OdTvDbObjectIterator& unloadingList ) { return false; }
  virtual bool hasDelayedUnloadingObjects() const { return false; }
  virtual void removeDelayedObject( OdTvDbObjectId id ) {};
};

class OdTvDbEmptyObjectIterator : public OdTvDbObjectIterator
{
public:
  OdTvDbEmptyObjectIterator() : OdTvDbObjectIterator()
  {
  }

  virtual void start(
    bool atBeginning = true,
    bool skipErased = true )
  {
  }

  virtual bool done() const
  {
    return true;
  }

  virtual OdTvDbObjectId objectId() const
  {
    return OdTvDbObjectId();
  }

  virtual OdTvDbEntityPtr entity(
    OdDb::OpenMode openMode = OdDb::kForRead,
    bool openErasedEntity = false )
  {
    return OdTvDbEntityPtr();
  }

  virtual void step(
    bool forward = true,
    bool skipErased = true )
  {
  }

  virtual bool seek(
    OdTvDbObjectId objectId )
  {
    return false;
  }

  virtual bool seek(
    const OdTvDbEntity* pEntity )
  {
    return false;
  }

  virtual void addRef()
  {}

  virtual void release()
  {}
};

class OdTvVSFXDatabase
{
  friend class OdTvDatabaseReceiverImpl;
public:
  virtual void* getInternalDatabase( OdTvResult* rc = NULL ) const = 0;

  struct OdTvVSFXContext
  {
    OdStreamBufPtr m_pStream;
    OdTvCoreDatabaseSectionMap m_sectionMap;
    OdTvVSFXHandleMap m_vsfxHandlesMap;
    OdTvCoreFilerWrapperPtr m_pObjectsFiler;
    OdTvCoreFilerPtr m_pHeaderFiler;
    OdTvCorePageMap m_pageMap;
    OdTvCorePagingOptions m_pagingOptions;
    OdString m_readedFileName;
    OdTvVSFXReadOptions m_readOptions;

    OdTvVSFXContext()
    {
      m_pStream = NULL;
      m_pObjectsFiler = NULL;
      m_pHeaderFiler = NULL;
      m_readedFileName = OdString::kEmpty;
    }

    ~OdTvVSFXContext()
    {
      reset();
    }

    void reset()
    {
      m_pStream = NULL;
      m_pObjectsFiler = NULL;
      m_pHeaderFiler = NULL;
      m_vsfxHandlesMap.clear();
      m_pageMap.reset();
      m_pagingOptions.pPageMap = NULL;
      m_sectionMap.reset();
      m_readOptions = OdTvVSFXReadOptions();
    }
  };

  OdTvVSFXDatabase();
  virtual ~OdTvVSFXDatabase();

  //VSFX methods

  bool isVSFXDatabase() const { return GETBIT( m_vsfxFlags, kIsVSFX ); }
  void setIsVSFXDatabase( bool bIsVSFX ) { SETBIT( m_vsfxFlags, kIsVSFX, bIsVSFX );  }
  static bool isVSFXSupportedVersion( OdUInt16 );

  static void initPagingOptions( OdTvVSFXContext* ctx )
  {
    ctx->m_pagingOptions.compression = OdTvCorePagingOptions::kZLIBCompression;
    ctx->m_pagingOptions.pageSize = 64 * 1024;
    ctx->m_pagingOptions.pPageMap = &ctx->m_pageMap;
  }

  OdTvResult writeVSFX( const OdString& filename, const OdTvVSFExportOptions* pOptions = NULL );
  OdTvResult writeVSFX( OdStreamBufPtr pStream, const OdTvVSFExportOptions* pOptions = NULL );
  OdTvResult readVSFX( const OdString& filename, bool bMtMode, bool bPartialMode, const OdTvVSFXReadOptions& options = OdTvVSFXReadOptions() );
  OdTvResult readVSFX( OdStreamBufPtr pStream, bool bMtMode, bool bPartialMode, const OdTvVSFXReadOptions& options = OdTvVSFXReadOptions() );

  void vsfxBeginPartialImport( OdStreamBufPtr pStream );
  void vsfxEndPartialImport();
  void vsfxWriteObjectPartial( OdTvDbObjectId id, bool pageObjectToDisk = true );

  void loadObjectsVSFX( OdTvDbObjectIterator* pObjects, OdMTLoadReactor* pReactor = 0, OdUInt32 delay = 0, OdGsDevice* pDevice = NULL );

  //Streaming methods
  static bool isStreamingCompatible( OdStreamBuf* pStream );
  static bool isHasPartialIndex( OdStreamBuf* pStream, OdTvResult* pRes );
  static bool isStreamingFriendly( OdStreamBuf* pStream );
  static OdUInt8 collectStreamingFlags( OdStreamBuf* pStream );
  static bool makeStreamingCompatible( OdStreamBuf* pInput, OdStreamBuf* pOutput, OdUInt32 nMaxBufferSize = 10 * 1024 * 1024 );

  static OdUInt32 VSFX_headerSize();
  static OdUInt32 VSFX_sectionMapItemSize();

protected:
  void writeVSFXObject( OdTvDbObjectId objectId, OdTvCoreFilerWrapperPtr pFiler );
  void loadVSFXMT( OdUInt32 nThreads );
  virtual OdApcAtomPtr beginMTLoading( int threadsCount );

protected:

  OdTvInternalDatabase castInternalDatabase() const;

  OdTvVSFXContext m_context;
  OdTvBinaryBufferAllocator m_binBufAlloc;
  enum VSFXFlag
  {
    kIsVSFX = 1,
    kForcePartialUnloading = 2
  };

  enum VSFXHeaderFlags
  {
    kVSFX_StreamingFriendly = 1 << 0
  };

  enum VSFXStreamingFlags
  {
    kVSFXStreaming_hasPI = 1 << 0
  };

  OdUInt8 m_vsfxFlags;
  OdTvVSFXFilerAllocator m_filerAlloc;
  OdTvVSFXContext* m_pPIContext;

  OdTvBinaryBufferAllocator* binaryBufferAllocator() { return &m_binBufAlloc; }

  //Read-write helpers
  static OdUInt16 readVSFXHeader( OdTvCoreFilerPtr pHeaderFiler, OdTvVSFXContext* ctx, OdUInt32* pHeaderFlags = NULL );
  static void writeVSFXHeader( OdUInt16 version, OdTvCoreFilerPtr pHeaderFiler, OdTvVSFXContext* ctx, OdUInt32 headerFlags = 0 );

  static void readVSFXSectionMap( OdTvCoreFilerPtr pHeaderFiler, OdTvVSFXContext* ctx );
  static void writeVSFXSectionMap( OdTvCoreFilerPtr pHeaderFiler, OdTvVSFXContext* ctx );

  static void readVSFXHandlesMap( OdTvCoreFilerPtr pHandlesTreeFiler, OdTvVSFXContext* ctx, OdDbDatabaseTv* pDatabase, bool bSetLeftOnDisk = false );
  static void writeVSFXHandlesMap( OdTvCoreFilerPtr pHandlesTreeFiler, OdTvVSFXContext* ctx );

  static void readVSFXPageMap( OdTvCoreFilerPtr pPagedFiler, OdTvVSFXContext* ctx );
  static void writeVSFXPageMap( OdTvCoreFilerPtr pPageMapFiler, OdTvVSFXContext* ctx );

  OdTvVSFXContext* vsfxContext() { return &m_context; }

  void vsfxReadClassMap( OdTvCoreFilerWrapperPtr pPagedClassesFiler, OdDbDatabaseTv* pDatabase );
  void vsfxReadInternalDatabase( OdTvCoreFilerWrapperPtr pPagedClassesFiler, OdDbDatabaseTv* pDatabase );

  bool vsfxReadObject( OdTvCoreFilerWrapperPtr pFiler, OdUInt64 handle, const OdTvVSFXHandleTreeItem& item );

  virtual OdUInt64 vsfxWriteServiceObjects( OdTvCoreFilerWrapperPtr pFiler, OdTvVSFXContext* ctx ) { return 0; }

public:
  void addStreamingDependency( OdTvDbObjectId objectId, OdUInt64 dependOn );
  void resolveStreamingDependency( OdUInt64 handle, bool bDepth = true );
  void delayDependencyResolution( OdUInt64 handle, std::set< OdUInt64 >& delayedSet );
  void resolveDelayedStreamingDependencies( const std::set< OdUInt64 >& delayedSet );
  void clearStreamingDependencies();
  static OdUInt64 getHandleOfParentBlock( OdTvDbObjectId& id );

protected:
  std::map< OdUInt64, std::set< OdTvDbObjectId >* > m_streamingDependencies;

  OdVector< OdTvGeometryDataId > m_partialGeometries;

  OdTvCoreFilerPtr m_pTemporaryReadFiler;

public:
  void registerPartialGeometry( OdTvGeometryDataId id ) 
  { 
    m_partialGeometries.push_back( id ); 
  }
  void loadAllPartial();
  const OdTvVSFXReadOptions& vsfxReadOptions() const { return m_context.m_readOptions; }

  struct OdTvVSFXSectionFilerDef
  {
    OdStreamBufPtr m_pStream;
    OdTvCoreFilerWrapperPtr m_pFiler;
    OdUInt64 m_sectionStart;

    OdTvVSFXSectionFilerDef()
    {
      m_pStream = NULL;
      m_pFiler = NULL;
      m_sectionStart = 0;
    }

    ~OdTvVSFXSectionFilerDef()
    {
      m_pStream = NULL;
      m_pFiler = NULL;
      m_sectionStart = 0;
    }
  };

  OdTvVSFXSectionFilerDef requestObjectSectionFiler();
  OdUInt64 requestObjectSectionOffset( OdDbHandle handle );

protected:
  OdTvVSFXObjectsCollector* m_pCollector;
public:
  OdTvVSFXObjectsCollector* objectsCollector() const { return m_pCollector; }
  void setObjectsCollector( OdTvVSFXObjectsCollector* pCollector ) { m_pCollector = pCollector; }
  virtual void disablePartialViewingModule() = 0;
  virtual bool forcePartialViewingRequest( OdGsDevice* pDevice, const std::set< OdTvDbObjectId >& detectedInserts ) = 0;

  virtual bool isForcePartialObjectsUnloading() const { return GETBIT( m_vsfxFlags, kForcePartialUnloading ); }
  virtual void setForcePartialObjectsUnloading( bool bUnload ) { SETBIT( m_vsfxFlags, kForcePartialUnloading, bUnload ); }

  virtual void processDelayedTasks();
};

#include "TD_PackPop.h"

#endif // _ODTV_VSFXDATABASE_H_INCLUDED_

