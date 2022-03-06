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
#ifndef __NW_READSTREAMCOMMON_H__
#define __NW_READSTREAMCOMMON_H__

#include "OdPlatformStreamer.h"
#include "NwFragmentType.h"
#include "NwModelUnits.h"
#include "NwColor.h"
#include "NwLinearUnits.h"
#include <time.h>
#include "OdBinaryData.h"
#include "NwStreamAlignment.h"
#include "OdCharMapper.h"
#include "TD_PackPush.h"

#ifndef NW_STARTSTREAM
#define NW_STARTSTREAM 0x00000064 
#endif

namespace NwStreamCommon
{
  template <OdNmStreamAlignment::Enum align>
  inline void alignPointer(OdStreamBuf& streamBuf)
  {
    OdUInt64 pos = streamBuf.tell();
    if ((align == OdNmStreamAlignment::EightBytes && (pos % 8 != 0)) ||
      (align == OdNmStreamAlignment::FourBytes && (pos % 8 == 0)))
      streamBuf.seek(4, OdDb::kSeekFromCurrent);
  }

  inline OdInt32 readStreamBitfield(OdStreamBuf& streamBuf)
  {
    ODA_ASSERT(OD_T("readStreamBitfield") && !(streamBuf.tell() % 4));

    return OdPlatformStreamer::rdInt32(streamBuf);
  }

  inline bool readBool(OdStreamBuf& streamBuf)
  {
    ODA_ASSERT(OD_T("readBool") && !(streamBuf.tell() % 4));

    auto res = OdPlatformStreamer::rdInt32(streamBuf);

    ODA_ASSERT(res == 1 || res == 0);

    return res ? true : false;
  }

  inline OdUInt32 readUInt8(OdStreamBuf& stream)
  {
    return stream.getByte();
  }

  inline OdUInt32 readUInt16(OdStreamBuf& stream)
  {
    OdUInt16 res;
    stream.getBytes(&res, sizeof(res));
    odSwap2BytesNumber(res);
    return res;
  }

  inline OdUInt32 readUInt32(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readUInt32") && !(stream.tell() % 4));

    OdUInt32 res;
    stream.getBytes(&res, sizeof(res));
    odSwap4BytesNumber(res);
    return res;
  }

  inline OdUInt64 readUInt64(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readUInt64") && !(stream.tell() % 8));

    OdUInt64 res;
    stream.getBytes(&res, sizeof(res));
    odSwap8Bytes(res);
    return res;
  }
  
  inline OdInt16 readInt16(OdStreamBuf& stream)
  {
    return OdPlatformStreamer::rdInt16(stream);
  }

  inline OdInt32 readInt32(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readInt32") && !(stream.tell() % 4));

    return OdPlatformStreamer::rdInt32(stream);
  }

  inline OdInt64 readInt64(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readInt64") && !(stream.tell() % 8));

    return OdPlatformStreamer::rdInt64(stream);
  }

  inline double readDouble(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readDouble") && !(stream.tell() % 8));

    return OdPlatformStreamer::rdDouble(stream);
  }

  inline float readFloat(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readFloat") && !(stream.tell() % 4));

    return OdPlatformStreamer::rdFloat(stream);
  }
  
  inline void readFloats(OdStreamBuf& streamBuf, int n, void* pResFloats)
  {
    streamBuf.getBytes(pResFloats, sizeof(float)*n);
    float* pF = (float*)pResFloats;
    while (n--) 
    {
      odSwap4Bytes(&pF++);
    }
  }

  inline OdUInt32 peekInt32(OdStreamBuf& stream)
  {
    const OdInt32 nRes = OdPlatformStreamer::rdInt32(stream);
    stream.seek(-4, OdDb::kSeekFromCurrent);
    return nRes;
  }

  inline OdUInt32 peekInt32Offset(OdStreamBuf& stream, OdInt32 offset)
  {
    OdInt64 pos = stream.tell();
    stream.seek(offset, OdDb::kSeekFromCurrent);
    OdUInt32 word = OdPlatformStreamer::rdInt32(stream);
    stream.seek(pos, OdDb::kSeekFromStart);
    return word;
  }

  inline void shiftBytes(OdStreamBuf& stream, OdInt32 offset)
  {
    stream.seek(offset, OdDb::kSeekFromCurrent);
  }

  inline void stepInt32(OdStreamBuf& stream, OdInt32 wordsCount = 1)
  {
    shiftBytes(stream, wordsCount * sizeof(OdInt32));
  }

  inline void skipSingleFillers(OdStreamBuf& stream)
  {
    OdInt64 pos = stream.tell();
    if (pos % 4 != 0)
      stream.seek(2, OdDb::kSeekFromCurrent);
  }

  inline void skipZeroFillers(OdStreamBuf& stream)
  {
    while (0 == OdPlatformStreamer::rdInt32(stream)) {}
      shiftBytes(stream, -4 /*-sizeof(OdUInt32)*/);
  }

  inline OdUInt32 readB_ABGR_Color(OdStreamBuf& stream)
  {
    OdUInt8 alpha = stream.getByte();
    OdUInt8 blue = stream.getByte();
    OdUInt8 green = stream.getByte();
    OdUInt8 red = stream.getByte();
    return ((OdUInt32)alpha << 24)
      || ((OdUInt32)red << 16)
      || ((OdUInt32)green << 8)
      || (blue);
  }

  inline OdNwColor readDRGBColor(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readDRGBColor") && !(stream.tell() % 8));

    double clr[3];
    OdPlatformStreamer::rd3Doubles(stream, clr);
    return OdNwColor(clr[0], clr[1], clr[2]);
  }

  inline OdNwColor readDRGBAColor(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readDRGBAColor") && !(stream.tell() % 8));

    double clr[4];
    OdPlatformStreamer::rdDoubles(stream, 4, clr);
    return OdNwColor(clr[3], clr[0], clr[1], clr[2]);
  }

  inline OdNwColor readFRGBColor(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readFRGBColor") && !(stream.tell() % 4));

    float clr[3];
    readFloats(stream, 3, clr);
    return OdNwColor(clr[0], clr[1], clr[2]);
  }

  inline OdUInt32 readBRGBAColor(OdStreamBuf& stream)
  {
    OdUInt8 red = stream.getByte();
    OdUInt8 green = stream.getByte();
    OdUInt8 blue = stream.getByte();
    OdUInt8 alpha = stream.getByte();
    return ((OdUInt32)alpha << 24)
      || ((OdUInt32)red << 16)
      || ((OdUInt32)green << 8)
      || (blue);
  }

  template <OdNmStreamAlignment::Enum alignMode = OdNmStreamAlignment::FourBytes>
  inline OdString readString(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readString") && !(stream.tell() % 4));
    const OdUInt32 nAlignment = getAlignment(alignMode);

    OdInt32 len = OdPlatformStreamer::rdInt32(stream);
    if (len > 0)
    {
      OdInt32 align = len % nAlignment;
      if (align > 0)
        len += nAlignment - align;
      OdAnsiString sBuffer; // NB: UTF-8 string
      stream.getBytes(sBuffer.getBufferSetLength(len), len);

      OdCharArray buf;
      OdCharMapper::utf8ToUnicode(sBuffer.c_str(), sBuffer.getLength(), buf);
      return OdString(buf.getPtr(), buf.size() - 1);
    }
    return OdString();
  }

  inline tm readTime(OdStreamBuf& stream)
  {
    ODA_ASSERT(OD_T("readTime") && !(stream.tell() % 8));
    
    time_t rawtime = OdPlatformStreamer::rdInt64(stream);
    return *gmtime(&rawtime);
  }

  template <typename T>
  inline T readEnum(OdStreamBuf &stream)
  {
    ODA_ASSERT(OD_T("readEnum") && !(stream.tell() % 4));

    T result = static_cast<T> (OdPlatformStreamer::rdInt32(stream));

    return result;
  }

  inline NwFragmentType::Enum readFragmentType(OdStreamBuf& stream)
  {
    NwFragmentType::Enum result = readEnum<NwFragmentType::Enum>(stream);

    // Unsupported extra data format check
    ODA_ASSERT(!(result == NwFragmentType::FRAGMENT_INTERNAL_REFERENCE ||
      result == NwFragmentType::FRAGMENT_EXTERNAL_REFERENCE ||
      result == NwFragmentType::FRAGMENT_EMBEDDED_DATA));
    return result;
  }

  inline NwModelUnits::Enum readLinearUnits(OdStreamBuf& stream)
  {
    switch(readEnum<NwLinearUnits::Enum>(stream))
    {
      case NwLinearUnits::UNITS_METERS:
        return NwModelUnits::UNITS_METERS;
        break;
      case NwLinearUnits::UNITS_CENTIMETERS:
        return NwModelUnits::UNITS_CENTIMETERS;
        break;
      case NwLinearUnits::UNITS_MILLIMETERS:
        return NwModelUnits::UNITS_MILLIMETERS;
        break;
      case NwLinearUnits::UNITS_FEET:
        return NwModelUnits::UNITS_FEET;
        break;
      case NwLinearUnits::UNITS_INCHES:
        return NwModelUnits::UNITS_INCHES;
        break;
      case NwLinearUnits::UNITS_YARDS:
        return NwModelUnits::UNITS_YARDS;
        break;
      case NwLinearUnits::UNITS_KILOMETERS:
        return NwModelUnits::UNITS_KILOMETERS;
        break;
      case NwLinearUnits::UNITS_MILES:
        return NwModelUnits::UNITS_MILES;
        break;
      case NwLinearUnits::UNITS_MICROMETERS:
        return NwModelUnits::UNITS_MICROMETERS;
        break;
      case NwLinearUnits::UNITS_MILS:
        return NwModelUnits::UNITS_MILS;
        break;
      case NwLinearUnits::UNITS_MICROINCHES:
        return NwModelUnits::UNITS_MICROINCHES;
        break;
      default:
      {
        ODA_ASSERT(OD_T("Unknown linear units while reading."));
        break;
      }
    }

    return NwModelUnits::UNITS_METERS;
  }

  inline OdGUID readGuid(OdStreamBuf& stream)
  {
    OdGUID::DataType guidData;
    stream.getBytes(guidData, sizeof(guidData));
    return OdGUID(guidData);
  }

  template <OdNmStreamAlignment::Enum alignMode = OdNmStreamAlignment::FourBytes>
  inline OdBinaryData readBinary(OdStreamBuf& stream, OdUInt64 dataSize)
  {
    const OdUInt32 nAlignment = getAlignment(alignMode);

    OdBinaryData data;
    data.resize(dataSize);
    OdUInt8* ptr = data.asArrayPtr();
    stream.getBytes(ptr, dataSize);
    OdInt32 dataAlign = dataSize % nAlignment;
    if (dataAlign != 0)
      NwStreamCommon::shiftBytes(stream, nAlignment - dataAlign);
    return data;
  }
} // namespace NwStreamCommon

#include "TD_PackPop.h"

#endif // __NW_READSTREAMCOMMON_H__
