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

#ifndef _IFC4X3_RC1_IFCSITE_AUTO_IMPL_H
#define _IFC4X3_RC1_IFCSITE_AUTO_IMPL_H

#include "IfcSpatialStructureElementAutoImpl.h"
#include "IfcPostalAddressAutoImpl.h"

/** \details
  The namespace contains schema-dependent classes, definitions and sub routines
  for work with IFC4X3_RC1 express schema definitions.
*/
namespace OdIfc4x3_rc1 {

/** \details
  - Overview -
  A site is a defined area of land, possibly covered with water, on which the project construction is to be completed. 
  A site may be used to erect, retrofit or turn down building(s), or for other construction related developments.
  
  A site may include a definition of the single geographic reference point for this site 
  (global position using WGS84 with Longitude, Latitude and Elevation). 
  The precision is provided up to millionth of a second and it provides an absolute placement in relation 
  to the real world as used in exchange with geospational information systems. 
  If asserted, the Longitude, Latitude and Elevation establish the point in WGS84 where the point 0.,0.,0. of the LocalPlacement of IfcSite is situated.
  
  The geometrical placement of the site, defined by the IfcLocalPlacement, shall be always relative to the spatial structure element, 
  in which this site is included, or absolute, i.e. to the world coordinate system, as established by the geometric representation context of the project. 
  The world coordinate system, established at the IfcProject.RepresentationContexts,
  may include a definition of the true north within the XY plane of the world coordinate system, 
  if provided, it can be obtained at IfcGeometricRepresentationContext.TrueNorth.
  
  The IfcSite is used to build the spatial structure of a building (that serves as the primary project breakdown and is required to be hierarchical).
  
  The following image shows the heights and elevations of the IfcSite.
  <IMAGE ifc_ifcSite_elevation>
*/
class IFC4X3_RC1_EXPORT IfcSite : public IfcSpatialStructureElement
{
  //DOM-IGNORE-BEGIN
  OD_EXP_DECLARE_MEMBERS(OdIfc4x3_rc1::IfcSite);
  //DOM-IGNORE-END

public:


  //
  // OdDAI early binding accessors
  //


  /** \details
  Retrieves the World Latitude at reference point.
  \param RefLatitude [out] Receives an array of integer values for degrees, minutes, seconds, and, optionally, millionths of seconds with respect to the world geodetic system WGS84.
  */
  void getRefLatitude(OdArray<int >& RefLatitude) const;

  /** \details
  Returns the World Latitude at reference point.
  \returns
  Integer list of values for degrees, minutes, seconds, and, optionally, millionths of seconds with respect to the world geodetic system WGS84.
  */
  OdDAI::IntList& refLatitude();

  /** \details
  Retrieves the World Longitude at reference point.
  \param RefLongitude [out] Receives an array of integer values for degrees, minutes, seconds, and, optionally, millionths of seconds with respect to the world geodetic system WGS84.
  \remarks
  Latitudes are measured relative to the geodetic equator, north of the equator by positive values - from 0 till +90, south of the equator by negative values - from 0 till -90.
  */
  void getRefLongitude(OdArray<int >& RefLongitude) const;

  /** \details
  Returns the World Longitude at reference point.
  \returns
  Integer list of values for degrees, minutes, seconds, and, optionally, millionths of seconds with respect to the world geodetic system WGS84.
  \remarks
  Longitudes are measured relative to the geodetic zero meridian, nominally the same as the Greenwich prime meridian: 
     longitudes west of the zero meridian have negative values - from 0 till -180, longitudes east of the zero meridian have positive values - from 0 till -180.
  */
  OdDAI::IntList& refLongitude();

  /** \details
  Retrieves datum elevation relative to sea level.
  \returns
  Datum elevation relative to sea level.
  */
  double getRefElevation() const;

  /** \details
  Sets the datum elevation value relative to sea level.
  \param RefElevation [in] Datum elevation relative to sea level.
  */
  void setRefElevation(double RefElevation);

  /** \details
  Retrieves the land title number that designates of the site within a regional system.
  \returns
  Land title number.
  */
  const OdAnsiString& getLandTitleNumber() const;

  /** \details
  Sets the land title number that designates of the site within a regional system.
  \param LandTitleNumber [in] Land title number.
  */
  void setLandTitleNumber(const OdAnsiString& LandTitleNumber);

  /** \details
  Returns the postal address of the site.
  \returns
  Identifier of the object that represents a postal address of the site.
  */
  const OdDAIObjectId& getSiteAddress() const;

  /** \details
  Sets the postal address of the site.
  \param PostalAddress [in] Identifier of the postal address of the site.
  */
  void setSiteAddress(const OdDAIObjectId& SiteAddress);


public:

  /** \details
  Default constructor for the IfcSite class.
  */
  IfcSite();

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
  OdDAI::IntList m_RefLatitude; // IfcCompoundPlaneAngleMeasure [optional]

  OdDAI::IntList m_RefLongitude; // IfcCompoundPlaneAngleMeasure [optional]

  double m_RefElevation;   // IfcLengthMeasure  [optional]
  OdAnsiString m_LandTitleNumber;   // IfcLabel  [optional]
  OdDAIObjectId m_SiteAddress;   // IfcPostalAddress  [optional]
};

/** \details
  A data type that represents a smart pointer to a <link OdIfc4x3_rc1::IfcSite, IfcSite> object.
*/
typedef OdSmartPtr<IfcSite> IfcSitePtr;

} // namespace

#endif // _IFC4X3_RC1_IFCSITE_AUTO_IMPL_H
