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


#ifndef TNW_TEXTURE_SPACE_MAPPING_H_
#define TNW_TEXTURE_SPACE_MAPPING_H_

/** \details
  Type of texture space mapping.

  <group TNW_Namespaces>
*/
namespace NwTextureSpaceMapping
{
  enum Enum
  {
    /**Box space mapping.*/
    kBox = 0x0,
    /**Plane space mapping.*/
    kPlane = 0x1,
    /**Cylinder space mapping.*/
    kCylinder = 0x2,
    /**Sphere space mapping.*/
    kSphere = 0x3,
    /**Explicit space mapping.*/
    kExplicit = 0x4
  };
}
#endif  // TNW_TEXTURE_SPACE_MAPPING_H_

