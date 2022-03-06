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


#ifndef TNW_LIGHT_TYPE_H_
#define TNW_LIGHT_TYPE_H_

/** \details
  Type of lighting used for a viewpoint.

  <group TNW_Namespaces>
*/
namespace NwLightType
{
  enum Enum
  {
    /**Turns off lighting completely.*/
    NO_LIGHT = 0,
    /**Uses lights from the user in the model.*/
    SCENE_LIGHT = 1,
    /**Uses an automatic headlight from the viewer.*/
    HEAD_LIGHT = 2,
    /**Uses advanced level of lighting from the application.*/
    FULL_LIGHT = 3
  };
}
#endif  // TNW_LIGHT_TYPE_H_

