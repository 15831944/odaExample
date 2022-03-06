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




#ifndef _OD_CHARMAPPER_H_
#define _OD_CHARMAPPER_H_

#include "TD_PackPush.h"

#include "OdCodePage.h"
#include "OdError.h"
#include "OdArray.h"
#include "IntArray.h"

class OdStreamBuf;
class OdString;
class OdFont;
typedef OdArray <char, OdMemoryAllocator<char> > OdAnsiCharArray;
typedef OdArray<OdChar, OdMemoryAllocator<OdChar> > OdCharArray;


/** \details
    This class implements character mapping.
    Corresponding C++ library: TD_Root
    <group Other_Classes>
*/
class FIRSTDLL_EXPORT OdCharMapper
{
  static OdString m_MapFile;
private:
	OdCharMapper();
public:
//	static OdResult initialize(OdStreamBuf* pIo);

  /** \details
    Initializes this CharMapper object from the specified mapping file.

    \param filename [in] File name.
    \returns eOk if the CharMapper is initialized successfully, or an appropriate error code otherwise.
  */
  static OdResult initialize(const OdString& filename);

  /** \details
    Maps the specified Unicode character to the specified code page.

    \param sourceChar [in] Unicode source character.
    \param codepageId [in] Object ID of the code page.
    \param codepageChar [out] Receives the code page character.
    \param bTryToUseSystemCP [in] Try to use the default ANSI code page and OEM code page if conversion with codepageId is not OK.
    \returns eOk if the code page character is received successfully, or an appropriate error code otherwise.
  */
  static OdResult unicodeToCodepage(OdChar sourceChar,
    OdCodePageId codepageId,
    OdChar& codepageChar,
    bool bTryToUseSystemCP = true );

  /** \details
    Maps the specified Unicode character to the specified code page using the IMLangFontLink2 interface.
    
    \param sourceChar [in]  Unicode source character.
    \param codepageId [in]  Object ID of the code page.
    \param codepageChar [out]  Receives the code page character.
    \returns eOk if the code page character is received successfully, or an appropriate error code otherwise.
  */
  static OdResult unicodeToCodepage2(OdChar sourceChar,
    OdCodePageId codepageId,
    OdChar& codepageChar);

  /** \details
    Maps the specified code page character to Unicode.

    \param sourceChar [in]  Code page source character.
    \param codepageId [in]  Object ID of the code page.
    \param unicodeChar [out]  Receives the Unicode character.
    \returns eOk if the Unicode character is received successfully, or an appropriate error code otherwise.
  */
  static OdResult codepageToUnicode(OdChar sourceChar,
    OdCodePageId codepageId,
    OdChar& unicodeChar);

  /** \details
    Checks whether the specified byte is one of the leading bytes of the specified code page.

    \param testByte [in] Byte to test.
    \param codepageId [in] Object ID of the code page.
    \returns true if the specified byte is one of the leading bytes of the specified code page, or false otherwise.
  */
  static bool isLeadByte(OdUInt8 testByte, OdCodePageId codepageId);

  /** \details
    Gets the code page with the specified description.

    \param description [in] Description.  
    \param codepageId [out] Receives the object ID of the code page.  
    \returns eOk if the object ID of the code page is received successfully, or an appropriate error code otherwise.
  */
  static OdResult codepageDescToId(const OdString& description, OdCodePageId& codepageId);

  /** \details
    Gets the description for the specified code page.

    \param codepageId [in] Object ID of the code page.
    \param description [out] Receives the description.  
    \returns eOk if the description is received successfully, or an appropriate error code otherwise.
  */
  static OdResult codepageIdToDesc(OdCodePageId codepageId, OdString& description);

  /** \details
    Returns the number of valid code pages for this CharMapper object.

    \returns The number of valid code pages for this CharMapper object.
  */
  static OdUInt32 numValidCodepages();

  /** \details
    Returns the code page corresponding to the specified ANSI code page.

    \param ansiCodePage [in] ANSI code page.
    \returns The code page corresponding to the specified ANSI code page.
  */
  static OdCodePageId ansiCpToAcadCp(OdUInt32 ansiCodePage);

  /** \details
    Returns the ANSI code page corresponding to the specified code page.

    \param acadCodePageId [in] Code page.
    \returns The ANSI code page corresponding to the specified code page.
  */
  static OdUInt32 acadCpToAnsiCp(OdCodePageId acadCodePageId);

  /** \details
    Returns the code page corresponding to the specified ANSI character set.

    \param ansiCharacterSet [in] Character set.
    \returns The code page corresponding to the specified ANSI character set.
  */
   static OdCodePageId getCodepageByCharset(OdUInt16 ansiCharacterSet);

   /** \details
     Gets the charset corresponding to the specified character.

     \param ch [in]  Character.
     \returns The charset corresponding to the specified character.
     \remarks
     If the character is in the Hebrew range, returns 0xB1.
     If the character is in the Arabic range, returns 0xB2. 
     Otherwise returns 0.
   */
   static OdUInt16 getReorderCharsetByChar(OdChar ch);

   /** \details
     Checks whether the specified code page supports conversion.

     \param codepageId [in]  Object ID of the code page.
     \returns true if the specified code page supports conversion, or false otherwise.
   */
   static bool isConversionSupported(OdCodePageId codepageId);

   /** \details
     Maps the Unicode characters to the specified code page.

     \param codepage [in]  Destination character code page.
     \param srcBuf [in] Source Unicode character buffer.
     \param srcSize [in] Size of the source character buffer.
     \param dstBuf [out]  Receives the character array in the specified code page.
   */
   static void wideCharToMultiByte(OdCodePageId codePage, const OdChar* srcBuf, int srcSize, OdAnsiCharArray& dstBuf);

   /** \details
     Maps the specified code page characters to Unicode.
     \param codepage [in]  Source character code page.
     \param srcBuf [in]  Source character buffer.
     \param srcSize [in] Size source character buffer.
     \param dstBuf [out]  Receives the Unicode character array.
   */
   static void multiByteToWideChar(OdCodePageId codePage, const char* srcBuf, int srcSize, OdCharArray& dstBuf);

   // This is actually CESU-8 encoding used in DXF (http://www.unicode.org/reports/tr26/)
   /** \details
      Maps the UTF-8 characters to Unicode. 

     \param srcBuf [in] Source UTF-8 character buffer.
     \param srcSize [in] Size of the source character buffer.
     \param dstBuf [out]  Receives the Unicode character array.
     \returns true if the value is mapped successfully, or false otherwise.
   */
   static bool utf8ToUnicode(const char* srcBuf, int srcSize, OdCharArray& dstBuf);

   /** \details
     Maps the Unicode characters to UTF-8.

     \param srcBuf [in] Source Unicode character buffer.
     \param srcSize [in] Size of the source character buffer.
     \param dstBuf [out] Receives the UTF-8 character array.
   */
   static void unicodeToUtf8(const OdChar* srcBuf, int srcSize, OdAnsiCharArray& dstBuf);

   /** \details
     Adds a bigFont to a map with the specified code page index.

     \param bigFont [in] Big font file name.  
     \param cpIndex [in] Code page index.
     \returns eOk if the bigFont is added to the map successfully, or an appropriate error code otherwise.
     \remarks
     cpIndex must be one of the following:
     
     <table>
     Value    Description
     1        CP_ANSI_932
     2        CP_ANSI_950
     3        CP_ANSI_949
     5        CP_ANSI_936
     </table>
   */
   static OdResult addBigFontWithIndex(const OdString& bigFont, OdInt32 cpIndex);

   /** \details
     Adds a bigFont to a map with the specified code page ID.

     \param bigFont [in] Big font file name.  
     \param codePageId [in] Code page ID.
     \returns eOk if the bigFont is added to the map successfully, or an appropriate error code otherwise.
     \remarks
     codePageId must be one of the following:
     
     @untitled table
     CP_ANSI_932
     CP_ANSI_950
     CP_ANSI_949
     CP_ANSI_936
   */
   static OdResult addBigFontWithCodepage(const OdString& bigFont, OdCodePageId codePageId);

   /** \details
     Receives the bigFont list to map from the specified stream.

     \param io [in] Stream with next format.
     \returns eOk if the bigFont list is received successfully, or an appropriate error code otherwise.
     \remarks
     Anything after the '#' character is a comment (and ignored).
     The ';' character is used to separate the file name from the code page index.
  
     <BIGFONTFILENAME.SHX>;<CODE PAGE INDEX>
   
     There should be no leading or trailing spaces for the filename.
    
     JAPANESE_CODEPAGE_INDEX = 1,
     TRADITIONAL_CHINESE_CODEPAGE_INDEX = 2,
     KOREAN_CODEPAGE_INDEX = 3,
     KOREAN_JOHAB_CODEPAGE_INDEX = 4,
     SIMPLIFIED_CHINESE_CODEPAGE_INDEX = 5
   */
   static OdResult addBigFonts(OdStreamBuf* io);

   /** \details
     Gets the code page from a big font file name.

     \param bigFont [in] Big font file name.
     \returns The code page. 
     \remarks
     getCpByBigFont returns one of the following:
     
     @untitled table
     CP_ANSI_932
     CP_ANSI_950
     CP_ANSI_949
     CP_ANSI_936
   */
   static OdCodePageId getCpByBigFont(const OdString& bigFont);

   /** \details
     Gets the code page index from a bigFont file name.

     \param bigFont [in] Big font file name.
     \returns The code page index.
     \remarks
     getCpIndexByBigFont returns one of the following:
     
     <table>
     Value     Description
     1         CP_ANSI_932
     2         CP_ANSI_950
     3         CP_ANSI_949
     5         CP_ANSI_936
     </table>
   */
   static OdInt32 getCpIndexByBigFont(const OdString& bigFont);

   /** \details
     Gets the check sum for an ANSI string.

     \param str [in] String for calculating the check sum.
     \returns The check sum for an ANSI string.
   */
   static double getCheckSumAnsi(OdAnsiString str);

   /** \details
     Gets the check sum for a Unicode string.

     \param str [in] String for calculating the check sum.  
     \returns The check sum for a Unicode string.
   */
   static double getCheckSumUnicode(OdString str);

   /** \details
     Gets a converted Unicode string from the specified CIF coding string.

     \param str [in] Source string for conversion.
     \returns The Unicode string converted from the CIF coding string.
   */
   static OdString convertCIFcoding(const OdString& strText);

   /** \details
     Gets a converted Unicode string from the specified string in the Latin alphanumeric Japanese Unicode range.

     \param str [in] Source string for conversion.
     \returns The Unicode string converted from the Latin alphanumeric Japanese Unicode range.
   */
   static OdString convertAlphaNumJapanese(const OdString& strText);

   /** \details
     Gets a converted ANSI string from a specified string in the Latin alphanumeric Japanese code page.

     \param str [in] Source string for conversion.
     \returns The ANSI string converted from the Latin alphanumeric Japanese code page.
   */
   static OdAnsiString convertAlphaNumJapanese(const OdAnsiString& strText);

   /** \details
     Checking special sequences and replacing them with character codes. Look for following sequences: "%%", "\\U+", "\\u+", "\\M+", "\\m+".

     \param str [in/out] Source string.
     \param font [in] Font.
     \param ulRanges [out] Ranges underlined, overlined and striked.
     \returns true if special sequence was found and replaced, or false otherwise.
   */
   static bool containsSpecialSequence(OdString& str, OdFont* font, OdIntArray& ulRanges);

   /** \details
     Conversion source string with flags underlined, overlined and striked to string with special sequence %%u, %%o and %%k

     \param str [in] Source string.
     \param ulRanges [in] Ranges underlined, overlined and striked.
     \param length [out] Length returned string.
     \param raw [out] Raw flag.
     \returns Result string with special sequences if it is needed
   */
   static OdString embedTextRawData(const OdString &msg, const OdIntArray &ulFlags, int *length = NULL, bool *raw = NULL);
};

// Surrogate pairs support
template<class T> inline bool odIsLeadSurrogate(T chr) {
  return (chr >= 0xD800 && chr <= 0xDFFF);
}
template<class T> inline bool odIsTailSurrogate(T chr) {
  return (chr >= 0xDC00 && chr <= 0xDFFF);
}
template<class T1, class T2> inline T1 odToCodepoint(T1 chr, T2 chr2) {
  return (chr << 10) + chr2 + (0x10000 - (0xD800 << 10) - 0xDC00);
}
template<class T> inline OdUInt32 odToCodeValue(T chr, T chr2) {
  return ((OdUInt32)chr << 10) + chr2 + (0x10000 - (0xD800 << 10) - 0xDC00);
}
template<class T> inline bool odIsCodepoint(T chr) {
  return (chr >= 0x10000 && chr <= 0x10FFFF);
}
template<class T> inline T odToLeadSurrogate(T chr) {
  return ((0xD800 - (0x10000 >> 10)) + (chr >> 10));
}
template<class T> inline T odToTailSurrogate(T chr) {
  return (0xDC00 + (chr & 0x3FF));
}

/** \details
  Defines the Asian code page index.
*/ 
enum OdAsianCpIndex
{
  /** Japanese code page index. */
  JAPANESE_CP_INDEX = 1,              // 932
  /** Traditional Chinese code page index. */
  TRADITIONAL_CHINESE_CP_INDEX = 2,   // 950
  /** Korean Wansung code page index. */
  KOREAN_WANSUNG_CP_INDEX = 3,        // 949
  /** Korean Johab code page index. */
  KOREAN_JOHAB_CP_INDEX = 4,          // 1361
  /** Simplified Chinese code page index. */
  SIMPLIFIED_CHINESE_CP_INDEX = 5     // 936
};

#include "TD_PackPop.h"

#endif

