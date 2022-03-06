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


#ifndef TNW_GRAPHIC_PROPERTY_MODEL_UNITS_H_
#define TNW_GRAPHIC_PROPERTY_MODEL_UNITS_H_

namespace NwGraphicPropertyModelUnits
{
  enum Enum
  {
    empty       = 0x0000,
    milimeters  = 0x2001,
    centimeters = 0x2009,
    decimeters  = 0x200C,
    meters      = 0x200D,
    kilometers  = 0x200E,
    inches      = 0x2016,
    foots       = 0x2017,
    yards       = 0x201D,
    miles       = 0x2021
  };
}
#endif  // TNW_GRAPHIC_PROPERTY_MODEL_UNITS_H_

