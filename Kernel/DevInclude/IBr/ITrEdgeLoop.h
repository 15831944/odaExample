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

#ifndef _INC_DDBRIMPEDGELOOPTRAVERSER_3F83F60D005D_INCLUDED
#define _INC_DDBRIMPEDGELOOPTRAVERSER_3F83F60D005D_INCLUDED

#include "ITrTemplate.h"
#include "IBrCoedge.h"
#include "IBrEdge.h"
#include "IBrLoop.h"
#include "SmartPtr.h"

class OdITrEdgeLoop : public OdIBaseTraverser
{
  OdIBrCoedge *m_pFirstChild;
  OdIBrCoedge *m_pCurChild;

protected:
  OdITrEdgeLoop()
    : m_pFirstChild(0)
    , m_pCurChild(0)
  {}
public:

  const OdIBrCoedge *getParent() const
  {
    return m_pFirstChild;
  }

  OdIBrCoedge *getCurrent() 
  {
    return m_pCurChild ? m_pCurChild : m_pFirstChild;
  }

  const OdIBrCoedge *getCurrent() const
  {
    return m_pCurChild ? m_pCurChild : m_pFirstChild;
  }

  virtual ~OdITrEdgeLoop()
  {
    m_pFirstChild = 0;
    m_pCurChild = 0;
  }

  virtual bool init(OdIBrEdge *pParent, OdIBrCoedge *pFirstChild, OdIBrCoedge *pChild)
  {
    if (pParent == 0 || pFirstChild == 0 || pFirstChild->getEdge() != pParent || pFirstChild->getLoop() == 0 )
      return false;

    m_pFirstChild = pFirstChild;
    m_pCurChild = pChild ? pChild : m_pFirstChild;
    if (m_pFirstChild == m_pCurChild)
      m_pCurChild = 0;

    return true;
  }

  virtual bool done() const
  {
    return m_pFirstChild == m_pCurChild;
  }

  virtual void next()
  {
    m_pFirstChild->nextOnEdge(m_pFirstChild, m_pCurChild);
  }

  virtual void restart()
  {
    m_pCurChild = 0;
  }

  virtual bool isEqualTo(const OdIBaseTraverser* pOther) const
  {
    const OdITrEdgeLoop * pEL1 = dynamic_cast<const OdITrEdgeLoop *>(pOther);
    const OdITrEdgeLoop * pEL2 = this;

    bool b1 = pEL1->getParent() == pEL2->getParent();
    bool b2 = pEL1->getCurrent() == pEL2->getCurrent();

    return b1 && b2;
  }

  virtual bool isNull() const
  {
    return m_pFirstChild == 0;
  }
};

typedef OdSmartPtr<OdITrEdgeLoop> OdITrEdgeLoopPtr ;

#endif /* _INC_DDBRIMPEDGELOOPTRAVERSER_3F83F60D005D_INCLUDED */

