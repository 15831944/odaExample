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
#ifndef __NW_STREAMLOADERFACTORY_H__
#define __NW_STREAMLOADERFACTORY_H__

#include "NwStreamType.h"
#define STL_USING_MEMORY
#define STL_USING_VECTOR
#include "OdaSTL.h"

#include "TD_PackPush.h"

class OdNwStreamLoader;
typedef std::shared_ptr<OdNwStreamLoader> OdNwStreamLoaderPtr;

template<int ...>
struct seq
{ };

template<int N, int ...S>
struct gens : gens<N-1, N-1, S...>
{ };

template<int ...S>
struct gens<0, S...>
{
  typedef seq<S...> type;
};

template<typename Func, typename Tuple, int ...S>
auto callFunc(Func func, Tuple t, seq<S...>)->decltype(func(std::get<S>(t) ...))
{
   return func(std::get<S>(t) ...);
}

class OdNwStreamLoaderFactory
{
  using createStreamLoaderCallBack = std::function<OdNwStreamLoaderPtr()>;
  using callBackMap = std::map<NwStreamType::Enum, createStreamLoaderCallBack>;
public:
  explicit OdNwStreamLoaderFactory(OdUInt32 loadersSetCounts = 2, OdUInt32 activeLoadersSetIndex = 0)
    : m_activeLoadersSetIndex(activeLoadersSetIndex)
    , m_vCallBacks(loadersSetCounts)
  {}
  virtual ~OdNwStreamLoaderFactory() {};

public:
  template<typename T, class ...Args>
  bool registerStreamLoader(NwStreamType::Enum streamId, T funcCreate, Args... args)
  {
    if (m_vCallBacks[m_activeLoadersSetIndex].find(streamId) != m_vCallBacks[m_activeLoadersSetIndex].end())
      return false;

    std::tuple<Args...> tArgs = std::make_tuple(std::forward<Args>(args)...);
    auto lamda = [funcCreate, tArgs]()
    {
      return callFunc(funcCreate, tArgs, typename gens<std::tuple_size<decltype(tArgs)>::value>::type());
    };
    return m_vCallBacks[m_activeLoadersSetIndex].insert({ streamId, lamda }).second;
  }
  bool unregisterStreamLoader(NwStreamType::Enum streamId)
  {
    return m_vCallBacks[m_activeLoadersSetIndex].erase(streamId) == 1;
  }
  OdNwStreamLoaderPtr createStreamLoader(NwStreamType::Enum streamId)
  {
    auto iFL = m_vCallBacks[m_activeLoadersSetIndex].find(streamId);
    if (iFL != m_vCallBacks[m_activeLoadersSetIndex].end())
      return (iFL->second)();
    return OdNwStreamLoaderPtr();
  }
  OdResult setActiveLoadersSetIndex(OdUInt32 index)
  {
    if (index < m_vCallBacks.size())
    {
      m_activeLoadersSetIndex = index;
      return eOk;
    }
    else
      return eInvalidIndex;
  }
  void resizeLoadersSet(OdUInt32 count)
  {
    m_vCallBacks.resize(count);
    if (m_activeLoadersSetIndex >= count)
      m_activeLoadersSetIndex = 0;
  }

protected:
  //VAS:: first index( = 0) always is idex for common stream loaders(XRefTable, CommonSchemas, OdyFileInfo), but next index( = 1) is index for start sheets loaders collection
  OdUInt32 m_activeLoadersSetIndex;
  std::vector<callBackMap> m_vCallBacks;
};


#include "TD_PackPop.h"

#endif // __NW_STREAMLOADERFACTORY_H__
