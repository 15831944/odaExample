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

#ifndef _ODAENTITYCONTAINER_INCLUDED
#define _ODAENTITYCONTAINER_INCLUDED

#include "DbDatabase.h"
#include "DbEntity.h"
#include "DbSequenceEnd.h"
#include "OdLinkedArray.h"
#include "DbObjectIterator.h"
#include "../Objects/DbObjectImpl.h"

class TOOLKIT_EXPORT OdTvObjectContainer : protected OdLinkedArray<OdTvDbObjectId, OdMemoryAllocator<OdTvDbObjectId> >
{
protected:
  OdTvObjectContainer(OdUInt32 pageSize = 0x10);
  ~OdTvObjectContainer();
  virtual const OdTvDbObjectImpl* dbObjectImpl() const = 0;
  void freeNonDBROList();

public:
  // Make DBRO during adding object to database
  // 
  virtual void makeDBROList();
  void clearEntityList()
  {
    freeNonDBROList();
    OdLinkedArray<OdTvDbObjectId, OdMemoryAllocator<OdTvDbObjectId> >::clear();
    m_pCurrent = OdTvDbObjectIteratorPtr();
  }
  unsigned numEntries() const
  {
    return OdLinkedArray<OdTvDbObjectId, OdMemoryAllocator<OdTvDbObjectId> >::size();
  }
  OdTvDbObjectId appendObject(OdTvDbObject* pEntity);
  bool isDBROContent() const { return m_isDBROContent; }

protected:
  OdTvDbObjectIteratorPtr m_pCurrent;
  bool isDBROObject() const { return dbObjectImpl()->isDBRO(); }
  inline bool isFullyLoaded() const { return m_firstSubEntId.isNull(); }
  bool m_isDBROContent;
  OdTvDbObjectId m_firstSubEntId;
  OdTvDbObjectId m_lastSubEntId;

  // Methods call makeDBROList() during adding object to database
  friend void OdTvDbObjectImpl::handOverTo(OdTvDbObject*, OdTvDbObject*, bool, bool, bool);
  friend OdTvDbObjectId OdTvDbDatabase::addOdTvDbObject(OdTvDbObject*, OdTvDbObjectId, OdDbHandle);
};

class TOOLKIT_EXPORT OdTvEntityContainer : public OdTvObjectContainer
{
protected:
  OdTvEntityContainer(OdUInt32 pageSize = 0x10);
public:
  // Content accessors
  // 
  OdTvDbObjectIteratorPtr newIterator(bool bForward = true, bool bSkipDeleted = true) const;
  OdTvDbObjectId append(OdTvDbEntity* pEntity);
  OdTvDbObjectId insertAt(const OdTvDbEntity* pPrev, OdTvDbEntity* pEntity);
  OdTvDbObjectId insertAt(const OdTvDbEntity* pPrev, OdTvDbEntityPtrArray &pEntityArr);
  OdTvDbObjectId moveAfter( const OdTvDbEntity* pPrev, OdTvDbEntity* pEntity );
  OdTvDbObjectId moveAfterLast( OdTvDbEntity* pEntity );
  OdTvDbObjectId firstSubEntId() const;
  OdInt32 getEntityPosition(OdTvDbObjectId entId) const;
  void insertEntityAt(OdInt32 pos, OdTvDbObjectId entId);

  // Dwg/dxf filling
  // 
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  // Audit
  // 
  void audit(OdTvDbAuditInfo* pAuditInfo);
  virtual bool isValidSubentityClass(OdRxClass* pClass) const = 0;

  // Setting variable values for subentities
  // 
  virtual void setSubentsColorIndex(OdUInt16 colorInd);
  virtual void setSubentsColor(const OdTvCmColor& color);
  virtual void setSubentsTransparency(const OdTvCmTransparency& trans);
  virtual void setSubentsDatabaseDefaults(OdTvDbDatabase *pDb);
  virtual void setSubentsColorId(OdTvDbObjectId clrId);
  virtual void setSubentsLayer(OdTvDbObjectId layer);
  virtual void setSubentsLinetype(OdTvDbObjectId l);
  virtual void setSubentsMaterial(OdTvDbObjectId m);
  virtual void setSubentsVisualStyle(OdTvDbObjectId visualStyleId, OdTvDbEntity::VisualStyleType vstype);
  virtual void setSubentsPlotStyleName(OdDb::PlotStyleNameType PSNType, OdTvDbObjectId newId);
  virtual void setSubentsMaterialMapper(const OdGiMapper* mapper);
  virtual void setSubentsLinetypeScale(double linetypeScale);
  virtual void setSubentsVisibility(OdDb::Visibility visibility);
  virtual void setSubentsLineWeight(OdDb::LineWeight lineWeight);
  virtual void setSubentsPropertiesFrom(const OdTvDbEntity* pSource);

  // Compose/decompose subentities
  //
  virtual void composeSubents(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void decomposeSubents(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void copyFrom(OdTvEntityContainer* pSrc);
  void setIdsFrom(OdTvEntityContainer* pSrc);

  // Forces loading of partialy loaded container for R15 dwg
  //
  inline void verifyContent(OdTvDbAuditInfo* pAuditInfo = 0) const;

  // Apply partial undo for handOverTo() operation
  //
  void writePartialUndo(OdTvDbDwgFiler* pFiler) const;
  void readPartialUndo(OdTvDbDwgFiler* pFiler);

  virtual OdTvDbObjectId entNext(const OdTvDbObjectId& prev);

  // Support i/o entities from R15 container
  //
  virtual void loadAc15Content(OdTvDbDwgFiler* pFiler);
  const OdTvDbObjectId& firstAc15SubEntId() { return m_firstSubEntId; }
private:
  void loadAc15List(OdTvDbDwgFiler* pFiler);
  void saveAc15List(OdTvDbDwgFiler* pFiler) const;

  // Support partial loading of R15 dwg files
  //
  void closeInput(OdTvDbAuditInfo* pAuditInfo);
  void closeInput();
  inline void clearAc15List();

protected:
  virtual OdTvDbObjectId appendEntity(OdTvDbEntity* pEntity);
  void remove(OdTvDbObjectId ent);
  OdTvDbObjectId removeLast()
  {
    m_pCurrent = OdTvDbObjectIteratorPtr();
    return OdLinkedArray<OdTvDbObjectId, OdMemoryAllocator<OdTvDbObjectId> >::removeLast();
  }

private:
  // Access to container implementation
  friend class OdTvDbObjectIteratorImpl;
};

class TOOLKIT_EXPORT OdTvEntitySeqEndContainer : public OdTvEntityContainer
{
protected:
  OdTvEntitySeqEndContainer(OdUInt32 pageSize = 8);

  static void recvPropagateModify(OdTvDbObject* pOwner, const OdTvDbObject* pSubObj);
public:

  // SequenceEnd support
  //
  OdTvDbObjectId& seqEndId() { return m_SeqendId; }
  const OdTvDbObjectId& getSeqEndId() const { return m_SeqendId; }
  OdTvDbSequenceEndPtr openSequenceEnd(OdDb::OpenMode openMode)
  { 
    return getSeqEndId().openObject(openMode).get();
  }
  virtual void addSeqEndIfNotPresent(); // to override in DbBlockReferenceImpl

  // Overridden from OdTvEntityContainer
  //
  OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  void dxfOut(OdTvDbDxfFiler* pFiler) const;
  virtual void audit(OdTvDbAuditInfo* pAuditInfo);
  virtual bool seqendShouldPresent();
  virtual OdTvDbObjectId entNext(const OdTvDbObjectId& prev);
  
  virtual void setSubentsColorIndex(OdUInt16 colorInd);
  virtual void setSubentsColor(const OdTvCmColor& color);
  virtual void setSubentsTransparency(const OdTvCmTransparency& trans);
  virtual void setSubentsDatabaseDefaults(OdTvDbDatabase *pDb);
  virtual void setSubentsColorId(OdTvDbObjectId clrId);
  virtual void setSubentsLayer(OdTvDbObjectId layer);
  virtual void setSubentsLinetype(OdTvDbObjectId l);
  virtual void setSubentsMaterial(OdTvDbObjectId m);
  virtual void setSubentsVisualStyle(OdTvDbObjectId visualStyleId, OdTvDbEntity::VisualStyleType vstype);
  virtual void setSubentsPlotStyleName(OdDb::PlotStyleNameType PSNType, OdTvDbObjectId newId);
  virtual void setSubentsMaterialMapper(const OdGiMapper* mapper);
  virtual void setSubentsLinetypeScale(double linetypeScale);
  virtual void setSubentsVisibility(OdDb::Visibility visibility);
  virtual void setSubentsLineWeight(OdDb::LineWeight lineWeight);
  virtual void setSubentsPropertiesFrom(const OdTvDbEntity* pSource);

  virtual void composeSubents(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void decomposeSubents(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  OdTvDbHardOwnershipId m_SeqendId;
};

//----------------------------------------------------------
//
// OdTvEntityContainer inline implementation
//
//----------------------------------------------------------

inline
void OdTvEntityContainer::verifyContent(OdTvDbAuditInfo* pAuditInfo) const
{
  if (!isFullyLoaded())
  {
    if (pAuditInfo)
      const_cast<OdTvEntityContainer*>(this)->closeInput(pAuditInfo);
    else
      const_cast<OdTvEntityContainer*>(this)->closeInput();
  }
}

inline
void OdTvEntityContainer::clearAc15List()
{
  m_pCurrent = OdTvDbObjectIteratorPtr();
  m_firstSubEntId.setNull();
  m_lastSubEntId.setNull();;
}

#endif //_ODAENTITYCONTAINER_INCLUDED
