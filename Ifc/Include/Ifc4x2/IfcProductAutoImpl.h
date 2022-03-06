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

#ifndef _IFC4X2_IFCPRODUCT_AUTO_IMPL_H
#define _IFC4X2_IFCPRODUCT_AUTO_IMPL_H

#include "IfcObjectAutoImpl.h"
#include "IfcObjectPlacementAutoImpl.h"
#include "IfcProductRepresentationAutoImpl.h"

/** \details
  The namespace contains schema-dependent classes, definitions and sub routines
  for work with IFC4X2 express schema definitions.
*/
namespace OdIfc4x2 {

/** \details
  The IfcProduct is an abstract representation of any object that relates to a geometric or spatial context. 
  An IfcProduct occurs at a specific location in space if it has a geometric representation assigned. 
  It can be placed relatively to other products, but ultimately relative to the project coordinate system. 
  The ObjectPlacement attribute establishes the coordinate system in which all points and directions used 
  by the geometric representation items under Representation are founded. 
  The Representation is provided by an IfcProductDefinitionShape being either a geometric shape representation, 
  or a topology representation (with or without underlying geometry of the topological items).
  
  Products include manufactured, supplied or created objects (referred to as elements) for incorporation into an AEC/FM project. 
  This also includes objects that are created indirectly by other products, as spaces are defined by bounding elements. 
  Products are defined by their properties and representations.
  
  Any instance of IfcProduct defines a particular occurrence of a product, the common type information, 
  that relates to many similar (or identical) occurrences of IfcProduct, is handled by the IfcTypeProduct (and its subtypes), 
  assigned to one or many occurrences of IfcProduct by using the objectified relationship IfcRelDefinesByType. 
  The IfcTypeProduct may provide, in addition to common properties, also a common geometric representation for all occurrences.
*/
class IFC4X2_EXPORT IfcProduct : public IfcObject
{
  //DOM-IGNORE-BEGIN
  OD_EXP_NON_INSTANTIABLE_DECLARE_MEMBERS(OdIfc4x2::IfcProduct);
  //DOM-IGNORE-END

public:


  //
  // OdDAI early binding accessors
  //


  /** \details
  Returns placement of the product in space. The placement can be:
    * Absolute (relative to the world coordinate system)
    * Relative (relative to the object placement of another product)
    * Constraint (e.g. relative to grid axes)
  \returns
  Identifier of the product placement that includes the axis placement information to determine the transformation for the object coordinate system.
  */
  const OdDAIObjectId& getObjectPlacement() const;

  /** \details
  Sets placement of the product in space.
  \param Representation [in] Identifier of the product placement that includes the axis placement information to determine the transformation for the object coordinate system.
  */
  void setObjectPlacement(const OdDAIObjectId& ObjectPlacement);

  /** \details
  Returns the representations of the product. Representation can either be an IfcProductRepresentation entity
  or as a special case of shape representations - IfcProductDefinitionShape entity.
  The geometric representation of any IfcProduct is provided by the IfcProductDefinitionShape allowing multiple geometric representations.
  \returns
  Identifier of the product representation.
  */
  const OdDAIObjectId& getRepresentation() const;

  /** \details
  Specifies the representations of the product.
  The geometric representation of any IfcProduct is provided by the IfcProductDefinitionShape allowing multiple geometric representations.
  \param Representation [in] Identifier of the product representation.
  */
  void setRepresentation(const OdDAIObjectId& Representation);

  /** \details
  Retrieves relationships, by which other products, processes, controls, resources or actors (as subtypes of IfcObjectDefinition) can be related to this product.
  \param ReferencedBy [out] Receives a reference to the IfcRelAssignsToProduct relationship.
  */
  void getInvReferencedBy(OdDAIObjectIds& ReferencedBy) const;
  void getInvPositionedRelativeTo(OdDAIObjectIds& PositionedRelativeTo) const;


public:

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
  Sets the object ID of this instance to inverse attributes of related instances according to schema specification of inverse attributes.
  */
  virtual void setInverseCounterParts();

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
  OdDAIObjectId m_ObjectPlacement;   // IfcObjectPlacement  [optional]
  OdDAIObjectId m_Representation;   // IfcProductRepresentation  [optional]

  // Declare friend classes for inverse attributes functionality: 
  friend class IfcRelAssignsToProduct;
  friend class IfcRelPositions;
};

/** \details
  A data type that represents a smart pointer to a <link OdIfc4x2::IfcProduct, IfcProduct> object.
*/
typedef OdSmartPtr<IfcProduct> IfcProductPtr;

} // namespace

#endif // _IFC4X2_IFCPRODUCT_AUTO_IMPL_H
