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

#ifndef _DAI_OBJECT_SDAI_H_
#define _DAI_OBJECT_SDAI_H_

#include "OdaCommon.h"
#include "Gi/GiDrawable.h"
#include "RxObjectImpl.h"
#include "RxValue.h"

#include "daiBuildOptions.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {

  class Model;
  class Entity;

  class Attribute;
  
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::Attribute, Attribute object>.
  */
  typedef OdSmartPtr<Attribute> AttributePtr;

  /** \details
  The base class for dictionary and application instances that can be manipulated with the Data Access Interface (DAI).
  */
  class DAI_EXPORT OdDAIObjectSDAI : public OdGiDrawable
  {
  public:
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdDAIObjectSDAI);
    //DOM-IGNORE-END

     /** \details
    Retrieves the <link OdDAI::Model, model object> that contains the Standard Data Access Interface (SDAI) object.
    \returns A raw pointer to the <link OdDAI::Model, owning model>; if the SDAI object is not appended to any model, the method returns a NULL pointer.
    */
    virtual Model* owningModel() const = 0;

    /** \details
    Retrieves whether the Standard Data Access Interface (SDAI) object is an instance of a specified instance type. 
    The instance type is specified with its name.
    \param entityName [in] An ANSI string that contains the entity's type name.
    \returns true if the SDAI object is an instance of the specified type; otherwise, the method returns false.
   */
    virtual bool isInstanceOf(const char *entityName) const = 0;

    /** \details
    Retrieves whether the Standard Data Access Interface (SDAI) object is an instance of a specified EXPRESS type.
    \param entityDef [in] An instance of the <link OdDAI::Entity, Entity> class that represents the entity type.
    \returns true if the SDAI object is an instance of the specified EXPRESS type; otherwise, the method returns false.
    */
    virtual bool isInstanceOf(const Entity *entityDef) const = 0;

    /** \details
    Retrieves whether the Standard Data Access Interface (SDAI) object belongs to a certain entity type with a specified name.
    \param entityName [in] A name of entities type.
    \returns true if the SDAI object belongs to the type of entity with the specified name; otherwise, the method returns false.
    */
    virtual bool isKindOf(const char *entityName) const = 0;

    /** \details
    Retrieves whether the Standard Data Access Interface (SDAI) object belongs to a specified entity type.
    \param entityDef [in]  An instance of the <link OdDAI::Entity, Entity> class that represents the entity type.
    \returns true if the SDAI object belongs to the specified type; otherwise, the method returns false.
    */
    virtual bool isKindOf(const Entity *entityDef) const = 0;

    /** \details
    Retrieves the type of the Standard Data Access Interface (SDAI) object.
    \returns A raw pointer to the <link OdDAI::Entity, schema entity definition> of the SDAI object.
    */
    virtual Entity* getInstanceType() const = 0;

    /** \details
    Retrieves the current value of the attribute specified by its name.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns The current value of the attribute.
    \remarks
    The method provides the late binding access to the attribute value by its name.
    Attributes of select and aggregate data types are also supported.
    The method is case sensitive for the attribute name. 
    For case-insensitive search of the attribute value, use the <link OdDAI::OdDAIObjectSDAI::getAttrCaseInsensitive@char *@const, getAttrCaseInsensitive()> method.
    */
    virtual OdRxValue getAttr(const char * attrName) const = 0;

    /** \details
    Retrieves the current value of an attribute specified by its name in case-insensitive mode.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns The current value of the attribute.
    \remarks
    The method provides the late binding access to the attribute value by its name.
    Attributes of select and aggregate data types are also supported.
    For case-sensitive search of the attribute value, use the <link OdDAI::OdDAIObjectSDAI::getAttr@char *@const, getAttr()> method.
    */
    OdRxValue getAttrCaseInsensitive(const char * attrName) const;

    /** \details
    Retrieves whether the attribute value is set or is unset.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns true if the attribute's value is set; otherwise, the method returns false (it means that the attribute's value is not set).
    */
    virtual bool testAttr(const char * attrName) const = 0;

    /** \details
    Retrieves whether the attribute value is set or is unset.
    \param attribute [in] A smart pointer to an <link OdDAI::Attribute, Attribute> object that represents the attribute's type.
    \returns true if the attribute's value is set; otherwise, the method returns false (it means that the attribute's value is not set).
    */
    virtual bool testAttr(const AttributePtr& attribute) const = 0;

    /** \details
    Retrieves whether the attribute value is set or is unset. 
    The specified attribute name is case-insensitive.
    \param attrName [in] An ANSI string that contains the attribute's name.
    \returns true if the attribute's value is set; otherwise, the method returns false (it means that the attribute's value is not set).
    */
    bool testAttrCaseInsensitive(const char * attrName) const;

    /** \details
    Retrieves whether the Standard Data Access Interface (SDAI) object is a persistent one.
    \returns true if the SDAI object is a persistent one; otherwise, the method returns false.
    \remarks
    Persistent objects are database-resident objects (i.e. they are stored in a database).
    */
    virtual bool isPersistent() const { return id ()!= NULL; }

    /** \details
    Retrieves the database object identifier of the Standard Data Access Interface (SDAI) object.
    \returns The SDAI object's database identifier.
    \remarks
    The method returns a NULL pointer if the SDAI object is not persistent (i.e. not stored in a database).
    */
    virtual OdDbStub* id() const { return NULL; };

    /** \details
    Sets a new Gs node cache for the Standard Data Access Interface (SDAI) object.
    \param pGsNode [in] A raw pointer to an <exref target="https://docs.opendesign.com/tv/OdGsCache.html">OdGsCache</exref> object.
    */
    virtual void setGsNode(OdGsCache* pGsNode) { throw OdError(eNotImplemented); };

    /** \details
    Retrieves the current Gs node object of the Standard Data Access Interface (SDAI) object.
    \returns A raw pointer to the <exref target="https://docs.opendesign.com/tv/OdGsCache.html">OdGsCache</exref> object associated with the SDAI object.
    */
    virtual OdGsCache* gsNode() const { throw OdError(eNotImplemented); };

    //DOM-IGNORE-BEGIN
  protected:

    /** \details 
    Sets the values of the Standard Data Access Interface (SDAI) object's subentity traits, and returns the object's subentity traits to the calling subroutine. 
    \param traits [in] A raw pointer to the <exref  target="https://docs.opendesign.com/tv/OdGiDrawableTraits.html">OdGiDrawableTraits</exref> object to be set. 
    \returns A set of flags represented with an unsigned 32-bit integer value.
    \remarks
    When re-implementing this method, use the &quot;or&quot; bit operation (|) for the return value of the parent class' subSetAttributes() method and any flags you have added. 
    \sa 
    <exref target="https://docs.opendesign.com/tv/OdGiDrawableTraits.html">OdGiDrawableTraits</exref> class documentation.
    */
    virtual OdUInt32 subSetAttributes(OdGiDrawableTraits * traits) const { throw OdError(eNotImplemented); };
    
    /**\details 
    Draws the graphical representation of the Standard Data Access Interface (SDAI) object that is independent of any viewport contexts.
    \param wd [in] A raw pointer to the <exref  target="https://docs.opendesign.com/tv/OdGiDrawable.html">OdGiDrawable</exref> object that encapsulates parameters of view port independent vectorization.  
    \returns true if the drawing was successful; otherwise, the method returns false.
    */
    virtual bool subWorldDraw(OdGiWorldDraw * wd) const { throw OdError(eNotImplemented); };
    
    /** \details 
    Draws the Standard Data Access Interface (SDAI) object that is dependent on the viewport context.
    \param vd [in] A raw pointer to the object that encapsulates parameters of viewport-dependent vectorization.
    \remarks 
    The default implementation is empty.
    */
    virtual void subViewportDraw(OdGiViewportDraw * vd) const {};

    //DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to a <link OdDAI::OdDAIObjectSDAI, SDAI object>.
  */
  typedef OdSmartPtr<OdDAIObjectSDAI> OdDAIObjectSDAIPtr;

}

#endif // _DAI_OBJECT_SDAI_H_
