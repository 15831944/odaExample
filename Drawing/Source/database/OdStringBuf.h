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

#ifndef __ODSTRINGBUF_H_
#define __ODSTRINGBUF_H_

#include "OdaCommon.h"

#include "TD_PackPush.h"

class TOOLKIT_EXPORT OdStringBuf : public OdRxObject
{
public:
  enum CharFormat
  {
    CharFormat_Undefined = 0, // Can't determine character format
    CharFormat_ANSI, // ANSI
    CharFormat_UTF8, // UTF8
    CharFormat_UTF16LE, // UTF16 LittleEndian
    CharFormat_UTF16BE, // UTF16 BigEndian
    CharFormat_UTF32LE, // UTF32 LittleEndian
    CharFormat_UTF32BE // UTF32 BigEndian
  };
protected:
  mutable OdStreamBufPtr m_pIo;
  CharFormat m_cf;
public:
  OdStringBuf();
  void init(OdStreamBuf* pIo, CharFormat cf = CharFormat_Undefined);

  ODRX_DECLARE_MEMBERS(OdStringBuf);

  virtual OdString getString();

  inline OdStreamBuf* getIOPtr() const
  {
    return ((OdStreamBuf*)(m_pIo.get()));
  }

  inline CharFormat getCharFormat()
  {
    return m_cf;
  }
protected:
  OdStringBuf::CharFormat DetermineCharFormat() const;
  OdChar ReadChar(OdChar &secChr) const;
  OdInt64 GetUnicodeHeaderSize() const;
  OdInt64 GetUnicodeBitSize() const;
  // Conversions
  OdChar FromANSI(OdUInt8 chr) const;
  OdChar FromUTF8(OdUInt8 chr) const;
  OdChar FromUTF16LE(OdUInt16 chr) const;
  OdChar FromUTF16BE(OdUInt16 chr) const;
  OdChar FromUTF32LE(OdUInt32 chr, OdChar &secChr) const;
  OdChar FromUTF32BE(OdUInt32 chr, OdChar &secChr) const;
  // Cross-platform swap bytes
  static void Swap2BytesNumber(OdUInt16& W);
  static void Swap4BytesNumber(OdUInt32& DW);
  static void Swap2BytesChar(OdChar& W);

public:
  // Static
  static OdUInt32 GetUnicodeHeaderForType(OdStringBuf::CharFormat type);
  static OdInt64 GetUnicodeHeaderSizeForType(OdStringBuf::CharFormat type);
  static OdInt64 GetUnicodeBitSizeForType(OdStringBuf::CharFormat type);
  static void DefaultingType(OdStringBuf::CharFormat &type);
  static void DefaultUTF16Type(OdStringBuf::CharFormat &type);
  static void DefaultUTF32Type(OdStringBuf::CharFormat &type);
  // Save to stream
  static void WriteUnicodeHeader(OdStringBuf::CharFormat type, OdStreamBuf &io);
  static void WriteString(OdStringBuf::CharFormat type, OdStreamBuf &io, const char *text);
  static void WriteString(OdStringBuf::CharFormat type, OdStreamBuf &io, const OdChar *text);
  // Additional
  static void WriteNL(OdStringBuf::CharFormat type, OdStreamBuf &io, bool use_odc = true);
  static void WriteSpace(OdStringBuf::CharFormat type, OdStreamBuf &io, bool use_odc = true);
  static void WriteTab(OdStringBuf::CharFormat type, OdStreamBuf &io, bool use_odc = true);
  // Types
  static void WriteOdInt8(OdStringBuf::CharFormat type, OdStreamBuf &io, OdInt8 var);
  static void WriteOdUInt8(OdStringBuf::CharFormat type, OdStreamBuf &io, OdUInt8 var);
  static void WriteOdInt16(OdStringBuf::CharFormat type, OdStreamBuf &io, OdInt16 var);
  static void WriteOdUInt16(OdStringBuf::CharFormat type, OdStreamBuf &io, OdUInt16 var);
  static void WriteOdInt32(OdStringBuf::CharFormat type, OdStreamBuf &io, OdInt32 var);
  static void WriteOdUInt32(OdStringBuf::CharFormat type, OdStreamBuf &io, OdUInt32 var);
  static void WriteOdFloat(OdStringBuf::CharFormat type, OdStreamBuf &io, float var);
  static void WriteOdDouble(OdStringBuf::CharFormat type, OdStreamBuf &io, double var);
};

typedef OdSmartPtr<OdStringBuf> OdStringBufPtr;

#include "TD_PackPop.h"

#endif //__ODSTRINGBUF_H_
