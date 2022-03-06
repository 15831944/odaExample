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
#ifndef __NW_WRITESTREAMCOMMON_H__
#define __NW_WRITESTREAMCOMMON_H__

#include "OdPlatformStreamer.h"
#include "NwModelUnits.h"
#include "NwColor.h"
#include "NwLinearUnits.h"
#include <time.h>
#include "OdBinaryData.h"
#include "OdGUID.h"
#include "NwStreamAlignment.h"

#include "TD_PackPush.h"

#ifndef NW_STARTSTREAM
#define NW_STARTSTREAM 0x00000064 
#endif

// Write
namespace NwStreamCommon
{
  inline void wrAlignPointer(OdStreamBuf& streamBuf, OdNmStreamAlignment::Enum alignMode)
  {
    const OdUInt32 posAlignment = getAlignment(alignMode);
    const OdUInt32 posAlign = streamBuf.tell() % posAlignment;
    if (posAlign)
    {
      auto stepSize = posAlignment - posAlign;
      for (OdUInt32 nZero = 0; nZero < stepSize; ++nZero)
        streamBuf.putByte(0);
    }
  }

  inline void writeUInt16(OdStreamBuf& stream, OdUInt16 val)
  {
    odSwap2BytesNumber(val);
    stream.putBytes(&val, sizeof(val));
  }
  inline void writeUInt32(OdStreamBuf& stream, OdUInt32 val)
  {
    ODA_ASSERT(OD_T("writeUInt32") && !(stream.tell() % 4));

    odSwap4BytesNumber(val);
    stream.putBytes(&val, sizeof(val));
  }

  inline void writeUInt64(OdStreamBuf& stream, OdUInt64 val)
  {
    ODA_ASSERT(OD_T("writeUInt64") && !(stream.tell() % 8));

    odSwap8Bytes(val);
    stream.putBytes(&val, sizeof(val));
  }

  inline void writeInt16(OdStreamBuf& stream, OdInt16 val)
  {
    OdPlatformStreamer::wrInt16(stream, val);
  }

  inline void writeInt32(OdStreamBuf& stream, OdInt32 val)
  {
    ODA_ASSERT(OD_T("writeInt32") && !(stream.tell() % 4));

    OdPlatformStreamer::wrInt32(stream, val);
  }

  inline void writeInt64(OdStreamBuf& stream, OdInt64 val)
  {
    ODA_ASSERT(OD_T("writeInt64") && !(stream.tell() % 8));

    OdPlatformStreamer::wrInt64(stream, val);
  }
  
  inline void writeFloat(OdStreamBuf& stream, float val)
  {
    ODA_ASSERT(OD_T("writeFloat") && !(stream.tell() % 4));

    OdPlatformStreamer::wrFloat(stream, val);
  }

  inline void writeDouble(OdStreamBuf& stream, double val)
  {
    ODA_ASSERT(OD_T("writeDouble") && !(stream.tell() % 8));

    OdPlatformStreamer::wrDouble(stream, val);
  }

  inline void writeDRGBColor(OdStreamBuf& stream, const OdNwColor& color)
  {
    ODA_ASSERT(OD_T("writeDRGBColor") && !(stream.tell() % 8));

    OdPlatformStreamer::wrDouble(stream, color.R());
    OdPlatformStreamer::wrDouble(stream, color.G());
    OdPlatformStreamer::wrDouble(stream, color.B());
  }
  
  inline void writeFRGBColor(OdStreamBuf& stream, const OdNwColor& color)
  {
    ODA_ASSERT(OD_T("writeFRGBColor") && !(stream.tell() % 4));

    OdPlatformStreamer::wrFloat(stream, color.R());
    OdPlatformStreamer::wrFloat(stream, color.G());
    OdPlatformStreamer::wrFloat(stream, color.B());
  }

  template <typename T>
  inline void writeEnum(OdStreamBuf &stream, T type)
  {
    writeUInt32(stream, static_cast<OdUInt32> (type));
  }

  inline void writeLinearUnits(OdStreamBuf& stream, NwModelUnits::Enum units)
  {
    switch(units)
    {
      case NwLinearUnits::UNITS_METERS:
        writeEnum(stream, NwLinearUnits::UNITS_METERS);
        break;
      case NwModelUnits::UNITS_CENTIMETERS:
        writeEnum(stream, NwLinearUnits::UNITS_CENTIMETERS);
        break;
      case NwModelUnits::UNITS_MILLIMETERS:
        writeEnum(stream, NwLinearUnits::UNITS_MILLIMETERS);
        break;
      case NwModelUnits::UNITS_FEET:
        writeEnum(stream, NwLinearUnits::UNITS_FEET);
        break;
      case NwModelUnits::UNITS_INCHES:
        writeEnum(stream, NwLinearUnits::UNITS_INCHES);
        break;
      case NwModelUnits::UNITS_YARDS:
        writeEnum(stream, NwLinearUnits::UNITS_YARDS);
        break;
      case NwModelUnits::UNITS_KILOMETERS:
        writeEnum(stream, NwLinearUnits::UNITS_KILOMETERS);
        break;
      case NwModelUnits::UNITS_MILES:
        writeEnum(stream, NwLinearUnits::UNITS_MILES);
        break;
      case NwModelUnits::UNITS_MICROMETERS:
        writeEnum(stream, NwLinearUnits::UNITS_MICROMETERS);
        break;
      case NwModelUnits::UNITS_MILS:
        writeEnum(stream, NwLinearUnits::UNITS_MILS);
        break;
      case NwModelUnits::UNITS_MICROINCHES:
        writeEnum(stream, NwLinearUnits::UNITS_MICROINCHES);
        break;
      default:
      {
        ODA_ASSERT(OD_T("Unknown linear units while writing."));
        break;
      }
    }
  }

  inline void writeTime(OdStreamBuf& stream, const tm& time)
  {
    ODA_ASSERT(OD_T("writeTime") && !(stream.tell() % 8));
    
#ifdef _WIN32
    time_t raw_time = _mkgmtime(const_cast<tm*>(&time));
#else
    time_t raw_time = timegm(const_cast<tm*>(&time));
#endif
    NwStreamCommon::writeInt64(stream, raw_time);
  }

  inline void writeGuid(OdStreamBuf& stream, const OdGUID& guid)
  {
    const OdGUID::DataType& guidData = guid.data();
    stream.putBytes(guidData, sizeof(guidData));
  }

  inline void writeStreamBitfield(OdStreamBuf& streamBuf, const OdInt32 bitfield)
  {
    writeInt32(streamBuf, bitfield);
  }

  inline void writeBool(OdStreamBuf& streamBuf, const bool val)
  {
    writeStreamBitfield(streamBuf, val ? 1 : 0);
  }
  
  template <OdNmStreamAlignment::Enum alignMode = OdNmStreamAlignment::FourBytes>
  void writeString(OdStreamBuf& streamBuf, const OdString& val)
  {
    OdAnsiString aval(val, CP_UTF_8);
    const OdUInt32 nStrLen = aval.getLength();
    if (0 == nStrLen)
      NwStreamCommon::writeInt32(streamBuf, -1);
    else
    {
      const auto nAlignment = getAlignment(alignMode);

      NwStreamCommon::writeUInt32(streamBuf, nStrLen);
      // convert to utf-8
      streamBuf.putBytes(aval.c_str(), aval.getLength());
      if (nAlignment > 0 && (streamBuf.length() % nAlignment))
      {
        const OdUInt32 nZerosToWrite = nAlignment - streamBuf.length() % nAlignment;
        for (OdUInt32 nZero = 0; nZero < nZerosToWrite; ++nZero)
          streamBuf.putByte(0);
      }
    }
  }

  template <OdNmStreamAlignment::Enum alignMode = OdNmStreamAlignment::FourBytes>
  inline void writeBinary(OdStreamBuf& streamBuf, const OdBinaryData& val)
  {
    const OdUInt8* ptr = val.asArrayPtr();
    if (!ptr)
      NwStreamCommon::writeUInt32(streamBuf, 0);
    else
    {
      const auto nAlignment = getAlignment(alignMode);
      streamBuf.putBytes(ptr, val.size());
      OdInt32 dataAlign = val.size() % nAlignment;
      if (dataAlign != 0)
      {
        auto tempCount = nAlignment - dataAlign;
        while (tempCount--)
          streamBuf.putByte(0);
      }
    }
  }
}// namespace NwStreamCommon

#include "TD_PackPop.h"

#endif // __NW_WRITESTREAMCOMMON_H__
