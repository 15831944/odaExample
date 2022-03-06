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


#ifndef TNW_MODE_TYPE_H_
#define TNW_MODE_TYPE_H_

/** \details
  Style used for rendering.

  <group TNW_Namespaces>
*/
namespace NwModeType
{
  enum Enum
  {
    /**Highest quality, as specified in the model.*/
    FULL_RENDER = 0,
    /**Smooth shaded (simple shaded model, no textures).*/
    SHADED = 2,
    /**Wireframe.*/
    WIREFRAME = 3,
    /**Hidden line wireframe.*/
    HIDDEN_LINE = 4
  };
}
#endif  // TNW_MODE_TYPE_H_

