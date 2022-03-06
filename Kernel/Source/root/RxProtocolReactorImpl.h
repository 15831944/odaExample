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

#ifndef _RxProtocolReactorImpl_h_Included_
#define _RxProtocolReactorImpl_h_Included_

#include "RxProtocolReactor.h"
#define STL_USING_MAP
#include "OdaSTL.h"
#include "OdArray.h"

class OdRxProtocolReactorListImpl;

typedef OdArray<OdRxProtocolReactor*,OdMemoryAllocator<OdRxProtocolReactor*> > OdRxProtocolReactorArray;

class OdRxProtocolReactorIteratorImpl : public OdRxProtocolReactorIterator
{
  friend class OdRxProtocolReactorListImpl;
  const OdRxProtocolReactorListImpl* m_pData;
  unsigned m_nIndex;
  virtual OdRxClass* reactorClass () const;
  virtual void start(); 
  virtual bool next ();
  virtual bool done () const;
  virtual OdRxProtocolReactor* object () const;
};

class OdRxProtocolReactorListImpl : public OdRxProtocolReactorList
{
  friend class OdRxProtocolReactorManagerImpl;
  friend class OdRxProtocolReactorIteratorImpl;
  OdRxClass* m_pClass;
  OdRxProtocolReactorArray m_pReactors;
  virtual OdRxClass* reactorClass() const;
  virtual bool addReactor(OdRxProtocolReactor* pReactor);
  virtual void removeReactor(OdRxProtocolReactor* pReactor);
  virtual OdRxProtocolReactorIteratorPtr newIterator () const;
};

typedef std::map<OdRxClass*,OdRxProtocolReactorListPtr> OdRxProtocolReactorListMap;

class OdRxProtocolReactorManagerImpl : public OdRxProtocolReactorManager
{
  virtual OdRxProtocolReactorList* createReactorList ( OdRxClass* pReactorClass);
  virtual OdRxProtocolReactorListIteratorPtr newIterator () const;
  OdRxProtocolReactorListMap m_pLists;
};

class OdRxProtocolReactorListIteratorImpl : public OdRxProtocolReactorListIterator
{
  friend class OdRxProtocolReactorManagerImpl;
  const OdRxProtocolReactorListMap* m_pListMap;
  OdRxProtocolReactorListMap::const_iterator m_pList;
  virtual void start(); 
  virtual bool next ();
  virtual bool done () const;
  virtual OdRxProtocolReactorList* object () const;
};

class OdRxProtocolReactorManagerFactoryImpl : public OdRxProtocolReactorManagerFactory
{
  virtual OdRxProtocolReactorManager* createReactorManager( OdRxClass* pRxClass ) const;
};

#endif //_RxProtocolReactorImpl_h_Included_
