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

#include "ODA_PyMemoryManager.h"

mutex ODA_PyMemoryManager::memLocker;
ODA_PyMemoryManager::TransactionsMap ODA_PyMemoryManager::thread_transactions_map;
ODA_PyMemoryManagerPtr ODA_PyMemoryManager::mMngr;

ODA_PyMemoryManager::ODA_PyMemoryManager()
{
}

ODA_PyMemoryManagerPtr ODA_PyMemoryManager::CreateMemoryManager() { return std::shared_ptr<ODA_PyMemoryManager>(new ODA_PyMemoryManager()); }

ODA_PyMemoryManager * ODA_PyMemoryManager::Get_MemoryManager()
{
  if (!mMngr)
  {
    memLocker.lock();
    {
      if (!mMngr)
      {
        mMngr = CreateMemoryManager();
      }
    }
    memLocker.unlock();
  }
  return mMngr.get();
}

ODA_PyMemoryTransaction * ODA_PyMemoryManager::GetCurrentTransaction()
{
  ThreadId threadId = ThreadId(std::this_thread::get_id());
  TransactionsMap::iterator it = thread_transactions_map.find(threadId);
  if (it == thread_transactions_map.end())
    return NULL;
  else 
  {
    ODA_PyMemTransactionCollectionPtr coll = it->second;
    return (coll->at(coll->size() - 1)).get();
  }
}

ODA_PyMemoryTransaction * ODA_PyMemoryManager::StartTransaction()
{
  ThreadId threadId = ThreadId(std::this_thread::get_id());
  return StartTransaction(threadId.asInt());
}

ODA_PyMemoryTransaction * ODA_PyMemoryManager::StartTransaction(int threadId)
{
  ODA_PyMemTransactionCollectionPtr currList;
  TransactionsMap::iterator it = thread_transactions_map.find(threadId);
  if (it == thread_transactions_map.end())
    thread_transactions_map.insert(std::pair<ThreadId, ODA_PyMemTransactionCollectionPtr>(threadId, currList = make_shared<ODA_PyMemoryTransactionCollection>()));
  else
    currList = it->second;

  ODA_PyMemoryTransactionPtr ret = ODA_PyMemoryTransaction::CreateMemoryTransaction();
  currList->push_back(ret);
  return ret.get();
}

void ODA_PyMemoryManager::StopTransaction(ODA_PyMemoryTransaction * value, int ManagedThreadId)
{
  if (thread_transactions_map.find(ManagedThreadId) == thread_transactions_map.end())
    return;

  ODA_PyMemTransactionCollectionPtr transactions = thread_transactions_map[ManagedThreadId];

  if (transactions->size() == 1)
    thread_transactions_map.erase(ManagedThreadId);

  int index_remove_to = transactions->IndexOf(value);
  size_t length = transactions->size();

  if ((index_remove_to < 0) || (index_remove_to >= length))
    throw new std::exception("Stop transaction exception");

  ODA_PyMemoryTransactionPtr trans;

  for (int idx = (length - 1); idx >= index_remove_to; idx--)
  {
    trans = transactions->at(idx);
    transactions->erase(transactions->begin() + idx);
    trans->DeleteObjects();
  }
}

void ODA_PyMemoryManager::StopTransaction(ODA_PyMemoryTransaction * value)
{
  ThreadId threadId = std::this_thread::get_id();
  StopTransaction(value, threadId.asInt());
}


ODA_PyMemoryManager::~ODA_PyMemoryManager()
{
  for (TransactionsMap::iterator it = thread_transactions_map.end(); it != thread_transactions_map.begin(); --it)
  {
    ODA_PyMemTransactionCollectionPtr transactions = it->second;
    size_t length = transactions->size();
    int index_remove_to = 0;
    ODA_PyMemoryTransactionPtr trans;
    for (int idx = (length - 1); idx >= index_remove_to; idx--)
    {
      trans = transactions->at(idx);
      trans->DeleteObjects();
    }
    transactions->clear();
  }
  thread_transactions_map.clear();
}

inline ODA_PyMemoryManager::ThreadId::ThreadId(const int & fromInt) {
  value = fromInt;
}

inline ODA_PyMemoryManager::ThreadId::ThreadId(const thread::id & from_thread_id) {
  value = asInt(from_thread_id);
}

inline int ODA_PyMemoryManager::ThreadId::asInt()
{
  return value;
}

inline int ODA_PyMemoryManager::ThreadId::asInt(thread::id from)
{
  std::stringstream ss;
  ss << std::this_thread::get_id();
  return std::stoi(ss.str());
}
