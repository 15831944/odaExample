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

#ifndef _DAI_ANY_H_
#define _DAI_ANY_H_

#include "OdPlatformSettings.h"
#include "OdArray.h"
#include "RxValue.h"

#include "daiBuildOptions.h"
#include "daiPrimitive.h"
#include "daiTCKind.h"
#include "daiSelect.h"

class OdDAIObjectId;
class OdTypeCode;

using OdTypeCodePtr = OdSharedPtr<OdTypeCode>;

/** \details 
A universal class that implements storing and handling values of different types.
*/
class DAI_EXPORT OdAny
{
public:

  /** An empty <link OdAny, OdAny> value.*/
  DAI_EXPORT_STATIC static const OdAny kEmpty;

  /** \details 
  Creates a new OdAny object with default parameters.
  */
  OdAny();
  
  /** \details 
  Creates a new OdAny object as a deep copy of another OdAny object.
  \param other [in] An OdAny object to be copied.
  */
  OdAny(const OdAny &other);
  
  /** \details 
  Creates a new OdAny object with specified parameters.
  \param typeCode [in] A code of the data type represented with a smart pointer to the <link OdTypeCode, OdTypeCode> object. 
  \param val      [in] A raw pointer to the data of the new OdAny object.
  \param size     [in] A data length in bytes.
  */
  OdAny(const OdTypeCodePtr typeCode, void *val, unsigned int size = 1) : m_size(size), m_val(val), m_typeCode(typeCode), m_release(false) {};

  /** \details 
  Destroys OdAny object and frees the allocated memory.
  */
  ~OdAny();

  /** \details 
  Retrieves the value of the OdAny object.
  \returns A raw pointer to the memory block that contains the value.
  */
  const void* value() const { return m_val; };
  
  /** \details 
  Retrieves the size of the OdAny object's value.
  \returns An unsigned integer value that contains the OdAny object's size in bytes.
  */
  unsigned int size() const { return m_size; };
  
  /** \details 
  Retrieves the code of the OdAny object's data type.
  \returns A smart pointer to the <link OdTypeCode, OdTypeCode> object that contains the data type code.
  */  
  const OdTypeCodePtr type() const ;
  
  /** \details 
  Retrieves the kind of the OdAny object's data.
  \returns An <link OdTCKind, OdTCKind> enumeration value that represents the kind of data contained in the OdAny object.
  */    
  OdTCKind kind() const;

  /** \details 
  Sets the kind of the OdAny object's data.
  \param kind [in] An <link OdTCKind, OdTCKind> enumeration value that represents the kind of data contained in the OdAny object.
  */      
  void kind(OdTCKind kind);
  
  /** \details 
  Resets the contents of the OdAny object. 
  */
  void reset();

  /** \details 
  Retrieves the OdAny object type path. 
  \param path [out] A placeholder for the array of data type names included into the path.
  \returns true if the type path was formed and returned to the calling subroutine successfully; otherwise, the method returns false.
  */
  bool getTypePath(OdArray<OdAnsiString> &path);
  
  /** \details 
  Sets the new type path for the OdAny object.
  \param typeCode [in] An instance of the <link OdTypeCode, OdTypeCode> class that represents the new type path to be set.
  \returns true if the type path was successfully set; otherwise, the method returns false.
  */
  bool setTypePath(OdTypeCodePtr typeCode);

  //
  // Single variable
  //
  
  /** \details 
  Writes the value of the short data type variable into the OdAny object.
  \param val [in] A short value to be written (right-hand operand of the << operator).
  */
  void operator << (const short val);
  
  /** \details 
  Writes the OdAny object's value into a short data type variable.
  \param val [out] The short data type variable (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully cast to the short value and written; otherwise, the method returns false.
  */
  bool operator >> (short &val) const;

  /** \details 
  Writes the value of the unsigned short data type variable into the OdAny object.
  \param val [in] An unsigned short value to be written (right-hand operand of the << operator).
  */
  void operator << (const unsigned short val);
  
  /** \details 
  Writes the OdAny object's value into an unsigned short data type variable.
  \param val [out] The unsigned short data type variable (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully cast to the unsigned short value and written; otherwise, the method returns false.
  */
  bool operator >> (unsigned short &val) const;

  /** \details 
  Writes the value of the int data type variable into the OdAny object.
  \param val [in] An int value to be written (right-hand operand of the << operator).
  */
  void operator << (const int val);
  
  /** \details 
  Writes the OdAny object's value into an int data type variable.
  \param val [out] The int data type variable (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully cast to the int value and written; otherwise, the method returns false.
  */
  bool operator >> (int &val) const;

  /** \details 
  Writes the value of the unsigned int data type variable into the OdAny object.
  \param val [in] An unsigned int value to be written (right-hand operand of the << operator).
  */
  void operator << (const unsigned long val);
  
  /** \details 
  Writes the OdAny object's value into an unsigned int data type variable.
  \param val [out] The unsigned int data type variable (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully cast to the unsigned int value and written; otherwise, the method returns false.
  */
  bool operator >> (unsigned long &val) const;

  /** \details 
  Writes the value of the float data type variable into the OdAny object.
  \param val [in] A float value to be written (right-hand operand of the << operator).
  */
  void operator << (const float val);
  
  /** \details 
  Writes the OdAny object's value into a float data type variable.
  \param val [out] The float data type variable (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully cast to the float value and written; otherwise, the method returns false.
  */
  bool operator >> (float &val) const;

  /** \details 
  Writes the value of the <link OdDAI::Logical, Logical> data type variable into the OdAny object.
  \param val [in] A <link OdDAI::Logical, Logical> value to be written (right-hand operand of the << operator).
  */
  void operator << (const OdDAI::Logical &val);
  
  /** \details 
  Writes the OdAny object's value into a <link OdDAI::Logical, Logical> data type variable.
  \param val [out] The <link OdDAI::Logical, Logical> data type variable (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully cast to the <link OdDAI::Logical, Logical> value and written; otherwise, the method returns false.
  */
  bool operator >> (OdDAI::Logical &val) const;

  /** \details 
  Writes the value of the bool data type variable into the OdAny object.
  \param val [in] A bool value to be written (right-hand operand of the << operator).
  */
  void operator << (const bool val);
  
  /** \details 
  Writes the OdAny object's value into a bool data type variable.
  \param val [out] The bool data type variable (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully cast to the bool value and written; otherwise, the method returns false.
  */
  bool operator >> (bool &val) const;

  /** \details 
  Writes the value of the double data type variable into the OdAny object.
  \param val [in] A double value to be written (right-hand operand of the << operator).
  */
  void operator << (const double val);
  
  /** \details 
  Writes the OdAny object's value into a double data type variable.
  \param val [out] The double data type variable (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully cast to the double value and written; otherwise, the method returns false.
  */
  bool operator >> (double &val) const;

  /** \details 
  Writes the value of the <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> data type variable into the OdAny object.
  \param val [in] An <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> value to be written (right-hand operand of the << operator).
  */
  void operator << (const OdString &val);
  
  /** \details 
  Writes the OdAny object's value into an <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> data type variable.
  \param val [out] The <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> data type variable (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully cast to the <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> value and written; otherwise, the method returns false.
  */
  bool operator >> (OdString &val) const;

  /** \details 
  Writes the value of the null-terminated string into the OdAny object.
  \param val [in] A null-terminated string to be written (right-hand operand of the << operator).
  */
  void operator << (const char *val);
  
  /** \details 
  Writes the value of the <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> data type variable into the OdAny object.
  \param val [in] An <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> value to be written (right-hand operand of the << operator).
  */
  void operator << (const OdAnsiString &val);
  
  /** \details 
  Writes the OdAny object's value into an <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> data type variable.
  \param val [out] The <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> data type variable (right-hand operand of the >> operator).
  \returns 
  true if the OdAny object's value was successfully cast to the <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> value and written; otherwise, the method returns false.
  */
  bool operator >> (OdAnsiString &val) const;

  /** \details 
  Writes the <link OdDAIObjectId, OdDAIObjectId> object into the OdAny object.
  \param val [in] An <link OdDAIObjectId, OdDAIObjectId> object to be written (right-hand operand of the << operator).
  */
  void operator << (const OdDAIObjectId &val);
  
  /** \details 
  Writes the OdAny object's value into an <link OdDAIObjectId, OdDAIObjectId> object.
  \param val [out] The <link OdDAIObjectId, OdDAIObjectId> object (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully cast to the <link OdDAIObjectId, OdDAIObjectId> object and written; otherwise, the method returns false.
  */
  bool operator >> (OdDAIObjectId &val) const;

  /** \details 
  Writes the <link OdTypeCode, OdTypeCode> object into the OdAny object.
  \param val [in] A smart pointer to the <link OdTypeCode, OdTypeCode> object to be written (right-hand operand of the << operator).
  */
  void operator << (const OdTypeCodePtr val);
  
  /** \details 
  Writes the OdAny object's value into an <link OdTypeCode, OdTypeCode> object.
  \param val [out] A smart pointer to the <link OdTypeCode, OdTypeCode> object (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully cast to the <link OdTypeCode, OdTypeCode> object and written; otherwise, the method returns false.
  */
  bool operator >> (OdTypeCodePtr &val) const;

  /** \details 
  Writes the OdAny object's value into another OdAny object.
  \param val [out] Another OdAny object (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully written; otherwise, the method returns false.
  */
  bool operator >> (OdAny& val) const;
  
  /** \details 
  Writes the OdAny object's value into a <link OdDAI::Select, Select> data type variable.
  \param val [out] A raw pointer to the <link OdDAI::Select, Select> data type variable (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully written; otherwise, the method returns false.
  */
  bool operator >> (OdDAI::Select* &val);

  //
  // Aggregates
  //
  
  /** \details 
  Writes the array of short data type values into the OdAny object.
  \param val [in] An array of short data type values to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<short> &val);
  
  /** \details 
  Writes the OdAny object's value into an array of short data type values.
  \param val [out] An array of short data type values to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of short data type values and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<short> &val) const;

  /** \details 
  Writes the array of unsigned short data type values into the OdAny object.
  \param val [in] An array of unsigned short data type values to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<unsigned short> &val);
  
  /** \details 
  Writes the OdAny object's value into an array of unsigned short data type values.
  \param val [out] An array of unsigned short data type values to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of unsigned short data type values and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<unsigned short> &val) const;

  /** \details 
  Writes the array of int data type values into the OdAny object.
  \param val [in] An array of int data type values to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<int> &val);
  
  /** \details 
  Writes the OdAny object's value into an array of int data type values.
  \param val [out] An array of int data type values to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of int data type values and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<int> &val) const;
  
  /** \details 
  Writes the two-dimensional array (matrix) of int data type values into the OdAny object.
  \param val [in] A matrix with int data type values to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<OdArray<int> > &val);
  
  /** \details 
  Writes the OdAny object's value into a two-dimensional (matrix) array of int data type values.
  \param val [out] A matrix with int data type values to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into a matrix with int data type values and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<OdArray<int> > &val) const;

  /** \details 
  Writes the array of unsigned int data type values into the OdAny object.
  \param val [in] An array of unsigned int data type values to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<unsigned long> &val);
  
  /** \details 
  Writes the OdAny object's value into an array of unsigned int data type values.
  \param val [out] An array of unsigned int data type values to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of unsigned int data type values and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<unsigned long> &val) const;

  /** \details 
  Writes the array of float data type values into the OdAny object.
  \param val [in] An array of float data type values to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<float> &val);
  
  /** \details 
  Writes the OdAny object's value into an array of float data type values.
  \param val [out] An array of float data type values to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of float data type values and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<float> &val) const;

  /** \details 
  Writes the array of double data type values into the OdAny object.
  \param val [in] An array of double data type values to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<double> &val);
  
  /** \details 
  Writes the OdAny object's value into an array of double data type values.
  \param val [out] An array of double data type values to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of double data type values and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<double> &val) const;
  
  /** \details 
  Writes the two-dimensional array (matrix) of double data type values into the OdAny object.
  \param val [in] A matrix with double data type values to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<OdArray<double> > &val);
  
  /** \details 
  Writes the OdAny object's value into a two-dimensional (matrix) array of double data type values.
  \param val [out] A matrix with double data type values to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into a matrix with double data type values and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<OdArray<double> > &val) const;

  /** \details 
  Writes the array of <link OdDAI::Logical, Logical> values into the OdAny object.
  \param val [in] An array of <link OdDAI::Logical, Logical> values to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<OdDAI::Logical> &val);
  
  /** \details 
  Writes the OdAny object's value into an array of <link OdDAI::Logical, Logical> values.
  \param val [out] An array of <link OdDAI::Logical, Logical> values to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of <link OdDAI::Logical, Logical> values and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<OdDAI::Logical> &val) const;

  /** \details 
  Writes the array of bool values into the OdAny object.
  \param val [in] An array of bool values to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<bool> &val);
  
  /** \details 
  Writes the OdAny object's value into an array of bool values.
  \param val [out] An array of bool values to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of bool values and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<bool> &val) const;

  /** \details 
  Writes the array of <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> objects into the OdAny object.
  \param val [in] An array of <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> objects to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<OdString> &val);
  
  /** \details 
  Writes the OdAny object's value into an array of <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> objects.
  \param val [out] An array of <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> objects to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString</exref> objects and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<OdString> &val) const;

  /** \details 
  Writes the array of <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> objects into the OdAny object.
  \param val [in] An array of <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> objects to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<OdAnsiString> &val);
  
  /** \details 
  Writes the OdAny object's value into an array of <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> objects.
  \param val [out] An array of <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> objects to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">OdAnsiString</exref> objects and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<OdAnsiString> &val) const;

  /** \details 
  Writes the array of <link OdDAIObjectId, OdDAIObjectId> objects into the OdAny object.
  \param val [in] An array of <link OdDAIObjectId, OdDAIObjectId> objects to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<OdDAIObjectId> &val);
  
  /** \details 
  Writes the OdAny object's value into an array of <link OdDAIObjectId, OdDAIObjectId> objects.
  \param val [out] An array of <link OdDAIObjectId, OdDAIObjectId> objects to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of <link OdDAIObjectId, OdDAIObjectId> objects and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<OdDAIObjectId> &val) const;
  
  /** \details 
  Writes the two-dimensional array (matrix) of <link OdDAIObjectId, OdDAIObjectId> objects into the OdAny object.
  \param val [in] A matrix with <link OdDAIObjectId, OdDAIObjectId> objects to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<OdArray<OdDAIObjectId> > &val);
  
  /** \details 
  Writes the OdAny object's value into a two-dimensional array (matrix) of <link OdDAIObjectId, OdDAIObjectId> objects.
  \param val [out] A matrix with <link OdDAIObjectId, OdDAIObjectId> objects to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into a matrix with <link OdDAIObjectId, OdDAIObjectId> objects and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<OdArray<OdDAIObjectId> > &val) const;

  /** \details 
  Writes the array of <link OdAny, OdAny> objects into the OdAny object.
  \param val [in] An array of <link OdAny, OdAny> objects to be written (right-hand operand of the << operator).
  */
  void operator << (const OdArray<OdAny> &val);
  
  /** \details 
  Writes the OdAny object's value into an array of <link OdAny, OdAny> objects.
  \param val [out] An array of <link OdAny, OdAny> objects to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of <link OdAny, OdAny> objects and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<OdAny> &val) const;
  
  /** \details 
  Writes the OdAny object's value into an array of <link OdDAI::Select, Select> data type values.
  \param val [out] An array of <link OdDAI::Select, Select> data type values to be written (right-hand operand of the >> operator).
  \returns true if the OdAny object's value was successfully converted into an array of <link OdDAI::Select, Select> data type values and written; otherwise, the method returns false.
  */
  bool operator >> (OdArray<OdDAI::Select*> &val) const;

  /** \details 
  Equality operator for the OdAny objects.
  It compares the OdAny object with another OdAny object and determines whether these objects are equal. 
  \param right [in] Another OdAny object to be compared with (right-hand operand of the equality operator).
  \returns true if the OdAny object is equal to another OdAny object; otherwise, the method returns false.
  */
  bool operator == (const OdAny& right) const;
  
  /** \details 
  Inequality operator for the OdAny objects.
  It compares the OdAny object with another OdAny object and determines whether these objects are unequal. 
  \param right [in] Another OdAny object to be compared with (right-hand operand of the equality operator).
  \returns true if the OdAny object is not equal to another OdAny object; otherwise, the method returns false.
  */
  bool operator != (const OdAny& right) const;

  /** \details 
  Assignment operator for the OdAny class objects.
  \param right [in] Another OdAny object (right-hand operand of the assignment operation). Its value should be copied to this OdAny object.
  \returns The reference to the OdAny object after its modification with the assignment operation.
  */
  OdAny& operator = (const OdAny& right);

  //DOM-IGNORE-BEGIN
  /** \details 
  Allocates memory for an array of the double data type with a specified size.
  \param double [in] A raw pointer to the double array.
  \param size   [in] A size of the array (number of elements).
  \remarks 
  This method is for internal use only.
  It is strictly recommended DO NOT use it in your applications.
  */
  void assignArray(const double *arr, int size);
  //DOM-IGNORE-END

private:
  void copy(const OdAny& other);
  void clear();
  void setTypeCode(OdTCKind tk);

  class Prop;
private:

  unsigned int  m_size;
  const void    *m_val;
  OdTypeCodePtr m_typeCode;
  mutable bool  m_release;

};

/** \details 
A data type that represents a smart pointer to an <link OdAny, OdAny> object.
*/
typedef OdArray<OdAny> OdAnyArray;




#endif // _DAI_ANY_H_
