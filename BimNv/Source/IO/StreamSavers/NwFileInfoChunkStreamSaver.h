  /////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2018, Open Design Alliance (the "Alliance"). 
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
//   This application incorporates Teigha(R) software pursuant to a license 
//   agreement with Open Design Alliance.
//   Teigha(R) Copyright (C) 2002-2019 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////
#ifndef __NW_GILEINFOCHUNKSTREAMSAVER_H__
#define __NW_GILEINFOCHUNKSTREAMSAVER_H__

#include "NwStreamSaver.h"
#include "SharedPtr.h"
#include "TD_PackPush.h"

class OdNwFileInfoChunkStreamSaver : public OdNwStreamSaver
{
public:
  explicit OdNwFileInfoChunkStreamSaver(const OdNwStreamContextPtr& ctx);
  virtual ~OdNwFileInfoChunkStreamSaver();
  virtual OdResult saveToStream();

  void setFileInfo(OdNwObjectId fileInfoId);

private:
  OdNwObjectId m_fileInfoId;
};

typedef std::shared_ptr<OdNwFileInfoChunkStreamSaver> OdNwFileInfoChunkStreamSaverPtr;
typedef std::weak_ptr<OdNwFileInfoChunkStreamSaver> OdNwFileInfoChunkStreamSaverWeakPtr;

#include "TD_PackPop.h"

#endif // __NW_GILEINFOCHUNKSTREAMSAVER_H__
