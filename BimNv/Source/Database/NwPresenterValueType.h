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


#ifndef TNW_PRESENTER_VALUE_TYPE_H_
#define TNW_PRESENTER_VALUE_TYPE_H_

namespace NwPresenterValueType
{
  enum Enum
  {
    P_VALUE_INT32 = 0x01,
    P_VALUE_NAT32 = 0x02,
    P_VALUE_DOUBLE = 0x03,
    P_VALUE_ENUM = 0x05,
    P_VALUE_BOOL = 0x06,
    P_VALUE_COLOR = 0x07,
    P_VALUE_FLOAT3_1 = 0x08,
    P_VALUE_FLOAT3_2 = 0x09,
    P_VALUE_STRING = 0x0A,
  };
}
#endif  // TNW_PRESENTER_VALUE_TYPE_H_

