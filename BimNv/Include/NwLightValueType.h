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


#ifndef TNW_LIGHT_VALUE_TYPE_H_
#define TNW_LIGHT_VALUE_TYPE_H_

/** \details
  Bit masks for getting types of values from a texture.

  <group TNW_Namespaces>
*/
namespace NwLightValueType
{
  enum Enum
  {
    /**OdNwColor value for the filter color of a common light.*/
    light_filter_color           = 0,
    /**OdNwColor value for the tint color of a common light.*/
    light_tint_color             = 1,
    /**OdNwColor value for the RGB light color of a common light.*/
    light_rgb_color              = 2,
    /**OdNwColor value for the shadow color of a common light.*/
    light_shadow_color           = 3,
    /**Double value for the intensity of a common light.*/
    light_intensity_value        = 4,
    /**Bool value for the target status of a position light.*/
    light_position_is_targeted   = 5,
    /**Matrix value for the web rotation, scale, and translation of a spot light.*/
    light_spot_web_matrix        = 6,
    /**Bool value for the ambient-only status of a common light.*/
    light_ambient_only_flag      = 7,
    /**Bool value for the tint-use status of a common light.*/
    light_use_tint_flag          = 8,
    /**Bool value for the shadow-enabled status of a common light.*/
    light_shadow_on_flag         = 9
  };
}
#endif  // TNW_LIGHT_VALUE_TYPE_H_

