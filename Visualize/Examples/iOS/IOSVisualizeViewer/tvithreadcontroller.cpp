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
#include "tvithreadcontroller.h"

#include "tviutils.h"

TviThreadController::TviThreadController()
  : QThread(), m_pTask(NULL), m_bisCancel(false)
{
  //connect(this, SIGNAL(finished), this, SLOT(deleteLater));
}

void TviThreadController::setTask(TviThreadTask *pTask)
{
  m_pTask = pTask;
  m_pTask->m_pController = this;
}

void TviThreadController::cancel()
{
  m_bisCancel = true;
  this->terminate();
}

void TviThreadController::run()
{
  try
  {
    m_pTask->run();
    if (!m_bisCancel)
      emit resultReady();
  }
  catch (OdTvError& err)
  {
    if (!m_bisCancel)
      emit error( toQString(err.description()) );
  }
  catch (OdError& err)
  {
    if (!m_bisCancel)
      emit error( toQString(err.description()) );
  }
  catch (...)
  {
    if (!m_bisCancel)
      emit unexpectedError();
  }
}
