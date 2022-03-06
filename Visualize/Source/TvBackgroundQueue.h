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

#ifndef TV_BACKGROUND_QUEUE_H
#define TV_BACKGROUND_QUEUE_H

#include "RxThreadPoolService.h"

/**\details
This class describes singleton STQueue for background processes
*/
class OdTvBackgroundQueue
{
  static OdApcQueuePtr m_pSTQueue;
  static OdRxThreadPoolServicePtr m_pThreadPool;
  static OdUInt32 m_nref;
  /** \details
  Releases smart pointers
  */
  void reset()
  {
    m_pSTQueue = NULL;
    m_pThreadPool = NULL;
  }
  /** \details
  Releases OdTvBackgroundQueue instance
  */
  void release()
  {
    m_nref--;
    if( m_nref == 0 ) reset();
  }
public:
  /** \details
  Constructs OdTvBackgroundQueue instance
  */
  OdTvBackgroundQueue(){ m_nref++; };
  /** \details
  Destroy OdTvBackgroundQueue instance
  */
  ~OdTvBackgroundQueue(){ release(); };
  /** \details
  Obtains STQueue instance
  \returns Smatr pointer to the STQueue
  */
  OdApcQueuePtr queue();
};

#endif //TV_BACKGROUND_QUEUE_H
