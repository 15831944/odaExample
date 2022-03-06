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

#ifndef _DAI_LIST_TYPE_H
#define _DAI_LIST_TYPE_H

#include "daiVariableSizeAggregationType.h"
#include "daiIntegerBound.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class SchemaFiller;

  /** \details
  A class that implements the storing and manipulating of list types.
  */
  class DAI_EXPORT ListType : public VariableSizeAggregationType
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(ListType);
    //DOM-IGNORE-END

    /** \details
    Creates a new aggregation type object with specified parameters.
    \param elementType [in] A pointer to a data type contained in the list type.
    \param lowerBound  [in] A smart pointer to lowest valid index for instances of the type.
    \param upperBound  [in] A smart pointer to highest valid index for instances of the type.
    \param unique      [in] A flag that determines whether elements of created list type required (equal to true) or not required (equal to false) to be unique.
    */
    static OdSmartPtr<ListType> createObject(
      const BaseType *elementType,
      const BoundPtr &lowerBound,
      const BoundPtr &upperBound = BoundPtr(),
      bool unique = false);

    /** \details
    Creates a new list type definition with default parameters.
    */
    ListType()
    : m_unique(false)
    {};

    /** \details
    Creates a new aggregation type definition with specified parameters.
    \param elementType [in] A pointer to a data type contained in the list type.
    \param lowerBound  [in] A smart pointer to lowest valid index for instances of the type.
    \param upperBound  [in] A smart pointer to highest valid index for instances of the type.
    \param unique      [in] A flag that determines whether elements of created list type required (equal to true) or not required (equal to false) to be unique.
    */
    ListType(
      const BaseType *elementType,
      const BoundPtr &lowerBound, 
      const BoundPtr &upperBound = BoundPtr(), 
      bool unique = false)
      : VariableSizeAggregationType(
        elementType,
        lowerBound,
        upperBound)
      , m_unique(unique)
    {};

    /** \details
    Determines whether the elements of list type required to be unique.
    \returns Returns true if elements of list type required to be unique; otherwise the method returns false.
    */
    bool unique() const { return m_unique; };

//DOM-IGNORE-BEGIN
  protected:
    bool m_unique;

    void setUnique(bool unique) { m_unique = unique; };

    friend class SchemaFiller;
//DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::ListType, list type> object.
  */
  typedef OdSmartPtr<ListType> ListTypePtr;
}

#endif // _DAI_LIST_TYPE_H
