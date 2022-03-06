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

// This file is generated automatically.

#ifndef _IFC2X2_FINAL_IFCPROJECT_AUTO_IMPL_H
#define _IFC2X2_FINAL_IFCPROJECT_AUTO_IMPL_H

#include "IfcObjectAutoImpl.h"
#include "IfcUnitAssignmentAutoImpl.h"

/** \details
  The namespace contains schema-dependent classes, definitions and sub routines
  for work with IFC2X2_FINAL express schema definitions.
*/
namespace OdIfc2x2_final {

/** \details
  IfcProject represents processes in design, engineering, construction, or maintenance activities performed for a product. 
  The project forms the context for exchangeable information and it may optionally represent a construction project. 
  The main aim of IfcProject's in an exchange structure is to provide the root instance and the context for other information items.
  
  The context related to the project:
  * the default units
  * the geometric representation context with shape representations
      * coordinate system of the project
      * the coordinate space dimension
      * the precision used for the geometric representations
      * [optional] the indication of the True North
      * [optional] conversion utilities between the project coordinate system and the geospatial coordinate reference system.
*/
class IFC2X2_FINAL_EXPORT IfcProject : public IfcObject
{
  //DOM-IGNORE-BEGIN
  OD_EXP_DECLARE_MEMBERS(OdIfc2x2_final::IfcProject);
  //DOM-IGNORE-END

public:


  //
  // OdDAI early binding accessors
  //

  const OdAnsiString& getLongName() const;
  void setLongName(const OdAnsiString& LongName);
  const OdAnsiString& getPhase() const;
  void setPhase(const OdAnsiString& Phase);
  void getRepresentationContexts(OdDAIObjectIds& RepresentationContexts) const;
  OdDAI::OdDAIObjectIdSet& representationContexts();
  const OdDAIObjectId& getUnitsInContext() const;
  void setUnitsInContext(const OdDAIObjectId& UnitsInContext);


public:
  IfcProject();

  /** \details
  Reads object's data from the specified filer.
  \param rdFiler [in] Pointer to a filer from which to read the data.
  \returns
  A value of OdResult type that contains the result of the method execution.
  */
  virtual OdResult inFields(OdDAI::OdSpfFilerBase* rdFiler);

  /** \details
  Writes object's data the the specified filer.
  \param wrFiler [in] Pointer to a filer to which to write the data.
  \returns
  A value of OdResult type that contains the result of the method execution.
  */
  virtual OdResult outFields(OdDAI::OdSpfFilerBase* wrFiler);

  /** \details
  Returns a type of a class instance.
  \returns
  Pointer to the <link OdDAI__Entity, OdDAI::Entity> type that determines an entity definition within a schema.
  */
  virtual OdDAI::Entity* getInstanceType() const;

  /** \details
  Returns an attribute value for the specified attribute name.
  \param attrName [in] Name of an attribute to query.
  \returns
  OdRxValue object that represents a generic variant type value.
  */
  virtual OdRxValue getAttr(const char * attrName) const;

  /** \details
  Resets a value for the specified attribute.
  \param explicitAttrName [in] Explicit name of the attribute to reset.
  */
  virtual void unsetAttr(const char * explicitAttrName);

  /** \details
  Checks whether the specified attribute is set.
  \param explicitAttrName [in] Explicit name of the attribute to test.
  \returns
  true if the specified attribute is set, false otherwise.
  */
  virtual bool testAttr(const char * explicitAttrName) const;

  /** \details
  Sets the specified attribute with a given value.
  \param explicitAttrName [in] Explicit name of the attribute to set.
  \param val [in] Value to set.
  \returns
  true if the value is successfully set for the specified attribute, false otherwise.
  */
  virtual bool putAttr(const char * explicitAttrName, const OdRxValue &val);

  /** \details
  Checks whether the specified instance is the object derived from or belongs to this class.
  \param entityType [in] Entity to check.
  \returns
  true if the specified instance is the object derived from or belongs to this class, false otherwise.
  */
  virtual bool isKindOf(OdIfc::OdIfcEntityType entityType) const;

  /** \details
  Returns the type of this entity.
  \returns
  A value of the <link OdIfc__OdIfcEntityType, OdIfc::OdIfcEntityType> type that represents type of this entity.
  */
  virtual OdIfc::OdIfcEntityType type() const;

  /** \details
  Returns an attribute value for the specified attribute definition.
  \param attrDef [in] Attribute definition to query.
  \returns
  OdRxValue object that represents a generic variant type value.
  */
  virtual OdRxValue getAttr(const OdIfc::OdIfcAttribute attrDef) const;

  /** \details
  Resets a value for the specified attribute.
  \param explicitAttrDef [in] Explicit definition that represents an attribute to reset.
  */
  virtual void unsetAttr(const OdIfc::OdIfcAttribute explicitAttrDef);

  /** \details
  Checks whether the specified attribute is set.
  \param explicitAttrDef [in] Attribute definition to test.
  \returns
  true if the specified attribute is set, false otherwise.
  */
  virtual bool testAttr(const OdIfc::OdIfcAttribute explicitAttrDef) const;

  /** \details
  Sets the specified attribute with a given value.
  \param explicitAttrDef [in] Explicit attribute definition to set.
  \param val [in] Value to set.
  \returns
  true if the value is successfully set for the specified attribute, false otherwise.
  */
  virtual bool putAttr(const OdIfc::OdIfcAttribute explicitAttrDef, const OdRxValue &val);

protected:
  // Fields declaration: 
  OdAnsiString m_LongName;   // IfcLabel  [optional]
  OdAnsiString m_Phase;   // IfcLabel  [optional]
  OdDAI::OdDAIObjectIdSet m_RepresentationContexts; // SET [1:?] of IfcRepresentationContext
  OdDAIObjectId m_UnitsInContext;   // IfcUnitAssignment
};

/** \details
  A data type that represents a smart pointer to a <link OdIfc2x2_final::IfcProject, IfcProject> object.
*/
typedef OdSmartPtr<IfcProject> IfcProjectPtr;

} // namespace

#endif // _IFC2X2_FINAL_IFCPROJECT_AUTO_IMPL_H
