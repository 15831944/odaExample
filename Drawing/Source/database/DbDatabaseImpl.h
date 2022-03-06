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

// ODA typedefs
#ifndef _ODDBDATABASEIMPL_INCLUDED_
#define _ODDBDATABASEIMPL_INCLUDED_

#include "DbSystemInternals.h"
#include "DbDatabase.h"
#include "DbSymbolTable.h"
#include "ProxyClass.h"
#include "DbDatabaseReactor.h"
#include "Ge/GePoint2d.h"
#include "Ge/GePoint3d.h"
#include "DbDate.h"
#include "IdArrays.h"
#include "DynamicLinker.h"
#include "OdToolKit.h"
#include "Entities/DimensionInfo.h"
#include "RxClassesDictionaryImpl.h"
#include "DbVXTable.h"
#include "DbTransactionReactor.h"
#include "DbFilerController.h"
#include "Objects/DbObjectImpl.h"
#include "DbObjectIterator.h"

#include "StaticRxObject.h"
#include "DbIdMapping.h"
#include "Objects/DbObjectImpl.h"
#include "DwgFiler/DwgWatermark.h"

#include "DbAnnotationScale.h"
#include "DbObjectContextManager.h"
#include "DbObjectContextCollection.h"
#include "DbUnitsFormatterImpl.h"
#include "DbLayerState.h"
#include "LyLayerFilter.h"

#include "Ds/DsRecordsSet.h"
#include "DwgFiler/DwgR18Controller.h"
#include "DbHistoryManager.h"

#include "OdDwgDigitalSignature.h"

// ODA_MT_DB_BEGIN
#include "../root/OdMutexPool.h"
// ODA_MT_DB_END

#define STL_USING_ALL
#include "OdaSTL.h"

// TODO:
class OdDbIdMapping;
class OdDbAuditInfo;
class OdGeMatrix3d;
class OdString;
class OdDbFilerController;
class OdDbTransaction;
class OdThumbnailImage;
class OdHandleTree;
class OdDbStub;

class OdDbEntity;
class OdDbFiler;
class OdDbDictionary;
class OdDbDictionaryWithDefault;
class OdDbDatabaseReactor;
class OdDbUndoController;
class OdDbSpatialFilter;
class OdDbLayerFilter;
class OdDbLoader;
class OdDbDwgFiler;
class OdDbUndoFilerImpl;
typedef std::deque<OdDbObjectPtr> OdDbObjectPtrDeque;
class OdOxOleLinkManagerImpl;
class OdDbHeaderLoadInfo;
class OdDbPager;
class OdDbDataLinkManager;

#include "summinfo.h"
typedef OdSmartPtr<OdDbDatabaseSummaryInfo> OdDbDatabaseSummaryInfoPtr;

extern TOOLKIT_EXPORT void odDbSetCurrentVersion(OdDbDatabase* pDb, OdDb::DwgVersion currentVer, OdDb::MaintReleaseVer currentMVer);
extern TOOLKIT_EXPORT void odDbAppendClass(OdDbDatabase* pDb, OdRxClass* pClass, bool bForceAppend);
extern TOOLKIT_EXPORT void odDbRemoveAllClasses(OdDbDatabase* pDb);
extern TOOLKIT_EXPORT OdRxClassPtr odDbGetClassAt(OdDbDatabase* pDb, const OdString& strClassName);
extern TOOLKIT_EXPORT void odDbAppendClass(OdDbDatabase* pDb, OdUInt32 nIndex, OdProxyClass* pClass);
extern TOOLKIT_EXPORT void odDbTrackClass(OdDbDatabase* pDb, OdDbObject* pObject);
extern void odDbForceObjectUndoOutput(OdDbDatabase* pDb);
extern void odDbSaveTransactionContext(OdDbObject* pObj);
extern void correctRootDictionary(OdDbDatabase* pDatabase);
extern void convertDatabaseTo(OdDbDatabase* pDb, OdDb::DwgVersion ver, OdDb::SaveType type, bool bLoading);

//Defaults arguments can be used for friends functions.
void resolveSummaryInfoForR15(OdDbDatabase* pDb, OdDb::SaveType type = OdDb::kDwg);
void createSummaryInfoForR15(OdDbDatabase* pDb, OdDb::SaveType type = OdDb::kDwg);

#define ODDBDATABASE_FIRE(method, inparams, params) \
  inline void fire_##method inparams\
{\
  Reactors reactors(m_Reactors);\
  OdDbDatabaseReactor** prs = (OdDbDatabaseReactor**)reactors.getPtr();\
  OdDbDatabaseReactor** prsend = prs + reactors.size();\
  for(; prs < prsend; ++prs)\
  {\
    if (m_Reactors.contains(*prs))\
      (*prs)->method params;\
  }\
}

#define ODDBTRANSACTMANAGER_FIRE(method, inparams, params) \
  inline void fire_##method inparams\
{\
  TransReactors reactors(m_TransReactors);\
  for(unsigned i=0; i<reactors.size(); ++i)\
  {\
    if (m_TransReactors.contains(reactors[i]))\
      reactors[i]->method params;\
  }\
}


class OdDbHostAppProgressMeter;
class OdDbDwgClassMap;
class OdDbFontTable;
typedef OdSmartPtr<OdDbFontTable> OdDbFontTablePtr;

class OdDbDatabaseImpl;

class OdDbConversionMeter : public OdDbHostAppProgressMeter
{
  OdDbDatabaseImpl         *m_pDb;
  OdDbHostAppProgressMeter *m_pMeter;
  const OdInt8              m_MaxPercentValue;
  const OdInt32             m_PercentStepDef;
  OdInt32                   m_PercentStep;
  OdInt32                   m_CurPercent;
  OdInt32                   m_PercentLeft;
  OdInt32                   m_numSteps;
  OdInt32                   m_StopAt;
  OdInt32                   m_StartAt;
  bool                      m_isInProgress;

public:
  OdDbConversionMeter();

  void setDb(OdDbDatabaseImpl *pDb)
  {
    m_pDb= pDb;
  }
  bool isInProgress() const { return m_isInProgress; }

  virtual void start(const OdString& displayString = OdString::kEmpty);
  virtual void stop();
  virtual void meterProgress();
  virtual void setLimit(int) { }
};

//#pragma MARKMESSAGE(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! implementation class OdDbDatabaseImpl exported here)
class TOOLKIT_EXPORT OdDbDatabaseImpl : public OdDimensionInfo,
                         public OdDbObjectImpl
{
  OdDbDatabaseImpl& operator =(const OdDbDatabaseImpl&);
//  OdDbHardOwnershipId                         m_FontTableId;
  OdStaticRxObject<OdRxClassesDictionaryImpl> m_classes;
  OdDbConversionMeter*                        m_pConvMeter;
  OdDbIdMappingPtr                            m_pXrefIdMapping;

  OdUInt32                                    m_nStateFlags;
  enum
  {
    kPerformingDbUndo     = 0x00000001,
    kUndoFilerEnabled     = 0x00000002,
    kUndoOutputForced     = 0x00000004,
    kUndoBlockStarted     = 0x00000008,

    kRetainOrigThumbnail  = 0x00000010,
    kUndoToMark           = 0x00000020,
    kDwgCheck             = 0x00000040,
    kUndoingBlock         = 0x00000080,
    kAssocDependencyNotificationDisabled = 0x00000100
  };
public:
  void startConversionMeter();
  void progressConversionMeter();
  void stopConversionMeter();

  static OdDbDatabaseImpl* getImpl(const OdDbDatabase *pDb) { return pDb->m_pImpl;}

  OdRxObjectPtr m_pDbUndoFiler;

  static void setXrefIdMapping(OdDbDatabase* pDb, OdDbIdMapping* pXrefIdMapping);
  static OdDbIdMapping* xrefIdMapping(const OdDbDatabase* pDb) { return getImpl(pDb)->m_pXrefIdMapping; }

  static OdDbFontTablePtr fontTable(OdDbDatabase* pDb);
//  OdDbObjectId fontTableId() const { return m_FontTableId; }
  OdDbHostAppServices* m_pHostAppSvcs;

  OdDbDatabaseImpl();
  ~OdDbDatabaseImpl();

  OdDbHandle getNextAvailableHandle() const;
  typedef OdArray<OdDbDatabaseReactor*,OdMemoryAllocator<OdDbDatabaseReactor*> > Reactors;
  Reactors m_Reactors;
  void generateThumbnailImage(OdThumbnailImage&) {}

  inline void fire_headerSysVarWillChange(const OdDbDatabase* pDb, const OdString& name)
  {
    // we need loacal copy for the case if reactor is removed while notification
    Reactors reactors(m_Reactors);
    for(unsigned i=0; i<reactors.size(); ++i)
    {
      if (m_Reactors.contains(reactors[i]))
        reactors[i]->headerSysVarWillChange(pDb, name);
    }
  }

#define RO_VAR_DEF(type, name, d1, d2, r1, r2)
#define VAR_DEF(type, name, d1, d2, r1, r2) \
  inline void fire_headerSysVar_##name##_WillChange(const OdDbDatabase* pDb)\
  {\
    Reactors reactors(m_Reactors);\
    for(unsigned i=0; i<reactors.size(); ++i)\
      if (m_Reactors.contains(reactors[i]))\
        reactors[i]->headerSysVar_##name##_WillChange(pDb);\
  }
#include "SysVarDefs.h"
#undef VAR_DEF
#define VAR_DEF(type, name, d1, d2, r1, r2) \
  inline void fire_headerSysVar_##name##_Changed(const OdDbDatabase* pDb)\
  {\
    Reactors reactors(m_Reactors);\
    for(unsigned i=0; i<reactors.size(); ++i)\
      if (m_Reactors.contains(reactors[i]))\
        reactors[i]->headerSysVar_##name##_Changed(pDb);\
  }
#include "SysVarDefs.h"
#undef VAR_DEF

#define VAR_DEF(type, name, dxf, d1, d2, r1, r2) \
  inline void fire_headerSysVar_dim##name##_WillChange(const OdDbDatabase* pDb)\
  {\
    Reactors reactors(m_Reactors);\
    for(unsigned i=0; i<reactors.size(); ++i)\
      if (m_Reactors.contains(reactors[i]))\
        reactors[i]->headerSysVar_dim##name##_WillChange(pDb);\
  }
#include "DimVarDefs.h"
#undef VAR_DEF
#define VAR_DEF(type, name, dxf, d1, d2, r1, r2) \
  inline void fire_headerSysVar_dim##name##_Changed(const OdDbDatabase* pDb)\
  {\
    Reactors reactors(m_Reactors);\
    for(unsigned i=0; i<reactors.size(); ++i)\
      if (m_Reactors.contains(reactors[i]))\
        reactors[i]->headerSysVar_dim##name##_Changed(pDb);\
  }
#include "DimVarDefs.h"
#undef VAR_DEF
#undef RO_VAR_DEF

  ODDBDATABASE_FIRE(objectOpenedForModify, \
  (const OdDbDatabase* pDb, const OdDbObject* pDbObj), (pDb, pDbObj))
  ODDBDATABASE_FIRE(objectAppended, \
  (const OdDbDatabase* pDb, const OdDbObject* pDbObj), (pDb, pDbObj))
  ODDBDATABASE_FIRE(objectUnAppended, \
  (const OdDbDatabase* pDb, const OdDbObject* pDbObj), (pDb, pDbObj))
  ODDBDATABASE_FIRE(objectReAppended, \
  (const OdDbDatabase* pDb, const OdDbObject* pDbObj), (pDb, pDbObj))
  ODDBDATABASE_FIRE(objectModified, \
  (const OdDbDatabase* pDb, const OdDbObject* pDbObj), (pDb, pDbObj))
  ODDBDATABASE_FIRE(objectErased, \
  (const OdDbDatabase* pDb, const OdDbObject* pDbObj, bool pErased = true), (pDb, pDbObj, pErased))
  ODDBDATABASE_FIRE(headerSysVarChanged, \
  (const OdDbDatabase* pDb, const OdString& name), (pDb, name))
  ODDBDATABASE_FIRE(proxyResurrectionCompleted, \
  (const OdDbDatabase* pDb, const OdString& appname, OdDbObjectIdArray& objects), (pDb, appname, objects))
  ODDBDATABASE_FIRE(goodbye, (const OdDbDatabase* pDb), (pDb))

  typedef OdArray<OdDbTransactionReactor*> TransReactors;
  TransReactors m_TransReactors;

  ODDBTRANSACTMANAGER_FIRE(transactionAboutToStart, (OdDbDatabase* pDb), (pDb))
  ODDBTRANSACTMANAGER_FIRE(transactionStarted,      (OdDbDatabase* pDb), (pDb))
  ODDBTRANSACTMANAGER_FIRE(transactionAboutToEnd,   (OdDbDatabase* pDb), (pDb))
  ODDBTRANSACTMANAGER_FIRE(transactionEnded,        (OdDbDatabase* pDb), (pDb))
  ODDBTRANSACTMANAGER_FIRE(transactionAboutToAbort, (OdDbDatabase* pDb), (pDb))
  ODDBTRANSACTMANAGER_FIRE(transactionAborted,      (OdDbDatabase* pDb), (pDb))
  ODDBTRANSACTMANAGER_FIRE(endCalledOnOutermostTransaction, (OdDbDatabase* pDb), (pDb))
  ODDBTRANSACTMANAGER_FIRE(objectIdSwapped, (const OdDbObject* pTransObj, const OdDbObject* pOtherObj, OdDbDatabase* pDb), (pTransObj, pOtherObj, pDb))

  OdRxClass* classAt(const OdString& szName) { return (OdRxClass*)m_classes.getAt(szName).get(); }
  OdRxClass* classAt(int nIndex) { return (OdRxClass*)m_classes.getAt(nIndex-500).get(); }
  OdUInt16 classId(const OdString& szName) const
  {
    OdUInt32 id = m_classes.idAt(szName);
    return OdUInt16(id==OdRx::kNullDictId ? 0 : id + 500);
  }

  OdUInt32  classCount()  { return m_classes.numEntries(); }

  OdResult dwgInFields(OdDbDwgFiler& io, OdDbHeaderLoadInfo& pInfo);
  void dwgInChecksum(OdDbDwgFiler* pFiler);
  void dwgOutChecksum(OdDbDwgFiler* pFiler);

  OdHandleTree*           m_pHandles;
  OdDbFilerControllerPtr  m_pFilerController;
  OdSharedPtr<OdDwgR18FileController::IncrementalInfo> m_II;
  bool m_enableIncSave;
  bool m_writeFileCalledUsingOpenAlways;

  OdDwgDigitalSignaturePtr m_pSignature;

  OdDbAuditInfo*          m_pAuditInfo;

  OdDbHardOwnershipId m_NamedObjectsDictId;
  OdDbHardPointerId   m_GroupDicId;
  mutable OdDbHardPointerId m_MLineDicId;

  OdDbHardPointerId   m_LayoutDicId;
  OdDbHardPointerId   m_PlotsettingsDicId;
  OdDbHardPointerId   m_ColorDicId;
  OdDbHardPointerId   m_MaterialDicId;
  OdDbHardPointerId   m_VisualStyleDicId;
  OdDbHardPointerId   m_TableStyleDicId;
  OdDbHardPointerId   m_MLeaderStyleDicId;
  OdDbHardPointerId   m_PlotstyleDicId;
  OdDbHardPointerId   m_ScaleListDicId;
  OdDbHardPointerId   m_UnknownAC27Id; // AC27 support
  OdDbHardPointerId   m_DetailViewStyleDicId;
  OdDbHardPointerId   m_SectionViewStyleDicId;
  OdDbHardPointerId   m_PointCloudDicId;

  OdDbHardOwnershipId m_BlockTableId;
  OdDbHardOwnershipId m_DimStyleTableId;
  OdDbHardOwnershipId m_LayerTableId;
  OdDbHardOwnershipId m_LinetypeTableId;
  OdDbHardOwnershipId m_StyleTableId;
  OdDbHardOwnershipId m_UcsTableId;
  OdDbHardOwnershipId m_ViewTableId;
  OdDbHardOwnershipId m_VPortTableId;
  OdDbHardOwnershipId m_RegAppTableId;
  OdDbHardOwnershipId m_VXTableId;

  mutable OdDbHardPointerId m_MSpaceId;
  mutable OdDbHardPointerId m_AcadAppId;
  mutable OdDbHardPointerId m_StandardTextStyleId;
  mutable OdDbHardPointerId m_StandardDimStyleId;
  mutable OdDbHardPointerId m_LayerZeroId;
  mutable OdDbHardPointerId m_LayerDefpointsId;

  mutable OdDbHardPointerId m_ByLayerLinetypeId;
  mutable OdDbHardPointerId m_ByBlockLinetypeId;
  mutable OdDbHardPointerId m_ContinuousLinetypeId;

  mutable OdDbHardPointerId m_ByLayerMaterialId;
  mutable OdDbHardPointerId m_ByBlockMaterialId;
  mutable OdDbHardPointerId m_GlobalMaterialId;

  OdDbHardPointerId m_CurVxRecordId;
  OdDbHardPointerId m_CurUcsOrthoRefId;
  OdDbHardPointerId m_CurPUcsOrthoRefId;
//  OdDbHardPointerId m_PlotStyleId;
  OdThumbnailImage m_ThumbnailImage;

#define REGVAR_DEF(type, name, unused3, unused4, unused5) \
  type get##name() const { return m_pHostAppSvcs->get##name(); }

#define VAR_DEF(type, name, def_value, metric_def_value, reserve1, reserve2)  \
protected:type  m_##name;\
public:type get##name() const { return m_##name; }\
  void set##name(type val) { m_##name = val; }

#undef ANNO_VAR_DEF
#define ANNO_VAR_DEF(type, name, def_value, metric_def_value, reserve1, reserve2)  \
protected:type  m_##name;\
public:type get##name() const { return m_##name; }\
  void set##name(type val) { m_##name = val; m_pObjectContextManager->contextCollection(ODDB_ANNOTATIONSCALES_COLLECTION)->setCurrentContext(val); }

#include "SysVarDefs.h"
#undef ANNO_VAR_DEF
#undef VAR_DEF
#undef REGVAR_DEF

  OdDbDate getTDCREATE() const;
  OdDbDate getTDUPDATE() const;

  void setDefaultVar(OdDb::MeasurementValue measurement);

  double m_UnkDouble0, m_UnkDouble1, m_UnkDouble2, m_UnkDouble3;
  OdString m_UnkString0, m_UnkString1, m_UnkString2, m_UnkString3;
  OdInt32 m_UnkLong0, m_UnkLong1;
  OdInt16 m_UnkShort0;

  OdDbObjectId& vxTableId() { return m_VXTableId; }
  OdDbObjectId& blockTableId() { return m_BlockTableId; }
  OdDbObjectId& layerTableId() { return m_LayerTableId; }
  OdDbObjectId& styleTableId() { return m_StyleTableId; }
  OdDbObjectId& linetypeTableId() { return m_LinetypeTableId; }
  OdDbObjectId& viewTableId() { return m_ViewTableId; }
  OdDbObjectId& ucsTableId() { return m_UcsTableId; }
  OdDbObjectId& vPortTableId() { return m_VPortTableId; }
  OdDbObjectId& regAppTableId() { return m_RegAppTableId; }
  OdDbObjectId& dimStyleTableId() { return m_DimStyleTableId; }

  OdDbVXTablePtr getVxTable(OdDb::OpenMode mode) { return vxTableId().safeOpenObject(mode); }

  void setFilerController(OdDbFilerController* pFilerController);
  OdDbFilerController* filerController() { return m_pFilerController.get(); }

  OdDbAuditInfo* recoverInfo()
  {
    return m_pAuditInfo;
  }

  void setRecoverInfo(OdDbAuditInfo* pAudit)
  {
    m_pAuditInfo = pAudit;
  }

  // Returns current database state
  //
  bool isDatabaseLoading() const;
  bool isDatabaseDestroying() const;
  bool isInitialized() const { return !m_BlockTableId.isNull(); }
  bool isPerObjectConverting() const { return !m_pFilerController.isNull(); }
  bool isDatabaseConverting() const;
  // #6049
  // Current PaperSpaceId may be changed via "Set Active Layout" before object loading in partial mode.
  // So m_CachedPaperSpaceId is set in OdDbDatabase::dwgInFields() and used in OdDbEntity::dwgInFields().
  // Also m_CachedPaperSpaceId is set in OdDbDatabase::dwgOutFields()
  // and used in OdDbEntity::dwgOutFields() to avoid the block table opening
  // through OdDbDatabase::getPaperSpaceId().
  mutable OdDbObjectId m_CachedPaperSpaceId;

  // #8465
  // Used to implement ARX like (entlast) behavior
  struct EntLastCache
  {
    OdDbObjectId m_id;
    OdDbObjectId m_spaceId;
    OdDbHandle   m_handseed;
    // (entnext) cached iterator
    OdDbObjectIteratorPtr m_iterator;
  } m_entLastCache;
  OdResBufPtr m_EntMakeCache;

  OdUInt32              m_educationalPlotStamp;
  OdUInt32              m_numberOfSaves;
  OdUInt32              m_numberOfSavesSinceOpened;
  OdDb::DwgVersion      m_lastSavedAsDwgVer;
  OdDb::MaintReleaseVer m_lastSavedAsMVer;
  OdDb::DwgVersion      m_origFileDwgVer;
  OdDb::MaintReleaseVer m_origFileMVer;
  OdDb::DwgVersion      m_origFileSavedByDwgVer;
  OdDb::MaintReleaseVer m_origFileSavedByMVer;
  OdDb::SaveType        m_origFileType;

  OdDbUndoFilerImpl* getDbUndoFiler(OdDbDatabase* pDb, bool bCreate);

  void audit          (OdDbAuditInfo* pAuditInfo);
  void auditDefaultObjects(OdDbAuditInfo* pAuditInfo = 0, bool bFixErrors = true);
  void auditDefaultSymbolTables(OdDbDatabase* pDb, OdDbAuditInfo* pAuditInfo = 0, bool bFixErrors = true);
  void auditDefaultDictionaries(OdDbDatabase* pDb, OdDbAuditInfo* pAuditInfo = 0, bool bFixErrors = true);
  void auditFinal     (OdDbAuditInfo* pAuditInfo);

  void setHANDSEED(OdDbHandle hanseed) { m_HANDSEED = hanseed; }
  OdDbHandle getHANDSEED() { return m_HANDSEED; }

  OdUInt32              m_numTransactions;

  bool isPerformingDbUndo() const { return GETBIT(m_nStateFlags, kPerformingDbUndo); }
  void setPerformingDbUndo(bool bFlag) { SETBIT(m_nStateFlags, kPerformingDbUndo, bFlag); }

  bool isUndoFilerEnabled() const { return GETBIT(m_nStateFlags, kUndoFilerEnabled); }
  void setUndoFilerEnabled(bool bFlag) { SETBIT(m_nStateFlags, kUndoFilerEnabled, bFlag); }

  bool isUndoOutputForced() const { return GETBIT(m_nStateFlags, kUndoOutputForced); }
  void forceUndoOutput(bool bForce = true) { SETBIT(m_nStateFlags, kUndoOutputForced, bForce); }

  void setUndoBlockStarted(bool bFlag) { SETBIT(m_nStateFlags, kUndoBlockStarted, bFlag); }
  bool isUndoBlockStarted() const { return GETBIT(m_nStateFlags, kUndoBlockStarted); }

  void setRetainOriginalThumbnailBitmap(bool bFlag) { SETBIT(m_nStateFlags, kRetainOrigThumbnail, bFlag); }
  bool retainOriginalThumbnailBitmap() const { return GETBIT(m_nStateFlags, kRetainOrigThumbnail); }

  void setUndoingBlock(bool bFlag) { SETBIT(m_nStateFlags, kUndoingBlock, bFlag); }
  bool isUndoingBlock() const { return GETBIT(m_nStateFlags, kUndoingBlock); }

  void setUndoToMark(bool bFlag) { SETBIT(m_nStateFlags, kUndoToMark, bFlag); }
  bool undoToMark() const { return GETBIT(m_nStateFlags, kUndoToMark); }

  void setDwgCheckPassed(bool bFlag) { SETBIT(m_nStateFlags, kDwgCheck, bFlag); }
  bool dwgCheckPassed() const { return GETBIT(m_nStateFlags, kDwgCheck); }

  void setAssocDependencyNotificationDisabled(bool bFlag) { SETBIT(m_nStateFlags, kAssocDependencyNotificationDisabled, bFlag); }
  bool assocDependencyNotificationDisabled() const { return GETBIT(m_nStateFlags, kAssocDependencyNotificationDisabled); }

  OdSecurityParams      m_securityParams;
  OdDbDatabaseSummaryInfoPtr m_pSummaryInfo;
  OdFileDependencyManagerPtr m_pFileDependencyManager;
  OdDbObjectContextManagerPtr m_pObjectContextManager;

  // Supports paging of database objects.
  //
  bool isPagingSupported() { return m_pPager != 0; }
  void initializePaging();
  void finalizePaging();
  void attachUnloadingData(const OdDbObjectId &id, OdUInt32 offset);
  bool enqueuePagingOnClose(const OdDbObjectId &id);
  bool enqueuePaging(const OdDbObjectId &id);

  // Supports saving ODA watermark in dwg files.
  //
  void setDwgFileWasSavedByOdaSoftware(const OdDwgWatermark::Product& pr) { m_watermark = pr; }
  OdDwgWatermark::Product getDwgFileWasSavedByOdaSoftware() { return m_watermark; }

  static OdDbObjectId deadendXrefBlock(OdDbDatabase* pDb);

  OdDbObjectPtrDeque    m_transResidents;
private:
  //OdDbNullTransResident*m_pNullTransResidents;
  OdDbDatabaseReactor*  m_pTransChangesFlusher;
  OdDbHandle            m_HANDSEED;
  OdDb::DwgVersion      m_currentVer;
  OdDb::MaintReleaseVer m_currentMVer;
public:
  OdString              m_currentFileName;
  OdString              m_originalFileName;
private:
  OdDbObjectId          m_DummyBlockId;
  OdDbObjectId          m_xrefBlockId;
  OdDbPager*            m_pPager;
  OdDwgWatermark::Product m_watermark;
  OdStaticRxObject<OdDbUnitsFormatterImpl> m_pUnitsFormatter;
  bool m_bEnableGraphicsFlush;
  public:
  bool m_bIsLoading;
  bool m_bIsDestroying;
  private:
  OdDb::SaveType  m_saveType;

// ODA_MT_DB_BEGIN
private:
  OdDb::MultiThreadedMode m_multiThreadedMode;
  OdMutexPool m_mutexPool;
  OdMutex m_ReactorsMutex;
// ODA_MT_DBIO_BEGIN
  bool m_bIsMTLoading;
// ODA_MT_DBIO_END
public:
  OdMutexPool* mutexPool() { return &m_mutexPool; }
  OdDb::MultiThreadedMode multiThreadedMode() const { return m_multiThreadedMode; }
// ODA_MT_DBIO_BEGIN
  bool isMTLoading() const { return m_bIsMTLoading; }
// ODA_MT_DBIO_END
// ODA_MT_DB_END

// AC27 support DS (begin)
public:
  OdDs::RecordsSet& dsRecordsSet()
  {
    return m_dsRecordsSet;
  }
  void setUseDsDecomposedData(bool val)
  {
    m_bHasDecomposedDsData = val;
  }
  bool useDsDecomposeData()
  {
    return m_bHasDecomposedDsData;
  }
private:
  OdDs::RecordsSet m_dsRecordsSet;
  bool m_bHasDecomposedDsData;
// AC27 support DS (end)

  // flag is set while undoing changes made in convertDatabaseTo()
  bool m_bIsUndoingConversion;
  bool m_bExclusiveReadingEnabled; //enable kOdDbIdNoAutoLock flag check
  OdRefCounter m_nRefsMTRendering;
public:
  bool isUndoingConversion() const {return m_bIsUndoingConversion;}

  // user variables for lisp and diesel (not saved, not present in the interface)
  OdString m_USERS1;
  OdString m_USERS2;
  OdString m_USERS3;
  OdString m_USERS4;
  OdString m_USERS5;
  // current long transaction for database
  OdDbObjectId m_LongTransactionId;
  OdInt16 m_BINDTYPE; 

  void clearRecomposeSet();
  void saveRecomposeSet();
  void addToRecompose(OdDbObjectId id);
  bool isRecomposed(OdDbObjectId id);
  const std::set<OdDbObjectId>& recomposeSet() const { return m_RecomposeSet; }
  void loadRecomposeSet();
  void updateEntLastCache();
  OdDbObjectId getModelSpaceId() const;

  bool isExclusiveReadingEnabled() const { return m_bExclusiveReadingEnabled; }
  void setExclusiveReadingEnabled(bool bOn) { m_bExclusiveReadingEnabled = bOn; }
private:
  std::set<OdDbObjectId> m_RecomposeSet;
  OdSmartPtr<OdDbLayerStateManager> m_pLayerStateManager;
public:
  OdLyLayerFilterManagerPtr m_pLayerFilterManager;
  OdArray<OdDbDatabasePtr> m_XrefUndoCache; // xref database pointers cached for undo to work (this is the only place where they are stored)
  int m_nAnnotativeObjectCount;
  void increaseAnnotativeObjectCount();
  void decreaseAnnotativeObjectCount();
  OdDbDataLinkManager* m_pLinkManager;
  OdRxObjectPtr m_pRevisionControlData;
  int m_nIndexingMode;
private:
  //   put friend declaration here

//  !!!! TODO  when we will have the special function to access reactors, we have to remove this
  friend class OdDbBlockTableRecord;
  friend class OdOxOleLinkManagerImpl;
  friend class OdDbLayout;

  friend class OdDbDatabase;
  friend class OdDbSystemInternals;
  friend class OdDbStub;
  friend class OdDbObject;
  friend class OdDbObjectImpl;
 // friend class OdDbNullTransResident;
  friend class OdProxyStuff;

  friend class OdDbHostAppServices;
  friend class OdDwgRecover;
  friend class OdObjRecoverResolver;

  friend class OdDbFilerController;
  friend class OdDbAuditController;
  friend class OdDbUndoFiler;

  friend class OdDbDxfLoader;
  friend class OdDbDxfWriter;
  friend class OdDwgFileController;
  friend class OdDwgFileLoader;
  friend class OdDwgFileWriter;
  friend class OdDwgR12FileLoader;
  friend class OdDwgR12FileWriter;
  friend class OdObjLoadResolver;
  friend class OdDwgR18FileLoader;
  friend class OdDwgR18FileWriter;
  friend class OdDwgR24FileLoader;
  friend class OdDwgR24FileWriter;
  friend class OdDwgR27FileWriter;

  //  friend class OdDbSymUtil;
  friend class OdDbLayoutImpl;
  friend TOOLKIT_EXPORT void odAdjustLayouts(OdDbDatabase* pDb);

  friend class OdVectorizer;

  friend class OdDbVXTable;
  friend class OdDbBlockTable;
  friend class OdDbLinetypeTable;
  friend class OdDbLinetypeTableImpl;

  friend void odDbSetCurrentVersion(OdDbDatabase* pDb, OdDb::DwgVersion currentVer, OdDb::MaintReleaseVer currentMVer);
  friend TOOLKIT_EXPORT void odDbAppendClass(OdDbDatabase* pDb, OdRxClass* pClass, bool bForceAppend);
  friend void odDbAppendClass(OdDbDatabase* pDb, OdUInt32 nIndex, OdProxyClass* pClass);
  friend TOOLKIT_EXPORT void odDbRemoveAllClasses(OdDbDatabase* pDb);
  friend TOOLKIT_EXPORT OdRxClassPtr odDbGetClassAt(OdDbDatabase* pDb, const OdString& strClassName);
  friend void odDbTrackClass(OdDbDatabase* pDb, OdDbObject* pObject);
  friend void odDbForceObjectUndoOutput(OdDbDatabase* pDb);
  friend void odDbSaveTransactionContext(OdDbObject* pObj);
  friend void correctRootDictionary(OdDbDatabase* pDatabase);

  friend const OdDbObjectId& OdDbSymUtil::textStyleStandardId(const OdDbDatabase* pDb);
  friend const OdDbObjectId& OdDbSymUtil::dimStyleStandardId(const OdDbDatabase* pDb);
  friend void convertDatabaseTo(OdDbDatabase* pDb, OdDb::DwgVersion ver, OdDb::SaveType type, bool bLoading);

  friend void ResolveHeaderRoundTripForR14(OdDbDatabase *pDb);
  friend void HeaderRoundTripForR14(OdDbDatabase *pDb);

  friend TOOLKIT_EXPORT OdDbDatabaseSummaryInfoPtr oddbGetSummaryInfo(OdDbDatabase* pDb);
  friend TOOLKIT_EXPORT void oddbPutSummaryInfo(const OdDbDatabaseSummaryInfo* pInfo);
  friend void resolveSummaryInfoForR15(OdDbDatabase* pDb, OdDb::SaveType type/* = OdDb::kDwg*/);
  friend void createSummaryInfoForR15(OdDbDatabase* pDb, OdDb::SaveType type/* = OdDb::kDwg*/);

  friend TOOLKIT_EXPORT OdRxDictionaryIteratorPtr odDbGetDrawingClasses(OdDbDatabase& database);

  friend void odSetCurrentLayout(OdDbDatabase* pDb, const OdDbObjectId& layoutId, const OdDbObjectId& oldLayoutId);
  friend struct OdDbDatabaseTfPE;
  friend void writeXrefLoadUnloadUndo(OdDbBlockTableRecord* pBTR);

  friend class OdDbKey;

  friend OdUInt32 getGapsAmount(OdDbDatabase* pDb);
  friend OdRxClass* getClassByName(OdDbDatabase* pDb, const OdString& className);
  friend void oddbDecomposeForSave(OdDbDatabase *pDb, OdDb::DwgVersion ver, OdDb::SaveType type);
  friend void OdDbDatabase_readFile(OdDbDatabase* pDb, OdStreamBuf* pFileBuff, bool bPartial, OdDbAuditInfo *pAuditInfo, const OdPassword& password, bool bAllowCPConversion);
  friend void OdDbDatabase_writeFile(OdDbDatabase* pDb, OdStreamBuf* pFileBuff, OdDb::SaveType type, OdDb::DwgVersion ver, bool bSaveThumbnailImage, int dxfPrecision);
};   // end of class OdDbDatabaseImpl  definition


TOOLKIT_EXPORT OdDbLayoutPtr createLayout(OdDbDatabase* pDb, const OdString& newname, const OdDbObjectId blockTableRecId);
TOOLKIT_EXPORT void odAdjustLayouts(OdDbDatabase* pDb);
OdDbLayoutPtr createModelLayout(OdDbDatabase* pDb, const OdDbObjectId blockTableRecId);
OdDbLayoutPtr createPaperLayout(OdDbDatabase* pDb, const OdDbObjectId blockTableRecId, int tabOrder);
void odSetCurrentLayout(OdDbDatabase* pDb, const OdDbObjectId& layoutId, const OdDbObjectId& oldLayoutId);

void writeXrefLoadUnloadUndo(OdDbBlockTableRecord* pBTR);


#include "DbBaseDatabasePEImpl.h"

class OdDbDatabasePE : public OdBaseDatabasePEImpl
{
public:
  OdDbBaseHostAppServices* appServices(OdDbBaseDatabase* pDb) const
  {
    return OdDbDatabasePtr(pDb)->appServices();
  }
  OdString getFilename(OdDbBaseDatabase* pDb) const
  {
    return OdDbDatabasePtr(pDb)->getFilename();
  }
  virtual void startTransaction(OdDbBaseDatabase* pDb);
  virtual void abortTransaction(OdDbBaseDatabase* pDb);

  virtual OdResult startUndoRecord(OdDbBaseDatabase* pDb);
  virtual OdResult undo(OdDbBaseDatabase* pDb);

  virtual OdResult evaluateFields(OdDbBaseDatabase* pDb, int nContext);

  virtual OdGiDefaultContextPtr createGiContext(OdDbBaseDatabase* pDb) const;
  virtual void putNamedViewInfo(OdDbBaseDatabase* pDb, OdDbStub* layoutId, OdStringArray& names, OdGePoint3dArray& points);
  virtual OdBaseTextIteratorPtr createTextIterator(OdDbBaseDatabase* db, const OdChar* textString, int length, bool raw, const OdGiTextStyle* pTextStyle) const;
  virtual OdGsDevicePtr setupActiveLayoutViews(OdGsDevice* pDevice, OdGiDefaultContext* pGiCtx);
  virtual OdGsDevicePtr setupLayoutView(OdGsDevice* pDevice, OdGiDefaultContext* /*pDgnContext*/, OdDbStub* /*objectId*/);
  virtual void setupPalette(OdGsDevice* device, OdGiDefaultContext* giContext, OdDbStub* layoutId = 0, ODCOLORREF palBackground = ODRGBA(0,0,0,0));
  virtual OdDbStub* getNextViewForActiveLayout(OdGiDefaultContext* /*pDgnContext*/, OdDbStub* /*objectId*/);
  virtual void applyLayoutSettings(OdGsDCRect& clipBox, OdGsDevice* pDevice, OdDbBaseDatabase* db, OdUInt32 extentsFlags = kZeroFlags, OdUInt32 dpi = 72);
  virtual void zoomToExtents(const OdGsDCRect& outputRect, OdGsDevice* pDevice, OdDbBaseDatabase* db, OdGeBoundBlock3d& plotExtents, OdUInt32 extentsFlags = kZeroFlags, OdDbStub* objectId = NULL);
  virtual void loadPlotstyleTableForActiveLayout(OdGiDefaultContext* pDwgContext, OdDbBaseDatabase* db);
  virtual OdRxIteratorPtr layers(OdDbBaseDatabase* db) const;
  virtual OdRxIteratorPtr visualStyles(OdDbBaseDatabase* db) const;
  virtual OdDbStub* getVisualStyleId(OdDbBaseDatabase* db, const OdString& name) const;
  virtual void setCurrentLayout(OdDbBaseDatabase* db, const OdString& name);

  virtual OdRxIteratorPtr layouts(OdDbBaseDatabase* db) const;
  virtual bool getLineTypeById( OdDbBaseDatabase* db, OdDbStub* pLTypeId, OdGiLinetype& LType );
  virtual bool getTextStyleById( OdDbBaseDatabase* db, OdDbStub* idStyle, OdGiTextStyle& shapeInfo ); 
  virtual OdDbStub* findLayoutIdByViewport(OdDbBaseDatabase* db, OdDbStub* pViewportId);

  virtual OdDbStub* findLayoutNamed(OdDbBaseDatabase* db, const OdString& name); // dgn dwf export
  virtual OdDbStub* getFirstLayoutId(OdDbBaseDatabase* db); // dgn dwf export
  virtual OdTimeStamp getCreationTime(OdDbBaseDatabase* db); // dgn dwf export
  virtual OdTimeStamp getUpdateTime(OdDbBaseDatabase* db); // dgn dwf export
  virtual OdString getFingerPrintGuid(OdDbBaseDatabase* db); // dgn dwf export
  virtual OdString getVersionGuid(OdDbBaseDatabase* db); // dgn dwf export

  virtual int getUnits(OdDbBaseDatabase* db); // dgn dwf export
  virtual OdUnitsFormatter* baseFormatter(OdDbBaseDatabase* db); // dgn dwg common formatter base class
  virtual int getMeasurement(OdDbBaseDatabase* db);

  virtual OdDbStub* getId(const OdRxObject* obj) const;

  virtual OdDbStub *getObject(OdDbBaseDatabase* db, OdUInt64 handle);

  virtual OdCodePageId getCodePage(OdDbBaseDatabase* db);

  virtual OdDbStub* getModelBlockId(OdDbBaseDatabase* pDb);
  virtual OdDbStub* getPaperBlockId(OdDbBaseDatabase* pDb);
  virtual OdDbStub* currentLayoutId(OdDbBaseDatabase* pDb);
  virtual OdDbStub* xrefBlockId(OdDbBaseDatabase* pDb);

  virtual void setMultiThreadedRender(OdDbBaseDatabase* pDb, bool bOn);
  virtual bool isExclusiveReadingEnabled(const OdDbBaseDatabase* pDb);

  virtual bool isAProxy(OdRxObject* pDrw);
  virtual OdRxObjectPtr openObject(OdDbStub* pId);
  virtual bool upgradeOpen(OdRxObject* pObj);
  virtual void downgradeOpen(OdRxObject* pObj);
  virtual bool getAnnoScaleSet(OdDbStub* drawableId, OdGiAnnoScaleSet& res);
  virtual OdDbStub *getCurrentLongTransation(const OdDbBaseDatabase *pDb);

  virtual OdRxObjectPtr addDatabaseUnloadReactor(OdDbBaseDatabase* pDb, OdRxObject *pPrevReactor, DatabaseUnloadReactor *pReactorRedirect);
  virtual void removeDatabaseUnloadReactor(OdDbBaseDatabase* pDb, OdRxObject *pReactor);
  virtual OdResult faceConversionHelper(OdDbStub*& material, OdDbBaseDatabase* pSourceDb, OdDbBaseDatabase* pDestinationDb, const OdGiMaterialTraits* pMaterialTraits,
                                  const OdGiMapper* pMaterialMapper /*= 0*/, const OdCmEntityColor* pMaterialColor /*= 0*/);

  virtual OdInt16 getObscuredLtype(OdDbBaseDatabase& db, OdInt16& color) const ODRX_OVERRIDE;
};

class OdDbBaseLayerPEImpl : public OdBaseLayerPEImpl
{
public:
  OdString name(const OdRxObject* obj) const;
  virtual bool isOff(const OdRxObject*) const;
  virtual bool isFrozen(const OdRxObject*) const;
  virtual void setIsOff(OdRxObject*, bool) const;
  virtual void setIsFrozen(OdRxObject*, bool) const;
  virtual bool getLineType(OdRxObject* obj, OdGiLinetype& LType) const;
};

class OdDbBaseVisualStylePEImpl : public OdBaseVisualStylePEImpl
{
public:
  virtual OdString name(const OdRxObject* obj) const;
  virtual bool isInternal(const OdRxObject* obj) const;
};


class OdDbBaseMaterialPEImpl : public OdBaseMaterialPEImpl
{
public:
  virtual OdString name(const OdRxObject* obj) const;
  virtual bool isDefault(const OdRxObject* obj) const;
};

class OdDbBaseLayoutPEImpl : public OdBaseLayoutPEImpl
{
public:
  virtual OdString name(const OdRxObject*);
  virtual bool isModelLayout(const OdRxObject*);
  virtual bool printLineweights(const OdRxObject*);
  virtual bool showPlotStyles(const OdRxObject*);
  virtual OdString paperName(const OdRxObject*);
  virtual void getPaperSize(const OdRxObject*, double& paperWidth, double& paperHeight) const;
  virtual OdDbBaseLayoutPE::PlotRotation plotRotation(const OdRxObject*);
  virtual double getTopMargin(const OdRxObject*);
  virtual double getRightMargin(const OdRxObject*);
  virtual double getBottomMargin(const OdRxObject*);
  virtual double getLeftMargin(const OdRxObject*);
  virtual bool isOverallVPortErased(const OdRxObject*);
  virtual OdResult getGeomExtents(const OdRxObject*, OdGeExtents3d& ext);

  virtual bool useStandardScale(const OdRxObject*);
  virtual void getStdScale(const OdRxObject*, double& scale);
  virtual void getCustomPrintScale(const OdRxObject*, double& numerator, double& denominator);
  virtual int plotType(const OdRxObject*);
  virtual OdString getPlotViewName(const OdRxObject*);
  virtual void getPlotWindowArea(const OdRxObject*, double& xmin, double& ymin, double& xmax, double& ymax);
  virtual void getPlotOrigin(const OdRxObject*, double& x, double& y);
  virtual void getPlotPaperSize(const OdRxObject*, double& paperWidth, double& paperHeight);
  virtual int plotPaperUnits(const OdRxObject*);

  virtual OdDbStub* getBlockId(const OdRxObject*) const;
  virtual bool scalePSLinetypes(const OdRxObject*) const;
  virtual bool getApproxExtents(const OdRxObject*, OdGePoint3d& extMin, OdGePoint3d& extMax) const;

  virtual OdResult getStdScaleType(const OdRxObject*, OdDbBaseLayoutPE::StdScaleType&) const;
};

class OdDbSetBasePlotSettingsPEImpl : public OdSetBasePlotSettingsPEImpl
{
public:
  virtual OdResult setPlotCfgName(OdRxObject* pPlotSetObj, const OdString &plotCfgName);
  virtual OdResult setPlotLayoutFlags(OdRxObject* pPlotSetObj, OdInt16 flags);
  virtual OdResult setMargins(OdRxObject* pPlotSetObj, double left, double bottom, double right, double top);
  virtual OdResult setPlotPaperSize(OdRxObject* pPlotSetObj, double paperWidth, double paperHeight);
  virtual OdResult setMediaName(OdRxObject* pPlotSetObj, OdString mediaName);
  virtual OdResult setOrigin(OdRxObject* pPlotSetObj, const OdGePoint2d &origin);
  virtual OdResult setPlotPaperUnits(OdRxObject* pPlotSetObj, OdDbBaseLayoutPE::PlotPaperUnits units);
  virtual OdResult setPlotRotation(OdRxObject* pPlotSetObj, OdDbBaseLayoutPE::PlotRotation plotRotation);
  virtual OdResult setPlotType(OdRxObject* pPlotSetObj, OdDbBaseLayoutPE::PlotType plotType);
  virtual OdResult setPlotWindowArea(OdRxObject* pPlotSetObj, double xmin, double ymin, double xmax, double ymax);
  virtual OdResult setPlotView(OdRxObject* pPlotSetObj, OdDbStub* plotViewId);
  virtual OdResult setPrintScale(OdRxObject* pPlotSetObj, double numerator, double denominator);
  virtual OdResult setStyleSheet(OdRxObject* pPlotSetObj, OdString styleSheet);
  virtual OdResult setStdScaleType(OdRxObject* pPlotSetObj, OdDbBaseLayoutPE::StdScaleType scaleType);
  virtual OdResult setScaleFactor(OdRxObject* pPlotSetObj, double dScaleFactor);
};

struct OdDbBaseBlockPEImpl : OdDbBaseBlockPE
{
  virtual bool isBlockReferenceAdded(OdRxObject *pBlock) const;

  virtual bool isFromExternalReference(const OdRxObject *pBlock) const;
  virtual OdDbBaseDatabase *xrefDatabase(const OdRxObject *pBlock) const;

  virtual OdDbStub *getLayoutId(const OdRxObject *pBlock) const;

  virtual bool isAnonymous( const OdRxObject *pBlock ) const;
  virtual OdString getName( const OdRxObject *pBlock ) const;
};

struct OdDbBaseBlockRefPEImpl : OdDbBaseBlockRefPE
{
  virtual OdDbStub *blockId(const OdRxObject *pBlockRef) const;
  virtual OdGeMatrix3d blockTransform(const OdRxObject *pBlockRef) const;

  virtual OdRxIteratorPtr newAttribIterator(const OdRxObject *pBlockRef, bool bSkipErased = true) const;
  virtual bool isAttribute(const OdRxObject *pAttrib) const;

  virtual bool isGeneric(const OdRxObject *pBlockRef) const;
  virtual bool isMInsert(const OdRxObject *pBlockRef) const;
  virtual bool isBasic(const OdRxObject *pBlockRef) const;
  virtual bool isSelfReferential(const OdRxObject *pEntity) const;
};

struct OdDbBaseSortEntsPEImpl : OdDbBaseSortEntsPE
{
  virtual OdDbStub *blockId(const OdRxObject *pSortents) const;
};

struct OdDbBaseLongTransactionPEImpl : OdDbBaseLongTransactionPE
{
  virtual OdDbStub *destinationBlock(const OdRxObject *pLT) const;
  virtual OdDbBaseDatabase *getDatabase(const OdRxObject *pLT) const;

  virtual bool workSetHas(const OdRxObject *pLT, OdDbStub *pId) const;
  virtual OdRxIteratorPtr newWorkSetIterator(const OdRxObject *pLT, bool incRemoved = false, bool incSecondary = false) const;
};

struct OdDbBaseHatchPEImpl : OdDbBaseHatchPE
{
  virtual int numLoops(const OdRxObject* pHatch) const;
  virtual OdInt32 loopTypeAt(const OdRxObject* pHatch, int loopIndex) const;
  virtual void getLoopAt(const OdRxObject* pHatch, int loopIndex, OdArray<OdGeCurve2d*>& edgePtrs) const;
  virtual void getLoopAt(const OdRxObject* pHatch, int loopIndex, OdGePoint2dArray& vertices, OdGeDoubleArray& bulges) const;
  virtual OdDbBaseHatchPE::HatchStyle hatchStyle(const OdRxObject* pHatch) const;
  virtual bool isGradient(const OdRxObject* pHatch) const;
  virtual bool isSolidFill(const OdRxObject* pHatch) const;
  virtual bool isReallyHatch(const OdRxObject* pHatch) const;
};

// ODA_MT_DB_BEGIN
#ifdef ODA_ST_DB

#define TD_AUTOLOCK_ID(ObjectId,DbImpl)
#define TD_AUTOLOCK_PTR(ObjectPtr,Db)

#else

class OdMutexAutoLockId
{
public:
  OdMutexAutoLockId(OdDbStub* id, OdDbDatabaseImpl* pDbImpl)
    : m_id(0)
  {
    if (id->flags(kOdDbIdNoAutoLock))
      return;
    if (!odThreadsCounter() || (pDbImpl && (pDbImpl->multiThreadedMode() != OdDb::kMTRendering)))
      return;
    ODA_ASSERT(id && pDbImpl);

    m_id = (OdDbStubExt*)id;
    m_pool = pDbImpl->mutexPool();
    m_mutex = m_pool->get(id);
    m_mutex->lock();
  }
  ~OdMutexAutoLockId()
  { 
    if (m_id)
    {
      m_mutex->unlock();
      m_pool->release(m_id);
    }
  }
private:
  OdDbStub*    m_id;
  OdMutex*     m_mutex;
  OdMutexPool* m_pool;
};

#define TD_AUTOLOCK_ID(ObjectId,DbImpl) OdMutexAutoLockId autoLock(ObjectId,DbImpl);

class OdMutexAutoLockPtr
{
public:
  OdMutexAutoLockPtr(void* ptr, OdDbDatabase* pDb)
    : m_ptr(0)
  {
    if (!odThreadsCounter())
      return;
    if (pDb && (OdDbDatabaseImpl::getImpl(pDb)->multiThreadedMode() == OdDb::kMTRendering))
    {
      ODA_ASSERT(ptr);
      m_ptr = ptr;
      m_pool = OdDbDatabaseImpl::getImpl(pDb)->mutexPool();
      m_mutex = m_pool->get(ptr);
      m_mutex->lock();
    }
  }
  ~OdMutexAutoLockPtr()
  { 
    unlock();
  }
  void unlock()
  {
    if (m_ptr)
    {
      m_mutex->unlock();
      m_pool->release(m_ptr);
      m_ptr = NULL;
    }
  }
private:
  void*        m_ptr;
  OdMutex*     m_mutex;
  OdMutexPool* m_pool;
};

#define TD_AUTOLOCK_PTR(ObjectPtr,Db) OdMutexAutoLockPtr autoLock(ObjectPtr,Db);

#endif
// ODA_MT_DB_END

// IS_DIFF_UNDO_ENABLED() support
TOOLKIT_EXPORT bool oddbIsDiffUndoEnabled();
TOOLKIT_EXPORT void oddbSetDiffUndoEnabled(bool val);
#define IS_DIFF_UNDO_ENABLED() oddbIsDiffUndoEnabled()

#endif //_ODDBDATABASEIMPL_INCLUDED_
