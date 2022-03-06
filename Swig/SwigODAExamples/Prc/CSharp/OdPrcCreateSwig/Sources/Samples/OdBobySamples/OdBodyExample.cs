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
using Teigha.Core;
using Teigha.PRC;
using Teigha.TD;

namespace OdPrcCreateSwigMgd.Samples.OdBobySamples
{
  public abstract class OdBodyExample : OdPrcCreateExample
  {
    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // creates prc single wire body
      OdPrcFile pFile = OdPrcCreateTopologyHelper.createTopologyCommon();
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure pFS = fileStructures[fileStructures.Count - 1];
      OdPrcProductOccurrence pRootPO = pFS.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
      OdPrcPartDefinition pPD = OdPrcCreateTopologyHelper.createPartDefinition(pFS, pRootPO);
      OdPrcTopoContext pTopoContext = OdPrcCreateTopologyHelper.createTopoContext(pFS);

      OdGePoint3d p1 = new OdGePoint3d(0.0, 0.0, 0.0);
      OdGePoint3d p2 = new OdGePoint3d(1.0, 1.0, 1.0);
      GC.SuppressFinalize(p1);
      GC.SuppressFinalize(p2);
      OdGeExtents3d extents = new OdGeExtents3d(p1, p2);
      pPD.boundingBox().box().set(extents.minPoint(), extents.maxPoint());
      OdPrcWireCurve pCurve = OdPrcCreateTopologyHelper.createRI<OdPrcWireCurve>(pFS, pPD);
      OdPrcSingleWireBody wireBody = OdPrcCreateTopologyHelper.createBody<OdPrcSingleWireBody>(pFS, pTopoContext, pCurve);

      // fill it with curve
      switch (mode)
      {
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvLine:
          FillTopoSingleWireBodyForLine(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvNURBS:
          FillTopoSingleWireBodyForNURBS(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvCircle:
          FillTopoSingleWireBodyForCircle(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvPolyLine:
          FillTopoSingleWireBodyForPolyLine(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvHyperbola:
          FillTopoSingleWireBodyForHyperbola(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvParabola:
          FillTopoSingleWireBodyForParabola(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvEllipse:
          FillTopoSingleWireBodyForEllipse(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvOnSurf:
          FillTopoSingleWireBodyForOnSurf(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvHelixT0:
          FillTopoSingleWireBodyForHelixT0(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvIntersection:
          FillTopoSingleWireBodyForIntersection(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvComposite:
          FillTopoSingleWireBodyForComposite(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvBlend02Boundary:
          FillTopoSingleWireBodyForBlend02Boundary(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvHelixT1:
          FillTopoSingleWireBodyForHelixT1(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvTransform:
          FillTopoSingleWireBodyForTransform(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvOffset:
          FillTopoSingleWireBodyForOffset(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvEquation:
          FillTopoSingleWireBodyForEquation(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvPolyLine2d:
          FillTopoSingleWireBodyForPolyLine2d(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvEquation2d:
          FillTopoSingleWireBodyForEquation2d(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvNURBS2d:
          FillTopoSingleWireBodyForNURBS2d(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvComposite2d:
          FillTopoSingleWireBodyForComposite2d(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvTransform2d:
          FillTopoSingleWireBodyForTransform2d(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvLine2d:
          FillTopoSingleWireBodyForLine2d(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvCircle2d:
          FillTopoSingleWireBodyForCircle2d(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvHyperbola2d:
          FillTopoSingleWireBodyForHyperbola2d(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvParabola2d:
          FillTopoSingleWireBodyForParabola2d(wireBody);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.SingleWireBodyCrvEllipse2d:
          FillTopoSingleWireBodyForEllipse2d(wireBody);
          break;
        default:
          throw new Exception();
      }

      // export prc
      pFile.writeFile(pPrcStream);
    }

    public static void FillTopoSingleWireBodyForPolyLine(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcPolyLine3d crvPolyLine = OdPrcPolyLine3d.createObject();
      {
        OdPrcContentCurve crvContent = crvPolyLine.contentCurve();

        // - array of control points defining curve
        OdGePoint3dArray crvPoint = new OdGePoint3dArray();
        crvPoint.Add(new OdGePoint3d(0.0, 0.0, 0.0));
        crvPoint.Add(new OdGePoint3d(1.0, 0.0, 0.0));
        crvPoint.Add(new OdGePoint3d(1.0, 0.0, 1.0));
        crvPoint.Add(new OdGePoint3d(0.0, 0.0, 1.0));
        crvPoint.Add(new OdGePoint3d(0.0, 1.0, 1.0));
        crvPoint.Add(new OdGePoint3d(0.0, 1.0, 0.0));
        crvPoint.Add(new OdGePoint3d(1.0, 1.0, 0.0));
        crvPoint.Add(new OdGePoint3d(1.0, 1.0, 1.0));
        crvPolyLine.setPoints(crvPoint, true);
      }

      wContent.setcurve(crvPolyLine);
    }

    public static void FillTopoSingleWireBodyForCircle(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named circle in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcCircle3d crvCircle = OdPrcCircle3d.createObject();
      {
        OdPrcContentCurve crvContent = crvCircle.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
        crvCircle.setParameterization(curveParams);

        // can add transformation if needed here
        // TBD
        crvCircle.setRadius(1.0);
      }

      wContent.setcurve(crvCircle);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named circle in wContent");
    }

    public static void FillTopoSingleWireBodyForNURBS(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcNurbsCurve3d crvNurbs = OdPrcNurbsCurve3d.createObject();
      {
        OdPrcContentCurve crvContent = crvNurbs.contentCurve();

        // fill nurbs parameters
        // - non-array parameters
        int crvdegree = 2;

        // - array of control points defining curve
        OdGePoint3dArray arrPRCPoints = new OdGePoint3dArray();
        arrPRCPoints.Add(new OdGePoint3d(0.0, -1.0, -1.0));
        arrPRCPoints.Add(new OdGePoint3d(0.3, -0.5, 0.7));
        arrPRCPoints.Add(new OdGePoint3d(1.0, 1.0, 1.0));
        arrPRCPoints.Add(new OdGePoint3d(1.5, -1.0, -1.0));

        // - array of knots
        OdGeDoubleArray arrDoublesForKnots = new OdGeDoubleArray();
        arrDoublesForKnots.Add(1.0);
        arrDoublesForKnots.Add(2.0);
        arrDoublesForKnots.Add(3.0);
        arrDoublesForKnots.Add(4.0);
        arrDoublesForKnots.Add(5.0);
        arrDoublesForKnots.Add(6.0);
        arrDoublesForKnots.Add(7.0);
        OdGeKnotVector arrPRCKnots = new OdGeKnotVector(arrDoublesForKnots);

        // - array of weights
        OdGeDoubleArray arrPRCWeights = new OdGeDoubleArray(); // zero or for each control point

        // create OdGe nurb curve
        OdGeNurbCurve3d geCurve = new OdGeNurbCurve3d();
        geCurve.set(crvdegree, arrPRCKnots, arrPRCPoints, arrPRCWeights);
        crvNurbs.setFromOdGeCurve(geCurve);
      }

      wContent.setcurve(crvNurbs);
    }

    public static void FillTopoSingleWireBodyForLine(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named line in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcLine3d crvLine = OdPrcLine3d.createObject();
      {
        OdPrcContentCurve crvContent = crvLine.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named line in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(0, 2.0);
        crvLine.setParameterization(curveParams);
        OdGeMatrix3d mx = new OdGeMatrix3d();
        mx.setCoordSystem(new OdGePoint3d(0, 0, 0), new OdGeVector3d(0.5, 0, 0), new OdGeVector3d(0, 0.5, 0), new OdGeVector3d(0, 0, 0.5));
        OdPrcTransformation3d transf = new OdPrcTransformation3d();
        transf.set(mx);
        crvLine.setTransformation(transf);
        // can add transformation if needed here
        // TBD
      }

      wContent.setcurve(crvLine);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named line in wContent");
    }

    public static void FillTopoSingleWireBodyForHyperbola(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named hyperbola in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcHyperbola3d crvHyperbola = OdPrcHyperbola3d.createObject();
      {
        OdPrcContentCurve crvContent = crvHyperbola.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named hyperbola in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(-2, 2);
        crvHyperbola.setParameterization(curveParams);

        // can add transformation if needed here
        OdPrcTransformation3d transform = new OdPrcTransformation3d();
        OdGeMatrix3d matr = new OdGeMatrix3d();
        OdGePoint3d origin = new OdGePoint3d();
        OdGeVector3d xAxis = new OdGeVector3d(0, 0, 1);
        OdGeVector3d yAxis = new OdGeVector3d(0, 1, 0);
        OdGeVector3d zAxis = xAxis.crossProduct(yAxis);
        matr.setCoordSystem(origin, xAxis, yAxis, zAxis);
        transform.set(matr);
        crvHyperbola.setTransformation(transform);

        // TBD
        crvHyperbola.setSemiAxis(2.0);
        crvHyperbola.setSemiImageAxis(3.0);
        crvHyperbola.setParameterizationType(1);
      }

      wContent.setcurve(crvHyperbola);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named hyperbola in wContent");
    }

    public static void FillTopoSingleWireBodyForParabola(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named parabola in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcParabola3d crvParabola = OdPrcParabola3d.createObject();
      {
        OdPrcContentCurve crvContent = crvParabola.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named parabola in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(-7, 7);
        crvParabola.setParameterization(curveParams);

        // can add transformation if needed here

        // TBD
        crvParabola.setFocalLength(0.4);
        crvParabola.setParameterizationType(0);
      }

      wContent.setcurve(crvParabola);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named parabola in wContent");
    }

    public static void FillTopoSingleWireBodyForEllipse(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named ellipse in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcEllipse3d crvEllipse = OdPrcEllipse3d.createObject();
      {
        OdPrcContentCurve crvContent = crvEllipse.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named ellipse in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
        crvEllipse.setParameterization(curveParams);

        // can add transformation if needed here

        // TBD
        crvEllipse.setRadiusAtXAxis(7);
        crvEllipse.setRadiusAtYAxis(3);
      }

      wContent.setcurve(crvEllipse);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named ellipse in wContent");
    }

    public static void FillTopoSingleWireBodyForOnSurf(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named OnSurf in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrc2dCurveOnSurfaceCurve3d crvOnSurf = OdPrc2dCurveOnSurfaceCurve3d.createObject();
      {
        OdPrcContentCurve crvContent = crvOnSurf.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named OnSurf in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(1.3, 3.5);
        crvOnSurf.setParameterization(curveParams);

        // can add transformation if needed here
        // TBD 
        OdPrcEllipse2d uv_curv = OdPrcEllipse2d.createObject();
        OdPrcContentCurve crvContent1 = uv_curv.contentCurve();
        uv_curv.setRadiusAtXAxis(7);
        uv_curv.setRadiusAtYAxis(2);
        uv_curv.setParameterization(new OdPrcParameterization(0, Globals.Oda2PI));

        OdPrcPlane base_sur = OdPrcPlane.createObject();

        base_sur.setUVParameterization(new OdPrcUVParameterization(OdPrcDomain.kInfinite, false, -1, -1, 0, 0));

        crvOnSurf.setCurveUV(uv_curv);
        crvOnSurf.setBaseSurface(base_sur);
      }

      wContent.setcurve(crvOnSurf);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named OnSurf in wContent");
    }

    public static void FillTopoSingleWireBodyForHelixT0(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named helix in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcHelixType0Curve crvHelix = OdPrcHelixType0Curve.createObject();
      {
        OdPrcContentCurve crvContent = crvHelix.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named helix in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(-30, 30);
        crvHelix.setParameterization(curveParams);

        // can add transformation if needed here

        // TBD
        crvHelix.setTrigonometricOrientation(true);
        crvHelix.setstart(new OdGePoint3d(0, 0, 0));
        crvHelix.setorigin(new OdGePoint3d(1, 4, 6));
        crvHelix.setdirection(OdGeVector3d.kZAxis);
        crvHelix.setPitch(0.3);
        crvHelix.setRadiusEvolution(0.2);
      }

      wContent.setcurve(crvHelix);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named helix in wContent");
    }

    public static void FillTopoSingleWireBodyForHelixT1(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named helix in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcHelixType1Curve crvHelix = OdPrcHelixType1Curve.createObject();
      {
        OdPrcContentCurve crvContent = crvHelix.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named helix in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(-35, 35);
        crvHelix.setParameterization(curveParams);

        // can add transformation if needed here

        // TBD
        crvHelix.setTrigonometricOrientation(true);
        crvHelix.setstart(new OdGePoint3d(0, 0, 0));
        crvHelix.setUnitU(OdGeVector3d.kXAxis);
        crvHelix.setUnitZ(OdGeVector3d.kZAxis);

        OdPrcMath1dPolynom radiusLaw = OdPrcMath1dPolynom.createObject();
        radiusLaw.coefficient().resize(2);
        radiusLaw.coefficient()[0] = 1;
        radiusLaw.coefficient()[1] = 2;

        OdPrcMath1dPolynom thetaLaw = OdPrcMath1dPolynom.createObject();
        thetaLaw.coefficient().resize(2);
        thetaLaw.coefficient()[0] = 1;
        thetaLaw.coefficient()[1] = 2;

        OdPrcMath1dPolynom zLaw = OdPrcMath1dPolynom.createObject();
        zLaw.coefficient().resize(2);
        zLaw.coefficient()[0] = 1;
        zLaw.coefficient()[1] = 2;

        crvHelix.setRadiusLaw(radiusLaw);
        crvHelix.setZLaw(zLaw);
        crvHelix.setThetaLaw(thetaLaw);
      }

      wContent.setcurve(crvHelix);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named helix in wContent");
    }

    public static void FillTopoSingleWireBodyForIntersection(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named intersection in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcIntersectionCurve3d crvIntersection = OdPrcIntersectionCurve3d.createObject();
      {
        OdPrcContentCurve crvContent = crvIntersection.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named intersection in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(-0.001607154928977807, 0.01195146616849428);
        crvIntersection.setParameterization(curveParams);

        // can add transformation if needed here

        // TBD
        OdPrcCylinder surCyl = OdPrcCylinder.createObject();
        OdPrcTorus surTor = OdPrcTorus.createObject();

        OdPrcTransformation3d transform = new OdPrcTransformation3d();
        OdGeMatrix3d matr = new OdGeMatrix3d();
        OdGePoint3d origin = new OdGePoint3d(0.1346409306333122, 0.05665149759597796, -0.15478);
        OdGeVector3d xAxis = new OdGeVector3d(-1, 0, 0);
        OdGeVector3d yAxis = new OdGeVector3d(0, -1, 0);
        OdGeVector3d zAxis = xAxis.crossProduct(yAxis);
        matr.setCoordSystem(origin, xAxis, yAxis, zAxis);
        transform.set(matr);
        surCyl.setTransformation(transform);

        surCyl.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, OdPrcDomain.kLowerInfinite, OdPrcDomain.kUpperInfinite));
        surCyl.setRadius(0.01039618035521435);

        OdPrcTransformation3d transform1 = new OdPrcTransformation3d();
        OdGeMatrix3d matr1 = new OdGeMatrix3d();
        OdGePoint3d origin1 = new OdGePoint3d(0.1016940451762275, 0.03587310626005076, -0.13081);
        OdGeVector3d xAxis1 = new OdGeVector3d(1, 0, 0);
        OdGeVector3d yAxis1 = new OdGeVector3d(0, -1, 0);
        OdGeVector3d zAxis1 = xAxis1.crossProduct(yAxis1);
        matr1.setCoordSystem(origin1, xAxis1, yAxis1, zAxis1);
        transform1.set(matr1);
        surTor.setTransformation(transform1);

        surTor.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, Globals.Oda2PI));
        surTor.setMajorRadius(0.02921000000000001);
        surTor.setMinorRadius(0.005079999999999999);

        crvIntersection.setSurface1(surCyl);
        crvIntersection.setSurface2(surTor);
        crvIntersection.setSurface1Sense(false);
        crvIntersection.setSurface2Sense(true);
        crvIntersection.setIntersectionSense(false);
        crvIntersection.crossingPointsCrvIntersection().resize(8);
        Byte nCrossingPointFlags = PRC_Globals.PRC_INTERSECTION_CROSS_POINT_SURFACE1 | PRC_Globals.PRC_INTERSECTION_CROSS_POINT_SURFACE2 | PRC_Globals.PRC_INTERSECTION_CROSS_POINT_INSIDE_CURVE_INTERVAL;

        crvIntersection.crossingPointsCrvIntersection()[0].crossingPointPosition().set(0.1341041808452103, 0.04626918255341075, -0.1292258279240333);
        crvIntersection.crossingPointsCrvIntersection()[0].crossingPointUv1().set(1.51914384319694, 0.02555417207596672);
        crvIntersection.crossingPointsCrvIntersection()[0].crossingPointUv2().set(5.972787481740113, 5.966051167063788);
        crvIntersection.crossingPointsCrvIntersection()[0].crossingPointTangent().set(0.3307189013079945, -0.01709766073082427, -0.9435744158862971);
        crvIntersection.crossingPointsCrvIntersection()[0].setCrossingPointParameter(-0.001607154928977807);
        crvIntersection.crossingPointsCrvIntersection()[0].setCrossingPointScale(1.000143483648419);
        crvIntersection.crossingPointsCrvIntersection()[0].setCrossingPointFlags(nCrossingPointFlags);

        crvIntersection.crossingPointsCrvIntersection()[1].crossingPointPosition().set(0.1343734318291666, 0.04625875924807728, -0.13081);
        crvIntersection.crossingPointsCrvIntersection()[1].crossingPointUv1().set(1.545062997781224, 0.02397000000000002);
        crvIntersection.crossingPointsCrvIntersection()[1].crossingPointUv2().set(5.975475281373264, 6.283185307179586);
        crvIntersection.crossingPointsCrvIntersection()[1].crossingPointTangent().set(2.591203737317232e-016, -6.669502087194884e-018, -0.9999999999999999);
        crvIntersection.crossingPointsCrvIntersection()[1].setCrossingPointParameter(-2.38524477946811e-017);
        crvIntersection.crossingPointsCrvIntersection()[1].setCrossingPointScale(0.9999999999999996);
        crvIntersection.crossingPointsCrvIntersection()[1].setCrossingPointFlags(nCrossingPointFlags);

        crvIntersection.crossingPointsCrvIntersection()[2].crossingPointPosition().set(0.1341068460463681, 0.04626904510958856, -0.1323865473133593);
        crvIntersection.crossingPointsCrvIntersection()[2].crossingPointUv1().set(1.519400547360803, 0.0223934526866407);
        crvIntersection.crossingPointsCrvIntersection()[2].crossingPointUv2().set(5.972815241757231, 0.315554835736894);
        crvIntersection.crossingPointsCrvIntersection()[2].crossingPointTangent().set(-0.3291216270733597, 0.01693037251846485, -0.9441357514038806);
        crvIntersection.crossingPointsCrvIntersection()[2].setCrossingPointParameter(0.001598960665494222);
        crvIntersection.crossingPointsCrvIntersection()[2].setCrossingPointScale(1.000343251512571);
        crvIntersection.crossingPointsCrvIntersection()[2].setCrossingPointFlags(nCrossingPointFlags);

        crvIntersection.crossingPointsCrvIntersection()[3].crossingPointPosition().set(0.1333353720053878, 0.04633761943850505, -0.1337862163025362);
        crvIntersection.crossingPointsCrvIntersection()[3].crossingPointUv1().set(1.444883278290392, 0.0209937836974638);
        crvIntersection.crossingPointsCrvIntersection()[3].crossingPointUv2().set(5.963785928215732, 0.6259523779802467);
        crvIntersection.crossingPointsCrvIntersection()[3].crossingPointTangent().set(-0.6202478501943297, 0.07851265255504558, -0.7804667627247703);
        crvIntersection.crossingPointsCrvIntersection()[3].setCrossingPointParameter(0.003199180944311991);
        crvIntersection.crossingPointsCrvIntersection()[3].setCrossingPointScale(0.9999042656648339);
        crvIntersection.crossingPointsCrvIntersection()[3].setCrossingPointFlags(nCrossingPointFlags);

        crvIntersection.crossingPointsCrvIntersection()[4].crossingPointPosition().set(0.1321782193823936, 0.04655121941798981, -0.1348419568152813);
        crvIntersection.crossingPointsCrvIntersection()[4].crossingPointUv1().set(1.331636798215172, 0.01993804318471873);
        crvIntersection.crossingPointsCrvIntersection()[4].crossingPointUv2().set(5.946257658954129, 0.9168548394635828);
        crvIntersection.crossingPointsCrvIntersection()[4].crossingPointTangent().set(-0.8172802565597779, 0.1992742425025279, -0.5406873019709518);
        crvIntersection.crossingPointsCrvIntersection()[4].setCrossingPointParameter(0.004779920225752386);
        crvIntersection.crossingPointsCrvIntersection()[4].setCrossingPointScale(0.9981746869563191);
        crvIntersection.crossingPointsCrvIntersection()[4].setCrossingPointFlags(nCrossingPointFlags);

        crvIntersection.crossingPointsCrvIntersection()[5].crossingPointPosition().set(0.130801052426036, 0.046990446859571, -0.1355017145668607);
        crvIntersection.crossingPointsCrvIntersection()[5].crossingPointUv1().set(1.192481790672, 0.01927828543313928);
        crvIntersection.crossingPointsCrvIntersection()[5].crossingPointUv2().set(5.918337874942981, 1.177278387632714);
        crvIntersection.crossingPointsCrvIntersection()[5].crossingPointTangent().set(-0.8886892161393534, 0.3532181381922888, -0.2923498314854912);
        crvIntersection.crossingPointsCrvIntersection()[5].setCrossingPointParameter(0.006365978613759873);
        crvIntersection.crossingPointsCrvIntersection()[5].setCrossingPointScale(1.002244619626312);
        crvIntersection.crossingPointsCrvIntersection()[5].setCrossingPointFlags(nCrossingPointFlags);

        crvIntersection.crossingPointsCrvIntersection()[6].crossingPointPosition().set(0.1288246894375459, 0.04803454312639792, -0.1358631432630582);
        crvIntersection.crossingPointsCrvIntersection()[6].crossingPointUv1().set(0.9770628501933092, 0.0189168567369418);
        crvIntersection.crossingPointsCrvIntersection()[6].crossingPointUv2().set(5.861783780995035, 1.467923355389826);
        crvIntersection.crossingPointsCrvIntersection()[6].crossingPointTangent().set(-0.827631385705026, 0.5586316810005541, -0.05437770111427551);
        crvIntersection.crossingPointsCrvIntersection()[6].setCrossingPointParameter(0.008635299997827233);
        crvIntersection.crossingPointsCrvIntersection()[6].setCrossingPointScale(1.005231774808438);
        crvIntersection.crossingPointsCrvIntersection()[6].setCrossingPointFlags(nCrossingPointFlags);

        crvIntersection.crossingPointsCrvIntersection()[7].crossingPointPosition().set(0.1264178276616657, 0.05029059015317995, -0.1358556726350897);
        crvIntersection.crossingPointsCrvIntersection()[7].crossingPointUv1().set(0.6583979164557663, 0.01892432736491032);
        crvIntersection.crossingPointsCrvIntersection()[7].crossingPointUv2().set(5.755253387857033, 1.687114677445861);
        crvIntersection.crossingPointsCrvIntersection()[7].crossingPointTangent().set(-0.6117797523107345, 0.7908821098969897, 0.01519943773639112);
        crvIntersection.crossingPointsCrvIntersection()[7].setCrossingPointParameter(0.01195146616849428);
        crvIntersection.crossingPointsCrvIntersection()[7].setCrossingPointScale(0.9924163238026051);
        crvIntersection.crossingPointsCrvIntersection()[7].setCrossingPointFlags(nCrossingPointFlags);

        crvIntersection.setstartLimitPoint(new OdGePoint3d(0.1341041808452103, 0.04626918255341075, -0.1292258279240333));
        crvIntersection.setStartLimitType((uint)EPRCIntersectionLimitType.KEPRCIntersectionLimitTypeLimit);
        crvIntersection.setendLimitPoint(new OdGePoint3d(0.1264178276616657, 0.05029059015317995, -0.1358556726350897));
        crvIntersection.setEndLimitType((uint)EPRCIntersectionLimitType.KEPRCIntersectionLimitTypeLimit);
        crvIntersection.setChordalError(0.0005549915232164794);
        crvIntersection.setAngularError(0.3966089353475057);
        crvIntersection.setParameterizationDefinitionRespected(true);
      }

      wContent.setcurve(crvIntersection);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named intersection in wContent");
    }

    public static void FillTopoSingleWireBodyForComposite(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named CRVtransform in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcCompositeCurve3d crvComposite = OdPrcCompositeCurve3d.createObject();
      {
        OdPrcContentCurve crvContent = crvComposite.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named transform in crvContent");

        // can add transformation if needed here

        // TBD
        OdPrcEllipse3d crvEllipse = OdPrcEllipse3d.createObject();
        {
          OdPrcContentCurve _crvContent = crvEllipse.contentCurve();
          // set name
          _crvContent.baseGeometry().name().setName("named ellipse in crvContent");

          // add some data to params
          OdPrcParameterization _curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
          crvEllipse.setParameterization(_curveParams);

          // can add transformation if needed here

          // TBD
          crvEllipse.setRadiusAtXAxis(1);
          crvEllipse.setRadiusAtYAxis(2);
        }
        OdPrcCurve ellipsePtr1 = crvEllipse;

        crvEllipse = OdPrcEllipse3d.createObject();
        {
          OdPrcContentCurve _crvContent = crvEllipse.contentCurve();
          // set name
          _crvContent.baseGeometry().name().setName("named ellipse in crvContent");

          // add some data to params
          OdPrcParameterization _curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
          crvEllipse.setParameterization(_curveParams);

          // can add transformation if needed here

          // TBD
          crvEllipse.setRadiusAtXAxis(2);
          crvEllipse.setRadiusAtYAxis(3);
        }
        OdPrcCurve ellipsePtr2 = crvEllipse;

        OdPrcPolyLine3d crvPolyLine = OdPrcPolyLine3d.createObject();
        {
          OdPrcContentCurve _crvContent = crvPolyLine.contentCurve();

          // - array of control points defining curve
          OdGePoint3dArray crvPoint = new OdGePoint3dArray();
          crvPoint.Add(new OdGePoint3d(-3.0, 0.0, 0.0));
          crvPoint.Add(new OdGePoint3d(3.0, 0.0, 0.0));
          crvPolyLine.setPoints(crvPoint, true);
        }
        OdPrcCurve polyLinePtr1 = crvPolyLine;

        crvPolyLine = OdPrcPolyLine3d.createObject();
        {
          OdPrcContentCurve _crvContent = crvPolyLine.contentCurve();

          // - array of control points defining curve
          OdGePoint3dArray crvPoint = new OdGePoint3dArray();
          crvPoint.Add(new OdGePoint3d(0.0, 0.0, 0.0));
          crvPoint.Add(new OdGePoint3d(0.0, 4.0, 0.0));
          crvPoint.Add(new OdGePoint3d(0.0, -4.0, 0.0));
          crvPolyLine.setPoints(crvPoint, true);
        }
        OdPrcCurve polyLinePtr2 = crvPolyLine;

        OdPrcCurvePtrArray crvArray = new OdPrcCurvePtrArray();
        crvArray.Add(polyLinePtr1);
        crvArray.Add(ellipsePtr1);
        crvArray.Add(ellipsePtr2);
        crvArray.Add(polyLinePtr2);

        OdBoolArray senseArray = new OdBoolArray();
        senseArray.Add(true);
        senseArray.Add(true);
        senseArray.Add(true);
        senseArray.Add(true);

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization();
        curveParams.set(0, crvArray.Count);

        OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(crvComposite.setData(crvArray, senseArray, true, curveParams) == OdResult.eOk);
      }
      wContent.setcurve(crvComposite);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named CRVTransform in wContent");

    }

    public static void FillTopoSingleWireBodyForBlend02Boundary(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named blend02boundary in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcBlend02Boundary3d crvBlend02Boundary = OdPrcBlend02Boundary3d.createObject();
      {
        OdPrcContentCurve crvContent = crvBlend02Boundary.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named blend02boundary in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(2.168404344971009e-019, 0.009753567003915551);
        crvBlend02Boundary.setParameterization(curveParams);

        // can add transformation if needed here
        // TBD

        OdPrcBlend02Surface blend02 = OdPrcBlend02Surface.createObject();
        blend02.setUVParameterization(new OdPrcUVParameterization(-0.001607154928977807, 0.01195146616849432, 0, 1));

        OdPrcCylinder srfCyl = OdPrcCylinder.createObject();
        {
          OdPrcTransformation3d transform = new OdPrcTransformation3d();
          OdGeMatrix3d matr = new OdGeMatrix3d();
          OdGePoint3d origin = new OdGePoint3d(0.1346409306333122, 0.05665149759597796, 0.05318000000000001);
          OdGeVector3d xAxis = new OdGeVector3d(-1, 0, 0);
          OdGeVector3d yAxis = new OdGeVector3d(0, 1, 0);
          OdGeVector3d zAxis = xAxis.crossProduct(yAxis);
          matr.setCoordSystem(origin, xAxis, yAxis, zAxis);
          transform.set(matr);
          srfCyl.setTransformation(transform);
          srfCyl.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, OdPrcDomain.kLowerInfinite, OdPrcDomain.kUpperInfinite));
          srfCyl.setRadius(0.007856180355214347);
        }

        OdPrcTorus bound_sur1 = OdPrcTorus.createObject();
        {
          OdPrcTransformation3d transform = new OdPrcTransformation3d();
          OdGeMatrix3d matr = new OdGeMatrix3d();
          OdGePoint3d origin = new OdGePoint3d(0.1016940451762275, 0.03587310626005076, 0.02921);
          OdGeVector3d xAxis = new OdGeVector3d(1, 0, 0);
          OdGeVector3d yAxis = new OdGeVector3d(0, 1, 0);
          OdGeVector3d zAxis = xAxis.crossProduct(yAxis);
          matr.setCoordSystem(origin, xAxis, yAxis, zAxis);
          transform.set(matr);
          bound_sur1.setTransformation(transform);

          bound_sur1.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, Globals.Oda2PI));
          bound_sur1.setMajorRadius(0.02921000000000001);
          bound_sur1.setMinorRadius(0.00254); //0.002539
        }

        OdPrcIntersectionCurve3d crvIntersection = OdPrcIntersectionCurve3d.createObject();
        {
          OdPrcContentCurve _crvContent = crvIntersection.contentCurve();

          // set name
          _crvContent.baseGeometry().name().setName("named intersection in crvContent");

          // add some data to params
          OdPrcParameterization _curveParams = new OdPrcParameterization(-0.001607154928977807, 0.01195146616849428);
          crvIntersection.setParameterization(_curveParams);

          // can add transformation if needed here

          // TBD
          OdPrcCylinder surCyl = OdPrcCylinder.createObject();
          OdPrcTorus surTor = OdPrcTorus.createObject();

          OdPrcTransformation3d transform = new OdPrcTransformation3d();
          OdGeMatrix3d matr = new OdGeMatrix3d();
          OdGePoint3d origin = new OdGePoint3d(0.1346409306333122, 0.05665149759597796, 0.05318000000000001);
          OdGeVector3d xAxis = new OdGeVector3d(-1, 0, 0);
          OdGeVector3d yAxis = new OdGeVector3d(0, 1, 0);
          OdGeVector3d zAxis = xAxis.crossProduct(yAxis);
          matr.setCoordSystem(origin, xAxis, yAxis, zAxis);
          transform.set(matr);
          surCyl.setTransformation(transform);

          surCyl.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, OdPrcDomain.kLowerInfinite, OdPrcDomain.kUpperInfinite));
          surCyl.setRadius(0.01039618035521435);

          OdPrcTransformation3d transform1 = new OdPrcTransformation3d();
          OdGeMatrix3d matr1 = new OdGeMatrix3d();
          OdGePoint3d origin1 = new OdGePoint3d(0.1016940451762275, 0.03587310626005076, 0.02921);
          OdGeVector3d xAxis1 = new OdGeVector3d(1, 0, 0);
          OdGeVector3d yAxis1 = new OdGeVector3d(0, 1, 0);
          OdGeVector3d zAxis1 = xAxis1.crossProduct(yAxis1);
          matr1.setCoordSystem(origin1, xAxis1, yAxis1, zAxis1);
          transform1.set(matr1);
          surTor.setTransformation(transform1);

          surTor.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, Globals.Oda2PI));
          surTor.setMajorRadius(0.02921000000000001);
          surTor.setMinorRadius(0.005079999999999999);

          crvIntersection.setSurface1(surTor);
          crvIntersection.setSurface2(surCyl);
          crvIntersection.setSurface1Sense(true);
          crvIntersection.setSurface2Sense(false);
          crvIntersection.setIntersectionSense(false);
          crvIntersection.crossingPointsCrvIntersection().resize(8);

          Byte nCrossingPointFlags = PRC_Globals.PRC_INTERSECTION_CROSS_POINT_SURFACE1 | PRC_Globals.PRC_INTERSECTION_CROSS_POINT_SURFACE2 | PRC_Globals.PRC_INTERSECTION_CROSS_POINT_INSIDE_CURVE_INTERVAL;

          crvIntersection.crossingPointsCrvIntersection()[0].crossingPointPosition().set(0.1341041808452103, 0.04626918255341075, 0.02762582792403328);
          crvIntersection.crossingPointsCrvIntersection()[0].crossingPointUv1().set(0.3103978254394728, 5.966051167063784);
          crvIntersection.crossingPointsCrvIntersection()[0].crossingPointUv2().set(4.764041463982647, 0.02555417207596673);
          crvIntersection.crossingPointsCrvIntersection()[0].crossingPointTangent().set(0.3307189013079988, -0.01709766073082449, 0.9435744158862954);
          crvIntersection.crossingPointsCrvIntersection()[0].setCrossingPointParameter(-0.001607154928977807);
          crvIntersection.crossingPointsCrvIntersection()[0].setCrossingPointScale(1.000143483648419);
          crvIntersection.crossingPointsCrvIntersection()[0].setCrossingPointFlags(nCrossingPointFlags);

          crvIntersection.crossingPointsCrvIntersection()[1].crossingPointPosition().set(0.1343734318291666, 0.04625875924807728, 0.02921);
          crvIntersection.crossingPointsCrvIntersection()[1].crossingPointUv1().set(0.307710025806323, 6.283185307179586);
          crvIntersection.crossingPointsCrvIntersection()[1].crossingPointUv2().set(4.738122309398362, 0.02397000000000001);
          crvIntersection.crossingPointsCrvIntersection()[1].crossingPointTangent().set(2.591203737317232e-016, -6.669502087194763e-018, 1);
          crvIntersection.crossingPointsCrvIntersection()[1].setCrossingPointParameter(2.168404344971009e-019);
          crvIntersection.crossingPointsCrvIntersection()[1].setCrossingPointScale(1);
          crvIntersection.crossingPointsCrvIntersection()[1].setCrossingPointFlags(nCrossingPointFlags);

          crvIntersection.crossingPointsCrvIntersection()[2].crossingPointPosition().set(0.1341068460463681, 0.04626904510958856, 0.03078654731335931);
          crvIntersection.crossingPointsCrvIntersection()[2].crossingPointUv1().set(0.3103700654223553, 0.3155548357368914);
          crvIntersection.crossingPointsCrvIntersection()[2].crossingPointUv2().set(4.763784759818783, 0.0223934526866407);
          crvIntersection.crossingPointsCrvIntersection()[2].crossingPointTangent().set(-0.329121627073357, 0.01693037251846447, 0.9441357514038816);
          crvIntersection.crossingPointsCrvIntersection()[2].setCrossingPointParameter(0.001598960665494233);
          crvIntersection.crossingPointsCrvIntersection()[2].setCrossingPointScale(1.000343251512573);
          crvIntersection.crossingPointsCrvIntersection()[2].setCrossingPointFlags(nCrossingPointFlags);

          crvIntersection.crossingPointsCrvIntersection()[3].crossingPointPosition().set(0.1333353720053878, 0.04633761943850505, 0.03218621630253621);
          crvIntersection.crossingPointsCrvIntersection()[3].crossingPointUv1().set(0.3193993789638551, 0.6259523779802445);
          crvIntersection.crossingPointsCrvIntersection()[3].crossingPointUv2().set(4.838302028889195, 0.0209937836974638);
          crvIntersection.crossingPointsCrvIntersection()[3].crossingPointTangent().set(-0.6202478501943279, 0.07851265255504523, 0.7804667627247718);
          crvIntersection.crossingPointsCrvIntersection()[3].setCrossingPointParameter(0.003199180944312005);
          crvIntersection.crossingPointsCrvIntersection()[3].setCrossingPointScale(0.9999042656648364);
          crvIntersection.crossingPointsCrvIntersection()[3].setCrossingPointFlags(nCrossingPointFlags);

          crvIntersection.crossingPointsCrvIntersection()[4].crossingPointPosition().set(0.1321782193823936, 0.04655121941798981, 0.03324195681528128);
          crvIntersection.crossingPointsCrvIntersection()[4].crossingPointUv1().set(0.3369276482254578, 0.9168548394635812);
          crvIntersection.crossingPointsCrvIntersection()[4].crossingPointUv2().set(4.951548508964415, 0.01993804318471873);
          crvIntersection.crossingPointsCrvIntersection()[4].crossingPointTangent().set(-0.8172802565597771, 0.1992742425025277, 0.5406873019709534);
          crvIntersection.crossingPointsCrvIntersection()[4].setCrossingPointParameter(0.004779920225752403);
          crvIntersection.crossingPointsCrvIntersection()[4].setCrossingPointScale(0.9981746869563218);
          crvIntersection.crossingPointsCrvIntersection()[4].setCrossingPointFlags(nCrossingPointFlags);

          crvIntersection.crossingPointsCrvIntersection()[5].crossingPointPosition().set(0.130801052426036, 0.046990446859571, 0.03390171456686072);
          crvIntersection.crossingPointsCrvIntersection()[5].crossingPointUv1().set(0.3648474322366052, 1.177278387632713);
          crvIntersection.crossingPointsCrvIntersection()[5].crossingPointUv2().set(5.090703516507586, 0.01927828543313928);
          crvIntersection.crossingPointsCrvIntersection()[5].crossingPointTangent().set(-0.8886892161393534, 0.3532181381922882, 0.2923498314854919);
          crvIntersection.crossingPointsCrvIntersection()[5].setCrossingPointParameter(0.006365978613759895);
          crvIntersection.crossingPointsCrvIntersection()[5].setCrossingPointScale(1.002244619626314);
          crvIntersection.crossingPointsCrvIntersection()[5].setCrossingPointFlags(nCrossingPointFlags);

          crvIntersection.crossingPointsCrvIntersection()[6].crossingPointPosition().set(0.1288246894375459, 0.04803454312639792, 0.03426314326305822);
          crvIntersection.crossingPointsCrvIntersection()[6].crossingPointUv1().set(0.4214015261845513, 1.467923355389826);
          crvIntersection.crossingPointsCrvIntersection()[6].crossingPointUv2().set(5.306122456986277, 0.01891685673694178);
          crvIntersection.crossingPointsCrvIntersection()[6].crossingPointTangent().set(-0.8276313857050265, 0.5586316810005534, 0.05437770111427561);
          crvIntersection.crossingPointsCrvIntersection()[6].setCrossingPointParameter(0.008635299997827261);
          crvIntersection.crossingPointsCrvIntersection()[6].setCrossingPointScale(1.00523177480844);
          crvIntersection.crossingPointsCrvIntersection()[6].setCrossingPointFlags(nCrossingPointFlags);

          crvIntersection.crossingPointsCrvIntersection()[7].crossingPointPosition().set(0.1264178276616657, 0.05029059015317995, 0.03425567263508969);
          crvIntersection.crossingPointsCrvIntersection()[7].crossingPointUv1().set(0.5279319193225527, 1.687114677445861);
          crvIntersection.crossingPointsCrvIntersection()[7].crossingPointUv2().set(5.62478739072382, 0.01892432736491032);
          crvIntersection.crossingPointsCrvIntersection()[7].crossingPointTangent().set(-0.6117797523107346, 0.7908821098969895, -0.01519943773639127);
          crvIntersection.crossingPointsCrvIntersection()[7].setCrossingPointParameter(0.01195146616849432);
          crvIntersection.crossingPointsCrvIntersection()[7].setCrossingPointScale(0.9924163238026075);
          crvIntersection.crossingPointsCrvIntersection()[7].setCrossingPointFlags(nCrossingPointFlags);

          crvIntersection.startLimitPoint().set(0.1341041808452103, 0.04626918255341075, 0.02762582792403328);
          crvIntersection.setStartLimitType((uint)EPRCIntersectionLimitType.KEPRCIntersectionLimitTypeLimit);
          crvIntersection.endLimitPoint().set(0.1264178276616657, 0.05029059015317995, 0.03425567263508969);
          crvIntersection.setEndLimitType((uint)EPRCIntersectionLimitType.KEPRCIntersectionLimitTypeLimit);
          crvIntersection.setChordalError(0.0005549915232164794);
          crvIntersection.setAngularError(0.3966089353475057);
          crvIntersection.setParameterizationDefinitionRespected(true);
        }

        // set name
        blend02.contentSurface().baseGeometry().name().setName("named blend02 in crvContent");

        blend02.setboundSurface0(bound_sur1);
        blend02.setboundSurface1(srfCyl);
        blend02.setboundCurve0(null);
        blend02.setboundCurve1(null);
        blend02.setCenterCurve(crvIntersection);
        blend02.setcliffSupportingSurface0(null);
        blend02.setcliffSupportingSurface1(null);
        blend02.setCenterCurveSens(false);
        blend02.setBoundSurfaceSens0(true);
        blend02.setBoundSurfaceSens1(false);
        blend02.setRadius0(0.00254);
        blend02.setRadius1(-0.00254);
        blend02.setParameterizationType(0);

        crvBlend02Boundary.setBlend(blend02);
        crvBlend02Boundary.setBound(0);

        crvBlend02Boundary.crossingPointPositions().resize(16);
        crvBlend02Boundary.crossingPointPositions()[0] = new OdGePoint3d(0.1319527365215415, 0.04548945161933458, 0.02921);
        crvBlend02Boundary.crossingPointPositions()[1] = new OdGePoint3d(0.131807627664526, 0.04553160394259012, 0.02999827365667965);
        crvBlend02Boundary.crossingPointPositions()[2] = new OdGePoint3d(0.131381048771085, 0.04569127987914516, 0.0306981081512681);
        crvBlend02Boundary.crossingPointPositions()[3] = new OdGePoint3d(0.1307199632929836, 0.04604041589644241, 0.03122597840764064);
        crvBlend02Boundary.crossingPointPositions()[4] = new OdGePoint3d(0.1298912215472017, 0.0466429394816688, 0.03155585728343036);
        crvBlend02Boundary.crossingPointPositions()[5] = new OdGePoint3d(0.1285866716184888, 0.04792785053732236, 0.03173657163152911);
        crvBlend02Boundary.crossingPointPositions()[6] = new OdGePoint3d(0.1266724760152784, 0.05043908638504839, 0.03173283631754485);
        crvBlend02Boundary.crossingPointPositions()[7] = new OdGePoint3d(0.1249248545470253, 0.0533475735894785, 0.03174610321705695);
        crvBlend02Boundary.crossingPointPositions()[8] = new OdGePoint3d(0.12384750717005, 0.05574798531870034, 0.03168925584356795);
        crvBlend02Boundary.crossingPointPositions()[9] = new OdGePoint3d(0.1234613491806969, 0.05712763016326012, 0.03144154143897057);
        crvBlend02Boundary.crossingPointPositions()[10] = new OdGePoint3d(0.123356529380409, 0.0578996554473304, 0.03111161338187723);
        crvBlend02Boundary.crossingPointPositions()[11] = new OdGePoint3d(0.1233434451998779, 0.0582013024690065, 0.03090628439768275);
        crvBlend02Boundary.crossingPointPositions()[12] = new OdGePoint3d(0.1233624522821722, 0.05869312061028737, 0.03037203111626576);
        crvBlend02Boundary.crossingPointPositions()[13] = new OdGePoint3d(0.1233713154228329, 0.05877730783570936, 0.03023091533091311);
        crvBlend02Boundary.crossingPointPositions()[14] = new OdGePoint3d(0.1234069985538145, 0.05901920807074548, 0.02947320733566101);
        crvBlend02Boundary.crossingPointPositions()[15] = new OdGePoint3d(0.123409921874157, 0.05903521322898435, 0.02921);

        crvBlend02Boundary.setChordalError(0.0002695529220499314);
        crvBlend02Boundary.setAngularError(0.3950311519258403);
        crvBlend02Boundary.setBoundingSurface(bound_sur1);
        crvBlend02Boundary.setBoundingSurfaceSens(true);
        crvBlend02Boundary.setIntersectionOrder(false);
        crvBlend02Boundary.setIntersectionCurveSens(true);
        crvBlend02Boundary.setBaseParameter(0);
        crvBlend02Boundary.setBaseScale(1);
        crvBlend02Boundary.setstartLimitPoint(new OdGePoint3d(0.1319527365215415, 0.04548945161933458, 0.02921));
        crvBlend02Boundary.setStartLimitType((uint)EPRCIntersectionLimitType.KEPRCIntersectionLimitTypeLimit);
        crvBlend02Boundary.setendLimitPoint(new OdGePoint3d(0.123409921874157, 0.05903521322898435, 0.02921));
        crvBlend02Boundary.setEndLimitType((uint)EPRCIntersectionLimitType.KEPRCIntersectionLimitTypeLimit);
      }

      wContent.setcurve(crvBlend02Boundary);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named blend02boundary in wContent");
    }

    public static void FillTopoSingleWireBodyForTransform(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named CRVtransform in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcTransformedCurve3d crvTransform = OdPrcTransformedCurve3d.createObject();
      {
        OdPrcContentCurve crvContent = crvTransform.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named transform in crvContent");

        // can add transformation if needed here

        // TBD
        OdPrcPolyLine3d crvPolyLine = OdPrcPolyLine3d.createObject();
        {
          OdPrcContentCurve _crvContent = crvPolyLine.contentCurve();

          // - array of control points defining curve
          OdGePoint3dArray crvPoint = new OdGePoint3dArray();
          crvPoint.Add(new OdGePoint3d(0.0, 0.0, 0.0));
          crvPoint.Add(new OdGePoint3d(1.0, 0.0, 0.0));
          crvPoint.Add(new OdGePoint3d(1.0, 1.0, 0.0));
          crvPoint.Add(new OdGePoint3d(1.0, 1.0, 1.0));
          crvPolyLine.setPoints(crvPoint, true);
        }
        crvTransform.setBaseCurve(crvPolyLine);

        // add some data to params
        crvTransform.setParameterization(crvPolyLine.parameterization());

        OdPrcMath3dLinear math_transformation = OdPrcMath3dLinear.createObject();
        {
          OdGeMatrix3d mat = math_transformation.mat();
          mat[0, 0] = 2;
          mat[1, 1] = 3;
          mat[2, 2] = 4;
          OdGeDoubleArray vect = new OdGeDoubleArray();
          vect.Add(0);
          vect.Add(0);
          vect.Add(0);
          math_transformation.setVect(vect);
        }
        crvTransform.setmathTransformation(math_transformation);
      }
      wContent.setcurve(crvTransform);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named CRVTransform in wContent");
    }

    public static void FillTopoSingleWireBodyForOffset(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named CRVoffset in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();

      OdPrcOffsetCurve3d crvOffet = OdPrcOffsetCurve3d.createObject();
      {
        OdPrcContentCurve crvContent = crvOffet.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named offset in crvContent");

        // can add transformation if needed here

        OdPrcPolyLine3d crvPolyLine = OdPrcPolyLine3d.createObject();
        {
          OdPrcContentCurve _crvContent = crvPolyLine.contentCurve();

          // - array of control points defining curve
          OdGePoint3dArray crvPoint = new OdGePoint3dArray();
          crvPoint.Add(new OdGePoint3d(0.0, 0.0, 0.0));
          crvPoint.Add(new OdGePoint3d(3.0, 0.0, 0.0));
          crvPoint.Add(new OdGePoint3d(3.0, 3.0, 0.0));
          crvPoint.Add(new OdGePoint3d(0.0, 3.0, 0.0));
          crvPoint.Add(new OdGePoint3d(0.0, 1.0, 0.0));
          crvPoint.Add(new OdGePoint3d(2.0, 1.0, 0.0));
          crvPoint.Add(new OdGePoint3d(2.0, 2.0, 0.0));
          crvPoint.Add(new OdGePoint3d(1.0, 2.0, 0.0));
          crvPolyLine.setPoints(crvPoint, true);
        }
        crvOffet.setBaseCurve(crvPolyLine);
        crvOffet.setOffsetDistance(3);
        OdGeVector3d plane_normal = new OdGeVector3d(0, 0, 1); //XY plane
        crvOffet.setOffsetPlaneNormal(plane_normal);
      }

      wContent.setcurve(crvOffet);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named CRVOffset in wContent");
    }

    public static void FillTopoSingleWireBodyForEquation(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named CRVequation in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcEquationCurve3d crvEquation = OdPrcEquationCurve3d.createObject();
      {
        OdPrcContentCurve crvContent = crvEquation.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named equation in crvContent");

        // can add transformation if needed here

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
        crvEquation.setParameterization(curveParams);

        OdPrcMath1dTrigonometric math1 = OdPrcMath1dTrigonometric.createObject();
        math1.setDcOffset(0);
        math1.setAmplitude(3);
        math1.setPhase(0);
        math1.setFrequency(5);

        OdPrcMath1dTrigonometric math2 = OdPrcMath1dTrigonometric.createObject();
        math2.setDcOffset(0);
        math2.setAmplitude(3);
        math2.setPhase(Globals.OdaPI / 2);
        math2.setFrequency(7);

        OdPrcMath1dTrigonometric math3 = OdPrcMath1dTrigonometric.createObject();
        math3.setDcOffset(0);
        math3.setAmplitude(3);
        math3.setPhase(0);
        math3.setFrequency(9);

        crvEquation.setFunctionX(math1);
        crvEquation.setFunctionY(math2);
        crvEquation.setFunctionZ(math3);
      }
      wContent.setcurve(crvEquation);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named CRVEquation in wContent");
    }

    public static void FillTopoSingleWireBodyForPolyLine2d(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcPolyLine2d crvPolyLine = OdPrcPolyLine2d.createObject();
      {
        OdPrcContentCurve crvContent = crvPolyLine.contentCurve();

        // - array of control points defining curve
        OdGePoint2dArray crvPoint = new OdGePoint2dArray();
        crvPoint.Add(new OdGePoint2d(0.0, 0.0));
        crvPoint.Add(new OdGePoint2d(2.0, 0.0));
        crvPoint.Add(new OdGePoint2d(1.0, -3.0));
        crvPoint.Add(new OdGePoint2d(4.0, 1.0));
        crvPoint.Add(new OdGePoint2d(2.5, 1.0));
        crvPoint.Add(new OdGePoint2d(3.0, 2.0));
        crvPoint.Add(new OdGePoint2d(1.0, 2.0));
        crvPoint.Add(new OdGePoint2d(0.0, 0.0));
        crvPolyLine.setPoints(crvPoint, true);
      }

      wContent.setcurve(crvPolyLine);
    }

    public static void FillTopoSingleWireBodyForEquation2d(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named CRVequation in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcEquationCurve2d crvEquation = OdPrcEquationCurve2d.createObject();
      {
        OdPrcContentCurve crvContent = crvEquation.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named equation in crvContent");

        // can add transformation if needed here

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
        crvEquation.setParameterization(curveParams);

        OdPrcMath1dTrigonometric mathx = OdPrcMath1dTrigonometric.createObject();
        mathx.setDcOffset(0);
        mathx.setAmplitude(3);
        mathx.setPhase(0);
        mathx.setFrequency(5);

        OdPrcMath1dTrigonometric mathy = OdPrcMath1dTrigonometric.createObject();
        mathy.setDcOffset(0);
        mathy.setAmplitude(5);
        mathy.setPhase(Globals.OdaPI / 2);
        mathy.setFrequency(8);

        crvEquation.setFunctionX(mathx);
        crvEquation.setFunctionY(mathy);
      }
      wContent.setcurve(crvEquation);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named CRVEquation in wContent");
    }

    public static void FillTopoSingleWireBodyForNURBS2d(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcNurbsCurve2d crvNurbs = OdPrcNurbsCurve2d.createObject();
      {
        OdPrcContentCurve crvContent = crvNurbs.contentCurve();

        // fill nurbs parameters
        // - non-array parameters
        int crvdegree = 2;

        // - array of control points defining curve
        OdGePoint2dArray arrPRCPoints = new OdGePoint2dArray();
        arrPRCPoints.Add(new OdGePoint2d(0.0, 0.0));
        arrPRCPoints.Add(new OdGePoint2d(1.5, -0.5));
        arrPRCPoints.Add(new OdGePoint2d(1.0, 1.0));
        arrPRCPoints.Add(new OdGePoint2d(0.0, 2.0));
        arrPRCPoints.Add(new OdGePoint2d(-1.0, 1.0));
        arrPRCPoints.Add(new OdGePoint2d(-1.5, -0.5));
        arrPRCPoints.Add(new OdGePoint2d(0.0, 0.0));
        arrPRCPoints.Add(new OdGePoint2d(-1.0, -2.0));
        arrPRCPoints.Add(new OdGePoint2d(1.0, -2.0));

        // - array of knots
        OdGeDoubleArray arrDoublesForKnots = new OdGeDoubleArray();
        arrDoublesForKnots.Add(1.0);
        arrDoublesForKnots.Add(2.0);
        arrDoublesForKnots.Add(3.0);
        arrDoublesForKnots.Add(4.0);
        arrDoublesForKnots.Add(5.0);
        arrDoublesForKnots.Add(6.0);
        arrDoublesForKnots.Add(7.0);
        arrDoublesForKnots.Add(8.0);
        arrDoublesForKnots.Add(9.0);
        arrDoublesForKnots.Add(10.0);
        arrDoublesForKnots.Add(11.0);
        arrDoublesForKnots.Add(12.0);
        OdGeKnotVector arrPRCKnots = new OdGeKnotVector(arrDoublesForKnots);

        // - array of weights
        OdGeDoubleArray arrPRCWeights = new OdGeDoubleArray(); // zero or for each control point

        // create OdGe nurb curve
        OdGeNurbCurve2d geCurve = new OdGeNurbCurve2d();
        geCurve.set(crvdegree, arrPRCKnots, arrPRCPoints, arrPRCWeights);
        crvNurbs.setFromOdGeCurve(geCurve);
      }

      wContent.setcurve(crvNurbs);
    }

    public static void FillTopoSingleWireBodyForComposite2d(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named CRVtransform in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcCompositeCurve2d crvComposite = OdPrcCompositeCurve2d.createObject();
      {
        OdPrcContentCurve crvContent = crvComposite.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named transform in crvContent");

        // can add transformation if needed here

        // TBD
        OdPrcPolyLine2d crvPolyLine = OdPrcPolyLine2d.createObject();
        {
          OdPrcContentCurve _crvContent = crvPolyLine.contentCurve();

          // - array of control points defining curve
          OdGePoint2dArray crvPoint = new OdGePoint2dArray();
          crvPoint.Add(new OdGePoint2d(0.0, 0.0));
          crvPoint.Add(new OdGePoint2d(1.0, 0.0));
          crvPoint.Add(new OdGePoint2d(1.0, 1.0));
          crvPoint.Add(new OdGePoint2d(-1.0, 1.0));
          crvPoint.Add(new OdGePoint2d(-1.0, 0.0));
          crvPoint.Add(new OdGePoint2d(0.0, 0.0));
          crvPolyLine.setPoints(crvPoint, true);
        }
        OdPrcCurve polyLine = crvPolyLine;

        OdPrcNurbsCurve2d crvNurbs = OdPrcNurbsCurve2d.createObject();
        {
          OdPrcContentCurve _crvContent = crvNurbs.contentCurve();

          // fill nurbs parameters
          // - non-array parameters
          int crvdegree = 2;

          // - array of control points defining curve
          OdGePoint2dArray arrPRCPoints = new OdGePoint2dArray();
          arrPRCPoints.Add(new OdGePoint2d(0.0, 0.0));
          arrPRCPoints.Add(new OdGePoint2d(0.0, -1.0));
          arrPRCPoints.Add(new OdGePoint2d(-1.0, -2.0));
          arrPRCPoints.Add(new OdGePoint2d(0.0, -4.0));
          arrPRCPoints.Add(new OdGePoint2d(1.0, -2.0));

          // - array of knots
          OdGeDoubleArray arrDoublesForKnots = new OdGeDoubleArray();
          arrDoublesForKnots.Add(1.0);
          arrDoublesForKnots.Add(2.0);
          arrDoublesForKnots.Add(3.0);
          arrDoublesForKnots.Add(4.0);
          arrDoublesForKnots.Add(5.0);
          arrDoublesForKnots.Add(6.0);
          arrDoublesForKnots.Add(7.0);
          arrDoublesForKnots.Add(8.0);
          OdGeKnotVector arrPRCKnots = new OdGeKnotVector(arrDoublesForKnots);

          // - array of weights
          OdGeDoubleArray arrPRCWeights = new OdGeDoubleArray(); // zero or for each control point

          // create OdGe nurb curve
          OdGeNurbCurve2d geCurve = new OdGeNurbCurve2d();
          geCurve.set(crvdegree, arrPRCKnots, arrPRCPoints, arrPRCWeights);
          crvNurbs.setFromOdGeCurve(geCurve);
        }
        OdPrcCurve Nurbs = crvNurbs;

        OdPrcCurvePtrArray crvArray = new OdPrcCurvePtrArray();
        crvArray.Add(polyLine);
        crvArray.Add(Nurbs);

        OdBoolArray senseArray = new OdBoolArray();
        senseArray.Add(true);
        senseArray.Add(true);

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization();
        curveParams.set(0, crvArray.Count);

        crvComposite.setData(crvArray, senseArray, false, curveParams);
      }
      wContent.setcurve(crvComposite);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named CRVTransform in wContent");

    }

    public static void FillTopoSingleWireBodyForTransform2d(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named CRVtransform in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcTransformedCurve2d crvTransform = OdPrcTransformedCurve2d.createObject();
      {
        OdPrcContentCurve crvContent = crvTransform.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named transform in crvContent");

        // can add transformation if needed here

        // TBD
        OdPrcNurbsCurve2d crvNurbs = OdPrcNurbsCurve2d.createObject();
        {
          OdPrcContentCurve _crvContent = crvNurbs.contentCurve();

          // fill nurbs parameters
          // - non-array parameters
          int crvdegree = 2;

          // - array of control points defining curve
          OdGePoint2dArray arrPRCPoints = new OdGePoint2dArray();
          arrPRCPoints.Add(new OdGePoint2d(0.0, 0.0));
          arrPRCPoints.Add(new OdGePoint2d(1.5, -0.5));
          arrPRCPoints.Add(new OdGePoint2d(1.0, 1.0));
          arrPRCPoints.Add(new OdGePoint2d(0.0, 2.0));
          arrPRCPoints.Add(new OdGePoint2d(-1.0, 1.0));
          arrPRCPoints.Add(new OdGePoint2d(-1.5, -0.5));
          arrPRCPoints.Add(new OdGePoint2d(0.0, 0.0));
          arrPRCPoints.Add(new OdGePoint2d(-1.0, -2.0));
          arrPRCPoints.Add(new OdGePoint2d(1.0, -2.0));

          // - array of knots
          OdGeDoubleArray arrDoublesForKnots = new OdGeDoubleArray();
          arrDoublesForKnots.Add(1.0);
          arrDoublesForKnots.Add(2.0);
          arrDoublesForKnots.Add(3.0);
          arrDoublesForKnots.Add(4.0);
          arrDoublesForKnots.Add(5.0);
          arrDoublesForKnots.Add(6.0);
          arrDoublesForKnots.Add(7.0);
          arrDoublesForKnots.Add(8.0);
          arrDoublesForKnots.Add(9.0);
          arrDoublesForKnots.Add(10.0);
          arrDoublesForKnots.Add(11.0);
          arrDoublesForKnots.Add(12.0);
          OdGeKnotVector arrPRCKnots = new OdGeKnotVector(arrDoublesForKnots);

          // - array of weights
          OdGeDoubleArray arrPRCWeights = new OdGeDoubleArray(); // zero or for each control point

          // create OdGe nurb curve
          OdGeNurbCurve2d geCurve = new OdGeNurbCurve2d();
          geCurve.set(crvdegree, arrPRCKnots, arrPRCPoints, arrPRCWeights);
          crvNurbs.setFromOdGeCurve(geCurve);
        }
        crvTransform.setBaseCurve(crvNurbs);
        // add some data to params
        //crvTransform.parameterization() = crvPolyLine.parameterization();
        OdPrcParameterization curveParams = new OdPrcParameterization(0, 10);
        crvTransform.setParameterization(curveParams);

        OdPrcMath3dLinear math_transformation = OdPrcMath3dLinear.createObject();
        {
          OdGeMatrix3d mat = math_transformation.mat();
          mat[0, 0] = 1;
          mat[1, 1] = 4;
          OdGeDoubleArray vect = new OdGeDoubleArray();
          vect.resize(3);
          vect[0] = 0;
          vect[1] = 5;
          vect[2] = 0;
          math_transformation.setVect(vect);
        }
        crvTransform.setmathTransformation(math_transformation);
      }
      wContent.setcurve(crvTransform);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named CRVTransform in wContent");
    }

    public static void FillTopoSingleWireBodyForLine2d(OdPrcSingleWireBody wireBody)
    {
      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named line2d in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcLine2d crvLine = OdPrcLine2d.createObject();
      {
        OdPrcContentCurve crvContent = crvLine.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named line2d in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(0, 3.0);
        crvLine.setParameterization(curveParams);

        // can add transformation if needed here
        // TBD
      }

      wContent.setcurve(crvLine);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named line2d in wContent");
    }

    public static void FillTopoSingleWireBodyForCircle2d(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named circle2d in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcCircle2d crvCircle = OdPrcCircle2d.createObject();
      {
        OdPrcContentCurve crvContent = crvCircle.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named circle in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
        crvCircle.setParameterization(curveParams);

        // can add transformation if needed here
        // TBD
        crvCircle.setRadius(1.0);
      }

      wContent.setcurve(crvCircle);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named circle in wContent");

      // may use it if needed
    }

    public static void FillTopoSingleWireBodyForHyperbola2d(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named hyperbola2d in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcHyperbola2d crvHyperbola = OdPrcHyperbola2d.createObject();
      {
        OdPrcContentCurve crvContent = crvHyperbola.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named hyperbola2d in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(-1, 1);
        crvHyperbola.setParameterization(curveParams);

        // TBD
        crvHyperbola.setSemiAxis(2.0);
        crvHyperbola.setSemiImageAxis(5.0);
        crvHyperbola.setParameterizationType(1);
      }

      wContent.setcurve(crvHyperbola);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named hyperbola2d in wContent");
    }

    public static void FillTopoSingleWireBodyForParabola2d(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named parabola2d in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcParabola2d crvParabola = OdPrcParabola2d.createObject();
      {
        OdPrcContentCurve crvContent = crvParabola.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named parabola2d in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(-4, 4);
        crvParabola.setParameterization(curveParams);

        // can add transformation if needed here

        // TBD
        crvParabola.setFocalLength(0.2);
        crvParabola.setParameterizationType(0);
      }

      wContent.setcurve(crvParabola);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named parabola2d in wContent");
    }

    public static void FillTopoSingleWireBodyForEllipse2d(OdPrcSingleWireBody wireBody)
    {
      // OdPrcContent ContentBody 
      // it is created when OdPrcSingleWireBody is created

      // set name to single wire body
      wireBody.contentBody().baseTopology().setBaseInformation(true);
      wireBody.contentBody().baseTopology().name().setName("named ellipse2d in wireBody");

      // wire edge must be of type PRC_TYPE_TOPO_WireEdge or PRC_TYPE_TOPO_Edge
      OdPrcWireEdge wEdge = OdPrcWireEdge.createObject();
      wireBody.setwireEdge(wEdge);

      // set curve
      OdPrcContentWireEdge wContent = wEdge.contentWireEdge();
      OdPrcEllipse2d crvEllipse = OdPrcEllipse2d.createObject();
      {
        OdPrcContentCurve crvContent = crvEllipse.contentCurve();

        // set name
        crvContent.baseGeometry().name().setName("named ellipse2d in crvContent");

        // add some data to params
        OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
        crvEllipse.setParameterization(curveParams);

        // can add transformation if needed here

        // TBD
        crvEllipse.setRadiusAtXAxis(4);
        crvEllipse.setRadiusAtYAxis(1);
      }

      wContent.setcurve(crvEllipse);

      // set name
      wContent.baseTopology().setBaseInformation(true);
      wContent.baseTopology().name().setName("named ellipse2d in wContent");
    }

  }
}
