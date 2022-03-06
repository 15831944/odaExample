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
//   This application incorporates Open Design Alliance software pursuant to a
//   license agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance.
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "OdaCommon.h"
#include "OdString.h"
#include "BaseConverterWorker.hpp"

#include <map>
#include <vector>
using namespace std;

class WorkerConvertFactory {
public:
  explicit WorkerConvertFactory() = default;

  template <class Derived>
  void add(const OdString& distExt)
  {
    m_items[distExt] = &creator<Derived>;
  }

  template <class Derived>
  void addMultiKey(const std::vector<OdString>& keys)
  {
    const auto creatorPtr = &creator<Derived>;
    for (const auto& key : keys)
    {
      m_items[key] = creatorPtr;
    }
  }

  BaseConvertWorkerPtr create(const OdString& distExt)
  {
    const auto itr = m_items.find(distExt);
    if (itr != m_items.end())
      return itr->second();
    return BaseConvertWorkerPtr();
  }

  std::vector<OdString> getFormatNames()
  {
    std::vector<OdString> formats;
    for (const auto& pair : m_items)
    {
      formats.push_back(pair.first);
    }
    return formats;
  }
private:
  typedef BaseConvertWorkerPtr (*functionCreator)();
  typedef map <OdString, functionCreator> FactoryMap;

  template<class BindType>
  static BaseConvertWorkerPtr creator()
  {
    return std::make_shared<BindType>();
  }

  FactoryMap m_items;
};
