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
#ifndef __NW_SAVED_ANIMATIONS_SAVER_H__
#define __NW_SAVED_ANIMATIONS_SAVER_H__

#include "NwStreamSaver.h"
#include "TD_PackPush.h"

class OdNwSavedAnimationsSaver : public OdNwStreamSaver
{
public:
  OdNwSavedAnimationsSaver(const OdNwStreamContextPtr& ctx);
  virtual ~OdNwSavedAnimationsSaver();
  virtual OdResult saveToStream();

  void setElement(OdNwObjectId elementId);

private:
  OdNwObjectId m_elementId;
};

typedef std::shared_ptr<OdNwSavedAnimationsSaver> OdNwSavedAnimationsSaverPtr;

#include "TD_PackPop.h"

#endif // __NW_SAVED_ANIMATIONS_SAVER_H__
