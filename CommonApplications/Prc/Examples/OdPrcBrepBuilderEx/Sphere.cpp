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

#include "PrcCommon.h"
#include "ExPrcHostAppServices.h"
#include "PrcBrepData.h"
#include "Ge/GeSphere.h"
#include "PrcCategory1LineStyle.h"

OdPrcBrepDataPtr createSphere(OdPrcHostAppServices& pHostApp, OdPrcFileStructure &newStructure, OdGeExtents3d& extents)
{
  OdBrepBuilder bbuilder;
  pHostApp.brepBuilder(bbuilder, kOpenShell);

  // Create connex
  BRepBuilderGeometryId complexId = bbuilder.addComplex();

  // Create shell
  BRepBuilderGeometryId shellId = bbuilder.addShell(complexId);

  OdSharedPtr <OdGeSphere> sphereSurf(new OdGeSphere(50., OdGePoint3d::kOrigin, OdGeVector3d::kZAxis, OdGeVector3d::kXAxis, -OdaPI2, OdaPI2, -OdaPI, OdaPI));
  BRepBuilderGeometryId sphereFaceId = bbuilder.addFace(sphereSurf.get(), OdBrepBuilder::kForward, shellId);
  bbuilder.finishFace(sphereFaceId);

  // Set faces materials
  OdDbStub* sphere_colorId = OdPrcCategory1LineStyle::createByColor(0.0, 1.0, 0.0, newStructure);
  bbuilder.setFacesMaterial(sphereFaceId, *sphere_colorId);

  bbuilder.finishShell(shellId);
  bbuilder.finishComplex(complexId);

  extents.set(OdGePoint3d(-50, -50, -50), OdGePoint3d(50, 50, 50));

  return bbuilder.finish();
}
