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

#ifndef _BFC_TIME_STAMP_H
#define _BFC_TIME_STAMP_H

#include "BcfCommon.h"

#include "OdTimeStamp.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  /** \details
  A class that provides functionality for working with DateTime data type values within the BCF format.
  */
  class BCF_EXPORT OdBcfTimeStamp : public OdRxObject
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfTimeStamp);
    //DOM-IGNORE-END

    /** \details
    Creates a new timestamp object for a specified datetime value.
    \param timeString [in] A string that contains a datetime value.
    \returns A smart pointer to the created <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> instance.
    */
    static OdSmartPtr<OdBcfTimeStamp> createObject(const OdString &timeString);

    /** \details
    Creates a new timestamp object for a specified 
    <exref target="https://docs.opendesign.com/tkernel/OdTimeStamp.html">OdTimeStamp</exref> value.
    \param localTimeStamp [in] An OdTimeStamp value.
    \returns A smart pointer to the created <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> instance.
    \remarks
    The method records provided value using the system native time zone.
    */
    static OdSmartPtr<OdBcfTimeStamp> createObject(const OdTimeStamp &localTimeStamp);

    /** \details
    Creates a new timestamp object with default parameters.
    */
    OdBcfTimeStamp();


    /** \details
    Converts the timestamp value to a datetime-style formatted string.
    \returns An OdString object that contains the timestamp value formatted in accordance with the datetime style.
    */
    OdString toString() const;

    /** \details
    Equality operator for BCF timestamp objects.
    \param val [in] Another BCF timestamp value to be compared with (right-hand operand).
    \returns true if the BCF timestamp object is equal to another BCF timestamp object; otherwise, the method returns false.
    */
    bool operator == (const OdBcfTimeStamp& val) const;

    /** \details
    Unequality operator for BCF timestamp objects.
    \param val [in] Another BCF timestamp value to be compared with (right-hand operand).
    \returns true if the BCF timestamp object is unequal to another BCF timestamp object; otherwise, the method returns false.
    */
    bool operator != (const OdBcfTimeStamp& val) const;

    /** \details
    Less than operator for BCF timestamp objects.
    \param val [in] Another BCF timestamp value to be compared with (right-hand operand).
    \returns true if the BCF timestamp object is less than another BCF timestamp object; otherwise, the method returns false.
    */
    bool operator < (const OdBcfTimeStamp& val) const;

    /** \details
    The conversion operator to an OdString for BCF timestamp objects.
    \returns An OdString object that contains the timestamp data formatted in accordance with datetime style.
    */
    operator OdString() const;

    //DOM-IGNORE-BEGIN
  protected:
    OdTimeStamp m_timeStamp;
    OdInt       m_timeZone;
    bool        m_isUTC;

    void init(const OdUInt16 year, const OdUInt8 month, const OdUInt8 day,
              const OdUInt8 hour, const OdUInt8 minute, const OdUInt8 second, const OdUInt16 msecond,
              const OdInt8 timeZoneSign, const OdUInt8 timeZoneHour, const OdUInt8 timeZoneMinute);

    OdTimeStamp toUTC() const;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfTimeStamp, OdBcfTimeStamp> object.
  */
  typedef OdSmartPtr<OdBcfTimeStamp> OdBcfTimeStampPtr;

} //namespace OdBcf

#endif // _BFC_TIME_STAMP_H
