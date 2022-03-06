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
#ifndef __NW_BACKGROUNDSTREAMLOADER_H__
#define __NW_BACKGROUNDSTREAMLOADER_H__

#include "NwStreamLoader.h"
#include "NwFormatVersionEx.h"
#include "NwBackgroundElement.h"
#include "TD_PackPush.h"

class OdNwBackgroundElementStreamLoader : public OdNwStreamLoader
{
public:
  OdNwBackgroundElementStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual ~OdNwBackgroundElementStreamLoader();
  static OdNwStreamLoaderPtr createStreamLoader(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual OdResult parseStream() override;

  OdNwObjectId getBackgroundElement();
  void setBackgroundElement(OdNwBackgroundElementPtr);

private:
  OdNwObjectId m_BackgroundElementId;
};

typedef std::shared_ptr<OdNwBackgroundElementStreamLoader> OdNwBackgroundElementStreamLoaderPtr;
typedef std::weak_ptr<OdNwBackgroundElementStreamLoader> OdNwBackgroundElementStreamLoaderWeakPtr;

#include "TD_PackPop.h"

#endif // __NW_BACKGROUNDSTREAMLOADER_H__
