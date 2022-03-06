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

#ifndef _ODDBXOBJECTIMPL_INCLUDED_
#define _ODDBXOBJECTIMPL_INCLUDED_

#include "OdArray.h"
#include "RxDictionary.h"
#include "IdArrays.h"
#include "DbObjectReactor.h"
#include "DbObject.h"
#include "OdBinaryData.h"
#include "../DbSystemInternals.h"
#include "DbSymUtl.h"
#include "DbFiler.h"
#include "BitFlags.h"
#include "Ge/GeExtents3d.h"
#include "../OdDwgCopyFiler.h"
#include "StaticRxObject.h"
#include "../DbStubExt.h"

class OdDbDatabase;
class OdRxDictionary;
class OdDbDwgFiler;
class OdProxyStuff;
class OdEntityContainer;
class OdXData;
class OdDbIdPair;
class OdGsCache;
class OdDbObjectContextDataManager;
class OdDbObjectContextData;

#include "TD_PackPush.h"

class OdDbSetNotifying
{
  OdDbObjectImpl* m_pImpl;
public:
  inline OdDbSetNotifying(OdDbObjectImpl* pImpl);
  inline ~OdDbSetNotifying();
};

#define ODDBOBJECT_FIRE(method, inparams, params) \
  void fire_##method inparams\
  {\
    OdDbSetNotifying state(this);\
    OdDbObjectReactorArray transientReactors(m_TransientReactors);\
    OdDbObjectReactorPtr* ptrs = (OdDbObjectReactorPtr*)transientReactors.getPtr();\
    OdDbObjectReactorPtr* ptrsend = ptrs + transientReactors.size();\
    for(; ptrs < ptrsend; ++ptrs)\
    {\
      if (m_TransientReactors.contains(*ptrs))\
        (*ptrs)->method params;\
    }\
    OdDbObjectIdArray reactors(m_Reactors);\
    OdDbObjectId* prs = (OdDbObjectId*)reactors.getPtr();\
    OdDbObjectId* prsend = prs + reactors.size();\
    for(; prs < prsend; ++prs)\
    {\
      if ( (*prs) != objectId() ) \
      { \
        OdDbObjectPtr pObj = (*prs).openObject(OdDb::kForNotify, true);\
        if(!pObj.isNull()) { \
          pObj->method params; \
          OdDbSystemInternals::getImpl(pObj)->setNotifyEnabled(false); \
        }\
      }\
    }\
  }

// Flags stored in OdDbObject
#define ODDBOBJECT_FLAGS(FLAG_DEF) \
  FLAG_DEF(AProxy,                0) \
  FLAG_DEF(OdDbObjectIdsInFlux,   0) \
  FLAG_DEF(ReadExclusive,         0) \
  FLAG_DEF(DiffUndoEnabled,       1) \
  FLAG_DEF(DiffUndoSaved,         0) \
  FLAG_DEF(HasDsData,             0) \
  FLAG_DEF(HasSaveVersionOverride,0)

// Open-time flags accessible from OdDbObject interface
#define OPENED_ODDBOBJECT_FLAGS(FLAG_DEF) \
/*  FLAG_DEF(Cancelling,            0)*/ \
  FLAG_DEF(ModifiedGraphics,      0) \
  FLAG_DEF(ModifiedXData,         0) \
  FLAG_DEF(NewObject,             1) \
  FLAG_DEF(NotifyEnabled,         0) \
  FLAG_DEF(Notifying,             0) \
  FLAG_DEF(ReadEnabled,           1) \
  FLAG_DEF(Undoing,               0) \
  FLAG_DEF(WriteEnabled,          1)

// Open-time flags inaccessible from OdDbObject interface
#define INT_OPENED_ODDBOBJECT_FLAGS(FLAG_DEF) \
  FLAG_DEF(ErasedAtOpening,       0) \
  FLAG_DEF(TransactionResident,   0) \
  FLAG_DEF(ModifiedItself,        1) \
  FLAG_DEF(UndoAppend,            0)

// All flags group
#define FLAGS_ALL(FLAG_DEF)         \
  ODDBOBJECT_FLAGS(FLAG_DEF)        \
  OPENED_ODDBOBJECT_FLAGS(FLAG_DEF) \
  INT_OPENED_ODDBOBJECT_FLAGS(FLAG_DEF)

// Open-time flags group
#define FLAGS_OPENTIME(FLAG_DEF)    \
  OPENED_ODDBOBJECT_FLAGS(FLAG_DEF) \
  INT_OPENED_ODDBOBJECT_FLAGS(FLAG_DEF)

#define XDATA_MAX_SIZE 0x4000
#define XDATA_MAX_SIZE_INTERNAL 0x8000

extern const OdChar* ACAD_FIELD;
extern const OdChar* ACAD_FIELDLIST;

class TOOLKIT_EXPORT OdDbObjectImpl
{
public:
  ODRX_HEAP_OPERATORS();
  OdDbObjectImpl(const OdDbObjectImpl&);
  bool isReallyClosing() const { return (isDBRO() ? m_nRefCounter==2 : m_nRefCounter==1); }
  bool isDBRO() const { return (!objectId().isNull()); }

  virtual ~OdDbObjectImpl();

private:
  OdDbObjectImpl& operator =(const OdDbObjectImpl&); // disabled

public:
  //////// Opened-time data: /////////////////////////////
// ODA_MT_DB_BEGIN
#ifndef ODA_ST_DB
  OdRefCounter      m_nRefCounter;
#else
  int               m_nRefCounter;
#endif
// ODA_MT_DB_END

private:
  OdUInt64          m_offset;
  OdUInt64          m_streamSizeOfObjRelatedData;

  OdDbObjectId      m_id;
  OdDbDatabase*     m_pDatabase;
  int               m_nTransSavedIn;
  int               m_nTransModifiedIn;
#ifndef ODA_ST_DB
  OdRefCounter      m_nUndoDisabled;
#else
  unsigned int      m_nUndoDisabled;
#endif

  // Define object flags:
  // m_objectFlags - object flags storage
  // openObjectFlags - mask and default flag values for all open-time object flags
  // newObjectFlags - mask and default flag values for newly created object
  //
  DEFINE_FLAGS(OdUInt32, m_objectFlags, FLAGS_ALL)
  DEFINE_FLAGS_VALUE(newObjectFlagsV,   FLAGS_ALL)
  DEFINE_FLAGS_MASK (newObjectFlagsM,   FLAGS_ALL)
  DEFINE_FLAGS_VALUE(openObjectFlagsV,  FLAGS_OPENTIME)
  DEFINE_FLAGS_MASK (openObjectFlagsM,  FLAGS_OPENTIME)

public:
  // Define accessors for object flags
  //
  DEFINE_FLAGS_ACCESSORS(FLAGS_ALL)
  bool isModified() const // not virtual as there is no way to set isModifiedGraphics() to true for non-OdDbEntity (#5674)
  {
    return isModifiedItself() || isModifiedGraphics();
  }
  virtual void setModified(bool v)
  {
    setModifiedItself(v);
    if (!v) 
      setModifiedXData(v);  // Bricsys torstenm : also mark XData part as unmodified
  }

  inline  OdDbObjectImpl()
    : m_pDatabase(NULL)
    , m_nTransSavedIn(0)
    , m_nTransModifiedIn(0)
    , m_nUndoDisabled(0)
    , m_objectFlags(newObjectFlagsV)
    , m_XDictId(0)
    , m_pXData(NULL)
    , m_pGsNode(0)
    , m_offset(0)
    , m_streamSizeOfObjRelatedData(0)
  {
    m_nRefCounter = 1;
  }

  inline bool isEraseStatusToggled() const
  {
    return (m_id.isErased() != isErasedAtOpening());
  }

//  ODDBOBJECT_FIRE(cancelled,       (const OdDbObject* pDbObj), (pDbObj))
  ODDBOBJECT_FIRE(copied,          (const OdDbObject* pDbObj, const OdDbObject* newObj), (pDbObj, newObj))
  ODDBOBJECT_FIRE(erased,          (const OdDbObject* pDbObj, bool pErasing),            (pDbObj, pErasing))
  //ODDBOBJECT_FIRE(goodbye,         (const OdDbObject* pDbObj), (pDbObj))
  ODDBOBJECT_FIRE(openedForModify, (const OdDbObject* pDbObj), (pDbObj))
  ODDBOBJECT_FIRE(modified,        (const OdDbObject* pDbObj), (pDbObj))
  ODDBOBJECT_FIRE(modifiedGraphics,(const OdDbObject* pDbObj), (pDbObj))
  ODDBOBJECT_FIRE(subObjModified,  (const OdDbObject* pDbObj, const OdDbObject* subObj), (pDbObj, subObj))
  ODDBOBJECT_FIRE(modifyUndone,    (const OdDbObject* pDbObj), (pDbObj))
  ODDBOBJECT_FIRE(modifiedXData,   (const OdDbObject* pDbObj), (pDbObj))
  ODDBOBJECT_FIRE(unappended,      (const OdDbObject* pDbObj), (pDbObj))
  ODDBOBJECT_FIRE(reappended,      (const OdDbObject* pDbObj), (pDbObj))
  ODDBOBJECT_FIRE(objectClosed,    (const OdDbObjectId& objId), (objId))
  void fire_goodbye(const OdDbObject* pDbObj)
  {
    OdDbSetNotifying state(this);
    OdDbObjectReactorArray transientReactors(m_TransientReactors);
    for(unsigned int i=0; i<transientReactors.size(); ++i)
    {
      if (m_TransientReactors.contains(transientReactors[i]))
        transientReactors[i]->goodbye(pDbObj);
    }
  }

  void setOpenMode(OdDb::OpenMode mode);
  OdDb::OpenMode getOpenMode() const;
  void dwgInXData(OdDbDwgFiler* pFiler);
  void dwgOutXData(OdDbDwgFiler* pFiler) const;
  void dxfInXData(OdDbDxfFiler* pFiler, bool clearXData = true);
  virtual void dxfOutXData(OdDbDxfFiler* pFiler) const;
  virtual bool hasXData(OdDb::DwgVersion ver, OdDbFiler::FilerType filerType) const;

private:
  void releaseObject(OdDbObject* pThis);

  friend class OdDbObject;
public:
  bool isUndoRecordingDisabled() const;
  void disableUndoRecording(bool bDoIt);
  OdDbSoftPointerId ownerId() const;
  void setOwnerId(OdDbObjectId id);
  virtual OdProxyStuff* getProxyStuff() { return 0; }
  virtual OdEntityContainer* entContainer() { return 0; }
  static void clearContainer(OdDbObject* pThis);

  // The methods support evaluating of connected objects.
  static void modified(OdDbObject* pThis, const OdDbObject* pAssocObj);
  static void openedForModify(OdDbObject* pThis, const OdDbObject* pAssocObj);
  // This function notified just before the current object is to be permanently erased,
  // giving this function the ability to cancel the permanent erase.
  // The function is used to:
  // - support partial loading of R15 dwg,
  // - support correct sorting of symbol records.
  virtual bool subErasePermanently();

  void createExtensionDictionary();
  void makeDBROFieldDictionary();
  union
  {
    OdDbStub*         m_XDictId;
    OdRxDictionary*   m_XDictIdNDBRO;
  };
  OdDbObjectIdArray           m_Reactors;

  mutable OdDbObjectReactorArray
                              m_TransientReactors;
  OdXData*                    m_pXData;
  OdGsCache*                  m_pGsNode;

  OdDbDatabase* database() const        { return m_pDatabase;}
  void setDatabase(OdDbDatabase* pDb)   { m_pDatabase = pDb; }

  inline OdDbObjectId objectId()  const { return m_id;}
  inline OdDbObjectId& objectId()       { return m_id;}
  int transSavedIn()    {return m_nTransSavedIn;}
  void setTransSavedIn(int n) {m_nTransSavedIn = n;}
  int transModifiedIn() {return m_nTransModifiedIn;}
  void setTransModifiedIn(int n) {m_nTransModifiedIn = n;}

  void setErased(bool flag);

  virtual void adjustProxyForSave(OdDbFiler*) {}

  virtual OdRxClass* saveAsClass(OdRxClass* pClass) const { return pClass; }

  virtual void audit(OdDbAuditInfo* pAuditInfo);
  virtual void auditXData(OdDbAuditInfo* pAuditInfo);

  virtual OdResBufPtr xData(const OdChar* regappName, bool treatLayerNameAsHandle = false) const;
  // Arguments:
  // treatLayerNameAsHandle (I) - added for correct processing of layer IDs in ID filers.
  // maxSize (I) - added for support files with more than 16k bytes of Xdata.
  virtual void setXData(const OdResBuf* pXData, bool treatLayerNameAsHandle = false, OdUInt16 maxSize = XDATA_MAX_SIZE, bool bTreatRegappAsId = false);
  void translateXData(OdDbIdMapping* pMap);

  //  dxf data read function
  virtual OdResult dxfReadData(OdDbDxfFiler* pFiler, int nCode, OdBinaryData *pData = NULL);

  OdResult dwgInRefs(OdDbDwgFiler* pFiler);
  void dwgOutRefs(OdDbDwgFiler* pFiler) const;

  // Database converting functions
  // Called for each database object during conversion
  // pObj - interface of object
  virtual void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version, OdDbAuditInfo* pAuditInfo)
  {
    composeForLoad(pObj, format, version);
  }

  virtual void convertToSysCodePage() {}

  // Called by the Drawings SDK to inform a parent object
  // that one of the objects that it owns has been modified.
  // Arguments:
  // pSubObj (I) Sub-object that has been modified.
  virtual void recvPropagateModify(OdDbObject* pOwner, const OdDbObject* pSubObj);

  static void wrXDataUndo(OdDbDwgFiler* pUndoFiler, const OdDbObjectImpl *pImpl);
  static void wrAppendUndo(OdDbDwgFiler* pUndoFiler, bool bAppending);
  static void wrEraseUndo(OdDbDwgFiler* pUndoFiler, bool bErasing);
  static void wrEraseUndoHistory(OdDbDwgFiler* pUndoFiler, OdDbObjectId objId, OdDbObjectId owner, bool bErasing);

  static void wrSubObjModifiedUndo(OdDbDwgFiler* pUndoFiler);

  friend void odDbSuppressAutoUndo(OdDbObjectImpl* pImpl);

  virtual OdDbObjectContextDataManager* contextDataManager() const {return 0;}
  virtual void copyFromContextData(OdDbObject*,OdDbObjectContextData*, OdDbObjectContextData*){}

  virtual bool isEntity() const { return false; }
  virtual bool isAnnotative() const { return false; }
  bool isAnnotativeByXdata() const;
  bool isLoading() const { return m_id.isNull() ? false : (m_id->flags(kOdDbIdLoading)!=0); }
  void handOverTo(OdDbObject* pOldObj, OdDbObject* pNewObj, bool bKeepXData, bool bKeepExtDict, bool updateOwners);
  bool enqueuePagingOnClose();

  OdDbDictionaryPtr safeXDictionary(OdDbAuditInfo* pAuditInfo) const;

  OdUInt64 getStreamOffset() const { return m_offset; }
  void setStreamOffset(OdUInt64 objOffset) { m_offset = objOffset; }

  OdUInt64 getStreamSize() const { return m_streamSizeOfObjRelatedData; }
  void setStreamSize(OdUInt64 streamSize) { m_streamSizeOfObjRelatedData = streamSize; }

protected:
  OdDbObject* getObject();
};

inline OdDbSetNotifying::OdDbSetNotifying(OdDbObjectImpl* pImpl)
  : m_pImpl(pImpl)
{
  pImpl->setNotifying(true);
}

inline OdDbSetNotifying::~OdDbSetNotifying()
{
  m_pImpl->setNotifying(false);
}

inline void odDbSuppressAutoUndoOutput(OdDbObjectImpl* pImpl)
{
  pImpl->setTransSavedIn(pImpl->database()->numActiveTransactions());
}

inline bool OdDbObjectImpl::isUndoRecordingDisabled() const
{
  if (isOdDbObjectIdsInFlux())
    return true;
  return m_nUndoDisabled != 0;
}

inline void OdDbObjectImpl::disableUndoRecording(bool bDisable)
{
  if(isUndoRecordingDisabled() || bDisable)
  {
    if(bDisable)
      ++m_nUndoDisabled;
    else
      --m_nUndoDisabled;
  }
}

inline OdDbObject* OdDbObjectImpl::getObject()
{
  ODA_ASSERT(m_id.isNull() || getOpenMode() != OdDb::kNotOpen); 
  return m_id.isNull() ? 0 : (OdDbObject*)m_id->getObject().get(); 
}

#include "../XDataBase.h"

class OdDbXDataRegApp
{
public:
  static OdDbStub* getRegAppId(const OdChar* appName, OdDbBaseDatabase* pBaseDb)
  {
    OdDbDatabasePtr pDb = pBaseDb;
    return OdDbSymUtil::getRegAppId(appName, pDb);
  }
  static OdString getRegAppName(OdDbStub* appId)
  {
    return OdDbSymUtil::getSymbolName(appId);
  }
};

class OdXData : public OdXDataBase< OdDbXDataRegApp >
{
};


#include "GiContextForDbDatabase.h"

template <class TExtCalc>
bool getObjectExtents(const OdDbObject* pThis, OdGeExtents3d& extents)
{
  pThis->assertReadEnabled();

  OdStaticRxObject<OdGiContextForDbDatabase> giContext;
  giContext.setDatabase( pThis->database(), false );

  OdStaticRxObject<TExtCalc> drawObject;
  drawObject.setContext(&giContext);
  drawObject.draw(pThis);
  drawObject.getExtents(extents);

  return extents.isValidExtents();
}

template <class TDbObject>
inline void oddbCopyClassData(const TDbObject* pSrc, TDbObject* pDst)
{
  pSrc->assertReadEnabled();
  OdDbObjectImpl* pSrcImpl = OdDbSystemInternals::getImpl(pSrc);
  OdDbDatabase* pSrcDb = pSrcImpl->database();

  OdStaticRxObject<OdDbDwgCopyFilerForClone > filer;
  filer.setDatabaseRef(pSrcDb);
  pSrcImpl->dwgOutXData(&filer);
  pSrc->TDbObject::dwgOutFields(&filer);

  pDst->assertWriteEnabled();
  OdDbObjectImpl* pDstImpl = OdDbSystemInternals::getImpl(pDst);
  OdDbDatabase* pDstDb = pDstImpl->database();
  if (pDstDb)
    filer.setDatabaseRef(pDstDb);
  else
    pDstImpl->setDatabase(pSrcDb);

  filer.rewind();
  // copyFrom() leaves reactors untouched  #16799
  OdDbObjectIdArray savedReactors(pDstImpl->m_Reactors);
  pDstImpl->dwgInXData(&filer);
  pDst->TDbObject::dwgInFields(&filer);
  pDstImpl->m_Reactors = savedReactors;
}

//----------------------------------------------------------
//
// OwnerIdUpdateFiler is a support class 
// used in handOverTo() and swapIdWith() operations
//
//----------------------------------------------------------
#include "../DbStubExt.h"
class OwnerIdUpdateFiler : public OdStaticRxObject<OdIdFiler>
{
  OdDbObjectId m_newOwnerIdToSet;
  OdDbDatabase* m_pDatabase;

public:
  OwnerIdUpdateFiler(OdDbDatabase* pDb = NULL)
    : m_pDatabase(pDb)
  {}

  virtual OdDbDatabase* database() const
  {
    return m_pDatabase;
  }

  void updateSubObjectsIds(const OdDbObject* pObject, const OdDbObjectId& ownerId)
  {
    m_newOwnerIdToSet = ownerId;
    pObject->dwgOutFields(this);
  }
  void wrSoftOwnershipId(const OdDbObjectId& id)
  {
    if (!id.isNull())
    {
      if (id->flags(kObjectLeftOnDisk|kObjectPageOnDisk) != 0)
      {
        id.openObject();
      }
      id->setOwnerId(m_newOwnerIdToSet);
    }
  }
  void wrHardOwnershipId(const OdDbObjectId& id) { wrSoftOwnershipId(id); }
  void addReference(OdDbObjectId id, OdDb::ReferenceType rt)
  {
    if((rt & 2)!=0)
    {
      wrSoftOwnershipId(id);
    }
  }
  void wrSoftPointerId(const OdDbObjectId& ) { }
  void wrHardPointerId(const OdDbObjectId& ) { }
};

#include "TD_PackPop.h"

#endif //_ODDBXOBJECTIMPL_INCLUDED_
