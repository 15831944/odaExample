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

#ifndef _PRCSOLIDPATTERN_INCLUDED_
#define _PRCSOLIDPATTERN_INCLUDED_ 
 

#include "PrcObjectId.h"
#include "PrcFillPattern.h"
#include "PrcColorIndex.h"

/** \details 
<group PRC_Graphic_Classes> 

Class stores information about a filling pattern with a defined style.
*/
class PRC_TOOLKIT OdPrcSolidPattern : public OdPrcFillPattern
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcSolidPattern)
  //DOM-IGNORE-END

  /** \details
  Sets a new color index.

  \param color_index [in] A new color index to be set.
  */
  void setColor(OdPrcColorIndex color_index = OdPrcColorIndex::kUninit);

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
  Returns the current color index.
  */
  OdPrcColorIndex color() const;

  /** \details
  Returns the current color of the pattern. Will throw an exception in case of uninitialized object.
  */
  const OdPrcRgbColor &getTrueColor() const;
  
  /** \details
  Sets a new value of the material index.

  \param id [in] An identifier of a new material to be set.
  */
  void setMaterialId(const OdPrcObjectId &id);

  /** \details
  Returns the current material index.
  */
  const OdPrcObjectId &material() const;

  /** \details
  Returns the current material index.
  */
  
  /** \details
  Returns the current material flag value.
  The material fill flag indicates whether the filling pattern is applied to a material (true) or to a plain color (false).
  Returns the current material index.
  */
  bool isMaterial() const;
};
SMARTPTR(OdPrcSolidPattern);

#endif // _PRCSOLIDPATTERN_INCLUDED_

