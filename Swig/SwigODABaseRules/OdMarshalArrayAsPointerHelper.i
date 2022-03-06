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

#include <map>
#include "OdMutex.h"

class OdMarshalArrayAsPointerHelper
{
public:
  static void Add(const void* arrPtr, long size) {
    m_mtx.lock();
    m_arrayToSize.insert(std::pair<const void*, long>(arrPtr, size));
    m_mtx.unlock();
  }

  static long GetSize(const void* arrPtr) {
    long size = -1;
    m_mtx.lock();
    std::map<const void*, long>::iterator it = m_arrayToSize.find(arrPtr);
    if (it != m_arrayToSize.end())
      size = it->second;
    m_mtx.unlock();
    return size;
  }

  static void Remove(const void* arrPtr)
  {
    m_mtx.lock();
    if (m_arrayToSize.find(arrPtr) != m_arrayToSize.end())
      m_arrayToSize.erase(arrPtr);
    m_mtx.unlock();
  }

private:
  static std::map<const void*, long> m_arrayToSize;
  static OdMutex m_mtx;
};

std::map<const void*, long> OdMarshalArrayAsPointerHelper::m_arrayToSize;
OdMutex OdMarshalArrayAsPointerHelper::m_mtx;