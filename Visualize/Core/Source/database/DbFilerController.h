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

// DwgFileController.h: interface for the OdTvDbFilerController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ODDBFILERCONTROLLER_H_INCLUDED_)
#define _ODDBFILERCONTROLLER_H_INCLUDED_

#include "OdStreamBuf.h"
#include "ProxyClass.h"
#include "DbDatabase.h"
#include "ThumbnailImage.h"
#include "DbHostAppServices.h"
#include "DbTypedId.h"
#include "DbStubExt.h"
#include "RxThreadPoolService.h"
#include "DbBlockTable.h"
#include "DbBlockTableRecord.h"
#define STL_USING_SET
#include "OdaSTL.h"

class OdTvDbDatabase;
class OdTvDbObject;
class OdThumbnailImage;
class OdTvDbAuditInfo;
class OdTvDbFilerController;
class OdTvDbSymbolTableImpl;
class OdTvDbBlockTableImpl;
class OdTvDbBlockTableRecordImpl;

class OdRxClassItem
{
  OdRxClassPtr m_pClass;
public:
  OdRxClassItem() {}
  OdRxClassItem(OdRxClass* pClass) : m_pClass(pClass) {}
  OdRxClassItem(OdRxObject* pClass) : m_pClass(pClass) {}
  const OdString getKey() const { return m_pClass->name(); }
  void setKey(const OdString& )
  {
    ODA_FAIL();// We shouldn't get here.
  }
  OdRxClassPtr getVal() const
  {
    return m_pClass;
  }
  void setVal(OdRxClass* pClass)
  {
    m_pClass = pClass;
  }
};

class OdTvDbObjectIdRefList
{
public:
  void addReference(OdTvDbObjectId id, OdDb::ReferenceType rt)
  {
    // No ID flags are set here - controller is responsible for setting and cleaning ID flags
    // See OdTvDbFilerController::addReference() method.
    ODA_ASSERT(!id.isErased());
    m_Ids.push_back(OdTvDbTypedId(id, rt));
  }

  OdTvDbTypedId getNextReference()
  {
    OdTvDbTypedId id;
    if ( !m_Ids.empty() )
    {
      id = *m_Ids.begin();
      ODA_ASSERT(!id.isNull());
      m_Ids.pop_front();
    }
    return id;
  }

// ODA_MT_DBIO_BEGIN
  void clear()
  {
    return m_Ids.clear();
  }
// ODA_MT_DBIO_END
private:
  OdList<OdTvDbTypedId> m_Ids;
};

namespace OdTvDbSymUtil
{
#define DBSYMUTL_MAKE_GETSYMBOLID_FUNC(T_TABLE) \
  OdTvDbObjectId get##T_TABLE##Id(OdInt16 nIndex, OdTvDbDatabase* pDb);

  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(Viewport)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(Block)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(DimStyle)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(Layer)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(Linetype)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(RegApp)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(TextStyle)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(UCS)
  DBSYMUTL_MAKE_GETSYMBOLID_FUNC(View)

#undef DBSYMUTL_MAKE_GETSYMBOLID_FUNC
}

class OdTvDbFilerController;
typedef OdSmartPtr<OdTvDbFilerController> OdTvDbFilerControllerPtr;

class OdTvDbDxfLoader;

// ODA_MT_DBIO_BEGIN
#include "OdLinkedArray.h"
class IdsContainer : public OdLinkedArray<OdTvDbObjectId, OdMemoryAllocator<OdTvDbObjectId> > {};
// ODA_MT_DBIO_END

class TOOLKIT_EXPORT OdTvDbFilerController : public OdRxObject
{
private:
  OdTvDbDatabase*         m_pDatabase;
  std::set<OdTvDbObjectId> m_RecomposeSet;
protected:
  OdStreamBufPtr        m_pStream;
  OdDb::DwgVersion      m_DwgVer;
  OdDb::MaintReleaseVer m_mVer;
  bool                  m_bPartial;
  bool                  m_bAllowCPConversion;
  OdTvDbObjectIdRefList   m_Ids;
  OdThumbnailImage*     m_ThumbNailImage;
  OdTvDbAuditInfo *       m_pAuditInfo;
  OdDbHostAppProgressMeter* m_pProgressMeter;
  OdDb::SaveType        m_SaveType;
// ODA_MT_DBIO_BEGIN
  bool                  m_bUseMTEngine;
  bool                  m_bIsMTMode;
  OdMutex               m_RefListLock;
  OdMutex               m_ProxyRefListLock;
  IdsContainer          m_ProxyIds;
  OdMutex               m_pmMutex;
  int                   m_numThreads;
  OdArray<bool, OdMemoryAllocator<bool> > m_MtAwarenessMap;
  bool                  m_bOldInt64;
// ODA_MT_DBIO_END

  ~OdTvDbFilerController();
  OdTvDbFilerController()
    : m_DwgVer(OdDb::kDHL_CURRENT)
    , m_mVer(OdDb::kMReleaseCurrent)
    , m_pDatabase(NULL)
    , m_bPartial(false)
    , m_bAllowCPConversion(false)
    , m_pAuditInfo(NULL)
    , m_ThumbNailImage(NULL)
    , m_pProgressMeter(NULL)
    , m_SaveType(OdDb::kDwg)
// ODA_MT_DBIO_BEGIN
    , m_bUseMTEngine(false)
    , m_bIsMTMode(false)
    , m_numThreads(1)
    , m_bOldInt64(false)
// ODA_MT_DBIO_END
  {}

  void addClass(OdTvProxyClass* pClass, OdInt32 nIndex = -1);
public:
  void loadClasses(OdTvDbDwgFiler &dwgStream, OdUInt64 nClassesDataSize/*=0xFFFFFFFFFFFFFFFF*/);
protected:
  virtual OdResult turnToOriginalObject(OdTvDbObject* pProxyObj);
public:
  ODRX_DECLARE_MEMBERS(OdTvDbFilerController);

  void setDatabase(OdTvDbDatabase* pDb)
  {
    m_pDatabase = pDb;
  }
  static void updateDatabase(OdTvDbDatabase* pDb);
  
  static OdTvDbFilerControllerPtr createFilerController(OdStreamBuf* pFileBuff, bool bRecover = false);

  inline void pmStart(const OdString& displayString = OdString::kEmpty);
  inline void pmStop();
  inline void pmMeterProgress();
  inline void pmSetLimit(int max);

  OdRxClass* getClass(OdUInt16 nClassId) const;

  OdRxClass* getClass(const OdString& className);

  OdUInt32 getClassId(const OdRxClass* pClass);

  const OdRxClass& getObjectClass(OdUInt16 nDwgType) const;

  void setDwgVer(OdDb::DwgVersion dwgVer)
  {
    m_DwgVer = dwgVer;
  }

  void setMaintVer(OdDb::MaintReleaseVer mVer)
  { 
    m_mVer = mVer; 
  }

  virtual OdDb::DwgVersion getDwgVer(OdDb::MaintReleaseVer* pmVer = NULL) const
  { 
    if(pmVer) 
    { 
      *pmVer = m_mVer; 
    } 
    return m_DwgVer; 
  }

  OdTvDbDatabase* database() 
  { 
    return m_pDatabase; 
  }
  void clearDatabase()
  {
    m_pDatabase = 0;
  }

  inline OdStreamBuf* getStreamBuf() { return m_pStream.get(); }

  virtual void closeInput();

  virtual OdTvDbObjectPtr loadObject(OdUInt64 offset) = 0;

  virtual void openR(OdStreamBuf* pOpenedIo)
  { 
    m_pStream = pOpenedIo; 
  }

  virtual void openW(OdStreamBuf* pOpenedIo, OdThumbnailImage* pImg)
  { 
    m_pStream = pOpenedIo; m_ThumbNailImage = pImg; 
  }

  virtual void loadPreviewImg(OdThumbnailImage* /*pPreview*/)
  { /* *pPreview=NULL;*/ ODA_FAIL(); /* SHOULD NOT GET HERE. SHOULD GET IN DERRIVED CLASS' METHOD.*/}

  virtual void getPreviewImg(OdThumbnailImage* /*pPreview*/)
  { /* *pPreview=NULL;*/ ODA_FAIL(); /* SHOULD NOT GET HERE. SHOULD GET IN DERRIVED CLASS' METHOD.*/}
  // Should be called from derived class's startDbLoading

  virtual void startDbLoading(OdTvDbDatabase* pDbToLoad, OdDbHostAppProgressMeter* pProgressMeter);

  // Should be called from derived class's endDbLoading
  virtual void endDbLoading();

  void findOwner(const OdTvDbObjectId& childId);

  virtual void startDbSaving(OdTvDbDatabase* );
  virtual void endDbSaving();

  virtual void startProgressMeter (OdTvDbDatabase*, const OdString&);
  virtual void endProgressMeter ();

  virtual bool supportsPartialLoading() const  { return true;}
          void setPartiallyOpened(bool val) { m_bPartial = val; }
          bool isPartiallyOpened() const { return m_bPartial; }

  virtual void setAuditInfo(OdTvDbAuditInfo* pAudit) 
  { 
    m_pAuditInfo = pAudit;
  }
  virtual OdTvDbAuditInfo* getAuditInfo(void) 
  { 
    return m_pAuditInfo; 
  }

  virtual void setPassword(const OdPassword& ) {}

  OdTvDbObjectIdRefList& getIdList() 
  { 
    return m_Ids; 
  };
  static void clearOwnershipCheckFlags(OdTvDbDatabase*);  
  static void clearSameOnDiskFlagForNonOwnedObjects(OdTvDbDatabase*);
  
  inline void addReference(OdTvDbObjectId id, OdDb::ReferenceType rt);

// ODA_MT_DBIO_BEGIN
  virtual OdResult loadObject(OdTvDbObjectPtr& pObj, const OdRxObject* pMTResolver, int threadId) { ODA_FAIL(); return eUnsupportedMethod; }

  bool isClassMTAware(OdUInt16 nDwgType) const;
  void readClassMtAwareness();
  bool useMTEngine() const { return m_bUseMTEngine; }
  void setUseMTEngine(int numThreads)
  { 
    m_bUseMTEngine = true;
    m_numThreads = numThreads;
  }
  int numThreads() const { return m_numThreads; }
  bool isMTMode() const { return m_bIsMTMode; }
  void setMTMode(bool val);
  virtual OdApcAtomPtr beginMTLoading(int threadsCount, OdTvDbObjectIterator* pObjs = 0, OdMTLoadReactor* pInterruptFlag = 0) { return OdApcAtomPtr(); }
  virtual void endMTLoading() {}
  inline void addMTPendingReference(OdTvDbObjectId id);
  inline void addMTProxyReference(OdTvDbObjectId id);

  OdMutex& pmMutex() { return m_pmMutex; }
// ODA_MT_DBIO_END

  // Load only database header
  // Used by TvFileDependency manager to update Xref info
  //
  virtual OdTvDbDatabasePtr loadDbHeader(OdTvDbHostAppServices*);

  void setAllowCPConversion (bool val) 
  { 
    m_bAllowCPConversion = val; 
  }
  bool allowCPConversion() 
  { 
    return m_bAllowCPConversion; 
  }
  bool oldInt64() 
  { 
    return m_bOldInt64; 
  }
  void loadDrawingMT(OdTvDbObjectIterator* = 0, OdMTLoadReactor* pInterruptFlag = 0);

  virtual void convertToSysCodePage();
  virtual OdTvDbDxfLoader* castToDxfLoader() { return 0; }
};


inline void OdTvDbFilerController::pmStart(const OdString& displayString)
{
  if (m_pProgressMeter)
    m_pProgressMeter->start(displayString);
}

inline void OdTvDbFilerController::pmStop()
{
  if (m_pProgressMeter)
    m_pProgressMeter->stop();
}

inline void OdTvDbFilerController::pmMeterProgress()
{
  if(m_pProgressMeter)
    m_pProgressMeter->meterProgress();
}

inline void OdTvDbFilerController::pmSetLimit(int max)
{
  if (m_pProgressMeter)
    m_pProgressMeter->setLimit(max);
}

void OdTvDbFilerController::addReference(OdTvDbObjectId id, OdDb::ReferenceType rt)
{
  if (database() != id.originalDatabase() || id.isNull())
    return;
  switch (rt)
  {
  case OdDb::kSoftOwnershipRef:
  case OdDb::kHardOwnershipRef:
    if (!id.isErased() && id->flags(kOdDbIdOwned)==0)
    {
// ODA_MT_DBIO_BEGIN
      if (!m_bIsMTMode)
      {
        m_Ids.addReference(id, rt);
      }
// ODA_MT_DBIO_END
      id->setFlags(kOdDbIdOwned,kOdDbIdOwned);
    }
    break;
  case OdDb::kHardPointerRef:
    if (!id.isNull())
    {
      id->setFlags(kOdDbIdReferenced,kOdDbIdReferenced);
    }
    break;
  case OdDb::kSoftPointerRef:
    break;
  }
}

// ODA_MT_DBIO_BEGIN
inline void OdTvDbFilerController::addMTPendingReference(OdTvDbObjectId id)
{
  if (!id.isErased())
  {
    TD_AUTOLOCK(m_RefListLock);
    m_Ids.addReference(id, OdDb::kSoftOwnershipRef);
  }
}

inline void OdTvDbFilerController::addMTProxyReference(OdTvDbObjectId id)
{
  if (!id.isErased())
  {
    TD_AUTOLOCK(m_ProxyRefListLock);
    m_ProxyIds.append(id);
  }
}
// ODA_MT_DBIO_END


template <class TDbObj, class TDbObjImpl> static TDbObjImpl* getimp(const TDbObj* obj) {
  return (TDbObjImpl*)OdTvDbSystemInternals::getImpl(obj);
}

#define DEFINE_GETIMP(CLASS) inline OdTvDb##CLASS##Impl* get##CLASS##Impl(const OdTvDb##CLASS* obj) { return getimp<OdTvDb##CLASS, OdTvDb##CLASS##Impl>(obj); }

DEFINE_GETIMP(SymbolTable);
DEFINE_GETIMP(BlockTable);
DEFINE_GETIMP(BlockTableRecord);


#endif // !defined(_OdDBFILERCONTROLLER_H_INCLUDED_)
