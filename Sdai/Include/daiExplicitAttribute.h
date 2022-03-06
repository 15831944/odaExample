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

#ifndef _DAI_EXPLICIT_ATTRIBUTE_H_
#define _DAI_EXPLICIT_ATTRIBUTE_H_

#include "daiAttribute.h"
#include "daiBaseType.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class Entity;
  
  /** \details 
  A class that implements the storing and manipulating of attributes.
  */
  class DAI_EXPORT ExplicitAttribute : public Attribute
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(ExplicitAttribute);
    //DOM-IGNORE-END

    /** \details 
    Creates a new explicit attribute definition for entity with a specified name.
    \param name [in] A pointer to a string that the contains the attribute name.
    \param parentEntity [in] A pointer to entity definition that keeps the attribute.
    \param domain [in] A pointer to data type defenition referenced by the attribute. 
    \param optional [in] A flag that determines whether the value of the created attribute is optional (equal to true) or mandatory (equal to false).
    \returns Returns a smart pointer to the created <link OdDAI::ExplicitAttribute, explicit attribute> instance.
    */
    static OdSmartPtr<ExplicitAttribute> createObject(
      const char *name,
      Entity *parentEntity,
      DictionaryInstance *domain = NULL,
      // redeclaring
      bool optional = false);

    /** \details
    Creates a new attribute object with default parameters.
    */
    ExplicitAttribute()
      : m_optional(false)
    {};

    /** \details
    Retrieves data type referenced by the attribute.
    \returns Returns a smart pointer to the data type.
    */
    const BaseTypePtr domain() const { return m_domain; };

    /** \details
    Determines whether the attribute is optional.
    \returns Returns true if the attribute is optional; otherwise the method returns false.
    */
    bool optional() const { return m_optional; };

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
    Retrieves an array of entity definitions which attributes redeclare this explicit attribute.
    \returns Returns an OdArray of raw pointers to OdDAI::Entity.
    */
    const OdArray<const OdDAI::Entity*>& redeclaredIn() const { return m_redeclaredIn; };

    /** \details
    Determines if attribute is redeclared by derived attribute of entity.
    \returns Returns true if attribute redeclared by derived attribute of provided entity, otherwise returns false.
    */
    bool isRedeclaredIn(const OdDAI::Entity *entity) const;

//DOM-IGNORE-BEGIN
  protected:

    bool m_optional;
    BaseTypePtr m_domain;

    OdArray<const OdDAI::Entity*> m_redeclaredIn;

    void setDomain(const BaseTypePtr &domain) { m_domain = domain; }
    void setOptional(bool optional) { m_optional = optional; };

    friend class SchemaFiller;
//DOM-IGNORE-END
  };
  
  /** \details 
  A data type that represents a smart pointer to an <link OdDAI::Attribute, attribute> object.
  */
  typedef OdSmartPtr<ExplicitAttribute> ExplicitAttributePtr;

}

#endif // _DAI_EXPLICIT_ATTRIBUTE_H_
