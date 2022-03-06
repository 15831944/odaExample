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

class TOOLKIT_EXPORT OdObjectContainer : protected OdLinkedArray<OdDbObjectId, OdMemoryAllocator<OdDbObjectId> >
{
protected:
  OdObjectContainer(OdUInt32 pageSize = 0x10);
  ~OdObjectContainer();
  virtual const OdDbObjectImpl* dbObjectImpl() const = 0;
  void freeNonDBROList();

public:
  // Make DBRO during adding object to database
  // 
  virtual void makeDBROList();
  void clearEntityList()
  {
    freeNonDBROList();
    OdLinkedArray<OdDbObjectId, OdMemoryAllocator<OdDbObjectId> >::clear();
    m_pCurrent = OdDbObjectIteratorPtr();
  }
  unsigned numEntries() const
  {
    return OdLinkedArray<OdDbObjectId, OdMemoryAllocator<OdDbObjectId> >::size();
  }
  OdDbObjectId appendObject(OdDbObject* pEntity);
  bool isDBROContent() const { return m_isDBROContent; }

protected:
  OdDbObjectIteratorPtr m_pCurrent;
  bool isDBROObject() const { return dbObjectImpl()->isDBRO(); }
  inline bool isFullyLoaded() const { return m_firstSubEntId.isNull(); }
  bool m_isDBROContent;
  OdDbObjectId m_firstSubEntId;
  OdDbObjectId m_lastSubEntId;

  // Methods call makeDBROList() during adding object to database
  friend void OdDbObjectImpl::handOverTo(OdDbObject*, OdDbObject*, bool, bool, bool);
  friend OdDbObjectId OdDbDatabase::addOdDbObject(OdDbObject*, OdDbObjectId, OdDbHandle);
};

class TOOLKIT_EXPORT OdEntityContainer : public OdObjectContainer
{
protected:
  OdEntityContainer(OdUInt32 pageSize = 0x10);
public:
  // Content accessors
  // 
  OdDbObjectIteratorPtr newIterator(bool bForward = true, bool bSkipDeleted = true) const;
  OdDbObjectId append(OdDbEntity* pEntity);
  OdDbObjectId insertAt(const OdDbEntity* pPrev, OdDbEntity* pEntity);
  OdDbObjectId insertAt(const OdDbEntity* pPrev, OdDbEntityPtrArray &pEntityArr);
  OdDbObjectId firstSubEntId() const;
  OdInt32 getEntityPosition(OdDbObjectId entId) const;
  void insertEntityAt(OdInt32 pos, OdDbObjectId entId);

  // Dwg/dxf filling
  // 
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  virtual void dxfOutFields(OdDbDxfFiler* pFiler) const;

  // Audit
  // 
  void audit(OdDbAuditInfo* pAuditInfo);
  virtual bool isValidSubentityClass(OdRxClass* pClass) const = 0;

  // Setting variable values for subentities
  // 
  virtual void setSubentsColorIndex(OdUInt16 colorInd);
  virtual void setSubentsColor(const OdCmColor& color);
  virtual void setSubentsTransparency(const OdCmTransparency& trans);
  virtual void setSubentsDatabaseDefaults(OdDbDatabase *pDb);
  virtual void setSubentsColorId(OdDbObjectId clrId);
  virtual void setSubentsLayer(OdDbObjectId layer);
  virtual void setSubentsLinetype(OdDbObjectId l);
  virtual void setSubentsMaterial(OdDbObjectId m);
  virtual void setSubentsVisualStyle(OdDbObjectId visualStyleId, OdDbEntity::VisualStyleType vstype);
  virtual void setSubentsPlotStyleName(OdDb::PlotStyleNameType PSNType, OdDbObjectId newId);
  virtual void setSubentsMaterialMapper(const OdGiMapper* mapper);
  virtual void setSubentsLinetypeScale(double linetypeScale);
  virtual void setSubentsVisibility(OdDb::Visibility visibility);
  virtual void setSubentsLineWeight(OdDb::LineWeight lineWeight);
  virtual void setSubentsPropertiesFrom(const OdDbEntity* pSource);

  // Compose/decompose subentities
  //
  virtual void composeSubents(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void decomposeSubents(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  void copyFrom(OdEntityContainer* pSrc);
  void setIdsFrom(OdEntityContainer* pSrc);

  // Forces loading of partialy loaded container for R15 dwg
  //
  inline void verifyContent(OdDbAuditInfo* pAuditInfo = 0) const;

  // Apply partial undo for handOverTo() operation
  //
  void writePartialUndo(OdDbDwgFiler* pFiler) const;
  void readPartialUndo(OdDbDwgFiler* pFiler);

  virtual OdDbObjectId entNext(const OdDbObjectId& prev);

  // Support i/o entities from R15 container
  //
  virtual void loadAc15Content(OdDbDwgFiler* pFiler);
  const OdDbObjectId& firstAc15SubEntId() { return m_firstSubEntId; }
private:
  void loadAc15List(OdDbDwgFiler* pFiler);
  void saveAc15List(OdDbDwgFiler* pFiler) const;

  // Support partial loading of R15 dwg files
  //
  void closeInput(OdDbAuditInfo* pAuditInfo);
  void closeInput();
  inline void clearAc15List();

protected:
  virtual OdDbObjectId appendEntity(OdDbEntity* pEntity);
  void remove(OdDbObjectId ent);
  void remove(const OdEntityContainer::iterator& pIt);
  OdDbObjectId removeLast()
  {
    m_pCurrent = OdDbObjectIteratorPtr();
    return OdLinkedArray<OdDbObjectId, OdMemoryAllocator<OdDbObjectId> >::removeLast();
  }

private:
  // Access to container implementation
  friend class OdDbObjectIteratorImpl;
};

class TOOLKIT_EXPORT OdEntitySeqEndContainer : public OdEntityContainer
{
protected:
  OdEntitySeqEndContainer(OdUInt32 pageSize = 8);

  static void recvPropagateModify(OdDbObject* pOwner, const OdDbObject* pSubObj);
public:

  // SequenceEnd support
  //
  OdDbObjectId& seqEndId() { return m_SeqendId; }
  const OdDbObjectId& getSeqEndId() const { return m_SeqendId; }
  OdDbSequenceEndPtr openSequenceEnd(OdDb::OpenMode openMode)
  { 
    return getSeqEndId().openObject(openMode).get();
  }
  virtual void addSeqEndIfNotPresent(); // to override in DbBlockReferenceImpl

  // Overridden from OdEntityContainer
  //
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  void dxfOut(OdDbDxfFiler* pFiler) const;
  virtual void audit(OdDbAuditInfo* pAuditInfo);
  virtual bool seqendShouldPresent();
  virtual OdDbObjectId entNext(const OdDbObjectId& prev);
  
  virtual void setSubentsColorIndex(OdUInt16 colorInd);
  virtual void setSubentsColor(const OdCmColor& color);
  virtual void setSubentsTransparency(const OdCmTransparency& trans);
  virtual void setSubentsDatabaseDefaults(OdDbDatabase *pDb);
  virtual void setSubentsColorId(OdDbObjectId clrId);
  virtual void setSubentsLayer(OdDbObjectId layer);
  virtual void setSubentsLinetype(OdDbObjectId l);
  virtual void setSubentsMaterial(OdDbObjectId m);
  virtual void setSubentsVisualStyle(OdDbObjectId visualStyleId, OdDbEntity::VisualStyleType vstype);
  virtual void setSubentsPlotStyleName(OdDb::PlotStyleNameType PSNType, OdDbObjectId newId);
  virtual void setSubentsMaterialMapper(const OdGiMapper* mapper);
  virtual void setSubentsLinetypeScale(double linetypeScale);
  virtual void setSubentsVisibility(OdDb::Visibility visibility);
  virtual void setSubentsLineWeight(OdDb::LineWeight lineWeight);
  virtual void setSubentsPropertiesFrom(const OdDbEntity* pSource);

  virtual void composeSubents(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  virtual void decomposeSubents(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);

  OdDbHardOwnershipId m_SeqendId;
};

//----------------------------------------------------------
//
// OdEntityContainer inline implementation
//
//----------------------------------------------------------

inline
void OdEntityContainer::verifyContent(OdDbAuditInfo* pAuditInfo) const
{
  if (!isFullyLoaded())
  {
    if (pAuditInfo)
      const_cast<OdEntityContainer*>(this)->closeInput(pAuditInfo);
    else
      const_cast<OdEntityContainer*>(this)->closeInput();
  }
}

inline
void OdEntityContainer::clearAc15List()
{
  m_pCurrent = OdDbObjectIteratorPtr();
  m_firstSubEntId.setNull();
  m_lastSubEntId.setNull();;
}

#endif //_ODAENTITYCONTAINER_INCLUDED
