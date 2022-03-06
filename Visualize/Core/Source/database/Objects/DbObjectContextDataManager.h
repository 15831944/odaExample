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

#ifndef _DBOBJECTCONTEXTDATAMANAGER_H_INCLUDED_
#define _DBOBJECTCONTEXTDATAMANAGER_H_INCLUDED_

#define STL_USING_MAP
#include "OdaSTL.h"
#include "DbObjectContextData.h"

class OdTvDbObjectContextPE;
class OdTvDbContextDataSubManager;
class OdTvDbObjectContextData;

class TOOLKIT_EXPORT OdTvDbObjectContextDataManager
{
  std::map<OdString,OdTvDbContextDataSubManager*> m_SubManagers;
  OdTvDbObjectId m_DictId;
public:
  OdTvDbObjectContextDataManager();
  ~OdTvDbObjectContextDataManager();
  void updateFromExtensionDictionary(const OdTvDbObject*);
  virtual OdTvDbContextDataSubManager* getSubManager(const OdString&);
  // object should be open for write
  OdResult saveToExtensionDictionary(const OdTvDbObject*);
  OdResult addSubManager(OdTvDbContextDataSubManager*);
  OdResult dwgOutFields(OdTvDbDwgFiler*) const;
  OdResult dwgInFields(const OdTvDbObject*, OdTvDbDwgFiler* pFiler);
  void  validateCachedPointers(const OdTvDbObject*);
  bool isEmpty()const { return m_SubManagers.empty(); }
  friend class OdTvDbContextDataSubManager;
};

class TOOLKIT_EXPORT OdTvDbContextDataSubManager
{
  typedef std::pair<OdTvDbObjectId, OdTvDbObjectContextDataPtr> ContextDataPair;
  typedef OdArray<ContextDataPair> ContextDataMap;
  ContextDataMap m_Data;
  OdString m_sName;
  OdTvDbObjectId m_DictId;
  int findContextData(OdIntPtr id) const;
public:
  OdTvDbContextDataSubManager(const OdString& name);
  void removeAllContextData(bool bRemoveDefault = true);
  OdResult setDefaultContext(const OdTvDbObjectContext&);
  void addContextData(OdTvDbObject*);
  bool hasContext(const OdTvDbObjectContext&);
  OdTvDbObjectContextDataPtr getContextData(const OdTvDbObjectContext&) const;
  virtual OdResult removeContextData(const OdTvDbObjectContext&);
  OdTvDbObjectContextDataPtr getDefaultContextData() const;
  int getDataCount()const;
  friend class OdTvDbObjectContextDataManager;
  friend class OdTvDbObjectContextDataIterator;
};

class TOOLKIT_EXPORT OdTvDbObjectContextDataIterator
{
protected:
  OdTvDbContextDataSubManager::ContextDataMap* m_pData;
  OdTvDbContextDataSubManager::ContextDataMap::iterator m_pIt;
public:
  OdTvDbObjectContextDataIterator(OdTvDbContextDataSubManager*);
  OdTvDbObjectContextDataPtr contextData();
  bool done() const;
  bool next();
};

/*
class TOOLKIT_EXPORT OdTvDbObjectContextDataIterNoLock
{
  OdTvDbObjectContextDataIterNoLock(void *,const OdTvDbObject*);
  OdTvDbObjectContextDataIterNoLock(const OdTvDbObject*);
  OdTvDbObjectContextDataIterNoLock(const OdTvDbObject*,const OdString&);
  ~OdTvDbObjectContextDataIterNoLock();
  bool done() const;
  class OdTvDbObjectContextData* next();
};

*/
#endif //_DBOBJECTCONTEXTDATAMANAGER_H_INCLUDED_
