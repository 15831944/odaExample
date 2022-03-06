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
#include "Ge/GeCylinder.h"
#include "Ge/GeEllipArc3d.h"
#include "PrcCategory1LineStyle.h"

OdPrcBrepDataPtr createCylinder(OdPrcHostAppServices& pHostApp, OdPrcFileStructure &newStructure, OdGeExtents3d& extents)
{
  OdBrepBuilder bbuilder;
  pHostApp.brepBuilder(bbuilder, kOpenShell);

  // Create connex
  BRepBuilderGeometryId complexId = bbuilder.addComplex();

  // Create shell
  BRepBuilderGeometryId shellId = bbuilder.addShell(complexId);

  OdGeInterval intrvlV(-50., 50.);
  OdSharedPtr <OdGeCylinder> cylSurf(new OdGeCylinder(50, OdGePoint3d(50, -100, 250), OdGeVector3d(0, 0, 1), OdGeVector3d(0, 1, 0), intrvlV, 0, Oda2PI));

  OdSharedPtr <OdGePlane> top = new OdGePlane(OdGePoint3d(0, 0, 300), OdGeVector3d(1, 0, 0), OdGeVector3d(0, 1, 0));
  OdSharedPtr <OdGePlane> bottom = new OdGePlane(OdGePoint3d(0, 0, 200), OdGeVector3d(1, 0, 0), OdGeVector3d(0, 1, 0));

  // Add Faces
  BRepBuilderGeometryId cylFaceId = bbuilder.addFace(cylSurf.get(), OdBrepBuilder::kForward, shellId);
  BRepBuilderGeometryId topFaceId = bbuilder.addFace(top.get(), OdBrepBuilder::kForward, shellId);
  BRepBuilderGeometryId bottomFaceId = bbuilder.addFace(bottom.get(), OdBrepBuilder::kReversed, shellId);

  // Set faces materials
  OdDbStub* cylinder_colorId = OdPrcCategory1LineStyle::createByColor(1.0, 0.0, 0.0, newStructure);
  OdDbStub* bottom_colorId = OdPrcCategory1LineStyle::createByColor(0.0, 1.0, 0.0, newStructure);
  OdDbStub* top_colorId = OdPrcCategory1LineStyle::createByColor(0.0, 0.0, 1.0, newStructure);
  bbuilder.setFacesMaterial(cylFaceId, *cylinder_colorId);
  bbuilder.setFacesMaterial(topFaceId, *bottom_colorId);
  bbuilder.setFacesMaterial(bottomFaceId, *top_colorId);

  OdSharedPtr <OdGeEllipArc3d> edgeBottom = new OdGeEllipArc3d(OdGePoint3d(50, -100, 200), OdGeVector3d::kXAxis, -OdGeVector3d::kYAxis, 50, 50, 0, Oda2PI);
  OdSharedPtr <OdGeEllipArc3d> edgeTop = new OdGeEllipArc3d(OdGePoint3d(50, -100, 300), OdGeVector3d::kXAxis, OdGeVector3d::kYAxis, 50, 50, 0, Oda2PI);

  BRepBuilderGeometryId edgeBottomId = bbuilder.addEdge(edgeBottom.get());
  BRepBuilderGeometryId edgeTopId = bbuilder.addEdge(edgeTop.get());

  BRepBuilderGeometryId loopId_cylTop = bbuilder.addLoop(cylFaceId);
  BRepBuilderGeometryId loopId_cylBottom = bbuilder.addLoop(cylFaceId);
  BRepBuilderGeometryId loopId_Top = bbuilder.addLoop(topFaceId);
  BRepBuilderGeometryId loopId_Bottom = bbuilder.addLoop(bottomFaceId);
  bbuilder.finishFace(cylFaceId);
  bbuilder.finishFace(topFaceId);
  bbuilder.finishFace(bottomFaceId);

  bbuilder.addCoedge(loopId_cylTop, edgeTopId, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_cylBottom, edgeBottomId, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Top, edgeTopId, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Bottom, edgeBottomId, OdBrepBuilder::kForward);
  bbuilder.finishLoop(loopId_cylTop);
  bbuilder.finishLoop(loopId_cylBottom);
  bbuilder.finishLoop(loopId_Top);
  bbuilder.finishLoop(loopId_Bottom);

  bbuilder.finishShell(shellId);
  bbuilder.finishComplex(complexId);

  extents.set(OdGePoint3d(0, -150, 200), OdGePoint3d(100, -50, 300));

  return bbuilder.finish();
}
