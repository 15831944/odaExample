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

#ifndef _OD_IFC_GUID_H_
#define _OD_IFC_GUID_H_

#include "OdaCommon.h"
#include "OdAnsiString.h"
#include "IfcBuildOptions.h"
#include "OdGUID.h"

/** \details
A class that implements generating and storing global unique identifiers (GUID) for IFC objects.
*/
class IFCCORE_EXPORT OdIfcGUID
{
public:
    
  /** \details
  Creates a new IFC GUID object with default parameters.
  */
  OdIfcGUID();

  /** \details
  Creates a new IFC GUID based on an existing OdGUID value (copy constructor).
  \param other [in] An OdGUID object that is used as a base for creating the IFC GUID object.
  */
  OdIfcGUID(const OdGUID &other);

  /** \details 
  Assignment operator for IFC GUID objects.
  \param s [in] A new IFC GUID value to be assigned represented as an ANSI string.
  \returns A reference to the IFC GUID object modified with the assignment operation.
  */
  OdIfcGUID& operator= (const OdAnsiString &s);

  /** \details
  Assignment operator for IFC GUID objects.
  \param other [in] A new GUID value to be assigned.
  \returns A reference to the IFC GUID object modified with the assignment operation.
  */
  OdIfcGUID& operator= (const OdGUID &other);

  /** \details 
  Comparison operator for IFC GUID objects.
  \param other [in] Another IFC GUID value to be compared with (right-hand operand).
  \returns true if the IFC GUID object is equal to another IFC GUID object; otherwise, the method returns false.
  */
  bool operator== (const OdIfcGUID &other) const
  {
    return strncmp(m_val, other.m_val, 22) == 0;
  };

  /** \details 
  Inequality operator for IFC GUID objects.
  \param other [in] Another IFC GUID value to be compared with (right-hand operand).
  \returns true if the IFC GUID object is not equal to another IFC GUID object; otherwise, the method returns false.
  */
  bool operator!= (const OdIfcGUID &other) const
  {
    return !(this->operator == (other));
  };

  /** \details
  The &quot;less-than&quot; operator for IFC GUID objects.
  \param other [in] Another IFC GUID value to be compared with (right-hand operand).
  \returns true if the IFC GUID value is less than the compared IFC GUID value; otherwise the operator returns false.
  \remarks 
  The IFC GUID is less than another IFC GUID if the string representation of the IFC GUID is not equal to the string representation 
  of another IFC GUID and the code of the first symbol that differs is less than the symbol code 
  in the same position in the string representation of the compared IFC GUID.
  */
  bool operator< (const OdIfcGUID &other) const
  {
    return strncmp(m_val, other.m_val, 22) < 0;
  };

  /** \details 
  Converts the IFC GUID object's value to a constant C++ character array.
  \returns A raw pointer to the C++ character array that contains the string with the IfcGUID value.
  */
  operator const char* () const;

  /** \details 
  Converts the IFC GUID object's value to a C++ character array.
  \returns A raw pointer to the C++ character array.
  */
  operator char* ();

  /** \details
  Retrieves the constant raw pointer to the underlying string.
  \returns A raw pointer to the C++ character array.
  */
  const char * c_str() const { return m_val; };

  /** \details
  Determines whether the IFC GUID value is valid.
  \returns true if the value is valid; otherwise the method returns false.
  */
  bool isValid() const;

  /** \details
  Generates a new IFC GUID object (pseudo constructor).
  \returns The generated GUID object.
  */
  static OdIfcGUID generate();

//DOM-IGNORE-BEGIN
private:
  char m_val[23];
//DOM-IGNORE-END
};

#endif // _OD_IFC_GUID_H_
