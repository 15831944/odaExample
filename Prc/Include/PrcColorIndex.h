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

#ifndef _PRCCOLORINDEX_INCLUDED_
#define _PRCCOLORINDEX_INCLUDED_
 

/** \details 
Class implements functionality of a color index management. 
Color indexes are stored in an array that can be retrieved through calling one of the 
<link !!OVERLOADED_colors_OdPrcFileStructureGlobals, colors()> methods 
of the <link OdPrcFileStructureGlobals, OdPrcFileStructureGlobals> object.
<group PRC_Graphic_Classes> 
*/
class PRC_TOOLKIT OdPrcColorIndex
{
//DOM-IGNORE-BEGIN
private:
  OdUInt16 m_index;

  void validate(OdUInt32 value) const
  {
    if (value > (0xFFFFFFFF - 1)/3)
    {
      throw OdError(eOutOfRange);
    }
  }

  void isValid() const
  {
    if (isInit() == false)
    {
      throw OdError(eNotInitializedYet);
    }
  }
//DOM-IGNORE-END

public:
  /**
  A color index value for the case when the color index object is not initialized (for example, right after its creation).
  */
  PRC_TOOLKIT_STATIC static const OdPrcColorIndex kUninit;

  /** \details 
  Creates a new color index with default parameters (white color). 
  */
  OdPrcColorIndex()
    : m_index(0xFFFF)
  {
  }

  /** \details 
  Creates a new color index with a specified color. 
  \param value [in] A value to be used for the newly created color index.
  */
  OdPrcColorIndex(OdUInt32 value)
  {
    validate(value);
    m_index = value;
  }

  /** \details 
  Assignment operator for the color index object.
  \param value [in] Another color index object to be assigned (right operand of the assignment operation.
  \returns A reference to the color index object after the assignment operation.
  */
  OdPrcColorIndex& operator=(OdUInt32 value)
  {
    validate(value);
    m_index = value;
    return *this;
  }

  /** \details 
  Compares the color index object with a specified color index value.
  \param value [in] A color index value to be compared with.
  \returns true if the color index object is equal to the specified color index value; otherwise, the method returns false.
  */
  bool operator==(OdUInt32 value)
  {
    return m_index == value;
  }

  /** \details 
  Comparision operator for two color index objects.
  \param value [in] Another color index object to be compared with.
  \returns true if color index objects are equal; otherwise, the method returns false.
  */
  bool operator==(const OdPrcColorIndex &value)
  {
    return m_index == value.m_index;
  }

  /** \details 
  Non-equality operator for the color index object and a specified color index value.
  \param value [in] A color index value to be compared with.
  \returns true if the color index object is not equal to the specified color index value; otherwise, the method returns false.
  */
  bool operator!=(OdUInt32 value)
  {
    return m_index != value;
  }

  /** \details 
  Comparision operator for two color index objects.
  \param value [in] Another color index object to be compared with.
  \returns true if color index objects are equal; otherwise, the method returns false.
  */
  bool operator!=(const OdPrcColorIndex &value)
  {
    return m_index != value.m_index;
  }

  /** \details 
  Cast operator for the color index object. 
  It casts the color index object to an appropriate unsigned 32-bit integer value.
  */
  operator OdUInt32() const
  {
    isValid();
    return m_index; 
  }

  /** \details 
  Determines whether the color index object is initialized with a color value that differs from the default (white).
  \returns true if the color index is initialized; otherwise, the method returns false.
  */
  bool isInit() const
  {
    return m_index != 0xFFFF;
  }

  /** \details 
  Clears the color index object. Sets the color index to the white color.
  */
  void clear()
  {
    m_index = 0xFFFF;
  }
};

#endif // _PRCCOLORINDEX_INCLUDED_

