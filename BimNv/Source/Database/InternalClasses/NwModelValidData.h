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

#ifndef __NWMODELVALIDDATA_INCLUDED_
#define __NWMODELVALIDDATA_INCLUDED_

#include "NwCachePlugin.h"
#include "OdArray.h"

class OdNwCacheXref;
typedef OdSharedPtr<OdNwCacheXref> OdNwCacheXrefPtr;
class OdNwCacheOption;
typedef OdSharedPtr<OdNwCacheOption> OdNwCacheOptionPtr;

class OdNwModelValidData : public OdNwCachePlugin
{
public:
  OdNwModelValidData() = default;
  virtual ~OdNwModelValidData() throw() {}

public:
  const OdArray<OdNwCachePluginPtr>& getCachePlugin() const;
  const OdArray<OdNwCacheXrefPtr>& getCacheXref() const;
  const OdArray<OdNwCacheOptionPtr>& getCacheOption() const;
  OdArray<OdNwCachePluginPtr>& getCachePlugin();
  OdArray<OdNwCacheXrefPtr>& getCacheXref();
  OdArray<OdNwCacheOptionPtr>& getCacheOption();

public:
  void addCachePlugin(OdNwCachePluginPtr pCachePlugin);
  void addCacheXref(OdNwCacheXrefPtr pCacheXref);
  void addCacheOption(OdNwCacheOptionPtr pCacheOption);

protected:
  OdArray<OdNwCachePluginPtr> m_aCachePlugin;
  OdArray<OdNwCacheXrefPtr> m_aCacheXref;
  OdArray<OdNwCacheOptionPtr> m_aCacheOption;
};

typedef OdSharedPtr<OdNwModelValidData> OdNwModelValidDataPtr;

#endif //__NWMODELVALIDDATA_INCLUDED_
