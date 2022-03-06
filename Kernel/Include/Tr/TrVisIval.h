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
// Interval definition

#ifndef ODTRVISIVAL
#define ODTRVISIVAL

#include "TD_PackPush.h"

/** \details
  Library: Source code provided.
  <group ExRender_Windows_Classes>
*/
template <typename DataType>
struct OdTrVisIvalImpl
{
  // Min/max interval bounds.
  DataType m_minBound, m_maxBound;

  // Set from actual values.
  OdTrVisIvalImpl &set(DataType minBound, DataType maxBound)
  {
    m_minBound = minBound;
    m_maxBound = maxBound;
    return *this;
  }
  // Set from linear array.
  OdTrVisIvalImpl &set(const DataType *pBounds)
  {
    m_minBound = pBounds[0];
    m_maxBound = pBounds[1];
    return *this;
  }
  // Set to identity.
  OdTrVisIvalImpl &setIdentity()
  {
    m_minBound = m_maxBound = 0.0f;
    return *this;
  }

  // Adapt from another DataType.
  template <typename AltClass>
  OdTrVisIvalImpl &adapt(const AltClass &altSet)
  {
    m_minBound = (DataType)altSet.m_minBound;
    m_maxBound = (DataType)altSet.m_maxBound;
    return *this;
  }

  // Linear getters.
  const DataType *getArray() const { return &m_minBound; }
  DataType *getArray() { return &m_minBound; }
  // Accessors.
  DataType minBound() const { return m_minBound; }
  OdTrVisIvalImpl &setMinBound(DataType minBound) { m_minBound = minBound; return *this; }
  DataType maxBound() const { return m_maxBound; }
  OdTrVisIvalImpl &setMaxBound(DataType maxBound) { m_maxBound = maxBound; return *this; }

  // Validate interval.
  OdTrVisIvalImpl &validate()
  {
    if (m_minBound > m_maxBound)
    {
      DataType tmpReg = m_minBound;
      m_minBound = m_maxBound;
      m_maxBound = tmpReg;
    }
    return *this;
  }

  bool isValid() const { return m_maxBound >= m_minBound; }

  // Check identity.
  bool isIdentity() const
  {
    return (m_maxBound == 0.0) && (m_minBound == m_maxBound);
  }

  // Interval length.
  DataType length() const
  {
    return m_maxBound - m_minBound;
  }

  // Intervals comparision.
  bool operator ==(const OdTrVisIvalImpl &ival) const
  {
    return (m_minBound == ival.m_minBound) && (m_maxBound == ival.m_maxBound);
  }
  bool operator !=(const OdTrVisIvalImpl &ival) const
  {
    return (m_minBound != ival.m_minBound) || (m_maxBound != ival.m_maxBound);
  }

  // Intervals intersection.
  OdTrVisIvalImpl operator &(const OdTrVisIvalImpl &ival) const
  {
    return OdTrVisIvalImpl(odmax(m_minBound, ival.m_minBound), odmin(m_maxBound, ival.m_maxBound));
  }
  OdTrVisIvalImpl &operator *=(const OdTrVisIvalImpl &ival)
  {
    return set(odmax(m_minBound, ival.m_minBound), odmin(m_maxBound, ival.m_maxBound));
  }

  // Intervals unionizing.
  OdTrVisIvalImpl operator |(const OdTrVisIvalImpl &ival) const
  {
    return OdTrVisIvalImpl(odmin(m_minBound, ival.m_minBound), odmax(m_maxBound, ival.m_maxBound));
  }
  OdTrVisIvalImpl &operator |=(const OdTrVisIvalImpl &ival)
  {
    return set(odmin(m_minBound, ival.m_minBound), odmax(m_maxBound, ival.m_maxBound));
  }

  void extend(DataType percents)
  {
    const DataType incVal = length() * 0.5f * percents;
    m_minBound -= incVal; m_maxBound += incVal;
  }

  // Transformation to fit bounds interval in current interval.
  OdTrVisIvalImpl fitTransform(const OdTrVisIvalImpl &bounds) const
  { // Current interval is physical range for values mapping. "bounds" argument provides big interval of exist values space.
    // For example, if we need to map "bounds" interval in { 0, 17 } range into physical interval in { 4, 5 } range for example.
    const DataType bounds_length = bounds.length();
    if (bounds_length > 0.0)
    {
      const DataType xform_scale = length() / bounds_length;
      return OdTrVisIvalImpl().set(xform_scale, m_minBound - bounds.m_minBound * xform_scale);
    }
    return OdTrVisIvalImpl().set(0.0, m_minBound);
  }
  // Xform point by interval.
  DataType xform(DataType value) const
  {
    return value * m_minBound + m_maxBound;
  }
  // Xform bounds by interval.
  OdTrVisIvalImpl xform(const OdTrVisIvalImpl &bounds) const
  {
    return OdTrVisIvalImpl().set(xform(bounds.m_minBound), xform(bounds.m_maxBound));
  }

  // Fit segments in bounds.
  OdTrVisIvalImpl fit(const OdTrVisIvalImpl &bounds, const OdTrVisIvalImpl &segment) const
  { // Current interval is xform. Return transform for nested bounds segment.
    const OdTrVisIvalImpl fitSegment = xform(segment);
    return fitSegment.fitTransform(bounds);
  }
};

// Type definitions.

typedef OdTrVisIvalImpl<float> OdTrVisIvalf;
typedef OdTrVisIvalImpl<double> OdTrVisIvald;

#include "TD_PackPop.h"

#endif // ODTRVISIVAL
