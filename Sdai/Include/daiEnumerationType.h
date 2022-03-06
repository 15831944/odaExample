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

#ifndef _DAI_ENUMERATION_TYPE_H
#define _DAI_ENUMERATION_TYPE_H

#include "daiDictionaryInstance.h"
#include "daiTypeCode.h"
#include "daiAggr/daiList.h"
#include "SharedPtr.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class SchemaFiller;
  class SpecifiedEnumPtrValueType;

  /** \details
  A class that represents the enumeration data type that stores metadata for the ENUMERATION TYPE defined within an EXPRESS schema.
  */
  class DAI_EXPORT EnumerationType : public DictionaryInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(EnumerationType);
    //DOM-IGNORE-END

    /** \details
    Creates a new enumeration data type definition.
    \param name     [in] A null-terminated string that contains the name of the enumeration data type.
    \param elements [in] An array of ANSI strings that contain enumerated values.
    \returns A smart pointer to the created <link OdDAI::EnumerationType, enumerationt type> instance.
    */
    static OdSmartPtr<EnumerationType> createObject(
      const char * name,
      const OdArray<OdAnsiString> &elements);

    /** \details
    Creates a new enumeration data type object with default parameters.
    */
    EnumerationType()
    {}


    /** \details
    Destroys the enumeration data type object and frees the memory it has been residing.
    */
    ~EnumerationType();

    /** \details
    Creates a new enumeration data type object with specified parameters.
    \param typeCode [in] A smart pointer to the <link OdTypeCode, type code> of the enumeration data type.
    \param elements [in] An array of ANSI strings that contain enumerated values.
    */
    EnumerationType(
      const OdTypeCodePtr &typeCode,
      const OdArray<OdAnsiString> &elements);

    /** \details
    Retrieves the <link OdTypeCode, type code> of the enumeration data type.
    \returns A smart pointer to the <link OdTypeCode, type code> object of the enumeration data type.
    */
    virtual const OdTypeCodePtr type() const { return m_typeCode; };

    /** \details
    Retrieves the list of values of the enumeration data type.
    \returns A list of ANSI strings that contains values of the enumeration data type.
    */
    const OdDAI::OdAnsiStringList& elements() const;;
    
    /** \details 
    Retrieves the undefined (unset) value for the enumeration data type.
    \returns An signed integer value that corresponds to the undefined (unset) value of the enumeration data type.
    */
    int getUnsetIndex() const;

    /** \details 
    Checks whether a specified enumeration value is valid. 
    \param testValue [in] An unsigned integer value that contains the value to check.
    \returns true if the specified value is valid; otherwise, the method returns false.
    */
    bool isValid(int testValue) const;

    /** \details 
    Converts the enumeration value into a null-terminated string. 
    \param convertWhat [in] An signed integer value that contains the value to be converted.
    \returns 
    A null-terminated string that contains the text representation of the specified enumeration value.
    If the method can not convert specified enumeration value into a string representation (for example when the specified enumeration value is not valid), the method returns an empty string.    
    */
    const char* valueToString(int convertWhat) const;

    /** \details 
    Converts a string representation of the enumeration value into an integer representation that corresponds to the specified enumeration value. 
    The method searches the specified string value in the elements list and returns the position of the found element. 
    \param convertWhat [in] An ANSI string that contains the value to be converted.
    \returns 
    A signed integer value that corresponds to the specified string representation of the enumeration value.
    If the specified representation doesn't match any integer representation of the enumeration value, the method returns -1.
    \remarks 
    The method uses the CASE-SENSITIVE search when it is looking for the integer representation of the enumeration value that corresponds to the specified string representation.
    */
    int stringToValue(const char * convertWhat) const;

    /** \details 
    Converts a string representation of the enumeration value into an integer representation that corresponds to the specified enumeration value. 
    The method searches the specified string value in the elements list and returns the position of the found element. 
    \param convertWhat [in] An ANSI string that contains the value to be converted.
    \returns 
    A signed integer value that corresponds to the specified string representation of the enumeration value.
    If the specified representation doesn't match any integer representation of the enumeration value, the method returns -1.
    \remarks 
    The method uses the CASE-INSENSITIVE search when it is looking for the integer representation of the enumeration value that corresponds to the specified string representation.
    */
    int stringToValueCaseInsensitive(const char * convertWhat) const;

    /** \details
    Retrieves the enumeration type object converted to an <link OdDAI::SpecifiedEnumValueType, OdDAI::SpecifiedEnumValueType> object.
    \returns A raw pointer to the <link OdDAI::SpecifiedEnumPtrValueType, OdDAI::SpecifiedEnumPtrValueType> object related to the enumeration object.
    */
    const OdDAI::SpecifiedEnumPtrValueType* getSpecifiedValueType() const;

  protected:
    //DOM-IGNORE-BEGIN
    /**The <link OdTypeCode, type code> of the enumeration data type.*/
    OdTypeCodePtr   m_typeCode;
    /**An ANSI string array that contains the text representation of the enumeration values.*/
    OdDAI::OdAnsiStringList m_elements;
    /**Corresponding specified enumeration value data type.*/
    mutable OdDAI::SpecifiedEnumPtrValueType* m_specifiedType = nullptr;

    /** \details 
    Sets the <link OdTypeCode, type code> of the enumeration data type.
    \param typeCode [in] A smart pointer to an <link OdTypeCode, OdTypeCode> object.
    */
    void type(const OdTypeCodePtr &typeCode) { m_typeCode = typeCode; };
    
    /** details 
    Sets the array of enumeration values in text representation.
    \param elements [in] An <exref target="">array</exref> of <exref target="">ANSI-strings</exref>
    */
    void setElements(const OdArray<OdAnsiString> &elements) { m_elements.setArray(elements); };

    friend class SchemaFiller;
    //DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::EnumerationType, enumeration type> object.
  */
  typedef OdSmartPtr<EnumerationType> EnumerationTypePtr;

  /** \details
  A data type that represents an STD list of ansi string objects.
  */
  typedef OdDAI::OdAnsiStringList ExpressIDList;
}

#endif // _DAI_ENUMERATION_TYPE_H
