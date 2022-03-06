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

/************************************************************************/
/* This file describes counted chunk-based memory management.           */
/************************************************************************/

#include "OdAlloc.h"
#include "OdMutex.h"

#ifndef OD_TV_MEMORY_TRACKING_H
#define OD_TV_MEMORY_TRACKING_H

const size_t MEMORY_TRACKING_NODE_OFFSET = (sizeof( size_t* ) + sizeof( size_t* ) + sizeof( OdUInt64 ));

struct OdTvMemoryTrackingNode
{
  OdTvMemoryTrackingNode* m_pPrev;
  OdTvMemoryTrackingNode* m_pNext;
  OdUInt64 m_size;

  OdTvMemoryTrackingNode() : m_pPrev( NULL ), m_pNext( NULL ), m_size( 0 )
  {
  }
};

struct OdTvMemoryTracker
{
  OdTvMemoryTrackingNode* m_pHead;
  OdTvMemoryTrackingNode* m_pTail;

  mutable OdMutex         m_mutex;

  OdTvMemoryTracker() : m_pHead( NULL ), m_pTail( NULL )
  {
  }

  void addNode( OdTvMemoryTrackingNode* pNode )
  {
    if( !pNode ) return;
    m_mutex.lock();
    if( !m_pTail )
    {
      pNode->m_pNext = NULL;
      pNode->m_pPrev = NULL;
      m_pTail = pNode;
      m_pHead = pNode;
      m_mutex.unlock();
      return;
    }
    m_pTail->m_pNext = pNode;
    pNode->m_pPrev = m_pTail;
    pNode->m_pNext = NULL;
    m_pTail = pNode;
    m_mutex.unlock();
  }

  void removeNode( OdTvMemoryTrackingNode* pNode )
  {
    if( !pNode ) return;
    m_mutex.lock();
    if( pNode != m_pTail && pNode != m_pHead )
    {
      OdTvMemoryTrackingNode* pPrev = pNode->m_pPrev;
      OdTvMemoryTrackingNode* pNext = pNode->m_pNext;
      if( pPrev )
      {
        pPrev->m_pNext = pNext;
      }
      if( pNext )
      {
        pNext->m_pPrev = pPrev;
      }
      pNode->m_pPrev = NULL;
      pNode->m_pNext = NULL;
      m_mutex.unlock();
      return;
    }
    if( pNode != m_pHead ) //remove tail node
    {
      m_pTail = m_pTail->m_pPrev;
      m_pTail->m_pNext = NULL;
      pNode->m_pPrev = NULL;
      pNode->m_pNext = NULL;
      m_mutex.unlock();
      return;
    }
    if( pNode != m_pTail ) //remove head
    {
      m_pHead = m_pHead->m_pNext;
      m_pHead->m_pPrev = NULL;
      pNode->m_pPrev = NULL;
      pNode->m_pNext = NULL;
      m_mutex.unlock();
      return;
    }
    //remove single one node
    m_pHead = NULL;
    m_pTail = NULL;
    pNode->m_pPrev = NULL;
    pNode->m_pNext = NULL;
    m_mutex.unlock();
  }

  OdUInt64 getAllocatedSize() const
  {
    m_mutex.lock();
    OdTvMemoryTrackingNode* pNode = m_pHead;
    OdUInt64 res = 0;
    while( pNode )
    {
      res += pNode->m_size;
      pNode = pNode->m_pNext;
    }
    m_mutex.unlock();
    return res;
  }

  OdUInt64 getNodesCount() const
  {
    m_mutex.lock();
    OdTvMemoryTrackingNode* pNode = m_pHead;
    OdUInt64 res = 0;
    while( pNode )
    {
      res ++;
      pNode = pNode->m_pNext;
    }
    m_mutex.unlock();
    return res;
  }
};

class OdTvAllocCounter
{
public:
  OdTvAllocCounter()
  {
    m_count = 0;
    m_peakUsage = 0;
  }
  ~OdTvAllocCounter()
  {
  }

  OdUInt64 getCount() const;
  OdUInt64 getPeakUsage() const;
  void add( OdUInt64 c );
  void remove( void* ptr );
protected:
  OdUInt64 m_count;
  OdUInt64 m_peakUsage;
  mutable OdMutex m_mutex;
};

#endif
