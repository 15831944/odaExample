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
#include "Ge/GePlane.h"
#include "Ge/GeCone.h"
#include "Ge/GeEllipArc3d.h"
#include "Ge/GeLineSeg3d.h"
#include "PrcCategory1LineStyle.h"

OdPrcBrepDataPtr createCone(OdPrcHostAppServices& pHostApp, OdPrcFileStructure &newStructure, OdGeExtents3d& extents)
{
  OdBrepBuilder bbuilder;
  pHostApp.brepBuilder(bbuilder, kOpenShell);

  // Create connex
  BRepBuilderGeometryId complexId = bbuilder.addComplex();

  // Create shell
  BRepBuilderGeometryId shellId = bbuilder.addShell(complexId);

  OdGeInterval intrvl(-51., 50.);
  OdSharedPtr <OdGeCone> coneSurf(new OdGeCone(0.89442719099991586, -0.44721359549995793, OdGePoint3d::kOrigin, 25, OdGeVector3d::kZAxis, OdGeVector3d::kXAxis, intrvl, -OdaPI, OdaPI));
  OdSharedPtr <OdGePlane> bottom = new OdGePlane(OdGePoint3d(0, 0, -50), OdGeVector3d(1, 0, 0), OdGeVector3d(0, 1, 0));

  // Add Faces
  BRepBuilderGeometryId coneFaceId = bbuilder.addFace(coneSurf.get(), OdBrepBuilder::kForward, shellId);
  BRepBuilderGeometryId bottomFaceId = bbuilder.addFace(bottom.get(), OdBrepBuilder::kReversed, shellId);

  // Set faces materials
  OdDbStub* cone_colorId = OdPrcCategory1LineStyle::createByColor(1.0, 0.0, 0.0, newStructure);
  OdDbStub* bottom_colorId = OdPrcCategory1LineStyle::createByColor(0.0, 1.0, 0.0, newStructure);
  bbuilder.setFacesMaterial(coneFaceId, *cone_colorId);
  bbuilder.setFacesMaterial(bottomFaceId, *bottom_colorId);

  // Create Edges
  OdSharedPtr <OdGeEllipArc3d> edgeBottom = new OdGeEllipArc3d(OdGePoint3d(0, 0, -50), OdGeVector3d::kXAxis, -OdGeVector3d::kYAxis, 50, 50, 0, Oda2PI);
  OdSharedPtr <OdGeLineSeg3d> edgeApex = new OdGeLineSeg3d(OdGePoint3d(0, 0, 50), OdGePoint3d(0, 0, 50));

  BRepBuilderGeometryId edgeBottomId = bbuilder.addEdge(edgeBottom.get());
  BRepBuilderGeometryId edgeApexId = bbuilder.addEdge(edgeApex.get());

  BRepBuilderGeometryId loopId_coneBottom = bbuilder.addLoop(coneFaceId);
  BRepBuilderGeometryId loopId_coneApex = bbuilder.addLoop(coneFaceId);
  BRepBuilderGeometryId loopId_Bottom = bbuilder.addLoop(bottomFaceId);
  bbuilder.finishFace(coneFaceId);
  bbuilder.finishFace(bottomFaceId);

  bbuilder.addCoedge(loopId_coneBottom, edgeBottomId, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_coneApex, edgeApexId, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Bottom, edgeBottomId, OdBrepBuilder::kForward);
  bbuilder.finishLoop(loopId_coneBottom);
  bbuilder.finishLoop(loopId_coneApex);
  bbuilder.finishLoop(loopId_Bottom);

  bbuilder.finishShell(shellId);
  bbuilder.finishComplex(complexId);

  extents.set(OdGePoint3d(-50, -50, -50), OdGePoint3d(50, 50, 50));

  return bbuilder.finish();
}
