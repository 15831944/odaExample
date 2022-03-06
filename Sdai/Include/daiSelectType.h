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

#ifndef _DAI_SELECT_TYPE_H
#define _DAI_SELECT_TYPE_H

#include "daiDictionaryInstance.h"
#include "daiNamedType.h"
#include "daiTypeCode.h"
#include "SharedPtr.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class SchemaFiller;

  /** \details
  A class that implements the storing of arbitrary SELECT type meta-data defined within an EXPRESS SCHEMA.
  */
  class DAI_EXPORT SelectType : public DictionaryInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(SelectType);
    //DOM-IGNORE-END

    /** \details
    Creates a new select data type definition.
    \param typeCode   [in] A smart pointer to a <link OdTypeCode, type code> of the select data type.
    \param selections [in] A set of selectable data types.
    \returns A smart pointer to the created <link OdDAI::SelectType, select type> instance.
    */
    static OdSmartPtr<SelectType> createObject(
      const OdTypeCodePtr &typeCode,
      const std::set<const NamedType*> &selections = std::set<const NamedType*>());

    /** \details
    Creates a new select data type definition.
    \param name       [in] A null-terminated string that contans the data type name.
    \param selections [in] A set of selectable data types.
    \returns A smart pointer to the created <link OdDAI::SelectType, select type> instance.
    */
    static OdSmartPtr<SelectType> createObject(
      const char *name,
      const OdArray<const NamedType*> &selections);

    /** \details
    Creates a new select data type object with default parameters.
    */
    SelectType()
    {}

    /** \details
    Creates a new select type object with specified parameters.
    \param typeCode   [in] A smart pointer to a <link OdTypeCode, type code> of select data type.
    \param selections [in] A set of selectable data types.
    */
    SelectType(
      const OdTypeCodePtr &typeCode,
      const std::set<const NamedType*> &selections = std::set<const NamedType*>())
      : m_typeCode(typeCode)
      , m_selections(selections)
    {}

    /** \details
    Retrieves a type code of the Select type.
    \returns A smart pointer to the type code of the Select type.
    */
    virtual const OdTypeCodePtr type() const { return m_typeCode; };

    /** \details
    Retreives the set of selectable data types associated with the select data type.
    \returns An STD set object that contains selectable data types.
    */
    const std::set<const NamedType*>& selections() const { return m_selections; };

  protected:
    //DOM-IGNORE-BEGIN
    /**The <link OdTypeCode, data type code> of the select data type.*/
    OdTypeCodePtr m_typeCode;
    /**An STD set object that contains selectable data types associated with the select data type.*/
    std::set<const NamedType*> m_selections;

    /** \details 
    Sets a new <link OdTypeCode, data type code> for the select data type.
    \param typeCode [in] A smart pointer to the <link OdTypeCode, OdTypeCode> object that contains the data type code to be set.
    */
    void type(const OdTypeCodePtr &typeCode) { m_typeCode = typeCode; };
    /** \details 
    Sets a new set of selectable data types for the select data type.
    \param selections [in] An STD set that contains th selectable data types to be set.
    */
    void setSelections(const std::set<const NamedType*> &selections) { m_selections = selections; };

    friend class SchemaFiller;
    //DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to a <link OdDAI::SelectType, select type> object.
  */
  typedef OdSmartPtr<SelectType> SelectTypePtr;

  /** \details
  A data type that represents an STD set of pointers to <link OdDAI::NamedType, named type> objects.
  */
  typedef std::set<const NamedType*> NamedTypeSet;
}

#endif // _DAI_SELECT_TYPE_H
