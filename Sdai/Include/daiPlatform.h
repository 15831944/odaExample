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


#ifndef _DAI_PLATFORM_H_
#define _DAI_PLATFORM_H_
// Temprary file! After function moving this file should be removed from the solution

#include "OdPlatform.h"

// This function should be tested on different platform. After successful tests we should move it to OdPlatfrom.h
template<class RealType>
inline RealType nanIEEERealCreate()
{
  /*
  int inf = 0x7F800000;
  int nan = 0x7F800001;
  */
  union nanType
  {
    RealType nan;
    unsigned char buf[sizeof(RealType)];
  };

  nanType nanGenerator = { 0 };

#ifdef ODA_BIGENDIAN
  nanGenerator.buf[0] = 0x7F;
  nanGenerator.buf[1] = 0xF0;
  nanGenerator.buf[sizeof(RealType) - 1] = 0x1;
#else
  nanGenerator.buf[sizeof(RealType) - 1] = 0x7F;
  nanGenerator.buf[sizeof(RealType) - 2] = 0xF0;
  nanGenerator.buf[0] = 0x1;
#endif

  return nanGenerator.nan;
}

#endif // _DAI_PLATFORM_H_

