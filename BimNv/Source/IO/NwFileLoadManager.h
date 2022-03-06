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

#ifndef __NWFILELOADMANAGER_H__
#define __NWFILELOADMANAGER_H__

#include "NwStreamLoader.h"
#include "SharedPtr.h"
#include "NwStreamLoaderFactory.h"

class OdNwLoaderBase
{
public:
  OdNwLoaderBase() = default;
  virtual ~OdNwLoaderBase() = default;
  
  //set stream loader by type to laoding, it possible to set lazy load mode(after that this stream not will parsed in main load, but only by request of stream data)
  virtual OdResult setToLoad(NwStreamType::Enum streamType, bool isLazyLoad = false) = 0;
  //set stream loader by type to late laoding, there is need to set streams which your stream is depend and after which streams your stream must be parsed
  virtual OdResult setToLateLoad(NwStreamType::Enum streamType, std::initializer_list<NwStreamType::Enum>&& linkStreams) = 0;
  //parse all stream which was marked as 'late load'(which has dependencies with other streams)
  virtual OdResult lateLoad(OdNwLoadersMap& mLoaders) = 0;
};

class OdNwFileLoadManager
{
public:
  static OdSharedPtr<OdNwLoaderBase> createLoader(OdNwDatabaseImpl* pDbImpl, OdNwStreamLoaderFactory& streamLoaderFactory, bool bIsActiveLoader = true);
};

#endif // __NWFILELOADMANAGER_H__
