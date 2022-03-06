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

#ifndef _PRCDOTTINGPATTERN_INCLUDED_
#define _PRCDOTTINGPATTERN_INCLUDED_ 
 

#include "PrcFillPattern.h"
#include "PrcColorIndex.h"

/** \details 
<group PRC_Graphic_Classes> 

Class representing a two-dimensional dotting pattern with points.
*/
class PRC_TOOLKIT OdPrcDottingPattern : public OdPrcFillPattern
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcDottingPattern)
  //DOM-IGNORE-END

  /** \details
  Sets a new value for the color index.

  \param color_index [in] An new color index in the color array to be set. 
  */
  void setColor(OdPrcColorIndex color_index = OdPrcColorIndex::kUninit);

  /** \details
  Returns the current value of the color index.
  */
  OdPrcColorIndex color() const;

  /** \details
  Returns the current color of the pattern. Will throw an exception in case of uninitialized object.
  */
  const OdPrcRgbColor &getTrueColor() const;

  /** \details
  Sets a new color for the line style.
  This method sets the material identifier to zero.
  Object must be database resident.

  \param r [in] A new red component value to be set. 0-1 range.
  \param g [in] A new green component value to be set. 0-1 range.
  \param b [in] A new blue component value to be set. 0-1 range.
  \param preventDuplication [in] Add new color to the end of color array or search the array to prevent duplication.
  */
  void setColor(double r, double g, double b, bool preventDuplication = false);

  /** \details
  Sets a new value for the pitch of point spacing.

  \param pitch [in] A new value of the pitch to be set. 
  */
  void setPitch(OdUInt32 pitch);

  /** \details
  Returns the current value of the pitch of point spacing.
  */
  OdUInt32 pitch() const;

  /** \details
  Sets a new value for the zigzag flag.
  The zigzag flag indicates that points are offset along the X-axis at the value of pitch/2.0 for odd rows (if true).
  If the flag is equal to false, points are spaced with the pitch on a regular grid.

  \param zigzag [in] A new zigzag flag value to be set. 
  */
  void setZigzag(bool zigzag);  

  /** \details
  Returns the current value of the zigzag flag.
  The zigzag flag indicates that points are offset along the X-axis at the value of pitch/2.0 for odd rows (if true).
  If the flag is equal to false, points are spaced with the pitch on a regular grid.
  */
  bool zigzag() const;
};
SMARTPTR(OdPrcDottingPattern);

#endif // _PRCDOTTINGPATTERN_INCLUDED_

