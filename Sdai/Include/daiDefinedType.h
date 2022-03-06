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

#ifndef _DAI_DEFINED_TYPE_H
#define _DAI_DEFINED_TYPE_H

#include "daiNamedType.h"
#include "daiUnderlyingType.h"
#include "SharedPtr.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class SchemaFiller;

  /** \details
  A class that implements the storing of types established as a result of EXPRESS TYPE declaration.
  \sa 
  <link ifc_overview_data_types, IFC Data Types>.
  */
  class DAI_EXPORT DefinedType : public NamedType
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(DefinedType);
    //DOM-IGNORE-END

    /** \details
    Creates a new defined type with specified parameters.
    \param parentSchema [in] A raw pointer to a schema in which defined type is declared.
    \param name         [in] A name of defined type.
    \param typeCode     [in] A smart pointer to a type code of defined type.
    \param domain       [in] A smart pointer to a underlying type of defined type.
    \returns A smart pointer to the created <link OdDAI::DefinedType, defined type> instance.
    */
    static OdSmartPtr<DefinedType> createObject(
      Schema *parentSchema, 
      const OdAnsiString &name, 
      const OdTypeCodePtr &typeCode = OdTypeCodePtr(), 
      UnderlyingTypePtr domain = UnderlyingTypePtr());

    /** \details
    Creates a new defined type object with default parameters.
    */
    DefinedType()
    {}

    /** \details
    Creates a new defined type object with specified parameters.
    \param parentSchema [in] A raw pointer to a schema in which defined type is declared.
    \param name         [in] A name of the defined type.
    \param typeCode     [in] A smart pointer to a type code of defined type.
    \param domain       [in] A smart pointer to an underlying type of defined type.
    */
    DefinedType(
      Schema *parentSchema, 
      const OdAnsiString &name, 
      const OdTypeCodePtr &typeCode = OdTypeCodePtr(),
      UnderlyingTypePtr domain = UnderlyingTypePtr())
      : NamedType(parentSchema, name)
      , m_domain(domain)
    {
      type(typeCode);
    }

    /** \details
    Retrieves a domain of the defined type.
    \returns A smart pointer to an <link OdDAI::UnderlyingType, underlying type> object associated with the defined type.
    */
    const UnderlyingTypePtr domain() const { return m_domain; };

    /** \details 
    Sets the domain (underlying data type) for the defined type object.
    \param underlyingType [in] A raw pointer to the <link OdDAI::UnderlyingType, underlying data type> object that represents the domain to be set.
    */
    void setDomain(const UnderlyingType *underlyingType);
    
  protected:
    //DOM-IGNORE-BEGIN
    /** A smart pointer to the <link OdDAI::UnderlyingType, underlying data type> object that represents the domain of the defined type.*/
    UnderlyingTypePtr m_domain;

    /** \details 
    Sets the domain (underlying data type) for the defined type object.
    \param domain [in] A smart pointer to the <link OdDAI::UnderlyingType, underlying data type> object that represents the domain to be set.
    */
    void setDomain(UnderlyingTypePtr domain) { m_domain = domain; };

    friend class SchemaFiller;
    //DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::DefinedType, defined type> object.
  */
  typedef OdSmartPtr<DefinedType> DefinedTypePtr;

  /** \details
  A data type that represents a smart pointer to a set of <link OdDAI::DefinedType, defined type> objects.
  */
  typedef OdRxDictionaryPtr DefinedTypeSet;
}

#endif // _DAI_DEFINED_TYPE_H
