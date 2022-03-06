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


#ifndef TNW_PRIMITIVE_TYPES_H_
#define TNW_PRIMITIVE_TYPES_H_

/** \details
  Different types of primitive used to define geometry.

  <group TNW_Namespaces>
*/
namespace NwPrimitiveTypes
{
  enum Enum
  {
    /**No primitives.*/
    NONE      = 0x00,
    /**Has triangle primitives.*/
    TRIANGLES  = 0x01,
    /**Has line primitives.*/
    LINES      = 0x02,
    /**Has point primitives.*/
    POINTS     = 0x04,
    /**Has snap point primitives.*/
    SNAPPOINTS = 0x08,
    /**Has text primitives.*/
    TEXT       = 0x10,
    /**Has solid primitives.*/
    SOLID      = 0x20
  };
}

#endif  // TNW_PRIMITIVE_TYPES_H_

