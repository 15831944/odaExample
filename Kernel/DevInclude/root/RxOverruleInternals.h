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

#ifndef _RXOVERRULEINTERNALS_H_INCLUDED_
#define _RXOVERRULEINTERNALS_H_INCLUDED_

#include "RxOverrule.h"
#include "RxClassImpl.h"

class OdRxOverruleIterator
{
  OdRxOverrule* pOverrule;
  OdRxOverruleIterator* pNext;
  OdRxOverruleIterator(OdRxOverrule* pOverrule, OdRxOverruleIterator* pNext)
    : pOverrule(pOverrule), pNext(pNext)
  {
  }
  friend class OdRxOverruleInternals;
  friend class OdRxClassImpl;
};

class FIRSTDLL_EXPORT OdRxOverruleInternals
{
  static bool removeOverruleDirect(OdRxClass* pClass, OdRxOverrule* pOverrule, OverrulingType t);
  static void addOverruleDirect(OdRxClass* pClass, OdRxOverrule* pOverrule, bool bAddAtLast, OverrulingType t);
public:
  static void addOverrule(OdRxClass* pClass, OdRxOverrule* pOverrule, bool bAddAtLast);
  static bool removeOverrule(OdRxClass* pClass, OdRxOverrule* pOverrule);
  static bool hasOverrule(const OdRxObject* pSubject, OdRxClass* pOverruleClass);
  inline static OdRxOverrule* getFirstOverrule(const OdRxObject* pSubject, OverrulingType t)
  {
    if (!OdRxOverrule::s_bIsOverruling || !pSubject)
      return 0;
    OdRxOverruleIterator* pIter = OdRxClassImpl::getImpl(pSubject->isA())->getOverrule(t);
    while (pIter && !pIter->pOverrule->isApplicable(pSubject))
      pIter = pIter->pNext;
    if (!pIter)
      return 0;
    pIter->pOverrule->m_pIter = pIter->pNext;
    return pIter->pOverrule;
  }
  inline static OdRxOverrule* getNextOverrule(OdRxOverrule* pOverrule, const OdRxObject* pSubject)
  {
    if (!pOverrule->m_pIter)
      return 0;
    OdRxOverruleIterator* i = pOverrule->m_pIter;
    while (i && !i->pOverrule->isApplicable(pSubject))
      i = i->pNext;
    if (!i)
      return 0;
    i->pOverrule->m_pIter = i->pNext;
    return i->pOverrule;
  }

  static void clear(OdRxClass* pClass);
  static void clear();
};

#endif //_RXOVERRULEINTERNALS_H_INCLUDED_
