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

#ifndef _DAI_APPLICATION_INSTANCE_H_
#define _DAI_APPLICATION_INSTANCE_H_

#include "daiObjectId.h"
#include "daiObjectSDAI.h"
#include "daiRTTI.h"
#include "daiAttribute/AttributeCollection.h"

/** \details 
Implements the Data Access Interface (DAI) that provides functionality for manipulating data that is defined within the EXPRESS SCHEMA format.
*/
namespace OdDAI {
  
  class OdSpfFilerBase;
  class InverseAttributeCalculator;

  class ApplicationInstance;
  
  /** \details
  A data type that represents a smart pointer to an <link OdDAI::ApplicationInstance, application instance> object.
  */
  typedef OdSmartPtr<ApplicationInstance> ApplicationInstancePtr;

  class ExplicitAttribute;

  /** \details
  The base class for application instances that can be manipulated with the Data Access Interface (DAI).
  */
  class DAI_EXPORT ApplicationInstance : public OdDAIObjectSDAI
  {
  public:
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(ApplicationInstance);
    //DOM-IGNORE-END

    /**\details 
    Creates a new application instance with default parameters.
    */
    ApplicationInstance() : m_id(NULL) {};

    /** \details
    Retrieves the model that contains the application instance.
    \returns A raw pointer to the owning model; if the application instance is not appended to any model, the method returns a NULL pointer.
    */
    virtual Model* owningModel() const;

    /** \details
    Reads values of the instance's explicit attribute fields from a file buffer that is associated with a specified filer object.
    \param rdFiler [in] A raw pointer to the filer object associated with the file buffer to read data from.
    \returns eOk if the attribute field values are successfully read; otherwise, the method returns an appropriate error.
    \remarks 
    The method's default implementation returns the eNotImplemented value.
    */
    virtual OdResult inFields(OdSpfFilerBase *rdFiler) { return eNotImplemented; };

    /** \details
    Writes values of the instance's explicit attribute fields to a file buffer that is assigned to a specified filer object.
    \param wrFiler [in] A raw pointer to the filer object assigned with the file buffer to write data to.
    \returns eOk if the attribute field values are successfully written; otherwise, the method returns an appropriate error.
    \remarks 
    The method's default implementation returns the eNotImplemented value.
    */
    virtual OdResult outFields(OdSpfFilerBase *wrFiler) { return eNotImplemented; };

    /** \details
    Retrieves whether the application instance is an instance of an instance type with a specified name.
    \param entityName [in] An entity's type name.
    \returns true if the application instance is an instance of the specified type; otherwise, the method returns false.
    */
    virtual bool isInstanceOf(const char *entityName) const;

    /** \details
    Retrieves whether the application instance is an instance of a specified EXPRESS type.
    \param entityDef [in] An instance of the <link OdDAI::Entity, Entity> class that represents the entity type.
    \returns true if the application instance is an instance of the specified EXPRESS type; otherwise, the method returns false.
    */
    virtual bool isInstanceOf(const Entity *entityDef) const;

    /** \details
    Retrieves whether the application instance belongs to or is derived from a certain entity type with a specified name.
    \param entityName [in] A name of entities type.
    \returns true if the application instance belongs to or is derived from the type of entity with the specified name; otherwise, the method returns false.
    */
    virtual bool isKindOf(const char *entityName) const;

    /** \details
    Retrieves whether the application instance belongs to or is derived from a specified entity type.
    \param entityDef [in]  An instance of the <link OdDAI::Entity, Entity> class that represents the entity type.
    \returns true if the application instance belongs to or is derived from the specified type; otherwise, the method returns false.
    */
    virtual bool isKindOf(const Entity *entityDef) const;

    /** \details
    Sets inverse attributes to related application instances.
    */
    virtual void setInverseCounterParts();

    /** \details
    Removes inverse attributes from related application instances.
    */
    virtual void resetInverseCounterParts();

    /** \details 
    Retrieves the current value of an inverse attribute with a specified name.
    \param attrName [in] A null-terminated string that contains the inverse attribute's name.
    \returns 
    An <exref target="https://docs.opendesign.com/tkernel/OdRxValue.html">OdRxValue</exref> object that contains the inverse attribute value.
    */
    OdRxValue getInverseAttr(const char* attrName) const;

    /** \details 
    Cleans dynamic attributes.
    */
    void cleanDynamicAttributes();

    /** \details
    Retrieves the type name of the application instance.
    \returns An ANSI string that contains the type name.
    */
    const OdAnsiString& typeName() const;

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
    \returns true if the attribute has a value; otherwise, the method returns false (it means that the attribute value is not set).
    */
    virtual bool testAttr(const char * attrName) const;

    /** \details
    Retrieves whether the attribute value is set or is unset.
    \param attribute [in] an attribute type.
    \returns true if the attribute has a value; otherwise, the method returns false (it means that the attribute value is not set).
    */
    virtual bool testAttr(const AttributePtr& attribute) const;

    /** \details
    Sets a new value of an attribute that is specified by its name.
    \param explicitAttrName [in] An ANSI string that contains the attribute name.
    \param val              [in] A new attribute value to be set.
    \returns true if the attribute value was successfully set; otherwise, the method returns false.
    */
    virtual bool putAttr(const char* explicitAttrName, const OdRxValue& val);

    /** \details
   Sets a new value of an attribute that is specified by its name in the case insensitive mode.
   \param explicitAttrName [in] An ANSI string that contains the attribute name.
   \param val              [in] A new attribute value to be set.
   \returns true if the attribute value was successfully set; otherwise, the method returns false.
   */
    bool putAttrCaseInsensitive(const char * explicitAttrName, const OdRxValue &val);

    /** \details
    Checks whether the value of a specified attribute is set.
    \param explicitAttrName [in] A null-terminated ANSI string that contains the attribute name.
    \returns true if the attribute has a value; otherwise, the method returns false (it means that the attribute value is not set).
    */
    void unsetAttrCaseInsensitive(const char * explicitAttrName);

    /** \details
    Clears the attribute value.
    \param explicitAttrName [in] An ANSI string that contains the attribute name.
    */
    virtual void unsetAttr(const char * explicitAttrName);

    /** \details
    Clears the attribute value.
    \param attribute [in] attribute to unset.
    */
    void unsetAttr(const AttributePtr& attribute);

    /** \details
    Retrieves the database object identifier of the application instance.
    \returns The application instance's database identifier represented with a raw pointer to an OdDbStub object.
    \remarks
    The method returns a NULL pointer if the application instance is not persistent (i.e. not stored in a database).
    */
    virtual OdDbStub* id() const { return m_id; };

    /** \details
    Compares the application instance object with another object.
    \param pOther [in]  A raw pointer to the object to be compared.
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdRx__Ordering.html">OdRx::Ordering</exref> value that represents the result of the comparison operation.
    \remarks
    This method returns one of the following:
    <table>
    Name             Value    Description
    _kLessThan_      -1       This object < Other Object.
    _kEqual_          0       This object = Other Object.
    _kGreaterThan_    1       This object > Other Object.
    _kNotOrderable_   2       This class is not orderable.
    </table>
    The default implementation of this method returns _kNotOrderable_.
    \sa
    * <exref target="https://docs.opendesign.com/tkernel/rx_object_compare_moreless.html">Comparing the Value of Rx Objects</exref>.
    * <exref target="https://docs.opendesign.com/tkernel/rx_object_compare.html">Comparing Rx-Objects</exref>
    */
    OdRx::Ordering comparedTo(const OdRxObject* pOther) const override;

    /** \details
    Compares the application instance object with another object by comparing their inverse attributes.
    \param pOther [in]  A raw pointer to the object to be compared.
    \returns An <exref target="https://docs.opendesign.com/tkernel/OdRx__Ordering.html">OdRx::Ordering</exref> value that represents the result of the comparison operation.
    \remarks
    This method returns one of the following:
    <table>
    Name             Value    Description
    _kLessThan_      -1       This object < Other Object.
    _kEqual_          0       This object = Other Object.
    _kGreaterThan_    1       This object > Other Object.
    _kNotOrderable_   2       This class is not orderable.
    </table>
    */
    OdRx::Ordering comparedToInverse(const OdRxObject* pOther) const;

    /** details
    Copies the contents of the specified object into this object.
    \param pSource [in] Pointer to the source object.
    \remarks
    The default implementation of this function does nothing but throws the eNotApplicable exception.    */
    virtual void copyFrom(const OdRxObject* pSource);


    /** \details
    Checks whether the instance has unset mandatory attributes and retrieves the list of such attributes.
    \param unsetAttrs [out] An array of pointers to ExplicitAttribute instances which are unset for the application instance.
    \returns 
    true if all mandatory attributes of an instance are set; the method returns false if at least one mandatory attribute of an instance is unset.
    */
    bool validateRequiredExplicitAttrsAssigned(OdArray<OdDAI::ExplicitAttribute*> &unsetAttrs) const;

    /** \details
    Checks whether the instance has inverse attributes with violated size constraints and retrieves the list of such attributes.
    \param aggr [out] An array of pointers to InverseAttribute instances which have violated size constraints for the application instance.
    \returns
    true if all inverse attributes constraints are satisfied or if the instance has no inverse attributes; otherwise, the method returns false.
    */
    bool validateInverseAttrs(OdArray<OdDAI::InverseAttribute*>& aggr) const;

    /** \details
    Checks the constraint (Where-Rule) for the application instance. The constraint (Where-Rule) is defined within the application entity definition or within a parent application entity definition.
    \param ruleName [in] A null-terminated string that contains the name of the constraint (Where-Rule) to be validated.
    \returns 
    * true if the constraint is satisfied.
    * false if the constraint is violated.
    * unknown if the constraint is not defined or can not be evaluated for any reason (an EXPRESS error, incorrectly filled data, mandatory data is unset, etc.).
    */
    Logical validateWhereRule(const char *ruleName) const;

    /** \details
    Checks the constraint (Where-Rule) for the application instance. The constraint (Where-Rule) is defined within the application entity definition or within a parent application entity definition.
    \param ruleDef [in] A raw pointer to the constraint (Where-Rule) object.
    \returns 
    * true if the constraint is satisfied.
    * false if the constraint is violated.
    * unknown if the constraint is not defined or can not be evaluated for any reason (an EXPRESS error, incorrectly filled data, mandatory data is unset, etc.).
    */
    Logical validateWhereRule(const WhereRule *ruleDef) const;

    /** \details
    Checks whether the instance has aggregate attributes violating size constraints and retrieves the list of such attributes.
    \param aggr [out] An array of pointers to Attribute instances which are violating size constarints for the application instance.
    \returns True if validation is satisfied, false if constraint is violated, and Unknown if expression
    evaluation value is unknown or indeterminate.
    */
    Logical validateAggrSize(OdArray<OdDAI::Attribute*>& aggr) const;

    /** \details
   Checks whether the instance has string attributes with incorrect width and retrieves the list of such attributes.
   \param aggr [out] An array of pointers to Attribute instances which have incorrect width for the application instance.
   \returns True if all attribute string values are of correct width, false if width constraint is violated, and Unknown if expression
   evaluation value is unknown or indeterminate.
   */
    Logical validateStringWidth(OdArray<OdDAI::Attribute*>& aggr) const;

    /** \details
    Calculates a value of a derived attribute specified by its name.
    \param attrName [in] An ANSI string that contains the derived attribute name.
    \returns Returns the calculated value of the attribute.
    \remarks
    The method provides the late binding access to the derived attribute value
    by its name.
    */
    OdRxValue getDerivedAttr(const char *attrName) const;

    /** \details
    Retrieves the identifiers of the Named/Defined data types of entity instances 
    of which the specified entity instance is a member according to the schema 
    types hierarchy.

    \param resultList [in/out] Identifier of the pre-existing NPL to which the
    Named/Defined type instance identifiers for those instances are added
    meeting the specified criteria.    
    \returns Identifier of the result NPL.
    */
    OdDAI::NonPersistentList* findDataTypes(OdDAI::NonPersistentList* resultList);

    /** \details
    Retrieves the identifiers of the attributes of entity instances referencing
    the curent entity instance.

    \param resultList [in/out] Identifier of the pre-existing NPL to which the
    attribute identifiers of the entity instances referencing the current instance 
    are added.
    \returns Identifier of the result NPL.
    */
    OdDAI::NonPersistentList* findRolesOf(OdDAI::NonPersistentList* resultList);

    /** \details
    Retrieves the identifiers of all the entity instances in the model
    that reference the current entity instance.

    \param resultList [in/out]  Identifier of the pre-existing NPL to which the 
    identifiers of the entity instances referencing the current instance by any 
    attribute are added.
    \returns Identifier of the result NPL.
    */
    OdDAI::NonPersistentList* findUsers(OdDAI::NonPersistentList* resultList);

    /** \details
    Retrieves the identifiers of all the entity instances in the model data
    that reference the curent entity instance by the specified attribute name.

    \param roleName [in] A string that contains a fully qualified attribute name, i.e.
    ifcplacement.location.
    \param resultList [in/out]  Identifier of the pre-existing NPL to which the
    identifiers of the entity instances referencing the current instance by
    the specified attribute name are added.
    \returns Identifier of the result NPL.
    */
    OdDAI::NonPersistentList* findUsedInBN(const OdAnsiString& roleName, OdDAI::NonPersistentList* resultList);

    /** \details
    Retrieves the identifiers of all the entity instances in the model data
    that reference the curent entity instance by the specified attribute.

    \param role [in] Identifier of the attribute as the role being requested.
    \param resultList [in/out]  Identifier of the pre-existing NPL to which the 
    identifiers of the entity instances referencing the current instance by
    the specified attribute are added.
    \returns Identifier of the result NPL.
    */
    OdDAI::NonPersistentList* findUsedIn(const OdDAI::Attribute& role, OdDAI::NonPersistentList* resultList);

//DOM-IGNORE-BEGIN

  protected:
    virtual OdRx::Ordering comparedToLateImpl(const ApplicationInstance* otherInstance) const ;
    virtual bool comparedToEarlyImpl(const ApplicationInstance* otherInstance, OdRx::Ordering&  result) const;
    virtual void copyFromLateImpl(const OdDAI::ApplicationInstance* otherInstance);
    virtual bool copyFromEarlyImpl(const OdDAI::ApplicationInstance* otherInstance);

    virtual const OdDAI::AttributeKeyCollection* getDynamicAttributesKeyData() const;

    template<class TType>
    inline TType* getInverseAttr(const char* attrName);

    bool putInverseAttr(const char* explicitAttrName, const OdRxValue& val);
    void resetInverseAttributes(OdDAI::ApplicationInstancePtr &referencedInstance, const OdDAI::ExplicitAttributePtr &explicitAttribute);

    /** \details
    Evaluates an expression to retrieve derived attribute value.
    \param derivedAttribute [in] A raw pointer to the derived attribute instance to be returned.
    \returns The value of the attribute represented with an <exref target="https://docs.opendesign.com/tkernel/OdRxValue.html">OdRxValue</exref> object.
    */
    OdRxValue getDerivedAttr(OdDAI::DerivedAttribute* derivedAttribute) const;

    /** \details
    Retrieves inverse or derived attribute value by its name.
    \param attrName [in] A null-terminated ANSI string that contains the attribute name.
    \returns The value of the attribute represented with an <exref target="https://docs.opendesign.com/tkernel/OdRxValue.html">OdRxValue</exref> object.
    */
    OdRxValue getDynamicAttr(const char *attrName) const;
    
    Logical validateAggrSizeRec(const OdDAI::ApplicationInstance* pInstance, const OdDAI::Entity* pEntity, OdArray<OdDAI::Attribute*>& aggr) const;
    Logical validateStringWidthRec(const OdDAI::ApplicationInstance* pInstance, const OdDAI::Entity* pEntity, OdArray<OdDAI::Attribute*>& aggr) const; 
    void processAttributeValue(OdRxValue& idInstance, const OdDAIObjectId& idCurrent, const OdDAI::Entity* pEntity, const OdDAI::ExplicitAttribute* pAttribute) const;

  protected:
    OdDbStub *m_id;
    mutable DynamicAttributeHolder  m_dynamicAttributes;

    friend class FilerBase;
    friend class ModelContents;
    friend class OdSpfFilerBase;
    friend class Pager;
    friend class InverseAttributeCalculator;
//DOM-IGNORE-END
  };
  
  /** \details 
  A template function that retrieves an inverse attribute with a specified name.
  \param attrName [in] A null-terminated ANSI string that contains the attribute name.
  \returns A raw pointer to the inverse attribute.
  */
  template<class TType>
  TType* ApplicationInstance::getInverseAttr(const char* attrName)
  {
    auto dynamicAttributesData = getDynamicAttributesKeyData();

    if (dynamicAttributesData)
    {
      return m_dynamicAttributes.getTypedAttr<TType>(attrName, *dynamicAttributesData, true);
    }
    return nullptr;
  }

}

#endif // _DAI_APPLICATION_INSTANCE_H_
