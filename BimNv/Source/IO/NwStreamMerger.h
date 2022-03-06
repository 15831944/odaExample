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

#ifndef __NWSTREAMMERGER_H__
#define __NWSTREAMMERGER_H__

#include "NwExport.h"
#include "OdBinaryData.h"
#include "NwStreamType.h"
#include "NwStreamConfig.h"

class OdNwStreamMerger
{
public:
  OdNwStreamMerger()
    : m_nInternalVersion (8)
    , m_nVersion (448)
  {}
  virtual ~OdNwStreamMerger() 
  {}

public:
  void setVersion(OdInt32);
  void setInternalVersion(OdInt32);
  void setStreamConfig(TNwStreamConfig config);
  OdResult addStream(NwSubStreamDefBase streamDef);

  OdNwSaveError::Enum writeHeader(OdStreamBufPtr stream);
  OdNwSaveError::Enum writeTail(OdStreamBufPtr stream);

private:
  OdInt32 m_nInternalVersion;
  OdInt32 m_nVersion;
  TNwStreamConfig m_oStreamConfig;
  OdArray<NwSubStreamDefBase> m_aSubStreamsDefs;
};


#endif // __NWSTREAMMERGER_H__
