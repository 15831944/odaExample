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

#ifndef _DAI_PRIMITIVE_H_
#define _DAI_PRIMITIVE_H_

#include "OdAnsiString.h"

#include "daiConsts.h"
#include "daiUtils/daiUnset.h"
#include "daiFixedLengthString.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class DAI_EXPORT Logical;

  /** \details
  Defines values for the <link OdDAI::Boolean, Boolean> data type.
  */
  enum Boolean_ {
    /**False value.*/
    kBoolean_F, 
    /**True value.*/
    kBoolean_T,
    /**The value is undefined (unset).*/
    kBoolean_unset
  };

  /** \details
  A class that represents the SDAI primitive Boolean data type.
  */
  class DAI_EXPORT Boolean {
    Boolean_ m_val;
  public:

    /**A constant that implements the False value for the <link OdDAI::Boolean, Boolean> data type.*/
    DAI_EXPORT_STATIC static const Boolean False;
    /**A constant that implements the True value for the <link OdDAI::Boolean, Boolean> data type.*/
    DAI_EXPORT_STATIC static const Boolean True;
    /**A constant that implements the undefined (unset) value for the <link OdDAI::Boolean, Boolean> data type.*/
    DAI_EXPORT_STATIC static const Boolean Unset;

    /** \details 
    Creates a new Boolean object with an undefined (unset) value.
    */
    Boolean() : m_val(kBoolean_unset) {};
    
    /** \details 
    Creates a new Boolean object as a copy of another existing Boolean value 
    (copy constructor for the <link OdDAI::Boolean, Boolean> class).
    \param other [in] Another instance of the <link OdDAI::Boolean, Boolean> class that will be copied.
    */
    Boolean(const Boolean &other) : m_val(other.m_val) {};


    /** \details 
    Creates a new Boolean object with a specified value.
    \param val [in] An initial value of the created Boolean object.
    */
    Boolean(Boolean_ val) : m_val(val) {};

    /** \details 
    Creates a new Boolean object with a specified value contained in a <link OdDAI::Logical, Logical> object.
    \param logical [in] A <link OdDAI::Logical, Logical> object that contains the initial value for the created Boolean object.
    */
    Boolean(const Logical &logical);
    
    /** \details 
    Checks whether the Boolean object has a defined value (whether the value is set).
    \returns 1 if the Boolean object's value is defined (set); otherwise, the method returns 0.
    \sa
    <link OdDAI::Boolean::nullify, nullify()> method.
    */
    int exists() const { return m_val != kBoolean_unset ? 1 : 0; };
    
    /** \details 
    Flashes the Boolean object to the undefined (unset) value.
    After calling this method the <link OdDAI::Boolean::exists@const, exists()> method returns 0.
    \sa
    <link OdDAI::Boolean::exists@const, exists()> method.
    */    
    void nullify() { m_val = kBoolean_unset; };
    
    /** \details 
    Casts the Boolean object's value to the signed int data type.
    */
    operator int() const { return m_val; };
    /*operator Logical() const {
      if (m_val == kBoolean_F)
        return Logical::False;
      if (m_val == kBoolean_T)
        return Logical::True;
      return Logical::Unset;
    };*/
    
    /** \details 
    Assignment operator for the Boolean data type.
    The operator casts specified value of the <link OdDAI::Boolean_, appropriate enumeration> to the Logical value and assigns it to the object.
    \param val [in] An <link OdDAI::Boolean_, enumeration> value to be assigned (a right-hand operand of the assignment operation).
    \returns The reference to the Boolean object modified by the assignment operation.
    */
    Boolean& operator = (const Boolean_ val) { m_val = val; return *this; };
    
    /** \details 
    Assignment operator for the Boolean data type. 
    The operator casts specified signed long value to the Boolean value and assigns it to the object.
    \param val [in] A signed long data type value to be assigned (a right-hand operand of the assignment operation).
    \returns The reference to the Boolean object modified by the assignment operation.
    */
    Boolean& operator = (const long val) { m_val = (Boolean_)val; return *this; };

    /** \details 
    Assignment operator for the Boolean data type. 
    The operator casts specified <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">ANSI string</exref> 
    to the Boolean value and assigns it to the object.
    \param val [in] An <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">ANSI string</exref> to be assigned (a right-hand operand of the assignment operation).
    \returns The reference to the Boolean object modified by the assignment operation.
    \remarks 
    The specified <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">ANSI string</exref> should be: 
    * &quot;F&quot; to set the Boolean object to the False value.
    * &quot;T&quot; to set the Boolean object to the True value.
    In all other cases, the operator makes the Boolean object undefined (its value is unset).
    */
    Boolean& operator = (const OdAnsiString &val) {
      if (val == "F")
        m_val = kBoolean_F;
      else
        if (val == "T")
          m_val = kBoolean_T;
        else
          m_val = kBoolean_unset;
      return *this;
    };

    Boolean operator || (const Boolean &other)
    {
      if (m_val == True || other.m_val == True)
        return OdDAI::Boolean::True;
      return OdDAI::Boolean::False;
    }

    Boolean operator && (const Boolean &other)
    {
      if (m_val == True && other.m_val == True)
        return OdDAI::Boolean::True;
      return OdDAI::Boolean::False;
    }

    /** \details 
    Converts the Boolean object value into an <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">ANSI string</exref>.
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">ANSI string</exref> that matches the Boolean object value.
    */
    const OdAnsiString& toStr() {
      switch (m_val)
      {
      case kBoolean_F:
        return OdDAI::Consts::StringF;
      case kBoolean_T:
        return OdDAI::Consts::StringT;
      default:
        break;
      }
      return OdDAI::Consts::AnsiStringUnset;
    };

  };

  /** \details
  Defines values for the <link OdDAI::Logical, Logical> data type.
  */
  enum Logical_ {
    /**False value.*/
    kLogical_F, 
    /**True value.*/
    kLogical_T, 
    /**The value is unknown.*/
    kLogical_U, 
    /**The value is undefined (unset).*/
    kLogical_unset
  };

  /** \details
  A class that represents the SDAI primitive Boolean data type.
  */
  class DAI_EXPORT Logical {
    Logical_ m_val;
  public:

    /**A constant that implements the False value for the <link OdDAI::Logical, Logical> data type.*/
    DAI_EXPORT_STATIC static const Logical False;
    /**A constant that implements the True value for the <link OdDAI::Logical, Logical> data type.*/
    DAI_EXPORT_STATIC static const Logical True;
    /**A constant that implements the value Unknown for the <link OdDAI::Logical, Logical> data type.*/
    DAI_EXPORT_STATIC static const Logical Unknown;
    /**A constant that implements the undefined (unset) value for the <link OdDAI::Logical, Logical> data type.*/
    DAI_EXPORT_STATIC static const Logical Unset;

    /** \details 
    Creates a new Logical object with an undefined (unset) value.
    */
    Logical() : m_val(kLogical_unset) {};

    /** \details 
    Creates a new Logical object with a specified value.
    \param val [in] An initial value of the created Logical object.
    */
    Logical(Logical_ val) : m_val(val) {};

    /** \details 
    Creates a new Logical object as a copy of another existing Logical value 
    (copy constructor for the <link OdDAI::Logical, Logical> class).
    \param other [in] Another instance of the <link OdDAI::Logical, Logical> class that will be copied.
    */
    Logical(const Logical &other) : m_val(other.m_val) {};

    /** \details 
    Creates a new Logical object with a specified signed int value. 
    \param i [in] A signed int value to be cast into a value of the created Logical object.
    */
    Logical(int i) : m_val(i == 0 ? kLogical_F : kLogical_T) {};

    /** \details 
    Creates a new Logical object with a specified value contained in a <link OdDAI::Boolean, Boolean> object.
    \param boo [in] A <link OdDAI::Boolean, Boolean> object that contains the initial value for the created Logical object.
    */    
    Logical(const Boolean &boo)
    {
      if (boo.exists())
        m_val = (boo == Boolean::True ? kLogical_T : kLogical_F);
      else
        m_val = kLogical_unset;
    };

    /** \details 
    Checks whether the Logical object has a defined value (whether the value is set).
    \returns 1 if the Logical object's value is defined (set); otherwise, the method returns 0.
    \sa
    <link OdDAI::Logical::exists@const, exists()> method.
    */
    int exists() const { return m_val != kLogical_unset ? 1 : 0; };

    /** \details 
    Flashes the Logical object to the undefined (unset) value.
    After calling this method the <link OdDAI::Logical::exists@const, exists()> method returns 0.
    \sa
    <link OdDAI::Logical::nullify, nullify()> method.
    */    
    void nullify() { m_val = kLogical_unset; };

    /** \details 
    Casts the Logical object's value to the value of the <link OdDAI::Logical_, Logical_> enumeration value.
    */
    operator Logical_() const { return m_val; };

    //operator int() const { return m_val; };
    
    /** \details 
    Assignment operator for the Logical data type.
    The operator casts specified value of the <link OdDAI::Logical_, appropriate enumeration> to the Logical value and assigns it to the object.
    \param val [in] An <link OdDAI::Logical_, enumeration> value to be assigned (a right-hand operand of the assignment operation).
    \returns The reference to the Logical object modified by the assignment operation.
    */
    Logical& operator = (const Logical_ val) { m_val = val; return *this; };
    
    /** \details 
    Assignment operator for the Logical data type. 
    The operator casts specified signed long value to the Logical value and assigns it to the object.
    \param val [in] A signed long data type value to be assigned (a right-hand operand of the assignment operation).
    \returns The reference to the Logical object modified by the assignment operation.
    */
    Logical& operator = (const long val) { m_val = (Logical_)val; return *this; };
    
    /** \details 
    Assignment operator for the Boolean data type. 
    The operator casts specified <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">ANSI string</exref> 
    to the Boolean value and assigns it to the object.
    \param val [in] An <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">ANSI string</exref> to be assigned (a right-hand operand of the assignment operation).
    \returns The reference to the Boolean object modified by the assignment operation.
    \remarks 
    The specified <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">ANSI string</exref> should be: 
    * &quot;F&quot; to set the Boolean object to the False value.
    * &quot;T&quot; to set the Boolean object to the True value.
    In all other cases, the operator makes the Boolean object undefined (its value is unset).
    */
    Logical& operator = (const OdAnsiString &val) {
      if (val == "F")
        m_val = kLogical_F;
      else
        if (val == "T")
          m_val = kLogical_T;
        else
          if (val == "U")
            m_val = kLogical_U;
          else
            m_val = kLogical_unset;
      return *this;
    };

    /** \details 
    An equality operator for the Logical data type.
    \param other [in] Another Logical object to be compared with (the right-hand operand of the comparison operation).
    \returns true if Logical objects are equal; otherwise, the method returns false.
    */
    bool operator == (const Logical &other) const
    {
      return m_val == other.m_val;
    };

    bool operator != (const Logical& other) const
    {
      return !operator == (other);
    };

    /** \details 
    A negation (&quot;NOT&quot;) operator for the Logical data type.
    Inverts the Logical object value: 
    * from True into False.
    * from False into True
    * in all other cases the operator returns the Unknown value.
    \returns The Logical object that has the inverted value.
    \remarks 
    Implementation according to the ISO 10303-11, 12.4.1.
    */
    Logical operator ! () const
    {
      if (m_val == kLogical_F)
        return kLogical_T;
      if (m_val == kLogical_T)
        return kLogical_F;
      return kLogical_U;
    };

    /** \details 
    An intersection (&quot;AND&quot;) operator for the Logical data type.
    \param other [in] Another Logical object (right-handed operand of the &quot;AND&quot; operation).
    \returns The resulted Logical object.
    \remarks 
    Implementation according to the ISO 10303-11, 12.4.2.
    */
    Logical operator && (const Logical &other)
    {
      if (m_val == kLogical_unset || other.m_val == kLogical_unset)
        return kLogical_U;
      if (m_val == kLogical_T)
        return other;
      if (m_val == kLogical_U)
      {
        if (other.m_val == kLogical_F)
          return other;
        return kLogical_U;
      }
      return kLogical_F;
    }

    /** \details 
    A union (&quot;OR&quot;) operator for the Logical data type.
    \param other [in] Another Logical object (right-handed operand of the &quot;OR&quot; operation).
    \returns The resulted Logical object.
    \remarks 
    Implementation according to the ISO 10303-11, 12.4.3.
    */
    Logical operator || (const Logical &other)
    {
      if (m_val == kLogical_unset || other.m_val == kLogical_unset)
        return kLogical_U;
      if (m_val == kLogical_T)
        return kLogical_T;
      if (m_val == kLogical_U)
      {
        if (other.m_val == kLogical_T)
          return kLogical_T;
        return kLogical_U;
      }
      return other.m_val;
    }

    /** \details
    A  &quot;XOR&quot; operator for the Logical data type.
    \param other [in] Another Logical object (right-handed operand of the &quot;OR&quot; operation).
    \returns The resulted Logical object.
    \remarks 
    Implementation according to the ISO 10303-11, 12.4.4.
    */
    Logical operator ^ (const Logical &other)
    {
      if (m_val == kLogical_U || m_val == kLogical_unset ||
        other.m_val == kLogical_U || other.m_val == kLogical_unset)
          return kLogical_U;
      if (m_val == other.m_val)
        return kLogical_F;
      return kLogical_T;
    }

    /** \details 
    Casts the Logical object's value to an <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">ANSI string</exref>.
    */
    operator OdAnsiString ()
    {
      switch (m_val)
      {
      case kLogical_F:
        return "F";
      case kLogical_T:
        return "T";
      case kLogical_U:
        return "U";
      default:
        break;
      }
      return OdDAI::Consts::OdStringUnset;
    };

  };

  /** \details 
  A data type that represents the SDAI primitive BINARY type.
  */
  typedef OdAnsiString BINARY;

  /** \details 
  A structure that contains information about the enumeration value.
  */
  struct EnumValueInfo
  {
    /**An array of bytes.*/
    const char* value;
  };

  namespace Utils
  {
    template <> inline const OdDAI::Logical& getUnset<OdDAI::Logical>() { return OdDAI::Logical::Unset; }
    template <> inline const OdDAI::Boolean& getUnset<OdDAI::Boolean>() { return OdDAI::Boolean::Unset; }

    template <> inline const OdDAI::Logical_& getUnset<OdDAI::Logical_>() { static OdDAI::Logical_ temp = OdDAI::kLogical_unset; return temp; }
    template <> inline const OdDAI::Boolean_& getUnset<OdDAI::Boolean_>() { static OdDAI::Boolean_ temp = OdDAI::kBoolean_unset; return temp; }

    inline bool isUnset(const OdDAI::Logical_& value) { return value == getUnset<OdDAI::Logical_>(); }
    inline bool isUnset(const OdDAI::Boolean_& value) { return value == getUnset<OdDAI::Boolean_>(); }
  }

}

#endif // _DAI_PRIMITIVE_H_
