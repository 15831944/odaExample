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

#pragma once
#include <mutex>
#include <thread>
#include <memory>
#include <map>
#include <sstream>
#include "ODA_PyMemManagerExportDef.h"
#include "ODA_PyMemoryTransaction.h"
#include "ODA_PyMemoryTransactionCollection.h"

using namespace std;

class ODA_PyMemoryManager;
typedef shared_ptr<ODA_PyMemoryManager> ODA_PyMemoryManagerPtr;

class PY_MEM_MANAGER_EXPORT ODA_PyMemoryManager
{
public:

  PY_MEM_MANAGER_STATIC_EXPORT static ODA_PyMemoryManager* Get_MemoryManager();

  PY_MEM_MANAGER_STATIC_EXPORT static ODA_PyMemoryTransaction* GetCurrentTransaction();

  ODA_PyMemoryTransaction* StartTransaction();

  ODA_PyMemoryTransaction* StartTransaction(int threadId);

  void StopTransaction(ODA_PyMemoryTransaction* value, int ManagedThreadId);

  void StopTransaction(ODA_PyMemoryTransaction* value);

  ~ODA_PyMemoryManager();

private:

  class ThreadId
  {
  public:
    ThreadId(const int& fromInt);
    ThreadId(const thread::id& from_thread_id);
    int asInt();;

    bool operator==(const ThreadId& other) const
    {
      return this->value == other.value;
    }

    bool operator!=(const ThreadId& other) const
    {
      return this->value != other.value;
    }

    bool operator<(const ThreadId& other) const
    {
      return this->value < other.value;
    }

  private:
    int value;
    static int asInt(thread::id from);;
  };

  typedef std::map<ThreadId, ODA_PyMemTransactionCollectionPtr> TransactionsMap;

  ODA_PyMemoryManager();

  static ODA_PyMemoryManagerPtr CreateMemoryManager();

  static mutex memLocker;

  static TransactionsMap thread_transactions_map;

  static ODA_PyMemoryManagerPtr mMngr;
};
