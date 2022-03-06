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


#ifndef TNW_AUTODESK_MATERIAL_PROPERTY_VALUE_TYPE_H_
#define TNW_AUTODESK_MATERIAL_PROPERTY_VALUE_TYPE_H_

namespace NwAutodeskMaterialPropertyValueType
{
  enum Enum
  {
    AMPR_VALUE_BOOL = 0x02,
    AMPR_VALUE_COLOR = 0x04,
    AMPR_VALUE_INT = 0x06,
    AMPR_VALUE_DOUBLE = 0x08,
    AMPR_VALUE_VECTOR = 0x09,
    AMPR_VALUE_STRING = 0x0A,
    AMPR_VALUE_TEXTURE = 0x0B,
    AMPR_VALUE_IMAGE_PATH = 0x0C,
    AMPR_VALUE_LIST = 0x0F,
    AMPR_VALUE_UNKNOWN_X10 = 0x10, // TODO: try to find value. Now detected only empty value.
  };
}

#endif  // TNW_AUTODESK_MATERIAL_PROPERTY_VALUE_TYPE_H_

