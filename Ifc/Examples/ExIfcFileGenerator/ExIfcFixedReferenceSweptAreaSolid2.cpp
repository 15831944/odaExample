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

// ExIfcFixedReferenceSweptAreaSolid2.cpp: implementation of the ExIfcFixedReferenceSweptAreaSolid2 class.
//
//////////////////////////////////////////////////////////////////////

#include "ExIfcFixedReferenceSweptAreaSolid2.h"
#include "ExIfcModelFiller.h"

ExIfcFixedReferenceSweptAreaSolid2::ExIfcFixedReferenceSweptAreaSolid2(const OdGeMatrix3d& objectPlacement, double overallWidth, double overallDepth, double webThickness, double flangeThickness, double curveScale) 
  : IfcRepresentationAdapter(objectPlacement)
  , m_overallWidth(overallWidth)
  , m_overallDepth(overallDepth)
  , m_webThickness(webThickness)
  , m_flangeThickness(flangeThickness)
  , m_curveScale(curveScale)
{
}

OdIfc::OdIfcEntityPtr ExIfcFixedReferenceSweptAreaSolid2::subProcess()
{
  OdIfc::OdIfcEntityPtr pGRC = m_b->filler()->getGeometricRepresentationContext("Model");
  if (pGRC.isNull())
  {
    ODA_ASSERT("Not convenient graphic representation context found.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcModelPtr model = m_b->filler()->model();

  OdIfc::OdIfcEntityPtr pSR = model->createEntityInstance("ifcshaperepresentation");
  pSR->putAttr("contextofitems", OdDAIObjectId(pGRC->id()));

  OdGeMatrix2d position;
  OdGeVector2d trans(0.0, m_overallDepth * 0.5);
  position.setToTranslation(trans);
  OdIfc::OdIfcEntityPtr pPosition1 = m_b->filler()->createAxis2Placement2D(position);
  OdIfc::OdIfcEntityPtr pProfile = m_b->createProfileBuilder()->createIShapeProfileDef(IfcProfileBuilder::kAREA, "road_line_profile", pPosition1->id(), m_overallWidth, m_overallDepth, m_webThickness, m_flangeThickness);
  position.setToTranslation(-trans);
  OdIfc::OdIfcEntityPtr pPosition2 = m_b->filler()->createAxis2Placement2D(position);
  OdIfc::OdIfcEntityPtr pProfile2 = m_b->createProfileBuilder()->createIShapeProfileDef(IfcProfileBuilder::kAREA, "road_line_profile", pPosition2->id(), m_overallWidth, m_overallDepth, m_webThickness, m_flangeThickness);
  
  OdDAIObjectIds profileIds;
  profileIds.append(pProfile->id());
  profileIds.append(pProfile2->id());
  OdIfc::OdIfcEntityPtr pCompProfile = m_b->createProfileBuilder()->createCompositeProfileDef(IfcProfileBuilder::kAREA, "swept_area_profile", profileIds);

  OdGePoint3dArray curvePoints;
  curvePoints.append(OdGePoint3d(0, m_curveScale, m_curveScale));
  curvePoints.append(OdGePoint3d(m_curveScale * 0.1, m_curveScale * 0.3, m_curveScale * 0.3));
  curvePoints.append(OdGePoint3d(m_curveScale * 0.01, -m_curveScale * 0.3, -m_curveScale * 0.3));
  curvePoints.append(OdGePoint3d(0, -m_curveScale, -m_curveScale));
  OdIfc::OdIfcEntityPtr pDrectrix = m_b->createPolyline(curvePoints);

  OdGeVector3d zAxis = (curvePoints.at(1) - curvePoints.at(0)).normalize();
  OdGeVector3d yAxis = zAxis.perpVector();
  OdGeVector3d refVec = zAxis.crossProduct(yAxis);
  OdIfc::OdIfcEntityPtr sweptArea = m_b->createFixedReferenceSweptAreaSolid(pCompProfile, m_objectPlacement, pDrectrix, OdDAI::Consts::OdNan, OdDAI::Consts::OdNan, refVec);
  setStyledItem(sweptArea, "Dark");

  OdAnsiString strBody("Body");
  OdAnsiString strType("SweptSolid");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, OdDAIObjectId(sweptArea->id()));
  model->appendEntityInstance(pSR);

  return pSR;
}
