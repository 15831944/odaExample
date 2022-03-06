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

#ifndef _ODTV_TEXTSTYLE_H_INCLUDED_
#define _ODTV_TEXTSTYLE_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvUserData.h"

/** \details
  The abstract interface class that implements functionality for working with Visualize SDK text style objects.
  \sa
  <link tv_working_with_attributes_text_style, Work with Text Styles>
*/  
class ODTV_EXPORT OdTvTextStyle : public OdTvHandledIObject
{
public:

  /** \details
    Types of text alignment.
  */
  enum AlignmentType
  {
    kLeft = 0,            // Left text alignment.
    kCenter = 1,          // Center text alignment.
    kRight = 2,           // Right text alignment.
    kAligned = 3,         // Text is aligned to horizontally fill the space of the text object.
    kMiddle = 4,          // Middle text alignment.
    kFit = 5,             // Fit text alignment.
    kTopLeft = 6,         // Top and left text alignment.
    kTopCenter = 7,       // Top and center text alignment.
    kTopRight = 8,        // Top and right text alignment.
    kMiddleLeft = 9,      // Middle and left text alignment.
    kMiddleCenter = 10,   // Middle and center text alignment.
    kMiddleRight = 11,    // Middle and right text alignment.
    kBottomLeft = 12,     // Bottom and left text alignment.
    kBottomCenter = 13,   // Bottom and center text alignment.
    kBottomRight = 14     // Bottom and right text alignment.
  };

  /** \details
    Types of mirror.
  */
  enum MirrorType
  {
    kNone = 0,            // No mirror.
    kMirroredInX = 1,     // Mirrored around the X-axis.
    kMirroredInY = 2,     // Mirrored around the Y-axis.
    kMirroredInXAndY = 3  // Mirrored around both the X-axis and Y-axis.
  };

  /** \details
    Retrieves the parameters of the current TrueType font associated with the text style object.
    
    \param typeface       [out] A placeholder for the typeface name.
    \param bold           [out] A placeholder for the bold flag value. The bold flag value is equal to true if the font should be displayed as bold; otherwise it is equal to false.
    \param italic         [out] A placeholder for the italic flag value. The italic flag value is equal to true if the font should be displayed as italic; otherwise it is equal to false.
    \param charset        [out] A placeholder for the character set identifier.
    \param pitchAndFamily [out] A placeholder for the pitch and character family identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the font parameters were successfully returned, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult getFont( OdString& typeface, bool& bold, bool& italic, int& charset, int& pitchAndFamily) const = 0;

  /** \details
    Associates a new TrueType font with the text style and sets font parameters.
    
    \param typeface       [in] A new typeface name.
    \param bold           [in] A value of the bold flag. The bold flag value is equal to true if the font should be displayed as bold; otherwise it is equal to false.
    \param italic         [in] A value of the italic flag. The italic flag value is equal to true if the font should be displayed as italic; otherwise it is equal to false.
    \param charset        [in] An identifier of the character set.
    \param pitchAndFamily [in] An identifier of the pitch and character family.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the font parameters were successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    If the typeface name is an empty string, the method disassociates the TrueType font from the text style and removes information about it.
  */
  virtual OdTvResult setFont( const OdString& typeface, bool bold, bool italic, int charset, int pitchAndFamily) = 0;

  /** \details
    Retrieves the current name of the uni-font file (*.shx) associated with the text style object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string object that contains the current uni-font file name.
    \remarks 
    A uni-font file (*.shx) contains definitions of the typical letter shapes for the text.
    If the rc parameter is not null and the uni-font file name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getFileName(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new name of the uni-font file (*.shx) and associates the uni-font with the text style object. 
    
    \param sUniFont [in]  A string that contains the new uni-font filename without its path to be associated with the text style object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    A uni-font file (*.shx) contains definitions of the typical letter shapes for the text.
    If the new name of the uni-font file was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setFileName( const OdString& sUniFont ) = 0;

  /** \details
    Retrieves the current name of the big-font file (*.shx) associated with the text style object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string object that contains the current big-font file name.
    \remarks 
    A big-font file (*.shx) contains definitions of the Asian-language letter shapes and special characters for the text.
    If the rc parameter is not null and the big-font file name was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdString getBigFontFileName(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new name of the big-font file (*.shx) and associates the big-font with the text style object. 
    
    \param sBigFont [in]  A string that contains the new big-font filename without its path to be associated with the text style object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    A big-font file (*.shx) contains definitions of the Asian-language letter shapes and special characters for the text.
    If the new name of the big-font file was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setBigFontFileName( const OdString& sBigFont ) = 0;

  /** \details
    Retrieves the current value of the shape flag. 
    The shape flag determines whether the font file associated with the text style object should be interpreted as a set of letter shapes (if equal to true). 
    Otherwise (if the font file contains a set of letters) the flag value is equal to true.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the font file should be interpreted as a set of letter shapes; otherwise the method returns false.
    \remarks 
    If the rc parameter is not null and the current shape flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getShapeStatus(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new value of the shape flag. 
    The shape flag determines whether the font file associated with the text style object should be interpreted as a set of letter shapes (if equal to true). 
    Otherwise (if the font file contains a set of letters) the flag value is equal to true.
    
    \param bShapeFile [in] A new shape flag value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new shape flag value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setShapeStatus( bool bShapeFile ) = 0;

  /** \details
    Retrieves the current value of the backwards flag.
    The backwards flag determines whether the text is drawn backward (if equal to true) or forward (if equal to false) from the start position.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the text is drawn backward; the method returns false if the text is drawn forward. 
    \remarks 
    If the rc parameter is not null and the current backwards flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getBackwards(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new value of the backwards flag. 
    The backwards flag determines whether the text is drawn backward (if equal to true) or forward (if equal to false) from the start position.
    
    \param bBackwards [in] A new backwards flag value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new backwards flag value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setBackwards( bool bBackwards ) = 0;

  /** \details
    Retrieves the current value of the upside-down flag.
    The upside-down flag determines whether the letters are drawn upside-down (if equal to true) or downside-up (if equal to false) from the text baseline.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the text is drawn upside-down; otherwise the method returns false. 
    \remarks 
    If the rc parameter is not null and the current upside-down flag value was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual bool getUpsideDown(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new value of the upside-down flag. 
    The upside-down flag determines whether the letters are drawn upside-down (if equal to true) or downside-up (if equal to false) from the text baseline.
    
    \param bUpsideDown [in] A new upside-down flag value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new upside-down flag value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setUpsideDown( bool bUpsideDown ) = 0;

  /** \details
    Retrieves the current value of the vertical direction flag.
    The vertical direction flag determines whether the text is drawn vertically (if equal to true) or horizontally (if equal to false) from the start position.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the text is drawn vertically; otherwise the text is drawn horizontally and the method returns false. 
    \remarks 
    If the rc parameter is not null and the current vertical direction flag value was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
  */
  virtual bool getVertical(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new value of the vertical direction flag. 
    The vertical direction flag determines whether the text is drawn vertically (if equal to true) or horizontally (if equal to false) from the start position.
    
    \param bVertical [in] A new vertical direction flag value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new vertical direction flag value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setVertical( bool bVertical ) = 0;

  /** \details
    Retrieves the current obliquing angle value of the text style object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns current obliquing angle value. 
    \remarks 
    If the rc parameter is not null and current obliquing angle value was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    The obliquing angle value should be in the range ±1.48335 radians (±85°) and influences the slant of text letters. 
    If the obliquing angle value is negative, the method adds 2PI to it. 
  */
  virtual double getObliquingAngle(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new obliquing angle value for the text style object.
    
    \param dAngle [in] A new obliquing angle value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new obliquing angle value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    The obliquing angle value should be in the range ±1.48335 radians (±85°) and influences the slant of text letters. 
    If the obliquing angle value is negative, the method adds 2PI to it. 
  */
  virtual OdTvResult setObliquingAngle( double dAngle ) = 0;

  /** \details
    Retrieves the current width factor value of the text style object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the current width factor value. 
    \remarks 
    If the rc parameter is not null and the current width factor value was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    The width factor value is used for scaling text letters and spaces. The height remains constant. 
    The width factor should have a positive double value.
    A width factor value that is less than 1.0 leads to condensed text; a value greater than 1.0 leads to expanded text. 
    The default width factor value is equal to 1.0.
  */
  virtual double widthFactor(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new width factor value for the text style object.
    
    \param widthFactor [in] A new width factor value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new width factor value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    The width factor value is used for scaling text letters and spaces. The height remains constant. 
    The width factor should have a positive double value.
    A width factor value that is less than 1.0 leads to condensed text; the value greater than 1.0 leads to expanded text. 
    The default width factor value is equal to 1.0.
  */
  virtual OdTvResult setWidthFactor( double widthFactor ) = 0;

  /** \details
    Retrieves the current text size of the text style object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the text size. 
    \remarks 
    If the rc parameter is not null and the current text size was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    The text size value defines both the width and height of the text and is used for proportional scaling of the text letters, spaces and boundaries. 
    A text size value less than 1.0 decreases the text size. A text size value greater than 1.0 increases the text size.
    The default value is equal to 0.2.
  */
  virtual double textSize(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new text size value for the text style object.
    
    \param dSize [in] A new text size value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new text size value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
    The text size value defines both the width and height of the text and is used for proportional scaling of the text letters, spaces and boundaries. 
    A text size value less than 1.0 decreases the text size. A text size value greater than 1.0 increases the text size.
    The default value is equal to 0.2.
  */
  virtual OdTvResult setTextSize( double dSize ) = 0;

  /** \details
    Retrieves the current alignment mode of the text style object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a value of the <link OdTvTextStyle::AlignmentType, AlignmentType> enumeration that represents the current text alignment. 
    \remarks 
    If the rc parameter is not null and the current text alignment was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
  */
  virtual OdTvTextStyle::AlignmentType getAlignmentMode(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new text alignment mode for text style object.
    
    \param alignMode [in] A new text <link OdTvTextStyle::AlignmentType, alignment> value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new text alignment value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setAlignmentMode(OdTvTextStyle::AlignmentType alignMode) = 0;

  /** \details
    Sets a new value of the underlined flag for the text style object.
    The underlined flag determines whether the text is drawn underlined (if equal to true) or not (if equal to false).
    
    \param bUnderlined [in] A new flag value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new underlined flag value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setUnderlined(bool bUnderlined) = 0;

  /** \details
    Retrieves the current value of the underlined flag of the text style object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the text is drawn underlined; otherwise the method returns false. 
    \remarks 
    If the rc parameter is not null and the current underlined flag value was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
  */
  virtual bool getUnderlined(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new value of the overlined flag for the text style object.
    The overlined flag determines whether the text is drawn overlined (if equal to true) or not (if equal to false).
    
    \param bOverlined [in] A new flag value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new overlined flag value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setOverlined(bool bOverlined) = 0;

  /** \details
    Retrieves the current value of the overlined flag of the text style object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the text is drawn overlined; otherwise the method returns false. 
    \remarks 
    If the rc parameter is not null and the current overlined flag value was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
  */
  virtual bool getOverlined(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new value of the strike out flag for the text style object.
    The strike out flag determines whether the text is drawn struck out (if equal to true) or not (if equal to false).
    
    \param bStriked [in] A new flag value to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new strike out flag value was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setStriked(bool bStriked) = 0;

  /** \details
    Retrieves the current value of the strike out flag of the text style object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns true if the text is drawn struck out; otherwise the method returns false. 
    \remarks 
    If the rc parameter is not null and the current strike out flag value was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
  */
  virtual bool getStriked(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new name for the text style object.
    
    \param sName [in] A string that contains the new text style name to be set.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    The text style name should have a length from 0 to 255 characters.
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
    If the new text style object name was successfully set, the method returns tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setName(const OdString& sName) = 0;
  
  /** \details
    Retrieves the current name of the text style object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string that contains the current text style object's name. 
    \remarks 
    If the rc parameter is not null and the current text style object name was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    The text style name should have a length from 0 to 255 characters.
    The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
    underscores, and some special characters, but cannot contain inadmissible letters
    ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
  */
  virtual OdString getName(OdTvResult* rc = NULL) const = 0;

  /** \details
    Sets a new path to a custom folder that contains font files used by the text style object.
    
    \param strFolderPath [in] A string that contains the new folder path.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the new path to the custom font folder was successfully set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult setCustomFontFolder(const OdString& strFolderPath) = 0;

  /** \details
    Retrieves the current path to the custom folder that contains font files used by the text style object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a string that contains the path to the current custom font folder. 
    \remarks 
    If the rc parameter is not null and the current path to the custom font folder was successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
  */
  virtual OdString getCustomFontFolder(OdTvResult* rc = NULL) const = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvTextStyle, OdTvTextStyle> object.
*/
typedef OdTvSmartPtr<OdTvTextStyle> OdTvTextStylePtr;


/** \details
  The interface class for a text style object identifier that allows access to the <link OdTvTextStyleId, OdTvTextStyleId> object.
*/
class ODTV_EXPORT OdTvTextStyleId : public OdTvId
{
public:
  
  /** \details
    Opens the text style determined by its identifier for a read or write operation. 
    
    \param mode [in]  An open mode value.
    \param rc   [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the open operation.
    \returns Returns a smart pointer to the text style object.
    \remarks
    If the rc parameter is not null and the text style object was successfully opened, the rc parameter accepts the tvOk value;
    otherwise it contains an appropriate error code.
  */
  OdTvTextStylePtr openObject(OdTv::OpenMode mode = OdTv::kForRead, OdTvResult* rc = NULL) const;
};

/** \details
  The base interface class for the iterator of Visualize SDK text style objects.
  An iterator object provides sequential access to a collection of text styles.
*/
class ODTV_EXPORT OdTvTextStylesIterator : public OdTvIterator, public OdTvIObject
{
public:

  /** \details
    Retrieves the text style that is currently referenced by the iterator object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \returns Returns the text style identifier if the iterator refers to a text style; otherwise it returns an identifier with a null value.
    \remarks 
    If the rc parameter is not null and the text style identifier is successfully returned, the rc parameter accepts the tvOk value; 
    otherwise it contains an appropriate error code.
    If the iterator refers to a text style, the identifier that the method returns is not null (i.e., the result of the isNull() method of the identifier is equal to false).
  */
  virtual OdTvTextStyleId getTextStyle(OdTvResult* rc = NULL) const = 0;
  
  /** \details
    Searches for the text style defined by its identifier and moves the iterator to this text style if found.
    
    \param textStyleId [in] A text style identifier.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks 
    If the text style specified by its identifier is found, the method returns tvOk; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult seek(const OdTvTextStyleId& textStyleId) = 0;
};

/** \details
  A data type that represents a smart pointer to an <link OdTvTextStylesIterator, text style iterator> object.
*/
typedef OdTvSmartPtr<OdTvTextStylesIterator> OdTvTextStylesIteratorPtr;

#endif //_ODTV_TEXTSTYLE_H_INCLUDED_
