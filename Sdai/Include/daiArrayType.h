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

#ifndef _DAI_ARRAY_TYPE_H
#define _DAI_ARRAY_TYPE_H

#include "daiAggregationType.h"
#include "daiBaseType.h"
#include "daiBound.h"
#include "SharedPtr.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class SchemaFiller;

  /** \details
  A class that implements the storing and manipulating of array types.
  */
  class DAI_EXPORT ArrayType : public AggregationType
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(ArrayType);
    //DOM-IGNORE-END

    /** \details
    Creates a new aggregation type object with specified parameters.
    \param elementType [in] A pointer to a data type contained in the array type.
    \param lowerBound  [in] A smart pointer to lowest valid index for instances of the type.
    \param upperBound  [in] A smart pointer to highest valid index for instances of the type.
    \param unique      [in] A flag that determines whether elements of created array type required (equal to true) or not required (equal to false) to be unique.
    \param optional    [in] A flag that determines whether all elements of created array type required (equal to true) or not required (equal to false) to have determinate values.
    */
    static OdSmartPtr<ArrayType> createObject(
      const BaseType *elementType,
      const BoundPtr &lowerBound,
      const BoundPtr &upperBound,
      bool unique,
      bool optional
    );

    /** \details
    Creates a new array type definition with default parameters.
    */
    ArrayType()
      : m_unique(false)
      , m_optional(false)
    {};

    /** \details
    Creates a new aggregation type definition with specified parameters.
    \param elementType [in] A pointer to a data type contained in the array type.
    \param lowerBound  [in] A smart pointer to lowest valid index for instances of the type.
    \param upperBound  [in] A smart pointer to highest valid index for instances of the type.
    \param unique      [in] A flag that determines whether elements of created array type required (equal to true) or not required (equal to false) to be unique.
    \param optional    [in] A flag that determines whether elements of created array type required (equal to true) or not required (equal to false) to have determinate values.
    */
    ArrayType(
      const BaseType *elementType,
      const BoundPtr &lowerBound,
      const BoundPtr &upperBound,
      bool unique,
      bool optional)
      : AggregationType(elementType)
      , m_lowerBound(lowerBound)
      , m_upperBound(upperBound)
      , m_unique(unique)
      , m_optional(optional)
    {};

    /** \details
    Retreives a lowest valid index for instances of the type.
    \returns Returns a smart pointer to lowest valid index for instances of the type.
    */
    BoundPtr lowerBound() const { return m_lowerBound; };

    /** \details
    Retreives a highest valid index for instances of the type.
    \returns Returns a smart pointer to highest valid index for instances of the type.
    */
    BoundPtr upperBound() const { return m_upperBound; };

    /** \details
    Determines whether the elements of array type required to be unique.
    \returns Returns true if elements of array type required to be unique; otherwise the method returns false.
    */
    bool unique() const { return m_unique; };

    /** \details
    Determines whether the elements of array type required to have determinate values.
    \returns Returns true if elements of array type required to have determinate values; otherwise the method returns false.
    */
    bool optional() const { return m_optional; };

//DOM-IGNORE-BEGIN
  protected:
    BoundPtr m_lowerBound;
    BoundPtr m_upperBound;
    bool m_unique;
    bool m_optional;

    void setLowerBound(const BoundPtr &lowerBound) { m_lowerBound = lowerBound; };
    void setUpperBound(const BoundPtr &upperBound) { m_upperBound = upperBound; };
    void setUnique(bool unique) { m_unique = unique; }
    void setOptional(bool optional) { m_optional = optional; }

    friend class SchemaFiller;
//DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::ArrayType, array type> object.
  */
  typedef OdSmartPtr<ArrayType> ArrayTypePtr;
}

#endif // _DAI_ARRAY_TYPE_H
