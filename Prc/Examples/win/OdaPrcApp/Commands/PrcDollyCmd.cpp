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

#include "../stdafx.h"
#include "Gi/GiDrawableImpl.h"
#include "Gs/GsBaseVectorizer.h"
#include "PrcFile.h"
#include "PrcDollyCmd.h"
#include "AbstractViewPE.h"

// Dolly command
const OdString OdExPrcDollyCmd::groupName() const
{
  return globalName();
}

const OdString OdExPrcDollyCmd::globalName() const
{
  return OD_T("DOLLY");
}

class RTDollyTracker : public OdEdPointTracker
{
  OdGsView*       m_pView;
  OdGePoint3d     m_pt;
  OdGePoint3d     m_pos;
public:
  RTDollyTracker()
    : m_pView(0)
  {
  }
  void reset() { m_pView = 0; }
  void init(OdGsView* pView, const OdGePoint3d& pt)
  {
    m_pView = pView;
    m_pos = pView->position();
    m_pt = pt - m_pos.asVector();
  }
  
  void setValue(const OdGePoint3d& value)
  {
    if(m_pView)
    {
      OdGeVector3d delta = (m_pt - (value - m_pos)).asVector();
      m_pt = value - m_pos.asVector();
      delta.transformBy(m_pView->viewingMatrix());
      m_pView->dolly(delta.x, delta.y, delta.z);
      m_pos = m_pView->position();
    }
  }

  int addDrawables(OdGsView* /*pView*/)
  {
    return 0;
  }
  void removeDrawables(OdGsView* /*pView*/)
  {
  }
};

void OdExPrcDollyCmd::execute(OdEdCommandContext* pCmdCtx)
{
  OdPrcCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdPrcFilePtr pDb = pDbCmdCtx->database();
  OdSmartPtr<OdEdBaseUserIO> pIO = pDbCmdCtx->userIO();

  OdGsView* pView = pDb->getActiveView();

  OdStaticRxObject<RTDollyTracker> tracker;
  for(;;)
  {
    try
    {
      tracker.init(pView, pIO->getPoint(OD_T("Press ESC or ENTER to exit."),
          OdEd::kInpThrowEmpty|OdEd::kGptNoUCS|OdEd::kGptNoOSnap|OdEd::kGptBeginDrag, 
              0, OdString::kEmpty, &tracker));
      pIO->getPoint(OD_T("Press ESC or ENTER to exit."),
          OdEd::kInpThrowEmpty|OdEd::kGptNoUCS|OdEd::kGptNoOSnap|OdEd::kGptEndDrag, 
              0, OdString::kEmpty, &tracker);
      tracker.reset();
    }
    catch(const OdEdCancel)
    {
      break;
    }
  }
}
