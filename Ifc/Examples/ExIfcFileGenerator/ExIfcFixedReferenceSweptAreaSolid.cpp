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
#include "ExIfcFixedReferenceSweptAreaSolid.h"

OdIfc::OdIfcEntityPtr ExIfcFixedReferenceSweptAreaSolid::subProcess()
{
  OdIfc::OdIfcEntityPtr grc = m_b->filler()->getGeometricRepresentationContext("Model");
  if (grc.isNull())
  {
    ODA_ASSERT("Not convenient graphic representation context found.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcModelPtr model = m_b->filler()->model();

  OdIfc::OdIfcEntityPtr pSR = model->createEntityInstance("ifcshaperepresentation");
  pSR->putAttr(OdIfc::kContextOfItems, OdDAIObjectId(grc->id()));

  OdGePoint2dArray profilePoints;
  profilePoints.append(OdGePoint2d(m_profileScale, m_profileScale));
  profilePoints.append(OdGePoint2d(m_profileScale, -m_profileScale));
  profilePoints.append(OdGePoint2d(-m_profileScale, -m_profileScale));
  profilePoints.append(OdGePoint2d(-m_profileScale, m_profileScale));
  OdIfc::OdIfcEntityPtr profileDef = m_b->createProfileBuilder()->createArbitraryClosedProfileDef(IfcProfileBuilder::kAREA, "swept_area_profile", profilePoints);

  OdGePoint3dArray curvePoints;
  curvePoints.append(OdGePoint3d(0, m_curveScale, m_curveScale));
  curvePoints.append(OdGePoint3d(0, m_curveScale, -m_curveScale));
  curvePoints.append(OdGePoint3d(0, -m_curveScale, -m_curveScale));
  curvePoints.append(OdGePoint3d(0, -m_curveScale, m_curveScale));
  OdIfc::OdIfcEntityPtr directrix = m_b->createPolyline(curvePoints);
  
  OdIfc::OdIfcEntityPtr sweptArea = m_b->createFixedReferenceSweptAreaSolid(profileDef, m_objectPlacement, directrix);
  OdGeMatrix3d secondObjectPlacement = m_objectPlacement * OdGeMatrix3d().setTranslation(OdGeVector3d(0, m_curveScale, m_curveScale));
  OdIfc::OdIfcEntityPtr sphere = m_b->createSphere(secondObjectPlacement, m_profileScale * 2);
  sweptArea = m_b->createIfcBooleanResult(sweptArea, sphere, "union");
  setStyledItem(sweptArea, "Dark");

  OdIfc::OdIfcEntityPtr pS = model->createEntityInstance("ifccsgsolid");
  pS->putAttr(OdIfc::kTreeRootExpression, OdDAIObjectId(sweptArea->id()));
  model->appendEntityInstance(pS);

  OdAnsiString strBody("Body");
  OdAnsiString strType("CSG");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, OdDAIObjectId(pS->id()));
  model->appendEntityInstance(pSR);

  return pSR;
}

ExIfcFixedReferenceSweptAreaSolid::ExIfcFixedReferenceSweptAreaSolid(
  const OdGeMatrix3d &objectPlacement,
  double profileScale,
  double curveScale
)
  : IfcRepresentationAdapter(objectPlacement)
  , m_profileScale(profileScale)
  , m_curveScale(curveScale)
{}
