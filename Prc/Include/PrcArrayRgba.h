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

#ifndef _PRCARRAYRGBA_INCLUDED_
#define _PRCARRAYRGBA_INCLUDED_ 
 

  /** \details
    <group PRC_Graphic_Classes>

    Class representing an array of RGB or RGBA colors.
  */
class PRC_TOOLKIT OdPrcArrayRgba
{
private:
  OdUInt8Array  m_Colors;
  bool          m_is_rgba;


public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcArrayRgba)
  //DOM-IGNORE-END

  /** \details
    Returns current colors.
    Colors are returned as a reference to an OdInt8Array object, therefore it can be used to set a new array of RGBA colors.
  */
  OdUInt8Array &colors();

  /** \details
    Returns current colors.
  */
  const OdUInt8Array &colors() const;

  /** \details
    Returns the current value of the RGBA flag.
    The RGBA flag determines whether current colors are RGBA (if true) or RGB (if false) colors.
    The flag value is returned as a reference to a boolean value, therefore it can be used to set a new value of the RGBA flag.
  */
  bool &isRgba();

  /** \details
    Returns the current value of the RGBA flag.
    The RGBA flag determines whether current colors are RGBA (if true) or RGB (if false) colors.
  */
  const bool &isRgba() const;

  /** \details
    Returns true if color array is empty or false in the other case.
  */
  bool isEmpty() const;

  /** \details
    Sets a new size of color array and new value of RGBA flag.

    \param num [in] A new size of the color array to be set.
    \param is_rgba [in] A new value of the RGBA flag.
    
    RGBA flag determines whether all colors in the array are RGBA (if true) or RGB (if false) colors.
  */
  void setNumOfColors(OdUInt32 num, bool is_rgba);

  /** \details
    Clears an array of colors.
  */
  void clear();
};

#endif // _PRCARRAYRGBA_INCLUDED_

