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

#ifndef _DAI_ENTITY_H_
#define _DAI_ENTITY_H_

#include "daiNamedType.h"
#include "daiDerivedAttribute.h"
#include "daiExplicitAttribute.h"
#include "daiInverseAttribute.h"
#include "daiAttribute/AttributeKeyCollection.h"

#define STL_USING_MAP
#include "OdaSTL.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class Schema;

  /** \details
  A class that provides an entity definition within a schema.
  */
  class DAI_EXPORT Entity : public NamedType
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(Entity);
    //DOM-IGNORE-END

  protected:
    /** \details
    Creates a new entity definition with default parameters.
    */
    Entity();

    /** \details
    Creates a new entity definition with specified parameters.
    \param name         [in] A new entity definition name.
    \param instantiable [in] A flag that defines whether the entity can be instantiated (equal to true) or not (equal to false). 
    */
    Entity(OdAnsiString name, bool instantiable);

  public:
//DOM-IGNORE-BEGIN
    /**\details 
    Creates a new entity definition with a specified name and schema. 
    \param owningSchema [in] Schema in which entity definition is declared.
    \param entityName   [in] An entity definition name.
    \param instantiable [in] A flag that defines whether the entity can be instantiated (equal to true) or not (equal to false). 
    \param thisClassDef [out] A raw pointer to the <link OdDAI::Entity, Entity> object that represents the entity definition.
    \param pBaseClass   [in] A raw pointer to the entity base class definition.
    \returns A smart pointer to the created entity.
    */
    static OdSmartPtr<Entity> createObject(
      Schema* owningSchema,
      const char *entityName,
      bool instantiable,
      Entity* &thisClassDef,
      const Entity* pBaseClass = NULL);

    /**\details
    Creates a new entity definition with a specified owning schema, name instantiable values.
    \param owningSchema [in] Schema in which entity definition is declared.
    \param entityName   [in] An entity definition name.
    \param instantiable [in] A flag that defines whether the entity can be instantiated (equal to true) or not (equal to false).
    \returns A smart pointer to the created entity.
    */
    static OdSmartPtr<Entity> createObject(
      Schema* owner,
      const char* entityName,
      bool instantiable,
      bool complex = false);
//DOM-IGNORE-END

    /** \details
    Retrieves the current list of attribute definitions for the entity definition.
    \returns The array of attribute definitions. 
    \remarks 
    The attributes definitions of the superclass entity definition are not included in the resulting array.
    */
    const AttributeSet& attributes() const
    {
      return m_attributes;
    };

    /** \details
    Retrieves the current list of the entity definition's supertypes.
    \returns An STD list of the entity definition's supertypes.
    */
    const List<Entity*>& supertypes() const
    {
      return m_supertypes;
    };


    /** \details
    Check whether the entity is a supertype of another entity.
    \param subtype [in] An entity subtype to check.
    \returns true if the object is a supertype of the specified entity type; otherwise, the method returns false. 
    */
    bool isSupertypeOf(const Entity* subtype) const;


    /** \details
    Retrieves whether the entity definition can be instantiated or not.
    \returns true if the entity definition can be instantiated; otherwise, the method returns false.
    */
    Boolean instantiable() const {
      return m_instantiable;
    };

    /** \details
    Retrieves whether the entity definition is complex or not.
    \returns true if the entity definition is complex; otherwise, the method returns false.
    */
    Boolean complex() const {
      return m_complex;
    };

    /** \details 
    Appends a new attribute definition to the entity definition.
    \param attributeDef [in] A smart pointer to an attribute definition to be added.
    */
    void appendAttribute(AttributePtr attributeDef)
    {
      attributeDef->setParentEntity(this);
      m_attributes.putByIndex(m_attributes.getMemberCount(), attributeDef);
    }

    /** \details 
    Appends a new supertype to the entity definition.
    \param supertype [in] A raw pointer to an entity definition that defines the new supertype to be appended.
    */
    void appendSuperType(Entity* supertype);

    /** \details
    Retrieves the current value of an attribute specified by its name.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns The current value of the attribute represented with an <exref target="https://docs.opendesign.com/tkernel/OdRxValue.html">OdRxValue</exref> object.
    \remarks
    The method provides the late binding access to the attribute value by its name.
    Attributes of select and aggregate data types are also supported.
    */
    virtual OdRxValue getAttr(const char * attrName) const;

    /** \details
    Collects all explicit attributes which are references or aggregations of
    references for the type and all its supertypes.
    \returns An array of pointers to ExplicitAttribute instances whose domain is other Entity for the entity definition and all its supertypes.
    */
    const OdArray<OdDAI::ExplicitAttribute*>& referenceAttributes() const;

    /** \details
    Collects all inverse attributes of the type and all its supertypes.
    \returns An array of pointers to InverseAttribute instances for the entity definition and all its supertypes.
    */
    const OdArray<OdDAI::InverseAttribute*>& inverseAttributes() const;

    /** \details
    Collects all explicit attributes of the type and all its supertypes.
    \returns An array of pointers to ExplicitAttribute instances for the entity definition and all its supertypes.
    */
    const OdArray<OdDAI::ExplicitAttribute*>& explicitAttributes() const;

    /** \details
    Searches for an attribute definition with a specified name for the entity definition and all its supertypes.
    \param attrName [in] An ANSI string that contains the name of the attribute to find.
    \returns A smart pointer to the found attribute definition; if the attribute is not found then a NULL smart pointer is returned.
    \remarks 
    The search of the attribute is performed starting from the most base entity definition towards its subtypes 
    (to this entity definition).
    */
    const AttributePtr findAttribute(const char *attrName) const;

    /** \details
    Searches for an attribute definition with a specified name for the entity definition and all its supertypes. The search proceeds in reversed order.
    \param attrName [in] An ANSI string that contains the name of the attribute to find.
    \returns A smart pointer to the found attribute definition; if the attribute is not found then a NULL smart pointer is returned.
    \remarks 
    The search of an attribute is performed starting from this entity definition towards its supertypes.
    */
    const AttributePtr rfindAttribute(const char *attrName) const;

    /** \details
    For entity definition and all its supertypes tries to recursively find WR Rule instance with name ruleName.
    Stops searching on first occurrence of rule with name provided.
    \param ruleName [in] An ANSI string that contains the name of the rule to find.
    \returns A smart pointer to OdDAI::WhereRule.
    */
    OdDAI::WhereRulePtr findWhereRule(const char *ruleName) const;

  //DOM-IGNORE-BEGIN
    const AttributeKeyCollection* attributeKeyCollection(KeyCollectionEntityType type) const;

  protected:

    enum StateFlags
    {
      kInverseCalculated = 1 << 0,
      kReferenceCalculated = 1 << 1,
      kExplicitCalculated = 1 << 2,
    };

  private:

    AttributeSet  m_attributes;
    List<Entity*> m_supertypes;
    Boolean       m_instantiable;
    Boolean       m_complex;

    //Boolean m_independent;

    mutable OdUInt32 m_stateFlags = 0;

    // Lazy inverse attributes set calculation
    mutable OdArray<OdDAI::InverseAttribute*> m_inverseAttributes;

    // Lazy reference attributes calculation
    mutable OdArray<OdDAI::ExplicitAttribute*> m_referenceAttributes;

    // Lazy explicit attributes calculation
    mutable OdArray<OdDAI::ExplicitAttribute*> m_explicitAttributes;

    using AttributeKeyCollectionUniquePtr = std::unique_ptr<OdDAI::AttributeKeyCollection>;

    // Dynamic attributes container
    mutable AttributeKeyCollectionUniquePtr m_attributeKeyCollectionCache[entityTypesCount];

    friend class SchemaFiller;
//DOM-IGNORE-END

  };

  /** \details 
  A data type that represents a smart pointer to an <link OdDAI::Entity, Entity> object.
  */
  typedef OdSmartPtr<Entity> EntityPtr;
  
  /** \details 
  A data type that represents a smart pointer to a set of <link OdDAI::Entity, Entity> objects.
  */
  typedef OdRxDictionaryPtr EntitySet;
  
  /** \details 
  A data type that represents an STD list of smart pointers to <link OdDAI::Entity, entity> objects.
  */
  typedef std::list<EntityPtr > EntityList;

}

#endif // _DAI_ENTITY_H_
