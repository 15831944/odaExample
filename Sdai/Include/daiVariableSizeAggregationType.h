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

#ifndef _DAI_VARIABLE_SIZE_AGGREGATION_TYPE_H
#define _DAI_VARIABLE_SIZE_AGGREGATION_TYPE_H

#include "daiAggregationType.h"
#include "daiBaseType.h"
#include "daiBound.h"
#include "daiIntegerBound.h"
#include "SharedPtr.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class SchemaFiller;

  /** \details
  A class that implements the storing and manipulating of variable size aggregation types.
  */
  class DAI_EXPORT VariableSizeAggregationType : public AggregationType
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(VariableSizeAggregationType);
    //DOM-IGNORE-END

    /** \details
    Creates a new variable size aggregation type definition with default parameters.
    */
    VariableSizeAggregationType()
      : m_lowerBound(IntegerBound::createObject(0))
    {};

    /** \details
    Creates a new aggregation type definition with specified parameters.
    \param elementType [in] A smart pointer to a data type contained in the variable size aggregation type.
    \param lowerBound  [in] A smart pointer to minimum number of elements that can be in an instance of the type.
    \param upperBound  [in] A smart pointer to maximum number of elements that can be in an instance of the type.
    */
    VariableSizeAggregationType(
      const BaseTypePtr &elementType,
      const BoundPtr &lowerBound,
      const BoundPtr &upperBound = BoundPtr())
      : AggregationType(elementType)
      , m_lowerBound(lowerBound)
      , m_upperBound(upperBound)
    {};

    /** \details
    Retreives a minimum number of elements that can be in an instance of the type.
    \returns Returns a smart pointer to minimum number of elements that can be in an instance of the type.
    */
    BoundPtr lowerBound() const { return m_lowerBound; };

    /** \details
    Retreives a maximum number of elements that can be in an instance of the type.
    \returns Returns a smart pointer to maximum number of elements that can be in an instance of the type.
    */
    BoundPtr upperBound() const { return m_upperBound; };

//DOM-IGNORE-BEGIN
  protected:
    BoundPtr m_lowerBound;
    BoundPtr m_upperBound;

    void setLowerBound(const BoundPtr &lowerBound) { m_lowerBound = lowerBound; };
    void setUpperBound(const BoundPtr &upperBound) { m_upperBound = upperBound; };

    friend class SchemaFiller;
//DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::VariableSizeAggregationType, variable size aggregation type> object.
  */
  typedef OdSmartPtr<VariableSizeAggregationType> VariableSizeAggregationTypePtr;
}

#endif // _DAI_VARIABLE_SIZE_AGGREGATION_TYPE_H
