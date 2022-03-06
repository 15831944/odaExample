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

#ifndef _BCF_UNSET_H
#define _BCF_UNSET_H

#include "OdaCommon.h"
#include "SmartPtr.h"

#define STL_USING_MAP
#include "OdaSTL.h"

#include "OdGUID.h"
#include "OdString.h"
#include "BcfConsts.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf
{
  /** \details
  Contains declarations related to utilities related to working with BCF files content.
  */
  namespace Utils
  {
    /** \details 
    A template function that returns an undefined value for those BCF datatypes that do not have an implemented getUnset() function.
    \returns An undefined (unset) value.
    */
    template <class TUnsetable>
    const TUnsetable& getUnset() {  ODA_ASSERT(0 && "Unknown type. Add getUnset for it."); static TUnsetable unsettled = 0; return unsettled; }

    /** \details 
    A template function that returns an undefined value for the double datatype.
    \returns A double value that represents an unset value.
    */
    template <> inline const double& getUnset<double>() { return Consts::OdNan; } 
    
    /** \details 
    A template function that returns an undefined value for the long datatype.
    \returns A long value that represents an unset value.
    */
    template <> inline const long& getUnset<long>() { return Consts::OdLongUnset; }
    
    /** \details 
    A template function that returns an undefined value for the int datatype.
    \returns An int value that represents an unset value.
    */
    template <> inline const int& getUnset<int>() { return Consts::OdIntUnset; }
    
    /** \details 
    A template function that returns an undefined value for the 
    <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> datatype.
    \returns 
    <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> value that represents an unset value.
    */
    template <> inline const OdString& getUnset<OdString>() { static OdString stringUnset = Consts::OdStringUnset; return stringUnset; }
    
    /** \details 
    A template function that returns an undefined value for the 
    <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> datatype.
    \returns 
    <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> value that represents an unset value.
    */
    template <> inline const OdAnsiString& getUnset<OdAnsiString>() { static OdAnsiString stringUnset = Consts::OdStringUnset; return stringUnset; }
    
    /** \details 
    A template function that returns an undefined value for the 
    <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> datatype.
    \returns 
    <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> value that represents an unset value.
    */
    template <> inline const OdGUID& getUnset<OdGUID>() { return OdGUID::kNull; }

    /** \details 
    A function that defines whether a specified boolean value is not set (undefined).
    \returns true if the value is not set; otherwise, the function returns false.
    */
    inline bool isUnset(const bool & value) { return false; }
    
    /** \details 
    A function that defines whether a specified float value is not set (undefined).
    \returns true if the value is not set; otherwise, the function returns false.
    */
    inline bool isUnset(const float & value) { return value != value; }
    
    /** \details 
    A function that defines whether a specified double value is not set (undefined).
    \returns true if the value is not set; otherwise, the function returns false.
    */
    inline bool isUnset(const double & value) { return value != value; }
    
    /** \details 
    A function that defines whether a specified long value is not set (undefined).
    \returns true if the value is not set; otherwise, the function returns false.
    */
    inline bool isUnset(const long value) { return value == Consts::OdLongUnset; }
    
    /** \details 
    A function that defines whether a specified unsigned integer value is not set (undefined).
    \returns true if the value is not set; otherwise, the function returns false.
    */
    inline bool isUnset(const int value) { return value == Consts::OdIntUnset; }
    
    /** \details 
    A function that defines whether a specified 
    <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> 
    value is not set (undefined).
    \returns true if the value is not set; otherwise, the function returns false.
    */
    inline bool isUnset(const OdString & value) { return value.getLength() == Consts::OdStringUnsetLength && value.compare(Consts::OdStringUnset) == 0; }
    
    /** \details 
    A function that defines whether a specified 
    <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> 
    value is not set (undefined).
    \returns true if the value is not set; otherwise, the function returns false.
    */
    inline bool isUnset(const OdAnsiString & value) { return value.getLength() == Consts::OdStringUnsetLength && value.compare(Consts::OdStringUnset) == 0; }
    
    /** \details 
    A function that defines whether a string value, represented as a null-terminated array of chars, is not set (undefined).
    \returns true if the value is not set; otherwise, the function returns false.
    */
    inline bool isUnset(const char * value) { return strlen(value) == Consts::OdStringUnsetLength && strcmp(value, Consts::OdStringUnset) == 0; }
    
    /** \details 
    A function that defines whether a specified 
    <exref target="https://docs.opendesign.com/tkernel/OdGUID.html">OdGUID</exref> 
    value is not set (undefined).
    \returns true if the value is not set; otherwise, the function returns false.
    */
    inline bool isUnset(const OdGUID & value) { return value == OdGUID::kNull; }
    
    /** \details 
    A function that defines whether a smart pointer is not set (undefined).
    \returns true if the smart pointer is not set; otherwise, the function returns false.
    */
    template <class TInner>
    inline bool isUnset(const OdSmartPtr<TInner> & value) { return value.isNull(); }
    
    /** \details 
    A function that defines whether an array of smart pointers is not set (undefined).
    \returns true if the array of smart pointers is not set; otherwise, the function returns false.
    */
    template <class TInner>
    inline bool isUnset(const OdArray<TInner> & value) { return value.empty(); }
    
    /** \details 
    A function that defines whether an STL map object is not set (undefined).
    \returns true if the map is not set; otherwise, the function returns false.
    */
    template <class TKey, class TValue>
    inline bool isUnset(const std::map<TKey, TValue> & value) { return value.empty(); }

    /** \details 
    A function that initializes a passed value as an unset (undefined) one.
    \param value [out] A placeholder for the value to be initialized.
    */
    template<class TUnsetable>
    void initUnset(TUnsetable &value) { value = getUnset<TUnsetable>(); }
  }
}

#endif // _BCF_UNSET_H

