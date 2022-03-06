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

#ifndef _DAI_ATTRIBUTE_H_
#define _DAI_ATTRIBUTE_H_

#include "daiDictionaryInstance.h"
#include "daiUtils/daiUnset.h"
#include "daiValueTypes.h"
#include "RxValue.h"
#include "SmartPtr.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class Entity;
  class Schema;

  /** \details
  A class that implements the storing and manipulating of attributes.
  */
  class DAI_EXPORT Attribute : public DictionaryInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(Attribute);
    //DOM-IGNORE-END

    /** \details
    Creates a new attribute with a specified name.
    \param name     [in] A pointer to a string that the contains the attribute name.
    \param optional [in] A flag that determines whether the value of the created attribute is optional (equal to true) or mandatory (equal to false).
    \returns Returns a smart pointer to the created <link OdDAI::Attribute, attribute> instance.
    */
    //static OdSmartPtr<Attribute> createObject(const char *name, bool optional = false);

    /** \details
    Creates a new attribute object with default parameters.
    */
    Attribute()
      : m_pParentEntity(NULL)
    {};

    /** \details
    Creates a new attribute object with specified parameters.
    \param name         [in] A pointer to a string that contains the attribute name.
    \param parentEntity [in] A raw pointer to the <link OdDAI::Entity, entity definition> object that the newly created attribute belongs to.
    */
    Attribute(OdAnsiString name, Entity *parentEntity = NULL)
      : m_pParentEntity(parentEntity)
    {
      setNames(name);
    };

    /** \details
    Retrieves the attribute's parent entity definition.
    \returns A raw pointer to the parent <link OdDAI::Entity, entity definition>.
    */
    const Entity* entityDef() const { return m_pParentEntity; };

    /** \details
    Retrieves the current attribute's name.
    \returns An ANSI string that contains the attribute's name.
    */
    const OdAnsiString& name() const { return m_name; };

    /** \details
    Retrieves the current attribute's original name.
    Attribute's original name is exactly a name specified in the source .exp file.
    Unlike the original name, the name is always represented in lower case.
    \returns An ANSI string that contains the attribute's original name.
    */
    const OdAnsiString& originalName() const { return m_originalName; };

    /** \details
    Retrieves the current value of an attribute specified by its name.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns The current value of the attribute.
    \remarks
    The method provides the late binding access to the attribute value by its name.
    Attributes of select and aggregate data types are also supported.
    */
    virtual OdRxValue getAttr(const char * attrName) const ODRX_OVERRIDE;

    //DOM-IGNORE-BEGIN
  protected:

    /** A raw pointer to the parent entity.*/
    Entity *m_pParentEntity;
    
    /** The attribute name (always is represented in lower case). */
    OdAnsiString m_name;
    
    /** The attribute's original name.
    Attribute's original name is exactly a name specified in the source .exp file.*/
    OdAnsiString m_originalName;

    /** \details 
    Sets a new parent entity for the attribute. 
    \param entityDef [in] A raw pointer to the <link OdDAI::Entity, entity definition> object to be set as parent of the attribute.
    */
    void setParentEntity(Entity *entityDef) { m_pParentEntity = entityDef; };

    /** \details 
    Set a new original name and name (in lower case) of the attribute.
    Attribute's original name is exactly a name specified in the source .exp file.
    Unlike the original name, the name is always represented in lower case.
    \param name [in] An ANSI string that contains the new attribute name.
    */
    void setNames(const char* name);

    friend class Entity;
    //DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdDAI::Attribute, attribute> object.
  */
  typedef OdSmartPtr<Attribute> AttributePtr;

  
  /** \details 
  A data type that represents an array of smart pointers to <link OdDAI::Attribute, attribute> objects.
  */
  typedef List<AttributePtr> AttributeSet;

}


#endif // _DAI_ATTRIBUTE_H_
