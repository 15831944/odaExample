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

// DwgFileController.h: interface for the OdDbFilerController class.
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

class OdDbDatabase;
class OdDbObject;
class OdThumbnailImage;
class OdDbAuditInfo;
class OdDbFilerController;
class OdDbSymbolTableImpl;
class OdDbBlockTableImpl;
class OdDbBlockTableRecordImpl;

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

class OdDbObjectIdRefList
{
public:
  void addReference(OdDbObjectId id, OdDb::ReferenceType rt)
  {
    // No ID flags are set here - controller is responsible for setting and cleaning ID flags
    // See OdDbFilerController::addReference() method.
    ODA_ASSERT(!id.isErased());
    m_Ids.push_back(OdDbTypedId(id, rt));
  }

  OdDbTypedId getNextReference()
  {
    OdDbTypedId id;
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
  OdList<OdDbTypedId> m_Ids;
};

namespace OdDbSymUtil
{
#define DBSYMUTL_MAKE_GETSYMBOLID_FUNC(T_TABLE) \
  OdDbObjectId get##T_TABLE##Id(OdInt16 nIndex, OdDbDatabase* pDb);

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

class OdDbFilerController;
typedef OdSmartPtr<OdDbFilerController> OdDbFilerControllerPtr;

class OdDbDxfLoader;

// ODA_MT_DBIO_BEGIN
#include "OdLinkedArray.h"
class IdsContainer : public OdLinkedArray<OdDbObjectId, OdMemoryAllocator<OdDbObjectId> > {};
// ODA_MT_DBIO_END

class TOOLKIT_EXPORT OdDbFilerController : public OdRxObject
{
private:
  OdDbDatabase*         m_pDatabase;
  std::set<OdDbObjectId> m_RecomposeSet;
protected:
  OdStreamBufPtr        m_pStream;
  OdDb::DwgVersion      m_DwgVer;
  OdDb::MaintReleaseVer m_mVer;
  bool                  m_bPartial;
  bool                  m_bAllowCPConversion;
  OdDbObjectIdRefList   m_Ids;
  OdThumbnailImage*     m_ThumbNailImage;
  OdDbAuditInfo *       m_pAuditInfo;
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

  ~OdDbFilerController();
  OdDbFilerController()
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

  virtual void addClass(OdProxyClass* pClass, OdInt32 nIndex = -1);
public:
  void loadClasses(OdDbDwgFiler &dwgStream, OdUInt64 nClassesDataSize/*=0xFFFFFFFFFFFFFFFF*/);
protected:
  virtual OdResult turnToOriginalObject(OdDbObject* pProxyObj);
public:
  ODRX_DECLARE_MEMBERS(OdDbFilerController);

  void setDatabase(OdDbDatabase* pDb)
  {
    m_pDatabase = pDb;
  }
  static void updateDatabase(OdDbDatabase* pDb);
  
  static OdDbFilerControllerPtr createFilerController(OdStreamBuf* pFileBuff, bool bRecover = false);

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

  OdDbDatabase* database() 
  { 
    return m_pDatabase; 
  }
  void clearDatabase()
  {
    m_pDatabase = 0;
  }

  inline OdStreamBuf* getStreamBuf() { return m_pStream.get(); }

  virtual void closeInput();

  virtual OdDbObjectPtr loadObject(OdUInt64 offset) = 0;

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

  virtual void startDbLoading(OdDbDatabase* pDbToLoad, OdDbHostAppProgressMeter* pProgressMeter);

  // Should be called from derived class's endDbLoading
  virtual void endDbLoading();

  void findOwner(const OdDbObjectId& childId);

  virtual void startDbSaving(OdDbDatabase* );
  virtual void endDbSaving();

  virtual void startProgressMeter (OdDbDatabase*, const OdString&);
  virtual void endProgressMeter ();

  virtual bool supportsPartialLoading() const  { return true;}
          void setPartiallyOpened(bool val) { m_bPartial = val; }
          bool isPartiallyOpened() const { return m_bPartial; }

  virtual void setAuditInfo(OdDbAuditInfo* pAudit) 
  { 
    m_pAuditInfo = pAudit;
  }
  virtual OdDbAuditInfo* getAuditInfo(void) 
  { 
    return m_pAuditInfo; 
  }

  virtual void setPassword(const OdPassword& ) {}

  OdDbObjectIdRefList& getIdList() 
  { 
    return m_Ids; 
  };
  static void clearOwnershipCheckFlags(OdDbDatabase*);  
  static void clearSameOnDiskFlagForNonOwnedObjects(OdDbDatabase*);
  
  inline void addReference(OdDbObjectId id, OdDb::ReferenceType rt);

// ODA_MT_DBIO_BEGIN
  virtual OdResult loadObject(OdDbObjectPtr& pObj, const OdRxObject* pMTResolver, int threadId) { ODA_FAIL(); return eUnsupportedMethod; }

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
  virtual OdApcAtomPtr beginMTLoading(int threadsCount, OdDbObjectIterator* pObjs = 0, OdMTLoadReactor* pInterruptFlag = 0) { return OdApcAtomPtr(); }
  virtual void endMTLoading() {}
  inline void addMTPendingReference(OdDbObjectId id);
  inline void addMTProxyReference(OdDbObjectId id);

  OdMutex& pmMutex() { return m_pmMutex; }
// ODA_MT_DBIO_END

  // Load only database header
  // Used by FileDependency manager to update Xref info
  //
  virtual OdDbDatabasePtr loadDbHeader(OdDbHostAppServices*);

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
  void loadDrawingMT(OdDbObjectIterator* = 0, OdMTLoadReactor* pInterruptFlag = 0);

  virtual void convertToSysCodePage();
  virtual OdDbDxfLoader* castToDxfLoader() { return 0; }
};


inline void OdDbFilerController::pmStart(const OdString& displayString)
{
  if (m_pProgressMeter)
    m_pProgressMeter->start(displayString);
}

inline void OdDbFilerController::pmStop()
{
  if (m_pProgressMeter)
    m_pProgressMeter->stop();
}

inline void OdDbFilerController::pmMeterProgress()
{
  if(m_pProgressMeter)
    m_pProgressMeter->meterProgress();
}

inline void OdDbFilerController::pmSetLimit(int max)
{
  if (m_pProgressMeter)
    m_pProgressMeter->setLimit(max);
}

void OdDbFilerController::addReference(OdDbObjectId id, OdDb::ReferenceType rt)
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
inline void OdDbFilerController::addMTPendingReference(OdDbObjectId id)
{
  if (!id.isErased())
  {
    TD_AUTOLOCK(m_RefListLock);
    m_Ids.addReference(id, OdDb::kSoftOwnershipRef);
  }
}

inline void OdDbFilerController::addMTProxyReference(OdDbObjectId id)
{
  if (!id.isErased())
  {
    TD_AUTOLOCK(m_ProxyRefListLock);
    m_ProxyIds.append(id);
  }
}
// ODA_MT_DBIO_END


template <class TDbObj, class TDbObjImpl> static TDbObjImpl* getimp(const TDbObj* obj) {
  return (TDbObjImpl*)OdDbSystemInternals::getImpl(obj);
}

#define DEFINE_GETIMP(CLASS) inline OdDb##CLASS##Impl* get##CLASS##Impl(const OdDb##CLASS* obj) { return getimp<OdDb##CLASS, OdDb##CLASS##Impl>(obj); }

DEFINE_GETIMP(SymbolTable);
DEFINE_GETIMP(BlockTable);
DEFINE_GETIMP(BlockTableRecord);


#endif // !defined(_OdDBFILERCONTROLLER_H_INCLUDED_)
