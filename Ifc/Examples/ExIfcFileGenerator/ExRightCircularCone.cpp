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
#include "ExRightCircularCone.h"

OdIfc::OdIfcEntityPtr ExRightCircularCone::subProcess()
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

  OdIfc::OdIfcEntityPtr cone = m_b->createRightCircularCone(m_objectPlacement, m_h, m_bR);

  if (m_createBoolean)
  {
    OdGeMatrix3d secondObjectPlacement = m_objectPlacement * OdGeMatrix3d().setTranslation(OdGeVector3d(0, 0, -0.5 * m_h));
    OdIfc::OdIfcEntityPtr block = m_b->createBlock(secondObjectPlacement, m_bR, m_bR, m_h);

    cone = m_b->createIfcBooleanResult(cone, block, "union");
  }
  setStyledItem(cone, "Dark");

  OdIfc::OdIfcEntityPtr pS = model->createEntityInstance("ifccsgsolid");
  pS->putAttr(OdIfc::kTreeRootExpression, OdDAIObjectId(cone->id()));
  model->appendEntityInstance(pS);

  OdAnsiString strBody("Body");
  OdAnsiString strType("CSG");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, OdDAIObjectId(pS->id()));
  model->appendEntityInstance(pSR);

  return pSR;
}

ExRightCircularCone::ExRightCircularCone(
  const OdGeMatrix3d &objectPlacement,
  double h,
  double bR,
  bool createBoolean
)
  : IfcRepresentationAdapter(objectPlacement)
  , m_h(h)
  , m_bR(bR)
  , m_createBoolean(createBoolean)
{}
