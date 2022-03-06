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

#ifndef _DAI_UNDERLYING_TYPE_H
#define _DAI_UNDERLYING_TYPE_H

#include "daiDictionaryInstance.h"
#include "daiSimpleType.h"
#include "daiAggregationType.h"
#include "daiConstructedType.h"
#include "daiTypeCode.h"
#include "daiBaseType.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{

  class DefinedType;
  typedef OdSmartPtr<DefinedType> DefinedTypePtr;

  class SchemaFiller;

  /** \details 
  Contains declarations of IFC data types, which are represented with an <link OdDAI::UnderlyingType, UnderlyingType> object. 
  \sa 
  <link ifc_data_types, IFC Data Types>
  */
  enum eUnderlyingType {
    /**Simple data type.*/
    kUnderlyingType_SimpleType,
    /**Aggregate data type.*/
    kUnderlyingType_AggregationType,
    /**Defined data type.*/
    kUnderlyingType_DefinedType,
    /**Constructred data type.*/
    kUnderlyingType_ConstructedType,
    /**The unspecified (unset) data type.*/
    kUnderlyingType_unset
  };

  /** \details
  A class that implements storing definitions of IFC underlying data types: 
  * Simple types.
  * Aggregation types.
  * Defined types. 
  * Constructed types.
  \sa 
  <link ifc_overview_data_types, IFC Data Types>.
  */
  class DAI_EXPORT UnderlyingType : public DictionaryInstance
  {
  public:
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(UnderlyingType);
    //DOM-IGNORE-END

    /** \details 
    Creates a new underlying data type definition. 
    \param nestedType [in] A raw pointer to the <link OdDAI::DictionaryInstance, DictionaryInstance> object that contains the nested data type wrapped with the UnderlyingType object to be created.
    \returns A smart pointer to the created instance of the <link OdDAI::UnderlyingType, UnderlyingType> class.
    */
    static OdSmartPtr<UnderlyingType> createObject(const DictionaryInstance *nestedType);
    
    /** \details 
    Creates a new underlying data type definition. 
    \param simpleType [in] A raw pointer to the <link OdDAI::OdSimpleType, OdSimpleType> object that contains the nested data type wrapped with the UnderlyingType object to be created.
    \returns A smart pointer to the created instance of the <link OdDAI::UnderlyingType, UnderlyingType> class.
    */
    static OdSmartPtr<UnderlyingType> createObject(const SimpleType *simpleType);
    
    
    /** \details 
    Creates a new underlying data type definition. 
    \param aggregationType [in] A raw pointer to the <link OdDAI::AggregationType, AggregationType> object that contains the nested data type wrapped with the UnderlyingType object to be created.
    \returns A smart pointer to the created instance of the <link OdDAI::UnderlyingType, UnderlyingType> class.
    */
    static OdSmartPtr<UnderlyingType> createObject(const AggregationType *aggregationType);
    
    /** \details 
    Creates a new underlying data type definition. 
    \param definedType [in] A raw pointer to the <link OdDAI::DefinedType, DefinedType> object that contains the nested data type wrapped with the UnderlyingType object to be created.
    \returns A smart pointer to the created instance of the <link OdDAI::UnderlyingType, UnderlyingType> class.
    */
    static OdSmartPtr<UnderlyingType> createObject(const DefinedType *definedType);
    
    /** \details 
    Creates a new underlying data type definition. 
    \param constructedType [in] A raw pointer to the <link OdDAI::ConstructedType, ConstructedType> object that contains the nested data type wrapped with the UnderlyingType object to be created.
    \returns A smart pointer to the created instance of the <link OdDAI::UnderlyingType, UnderlyingType> class.
    */
    static OdSmartPtr<UnderlyingType> createObject(const ConstructedType *constructedType);

    /** \details 
    Creates a new underlying data type definition with unset nested data type inside. 
    */
    UnderlyingType() : m_determinant(kUnderlyingType_unset) {}
    
    /** \details 
    Retrieves whether the underlying data type is set for the UnderlyingType object.
    \returns true if the underlying data type is specified; otherwise, the method returns false.
    */
    int exists() const { return m_determinant == kUnderlyingType_unset ? 0 : 1; };
    
    /** \details 
    Resets the underlying data type for the object.
    */
    void unset() { m_determinant = kUnderlyingType_unset; };

    /** \details 
    Determines whether the underlying data type is a simple data type.
    \returns true if the underlying data type is a simple data type; otherwise, the method returns false.
    */
    bool isSimpleType() const { return m_determinant == kUnderlyingType_SimpleType; }
    
    /** \details 
    Defines the underlying data type as a simple data type.
    \param simpleType [in] A raw pointer to an <link OdDAI::OdSimpleType, OdSimpleType> object that represents the simple data type definition to be used as the underlying data type.
    */
    void setSimpleType(const SimpleType *simpleType);
    
    /** \details 
    Retrieves the underlying simple data type definition.
    \return A smart pointer to the <link OdDAI::OdSimpleType, OdSimpleType> object that represents the simple data type definition that is used as the underlying data type.
    */
    const SimpleTypePtr simpleType() const;

    /** \details 
    Determines whether the underlying data type is an aggregation data type.
    \returns true if the underlying data type is an aggregation data type; otherwise, the method returns false.
    */
    bool isAggregationType() const { return m_determinant == kUnderlyingType_AggregationType; }
    
    /** \details 
    Defines the underlying data type as an aggregation data type.
    \param aggregationType [in] A raw pointer to an <link OdDAI::AggregationType, AggregationType> object that represents the aggregation data type definition to be used as the underlying data type.
    */
    void setAggregationType(const AggregationType *aggregationType);
    
    /** \details 
    Retrieves the underlying aggregation data type definition.
    \return A smart pointer to the <link OdDAI::AggregationType, AggregationType> object that represents the aggregation data type definition that is used as the underlying data type.
    */
    const AggregationTypePtr aggregationType() const;

    /** \details 
    Determines whether the underlying data type is a defined data type.
    \returns true if the underlying data type is a defined data type; otherwise, the method returns false.
    */
    bool isDefinedType() const { return m_determinant == kUnderlyingType_DefinedType; }

    /** \details 
    Defines the underlying data type as a defined data type.
    \param definedType [in] A raw pointer to an <link OdDAI::DefinedType, DefinedType> object that represents the defined data type definition to be used as the underlying data type.
    */
    void setDefinedType(const DefinedType *definedType);
    
    /** \details 
    Retrieves the underlying defined data type definition.
    \return A smart pointer to the <link OdDAI::DefinedType, DefinedType> object that represents the defined data type definition that is used as the underlying data type.
    */
    const DefinedTypePtr definedType() const;

    /** \details 
    Determines whether the underlying data type is a constructed data type.
    \returns true if the underlying data type is a constructed data type; otherwise, the method returns false.
    */
    bool isConstructedType() const { return m_determinant == kUnderlyingType_ConstructedType; }

    /** \details 
    Defines the underlying data type as a constructed data type.
    \param constructedType [in] A raw pointer to an <link OdDAI::ConstructedType, ConstructedType> object that represents the constructed data type definition to be used as the underlying data type.
    */
    void setConstructedType(const ConstructedType *constructedType);
    
    /** \details 
    Retrieves the underlying constructed data type definition.
    \return A smart pointer to the <link OdDAI::ConstructedType, ConstructedType> object that represents the constructed data type definition that is used as the underlying data type.
    */
    const ConstructedTypePtr constructedType() const;

    /** \details
    Retrieves a type code of the underlying type.
    \returns A smart pointer to <link OdTypeCode, type code> object of the contained type.
    */
    const OdTypeCodePtr type() const;

    /** \details
    Retrieves the definition of the data type contained in the aggregation data type.
    \returns A smart pointer to the <link OdDAI::BaseType, BaseType> object that represents the defintion of the aggregation data type.
    */
    const BaseTypePtr elementType() const;

    /** \details
   Retrieves the domain of the defined data type.
   \returns A smart pointer to the underlying type of the defined type.
   */
    const OdSmartPtr<UnderlyingType> domain() const;

  private:
    //DOM-IGNORE-BEGIN
    eUnderlyingType m_determinant;
    DictionaryInstancePtr m_pType;

    friend class SchemaFiller;
    //DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::UnderlyingType, underlying type> object.
  */
  typedef OdSmartPtr<UnderlyingType> UnderlyingTypePtr;
}

#endif // _DAI_UNDERLYING_TYPE_H
