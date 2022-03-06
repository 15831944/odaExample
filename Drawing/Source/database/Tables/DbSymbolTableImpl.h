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


extern void odClearTable(OdDbSymbolTable*);

class OdSymbolTableItem
{
  OdDbObjectId m_id;
public:
  OdSymbolTableItem() {}
  OdSymbolTableItem(const OdDbObjectId& id) : m_id(id) {}

  OdString getKey() const { return OdDbSymUtil::getSymbolName(m_id); }
  void setKey(const OdString& key);
  const OdDbObjectId& getVal() const { return m_id; }
  void setVal(const OdDbObjectId& id) { m_id = id; }
  bool isErased() const
  {
    if (m_id.objectLeftOnDisk()) // #9898 Fixed iteration in partial open mode as object can be erased during loading
      m_id.openObject();
    return m_id.isErased();
  }
};



// Maybe it will be templates
class OdDbSymbolTableImpl
  : public OdBaseDictionaryImpl<OdString, OdDbObjectId, OdString::lessnocase, OdSymbolTableItem>
  , public OdDbObjectImpl
{
  static OdDbSymbolTableImpl* getImpl(const OdDbSymbolTable *pObj)
  { return (OdDbSymbolTableImpl*)OdDbSystemInternals::getImpl(pObj);}

protected:
  using OdBaseDictionaryImpl<OdString, OdDbObjectId, OdString::lessnocase, OdSymbolTableItem>::clear;
  using OdBaseDictionaryImpl<OdString, OdDbObjectId, OdString::lessnocase, OdSymbolTableItem>::needSorting;
public:
  TOOLKIT_EXPORT virtual OdDbObjectId getByIndex(OdInt16 nIndex) const;
  TOOLKIT_EXPORT virtual OdInt16 getIndexById(const OdDbObjectId& id) const;
  TOOLKIT_EXPORT virtual OdString getNameByIndex(OdInt16 nIndex) const;
  TOOLKIT_EXPORT virtual OdInt16 getIndexByName(const OdString& name) const;

  // Called for each database object during conversion
  // pObj - interface of object
  TOOLKIT_EXPORT void decomposeForSave(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  TOOLKIT_EXPORT void composeForLoad(OdDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  TOOLKIT_EXPORT void truncateXRefName(OdDbObjectIdArray& xrefIds);

  TOOLKIT_EXPORT void audit (OdDbAuditInfo* pAuditInfo);
  TOOLKIT_EXPORT virtual bool needNameUnicity(OdDbSymbolTableRecord* pRec = 0);

  static void removeRecord(OdDbSymbolTable* pTable, const OdDbObjectId& recId);
  static void needSorting(OdDbSymbolTablePtr pTable)
  {
    ODA_ASSERT(pTable.get());
    OdDbSymbolTableImpl::getImpl(pTable)->needSorting();
  }
  static void removeDependentRecords(OdDbObjectId tableId, OdDbDatabase* owner);
protected:
  bool findRecord(const OdString& name, sorted_iterator& iter, bool getErased) const;
  OdDbObjectId getRecordAt(const OdString& name, bool getErased) const;
  OdResult resetRecordName(const OdString& oldKey, const OdString& newKey, const OdDbObjectId& recId);
  TOOLKIT_EXPORT virtual void sort() const;
  class DictPr
  {
    OdArray<OdString> m_Names;
  public:
    DictPr(ItemArray& items)
    {
      // Using items.at(i).getKey() can produce record loading and adding other records to table.
      // (e.g. OdDbLeaderImpl::composeForLoad() can create additional block).
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

  void makeRecordFirst(const OdDbObjectId& id);
  TOOLKIT_EXPORT virtual bool isValidRecordClass(OdRxClass* pClass) const;
  int getOwnRecordsNumber(bool bVISRETAIN);
private:

  virtual const OdString getEntryDxfName() const { return OD_T("SYMBOL_TABLE_RECORD");}// Must be overridden in derived classes

  friend class OdDbSymbolTable;
  friend class OdDbSymbolTableRecord;
  friend class OdDbSymbolTableRecordImpl;
  friend class OdDbDatabaseImpl;
  friend void odClearTable(OdDbSymbolTable*);
  friend class OdDbEntityImpl;
  friend class OdDbLayerIndexImpl;
  friend class OdDwgRecover;
  friend class OdDwgR12FileLoader;
  friend class OdDbUtils;
  friend struct OdDbSymbolTableTfPE;
};

class OdDbSymbolTableIteratorImpl
  : public OdBaseIteratorImpl<OdDbSymbolTableImpl::ItemArray, OdString, OdDbObjectId>
{
public:
  OdDbSymbolTableIteratorImpl();

  virtual void start(bool atBeginning = true, bool skipDeleted = true);
  virtual bool done() const;
  virtual OdDbObjectId getRecordId() const;
  virtual OdDbSymbolTableRecordPtr getRecord(OdDb::OpenMode openMode, bool openErasedRec) const;

  virtual void step(bool forward = true, bool skipDeleted = true);
  virtual void seek(const OdDbSymbolTableRecord* pRecord);
  virtual void seek(const OdDbObjectId& id);
};

#endif // ifndef _OD_DB_SYMBOLTABLE_IMPL_
