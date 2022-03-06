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

class OdDbBlockTableImpl;
class OdBlob;

// OdDbBlockTableRecord status flags:
// BlockReferenceAdded - Brics #7184.
//   This bit is set in addReferenceId() and cleared when closing OdDbBlockTableRecord
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

// Define this outside of OdDbBlockTableRecordImpl to prevent compiler errors on mac.
class RefsContainer : public OdArray<OdDbObjectId, OdMemoryAllocator<OdDbObjectId> > {};

class OdDbBlockTableRecordImpl : public OdDbSymbolTableRecordImpl, public OdEntityContainer
{
  static OdDbBlockTableRecordImpl* getImpl(const OdDbBlockTableRecord *pObj)
  { return (OdDbBlockTableRecordImpl*)OdDbSystemInternals::getImpl(pObj);}

  enum
  {
    kAnonymous     = 1,
    kHasattributes = 2,
    kXref          = 4,
    kOverlaid      = 8,
  };

  const OdDbObjectImpl* dbObjectImpl() const { return this; }
  OdEntityContainer* entContainer() { return this; }

  DEFINE_FLAGS(OdUInt16, m_nStatusBits, STATUS_FLAGS)
  DEFINE_FLAGS_VALUE(newStatusFlagsV,   STATUS_FLAGS)
  DEFINE_FLAGS_MASK (newStatusFlagsM,   STATUS_FLAGS)
  STATUS_FLAGS(FLAG_DEF_ACCESSORS)

  OdDbHardPointerId     m_LayoutId;
  OdGePoint3d           m_BasePoint;
  OdString              m_strDescription;
  OdString              m_NameWithIndex;
  OdBinaryData          m_BitmapPreview;

  typedef RefsContainer::iterator RefsIterator;
  typedef RefsContainer::const_iterator ConstRefsIterator;
  typedef std::multimap<OdUInt32, std::pair<OdDbBlockTableRecord*, OdEntityContainer::iterator> > MultimapIndexEntity;
  RefsContainer         m_BlkRefs;

  OdDbHardOwnershipId   m_BlockBeginId;
  OdDbHardOwnershipId   m_BlockEndId;

  OdDb::FileDependency  m_strXRefPath;
  OdDbObjectIdArray     m_NestedXrefs;
  OdDbDatabasePtr       m_pXRefDb;
  int                   m_XrefReferenceCount; // keeps track of the references, if one nested xref is loaded by different parents
  void*                 m_blockChangeIterator;

  // save to xdictionary
  void saveBlockTableRecordData();
  // load from xdictionary
  void readBlockTableRecordData();

  OdInt16               m_nInsertUnits;
  OdUInt8               m_nBlockScaling;
  bool                  m_bExplodable;

  void getNameWithIndex(const OdString& sName, OdString& sNameWithIndex, OdDbBlockTableImpl* pOwnerImpl, int index = -1);
  void adjustNameWithIndex(OdDbBlockTableImpl* pOwnerImpl, int index);
  static bool verifyNameWithIndex (OdString& sSrcName, OdString& sDstName, OdDb::DwgVersion ver);
  void assumeOwnershipOf(OdDbBlockTableRecord* pBlock, OdArray<OdDbEntityPtr>& ents, OdArray<OdDbBlockTableRecordPtr>& owners, const MultimapIndexEntity* pMMapIt, OdInt32Array& posEnts, bool hasAttrs);
  OdResult assumeOwnershipOf(OdDbBlockTableRecord* pBlock, OdDbObjectIdArray entitiesToMove);

  void setBlockInsertUnits(OdDbObject *pObj);
  OdDb::UnitsValue getBlockInsertUnits(OdDbObject *pObj) const;

  // OdEntityContainer overridden
  virtual void loadAc15Content(OdDbDwgFiler* pFiler);
  virtual OdDbObjectId entNext(const OdDbObjectId& prev);

protected:
  // 17.12.2004 GU made this method virtual to update sortentstable on
  // subDeepClone
  virtual OdDbObjectId appendEntity(OdDbEntity* pEntity);

public:
  OdDbBlockTableRecordImpl();
  ~OdDbBlockTableRecordImpl();

  static void adjustNameWithIndex(OdDbBlockTableRecord* pRec, OdDbBlockTableImpl* pOwnerImpl, int index);

  void setAnonymous(bool value) { SETBIT(m_Flags, kAnonymous, value); }
  bool isAnonymous() const { return GETBIT(m_Flags, kAnonymous); }

  void setHasAttributes(bool value) {	SETBIT(m_Flags, kHasattributes, value); }
  bool hasAttributes() const { return GETBIT(m_Flags, kHasattributes); }

  void setXRef(bool value) { SETBIT(m_Flags, kXref, value); }
  bool isXRef() const {	return GETBIT(m_Flags, kXref); }

  void setOverlaid(bool value) { SETBIT(m_Flags, kOverlaid, value); }
  bool isOverlaid() const {	return GETBIT(m_Flags, kOverlaid); }

  static void removeReferenceId(const OdDbObjectId& idBlkRec, const OdDbObjectId& idRef);
  TOOLKIT_EXPORT static void removeReferenceId(OdDbBlockTableRecord* pThis, const OdDbObjectId& idRef);
  TOOLKIT_EXPORT static bool addReferenceId(OdDbBlockTableRecord* pThis, const OdDbObjectId& idRef);
  // for audit: check if passed blockId is valid and the block reference is present in the reference list (add if not)
  TOOLKIT_EXPORT static bool verifyReferenceId(OdDbObjectId blockId, OdDbObjectId refId);
  static void clearContainer(OdDbBlockTableRecord* pThis);
  static void writeXrefBindUndo(OdDbBlockTableRecord* pThis);
  static void setXRefDatabase(OdDbBlockTableRecord* pThis, OdDbDatabase* pXrefDb);

  static void getNestedXrefIds(const OdDbBlockTableRecord* pBlkRec, OdDbObjectIdArray& nestedXrefsIds);
  static void addNestedXrefId(OdDbBlockTableRecord* pBlkRec, OdDbObjectId idRef);
  static void removeNestedXrefId(OdDbBlockTableRecord* pBlkRec, OdDbObjectId idRef);
  static void clearNestedXrefIds(OdDbBlockTableRecord* pBlkRec);

  static bool hasBlockReferenceIds(OdDbBlockTableRecord* pBlkRec);
  static bool isBlockReferenceAdded(OdDbBlockTableRecord* pBlkRec); //Brics: returns kBlockReferenceAdded flag for the block, see above.

  void* blockChangeIterator() { return m_blockChangeIterator; }
  void setBlockChangeIterator(void* bcit);

  // !!! To use only from DXF loading !!! (& R12 DWG)
  TOOLKIT_EXPORT void setNameFromDXF(OdString name, OdDb::DwgVersion ver);

  void audit (OdDbAuditInfo* pAuditInfo);
  virtual bool isValidSubentityClass(OdRxClass* pClass) const;
  virtual void verifyName(OdDbAuditInfo* pAuditInfo);
  virtual void verifyXrefDependence(OdDbAuditInfo* pAuditInfo);

  OdString getName() const;
  void setName(const OdString& name);
  void setKeyName(const OdString& name);

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
// ODA_MT_DBIO_BEGIN
  TOOLKIT_EXPORT static void composeForLoadMT(OdDbBlockTableRecord* pThis, OdDb::SaveType format, OdDb::DwgVersion version);
  TOOLKIT_EXPORT static void endMTLoading(OdDbBlockTableRecord* pThis, OdDb::SaveType format, OdDb::DwgVersion version);
// ODA_MT_DBIO_END

  TOOLKIT_EXPORT void restoreDynamicBlockName(OdDbBlockTable* pBT);
  virtual bool mangleName(
    OdDb::DeepCloneType cloneType,
    OdDb::DuplicateRecordCloning drc,
    const OdString& recName,
    unsigned index = 0,
    const OdString& xrefName = OdString::kEmpty);
  virtual void mergeXrefTable(
    OdDbIdPair& idPair,
    OdDbSymbolTable* pTable,
    OdDbIdMapping& idMap,
    OdDbSymbolTableRecord* pRec);

  virtual void recvPropagateModify(OdDbObject* pOwner, const OdDbObject* pSubObj);
  virtual void setModified(bool v);

  static inline OdResult verifyBlock(const OdDbBlockTableRecord* pBlock);
  static void renamePaperSpace(OdDbBlockTableRecord* pBlock, const OdString& sNewNameWithIndex);
  void updateSortEntsTable(OdDbSortentsTable* pSETable = NULL);
  bool isAnnotative() const;

  enum GeomExtFlags
  {
    kIgnoreFrozen = (1 << 0),
    kIgnoreOff    = (1 << 1)
  };
  OdResult getGeomExtents(const OdDbBlockTableRecord* pThis, OdGeExtents3d& extents, OdUInt32 extFlags = 0);
  OdResult geomExtentsBestFit(const OdDbBlockTableRecord* pThis, OdGeExtents3d& extents, OdUInt32 extFlags = 0,
                              const OdGeMatrix3d& parentXform = OdGeMatrix3d::kIdentity);
  int verifyName(const OdString& strName, bool bLeadAsteriskAllowed = false) const;

  friend class OdDbBlockTable;
  friend class OdDbBlockTableImpl;
  friend class OdDbBlockTableRecord;
  friend class OdDbBlockBegin;
  friend class OdDbBlockReference;
  friend class OdDbDxfLoader;
  friend class OdDwgR12FileLoader;
  friend class OdDwgR12FileWriter;
  friend class OdDbSymbolTableRecordImpl;
  friend class OdDbDatabase;
  friend class OdDbXrefGraph;
  friend class OdDbAttributeDefinition;
  friend class OdDbXRefMan;
  friend class OdDbXRefManExt;
  friend class OdDbBlockIndexController;
  friend class OdApLongTransactionManagerImpl;
  friend class OdDbBlockRepresentationContext;
  friend class OdDbObject;
  friend void oddbXrefDetach(OdDbBlockTableRecord*);
  friend void xrefNestedXrefBlocks(OdDbIdMapping*, OdDbBlockTableRecord*);
  friend OdResult xrefBind(OdDbBlockTableRecord* pBTR, bool bInsertBind, OdList<OdDbObjectId>& nestedXrefIds);
  friend OdDbObjectId insert(OdDbDatabase*, const OdString&, OdDbObjectId, bool);
  friend OdResult loadAllXrefs(const OdDbObjectIdArray& xrefs, bool bVerify);
  friend class BlockOperationStatus;
  friend bool isAnnotativeBlock(OdDbBlockTableRecord* owner);
  friend struct OdDbBlockTableRecordTfPE;
  friend void writeXrefLoadUnloadUndo(OdDbBlockTableRecord* pBTR);
  friend void clearReferencesToUnloadedBase(OdDbDatabase* pDb, OdDbDatabase* pXref);
  friend class OdDbViewport;
  friend class OdDbPoint;
};


class BlockOperationStatus
{
public:
  BlockOperationStatus(int flag)
    : m_pBlockImpl(0)
    , m_flag(flag)
  {}
  bool isReentered(OdDbBlockTableRecordImpl* pBlockImpl)
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
  OdDbBlockTableRecordImpl* m_pBlockImpl;
  int m_flag;
};


inline
OdResult OdDbBlockTableRecordImpl::verifyBlock(const OdDbBlockTableRecord* pBlock)
{
  OdResult res = eOk;
  if (pBlock->isFromExternalReference() || pBlock->isFromOverlayReference())
  {
    OdDbBlockTableRecordImpl* pImpl = OdDbBlockTableRecordImpl::getImpl(pBlock);
    if ( !pImpl->isXrefUnloaded()
      && !pImpl->isXrefUnresolved()
      && !pImpl->isXrefResolved()
      && !pImpl->isXrefFileNotFound() )
    {
      res = OdDbXRefMan::load(const_cast<OdDbBlockTableRecord*>(pBlock));
    }
  }
  return res;
}

inline
bool OdDbBlockTableRecordImpl::isBlockReferenceAdded(OdDbBlockTableRecord* pBlkRec)
{
  return OdDbBlockTableRecordImpl::getImpl(pBlkRec)->isBlockReferenceAdded();
}

#endif //_ODDBBLOCKTABLERECORDIMPL_INCLUDED_
