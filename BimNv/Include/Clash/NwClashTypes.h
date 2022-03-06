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


#ifndef TNW_CLASH_TYPES_H_
#define TNW_CLASH_TYPES_H_

/** \details
  Contains clast test type definitions.

  <group TNW_Namespaces>
*/
namespace NwClashTestType
{
  /** \details
    Defines clash test types.
  */
  enum Enum
  {
    /** Hard */
    HARD = 0,
    /** Hard (Conservative) */
    HARD_CONSERVATIVE = 0x01,
    /** Clearance */
    CLEARANCE = 0x02,
    /** Duplicates */
    DUPLICATES = 0x03,
    /** Custom */
    CUSTOM = 0x04
  };
}

/** \details
  Contains clash test status type definition.

  <group TNW_Namespaces>
*/
namespace NwClashTestStatusType
{
  /** \details
    Defines clash test status types.
  */
  enum Enum
  {
    /** New */
    NEW = 0,
    /** Old */
    OLD = 0x01,
    /** Partial */
    PARTIAL = 0x02,
    /** OK */
    OK = 0x03
  };
}

/** \details
  Contains clash test result status type definitions.

  <group TNW_Namespaces>
*/
namespace NwClashTestResultStatusType
{
  /** \details
    Defines clash test result status types.
  */
  enum Enum
  {
    /** New */
    NEW = 0,
    /** Active */
    ACTIVE = 1,
    /** Approved */
    APPROVED = 2,
    /** Resolved */
    RESOLVED = 3,
    /** Reviewed */
    REVIEWED = 4,
    /** Num */
    NUM = 5,
    /** Unmerged */
    UNMERGED = 256
  };
}
#endif  // TNW_CLASH_TYPES_H_

