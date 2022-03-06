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

#ifndef _DAI_FIXED_LENGTH_STRING_H_
#define _DAI_FIXED_LENGTH_STRING_H_

#include "OdaCommon.h"
#include "OdAnsiString.h"
#include "daiBuildOptions.h"
#include "daiConsts.h"

namespace OdDAI
{

  /** \details
  A class that implements generating and storing fiexed length string objects.
  */
  template<size_t fixedLength = 22>
  class DAI_EXPORT FixedLengthString
  {
  public:

    /** \details
    Creates a new fiexed length string object with default parameters.
    */
    FixedLengthString()
    {
      strncpy(m_val,
        OdDAI::Consts::OdStringUnset,
        odmin(fixedLength + 1, sizeof(OdDAI::Consts::OdStringUnset) / sizeof(OdDAI::Consts::OdStringUnset[0])));
      m_val[fixedLength] = '\0';
    };

    /** \details
    Assignment operator for fiexed length string objects.
    \param s [in] A new fiexed length string value to be assigned represented as an ANSI string.
    \returns A reference to the fiexed length string object modified with the assignment operation.
    */
    FixedLengthString& operator= (const OdAnsiString &s)
    {
      if (s == OdDAI::Consts::OdStringUnset)
      {
        strncpy(m_val,
          OdDAI::Consts::OdStringUnset,
          odmin(fixedLength + 1, sizeof(OdDAI::Consts::OdStringUnset) / sizeof(OdDAI::Consts::OdStringUnset[0])));
      }
      else
      {
        ODA_ASSERT_ONCE(s.getLength() == fixedLength);
        strncpy(m_val, s.c_str(), fixedLength);
      }
      m_val[fixedLength] = '\0';
      return *this;
    }

    /** \details
    Comparison operator for fiexed length string objects.
    \param other [in] Another fiexed length string value to be compared with (right-hand operand).
    \returns true if the fiexed length string object is equal to another fiexed length string object;
    otherwise, the method returns false.
    */
    bool operator== (const FixedLengthString &other) const
    {
      return strncmp(m_val, other.m_val, fixedLength) == 0;
    };

    /** \details
    Inequality operator for fiexed length string objects.
    \param other [in] Another fiexed length string value to be compared with (right-hand operand).
    \returns true if the fiexed length string object is not equal to another fiexed length string object;
    otherwise, the method returns false.
    */
    bool operator!= (const FixedLengthString &other) const
    {
      return !(this->operator == (other));
    };

    /** \details
    The &quot;less-than&quot; operator for fiexed length string objects.
    \param other [in] Another fiexed length string value to be compared with (right-hand operand).
    \returns
    Returns true if the fiexed length string value in string representation is not equal to another fiexed length string
    value in string representation and the code of the first different symbol in the fiexed length string string is less
    than the code of the symbol in the same position in the other fiexed length string string;
    otherwise, the method returns false.
    */
    bool operator< (const FixedLengthString &other) const
    {
      return strncmp(m_val, other.m_val, fixedLength) < 0;
    };

    /** \details
    Converts the fiexed length string object's value to a constant C++ character array.
    \returns A raw pointer to the C++ character array that contains the string with the IfcGUID value.
    */
    operator const char* () const { return m_val; };

    /** \details
    Converts the fiexed length string object's value to a C++ character array.
    \returns A raw pointer to the C++ character array.
    */
    operator char* () { return m_val; };

    /** \details
    Retrieves the constant raw pointer to the underlying string.
    \returns A raw pointer to the C++ character array.
    */
    const char * c_str() const { return m_val; };

    //DOM-IGNORE-BEGIN
  private:
    char m_val[fixedLength + 1];
    //DOM-IGNORE-END
  };

}

#endif // _DAI_FIXED_LENGTH_STRING_H_
