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


#ifndef TNW_SHEET_TYPE_H_
#define TNW_SHEET_TYPE_H_

/** \details
  Contains sheet type definitions.

  <group TNW_Namespaces>
*/
namespace NwSheetType
{
  /** \details
    This enumeration specifies sheet types.
  */
  enum Enum
  {
    /** 3D type of sheet */
    Sheet3d = 0,
    /** 2D type of sheet */
    Sheet2d = 1,
  };
}
#endif  // TNW_SHEET_TYPE_H_

