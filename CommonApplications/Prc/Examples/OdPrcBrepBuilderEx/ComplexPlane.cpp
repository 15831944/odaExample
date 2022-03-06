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

OdPrcBrepDataPtr createComplexPlane(OdPrcHostAppServices& pHostApp, OdPrcFileStructure &newStructure, OdGeExtents3d& extents)
{
  OdBrepBuilder bbuilder;
  pHostApp.brepBuilder(bbuilder, kOpenShell);

  // Create connex
  BRepBuilderGeometryId complexId = bbuilder.addComplex();

  // Create shell
  BRepBuilderGeometryId shellId = bbuilder.addShell(complexId);

  OdSharedPtr <OdGePlane> bottom1 = new OdGePlane(OdGePoint3d(50, 75, 0), OdGeVector3d::kXAxis, OdGeVector3d::kYAxis);
  OdSharedPtr <OdGePlane> top1 = new OdGePlane(OdGePoint3d(50, 75, 100), OdGeVector3d::kXAxis, OdGeVector3d::kYAxis);
  OdSharedPtr <OdGePlane> front1 = new OdGePlane(OdGePoint3d(0, 50, 50), OdGeVector3d::kZAxis, OdGeVector3d::kYAxis);
  OdSharedPtr <OdGePlane> front2 = new OdGePlane(OdGePoint3d(0, 100, 0), OdGeVector3d(0.707106781186548, 0.707106781186548, 0), OdGeVector3d::kZAxis);
  OdSharedPtr <OdGePlane> front3 = new OdGePlane(OdGePoint3d(50, -50, 0), OdGeVector3d(0.707106781186548, -0.707106781186548, 0), -OdGeVector3d::kZAxis);
  OdSharedPtr <OdGePlane> front4 = new OdGePlane(OdGePoint3d(25, 50, 50), OdGeVector3d::kZAxis, OdGeVector3d::kYAxis);
  OdSharedPtr <OdGePlane> front5 = new OdGePlane(OdGePoint3d(25, 75, 0), OdGeVector3d(0.447213595499958, 0.894427190999916, 0), OdGeVector3d::kZAxis);
  OdSharedPtr <OdGePlane> front6 = new OdGePlane(OdGePoint3d(25, 25, 0), OdGeVector3d(0.447213595499958, -0.894427190999916, 0), OdGeVector3d::kZAxis);
  OdSharedPtr <OdGePlane> back1 = new OdGePlane(OdGePoint3d(100, 50, 50), OdGeVector3d::kZAxis, OdGeVector3d::kYAxis);
  OdSharedPtr <OdGePlane> back2 = new OdGePlane(OdGePoint3d(50, 150, 0), OdGeVector3d(0.707106781186548, -0.707106781186548, 0), OdGeVector3d::kZAxis);
  OdSharedPtr <OdGePlane> back3 = new OdGePlane(OdGePoint3d(50, -50, 0), OdGeVector3d(0.707106781186548, 0.707106781186548, 0), OdGeVector3d::kZAxis);
  OdSharedPtr <OdGePlane> back4 = new OdGePlane(OdGePoint3d(75, 25, 0), OdGeVector3d::kYAxis, OdGeVector3d::kZAxis);
  OdSharedPtr <OdGePlane> back5 = new OdGePlane(OdGePoint3d(75, 75, 0), OdGeVector3d(0.447213595499958, -0.894427190999916, 0), -OdGeVector3d::kZAxis);
  OdSharedPtr <OdGePlane> back6 = new OdGePlane(OdGePoint3d(50, -25, 0), OdGeVector3d(0.447213595499958, 0.894427190999916, 0), OdGeVector3d::kZAxis);

  // 2. Faces.
  BRepBuilderGeometryId faceId_Bottom1 = bbuilder.addFace(bottom1.get(), OdBrepBuilder::kReversed, shellId);
  BRepBuilderGeometryId faceId_Top1 = bbuilder.addFace(top1.get(), OdBrepBuilder::kForward, shellId);
  BRepBuilderGeometryId faceId_Front1 = bbuilder.addFace(front1.get(), OdBrepBuilder::kForward, shellId);
  BRepBuilderGeometryId faceId_Front2 = bbuilder.addFace(front2.get(), OdBrepBuilder::kReversed, shellId);
  BRepBuilderGeometryId faceId_Front3 = bbuilder.addFace(front3.get(), OdBrepBuilder::kReversed, shellId);
  BRepBuilderGeometryId faceId_Front4 = bbuilder.addFace(front4.get(), OdBrepBuilder::kReversed, shellId);
  BRepBuilderGeometryId faceId_Front5 = bbuilder.addFace(front5.get(), OdBrepBuilder::kForward, shellId);
  BRepBuilderGeometryId faceId_Front6 = bbuilder.addFace(front6.get(), OdBrepBuilder::kReversed, shellId);
  BRepBuilderGeometryId faceId_Back1 = bbuilder.addFace(back1.get(), OdBrepBuilder::kReversed, shellId);
  BRepBuilderGeometryId faceId_Back2 = bbuilder.addFace(back2.get(), OdBrepBuilder::kReversed, shellId);
  BRepBuilderGeometryId faceId_Back3 = bbuilder.addFace(back3.get(), OdBrepBuilder::kForward, shellId);
  BRepBuilderGeometryId faceId_Back4 = bbuilder.addFace(back4.get(), OdBrepBuilder::kReversed, shellId);
  BRepBuilderGeometryId faceId_Back5 = bbuilder.addFace(back5.get(), OdBrepBuilder::kReversed, shellId);
  BRepBuilderGeometryId faceId_Back6 = bbuilder.addFace(back6.get(), OdBrepBuilder::kReversed, shellId);


  // 3. Edges.
  OdSharedPtr <OdGeLineSeg3d> edge1 = new OdGeLineSeg3d(OdGePoint3d(100.0, 0, 0), OdGePoint3d(100.0, 100.0, 0));
  OdSharedPtr <OdGeLineSeg3d> edge2 = new OdGeLineSeg3d(OdGePoint3d(100, 100, 0), OdGePoint3d(50, 150, 0));
  OdSharedPtr <OdGeLineSeg3d> edge3 = new OdGeLineSeg3d(OdGePoint3d(50, 150, 0), OdGePoint3d(0, 100, 0));
  OdSharedPtr <OdGeLineSeg3d> edge4 = new OdGeLineSeg3d(OdGePoint3d(0, 100, 0), OdGePoint3d::kOrigin);
  OdSharedPtr <OdGeLineSeg3d> edge5 = new OdGeLineSeg3d(OdGePoint3d::kOrigin, OdGePoint3d(50, -50, 0));
  OdSharedPtr <OdGeLineSeg3d> edge6 = new OdGeLineSeg3d(OdGePoint3d(50, -50, 0), OdGePoint3d(100, 0, 0));
  OdSharedPtr <OdGeLineSeg3d> edge7 = new OdGeLineSeg3d(OdGePoint3d(75, 75, 0), OdGePoint3d(75, 25, 0));
  OdSharedPtr <OdGeLineSeg3d> edge8 = new OdGeLineSeg3d(OdGePoint3d(50, 125, 0), OdGePoint3d(75, 75, 0));
  OdSharedPtr <OdGeLineSeg3d> edge9 = new OdGeLineSeg3d(OdGePoint3d(25, 75, 0), OdGePoint3d(50, 125, 0));
  OdSharedPtr <OdGeLineSeg3d> edge10 = new OdGeLineSeg3d(OdGePoint3d(25, 25, 0), OdGePoint3d(25, 75, 0));
  OdSharedPtr <OdGeLineSeg3d> edge11 = new OdGeLineSeg3d(OdGePoint3d(50, -25, 0), OdGePoint3d(25, 25, 0));
  OdSharedPtr <OdGeLineSeg3d> edge12 = new OdGeLineSeg3d(OdGePoint3d(75, 25, 0), OdGePoint3d(50, -25, 0));
  OdSharedPtr <OdGeLineSeg3d> edge19 = new OdGeLineSeg3d(OdGePoint3d(100, 0, 100), OdGePoint3d(100, 100, 100));
  OdSharedPtr <OdGeLineSeg3d> edge20 = new OdGeLineSeg3d(OdGePoint3d(100, 100, 100), OdGePoint3d(50, 150, 100));
  OdSharedPtr <OdGeLineSeg3d> edge21 = new OdGeLineSeg3d(OdGePoint3d(50, 150, 100), OdGePoint3d(0, 100, 100));
  OdSharedPtr <OdGeLineSeg3d> edge22 = new OdGeLineSeg3d(OdGePoint3d(0, 100, 100), OdGePoint3d(0, 0, 100));
  OdSharedPtr <OdGeLineSeg3d> edge23 = new OdGeLineSeg3d(OdGePoint3d(0, 0, 100), OdGePoint3d(50, -50, 100));
  OdSharedPtr <OdGeLineSeg3d> edge24 = new OdGeLineSeg3d(OdGePoint3d(50, -50, 100), OdGePoint3d(100, 0, 100));
  OdSharedPtr <OdGeLineSeg3d> edge25 = new OdGeLineSeg3d(OdGePoint3d(75, 75, 100), OdGePoint3d(75, 25, 100));
  OdSharedPtr <OdGeLineSeg3d> edge26 = new OdGeLineSeg3d(OdGePoint3d(50, 125, 100), OdGePoint3d(75, 75, 100));
  OdSharedPtr <OdGeLineSeg3d> edge27 = new OdGeLineSeg3d(OdGePoint3d(25, 75, 100), OdGePoint3d(50, 125, 100));
  OdSharedPtr <OdGeLineSeg3d> edge28 = new OdGeLineSeg3d(OdGePoint3d(25, 25, 100), OdGePoint3d(25, 75, 100));
  OdSharedPtr <OdGeLineSeg3d> edge29 = new OdGeLineSeg3d(OdGePoint3d(50, -25, 100), OdGePoint3d(25, 25, 100));
  OdSharedPtr <OdGeLineSeg3d> edge30 = new OdGeLineSeg3d(OdGePoint3d(75, 25, 100), OdGePoint3d(50, -25, 100));
  OdSharedPtr <OdGeLineSeg3d> edge37 = new OdGeLineSeg3d(OdGePoint3d(0, 0, 0), OdGePoint3d(0, 0, 100));
  OdSharedPtr <OdGeLineSeg3d> edge38 = new OdGeLineSeg3d(OdGePoint3d(0, 100, 0), OdGePoint3d(0, 100, 100));
  OdSharedPtr <OdGeLineSeg3d> edge39 = new OdGeLineSeg3d(OdGePoint3d(50, 150, 0), OdGePoint3d(50, 150, 100));
  OdSharedPtr <OdGeLineSeg3d> edge40 = new OdGeLineSeg3d(OdGePoint3d(50, -50, 0), OdGePoint3d(50, -50, 100));
  OdSharedPtr <OdGeLineSeg3d> edge41 = new OdGeLineSeg3d(OdGePoint3d(100, 0, 0), OdGePoint3d(100, 0, 100));
  OdSharedPtr <OdGeLineSeg3d> edge42 = new OdGeLineSeg3d(OdGePoint3d(100, 100, 0), OdGePoint3d(100, 100, 100));
  OdSharedPtr <OdGeLineSeg3d> edge43 = new OdGeLineSeg3d(OdGePoint3d(25, 25, 0), OdGePoint3d(25, 25, 100));
  OdSharedPtr <OdGeLineSeg3d> edge44 = new OdGeLineSeg3d(OdGePoint3d(25, 75, 0), OdGePoint3d(25, 75, 100));
  OdSharedPtr <OdGeLineSeg3d> edge45 = new OdGeLineSeg3d(OdGePoint3d(50, 125, 0), OdGePoint3d(50, 125, 100));
  OdSharedPtr <OdGeLineSeg3d> edge46 = new OdGeLineSeg3d(OdGePoint3d(50, -25, 0), OdGePoint3d(50, -25, 100));
  OdSharedPtr <OdGeLineSeg3d> edge47 = new OdGeLineSeg3d(OdGePoint3d(75, 25, 0), OdGePoint3d(75, 25, 100));
  OdSharedPtr < OdGeLineSeg3d> edge48 = new OdGeLineSeg3d(OdGePoint3d(75, 75, 0), OdGePoint3d(75, 75, 100));

  // 3.b (define the edges themselves)
  BRepBuilderGeometryId edgeId_1 = bbuilder.addEdge(edge1.get());
  BRepBuilderGeometryId edgeId_2 = bbuilder.addEdge(edge2.get());
  BRepBuilderGeometryId edgeId_3 = bbuilder.addEdge(edge3.get());
  BRepBuilderGeometryId edgeId_4 = bbuilder.addEdge(edge4.get());
  BRepBuilderGeometryId edgeId_5 = bbuilder.addEdge(edge5.get());
  BRepBuilderGeometryId edgeId_6 = bbuilder.addEdge(edge6.get());
  BRepBuilderGeometryId edgeId_7 = bbuilder.addEdge(edge7.get());
  BRepBuilderGeometryId edgeId_8 = bbuilder.addEdge(edge8.get());
  BRepBuilderGeometryId edgeId_9 = bbuilder.addEdge(edge9.get());
  BRepBuilderGeometryId edgeId_10 = bbuilder.addEdge(edge10.get());
  BRepBuilderGeometryId edgeId_11 = bbuilder.addEdge(edge11.get());
  BRepBuilderGeometryId edgeId_12 = bbuilder.addEdge(edge12.get());

  BRepBuilderGeometryId edgeId_19 = bbuilder.addEdge(edge19.get());
  BRepBuilderGeometryId edgeId_20 = bbuilder.addEdge(edge20.get());
  BRepBuilderGeometryId edgeId_21 = bbuilder.addEdge(edge21.get());
  BRepBuilderGeometryId edgeId_22 = bbuilder.addEdge(edge22.get());
  BRepBuilderGeometryId edgeId_23 = bbuilder.addEdge(edge23.get());
  BRepBuilderGeometryId edgeId_24 = bbuilder.addEdge(edge24.get());
  BRepBuilderGeometryId edgeId_25 = bbuilder.addEdge(edge25.get());
  BRepBuilderGeometryId edgeId_26 = bbuilder.addEdge(edge26.get());
  BRepBuilderGeometryId edgeId_27 = bbuilder.addEdge(edge27.get());
  BRepBuilderGeometryId edgeId_28 = bbuilder.addEdge(edge28.get());
  BRepBuilderGeometryId edgeId_29 = bbuilder.addEdge(edge29.get());
  BRepBuilderGeometryId edgeId_30 = bbuilder.addEdge(edge30.get());

  BRepBuilderGeometryId edgeId_37 = bbuilder.addEdge(edge37.get());
  BRepBuilderGeometryId edgeId_38 = bbuilder.addEdge(edge38.get());
  BRepBuilderGeometryId edgeId_39 = bbuilder.addEdge(edge39.get());
  BRepBuilderGeometryId edgeId_40 = bbuilder.addEdge(edge40.get());
  BRepBuilderGeometryId edgeId_41 = bbuilder.addEdge(edge41.get());
  BRepBuilderGeometryId edgeId_42 = bbuilder.addEdge(edge42.get());
  BRepBuilderGeometryId edgeId_43 = bbuilder.addEdge(edge43.get());
  BRepBuilderGeometryId edgeId_44 = bbuilder.addEdge(edge44.get());
  BRepBuilderGeometryId edgeId_45 = bbuilder.addEdge(edge45.get());
  BRepBuilderGeometryId edgeId_46 = bbuilder.addEdge(edge46.get());
  BRepBuilderGeometryId edgeId_47 = bbuilder.addEdge(edge47.get());
  BRepBuilderGeometryId edgeId_48 = bbuilder.addEdge(edge48.get());

  // 4. Loops.
  BRepBuilderGeometryId loopId_Bottom1 = bbuilder.addLoop(faceId_Bottom1);

  // 5. Co-edges. 
  // Bottom face. All edges reversed
  bbuilder.addCoedge(loopId_Bottom1, edgeId_1, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom1, edgeId_6, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom1, edgeId_5, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom1, edgeId_4, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom1, edgeId_3, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom1, edgeId_2, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Bottom1);

  BRepBuilderGeometryId loopId_Bottom2 = bbuilder.addLoop(faceId_Bottom1);
  bbuilder.finishFace(faceId_Bottom1);

  bbuilder.addCoedge(loopId_Bottom2, edgeId_7, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom2, edgeId_8, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom2, edgeId_9, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom2, edgeId_10, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom2, edgeId_11, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Bottom2, edgeId_12, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Bottom2);

  // Top face
  BRepBuilderGeometryId loopId_Top1 = bbuilder.addLoop(faceId_Top1);

  bbuilder.addCoedge(loopId_Top1, edgeId_19, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top1, edgeId_20, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top1, edgeId_21, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top1, edgeId_22, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top1, edgeId_23, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top1, edgeId_24, OdBrepBuilder::kForward);
  bbuilder.finishLoop(loopId_Top1);

  BRepBuilderGeometryId loopId_Top2 = bbuilder.addLoop(faceId_Top1);
  bbuilder.finishFace(faceId_Top1);

  bbuilder.addCoedge(loopId_Top2, edgeId_25, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top2, edgeId_30, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top2, edgeId_29, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top2, edgeId_28, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top2, edgeId_27, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Top2, edgeId_26, OdBrepBuilder::kForward);
  bbuilder.finishLoop(loopId_Top2);

  BRepBuilderGeometryId loopId_Front1 = bbuilder.addLoop(faceId_Front1);
  bbuilder.finishFace(faceId_Front1);

  bbuilder.addCoedge(loopId_Front1, edgeId_4, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front1, edgeId_37, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front1, edgeId_22, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Front1, edgeId_38, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Front1);

  BRepBuilderGeometryId loopId_Front2 = bbuilder.addLoop(faceId_Front2);
  bbuilder.finishFace(faceId_Front2);

  bbuilder.addCoedge(loopId_Front2, edgeId_3, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front2, edgeId_38, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front2, edgeId_21, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Front2, edgeId_39, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Front2);

  BRepBuilderGeometryId loopId_Front3 = bbuilder.addLoop(faceId_Front3);
  bbuilder.finishFace(faceId_Front3);

  bbuilder.addCoedge(loopId_Front3, edgeId_5, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front3, edgeId_40, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front3, edgeId_23, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Front3, edgeId_37, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Front3);

  BRepBuilderGeometryId loopId_Front4 = bbuilder.addLoop(faceId_Front4);
  bbuilder.finishFace(faceId_Front4);

  bbuilder.addCoedge(loopId_Front4, edgeId_10, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front4, edgeId_44, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front4, edgeId_28, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Front4, edgeId_43, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Front4);

  BRepBuilderGeometryId loopId_Front5 = bbuilder.addLoop(faceId_Front5);
  bbuilder.finishFace(faceId_Front5);

  bbuilder.addCoedge(loopId_Front5, edgeId_9, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front5, edgeId_45, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front5, edgeId_27, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Front5, edgeId_44, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Front5);

  BRepBuilderGeometryId loopId_Front6 = bbuilder.addLoop(faceId_Front6);
  bbuilder.finishFace(faceId_Front6);

  bbuilder.addCoedge(loopId_Front6, edgeId_11, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front6, edgeId_43, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Front6, edgeId_29, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Front6, edgeId_46, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Front6);

  BRepBuilderGeometryId loopId_Back1 = bbuilder.addLoop(faceId_Back1);
  bbuilder.finishFace(faceId_Back1);

  bbuilder.addCoedge(loopId_Back1, edgeId_1, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back1, edgeId_42, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back1, edgeId_19, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Back1, edgeId_41, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Back1);

  BRepBuilderGeometryId loopId_Back2 = bbuilder.addLoop(faceId_Back2);
  bbuilder.finishFace(faceId_Back2);

  bbuilder.addCoedge(loopId_Back2, edgeId_2, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back2, edgeId_39, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back2, edgeId_20, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Back2, edgeId_42, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Back2);

  BRepBuilderGeometryId loopId_Back3 = bbuilder.addLoop(faceId_Back3);
  bbuilder.finishFace(faceId_Back3);

  bbuilder.addCoedge(loopId_Back3, edgeId_6, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back3, edgeId_41, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back3, edgeId_24, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Back3, edgeId_40, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Back3);

  BRepBuilderGeometryId loopId_Back4 = bbuilder.addLoop(faceId_Back4);
  bbuilder.finishFace(faceId_Back4);

  bbuilder.addCoedge(loopId_Back4, edgeId_7, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back4, edgeId_47, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back4, edgeId_25, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Back4, edgeId_48, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Back4);

  BRepBuilderGeometryId loopId_Back5 = bbuilder.addLoop(faceId_Back5);
  bbuilder.finishFace(faceId_Back5);

  bbuilder.addCoedge(loopId_Back5, edgeId_8, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back5, edgeId_48, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back5, edgeId_26, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Back5, edgeId_45, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Back5);

  BRepBuilderGeometryId loopId_Back6 = bbuilder.addLoop(faceId_Back6);
  bbuilder.finishFace(faceId_Back6);

  bbuilder.addCoedge(loopId_Back6, edgeId_12, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back6, edgeId_46, OdBrepBuilder::kForward);
  bbuilder.addCoedge(loopId_Back6, edgeId_30, OdBrepBuilder::kReversed);
  bbuilder.addCoedge(loopId_Back6, edgeId_47, OdBrepBuilder::kReversed);
  bbuilder.finishLoop(loopId_Back6);

  bbuilder.finishShell(shellId);
  bbuilder.finishComplex(complexId);

  extents.set(OdGePoint3d(0, -50, 0), OdGePoint3d(100, 150, 100));

  return bbuilder.finish();
}
