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



#ifndef _INC_ODITRAVERSER_3F82DF7201C5_INCLUDED
#define _INC_ODITRAVERSER_3F82DF7201C5_INCLUDED

#include "TD_PackPush.h"
#include "RxObject.h"

class OdIBaseTraverser : public OdRxObject
{
public:
  virtual ~OdIBaseTraverser() {}

  virtual bool done() const = 0;
  virtual void next() = 0;
  virtual void restart() = 0;
  virtual bool isEqualTo(const OdIBaseTraverser* pOtherTraverser) const = 0;
  virtual bool isNull() const = 0;
};

template <class Parent, class Child>
class OdITraverser : public OdIBaseTraverser
{
  Parent *m_pParent;
  Child  *m_pFirstChild;
  Child  *m_pCurChild;

protected:
  OdITraverser<Parent, Child>()
    : m_pParent(0)
    , m_pFirstChild(0)
    , m_pCurChild(0)
  {}
public:

  Child *getCurrent() 
  {
    return m_pCurChild ? m_pCurChild : m_pFirstChild;
  }

  const Child *getCurrent() const
  {
    return m_pCurChild ? m_pCurChild : m_pFirstChild;
  }

  Parent *getParent() 
  {
    return m_pParent;
  }

  const Parent *getParent() const
  {
    return m_pParent;
  }

  virtual ~OdITraverser<Parent, Child>()
  {
    m_pParent = 0;
    m_pFirstChild = 0;
    m_pCurChild = 0;
  }

  virtual bool init(Parent *pParent, Child *pFirstChild, Child *pChild)
  {
    if (pParent == 0 || pFirstChild == 0)
      return false;

    if (pChild == 0)
      pChild = pFirstChild;

    m_pParent = pParent;
    m_pFirstChild = pFirstChild;
    m_pCurChild = (pFirstChild == pChild) ? 0 : pChild;
    return true;
  }

  virtual bool done() const
  {
    return m_pFirstChild == m_pCurChild;
  }

  virtual void next()
  {
    m_pParent->next(m_pFirstChild, m_pCurChild);
  }

  virtual void restart()
  {
    init(m_pParent, m_pFirstChild, 0);
  }

  virtual bool isEqualTo(const OdIBaseTraverser* pOther) const
  {
    OdITraverser<Parent, Child> * pOtherTraverser = (OdITraverser<Parent, Child> *)pOther;
    return m_pParent == pOtherTraverser->m_pParent && 
           // m_pFirstChild == pOtherTraverser->m_pFirstChild && 
           getCurrent() == pOtherTraverser->getCurrent();
  }

  virtual bool isNull() const
  {
    return m_pParent == 0;
  }
};

#include "TD_PackPop.h"

#endif /* _INC_ODITRAVERSER_3F82DF7201C5_INCLUDED */

