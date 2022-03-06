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
#ifndef __NW_FILEINFOCHUNKSTREAMLOADER_H__
#define __NW_FILEINFOCHUNKSTREAMLOADER_H__

#include "NwStreamLoader.h"
#include "TD_PackPush.h"

class OdNwFileInfo;
typedef OdSmartPtr<OdNwFileInfo> OdNwFileInfoPtr;
class OdNwXRefTable;
typedef OdSharedPtr<OdNwXRefTable> OdNwXRefTablePtr;

class OdNwFileInfoChunkStreamContext : public OdNwStreamContext
{
public:
  explicit OdNwFileInfoChunkStreamContext(const OdNwStreamContext& ctx);
  virtual ~OdNwFileInfoChunkStreamContext() = default;

  OdNwXRefTablePtr getXRefTable() const;
  void setXRefTable(OdNwXRefTablePtr pXRefTable);

protected:
  OdNwXRefTablePtr m_pXRefTable;
};

class OdNwFileInfoChunkStreamLoader : public OdNwStreamLoader
{
public:
  OdNwFileInfoChunkStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual ~OdNwFileInfoChunkStreamLoader();
  static OdNwStreamLoaderPtr createStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual OdResult parseStream() override;
  
public:
  virtual void setLinkLoaderGetter(const std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)>& getLoader) override;

public:
  OdNwFileInfoPtr getFileInfo() const;

protected:
  OdNwFileInfoPtr m_pFileInfo;
  std::function<OdNwStreamLoaderPtr(NwStreamType::Enum)> m_getLoaderCallBack;
};

#include "TD_PackPop.h"

#endif // __NW_FILEINFOCHUNKSTREAMLOADER_H__
