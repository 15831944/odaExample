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
#ifndef __NW_GEOMETRYSTREAMLOADERMT_H__
#define __NW_GEOMETRYSTREAMLOADERMT_H__

#include "NwGeometryStreamLoader.h"
#pragma push_macro("free")
#undef free
#if defined(ODA_WINDOWS)
#ifndef _TOOLKIT_IN_DLL_ 
#define __TBB_NO_IMPLICIT_LINKAGE 1
#endif
#endif
#include "tbb/spin_mutex.h"
#pragma pop_macro("free")

#include "TD_PackPush.h"

class OdNwGeometryStreamLoaderMT : public OdNwGeometryStreamLoader
{
public:
  OdNwGeometryStreamLoaderMT(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual ~OdNwGeometryStreamLoaderMT();
  static OdNwStreamLoaderPtr createStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  OdResult parseStream() override;
  OdStreamBufPtr getStream(OdUInt64 nElementPos, OdUInt64 nElementEnd) override;

protected:
  tbb::spin_mutex m_mutexGeomArray;
  tbb::spin_mutex m_mutexStreamBuf;
};

#include "TD_PackPop.h"

#endif // __NW_GEOMETRYSTREAMLOADERMT_H__
