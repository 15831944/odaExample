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
#include "ExPier.h"

OdIfc::OdIfcEntityPtr ExPier::subProcess()
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
  pSR->putAttr(OdIfc::kContextOfItems, OdDAIObjectId(grc->id()));

  OdAnsiString strProfileType("area");

  //
  // Rectangular column
  //
  OdIfc::OdIfcEntityPtr columnProfileDef = model->createEntityInstance("ifcroundedrectangleprofiledef");
  columnProfileDef->putAttr("profiletype", strProfileType);
  columnProfileDef->putAttr("xdim", m_xdimColumn);
  columnProfileDef->putAttr("ydim", m_ydimColumn);
  columnProfileDef->putAttr("roundingradius", m_fillet_r);
  OdDAIObjectId idProfile = model->appendEntityInstance(columnProfileDef);

  OdIfc::OdIfcEntityPtr extrudeBase = m_b->createExtrudedAreaSolid(columnProfileDef, m_fullHeight - m_capHeight * 0.5, m_b->filler()->dirZ());

  //
  // Pier cap
  //

  /*
  OdIfc::OdIfcEntityPtr capProfileDef = model->createEntityInstance(OdIfc::kIfcRoundedRectangleProfileDef);
  capProfileDef->putAttr("profiletype", strProfileType);
  capProfileDef->putAttr("xdim", m_xdimCap);
  capProfileDef->putAttr("ydim", m_ydimCap);
  capProfileDef->putAttr("roundingradius", m_fillet_r);
  OdDAIObjectId idCapProfile = model->appendEntityInstance(capProfileDef);

  OdGeMatrix3d mCapPos;
  OdGeVector3d vCapPos(0., 0., m_fullHeight - m_capHeight);
  mCapPos.setTranslation(vCapPos);
  OdIfc::OdIfcEntityPtr capPos = m_b->filler()->createAxis2Placement3D(mCapPos);

  OdIfc::OdIfcEntityPtr extrudeCap = m_b->createExtrudedAreaSolid(capProfileDef, m_capHeight, m_b->filler()->dirZ());
  extrudeCap->putAttr("position", OdDAIObjectId(capPos->id()));
  */

  IfcProfileBuilderPtr profileBuilder = m_b->createProfileBuilder();
  OdGePoint2dArray points;
  points.append(OdGePoint2d(-m_xdimCap * 0.5, 0.));
  points.append(OdGePoint2d(-m_xdimCap * 0.5 - m_capWing, m_bearingThickness));
  points.append(OdGePoint2d(-m_xdimCap * 0.5 - m_capWing, -m_bearingThickness));
  points.append(OdGePoint2d(-m_xdimCap * 0.5, -m_capHeight * 0.75));
  points.append(OdGePoint2d(0, -m_capHeight));
  points.append(OdGePoint2d(m_xdimCap * 0.5, -m_capHeight * 0.75));
  points.append(OdGePoint2d(m_xdimCap * 0.5 + m_capWing, -m_bearingThickness));
  points.append(OdGePoint2d(m_xdimCap * 0.5 + m_capWing, m_bearingThickness));
  points.append(OdGePoint2d(m_xdimCap * 0.5, 0.));
  OdIfc::OdIfcEntityPtr capProfileDef = profileBuilder->createArbitraryClosedProfileDef(IfcProfileBuilder::kAREA, "pier_cap_profile", points);

  // TODO: As IfcSectionedSolidHorizontal
  OdGeMatrix3d mPlacement = OdGeMatrix3d::rotation(OdaPI, OdGeVector3d::kZAxis);
  mPlacement *= OdGeMatrix3d::rotation(OdaPI2, OdGeVector3d::kXAxis);
  OdGePoint3d elevation(0., -m_ydimCap * 0.5, m_fullHeight);
  mPlacement.setTranslation(elevation.asVector());
  OdIfc::OdIfcEntityPtr positionInst = m_b->filler()->createAxis2Placement3D(mPlacement);

  OdIfc::OdIfcEntityPtr extrudeCap = m_b->createExtrudedAreaSolid(capProfileDef, m_capHeight, m_b->filler()->dirZ());
  extrudeCap->putAttr("position", OdDAIObjectId(positionInst->id()));

  OdIfc::OdIfcEntityPtr booleanResult = m_b->createIfcBooleanResult(extrudeBase, extrudeCap, "union");
  setStyledItem(booleanResult, "ConcreteDark");

  OdAnsiString strBody("Body");
  OdAnsiString strType("CSG");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, OdDAIObjectId(booleanResult->id()));
  //m_b->filler()->appendId(pSR, OdIfc::kItems, idExtrude1);
  //m_b->filler()->appendId(pSR, OdIfc::kItems, idExtrudeCap);
  model->appendEntityInstance(pSR);

  OdAnsiString strPierStem("pierstem");
  m_b->getProduct()->putAttr("predefinedtype", strPierStem);

  return pSR;
}

ExPier::ExPier(
  const OdGeMatrix3d &objectPlacement,
  double fullHeight,
  double xdimColumn,
  double ydimColumn,
  double fillet_r,
  double xdimCap,
  double ydimCap,
  double capHeight,
  double capWing,
  double bearingThickness
)
  : IfcRepresentationAdapter(objectPlacement)
  , m_fullHeight(fullHeight)
  , m_xdimColumn(xdimColumn)
  , m_ydimColumn(ydimColumn)
  , m_fillet_r(fillet_r)
  , m_xdimCap(xdimCap)
  , m_ydimCap(ydimCap)
  , m_capHeight(capHeight)
  , m_capWing(capWing)
  , m_bearingThickness(bearingThickness)
{}
