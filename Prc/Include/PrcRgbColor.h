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

#ifndef _PRCRGBCOLOR_INCLUDED_
#define _PRCRGBCOLOR_INCLUDED_ 

#include "CmColorBase.h"

 

/** \details 
<group PRC_Graphic_Classes> 

Class representing a color defined with 3 components: red, green, blue. 
*/
class PRC_TOOLKIT OdPrcRgbColor
{
private:
  double m_r, m_g, m_b;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcRgbColor)
  //DOM-IGNORE-END

  /** \details
  Creates a new RGB color object with specified color components.

  \param r [in] A new red component value to be set. 0-1 range.
  \param g [in] A new green component value to be set. 0-1 range.
  \param b [in] A new blue component value to be set. 0-1 range.
  \remarks 
  The method sets the newly created color object color components to defaults if specified components are not in the range.
  */
  OdPrcRgbColor(double r, double g, double b);

  /** \details
  Creates a new RGB color object basing on a specified OdCmEntityColor object.

  \param color [in] An OdCmEntityColor object .
  */
  OdPrcRgbColor(const OdCmEntityColor & color);

  /** \details
  Retrieves the current red component value. 
  \returns A double value that represents the red component of the color object.
  */
  double r() const;

  /** \details
  Retrieves the current green component value. 
  \returns A double value that represents the green component of the color object.
  */
  double g() const;

  /** \details
  Retrieves the current blue component value. 
  \returns A double value that represents the blue component of the color object.
  */
  double b() const;

  /** \details
  Retrieves the values of the color object components.

  \param r [out] A placeholder for the red component value.
  \param g [out] A placeholder for the green component value.
  \param b [out] A placeholder for the blue component value.
  \remarks 
  The method fills the passed values and returns them to a calling subroutine.
  */
  void get(double &r, double &g, double &b) const;

  /** \details
  Sets new values of the color components.

  \param r [in] A new red component value to be set. 0-1 range.
  \param g [in] A new green component value to be set. 0-1 range.
  \param b [in] A new blue component value to be set. 0-1 range.
  
  \returns eOk if new component values were successfully set or an appropriate error code in the other case.
  */
  OdResult set(double r, double g, double b);

  /** \details
  Sets a new red component value.

  \param r [in] A new red component value to be set. 0-1 range.
  
  \returns Returns eOk if a new red component value was successfully set or an appropriate error code in the other case.
  */
  OdResult setR(double r);

  /** \details
  Sets a new green component value. 0-1 range.

  \param g [in] A new green component value to be set.
  
  \returns Returns eOk if a new green component value was successfully set or an appropriate error code in the other case.
  */
  OdResult setG(double g);

  /** \details
  Sets a new blue component value. 0-1 range.

  \param b [in] A new blue component value to be set.
  
  \returns Returns eOk if a new blue component value was successfully set or an appropriate error code in the other case.
  */
  OdResult setB(double b);

  /** \details
  Compare operator for the color.

  \param color [in] An operand to be compared with.
  
  \returns Returns true if the color and operand are equal or false in the other case.
  */
  bool operator ==(const OdPrcRgbColor &color) const;

  /** \details 
  Retrieves the true color of the RGB color object.
  \returns An OdCmEntityColor that represent the true color.
  */
  OdCmEntityColor getTrueColor() const;
  
  /** \details 
  An assignment operator for the RGB color object.
  \param color [in] Another color object that acts as the right operand of the assignment operation.
  \returns The reference to the RGB color object after the assignment operation.
  */
  OdPrcRgbColor & operator=(const OdCmEntityColor& color);
};

typedef OdArray<OdPrcRgbColor> OdPrcRgbColorArray;

#endif // _PrcRgbColor_INCLUDED_

