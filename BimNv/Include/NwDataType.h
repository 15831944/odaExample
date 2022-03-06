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


#ifndef TNW_DATA_TYPE_H_
#define TNW_DATA_TYPE_H_

/** \details
  Contains definitions of data property value types.

  <group TNW_Namespaces>
*/
namespace NwDataType
{
  /** \details
    Defines data property value types.
  */
  enum Enum
  {
    /**Default value type.*/
    dt_NONE = 0,
    /**Double value type.*/
    dt_DOUBLE = 0x01,
    /**32-bit integer value type.*/
    dt_INT32 = 0x02,
    /**Boolean value type.*/
    dt_BOOL = 0x03,
    /**Display end-user string value type.*/
    dt_DISPLAY_STRING = 0x04,
    /**Datetime value type.*/
    dt_DATETIME = 0x05,
    /**Double value type for length (in length's units).*/
    dt_DOUBLE_LENGTH = 0x06,
    /**Double value type for angle (in radians).*/
    dt_DOUBLE_ANGLE = 0x07,
    /**Name value type (with a pointer to an OdNwName object).*/
    dt_NAME = 0x08,
    /**Programmatic identifier string value type.*/
    dt_IDENTIFIER_STRING = 0x09,
    /**Double value type for area.*/
    dt_DOUBLE_AREA = 0x0A,
    /**Double value type for volume.*/
    dt_DOUBLE_VOLUME = 0x0B,
    /**Point3d value type.*/
    dt_POINT3D = 0x0C,
    /**Point2d value type.*/
    dt_POINT2D = 0x0D
  };
}
#endif  // TNW_DATA_TYPE_H_

