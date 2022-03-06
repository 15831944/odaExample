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
#ifndef __NW_STREAMSAVER_H__
#define __NW_STREAMSAVER_H__

#include "NwDatabase.h"
#include "NwStreamType.h"
#include "NwStreamConfig.h"
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "TD_PackPush.h"

class OdNwStreamContext;
typedef std::shared_ptr<OdNwStreamContext> OdNwStreamContextPtr;

class OdNwStreamSaver
{
public:
  OdNwStreamSaver(const OdNwStreamContextPtr& ctx);
  virtual ~OdNwStreamSaver();

  OdString getName() const;
  void setName(const OdString& name);

  OdNwStreamContextPtr context();

  virtual OdResult saveToStream() = 0;
  NwSubStreamDefBase getStreamDef() const;

protected:
  OdUInt32                           m_nBitfield;
  bool                               m_bSaved;
  OdNwStreamContextPtr               m_context;
  NwSubStreamDefBase                 m_oStreamDef;
};

typedef std::shared_ptr<OdNwStreamSaver> OdNwStreamSaverPtr;
typedef std::weak_ptr<OdNwStreamSaver> OdNwStreamSaverWeakPtr;

#include "TD_PackPop.h"

#endif // __NW_STREAMSAVER_H__
