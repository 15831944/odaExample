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
#include "PrcFile.h"
#include "PrcBrepModel.h"
#include "PrcBrepData.h"
#include "PrcRepresentationItem.h"

#include "PrcCircle3d.h"
#include "PrcTorus.h"
#include "PrcLine3d.h"
#include "PrcCylinder.h"
#include "PrcConnex.h"
#include "PrcShell.h"
#include "PrcFace.h"
#include "PrcEdge.h"
#include "PrcCoEdge.h"
#include "PrcLoop.h"
#include "PrcUniqueVertex.h"

#include "Ge/GeCircArc3d.h"
#include "Ge/GeLineSeg3d.h"

#include "OdPrcCreateStart.h"
#include "PrcCreateTopologyHelper.h"


void addLineStyleForBrep (OdPrcFileStructure &newStructure, double r, double g, double b);
void addGraphicDataToBrep (OdPrcFileStructure &newStructure);

void FillTopoBrepFaceWasher (OdPrcBrepDataPtr brepData)
{
  OdPrcConnexPtr pCurConnex = OdPrcConnex::createObject();
  brepData->addConnex(pCurConnex);

  {
    OdPrcShellPtr pCurShell = OdPrcShell::createObject();
    pCurConnex->addShell(pCurShell);

    OdPrcEdgePtr edge, edge1, edge2, edge3;

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        pPrcPlane->setUVParameterization(OdPrcUVParameterization(-1,3,-1,3));

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(-1,-1,0.1)));
        pPrcPlane->setTransformation(&transform);
        // TBD
      }

      OdPrcCircle3dPtr crvCircle = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,0.1)));
        crvCircle->setTransformation(&transform);
        // TBD
        crvCircle->setRadius(1.4);
      }

      edge = OdPrcEdge::createObject();
      edge->contentWireEdge().curve() = crvCircle;

      OdPrcUniqueVertexPtr vertex_start = OdPrcUniqueVertex::createObject();
      vertex_start->point() = OdGePoint3d(1.4,0,0.1);
      edge->setStartVertex(vertex_start);
      edge->setEndVertex(vertex_start);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge);
      coEdge->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop = OdPrcLoop::createObject();
      pCurFace->addLoop(loop);
      loop->addCoEdge(coEdge);
      loop->setOrientationWithSurface(true);

         
////////////////////////////////////////////////////////////////////////////////////////////////////////////

      OdPrcCircle3dPtr crvCircle1 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle1->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle1->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,0.1)));
        crvCircle1->setTransformation(&transform);
        // TBD
        crvCircle1->setRadius(0.8);
      }
      edge1 = OdPrcEdge::createObject();
      edge1->contentWireEdge().curve() = crvCircle1;

      OdPrcUniqueVertexPtr vertex_start1 = OdPrcUniqueVertex::createObject();
      vertex_start1->point() = OdGePoint3d(0.8,0,0.1);
      edge1->setStartVertex(vertex_start1);
      edge1->setEndVertex(vertex_start1);

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge1);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->setOrientationWithSurface(true);

         
/////////////////////////////////////////////////////////////////////////////////////////////////
      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        pPrcPlane->setUVParameterization(OdPrcUVParameterization(-1,3,-1,3));

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(-1,-1,-0.1)));
        pPrcPlane->setTransformation(&transform);
        // TBD
      }

      OdPrcCircle3dPtr crvCircle = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,-0.1)));
        crvCircle->setTransformation(&transform);
        // TBD
        crvCircle->setRadius(1.4);
      }

      edge2 = OdPrcEdge::createObject();
      edge2->contentWireEdge().curve() = crvCircle;

      OdPrcUniqueVertexPtr vertex_start2 = OdPrcUniqueVertex::createObject();
      vertex_start2->point() = OdGePoint3d(1.4,0,-0.1);
      edge2->setStartVertex(vertex_start2);
      edge2->setEndVertex(vertex_start2);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge2);
      coEdge->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop = OdPrcLoop::createObject();
      pCurFace->addLoop(loop);
      loop->addCoEdge(coEdge);
      loop->setOrientationWithSurface(false);

         
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////

      OdPrcCircle3dPtr crvCircle1 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle1->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle1->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,-0.1)));
        crvCircle1->setTransformation(&transform);
        // TBD
        crvCircle1->setRadius(0.8);
      }
      edge3 = OdPrcEdge::createObject();
      edge3->contentWireEdge().curve() = crvCircle1;

      OdPrcUniqueVertexPtr vertex_start3 = OdPrcUniqueVertex::createObject();
      vertex_start3->point() = OdGePoint3d(0.8,0,-0.1);
      edge3->setStartVertex(vertex_start3);
      edge3->setEndVertex(vertex_start3);

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge3);
      coEdge1->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->setOrientationWithSurface(false);

         
      /////////////////////////////////////////////////////////////////////////////////////////////////

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kOpposite;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);

    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCylinderPtr pPrcCylinder = OdPrcCylinder::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcCylinder->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named cylinder in srfContent");

        pPrcCylinder->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, -0.102, 0.102));
        // can add transformation if needed here
        // TBD

        pPrcCylinder->setRadius(1.4);
      }

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge2);
      coEdge->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->setOrientationWithSurface(true);

         

      ///////////////////////////////////////////////////////////////////////////
      OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop2);
      loop2->addCoEdge(coEdge);
      loop2->setOrientationWithSurface(true);

         
      ///////////////////////////////////////////////////////////////////////////

      pCurFace->baseSurface() = pPrcCylinder;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCylinderPtr pPrcCylinder = OdPrcCylinder::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcCylinder->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named cylinder in srfContent");

        pPrcCylinder->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, -0.102, 0.102));
        // can add transformation if needed here
        // TBD

        pPrcCylinder->setRadius(0.8);
      }

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge1);
      coEdge1->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge3);
      coEdge->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->setOrientationWithSurface(false);

         

      ///////////////////////////////////////////////////////////////////////
      OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop2);
      loop2->addCoEdge(coEdge);
      loop2->setOrientationWithSurface(false);

         
      ///////////////////////////////////////////////////////////////////////

      pCurFace->baseSurface() = pPrcCylinder;
      pCurFace->orientationSurfaceWithShell() = kOpposite;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    pCurShell->setShellIsClosed(true);
  }
}

void FillTopoBrepFaceNut (OdPrcBrepDataPtr brepData)
{
  OdPrcConnexPtr pCurConnex = OdPrcConnex::createObject();
  brepData->addConnex(pCurConnex);

  {
    OdPrcShellPtr pCurShell = OdPrcShell::createObject();
    pCurConnex->addShell(pCurShell);

    OdPrcEdgePtr edge1, edge2, edge3, edge4, edge5, edge6;

    OdPrcEdgePtr edge11, edge12, edge13, edge14, edge15, edge16;

    OdPrcEdgePtr edge111, edge112;

    OdPrcEdgePtr edgeS1, edgeS2, edgeS3, edgeS4, edgeS5, edgeS6;

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

//         OdGeCircArc3d circle(OdGePoint3d(0,0,0.1),OdGeVector3d::kZAxis,1.2);
// 
//         OdPrcPolyLine3dPtr crvPolyLine = OdPrcPolyLine3d::createObject();
//         {
//           OdPrcContentCurve &crvContent = crvPolyLine->contentCurve();
// 
//           // - array of control points defining curve
//           OdGePoint3dArray crvPoint;
// //           crvPoint.push_back(OdGePoint3d(2.0 , 0.0, 0.1));
// //           crvPoint.push_back(OdGePoint3d(1.0 , 1.73, 0.1));
// //           crvPoint.push_back(OdGePoint3d(-1.0 , 1.73, 0.1));
// //           crvPoint.push_back(OdGePoint3d(-2.0 , 0.0, 0.1));
// //           crvPoint.push_back(OdGePoint3d(-1.0 , -1.73, 0.1));
// //           crvPoint.push_back(OdGePoint3d(1.0 , -1.73, 0.1));
// //           crvPoint.push_back(OdGePoint3d(2.0 , 0.0, 0.1));
// 
//           circle.getSamplePoints(7,crvPoint);
//           crvPoint.push_back(crvPoint[0]);
// 
//           crvPolyLine->setPoints(crvPoint, true);
//         }

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();

      edge1 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end = OdPrcUniqueVertex::createObject();
      vertex_start->point() = OdGePoint3d(1.200000,0.000000,0.300000);
      vertex_end->point() = OdGePoint3d(0.600000,1.039230,0.300000);
      edge1->setStartVertex(vertex_start);
      edge1->setEndVertex(vertex_end);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start->point(),vertex_end->point());
        pLine->setFromOdGeCurve(line);
        edge1->contentWireEdge().curve() = pLine;
      }

      coEdge1->setEdge(edge1);
      coEdge1->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();

      edge2 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start2 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end2 = OdPrcUniqueVertex::createObject();
      vertex_start2->point() = OdGePoint3d(0.600000,1.039230,0.300000);
      vertex_end2->point() = OdGePoint3d(-0.600000,1.039230,0.300000);
      edge2->setStartVertex(vertex_start2);
      edge2->setEndVertex(vertex_end2);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start2->point(),vertex_end2->point());
        pLine->setFromOdGeCurve(line);
        edge2->contentWireEdge().curve() = pLine;
      }

      coEdge2->setEdge(edge2);
      coEdge2->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();

      edge3 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start3 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end3 = OdPrcUniqueVertex::createObject();
      vertex_start3->point() = OdGePoint3d(-0.600000,1.039230,0.300000);
      vertex_end3->point() = OdGePoint3d(-1.200000,0.000000,0.300000);
      edge3->setStartVertex(vertex_start3);
      edge3->setEndVertex(vertex_end3);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start3->point(),vertex_end3->point());
        pLine->setFromOdGeCurve(line);
        edge3->contentWireEdge().curve() = pLine;
      }

      coEdge3->setEdge(edge3);
      coEdge3->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();

      edge4 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start4 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end4 = OdPrcUniqueVertex::createObject();
      vertex_start4->point() = OdGePoint3d(-1.200000,0.000000,0.300000);
      vertex_end4->point() = OdGePoint3d(-0.600000,-1.039230,0.300000);
      edge4->setStartVertex(vertex_start4);
      edge4->setEndVertex(vertex_end4);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start4->point(),vertex_end4->point());
        pLine->setFromOdGeCurve(line);
        edge4->contentWireEdge().curve() = pLine;
      }

      coEdge4->setEdge(edge4);
      coEdge4->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge5 = OdPrcCoEdge::createObject();

      edge5 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start5 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end5 = OdPrcUniqueVertex::createObject();
      vertex_start5->point() = OdGePoint3d(-0.600000,-1.039230,0.300000);
      vertex_end5->point() = OdGePoint3d(0.600000,-1.039230,0.300000);
      edge5->setStartVertex(vertex_start5);
      edge5->setEndVertex(vertex_end5);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start5->point(),vertex_end5->point());
        pLine->setFromOdGeCurve(line);
        edge5->contentWireEdge().curve() = pLine;
      }

      coEdge5->setEdge(edge5);
      coEdge5->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge6 = OdPrcCoEdge::createObject();

      edge6 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start6 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end6 = OdPrcUniqueVertex::createObject();
      vertex_start6->point() = OdGePoint3d(0.600000,-1.039230,0.300000);
      vertex_end6->point() = OdGePoint3d(1.200000,0.000000,0.300000);
      edge6->setStartVertex(vertex_start6);
      edge6->setEndVertex(vertex_end6);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start6->point(),vertex_end6->point());
        pLine->setFromOdGeCurve(line);
        edge6->contentWireEdge().curve() = pLine;
      }

      coEdge6->setEdge(edge6);
      coEdge6->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop = OdPrcLoop::createObject();
      pCurFace->addLoop(loop);
      loop->addCoEdge(coEdge1);
      loop->addCoEdge(coEdge2);
      loop->addCoEdge(coEdge3);
      loop->addCoEdge(coEdge4);
      loop->addCoEdge(coEdge5);
      loop->addCoEdge(coEdge6);
      loop->setOrientationWithSurface(true);

         
//////////////////////////////////////////////////////////////////////////////////////////////////////////
      OdPrcCircle3dPtr crvCircle1 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle1->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle1->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,0.3)));
        crvCircle1->setTransformation(&transform);
        // TBD
        crvCircle1->setRadius(0.6);
      }
      edge111 = OdPrcEdge::createObject();
      edge111->contentWireEdge().curve() = crvCircle1;

      OdPrcUniqueVertexPtr vertex_start1 = OdPrcUniqueVertex::createObject();
      vertex_start1->point() = OdGePoint3d(0.6,0,0.3);
      edge111->setStartVertex(vertex_start1);
      edge111->setEndVertex(vertex_start1);

      OdPrcCoEdgePtr coEdge11 = OdPrcCoEdge::createObject();
      coEdge11->setEdge(edge111);
      coEdge11->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge11);
      loop1->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge1->vertexEnd())->point() - ((OdPrcUniqueVertexPtr) edge1->vertexStart())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edge2->vertexEnd())->point() - ((OdPrcUniqueVertexPtr) edge2->vertexStart())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge1->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

////////////////////////////////////////////////////////////////////////////////////////////////////
      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }


    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();

      edge11 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end = OdPrcUniqueVertex::createObject();
      vertex_start->point() = OdGePoint3d(1.200000,0.000000,-0.300000);
      vertex_end->point() = OdGePoint3d(0.600000,-1.039230,-0.300000);
      edge11->setStartVertex(vertex_start);
      edge11->setEndVertex(vertex_end);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start->point(),vertex_end->point());
        pLine->setFromOdGeCurve(line);
        edge11->contentWireEdge().curve() = pLine;
      }

      coEdge1->setEdge(edge11);
      coEdge1->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();

      edge12 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start2 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end2 = OdPrcUniqueVertex::createObject();
      vertex_start2->point() = OdGePoint3d(0.600000,-1.039230,-0.300000);
      vertex_end2->point() = OdGePoint3d(-0.600000,-1.039230,-0.300000);
      edge12->setStartVertex(vertex_start2);
      edge12->setEndVertex(vertex_end2);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start2->point(),vertex_end2->point());
        pLine->setFromOdGeCurve(line);
        edge12->contentWireEdge().curve() = pLine;
      }

      coEdge2->setEdge(edge12);
      coEdge2->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();

      edge13 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start3 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end3 = OdPrcUniqueVertex::createObject();
      vertex_start3->point() = OdGePoint3d(-0.600000,-1.039230,-0.300000);
      vertex_end3->point() = OdGePoint3d(-1.200000,0.000000,-0.300000);
      edge13->setStartVertex(vertex_start3);
      edge13->setEndVertex(vertex_end3);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start3->point(),vertex_end3->point());
        pLine->setFromOdGeCurve(line);
        edge13->contentWireEdge().curve() = pLine;
      }

      coEdge3->setEdge(edge13);
      coEdge3->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();

      edge14 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start4 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end4 = OdPrcUniqueVertex::createObject();
      vertex_start4->point() = OdGePoint3d(-1.200000,0.000000,-0.300000);
      vertex_end4->point() = OdGePoint3d(-0.600000,1.039230,-0.300000);
      edge14->setStartVertex(vertex_start4);
      edge14->setEndVertex(vertex_end4);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start4->point(),vertex_end4->point());
        pLine->setFromOdGeCurve(line);
        edge14->contentWireEdge().curve() = pLine;
      }

      coEdge4->setEdge(edge14);
      coEdge4->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge5 = OdPrcCoEdge::createObject();

      edge15 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start5 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end5 = OdPrcUniqueVertex::createObject();
      vertex_start5->point() = OdGePoint3d(-0.600000,1.039230,-0.300000);
      vertex_end5->point() = OdGePoint3d(0.600000,1.039230,-0.300000);
      edge15->setStartVertex(vertex_start5);
      edge15->setEndVertex(vertex_end5);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start5->point(),vertex_end5->point());
        pLine->setFromOdGeCurve(line);
        edge15->contentWireEdge().curve() = pLine;
      }

      coEdge5->setEdge(edge15);
      coEdge5->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge6 = OdPrcCoEdge::createObject();

      edge16 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start6 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end6 = OdPrcUniqueVertex::createObject();
      vertex_start6->point() = OdGePoint3d(0.600000,1.039230,-0.300000);
      vertex_end6->point() = OdGePoint3d(1.200000,0.000000,-0.300000);
      edge16->setStartVertex(vertex_start6);
      edge16->setEndVertex(vertex_end6);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start6->point(),vertex_end6->point());
        pLine->setFromOdGeCurve(line);
        edge16->contentWireEdge().curve() = pLine;
      }

      coEdge6->setEdge(edge16);
      coEdge6->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop = OdPrcLoop::createObject();
      pCurFace->addLoop(loop);
      loop->addCoEdge(coEdge1);
      loop->addCoEdge(coEdge2);
      loop->addCoEdge(coEdge3);
      loop->addCoEdge(coEdge4);
      loop->addCoEdge(coEdge5);
      loop->addCoEdge(coEdge6);
      loop->setOrientationWithSurface(true);

         
//////////////////////////////////////////////////////////////////////////////////////////////////////////
      OdPrcCircle3dPtr crvCircle1 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle1->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle1->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,-0.3)));
        crvCircle1->setTransformation(&transform);
        // TBD
        crvCircle1->setRadius(0.6);
      }
      edge112 = OdPrcEdge::createObject();
      edge112->contentWireEdge().curve() = crvCircle1;

      OdPrcUniqueVertexPtr vertex_start1 = OdPrcUniqueVertex::createObject();
      vertex_start1->point() = OdGePoint3d(0.6,0,-0.3);
      edge112->setStartVertex(vertex_start1);
      edge112->setEndVertex(vertex_start1);

      OdPrcCoEdgePtr coEdge11 = OdPrcCoEdge::createObject();
      coEdge11->setEdge(edge112);
      coEdge11->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge11);
      loop1->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge11->vertexEnd())->point() - ((OdPrcUniqueVertexPtr) edge11->vertexStart())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edge12->vertexEnd())->point() - ((OdPrcUniqueVertexPtr) edge12->vertexStart())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge11->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

////////////////////////////////////////////////////////////////////////////////////////////////////
      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCylinderPtr pPrcCylinder = OdPrcCylinder::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcCylinder->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named cylinder in srfContent");

        pPrcCylinder->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, -0.306, 0.306));
        // can add transformation if needed here
        // TBD

        pPrcCylinder->setRadius(0.6);
      }

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge111);
      coEdge1->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge112);
      coEdge->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->setOrientationWithSurface(false);

         

      ///////////////////////////////////////////////////////////////////////
      OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop2);
      loop2->addCoEdge(coEdge);
      loop2->setOrientationWithSurface(false);

         
      ///////////////////////////////////////////////////////////////////////

      pCurFace->baseSurface() = pPrcCylinder;
      pCurFace->orientationSurfaceWithShell() = kOpposite;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge1);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();
      edgeS2 = OdPrcEdge::createObject();
      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(((OdPrcUniqueVertexPtr)edge1->vertexStart())->point(),((OdPrcUniqueVertexPtr)edge11->vertexStart())->point());
        pLine->setFromOdGeCurve(line);
        edgeS2->contentWireEdge().curve() = pLine;
      }
      edgeS2->setStartVertex(edge1->vertexStart());
      edgeS2->setEndVertex(edge11->vertexStart());

      coEdge2->setEdge(edgeS2);
      coEdge2->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();
      coEdge3->setEdge(edge16);
      coEdge3->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();
      edgeS1 = OdPrcEdge::createObject();
      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(((OdPrcUniqueVertexPtr)edge16->vertexStart())->point(),((OdPrcUniqueVertexPtr)edge1->vertexEnd())->point());
        pLine->setFromOdGeCurve(line);
        edgeS1->contentWireEdge().curve() = pLine;
      }
      edgeS1->setStartVertex(edge16->vertexStart());
      edgeS1->setEndVertex(edge1->vertexEnd());
      coEdge4->setEdge(edgeS1);
      coEdge4->setOrientationWithLoop(kSame);


      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->addCoEdge(coEdge2);
      loop1->addCoEdge(coEdge3);
      loop1->addCoEdge(coEdge4);
      loop1->setOrientationWithSurface(true);


      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge1->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edge1->vertexEnd())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edgeS2->vertexEnd())->point() - ((OdPrcUniqueVertexPtr) edgeS2->vertexStart())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge1->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge2);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();
      coEdge2->setEdge(edgeS1);
      coEdge2->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();
      coEdge3->setEdge(edge15);
      coEdge3->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();
      edgeS3 = OdPrcEdge::createObject();
      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(((OdPrcUniqueVertexPtr)edge15->vertexStart())->point(),((OdPrcUniqueVertexPtr)edge2->vertexEnd())->point());
        pLine->setFromOdGeCurve(line);
        edgeS3->contentWireEdge().curve() = pLine;
      }
      edgeS3->setStartVertex(edge15->vertexStart());
      edgeS3->setEndVertex(edge2->vertexEnd());

      coEdge4->setEdge(edgeS3);
      coEdge4->setOrientationWithLoop(kSame);


      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->addCoEdge(coEdge2);
      loop1->addCoEdge(coEdge3);
      loop1->addCoEdge(coEdge4);
      loop1->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge2->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edge2->vertexEnd())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edgeS1->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edgeS1->vertexEnd())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge2->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge3);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();
      coEdge2->setEdge(edgeS3);
      coEdge2->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();
      coEdge3->setEdge(edge14);
      coEdge3->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();
      edgeS4 = OdPrcEdge::createObject();
      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(((OdPrcUniqueVertexPtr)edge14->vertexStart())->point(),((OdPrcUniqueVertexPtr)edge3->vertexEnd())->point());
        pLine->setFromOdGeCurve(line);
        edgeS4->contentWireEdge().curve() = pLine;
      }
      edgeS4->setStartVertex(edge14->vertexStart());
      edgeS4->setEndVertex(edge3->vertexEnd());

      coEdge4->setEdge(edgeS4);
      coEdge4->setOrientationWithLoop(kSame);


      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->addCoEdge(coEdge2);
      loop1->addCoEdge(coEdge3);
      loop1->addCoEdge(coEdge4);
      loop1->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge3->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edge3->vertexEnd())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edgeS3->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edgeS3->vertexEnd())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge3->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge4);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();
      coEdge2->setEdge(edgeS4);
      coEdge2->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();
      coEdge3->setEdge(edge13);
      coEdge3->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();
      edgeS5 = OdPrcEdge::createObject();
      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(((OdPrcUniqueVertexPtr)edge13->vertexStart())->point(),((OdPrcUniqueVertexPtr)edge4->vertexEnd())->point());
        pLine->setFromOdGeCurve(line);
        edgeS5->contentWireEdge().curve() = pLine;
      }
      edgeS5->setStartVertex(edge13->vertexStart());
      edgeS5->setEndVertex(edge4->vertexEnd());

      coEdge4->setEdge(edgeS5);
      coEdge4->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->addCoEdge(coEdge2);
      loop1->addCoEdge(coEdge3);
      loop1->addCoEdge(coEdge4);
      loop1->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge4->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edge4->vertexEnd())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edgeS4->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edgeS4->vertexEnd())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge4->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge5);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();
      coEdge2->setEdge(edgeS5);
      coEdge2->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();
      coEdge3->setEdge(edge12);
      coEdge3->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();
      edgeS6 = OdPrcEdge::createObject();
      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(((OdPrcUniqueVertexPtr)edge12->vertexStart())->point(),((OdPrcUniqueVertexPtr)edge5->vertexEnd())->point());
        pLine->setFromOdGeCurve(line);
        edgeS6->contentWireEdge().curve() = pLine;
      }
      edgeS6->setStartVertex(edge12->vertexStart());
      edgeS6->setEndVertex(edge5->vertexEnd());

      coEdge4->setEdge(edgeS6);
      coEdge4->setOrientationWithLoop(kSame);


      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->addCoEdge(coEdge2);
      loop1->addCoEdge(coEdge3);
      loop1->addCoEdge(coEdge4);
      loop1->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge5->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edge5->vertexEnd())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edgeS5->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edgeS5->vertexEnd())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge5->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge6);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();
      coEdge2->setEdge(edgeS6);
      coEdge2->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();
      coEdge3->setEdge(edge11);
      coEdge3->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();
      coEdge4->setEdge(edgeS2);
      coEdge4->setOrientationWithLoop(kOpposite);


      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->addCoEdge(coEdge2);
      loop1->addCoEdge(coEdge3);
      loop1->addCoEdge(coEdge4);
      loop1->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge6->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edge6->vertexEnd())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edgeS6->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edgeS6->vertexEnd())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge6->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    pCurShell->setShellIsClosed(true);
  }
}

void FillTopoBrepFaceBolt (OdPrcBrepDataPtr brepData)
{
  OdPrcConnexPtr pCurConnex = OdPrcConnex::createObject();
  brepData->addConnex(pCurConnex);

  {
    OdPrcShellPtr pCurShell = OdPrcShell::createObject();
    pCurConnex->addShell(pCurShell);

    OdPrcEdgePtr edge1, edge2, edge3, edge4, edge5, edge6;

    OdPrcEdgePtr edge11, edge12, edge13, edge14, edge15, edge16;

    OdPrcEdgePtr edge111, edge112;

    OdPrcEdgePtr edgeS1, edgeS2, edgeS3, edgeS4, edgeS5, edgeS6;

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

//         OdGeCircArc3d circle(OdGePoint3d(0,0,0.1),OdGeVector3d::kZAxis,1.2);
// 
//         OdPrcPolyLine3dPtr crvPolyLine = OdPrcPolyLine3d::createObject();
//         {
//           OdPrcContentCurve &crvContent = crvPolyLine->contentCurve();
// 
//           // - array of control points defining curve
//           OdGePoint3dArray crvPoint;
// //           crvPoint.push_back(OdGePoint3d(2.0 , 0.0, 0.1));
// //           crvPoint.push_back(OdGePoint3d(1.0 , 1.73, 0.1));
// //           crvPoint.push_back(OdGePoint3d(-1.0 , 1.73, 0.1));
// //           crvPoint.push_back(OdGePoint3d(-2.0 , 0.0, 0.1));
// //           crvPoint.push_back(OdGePoint3d(-1.0 , -1.73, 0.1));
// //           crvPoint.push_back(OdGePoint3d(1.0 , -1.73, 0.1));
// //           crvPoint.push_back(OdGePoint3d(2.0 , 0.0, 0.1));
// 
//           circle.getSamplePoints(7,crvPoint);
//           crvPoint.push_back(crvPoint[0]);
// 
//           crvPolyLine->setPoints(crvPoint, true);
//         }

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();

      edge1 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end = OdPrcUniqueVertex::createObject();
      vertex_start->point() = OdGePoint3d(1.200000,0.000000,0.300000);
      vertex_end->point() = OdGePoint3d(0.600000,1.039230,0.300000);
      edge1->setStartVertex(vertex_start);
      edge1->setEndVertex(vertex_end);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start->point(),vertex_end->point());
        pLine->setFromOdGeCurve(line);
        edge1->contentWireEdge().curve() = pLine;
      }

      coEdge1->setEdge(edge1);
      coEdge1->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();

      edge2 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start2 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end2 = OdPrcUniqueVertex::createObject();
      vertex_start2->point() = OdGePoint3d(0.600000,1.039230,0.300000);
      vertex_end2->point() = OdGePoint3d(-0.600000,1.039230,0.300000);
      edge2->setStartVertex(vertex_start2);
      edge2->setEndVertex(vertex_end2);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start2->point(),vertex_end2->point());
        pLine->setFromOdGeCurve(line);
        edge2->contentWireEdge().curve() = pLine;
      }

      coEdge2->setEdge(edge2);
      coEdge2->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();

      edge3 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start3 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end3 = OdPrcUniqueVertex::createObject();
      vertex_start3->point() = OdGePoint3d(-0.600000,1.039230,0.300000);
      vertex_end3->point() = OdGePoint3d(-1.200000,0.000000,0.300000);
      edge3->setStartVertex(vertex_start3);
      edge3->setEndVertex(vertex_end3);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start3->point(),vertex_end3->point());
        pLine->setFromOdGeCurve(line);
        edge3->contentWireEdge().curve() = pLine;
      }

      coEdge3->setEdge(edge3);
      coEdge3->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();

      edge4 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start4 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end4 = OdPrcUniqueVertex::createObject();
      vertex_start4->point() = OdGePoint3d(-1.200000,0.000000,0.300000);
      vertex_end4->point() = OdGePoint3d(-0.600000,-1.039230,0.300000);
      edge4->setStartVertex(vertex_start4);
      edge4->setEndVertex(vertex_end4);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start4->point(),vertex_end4->point());
        pLine->setFromOdGeCurve(line);
        edge4->contentWireEdge().curve() = pLine;
      }

      coEdge4->setEdge(edge4);
      coEdge4->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge5 = OdPrcCoEdge::createObject();

      edge5 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start5 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end5 = OdPrcUniqueVertex::createObject();
      vertex_start5->point() = OdGePoint3d(-0.600000,-1.039230,0.300000);
      vertex_end5->point() = OdGePoint3d(0.600000,-1.039230,0.300000);
      edge5->setStartVertex(vertex_start5);
      edge5->setEndVertex(vertex_end5);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start5->point(),vertex_end5->point());
        pLine->setFromOdGeCurve(line);
        edge5->contentWireEdge().curve() = pLine;
      }

      coEdge5->setEdge(edge5);
      coEdge5->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge6 = OdPrcCoEdge::createObject();

      edge6 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start6 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end6 = OdPrcUniqueVertex::createObject();
      vertex_start6->point() = OdGePoint3d(0.600000,-1.039230,0.300000);
      vertex_end6->point() = OdGePoint3d(1.200000,0.000000,0.300000);
      edge6->setStartVertex(vertex_start6);
      edge6->setEndVertex(vertex_end6);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start6->point(),vertex_end6->point());
        pLine->setFromOdGeCurve(line);
        edge6->contentWireEdge().curve() = pLine;
      }

      coEdge6->setEdge(edge6);
      coEdge6->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop = OdPrcLoop::createObject();
      pCurFace->addLoop(loop);
      loop->addCoEdge(coEdge1);
      loop->addCoEdge(coEdge2);
      loop->addCoEdge(coEdge3);
      loop->addCoEdge(coEdge4);
      loop->addCoEdge(coEdge5);
      loop->addCoEdge(coEdge6);
      loop->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge1->vertexEnd())->point() - ((OdPrcUniqueVertexPtr) edge1->vertexStart())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edge2->vertexEnd())->point() - ((OdPrcUniqueVertexPtr) edge2->vertexStart())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge1->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }


    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();

      edge11 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end = OdPrcUniqueVertex::createObject();
      vertex_start->point() = OdGePoint3d(1.200000,0.000000,-0.300000);
      vertex_end->point() = OdGePoint3d(0.600000,-1.039230,-0.300000);
      edge11->setStartVertex(vertex_start);
      edge11->setEndVertex(vertex_end);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start->point(),vertex_end->point());
        pLine->setFromOdGeCurve(line);
        edge11->contentWireEdge().curve() = pLine;
      }

      coEdge1->setEdge(edge11);
      coEdge1->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();

      edge12 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start2 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end2 = OdPrcUniqueVertex::createObject();
      vertex_start2->point() = OdGePoint3d(0.600000,-1.039230,-0.300000);
      vertex_end2->point() = OdGePoint3d(-0.600000,-1.039230,-0.300000);
      edge12->setStartVertex(vertex_start2);
      edge12->setEndVertex(vertex_end2);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start2->point(),vertex_end2->point());
        pLine->setFromOdGeCurve(line);
        edge12->contentWireEdge().curve() = pLine;
      }

      coEdge2->setEdge(edge12);
      coEdge2->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();

      edge13 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start3 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end3 = OdPrcUniqueVertex::createObject();
      vertex_start3->point() = OdGePoint3d(-0.600000,-1.039230,-0.300000);
      vertex_end3->point() = OdGePoint3d(-1.200000,0.000000,-0.300000);
      edge13->setStartVertex(vertex_start3);
      edge13->setEndVertex(vertex_end3);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start3->point(),vertex_end3->point());
        pLine->setFromOdGeCurve(line);
        edge13->contentWireEdge().curve() = pLine;
      }

      coEdge3->setEdge(edge13);
      coEdge3->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();

      edge14 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start4 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end4 = OdPrcUniqueVertex::createObject();
      vertex_start4->point() = OdGePoint3d(-1.200000,0.000000,-0.300000);
      vertex_end4->point() = OdGePoint3d(-0.600000,1.039230,-0.300000);
      edge14->setStartVertex(vertex_start4);
      edge14->setEndVertex(vertex_end4);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start4->point(),vertex_end4->point());
        pLine->setFromOdGeCurve(line);
        edge14->contentWireEdge().curve() = pLine;
      }

      coEdge4->setEdge(edge14);
      coEdge4->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge5 = OdPrcCoEdge::createObject();

      edge15 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start5 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end5 = OdPrcUniqueVertex::createObject();
      vertex_start5->point() = OdGePoint3d(-0.600000,1.039230,-0.300000);
      vertex_end5->point() = OdGePoint3d(0.600000,1.039230,-0.300000);
      edge15->setStartVertex(vertex_start5);
      edge15->setEndVertex(vertex_end5);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start5->point(),vertex_end5->point());
        pLine->setFromOdGeCurve(line);
        edge15->contentWireEdge().curve() = pLine;
      }

      coEdge5->setEdge(edge15);
      coEdge5->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge6 = OdPrcCoEdge::createObject();

      edge16 = OdPrcEdge::createObject();
      OdPrcUniqueVertexPtr vertex_start6 = OdPrcUniqueVertex::createObject();
      OdPrcUniqueVertexPtr vertex_end6 = OdPrcUniqueVertex::createObject();
      vertex_start6->point() = OdGePoint3d(0.600000,1.039230,-0.300000);
      vertex_end6->point() = OdGePoint3d(1.200000,0.000000,-0.300000);
      edge16->setStartVertex(vertex_start6);
      edge16->setEndVertex(vertex_end6);

      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(vertex_start6->point(),vertex_end6->point());
        pLine->setFromOdGeCurve(line);
        edge16->contentWireEdge().curve() = pLine;
      }

      coEdge6->setEdge(edge16);
      coEdge6->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop = OdPrcLoop::createObject();
      pCurFace->addLoop(loop);
      loop->addCoEdge(coEdge1);
      loop->addCoEdge(coEdge2);
      loop->addCoEdge(coEdge3);
      loop->addCoEdge(coEdge4);
      loop->addCoEdge(coEdge5);
      loop->addCoEdge(coEdge6);
      loop->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge11->vertexEnd())->point() - ((OdPrcUniqueVertexPtr) edge11->vertexStart())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edge12->vertexEnd())->point() - ((OdPrcUniqueVertexPtr) edge12->vertexStart())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge11->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

//////////////////////////////////////////////////////////////////////////////////////////////////////////
      OdPrcCircle3dPtr crvCircle1 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle1->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle1->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,-0.3)));
        crvCircle1->setTransformation(&transform);
        // TBD
        crvCircle1->setRadius(0.6);
      }
      edge112 = OdPrcEdge::createObject();
      edge112->contentWireEdge().curve() = crvCircle1;

      OdPrcUniqueVertexPtr vertex_start1 = OdPrcUniqueVertex::createObject();
      vertex_start1->point() = OdGePoint3d(0.6,0,-0.3);
      edge112->setStartVertex(vertex_start1);
      edge112->setEndVertex(vertex_start1);

      OdPrcCoEdgePtr coEdge11 = OdPrcCoEdge::createObject();
      coEdge11->setEdge(edge112);
      coEdge11->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge11);
      loop1->setOrientationWithSurface(true);

         
////////////////////////////////////////////////////////////////////////////////////////////////////
      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        pPrcPlane->setUVParameterization(OdPrcUVParameterization(0,4,0,4));

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        OdGeMatrix3d matr;
        matr *= matr.translation(OdGeVector3d(-2,2,-5));
        matr *= matr.rotation(OdaPI,OdGeVector3d::kXAxis);
        transform.set(matr);
        pPrcPlane->setTransformation(&transform);
        // TBD
      }

      OdPrcCircle3dPtr crvCircle1 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle1->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle1->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,-5)));
        crvCircle1->setTransformation(&transform);
        // TBD
        crvCircle1->setRadius(0.6);
      }
      edge111 = OdPrcEdge::createObject();
      edge111->contentWireEdge().curve() = crvCircle1;

      OdPrcUniqueVertexPtr vertex_start1 = OdPrcUniqueVertex::createObject();
      vertex_start1->point() = OdGePoint3d(0.6,0,-5);
      edge111->setStartVertex(vertex_start1);
      edge111->setEndVertex(vertex_start1);

      OdPrcCoEdgePtr coEdge11 = OdPrcCoEdge::createObject();
      coEdge11->setEdge(edge111);
      coEdge11->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge11);
      loop1->setOrientationWithSurface(true);

         

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCylinderPtr pPrcCylinder = OdPrcCylinder::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcCylinder->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named cylinder in srfContent");

        pPrcCylinder->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, -2.397, 2.397));
        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,-2.65)));
        pPrcCylinder->setTransformation(&transform);
        // TBD

        pPrcCylinder->setRadius(0.6);
      }

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge111);
      coEdge1->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge112);
      coEdge->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->setOrientationWithSurface(true);

///////////////////////////////////////////////////////////////////////
      OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop2);
      loop2->addCoEdge(coEdge);
      loop2->setOrientationWithSurface(true);

///////////////////////////////////////////////////////////////////////

      pCurFace->baseSurface() = pPrcCylinder;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge1);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();
      edgeS2 = OdPrcEdge::createObject();
      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(((OdPrcUniqueVertexPtr)edge1->vertexStart())->point(),((OdPrcUniqueVertexPtr)edge11->vertexStart())->point());
        pLine->setFromOdGeCurve(line);
        edgeS2->contentWireEdge().curve() = pLine;
      }
      edgeS2->setStartVertex(edge1->vertexStart());
      edgeS2->setEndVertex(edge11->vertexStart());

      coEdge2->setEdge(edgeS2);
      coEdge2->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();
      coEdge3->setEdge(edge16);
      coEdge3->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();
      edgeS1 = OdPrcEdge::createObject();
      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(((OdPrcUniqueVertexPtr)edge16->vertexStart())->point(),((OdPrcUniqueVertexPtr)edge1->vertexEnd())->point());
        pLine->setFromOdGeCurve(line);
        edgeS1->contentWireEdge().curve() = pLine;
      }
      edgeS1->setStartVertex(edge16->vertexStart());
      edgeS1->setEndVertex(edge1->vertexEnd());
      coEdge4->setEdge(edgeS1);
      coEdge4->setOrientationWithLoop(kSame);


      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->addCoEdge(coEdge2);
      loop1->addCoEdge(coEdge3);
      loop1->addCoEdge(coEdge4);
      loop1->setOrientationWithSurface(true);


      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge1->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edge1->vertexEnd())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edgeS2->vertexEnd())->point() - ((OdPrcUniqueVertexPtr) edgeS2->vertexStart())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge1->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge2);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();
      coEdge2->setEdge(edgeS1);
      coEdge2->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();
      coEdge3->setEdge(edge15);
      coEdge3->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();
      edgeS3 = OdPrcEdge::createObject();
      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(((OdPrcUniqueVertexPtr)edge15->vertexStart())->point(),((OdPrcUniqueVertexPtr)edge2->vertexEnd())->point());
        pLine->setFromOdGeCurve(line);
        edgeS3->contentWireEdge().curve() = pLine;
      }
      edgeS3->setStartVertex(edge15->vertexStart());
      edgeS3->setEndVertex(edge2->vertexEnd());

      coEdge4->setEdge(edgeS3);
      coEdge4->setOrientationWithLoop(kSame);


      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->addCoEdge(coEdge2);
      loop1->addCoEdge(coEdge3);
      loop1->addCoEdge(coEdge4);
      loop1->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge2->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edge2->vertexEnd())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edgeS1->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edgeS1->vertexEnd())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge2->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge3);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();
      coEdge2->setEdge(edgeS3);
      coEdge2->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();
      coEdge3->setEdge(edge14);
      coEdge3->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();
      edgeS4 = OdPrcEdge::createObject();
      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(((OdPrcUniqueVertexPtr)edge14->vertexStart())->point(),((OdPrcUniqueVertexPtr)edge3->vertexEnd())->point());
        pLine->setFromOdGeCurve(line);
        edgeS4->contentWireEdge().curve() = pLine;
      }
      edgeS4->setStartVertex(edge14->vertexStart());
      edgeS4->setEndVertex(edge3->vertexEnd());

      coEdge4->setEdge(edgeS4);
      coEdge4->setOrientationWithLoop(kSame);


      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->addCoEdge(coEdge2);
      loop1->addCoEdge(coEdge3);
      loop1->addCoEdge(coEdge4);
      loop1->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge3->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edge3->vertexEnd())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edgeS3->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edgeS3->vertexEnd())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge3->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge4);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();
      coEdge2->setEdge(edgeS4);
      coEdge2->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();
      coEdge3->setEdge(edge13);
      coEdge3->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();
      edgeS5 = OdPrcEdge::createObject();
      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(((OdPrcUniqueVertexPtr)edge13->vertexStart())->point(),((OdPrcUniqueVertexPtr)edge4->vertexEnd())->point());
        pLine->setFromOdGeCurve(line);
        edgeS5->contentWireEdge().curve() = pLine;
      }
      edgeS5->setStartVertex(edge13->vertexStart());
      edgeS5->setEndVertex(edge4->vertexEnd());

      coEdge4->setEdge(edgeS5);
      coEdge4->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->addCoEdge(coEdge2);
      loop1->addCoEdge(coEdge3);
      loop1->addCoEdge(coEdge4);
      loop1->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge4->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edge4->vertexEnd())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edgeS4->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edgeS4->vertexEnd())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge4->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge5);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();
      coEdge2->setEdge(edgeS5);
      coEdge2->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();
      coEdge3->setEdge(edge12);
      coEdge3->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();
      edgeS6 = OdPrcEdge::createObject();
      {
        OdPrcLine3dPtr pLine = OdPrcLine3d::createObject();
        OdGeLineSeg3d line(((OdPrcUniqueVertexPtr)edge12->vertexStart())->point(),((OdPrcUniqueVertexPtr)edge5->vertexEnd())->point());
        pLine->setFromOdGeCurve(line);
        edgeS6->contentWireEdge().curve() = pLine;
      }
      edgeS6->setStartVertex(edge12->vertexStart());
      edgeS6->setEndVertex(edge5->vertexEnd());

      coEdge4->setEdge(edgeS6);
      coEdge4->setOrientationWithLoop(kSame);


      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->addCoEdge(coEdge2);
      loop1->addCoEdge(coEdge3);
      loop1->addCoEdge(coEdge4);
      loop1->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge5->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edge5->vertexEnd())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edgeS5->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edgeS5->vertexEnd())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge5->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCoEdgePtr coEdge1 = OdPrcCoEdge::createObject();
      coEdge1->setEdge(edge6);
      coEdge1->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge2 = OdPrcCoEdge::createObject();
      coEdge2->setEdge(edgeS6);
      coEdge2->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge3 = OdPrcCoEdge::createObject();
      coEdge3->setEdge(edge11);
      coEdge3->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge4 = OdPrcCoEdge::createObject();
      coEdge4->setEdge(edgeS2);
      coEdge4->setOrientationWithLoop(kOpposite);


      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coEdge1);
      loop1->addCoEdge(coEdge2);
      loop1->addCoEdge(coEdge3);
      loop1->addCoEdge(coEdge4);
      loop1->setOrientationWithSurface(true);

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        OdGeVector3d vec1 = ((OdPrcUniqueVertexPtr) edge6->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edge6->vertexEnd())->point();
        OdGeVector3d vec2 = ((OdPrcUniqueVertexPtr) edgeS6->vertexStart())->point() - ((OdPrcUniqueVertexPtr) edgeS6->vertexEnd())->point();
        OdGeVector3d vrNormal = vec1.crossProduct(vec2);
        vrNormal.normalize();
        OdGePlane gePlane(((OdPrcUniqueVertexPtr) edge6->vertexStart())->point(),vrNormal);
        OdGeInterval intU( -3., 3 );
        OdGeInterval intV( -3., 3 );
        gePlane.setEnvelope(intU, intV);
        pPrcPlane->setFromOdGeSurface(gePlane);
      }

      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    pCurShell->setShellIsClosed(true);
  }
}

void FillTopoBrepFaceRim (OdPrcBrepDataPtr brepData)
{
  OdPrcConnexPtr pCurConnex = OdPrcConnex::createObject();
  brepData->addConnex(pCurConnex);

  {
    OdPrcShellPtr pCurShell = OdPrcShell::createObject();
    pCurConnex->addShell(pCurShell);

    OdPrcEdgePtr edge11, edge12, edge13, edge14, edge15;
    OdPrcEdgePtr edge21, edge22, edge23, edge24, edge25;

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        pPrcPlane->setUVParameterization(OdPrcUVParameterization(0,30,0,30));

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(-15,-15,-0.3)));
        pPrcPlane->setTransformation(&transform);
        // TBD
      }

      OdPrcCircle3dPtr crvCircle = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,-0.3)));
        crvCircle->setTransformation(&transform);
        // TBD
        crvCircle->setRadius(12);
      }

      edge11 = OdPrcEdge::createObject();
      edge11->contentWireEdge().curve() = crvCircle;

      OdPrcUniqueVertexPtr vertex_start = OdPrcUniqueVertex::createObject();
      vertex_start->point() = OdGePoint3d(12,0,-0.3);
      edge11->setStartVertex(vertex_start);
      edge11->setEndVertex(vertex_start);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge11);
      coEdge->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop = OdPrcLoop::createObject();
      pCurFace->addLoop(loop);
      loop->addCoEdge(coEdge);
      loop->setOrientationWithSurface(true);

         
      //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole1 start

      OdPrcCircle3dPtr crvCircle1 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle1->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle1->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(4,0,-0.3)));
        crvCircle1->setTransformation(&transform);
        // TBD
        crvCircle1->setRadius(0.6);
      }
      edge12 = OdPrcEdge::createObject();
      edge12->contentWireEdge().curve() = crvCircle1;

      OdPrcUniqueVertexPtr vertex_start1 = OdPrcUniqueVertex::createObject();
      vertex_start1->point() = OdGePoint3d(4.6,0,-0.3);
      edge12->setStartVertex(vertex_start1);
      edge12->setEndVertex(vertex_start1);

      OdPrcCoEdgePtr coedge12 = OdPrcCoEdge::createObject();
      coedge12->setEdge(edge12);
      coedge12->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coedge12);
      loop1->setOrientationWithSurface(true);

         

      //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole2 start
      OdPrcCircle3dPtr crvCircle2 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle2->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle2->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(-4,0,-0.3)));
        crvCircle2->setTransformation(&transform);
        // TBD
        crvCircle2->setRadius(0.6);
      }
      edge13 = OdPrcEdge::createObject();
      edge13->contentWireEdge().curve() = crvCircle2;

      OdPrcUniqueVertexPtr vertex_start2 = OdPrcUniqueVertex::createObject();
      vertex_start2->point() = OdGePoint3d(-3.4,0,-0.3);
      edge13->setStartVertex(vertex_start2);
      edge13->setEndVertex(vertex_start2);

      OdPrcCoEdgePtr coedge13 = OdPrcCoEdge::createObject();
      coedge13->setEdge(edge13);
      coedge13->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop2);
      loop2->addCoEdge(coedge13);
      loop2->setOrientationWithSurface(true);

         

      //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole3 start
      OdPrcCircle3dPtr crvCircle3 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle3->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle3->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,4,-0.3)));
        crvCircle3->setTransformation(&transform);
        // TBD
        crvCircle3->setRadius(0.6);
      }
      edge14 = OdPrcEdge::createObject();
      edge14->contentWireEdge().curve() = crvCircle3;

      OdPrcUniqueVertexPtr vertex_start3 = OdPrcUniqueVertex::createObject();
      vertex_start3->point() = OdGePoint3d(0.6,4.,-0.3);
      edge14->setStartVertex(vertex_start3);
      edge14->setEndVertex(vertex_start3);

      OdPrcCoEdgePtr coedge14 = OdPrcCoEdge::createObject();
      coedge14->setEdge(edge14);
      coedge14->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop3 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop3);
      loop3->addCoEdge(coedge14);
      loop3->setOrientationWithSurface(true);

         

      //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole3 start
      OdPrcCircle3dPtr crvCircle4 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle4->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle4->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,-4,-0.3)));
        crvCircle4->setTransformation(&transform);
        // TBD
        crvCircle4->setRadius(0.6);
      }
      edge15 = OdPrcEdge::createObject();
      edge15->contentWireEdge().curve() = crvCircle4;

      OdPrcUniqueVertexPtr vertex_start4 = OdPrcUniqueVertex::createObject();
      vertex_start4->point() = OdGePoint3d(0.6,-4.,-0.3);
      edge15->setStartVertex(vertex_start4);
      edge15->setEndVertex(vertex_start4);

      OdPrcCoEdgePtr coedge15 = OdPrcCoEdge::createObject();
      coedge15->setEdge(edge15);
      coedge15->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop4 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop4);
      loop4->addCoEdge(coedge15);
      loop4->setOrientationWithSurface(true);

         
      /////////////////////////////////////////////////////////////////////////////////////////////////
      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcPlanePtr pPrcPlane = OdPrcPlane::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcPlane->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named plane in srfContent");

        pPrcPlane->setUVParameterization(OdPrcUVParameterization(0,30,0,30));

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(-15,-15,-3.9)));
        pPrcPlane->setTransformation(&transform);
        // TBD
      }

      OdPrcCircle3dPtr crvCircle = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,-3.9)));
        crvCircle->setTransformation(&transform);
        // TBD
        crvCircle->setRadius(12);
      }

      edge21 = OdPrcEdge::createObject();
      edge21->contentWireEdge().curve() = crvCircle;

      OdPrcUniqueVertexPtr vertex_start = OdPrcUniqueVertex::createObject();
      vertex_start->point() = OdGePoint3d(12,0,-3.9);
      edge21->setStartVertex(vertex_start);
      edge21->setEndVertex(vertex_start);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge21);
      coEdge->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop = OdPrcLoop::createObject();
      pCurFace->addLoop(loop);
      loop->addCoEdge(coEdge);
      loop->setOrientationWithSurface(false);

         
      //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole1 start

      OdPrcCircle3dPtr crvCircle1 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle1->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle1->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(4,0,-3.9)));
        crvCircle1->setTransformation(&transform);
        // TBD
        crvCircle1->setRadius(0.6);
      }
      edge22 = OdPrcEdge::createObject();
      edge22->contentWireEdge().curve() = crvCircle1;

      OdPrcUniqueVertexPtr vertex_start1 = OdPrcUniqueVertex::createObject();
      vertex_start1->point() = OdGePoint3d(4.6,0,-3.9);
      edge22->setStartVertex(vertex_start1);
      edge22->setEndVertex(vertex_start1);

      OdPrcCoEdgePtr coedge22 = OdPrcCoEdge::createObject();
      coedge22->setEdge(edge22);
      coedge22->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coedge22);
      loop1->setOrientationWithSurface(false);

         

      //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole2 start
      OdPrcCircle3dPtr crvCircle2 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle2->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle2->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(-4,0,-3.9)));
        crvCircle2->setTransformation(&transform);
        // TBD
        crvCircle2->setRadius(0.6);
      }
      edge23 = OdPrcEdge::createObject();
      edge23->contentWireEdge().curve() = crvCircle2;

      OdPrcUniqueVertexPtr vertex_start2 = OdPrcUniqueVertex::createObject();
      vertex_start2->point() = OdGePoint3d(-3.4,0,-3.9);
      edge23->setStartVertex(vertex_start2);
      edge23->setEndVertex(vertex_start2);

      OdPrcCoEdgePtr coedge23 = OdPrcCoEdge::createObject();
      coedge23->setEdge(edge23);
      coedge23->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop2);
      loop2->addCoEdge(coedge23);
      loop2->setOrientationWithSurface(false);

         

      //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole3 start
      OdPrcCircle3dPtr crvCircle3 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle3->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle3->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,4,-3.9)));
        crvCircle3->setTransformation(&transform);
        // TBD
        crvCircle3->setRadius(0.6);
      }
      edge24 = OdPrcEdge::createObject();
      edge24->contentWireEdge().curve() = crvCircle3;

      OdPrcUniqueVertexPtr vertex_start3 = OdPrcUniqueVertex::createObject();
      vertex_start3->point() = OdGePoint3d(0.6,4.,-3.9);
      edge24->setStartVertex(vertex_start3);
      edge24->setEndVertex(vertex_start3);

      OdPrcCoEdgePtr coedge24 = OdPrcCoEdge::createObject();
      coedge24->setEdge(edge24);
      coedge24->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop3 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop3);
      loop3->addCoEdge(coedge24);
      loop3->setOrientationWithSurface(false);

         

      //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole3 start
      OdPrcCircle3dPtr crvCircle4 = OdPrcCircle3d::createObject();
      {
        OdPrcContentCurve &crvContent = crvCircle4->contentCurve();

        // set name
        crvContent.baseGeometry().name().setName(L"named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams(0, Oda2PI);
        crvCircle4->setParameterization( curveParams );

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,-4,-3.9)));
        crvCircle4->setTransformation(&transform);
        // TBD
        crvCircle4->setRadius(0.6);
      }
      edge25 = OdPrcEdge::createObject();
      edge25->contentWireEdge().curve() = crvCircle4;

      OdPrcUniqueVertexPtr vertex_start4 = OdPrcUniqueVertex::createObject();
      vertex_start4->point() = OdGePoint3d(0.6,-4.,-3.9);
      edge25->setStartVertex(vertex_start4);
      edge25->setEndVertex(vertex_start4);

      OdPrcCoEdgePtr coedge25 = OdPrcCoEdge::createObject();
      coedge25->setEdge(edge25);
      coedge25->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop4 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop4);
      loop4->addCoEdge(coedge25);
      loop4->setOrientationWithSurface(false);

         
      /////////////////////////////////////////////////////////////////////////////////////////////////
      pCurFace->baseSurface() = pPrcPlane;
      pCurFace->orientationSurfaceWithShell() = kOpposite;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCylinderPtr pPrcCylinder = OdPrcCylinder::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcCylinder->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named cylinder in srfContent");

        pPrcCylinder->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, -5.1, 5.1));
        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(4,0,0)));
        pPrcCylinder->setTransformation(&transform);
        // TBD

        pPrcCylinder->setRadius(0.6);
      }

      OdPrcCoEdgePtr coedge12 = OdPrcCoEdge::createObject();
      coedge12->setEdge(edge12);
      coedge12->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge22);
      coEdge->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coedge12);
      loop1->setOrientationWithSurface(false);

         

      ///////////////////////////////////////////////////////////////////////
      OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop2);
      loop2->addCoEdge(coEdge);
      loop2->setOrientationWithSurface(false);

         
      ///////////////////////////////////////////////////////////////////////

      pCurFace->baseSurface() = pPrcCylinder;
      pCurFace->orientationSurfaceWithShell() = kOpposite;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCylinderPtr pPrcCylinder = OdPrcCylinder::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcCylinder->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named cylinder in srfContent");

        pPrcCylinder->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, -5.1, 5.1));
        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(-4,0,0)));
        pPrcCylinder->setTransformation(&transform);
        // TBD

        pPrcCylinder->setRadius(0.6);
      }

      OdPrcCoEdgePtr coedge12 = OdPrcCoEdge::createObject();
      coedge12->setEdge(edge13);
      coedge12->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge23);
      coEdge->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coedge12);
      loop1->setOrientationWithSurface(false);

         

      ///////////////////////////////////////////////////////////////////////
      OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop2);
      loop2->addCoEdge(coEdge);
      loop2->setOrientationWithSurface(false);

         
      ///////////////////////////////////////////////////////////////////////

      pCurFace->baseSurface() = pPrcCylinder;
      pCurFace->orientationSurfaceWithShell() = kOpposite;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCylinderPtr pPrcCylinder = OdPrcCylinder::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcCylinder->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named cylinder in srfContent");

        pPrcCylinder->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, -5.1, 5.1));
        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,4,0)));
        pPrcCylinder->setTransformation(&transform);
        // TBD

        pPrcCylinder->setRadius(0.6);
      }

      OdPrcCoEdgePtr coedge12 = OdPrcCoEdge::createObject();
      coedge12->setEdge(edge14);
      coedge12->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge24);
      coEdge->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coedge12);
      loop1->setOrientationWithSurface(false);

         

      ///////////////////////////////////////////////////////////////////////
      OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop2);
      loop2->addCoEdge(coEdge);
      loop2->setOrientationWithSurface(false);

         
      ///////////////////////////////////////////////////////////////////////

      pCurFace->baseSurface() = pPrcCylinder;
      pCurFace->orientationSurfaceWithShell() = kOpposite;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCylinderPtr pPrcCylinder = OdPrcCylinder::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcCylinder->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named cylinder in srfContent");

        pPrcCylinder->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, -5.1, 5.1));
        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,-4,0)));
        pPrcCylinder->setTransformation(&transform);
        // TBD

        pPrcCylinder->setRadius(0.6);
      }

      OdPrcCoEdgePtr coedge12 = OdPrcCoEdge::createObject();
      coedge12->setEdge(edge15);
      coedge12->setOrientationWithLoop(kSame);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge25);
      coEdge->setOrientationWithLoop(kOpposite);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coedge12);
      loop1->setOrientationWithSurface(false);

         

      ///////////////////////////////////////////////////////////////////////
      OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop2);
      loop2->addCoEdge(coEdge);
      loop2->setOrientationWithSurface(false);

         
      ///////////////////////////////////////////////////////////////////////

      pCurFace->baseSurface() = pPrcCylinder;
      pCurFace->orientationSurfaceWithShell() = kOpposite;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcCylinderPtr pPrcCylinder = OdPrcCylinder::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcCylinder->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named cylinder in srfContent");

        pPrcCylinder->setUVParameterization(OdPrcUVParameterization(0, Oda2PI, -5.1, 5.1));
        // can add transformation if needed here
        // TBD

        pPrcCylinder->setRadius(12);
      }

      OdPrcCoEdgePtr coedge12 = OdPrcCoEdge::createObject();
      coedge12->setEdge(edge11);
      coedge12->setOrientationWithLoop(kOpposite);

      OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
      coEdge->setEdge(edge21);
      coEdge->setOrientationWithLoop(kSame);

      OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop1);
      loop1->addCoEdge(coedge12);
      loop1->setOrientationWithSurface(true);

         

      ///////////////////////////////////////////////////////////////////////////
      OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
      pCurFace->addLoop(loop2);
      loop2->addCoEdge(coEdge);
      loop2->setOrientationWithSurface(true);

         
      ///////////////////////////////////////////////////////////////////////////

      pCurFace->baseSurface() = pPrcCylinder;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    pCurShell->setShellIsClosed(true);
  }
}

void FillTopoBrepFaceTire (OdPrcBrepDataPtr brepData)
{
  OdPrcConnexPtr pCurConnex = OdPrcConnex::createObject();
  brepData->addConnex(pCurConnex);

  {
    OdPrcShellPtr pCurShell = OdPrcShell::createObject();
    pCurConnex->addShell(pCurShell);

    OdPrcEdgePtr edge1, edge2;

    {
      OdPrcFacePtr pCurFace = OdPrcFace::createObject();

      OdPrcTorusPtr pPrcTorus = OdPrcTorus::createObject();
      {
        OdPrcContentSurface &srfContent  = pPrcTorus->contentSurface();

        // set name
        srfContent.baseGeometry().name().setName(L"named torus_T1 in srfContent");

        pPrcTorus->setUVParameterization(OdPrcUVParameterization(-OdaPI, OdaPI, -OdaPI, OdaPI));

        // can add transformation if needed here
        OdPrcTransformation3d transform;
        transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,-2.1)));
        pPrcTorus->setTransformation(&transform);
        // TBD

        pPrcTorus->setMajorRadius(12);
        pPrcTorus->setMinorRadius(2.2);


        OdPrcCircle3dPtr crvCircle1 = OdPrcCircle3d::createObject();
        {
          OdPrcContentCurve &crvContent = crvCircle1->contentCurve();

          // set name
          crvContent.baseGeometry().name().setName(L"named circle in crvContent");

          // add some data to params
          OdPrcParameterization curveParams(0, Oda2PI);
          crvCircle1->setParameterization( curveParams );

          // can add transformation if needed here
          OdPrcTransformation3d transform;
          OdGeMatrix3d matr;
          matr.setCoordSystem(OdGePoint3d(0,0,0.1), OdGeVector3d(-1,0,0), OdGeVector3d(0,1,0), OdGeVector3d(0,0,-1));
          transform.set(matr);
          crvCircle1->setTransformation(&transform);
          // TBD
          crvCircle1->setRadius(12.0);
        }

        edge1 = OdPrcEdge::createObject();
        edge1->contentWireEdge().curve() = crvCircle1;

        OdPrcUniqueVertexPtr vertex_start1 = OdPrcUniqueVertex::createObject();
        vertex_start1->point() = OdGePoint3d(-12,0,0.1);
        edge1->setStartVertex(vertex_start1);
        edge1->setEndVertex(vertex_start1);

        OdPrcCoEdgePtr coedge1 = OdPrcCoEdge::createObject();
        coedge1->setEdge(edge1);
        coedge1->setOrientationWithLoop(kSame);

        OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
        pCurFace->addLoop(loop1);
        loop1->addCoEdge(coedge1);
        loop1->setOrientationWithSurface(true);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        OdPrcCircle3dPtr crvCircle2 = OdPrcCircle3d::createObject();
        {
          OdPrcContentCurve &crvContent = crvCircle2->contentCurve();

          // set name
          crvContent.baseGeometry().name().setName(L"named circle in crvContent");

          // add some data to params
          OdPrcParameterization curveParams(0, Oda2PI);
          crvCircle2->setParameterization( curveParams );

          // can add transformation if needed here
          OdPrcTransformation3d transform;
          OdGeMatrix3d matr;
          matr.setCoordSystem(OdGePoint3d(0,0,-4.3), OdGeVector3d(-1,0,0), OdGeVector3d(0,-1,0), OdGeVector3d(0,0,1));
          transform.set(matr);
          crvCircle2->setTransformation(&transform);
          // TBD
          crvCircle2->setRadius(12.0);
        }

        edge2 = OdPrcEdge::createObject();
        edge2->contentWireEdge().curve() = crvCircle2;

        OdPrcUniqueVertexPtr vertex_start2 = OdPrcUniqueVertex::createObject();
        vertex_start2->point() = OdGePoint3d(-12,0,-4.3);
        edge2->setStartVertex(vertex_start2);
        edge2->setEndVertex(vertex_start2);

        OdPrcCoEdgePtr coedge2 = OdPrcCoEdge::createObject();
        coedge2->setEdge(edge2);
        coedge2->setOrientationWithLoop(kSame);

        OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
        pCurFace->addLoop(loop2);
        loop2->addCoEdge(coedge2);
        loop2->setOrientationWithSurface(true);

      }

      {
        OdPrcFacePtr pCurFace = OdPrcFace::createObject();

        OdPrcCylinderPtr pPrcCylinder = OdPrcCylinder::createObject();
        {
          OdPrcContentSurface &srfContent  = pPrcCylinder->contentSurface();

          // set name
          srfContent.baseGeometry().name().setName(L"named cylinder in srfContent");

          pPrcCylinder->setUVParameterization(OdPrcUVParameterization(-OdaPI, OdaPI, -2.344, 2.144));
          // can add transformation if needed here
          OdPrcTransformation3d transform;
          transform.set(OdGeMatrix3d::translation(OdGeVector3d(0,0,-2)));
          pPrcCylinder->setTransformation(&transform);
          // TBD

          pPrcCylinder->setRadius(12.0);
        }

        OdPrcCoEdgePtr coedge12 = OdPrcCoEdge::createObject();
        coedge12->setEdge(edge1);
        coedge12->setOrientationWithLoop(kOpposite);

        OdPrcCoEdgePtr coEdge = OdPrcCoEdge::createObject();
        coEdge->setEdge(edge2);
        coEdge->setOrientationWithLoop(kOpposite);

        OdPrcLoopPtr loop1 = OdPrcLoop::createObject();
        pCurFace->addLoop(loop1);
        loop1->addCoEdge(coedge12);
        loop1->setOrientationWithSurface(false);


///////////////////////////////////////////////////////////////////////
        OdPrcLoopPtr loop2 = OdPrcLoop::createObject();
        pCurFace->addLoop(loop2);
        loop2->addCoEdge(coEdge);
        loop2->setOrientationWithSurface(false);

///////////////////////////////////////////////////////////////////////

        pCurFace->baseSurface() = pPrcCylinder;
        pCurFace->orientationSurfaceWithShell() = kOpposite;
        pCurFace->setSurfaceTrimDomain(0);
        pCurFace->setTolerance(0.);

        pCurShell->addFace(pCurFace);
      }

      pCurFace->baseSurface() = pPrcTorus;
      pCurFace->orientationSurfaceWithShell() = kSame;
      pCurFace->setSurfaceTrimDomain(0);
      pCurFace->setTolerance(0.);

      pCurShell->addFace(pCurFace);
    }

    pCurShell->setShellIsClosed(true);
  }
}

OdPrcFilePtr CreatePRCCommonForBrepComplex (void)
{
  // create prc
  OdPrcFilePtr pFile = OdPrcFile::createObject();

  pFile->setVersions(8137, 8137);
  pFile->fileStructureId() = OdPrcUniqueId::generateUID();

  // init model file data section
  pFile->modelFileData().unit().setUnitFromCADFile(true);
  pFile->modelFileData().unit().setUnit(1); // 1 mm

  return pFile;
}

void CreateTopologyCommonForComplex (OdPrcFileStructurePtr curStructure, OdPrcProductOccurrencePtr curOccurrence, OdGeExtents3d &extents, const char* brepModelName)
{
  // part definition section
  OdPrcPartDefinitionPtr newDefinition = createPartDefinition(*curStructure, *curOccurrence);

  // bounding box
  newDefinition->boundingBox().box() = extents;

  // create brep model
  OdPrcBrepModelPtr newBrep = OdPrcBrepModel::createObject();
  curStructure->addObject(newBrep);
  newBrep->setIsClosed(true);
  newBrep->name().setName(brepModelName);
  newDefinition->representationItem().push_back(newBrep->objectId());

  // create Brep Data
  OdPrcBrepDataPtr newBrepData = OdPrcBrepData::createObject();
  curStructure->addObject(newBrepData);
  newBrepData->boundingBox().box() = extents;
  newBrepData->contentBody().setBoundingBoxBehaviour(2);

  // set reference to this body in representation item
  newBrep->setReferenceToBody(newBrepData);

  // file structure geometry section
  OdPrcTopoContextPtr newTopoContext = createTopoContext(*curStructure);
  newTopoContext->appendBody(newBrepData->objectId());
}

template <typename Type>
void AddAttribute(OdPrcAttributeData &attrdata, const OdString strTitle, const Type& data)
{
  OdPrcAttributeArray &attrArr = attrdata.attributes();
  OdPrcAttribute* newAttribute = attrArr.append();

  // create pair
  OdPrcContentSingleAttribute attributeDataPair;
  attributeDataPair.setData(data);

  // add pair to attribute
  newAttribute->AddDataPair(attributeDataPair);

  OdPrcAttributeEntry title;
  title.setData(strTitle);
  newAttribute->SetTitle(title);
}

OdPrcFilePtr CreateComplexModels (void)
{
  // common
  OdGeExtents3d extents;
  extents.addPoint(OdGePoint3d(-14.2,-14.2,-4.3));
  extents.addPoint(OdGePoint3d(14.2,14.2,0.1));
  OdPrcFilePtr pFile = CreatePRCCommonForBrepComplex();

  OdPrcFileStructurePtr washerStructure = addNewFileStructure(*pFile);
  OdPrcFileStructurePtr nutStructure = addNewFileStructure(*pFile);
  OdPrcFileStructurePtr boltStructure = addNewFileStructure(*pFile);
  OdPrcFileStructurePtr rimStructure = addNewFileStructure(*pFile);
  OdPrcFileStructurePtr tireStructure = addNewFileStructure(*pFile);

  washerStructure->fileStructureId() = OdPrcUniqueId(1,2,3,4);
  nutStructure->fileStructureId() = OdPrcUniqueId(5,6,7,8);
  boltStructure->fileStructureId() = OdPrcUniqueId(9,10,11,12);
  rimStructure->fileStructureId() = OdPrcUniqueId(13,14,15,16);
  tireStructure->fileStructureId() = OdPrcUniqueId(17,18,19,20);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // create root product occurrence
  OdPrcProductOccurrencePtr rootOccurrenceWasher = OdPrcProductOccurrence::createObject();
  washerStructure->addObject(rootOccurrenceWasher);
  washerStructure->fileStructureTree().internalData().setRootProductOccurrence(rootOccurrenceWasher->objectId());
  rootOccurrenceWasher->name().setName(L"Washer");

  AddAttribute(rootOccurrenceWasher->attributeData(), L"Weight", L"5 g");
  AddAttribute(rootOccurrenceWasher->attributeData(), L"Material", L"Steel");
  AddAttribute(rootOccurrenceWasher->attributeData(), L"Size", L"M16");
  AddAttribute(rootOccurrenceWasher->attributeData(), L"Name", rootOccurrenceWasher->name().name());
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // create root product occurrence
  OdPrcProductOccurrencePtr rootOccurrenceNut = OdPrcProductOccurrence::createObject();
  nutStructure->addObject(rootOccurrenceNut);
  nutStructure->fileStructureTree().internalData().setRootProductOccurrence(rootOccurrenceNut->objectId());
  rootOccurrenceNut->name().setName(L"Nut");

  AddAttribute(rootOccurrenceNut->attributeData(), L"Weight", L"18 g");
  AddAttribute(rootOccurrenceNut->attributeData(), L"Material", L"Steel");
  AddAttribute(rootOccurrenceNut->attributeData(), L"Size", L"M16x1.5");
  AddAttribute(rootOccurrenceNut->attributeData(), L"Name", rootOccurrenceNut->name().name());
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // create root product occurrence
  OdPrcProductOccurrencePtr rootOccurrenceBolt = OdPrcProductOccurrence::createObject();
  boltStructure->addObject(rootOccurrenceBolt);
  boltStructure->fileStructureTree().internalData().setRootProductOccurrence(rootOccurrenceBolt->objectId());
  rootOccurrenceBolt->name().setName(L"Bolt");

  AddAttribute(rootOccurrenceBolt->attributeData(), L"Weight", L"143 g");
  AddAttribute(rootOccurrenceBolt->attributeData(), L"Material", L"Steel");
  AddAttribute(rootOccurrenceBolt->attributeData(), L"Size", L"M16x1.5x60");
  AddAttribute(rootOccurrenceBolt->attributeData(), L"Name", rootOccurrenceBolt->name().name());

  OdPrcObjectIdArray &son_occurrencesForBolt = rootOccurrenceBolt->referencesOfProductOccurrence().getSonProductOccurrences();

  OdPrcProductOccurrencePtr newProductOccurrenceForWasher = OdPrcProductOccurrence::createObject();
  boltStructure->addObject(newProductOccurrenceForWasher);
  newProductOccurrenceForWasher->referencesOfProductOccurrence().setPrototype(rootOccurrenceWasher->objectId());

  OdPrcProductOccurrencePtr newProductOccurrenceForNut = OdPrcProductOccurrence::createObject();
  boltStructure->addObject(newProductOccurrenceForNut);
  newProductOccurrenceForNut->referencesOfProductOccurrence().setPrototype(rootOccurrenceNut->objectId());
  son_occurrencesForBolt.push_back(newProductOccurrenceForWasher->objectId());
  son_occurrencesForBolt.push_back(newProductOccurrenceForNut->objectId());
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // create root product occurrence
  OdPrcProductOccurrencePtr rootOccurrenceRim = OdPrcProductOccurrence::createObject();
  rimStructure->addObject(rootOccurrenceRim);
  rimStructure->fileStructureTree().internalData().setRootProductOccurrence(rootOccurrenceRim->objectId());
  rootOccurrenceRim->name().setName(L"Rim");
  AddAttribute(rootOccurrenceRim->attributeData(), L"Weight", L"1375 g");
  AddAttribute(rootOccurrenceRim->attributeData(), L"Material", L"Steel");
  AddAttribute(rootOccurrenceRim->attributeData(), L"Name", rootOccurrenceRim->name().name());
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // create root product occurrence
  OdPrcProductOccurrencePtr rootOccurrenceTire = OdPrcProductOccurrence::createObject();
  tireStructure->addObject(rootOccurrenceTire);
  OdPrcObjectIdArray &son_occurrences = rootOccurrenceTire->referencesOfProductOccurrence().getSonProductOccurrences();
  pFile->modelFileData().addStartRootOccurrence(*rootOccurrenceTire);
  tireStructure->fileStructureTree().internalData().setRootProductOccurrence(rootOccurrenceTire->objectId());
  rootOccurrenceTire->name().setName(L"Tire");
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  OdPrcTransformation3d shift;

  {
    CreateTopologyCommonForComplex(washerStructure, rootOccurrenceWasher, extents,"BrepModelWasher");  

    // Add line style to globals
    addLineStyleForBrep(*washerStructure, 1.0f, 0.0f, 0.0f);

    // Add graphic
    addGraphicDataToBrep(*washerStructure);

    // fill it with Brep Data
    OdPrcTopoContextPtr newTopoContext = washerStructure->fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
    OdPrcBrepDataPtr brepData = newTopoContext->bodies().last().safeOpenObject(kForWrite);
    FillTopoBrepFaceWasher(brepData);

    // add transformation
    OdGeVector3d translateVect (0, 0, -4.);
    OdGeMatrix3d geMatrix;
    geMatrix.setTranslation(translateVect);
    shift.set(geMatrix);
    rootOccurrenceWasher->setLocation(&shift);

    washerStructure->fileStructureGeometry().fileStructureExactGeometry().updateCoedgeNeighbours();
  }

  {
    CreateTopologyCommonForComplex(nutStructure, rootOccurrenceNut, extents, "BrepModelNut");  

    // Add line style to globals
    addLineStyleForBrep(*nutStructure, 1.0f, 0.0f, 0.0f);

    // Add graphic
    addGraphicDataToBrep(*nutStructure);

    // fill it with Brep Data
    OdPrcTopoContextPtr newTopoContext = nutStructure->fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
    OdPrcBrepDataPtr brepData = newTopoContext->bodies().last().safeOpenObject(kForWrite);
    FillTopoBrepFaceNut(brepData);

    // add transformation
    OdGeVector3d translateVect (0, 0, -4.4);
    OdGeMatrix3d geMatrix;
    geMatrix.setTranslation(translateVect);
    shift.set(geMatrix);
    rootOccurrenceNut->setLocation(&shift);

    nutStructure->fileStructureGeometry().fileStructureExactGeometry().updateCoedgeNeighbours();
  }

  {
    CreateTopologyCommonForComplex(boltStructure, rootOccurrenceBolt, extents, "BrepModelBolt");  

    // Add line style to globals
    addLineStyleForBrep(*boltStructure, 1.0f, 0.0f, 0.0f);

    // Add graphic
    addGraphicDataToBrep(*boltStructure);

    // fill it with Brep Data
    OdPrcTopoContextPtr newTopoContext = boltStructure->fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
    OdPrcBrepDataPtr brepData = newTopoContext->bodies().last().safeOpenObject(kForWrite);
    FillTopoBrepFaceBolt(brepData);

    boltStructure->fileStructureGeometry().fileStructureExactGeometry().updateCoedgeNeighbours();
  }

  {
    CreateTopologyCommonForComplex(rimStructure, rootOccurrenceRim, extents, "BrepModelRim");  

    // Add line style to globals
    addLineStyleForBrep(*rimStructure, 1.0f, 0.0f, 0.0f);

    // Add graphic
    addGraphicDataToBrep(*rimStructure);

    // fill it with Brep Data
    OdPrcTopoContextPtr newTopoContext = rimStructure->fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
    OdPrcBrepDataPtr brepData = newTopoContext->bodies().last().safeOpenObject(kForWrite);
    FillTopoBrepFaceRim(brepData);

    rimStructure->fileStructureGeometry().fileStructureExactGeometry().updateCoedgeNeighbours();
  }

  {
    CreateTopologyCommonForComplex(tireStructure, rootOccurrenceTire, extents, "BrepModelTire");  

    // Add line style to globals
    addLineStyleForBrep(*tireStructure, 1.0f, 0.0f, 0.0f);

    // Add graphic
    addGraphicDataToBrep(*tireStructure);

    // fill it with Brep Data
    OdPrcTopoContextPtr newTopoContext = tireStructure->fileStructureGeometry().fileStructureExactGeometry().topologicalContext().last();
    OdPrcBrepDataPtr brepData = newTopoContext->bodies().last().safeOpenObject(kForWrite);
    FillTopoBrepFaceTire(brepData);

    tireStructure->fileStructureGeometry().fileStructureExactGeometry().updateCoedgeNeighbours();
  }
  
  OdPrcProductOccurrencePtr newProductOccurrenceForRim = OdPrcProductOccurrence::createObject();
  tireStructure->addObject(newProductOccurrenceForRim);
  newProductOccurrenceForRim->referencesOfProductOccurrence().setPrototype(rootOccurrenceRim->objectId());

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  OdPrcProductOccurrencePtr newProductOccurrenceForBolt1 = OdPrcProductOccurrence::createObject();
  newProductOccurrenceForBolt1->name().setName(L"Bolt_1");
  {
    tireStructure->addObject(newProductOccurrenceForBolt1);
  
    // add transformation
    OdGeVector3d translateVect (4, 0, 0);
    OdGeMatrix3d geMatrix;
    geMatrix.setTranslation(translateVect);
    shift.set(geMatrix);
    newProductOccurrenceForBolt1->setLocation(&shift);

    newProductOccurrenceForBolt1->referencesOfProductOccurrence().setPrototype(rootOccurrenceBolt->objectId());
    AddAttribute(newProductOccurrenceForBolt1->attributeData(), L"Name", newProductOccurrenceForBolt1->name().name());
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  OdPrcProductOccurrencePtr newProductOccurrenceForBolt2 = OdPrcProductOccurrence::createObject();
  newProductOccurrenceForBolt2->name().setName(L"Bolt_2");
  {
    tireStructure->addObject(newProductOccurrenceForBolt2);

    // add transformation
    OdGeVector3d translateVect (-4, 0, 0);
    OdGeMatrix3d geMatrix;
    geMatrix.setTranslation(translateVect);
    shift.set(geMatrix);
    newProductOccurrenceForBolt2->setLocation(&shift);

    newProductOccurrenceForBolt2->referencesOfProductOccurrence().setPrototype(rootOccurrenceBolt->objectId());
    AddAttribute(newProductOccurrenceForBolt2->attributeData(), L"Name", newProductOccurrenceForBolt2->name().name());
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  OdPrcProductOccurrencePtr newProductOccurrenceForBolt3 = OdPrcProductOccurrence::createObject();
  newProductOccurrenceForBolt3->name().setName(L"Bolt_3");
  {
    tireStructure->addObject(newProductOccurrenceForBolt3);

    // add transformation
    OdGeVector3d translateVect (0, 4, 0);
    OdGeMatrix3d geMatrix;
    geMatrix.setTranslation(translateVect);
    shift.set(geMatrix);
    newProductOccurrenceForBolt3->setLocation(&shift);

    newProductOccurrenceForBolt3->referencesOfProductOccurrence().setPrototype(rootOccurrenceBolt->objectId());
    AddAttribute(newProductOccurrenceForBolt3->attributeData(), L"Name", newProductOccurrenceForBolt3->name().name());
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  OdPrcProductOccurrencePtr newProductOccurrenceForBolt4 = OdPrcProductOccurrence::createObject();
  newProductOccurrenceForBolt4->name().setName(L"Bolt_4");
  {
    tireStructure->addObject(newProductOccurrenceForBolt4);

    // add transformation
    OdGeVector3d translateVect (0, -4, 0);
    OdGeMatrix3d geMatrix;
    geMatrix.setTranslation(translateVect);
    shift.set(geMatrix);
    newProductOccurrenceForBolt4->setLocation(&shift);

    newProductOccurrenceForBolt4->referencesOfProductOccurrence().setPrototype(rootOccurrenceBolt->objectId());
    AddAttribute(newProductOccurrenceForBolt4->attributeData(), L"Name", newProductOccurrenceForBolt4->name().name());
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // add reference to root product occurrence
  son_occurrences.push_back(newProductOccurrenceForBolt1->objectId());
  son_occurrences.push_back(newProductOccurrenceForBolt2->objectId());
  son_occurrences.push_back(newProductOccurrenceForBolt3->objectId());
  son_occurrences.push_back(newProductOccurrenceForBolt4->objectId());
  son_occurrences.push_back(newProductOccurrenceForRim->objectId());

  return pFile;
}

void CreateComplexExample (OdStreamBufPtr pPrcStream, CreationMode mode, OdDbHostAppServices &pH, OdPrcHostAppServices &pPrcHost)
{
  ODA_ASSERT(mode == kCreateComplexExample);

  // create prc with all brep examples
  OdPrcFilePtr pFile = CreateComplexModels();

  // export prc
  pFile->writeFile(pPrcStream);
}
