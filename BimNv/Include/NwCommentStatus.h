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


#ifndef TNW_COMMENT_STATUS_H_
#define TNW_COMMENT_STATUS_H_

/** \details
  Contains the comment status type definition.

  <group TNW_Namespaces>
*/
namespace NwCommentStatus
{
  /** \details
    Defines comment status types.
  */
  enum Enum
  {
    /**New comment.*/
    NEW = 0x00,
    /**Active comment.*/
    ACTIVE = 0x01,
    /**Comment is approved.*/
    APPROVED = 0x02,
    /**Comment is resolved.*/
    RESOLVED = 0x03
  };
}
#endif  // TNW_COMMENT_STATUS_H_

