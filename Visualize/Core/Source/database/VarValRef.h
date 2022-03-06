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

#ifndef _ODVARVALREF_H_
#define _ODVARVALREF_H_

#include "DbFiler.h"
#include "OdRound.h"
#include <limits.h>

class OdVarValRef
{
  const OdTvResBuf*     m_pRb;
  const OdTvDbDatabase* m_pDb;
public:
  inline OdVarValRef(const OdTvResBuf*  pRb, const OdTvDbDatabase* pDb)
    : m_pRb(pRb), m_pDb(pDb) {}
  inline operator bool() const
  {
    return m_pRb->getBool();
  }
  inline operator OdUInt8() const
  {
    return m_pRb->getInt8();
  }
  inline operator OdUInt16() const
  {
    return m_pRb->getInt16();
  }
  inline operator OdUInt32() const
  {
    return m_pRb->getInt32();
  }
  inline operator OdUInt64() const
  {
    return m_pRb->getInt64();
  }
  inline operator OdDbHandle() const
  {
    return m_pRb->getHandle();
  }
  inline operator OdInt8() const
  {
    return m_pRb->getInt8();
  }
  inline operator OdInt16() const
  {
    return m_pRb->getInt16();
  }
  inline operator OdInt32() const
  {
    return m_pRb->getInt32();
  }
  inline operator OdInt64() const
  {
    return m_pRb->getInt64();
  }
#if !((defined(__GNUC__) || defined(__hpux) || defined(sparc)) && defined(_LP64)) && !(defined(sgi) && (_MIPS_SZLONG == 64)) && !(defined(_AIX) && defined(__64BIT__))
  inline operator const int() const
  {
    return m_pRb->getInt32();
  }
#endif
  inline operator double() const
  {
    return m_pRb->getDouble();
  }
  inline operator OdString() const
  {
    return m_pRb->getString();
  }
  inline operator OdTvDbHardPointerId() const
  {
    return m_pRb->getObjectId(m_pDb);
  }
  inline operator OdGePoint3d() const
  {
    return m_pRb->getPoint3d();
  }
  inline operator OdGeVector3d() const
  {
    return m_pRb->getPoint3d().asVector();
  }
  inline operator OdGePoint2d() const
  {
    OdGePoint2d res = (const OdGePoint2d&)m_pRb->getPoint3d();
    return res;
  }
  inline operator OdTvDbDate() const
  {
    OdTvDbDate res;
    res.setJulianFraction(m_pRb->getDouble());
    return res;
  }
  inline operator OdDb::MeasurementValue() const
  {
    return OdDb::MeasurementValue(m_pRb->getInt16());
  }
  inline operator OdDb::EndCaps() const
  {
    return OdDb::EndCaps(m_pRb->getInt16());
  }
  inline operator OdDb::UnitsValue() const
  {
    return OdDb::UnitsValue(m_pRb->getInt16());
  }
  inline operator OdDb::PlotStyleNameType() const
  {
    return OdDb::PlotStyleNameType(m_pRb->getInt16());
  }
  inline operator OdDb::JoinStyle() const
  {
    return OdDb::JoinStyle(m_pRb->getInt16());
  }
  inline operator OdCodePageId() const
  {
    return OdCodePageId(m_pRb->getInt16());
  }
  inline operator OdDb::LineWeight() const
  {
    return OdDb::LineWeight(m_pRb->getInt16());
  }
  inline operator OdGiSubEntityTraits::ShadowFlags() const
  {
    return OdGiSubEntityTraits::ShadowFlags(m_pRb->getInt16());
  }
  inline operator OdDb::ProxyImage() const
  {
    return OdDb::ProxyImage(m_pRb->getInt16());
  }
  inline operator OdTvCmColor() const
  {
    if(m_pRb->restype()==OdTvResBuf::kRtColor)
      return m_pRb->getColor();
    if (OdTvDxfCode::_getType(m_pRb->restype()) == OdTvDxfCode::Integer16)
    {
      OdInt16 index = m_pRb->getInt16();
      if (index < 0 || index > OdTvCmColor::MaxColorIndex)
      {
        index = OdCmEntityColor::kACIbyBlock;
      }
      OdTvCmColor col;
      col.setColorIndex(index);
      return col;
    }
    throw OdError(eInvalidResBuf);
  }
  inline operator OdTvCmTransparency() const
  {
    if (m_pRb->restype() != OdTvResBuf::kRtString)
      throw OdError(eInvalidResBuf);
    OdString sVal = m_pRb->getString().trimLeft().trimRight().makeUpper();
    OdTvCmTransparency val;
    if (sVal == L"BYLAYER")
      val.setMethod(OdTvCmTransparency::kByLayer);
    else if (sVal == L"BYBLOCK")
      val.setMethod(OdTvCmTransparency::kByBlock);
    else if (sVal == L".")
      val.setMethod(OdTvCmTransparency::kErrorValue);
    else
    {
      if (sVal.isEmpty())
        throw OdError(eInvalidInput);
      for (const OdChar* pCh = sVal.c_str(); *pCh; pCh++)
        if (*pCh < L'0' || *pCh > L'9')
          throw OdError(eOutOfRange);
      OdUInt32 percent = odStrToInt(sVal);
      if (percent > 90)
        throw OdError(eOutOfRange);
      val.setAlphaPercent((100 - percent) / 100.0);
      ODA_ASSERT_ONCE(percent == (OdUInt32)(100 - OdRoundToLong(val.alphaPercent() * 100.0)));
    }
    return val;
  }
  inline operator OdDb::TimeZone() const
  {
    return OdDb::TimeZone(m_pRb->getInt16());
  }
  inline operator OdDb::LoftParamType() const
  {
    return OdDb::LoftParamType(m_pRb->getInt8());
  }
  inline operator OdDb::LoftNormalsType() const
  {
    return OdDb::LoftNormalsType(m_pRb->getInt16());
  }

};


#endif //#ifndef _ODVARVALREF_H_
