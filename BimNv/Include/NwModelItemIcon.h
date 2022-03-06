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


#ifndef TNW_MODEL_ITEM_ICON_H_
#define TNW_MODEL_ITEM_ICON_H_

/** \details
  Contains model item icon definitions.

  <group TNW_Namespaces>
*/
namespace NwModelItemIcon
{
  /** \details
    Model item icon type.
  */
  enum Enum
  {
    /** Model item don't have type. */
    NONE = 0x0,
    /** Model item type is file. */
    FILE = 0x01,
    /** Model item type is layer. */
    LAYER = 0x02,
    /** Model item type is collection. */
    COLLECTION = 0x03,
    /** Model item type is group. */
    GROUP = 0x04,
    /** Model item type is insert group. */
    INSERT_GROUP = 0x05,
    /** Model item type is composite object. */
    COMPOSITE_OBJECT = 0x06,
    /** Model item type is insert geometry. */
    INSERT_GEOMETRY = 0x07,
    /** Model item type is geometry. */
    GEOMETRY = 0x08
  };
}
#endif  // TNW_MODEL_ITEM_ICON_H_

