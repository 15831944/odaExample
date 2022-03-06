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


///////////////////////////////////////////////////////////////////////////////
//
// PdfPublishTextField.h
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PDF_PUBLISH_TEXTFIELD_INCLUDED_
#define _PDF_PUBLISH_TEXTFIELD_INCLUDED_

#include "PdfPublishBaseObject.h"

/** \details
  Contains declarations for Publish SDK.
  <group TD_Namespaces>
*/
namespace OdPdfPublish{

/** \details
  This class implements a text field control contained in a .pdf document created with Publish SDK.
  A text field allows entry of text information with specified format options.
*/
class PDFPUBLISH_TOOLKIT OdTextField : public OdObject
{
  //DOM-IGNORE-BEGIN
protected:
  OdTextField();
  //DOM-IGNORE-END
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdTextField);
  ODRX_HEAP_OPERATORS();
  //DOM-IGNORE-END
 
  /** \details
    Destroys the text field.
  */
  virtual ~OdTextField();

  /** \details
    Sets the text field name.
    
    \param name [in] A new text field name.

    \remarks
    The name is mandatory and must be unique among the document object names.
  */
  void setName(const OdString& name);
  
  /** \details
    Sets the text field font type from the list of <link OdPdfPublish::Text::StandardFontsType,  predefined fonts>. 
    
    \param fontType [in] A new font type value.
    
    \sa 
    <link OdPdfPublish::Text::StandardFontsType, Text::StandardFontsType enumeration>.
  */
  void setFont(Text::StandardFontsType fontType);

  /** \details
    Sets the text field font name and style. 
    
    \param fontName  [in] A new font name.
    \param fontStyle [in] A new font style.
    
    \remarks
    This method can set a font that is not in the list of 
    <link OdPdfPublish::Text::StandardFontsType, standard fonts>.
    By default the <link OdPdfPublish::Text::StandardFontsType::kTimesRoman, normal Times New Roman font> is used.
    
    \sa 
    <link OdPdfPublish::Text::FontStyle, Text::FontStyle enumeration>
    <link OdPdfPublish::Text::StandardFontsType, StandardFontsType enumeration>
  */
  void setFont(const OdString& fontName, Text::FontStyle fontStyle = Text::kRegular);
  
  /** \details
    Sets a font size for the text field.
    
    \param size [in] A new font size value of the text field.
  */
  void setFontSize(OdUInt16 size);
  
  /** \details
    Sets a foreground color for the text field.
    
    \param color [in] A new color value.
  */
  void setTextColor(ODCOLORREF color);
  
  /** \details
    Sets tooltip text for the text field.
    Tooltip text is the text that appears when a user hovers the mouse pointer over the text field.
    
    \param tooltip [in] A new value of the tooltip text.
  */
  void setTooltip(const OdString& tooltip);
  
  /** \details
    Sets a new value of the visibility flag for the text field.
    The visibility flag determines whether the text field is visible in the document (if true) or is hidden (if false).
    
    \param state [in] A new flag value.
  */
  void setVisibility(bool state);
  
  /** \details
    Sets a new value of the flag that determines whether the text field should be printed.
    If the text field should be printed, the flag value is equal to true, otherwise it is equal to false.
    
    \param state [in] A new flag value.
  */
  void setPrintability(bool state);
  
  /** \details
    Sets a new value of the flag that determines whether the text field is locked.
    If the flag value is equal to true, the text field is locked and becomes disabled, otherwise it is enabled and unlocked.
    
    \param state [in] A new flag value.
  */
  void setLock(bool state);
  
  /** \details
    Sets a new value of the flag that determines whether the text field has a border.
    If the flag value is equal to true, the text field has a border, otherwise it does not.
    
    \param state [in] A new flag value.
  */
  void setBorder(bool state);
  
  /** \details
    Sets a text field border color.
    
    \param color [in] A new color value.
  */
  void setBorderColor(ODCOLORREF color);
  
  /** \details
    Sets a text field border thickness.
    
    \param thickness [in] A new thickness value.
    
    \sa 
    <link OdPdfPublish::Border::Thickness, Border::Thickness enumeration>.
  */
  void setBorderThickness(Border::Thickness thickness);
  
  /** \details
    Sets a text field border style.
    
    \param style [in] A new border style.
    
    \sa
    <link OdPdfPublish::Border::Style, Border::Style enumeration>.
  */
  void setBorderStyle(Border::Style style);
  
  /** \details
    Sets a text field fill color.
    
    \param color [in] A new color value.
  */
  void setFillColor(ODCOLORREF color);
  
  /** \details
    Sets a text field default value.
    
    \param value [in] A new default value.
  */  
  void setDefaultValue(const OdString& value);
  
  /** \details
    Sets a text field justification value.
    
    \param justification [in] A new text justification value.
    
    \sa
    <link OdPdfPublish::Text::Justification, Text::Justification enumeration>.
  */
  void setTextJustification(Text::Justification justification);
  
  /** \details
    Sets a text field multiline flag value.
    This flag determines whether the text field content can be divided into several lines.
    If the flag is equal to true, the text field can contain several lines, otherwise text field content is in a single line.
    
    \param state [in] A new multiline flag value.
  */
  void setMultiline(bool state);
  
  /** \details
    Sets a text field scrolling flag value.
    If the flag is equal to true, the text field has a scroll control that can be used to scroll multiline text.
    Otherwise the text field does not contain a scroll control.
    
    \param state [in] A new scrolling flag value.
  */
  void setScrolling(bool state);
  
  /** \details
    Sets a text field read-only flag value.
    The read-only flag determines whether text field content can be edited (if its value is true) or not (if its value is false).
    
    \param state [in] A new read-only flag value.
  */
  void setReadOnly(bool state);
  
  /** \details
    Sets a text field rotation value.
    
    \param rotation [in] A new rotation value.
    
    \sa
    <link OdPdfPublish::Text::Rotation, Text::Rotation enumeration>.
  */
  void setTextRotation(Text::Rotation rotation);

  /** \details
    Returns the current name of the text field.
    The method fills a passed string object with the text field name and returns it to a calling subroutine.
    
    \param name [out] A placeholder for the text field name.
  */
  void getName(OdString& name) const;

  /** \details
    Returns the current font type name used for displaying the text field caption.
    The method fills a passed string object with the text field font name and returns it to a calling subroutine.
    
    \param storageType  [out] A placeholder for the storage type value.
    \param fontType     [out] A placeholder for the font type that should be used for displaying the text field caption.
    \param fontName     [out] A placeholder for the font name that should be used for displaying the text field caption.
    \param fontStyle    [out] A placeholder for the font style that should be used for displaying the text field caption.
    
    \sa
    <link OdPdfPublish::Text::StorageType, Text::StorageType enumeration>
    <link OdPdfPublish::Text::StandardFontsType, Text::StandardFontsType enumeration>
    <link OdPdfPublish::Text::FontStyle, Text::FontStyle enumeration>
  */  
  void getFont(Text::StorageType& storageType, Text::StandardFontsType& fontType, OdString& fontName, Text::FontStyle& fontStyle) const;
  
  /** \details
    Returns the current font size used for displaying the text field caption.
    The method fills a passed integer value with the text field font size and returns it to a calling subroutine.
    
    \param size [out] A placeholder for the font size that should be used for the text field caption.
  */
  void getFontSize(OdUInt16& size) const;
  
  /** \details
    Returns the current text color used for displaying the text field caption.
    The method fills a passed ODCOLORREF value with the text field caption color and returns it to a calling subroutine.
    
    \param color [out] A placeholder for the text color that should be used for the text field caption.
  */
  void getTextColor(ODCOLORREF& color) const;
  
/** \details
    Returns the current tooltip text for the text field.
    Tooltip text is the text that appears when a user hovers the mouse pointer over the text field.
    
    The method fills a passed string object with the text field tooltip text and returns it to a calling subroutine.
    
    \param tooltip [out] A placeholder for the tooltip text.
  */
  void getTooltip(OdString& tooltip) const;
  
  /** \details
    Returns the current value of the visibility flag for the text field.
    The visibility flag determines whether the text field is visible in the document (if true) or is hidden (if false).
    The method fills a passed boolean value with the text field visibility flag value and returns it to a calling subroutine.
    
    \param state [out] A placeholder for the flag value.
  */
  void getVisibility(bool& state) const;
  
  /** \details
    Returns the current value of the flag that determines whether the text field should be printed.
    If the text field should be printed, the flag value is equal to true, otherwise it is equal to false.
    The method fills a passed boolean value with the text field printability flag value and returns it to a calling subroutine.
    
    \param state [out] A placeholder for the flag value.
  */
  void getPrintability(bool& state) const;
  
  /** \details
    Returns the current value of the flag that determines whether the text field is locked.
    If the flag value is equal to true, the text field is locked and becomes disabled, otherwise it is enabled and unlocked.
    The method fills a passed boolean value with the text field lock flag value and returns it to a calling subroutine.
    
    \param state [out] A placeholder for the flag value.
  */
  void getLock(bool& state) const;
  
  /** \details
    Returns the current value of the flag that determines whether the text field has a border.
    If the flag value is equal to true, the text field has a border, otherwise it does not.
    The method fills a passed boolean value with the text field border flag value and returns it to a calling subroutine.
    
    \param state [out] A placeholder for the flag value.
  */
  void getBorder(bool& state) const;
  
  /** \details
    Returns the current text field border color.
    The method fills a passed ODCOLORREF value with the text field border color value and returns it to a calling subroutine.
    
    \param color [out] A placeholder for the color value.
  */
  void getBorderColor(ODCOLORREF& color) const;
  
  /** \details
    Returns the current thickness value of the text field border.
    This method fills a passed value with the current thickness value and returns it to a calling subroutine.
    
    \param thickness [out] A placeholder for the thickness value.
    
    \sa
    <link OdPdfPublish::Border::Thickness, Border::Thickness enumeration>.
  */
  void getBorderThickness(Border::Thickness& thickness) const;
  
  /** \details
    Returns the current text field border style.
    
    \param style [out] A placeholder for the border style of the text field.
    
    \sa
    <link OdPdfPublish::Border::Style, Border::Style enumeration>.
  */
  void getBorderStyle(Border::Style& style) const;
  
  /** \details
    Returns the text field fill color.
    The method fills a passed ODCOLORREF value and returns it to a calling subroutine.
    
    \param color [out] A placeholder for the fill color value.
  */
  void getFillColor(ODCOLORREF& color) const;
  
  /** \details
    Returns the current text field default value.
    The method fills a passed string object with the current text field default value and returns it to a calling subroutine.
    
    \param value [out] A placeholder for the text field default value.
  */
  void getDefaultValue(OdString& value) const;
  
  /** \details
    Returns the current text field justification.
    The method fills a passed justification value and returns it to a calling subroutine.
    
    \param justification [out] A placeholder for the justification value.
    
    \sa
    <link OdPdfPublish::Text::Justification, Text::Justification enumeration>.
  */
  void getTextJustification(Text::Justification& justification) const;
  
  /** \details
    Returns the current multiline flag value of the text.
    This flag determines whether the text field content can be divided into several lines.
    If the flag is equal to true, the text field can contain several lines, otherwise text field content is in a single line.
    The method fills a passed boolean value with the current flag value and returns it to a calling subroutine.
    
    \param state [out] A placeholder for the multiline flag value.
  */
  void getMultiline(bool& state) const;
  
  /** \details
    Returns the current text field scrolling flag value.
    If the flag is equal to true, the text field has a scroll control that can be used to scroll multiline text.
    Otherwise the text field does not contain a scroll control.
    The method fills a passed boolean value with the current flag value and returns it to a calling subroutine.
    
    \param state [out] A placeholder for the scrolling flag value.
  */
  void getScrolling(bool& state) const;
  
  /** \details
    Returns the current read-only flag value of the text field.
    The read-only flag determines whether text field content can be edited (if its value is true) or not (if its value is false).
    The method fills a passed boolean value with the current flag value and returns it to a calling subroutine.
    
    \param state [out] A placeholder for the read-only flag value.
  */
  void getReadOnly(bool& state) const;
  
  /** \details
    Returns the current text field rotation value.
    The method fills a passed value with the current rotation value and returns it to a calling subroutine.
    
    \param rotation [out] A placeholder for the rotation value of the text field.
    
    \sa
    <link OdPdfPublish::Text::Rotation, Text::Rotation enumeration>.
  */
  void getTextRotation(Text::Rotation& rotation) const;

};

/** \details
  A data type that represents a smart pointer to an <link OdPdfPublish::OdTextField, OdTextField> object.
*/
SMARTPTR(OdTextField);

}
#endif // _PDF_PUBLISH_TEXTFIELD_INCLUDED_

