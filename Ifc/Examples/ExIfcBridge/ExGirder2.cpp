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
#include "ExGirder2.h"

OdIfc::OdIfcEntityPtr ExGirder2::createDeckProfile(const OdAnsiString &name)
{
  IfcProfileBuilderPtr profileBuilder = m_b->createProfileBuilder();

  double left = -m_xdim * 0.5;
  double right = m_xdim * 0.5;
  double bearingHalfXDim = m_bearingXDim * 0.5;

  OdGePoint2dArray points;


  // left bearing
  double leftBearingCenter = -m_bearingDist;

  // left wing
  points.append(OdGePoint2d(left, m_ydim));
  points.append(OdGePoint2d(left, m_ydim - m_plateThickness * 0.5));
  points.append(OdGePoint2d(left + m_wingWidth, m_ydim - m_plateThickness));

  // right wing
  points.append(OdGePoint2d(right - m_wingWidth, m_ydim - m_plateThickness));
  points.append(OdGePoint2d(right, m_ydim - m_plateThickness * 0.5));
  points.append(OdGePoint2d(right, m_ydim));

  return profileBuilder->createArbitraryClosedProfileDef(
    IfcProfileBuilder::kAREA, name, points);
}

OdIfc::OdIfcEntityPtr ExGirder2::createGirderProfileBig(const OdAnsiString &name)
{
  IfcProfileBuilderPtr profileBuilder = m_b->createProfileBuilder();

  double left = -m_xdim * 0.5;
  double right = m_xdim * 0.5;
  double bearingHalfXDim = m_bearingXDim * 0.5;

  OdGePoint2dArray points;


  // left bearing
  double leftBearingCenter = -m_bearingDist;

  // mid slot
  points.append(OdGePoint2d(-m_plateThickness * 1.5, m_ydim - m_plateThickness)); // 0
  points.append(OdGePoint2d(-m_plateThickness * 1.5, m_ydim - m_plateThickness * 2)); // 1
  points.append(OdGePoint2d(leftBearingCenter, m_plateThickness));


  points.append(OdGePoint2d(leftBearingCenter - bearingHalfXDim, m_ydim - m_plateThickness));
  points.append(OdGePoint2d(leftBearingCenter - bearingHalfXDim - m_plateThickness, m_ydim - m_plateThickness));

  points.append(OdGePoint2d(leftBearingCenter - bearingHalfXDim, 0.));
  points.append(OdGePoint2d(leftBearingCenter + bearingHalfXDim, 0.));

  // mid
  points.append(OdGePoint2d(-m_bearingDist * 0.25, m_ydim * 0.25));
  points.append(OdGePoint2d(-m_plateThickness, m_ydim - m_plateThickness * 3));
  points.append(OdGePoint2d(m_plateThickness, m_ydim - m_plateThickness * 3));
  points.append(OdGePoint2d(m_bearingDist * 0.25, m_ydim * 0.25));

  // right bearing
  double rightBearingCenter = m_bearingDist;
  points.append(OdGePoint2d(rightBearingCenter - bearingHalfXDim, 0.));
  points.append(OdGePoint2d(rightBearingCenter + bearingHalfXDim, 0.));

  points.append(OdGePoint2d(rightBearingCenter + bearingHalfXDim + m_plateThickness, m_ydim - m_plateThickness));
  points.append(OdGePoint2d(rightBearingCenter + bearingHalfXDim, m_ydim - m_plateThickness));

  points.append(OdGePoint2d(rightBearingCenter, m_plateThickness));
  points.append(OdGePoint2d(m_plateThickness * 1.5, m_ydim - m_plateThickness * 2));
  points.append(OdGePoint2d(m_plateThickness * 1.5, m_ydim - m_plateThickness));

  return profileBuilder->createArbitraryClosedProfileDef(
    IfcProfileBuilder::kAREA, name, points);
}

OdIfc::OdIfcEntityPtr ExGirder2::createGirderProfileSmall(const OdAnsiString &name)
{
  IfcProfileBuilderPtr profileBuilder = m_b->createProfileBuilder();

  double left = -m_xdim * 0.5;
  double right = m_xdim * 0.5;
  double bearingHalfXDim = m_bearingXDim * 0.5;

  OdGePoint2dArray points;


  // left bearing
  double leftBearingCenter = -m_bearingDist;

  // mid slot
  points.append(OdGePoint2d(-m_plateThickness * 1.5, m_ydim - m_plateThickness)); // 0
  points.append(OdGePoint2d(-m_plateThickness * 1.5, m_ydim - m_plateThickness * 2)); // 1
  points.append(OdGePoint2d(leftBearingCenter, m_plateThickness));


  points.append(OdGePoint2d(leftBearingCenter - bearingHalfXDim, m_ydim - m_plateThickness));
  points.append(OdGePoint2d(leftBearingCenter - bearingHalfXDim - m_plateThickness, m_ydim - m_plateThickness));

  points.append(OdGePoint2d(leftBearingCenter - bearingHalfXDim, m_ydim * 0.25)); // bottom
  points.append(OdGePoint2d(leftBearingCenter + bearingHalfXDim, m_ydim * 0.25)); // bottom

  // mid
  points.append(OdGePoint2d(-m_bearingDist * 0.25, m_ydim * 0.35));
  points.append(OdGePoint2d(-m_plateThickness, m_ydim - m_plateThickness * 3));
  points.append(OdGePoint2d(m_plateThickness, m_ydim - m_plateThickness * 3));
  points.append(OdGePoint2d(m_bearingDist * 0.25, m_ydim * 0.35));

  // right bearing
  double rightBearingCenter = m_bearingDist;
  points.append(OdGePoint2d(rightBearingCenter - bearingHalfXDim, m_ydim * 0.25)); // bottom
  points.append(OdGePoint2d(rightBearingCenter + bearingHalfXDim, m_ydim * 0.25)); // bottom

  points.append(OdGePoint2d(rightBearingCenter + bearingHalfXDim + m_plateThickness, m_ydim - m_plateThickness));
  points.append(OdGePoint2d(rightBearingCenter + bearingHalfXDim, m_ydim - m_plateThickness));

  points.append(OdGePoint2d(rightBearingCenter, m_plateThickness));
  points.append(OdGePoint2d(m_plateThickness * 1.5, m_ydim - m_plateThickness * 2));
  points.append(OdGePoint2d(m_plateThickness * 1.5, m_ydim - m_plateThickness));

  return profileBuilder->createArbitraryClosedProfileDef(
    IfcProfileBuilder::kAREA, name, points);
}

OdIfc::OdIfcEntityPtr ExGirder2::subProcess()
{
  // Form cross sections
  OdIfc::OdIfcEntityPtr profileFullHeight = createGirderProfileBig("girder_profile_full_height");
  OdIfc::OdIfcEntityPtr profileHalfHeight = createGirderProfileSmall("girder_profile_half_height");
  OdDAIObjectIds crossSections(4);
  crossSections.append(profileFullHeight->id());
  crossSections.append(profileHalfHeight->id());
  crossSections.append(profileHalfHeight->id());
  crossSections.append(profileFullHeight->id());

  // TODO: create path as IfcAlignmentCurve
  // Append curve
  OdGePoint3dArray points;
  points.append(m_objectPlacement.getCsOrigin());
  points.append((m_objectPlacement.getCsYAxis() * m_girderDepth).asPoint());
  OdIfc::OdIfcEntityPtr path = m_b->createPolyline(points);

  OdGeVector3d dir = points[1] - points[0];
  double len = dir.length();

  //
  // Girder 3d representation
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

  // TODO: As IfcSectionedSolidHorizontal
  OdIfc::OdIfcEntityPtr sectionedSolidHorizontal = model->createEntityInstance("ifcsectionedsolidhorizontal");
  sectionedSolidHorizontal->putAttr("directrix", OdDAIObjectId(path->id()));
  sectionedSolidHorizontal->putAttr("crosssections", crossSections);

  // foorm u-value for profiles positions
  double parmStep = len / (crossSections.size() - 1);
  OdDAIObjectIds crossSectionPositions;
  for (unsigned int i = 0; i < crossSections.size(); ++i)
  {
    OdIfc::OdIfcEntityPtr pDistanceExpr = model->createEntityInstance("ifcdistanceexpression");
    pDistanceExpr->putAttr("distancealong", parmStep * i);
    crossSectionPositions.append(model->appendEntityInstance(pDistanceExpr));
  }

  sectionedSolidHorizontal->putAttr("crosssectionpositions", crossSectionPositions);
  sectionedSolidHorizontal->putAttr("fixedaxisvertical", true);
  OdDAIObjectId idSectionedSolidHorizontal = model->appendEntityInstance(sectionedSolidHorizontal);
  setStyledItem(sectionedSolidHorizontal, "ConcreteLight");

  OdAnsiString strBody("Body");
  OdAnsiString strType("CSG");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, idSectionedSolidHorizontal);
  model->appendEntityInstance(pSR);

  OdAnsiString strGirderSegment("girder_segment");
  m_b->getProduct()->putAttr("predefinedtype", strGirderSegment);

  return pSR;
}

ExGirder2::ExGirder2(
  const OdGeMatrix3d &objectPlacement,
  const OdAnsiString &name,
  double xdim,
  double ydim,
  double plateThickness,
  double wingWidth,
  double bearingDist,
  double bearingXDim,
  double girderDepth
)
  : IfcRepresentationAdapter(objectPlacement)
  , m_name(name)
  , m_xdim(xdim)
  , m_ydim(ydim)
  , m_plateThickness(plateThickness)
  , m_wingWidth(wingWidth)
  , m_bearingDist(bearingDist)
  , m_bearingXDim(bearingXDim)
  , m_girderDepth(girderDepth)
{}
