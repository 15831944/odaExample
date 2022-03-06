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
#include "ExAbutment.h"

OdIfc::OdIfcEntityPtr ExAbutment::createProfile(const OdAnsiString &name)
{
  IfcProfileBuilderPtr profileBuilder = m_b->createProfileBuilder();

  //double left = -m_xdim * 0.5;
  //double right = m_xdim * 0.5;
  //double bearingHalfXDim = m_bearingXDim * 0.5;

  OdGePoint2dArray points;

  // left wing
  /*points.append(OdGePoint2d(left, m_ydim));
  points.append(OdGePoint2d(left, m_ydim - m_plateThickness * 0.5));
  points.append(OdGePoint2d(left + m_wingWidth, m_ydim - m_plateThickness));

  // left bearing
  double leftBearingCenter = -m_bearingDist;
  points.append(OdGePoint2d(leftBearingCenter - bearingHalfXDim, 0.));
  points.append(OdGePoint2d(leftBearingCenter + bearingHalfXDim, 0.));

  // mid
  points.append(OdGePoint2d(-m_bearingDist * 0.25, m_ydim - m_plateThickness));
  points.append(OdGePoint2d(m_bearingDist * 0.25, m_ydim - m_plateThickness));

  // right bearing
  double rightBearingCenter = m_bearingDist;
  points.append(OdGePoint2d(rightBearingCenter - bearingHalfXDim, 0.));
  points.append(OdGePoint2d(rightBearingCenter + bearingHalfXDim, 0.));

  // right wing
  points.append(OdGePoint2d(right - m_wingWidth, m_ydim - m_plateThickness));
  points.append(OdGePoint2d(right, m_ydim - m_plateThickness * 0.5));
  points.append(OdGePoint2d(right, m_ydim));

  // return back to start
  points.append(OdGePoint2d(left, m_ydim));*/

  return profileBuilder->createArbitraryClosedProfileDef(
    IfcProfileBuilder::kAREA, name, points);
}

OdIfc::OdIfcEntityPtr ExAbutment::subProcess()
{
  //
  // Pier 3d representation
  //
  OdIfc::OdIfcEntityPtr grc = m_b->filler()->getGeometricRepresentationContext("Model");
  if (grc.isNull())
  {
    ODA_ASSERT("Not convenient graphic representation context found.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcModelPtr model = m_b->filler()->model();

  OdIfc::OdIfcEntityPtr pSR = model->createEntityInstance("ifcshaperepresentation");
  pSR->putAttr("contextofitems", OdDAIObjectId(grc->id()));

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
  extrudeBase->putAttr("depth", m_height);
  extrudeBase->putAttr("extrudeddirection", m_b->filler()->dirZ());
  OdDAIObjectId idExtrude = model->appendEntityInstance(extrudeBase);
  setStyledItem(extrudeBase, "AbutmentBrick");

  OdAnsiString strBody("Body");
  OdAnsiString strType("CSG");
  pSR->putAttr("representationidentifier", strBody);
  pSR->putAttr("representationtype", strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, idExtrude);
  model->appendEntityInstance(pSR);
  return pSR;
}

ExAbutment::ExAbutment(
  const OdGeMatrix3d &objectPlacement,
  double xdim,
  double ydim,
  double height
)
  : IfcRepresentationAdapter(objectPlacement)
  , m_xdim(xdim)
  , m_ydim(ydim)
  , m_height(height)
{}
