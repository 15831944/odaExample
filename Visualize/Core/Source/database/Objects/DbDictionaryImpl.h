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

// DbDictionaryImpl.h: interface for the OdTvDbDictionaryImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBDICTIONARYIMPL_H__BBF5B822_AC04_11D5_9C8B_0000B4741A23__INCLUDED_)
#define AFX_DBDICTIONARYIMPL_H__BBF5B822_AC04_11D5_9C8B_0000B4741A23__INCLUDED_


#include "BaseDictionaryImpl.h"
#include "../DbSystemInternals.h"
#include "DbDictionary.h"
#include "DbObjectImpl.h"


#include "RxObjectImpl.h"

class OdTvDbObject;
class OdTvDbObjectId;

class OdTvDbDictItem
{
  OdString      m_key;
  OdTvDbObjectId  m_val;
public:
  OdTvDbDictItem() {}
  OdTvDbDictItem(const OdString& key, const OdTvDbObjectId& val)
    : m_key(key)
    , m_val(val)
  {}
  const OdString& getKey() const { return m_key; }
  void setKey(const OdString& key) { m_key = key; }
  const OdTvDbObjectId& getVal() const { return m_val; }
  void setVal(const OdTvDbObjectId& id) { m_val = id; }
  bool isErased() const { return m_val.isErased(); }
  void erase() { m_val.setNull(); }
};

class OdTvDbDictionaryImpl : public OdBaseDictionaryImpl<OdString, OdTvDbObjectId, OdString::lessnocase, OdTvDbDictItem>
                         , public OdTvDbObjectImpl
{
  static OdTvDbDictionaryImpl* getImpl(const OdTvDbDictionary *pObj)
  { 
    return (OdTvDbDictionaryImpl*)OdTvDbSystemInternals::getImpl(pObj);
  }
  OdString checkAnonym( const OdString& name );

public:
  OdDb::DuplicateRecordCloning  m_mergeStyle;
  OdUInt32                      m_nAnonymousIndex; // Run-time variable
  OdUInt8                       m_flags;
  enum
  {
    kTreatElementsAsHard  = 1,
    kSeparatedPartialUndo = 2
  };
  void setTreatElementsAsHard(bool value) { SETBIT(m_flags, kTreatElementsAsHard, value); }
  bool isTreatElementsAsHard() const { return GETBIT(m_flags, kTreatElementsAsHard); }
  void setSeparatedPartialUndo(bool value) { SETBIT(m_flags, kSeparatedPartialUndo, value); }
  bool isSeparatedPartialUndo() const { return GETBIT(m_flags, kSeparatedPartialUndo); }

  OdTvDbDictionaryImpl();

  void removeEntry(sorted_iterator& iter, OdTvDbDwgFiler* pUndo = 0);

  // Called for each database object during conversion
  // pObj - interface of object
  void decomposeForSave(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void composeForLoad(OdTvDbObject *pObj, OdDb::SaveType format, OdDb::DwgVersion version);
  void convertToSysCodePage();

  void audit (OdTvDbAuditInfo* pAuditInfo);

  static bool getByIndex(const OdTvDbDictionary * pDic, OdUInt32 id, OdTvDbObjectId& val)
  { return getImpl(pDic)->getAt(id, val);}

  static void clearItems(OdTvDbDictionary * pDic)
  { getImpl(pDic)->clear();}

protected:
  OdTvDbDictionaryIteratorPtr newIterator(OdRx::DictIterType iterType, bool bSkipDeleted = true);

  friend class OdTvDbDictionary;
  friend struct OdTvDbDictionaryTfPE;
};


template <class ArrayType>
class OdTvDbDictionaryIteratorImpl : public OdTvDbDictionaryIterator
{
  OdTvDbDictionaryIteratorImpl& operator = (const OdTvDbDictionaryIteratorImpl&);

  OdBaseIteratorImpl<ArrayType, OdString, OdTvDbObjectId> m_iter;
public:
  ~OdTvDbDictionaryIteratorImpl() {}

  static OdTvDbDictionaryIteratorPtr createObject(ArrayType& items, bool bSkipDeleted = true)
  {
    OdSmartPtr<OdTvDbDictionaryIteratorImpl> pRes = 
      OdRxObjectImpl<OdTvDbDictionaryIteratorImpl<ArrayType> >::createObject();
    pRes->m_iter.init(items, true, bSkipDeleted);
    return pRes;
  }
  
  OdString name() const
  {
    return m_iter.getKey();
  }

  OdTvDbObjectPtr getObject(OdDb::OpenMode mode)
  {
    return m_iter.getItem().openObject(mode);
  }
  
  OdTvDbObjectId objectId() const
  {
    return m_iter.getItem();
  }

  bool setPosition(OdTvDbObjectId objId)
  {
    return m_iter.seek(objId);
  }

  bool done() const 
  { 
    return m_iter.isDone();
  }

  bool next() 
  { 
    return m_iter.next();
  }
};


#endif // !defined(AFX_DBDICTIONARYIMPL_H__BBF5B822_AC04_11D5_9C8B_0000B4741A23__INCLUDED_)

