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

#ifndef _DAI_SDAI_INSTANCE_H
#define _DAI_SDAI_INSTANCE_H

#include "OdaCommon.h"
#include "daiObjectSDAI.h"

#include "daiBuildOptions.h"

/** \details
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  /** \details
  A base class for <link OdDAI::DictionaryInstance, dictionary instance> and <link OdDAI::SessionInstance, session instance>.
  It contains the base interface for a Standard Data Access Interface instance. 
  */
  class DAI_EXPORT OdSDAIInstance : public OdDAIObjectSDAI
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdSDAIInstance);
    //DOM-IGNORE-END


     /** \details
    Retrieves the model that contains the Standard Data Access Interface (SDAI) instance.
    \returns A raw pointer to the <link OdDAI::Model, owning model>; if the SDAI instance is not appended to any model, the method returns a NULL pointer.
    */
    virtual Model* owningModel() const;

    /** \details
   Retrieves whether the Standard Data Access Interface (SDAI) instance is an instance of a specified type.
   \param entityName [in] An ANSI string that contains the entity's type name.
   \returns true if the SDAI instance is an instance of the specified type; otherwise, the method returns false.
   */
    virtual bool isInstanceOf(const char *entityName) const;

    /** \details
    Retrieves whether the Standard Data Access Interface (SDAI) instance is an instance of a specified EXPRESS type.
    \param entityDef [in] An instance of the <link OdDAI::Entity, Entity> class that represents the entity type.
    \returns true if the SDAI instance is an instance of the specified EXPRESS type; otherwise, the method returns false.
    */
    virtual bool isInstanceOf(const Entity *entityDef) const;

    /** \details
    Retrieves whether the Standard Data Access Interface (SDAI) instance belongs to a certain entity type with a specified name.
    \param entityName [in] An ANSI string that contains the name of entitiy type.
    \returns true if the SDAI instance belongs to the type of entity with the specified name; otherwise, the method returns false.
    */
    virtual bool isKindOf(const char *entityName) const;

    /** \details
    Retrieves whether the Standard Data Access Interface (SDAI) instance belongs to a specified entity type.
    \param entityDef [in]  An instance of the <link OdDAI::Entity, Entity> class that represents the entity type.
    \returns true if the SDAI instance belongs to the specified type; otherwise, the method returns false.
    */
    virtual bool isKindOf(const Entity *entityDef) const;

    /** \details
    Retrieves the type of the Standard Data Access Interface (SDAI) instance.
    \returns A raw pointer to the <link OdDAI::Entity, schema entity definition> of the SDAI instance.
    */
    virtual Entity* getInstanceType() const;

    /** \details
    Retrieves the current value of an attribute specified by its name.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns The current value of the attribute.
    \remarks
    The method provides the late binding access to the attribute value by its name.
    Attributes of select and aggregate data types are also supported.
    */
    virtual OdRxValue getAttr(const char * attrName) const;

    /** \details
   Retrieves whether the attribute value is set or is unset.
   \param attrName [in] An ANSI string that contains the attribute name.
   \returns true if the attribute value is set; otherwise, the method returns false (it means that the attribute value is not set).
   */
    virtual bool testAttr(const char * attrName) const;

    /** \details
    Retrieves whether the attribute value is set or is unset.
    \param attribute [in] A smart pointer to an instance of the <link OdDAI::Attribute, Attribute> class that represents the attribute type.
    \returns true if the attribute has a value; otherwise, the method returns false (it means that the attribute value is not set).
    */
    virtual bool testAttr(const AttributePtr& attribute) const;

  };

}

#endif // _DAI_SDAI_INSTANCE_H
