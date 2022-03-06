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

void oddbSetLongTransactionForDatabase(OdDbDatabase* pDb, OdDbObjectId lt);
class OdDbLongTransactionImpl;
struct OdApLongTransactionDatabaseReactor : OdDbDatabaseReactor
{
  virtual void objectAppended(const OdDbDatabase* pDb, const OdDbObject* pObject) ODRX_OVERRIDE;
};

class OdApLongTransactionManagerImpl : public OdApLongTransactionManager
{
  OdStaticRxObject<OdApLongTransactionDatabaseReactor> m_DbReactor;
  OdArray<OdApLongTransactionReactor*> m_reactors;
  OdArray<OdRxClass*> m_filters;
  OdResult abortTransaction(OdResult res, OdDbLongTransaction* lt)
  {
    lt->database()->removeReactor(&m_DbReactor);
    for (unsigned int j = 0; j < m_reactors.size(); ++j)
      m_reactors[j]->abortLongTransaction(*lt);
    oddbSetLongTransactionForDatabase(lt->database(), 0);
    lt->erase();
    return res;
  }
  struct OdDbIdPairCompare
  {
    bool operator()(const OdDbIdPair& p1, const OdDbIdPair& p2)const{return p1.key() < p2.key();}
  };

public:  // for AIX
  typedef std::set<OdDbIdPair, OdDbIdPairCompare> IdMap;

  struct CombinedIdMappingIterator : public OdDbIdMappingIter
  {
    IdMap* m_pMap;
    IdMap::const_iterator m_pIt;
    virtual void start(){m_pIt = m_pMap->begin();}
    virtual void getMap(OdDbIdPair& idPair){idPair = *m_pIt;}
    virtual void next(){if (m_pIt != m_pMap->end()) ++m_pIt;}
    virtual bool done(){return m_pIt == m_pMap->end();}
  };

private:

  // This is id mapping between the objects inside one block
  class CombinedIdMapping : public OdStaticRxObject<OdDbIdMapping>
  {
    IdMap m_map;
    OdDbDatabase* m_pDb;
    OdDb::DeepCloneType m_dct;
    OdDb::DuplicateRecordCloning m_drc;
  public:
    CombinedIdMapping(OdDbDatabase* pDb, OdDb::DeepCloneType dct, OdDb::DuplicateRecordCloning drc) 
      : m_pDb(pDb), m_dct(dct), m_drc(drc){}

    virtual void assign(const OdDbIdPair& idPair)
    {
      if (!m_map.insert(idPair).second)
      {
        m_map.erase(idPair);
        m_map.insert(idPair);
      }
    }

    virtual bool compute(OdDbIdPair& idPair) const
    {
      IdMap::const_iterator i = m_map.find(idPair);
      if (i == m_map.end())
        return false;
      idPair = *i;
      return true;
    }
    virtual bool del(const OdDbObjectId& key)
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
    virtual OdDbIdMappingIterPtr newIterator()
    {
      OdDbIdMappingIterPtr p = OdRxObjectImpl<CombinedIdMappingIterator>::createObject();
      ((CombinedIdMappingIterator*)p.get())->m_pMap = &m_map;
      ((CombinedIdMappingIterator*)p.get())->m_pIt = m_map.begin();
      return p;
    }
    virtual OdDbDatabase* destDb() const { return m_pDb; }
    virtual void setDestDb(OdDbDatabase* pDb) { m_pDb = pDb; }
    virtual OdDbDatabase* origDb() const { return m_pDb; }
    virtual OdDbObjectId insertingXrefBlockId() const {return OdDbObjectId::kNull;}
    virtual OdDb::DeepCloneType deepCloneContext() const { return m_dct; }
    virtual OdDb::DuplicateRecordCloning duplicateRecordCloning() const { return m_drc; }
  };
  // clone workset to original block
  void cloneWorkSet(OdDbLongTransaction* lt, const OdDbObjectIdArray& toClone);
  // swap cloned workset with original objects
  void swapClonedWorkset(OdArray<OdDbIdPair>& oldMapping, OdDbLongTransactionImpl* pImpl);
  // check if all the objects were removed
  static bool allObjectsRemoved(OdDbLongTransactionImpl* pImpl);
  static void saveIdMapping(OdDbIdMapping* m, OdArray<OdDbIdPair>& oldMapping);
public:
  OdApLongTransactionManagerImpl();
  virtual OdResult checkOut(OdDbObjectId& transId, OdDbObjectIdArray& objList, OdDbObjectId toBlock, 
    OdDbIdMapping& errorMap, OdDbObjectId lockBlkRef = OdDbObjectId::kNull);
  virtual OdResult checkIn(OdDbObjectId transId, OdDbIdMapping& errorMap, bool keepObjs = false);
  virtual OdResult abortLongTransaction(OdDbObjectId transId, bool keepObjs = false);
  virtual void addReactor(OdApLongTransactionReactor*);
  virtual void removeReactor(OdApLongTransactionReactor*);
  virtual OdResult addClassFilter (OdRxClass* );
  virtual bool isFiltered (OdRxClass* ) const;
  virtual OdDbObjectId currentLongTransactionFor(const OdDbDatabase* pDb) const;
};
