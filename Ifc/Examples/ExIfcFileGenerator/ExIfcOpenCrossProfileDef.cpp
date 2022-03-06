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

// ExIfcOpenCrossProfileDef.cpp: implementation of the ExIfcOpenCrossProfileDef class.
//
//////////////////////////////////////////////////////////////////////

#include "ExIfcOpenCrossProfileDef.h"
#include "ExIfcModelFiller.h"

OdIfc::OdIfcEntityPtr ExIfcOpenCrossProfileDef::subProcess()
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
  //////////////

  OdArray<double> widths;
  widths.append(m_profileScale * 5.);
  widths.append(m_profileScale * 5.);
  widths.append(m_profileScale * 5.);
  widths.append(m_profileScale * 5.);

  OdArray<double> slopes;
  slopes.append(0);
  slopes.append(1.57);
  slopes.append(3.14);
  slopes.append(-1.57);

  // TODO: Add offsetPoint to createOpenCrossProfileDef function, when it will be support by OdIfcOpenCrossProfileDef class.
  OdIfc::OdIfcEntityPtr profile = m_b->createProfileBuilder()->createOpenCrossProfileDef("OpenCross", false, widths, slopes);

  // All current areas don't support curve as profile type, so the profile draw closed with cap faces, but must be without and opened.
  // TODO: ExtrudedAreaSolid should be changed to SectionedSurface, when it will be implemented.
  OdIfc::OdIfcEntityPtr extrudedAreaSolid = m_b->createExtrudedAreaSolid(profile, m_pathScale, OdGeVector3d(0., 0., 1.));

  //////////////
  OdAnsiString strBody("Body");
  OdAnsiString strType("ExtrudedSolid");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  m_b->filler()->appendId(pSR, OdIfc::kItems, OdDAIObjectId(extrudedAreaSolid->id()));
  model->appendEntityInstance(pSR);

  return pSR;
}

ExIfcOpenCrossProfileDef::ExIfcOpenCrossProfileDef(
  const OdGeMatrix3d& objectPlacement,
  double profileScale,
  double pathScale
)
  : IfcRepresentationAdapter(objectPlacement)
  , m_profileScale(profileScale)
  , m_pathScale(pathScale)
{}
