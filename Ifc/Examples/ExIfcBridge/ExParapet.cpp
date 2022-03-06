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
#include "ExParapet.h"

OdIfc::OdIfcEntityPtr ExParapet::createBaseProfileBig(const OdAnsiString &name)
{
  IfcProfileBuilderPtr profileBuilder = m_b->createProfileBuilder();
  return profileBuilder->createRectangleProfileDef(IfcProfileBuilder::kAREA, name, m_width, m_width * 3.);

  /*double right = m_width * 0.5;
  double left = -right;
  double top = m_width * 1.5;
  double bottom = -m_width * 1.5;
  double h = m_height;

  OdGePoint2dArray points;

  IfcProfileBuilderPtr profileBuilder = m_b->createProfileBuilder();

  points.append(OdGePoint2d(left, bottom));
  points.append(OdGePoint2d(right, bottom));
  points.append(OdGePoint2d(right, top));
  points.append(OdGePoint2d(left, top));

  return profileBuilder->createArbitraryClosedProfileDef(
    name, IfcProfileBuilder::kAREA, points);*/
}

OdIfc::OdIfcEntityPtr ExParapet::createBaseProfile(const OdAnsiString &name)
{
  IfcProfileBuilderPtr profileBuilder = m_b->createProfileBuilder();
  return profileBuilder->createRectangleProfileDef(IfcProfileBuilder::kAREA, name, m_width, m_width);

  /*double right = m_width * 0.5;
  double left = -right;
  double top = right;
  double bottom = left;
  double h = m_height;

  OdGePoint2dArray points;

  IfcProfileBuilderPtr profileBuilder = m_b->createProfileBuilder();

  points.append(OdGePoint2d(left, bottom));
  points.append(OdGePoint2d(right, bottom));
  points.append(OdGePoint2d(right, top));
  points.append(OdGePoint2d(left, top));

  return profileBuilder->createArbitraryClosedProfileDef(
    IfcProfileBuilder::kAREA, name, points);*/
}

OdIfc::OdIfcEntityPtr ExParapet::createBaseProfileSmall(const OdAnsiString &name)
{
  double right = m_width * 0.25;
  double left = -right;
  double top = right;
  double bottom = left;
  double h = m_height;

  OdGePoint2dArray points;

  IfcProfileBuilderPtr profileBuilder = m_b->createProfileBuilder();

  points.append(OdGePoint2d(left, bottom));
  points.append(OdGePoint2d(right, bottom));
  points.append(OdGePoint2d(right, top));
  points.append(OdGePoint2d(left, top));

  return profileBuilder->createArbitraryClosedProfileDef(
    IfcProfileBuilder::kAREA, name, points);
}

OdIfc::OdIfcEntityPtr ExParapet::subProcess()
{
  //
  // Parapet parent representation context
  //
  OdIfc::OdIfcEntityPtr grc = m_b->filler()->getGeometricRepresentationContext("Model");
  if (grc.isNull())
  {
    ODA_ASSERT("Not convenient graphic representation context found.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcModelPtr model = m_b->filler()->model();

  //
  // Parapet 3d representation
  //
  OdIfc::OdIfcEntityPtr baseProfile = createBaseProfile("parapet_base_profile");
  OdIfc::OdIfcEntityPtr baseProfileBig = createBaseProfileBig("parapet_base_profile_big");

  OdGeVector3d dir = m_endPoint - m_startPoint;
  double fullLen = dir.length();
  double segmLen = fullLen / (m_hrzSegmentsCount - 1);
  OdGePoint3d start(0., 0., 0.);
  OdGePoint3d end = dir.asPoint();
  dir.normalize();

  double vertSegmLenght = m_height / m_vrtSegmentsCount;

  OdIfc::OdIfcEntityPtr pSR = model->createEntityInstance("ifcshaperepresentation");
  pSR->putAttr(OdIfc::kContextOfItems, OdDAIObjectId(grc->id()));

  //
  // Railing columns generation
  //
  OdIfc::OdIfcEntityPtr baseProfileSmall = createBaseProfileSmall("parapet_base_profile");
  for (unsigned int i = 0; i < m_hrzSegmentsCount; ++i)
  {
    OdIfc::OdIfcEntityPtr positionInst;
    if (i > 0)
    {
      OdGePoint3d pos(start);
      pos += (segmLen * i) * dir;
      OdGeMatrix3d mPos;
      mPos.setToTranslation(pos.asVector());
      positionInst = m_b->filler()->createAxis2Placement3D(mPos);
    }

    // base
    OdIfc::OdIfcEntityPtr extrudeBase = model->createEntityInstance("ifcextrudedareasolid");
    
    // IfcSweptAreaSolid attributes
    extrudeBase->putAttr("sweptarea", OdDAIObjectId(baseProfileBig->id()));
    if (!positionInst.isNull())
    {
      extrudeBase->putAttr("position", OdDAIObjectId(positionInst->id()));
    }

    // IfcExtrudedAreaSolid attributes
    extrudeBase->putAttr("depth", m_height * 0.05);
    extrudeBase->putAttr("extrudeddirection", m_b->filler()->dirZ());

    OdDAIObjectId idExtrudeBase = model->appendEntityInstance(extrudeBase);

    // column
    OdIfc::OdIfcEntityPtr extrudeColumn = model->createEntityInstance("ifcextrudedareasolid");

    // IfcSweptAreaSolid attributes
    extrudeColumn->putAttr("sweptarea", OdDAIObjectId(baseProfile->id()));
    if (!positionInst.isNull())
    {
      extrudeColumn->putAttr("position", OdDAIObjectId(positionInst->id()));
    }

    // IfcExtrudedAreaSolid attributes
    extrudeColumn->putAttr("depth", m_height);
    extrudeColumn->putAttr("extrudeddirection", m_b->filler()->dirZ());

    OdDAIObjectId idExtrudeColumn = model->appendEntityInstance(extrudeColumn);

    OdIfc::OdIfcEntityPtr booleanResult = m_b->createIfcBooleanResult(extrudeBase, extrudeColumn, "union");

    OdAnsiString strBody("Body");
    OdAnsiString strType("CSG");
    pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
    pSR->putAttr(OdIfc::kRepresentationType, strType);
    m_b->filler()->appendId(pSR, OdIfc::kItems, OdDAIObjectId(booleanResult->id()));

    setStyledItem(booleanResult, "ConcreteLight");
  }

  //
  // Railing strings generation
  //
  for (unsigned int i = 0; i < m_vrtSegmentsCount; ++i)
  {
    OdGeMatrix3d mPlacement = OdGeMatrix3d::rotation(OdaPI, OdGeVector3d::kZAxis);
    mPlacement *= OdGeMatrix3d::rotation(OdaPI2, OdGeVector3d::kXAxis);
    OdGePoint3d elevation(0., 0., vertSegmLenght * (i + 1));
    mPlacement.setTranslation(elevation.asVector());
    OdIfc::OdIfcEntityPtr positionInst = m_b->filler()->createAxis2Placement3D(mPlacement);

    OdIfc::OdIfcEntityPtr extrudeBase = model->createEntityInstance("ifcextrudedareasolid");

    // IfcSweptAreaSolid attributes
    extrudeBase->putAttr("sweptarea", i < m_vrtSegmentsCount - 1 ? OdDAIObjectId(baseProfileSmall->id()) : OdDAIObjectId(baseProfile->id()));
    if (!positionInst.isNull())
    {
      extrudeBase->putAttr("position", OdDAIObjectId(positionInst->id()));
    }

    // IfcExtrudedAreaSolid attributes
    extrudeBase->putAttr("depth", fullLen);
    extrudeBase->putAttr("extrudeddirection", m_b->filler()->dirZ());

    OdDAIObjectId idExtrude = model->appendEntityInstance(extrudeBase);

    OdAnsiString strBody("Body");
    OdAnsiString strType("CSG");
    pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
    pSR->putAttr(OdIfc::kRepresentationType, strType);
    m_b->filler()->appendId(pSR, OdIfc::kItems, idExtrude);

    setStyledItem(extrudeBase, "RailingSteel");
  }

  model->appendEntityInstance(pSR);

  OdAnsiString strRailingType("guardrail");
  m_b->getProduct()->putAttr("predefinedtype", strRailingType);

  return pSR;
}

ExParapet::ExParapet(
  const OdGePoint3d &startPoint,
  const OdGePoint3d &endPoint,
  const OdAnsiString &name,

  double heigth,
  double width,
  unsigned int hrzSegmentsCount,
  unsigned int vrtSegmentsCount
)
  : m_name(name)
  , m_startPoint(startPoint)
  , m_endPoint(endPoint)
  , m_height(heigth)
  , m_width(width)
  , m_hrzSegmentsCount(hrzSegmentsCount)
  , m_vrtSegmentsCount(vrtSegmentsCount)
{
  if (m_vrtSegmentsCount < 2)
    m_vrtSegmentsCount = 2;
  if (m_hrzSegmentsCount < 2)
    m_hrzSegmentsCount = 2;
  //m_objectPlacement.setTranslation(startPoint.asVector());
}
