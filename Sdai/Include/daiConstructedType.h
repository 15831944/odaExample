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

#ifndef _DAI_CONSTRUCTED_TYPE_H
#define _DAI_CONSTRUCTED_TYPE_H

#include "daiDictionaryInstance.h"
#include "daiEnumerationType.h"
#include "daiSelectType.h"
#include "daiTypeCode.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI
{
  /** \details 
  Contains declarations of IFC data types, which are represented with an <link OdDAI::ConstructedType, ConstructedType> object. 
  \sa 
  <link ifc_data_types, IFC Data Types>
  */
  enum eConstructedType {
    /**Enumeration data type.*/
    kConstructedType_EnumerationType,
    /**Select data type.*/
    kConstructedType_SelectType,
    /**The unspecified (unset) data type.*/
    kConstructedType_unset
  };

  /** \details
  Container for enumeration type or select type.
  */
  /** \details
  A base class that implements the storing and manipulating of enumeration and select data types definitions.
  */  
  class DAI_EXPORT ConstructedType : public DictionaryInstance
  {
  public:
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(ConstructedType);
    //DOM-IGNORE-END

    /** \details 
    Creates an instance of constructed data type definition with a specified data type inside it. 
    \param nestedType [in] A raw pointer to the <link OdDAI::DictionaryInstance, DictionaryInstance> object that represents the nested data type.
    \returns A smart pointer to the created instance.
    */
    static OdSmartPtr<ConstructedType> createObject(DictionaryInstance *nestedType);
    
    /** \details 
    Creates an instance of constructed data type definition with an enumeration data type inside it. 
    \param enumerationType [in] A raw pointer to the <link OdDAI::EnumerationType, EnumerationType> object that represents the nested data type.
    \returns A smart pointer to the created instance.
    */
    static OdSmartPtr<ConstructedType> createObject(EnumerationType *enumerationType);
    
    /** \details 
    Creates an instance of constructed data type definition with a select data type inside it. 
    \param selectType [in] A raw pointer to the <link OdDAI::SelectType, SelectType> object that represents the nested data type.
    \returns A smart pointer to the created instance.
    */
    static OdSmartPtr<ConstructedType> createObject(SelectType *selectType);

    /** \details 
    Creates an instance of constructed data type definition with default parameters. 
    The nested data type for the created object is unset.
    */
    ConstructedType() : m_determinant(kConstructedType_unset) {}
    
    /** \details 
    Checks whether the nested data type is specified within the constructed type instance. 
    \returns 1 if the nested data type is specified; otherwise (nested data type is unset), the method returns 0.
    */    
    int exists() const { return m_determinant == kConstructedType_unset ? 0 : 1; };
    
    /** \details 
    Clears the nested data type. The nested data type is unset after the method is executed.
    */
    void unset() { m_determinant = kConstructedType_unset; };

    /** \details 
    Determines whether the nested data type is an enumeration data type.
    \returns true if the nested data type is an enumeration data type; otherwise, the method returns false.
    */
    bool isEnumerationType() const { return m_determinant == kConstructedType_EnumerationType; }
    
    /** \details 
    Sets the nested data type as an enumeration data type.
    \param enumerationType [in] A raw pointer to an <link OdDAI::EnumerationType, EnumerationType> object that represents the enumeration data type definition to be used as the nested data type.
    */
    void setEnumerationType(EnumerationType *enumerationType);
    
    /** \details 
    Retrieves the nested enumeration data type definition.
    \return A smart pointer to the <link OdDAI::EnumerationType, EnumerationType> object that represents the enumeration data type definition that is used as the nested data type.
    */
    const EnumerationTypePtr enumerationType() const;

    /** \details 
    Determines whether the nested data type is a select data type.
    \returns true if the nested data type is a select data type; otherwise, the method returns false.
    */
    bool isSelectType() const { return m_determinant == kConstructedType_SelectType; }
    
    /** \details 
    Sets the nested data type as a select data type.
    \param selectType [in] A raw pointer to an <link OdDAI::SelectType, SelectType> object that represents the select data type definition to be used as the nested data type.
    */
    void setSelectType(SelectType *selectType);
    
    /** \details 
    Retrieves the nested select data type definition.
    \return A smart pointer to the <link OdDAI::SelectType, SelectType> object that represents the select data type definition that is used as the nested data type.
    */
    const SelectTypePtr selectType() const;

    /** \details
    Retreives a list of values for an enumeration data type.
    \returns A list of <exref target="https://docs.opendesign.com/tkernel/OdAnsiString.html">ANSI-strings</exref> that contains values of the enumeration data type.
    */
    const OdDAI::OdAnsiStringList& elements() const;

    /** \details
    Retreives a set of selectable data types.
    \returns An STD set of selectable data types (<link OdDAI::NamedType, named types>).
    */
    const std::set<const NamedType*>& selections() const;

    /** \details
    Retrieves a type code of the nested type.
    \returns A smart pointer to <link OdTypeCode, type code> object of the contained type.
    */
    const OdTypeCodePtr type() const;

  private:
    //DOM-IGNORE-BEGIN
    eConstructedType m_determinant;
    DictionaryInstancePtr m_pType;
    //DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to a <link OdDAI::ConstructedType, constructed data type> object.
  */
  typedef OdSmartPtr<ConstructedType> ConstructedTypePtr;
}

#endif // _DAI_CONSTRUCTED_TYPE_H
