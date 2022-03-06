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

#ifndef _DBTRANSRESIDENT_H_INCLUDED_
#define _DBTRANSRESIDENT_H_INCLUDED_

#include "TD_PackPush.h"

class OdTvDbTransResident
{
  inline OdTvDbTransResident(OdTvDbObject* pObj)
    : m_pNext(OdTvDbDatabaseImpl::getImpl(pObj->database())->m_pTransResidents)
    , m_pObj(pObj)
  {
    m_pPrevious = 0;
    if (m_pNext)
      m_pNext->m_pPrevious = this;
  }
public:
  static inline void add(OdTvDbObject* pObj)
  {
    OdTvDbDatabaseImpl* pDbImpl = OdTvDbDatabaseImpl::getImpl(pObj->database());
    pDbImpl->m_pTransResidents = new OdTvDbTransResident(pObj);
    if (!pDbImpl->m_pTransResidentsFirst)
      pDbImpl->m_pTransResidentsFirst = pDbImpl->m_pTransResidents;
  }
  static inline OdTvDbTransResident* front(OdTvDbDatabaseImpl* pDbImpl)
  {
    return pDbImpl->m_pTransResidents;
  }
  static inline OdTvDbTransResident* end(OdTvDbDatabaseImpl* pDbImpl)
  {
    return pDbImpl->m_pTransResidentsFirst;
  }
  static inline void clear(OdTvDbDatabaseImpl* pDbImpl)
  {
    OdTvDbTransResident* pTr = pDbImpl->m_pTransResidents;
    while (pTr)
    {
      OdTvDbTransResident* pNext = pTr->m_pNext;
      delete pTr;
      pTr = pNext;
    }
    pDbImpl->m_pTransResidents = 0;
    pDbImpl->m_pTransResidentsFirst = 0;
  }
  static OdTvDbTransResident* step(OdTvDbTransResident* pTR, OdTvDbDatabaseImpl* pDbImpl)
  {
    pTR->m_pObj = 0; // mark item as processed
    pTR = pTR->m_pPrevious; // step
    if (!pTR || pTR->m_pObj.isNull()) // rewind when end is reached or processed item is met (the rest is processed)
      pTR = OdTvDbTransResident::end(pDbImpl);
    return pTR;
  }
  OdTvDbObjectPtr       m_pObj;
  OdTvDbTransResident*  m_pNext;
  OdTvDbTransResident*  m_pPrevious;
};

#include "TD_PackPop.h"

#endif // _DBTRANSRESIDENT_H_INCLUDED_
