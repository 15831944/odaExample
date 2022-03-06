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


#ifndef _OD_GDTOA_H_
#define _OD_GDTOA_H_

#include "OdPlatformSettings.h"
#include "OdaDefs.h"
#include "OdAlloc.h"
#include <new>

class OdGdtoaBuffer
{
  char _buffer[80];
  char* _dynBuffer;
public:
  OdGdtoaBuffer()
    : _dynBuffer(0)
  {
    //::memset(_buffer, 0, sizeof(_buffer));
  }

  ~OdGdtoaBuffer()
  {
    if (_dynBuffer)
      odrxFree(_dynBuffer);
  }

  char* alloc(int i)
  {
    if (i < 80)
      return _buffer;
    i++;
    i += 8 - (i&7);
    _dynBuffer = (char*)::odrxAlloc(i * sizeof(char));
    if (!_dynBuffer)
      throw std::bad_alloc();
    return _dynBuffer;
  }

  char* data()
  {
    if (_dynBuffer)
      return _dynBuffer;
    return _buffer;
  }
};


namespace OdGdImpl
{
  extern void dtoa(OdGdtoaBuffer& result, double d0, int mode, int ndigits, int* decpt, int* sign, char** rve);
}

#endif // _OD_GDTOA_H_
