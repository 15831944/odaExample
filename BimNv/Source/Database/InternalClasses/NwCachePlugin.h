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

#ifndef __NWCACHEPLUGIN_INCLUDED_
#define __NWCACHEPLUGIN_INCLUDED_

#include "SharedPtr.h"
#include "OdString.h"

class OdNwOptions;
typedef OdSharedPtr<OdNwOptions> OdNwOptionsPtr;

class OdNwCachePlugin
{
public:
  OdNwCachePlugin();
  virtual ~OdNwCachePlugin() = default;

public:
  OdString getName() const;
  OdUInt32 getUnknown() const;
  OdNwOptionsPtr getOptions() const;

public:
  void setName(const OdString& name);
  void setUnknown(OdUInt32 unknown);
  void setOptions(OdNwOptionsPtr pOptions);

protected:
  OdString m_name;
  OdUInt32 m_unknown;
  OdNwOptionsPtr m_pOptions;
};

typedef OdSharedPtr<OdNwCachePlugin> OdNwCachePluginPtr;

#endif //__NWCACHEPLUGIN_INCLUDED_
