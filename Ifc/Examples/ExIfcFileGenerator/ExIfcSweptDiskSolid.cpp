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

// ExIfcFixedReferenceSweptAreaSolid3.cpp: implementation of the ExIfcFixedReferenceSweptAreaSolid3 class.
//
//////////////////////////////////////////////////////////////////////

#include "ExIfcSweptDiskSolid.h"
#include "ExIfcModelFiller.h"



OdIfc::OdIfcEntityPtr ExIfcSweptDiskSolid::subProcess()
{
  OdIfc::OdIfcEntityPtr grc = m_b->filler()->getGeometricRepresentationContext("Model");
  if (grc.isNull())
  {
    ODA_FAIL_M_ONCE("Not convenient graphic representation context found.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcModelPtr model = m_b->filler()->model();

  OdIfc::OdIfcEntityPtr pSR = model->createEntityInstance("ifcshaperepresentation");
  pSR->putAttr(OdIfc::kContextOfItems, OdDAIObjectId(grc->id()));

  //
  OdGePoint3d path1Points[] =
  {
    m_pathScale * OdGePoint3d(0., 0., 0.),
    m_pathScale * OdGePoint3d(1., 0., 0.),
    m_pathScale * OdGePoint3d(1., 1., 0.),
    m_pathScale * OdGePoint3d(2., 1., 0.),
  };
  OdIfc::OdIfcEntityPtr path1Ent = m_b->createPolyline(OdGePoint3dArray::create(path1Points, sizeof(path1Points) / sizeof(*path1Points)));
  OdIfc::OdIfcEntityPtr sweptDisk1 = m_b->createSweptDiskSolid(path1Ent, m_profileScale * 2., m_profileScale * 1.3);

  //
  OdGePoint3d path2Points[] =
  {
    m_pathScale * OdGePoint3d(0.5, -1, 0.),
    m_pathScale * OdGePoint3d(0.5, 2., 0.),
    m_pathScale * OdGePoint3d(1.5, 2., 0.),
    m_pathScale * OdGePoint3d(1.5, -1., 0.),
  };
  OdIfc::OdIfcEntityPtr path2Ent = m_b->createPolyline(OdGePoint3dArray::create(path2Points, sizeof(path2Points) / sizeof(*path2Points)));
  OdIfc::OdIfcEntityPtr sweptDisk2 = m_b->createSweptDiskSolid(path2Ent, m_profileScale, 0.);

  OdIfc::OdIfcEntityPtr resultBody = m_b->createIfcBooleanResult(sweptDisk1, sweptDisk2, "union");
  setStyledItem(resultBody, "Dark");

  OdAnsiString strBody("Body");
  OdAnsiString strType("SweptSolid");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, OdDAIObjectId(resultBody->id()));
  model->appendEntityInstance(pSR);

  return pSR;
}

ExIfcSweptDiskSolid::ExIfcSweptDiskSolid(
  const OdGeMatrix3d &objectPlacement,
  double profileScale,
  double pathScale
)
  : IfcRepresentationAdapter(objectPlacement)
  , m_profileScale(profileScale)
  , m_pathScale(pathScale)
{}
