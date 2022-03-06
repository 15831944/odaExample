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

#include "ApLongTransactions.h"
#include "DbDatabaseImpl.h"
#include "DbLongTransaction.h"

struct OdTvDbTransactionWrapper
{
  OdTvDbDatabasePtr m_pDb;
  OdTvDbTransactionWrapper( OdTvDbDatabase* db )
  {
    if( db )
    {
      m_pDb = db;
      db->startTransaction();
    }
  }
  void endTransaction()
  {
    if( !m_pDb.isNull() )
    {
      m_pDb->endTransaction();
      m_pDb = 0;
    }
  }
  ~OdTvDbTransactionWrapper()
  {
    if( !m_pDb.isNull() )
      m_pDb->abortTransaction();
  }
};

void odtvdbSetLongTransactionForDatabase(OdTvDbDatabase* pDb, OdTvDbObjectId lt);
class OdTvDbLongTransactionImpl;
struct OdTvApLongTransactionDatabaseReactor : OdTvDbDatabaseReactor
{
  virtual void objectAppended(const OdTvDbDatabase* pDb, const OdTvDbObject* pObject) ODRX_OVERRIDE;
};

class OdTvApLongTransactionManagerImpl : public OdTvApLongTransactionManager
{
  OdStaticRxObject<OdTvApLongTransactionDatabaseReactor> m_DbReactor;
  OdArray<OdTvApLongTransactionReactor*> m_reactors;
  OdArray<OdRxClass*> m_filters;
  OdResult abortTransaction(OdResult res, OdTvDbLongTransaction* lt)
  {
    lt->database()->removeReactor(&m_DbReactor);
    for (unsigned int j = 0; j < m_reactors.size(); ++j)
      m_reactors[j]->abortLongTransaction(*lt);
    odtvdbSetLongTransactionForDatabase(lt->database(), 0);
    lt->erase();
    return res;
  }
  struct OdTvDbIdPairCompare
  {
    bool operator()(const OdTvDbIdPair& p1, const OdTvDbIdPair& p2)const{return p1.key() < p2.key();}
  };

public:  // for AIX
  typedef std::set<OdTvDbIdPair, OdTvDbIdPairCompare> IdMap;

  struct CombinedIdMappingIterator : public OdTvDbIdMappingIter
  {
    IdMap* m_pMap;
    IdMap::const_iterator m_pIt;
    virtual void start(){m_pIt = m_pMap->begin();}
    virtual void getMap(OdTvDbIdPair& idPair){idPair = *m_pIt;}
    virtual void next(){if (m_pIt != m_pMap->end()) ++m_pIt;}
    virtual bool done(){return m_pIt == m_pMap->end();}
  };

private:

  // This is id mapping between the objects inside one block
  class CombinedIdMapping : public OdStaticRxObject<OdTvDbIdMapping>
  {
    IdMap m_map;
    OdTvDbDatabase* m_pDb;
    OdDb::DeepCloneType m_dct;
    OdDb::DuplicateRecordCloning m_drc;
  public:
    CombinedIdMapping(OdTvDbDatabase* pDb, OdDb::DeepCloneType dct, OdDb::DuplicateRecordCloning drc) 
      : m_pDb(pDb), m_dct(dct), m_drc(drc){}

    virtual void assign(const OdTvDbIdPair& idPair)
    {
      if (!m_map.insert(idPair).second)
      {
        m_map.erase(idPair);
        m_map.insert(idPair);
      }
    }

    virtual bool compute(OdTvDbIdPair& idPair) const
    {
      IdMap::const_iterator i = m_map.find(idPair);
      if (i == m_map.end())
        return false;
      idPair = *i;
      return true;
    }
    virtual bool del(const OdTvDbObjectId& key)
    {
      IdMap::iterator i = m_map.find(key);
      if (i != m_map.end())
      {
        m_map.erase(i);
        return true;
      }
      else
        return false;
    }
    virtual OdTvDbIdMappingIterPtr newIterator()
    {
      OdTvDbIdMappingIterPtr p = OdRxObjectImpl<CombinedIdMappingIterator>::createObject();
      ((CombinedIdMappingIterator*)p.get())->m_pMap = &m_map;
      ((CombinedIdMappingIterator*)p.get())->m_pIt = m_map.begin();
      return p;
    }
    virtual OdTvDbDatabase* destDb() const { return m_pDb; }
    virtual void setDestDb(OdTvDbDatabase* pDb) { m_pDb = pDb; }
    virtual OdTvDbDatabase* origDb() const { return m_pDb; }
    virtual OdTvDbObjectId insertingXrefBlockId() const {return OdTvDbObjectId::kNull;}
    virtual OdDb::DeepCloneType deepCloneContext() const { return m_dct; }
    virtual OdDb::DuplicateRecordCloning duplicateRecordCloning() const { return m_drc; }
  };
  // clone workset to original block
  void cloneWorkSet(OdTvDbLongTransaction* lt, const OdTvDbObjectIdArray& toClone);
  // swap cloned workset with original objects
  void swapClonedWorkset(OdArray<OdTvDbIdPair>& oldMapping, OdTvDbLongTransactionImpl* pImpl);
  // check if all the objects were removed
  static bool allObjectsRemoved(OdTvDbLongTransactionImpl* pImpl);
  static void saveIdMapping(OdTvDbIdMapping* m, OdArray<OdTvDbIdPair>& oldMapping);
public:
  OdTvApLongTransactionManagerImpl();
  virtual OdResult checkOut(OdTvDbObjectId& transId, OdTvDbObjectIdArray& objList, OdTvDbObjectId toBlock, 
    OdTvDbIdMapping& errorMap, OdTvDbObjectId lockBlkRef = OdTvDbObjectId::kNull);
  virtual OdResult checkIn(OdTvDbObjectId transId, OdTvDbIdMapping& errorMap, bool keepObjs = false);
  virtual OdResult abortLongTransaction(OdTvDbObjectId transId, bool keepObjs = false);
  virtual void addReactor(OdTvApLongTransactionReactor*);
  virtual void removeReactor(OdTvApLongTransactionReactor*);
  virtual OdResult addClassFilter (OdRxClass* );
  virtual bool isFiltered (OdRxClass* ) const;
  virtual OdTvDbObjectId currentLongTransactionFor(const OdTvDbDatabase* pDb) const;
};
