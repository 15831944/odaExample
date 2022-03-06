// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include <memory>

#include "core/fxge/cfx_fontmapper.h"
#include "core/fxge/ifx_systemfontinfo.h"

static ByteString GetStringFromTable(const uint8_t* string_ptr,
                                     uint32_t string_ptr_length,
                                     uint16_t offset,
                                     uint16_t length) {
  if (string_ptr_length < static_cast<uint32_t>(offset + length)) {
    return ByteString();
  }
  return ByteString(string_ptr + offset, length);
}

#ifdef ODA_CHANGES
namespace
{
  // These numbers come from the OpenType name table specification.
  constexpr uint16_t kNamePlatformMac = 1;
  constexpr uint16_t kNameMacEncodingRoman = 0;
  constexpr uint16_t kNamePlatformWindows = 3;
  constexpr uint16_t kNameWindowsEncodingUnicode = 1;

  WideString FromUTF16BE(const unsigned short* wstr, size_t wlen)
  {
    if (!wstr || wlen == 0)
      return WideString();

    WideString result;
    {
      wchar_t* buf = result.GetBuffer(wlen);
      for (size_t i = 0; i < wlen; i++)
      {
        auto wch = wstr[i];
        wch = (wch >> 8) | (wch << 8);
        buf[i] = wch;
      }
    }
    result.ReleaseBuffer(wlen);
    return result;
  }
}

ByteString GetNameFromTT(const uint8_t* name_table,  uint32_t name_table_size, uint32_t name_id) 
{
  if (!name_table || name_table_size < 6) 
  {
    return ByteString();
  }
  uint32_t name_count = GET_TT_SHORT(name_table + 2);
  uint32_t string_offset = GET_TT_SHORT(name_table + 4);
  // We will ignore the possibility of overlap of structures and
  // string table as if it's all corrupt there's not a lot we can do.
  if (name_table_size < string_offset) 
  {
    return ByteString();
  }

  const uint8_t* string_ptr = name_table + string_offset;
  uint32_t string_ptr_size = name_table_size - string_offset;
  name_table += 6;
  name_table_size -= 6;
  if (name_table_size < name_count * 12) {
    return ByteString();
  }

  for (uint32_t i = 0; i < name_count;  i++, name_table += 12)
  {
    if (GET_TT_SHORT(&name_table[6]) == name_id) 
    {
      const uint16_t platform_identifier = GET_TT_SHORT(name_table);
      const uint16_t platform_encoding = GET_TT_SHORT(&name_table[2]);

      if (platform_identifier == kNamePlatformMac &&
        platform_encoding == kNameMacEncodingRoman)
      {
        return GetStringFromTable(string_ptr, string_ptr_size, GET_TT_SHORT(&name_table[10]), GET_TT_SHORT(&name_table[8]));
      }
      if (platform_identifier == kNamePlatformWindows && platform_encoding == kNameWindowsEncodingUnicode) 
      {
        // This name is always UTF16-BE and we have to convert it to UTF8.
        ByteString utf16_be = GetStringFromTable(string_ptr, string_ptr_size, GET_TT_SHORT(&name_table[10]), GET_TT_SHORT(&name_table[8]));
        if (utf16_be.IsEmpty() || utf16_be.GetLength() % 2 != 0) 
        {
          return ByteString();
        }

        const uint8_t* raw_span = utf16_be.raw_str();
        return FromUTF16BE(reinterpret_cast<const uint16_t*>(raw_span), utf16_be.GetLength() / 2).UTF8Encode();
      }
    }
  }
  return ByteString();
}
#else
ByteString GetNameFromTT(const uint8_t* name_table,
                         uint32_t name_table_size,
                         uint32_t name_id) {
  if (!name_table || name_table_size < 6) {
    return ByteString();
  }
  uint32_t name_count = GET_TT_SHORT(name_table + 2);
  uint32_t string_offset = GET_TT_SHORT(name_table + 4);
  // We will ignore the possibility of overlap of structures and
  // string table as if it's all corrupt there's not a lot we can do.
  if (name_table_size < string_offset) {
    return ByteString();
  }

  const uint8_t* string_ptr = name_table + string_offset;
  uint32_t string_ptr_size = name_table_size - string_offset;
  name_table += 6;
  name_table_size -= 6;
  if (name_table_size < name_count * 12) {
    return ByteString();
  }

  for (uint32_t i = 0; i < name_count; i++, name_table += 12) {
    if (GET_TT_SHORT(name_table + 6) == name_id &&
        GET_TT_SHORT(name_table) == 1 && GET_TT_SHORT(name_table + 2) == 0) {
      return GetStringFromTable(string_ptr, string_ptr_size,
                                GET_TT_SHORT(name_table + 10),
                                GET_TT_SHORT(name_table + 8));
    }
  }
  return ByteString();
}
#endif // ODA_CHANGES

#ifdef PDF_ENABLE_XFA
void* IFX_SystemFontInfo::MapFontByUnicode(uint32_t dwUnicode,
                                           int weight,
                                           bool bItalic,
                                           int pitch_family) {
  return nullptr;
}
#endif  // PDF_ENABLE_XFA

int IFX_SystemFontInfo::GetFaceIndex(void* hFont) {
  return 0;
}

extern "C" {
unsigned long _FTStreamRead(FXFT_Stream stream,
                            unsigned long offset,
                            unsigned char* buffer,
                            unsigned long count);
void _FTStreamClose(FXFT_Stream stream);
};

#if _FX_OS_ == _FX_OS_ANDROID_
std::unique_ptr<IFX_SystemFontInfo> IFX_SystemFontInfo::CreateDefault(
    const char** pUnused) {
  return nullptr;
}
#endif
