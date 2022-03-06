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


#ifndef _OD_BIGINTEGER_INCLUDED_
#define _OD_BIGINTEGER_INCLUDED_

#include <new>

#define BIGINTEGER_DEF_SIZE 80

class OdBigInteger
{
  OdBigInteger(const OdBigInteger& src);
public:
  OdBigInteger()
    : _sign(0)
    , _size(0)
    , _maxSize(BIGINTEGER_DEF_SIZE)
    , _pints(_ints)
  {
    _pints[0] = 0;
  }

  ~OdBigInteger()
  {
    if (_pints != _ints)
    {
      ::odrxFree(_pints);
      _pints = _ints;
    }
  }

  OdBigInteger& operator = (const OdBigInteger& src)
  {
    copyFrom(src);
    return *this;
  }

  void copyFrom(const OdBigInteger& src)
  {
    reallocBuff(src.size());
    _sign = src.sign();
    _size = src.size();
    ::memcpy(_pints, src.ints(), _size * sizeof(OdUInt32));
  }

  void clear()
  {
    _sign = 0;
    _size = 0;
    _pints[0] = 0;
  }

  unsigned size() const
  {
    return _size;
  }

  void resize(unsigned newSize)
  {
    if (newSize > _size)
    {
      reallocBuff(newSize);
      ::memset(_pints + _size, 0, ((newSize - _size) * sizeof(OdUInt32)));
    }
    _size = newSize;
  }

  void append(OdUInt32 val)
  {
    reallocBuff(_size + 1);
    _pints[_size] = val;
    ++_size;
  }

  OdUInt32* ints()
  {
    return _pints;
  }

  const OdUInt32* ints() const
  {
    return _pints;
  }

  int sign() const
  {
    return _sign;
  }

  void setSign(int sign)
  {
    _sign = sign;
  }

  bool usesAutoBuffer()
  {
    return _pints == _ints;
  }
private:
  void reallocBuff(unsigned newSize)
  {
    if (newSize > _maxSize)
    {
      int newMaxSize = odmax(newSize, _maxSize+BIGINTEGER_DEF_SIZE);
      if (_pints != _ints)
      {
        _pints = (OdUInt32*)::odrxRealloc(_pints, newMaxSize * sizeof(OdUInt32), _maxSize * sizeof(OdUInt32));
        if (!_pints)
          throw std::bad_alloc();
      }
      else
      {
        OdUInt32* pints = (OdUInt32*)::odrxAlloc(newMaxSize * sizeof(OdUInt32));
        if (!pints)
          throw std::bad_alloc();
        ::memcpy(pints, _pints, _size * sizeof(OdUInt32));
        _pints = pints;
      }
      _maxSize = newMaxSize;
    }
  }

  int       _sign;
  unsigned  _size;
  unsigned  _maxSize;
  OdUInt32  _ints[BIGINTEGER_DEF_SIZE];
  OdUInt32* _pints;
};

#endif
