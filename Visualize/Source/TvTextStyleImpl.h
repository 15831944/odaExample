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


#ifndef _ODTV_TEXTSTYLEIMPL_H_INCLUDED_
#define _ODTV_TEXTSTYLEIMPL_H_INCLUDED_

#include "TD_PackPush.h"

#include "TvTextStyle.h"
#include "TvInterfaceWrappers.h"
#include "TvUserDataImpl.h"

#include "DbTextStyleTableRecord.h"
#include "DbSymbolTable.h"

/** \details
This class is the internal implementation of the text style. Such implementation is need
because of storing the alignment and cach info about changes
*/
class OdTvTextStyleImpl : public OdTvDbTextStyleTableRecord, public OdTvXDataStorage
{
  OdTvTextStyleImpl();

  virtual ~OdTvTextStyleImpl();

public:
  ODRX_DECLARE_MEMBERS(OdTvTextStyleImpl);

  /** \details
  Reads the .dwg file data of this object.

  \param pFiler [in]  Filer object from which data are read.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
  Writes the .dwg file data of this object.

  \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
  Close the text style
  */
  virtual void subClose();

  /** \details
  Returns the alignment mode
  */
  OdTvTextStyle::AlignmentType getAlignmentMode() const;

  /** \details
  Set the alignment mode
  */
  void setAlignmentMode(OdTvTextStyle::AlignmentType alignMode);

  /** \details
  Controls the underlined drawing of text with this TextStyle.

  \param underlined [in]  Controls underlined drawing.
  */
  void setUnderlined(bool bUnderlined);

  /** \details
  Returns true if and only if text is drawn underlined with this TextStyle.
  */
  bool getUnderlined() const;

  /** \details
  Controls the overlined drawing of text with this TextStyle.

  \param overlined [in]  Controls overlined drawing.
  */
  void setOverlined(bool bOverlined);

  /** \details
  Returns true if and only if text is drawn overlined with this TextStyle.
  */
  bool getOverlined() const;

  /** \details
  Controls the striked drawing of text with this TextStyle.

  \param overlined [in]  Controls overlined drawing.
  */
  void setStriked(bool bStriked);

  /** \details
  Returns true if and only if text is drawn striked with this TextStyle.
  */
  bool getStriked() const;

  /** \details
  Setup the custom folder with fonts for this TextStyle.

  \param strFolderPath [in]  Folder path.
  */
  void setCustomFontFolder(const OdString& strFolderPath);

  /** \details
  Returns the custom folde path for this  TextStyle.
  */
  const OdString& getCustomFontFolder() const;

  /** \details
  Returns the value of m_cntChanges
  */
  OdUInt32 getCacheChanges() const;

  /** \details
  Return the value of memory, which this object takes up.
  */
  OdUInt64 getObjectSize(OdTvResult* rc = NULL) const;

  /** \details
  Internal (not API) method which marks the text style as not preloaded. NEED for CLOUD
  */
  void setPreloaded(bool value);

private:

  // alignment mode
  OdTvTextStyle::AlignmentType  m_alignmentMode; 
  // underlined
  bool m_underlined;
  // overlined
  bool m_overlined;
  //striked
  bool m_striked;
  //custom font foldetr
  OdString m_strCustomFontFolder;

  // cache update
  OdUInt32      m_cntChanges;
};

typedef OdSmartPtr<OdTvTextStyleImpl> OdTvTextStyleImplPtr;

/** \details
  This is an wrapper of the interface class OdTvTextStyle.
  
  \remarks
  The purpose of this class is to connect the internal object(OdTvDbTextStyleTableRecord) with an interface object(OdTvTextStyle)
*/
class OdTvTextStyleWrapper : public OdTvTextStyle
{
 ODTV_DEFINE_WRAPPERS_DB_MEMBERS_DECL(OdTvTextStyle, OdTvTextStyleImpl)

 friend class OdTvLinetypeWrapper;
 friend class OdTvTextStylesIteratorImpl;
 friend class OdTvDatabaseImpl;

protected:
 ODRX_HEAP_OPERATORS();

public:

 /** \details
  Gets the characteristics of the true type font associated with the text style.

  \param typeface [out]  Typeface name of the font.
  \param bold [out]  True if and only if Bold font.
  \param italic [out]  True if and only if Italic font.
  \param charset [out]  Character set identitier.
  \param pitchAndFamily [out]  Pitch and character family identifier.
 */
 virtual OdTvResult getFont(OdString& typeface, bool& bold, bool& italic, int& charset, int& pitchAndFamily) const;

 /** \details
  Associates the true type font with the text style and sets its characteristics.

  \param typeface [in]  Typeface name of the font.
  \param bold [in]  True - to set the Bold font.
  \param italic [in]  True - to set the Italic font.
  \param charset [in]  Windows character set identitier.
  \param pitchAndFamily [in]  Windows pitch and character family identifier.

  \remarks
  If typeface is an empty string, this method disassociates the true type font with this text style
  and removes information about it.
 */
  virtual OdTvResult setFont(const OdString& typeface, bool bold, bool italic, int charset, int pitchAndFamily);

 /** \details
  Returns the name of the /uni-font/ (*.shx) file associated with this text style.
 */
  virtual OdString getFileName(OdTvResult* rc = NULL) const;

 /** \details
  Sets the name of the /uni-font/ (*.shx) file and associates this uni-font with the text style.
  This /uni-font/ (*.shx) defines the shape of typical letters for text.

  \param sUniFont [in]  Uni-font filename without path to be associated with the text style as a String value.
 */
  virtual OdTvResult setFileName(const OdString& sUniFont);

 /** \details
  Returns the name of the /big-font/ (*.shx) file associated with this text style.
 */
  virtual OdString getBigFontFileName(OdTvResult* rc = NULL) const;

 /** \details
  Sets the name of the /big-font/ (*.shx) file and associates this big-font with the text style.
  This /big-font/ (*.shx) defines the shape of Asian-language letters and special characters for text.

  \param sBigFont [in]  Big-font filename without path to be associated with the text style as a String value.
 */
  virtual OdTvResult setBigFontFileName(const OdString& sBigFont);

 /** \details
  Determines whether the font file associated with this text style should be interpreted as
  a set of shapes or letters and returns True if the font file is a set
  of shapes or False if the font file is a set of letters.
 */
  virtual bool getShapeStatus(OdTvResult* rc = NULL) const;

 /** \details
  Sets the interpretation of the associated font file as a Boolean value.
  The initial value is False (Letters) by default.

  \param bShapeFile [in]  True - to determine the font file as a set of shapes, or
          False - to determine the font file as a set of letters.
 */
  virtual OdTvResult setShapeStatus(bool bShapeFile);

 /** \details
  Determines whether text is drawn backward or forward from the start position
  and returns True if text is backward or False if text is forward.
 */
  virtual bool getBackwards(OdTvResult* rc = NULL) const;

 /** \details
  Sets the direction typeface as a Boolean value. The initial value is False
  (Forward) by default.

  \param bBackwards [in]  True - to draw the text backward, or False - to draw the text forward.
 */
  virtual OdTvResult setBackwards(bool bBackwards);

 /** \details
  Determines whether letters are placed up or down relative to the baseline when text is drawn
  and returns True if letters are placed up or False if letters are placed
  upside down.
 */
  virtual bool getUpsideDown(OdTvResult* rc = NULL) const;

 /** \details
  Sets the letter side typeface as a Boolean value. The initial value is False (Upside) by default.

  \param bUpsideDown [in]  True - to draw the text downside, or False - to draw the text upside.
 */
  virtual OdTvResult setUpsideDown(bool bUpsideDown);

 /** \details
  Determines whether text is drawn vertically or horizontally from the start position
  and returns True if text is vertical or False if text is horizontal.
 */
  virtual bool getVertical(OdTvResult* rc = NULL) const;

 /** \details
  Sets the orientation typeface as a Boolean value. The initial value is False
  (Horizontal) by default.

  \param bVertical [in]  True - to make the vertical text, or False - to make the horizontal text.
 */
  virtual OdTvResult setVertical(bool bVertical);

 /** \details
  Returns the obliquing angle in range ±1.48335 radians (±85°). This angle influences on
  the lean of letters. Negative angles will have 2PI added to them.
 */
  virtual double getObliquingAngle(OdTvResult* rc = NULL) const;

 /** \details
  Sets the obliquing angle of letters in range ±1.48335 radians (±85°). A positive angle
  leans the letters clockwise (to the right). A negative value leans the letters counterclockwise
  (to the left). A negative value is converted to its positive equivalent by adding the value 2*PI.
  The initial value is 0.0 by default.

  \param vAngle [in]  Obliquing angle in radians as a Double value in range ±1.48335.
 */
  virtual OdTvResult setObliquingAngle(double dAngle);

  /** \details
  Returns the width scale factor of the text boundary. This factor influences only on the
  width and is used for scaling of letters and spaces when the height is constant.
  */
  virtual double widthFactor(OdTvResult* rc = NULL) const;

  /** \details
  Sets the width scale factor of the text boundary. This factor influences only on the
  text width and is used for scaling of letters and spaces when the height is constant. A value
  less than 1.0 condenses the text. A value greater than 1.0 expands the text. The initial value
  is 1.0 by default.

  \param widthFactor [in]  width factor as a positive non-zero Double value.
  */
  virtual OdTvResult setWidthFactor(double widthFactor);

  /** \details
  Returns the height scale factor of the text boundary. This factor influences on the width
  and height together and is used for proportional scaling of letters, spaces, and the text boundary.
  */
  virtual double textSize(OdTvResult* rc = NULL) const;

  /** \details
  Sets the text size which is the height scale factor of the text boundary. This factor
  influences on the text width and text height together and is used for proportional scaling of
  letters, spaces, and the text boundary. A value less than 1.0 decreases the text. A value
  greater than 1.0 increases the text. The initial value is 0.2 by default.

  \param vSize [in]  Text size as a positive non-zero Double value.
  */
  virtual OdTvResult setTextSize(double dSize);

  /** \details
  Returns the alignment mode
  */
  virtual OdTvTextStyle::AlignmentType getAlignmentMode(OdTvResult* rc = NULL) const;

  /** \details
  Set the alignment mode
  */
  virtual OdTvResult setAlignmentMode(OdTvTextStyle::AlignmentType alignMode);

  /** \details
  Controls the underlined drawing of text with this TextStyle.

  \param underlined [in]  Controls underlined drawing.
  */
  virtual OdTvResult setUnderlined(bool bUnderlined);

  /** \details
  Returns true if and only if text is drawn underlined with this TextStyle.
  */
  virtual bool getUnderlined(OdTvResult* rc = NULL) const;

  /** \details
  Controls the overlined drawing of text with this TextStyle.

  \param overlined [in]  Controls overlined drawing.
  */
  virtual OdTvResult setOverlined(bool bOverlined);

  /** \details
  Returns true if and only if text is drawn overlined with this TextStyle.
  */
  virtual bool getOverlined(OdTvResult* rc = NULL) const;

  /** \details
  Controls the striked drawing of text with this TextStyle.

  \param overlined [in]  Controls overlined drawing.
  */
  virtual OdTvResult setStriked(bool bStriked);

  /** \details
  Returns true if and only if text is drawn striked with this TextStyle.
  */
  virtual bool getStriked(OdTvResult* rc = NULL) const;

 /** \details
 Sets the name for the text style object.

 \param sName [in]  Text style name as a String value up to 255 characters long.

 \remarks
 The name is an arbitrary non-empty string that can contain letters, digits, blank spaces,
 underscores, and some special characters, but cannot contain inadmissible letters
 ("<", ">", "\", "/", ":", ";", "?", ",", "*", "|", "=", "'", quotation marks and some special characters created with Unicode fonts).
 */
  virtual OdTvResult setName(const OdString& sName);

 /** \details
 Returns the name of the text style object.
 */
  virtual OdString getName(OdTvResult* rc = NULL) const;

  /** \details
  Setup the custom folder with fonts for this TextStyle.

  \param strFolderPath [in]  Folder path.
  */
  virtual OdTvResult setCustomFontFolder(const OdString& strFolderPath);

  /** \details
  Returns the custom folder path for this TextStyle.
  */
  virtual OdString getCustomFontFolder(OdTvResult* rc = NULL) const;

  ODTV_DEFINE_XDATA_DECL(virtual);
  ODTV_DEFINE_HANDLED_OBJECT_DECL(virtual);
  ODTV_DEFINE_SERIALIZABLE_OBJECT_DECL(virtual);

  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // Internal methods
  //////////////////////////////////////////////////////////////////////////////////////////////////////

  OdTvDbObjectId getWrappedDbObjectId();
};

/** \details
This is an implementation of the iterator class for the textstyles
*/
class ODTV_EXPORT OdTvTextStylesIteratorImpl : public OdTvTextStylesIterator
{

  friend class OdTvDatabaseImpl;
public:
  /** \details
  Returns true if and only if the traversal by this Iterator object is complete.
  */
  virtual bool done(OdTvResult* rc = NULL) const;

  /** \details
  Steps this Iterator object.
  */
  virtual OdTvResult step();

  /** \details
  Returns the textstyle currently referenced by this Iterator object.
  */
  virtual OdTvTextStyleId getTextStyle(OdTvResult* rc = NULL) const;

  /** \details
  Positions this Iterator object at the specified textstyle.
  \param objectId [in]  TextStyle ID.
  */
  virtual OdTvResult seek(const OdTvTextStyleId& TextStyleId);
  
  /** \details
  Methods for creating the object
  */
  static OdTvTextStylesIteratorPtr createObject(OdTvDbSymbolTableIterator* pDbIterator);
  
  ODTV_WRAPPERS_REFERENCE_MEMBERS()

private:
  OdTvTextStylesIteratorImpl();
  OdTvTextStylesIteratorImpl(OdTvDbSymbolTableIterator* pDbIterator);

  virtual ~OdTvTextStylesIteratorImpl();

  // Db iterator
  OdTvDbSymbolTableIteratorPtr m_pDbIterator;

  // reference counter
  unsigned int               m_nRefCounter;
};

#include "TD_PackPop.h"

#endif // _ODTV_TEXTSTYLEIMPL_H_INCLUDED_

