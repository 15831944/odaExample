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
#include "ExPile.h"

OdIfc::OdIfcEntityPtr ExPile::subProcess()
{
  //
  // Pile 3d representation
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
  // Circular base
  //
  OdIfc::OdIfcEntityPtr profile = m_b->createProfileBuilder()->createCircleProfileDef(IfcProfileBuilder::kAREA, "Pile_Circular_Profile", m_r);

  //
  // Lower than owning product level
  //
  OdGePoint3d pos(0., 0., -m_height);
  OdGeMatrix3d mPos;
  mPos.setToTranslation(pos.asVector());
  OdIfc::OdIfcEntityPtr positionInst = m_b->filler()->createAxis2Placement3D(mPos);

  OdIfc::OdIfcEntityPtr extrudeBase = model->createEntityInstance("ifcextrudedareasolid");
  extrudeBase->putAttr("sweptarea", OdDAIObjectId(profile->id()));
  extrudeBase->putAttr("depth", m_height);
  extrudeBase->putAttr("extrudeddirection", m_b->filler()->dirZ());
  extrudeBase->putAttr("position", OdDAIObjectId(positionInst->id()));
  OdDAIObjectId idExtrudeBase = model->appendEntityInstance(extrudeBase);
  setStyledItem(extrudeBase, "ConcreteLight");

  OdAnsiString strBody("Body");
  OdAnsiString strType("CSG");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, idExtrudeBase);
  model->appendEntityInstance(pSR);

  m_b->getProduct()->putAttr("predefinedtype", OdAnsiString("BORED"));
  m_b->getProduct()->putAttr("constructiontype ", OdAnsiString("CAST_IN_PLACE"));
  return pSR;
}

ExPile::ExPile(
  const OdGeMatrix3d &objectPlacement,
  double r,
  double height
)
  : IfcRepresentationAdapter(objectPlacement)
  , m_r(r)
  , m_height(height)
{}
