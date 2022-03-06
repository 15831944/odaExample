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

#ifndef _SDAI_ADB_VALUE_H
#define _SDAI_ADB_VALUE_H

#include "OdaCommon.h"
#include "OdPlatformSettings.h"
#include "daiBuildOptions.h"

#include "OdArray.h"
#include "daiPrimitive.h"
#include "sdai.h"

#define STL_USING_VECTOR
#define STL_USING_STRING
#include "OdaSTL.h"

#include "daiTCKind.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  class Aggr;
  /** \details
  Class should holds a value of select.
  */
  class DAI_EXPORT ADB_Value
  {
  public:
    /** \details
    Creates a new empty instance.
    */
    ADB_Value();

    /** \details
    Constructor copy. Creates a new empty instance and init data from the right value.
    \param rightValue [in] the value to copy from.
    */
    ADB_Value(const ADB_Value& rightValue);

    /** \details
    Destroys th value.
    */
    ~ADB_Value();

    /** \details
      Copy one value to another.
      \param rightValue [in] value to copy from.
      \returns the reference to itself.
    */
    ADB_Value& operator=(const ADB_Value& rightValue);

    /** \details
      Compare two values.
      \param rightValue [in] other value to compare.
      \returns true if equal, and false otherwise.
    */
    bool operator==(const ADB_Value& rightValue) const;


    /** \details
      Operator int. Provides int value. If there is not int value, exception will be thrown.
      \returns int value.
    */
    operator int() const;

    /** \details
      Operator bool. Provides bool value. If there is not bool value inside, exception will be thrown.
      \returns bool value.
    */
    operator bool() const;

    /** \details
      Operator EnumValueInfo. Provides EnumValueInfo value.
      If there is not EnumValueInfo value inside, exception will be thrown.
      \returns EnumValueInfo value.
    */
    operator EnumValueInfo() const;

    /** \details
      Operator double. Provides double value. If there is not double value, exception will be thrown.
      \returns double value.
    */
    operator const double& () const;

    /** \details
      Operator Logical. Provides Logical value. If there is not Logical value, exception will be thrown.
      \returns Logical value.
    */
    operator const OdDAI::Logical& () const;

    /** \details
      Operator Boolean. Provides Boolean value. If there is not Boolean value, exception will be thrown.
      \returns Boolean value.
    */
    operator const OdDAI::Boolean& () const;

    /** \details
      Operator OdDAIObjectId. Provides OdDAIObjectId value. If there is not OdDAIObjectId value, exception will be thrown.
      \returns OdDAIObjectId value.
    */
    operator const OdDAIObjectId& () const;

    /** \details
      Operator OdAnsiString. Provides OdAnsiString value. If there is not OdAnsiString value, exception will be thrown.
      \returns OdAnsiString value.
    */
    operator const OdAnsiString& () const;

    /** \details
      Operator Aggr*. Provides Aggr* value. If there is not Aggr* value, exception will be thrown.
      \returns Aggr* value.
    */
    operator const OdDAI::Aggr* () const;

    /** \details
      Sets int value.
      \returns true if succeeded, false otherwise
    */
    bool setValue(const int& setFrom);

    /** \details
      Sets bool value.
      \returns true if succeeded, false otherwise
    */
    bool setValue(const bool& setFrom);

    /** \details
      Sets EnumValueInfo value.
      \returns true if succeeded, false otherwise
    */
    bool setValue(const EnumValueInfo& setFrom);

    /** \details
      Sets double value.
      \returns true if succeeded, false otherwise
    */
    bool setValue(const double& setFrom);

    /** \details
      Sets Logical value.
      \returns true if succeeded, false otherwise
    */
    bool setValue(const OdDAI::Logical& setFrom);

    /** \details
      Sets Boolean value.
      \returns true if succeeded, false otherwise
    */
    bool setValue(const OdDAI::Boolean& setFrom);

    /** \details
      Sets OdDAIObjectId value.
      \returns true if succeeded, false otherwise
    */
    bool setValue(const OdDAIObjectId& setFrom);

    /** \details
      Sets const char* value.
      \returns true if succeeded, false otherwise
    */
    bool setValue(const char* setFrom);

    /** \details
      Sets OdAnsiString value.
      \returns true if succeeded, false otherwise
    */
    bool setValue(const OdAnsiString& setFrom);

    /** \details
      Sets Aggr* value.
      \returns true if succeeded, false otherwise
    */
    bool setValue(OdDAI::Aggr* setFrom);

    /** \details
      Gets int value.
      \param getTo [out] the reference to int value to get to.
      \returns if the internal type is int the function returns true, in otherwis returns false.
    */
    bool getValue(int& getTo) const;

    /** \details
      Gets bool value.
      \param getTo [out] the reference to bool value to get to.
      \returns if the internal type is bool the function returns true, in otherwis returns false.
    */
    bool getValue(bool& getTo) const;

    /** \details
      Gets EnumValueInfo value.
      \param getTo [out] the reference to EnumValueInfo value to get to.
      \returns if the internal type is EnumValueInfo the function returns true, in otherwis returns false.
    */
    bool getValue(EnumValueInfo& getTo) const;

    /** \details
      Gets double value.
      \param getTo [out] the reference to double value to get to.
      \returns if the internal type is double the function returns true, in otherwis returns false.
    */
    bool getValue(double& getTo) const;

    /** \details
      Gets Logical value.
      \param getTo [out] the reference to Logical value to get to.
      \returns if the internal type is Logical the function returns true, in otherwis returns false.
    */
    bool getValue(OdDAI::Logical& getTo)const;

    /** \details
      Gets Boolean value.
      \param getTo [out] the reference to Boolean value to get to.
      \returns if the internal type is Boolean the function returns true, in otherwis returns false.
    */
    bool getValue(OdDAI::Boolean& getTo)const;

    /** \details
      Gets OdDAIObjectId value.
      \param getTo [out] the reference to OdDAIObjectId value to get to.
      \returns if the internal type is OdDAIObjectId the function returns true, in otherwis returns false.
    */
    bool getValue(OdDAIObjectId& getTo)const;

    /** \details
      Gets const char* value.
      \param getTo [out] the reference to const char* value to get to.
      \returns if the internal type is const char* the function returns true, in otherwis returns false.
    */
    bool getValue(const char*& getTo)const;

    /** \details
      Gets OdAnsiString value.
      \param getTo [out] the reference to OdAnsiString value to get to.
      \returns if the internal type is OdAnsiString the function returns true, in otherwis returns false.
    */
    bool getValue(OdAnsiString& getTo)const;

    /** \details
      Gets OdDAI::Aggr* value.
      \param getTo [out] the reference to OdDAI::Aggr* value to get to.
      \returns if the internal type is OdDAI::Aggr* the function returns true, in otherwis returns false.
    */
    bool getValue(OdDAI::Aggr*& getTo)const;



    /** \details
      template function to set a different type value.
      \param val [in] the new value to set.
    */
    template<typename ValueType>
    void operator << (const ValueType& val)
    {
      setValue(val);
    }

    void operator << (const OdDAI::Boolean& val)
    {
      setValue(val);
    }


    /** \details
      template function to get an internal value.
      \param val [out] the value to get to.
      \returns if the internal type is the same as ValueType the function returns true, in otherwis returns false.
    */
    template<typename ValueType>
    bool operator >> (ValueType& val) const
    {
      return getValue(val);
    }

    bool operator >> (OdDAI::Boolean& val) const
    {
      bool transitValue = false;
      if (!getValue(transitValue))
      {
        return false;
      }

      val = transitValue ? OdDAI::Boolean::True : OdDAI::Boolean::False;
      return true;
    }

    /** \details
      Provides tyep of the value.
      \returns the type OdTCKind.
    */
    OdTCKind type() const;

    /** \details
      Clear all data.
    */
    void clean();

    //DOM-IGNORE-BEGIN
  private:
    static void copyADB_internal(const ADB_Value& from, ADB_Value& to);
    static bool compareADB_internal(const ADB_Value& left, const ADB_Value& right);
    static void unsetADB_internal(ADB_Value& unsetWhat);

  private:
    OdTCKind m_type;

    union
    {
      int intValue;
      EnumValueInfo  enumValue;
      double doubleValue;
      OdDAI::Logical logicalValue;
      OdDAI::Boolean booleanValue;
      OdDAIObjectId objectIdValue;
      OdAnsiString ansiStringValue;
      OdDAI::Aggr* aggrValue;
    };
    //DOM-IGNORE-END
  };
}


#endif
