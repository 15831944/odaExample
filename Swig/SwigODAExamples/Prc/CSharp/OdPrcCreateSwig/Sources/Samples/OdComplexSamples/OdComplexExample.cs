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
using System;
using OdPrcCreateSwigMgd.Samples.OdBrepModelSamples;
using Teigha.Core;
using Teigha.PRC;
using Teigha.TD;

namespace OdPrcCreateSwigMgd.Samples.OdComplexSamples
{
  public class OdComplexExample_CreateComplexExample : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "Example with complex topology";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // create prc with all brep examples
      OdPrcFile pFile = CreateComplexModels();

      // export prc
      pFile.writeFile(pPrcStream);
    }

    public static void FillTopoBrepFaceWasher(OdPrcBrepData brepData)
    {
      OdPrcConnex pCurConnex = OdPrcConnex.createObject();
      brepData.addConnex(pCurConnex);

      {
        OdPrcShell pCurShell = OdPrcShell.createObject();
        pCurConnex.addShell(pCurShell);

        OdPrcEdge edge, edge1, edge2, edge3;

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            pPrcPlane.setUVParameterization(new OdPrcUVParameterization(-1, 3, -1, 3));

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(-1, -1, 0.1)));
            pPrcPlane.setTransformation(transform);
            // TBD
          }

          OdPrcCircle3d crvCircle = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, 0.1)));
            crvCircle.setTransformation(transform);
            // TBD
            crvCircle.setRadius(1.4);
          }

          edge = OdPrcEdge.createObject();
          edge.contentWireEdge().setcurve(crvCircle);

          OdPrcUniqueVertex vertex_start = OdPrcUniqueVertex.createObject();
          vertex_start.setpoint(new OdGePoint3d(1.4, 0, 0.1));
          edge.setStartVertex(vertex_start);
          edge.setEndVertex(vertex_start);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop = OdPrcLoop.createObject();
          pCurFace.addLoop(loop);
          loop.addCoEdge(coEdge);
          loop.setOrientationWithSurface(1);


          ////////////////////////////////////////////////////////////////////////////////////////////////////////////

          OdPrcCircle3d crvCircle1 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle1.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle1.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, 0.1)));
            crvCircle1.setTransformation(transform);
            // TBD
            crvCircle1.setRadius(0.8);
          }
          edge1 = OdPrcEdge.createObject();
          edge1.contentWireEdge().setcurve(crvCircle1);

          OdPrcUniqueVertex vertex_start1 = OdPrcUniqueVertex.createObject();
          vertex_start1.setpoint(new OdGePoint3d(0.8, 0, 0.1));
          edge1.setStartVertex(vertex_start1);
          edge1.setEndVertex(vertex_start1);

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge1);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.setOrientationWithSurface(1);


          /////////////////////////////////////////////////////////////////////////////////////////////////
          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            pPrcPlane.setUVParameterization(new OdPrcUVParameterization(-1, 3, -1, 3));

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(-1, -1, -0.1)));
            pPrcPlane.setTransformation(transform);
            // TBD
          }

          OdPrcCircle3d crvCircle = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, -0.1)));
            crvCircle.setTransformation(transform);
            // TBD
            crvCircle.setRadius(1.4);
          }

          edge2 = OdPrcEdge.createObject();
          edge2.contentWireEdge().setcurve(crvCircle);

          OdPrcUniqueVertex vertex_start2 = OdPrcUniqueVertex.createObject();
          vertex_start2.setpoint(new OdGePoint3d(1.4, 0, -0.1));
          edge2.setStartVertex(vertex_start2);
          edge2.setEndVertex(vertex_start2);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge2);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop = OdPrcLoop.createObject();
          pCurFace.addLoop(loop);
          loop.addCoEdge(coEdge);
          loop.setOrientationWithSurface(0);


          ////////////////////////////////////////////////////////////////////////////////////////////////////////////

          OdPrcCircle3d crvCircle1 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle1.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle1.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, -0.1)));
            crvCircle1.setTransformation(transform);
            // TBD
            crvCircle1.setRadius(0.8);
          }
          edge3 = OdPrcEdge.createObject();
          edge3.contentWireEdge().setcurve(crvCircle1);

          OdPrcUniqueVertex vertex_start3 = OdPrcUniqueVertex.createObject();
          vertex_start3.setpoint(new OdGePoint3d(0.8, 0, -0.1));
          edge3.setStartVertex(vertex_start3);
          edge3.setEndVertex(vertex_start3);

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge3);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.setOrientationWithSurface(0);


          /////////////////////////////////////////////////////////////////////////////////////////////////

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kOpposite);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);

        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCylinder pPrcCylinder = OdPrcCylinder.createObject();
          {
            OdPrcContentSurface srfContent = pPrcCylinder.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named cylinder in srfContent");

            pPrcCylinder.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, -0.102, 0.102));
            // can add transformation if needed here
            // TBD

            pPrcCylinder.setRadius(1.4);
          }

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge2);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.setOrientationWithSurface(1);



          ///////////////////////////////////////////////////////////////////////////
          OdPrcLoop loop2 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop2);
          loop2.addCoEdge(coEdge);
          loop2.setOrientationWithSurface(1);


          ///////////////////////////////////////////////////////////////////////////

          pCurFace.setbaseSurface(pPrcCylinder);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCylinder pPrcCylinder = OdPrcCylinder.createObject();
          {
            OdPrcContentSurface srfContent = pPrcCylinder.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named cylinder in srfContent");

            pPrcCylinder.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, -0.102, 0.102));
            // can add transformation if needed here
            // TBD

            pPrcCylinder.setRadius(0.8);
          }

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge1);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge3);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.setOrientationWithSurface(0);



          ///////////////////////////////////////////////////////////////////////
          OdPrcLoop loop2 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop2);
          loop2.addCoEdge(coEdge);
          loop2.setOrientationWithSurface(0);


          ///////////////////////////////////////////////////////////////////////

          pCurFace.setbaseSurface(pPrcCylinder);
          pCurFace.setorientationSurfaceWithShell(Orientation.kOpposite);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        pCurShell.setShellIsClosed(true);
      }
    }

    public static void FillTopoBrepFaceNut(OdPrcBrepData brepData)
    {
      OdPrcConnex pCurConnex = OdPrcConnex.createObject();
      brepData.addConnex(pCurConnex);

      {
        OdPrcShell pCurShell = OdPrcShell.createObject();
        pCurConnex.addShell(pCurShell);

        OdPrcEdge edge1, edge2, edge3, edge4, edge5, edge6;

        OdPrcEdge edge11, edge12, edge13, edge14, edge15, edge16;

        OdPrcEdge edge111, edge112;

        OdPrcEdge edgeS1, edgeS2, edgeS3, edgeS4, edgeS5, edgeS6;

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          //         OdGeCircArc3d circle(OdGePoint3d(0,0,0.1),OdGeVector3d.kZAxis,1.2);
          // 
          //         OdPrcPolyLine3d crvPolyLine = OdPrcPolyLine3d.createObject();
          //         {
          //           OdPrcContentCurve crvContent = crvPolyLine.contentCurve();
          // 
          //           // - array of control points defining curve
          //           OdGePoint3dArray crvPoint;
          // //           crvPoint.Add(OdGePoint3d(2.0 , 0.0, 0.1));
          // //           crvPoint.Add(OdGePoint3d(1.0 , 1.73, 0.1));
          // //           crvPoint.Add(OdGePoint3d(-1.0 , 1.73, 0.1));
          // //           crvPoint.Add(OdGePoint3d(-2.0 , 0.0, 0.1));
          // //           crvPoint.Add(OdGePoint3d(-1.0 , -1.73, 0.1));
          // //           crvPoint.Add(OdGePoint3d(1.0 , -1.73, 0.1));
          // //           crvPoint.Add(OdGePoint3d(2.0 , 0.0, 0.1));
          // 
          //           circle.getSamplePoints(7,crvPoint);
          //           crvPoint.Add(crvPoint[0]);
          // 
          //           crvPolyLine.setPoints(crvPoint, true);
          //         }

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();

          edge1 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end = OdPrcUniqueVertex.createObject();
          vertex_start.setpoint(new OdGePoint3d(1.200000, 0.000000, 0.300000));
          vertex_end.setpoint(new OdGePoint3d(0.600000, 1.039230, 0.300000));
          edge1.setStartVertex(vertex_start);
          edge1.setEndVertex(vertex_end);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start.point(), vertex_end.point());
            pLine.setFromOdGeCurve(line);
            edge1.contentWireEdge().setcurve(pLine);
          }

          coEdge1.setEdge(edge1);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();

          edge2 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start2 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end2 = OdPrcUniqueVertex.createObject();
          vertex_start2.setpoint(new OdGePoint3d(0.600000, 1.039230, 0.300000));
          vertex_end2.setpoint(new OdGePoint3d(-0.600000, 1.039230, 0.300000));
          edge2.setStartVertex(vertex_start2);
          edge2.setEndVertex(vertex_end2);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start2.point(), vertex_end2.point());
            pLine.setFromOdGeCurve(line);
            edge2.contentWireEdge().setcurve(pLine);
          }

          coEdge2.setEdge(edge2);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();

          edge3 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start3 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end3 = OdPrcUniqueVertex.createObject();
          vertex_start3.setpoint(new OdGePoint3d(-0.600000, 1.039230, 0.300000));
          vertex_end3.setpoint(new OdGePoint3d(-1.200000, 0.000000, 0.300000));
          edge3.setStartVertex(vertex_start3);
          edge3.setEndVertex(vertex_end3);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start3.point(), vertex_end3.point());
            pLine.setFromOdGeCurve(line);
            edge3.contentWireEdge().setcurve(pLine);
          }

          coEdge3.setEdge(edge3);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();

          edge4 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start4 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end4 = OdPrcUniqueVertex.createObject();
          vertex_start4.setpoint(new OdGePoint3d(-1.200000, 0.000000, 0.300000));
          vertex_end4.setpoint(new OdGePoint3d(-0.600000, -1.039230, 0.300000));
          edge4.setStartVertex(vertex_start4);
          edge4.setEndVertex(vertex_end4);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start4.point(), vertex_end4.point());
            pLine.setFromOdGeCurve(line);
            edge4.contentWireEdge().setcurve(pLine);
          }

          coEdge4.setEdge(edge4);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge5 = OdPrcCoEdge.createObject();

          edge5 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start5 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end5 = OdPrcUniqueVertex.createObject();
          vertex_start5.setpoint(new OdGePoint3d(-0.600000, -1.039230, 0.300000));
          vertex_end5.setpoint(new OdGePoint3d(0.600000, -1.039230, 0.300000));
          edge5.setStartVertex(vertex_start5);
          edge5.setEndVertex(vertex_end5);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start5.point(), vertex_end5.point());
            pLine.setFromOdGeCurve(line);
            edge5.contentWireEdge().setcurve(pLine);
          }

          coEdge5.setEdge(edge5);
          coEdge5.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge6 = OdPrcCoEdge.createObject();

          edge6 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start6 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end6 = OdPrcUniqueVertex.createObject();
          vertex_start6.setpoint(new OdGePoint3d(0.600000, -1.039230, 0.300000));
          vertex_end6.setpoint(new OdGePoint3d(1.200000, 0.000000, 0.300000));
          edge6.setStartVertex(vertex_start6);
          edge6.setEndVertex(vertex_end6);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start6.point(), vertex_end6.point());
            pLine.setFromOdGeCurve(line);
            edge6.contentWireEdge().setcurve(pLine);
          }

          coEdge6.setEdge(edge6);
          coEdge6.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop = OdPrcLoop.createObject();
          pCurFace.addLoop(loop);
          loop.addCoEdge(coEdge1);
          loop.addCoEdge(coEdge2);
          loop.addCoEdge(coEdge3);
          loop.addCoEdge(coEdge4);
          loop.addCoEdge(coEdge5);
          loop.addCoEdge(coEdge6);
          loop.setOrientationWithSurface(1);


          //////////////////////////////////////////////////////////////////////////////////////////////////////////
          OdPrcCircle3d crvCircle1 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle1.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle1.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, 0.3)));
            crvCircle1.setTransformation(transform);
            // TBD
            crvCircle1.setRadius(0.6);
          }
          edge111 = OdPrcEdge.createObject();
          edge111.contentWireEdge().setcurve(crvCircle1);

          OdPrcUniqueVertex vertex_start1 = OdPrcUniqueVertex.createObject();
          vertex_start1.setpoint(new OdGePoint3d(0.6, 0, 0.3));
          edge111.setStartVertex(vertex_start1);
          edge111.setEndVertex(vertex_start1);

          OdPrcCoEdge coEdge11 = OdPrcCoEdge.createObject();
          coEdge11.setEdge(edge111);
          coEdge11.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge11);
          loop1.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge1.vertexEnd()).point() - ((OdPrcUniqueVertex)edge1.vertexStart()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edge2.vertexEnd()).point() - ((OdPrcUniqueVertex)edge2.vertexStart()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge1.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          ////////////////////////////////////////////////////////////////////////////////////////////////////
          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }


        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();

          edge11 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end = OdPrcUniqueVertex.createObject();
          vertex_start.setpoint(new OdGePoint3d(1.200000, 0.000000, -0.300000));
          vertex_end.setpoint(new OdGePoint3d(0.600000, -1.039230, -0.300000));
          edge11.setStartVertex(vertex_start);
          edge11.setEndVertex(vertex_end);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start.point(), vertex_end.point());
            pLine.setFromOdGeCurve(line);
            edge11.contentWireEdge().setcurve(pLine);
          }

          coEdge1.setEdge(edge11);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();

          edge12 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start2 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end2 = OdPrcUniqueVertex.createObject();
          vertex_start2.setpoint(new OdGePoint3d(0.600000, -1.039230, -0.300000));
          vertex_end2.setpoint(new OdGePoint3d(-0.600000, -1.039230, -0.300000));
          edge12.setStartVertex(vertex_start2);
          edge12.setEndVertex(vertex_end2);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start2.point(), vertex_end2.point());
            pLine.setFromOdGeCurve(line);
            edge12.contentWireEdge().setcurve(pLine);
          }

          coEdge2.setEdge(edge12);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();

          edge13 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start3 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end3 = OdPrcUniqueVertex.createObject();
          vertex_start3.setpoint(new OdGePoint3d(-0.600000, -1.039230, -0.300000));
          vertex_end3.setpoint(new OdGePoint3d(-1.200000, 0.000000, -0.300000));
          edge13.setStartVertex(vertex_start3);
          edge13.setEndVertex(vertex_end3);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start3.point(), vertex_end3.point());
            pLine.setFromOdGeCurve(line);
            edge13.contentWireEdge().setcurve(pLine);
          }

          coEdge3.setEdge(edge13);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();

          edge14 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start4 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end4 = OdPrcUniqueVertex.createObject();
          vertex_start4.setpoint(new OdGePoint3d(-1.200000, 0.000000, -0.300000));
          vertex_end4.setpoint(new OdGePoint3d(-0.600000, 1.039230, -0.300000));
          edge14.setStartVertex(vertex_start4);
          edge14.setEndVertex(vertex_end4);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start4.point(), vertex_end4.point());
            pLine.setFromOdGeCurve(line);
            edge14.contentWireEdge().setcurve(pLine);
          }

          coEdge4.setEdge(edge14);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge5 = OdPrcCoEdge.createObject();

          edge15 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start5 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end5 = OdPrcUniqueVertex.createObject();
          vertex_start5.setpoint(new OdGePoint3d(-0.600000, 1.039230, -0.300000));
          vertex_end5.setpoint(new OdGePoint3d(0.600000, 1.039230, -0.300000));
          edge15.setStartVertex(vertex_start5);
          edge15.setEndVertex(vertex_end5);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start5.point(), vertex_end5.point());
            pLine.setFromOdGeCurve(line);
            edge15.contentWireEdge().setcurve(pLine);
          }

          coEdge5.setEdge(edge15);
          coEdge5.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge6 = OdPrcCoEdge.createObject();

          edge16 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start6 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end6 = OdPrcUniqueVertex.createObject();
          vertex_start6.setpoint(new OdGePoint3d(0.600000, 1.039230, -0.300000));
          vertex_end6.setpoint(new OdGePoint3d(1.200000, 0.000000, -0.300000));
          edge16.setStartVertex(vertex_start6);
          edge16.setEndVertex(vertex_end6);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start6.point(), vertex_end6.point());
            pLine.setFromOdGeCurve(line);
            edge16.contentWireEdge().setcurve(pLine);
          }

          coEdge6.setEdge(edge16);
          coEdge6.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop = OdPrcLoop.createObject();
          pCurFace.addLoop(loop);
          loop.addCoEdge(coEdge1);
          loop.addCoEdge(coEdge2);
          loop.addCoEdge(coEdge3);
          loop.addCoEdge(coEdge4);
          loop.addCoEdge(coEdge5);
          loop.addCoEdge(coEdge6);
          loop.setOrientationWithSurface(1);


          //////////////////////////////////////////////////////////////////////////////////////////////////////////
          OdPrcCircle3d crvCircle1 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle1.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle1.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, -0.3)));
            crvCircle1.setTransformation(transform);
            // TBD
            crvCircle1.setRadius(0.6);
          }
          edge112 = OdPrcEdge.createObject();
          edge112.contentWireEdge().setcurve(crvCircle1);

          OdPrcUniqueVertex vertex_start1 = OdPrcUniqueVertex.createObject();
          vertex_start1.setpoint(new OdGePoint3d(0.6, 0, -0.3));
          edge112.setStartVertex(vertex_start1);
          edge112.setEndVertex(vertex_start1);

          OdPrcCoEdge coEdge11 = OdPrcCoEdge.createObject();
          coEdge11.setEdge(edge112);
          coEdge11.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge11);
          loop1.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge11.vertexEnd()).point() - ((OdPrcUniqueVertex)edge11.vertexStart()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edge12.vertexEnd()).point() - ((OdPrcUniqueVertex)edge12.vertexStart()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge11.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          ////////////////////////////////////////////////////////////////////////////////////////////////////
          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCylinder pPrcCylinder = OdPrcCylinder.createObject();
          {
            OdPrcContentSurface srfContent = pPrcCylinder.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named cylinder in srfContent");

            pPrcCylinder.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, -0.306, 0.306));
            // can add transformation if needed here
            // TBD

            pPrcCylinder.setRadius(0.6);
          }

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge111);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge112);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.setOrientationWithSurface(0);



          ///////////////////////////////////////////////////////////////////////
          OdPrcLoop loop2 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop2);
          loop2.addCoEdge(coEdge);
          loop2.setOrientationWithSurface(0);


          ///////////////////////////////////////////////////////////////////////

          pCurFace.setbaseSurface(pPrcCylinder);
          pCurFace.setorientationSurfaceWithShell(Orientation.kOpposite);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge1);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();
          edgeS2 = OdPrcEdge.createObject();
          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(((OdPrcUniqueVertex)edge1.vertexStart()).point(), ((OdPrcUniqueVertex)edge11.vertexStart()).point());
            pLine.setFromOdGeCurve(line);
            edgeS2.contentWireEdge().setcurve(pLine);
          }
          edgeS2.setStartVertex(edge1.vertexStart());
          edgeS2.setEndVertex(edge11.vertexStart());

          coEdge2.setEdge(edgeS2);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();
          coEdge3.setEdge(edge16);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();
          edgeS1 = OdPrcEdge.createObject();
          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(((OdPrcUniqueVertex)edge16.vertexStart()).point(), ((OdPrcUniqueVertex)edge1.vertexEnd()).point());
            pLine.setFromOdGeCurve(line);
            edgeS1.contentWireEdge().setcurve(pLine);
          }
          edgeS1.setStartVertex(edge16.vertexStart());
          edgeS1.setEndVertex(edge1.vertexEnd());
          coEdge4.setEdge(edgeS1);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);


          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.addCoEdge(coEdge2);
          loop1.addCoEdge(coEdge3);
          loop1.addCoEdge(coEdge4);
          loop1.setOrientationWithSurface(1);


          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge1.vertexStart()).point() - ((OdPrcUniqueVertex)edge1.vertexEnd()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edgeS2.vertexEnd()).point() - ((OdPrcUniqueVertex)edgeS2.vertexStart()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge1.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge2);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();
          coEdge2.setEdge(edgeS1);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();
          coEdge3.setEdge(edge15);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();
          edgeS3 = OdPrcEdge.createObject();
          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(((OdPrcUniqueVertex)edge15.vertexStart()).point(), ((OdPrcUniqueVertex)edge2.vertexEnd()).point());
            pLine.setFromOdGeCurve(line);
            edgeS3.contentWireEdge().setcurve(pLine);
          }
          edgeS3.setStartVertex(edge15.vertexStart());
          edgeS3.setEndVertex(edge2.vertexEnd());

          coEdge4.setEdge(edgeS3);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);


          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.addCoEdge(coEdge2);
          loop1.addCoEdge(coEdge3);
          loop1.addCoEdge(coEdge4);
          loop1.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge2.vertexStart()).point() - ((OdPrcUniqueVertex)edge2.vertexEnd()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edgeS1.vertexStart()).point() - ((OdPrcUniqueVertex)edgeS1.vertexEnd()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge2.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge3);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();
          coEdge2.setEdge(edgeS3);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();
          coEdge3.setEdge(edge14);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();
          edgeS4 = OdPrcEdge.createObject();
          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(((OdPrcUniqueVertex)edge14.vertexStart()).point(), ((OdPrcUniqueVertex)edge3.vertexEnd()).point());
            pLine.setFromOdGeCurve(line);
            edgeS4.contentWireEdge().setcurve(pLine);
          }
          edgeS4.setStartVertex(edge14.vertexStart());
          edgeS4.setEndVertex(edge3.vertexEnd());

          coEdge4.setEdge(edgeS4);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);


          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.addCoEdge(coEdge2);
          loop1.addCoEdge(coEdge3);
          loop1.addCoEdge(coEdge4);
          loop1.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge3.vertexStart()).point() - ((OdPrcUniqueVertex)edge3.vertexEnd()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edgeS3.vertexStart()).point() - ((OdPrcUniqueVertex)edgeS3.vertexEnd()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge3.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge4);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();
          coEdge2.setEdge(edgeS4);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();
          coEdge3.setEdge(edge13);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();
          edgeS5 = OdPrcEdge.createObject();
          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(((OdPrcUniqueVertex)edge13.vertexStart()).point(), ((OdPrcUniqueVertex)edge4.vertexEnd()).point());
            pLine.setFromOdGeCurve(line);
            edgeS5.contentWireEdge().setcurve(pLine);
          }
          edgeS5.setStartVertex(edge13.vertexStart());
          edgeS5.setEndVertex(edge4.vertexEnd());

          coEdge4.setEdge(edgeS5);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.addCoEdge(coEdge2);
          loop1.addCoEdge(coEdge3);
          loop1.addCoEdge(coEdge4);
          loop1.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge4.vertexStart()).point() - ((OdPrcUniqueVertex)edge4.vertexEnd()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edgeS4.vertexStart()).point() - ((OdPrcUniqueVertex)edgeS4.vertexEnd()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge4.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge5);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();
          coEdge2.setEdge(edgeS5);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();
          coEdge3.setEdge(edge12);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();
          edgeS6 = OdPrcEdge.createObject();
          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(((OdPrcUniqueVertex)edge12.vertexStart()).point(), ((OdPrcUniqueVertex)edge5.vertexEnd()).point());
            pLine.setFromOdGeCurve(line);
            edgeS6.contentWireEdge().setcurve(pLine);
          }
          edgeS6.setStartVertex(edge12.vertexStart());
          edgeS6.setEndVertex(edge5.vertexEnd());

          coEdge4.setEdge(edgeS6);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);


          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.addCoEdge(coEdge2);
          loop1.addCoEdge(coEdge3);
          loop1.addCoEdge(coEdge4);
          loop1.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge5.vertexStart()).point() - ((OdPrcUniqueVertex)edge5.vertexEnd()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edgeS5.vertexStart()).point() - ((OdPrcUniqueVertex)edgeS5.vertexEnd()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge5.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge6);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();
          coEdge2.setEdge(edgeS6);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();
          coEdge3.setEdge(edge11);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();
          coEdge4.setEdge(edgeS2);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kOpposite);


          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.addCoEdge(coEdge2);
          loop1.addCoEdge(coEdge3);
          loop1.addCoEdge(coEdge4);
          loop1.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge6.vertexStart()).point() - ((OdPrcUniqueVertex)edge6.vertexEnd()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edgeS6.vertexStart()).point() - ((OdPrcUniqueVertex)edgeS6.vertexEnd()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge6.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        pCurShell.setShellIsClosed(true);
      }
    }

    public static void FillTopoBrepFaceBolt(OdPrcBrepData brepData)
    {
      OdPrcConnex pCurConnex = OdPrcConnex.createObject();
      brepData.addConnex(pCurConnex);

      {
        OdPrcShell pCurShell = OdPrcShell.createObject();
        pCurConnex.addShell(pCurShell);

        OdPrcEdge edge1, edge2, edge3, edge4, edge5, edge6;

        OdPrcEdge edge11, edge12, edge13, edge14, edge15, edge16;

        OdPrcEdge edge111, edge112;

        OdPrcEdge edgeS1, edgeS2, edgeS3, edgeS4, edgeS5, edgeS6;

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          //         OdGeCircArc3d circle(OdGePoint3d(0,0,0.1),OdGeVector3d.kZAxis,1.2);
          // 
          //         OdPrcPolyLine3d crvPolyLine = OdPrcPolyLine3d.createObject();
          //         {
          //           OdPrcContentCurve crvContent = crvPolyLine.contentCurve();
          // 
          //           // - array of control points defining curve
          //           OdGePoint3dArray crvPoint;
          // //           crvPoint.Add(OdGePoint3d(2.0 , 0.0, 0.1));
          // //           crvPoint.Add(OdGePoint3d(1.0 , 1.73, 0.1));
          // //           crvPoint.Add(OdGePoint3d(-1.0 , 1.73, 0.1));
          // //           crvPoint.Add(OdGePoint3d(-2.0 , 0.0, 0.1));
          // //           crvPoint.Add(OdGePoint3d(-1.0 , -1.73, 0.1));
          // //           crvPoint.Add(OdGePoint3d(1.0 , -1.73, 0.1));
          // //           crvPoint.Add(OdGePoint3d(2.0 , 0.0, 0.1));
          // 
          //           circle.getSamplePoints(7,crvPoint);
          //           crvPoint.Add(crvPoint[0]);
          // 
          //           crvPolyLine.setPoints(crvPoint, true);
          //         }

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();

          edge1 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end = OdPrcUniqueVertex.createObject();
          vertex_start.setpoint(new OdGePoint3d(1.200000, 0.000000, 0.300000));
          vertex_end.setpoint(new OdGePoint3d(0.600000, 1.039230, 0.300000));
          edge1.setStartVertex(vertex_start);
          edge1.setEndVertex(vertex_end);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start.point(), vertex_end.point());
            pLine.setFromOdGeCurve(line);
            edge1.contentWireEdge().setcurve(pLine);
          }

          coEdge1.setEdge(edge1);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();

          edge2 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start2 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end2 = OdPrcUniqueVertex.createObject();
          vertex_start2.setpoint(new OdGePoint3d(0.600000, 1.039230, 0.300000));
          vertex_end2.setpoint(new OdGePoint3d(-0.600000, 1.039230, 0.300000));
          edge2.setStartVertex(vertex_start2);
          edge2.setEndVertex(vertex_end2);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start2.point(), vertex_end2.point());
            pLine.setFromOdGeCurve(line);
            edge2.contentWireEdge().setcurve(pLine);
          }

          coEdge2.setEdge(edge2);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();

          edge3 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start3 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end3 = OdPrcUniqueVertex.createObject();
          vertex_start3.setpoint(new OdGePoint3d(-0.600000, 1.039230, 0.300000));
          vertex_end3.setpoint(new OdGePoint3d(-1.200000, 0.000000, 0.300000));
          edge3.setStartVertex(vertex_start3);
          edge3.setEndVertex(vertex_end3);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start3.point(), vertex_end3.point());
            pLine.setFromOdGeCurve(line);
            edge3.contentWireEdge().setcurve(pLine);
          }

          coEdge3.setEdge(edge3);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();

          edge4 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start4 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end4 = OdPrcUniqueVertex.createObject();
          vertex_start4.setpoint(new OdGePoint3d(-1.200000, 0.000000, 0.300000));
          vertex_end4.setpoint(new OdGePoint3d(-0.600000, -1.039230, 0.300000));
          edge4.setStartVertex(vertex_start4);
          edge4.setEndVertex(vertex_end4);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start4.point(), vertex_end4.point());
            pLine.setFromOdGeCurve(line);
            edge4.contentWireEdge().setcurve(pLine);
          }

          coEdge4.setEdge(edge4);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge5 = OdPrcCoEdge.createObject();

          edge5 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start5 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end5 = OdPrcUniqueVertex.createObject();
          vertex_start5.setpoint(new OdGePoint3d(-0.600000, -1.039230, 0.300000));
          vertex_end5.setpoint(new OdGePoint3d(0.600000, -1.039230, 0.300000));
          edge5.setStartVertex(vertex_start5);
          edge5.setEndVertex(vertex_end5);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start5.point(), vertex_end5.point());
            pLine.setFromOdGeCurve(line);
            edge5.contentWireEdge().setcurve(pLine);
          }

          coEdge5.setEdge(edge5);
          coEdge5.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge6 = OdPrcCoEdge.createObject();

          edge6 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start6 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end6 = OdPrcUniqueVertex.createObject();
          vertex_start6.setpoint(new OdGePoint3d(0.600000, -1.039230, 0.300000));
          vertex_end6.setpoint(new OdGePoint3d(1.200000, 0.000000, 0.300000));
          edge6.setStartVertex(vertex_start6);
          edge6.setEndVertex(vertex_end6);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start6.point(), vertex_end6.point());
            pLine.setFromOdGeCurve(line);
            edge6.contentWireEdge().setcurve(pLine);
          }

          coEdge6.setEdge(edge6);
          coEdge6.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop = OdPrcLoop.createObject();
          pCurFace.addLoop(loop);
          loop.addCoEdge(coEdge1);
          loop.addCoEdge(coEdge2);
          loop.addCoEdge(coEdge3);
          loop.addCoEdge(coEdge4);
          loop.addCoEdge(coEdge5);
          loop.addCoEdge(coEdge6);
          loop.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge1.vertexEnd()).point() - ((OdPrcUniqueVertex)edge1.vertexStart()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edge2.vertexEnd()).point() - ((OdPrcUniqueVertex)edge2.vertexStart()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge1.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }


        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();

          edge11 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end = OdPrcUniqueVertex.createObject();
          vertex_start.setpoint(new OdGePoint3d(1.200000, 0.000000, -0.300000));
          vertex_end.setpoint(new OdGePoint3d(0.600000, -1.039230, -0.300000));
          edge11.setStartVertex(vertex_start);
          edge11.setEndVertex(vertex_end);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start.point(), vertex_end.point());
            pLine.setFromOdGeCurve(line);
            edge11.contentWireEdge().setcurve(pLine);
          }

          coEdge1.setEdge(edge11);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();

          edge12 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start2 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end2 = OdPrcUniqueVertex.createObject();
          vertex_start2.setpoint(new OdGePoint3d(0.600000, -1.039230, -0.300000));
          vertex_end2.setpoint(new OdGePoint3d(-0.600000, -1.039230, -0.300000));
          edge12.setStartVertex(vertex_start2);
          edge12.setEndVertex(vertex_end2);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start2.point(), vertex_end2.point());
            pLine.setFromOdGeCurve(line);
            edge12.contentWireEdge().setcurve(pLine);
          }

          coEdge2.setEdge(edge12);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();

          edge13 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start3 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end3 = OdPrcUniqueVertex.createObject();
          vertex_start3.setpoint(new OdGePoint3d(-0.600000, -1.039230, -0.300000));
          vertex_end3.setpoint(new OdGePoint3d(-1.200000, 0.000000, -0.300000));
          edge13.setStartVertex(vertex_start3);
          edge13.setEndVertex(vertex_end3);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start3.point(), vertex_end3.point());
            pLine.setFromOdGeCurve(line);
            edge13.contentWireEdge().setcurve(pLine);
          }

          coEdge3.setEdge(edge13);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();

          edge14 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start4 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end4 = OdPrcUniqueVertex.createObject();
          vertex_start4.setpoint(new OdGePoint3d(-1.200000, 0.000000, -0.300000));
          vertex_end4.setpoint(new OdGePoint3d(-0.600000, 1.039230, -0.300000));
          edge14.setStartVertex(vertex_start4);
          edge14.setEndVertex(vertex_end4);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start4.point(), vertex_end4.point());
            pLine.setFromOdGeCurve(line);
            edge14.contentWireEdge().setcurve(pLine);
          }

          coEdge4.setEdge(edge14);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge5 = OdPrcCoEdge.createObject();

          edge15 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start5 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end5 = OdPrcUniqueVertex.createObject();
          vertex_start5.setpoint(new OdGePoint3d(-0.600000, 1.039230, -0.300000));
          vertex_end5.setpoint(new OdGePoint3d(0.600000, 1.039230, -0.300000));
          edge15.setStartVertex(vertex_start5);
          edge15.setEndVertex(vertex_end5);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start5.point(), vertex_end5.point());
            pLine.setFromOdGeCurve(line);
            edge15.contentWireEdge().setcurve(pLine);
          }

          coEdge5.setEdge(edge15);
          coEdge5.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge6 = OdPrcCoEdge.createObject();

          edge16 = OdPrcEdge.createObject();
          OdPrcUniqueVertex vertex_start6 = OdPrcUniqueVertex.createObject();
          OdPrcUniqueVertex vertex_end6 = OdPrcUniqueVertex.createObject();
          vertex_start6.setpoint(new OdGePoint3d(0.600000, 1.039230, -0.300000));
          vertex_end6.setpoint(new OdGePoint3d(1.200000, 0.000000, -0.300000));
          edge16.setStartVertex(vertex_start6);
          edge16.setEndVertex(vertex_end6);

          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(vertex_start6.point(), vertex_end6.point());
            pLine.setFromOdGeCurve(line);
            edge16.contentWireEdge().setcurve(pLine);
          }

          coEdge6.setEdge(edge16);
          coEdge6.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop = OdPrcLoop.createObject();
          pCurFace.addLoop(loop);
          loop.addCoEdge(coEdge1);
          loop.addCoEdge(coEdge2);
          loop.addCoEdge(coEdge3);
          loop.addCoEdge(coEdge4);
          loop.addCoEdge(coEdge5);
          loop.addCoEdge(coEdge6);
          loop.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge11.vertexEnd()).point() - ((OdPrcUniqueVertex)edge11.vertexStart()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edge12.vertexEnd()).point() - ((OdPrcUniqueVertex)edge12.vertexStart()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge11.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          //////////////////////////////////////////////////////////////////////////////////////////////////////////
          OdPrcCircle3d crvCircle1 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle1.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle1.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, -0.3)));
            crvCircle1.setTransformation(transform);
            // TBD
            crvCircle1.setRadius(0.6);
          }
          edge112 = OdPrcEdge.createObject();
          edge112.contentWireEdge().setcurve(crvCircle1);

          OdPrcUniqueVertex vertex_start1 = OdPrcUniqueVertex.createObject();
          vertex_start1.setpoint(new OdGePoint3d(0.6, 0, -0.3));
          edge112.setStartVertex(vertex_start1);
          edge112.setEndVertex(vertex_start1);

          OdPrcCoEdge coEdge11 = OdPrcCoEdge.createObject();
          coEdge11.setEdge(edge112);
          coEdge11.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge11);
          loop1.setOrientationWithSurface(1);


          ////////////////////////////////////////////////////////////////////////////////////////////////////
          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            pPrcPlane.setUVParameterization(new OdPrcUVParameterization(0, 4, 0, 4));

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            OdGeMatrix3d matr = new OdGeMatrix3d();
            matr *= OdGeMatrix3d.translation(new OdGeVector3d(-2, 2, -5));
            matr *= OdGeMatrix3d.rotation(Globals.OdaPI, OdGeVector3d.kXAxis);
            transform.set(matr);
            pPrcPlane.setTransformation(transform);
            // TBD
          }

          OdPrcCircle3d crvCircle1 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle1.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle1.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, -5)));
            crvCircle1.setTransformation(transform);
            // TBD
            crvCircle1.setRadius(0.6);
          }
          edge111 = OdPrcEdge.createObject();
          edge111.contentWireEdge().setcurve(crvCircle1);

          OdPrcUniqueVertex vertex_start1 = OdPrcUniqueVertex.createObject();
          vertex_start1.setpoint(new OdGePoint3d(0.6, 0, -5));
          edge111.setStartVertex(vertex_start1);
          edge111.setEndVertex(vertex_start1);

          OdPrcCoEdge coEdge11 = OdPrcCoEdge.createObject();
          coEdge11.setEdge(edge111);
          coEdge11.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge11);
          loop1.setOrientationWithSurface(1);



          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCylinder pPrcCylinder = OdPrcCylinder.createObject();
          {
            OdPrcContentSurface srfContent = pPrcCylinder.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named cylinder in srfContent");

            pPrcCylinder.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, -2.397, 2.397));
            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, -2.65)));
            pPrcCylinder.setTransformation(transform);
            // TBD

            pPrcCylinder.setRadius(0.6);
          }

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge111);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge112);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.setOrientationWithSurface(1);

          ///////////////////////////////////////////////////////////////////////
          OdPrcLoop loop2 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop2);
          loop2.addCoEdge(coEdge);
          loop2.setOrientationWithSurface(1);

          ///////////////////////////////////////////////////////////////////////

          pCurFace.setbaseSurface(pPrcCylinder);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge1);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();
          edgeS2 = OdPrcEdge.createObject();
          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(((OdPrcUniqueVertex)edge1.vertexStart()).point(), ((OdPrcUniqueVertex)edge11.vertexStart()).point());
            pLine.setFromOdGeCurve(line);
            edgeS2.contentWireEdge().setcurve(pLine);
          }
          edgeS2.setStartVertex(edge1.vertexStart());
          edgeS2.setEndVertex(edge11.vertexStart());

          coEdge2.setEdge(edgeS2);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();
          coEdge3.setEdge(edge16);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();
          edgeS1 = OdPrcEdge.createObject();
          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(((OdPrcUniqueVertex)edge16.vertexStart()).point(), ((OdPrcUniqueVertex)edge1.vertexEnd()).point());
            pLine.setFromOdGeCurve(line);
            edgeS1.contentWireEdge().setcurve(pLine);
          }
          edgeS1.setStartVertex(edge16.vertexStart());
          edgeS1.setEndVertex(edge1.vertexEnd());
          coEdge4.setEdge(edgeS1);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);


          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.addCoEdge(coEdge2);
          loop1.addCoEdge(coEdge3);
          loop1.addCoEdge(coEdge4);
          loop1.setOrientationWithSurface(1);


          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge1.vertexStart()).point() - ((OdPrcUniqueVertex)edge1.vertexEnd()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edgeS2.vertexEnd()).point() - ((OdPrcUniqueVertex)edgeS2.vertexStart()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge1.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge2);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();
          coEdge2.setEdge(edgeS1);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();
          coEdge3.setEdge(edge15);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();
          edgeS3 = OdPrcEdge.createObject();
          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(((OdPrcUniqueVertex)edge15.vertexStart()).point(), ((OdPrcUniqueVertex)edge2.vertexEnd()).point());
            pLine.setFromOdGeCurve(line);
            edgeS3.contentWireEdge().setcurve(pLine);
          }
          edgeS3.setStartVertex(edge15.vertexStart());
          edgeS3.setEndVertex(edge2.vertexEnd());

          coEdge4.setEdge(edgeS3);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);


          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.addCoEdge(coEdge2);
          loop1.addCoEdge(coEdge3);
          loop1.addCoEdge(coEdge4);
          loop1.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge2.vertexStart()).point() - ((OdPrcUniqueVertex)edge2.vertexEnd()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edgeS1.vertexStart()).point() - ((OdPrcUniqueVertex)edgeS1.vertexEnd()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge2.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge3);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();
          coEdge2.setEdge(edgeS3);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();
          coEdge3.setEdge(edge14);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();
          edgeS4 = OdPrcEdge.createObject();
          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(((OdPrcUniqueVertex)edge14.vertexStart()).point(), ((OdPrcUniqueVertex)edge3.vertexEnd()).point());
            pLine.setFromOdGeCurve(line);
            edgeS4.contentWireEdge().setcurve(pLine);
          }
          edgeS4.setStartVertex(edge14.vertexStart());
          edgeS4.setEndVertex(edge3.vertexEnd());

          coEdge4.setEdge(edgeS4);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);


          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.addCoEdge(coEdge2);
          loop1.addCoEdge(coEdge3);
          loop1.addCoEdge(coEdge4);
          loop1.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge3.vertexStart()).point() - ((OdPrcUniqueVertex)edge3.vertexEnd()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edgeS3.vertexStart()).point() - ((OdPrcUniqueVertex)edgeS3.vertexEnd()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge3.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge4);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();
          coEdge2.setEdge(edgeS4);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();
          coEdge3.setEdge(edge13);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();
          edgeS5 = OdPrcEdge.createObject();
          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(((OdPrcUniqueVertex)edge13.vertexStart()).point(), ((OdPrcUniqueVertex)edge4.vertexEnd()).point());
            pLine.setFromOdGeCurve(line);
            edgeS5.contentWireEdge().setcurve(pLine);
          }
          edgeS5.setStartVertex(edge13.vertexStart());
          edgeS5.setEndVertex(edge4.vertexEnd());

          coEdge4.setEdge(edgeS5);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.addCoEdge(coEdge2);
          loop1.addCoEdge(coEdge3);
          loop1.addCoEdge(coEdge4);
          loop1.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge4.vertexStart()).point() - ((OdPrcUniqueVertex)edge4.vertexEnd()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edgeS4.vertexStart()).point() - ((OdPrcUniqueVertex)edgeS4.vertexEnd()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge4.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge5);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();
          coEdge2.setEdge(edgeS5);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();
          coEdge3.setEdge(edge12);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();
          edgeS6 = OdPrcEdge.createObject();
          {
            OdPrcLine3d pLine = OdPrcLine3d.createObject();
            OdGeLineSeg3d line = new OdGeLineSeg3d(((OdPrcUniqueVertex)edge12.vertexStart()).point(), ((OdPrcUniqueVertex)edge5.vertexEnd()).point());
            pLine.setFromOdGeCurve(line);
            edgeS6.contentWireEdge().setcurve(pLine);
          }
          edgeS6.setStartVertex(edge12.vertexStart());
          edgeS6.setEndVertex(edge5.vertexEnd());

          coEdge4.setEdge(edgeS6);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kSame);


          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.addCoEdge(coEdge2);
          loop1.addCoEdge(coEdge3);
          loop1.addCoEdge(coEdge4);
          loop1.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge5.vertexStart()).point() - ((OdPrcUniqueVertex)edge5.vertexEnd()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edgeS5.vertexStart()).point() - ((OdPrcUniqueVertex)edgeS5.vertexEnd()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge5.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCoEdge coEdge1 = OdPrcCoEdge.createObject();
          coEdge1.setEdge(edge6);
          coEdge1.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge2 = OdPrcCoEdge.createObject();
          coEdge2.setEdge(edgeS6);
          coEdge2.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge3 = OdPrcCoEdge.createObject();
          coEdge3.setEdge(edge11);
          coEdge3.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge4 = OdPrcCoEdge.createObject();
          coEdge4.setEdge(edgeS2);
          coEdge4.setOrientationWithLoop((sbyte)Orientation.kOpposite);


          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coEdge1);
          loop1.addCoEdge(coEdge2);
          loop1.addCoEdge(coEdge3);
          loop1.addCoEdge(coEdge4);
          loop1.setOrientationWithSurface(1);

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            OdGeVector3d vec1 = ((OdPrcUniqueVertex)edge6.vertexStart()).point() - ((OdPrcUniqueVertex)edge6.vertexEnd()).point();
            OdGeVector3d vec2 = ((OdPrcUniqueVertex)edgeS6.vertexStart()).point() - ((OdPrcUniqueVertex)edgeS6.vertexEnd()).point();
            OdGeVector3d vrNormal = vec1.crossProduct(vec2);
            vrNormal.normalize();
            OdGePlane gePlane = new OdGePlane(((OdPrcUniqueVertex)edge6.vertexStart()).point(), vrNormal);
            OdGeInterval intU = new OdGeInterval(-3.0, 3);
            OdGeInterval intV = new OdGeInterval(-3.0, 3);
            gePlane.setEnvelope(intU, intV);
            pPrcPlane.setFromOdGeSurface(gePlane);
          }

          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        pCurShell.setShellIsClosed(true);
      }
    }

    public static void FillTopoBrepFaceRim(OdPrcBrepData brepData)
    {
      OdPrcConnex pCurConnex = OdPrcConnex.createObject();
      brepData.addConnex(pCurConnex);

      {
        OdPrcShell pCurShell = OdPrcShell.createObject();
        pCurConnex.addShell(pCurShell);

        OdPrcEdge edge11, edge12, edge13, edge14, edge15;
        OdPrcEdge edge21, edge22, edge23, edge24, edge25;

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            pPrcPlane.setUVParameterization(new OdPrcUVParameterization(0, 30, 0, 30));

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(-15, -15, -0.3)));
            pPrcPlane.setTransformation(transform);
            // TBD
          }

          OdPrcCircle3d crvCircle = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, -0.3)));
            crvCircle.setTransformation(transform);
            // TBD
            crvCircle.setRadius(12);
          }

          edge11 = OdPrcEdge.createObject();
          edge11.contentWireEdge().setcurve(crvCircle);

          OdPrcUniqueVertex vertex_start = OdPrcUniqueVertex.createObject();
          vertex_start.setpoint(new OdGePoint3d(12, 0, -0.3));
          edge11.setStartVertex(vertex_start);
          edge11.setEndVertex(vertex_start);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge11);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop = OdPrcLoop.createObject();
          pCurFace.addLoop(loop);
          loop.addCoEdge(coEdge);
          loop.setOrientationWithSurface(1);


          //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole1 start

          OdPrcCircle3d crvCircle1 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle1.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle1.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(4, 0, -0.3)));
            crvCircle1.setTransformation(transform);
            // TBD
            crvCircle1.setRadius(0.6);
          }
          edge12 = OdPrcEdge.createObject();
          edge12.contentWireEdge().setcurve(crvCircle1);

          OdPrcUniqueVertex vertex_start1 = OdPrcUniqueVertex.createObject();
          vertex_start1.setpoint(new OdGePoint3d(4.6, 0, -0.3));
          edge12.setStartVertex(vertex_start1);
          edge12.setEndVertex(vertex_start1);

          OdPrcCoEdge coedge12 = OdPrcCoEdge.createObject();
          coedge12.setEdge(edge12);
          coedge12.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coedge12);
          loop1.setOrientationWithSurface(1);



          //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole2 start
          OdPrcCircle3d crvCircle2 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle2.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle2.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(-4, 0, -0.3)));
            crvCircle2.setTransformation(transform);
            // TBD
            crvCircle2.setRadius(0.6);
          }
          edge13 = OdPrcEdge.createObject();
          edge13.contentWireEdge().setcurve(crvCircle2);

          OdPrcUniqueVertex vertex_start2 = OdPrcUniqueVertex.createObject();
          vertex_start2.setpoint(new OdGePoint3d(-3.4, 0, -0.3));
          edge13.setStartVertex(vertex_start2);
          edge13.setEndVertex(vertex_start2);

          OdPrcCoEdge coedge13 = OdPrcCoEdge.createObject();
          coedge13.setEdge(edge13);
          coedge13.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop2 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop2);
          loop2.addCoEdge(coedge13);
          loop2.setOrientationWithSurface(1);



          //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole3 start
          OdPrcCircle3d crvCircle3 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle3.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle3.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 4, -0.3)));
            crvCircle3.setTransformation(transform);
            // TBD
            crvCircle3.setRadius(0.6);
          }
          edge14 = OdPrcEdge.createObject();
          edge14.contentWireEdge().setcurve(crvCircle3);

          OdPrcUniqueVertex vertex_start3 = OdPrcUniqueVertex.createObject();
          vertex_start3.setpoint(new OdGePoint3d(0.6, 4.0, -0.3));
          edge14.setStartVertex(vertex_start3);
          edge14.setEndVertex(vertex_start3);

          OdPrcCoEdge coedge14 = OdPrcCoEdge.createObject();
          coedge14.setEdge(edge14);
          coedge14.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop3 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop3);
          loop3.addCoEdge(coedge14);
          loop3.setOrientationWithSurface(1);



          //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole3 start
          OdPrcCircle3d crvCircle4 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle4.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle4.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, -4, -0.3)));
            crvCircle4.setTransformation(transform);
            // TBD
            crvCircle4.setRadius(0.6);
          }
          edge15 = OdPrcEdge.createObject();
          edge15.contentWireEdge().setcurve(crvCircle4);

          OdPrcUniqueVertex vertex_start4 = OdPrcUniqueVertex.createObject();
          vertex_start4.setpoint(new OdGePoint3d(0.6, -4.0, -0.3));
          edge15.setStartVertex(vertex_start4);
          edge15.setEndVertex(vertex_start4);

          OdPrcCoEdge coedge15 = OdPrcCoEdge.createObject();
          coedge15.setEdge(edge15);
          coedge15.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop4 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop4);
          loop4.addCoEdge(coedge15);
          loop4.setOrientationWithSurface(1);


          /////////////////////////////////////////////////////////////////////////////////////////////////
          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
          {
            OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named plane in srfContent");

            pPrcPlane.setUVParameterization(new OdPrcUVParameterization(0, 30, 0, 30));

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(-15, -15, -3.9)));
            pPrcPlane.setTransformation(transform);
            // TBD
          }

          OdPrcCircle3d crvCircle = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, -3.9)));
            crvCircle.setTransformation(transform);
            // TBD
            crvCircle.setRadius(12);
          }

          edge21 = OdPrcEdge.createObject();
          edge21.contentWireEdge().setcurve(crvCircle);

          OdPrcUniqueVertex vertex_start = OdPrcUniqueVertex.createObject();
          vertex_start.setpoint(new OdGePoint3d(12, 0, -3.9));
          edge21.setStartVertex(vertex_start);
          edge21.setEndVertex(vertex_start);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge21);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop = OdPrcLoop.createObject();
          pCurFace.addLoop(loop);
          loop.addCoEdge(coEdge);
          loop.setOrientationWithSurface(0);


          //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole1 start

          OdPrcCircle3d crvCircle1 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle1.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle1.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(4, 0, -3.9)));
            crvCircle1.setTransformation(transform);
            // TBD
            crvCircle1.setRadius(0.6);
          }
          edge22 = OdPrcEdge.createObject();
          edge22.contentWireEdge().setcurve(crvCircle1);

          OdPrcUniqueVertex vertex_start1 = OdPrcUniqueVertex.createObject();
          vertex_start1.setpoint(new OdGePoint3d(4.6, 0, -3.9));
          edge22.setStartVertex(vertex_start1);
          edge22.setEndVertex(vertex_start1);

          OdPrcCoEdge coedge22 = OdPrcCoEdge.createObject();
          coedge22.setEdge(edge22);
          coedge22.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coedge22);
          loop1.setOrientationWithSurface(0);



          //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole2 start
          OdPrcCircle3d crvCircle2 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle2.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle2.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(-4, 0, -3.9)));
            crvCircle2.setTransformation(transform);
            // TBD
            crvCircle2.setRadius(0.6);
          }
          edge23 = OdPrcEdge.createObject();
          edge23.contentWireEdge().setcurve(crvCircle2);

          OdPrcUniqueVertex vertex_start2 = OdPrcUniqueVertex.createObject();
          vertex_start2.setpoint(new OdGePoint3d(-3.4, 0, -3.9));
          edge23.setStartVertex(vertex_start2);
          edge23.setEndVertex(vertex_start2);

          OdPrcCoEdge coedge23 = OdPrcCoEdge.createObject();
          coedge23.setEdge(edge23);
          coedge23.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop2 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop2);
          loop2.addCoEdge(coedge23);
          loop2.setOrientationWithSurface(0);



          //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole3 start
          OdPrcCircle3d crvCircle3 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle3.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle3.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 4, -3.9)));
            crvCircle3.setTransformation(transform);
            // TBD
            crvCircle3.setRadius(0.6);
          }
          edge24 = OdPrcEdge.createObject();
          edge24.contentWireEdge().setcurve(crvCircle3);

          OdPrcUniqueVertex vertex_start3 = OdPrcUniqueVertex.createObject();
          vertex_start3.setpoint(new OdGePoint3d(0.6, 4.0, -3.9));
          edge24.setStartVertex(vertex_start3);
          edge24.setEndVertex(vertex_start3);

          OdPrcCoEdge coedge24 = OdPrcCoEdge.createObject();
          coedge24.setEdge(edge24);
          coedge24.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop3 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop3);
          loop3.addCoEdge(coedge24);
          loop3.setOrientationWithSurface(0);



          //////////////////////////////////////////////////////////////////////////////////////////////////////////// hole3 start
          OdPrcCircle3d crvCircle4 = OdPrcCircle3d.createObject();
          {
            OdPrcContentCurve crvContent = crvCircle4.contentCurve();

            // set name
            crvContent.baseGeometry().name().setName("named circle in crvContent");

            // add some data to params
            OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
            crvCircle4.setParameterization(curveParams);

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, -4, -3.9)));
            crvCircle4.setTransformation(transform);
            // TBD
            crvCircle4.setRadius(0.6);
          }
          edge25 = OdPrcEdge.createObject();
          edge25.contentWireEdge().setcurve(crvCircle4);

          OdPrcUniqueVertex vertex_start4 = OdPrcUniqueVertex.createObject();
          vertex_start4.setpoint(new OdGePoint3d(0.6, -4.0, -3.9));
          edge25.setStartVertex(vertex_start4);
          edge25.setEndVertex(vertex_start4);

          OdPrcCoEdge coedge25 = OdPrcCoEdge.createObject();
          coedge25.setEdge(edge25);
          coedge25.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop4 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop4);
          loop4.addCoEdge(coedge25);
          loop4.setOrientationWithSurface(0);


          /////////////////////////////////////////////////////////////////////////////////////////////////
          pCurFace.setbaseSurface(pPrcPlane);
          pCurFace.setorientationSurfaceWithShell(Orientation.kOpposite);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCylinder pPrcCylinder = OdPrcCylinder.createObject();
          {
            OdPrcContentSurface srfContent = pPrcCylinder.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named cylinder in srfContent");

            pPrcCylinder.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, -5.1, 5.1));
            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(4, 0, 0)));
            pPrcCylinder.setTransformation(transform);
            // TBD

            pPrcCylinder.setRadius(0.6);
          }

          OdPrcCoEdge coedge12 = OdPrcCoEdge.createObject();
          coedge12.setEdge(edge12);
          coedge12.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge22);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coedge12);
          loop1.setOrientationWithSurface(0);



          ///////////////////////////////////////////////////////////////////////
          OdPrcLoop loop2 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop2);
          loop2.addCoEdge(coEdge);
          loop2.setOrientationWithSurface(0);


          ///////////////////////////////////////////////////////////////////////

          pCurFace.setbaseSurface(pPrcCylinder);
          pCurFace.setorientationSurfaceWithShell(Orientation.kOpposite);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCylinder pPrcCylinder = OdPrcCylinder.createObject();
          {
            OdPrcContentSurface srfContent = pPrcCylinder.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named cylinder in srfContent");

            pPrcCylinder.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, -5.1, 5.1));
            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(-4, 0, 0)));
            pPrcCylinder.setTransformation(transform);
            // TBD

            pPrcCylinder.setRadius(0.6);
          }

          OdPrcCoEdge coedge12 = OdPrcCoEdge.createObject();
          coedge12.setEdge(edge13);
          coedge12.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge23);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coedge12);
          loop1.setOrientationWithSurface(0);



          ///////////////////////////////////////////////////////////////////////
          OdPrcLoop loop2 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop2);
          loop2.addCoEdge(coEdge);
          loop2.setOrientationWithSurface(0);


          ///////////////////////////////////////////////////////////////////////

          pCurFace.setbaseSurface(pPrcCylinder);
          pCurFace.setorientationSurfaceWithShell(Orientation.kOpposite);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCylinder pPrcCylinder = OdPrcCylinder.createObject();
          {
            OdPrcContentSurface srfContent = pPrcCylinder.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named cylinder in srfContent");

            pPrcCylinder.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, -5.1, 5.1));
            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 4, 0)));
            pPrcCylinder.setTransformation(transform);
            // TBD

            pPrcCylinder.setRadius(0.6);
          }

          OdPrcCoEdge coedge12 = OdPrcCoEdge.createObject();
          coedge12.setEdge(edge14);
          coedge12.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge24);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coedge12);
          loop1.setOrientationWithSurface(0);



          ///////////////////////////////////////////////////////////////////////
          OdPrcLoop loop2 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop2);
          loop2.addCoEdge(coEdge);
          loop2.setOrientationWithSurface(0);


          ///////////////////////////////////////////////////////////////////////

          pCurFace.setbaseSurface(pPrcCylinder);
          pCurFace.setorientationSurfaceWithShell(Orientation.kOpposite);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCylinder pPrcCylinder = OdPrcCylinder.createObject();
          {
            OdPrcContentSurface srfContent = pPrcCylinder.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named cylinder in srfContent");

            pPrcCylinder.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, -5.1, 5.1));
            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, -4, 0)));
            pPrcCylinder.setTransformation(transform);
            // TBD

            pPrcCylinder.setRadius(0.6);
          }

          OdPrcCoEdge coedge12 = OdPrcCoEdge.createObject();
          coedge12.setEdge(edge15);
          coedge12.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge25);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coedge12);
          loop1.setOrientationWithSurface(0);



          ///////////////////////////////////////////////////////////////////////
          OdPrcLoop loop2 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop2);
          loop2.addCoEdge(coEdge);
          loop2.setOrientationWithSurface(0);


          ///////////////////////////////////////////////////////////////////////

          pCurFace.setbaseSurface(pPrcCylinder);
          pCurFace.setorientationSurfaceWithShell(Orientation.kOpposite);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCylinder pPrcCylinder = OdPrcCylinder.createObject();
          {
            OdPrcContentSurface srfContent = pPrcCylinder.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named cylinder in srfContent");

            pPrcCylinder.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, -5.1, 5.1));
            // can add transformation if needed here
            // TBD

            pPrcCylinder.setRadius(12);
          }

          OdPrcCoEdge coedge12 = OdPrcCoEdge.createObject();
          coedge12.setEdge(edge11);
          coedge12.setOrientationWithLoop((sbyte)Orientation.kOpposite);

          OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
          coEdge.setEdge(edge21);
          coEdge.setOrientationWithLoop((sbyte)Orientation.kSame);

          OdPrcLoop loop1 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop1);
          loop1.addCoEdge(coedge12);
          loop1.setOrientationWithSurface(1);



          ///////////////////////////////////////////////////////////////////////////
          OdPrcLoop loop2 = OdPrcLoop.createObject();
          pCurFace.addLoop(loop2);
          loop2.addCoEdge(coEdge);
          loop2.setOrientationWithSurface(1);


          ///////////////////////////////////////////////////////////////////////////

          pCurFace.setbaseSurface(pPrcCylinder);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        pCurShell.setShellIsClosed(true);
      }
    }

    public static void FillTopoBrepFaceTire(OdPrcBrepData brepData)
    {
      OdPrcConnex pCurConnex = OdPrcConnex.createObject();
      brepData.addConnex(pCurConnex);

      {
        OdPrcShell pCurShell = OdPrcShell.createObject();
        pCurConnex.addShell(pCurShell);

        OdPrcEdge edge1, edge2;

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcTorus pPrcTorus = OdPrcTorus.createObject();
          {
            OdPrcContentSurface srfContent = pPrcTorus.contentSurface();

            // set name
            srfContent.baseGeometry().name().setName("named torus_T1 in srfContent");

            pPrcTorus.setUVParameterization(new OdPrcUVParameterization(-Globals.OdaPI, Globals.OdaPI, -Globals.OdaPI, Globals.OdaPI));

            // can add transformation if needed here
            OdPrcTransformation3d transform = new OdPrcTransformation3d();
            transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, -2.1)));
            pPrcTorus.setTransformation(transform);
            // TBD

            pPrcTorus.setMajorRadius(12);
            pPrcTorus.setMinorRadius(2.2);


            OdPrcCircle3d crvCircle1 = OdPrcCircle3d.createObject();
            {
              OdPrcContentCurve crvContent = crvCircle1.contentCurve();

              // set name
              crvContent.baseGeometry().name().setName("named circle in crvContent");

              // add some data to params
              OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
              crvCircle1.setParameterization(curveParams);

              // can add transformation if needed here
              OdPrcTransformation3d _transform = new OdPrcTransformation3d();
              OdGeMatrix3d matr = new OdGeMatrix3d();
              matr.setCoordSystem(new OdGePoint3d(0, 0, 0.1),new  OdGeVector3d(-1, 0, 0),new  OdGeVector3d(0, 1, 0), new OdGeVector3d(0, 0, -1));
              _transform.set(matr);
              crvCircle1.setTransformation(_transform);
              // TBD
              crvCircle1.setRadius(12.0);
            }

            edge1 = OdPrcEdge.createObject();
            edge1.contentWireEdge().setcurve(crvCircle1);

            OdPrcUniqueVertex vertex_start1 = OdPrcUniqueVertex.createObject();
            vertex_start1.setpoint(new OdGePoint3d(-12, 0, 0.1));
            edge1.setStartVertex(vertex_start1);
            edge1.setEndVertex(vertex_start1);

            OdPrcCoEdge coedge1 = OdPrcCoEdge.createObject();
            coedge1.setEdge(edge1);
            coedge1.setOrientationWithLoop((sbyte)Orientation.kSame);

            OdPrcLoop loop1 = OdPrcLoop.createObject();
            pCurFace.addLoop(loop1);
            loop1.addCoEdge(coedge1);
            loop1.setOrientationWithSurface(1);

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            OdPrcCircle3d crvCircle2 = OdPrcCircle3d.createObject();
            {
              OdPrcContentCurve crvContent = crvCircle2.contentCurve();

              // set name
              crvContent.baseGeometry().name().setName("named circle in crvContent");

              // add some data to params
              OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
              crvCircle2.setParameterization(curveParams);

              // can add transformation if needed here
              OdPrcTransformation3d _transform = new OdPrcTransformation3d();
              OdGeMatrix3d matr = new OdGeMatrix3d();
              matr.setCoordSystem(new OdGePoint3d(0, 0, -4.3), new OdGeVector3d(-1, 0, 0), new OdGeVector3d(0, -1, 0), new OdGeVector3d(0, 0, 1));
              _transform.set(matr);
              crvCircle2.setTransformation(_transform);
              // TBD
              crvCircle2.setRadius(12.0);
            }

            edge2 = OdPrcEdge.createObject();
            edge2.contentWireEdge().setcurve(crvCircle2);

            OdPrcUniqueVertex vertex_start2 = OdPrcUniqueVertex.createObject();
            vertex_start2.setpoint(new OdGePoint3d(-12, 0, -4.3));
            edge2.setStartVertex(vertex_start2);
            edge2.setEndVertex(vertex_start2);

            OdPrcCoEdge coedge2 = OdPrcCoEdge.createObject();
            coedge2.setEdge(edge2);
            coedge2.setOrientationWithLoop((sbyte)Orientation.kSame);

            OdPrcLoop loop2 = OdPrcLoop.createObject();
            pCurFace.addLoop(loop2);
            loop2.addCoEdge(coedge2);
            loop2.setOrientationWithSurface(1);

          }

          {
            OdPrcFace _pCurFace = OdPrcFace.createObject();

            OdPrcCylinder pPrcCylinder = OdPrcCylinder.createObject();
            {
              OdPrcContentSurface srfContent = pPrcCylinder.contentSurface();

              // set name
              srfContent.baseGeometry().name().setName("named cylinder in srfContent");

              pPrcCylinder.setUVParameterization(new OdPrcUVParameterization(-Globals.OdaPI, Globals.OdaPI, -2.344, 2.144));
              // can add transformation if needed here
              OdPrcTransformation3d transform = new OdPrcTransformation3d();
              transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, -2)));
              pPrcCylinder.setTransformation(transform);
              // TBD

              pPrcCylinder.setRadius(12.0);
            }

            OdPrcCoEdge coedge12 = OdPrcCoEdge.createObject();
            coedge12.setEdge(edge1);
            coedge12.setOrientationWithLoop((sbyte)Orientation.kOpposite);

            OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
            coEdge.setEdge(edge2);
            coEdge.setOrientationWithLoop((sbyte)Orientation.kOpposite);

            OdPrcLoop loop1 = OdPrcLoop.createObject();
            _pCurFace.addLoop(loop1);
            loop1.addCoEdge(coedge12);
            loop1.setOrientationWithSurface(0);


            ///////////////////////////////////////////////////////////////////////
            OdPrcLoop loop2 = OdPrcLoop.createObject();
            _pCurFace.addLoop(loop2);
            loop2.addCoEdge(coEdge);
            loop2.setOrientationWithSurface(0);

            ///////////////////////////////////////////////////////////////////////

            _pCurFace.setbaseSurface(pPrcCylinder);
            _pCurFace.setorientationSurfaceWithShell(Orientation.kOpposite);
            _pCurFace.setSurfaceTrimDomain(null);
            _pCurFace.setTolerance(0.0);

            pCurShell.addFace(_pCurFace);
          }

          pCurFace.setbaseSurface(pPrcTorus);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        pCurShell.setShellIsClosed(true);
      }
    }

    public static OdPrcFile CreatePRCCommonForBrepComplex()
    {
      // create prc
      OdPrcFile pFile = OdPrcFile.createObject();

      pFile.setVersions(8137, 8137);
      pFile.setfileStructureId(OdPrcUniqueId.generateUID());

      // init model file data section
      pFile.modelFileData().unit().setUnitFromCADFile(true);
      pFile.modelFileData().unit().setUnit(1); // 1 mm

      return pFile;
    }

    public static void CreateTopologyCommonForComplex(OdPrcFileStructure curStructure, OdPrcProductOccurrence curOccurrence, OdGeExtents3d extents, String brepModelName)
    {
      // part definition section
      OdPrcPartDefinition newDefinition = OdPrcCreateTopologyHelper.createPartDefinition(curStructure, curOccurrence);

      // bounding box
      newDefinition.boundingBox().setbox(extents);

      // create brep model
      OdPrcBrepModel newBrep = OdPrcBrepModel.createObject();
      curStructure.addObject(newBrep);
      newBrep.setIsClosed(true);
      newBrep.name().setName(brepModelName);
      newDefinition.representationItem().Add(newBrep.objectId());

      // create Brep Data
      OdPrcBrepData newBrepData = OdPrcBrepData.createObject();
      curStructure.addObject(newBrepData);
      newBrepData.boundingBox().setbox(extents);
      newBrepData.contentBody().setBoundingBoxBehaviour(2);

      // set reference to this body in representation item
      newBrep.setReferenceToBody(newBrepData);

      // file structure geometry section
      OdPrcTopoContext newTopoContext = OdPrcCreateTopologyHelper.createTopoContext(curStructure);
      newTopoContext.bodies().Add(newBrepData.objectId());
    }

    public static void AddAttribute(OdPrcAttributeData attrdata, String strTitle, String data)
    {
      OdPrcAttributeArray attrArr = attrdata.attributes();
      OdPrcAttribute newAttribute = new OdPrcAttribute();
      attrArr.Add(newAttribute);

      // create pair
      OdPrcContentSingleAttribute attributeDataPair = new OdPrcContentSingleAttribute();
      attributeDataPair.setData(data);

      // add pair to attribute
      newAttribute.AddDataPair(attributeDataPair);

      OdPrcAttributeEntry title = new OdPrcAttributeEntry();
      title.setData(strTitle);
      newAttribute.SetTitle(title);
    }

    public static OdPrcFile CreateComplexModels()
    {
      // common
      OdGeExtents3d extents = new OdGeExtents3d();
      extents.addPoint(new OdGePoint3d(-14.2, -14.2, -4.3));
      extents.addPoint(new OdGePoint3d(14.2, 14.2, 0.1));
      OdPrcFile pFile = CreatePRCCommonForBrepComplex();

      OdPrcFileStructure washerStructure = OdPrcCreateTopologyHelper.addNewFileStructure(pFile);
      OdPrcFileStructure nutStructure = OdPrcCreateTopologyHelper.addNewFileStructure(pFile);
      OdPrcFileStructure boltStructure = OdPrcCreateTopologyHelper.addNewFileStructure(pFile);
      OdPrcFileStructure rimStructure = OdPrcCreateTopologyHelper.addNewFileStructure(pFile);
      OdPrcFileStructure tireStructure = OdPrcCreateTopologyHelper.addNewFileStructure(pFile);

      washerStructure.setfileStructureId(new OdPrcUniqueId(1, 2, 3, 4));
      nutStructure.setfileStructureId(new OdPrcUniqueId(5, 6, 7, 8));
      boltStructure.setfileStructureId(new OdPrcUniqueId(9, 10, 11, 12));
      rimStructure.setfileStructureId(new OdPrcUniqueId(13, 14, 15, 16));
      tireStructure.setfileStructureId(new OdPrcUniqueId(17, 18, 19, 20));

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // create root product occurrence
      OdPrcProductOccurrence rootOccurrenceWasher = OdPrcProductOccurrence.createObject();
      washerStructure.addObject(rootOccurrenceWasher);
      washerStructure.fileStructureTree().internalData().setRootProductOccurrence(rootOccurrenceWasher.objectId());
      rootOccurrenceWasher.name().setName("Washer");

      AddAttribute(rootOccurrenceWasher.attributeData(), "Weight", "5 g");
      AddAttribute(rootOccurrenceWasher.attributeData(), "Material", "Steel");
      AddAttribute(rootOccurrenceWasher.attributeData(), "Size", "M16");
      AddAttribute(rootOccurrenceWasher.attributeData(), "Name", rootOccurrenceWasher.name().name());
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // create root product occurrence
      OdPrcProductOccurrence rootOccurrenceNut = OdPrcProductOccurrence.createObject();
      nutStructure.addObject(rootOccurrenceNut);
      nutStructure.fileStructureTree().internalData().setRootProductOccurrence(rootOccurrenceNut.objectId());
      rootOccurrenceNut.name().setName("Nut");

      AddAttribute(rootOccurrenceNut.attributeData(), "Weight", "18 g");
      AddAttribute(rootOccurrenceNut.attributeData(), "Material", "Steel");
      AddAttribute(rootOccurrenceNut.attributeData(), "Size", "M16x1.5");
      AddAttribute(rootOccurrenceNut.attributeData(), "Name", rootOccurrenceNut.name().name());
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // create root product occurrence
      OdPrcProductOccurrence rootOccurrenceBolt = OdPrcProductOccurrence.createObject();
      boltStructure.addObject(rootOccurrenceBolt);
      boltStructure.fileStructureTree().internalData().setRootProductOccurrence(rootOccurrenceBolt.objectId());
      rootOccurrenceBolt.name().setName("Bolt");

      AddAttribute(rootOccurrenceBolt.attributeData(), "Weight", "143 g");
      AddAttribute(rootOccurrenceBolt.attributeData(), "Material", "Steel");
      AddAttribute(rootOccurrenceBolt.attributeData(), "Size", "M16x1.5x60");
      AddAttribute(rootOccurrenceBolt.attributeData(), "Name", rootOccurrenceBolt.name().name());

      OdPrcObjectIdArray son_occurrencesForBolt = rootOccurrenceBolt.referencesOfProductOccurrence().getSonProductOccurrences();

      OdPrcProductOccurrence newProductOccurrenceForWasher = OdPrcProductOccurrence.createObject();
      boltStructure.addObject(newProductOccurrenceForWasher);
      newProductOccurrenceForWasher.referencesOfProductOccurrence().setPrototype(rootOccurrenceWasher.objectId());

      OdPrcProductOccurrence newProductOccurrenceForNut = OdPrcProductOccurrence.createObject();
      boltStructure.addObject(newProductOccurrenceForNut);
      newProductOccurrenceForNut.referencesOfProductOccurrence().setPrototype(rootOccurrenceNut.objectId());
      son_occurrencesForBolt.Add(newProductOccurrenceForWasher.objectId());
      son_occurrencesForBolt.Add(newProductOccurrenceForNut.objectId());
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // create root product occurrence
      OdPrcProductOccurrence rootOccurrenceRim = OdPrcProductOccurrence.createObject();
      rimStructure.addObject(rootOccurrenceRim);
      rimStructure.fileStructureTree().internalData().setRootProductOccurrence(rootOccurrenceRim.objectId());
      rootOccurrenceRim.name().setName("Rim");
      AddAttribute(rootOccurrenceRim.attributeData(), "Weight", "1375 g");
      AddAttribute(rootOccurrenceRim.attributeData(), "Material", "Steel");
      AddAttribute(rootOccurrenceRim.attributeData(), "Name", rootOccurrenceRim.name().name());
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // create root product occurrence
      OdPrcProductOccurrence rootOccurrenceTire = OdPrcProductOccurrence.createObject();
      tireStructure.addObject(rootOccurrenceTire);
      OdPrcObjectIdArray son_occurrences = rootOccurrenceTire.referencesOfProductOccurrence().getSonProductOccurrences();
      pFile.modelFileData().addStartRootOccurrence(rootOccurrenceTire);
      tireStructure.fileStructureTree().internalData().setRootProductOccurrence(rootOccurrenceTire.objectId());
      rootOccurrenceTire.name().setName("Tire");
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      OdPrcTransformation3d shift = new OdPrcTransformation3d();

      {
        CreateTopologyCommonForComplex(washerStructure, rootOccurrenceWasher, extents, "BrepModelWasher");

        // Add line style to globals
        OdBrepModelExample.addLineStyleForBrep(washerStructure, 1.0f, 0.0f, 0.0f);

        // Add graphic
        OdBrepModelExample.addGraphicDataToBrep(washerStructure);

        // fill it with Brep Data
        OdPrcTopoContextPtrArray topologicalContext = washerStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext();
        OdPrcTopoContext newTopoContext = topologicalContext[topologicalContext.Count - 1];

        OdPrcObjectIdArray bodies = newTopoContext.bodies();
        OdPrcBrepData brepData = bodies[bodies.Count - 1].safeOpenObjectOdRx(Teigha.PRC.OpenMode.kForWrite,false) as OdPrcBrepData;
        FillTopoBrepFaceWasher(brepData);

        // add transformation
        OdGeVector3d translateVect = new OdGeVector3d(0, 0, -4.0);
        OdGeMatrix3d geMatrix = new OdGeMatrix3d();
        geMatrix.setTranslation(translateVect);
        shift.set(geMatrix);
        rootOccurrenceWasher.setLocation(shift);

        washerStructure.fileStructureGeometry().fileStructureExactGeometry().updateCoedgeNeighbours();
      }

      {
        CreateTopologyCommonForComplex(nutStructure, rootOccurrenceNut, extents, "BrepModelNut");

        // Add line style to globals
        OdBrepModelExample.addLineStyleForBrep(nutStructure, 1.0f, 0.0f, 0.0f);

        // Add graphic
        OdBrepModelExample.addGraphicDataToBrep(nutStructure);

        // fill it with Brep Data
        OdPrcTopoContextPtrArray topologicalContext = nutStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext();
        OdPrcTopoContext newTopoContext = topologicalContext[topologicalContext.Count - 1];
        OdPrcObjectIdArray bodies = newTopoContext.bodies();
        OdPrcBrepData brepData = bodies[bodies.Count - 1].safeOpenObjectOdRx(Teigha.PRC.OpenMode.kForWrite, false) as OdPrcBrepData;
        FillTopoBrepFaceNut(brepData);

        // add transformation
        OdGeVector3d translateVect = new OdGeVector3d(0, 0, -4.4);
        OdGeMatrix3d geMatrix = new OdGeMatrix3d();
        geMatrix.setTranslation(translateVect);
        shift.set(geMatrix);
        rootOccurrenceNut.setLocation(shift);

        nutStructure.fileStructureGeometry().fileStructureExactGeometry().updateCoedgeNeighbours();
      }

      {
        CreateTopologyCommonForComplex(boltStructure, rootOccurrenceBolt, extents, "BrepModelBolt");

        // Add line style to globals
        OdBrepModelExample.addLineStyleForBrep(boltStructure, 1.0f, 0.0f, 0.0f);

        // Add graphic
        OdBrepModelExample.addGraphicDataToBrep(boltStructure);

        // fill it with Brep Data
        OdPrcTopoContextPtrArray topologicalContext = boltStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext();
        OdPrcTopoContext newTopoContext = topologicalContext[topologicalContext.Count - 1];
        OdPrcObjectIdArray bodies = newTopoContext.bodies();
        OdPrcBrepData brepData = bodies[bodies.Count -1].safeOpenObjectOdRx(Teigha.PRC.OpenMode.kForWrite,false) as OdPrcBrepData;
        FillTopoBrepFaceBolt(brepData);

        boltStructure.fileStructureGeometry().fileStructureExactGeometry().updateCoedgeNeighbours();
      }

      {
        CreateTopologyCommonForComplex(rimStructure, rootOccurrenceRim, extents, "BrepModelRim");

        // Add line style to globals
        OdBrepModelExample.addLineStyleForBrep(rimStructure, 1.0f, 0.0f, 0.0f);

        // Add graphic
        OdBrepModelExample.addGraphicDataToBrep(rimStructure);

        // fill it with Brep Data
        OdPrcTopoContextPtrArray topologicalContext = rimStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext();
        OdPrcTopoContext newTopoContext = topologicalContext[topologicalContext.Count - 1];
        OdPrcObjectIdArray bodies = newTopoContext.bodies();
        OdPrcBrepData brepData = bodies[bodies.Count - 1].safeOpenObjectOdRx(Teigha.PRC.OpenMode.kForWrite, false) as OdPrcBrepData;
        FillTopoBrepFaceRim(brepData);

        rimStructure.fileStructureGeometry().fileStructureExactGeometry().updateCoedgeNeighbours();
      }

      {
        CreateTopologyCommonForComplex(tireStructure, rootOccurrenceTire, extents, "BrepModelTire");

        // Add line style to globals
        OdBrepModelExample.addLineStyleForBrep(tireStructure, 1.0f, 0.0f, 0.0f);

        // Add graphic
        OdBrepModelExample.addGraphicDataToBrep(tireStructure);

        // fill it with Brep Data
        OdPrcTopoContextPtrArray topologicalContext = tireStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext();
        OdPrcTopoContext newTopoContext = topologicalContext[topologicalContext.Count - 1];
        OdPrcObjectIdArray bodies = newTopoContext.bodies();
        OdPrcBrepData brepData = bodies[bodies.Count - 1].safeOpenObjectOdRx(Teigha.PRC.OpenMode.kForWrite, false) as OdPrcBrepData;
        FillTopoBrepFaceTire(brepData);

        tireStructure.fileStructureGeometry().fileStructureExactGeometry().updateCoedgeNeighbours();
      }

      OdPrcProductOccurrence newProductOccurrenceForRim = OdPrcProductOccurrence.createObject();
      tireStructure.addObject(newProductOccurrenceForRim);
      newProductOccurrenceForRim.referencesOfProductOccurrence().setPrototype(rootOccurrenceRim.objectId());

      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      OdPrcProductOccurrence newProductOccurrenceForBolt1 = OdPrcProductOccurrence.createObject();
      newProductOccurrenceForBolt1.name().setName("Bolt_1");
      {
        tireStructure.addObject(newProductOccurrenceForBolt1);

        // add transformation
        OdGeVector3d translateVect = new OdGeVector3d(4, 0, 0);
        OdGeMatrix3d geMatrix = new OdGeMatrix3d();
        geMatrix.setTranslation(translateVect);
        shift.set(geMatrix);
        newProductOccurrenceForBolt1.setLocation(shift);

        newProductOccurrenceForBolt1.referencesOfProductOccurrence().setPrototype(rootOccurrenceBolt.objectId());
        AddAttribute(newProductOccurrenceForBolt1.attributeData(), "Name", newProductOccurrenceForBolt1.name().name());
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      OdPrcProductOccurrence newProductOccurrenceForBolt2 = OdPrcProductOccurrence.createObject();
      newProductOccurrenceForBolt2.name().setName("Bolt_2");
      {
        tireStructure.addObject(newProductOccurrenceForBolt2);

        // add transformation
        OdGeVector3d translateVect = new OdGeVector3d(-4, 0, 0);
        OdGeMatrix3d geMatrix = new OdGeMatrix3d();
        geMatrix.setTranslation(translateVect);
        shift.set(geMatrix);
        newProductOccurrenceForBolt2.setLocation(shift);

        newProductOccurrenceForBolt2.referencesOfProductOccurrence().setPrototype(rootOccurrenceBolt.objectId());
        AddAttribute(newProductOccurrenceForBolt2.attributeData(), "Name", newProductOccurrenceForBolt2.name().name());
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      OdPrcProductOccurrence newProductOccurrenceForBolt3 = OdPrcProductOccurrence.createObject();
      newProductOccurrenceForBolt3.name().setName("Bolt_3");
      {
        tireStructure.addObject(newProductOccurrenceForBolt3);

        // add transformation
        OdGeVector3d translateVect = new OdGeVector3d(0, 4, 0);
        OdGeMatrix3d geMatrix = new OdGeMatrix3d();
        geMatrix.setTranslation(translateVect);
        shift.set(geMatrix);
        newProductOccurrenceForBolt3.setLocation(shift);

        newProductOccurrenceForBolt3.referencesOfProductOccurrence().setPrototype(rootOccurrenceBolt.objectId());
        AddAttribute(newProductOccurrenceForBolt3.attributeData(), "Name", newProductOccurrenceForBolt3.name().name());
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      OdPrcProductOccurrence newProductOccurrenceForBolt4 = OdPrcProductOccurrence.createObject();
      newProductOccurrenceForBolt4.name().setName("Bolt_4");
      {
        tireStructure.addObject(newProductOccurrenceForBolt4);

        // add transformation
        OdGeVector3d translateVect = new OdGeVector3d(0, -4, 0);
        OdGeMatrix3d geMatrix = new OdGeMatrix3d();
        geMatrix.setTranslation(translateVect);
        shift.set(geMatrix);
        newProductOccurrenceForBolt4.setLocation(shift);

        newProductOccurrenceForBolt4.referencesOfProductOccurrence().setPrototype(rootOccurrenceBolt.objectId());
        AddAttribute(newProductOccurrenceForBolt4.attributeData(), "Name", newProductOccurrenceForBolt4.name().name());
      }
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // add reference to root product occurrence
      son_occurrences.Add(newProductOccurrenceForBolt1.objectId());
      son_occurrences.Add(newProductOccurrenceForBolt2.objectId());
      son_occurrences.Add(newProductOccurrenceForBolt3.objectId());
      son_occurrences.Add(newProductOccurrenceForBolt4.objectId());
      son_occurrences.Add(newProductOccurrenceForRim.objectId());

      return pFile;
    }
  }
}
