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
#include "ExReinforcingMeshCirc.h"

OdIfc::OdIfcEntityPtr ExReinforcingMeshCirc::appendRebarVertical(double x, double y)
{
  double offsetFromBottom = 100.;
  double rebarRadius = m_rebarDiam * 0.5;

  OdGePoint3dArray points;
  points.append(OdGePoint3d(x, y, -m_height + offsetFromBottom));
  points.append(OdGePoint3d(x, y, m_topOffset));
  OdIfc::OdIfcEntityPtr polyline = m_b->createPolyline(points);

  OdIfcModelPtr model = m_b->filler()->model();
  OdIfc::OdIfcEntityPtr sweptDiskSolid = model->createEntityInstance("ifcsweptdisksolid");
  sweptDiskSolid->putAttr("directrix", OdDAIObjectId(polyline->id()));
  sweptDiskSolid->putAttr("radius", rebarRadius);
  model->appendEntityInstance(sweptDiskSolid);
  setStyledItem(sweptDiskSolid, "RebarSteel");
  return sweptDiskSolid;
}

OdIfc::OdIfcEntityPtr ExReinforcingMeshCirc::subProcess()
{
  //
  // Circular reinforcing mesh 3d representation
  //
  OdIfc::OdIfcEntityPtr pSR = m_b->filler()->createShapeRepresentation("Model", "Body", "AdvancedSweptSolid");
  if (pSR.isNull())
  {
    ODA_FAIL_M("Can not create shape representation for Reinforcing Mesh.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcModelPtr model = m_b->filler()->model();

  //
  // Lower than owning product level
  //

  if (m_centralRebar)
  {
    OdIfc::OdIfcEntityPtr sweptDiskSolid = appendRebarVertical(0, 0);
    m_b->filler()->appendId(pSR, OdIfc::kItems, OdDAIObjectId(sweptDiskSolid->id()));
  }

  if (m_numAngular < 3)
    m_numAngular = 3;
  if (m_numRadial < 1)
    m_numRadial = 1;

  double angStep = Oda2PI / m_numAngular;
  double rStep = m_r / m_numRadial;
  for (unsigned int rad = 1; rad <= m_numRadial; ++rad)
  {
    for (unsigned int ang = 0; ang < m_numAngular; ++ang)
    {
      double x = rStep * rad * cos(angStep * ang);
      double y = rStep * rad * sin(angStep * ang);
      OdIfc::OdIfcEntityPtr sweptDiskSolid = appendRebarVertical(x, y);
      m_b->filler()->appendId(pSR, OdIfc::kItems, OdDAIObjectId(sweptDiskSolid->id()));
    }
  }

  double radius = m_rebarDiam * 0.5;
  int totalCount = (int)m_centralRebar + angStep * rStep;
  double reinforcingLength = m_height + m_topOffset;
  double reinforcingVolume =  OdaPI * radius * radius * (m_height + m_topOffset);

  IfcQuantitySetFillerPtr qs = m_b->filler()->createQuantitySet(m_b->getProduct());
  qs->
    appendQuantityCount("Count", totalCount, "").
    appendQuantityLength("Length", reinforcingLength, "").
    createQuantitySet("Qto_ReinforcingElementBaseQuantities");

  model->appendEntityInstance(pSR);
  m_b->getProduct()->putAttr("meshlength", reinforcingLength);
  m_b->getProduct()->putAttr("meshwidth", m_r * 2);
  m_b->getProduct()->putAttr("longitudinalbarnominaldiameter", 2.);
  m_b->getProduct()->putAttr("transversebarnominaldiameter", 2.);
  m_b->getProduct()->putAttr("predefinedtype", OdAnsiString("notdefined"));
  return pSR;
}

ExReinforcingMeshCirc::ExReinforcingMeshCirc(
  const OdGeMatrix3d &objectPlacement,
  double r,
  double height,
  double topOffset,
  double rebarDiam,
  bool centralRebar,
  unsigned int numAngular,
  unsigned int numRadial
)
  : IfcRepresentationAdapter(objectPlacement)
  , m_r(r)
  , m_height(height)
  , m_topOffset(topOffset)
  , m_rebarDiam(rebarDiam)
  , m_centralRebar(centralRebar)
  , m_numAngular(numAngular)
  , m_numRadial(numRadial)
{}
