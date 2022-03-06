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

#ifndef _DAI_INVERSE_ATTRIBUTE_H_
#define _DAI_INVERSE_ATTRIBUTE_H_

#include "daiAttribute.h"
#include "daiConsts.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {
  
  class ExplicitAttribute;

  /** \details 
  A class that implements the storing and manipulating of attributes.
  */
  class DAI_EXPORT InverseAttribute : public Attribute
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(InverseAttribute);
    //DOM-IGNORE-END

    /** \details
    Creates a new attribute object with default parameters.
    */
    InverseAttribute()
      : m_domain(NULL),
        m_invertedAttr(NULL),
        m_minCardinality(Consts::OdIntUnset),
        m_maxCardinality(Consts::OdIntUnset),
        m_duplicates(false)
    {};

    /** \details
    Creates a new inverse attribute definition for an entity with a specified name.
    \param name [in] A pointer to a string that contains the attribute name.
    \param parentEntity [in] A pointer to entity definition that keeps the attribute.
    \param domain [in] A pointer to referencing entity definition of the attribute.
    \param invertedAttr [in] A pointer to attribute definition in the referencing entity type whose relationship is being inverted.
    \param minCardinality [in] A minimum number of references from the inverted attribute.
    \param maxCardinality [in] A maximum number of references from the inverted attribute.
    \param duplicates [in] A flag that determines whether the value of the created attribute may contain duplicates (equal to true) or may not contain duplicates (equal to false).
    \returns Returns a smart pointer to the created <link OdDAI::InverseAttribute, inverse attribute> instance.
    */
    static OdSmartPtr<InverseAttribute> createObject(
      const char *name,
      Entity *parentEntity,
      const Entity *domain,
      // redeclaring
      const ExplicitAttribute *invertedAttr,
      int minCardinality = Consts::OdIntUnset,
      int maxCardinality = Consts::OdIntUnset,
      bool duplicates = false
    );

    /** \details
    Retrieves referencing entity type of the attribute.
    \returns A raw pointer to the entity type.
    */
    const Entity* domain() const { return m_domain; };

    /** \details
    Retrieves attribute in the referencing entity type whose relationship is being inverted.
    \returns A raw pointer to an <link OdDAI::ExplicitAttribute, explicit attribute>.
    */
    const ExplicitAttribute* invertedAttr() const { return m_invertedAttr; };

    /** \details
    Retrieves the minimum number of references from the inverted attribute.
    \returns An unsigned integer value that contains the minimum number of references.
    */
    int minCardinality() const { return m_minCardinality; };

    /** \details
    Retrieves the maximum number of references from the inverted attribute.
    \returns An unsigned integer value that contains the maximum number of references.
    */
    int maxCardinality() const { return m_maxCardinality; };

    /** \details
    Determines whether the attribute may contain duplicates of references from the inverted attribute.
    \returns true if the attribute may contain duplicates; otherwise, the method returns false.
    */
    bool duplicates() const { return m_duplicates; };

    /** \details
    Retrieves the current value of an attribute specified by its name.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns The current value of the attribute.
    \remarks
    The method provides the late binding access to the attribute value by its name.
    Attributes of select and aggregate data types are also supported.
    */
    virtual OdRxValue getAttr(const char * attrName) const ODRX_OVERRIDE;

    /** \details
    Determines whether the attribute is represented with a set or a bag or with a single reference.
    \returns true if the attribute is represented with a set or a bag; false if the attribute is represented with a single reference.
    */
    bool isAggregate() const { return m_minCardinality != Consts::OdIntUnset; };

  //DOM-IGNORE-BEGIN
  protected:
      const Entity *m_domain;
      const ExplicitAttribute *m_invertedAttr;
      int m_minCardinality;
      int m_maxCardinality;
      bool m_duplicates;

      void setDomain(const Entity *domain) { m_domain = domain; };
      void setInvertedAttr(const ExplicitAttribute *invertedAttr) { m_invertedAttr = invertedAttr; };
      void setMinCardinality(int minCardinality) { m_minCardinality = minCardinality; };
      void setMaxCardinality(int maxCardinality) { m_maxCardinality = maxCardinality; };
      void setDuplicates(bool duplicates) { m_duplicates = duplicates; };

      friend class SchemaFiller;
  //DOM-IGNORE-END
  };
  
  /** \details 
  A data type that represents a smart pointer to an <link OdDAI::Attribute, attribute> object.
  */
  typedef OdSmartPtr<InverseAttribute> InverseAttributePtr;

}

#endif // _DAI_INVERSE_ATTRIBUTE_H_
