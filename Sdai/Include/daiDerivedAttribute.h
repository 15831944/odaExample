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

#ifndef _DAI_DERIVED_ATTRIBUTE_H_
#define _DAI_DERIVED_ATTRIBUTE_H_

#include "daiAttribute.h"
#include "daiBaseType.h"
#include "daiExplicitOrDerived.h"

//DOM-IGNORE-BEGIN
class AST;
//DOM-IGNORE-END

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  /** \details 
  A class that implements the storing and manipulating of attributes.
  */
  class DAI_EXPORT DerivedAttribute : public Attribute
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(DerivedAttribute);
    //DOM-IGNORE-END

    /** \details 
    Creates a new derived attribute definition with a specified name.
    \param name     [in] A pointer to a string that the contains the attribute name.
    \param optional [in] A flag that determines whether the value of the created attribute is optional (equal to true) or mandatory (equal to false).
    \param domain [in] A pointer to data type defenition referenced by the attribute.
    \param redeclaring [in] A pointer to container with defenition of redeclared attribute.
    \returns Returns a smart pointer to the created <link OdDAI::Attribute, attribute> instance.
    */
    static OdSmartPtr<DerivedAttribute> createObject(
      const char *name,
      Entity *parentEntity,
      DictionaryInstance *domain = nullptr,
      ExplicitOrDerived *redeclaring = nullptr);

    /** \details
    Creates a new attribute object with default parameters.
    */
    DerivedAttribute()
    {};

    /** \details
    Destructor.
    */
    ~DerivedAttribute();

    /** \details
    Retrieves data type referenced by the attribute.
    \returns Returns a smart pointer to the data type.
    */
    const BaseTypePtr domain() const { return m_domain; };

    /** \details
    Retrieves defenition of redeclared attribute.
    \returns Returns a smart pointer to the container with defenition of redeclared attribute.
    */
    const ExplicitOrDerivedPtr redeclaring() const { return m_redeclaring; };

    /** \details
    Retrieves the current value of an attribute specified by its name.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns Returns the current value of the attribute.
    \remarks
    The method provides the late binding access to the attribute value by its name.
    Attributes of select and aggregate data types are also supported.
    */
    virtual OdRxValue getAttr(const char * attrName) const ODRX_OVERRIDE;

    /** \details
    Evaluates a nested expression and gets a calculated value.
    */
    OdRxValue evaluate(const ApplicationInstancePtr inst) const;

    /** \details
    Returns an expression of the derived attribute.
    \returns Returns an expression of the derived attribute.
    */
    const OdAnsiString expression() const;

  //DOM-IGNORE-BEGIN

    void setAST(AST *ast);
    AST* getAST() const;

  protected:

    BaseTypePtr m_domain;
    ExplicitOrDerivedPtr m_redeclaring;
    
    AST *m_expression = nullptr;

    void setDomain(const BaseTypePtr &domain) { m_domain = domain; };
    void setRedeclaring(const ExplicitOrDerivedPtr& redeclaring) { m_redeclaring = redeclaring; };

    friend class SchemaFiller;
  //DOM-IGNORE-END
  };
  
  /** \details 
  A data type that represents a smart pointer to an <link OdDAI::Attribute, attribute> object.
  */
  typedef OdSmartPtr<DerivedAttribute> DerivedAttributePtr;

}

#endif // _DAI_DERIVED_ATTRIBUTE_H_
