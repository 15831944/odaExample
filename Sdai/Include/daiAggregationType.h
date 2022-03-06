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

#ifndef _DAI_AGGREGATIONTYPE_H
#define _DAI_AGGREGATIONTYPE_H

#include "daiDictionaryInstance.h"
#include "daiTypeCode.h"
#include "daiBaseType.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class SchemaFiller;
  class BaseType;
  typedef OdSmartPtr<BaseType> BaseTypePtr;

  class AggrInstance;
  typedef OdSharedPtr<AggrInstance> AggrInstancePtr;

  /** \details
  A class that implements the storing and manipulating of aggregation types.
  */
  class DAI_EXPORT AggregationType : public DictionaryInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(AggregationType);
    //DOM-IGNORE-END

    /** \details
    Creates a new aggregation type definition with default parameters.
    */
    AggregationType();

    /** \details 
    Destroys the aggregation type definition object.
    */
    ~AggregationType();

    /** \details
    Creates a new aggregation type definition with a specified data type of its element.
    \param elementType [in] A smart pointer to a data type contained in the aggregation type.
    */
    AggregationType(const BaseTypePtr &elementType)
      : m_elementType(elementType)
    {};

    /** \details
    Retrieves the code of the aggregate data type.
    \returns A smart pointer to the <link OdTypeCode, type code> object of the aggregate data type.
    */
    virtual const OdTypeCodePtr type() const { return m_typeCode; };
    
    /** \details
    Sets a new type code for the aggregation data type.
    \param typeCode [in] A type code for the aggregation data type to be set.
    */
    void type(const OdTypeCodePtr &typeCode) { m_typeCode = typeCode; };

    /** \details
    Retrieves the data type of an aggregation element.
    \returns A smart pointer to the <link OdDAI::BaseType, BaseType> object that represents the definition of the aggregation data type.
    */
    const BaseTypePtr elementType() const { return m_elementType; };

    const AggrInstance* getCachedAggrInstance();
    void setCachedAggrInstance(AggrInstancePtr& aggregateInstance);

//DOM-IGNORE-BEGIN
  protected:
    void setElementType(const BaseTypePtr &elementType);

    friend class SchemaFiller;

    OdTypeCodePtr m_typeCode;
    BaseTypePtr m_elementType;

    AggrInstancePtr m_defaultInstance;

//DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::AggregationType, aggregation type> object.
  */
  typedef OdSmartPtr<AggregationType> AggregationTypePtr;

  /** \details
  A data type that represents an STD map of pairs consisting of an STD string and a smart pointer to an <link OdDAI::AggregationType, aggregation type> object.
  */
  typedef std::map<std::string, AggregationTypePtr> AggregationTypeDictionary;
}

#endif // 
