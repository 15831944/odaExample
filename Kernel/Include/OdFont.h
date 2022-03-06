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




// OdFont.h: interface for the OdFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ODFONT_H__0B76813A_DCFA_450E_8591_B6C6F1ED76EC__INCLUDED_)
#define AFX_ODFONT_H__0B76813A_DCFA_450E_8591_B6C6F1ED76EC__INCLUDED_

#include "RxObject.h"
#include "OdArray.h"
#include "OdCharMapper.h"

// For memset below
#include <memory.h>

class OdGiCommonDraw;
class OdGiConveyorGeometry;
class OdGePoint2d;
class OdGePoint3d;
class OdStreamBuf;

#include "TD_PackPush.h"

/** \details
  Defines font type options.
*/
typedef enum {
  /** Unknown */
  kFontTypeUnknown    = 0,
  /** SHX font. */
  kFontTypeShx        = 1,
  /** TrueType font. */
  kFontTypeTrueType   = 2,
  /** Shape file. */
  kFontTypeShape      = 3, 
  /** Big font file. */
  kFontTypeBig        = 4,
  /** MicroStation resource file. */
  kFontTypeRsc        = 5 
} OdFontType;

/** \details
    This structure implements character properties in an OdGi context. 
    Corresponding C++ library: TD_Root
    <group !!RECORDS_tkernel_apiref>
*/
struct FIRSTDLL_EXPORT OdCharacterProperties
{
  OdCharacterProperties()
  { ::memset(this, 0, sizeof(*this)); }
  /** Underlined character */
  bool  bUnderlined;
  /** Overlined character */
  bool  bOverlined;
  /** Striked character */
  bool  bStriked;
  /** Last character */
  bool  bLastChar;
  /** In big font character */
  bool  bInBigFont;
  /** Asian character */
  bool  bAsian;
  /** Valid character */
  bool  bValid;
  /** Unicode for char*/
  OdChar uCode;
};

/** \details
    This structure implements text properties in an OdGi context.
    Corresponding C++ library: TD_Root
    <group !!RECORDS_tkernel_apiref>
*/
struct FIRSTDLL_EXPORT OdTextProperties
{
  /** Tracking percent */
  double   m_trackingPercent;
  /** Text flags */
  OdUInt16 m_flags;
  /** Text quality in the range [0,100] */
  OdUInt16 m_textQuality;
  enum
  {
    /** Normal text */
    kNormalText   = 0x01,
    /** Vertical text */
    kVerticalText = 0x02,
    /** Underlined text */
    kUnderlined   = 0x04,
    /** Overlined text */
    kOverlined    = 0x08,
    /** Last character in text */
    kLastChar     = 0x10,
    /** Character in Big Font */
    kInBigFont    = 0x20,
    /** Include pen ups in extents for SHX font*/
    kInclPenups   = 0x40,
    /** Zero normals */
    kZeroNormals  = 0x80,
    /** Bezier curves for TrueType font*/
    kBezierCurves = 0x100,
    /** Striked text */
    kStriked      = 0x200,
    /** Last position only. For internal use only. */
    kLastPosOnly  = 0x400,    // 
    /** Use triangle cache for TrueType font. For internal use only. */
    kTriangleCache = 0x800,
    /** Symbol code is glyph. For internal use only. */
    kIsGlyph      = 0x1000
  };
  /** Previous character */
  OdChar  m_prevChar;
public:
  OdTextProperties() : m_flags(0), m_trackingPercent(0.0), m_textQuality(50), m_prevChar(0) {}

  /** \details
    Checks whether the normal text flag is set for this TextProperties object.

    \returns The true value if the normal text flag is set for this TextProperties object successfully, or false otherwise.
  */
  bool isNormalText() const { return GETBIT(m_flags, kNormalText); }

  /** \details
    Controls the normal text flag for this TextProperties object.

    \param value [in] Property value to control the flag.
  */
  void setNormalText(bool value) { SETBIT(m_flags, kNormalText, value); }

  /** \details
    Checks whether the vertical text flag is set for this TextProperties object.

    \returns The true value if the vertical text flag is set for this TextProperties object successfully, or false otherwise.
  */
  bool isVerticalText() const { return GETBIT(m_flags, kVerticalText); }

  /** \details
    Controls the vertical text flag for this TextProperties object.

    \param value [in] Property value to control the flag.
  */
  void setVerticalText(bool value) { SETBIT(m_flags, kVerticalText, value); }

  /** \details
    Checks whether the underlined flag is set for this TextProperties object.

    \returns The true value if the underlined flag is set for this TextProperties object successfully, or false otherwise.
  */
  bool isUnderlined() const { return GETBIT(m_flags, kUnderlined); }

  /** \details
    Controls the underlined flag for this TextProperties object.

    \param value [in] Property value to control the flag.
  */
  void setUnderlined(bool value) { SETBIT(m_flags, kUnderlined, value); }

  /** \details
    Checks whether the overlined flag is set for this TextProperties object.

    \returns The true value if the overlined flag is set for this TextProperties object successfully, or false otherwise.
  */
  bool isOverlined() const { return GETBIT(m_flags, kOverlined); }

  /** \details
    Controls the overlined flag for this TextProperties object.

    \param value [in] Property value to control the flag.
  */
  void setOverlined(bool value) { SETBIT(m_flags, kOverlined, value); }

  /** \details
    Checks whether the striked flag is set for this TextProperties object.

    \returns The true value if the striked flag is set for this TextProperties object successfully, or false otherwise.
  */
  bool isStriked() const { return GETBIT(m_flags, kStriked); }

  /** \details
    Controls the striked flag for this TextProperties object.

    \param value [in] Property value to control the flag.
  */
  void setStriked(bool value) { SETBIT(m_flags, kStriked, value); }

  /** \details
    Checks whether the lastChar flag is set for this TextProperties object.

    \returns The true value if the lastChar flag is set for this TextProperties object successfully, or false otherwise.
  */
  bool isLastChar() const { return GETBIT(m_flags, kLastChar); }

  /** \details
    Controls the lastChar flag for this TextProperties object.

    \param value [in] Property value to control the flag.
  */
  void setLastChar(bool value) { SETBIT(m_flags, kLastChar, value); }

  /** \details
    Checks whether the inBigFont flag is set for this TextProperties object.

    \returns The true value if the inBigFont flag is set for this TextProperties object successfully, or false otherwise.
  */
  bool isInBigFont() const { return GETBIT(m_flags, kInBigFont); }

  /** \details
    Controls the inBigFont flag for this TextProperties object.

    \param value [in] Property value to control the flag.
  */
  void setInBigFont(bool value) { SETBIT(m_flags, kInBigFont, value); }

  /** \details
    Checks whether the includePenups flag is set for this TextProperties object.

    \returns The true value if the includePenups flag is set for this TextProperties object successfully, or false otherwise.
  */
  bool isIncludePenups() const { return GETBIT(m_flags, kInclPenups); }

  /** \details
    Controls the includePenups flag for this TextProperties object.

    \param value [in] Property value to control the flag.
  */
  void setIncludePenups(bool value) { SETBIT(m_flags, kInclPenups, value); }

  /** \details
    Checks whether the kZeroNormals flag is set for this TextProperties object.

    \returns The true value if the zeroNormals flag is set for this TextProperties object successfully, or false otherwise.
  */
  bool isZeroNormals() const { return GETBIT(m_flags, kZeroNormals); }

  /** \details
    Controls the kZeroNormals flag for this TextProperties object.

    \param value [in] Property value to control the flag.
  */
  void setZeroNormals(bool value) { SETBIT(m_flags, kZeroNormals, value); }

  /** \details
    Gets the smooth TrueType font text contour output flag.

    \returns The smooth TrueType font text contour output flag.
  */
  bool ttfPolyDraw() const { return GETBIT(m_flags, kBezierCurves); }

  /** \details
    Sets the smooth TrueType font text contour output flag.

    \param bFlag [in] New flag value.
  */
  void setTtfPolyDraw(bool bFlag) { SETBIT(m_flags, kBezierCurves, bFlag); }

  /** \details
    Gets the tracking percent for this TextProperties object.

    \returns The tracking percent for this TextProperties object.
  */
  double trackingPercent() const {return m_trackingPercent; }

  /** \details
    Sets the tracking percent for this TextProperties object.

    \param trackingPercent [in] Tracking percent to set.
  */
  void setTrackingPercent(double trackingPercent) { m_trackingPercent = trackingPercent; }

  /** \details
    Gets the text quality percent for this vectorization process.

    \returns The text quality percent for this vectorization process.
    \remarks
    Returns a value in the range [0,100]. 
    The default is 50.
  */
  OdUInt32 textQuality() const { return m_textQuality; }

  /** \details
    Sets the text quality percent for this vectorization process.

    \param val [in] Property value to set.
    \remarks
    Sets a value in the range [0,100]. 
    The default is 50.
  */
  void setTextQuality(OdUInt32 val) { m_textQuality = (OdUInt16)val; }

  /** \details
    Checks whether the kTringleCache flag is set for this TextProperties object.

    \returns The true value if the kTringleCache flag is set for this TextProperties object successfully, or false otherwise.
  */
  bool isTriangleCache() const { return GETBIT(m_flags, kTriangleCache); }

  /** \details
    Controls the kTringleCache flag for this TextProperties object.
    
    \param value [in] Property value to control the flag.
  */
  void setSetTriangleCache(bool value) { SETBIT(m_flags, kTriangleCache, value); }

  // For internal use only
  /** \details
    Checks whether the kLastPosOnly flag is set for this TextProperties object.

    \returns The true value if the kLastPosOnly flag is set for this TextProperties object, or false otherwise.
  */
  bool isLastPosOnly() const { return GETBIT(m_flags, kLastPosOnly); }

  /** \details
    Controls the kLastPosOnly flag for this TextProperties object.

    \param value [in] Property value to control the flag.
  */
  void setLastPosOnly(bool value) { SETBIT(m_flags, kLastPosOnly, value); }

  /** \details
    Checks whether the kIsGlyph flag is set for this TextProperties object.

    \returns The true value if the kIsGlyph flag is set for this TextProperties object, or false otherwise.
  */
  bool isGlyph() const { return GETBIT(m_flags, kIsGlyph); }

  /** \details
    Controls the kIsGlyph flag for this TextProperties object.

    \param value [in] Property value to control the flag.
  */
  void setGlyph(bool value) { SETBIT(m_flags, kIsGlyph, value); }
};

typedef OdUInt32 OdFontSubType;

class OdGePoint2d;
class OdGiConveyorGeometry;
class OdTtfDescriptor;

/** \details
    This class is the base interface class for classes that implement font objects.
    <group Other_Classes>
*/
class FIRSTDLL_EXPORT OdFont : public OdRxObject
{
  OdUInt32 m_Flags;

public:
  ODRX_DECLARE_MEMBERS(OdFont);

  OdFont() : m_Flags(0) {}

  enum
  {
    kBigFont10 = 0x0001,
    kUniFont10 = 0x0002,
    kFont10    = 0x0004,
    kFont11    = 0x0008,
    kFont10A   = 0x0010,
    kTrueType  = 0x0020,
    kFontGdt   = 0x0040,
    kFontSimplex6 = 0x0080,
    kShapes11   = 0x0100,
    kFontRsc    = 0x0200   // MicroStation resource file.
  };

  /** \details
    Returns the font flags for this font object.

    \returns The font flags for this font object.
    \remarks
    Returns a combination of zero or more of the following: 
    
    <table>
    Name              Value
    kBigFont10        0x0001
    kUniFont10        0x0002
    kFont10           0x0004
    kFont11           0x0008
    kFont10A          0x0010
    kTrueType         0x0020
    kFontGdt          0x0040
    kFontSimplex6     0x0080
    kShapes11         0x0100
    kFontRsc          0x0200
    </table>
  */
    OdUInt32 getFlags() const { return m_Flags; }

  /** \details
    Returns the font flags for this font object.
    
    \returns The font flags for this font object.
    \remarks
    Returns a combination of zero or more of the following: 
    
    <table>
    Name              Value
    kBigFont10        0x0001
    kUniFont10        0x0002
    kFont10           0x0004
    kFont11           0x0008
    kFont10A          0x0010
    kTrueType         0x0020
    kFontGdt          0x0040
    kFontSimplex6     0x0080
    kShapes11         0x0100
    kFontRsc          0x0200
    </table>
  */
    OdUInt32 flags() { return m_Flags; }

  /** \details
    Sets the font flags for this font object.

    \param fontFlags [in] Property font flags to set.
    \remarks
    Font flags must be a combination of zero or more of the following:
    
    <table>
    Name              Value
    kBigFont10        0x0001
    kUniFont10        0x0002
    kFont10           0x0004
    kFont11           0x0008
    kFont10A          0x0010
    kTrueType         0x0020
    kFontGdt          0x0040
    kFontSimplex6     0x0080
    kShapes11         0x0100
    kFontRsc          0x0200
    </table>
  */
    void setFlags(OdUInt32 fontFlags) { m_Flags = fontFlags; }

  /** \details
    Adds the specified font flags to this font object.

    \param fontFlags [in] Property font flags to set.
    \remarks
    Font flags must be a combination of zero or more of the following:
     
    <table>
    Name              Value
    kBigFont10        0x0001
    kUniFont10        0x0002
    kFont10           0x0004
    kFont11           0x0008
    kFont10A          0x0010
    kTrueType         0x0020
    kFontGdt          0x0040
    kFontSimplex6     0x0080
    kShapes11         0x0100
    kFontRsc          0x0200
    </table>
  */
    void addFlag(OdUInt32 fontFlags) { m_Flags |= fontFlags; }

  /** \details
    Initializes this font object to read font data from the specified StreamBuf object.

    \param pStreamBuf [in] Pointer to the StreamBuf object from which the data is to be read.
    \returns Returns eOk if the font object is initialized successfully, or an appropriate error code otherwise.    
  */
      virtual OdResult initialize(OdStreamBuf* pStreamBuf) = 0;

  /** \details
    Draws the specified character with this font object.

    \param character [in] Character to draw.
    \param advance [in] Offset to next character.
    \param pWd [in/out] Draw object that can be used by this function to set the necessary attributes and create the necessary geometry.
    \param textProperties [in] Text properties.

    \returns Returns eOk if the specified character is drawn with the font object successfully, or an appropriate error code otherwise.
  */
  virtual OdResult     drawCharacter(OdChar character, OdGePoint2d& advance, OdGiCommonDraw* pWd,
                                     OdTextProperties& textProperties) = 0;

  /** \details
    Draws the specified character with this font object.

    \param character [in] Character to draw.
    \param advance [in] Offset to next character.
    \param pGeometry [in] Pointer to the modeler geometry.
    \param textProperties [in] Text properties.

    \returns Returns eOk if the specified character is drawn with the font object successfully, or an appropriate error code otherwise.
  */
  virtual OdResult     drawCharacter(OdChar character, OdGePoint2d& advance,
                                     OdGiConveyorGeometry* pGeometry,
                                     OdTextProperties& textProperties) = 0;
  /** \details
    Returns the height of this font object above the baseline.

    \returns The height of this font object above the baseline.
  */
  virtual double       getAbove() const = 0;

  /** \details
    Returns the depth of this font object below the baseline.

    \returns The depth of this font object below the baseline.
  */
  virtual double       getBelow() const = 0;

  /** \details
    Returns an array of the characters defined in this font object.

    \param characters [out] Receives the array of characters.
    \returns The array of the characters defined in this font object.
  */
  virtual OdUInt32     getAvailableChars(OdCharArray& characters) = 0;

  /** \details
    Checks whether the specified character is defined in this font object.

    \param character [in] Character.
    \returns The true value if the specified character is defined in this font object successfully, or an appropriate error code otherwise.
  */
  virtual bool        hasCharacter(OdChar character) = 0;
  
  /** \details
    Returns the height of this font object.

    \returns The height of this font object.
  */
  virtual double      getHeight() const                                                   // MKU 20.02.2003
  {
    return getAbove() + getBelow();
  }

  /** \details
    Returns the internal leading of this font object.

    \returns The internal leading of this font object.
    \remarks
    The default implementation of this function always returns 0.
  */
  virtual double getInternalLeading() const
  {
    return 0;
  }


  //  removed here from GiContextForDbDatabase.cpp              // MKU 04.03.2003

  /** \details
    Returns the height of this font object above the baseline.

    \returns The height of this font object above the baseline.
    \remarks
    The default implementation of this function returns getAbove() unless it is 0.0, in which case this function returns 1.0. 
  */
  double fontAbove() const  
  {
    double above = getAbove();
    if(OdZero(above))
    {
      above = 1.0;
    }
    return above;
  }

  /** \details
    Returns the underline position for this font object at the specified text size.

    \param textSize [in] Text size.
    \returns The underline position for this font object at the specified text size.
    \remarks
    The default implementation of this function returns -2.0 * textSize.
  */
  virtual double getUnderlinePos(double textSize) const
  {
    return -0.2 * textSize;
    
  }
  /** \details
    Returns the overline position for this font object at the specified text size.

    \param textSize [in] Text size.
    \returns The overline position for this font object at the specified text size.
    \remarks
    The default implementation of this function returns 1.2 * textSize.
  */
  virtual double getOverlinePos(double textSize) const
  {
    return 1.2 * textSize;
  }
  
  /** \details
    Checks whether this font object is an SHX font.

    \returns The true value if the font object is an SHX font, or false otherwise.
    \remarks
    The default implementation of this function always returns true.
  */
  virtual bool isShxFont()
  {
    return true;
  }

  /** \details
    Returns the average width of characters in this font object.

    \returns The average width of characters in this font object.
    \remarks
    The default implementation of this function always returns 0.0.
  */
  virtual double getAverageWidth()
  {
    return 0.0;
  }

  /** \details
    Returns an array of points over and under the baseline for the specified character in this OdFont object.

    \param character [in] Character.
    \param advance [in] Offset to next character.
    \param pointsOver [in] Array of points over the baseline.
    \param pointsUnder [in] Array of points under the baseline.
    \param textFlags [in] Text flags.
    \returns Array of points over and under the baseline for the specified character in this OdFont object.
    \remarks
    The default implementation of this function does nothing.

    The textFlags parameter must be a combination of one or more of the following:
 
    <table>
    Name                                Value
    OdTextProperties::kNormalText       0x01
    OdTextProperties::kVerticalText     0x02
    OdTextProperties::kUnderlined       0x04
    OdTextProperties::kOverlined        0x08
    OdTextProperties::kLastChar         0x10
    OdTextProperties::kInBigFont        0x20
    OdTextProperties::kInclPenups       0x40
    </table>
  */
  virtual void getScore( OdChar character,
                         OdGePoint2d& advance, 
                         OdGePoint3d* pointsOver,
                         OdGePoint3d* pointsUnder,
                         const OdTextProperties& textFlags);

  /** \details
    Returns the font data for the specified character.

    \param dwTable [in] Metric table to query.
    \param dwOffset [in] Offset into table.
    \param pBuffer [in] Pointer to the buffer to receive the data.
    \param cbData [in] The length, in bytes, of the information to be retrieved.
    \returns The font data for the specified character.
    \remarks
    The default implementation of this function does nothing but return -1.

    The number of bytes returned in the buffer.
  */
  virtual OdUInt32 getFontData(
    OdUInt32 dwTable,     // Metric table to query
    OdUInt32 dwOffset,    // Offset into table being queried
    void * pBuffer,  // Pointer to buffer for returned data
    OdUInt32 cbData       ) const;

  /** \details
    Checks whether the font supports vertical mode.
    \returns The true value if the font supports vertical mode, or false otherwise.
    \remarks
    The default implementation of this function returns false.
  */
  virtual bool supportsVerticalMode()
  {
    return false;
  }

  /** \details
    Returns the font file name.

    \returns The font file name.
    \remarks
    The default implementation of this function returns an empty string.
  */
  virtual OdString getFileName() const
  {
    return OdString();
  }

  /** \details
    Gets the OdTtfDescriptor for this font.

    \param descr [out] TrueType font descriptor.
  */
  virtual void getDescriptor(OdTtfDescriptor& descr) const
  {
  }

  /** \details
    Returns the LOGFONT for this font.

    \param lpLogFont [in] Pointer to the buffer to receive the data.
    \returns The number of bytes returned in the buffer.
    
    \remarks
    The default implementation of this function does nothing but return -1.
    If lpLogFont is NULL, the method returns the number of bytes required in the buffer. 
  */
  virtual OdInt32 getLogFont(void* lpLogFont) const
  {
    return -1;
  }
};

inline void OdFont::getScore( OdChar /*character*/, 
                         OdGePoint2d& /*advance*/, 
                         OdGePoint3d* /*pointsOver*/,
                         OdGePoint3d* /*pointsUnder*/,
                         const OdTextProperties& /*flags*/ )
  {}

inline OdUInt32 OdFont::getFontData(
    OdUInt32 /*dwTable*/,     // Metric table to query
    OdUInt32 /*dwOffset*/,    // Offset into table being queried
    void * /*lpvBuffer*/,  // Pointer to buffer for returned data
    OdUInt32 /*cbData*/       ) const
  {
    return OdUInt32(-1);
  }


/** \details
  This template class is a specialization of the OdSmartPtr class for OdFont object pointers.
*/
typedef OdSmartPtr<OdFont> OdFontPtr;

/** \details
  This class is the base interface class for text iterators.
  
  <group Other_Classes>
*/
class FIRSTDLL_EXPORT OdBaseTextIterator : public OdRxObject
{
public:
  virtual OdChar nextChar() = 0;
  /** \details
  Returns the properties of the character at the current position of this TextIterator object.

  \returns The properties of the character at the current position of this TextIterator object.
  */
  virtual const OdCharacterProperties& currProperties() const = 0;

  /** \details
  Returns the character at the current position of this TextIterator object.

  \returns The character at the current position of this TextIterator object.
  */
  virtual const OdChar* currPos() const = 0;
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdBaseTextIterator object pointers.
*/
typedef OdSmartPtr<OdBaseTextIterator> OdBaseTextIteratorPtr;

#include "TD_PackPop.h"

#endif // !defined(AFX_ODFONT_H__0B76813A_DCFA_450E_8591_B6C6F1ED76EC__INCLUDED_)

