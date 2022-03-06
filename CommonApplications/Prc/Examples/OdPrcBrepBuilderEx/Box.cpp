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
#include "Ge/GeLineSeg3d.h"
#include "PrcCategory1LineStyle.h"

OdPrcBrepDataPtr createBox(OdPrcHostAppServices& pHostApp, OdPrcFileStructure &newStructure, OdGeExtents3d& extents)
{
  OdBrepBuilder bbuilder;
  pHostApp.brepBuilder(bbuilder, kOpenShell);

  // Create connex
  BRepBuilderGeometryId complexId = bbuilder.addComplex();

  // Create shell
  BRepBuilderGeometryId shellId = bbuilder.addShell(complexId);

  // Create surfaces (Plane)
  OdSharedPtr <OdGePlane> pSurfBottom = new OdGePlane(OdGePoint3d(50, 50, 0), OdGeVector3d::kXAxis, OdGeVector3d::kYAxis);
  OdSharedPtr <OdGePlane> pSurfTop = new OdGePlane(OdGePoint3d(0, 0, 100), OdGeVector3d::kXAxis, OdGeVector3d::kYAxis);
  OdSharedPtr <OdGePlane> pSurfFront = new OdGePlane(OdGePoint3d(100, 50, 50), OdGeVector3d::kZAxis, OdGeVector3d::kYAxis);
  OdSharedPtr <OdGePlane> pSurfBack = new OdGePlane(OdGePoint3d(0, 0, 0), OdGeVector3d::kZAxis, OdGeVector3d::kYAxis);
  OdSharedPtr <OdGePlane> pSurfLeft = new OdGePlane(OdGePoint3d(50, 0, 50), OdGeVector3d::kZAxis, OdGeVector3d::kXAxis);
  OdSharedPtr <OdGePlane> pSurfRight = new OdGePlane(OdGePoint3d(50, 100, 50), OdGeVector3d::kZAxis, OdGeVector3d::kXAxis);

  // Add Faces
  BRepBuilderGeometryId faceId_Bottom = bbuilder.addFace(pSurfBottom.get(), OdBrepBuilder::kReversed, shellId);
  BRepBuilderGeometryId faceId_Top = bbuilder.addFace(pSurfTop.get(), OdBrepBuilder::kForward, shellId);
  BRepBuilderGeometryId faceId_Front = bbuilder.addFace(pSurfFront.get(), OdBrepBuilder::kReversed, shellId);
  BRepBuilderGeometryId faceId_Back = bbuilder.addFace(pSurfBack.get(), OdBrepBuilder::kForward, shellId);
  BRepBuilderGeometryId faceId_Left = bbuilder.addFace(pSurfLeft.get(), OdBrepBuilder::kReversed, shellId);
  BRepBuilderGeometryId faceId_Right = bbuilder.addFace(pSurfRight.get(), OdBrepBuilder::kForward, shellId);

  // Set faces materials
  OdDbStub* bottom_colorId = OdPrcCategory1LineStyle::createByColor(1.0, 0.0, 0.0, newStructure);
  OdDbStub* top_colorId = OdPrcCategory1LineStyle::createByColor(0.0, 1.0, 0.0, newStructure);
  OdDbStub* front_colorId = OdPrcCategory1LineStyle::createByColor(1.0, 1.0, 0.0, newStructure);
  OdDbStub* back_colorId = OdPrcCategory1LineStyle::createByColor(0.0, 0.0, 1.0, newStructure);
  OdDbStub* left_colorId = OdPrcCategory1LineStyle::createByColor(1.0, 0.0, 1.0, newStructure);
  OdDbStub* right_colorId = OdPrcCategory1LineStyle::createByColor(0.0, 1.0, 1.0, newStructure);
  bbuilder.setFacesMaterial(faceId_Bottom, *bottom_colorId);
  bbuilder.setFacesMaterial(faceId_Top, *top_colorId);
  bbuilder.setFacesMaterial(faceId_Front, *front_colorId);
  bbuilder.setFacesMaterial(faceId_Back, *back_colorId);
  bbuilder.setFacesMaterial(faceId_Left, *left_colorId);
  bbuilder.setFacesMaterial(faceId_Right, *right_colorId);


  // Create Edges
  OdSharedPtr <OdGeLineSeg3d> edgeBottomFront = new OdGeLineSeg3d(OdGePoint3d(100.0, 0, 0), OdGePoint3d(100.0, 100.0, 0));
  OdSharedPtr <OdGeLineSeg3d> edgeBottomRight = new OdGeLineSeg3d(OdGePoint3d(100.0, 100.0, 0), OdGePoint3d(0, 100.0, 0));
  OdSharedPtr <OdGeLineSeg3d> edgeBottomBack = new OdGeLineSeg3d(OdGePoint3d(0, 100.0, 0), OdGePoint3d(0, 0, 0));
  OdSharedPtr <OdGeLineSeg3d> edgeBottomLeft = new OdGeLineSeg3d(OdGePoint3d(0, 0, 0), OdGePoint3d(100.0, 0, 0));

  OdSharedPtr <OdGeLineSeg3d> edgeTopFront = new OdGeLineSeg3d(OdGePoint3d(100, 0, 100), OdGePoint3d(100, 100, 100));
  OdSharedPtr <OdGeLineSeg3d> edgeTopRight = new OdGeLineSeg3d(OdGePoint3d(100, 100, 100), OdGePoint3d(0, 100, 100));
  OdSharedPtr <OdGeLineSeg3d> edgeTopBack = new OdGeLineSeg3d(OdGePoint3d(0, 100, 100), OdGePoint3d(0, 0, 100));
  OdSharedPtr <OdGeLineSeg3d> edgeTopLeft = new OdGeLineSeg3d(OdGePoint3d(0, 0, 100), OdGePoint3d(100, 0, 100));

  OdSharedPtr <OdGeLineSeg3d> edgeFrontRight = new OdGeLineSeg3d(OdGePoint3d(100, 100, 0), OdGePoint3d(100, 100, 100));
  OdSharedPtr <OdGeLineSeg3d> edgeRightBack = new OdGeLineSeg3d(OdGePoint3d(0, 100, 0), OdGePoint3d(0, 100, 100));
  OdSharedPtr <OdGeLineSeg3d> edgeBackLeft = new OdGeLineSeg3d(OdGePoint3d(0, 0, 0), OdGePoint3d(0, 0, 100));
  OdSharedPtr <OdGeLineSeg3d> edgeLeftFront = new OdGeLineSeg3d(OdGePoint3d(100, 0, 0), OdGePoint3d(100, 0, 100));

  // Add Edges
  BRepBuilderGeometryId edgeId_BottomFront = bbuilder.addEdge(edgeBottomFront.get());
  BRepBuilderGeometryId edgeId_BottomRight = bbuilder.addEdge(edgeBottomRight.get());
  BRepBuilderGeometryId edgeId_BottomBack = bbuilder.addEdge(edgeBottomBack.get());
  BRepBuilderGeometryId edgeId_BottomLeft = bbuilder.addEdge(edgeBottomLeft.get());

  BRepBuilderGeometryId edgeId_TopFront = bbuilder.addEdge(edgeTopFront.get());
  BRepBuilderGeometryId edgeId_TopRight = bbuilder.addEdge(edgeTopRight.get());
  BRepBuilderGeometryId edgeId_TopBack = bbuilder.addEdge(edgeTopBack.get());
  BRepBuilderGeometryId edgeId_TopLeft = bbuilder.addEdge(edgeTopLeft.get());

  BRepBuilderGeometryId edgeId_FrontRight = bbuilder.addEdge(edgeFrontRight.get());
  BRepBuilderGeometryId edgeId_RightBack = bbuilder.addEdge(edgeRightBack.get());
  BRepBuilderGeometryId edgeId_BackLeft = bbuilder.addEdge(edgeBackLeft.get());
  BRepBuilderGeometryId edgeId_LeftFront = bbuilder.addEdge(edgeLeftFront.get());

  // Add Loops
  BRepBuilderGeometryId loopId_Bottom = bbuilder.addLoop(faceId_Bottom);
  BRepBuilderGeometryId loopId_Top = bbuilder.addLoop(faceId_Top);
  BRepBuilderGeometryId loopId_Front = bbuilder.addLoop(faceId_Front);
  BRepBuilderGeometryId loopId_Back = bbuilder.addLoop(faceId_Back);
  BRepBuilderGeometryId loopId_Right = bbuilder.addLoop(faceId_Right);
  BRepBuilderGeometryId loopId_Left = bbuilder.addLoop(faceId_Left);
  bbuilder.finishFace(faceId_Bottom);
  bbuilder.finishFace(faceId_Top);
  bbuilder.finishFace(faceId_Front);
  bbuilder.finishFace(faceId_Back);
  bbuilder.finishFace(faceId_Right);
  bbuilder.finishFace(faceId_Left);

  // Add Coedge
  // Bottom face. 
  bbuilder.addCoedge(loopId_Bottom, edgeId_BottomFront, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom, edgeId_BottomLeft, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom, edgeId_BottomBack, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom, edgeId_BottomRight, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Bottom);

  // Top face
  bbuilder.addCoedge(loopId_Top, edgeId_TopFront, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top, edgeId_TopRight, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top, edgeId_TopBack, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top, edgeId_TopLeft, OdBrepBuilder::kForward);
  bbuilder.finishLoop(loopId_Top);

  // Front Face
  bbuilder.addCoedge(loopId_Front, edgeId_BottomFront, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front, edgeId_FrontRight, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front, edgeId_TopFront, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Front, edgeId_LeftFront, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Front);

  // Back face
  bbuilder.addCoedge(loopId_Back, edgeId_BottomBack, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back, edgeId_BackLeft, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back, edgeId_TopBack, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Back, edgeId_RightBack, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Back);

//   // Right face
  bbuilder.addCoedge(loopId_Right, edgeId_BottomRight, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Right, edgeId_RightBack, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Right, edgeId_TopRight, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Right, edgeId_FrontRight, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Right);

  // Left face
  bbuilder.addCoedge(loopId_Left, edgeId_BottomLeft, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Left, edgeId_LeftFront, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Left, edgeId_TopLeft, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Left, edgeId_BackLeft, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Left);

  bbuilder.finishShell(shellId);
  bbuilder.finishComplex(complexId);

  extents.set(OdGePoint3d::kOrigin, OdGePoint3d(100, 100, 100));

  return bbuilder.finish();
}
