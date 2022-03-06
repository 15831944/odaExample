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

#ifndef _DAI_TEXT_ENCODE_DECODE_H_
#define _DAI_TEXT_ENCODE_DECODE_H_

#include "OdaCommon.h"
#include "daiBuildOptions.h"
#include "DbHandle.h"
#include "OdString.h"

namespace OdDAI
{
  namespace Utils
  {
    /** \details
    Defines type of conversion codecs.
    */
    enum class CodecType
    {
      /** UTF8 codec. */
      utf8,

      /** ISO8895 codec. */
      iso8895
    };

    /** \details
      Encode widechar string to char string with using special codecs.
      \param encodeWhat [in] widechar conversion destination.
      \param encodeTo [out] encoded char result target.
      \param encodeType [out] codec type.
      \returns Returns true if conversion were ended successfully, or a false otherwise.
   */
    bool DAI_EXPORT encodeText(const OdString& encodeWhat, OdAnsiString& encodeTo, CodecType encodeType);

    /** \details
      Decode encoded char string to widechar string with using special codecs.
      \param encodeWhat [in] char encoded conversion destination.
      \param encodeTo [out] decoded widechar result target.
      \param encodeType [out] codec type.
      \returns Returns true if conversion were ended successfully, or a false otherwise.
   */
    bool DAI_EXPORT decodeText(const OdAnsiString& decodeWhat, OdString& decodeTo, CodecType decodeType);

    /** \details
      Converts ISO8859 text to UTF8 text.
      \param from [in] converts destination.
      \param to [out] converts target.
      \returns Returns true if conversion were ended successfully, or a false otherwise.
    */
    bool DAI_EXPORT fromISO8859_ToUtf8(const OdAnsiString& from, OdAnsiString& to);

    /** \details
      Converts UTF8 text to ISO8859 text.
      \param from [in] converts destination.
      \param to [out] converts target.
      \returns Returns true if conversion were ended successfully, or a false otherwise.
    */
    bool DAI_EXPORT fromUtf8_ToISO8859(const OdAnsiString& from, OdAnsiString& to);

    /** \details
      Checks if string contains upper case characters.
      \param str [in] A string to check.
      \returns Returns true if string contains at least one upper case character, or a false otherwise.
    */
    bool DAI_EXPORT findIfUpper(const OdAnsiString& str);
  }
}

#endif // _DAI_UTILS_H_

