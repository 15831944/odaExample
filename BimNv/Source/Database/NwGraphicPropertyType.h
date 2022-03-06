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


#ifndef TNW_GRAPHIC_PROPERTY_TYPE_H_
#define TNW_GRAPHIC_PROPERTY_TYPE_H_

/** \details
  displayed background type

  <group TNW_Namespaces>
*/
namespace NwGraphicPropertyType
{
  enum Enum
  {
    gp_binary = 1,
    gp_bool = 2,
    gp_colorRGB = 3,
    gp_colorRGBA = 4,
    gp_dateTime = 5,
    gp_integer = 6,
    gp_integerArray = 7,
    gp_double = 8,
    gp_doubleArray = 9,
    gp_string = 0xA,
    gp_texture = 0xB,
    gp_URI = 0xC,
    gp_URIArray = 0xD,
    gp_embeddedURI = 0xE,
    gp_choiceList = 0xF,
    gp_uuid = 0x10
  };
}
#endif  // TNW_GRAPHIC_PROPERTY_TYPE_H_

