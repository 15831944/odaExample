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

#ifndef _DAI_NAMEDTYPE_H
#define _DAI_NAMEDTYPE_H

#include "daiRules/daiWhereRule.h"
#include "daiAggr/daiList.h"
#include "daiTypeCode.h"
#include "daiValueTypes.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class Schema;

  /** \details
  A class that implements the storing of the definition of a named type.
  */
  class DAI_EXPORT NamedType : public DictionaryInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(NamedType);
    //DOM-IGNORE-END

    // TODO: Class should be virtual finally

    /** \details
    Creates a new named type object with default parameters.
    */
    NamedType()
      : m_parentSchema(NULL)
    {}

    /** \details
    Creates a new named type with specified parameters.
    \param parentSchema [in] A raw pointer to a schema that contains the type declaration and definition.
    \param name          [in] A name of the named type.
    */
    NamedType(Schema *parentSchema, const OdAnsiString &name)
      : m_parentSchema(parentSchema)
    {
      setNames(name);
    }

    /** \details
    Retrieves the owner schema of the named type definition.
    \returns A raw pointer to the owner schema of the named type definition.
    */
    Schema*  parentSchema() const { return m_parentSchema; }

    /** \details
    Retrieves the name of the named type definition.
    The name is always represented in the lower case.
    \returns An ANSI string that contains the name of the named type definition.
    */
    const OdAnsiString& name() const { return m_name; };

    /** \details
    Retrieves the original name of the named type definition.
    The original name is exactly the name that was defined within the .exp file.
    Unlike the original name, the name is always represented in lower case.
    \returns An ANSI string that contains the original name of the named type definition.
    */
    const OdAnsiString& originalName() const { return m_originalName; };

    /** \details
    Retrieves a type code of the named type.
    \returns A smart pointer to named type's type code.
    */
    virtual const OdTypeCodePtr& type() const;

    /** \details
    Sets the type code for the named type.
    \param typeCode [in] A smart pointer to the type code object to be set.
    */
    void type(const OdTypeCodePtr& typeCode);

    /** \details
    Retrieves the current value of the attribute specified by its name.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns The current value of the attribute.
    \remarks
    The method provides the late binding access to the attribute value by its name.
    Attributes of select and aggregate data types are also supported.
    */
    virtual OdRxValue getAttr(const char * attrName) const;

    /** \details
    Retrieves the list of Where Rules associated with the named type.
    \returns A list of pointers to associated Where Rule objects.
    */
    const WhereRuleList& whereRules() const { return m_whereRules; };

    //DOM-IGNORE-BEGIN
    /** \details
    Appends a new Where Rule to the named type.
    \param ruleDef [in] A raw pointer to the rule definition.
    */
    void appendWhereRule(WhereRule *ruleDef);

  protected:
    
    /** \details 
    Sets a name for the named data type.
    \param name [in] An ANSI string that contains the name to be set.
    */
    void setName(const char *name) { m_name = name; m_name.makeLower(); };

    /** \details 
    Sets names (original name and name) for the named data type.
    The original name is exactly the name that was defined within the .exp file.
    Unlike the original name, the name is always represented in lower case.
    \param name [in] An ANSI string that contains names to be set.
    */
    void setNames(const char* name);

    /** The name of the data type (always is represented in lower case).*/
    OdAnsiString        m_name;
    
    /** The original name of the data type.*/
    OdAnsiString        m_originalName;
    
    /** A raw pointer to the schema object that contains the definition of the named data type.*/
    Schema*             m_parentSchema;
    
    /** The list of Where rules associated with the named data type.*/
    WhereRuleList       m_whereRules;
    
    /** A smart pointer to the type code.*/
    OdTypeCodePtr       m_typeCode;

    friend class SchemaFiller;
    //DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::NamedType, named type> object.
  */
  typedef OdSmartPtr<NamedType> NamedTypePtr;

  /** \details
  A data type that represents an STD map of pairs consisting of STD string and a smart pointer to <link OdDAI::NamedType, named type>.
  */
  typedef std::map<std::string, NamedTypePtr> NamedTypeDictionary;
}

#endif // _DAI_NAMEDTYPE_H
