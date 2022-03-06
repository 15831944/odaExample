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


#ifndef TNW_CLIPPLANE_ALIGNMENT_H_
#define TNW_CLIPPLANE_ALIGNMENT_H_

/** \details
  Contains clipping plane alignment definitions.

  <group TNW_Namespaces>
*/
namespace NwClipPlaneAlignment
{
  /** \details
    Clipping plane alignment type.
  */
  enum Enum
  {
    /** Type is unset. */
    AL_NONE = 0x00,
    /** View clip plane. */
    TO_VIEW = 0x01,
    /** Back clip plane. */
    BACK = 0x02,
    /** Front clip plane. */
    FRONT = 0x03,
    /** Left clip plane. */
    LEFT = 0x04,
    /** Right clip plane. */
    RIGHT = 0x05,
    /** Top clip plane. */
    TOP = 0x06,
    /** Bottom clip plane. */
    BOTTOM = 0x07,
    /** Surface clip plane. */
    TO_SURFACE = 0x08,
    /** Line clip plane. */
    TO_LINE = 0x09,
    /** Custom clip plane. */
    CUSTOM = 0x0A,
  };
}
#endif  // TNW_CLIPPLANE_ALIGNMENT_H_

