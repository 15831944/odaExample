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

#ifndef _IFC4X3_RC1_IFCPROFILEDEF_AUTO_IMPL_H
#define _IFC4X3_RC1_IFCPROFILEDEF_AUTO_IMPL_H

#include "IfcEntity.h"

#include "Ifc4x3_RC1Enum.h"
#include "Ifc4x3_RC1SelectTypes.h"
#include "Ifc4x3_RC1CollectionTypes.h"
#include "Ifc4x3_RC1BuildOption.h"

/** \details
  The namespace contains schema-dependent classes, definitions and sub routines
  for work with IFC4X3_RC1 express schema definitions.
*/
namespace OdIfc4x3_rc1 {

/** \details
  - Overview -
  IfcProfileDef is the base class for all definitions of standard and custom profiles used within IFC. 
  This class defines a standard set of commonly used section profiles by their parameters or by their explicit curve geometry.
  * Parameterized profiles are 2D primitives, which are used within the industry to describe cross sections by a description of its parameters.
  * Arbitrary profiles are cross sections defined by an outer boundary as bounded curve, which may also include holes, defined by inner boundaries.
  * Derived profiles, based on a transformation of a parent profile, are also part of the profile definitions available.
  * In addition composite profiles can be defined, which include two or more profile definitions to define the resulting profile.
  
  - Use in Material Association -
  Beams, columns, and similarly shaped building elements and their type objects may be associated with a section profile definition, combined with material definition, by means of IfcRelAssociatesMaterial together with IfcMaterialProfileSet and IfcMaterialProfileSetUsage. This way, building elements and element types with same section and material can share a common section profile definition and association.

  The profile definition in material association is required to be consistent with shape representations of the respective building elements.
  
  - Use in Shape Models -
  Profile definitions are used within the geometry and geometric model resource to create either swept surfaces, swept area solids, or sectioned spines.
  The purpose of the profile definition within the swept surfaces or swept area solids is to define a uniform cross section being swept:
  * Along a line (extrusion) using IfcSurfaceOfLinearExtrusion or IfcExtrudedAreaSolid.
  * Along a circular arc (revolution) using IfcSurfaceOfRevolution or IfcRevolvedAreaSolid.
  * Along a directrix lying on a reference surface using IfcSurfaceCurveSweptAreaSolid.
  
  The purpose of the profile definition within the sectioned spine is to define a varying cross sections at several positions along a spine curve. 
  The subtype IfcDerivedProfileDef is particularly suited to provide the consecutive profiles to be based on transformations of the start profile and thus maintaining the identity of vertices and edges.
  
  An IfcProfileDef is treated as bounded area if it is used within swept area solids. In this case, the inside of the profile is part of the profile. The attribute ProfileType is set to AREA. 
  An IfcProfileDef is treated as a curve if it is used within swept surfaces. In this case, the inside of the profile (if the curve is closed) is not part of the profile. The attribute ProfileType is set to CURVE.
  
  - Profile Types -
  The ProfileType defines whether the inside (the bounded area) is part of the profile definition (Area) or not (Curve).
  
  - Profile Specification by External Reference -
  If the profile is standardized by a norm or a catalogue, a reference to this norm or catalogue should be provided by means of HasExternalReference. 
  This inverse relationship is used to associate an IfcExternalReference (notably IfcClassificationReference or IfcLibraryReference) with the profile.
  IfcClassificationReference is used to refer to a profile norm (a common standard or manufacturer's standard). In this case,
  * IfcClassificationReference.ItemReference contains the formal profile designation from the norm. (On the other hand, IfcProfileDef.ProfileName contains a displayable name which may not necessarily be the same as the formal designation.)
  * IfcClassificationReference.Name carries the short name of the profile norm.
  * Optionally, the norm can be further described by IfcClassificationReference.ReferencedSource.
  
  IfcLibraryReference is used to refer to a library which contains profile definitions. In this case,
  * IfcLibraryReference.ItemReference contains the identifier of the profile within the library and is meant to be machine-readable (in contrast to IfcProfileDef.ProfileName which should be human-readable).
  * IfcLibraryReference.Location and .Name or .ReferencedLibrary further describe the library.
  
  If an external reference is provided, sending systems shall ensure that the shape of the profile definition object agrees with the definitions in the referenced classification or library.
  
  - Direct instances of IfcProfileDef -
  Usually, only subtypes of IfcProfileDef should be instantiated. In some special cases, e.g. if the profile object is used for purposes other than geometric models (e.g. for structural analysis models), 
  it may be possible to directly instantiate IfcProfileDef and further specify the profile only by external reference or by profile properties. The latter are tracked by the inverse attribute HasProperties.
*/
class IFC4X3_RC1_EXPORT IfcProfileDef : public OdIfc::OdIfcEntity
{
  //DOM-IGNORE-BEGIN
  OD_EXP_DECLARE_MEMBERS(OdIfc4x3_rc1::IfcProfileDef);
  //DOM-IGNORE-END

public:


  //
  // OdDAI early binding accessors
  //


  /** \details
  Returns the type of geometry into which this profile definition is resolved.
  \returns
  Geometry type of the profile definition which is either a curve or a surface area.
    In case of curve the inside (the bounded area) is not part of the profile definition, in case of area - it is.
  */
  IfcProfileTypeEnum getProfileType() const;

  /** \details
  Sets the type of geometry for the profile definition.
  \param ProfileType [in] Profile type to set. In case of curve the profile should be referenced by a swept surface, in case of area the profile should be referenced by a swept area solid.
  */
  void setProfileType(IfcProfileTypeEnum ProfileType);

  /** \details
  Returns a human-readable profile name.
  \returns
  A string that contains name of the profile definition.
  */
  const OdAnsiString& getProfileName() const;

  /** \details
  Sets a human-readable name of the profile definition.
  \param ProfileName [in] Name of the profile definition.
  */
  void setProfileName(const OdAnsiString& ProfileName);

  /** \details
  Retrieves a reference to external information. For example, this information can be about library classification or document that is associated with the profile.
  \param ProfileName [out] Receives an array of Data Access Interface (DAI) identifiers that are related to external data objects.
  */
  void getInvHasExternalReference(OdDAIObjectIds& HasExternalReference) const;

  /** \details
  Retrieves additional properties of the profile.
  \param idsIfcProfileProperties [out] Receives an array of Data Access Interface (DAI) identifiers that are related to objects that define additional properties.
  */
  void getInvHasProperties(OdDAIObjectIds& HasProperties) const;


public:

  /** \details
  Default constructor for the IfcProfileDef class.
  */
  IfcProfileDef();

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
  Early-bound version of instances comparison.
  \param pOther [in] Other application instance.
  \param ordering [out] Receives the ordering (comparison) status.
  \returns
  true if comparison was performed, false if method has no implementation, so late-bound version could be applied.
  \remarks
  If the method returns true,
  the ordering parameter can receive one of the following statuses:
  <table>
    Name             Value    Description
    _kLessThan_      -1       This object < Other Object.
    _kEqual_          0       This object = Other Object.
    _kGreaterThan_    1       This object > Other Object.
    _kNotOrderable_   2       This class is not orderable.
  </table>
  */
  virtual bool comparedToEarlyImpl(const OdDAI::ApplicationInstance *pOther, OdRx::Ordering &ordering) const;

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
  OdDAI::Enum m_ProfileType;   // IfcProfileTypeEnum
  OdAnsiString m_ProfileName;   // IfcLabel  [optional]

  // Declare friend classes for inverse attributes functionality: 
  friend class IfcExternalReferenceRelationship;
  friend class IfcProfileProperties;
};

/** \details
  A data type that represents a smart pointer to a <link OdIfc4x3_rc1::IfcProfileDef, IfcProfileDef> object.
*/
typedef OdSmartPtr<IfcProfileDef> IfcProfileDefPtr;

} // namespace

#endif // _IFC4X3_RC1_IFCPROFILEDEF_AUTO_IMPL_H
