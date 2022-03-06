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

class OdDbObjectContextPE;
class OdDbContextDataSubManager;
class OdDbObjectContextData;

class TOOLKIT_EXPORT OdDbObjectContextDataManager
{
  std::map<OdString,OdDbContextDataSubManager*> m_SubManagers;
  OdDbObjectId m_DictId;
public:
  OdDbObjectContextDataManager();
  ~OdDbObjectContextDataManager();
  void updateFromExtensionDictionary(const OdDbObject*);
  virtual OdDbContextDataSubManager* getSubManager(const OdString&);
  // object should be open for write
  OdResult saveToExtensionDictionary(const OdDbObject*);
  OdResult addSubManager(OdDbContextDataSubManager*);
  OdResult dwgOutFields(OdDbDwgFiler*) const;
  OdResult dwgInFields(const OdDbObject*, OdDbDwgFiler* pFiler);
  void  validateCachedPointers(const OdDbObject*);
  bool isEmpty()const { return m_SubManagers.empty(); }
  friend class OdDbContextDataSubManager;
};

class TOOLKIT_EXPORT OdDbContextDataSubManager
{
  typedef std::pair<OdDbObjectId, OdDbObjectContextDataPtr> ContextDataPair;
  typedef OdArray<ContextDataPair> ContextDataMap;
  ContextDataMap m_Data;
  OdString m_sName;
  OdDbObjectId m_DictId;
  int findContextData(OdIntPtr id) const;
public:
  OdDbContextDataSubManager(const OdString& name);
  void removeAllContextData(bool bRemoveDefault = true);
  OdResult setDefaultContext(const OdDbObjectContext&);
  void addContextData(OdDbObject*);
  bool hasContext(const OdDbObjectContext&);
  OdDbObjectContextDataPtr getContextData(const OdDbObjectContext&) const;
  virtual OdResult removeContextData(const OdDbObjectContext&);
  OdDbObjectContextDataPtr getDefaultContextData() const;
  int getDataCount()const;
  friend class OdDbObjectContextDataManager;
  friend class OdDbObjectContextDataIterator;
};

class TOOLKIT_EXPORT OdDbObjectContextDataIterator
{
protected:
  OdDbContextDataSubManager::ContextDataMap* m_pData;
  OdDbContextDataSubManager::ContextDataMap::iterator m_pIt;
public:
  OdDbObjectContextDataIterator(OdDbContextDataSubManager*);
  OdDbObjectContextDataPtr contextData();
  bool done() const;
  bool next();
};

/*
class TOOLKIT_EXPORT OdDbObjectContextDataIterNoLock
{
  OdDbObjectContextDataIterNoLock(void *,const OdDbObject*);
  OdDbObjectContextDataIterNoLock(const OdDbObject*);
  OdDbObjectContextDataIterNoLock(const OdDbObject*,const OdString&);
  ~OdDbObjectContextDataIterNoLock();
  bool done() const;
  class OdDbObjectContextData* next();
};

*/
#endif //_DBOBJECTCONTEXTDATAMANAGER_H_INCLUDED_
