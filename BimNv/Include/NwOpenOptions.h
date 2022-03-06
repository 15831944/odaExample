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


#ifndef TNW_OPEN_OPTIONS_H_
#define TNW_OPEN_OPTIONS_H_

/** \details
  Contains definitions of open options.

  <group TNW_Namespaces>
*/
namespace NwOpenOptions
{
  /** \details
    Defines data property value types.
  */
  enum Enum
  {
    /**Cache geometry.*/
    kOptionCacheGeometry = 0x00,
    /**Draw parametric geometry line circles and cylinders*/
    kOptionDrawParametricGeometry = 0x01,
    /**Load compressed data on-the-fly*/
    kOptionLoadCompressedDataOnFly = 0x02,
    /**Save compressed geometry flag
    It is a combination of values:
    0x0001 - compress vertices on saving
    0x0002 - compress normals on saving
    */
    kOptionSaveCompressedGeometryFlag = 0x20
  };
}
#endif  // TNW_OPEN_OPTIONS_H_

