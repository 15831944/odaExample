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

#ifndef _ODDBBLOCKTABLERECORDIMPL_INCLUDED_
#define _ODDBBLOCKTABLERECORDIMPL_INCLUDED_

#include "../DbSystemInternals.h"
#include "DbBlockTableRecord.h"
#include "DbSymbolTableRecordImpl.h"
#include "../Entities/EntityContainer.h"
#include "../FileDependency.h"
#include "XRefMan.h"
#include "OdList.h"

class OdTvDbBlockTableImpl;
class OdBlob;

// OdTvDbBlockTableRecord status flags:
// BlockReferenceAdded - Brics #7184.
//   This bit is set in addReferenceId() and cleared when closing OdTvDbBlockTableRecord
//   thus it is active during notifications only.
//   Is is used in GS module to distinguish block modification event from the case when
//   its reference was added and no other changes happened.
// DrawReentered - used to avoid infinite loops in worldDraw() for cyclic block references.
// XrefReentered - used to avoid infinite loops in xref processing for cyclic block references.
#define STATUS_FLAGS(FLAG_DEF) \
  FLAG_DEF(XrefUnresolved,      0) \
  FLAG_DEF(XrefUnloaded,        0) \
  FLAG_DEF(XrefFileNotFound,    0) \
  FLAG_DEF(NeedCorrection,      1) \
  FLAG_DEF(BlockReferenceAdded, 0) \
  FLAG_DEF(DrawReentered,       0) \
  FLAG_DEF(ExtentsReentered,    0) \
  FLAG_DEF(XrefReentered,       0) \
  FLAG_DEF(SortentsNeedUpdate,  0) \
  FLAG_DEF(SortentsInvalidate,  0) 


// Flag accessors
#define FLAG_DEF_ACCESSORS(name, v) \
  bool is##name() const     { return GETBIT(m_nStatusBits, name##_M);} \
  void set##name(bool val)  { SETBIT(m_nStatusBits, name##_M, val);}

// Define this outside of OdTvDbBlockTableRecordImpl to prevent compiler errors on mac.
class RefsContainer : public OdArray<OdTvDbObjectId, OdMemoryAllocator<OdTvDbObjectId> > {};

class OdTvDbBlockTableRecordImpl : public OdTvDbSymbolTableRecordImpl, public OdTvEntityContainer
{
  static OdTvDbBlockTableRecordImpl* getImpl(const OdTvDbBlockTableRecord *pObj)
  { return (OdTvDbBlockTableRecordImpl*)OdTvDbSystemInternals::getImpl(pObj);}

  enum
  {
    kAnonymous     = 1,
    kHasattributes = 2,
    kXref          = 4,
    kOverlaid      = 8,
  };

  const OdTvDbObjectImpl* dbObjectImpl() const { return this; }
  OdTvEntityContainer* entContainer() { return this; }

  DEFINE_FLAGS(OdUInt16, m_nStatusBits, STATUS_FLAGS)
  DEFINE_FLAGS_VALUE(newStatusFlagsV,   STATUS_FLAGS)
  DEFINE_FLAGS_MASK (newStatusFlagsM,   STATUS_FLAGS)
  STATUS_FLAGS(FLAG_DEF_ACCESSORS)

  OdTvDbHardPointerId     m_LayoutId;
  OdGePoint3d           m_BasePoint;
  OdString              m_strDescription;
  OdString              m_NameWithIndex;
  OdBinaryData          m_BitmapPreview;

  typedef RefsContainer::iterator RefsIterator;
  typedef RefsContainer::const_iterator ConstRefsIterator;
  RefsContainer         m_BlkRefs;

  OdTvDbHardOwnershipId   m_BlockBeginId;
  OdTvDbHardOwnershipId   m_BlockEndId;

  OdDb::TvFileDependency  m_strXRefPath;
  OdTvDbObjectIdArray     m_NestedXrefs;
  OdTvDbDatabasePtr       m_pXRefDb;
  int                   m_XrefReferenceCount; // keeps track of the references, if one nested xref is loaded by different parents
  void*                 m_blockChangeIterator;

  // save to xdictionary
  void saveBlockTableRecordData();
  // load from xdictionary
  void readBlockTableRecordData();

  OdInt16               m_nInsertUnits;
  OdUInt8               m_nBlockScaling;
  bool                  m_bExplodable;

  void getNameWithIndex(const OdString& sName, OdString& sNameWithIndex, OdTvDbBlockTableImpl* pOwnerImpl, int index = -1);
  void adjustNameWithIndex(OdTvDbBlockTableImpl* pOwnerImpl, int index);
  static bool verifyNameWithIndex (OdString& sSrcName, OdString& sDstName, OdDb::DwgVersion ver);
  void assumeOwnershipOf(OdTvDbBlockTableRecord* pBlock, OdArray<OdTvDbEntityPtr>& ents, OdArray<OdTvDbBlockTableRecordPtr>& owners, OdInt32Array& posEnts, bool hasAttrs);

  void setBlockInsertUnits(OdTvDbObject *pObj);
  OdDb::UnitsValue getBlockInsertUnits(OdTvDbObject *pObj) const;

  // OdTvEntityContainer overridden
  virtual void loadAc15Content(OdTvDbDwgFiler* pFiler);
  virtual OdTvDbObjectId entNext(const OdTvDbObjectId& prev);

protected:
  // 17.12.2004 GU made this method virtual to update sortentstable on
  // subDeepClone
  virtual OdTvDbObjectId appendEntity(OdTvDbEntity* pEntity);

public:
  OdTvDbBlockTableRecordImpl();
  ~OdTvDbBlockTableRecordImpl();

  static void adjustNameWithIndex(OdTvDbBlockTableRecord* pRec, OdTvDbBlockTableImpl* pOwnerImpl, int index);

  void setAnonymous(bool value) { SETBIT(m_Flags, kAnonymous, value); }
  bool isAnonymous() const { return GETBIT(m_Flags, kAnonymous); }

  void setHasAttributes(bool value) {	SETBIT(m_Flags, kHasattributes, value); }
  bool hasAttributes() const { return GETBIT(m_Flags, kHasattributes); }

  void setXRef(bool value) { SETBIT(m_Flags, kXref, value); }
  bool isXRef() const {	return GETBIT(m_Flags, kXref); }

  void setOverlaid(bool value) { SETBIT(m_Flags, kOverlaid, value); }
  bool isOverlaid() const {	return GETBIT(m_Flags, kOverlaid); }

  static void removeReferenceId(const OdTvDbObjectId& idBlkRec, const OdTvDbObjectId& idRef);
  TOOLKIT_EXPORT static void removeReferenceId(OdTvDbBlockTableRecord* pThis, const OdTvDbObjectId& idRef);
  TOOLKIT_EXPORT static bool addReferenceId(OdTvDbBlockTableRecord* pThis, const OdTvDbObjectId& idRef);
  // for audit: check if passed blockId is valid and the block reference is present in the reference list (add if not)
  TOOLKIT_EXPORT static bool verifyReferenceId(OdTvDbObjectId blockId, OdTvDbObjectId refId);
  static void clearContainer(OdTvDbBlockTableRecord* pThis);
  static void writeXrefBindUndo(OdTvDbBlockTableRecord* pThis);
  static void setXRefDatabase(OdTvDbBlockTableRecord* pThis, OdTvDbDatabase* pXrefDb);

  static void getNestedXrefIds(const OdTvDbBlockTableRecord* pBlkRec, OdTvDbObjectIdArray& nestedXrefsIds);
  static void addNestedXrefId(OdTvDbBlockTableRecord* pBlkRec, OdTvDbObjectId idRef);
  static void removeNestedXrefId(OdTvDbBlockTableRecord* pBlkRec, OdTvDbObjectId idRef);
  static void clearNestedXrefIds(OdTvDbBlockTableRecord* pBlkRec);

  static bool hasBlockReferenceIds(OdTvDbBlockTableRecord* pBlkRec);
  static bool isBlockReferenceAdded(OdTvDbBlockTableRecord* pBlkRec); //Brics: returns kBlockReferenceAdded flag for the block, see above.

  void* blockChangeIterator() { return m_blockChangeIterator; }
  void setBlockChangeIterator(void* bcit);

  // !!! To use only from DXF loading !!! (& R12 DWG)
  TOOLKIT_EXPORT void setNameFromDXF(OdString name, OdDb::DwgVersion ver);

  void audit (OdTvDbAuditInfo* pAuditInfo);
  virtual bool isValidSubentityClass(OdRxClass* pClass) const;
  virtual void verifyName(OdTvDbAuditInfo* pAuditInfo);
  virtual void verifyXrefDependence(OdTvDbAuditInfo* pAuditInfo);

  OdString getName() const;
  void setName(const OdString& name);
  void setKeyName(const OdString& name);

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
// ODA_MT_DBIO_BEGIN
  TOOLKIT_EXPORT static void composeForLoadMT(OdTvDbBlockTableRecord* pThis, OdDb::SaveType format, OdDb::DwgVersion version);
  TOOLKIT_EXPORT static void endMTLoading(OdTvDbBlockTableRecord* pThis, OdDb::SaveType format, OdDb::DwgVersion version);
// ODA_MT_DBIO_END

  TOOLKIT_EXPORT void restoreDynamicBlockName(OdTvDbBlockTable* pBT);
  virtual bool mangleName(
    OdDb::DeepCloneType cloneType,
    OdDb::DuplicateRecordCloning drc,
    const OdString& recName,
    unsigned index = 0,
    const OdString& xrefName = OdString::kEmpty);
  virtual void mergeXrefTable(
    OdTvDbIdPair& idPair,
    OdTvDbSymbolTable* pTable,
    OdTvDbIdMapping& idMap,
    OdTvDbSymbolTableRecord* pRec);

  virtual void recvPropagateModify(OdTvDbObject* pOwner, const OdTvDbObject* pSubObj);
  virtual void setModified(bool v);

  static inline OdResult verifyBlock(const OdTvDbBlockTableRecord* pBlock);
  static void renamePaperSpace(OdTvDbBlockTableRecord* pBlock, const OdString& sNewNameWithIndex);
  void updateSortEntsTable(OdTvDbSortentsTable* pSETable = NULL);
  bool isAnnotative() const;

  enum GeomExtFlags
  {
    kIgnoreFrozen = (1 << 0),
    kIgnoreOff    = (1 << 1)
  };
  OdResult getGeomExtents(const OdTvDbBlockTableRecord* pThis, OdGeExtents3d& extents, OdUInt32 extFlags = 0);
  OdResult geomExtentsBestFit(const OdTvDbBlockTableRecord* pThis, OdGeExtents3d& extents, OdUInt32 extFlags = 0,
                              const OdGeMatrix3d& parentXform = OdGeMatrix3d::kIdentity);
  int verifyName(const OdString& strName, bool bLeadAsteriskAllowed = false) const;

  friend class OdTvDbBlockTable;
  friend class OdTvDbBlockTableImpl;
  friend class OdTvDbBlockTableRecord;
  friend class OdTvDbBlockBegin;
  friend class OdTvDbBlockReference;
  friend class OdTvDbDxfLoader;
  friend class OdTvDwgR12FileLoader;
  friend class OdTvDwgR12FileWriter;
  friend class OdTvDbSymbolTableRecordImpl;
  friend class OdTvDbDatabase;
  friend class OdTvDbXrefGraph;
  friend class OdTvDbAttributeDefinition;
  friend class OdTvDbXRefMan;
  friend class OdTvDbXRefManExt;
  friend class OdTvDbBlockIndexController;
  friend class OdTvApLongTransactionManagerImpl;
  friend class OdTvDbBlockRepresentationContext;
  friend class OdTvDbObject;
  friend void odtvdbXrefDetach(OdTvDbBlockTableRecord*);
  friend void xrefNestedXrefBlocks(OdTvDbIdMapping*, OdTvDbBlockTableRecord*);
  friend OdResult xrefBind(OdTvDbBlockTableRecord* pBTR, bool bInsertBind, OdList<OdTvDbObjectId>& nestedXrefIds);
  friend OdTvDbObjectId insert(OdTvDbDatabase*, const OdString&, OdTvDbObjectId, bool);
  friend OdResult loadAllXrefs(const OdTvDbObjectIdArray& xrefs, bool bVerify);
  friend class BlockOperationStatus;
  friend bool isAnnotativeBlock(OdTvDbBlockTableRecord* owner);
  friend struct OdTvDbBlockTableRecordTfPE;
  friend void writeXrefLoadUnloadUndo(OdTvDbBlockTableRecord* pBTR);
  friend void clearReferencesToUnloadedBase(OdTvDbDatabase* pDb, OdTvDbDatabase* pXref);
  friend class OdTvDbViewport;
};


class BlockOperationStatus
{
public:
  BlockOperationStatus(int flag)
    : m_pBlockImpl(0)
    , m_flag(flag)
  {}
  bool isReentered(OdTvDbBlockTableRecordImpl* pBlockImpl)
  {
    if (pBlockImpl->getFlags(m_flag) != 0)
    {
      return true;
    }
    m_pBlockImpl = pBlockImpl;
    pBlockImpl->setFlags(m_flag, m_flag);
    return false;
  }
  ~BlockOperationStatus()
  {
    if (m_pBlockImpl)
    {
      m_pBlockImpl->setFlags(m_flag, 0);
    }
  }
private:
  OdTvDbBlockTableRecordImpl* m_pBlockImpl;
  int m_flag;
};


inline
OdResult OdTvDbBlockTableRecordImpl::verifyBlock(const OdTvDbBlockTableRecord* pBlock)
{
  OdResult res = eOk;
  if (pBlock->isFromExternalReference() || pBlock->isFromOverlayReference())
  {
    OdTvDbBlockTableRecordImpl* pImpl = OdTvDbBlockTableRecordImpl::getImpl(pBlock);
    if ( !pImpl->isXrefUnloaded()
      && !pImpl->isXrefUnresolved()
      && !pImpl->isXrefResolved()
      && !pImpl->isXrefFileNotFound() )
    {
      res = OdTvDbXRefMan::load(const_cast<OdTvDbBlockTableRecord*>(pBlock));
    }
  }
  return res;
}

inline
bool OdTvDbBlockTableRecordImpl::isBlockReferenceAdded(OdTvDbBlockTableRecord* pBlkRec)
{
  return OdTvDbBlockTableRecordImpl::getImpl(pBlkRec)->isBlockReferenceAdded();
}

#endif //_ODDBBLOCKTABLERECORDIMPL_INCLUDED_
