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

#ifndef __NW_CMCOLOR_H__
#define __NW_CMCOLOR_H__

#include "TD_PackPush.h"

#include "NwExport.h"
#include "OdString.h"
#include "CmColorBase.h"

/** \details
  This class represents the entity color object that represents the unnamed
  colors specified by the byLayer, byBlock, byColor, byACI, byPen, Foreground,
  byDgnIndex, or None color methods.

  \remarks
  The entity color object can specify any of the following color methods:

  <table>
  <b>Name</b>    <b>Value</b>    <b>Description</b>
  kByLayer       0xC0            Color is specified by the layer object on which the object resides.
  kByBlock       0xC1            Color is specified by the block object in which the object is contained.
  kByColor       0xC2            Color is specified by an RGB value.
  kByACI         0xC3            Color is specified by an index (ACI) of a color palette.
  kByPen         0xC4            Color is specified by an index of a pen color table.
  kForeground    0xC5            Color is the same as the foreground color.
  kByDgnIndex    0xC7            Color is specified by an index of a .dgn color table.
  kNone          0xC8            Color is absent (object is clear).
  </table>

  An entity has no color from the time it is first instantiated until it is
  assigned one or added to a database. The ColorMethod enumeration defines the
  constants for color methods.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwCmColor : public OdCmColorBase
{
public:
  /** \details
    Default constructor for objects of the OdNwCmColor class.
  */
  OdNwCmColor();

  /** \details
    Copy constructor for objects of the OdNwCmColor class. Creates a copy of the
    specified object of the OdNwCmColor class.
    \param color [in] OdNwCmColor object to be copied.
  */
  OdNwCmColor(
    const OdNwCmColor& color);

  /** \details
    Constructor for objects of the OdNwCmColor class. Creates an object of the
    OdNwCmColor class with the specified color value specified by the object of
    the OdCmColorBase class.
    \param color [in] Color value.
  */
  OdNwCmColor(
    const OdCmColorBase& color);

  /** \details
    Constructor for objects of the OdNwCmColor class. Creates an object of the
    OdNwCmColor class with the specified color method value.
    \param color [in] Color method value.
    \remarks
    The color method value must be one of the following:

    <table>
    <b>Name</b>    <b>Value</b>    <b>Description</b>
    kByLayer       0xC0            Color is specified by the layer object on which the object resides.
    kByBlock       0xC1            Color is specified by the block object in which the object is contained.
    kByColor       0xC2            Color is specified by an RGB value.
    kByACI         0xC3            Color is specified by an index (ACI) of a color palette.
    kByPen         0xC4            Color is specified by an index of a pen color table.
    kForeground    0xC5            Color is the same as the foreground color.
    kByDgnIndex    0xC7            Color is specified by an index of a .dgn color table.
    kNone          0xC8            Color is absent (object is clear).
    </table>
  */
  OdNwCmColor(
    OdCmEntityColor::ColorMethod color);

  /** \details
    Assignment operator for objects of the OdNwCmColor class. Assigns the
    specified object of the OdNwCmColor class to this object.
    \param color [in] OdNwCmColor object to assign to this object.
    \returns This OdNwCmColor object.
  */
  OdNwCmColor& operator=(
    const OdNwCmColor& color);

  /** \details
    Assignment operator for objects of the OdNwCmColor class. Assigns the
    specified object of the OdCmColorBase class to this object.
    \param color [in] OdCmColorBase object to assign to this object.
    \returns This OdNwCmColor object.
  */
  OdNwCmColor& operator=(
    const OdCmColorBase& color);

  /** \details
    Default destructor for objects of the OdNwCmColor class. Frees allocated
    resources.
  */
  ~OdNwCmColor();


  /** \details
    Comparison operator. Compares the specified object of the OdNwCmColor class
    with this object.
    \param color [in] OdNwCmColor object to compare with this object.
    \returns True if compared objects are equal; false otherwise.
  */
  bool operator ==(
    const OdNwCmColor& color) const;

  /** \details
    Negative comparison operator. Compares the specified object of the
    OdNwCmColor class with this object.
    \param color [in] OdNwCmColor object to compare with this object.
    \returns True if compared objects are not equal; false otherwise.
  */
  bool operator !=(
    const OdNwCmColor& color) const;

  /** \details
    Comparison operator. Compares the specified object of the OdCmColorBase
    class with this object.
    \param color [in] OdCmColorBase object to compare with this object.
    \returns True if color values of compared objects are equal; false
    otherwise.
  */
  bool operator ==(
    const OdCmColorBase& color) const;

  /** \details
    Negative comparison operator. Compares the specified object of the
    OdCmColorBase class with this object.
    \param color [in] OdCmColorBase object to compare with this object.
    \returns True if color values of compared objects are not equal; false
    otherwise.
  */
  bool operator !=(
    const OdCmColorBase& color) const;

  // ------------OdCmColorBase----------------------

  /** \details
    Returns the color method of this color object.
    \returns Color method value.
    \remarks
    The color method value must be one of the following:

    <table>
    <b>Name</b>    <b>Value</b>    <b>Description</b>
    kByLayer       0xC0            Color is specified by the layer object on which the object resides.
    kByBlock       0xC1            Color is specified by the block object in which the object is contained.
    kByColor       0xC2            Color is specified by an RGB value.
    kByACI         0xC3            Color is specified by an index (ACI) of a color palette.
    kByPen         0xC4            Color is specified by an index of a pen color table.
    kForeground    0xC5            Color is the same as the foreground color.
    kByDgnIndex    0xC7            Color is specified by an index of a .dgn color table.
    kNone          0xC8            Color is absent (object is clear).
    </table>
  */
  virtual OdCmEntityColor::ColorMethod colorMethod() const;

  /** \details
    Sets the color method for this color object.
    \param colorMethod [in] Color method value.
    \remarks
    The color method value must be one of the following:

    <table>
    <b>Name</b>    <b>Value</b>    <b>Description</b>
    kByLayer       0xC0            Color is specified by the layer object on which the object resides.
    kByBlock       0xC1            Color is specified by the block object in which the object is contained.
    kByColor       0xC2            Color is specified by an RGB value.
    kByACI         0xC3            Color is specified by an index (ACI) of a color palette.
    kByPen         0xC4            Color is specified by an index of a pen color table.
    kForeground    0xC5            Color is the same as the foreground color.
    kByDgnIndex    0xC7            Color is specified by an index of a .dgn color table.
    kNone          0xC8            Color is absent (object is clear).
    </table>
  */
  virtual void setColorMethod(OdCmEntityColor::ColorMethod colorMethod);

  /** \details
    Indicates whether the color method of this object is kByColor.
    \returns True if the color method of this object is kByColor; false
    otherwise.
  */
  virtual bool isByColor() const;

  /** \details
    Indicates whether the color method of this object is kByLayer.
    \returns True if the color method of this object is kByLayer; false
    otherwise.
  */
  virtual bool isByLayer() const;

  /** \details
    Indicates whether the color method of this object is kByBlock.
    \returns True if the color method of this object is kByBlock; false
    otherwise.
  */
  virtual bool isByBlock() const;

  /** \details
    Indicates whether the color method of this object is kByACI.
    \returns True if the color method of this object is kByACI; false
    otherwise.
  */
  virtual bool isByACI() const;

  /** \details
    Indicates whether the color method of this object is kForeground.
    \returns True if the color method of this object is kForeground; false
    otherwise.
  */
  virtual bool isForeground() const;

  /** \details
    Indicates whether the color method of this object is kByDgnIndex.
    \returns True if the color method of this object is kByDgnIndex; false
    otherwise.
  */
  virtual bool isByDgnIndex() const;

  /** \details
    Indicates whether the color method of this object is kNone.
    \returns True if the color method of this object is kNone; false
    otherwise.
  */
  virtual bool isNone() const;

  /** \details
    Returns the color value of this color object.
    \returns Color value.
  */
  virtual OdUInt32  color() const;

  /** \details
    Sets the color value for this color object.
    \param color [in] Color value.
  */
  virtual void setColor(OdUInt32 color);

  /** \details
    Sets the RGB color value for this color object.
    \param red   [in] Red channel value.
    \param green [in] Green channel value.
    \param blue  [in] Blue channel value.
  */
  virtual void setRGB(OdUInt8 red,
                      OdUInt8 green,
                      OdUInt8 blue);

  /** \details
    Sets the RGB color value for this color object.
    \param rgb [in] RGB color value.
  */
  virtual void setRGB(OdUInt32 rgb);

  /** \details
    Sets the red channel value of the RGB color for this color object.
    \param red [in] Red channel value of the RGB color.
  */
  virtual void setRed(OdUInt8 red);

  /** \details
    Sets the green channel value of the RGB color for this color object.
    \param green [in] Green channel value of the RGB color.
  */
  virtual void setGreen(OdUInt8 green);

  /** \details
    Sets the blue channel value of the RGB color for this color object.
    \param blue [in] Blue channel value of the RGB color.
  */
  virtual void setBlue(OdUInt8 blue);

  /** \details
    Returns the red channel value of the RGB color of this color object.
    \returns Red channel value of the RGB color.
  */
  virtual OdUInt8 red() const;

  /** \details
    Returns the green channel value of the RGB color of this color object.
    \returns Green channel value of the RGB color.
  */
  virtual OdUInt8 green() const;

  /** \details
    Returns the blue channel value of the RGB color of this color object.
    \returns Blue channel value of the RGB color.
  */
  virtual OdUInt8 blue() const;

  /** \details
    Returns the color index of this color object.
    \returns Color index value.
  */
  virtual OdUInt16 colorIndex() const;

  /** \details
    Sets the color index for this color object.
    \param colorIndex [in] Color index value.
  */
  virtual void setColorIndex(OdUInt16 colorIndex);

  /** \details
    Sets the color name and book name for this color object.
    \param colorName [in] Color name.
    \param bookName  [in] Book name.
    \returns False if the color name parameter is an empty string while the book
    name parameter is not empty; true otherwise.
  */
  virtual bool  setNames( const OdString& colorName,
                          const OdString& bookName = OdString::kEmpty);

  /** \details
    Returns the color name of this color object.
    \returns Color name.
  */
  virtual OdString colorName() const;

  /** \details
    Returns the book name of this color object.
    \returns Book name.
  */
  virtual OdString bookName() const;

  /** \details
    Returns the displayed color name of this color object.
    \returns Displayed color name.
  */
  virtual OdString colorNameForDisplay() const;

  /** \details
    Converts this color object to the OdCmEntityColor object.
    \returns Resulting OdCmEntityColor object.
  */
  OdCmEntityColor toCmEntityColor() const;

private:
  //DOM-IGNORE-BEGIN
  OdCmEntityColor::RGBM   m_RGBM;
  OdString                m_colorName;
  OdString                m_bookName;
  //DOM-IGNORE-END
};

/** \details
  Swaps red and blue color channels in the source RGB color value
  (ARGB &lt;--&gt; ABGR).
  \param src [in] Source RGB color value.
  \returns Resulting RGB color value with swapped red and blue color channels.
*/
NWDBEXPORT const OdUInt32 swapRGB(const OdUInt32 src);

#include "TD_PackPop.h"

#endif // __NW_CMCOLOR_H__
