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

// DwgFileController.h: interface for the OdTvDwgFileLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ODDWGFILELOADER_H_INCLUDED_)
#define _ODDWGFILELOADER_H_INCLUDED_

#include "DwgInController.h"

class OdTvDwgFileStream;
class OdTvDwgFileSplitStream;

template <class T>
class ObjectPool
{
  OdArray<T*> m_Objects;
  OdUInt32    m_UsedObjects;
public:
  ObjectPool() : m_UsedObjects(0) {}
  ~ObjectPool() 
  {
    for (unsigned i=0; i<m_Objects.size(); ++i)
    {
      delete m_Objects[i];
    }
  }

  T* getObject()
  {
    if (m_UsedObjects >= m_Objects.size())
    {
      ODA_ASSERT(m_UsedObjects == m_Objects.size());
      m_Objects.resize(m_UsedObjects+1);
      m_Objects.last() = new T;
    }
    return m_Objects[m_UsedObjects++];
  }

  void releaseObject()
  {
    m_UsedObjects--;
  }
};

class DBIO_EXPORT OdTvDwgFileLoader : public OdTvDwgInController
{
public:
  ODRX_DECLARE_MEMBERS(OdTvDwgFileLoader);
  OdTvDwgFileLoader();
  ~OdTvDwgFileLoader();

  virtual void getVbaProjectData(OdUInt32 size, OdBinaryData& binaryData);

  // DbFilerController overridden
  void startDbLoading(OdTvDbDatabase* pLoadedDb, OdDbHostAppProgressMeter* pProgressMeter);
  void endDbLoading();
  OdTvDbDatabasePtr loadDbHeader(OdTvDbHostAppServices*);

  virtual void verifyExistingSignature(OdCryptoServices::OdSignatureVerificationResult& verificationResult, 
    OdSignatureDescription& signatureDesc);
  virtual OdTvDbDate getStreamModTimeFromSummary();

protected:
  // Load all data except database objects

  virtual void loadFileHeader();

  // Load R15 system data

  void loadMetadata();

  // Load data sections present in dwg files of version >=R13 
  
  virtual void loadHeader();
  virtual void loadClasses();
  void loadHeader(OdTvDwgFileSplitStream& dwgStream);
  void loadClasses(OdTvDwgFileStream& dwgStream);
  void loadHandles();
  void loadAuxHeader();
  virtual void loadObjFreeSpace();
  void loadTemplate();

  // Load data sections present in dwg files of version >=R18 

  void loadFileDepList();
  void loadSummaryInfo();

  // DbFilerController overridden 

  OdTvDbObjectPtr loadObject(OdUInt64 offset);

  // Load object implementation

  OdTvDbObjectPtr loadObject(OdTvDwgFileSplitStream& dwgStream, OdUInt64 offset);
  OdResult loadObjectData(OdTvDwgFileSplitStream& dwgStream, OdTvDbObjectPtr& pObj);

private:
  inline OdResult loadObjectDwgData(OdTvDwgFileSplitStream& dwgStream, OdTvDbObject* pObj);
protected:
  ObjectPool<OdBinaryData> m_loadObjects;

// ODA_MT_DBIO_BEGIN
public:
  enum { kMaxIdsBlockSize = 100 };
  class MTContext
  {
  public:
    MTContext() : m_blockSize(kMaxIdsBlockSize), m_nUnrecoverableErrors(0){}
    virtual ~MTContext() {}
    OdArray<ObjectPool<OdBinaryData> > m_objectPools;
    OdArray<OdStreamBufPtr> m_rawStreams;
    int m_blockSize;
    OdRefCounter m_nUnrecoverableErrors;
  };
  MTContext* getMTContext() { return m_pMTContext; }
protected:
  MTContext* m_pMTContext;

  OdResult loadObject(OdTvDbObjectPtr& pObj, const OdRxObject* pMTResolver, int threadId); // DbFilerController overridden
  virtual OdResult loadObject(OdTvDwgFileSplitStream& dwgStream, OdTvDbObjectPtr& pObj, const OdRxObject* pMTResolver, int threadId);

  TD_USING(OdTvDwgInController::getStreamBuf);
  inline OdStreamBuf* getStreamBuf(int threadId) { ODA_ASSERT(m_pMTContext); return m_pMTContext->m_rawStreams[threadId]; }

  virtual OdApcAtomPtr beginMTLoading(int threadsCount, OdTvDbObjectIterator* pObjs = 0, OdMTLoadReactor* pInterruptFlag = 0) ODRX_OVERRIDE;
  void endMTLoading();
// ODA_MT_DBIO_END
};


class TOOLKIT_EXPORT OdTvObjLoadResolver : public OdRxObject
{
  OdTvObjLoadResolver& operator = (const OdTvObjLoadResolver&);
protected:
  OdTvDbObjectId  m_id;
  OdUInt32      m_offset;
public:
  void init(const OdTvDbObjectId& id, OdUInt32 offset) {
    m_id = id;
    m_offset = offset;
  }
  static OdRxObjectPtr createObject(const OdTvDbObjectId& id, OdUInt32 offset)
  {
    OdSmartPtr<OdRxObjectImpl<OdTvObjLoadResolver> > res = OdRxObjectImpl<OdTvObjLoadResolver>::createObject();
    res->init(id, offset);
    return res;
  }
  virtual OdRxObject* queryX(const OdRxClass* pClass) const ODRX_OVERRIDE;

  OdUInt32 offset() { return m_offset; }
};

class OdTvObjUnloadResolver : public OdTvObjLoadResolver
{
protected:
  OdGsCache* m_pGsNode;
  void init(const OdTvDbObjectId& id, OdUInt32 offset, OdGsCache* pGsNode) {
    OdTvObjLoadResolver::init(id, offset);
    m_pGsNode = pGsNode;
  }
public:
  static OdRxObjectPtr createObject(const OdTvDbObjectId& id, OdUInt32 offset, OdGsCache* pGsNode)
  {
    OdSmartPtr<OdRxObjectImpl<OdTvObjUnloadResolver> > res = OdRxObjectImpl<OdTvObjUnloadResolver>::createObject();
    res->init(id, offset, pGsNode);
    return res;
  }
  OdRxObject* queryX(const OdRxClass* pClass) const;
};

class OdTvObjUnloadResolverEx : public OdTvObjUnloadResolver
{
protected:
  OdGsView* m_pGsView;
public:
  void init(const OdTvDbObjectId& id, OdUInt32 offset, OdGsCache* pGsNode, OdGsView* pGsView) {
    OdTvObjUnloadResolver::init(id, offset, pGsNode);
    m_pGsView = pGsView;
  }
  static OdRxObjectPtr createObject(const OdTvDbObjectId& id, OdUInt32 offset, OdGsCache* pGsNode, OdGsView* pGsView)
  {
    OdSmartPtr<OdTvObjUnloadResolverEx> res = OdRxObjectImpl<OdTvObjUnloadResolverEx>::createObject();
    res->init(id, offset, pGsNode, pGsView);
    return res;
  }
  OdRxObject* queryX(const OdRxClass* pClass) const;
};

// ODA_MT_DBIO_BEGIN
class TOOLKIT_EXPORT OdTvObjMTLoadResolver : public OdTvObjLoadResolver
{
public:
  OdTvObjMTLoadResolver()
    : m_isPreloaded(false)
    , m_dwgType(0)
    , m_totalObjSize(0)
    , m_totalIdsBitSize(0)
    , m_rawOffset(0)
    , m_crc(0)
    , m_lengthOfSizeInfo(0)
  {}
  static OdRxObjectPtr createObject(const OdTvDbObjectId& id, OdUInt32 offset)
  {
    OdSmartPtr<OdRxObjectImpl<OdTvObjMTLoadResolver> > res = OdRxObjectImpl<OdTvObjMTLoadResolver>::createObject();
    res->init(id, offset);
    return res;
  }

  OdRxObject* queryX(const OdRxClass* pClass) const;

  OdResult loadObject(OdTvDbFilerController* pC, int threadId) const;

  bool     m_isPreloaded;
  OdUInt16 m_dwgType;
  OdUInt64 m_totalObjSize;
  OdUInt64 m_totalIdsBitSize;
  OdUInt64 m_rawOffset;
  OdUInt16 m_crc;
  OdUInt8  m_lengthOfSizeInfo;
};
// ODA_MT_DBIO_END

#endif // !defined(_ODDWGFILELOADER_H_INCLUDED_)
