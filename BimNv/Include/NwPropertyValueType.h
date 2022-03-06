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


#ifndef TNW_PROPERTY_VALUE_TYPE_H_
#define TNW_PROPERTY_VALUE_TYPE_H_

/** \details
  Contains definitions of property value types.

  <group TNW_Namespaces>

*/
namespace NwPropertyValueType
{
  /** \details
    Defines property value types.
  */
  enum Enum
  {
    /**Default value type.*/
    value_type_default = 0,
    /**Boolean value type.*/
    value_type_bool,
    /**Double value type.*/
    value_type_double,
    /**Float value type.*/
    value_type_float,
    /**Integer value type.*/
    value_type_OdInt32,
    /**Short integer value type.*/
    value_type_OdInt8,
    /**Unsigned integer value type.*/
    value_type_OdUInt32,
    /**Unsigned short integer value type.*/
    value_type_OdUInt8,
    /**OdString value type.*/
    value_type_OdString,
    /**OdStringArray value type.*/
    value_type_OdStringArray,
    /**OdGeVector3d value type.*/
    value_type_OdGeVector3d,
    /**Unsigned long integer value type.*/
    value_type_OdUInt64,
    /**OdNwColor value type.*/
    value_type_OdNwColor,
    /**Date/time value type.*/
    value_type_tm,
    /**GUID value type.*/
    value_type_GUID,
    /**OdGePoint3d value type.*/
    value_type_OdGePoint3d,
    /**OdGePoint2d value type.*/
    value_type_OdGePoint2d,
  };
}
#endif  // TNW_PROPERTY_VALUE_TYPE_H_

