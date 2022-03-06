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

#include "ExIfcModelFiller.h"
#include "ExBearing.h"

ExBearing::ExBearing(
  const OdGeMatrix3d &objectPlacement,
  double xdim,
  double ydim,
  double baseThickness,
  double topThickness,
  double r
)
  : IfcRepresentationAdapter(objectPlacement)
  , m_xdim(xdim)
  , m_ydim(ydim)
  , m_baseThickness(baseThickness)
  , m_topThickness(topThickness)
  , m_r(r)
{}

OdIfc::OdIfcEntityPtr ExBearing::processShapeRepresentation()
{
  //
  // Bearing 3d representation
  //
  OdIfc::OdIfcEntityPtr grc = m_b->filler()->getGeometricRepresentationContext("Model");
  if (grc.isNull())
  {
    ODA_ASSERT("Not convenient graphic representation context found.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcModelPtr model = m_b->filler()->model();

  OdIfc::OdIfcEntityPtr pSR = model->createEntityInstance("ifcshaperepresentation");
  pSR->putAttr(OdIfc::kContextOfItems, OdDAIObjectId(grc->id()));

  OdAnsiString strProfileType("area");

  //
  // Rectangular base
  //
  OdIfc::OdIfcEntityPtr rectangleProfileDef = model->createEntityInstance("ifcrectangleprofiledef");
  rectangleProfileDef->putAttr("profiletype", strProfileType);
  rectangleProfileDef->putAttr("xdim", m_xdim);
  rectangleProfileDef->putAttr("ydim", m_ydim);
  OdDAIObjectId idProfile = model->appendEntityInstance(rectangleProfileDef);

  OdIfc::OdIfcEntityPtr extrudeBase = model->createEntityInstance("ifcextrudedareasolid");
  extrudeBase->putAttr("sweptarea", OdDAIObjectId(idProfile));
  extrudeBase->putAttr("depth", m_baseThickness);
  extrudeBase->putAttr("extrudeddirection", m_b->filler()->dirZ());
  OdDAIObjectId idExtrudeBase = model->appendEntityInstance(extrudeBase);
  setStyledItem(extrudeBase, "BearingBase");

  //
  // Circular spring
  //
  OdIfc::OdIfcEntityPtr circleProfileDef = model->createEntityInstance("ifccircleprofiledef");
  circleProfileDef->putAttr("profiletype", strProfileType);
  circleProfileDef->putAttr("radius", m_r);
  OdDAIObjectId idCircleProfile = model->appendEntityInstance(circleProfileDef);

  OdIfc::OdIfcEntityPtr extrudeSpring = model->createEntityInstance("ifcextrudedareasolid");
  OdGeMatrix3d position;
  position.setTranslation(OdGeVector3d(0, 0, m_baseThickness));
  OdIfc::OdIfcEntityPtr springTranslation =  m_b->filler()->createAxis2Placement3D(position);
  extrudeSpring->putAttr("sweptarea", OdDAIObjectId(idCircleProfile));
  extrudeSpring->putAttr("position", OdDAIObjectId(springTranslation->id()));
  extrudeSpring->putAttr("depth", m_topThickness);
  extrudeSpring->putAttr("extrudeddirection", m_b->filler()->dirZ());
  OdDAIObjectId idExtrudeSpring = model->appendEntityInstance(extrudeSpring);
  setStyledItem(extrudeSpring, "BearingLiner");

  OdAnsiString strBody("Body");
  OdAnsiString strType("CSG");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, idExtrudeBase);
  m_b->filler()->appendId(pSR, OdIfc::kItems, idExtrudeSpring);
  model->appendEntityInstance(pSR);

  OdAnsiString strElasomeric("elastomeric");
  m_b->getProduct()->putAttr("predefinedtype", strElasomeric);

  m_b->filler()->createPropertySet(m_b->getProduct())->
    appendPropertySingleValue("DisplacementAccomodated", false, "IfcBoolean").
    appendPropertySingleValue("RotationAccomodated", false, "IfcBoolean").
    createPropertySet("Pset_BearingCommon");
  m_b->filler()->createPropertySet(m_b->getProduct())->
    appendPropertySingleValue("Type", OdAnsiString("KF15"), "IfcText").
    appendPropertySingleValue("A", m_xdim, "IfcPositiveLengthMeasure").
    appendPropertySingleValue("B", m_ydim, "IfcPositiveLengthMeasure").
    appendPropertySingleValue("H", m_baseThickness + m_topThickness, "IfcPositiveLengthMeasure").
    appendPropertySingleValue("Mix N", 15000., "IfcPositiveLengthMeasure").
    appendPropertySingleValue("Mix N", 6000., "IfcPositiveLengthMeasure").
    appendPropertySingleValue("Max V(x)", 1500., "IfcReal").
    appendPropertySingleValue("Max V(y)", 1500., "IfcReal").
    createPropertySet("Pset_BridgeBearing");

  return pSR;
}

OdIfc::OdIfcEntityPtr ExBearing::subProcess()
{
  return processShapeRepresentation();
}
