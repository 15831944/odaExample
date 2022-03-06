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

#ifndef _PRCFONTKEYSSAMEFONT_INCLUDED_
#define _PRCFONTKEYSSAMEFONT_INCLUDED_ 
 

/** \details
<group PRC_Miscellaneous_Classes>

Class stores information about a list of usages for the same font and character set with various attributes.
*/
class PRC_TOOLKIT OdPrcFontKeysSameFont
{
public:
  /** \details
  Structure contains information about font attributes. 
  */
  struct FontKey
  {
    /** \details
    Font attributes structure default constructor.
    */
    FontKey()
    {
      font_size = attributes = 0;
    }

    OdInt32 font_size; /** Font size.*/

    /** \details 
    Font attribute flags. 
    <table>
    Value   Description
    2       Bold flag.
    4       Italic flag.
    8       Underlined flag.
    16      Strike-Out flag.
    32      Overlined flag.
    64      Stretch flag. If switched on, indicates that the text must be streched to fit within its bounding box. Used only if the original font is not used. 
    128     Wire flag. If switched on, the original font is a wireframe font.
    256     Fixed width flag. If switched on, the original font is not proportional (each glyph has the same width).
  </table>
    */
    OdUInt8 attributes;
  };

private:
  OdArray<FontKey>  m_font_keys;
  OdUInt32          m_char_set;
  OdString          m_font_name;

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcFontKeysSameFont)
  //DOM-IGNORE-END

  /** \details
  Returns the current list of font keys.
  The font keys list is returned as a reference to an array of OdPrcFontKeysSameFont::FontKey structures, 
  therefore it can be used to set a new font keys list.
  */
  OdArray<FontKey> &fontKeys();
  
  /** \details
  Returns the current list of font keys.
  */
  const OdArray<FontKey> &fontKeys() const;
  
  /** \details
  Sets a new font name.
  
  \param font_name [in] A new font name to be set.
  */
  void setFontName(OdString font_name);
  
  /** \details
  Returns the current font name.
  */
  OdString fontName() const;
  
  /** \details
  Sets a new character set code for the font.
  
  \param char_set [in] A new character set code to be set.
  
  Character set codes are represented in the table below:
  <table>
    Value   Description
    0       Roman 
    1       Japanese 
    2       Traditional Chinese 
    3       Korean 
    4       Arabic 
    5       Hebrew 
    6       Greek 
    7       Cyrillic 
    8       RightLeft 
    9       Devanagari 
    10      Gurmukhi 
    11      Gujarati 
    12      Oriya 
    13      Bengali 
    14      Tamil 
    15      Telugu 
    16      Kannada 
    17      Malayalam 
    18      Sinhalese 
    19      Burmese 
    20      Khmer 
    21      Thai 
    22      Laotian 
    23      Georgian 
    24      Armenian 
    25      Simplified Chinese 
    26      Tibetan 
    27      Mongolian 
    28      Geez 
    29      EastEuropeanRoman 
    30      Vietnamese 
    31      ExtendedArabic
  </table>
  */
  void setCharSet(OdUInt32 char_set);
  
  /** \details
  Returns the current character set code.
  Character set codes are represented in the table below:
  <table>
    Value   Description
    0       Roman 
    1       Japanese 
    2       Traditional Chinese 
    3       Korean 
    4       Arabic 
    5       Hebrew 
    6       Greek 
    7       Cyrillic 
    8       RightLeft 
    9       Devanagari 
    10      Gurmukhi 
    11      Gujarati 
    12      Oriya 
    13      Bengali 
    14      Tamil 
    15      Telugu 
    16      Kannada 
    17      Malayalam 
    18      Sinhalese 
    19      Burmese 
    20      Khmer 
    21      Thai 
    22      Laotian 
    23      Georgian 
    24      Armenian 
    25      Simplified Chinese 
    26      Tibetan 
    27      Mongolian 
    28      Geez 
    29      EastEuropeanRoman 
    30      Vietnamese 
    31      ExtendedArabic
  </table>
  */
  OdUInt32 charSet() const;
};
typedef OdArray<OdPrcFontKeysSameFont> OdPrcFontKeysSameFontArray;

#endif // _PRCFONTKEYSSAMEFONT_INCLUDED_

