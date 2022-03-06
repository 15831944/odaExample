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
#ifndef __NW_PARTITION_PROPS_STREAMSAVER_H__
#define __NW_PARTITION_PROPS_STREAMSAVER_H__

#include "NwStreamSaver.h"
#include "SharedPtr.h"
#define STL_USING_MEMORY
#include "OdaSTL.h"
#include "TD_PackPush.h"

class OdNwPartitionPropsStreamSaver : public OdNwStreamSaver
{
public:
  OdNwPartitionPropsStreamSaver(const std::shared_ptr<OdNwStreamContext> &ctx);
  virtual ~OdNwPartitionPropsStreamSaver();
  virtual OdResult saveToStream();
};

/** \details
    This template class is a specialization of the OdSharedPtr class for OdNwPartitionPropsStreamSaver object pointers.
*/
typedef OdSharedPtr<OdNwPartitionPropsStreamSaver> OdNwPartitionPropsStreamSaverPtr;

#include "TD_PackPop.h"

#endif // __NW_PARTITION_PROPS_STREAMSAVER_H__
