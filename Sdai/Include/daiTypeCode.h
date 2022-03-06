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

#ifndef _DAI_TYPECODE_H_
#define _DAI_TYPECODE_H_

#include "TD_PackPush.h"

#include "SharedPtr.h"
#include "daiTCKind.h"
#include "daiAny.h"

#define STL_USING_MEMORY
#include "OdaSTL.h"

class OdTypeCode;
using OdTypeCodePtr = OdSharedPtr<OdTypeCode>;

/** \details
A class that stores principal information about EXPRESS types.
\sa 
<link ifc_overview_data_types, IFC Data Types>
*/
class DAI_EXPORT OdTypeCode
{
public:

  /** \details 
  A constant that represents the NULL value for any data type of the EXPRESS definition language.
  */
  DAI_EXPORT_STATIC static const OdTypeCodePtr kTCNull;

  /** \details 
  A constant that represents the integer data type for the EXPRESS definition language.
  */
  DAI_EXPORT_STATIC static const OdTypeCodePtr kTCInteger;

  /** \details 
  A constant that represents the Real data type for the EXPRESS definition language.
  */
  DAI_EXPORT_STATIC static const OdTypeCodePtr kTCReal;

  /** \details 
  A constant that represents the Boolean data type for the EXPRESS definition language.
  */
  DAI_EXPORT_STATIC static const OdTypeCodePtr kTCBoolean;

  /** \details 
  A constant that represents the Logical data type for the EXPRESS definition language.
  */
  DAI_EXPORT_STATIC static const OdTypeCodePtr kTCLogical;

  /** \details 
  A constant that represents the String class for the EXPRESS definition language.
  */
  DAI_EXPORT_STATIC static const OdTypeCodePtr kTCString;
  
  /** \details 
  A constant that represents the object identifier data type for the EXPRESS definition language.
  */
  DAI_EXPORT_STATIC static const OdTypeCodePtr kTCObjectId;
  
  /** \details 
  A constant that represents the <link OdTypeCode, OdTypeCode> data type for the EXPRESS definition language.
  */
  DAI_EXPORT_STATIC static const OdTypeCodePtr kTCTypeCode;
  
  /** \details 
  A constant that represents the Sequence data type for the EXPRESS definition language.
  */
  DAI_EXPORT_STATIC static const OdTypeCodePtr kTCSequence;
  
  /** \details 
  A constant that represents the Union data type for the EXPRESS definition language.
  */
  DAI_EXPORT_STATIC static const OdTypeCodePtr kTCUnion;
  
  /** \details 
  A constant that represents the Octet data type for the EXPRESS definition language.
  */
  DAI_EXPORT_STATIC static const OdTypeCodePtr kTCOctet;
  
  /** \details 
  A constant that represents the Any data type for the EXPRESS definition language.
  */
  DAI_EXPORT_STATIC static const OdTypeCodePtr kTCAny;

  /** \details 
  Creates a new OdTypeCode object with a NULL value.
  */
  OdTypeCode() : m_kind(tkNull) {};

  /** \details 
  Creates a new OdTypeCode object of a specified kind.
  \param kind [in] A <link OdTCKind, kind> of the OdTypeCode object. 
  */  
  OdTypeCode(OdTCKind kind) : m_kind(kind) {};

  /** \details 
  Retrieves the <link OdTCKind, kind> of the OdTypeCode object.
  \returns An <link OdTCKind, OdTCKind> enumeration value that represent the OdTypeCode object's kind.
  */
  OdTCKind kind() const { return m_kind; };

  /** \details 
  Retrieves the number of the OdTypeCode object parameters.
  \returns A <exref target="https://docs.opendesign.com/tkernel/OdUInt32.html">32-bit unsigned integer</exref> value that contains the number of the OdTypeCode object parameters.
  */
  OdUInt32 paramCount() const { return m_parameters.size(); };

  /** \details 
  Retrieves the current value of a specified parameter of the OdTypeCode object.
  The parameter which value is requested is specified with its index.
  \param ind [in] A <exref target="https://docs.opendesign.com/tkernel/OdUInt32.html">32-bit unsigned integer</exref> value that contains the index of the requested parameter.
  \returns An <link OdAny, OdAny> object that contains the current parameter value.
  \remarks 
  If the index value is incorrect, the method returns an empty <link OdAny, OdAny> object.
  */  
  OdAny parameter(OdUInt32 ind) const {
    if (ind < m_parameters.size())
      return m_parameters.at(ind);
    return OdAny();
  };
  
  /** \details 
  Appends a new parameter for the OdTypeCode object.
  \param any_var [in] An <link OdAny, OdAny> object that contains the value of the new parameter to be appended.
  */
  void appendParameter(const OdAny& any_var) { m_parameters.push_back(any_var); };

  /** \details 
  Creates a new OdTypeCode object from a specified path with a specified kind in a following format of type path definition: 
  "IfcMeasureValue/IfcPositiveLengthMeasure/../../.. etc.
  \param tk   [in] An <link OdTCKind, OdTCKind> enumeration value that contains the kind of the object to be created.
  \param path [in] A null-terminated string that contains the type-path for the object to be created.
  \returns A raw pointer to the created odTypeCode object.
  */
  static OdTypeCode* createFromPath(OdTCKind tk, const char *path);

  /** \details 
  Resets all parameters of the OdTypeCode object.
  The method clears the parameters array.
  */
  void reset() { m_parameters.clear(); }

private:

  mutable OdTCKind m_kind;
  OdAnyArray m_parameters;
  friend class OdAny;

};


#include "TD_PackPop.h"

#endif // _DAI_TYPECODE_H_
