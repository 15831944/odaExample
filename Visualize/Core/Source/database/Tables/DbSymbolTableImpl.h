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

#ifndef _OD_DB_SYMBOLTABLE_IMPL_
#define _OD_DB_SYMBOLTABLE_IMPL_

#include "../DbSystemInternals.h"
#include "DbSymbolTable.h"
#include "BaseDictionaryImpl.h"
#include "DbSymUtl.h"
#include "../Objects/DbObjectImpl.h"


extern void odClearTable(OdTvDbSymbolTable*);

class OdTvSymbolTableItem
{
  OdTvDbObjectId m_id;
public:
  OdTvSymbolTableItem() {}
  OdTvSymbolTableItem(const OdTvDbObjectId& id) : m_id(id) {}

  OdString getKey() const { return OdTvDbSymUtil::getSymbolName(m_id); }
  void setKey(const OdString& key);
  const OdTvDbObjectId& getVal() const { return m_id; }
  void setVal(const OdTvDbObjectId& id) { m_id = id; }
  bool isErased() const
  {
    if (m_id.objectLeftOnDisk()) // #9898 Fixed iteration in partial open mode as object can be erased during loading
      m_id.openObject();
    return m_id.isErased();
  }
};



// Maybe it will be templates
class OdTvDbSymbolTableImpl
  : public OdBaseDictionaryImpl<OdString, OdTvDbObjectId, OdString::lessnocase, OdTvSymbolTableItem>
  , public OdTvDbObjectImpl
{
  static OdTvDbSymbolTableImpl* getImpl(const OdTvDbSymbolTable *pObj)
  { return (OdTvDbSymbolTableImpl*)OdTvDbSystemInternals::getImpl(pObj);}

protected:
  using OdBaseDictionaryImpl<OdString, OdTvDbObjectId, OdString::lessnocase, OdTvSymbolTableItem>::clear;
  using OdBaseDictionaryImpl<OdString, OdTvDbObjectId, OdString::lessnocase, OdTvSymbolTableItem>::needSorting;
public:
  TOOLKIT_EXPORT virtual OdTvDbObjectId getByIndex(OdInt16 nIndex) const;
  TOOLKIT_EXPORT virtual OdInt16 getIndexById(const OdTvDbObjectId& id) const;
  TOOLKIT_EXPORT virtual OdString getNameByIndex(OdInt16 nIndex) const;
  TOOLKIT_EXPORT virtual OdInt16 getIndexByName(const OdString& name) const;

  // Called for each database object during conversion
  // pObj - interface of object
  TOOLKIT_EXPORT void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  TOOLKIT_EXPORT void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  TOOLKIT_EXPORT void truncateXRefName(OdTvDbObjectIdArray& xrefIds);

  TOOLKIT_EXPORT void audit (OdTvDbAuditInfo* pAuditInfo);
  TOOLKIT_EXPORT virtual bool needNameUnicity(OdTvDbSymbolTableRecord* pRec = 0);

  static void removeRecord(OdTvDbSymbolTable* pTable, const OdTvDbObjectId& recId);
  static void needSorting(OdTvDbSymbolTablePtr pTable)
  {
    ODA_ASSERT(pTable.get());
    OdTvDbSymbolTableImpl::getImpl(pTable)->needSorting();
  }
  static void removeDependentRecords(OdTvDbObjectId tableId, OdTvDbDatabase* owner);
protected:
  bool findRecord(const OdString& name, sorted_iterator& iter, bool getErased) const;
  OdTvDbObjectId getRecordAt(const OdString& name, bool getErased) const;
  OdResult resetRecordName(const OdString& oldKey, const OdString& newKey, const OdTvDbObjectId& recId);
  TOOLKIT_EXPORT virtual void sort() const;
  class DictPr
  {
    OdArray<OdString> m_Names;
  public:
    DictPr(ItemArray& items)
    {
      // Using items.at(i).getKey() can produce record loading and adding other records to table.
      // (e.g. OdTvDbLeaderImpl::composeForLoad() can create additional block).
      // As a result a size of items array will be changed, so do not use temporary variable for items.size() value.
      m_Names.reserve(items.size());
      for (unsigned i = 0; i < items.size(); ++i)
      {
        Item item = items.at(i);
        m_Names.push_back(item.getKey());
      }
    }

    bool operator ()(OdUInt32 id, const OdString& key) const
    {
      return m_Names.at(id).iCompare(key) < 0;
    }

    bool operator ()(const OdString& key, OdUInt32 id) const
    {
      return key.iCompare(m_Names.at(id)) < 0;
    }

    bool operator () (OdUInt32 id1, OdUInt32 id2) const
    {
      return m_Names.at(id1).iCompare(m_Names.at(id2)) < 0;
    }
  };

  void makeRecordFirst(const OdTvDbObjectId& id);
  TOOLKIT_EXPORT virtual bool isValidRecordClass(OdRxClass* pClass) const;
  int getOwnRecordsNumber(bool bVISRETAIN);
private:

  virtual const OdString getEntryDxfName() const { return OD_T("TV_DXF_SYMBOL_TABLE_RECORD");}// Must be overridden in derived classes

  friend class OdTvDbSymbolTable;
  friend class OdTvDbSymbolTableRecord;
  friend class OdTvDbSymbolTableRecordImpl;
  friend class OdTvDbDatabaseImpl;
  friend void odClearTable(OdTvDbSymbolTable*);
  friend class OdTvDbEntityImpl;
  friend class OdTvDbLayerIndexImpl;
  friend class OdTvDwgRecover;
  friend class OdTvDwgR12FileLoader;
  friend class OdTvDbUtils;
  friend struct OdTvDbSymbolTableTfPE;
};

class OdTvDbSymbolTableIteratorImpl
  : public OdBaseIteratorImpl<OdTvDbSymbolTableImpl::ItemArray, OdString, OdTvDbObjectId>
{
public:
  OdTvDbSymbolTableIteratorImpl();

  virtual void start(bool atBeginning = true, bool skipDeleted = true);
  virtual bool done() const;
  virtual OdTvDbObjectId getRecordId() const;
  virtual OdTvDbSymbolTableRecordPtr getRecord(OdDb::OpenMode openMode, bool openErasedRec) const;

  virtual void step(bool forward = true, bool skipDeleted = true);
  virtual void seek(const OdTvDbSymbolTableRecord* pRecord);
  virtual void seek(const OdTvDbObjectId& id);
};

#endif // ifndef _OD_DB_SYMBOLTABLE_IMPL_
