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

#ifndef _DAI_BASETYPE_H
#define _DAI_BASETYPE_H

#include "daiDictionaryInstance.h"
#include "daiSimpleType.h"
#include "daiNamedType.h"
#include "daiAggregationType.h"
#include "daiTypeCode.h"

#include "daiSelect.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details 
  Contains declarations of IFC data types, which are represented with an <link OdDAI::BaseType, BaseType> object. 
  \sa 
  <link ifc_data_types, IFC Data Types>
  */
  enum eBaseType {
    /**Simple data type.*/
    kBaseType_SimpleType,
    /**Named data type.*/
    kBaseType_NamedType,
    /**Aggregate data type.*/
    kBaseType_AggregationType,
    /**The unspecified (unset) data type.*/
    kBaseType_unset
  };

  /** \details
  A base class that implements the storing and manipulating of data type definitions for attributes.
  */  
  class DAI_EXPORT BaseType : public DictionaryInstance
  {
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(BaseType);
    //DOM-IGNORE-END

  public:

    /** \details 
    Creates an instance of base data type definition with a specified data type inside it. 
    \param nestedType [in] A raw pointer to the <link OdDAI::DictionaryInstance, DictionaryInstance> object that represents the nested data type.
    \returns A smart pointer to the created instance.
    */
    static OdSmartPtr<BaseType> createObject(const DictionaryInstance *nestedType);
    
    /** \details 
    Creates an instance of base data type definition with a simple data type inside it. 
    \param simpleType [in] A raw pointer to the <link OdDAI::OdSimpleType, OdSimpleType> object that represents the nested data type.
    \returns A smart pointer to the created instance.
    */
    static OdSmartPtr<BaseType> createObject(const SimpleType *simpleType);

    /** \details 
    Creates an instance of base data type definition with a named data type inside it. 
    \param namedType [in] A raw pointer to the <link OdDAI::NamedType, NamedType> object that represents the nested data type.
    \returns A smart pointer to the created instance.
    */
    static OdSmartPtr<BaseType> createObject(const NamedType *namedType);
    
    /** \details 
    Creates an instance of base data type definition with an aggregation data type inside it. 
    \param aggregationType [in] A raw pointer to the <link OdDAI::AggregationType, AggregationType> object that represents the nested data type.
    \returns A smart pointer to the created instance.
    */
    static OdSmartPtr<BaseType> createObject(const AggregationType *aggregationType);

    /** \details 
    Creates an instance of base data type definition with default parameters. 
    The nested data type for the created object is unset.
    */
    BaseType() : m_determinant(kBaseType_unset) {}
    
    /** \details 
    Checks whether the nested data type is specified within the base type instance. 
    \returns 1 if the nested data type is specified; otherwise (nested data type is unset), the method returns 0.
    */
    int exists() const { return m_determinant == kBaseType_unset ? 0 : 1; };
    
    /** \details 
    Clears the nested data type. The nested data type is unset after the method is executed.
    */
    void unset() { m_determinant = kBaseType_unset; };

    /** \details 
    Determines whether the nested data type is a simple data type.
    \returns true if the nested data type is a simple data type; otherwise, the method returns false.
    */
    bool isSimpleType() const { return m_determinant == kBaseType_SimpleType; }
    
    /** \details 
    Sets the nested data type as a simple data type.
    \param simpleType [in] A raw pointer to an <link OdDAI::OdSimpleType, OdSimpleType> object that represents the simple data type definition to be used as the nested data type.
    */
    void setSimpleType(const SimpleType *simpleType);
    
    /** \details 
    Retrieves the nested simple data type definition.
    \return A smart pointer to the <link OdDAI::OdSimpleType, OdSimpleType> object that represents the simple data type definition that is used as the nested data type.
    */
    const SimpleType* simpleType() const;

    /** \details 
    Determines whether the nested data type is a named data type.
    \returns true if the nested data type is a named data type; otherwise, the method returns false.
    */
    bool isNamedType() const { return m_determinant == kBaseType_NamedType; }
    
    /** \details 
    Sets the nested data type as a named data type.
    \param namedType [in] A raw pointer to an <link OdDAI::NamedType, NamedType> object that represents the named data type definition to be used as the nested data type.
    */
    void setNamedType(const NamedType *namedType);
    
    /** \details 
    Retrieves the nested named data type definition.
    \return A smart pointer to the <link OdDAI::NamedType, NamedType> object that represents the named data type definition that is used as the nested data type.
    */
    const NamedType* namedType() const;

    /** \details 
    Determines whether the nested data type is an aggregation data type.
    \returns true if the nested data type is an aggregation data type; otherwise, the method returns false.
    */
    bool isAggregationType() const { return m_determinant == kBaseType_AggregationType; }
    
    /** \details 
    Sets the nested data type as an aggregation data type.
    \param aggregationType [in] A raw pointer to an <link OdDAI::AggregationType, AggregationType> object that represents the aggregation data type definition to be used as the nested data type.
    */
    void setAggregationType(const AggregationType *aggregationType);
    
    /** \details 
    Retrieves the nested aggregation data type definition.
    \return A smart pointer to the <link OdDAI::AggregationType, AggregationType> object that represents the aggregation data type definition that is used as the nested data type.
    */
    const AggregationType* aggregationType() const;

    /** \details
    Retrieves a type code of the nested type.
    \returns A smart pointer to <link OdTypeCode, type code> object of the contained type.
    */
    const OdTypeCodePtr type() const;

  private:

    eBaseType m_determinant;
    const DictionaryInstance *m_pType;
  };
  
  /** \details
  A data type that represents a smart pointer to a <link OdDAI::BaseType, BaseType> object.
  */
  typedef OdSmartPtr<BaseType> BaseTypePtr;

}

#endif // _DAI_BASETYPE_H
