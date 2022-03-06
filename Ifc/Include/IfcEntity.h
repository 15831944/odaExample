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

#ifndef _IFC_ENTITY_H_
#define _IFC_ENTITY_H_

#include "IfcCommon.h"
#include "IfcBuildOptions.h"
#include "IfcEntityTypes.h"
#include "IfcAttributesEnum.h"
#include "daiApplicationInstance.h"
#include "daiEntity.h"

#include "Ge/GePoint2d.h"
#include "Ge/GePoint3d.h"
#include "Ge/GeVector2d.h"
#include "Ge/GeVector3d.h"
#include "Ge/GeMatrix2d.h"
#include "Ge/GeMatrix3d.h"
#include "CmColorBase.h"

/** \details 
Contains declarations related to working with IFC files content.
*/
namespace OdIfc {

  /** \details 
  Types of results of IFC file operations.
  */
  enum IfcOpResult
  {
    /**Unresolved operation.*/
    kUnresolved = 0, 
    /**No appropriate compound object exists for the entity instance.*/
    kResVisited = 1, 
    /**The entity is composed as an <exref target="https://docs.opendesign.com/tkernel/OdGePoint2d.html">OdGePoint2d</exref> object.*/
    kResPoint2d, 
    /**The entity is composed as an <exref target="https://docs.opendesign.com/tkernel/OdGePoint3d.html">OdGePoint3d</exref> object.*/
    kResPoint3d, 
    /**The entity is composed as an <exref target="https://docs.opendesign.com/tkernel/OdGeVector2d.html">OdGeVector2d</exref> object.*/
    kResVector2d, 
    /**The entity is composed as an <exref target="https://docs.opendesign.com/tkernel/OdGeVector3d.html">OdGeVector3d</exref> object.*/
    kResVector3d, 
    /**The entity is composed as an <exref target="https://docs.opendesign.com/tkernel/OdGeMatrix2d.html">OdGeMatrix2d</exref> object.*/
    kResMatrix2d, 
    /**The entity is composed as an <exref target="https://docs.opendesign.com/tkernel/OdGeMatrix3d.html">OdGeMatrix3d</exref> object.*/
    kResMatrix3d, 
    /**The entity is composed as an RGB color value.*/
    kRgbColor, 
    /**The entity has an attached compound object.*/
    kResCompound, 
    /**An error occurred during the compose operation.*/
    kResError 
  };

  class OdIfcCompound;

  /** \details 
  A data type that represents a smart pointer to an <link OdIfc::OdIfcCompound, OdIfcCompound> object.
  */
  typedef OdSmartPtr<OdIfcCompound> OdIfcCompoundPtr;

  /** \details
  A class that represents an entity instance of an IFC file and provides IFC-specific functionality.
  */
  class IFCCORE_EXPORT OdIfcEntity : public OdDAI::ApplicationInstance
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdIfcEntity);
    //DOM-IGNORE-END

    /** \details 
    Creates a new entity object with default parameters.
    */
    OdIfcEntity();
    
    /** \details 
    Destroys the entity object.
    \remarks 
    All attached compound objects are deleted as well.
    */
    ~OdIfcEntity();

    /**  \details
    Retrieves whether the entity belongs to a specified entity type.
    \param entityType [in] An entity type.
    \returns true if the entity belongs to the specified type; otherwise, the method returns false.
    */
    virtual bool isKindOf(OdIfcEntityType entityType) const;

    /** \details
    Retrieves whether the entity is an instance of a specified type.
    \param entityType [in] An instance of the <link OdIfc::OdIfcEntityType, OdIfcEntityType> enumeration that represents the entity type.
    \returns true if the entity is an instance of the specified type; otherwise, the method returns false.
    */
    bool isInstanceOf(OdIfcEntityType entityType) const;

    /** \details
    Retrieves the current type of the entity.
    \returns A value of the <link OdIfc::OdIfcEntityType, OdIfcEntityType> enumeration that represents the current entity's type.
    */
    virtual OdIfcEntityType type() const;
    
    /** \details
    Retrieves the current value of an attribute specified by its name.
    \param attrName [in] An ANSI string that contains the attribute name.
    \returns The current value of the attribute.
    \remarks 
    The method provides late binding access to the attribute value by its name. 
    Attributes of select and aggregate data types are also supported.
    */
    using OdDAI::ApplicationInstance::getAttr;

    /** \details
    Retrieves the current value of an attribute specified by its definition.
    \param attrDef [in] A value of the <link OdIfc::OdIfcAttribute, OdIfcAttribute> enumeration that represents the attribute definition.
    \returns The current value of the attribute.
    \remarks 
    The method provides late binding access to the attribute value by its name. 
    Attributes of select and aggregate data types are also supported.
    */
    virtual OdRxValue getAttr(const OdIfcAttribute attrDef) const;

    /** \details
    Retrieves whether the attribute value is set or is unset.
    \param explicitAttrName [in] An ANSI string that contains the attribute name.
    \returns true if the attribute has a value; otherwise, the method returns false (the attribute value is not set).
    */
    virtual bool testAttr(const char * explicitAttrName) const;

    /** \details
    Retrieves whether the attribute value is set or is unset.
    \param explicitAttrDef [in] An <link OdIfc::OdIfcAttribute, OdIfcAttribute> enumeration that represents the attribute definition.
    \returns true if the attribute has a value; otherwise, the method returns false (the attribute value is not set).
    */
    virtual bool testAttr(const OdIfcAttribute explicitAttrDef) const;

    /** \details
    Clears the attribute value. 
    \param explicitAttrName [in] An ANSI string that contains the attribute name.
    */
    virtual void unsetAttr(const char * explicitAttrName);

    /** \details
    Clears the attribute value.
    \param explicitAttrDef [in] An <link OdIfc::OdIfcAttribute, OdIfcAttribute> enumeration that represents the attribute definition.
    */
    virtual void unsetAttr(const OdIfcAttribute explicitAttrDef);

    /** \details
    Sets a new value of an attribute that is specified by its name.
    \param explicitAttrName [in] An ANSI string that contains the attribute name.
    \param val              [in] A new attribute value to be set.
    \returns true if the attribute value was successfully set; otherwise, the method returns false.
    */
    virtual bool putAttr(const char * explicitAttrName, const OdRxValue &val);

    /** \details
    Sets a new value of a specified attribute.
    \param explicitAttrDef [in] An <link OdIfc::OdIfcAttribute, OdIfcAttribute> enumeration that represents the attribute definition.
    \param val             [in] A new attribute value to be set.
    \returns true if the attribute value was successfully set; otherwise, the method returns false.
    */
    virtual bool putAttr(const OdIfcAttribute explicitAttrDef, const OdRxValue &val);

    /** \details 
    Retrieves whether the entity is resolved into a compound object, into a Ge compound object, or is unresolved/visited.
    \returns A value of the <link OdIfc::IfcOpResult, IfcOpResult> enumeration that contains the result of the entity resolution.
    */
    IfcOpResult resolved() { return m_resolved; };

    /** \details 
    Resolves the entity and returns the result of the entity composition to a calling subroutine.
    \param resolved [in]  A resolution operation result.
    \param resPtr   [out] A raw pointer that references the entity composition result value.
    */
    void resolve(IfcOpResult resolved, void *resPtr)
    {
      ODA_ASSERT_ONCE(
        ((resolved == kUnresolved || resolved == kResVisited) && !resPtr)
          || resPtr);
      m_resolved = resolved;
      m_resPtr = resPtr;
    };

    /** \details
   Unresolves the entity.
   */
    void unresolve();

    /** \details 
    Returns the result of the entity resolution represented as a three-dimensional point.
    \param pEnt [in] A smart pointer to an entity to be resolved.
    \returns A raw pointer to an instance of the <exref target="https://docs.opendesign.com/tkernel/OdGePoint3d.html">OdGePoint3d</exref> class.
    \remarks 
    The method returns a valid raw pointer to the <exref target="https://docs.opendesign.com/tkernel/OdGePoint3d.html">OdGePoint3d</exref> object 
    if the resolution result is equal to the <link OdIfc::IfcOpResult::kResPoint3d, kResPoint3d> 
    or the <link OdIfc::IfcOpResult::kResPoint2d, kResPoint2d>; otherwise, the method returns a NULL pointer.
    */
    static const OdGePoint3d* asPoint3d(const OdIfcEntity *pEnt) {
      if (pEnt->m_resolved == kResPoint3d || pEnt->m_resolved == kResPoint2d)
        return reinterpret_cast<OdGePoint3d*>(pEnt->m_resPtr);
      ODA_ASSERT(0);
      return nullptr;
    };

    /** \details
    Returns the result of the entity resolution represented as a two-dimensional point.
    \param pEnt [in] A smart pointer to an entity to be resolved.
    \returns A raw pointer to an instance of the <exref target="https://docs.opendesign.com/tkernel/OdGePoint2d.html">OdGePoint2d</exref> class.
    \remarks 
    The method returns a valid raw pointer to the <exref target="https://docs.opendesign.com/tkernel/OdGePoint2d.html">OdGePoint2d</exref> object 
    if the resolution result is equal to <link OdIfc::IfcOpResult::kResPoint3d, kResPoint3d> 
    or <link OdIfc::IfcOpResult::kResPoint2d, kResPoint2d>; otherwise, the method returns a NULL pointer.
    */
    static const OdGePoint2d* asPoint2d(const OdIfcEntity *pEnt) {
      if (pEnt->m_resolved == kResPoint2d || pEnt->m_resolved == kResPoint3d)
        return reinterpret_cast<OdGePoint2d*>(pEnt->m_resPtr);
      ODA_ASSERT(0);
      return nullptr;
    };

    /** \details
    Returns the result of the entity resolution represented as a three-dimensional vector.
    \param pEnt [in] A smart pointer to an entity to be resolved.
    \returns A raw pointer to an instance of the <exref target="https://docs.opendesign.com/tkernel/OdGeVector3d.html">OdGeVector3d</exref> class.
    \remarks 
    The method returns a valid raw pointer to the <exref target="https://docs.opendesign.com/tkernel/OdGeVector3d.html">OdVector3d</exref> object 
    if the resolution result is equal to <link OdIfc::IfcOpResult::kResVector3d, kResVector3d> 
    or <link OdIfc::IfcOpResult::kResVector2d, kResVector2d>; otherwise, the method returns a NULL pointer.
    */
    static const OdGeVector3d* asVector3d(const OdIfcEntity *pEnt) {
      if (pEnt->m_resolved == kResVector3d || pEnt->m_resolved == kResVector2d)
        return reinterpret_cast<OdGeVector3d*>(pEnt->m_resPtr);
      ODA_ASSERT(0);
      return nullptr;
    };

    /** \details
    Returns the result of the entity resolution represented as a two-dimensional vector.
    \param pEnt [in] A smart pointer to an entity to be resolved.
    \returns A raw pointer to an instance of the <exref target="https://docs.opendesign.com/tkernel/OdGeVector2d.html">OdGeVector2d</exref> class.
    \remarks 
    The method returns a valid raw pointer to the <exref target="https://docs.opendesign.com/tkernel/OdGeVector2d.html">OdVector2d</exref> object 
    if the resolution result is equal to <link OdIfc::IfcOpResult::kResVector3d, kResVector3d> 
    or <link OdIfc::IfcOpResult::kResVector2d, kResVector2d>; otherwise, the method returns a NULL pointer.
    */
    static const OdGeVector2d* asVector2d(const OdIfcEntity *pEnt) {
      if (pEnt->m_resolved == kResVector2d || pEnt->m_resolved == kResVector3d)
        return reinterpret_cast<OdGeVector2d*>(pEnt->m_resPtr);
      ODA_ASSERT(0);
      return nullptr;
    };

    /** \details
    Returns the result of the entity resolution represented as a two-dimensional matrix.
    \param pEnt [in] A smart pointer to an entity to be resolved.
    \returns A raw pointer to an instance of the <exref target="https://docs.opendesign.com/tkernel/OdGeMatrix2d.html">OdGeMatrix2d</exref> class.
    \remarks
    The method returns a valid raw pointer to the <exref target="https://docs.opendesign.com/tkernel/OdGeMatrix2d.html">OdMatrix2d</exref> object 
    if the resolution result is equal to <link OdIfc::IfcOpResult::kResMatrix2d, kResMatrix2d>; otherwise, the method returns a NULL pointer.
    */
    static const OdGeMatrix2d* asMatrix2d(const OdIfcEntity *pEnt) {
      if (pEnt->m_resolved == kResMatrix2d)
        return reinterpret_cast<OdGeMatrix2d*>(pEnt->m_resPtr);
      ODA_ASSERT(0);
      return nullptr;
    };

    /** \details
    Returns the result of the entity resolution represented as a three-dimensional vector.
    \param pEnt [in] A smart pointer to an entity to be resolved.
    \returns A raw pointer to an instance of the <exref target="https://docs.opendesign.com/tkernel/OdGeMatrix3d.html">OdGeMatrix3d</exref> class.
    \remarks 
    The method returns a valid raw pointer to the <exref target="https://docs.opendesign.com/tkernel/OdGeMatrix3d.html">OdMatrix3d</exref> object 
    if the resolution result is equal to <link OdIfc::IfcOpResult::kResMatrix3d, kResMatrix3d>; otherwise, the method returns a NULL pointer.
    */
    static const OdGeMatrix3d* asMatrix3d(const OdIfcEntity *pEnt) {
      if (pEnt->m_resolved == kResMatrix3d)
        return reinterpret_cast<OdGeMatrix3d*>(pEnt->m_resPtr);
      ODA_ASSERT(0);
      return nullptr;
    };

    /** \details
    Returns the result of the entity resolution represented as a compound object.
    \param pEnt [in] A smart pointer to an entity to get the compound object from.
    \returns A smart pointer to a <link OdIfc::OdIfcCompound, compound> object.
    \remarks 
    The method returns a valid smart pointer to the <link OdIfc::OdIfcCompound, compound> object 
    if the resolution result is equal to <link OdIfc::IfcOpResult::kResCompound, kResCompound>; otherwise, the method returns a NULL pointer.
    */
    static OdIfcCompoundPtr asCompound(OdSmartPtr<OdIfcEntity> pEnt);

    /** \details
    Returns the result of the entity resolution represented as an <exref target="https://docs.opendesign.com/tkernel/OdCmEntityColor.html">RGB color</exref> object.
    \param pEnt [in] A smart pointer to an entity to be resolved.
    \returns A raw pointer to an <exref target="https://docs.opendesign.com/tkernel/OdCmEntityColor.html">RGB color</exref> object.
    \remarks 
    The method returns a valid raw pointer to the <exref target="https://docs.opendesign.com/tkernel/OdCmEntityColor.html">RGB color</exref> object 
    if the resolution result is equal to <link OdIfc::IfcOpResult::kRgbColor, kRgbColor>; otherwise, the method returns a NULL pointer.
    */
    static const OdCmEntityColor* asRgbColor(const OdIfcEntity *pEnt) {
      if (pEnt->m_resolved == kRgbColor)
        return reinterpret_cast<OdCmEntityColor*>(pEnt->m_resPtr);
      ODA_ASSERT(0);
      return nullptr;
    }

    /** \details 
    Sets a new Gs node cache for the entity.
    \param pGsNode [in] A raw pointer to an <exref target="https://docs.opendesign.com/tv/OdGsCache.html">OdGsCache</exref> object.
    */
    virtual void setGsNode(OdGsCache* pGsNode);

    /** \details
    Retrieves the current Gs node object of the entity.
    \returns A raw pointer to the <exref target="https://docs.opendesign.com/tv/OdGsCache.html">OdGsCache</exref> object associated with the entity.
    */
    virtual OdGsCache* gsNode() const;

    /** \details 
    Sets the values of the entity's sub-entity traits. 
    \param traits [out] A raw pointer to the traits to be filled and returned to a calling subroutine.
    \returns The result of setting the values.
    */
    virtual OdUInt32 subSetAttributes(OdGiDrawableTraits * traits) const;

    /** \details 
    Draws a graphical entity representation that is independent of any viewport context. 
    \param wd [in] A raw pointer to the object that encapsulates parameters of viewport-independent vectorization.
    \returns true if the drawing was successful; otherwise, the method returns false.
    */
    virtual bool subWorldDraw(OdGiWorldDraw * wd) const;

    using OdDAI::ApplicationInstance::isKindOf;

//DOM-IGNORE-BEGIN
  protected:

    void          *m_resPtr;
    IfcOpResult   m_resolved;

  private:

    void* asCustom() const { return m_resPtr; }

    friend class OdIfcCompound;
//DOM-IGNORE-END
  };

  /** \details
  A data type that represents a smart pointer to an <link OdIfc::OdIfcEntity, OdIfcEntity> object and array of objects.
  */
  SMARTPTR(OdIfcEntity);

} //namespace OdIfc

#endif // _IFC_ENTITY_H_
