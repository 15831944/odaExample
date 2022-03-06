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

#ifndef _WRITE_UTILS_H_
#define _WRITE_UTILS_H_

#include "OdaCommon.h"
#include "DebugStuff.h"

#include "OdStreamBuf.h"
#include "OdPlatformSettings.h"
#include "daiBuildOptions.h"
#include "daiSettings.h"
#include "StringArray.h"

#define STL_USING_VECTOR
#define STL_USING_STRING
#include "OdaSTL.h"

class OdDbHandle;

namespace OdDAI
{
  namespace WrUtils
  {
    const OdUInt32 writeErorCode = static_cast<OdUInt32>(-1);

    OdUInt32 writeValue(const OdDbHandle& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 writeValue(const int valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 writeValue(const long int valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 writeValue(const OdUInt64& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 writeValue(const double& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 writeValue(const std::string& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 writeValue(const OdAnsiString& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 writeValue(const OdString& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 writeValue(const char& valueToWrite, std::vector<OdUInt8>& writeBuffer);

    OdUInt32 appendValue(const OdDbHandle& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 appendValue(int valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 appendValue(const OdUInt64& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 appendValue(const double& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 appendValue(const std::string& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 appendValue(const OdString& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 appendValue(const OdAnsiString& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    OdUInt32 appendValue(const char& valueToWrite, std::vector<OdUInt8>& writeBuffer);
    void appendValue(const char* bufferToWrite, OdUInt32 sizeBuffer, std::vector<OdUInt8>& writeBuffer);

    template<class ValueType, class BufferType>
    inline OdUInt32 writeValue(const ValueType& valueToWrite, BufferType& writeBuffer, const OdUInt64& writeBufferSize, const char* printfTemplate)
    {
#if defined(_MSC_VER) && _MSC_VER < 1900
	    return _snprintf(reinterpret_cast<char* const>(&writeBuffer[0]), writeBufferSize, printfTemplate, valueToWrite); 
#else
      return snprintf(reinterpret_cast<char* const>(&writeBuffer[0]), writeBufferSize, printfTemplate, valueToWrite); 
#endif
    }

    template<class BufferType>
    inline OdUInt32 writeValue(const double& valueToWrite, BufferType& writeBuffer, const OdUInt64& writeBufferSize, const char* printfTemplate)
    {
      char *buf = reinterpret_cast<char*>(&writeBuffer[0]);

#if defined(_MSC_VER) && _MSC_VER < 1900
      OdUInt32 writtenSize = _snprintf(buf, writeBufferSize, printfTemplate, valueToWrite);
#else
      OdUInt32 writtenSize = snprintf(buf, writeBufferSize, printfTemplate, valueToWrite);
#endif

      // Terminating null character automatically appended by snprintf
      char* posDot = strchr(buf, '.');
      if (posDot == nullptr)
      {
        char *posE = strchr(buf, 'E');
        if (posE == nullptr)
        {
          buf[writtenSize++] = '.';
          buf[writtenSize] = 0;
        }
        else
        {
          Od_memmove_s(posE + 1, posE, strlen(posE));
          buf[++writtenSize] = 0;
          *posE = '.';
        }
      }
      else if (OdDAI::settings().get_digitsNumber() > 0)
      {
        while (buf[writtenSize-1] == '0')
        {
          --writtenSize;
        }
      }

      return writtenSize;
    }

    template<class ValueType, OdUInt64 writeBufferSize>
    inline OdUInt32 appendValue(const ValueType& valueToWrite, std::vector<OdUInt8>& writeBuffer, const char* printfTemplate)
    {
      OdUInt8* appendBuffer[writeBufferSize + 1] = { 0 };
      OdUInt32 countWrite = writeValue(valueToWrite, appendBuffer, writeBufferSize + 1, printfTemplate);
      
      if (countWrite == writeErorCode)
      {
        return writeErorCode;
      }

      OdUInt64  insertionIndex = writeBuffer.size();
      writeBuffer.resize(insertionIndex + countWrite);

      Od_memcpy_s(&writeBuffer[insertionIndex], writeBuffer.size(), &appendBuffer[0], countWrite);
      return countWrite;
    }

    template<class ValueType, OdUInt64 writeBufferSize>
    inline OdUInt32 writeValue(const ValueType& valueToWrite, std::vector<OdUInt8>& writeBuffer, const char* printfTemplate)
    {
      return appendValue<ValueType, writeBufferSize>(valueToWrite, writeBuffer, printfTemplate);
    }

    template<class ValueType, OdUInt64 writeBufferSize>
    inline OdUInt32 writeValue(const ValueType& valueToWrite, OdUInt8* writeBuffer, const char* printfTemplate)
    {
      return writeValue(valueToWrite, writeBuffer, writeBufferSize, printfTemplate);
    }
  }
} 

#endif 

