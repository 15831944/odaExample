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


#ifndef TNW_VIEWPOINT_FLAGS_H_
#define TNW_VIEWPOINT_FLAGS_H_

namespace NwViewpointFlags
{
  enum Enum
  {
    NONE            = 0x0,
    CAMERA          = 0x01,
    VIEWER          = 0x02,
    WORLD_UP_VECTOR = 0x04,
    FOCAL_DISTANCE  = 0x08,
    LINEAR_SPEED    = 0x10,
    ANGULAR_SPEED   = 0x20,
    TOOL            = 0x40,
    TILT_LIMITS     = 0x80,
    LIGHTING        = 0x100,
    RENDER_STYLE    = 0x200,
    PREFERED_FOV    = 0x400,
    PRIMITIVES      = 0x800
  };
}
#endif  // TNW_VIEWPOINT_FLAGS_H_

