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
#include "ExPavement.h"

OdIfc::OdIfcEntityPtr ExPavement::createProfile(const OdAnsiString &name)
{
  IfcProfileBuilderPtr profileBuilder = m_b->createProfileBuilder();

  //
  // Just rectangle
  //
  return profileBuilder->createRectangleProfileDef(IfcProfileBuilder::kAREA, name, m_xdim, m_ydim);

  //
  // Just arbitrary closed profile def =)
  //
  /*OdGePoint2dArray points;
  points.append(OdGePoint2d(-halfWidth, -halfHeight));
  points.append(OdGePoint2d(halfWidth, -halfHeight));
  points.append(OdGePoint2d(halfWidth, halfHeight));
  points.append(OdGePoint2d(-halfWidth, halfHeight));

  return profileBuilder->createArbitraryClosedProfileDef(
    name, IfcProfileBuilder::kAREA, points);*/
}

OdIfc::OdIfcEntityPtr ExPavement::subProcess()
{
  //
  // Pavement 3d representation
  //
  OdIfc::OdIfcEntityPtr grc = m_b->filler()->getGeometricRepresentationContext("Model");
  if (grc.isNull())
  {
    ODA_FAIL_M("Not convenient graphic representation context found.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcModelPtr model = m_b->filler()->model();

  OdIfc::OdIfcEntityPtr sectionProfile = createProfile("pavement_profile");
  OdGeVector3d dir = m_endPoint - m_startPoint;
  double fullLen = dir.length();

  OdIfc::OdIfcEntityPtr pSR = model->createEntityInstance("ifcshaperepresentation");
  pSR->putAttr(OdIfc::kContextOfItems, OdDAIObjectId(grc->id()));

  // TODO: As IfcSectionedSolidHorizontal

  OdGeMatrix3d mPlacement = OdGeMatrix3d::rotation(OdaPI, OdGeVector3d::kZAxis);
  mPlacement *= OdGeMatrix3d::rotation(OdaPI2, OdGeVector3d::kXAxis);
  OdGePoint3d elevation(0., 0., m_ydim * 0.5);
  mPlacement.setTranslation(elevation.asVector());
  OdIfc::OdIfcEntityPtr positionInst = m_b->filler()->createAxis2Placement3D(mPlacement);

  OdIfc::OdIfcEntityPtr extrudeBase = model->createEntityInstance("ifcextrudedareasolid");

  // IfcSweptAreaSolid attributes
  extrudeBase->putAttr("sweptarea", OdDAIObjectId(sectionProfile->id()));
  extrudeBase->putAttr("position", OdDAIObjectId(positionInst->id()));

  // IfcExtrudedAreaSolid attributes
  extrudeBase->putAttr("depth", fullLen);
  extrudeBase->putAttr("extrudeddirection", m_b->filler()->dirZ());

  OdDAIObjectId idExtrude = model->appendEntityInstance(extrudeBase);

  OdAnsiString strBody("Body");
  OdAnsiString strType("CSG");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, idExtrude);

  setStyledItem(extrudeBase, m_styleName);

  /*
  // TODO: As IfcSectionedSolidHorizontal
  OdIfc::OdIfcEntityPtr extrudeBase = model->createEntityInstance(OdIfc::kIfcExtrudedAreaSolid);
  extrudeBase->putAttr("sweptarea", OdDAIObjectId(sectionProfile->id()));
  extrudeBase->putAttr("depth", fullLen);
  extrudeBase->putAttr("extrudeddirection", OdDAIObjectId(m_b->filler()->dirZ()->id()));
  OdDAIObjectId idAsExtrude = model->appendEntityInstance(extrudeBase);

  OdAnsiString strBody("Body");
  OdAnsiString strType("CSG");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, idAsExtrude);*/

  model->appendEntityInstance(pSR);

  OdAnsiString predefinedType("paving");
  m_b->getProduct()->putAttr("predefinedtype", predefinedType);

  return pSR;
}

ExPavement::ExPavement(
  const OdGePoint3d &startPoint,
  const OdGePoint3d &endPoint,
  const OdAnsiString &name,
  double xdim,
  double ydim,
  const OdAnsiString &styleName
)
  : m_name(name)
  , m_startPoint(startPoint)
  , m_endPoint(endPoint)
  , m_xdim(xdim)
  , m_ydim(ydim)
  , m_styleName(styleName)
{
  //m_objectPlacement.setTranslation(startPoint.asVector());
}
