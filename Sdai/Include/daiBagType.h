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

#ifndef _DAI_BAG_TYPE_H
#define _DAI_BAG_TYPE_H

#include "daiVariableSizeAggregationType.h"
#include "SharedPtr.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class SchemaFiller;

  /** \details
  A class that implements the storing and manipulating of bag types.
  */
  class DAI_EXPORT BagType : public VariableSizeAggregationType
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(BagType);
    //DOM-IGNORE-END

    /** \details
    Creates a new aggregation type object with specified parameters.
    \param elementType [in] A pointer to a data type contained in the bag type.
    \param lowerBound  [in] A smart pointer to lowest valid index for instances of the type.
    \param upperBound  [in] A smart pointer to highest valid index for instances of the type.
    */
    static OdSmartPtr<BagType> createObject(
      const BaseType *elementType,
      const BoundPtr &lowerBound,
      const BoundPtr &upperBound = BoundPtr());

    /** \details
    Creates a new bag type definition with default parameters.
    */
    BagType() {};

    /** \details
    Creates a new aggregation type definition with specified parameters.
    \param elementType [in] A pointer to a data type contained in the bag type.
    \param lowerBound  [in] A smart pointer to lowest valid index for instances of the type.
    \param upperBound  [in] A smart pointer to highest valid index for instances of the type.
    */
    BagType(
      const BaseType *elementType,
      const BoundPtr& lowerBound,
      const BoundPtr& upperBound = BoundPtr())
      : VariableSizeAggregationType(
        elementType,
        lowerBound,
        upperBound)
    {};

    //DOM-IGNORE-BEGIN
    friend class SchemaFiller;
    //DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::BagType, bag type> object.
  */
  typedef OdSmartPtr<BagType> BagTypePtr;
}

#endif // _DAI_BAG_TYPE_H
