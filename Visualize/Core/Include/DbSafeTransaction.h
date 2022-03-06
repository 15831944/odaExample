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




#ifndef _ODDBSAFETRANSACTION_INCLUDED_
#define _ODDBSAFETRANSACTION_INCLUDED_

#include "TD_PackPush.h"

#include "RxObject.h"
#include "StaticRxObject.h"
#include "DbTransactionReactor.h"


/** \details
    This class implements Safe OdTvDbTransactionReactor objects.
    
    \remarks
    These Reactor objects assure that all active database transactions for the 
    tracked database will be aborted when an instance of this class is destroyed.

    <group OdTvDb_Classes>
*/
class OdTvDbSafeTransaction : private OdStaticRxObject<OdTvDbTransactionReactor>
{
  int m_nCounter;
  OdTvDbDatabase* m_pTrackedDB;

  OdTvDbSafeTransaction& operator = (const OdTvDbSafeTransaction& other);

  /** \details
    Notification function called whenever a transaction has started.
    \remarks
    Increments the reference count of this Reactor object.
  */
void transactionStarted(OdTvDbDatabase* )  { ++m_nCounter; }
  /** \details
    Notification function called whenever a transaction has ended.
    \param pTrackedDb [in]  Pointer to the tracked database.
    \remarks
    Decrements the reference count of this Reactor object.

    This Reactor object is removed from the tracked database when the reference count reaches zero.
  */
  void transactionEnded(OdTvDbDatabase* pTrackedDb)
  {
    if(!--m_nCounter)
      pTrackedDb->removeTransactionReactor(this);
  }
  /** \details
    Notification function called whenever a transaction has been aborted.
    \param pTrackedDb [in]  Pointer to the tracked database.
    \remarks
    Decrements the reference count of this Reactor object.

    This Reactor object is removed from the tracked database when the reference count reaches zero.
  */
  void transactionAborted(OdTvDbDatabase* pTrackedDb)
  {
    if(!--m_nCounter)
      pTrackedDb->removeTransactionReactor(this);
  }
public:
  /** \param pTrackedDB [in]  Pointer to the tracked database.
    
    \remarks
    Adds this Reactor object to the tracked database. 
  */
  OdTvDbSafeTransaction(OdTvDbDatabase* pTrackedDb)
  : m_nCounter(0), m_pTrackedDB(pTrackedDb)
  {
    if (m_pTrackedDB)
    {
      m_pTrackedDB->addTransactionReactor(this);
    }
  }

  /** \remarks
    Removes this Reactor object from the tracked database,
    and aborts all active transactions started since this Reactor object
    was constructed. 
  */
	~OdTvDbSafeTransaction()
  { 
    m_pTrackedDB->removeTransactionReactor(this);
    while(m_nCounter--)
      m_pTrackedDB->abortTransaction();
  }
};

#include "TD_PackPop.h"

#endif // _ODDBSAFETRANSACTION_INCLUDED_

