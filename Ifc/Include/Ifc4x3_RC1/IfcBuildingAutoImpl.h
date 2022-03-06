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

#ifndef _IFC4X3_RC1_IFCBUILDING_AUTO_IMPL_H
#define _IFC4X3_RC1_IFCBUILDING_AUTO_IMPL_H

#include "IfcFacilityAutoImpl.h"
#include "IfcPostalAddressAutoImpl.h"

/** \details
  The namespace contains schema-dependent classes, definitions and sub routines
  for work with IFC4X3_RC1 express schema definitions.
*/
namespace OdIfc4x3_rc1 {

/** \details
  A building represents a structure that provides shelter for its occupants or contents and stands in one place.
  The building also provides a basic element within the spatial structure hierarchy for the components of a building project (together with site, storey, and space).
  A building is (if specified) associated to a site. The site can include a collection of buildings that are organized as a building complex.
  A building can be decomposed in parts to define a building sections:
  * COMPLEX: building complex
  * ELEMENT: building
  * PARTIAL: building section
  
  The IfcBuilding is used to build the spatial structure of a building (that serves as the primary project breakdown and is required to be hierarchical).
*/
class IFC4X3_RC1_EXPORT IfcBuilding : public IfcFacility
{
  //DOM-IGNORE-BEGIN
  OD_EXP_DECLARE_MEMBERS(OdIfc4x3_rc1::IfcBuilding);
  //DOM-IGNORE-END

public:


  //
  // OdDAI early binding accessors
  //


  /** \details
  Returns the elevation above sea level of the reference height used for all storey elevation measures.
  \returns
  Elevation of the reference height that is usually the ground floor level.
  */
  double getElevationOfRefHeight() const;

  /** \details
  Sets the elevation above sea level of the reference height used for all storey elevation measures.
  \param ElevationOfRefHeight [in] Elevation of the reference height.
  */
  void setElevationOfRefHeight(double ElevationOfRefHeight);

  /** \details
  Returns the elevation above the minimal terrain level around the foot print of the building, given in elevation above sea level.
  \returns
  Elevation above the minimal terrain level.
  */
  double getElevationOfTerrain() const;

  /** \details
  Sets the elevation above the minimal terrain level around the foot print of the building, given in elevation above sea level.
  \param ElevationOfTerrain [in] Elevation above the minimal terrain level.
  */
  void setElevationOfTerrain(double ElevationOfTerrain);

  /** \details
  Returns the postal address of the building.
  \returns
  Identifier of the object that represents the postal address of the building.
  */
  const OdDAIObjectId& getBuildingAddress() const;

  /** \details
  Sets the postal address of the building.
  \param BuildingAddress [in] Identifier of the object that represents the postal address of the building.
  */
  void setBuildingAddress(const OdDAIObjectId& BuildingAddress);


public:

  /** \details
  Default constructor for the IfcBuilding class.
  */
  IfcBuilding();

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
  double m_ElevationOfRefHeight;   // IfcLengthMeasure  [optional]
  double m_ElevationOfTerrain;   // IfcLengthMeasure  [optional]
  OdDAIObjectId m_BuildingAddress;   // IfcPostalAddress  [optional]
};

/** \details
  A data type that represents a smart pointer to a <link OdIfc4x3_rc1::IfcBuilding, IfcBuilding> object.
*/
typedef OdSmartPtr<IfcBuilding> IfcBuildingPtr;

} // namespace

#endif // _IFC4X3_RC1_IFCBUILDING_AUTO_IMPL_H
