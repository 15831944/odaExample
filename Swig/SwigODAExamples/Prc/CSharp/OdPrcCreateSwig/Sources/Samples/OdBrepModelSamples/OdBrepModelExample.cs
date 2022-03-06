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

namespace OdPrcCreateSwigMgd.Samples.OdBrepModelSamples
{
  public class OdBrepModelExample_BrepModelConeWithLoops : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfCone example With Loops";
      }
    }
  }

  public class OdBrepModelExample_BrepObjectMaterial : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep with material model filled with srfPlane example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelSphere : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfSphere example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelCylinder : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfCylinder example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelCone : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfCone example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelRuled : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfRuled example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelExtrusion : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfExtrusion example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelFromCurves : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfFromCurves example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelRevolution : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfRevolution example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelCylindrical : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfCylindrical example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelNURBS : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfNURBS example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelTorusT1 : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfTorusT1 example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelTorusT2 : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfTorusT2 example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelOffset : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfOffset example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelTransform : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfTransform example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelPlane : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfPlane example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelBlend01 : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfBlend01 example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelBlend02 : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfBlend02 example";
      }
    }
  }

  public class OdBrepModelExample_BrepModelBlend03 : OdBrepModelExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with srfBlend03 example";
      }
    }
  }

  public abstract class OdBrepModelExample : OdPrcCreateExample
  {
    public static void addLineStyleForBrep(OdPrcFileStructure newStructure, double r, double g, double b)
    {
      // - add style
      OdPrcCategory1LineStyle.createByColor(r, g, b, newStructure);
    }
    public static void addLineStyleWithMaterialForBrep(OdPrcFileStructure newStructure)
    {
      OdPrcFileStructureGlobals globalData = newStructure.fileStructureGlobals();
      // - add color
      OdPrcRgbColorArray colorArr = globalData.colors();
      OdPrcRgbColor color = new OdPrcRgbColor();
      color.set(1, 0, 0);
      colorArr.Add(color);
      color.set(0, 1, 0);
      colorArr.Add(color);
      color.set(0, 0, 1);
      colorArr.Add(color);

      OdPrcMaterialGeneric material = OdPrcMaterialGeneric.createObject();
      material.setAmbient(new OdPrcColorIndex(0));
      material.setAmbientAlpha(1);
      material.setDiffuse(new OdPrcColorIndex(1));
      material.setDiffuseAlpha(1);
      material.setEmissive(new OdPrcColorIndex(2));
      material.setEmissiveAlpha(1);
      material.setSpecular(new OdPrcColorIndex(0));
      material.setSpecularAlpha(0);
      material.setShininess(0.5);
      newStructure.addObject(material);

      OdPrcCategory1LineStyle.createByMaterial(material.objectId(), newStructure);
    }
    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // create prc BrepData Model
      OdPrcFile pFile = OdPrcCreateTopologyHelper.createTopologyCommon();
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure pFS = fileStructures[fileStructures.Count - 1];
      OdPrcProductOccurrence pRootPO = pFS.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
      OdPrcPartDefinition pPD = OdPrcCreateTopologyHelper.createPartDefinition(pFS, pRootPO);
      OdPrcTopoContext pTopoContext = OdPrcCreateTopologyHelper.createTopoContext(pFS);

      OdGeExtents3d extents = new OdGeExtents3d(new OdGePoint3d(0.0, 0.0, 0.0), new OdGePoint3d(1.0, 1.0, 1.0));
      pPD.boundingBox().box().set(extents.minPoint(), extents.maxPoint());
      OdPrcBrepModel pBrepModel = OdPrcCreateTopologyHelper.createRI<OdPrcBrepModel>(pFS, pPD);
      OdPrcBrepData brepData = OdPrcCreateTopologyHelper.createBody<OdPrcBrepData>(pFS, pTopoContext, pBrepModel);
      brepData.boundingBox().box().set(extents.minPoint(), extents.maxPoint());
      brepData.contentBody().setBoundingBoxBehaviour(2);

      // Add line style to globals
      if (mode == OdPrcCreateSwigMgd_ExampleModes.BrepObjectMaterial)
      {
        addLineStyleWithMaterialForBrep(pFS);
      }
      else
      {
        addLineStyleForBrep(pFS, 1.0f, 0.0f, 0.0f);
      }


      // Add graphic
      addGraphicDataToBrep(pFS);

      switch (mode)
      {
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelSphere:
          pBrepModel.name().setName("Sphere");
          FillTopoBrepFace(brepData, CreateSphere());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelCylinder:
          pBrepModel.name().setName("Cylinder");
          FillTopoBrepFace(brepData, CreateCylinder());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelCone:
          pBrepModel.name().setName("Cone");
          FillTopoBrepFace(brepData, CreateCone());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelRuled:
          pBrepModel.name().setName("Ruled");
          FillTopoBrepFace(brepData, CreateRuled());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelExtrusion:
          pBrepModel.name().setName("Extrusion");
          FillTopoBrepFace(brepData, CreateExtrusion());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelFromCurves:
          pBrepModel.name().setName("FromCurves");
          FillTopoBrepFace(brepData, CreateFromCurves());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelRevolution:
          pBrepModel.name().setName("Revolution");
          FillTopoBrepFace(brepData, CreateRevolution());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelCylindrical:
          pBrepModel.name().setName("Cylindrical");
          FillTopoBrepFace(brepData, CreateCylindrical());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelNURBS:
          pBrepModel.name().setName("NURBS");
          FillTopoBrepFace(brepData, CreateNURBS());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelTorusT1:
          pBrepModel.name().setName("TorusT1_origin");
          FillTopoBrepFace(brepData, CreateTorus());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelTorusT2:
          pBrepModel.name().setName("TorusT2_apple");
          FillTopoBrepFace(brepData, CreateAppleTorus());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelOffset:
          pBrepModel.name().setName("Offset");
          FillTopoBrepFace(brepData, CreateOffset());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelTransform:
          pBrepModel.name().setName("Transform");
          FillTopoBrepFace(brepData, CreateTransform());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelPlane:
          pBrepModel.name().setName("Plane");
          FillTopoBrepFace(brepData, CreatePlane());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelBlend01:
          pBrepModel.name().setName("Blend01");
          FillTopoBrepFace(brepData, CreateBlend01());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelBlend02:
          pBrepModel.name().setName("Blend02");
          FillTopoBrepFace(brepData, CreateBlend02());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelBlend03:
          pBrepModel.name().setName("Blend03");
          FillTopoBrepFace(brepData, CreateBlend03());
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepModelConeWithLoops:
          pBrepModel.name().setName("ConeWithLoops");
          CreateConeWithLoops(brepData);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.BrepObjectMaterial:
          pBrepModel.name().setName("PlaneWithMaterial");
          FillTopoBrepFace(brepData, CreatePlane());
          break;
        default:
          throw new Exception();
      }

      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBrepModel.updateIsClosedFlag() == OdResult.eOk);

      // export prc
      pFile.writeFile(pPrcStream);
    }

    public static void addGraphicDataToBrep(OdPrcFileStructure newStructure)
    {
      OdPrcFileStructureTree tree = newStructure.fileStructureTree();
      OdPrcObjectIdArray partArr = tree.partDefinition();
      OdPrcPartDefinition part = partArr[partArr.Count - 1].safeOpenObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcPartDefinition;
      OdPrcObjectIdArray itemArr = part.representationItem();
      OdPrcRepresentationItem item = itemArr[itemArr.Count - 1].safeOpenObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcRepresentationItem;

      item.setstyleId(newStructure.fileStructureGlobals().category1LineStyles()[0]);
      item.setBehaviourBitField(PRC_Globals.PRC_GRAPHICS_Show);
    }

    public static void FillTopoBrepFace(OdPrcBrepData brepData, OdPrcSurface pSurface)
    {
      OdPrcConnex pCurConnex = OdPrcConnex.createObject();
      brepData.addConnex(pCurConnex);

      {
        OdPrcShell pCurShell = OdPrcShell.createObject();
        pCurConnex.addShell(pCurShell);

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          pCurFace.setbaseSurface(pSurface);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        pCurShell.setShellIsClosed(false);
      }
    }

    public static OdPrcSurface CreateSphere()
    {
      OdPrcSphere pPrcSphere = OdPrcSphere.createObject();
      {
        OdPrcContentSurface srfContent = pPrcSphere.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named sphere in srfContent");
        pPrcSphere.setUVParameterization(new OdPrcUVParameterization(-Globals.OdaPI, Globals.OdaPI, -Globals.OdaPI / 2, Globals.OdaPI / 2));
        // can add transformation if needed here
        // TBD

        pPrcSphere.setRadius(1);
      }
      return pPrcSphere;
    }

    public static OdPrcSurface CreateCylinder()
    {
      OdPrcCylinder pPrcCylinder = OdPrcCylinder.createObject();
      {
        OdPrcContentSurface srfContent = pPrcCylinder.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named cylinder in srfContent");

        pPrcCylinder.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, -Globals.OdaPI / 2, Globals.OdaPI / 2));
        // can add transformation if needed here
        // TBD

        pPrcCylinder.setRadius(1);
      }
      return pPrcCylinder;
    }

    public static OdPrcSurface CreateCone()
    {
      OdPrcCone pPrcCone = OdPrcCone.createObject();
      {
        OdPrcContentSurface srfContent = pPrcCone.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named cone in srfContent");

        pPrcCone.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, OdPrcDomain.kUpperInfinite));

        // can add transformation if needed here
        OdPrcTransformation3d transform = new OdPrcTransformation3d();
        OdGeMatrix3d matr = new OdGeMatrix3d();
        matr *= OdGeMatrix3d.rotation(2.14, OdGeVector3d.kXAxis);
        matr *= OdGeMatrix3d.scaling(0.00018);
        transform.set(matr);
        pPrcCone.setTransformation(transform);
        // TBD

        pPrcCone.setBottomRadius(10);
        pPrcCone.setSemiAngle(0.5);
      }
      return pPrcCone;
    }

    public static OdPrcSurface CreateRuled()
    {
      OdPrcRuledSurface pPrcRuledSurface = OdPrcRuledSurface.createObject();
      {
        OdPrcContentSurface srfContent = pPrcRuledSurface.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named ruled in srfContent");

        pPrcRuledSurface.setUVParameterization(new OdPrcUVParameterization(-5, 5, -5, 5));

        // can add transformation if needed here
        // TBD

        OdPrcParabola3d crvParabola = OdPrcParabola3d.createObject();
        {
          OdPrcContentCurve crvContent = crvParabola.contentCurve();

          // set name
          crvContent.baseGeometry().name().setName("named parabola in crvContent");

          // add some data to params
          OdPrcParameterization curveParams = new OdPrcParameterization(-7.0, 7.0);
          crvParabola.setParameterization(curveParams);

          // can add transformation if needed here

          // TBD
          crvParabola.setFocalLength(0.4);
          crvParabola.setParameterizationType(0);
        }

        OdPrcParabola3d crvParabola1 = OdPrcParabola3d.createObject();
        {
          OdPrcContentCurve crvContent = crvParabola1.contentCurve();

          // set name
          crvContent.baseGeometry().name().setName("named parabola in crvContent");

          // add some data to params
          OdPrcParameterization curveParams = new OdPrcParameterization(-7.0, 7.0);
          crvParabola1.setParameterization(curveParams);

          // can add transformation if needed here
          OdPrcTransformation3d transform = new OdPrcTransformation3d();
          transform.set(OdGeMatrix3d.translation(new OdGeVector3d(0, 0, 1)));
          crvParabola1.setTransformation(transform);

          // TBD
          crvParabola1.setFocalLength(0.5);
          crvParabola1.setParameterizationType(0);
        }
        pPrcRuledSurface.setfirstCurve(crvParabola);
        pPrcRuledSurface.setsecondCurve(crvParabola1);
      }
      return pPrcRuledSurface;
    }

    public static OdPrcSurface CreateExtrusion()
    {
      OdPrcExtrusionSurface pPrcExtrusionSurface = OdPrcExtrusionSurface.createObject();
      {
        OdPrcContentSurface srfContent = pPrcExtrusionSurface.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named extrusion in srfContent");

        pPrcExtrusionSurface.setUVParameterization(new OdPrcUVParameterization(0, 10, 0, 10));

        // can add transformation if needed here
        // TBD

        OdPrcPolyLine2d crvPolyLine = OdPrcPolyLine2d.createObject();
        {
          OdPrcContentCurve crvContent = crvPolyLine.contentCurve();

          // - array of control points defining curve


          OdGePoint2dArray points = new OdGePoint2dArray();
          points.Add(new OdGePoint2d(0.0, 0.0));
          points.Add(new OdGePoint2d(2.0, -1.0));
          points.Add(new OdGePoint2d(1.0, -3.0));
          points.Add(new OdGePoint2d(3.0, -1.0));
          points.Add(new OdGePoint2d(5.0, -3.0));
          points.Add(new OdGePoint2d(4.0, -1.0));
          points.Add(new OdGePoint2d(6.0, 0.0));
          points.Add(new OdGePoint2d(4.0, 0.0));
          points.Add(new OdGePoint2d(3.0, 2.0));
          points.Add(new OdGePoint2d(2.0, 0.0));
          points.Add(new OdGePoint2d(0.0, 0.0));

          crvPolyLine.setPoints(points, true);
        }

        pPrcExtrusionSurface.setBaseCurve(crvPolyLine);
        pPrcExtrusionSurface.setsweepVector(OdGeVector3d.kZAxis);
      }
      return pPrcExtrusionSurface;
    }

    public static OdPrcSurface CreateFromCurves()
    {
      OdPrcFromCurvesSurface pPrcFromCurvesSurface = OdPrcFromCurvesSurface.createObject();
      {
        OdPrcContentSurface srfContent = pPrcFromCurvesSurface.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named fromCurves in srfContent");

        pPrcFromCurvesSurface.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, Globals.Oda2PI));

        // can add transformation if needed here
        // TBD

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
          arrPRCPoints.Add(new OdGePoint3d(1.5, -1.0, -5.0));

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
          OdGeDoubleArray arrPRCWeights = new OdGeDoubleArray();  // zero or for each control point

          // create OdGe nurb curve
          OdGeNurbCurve3d geCurve = new OdGeNurbCurve3d();
          geCurve.set(crvdegree, arrPRCKnots, arrPRCPoints, arrPRCWeights);
          crvNurbs.setFromOdGeCurve(geCurve);
        }

        OdPrcLine3d crvLine = OdPrcLine3d.createObject();
        {
          OdPrcContentCurve crvContent = crvLine.contentCurve();

          // set name
          crvContent.baseGeometry().name().setName("named line in crvContent");

          // add some data to params
          OdPrcParameterization curveParams = new OdPrcParameterization(0.0, 1.0);
          crvLine.setParameterization(curveParams);

          // can add transformation if needed here
          // TBD
        }

        pPrcFromCurvesSurface.setorigin(new OdGePoint3d());
        pPrcFromCurvesSurface.setfirstCurve(crvNurbs);
        pPrcFromCurvesSurface.setsecondCurve(crvLine);
      }
      return pPrcFromCurvesSurface;
    }

    public static OdPrcSurface CreateRevolution()
    {
      OdPrcRevolutionSurface pPrcRevolutionSurface = OdPrcRevolutionSurface.createObject();
      {
        OdPrcContentSurface srfContent = pPrcRevolutionSurface.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named revolution in srfContent");

        pPrcRevolutionSurface.setUVParameterization(new OdPrcUVParameterization(0, Globals.OdaPI / 2, 0, Globals.OdaPI / 2));

        // can add transformation if needed here
        // TBD

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
          OdGeMatrix3d matr = new OdGeMatrix3d();
          matr *= OdGeMatrix3d.rotation(0.57, OdGeVector3d.kXAxis);
          transform.set(matr);
          crvCircle.setTransformation(transform);
          // TBD
          crvCircle.setRadius(1.0);
        }

        pPrcRevolutionSurface.setorigin(new OdGePoint3d());
        pPrcRevolutionSurface.setx(OdGeVector3d.kZAxis);
        pPrcRevolutionSurface.sety(OdGeVector3d.kXAxis);
        pPrcRevolutionSurface.setBaseCurve(crvCircle);
      }
      return pPrcRevolutionSurface;
    }

    public static OdPrcSurface CreateCylindrical()
    {
      OdPrcCylindricalSurface pPrcCylindricalSurface = OdPrcCylindricalSurface.createObject();
      {
        OdPrcContentSurface srfContent = pPrcCylindricalSurface.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named cylindrical in srfContent");

        pPrcCylindricalSurface.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, Globals.OdaPI));

        // can add transformation if needed here
        // TBD

        OdPrcSphere pPrcSphere = OdPrcSphere.createObject();
        {
          OdPrcContentSurface _srfContent = pPrcSphere.contentSurface();

          // set name
          _srfContent.baseGeometry().name().setName("named sphere in srfContent");
          pPrcSphere.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, Globals.OdaPI));
          // can add transformation if needed here
          // TBD

          pPrcSphere.setRadius(1);
        }

        pPrcCylindricalSurface.setBaseSurface(pPrcSphere);
      }
      return pPrcCylindricalSurface;
    }

    public static OdPrcSurface CreateNURBS()
    {
      OdPrcNurbsSurface pPrcNurbsSurface = OdPrcNurbsSurface.createObject();
      {
        OdPrcContentSurface srfContent = pPrcNurbsSurface.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named Nurbs in srfContent");

        // can add transformation if needed here
        // TBD

        int degree_in_u = 3;
        int degree_in_v = 3;

        // - array of control points defining curve
        OdGePoint3dArray arrPRCPoints = new OdGePoint3dArray();
        arrPRCPoints.Add(new OdGePoint3d(2.340000, -1.082736, 2.636552));
        arrPRCPoints.Add(new OdGePoint3d(1.362549, -1.082736, 2.636552));
        arrPRCPoints.Add(new OdGePoint3d(-0.608291, -0.705984, 2.263106));
        arrPRCPoints.Add(new OdGePoint3d(-3.123146, 0.692628, 0.473068));
        arrPRCPoints.Add(new OdGePoint3d(-4.468527, 1.811826, -2.305555));
        arrPRCPoints.Add(new OdGePoint3d(-4.751031, 2.062498, -5.010829));
        arrPRCPoints.Add(new OdGePoint3d(-4.460485, 1.805052, -7.712991));
        arrPRCPoints.Add(new OdGePoint3d(-3.114097, 0.683449, -10.489599));
        arrPRCPoints.Add(new OdGePoint3d(-0.594440, -0.706363, -12.264858));
        arrPRCPoints.Add(new OdGePoint3d(1.362549, -1.082736, -12.636552));
        arrPRCPoints.Add(new OdGePoint3d(2.340000, -1.082736, -12.636552));
        arrPRCPoints.Add(new OdGePoint3d(2.340000, -0.612156, 2.148675));
        arrPRCPoints.Add(new OdGePoint3d(1.449014, -0.612156, 2.148675));
        arrPRCPoints.Add(new OdGePoint3d(-0.348526, -0.300052, 1.791464));
        arrPRCPoints.Add(new OdGePoint3d(-2.696407, 0.880859, 0.095369));
        arrPRCPoints.Add(new OdGePoint3d(-3.978369, 1.838789, -2.497939));
        arrPRCPoints.Add(new OdGePoint3d(-4.248272, 2.053787, -5.010058));
        arrPRCPoints.Add(new OdGePoint3d(-3.970658, 1.832986, -7.519957));
        arrPRCPoints.Add(new OdGePoint3d(-2.687596, 0.872820, -10.110502));
        arrPRCPoints.Add(new OdGePoint3d(-0.336250, -0.300022, -11.793093));
        arrPRCPoints.Add(new OdGePoint3d(1.449014, -0.612156, -12.148675));
        arrPRCPoints.Add(new OdGePoint3d(2.340000, -0.612156, -12.148675));
        arrPRCPoints.Add(new OdGePoint3d(2.340000, 0.086907, 0.622159));
        arrPRCPoints.Add(new OdGePoint3d(1.651939, 0.086907, 0.622159));
        arrPRCPoints.Add(new OdGePoint3d(0.260600, 0.252936, 0.346781));
        arrPRCPoints.Add(new OdGePoint3d(-1.697724, 0.964283, -0.973132));
        arrPRCPoints.Add(new OdGePoint3d(-2.832725, 1.594685, -3.018412));
        arrPRCPoints.Add(new OdGePoint3d(-3.073413, 1.738681, -5.007989));
        arrPRCPoints.Add(new OdGePoint3d(-2.825793, 1.590912, -6.995324));
        arrPRCPoints.Add(new OdGePoint3d(-1.689364, 0.958200, -9.039041));
        arrPRCPoints.Add(new OdGePoint3d(0.269174, 0.254236, -10.348068));
        arrPRCPoints.Add(new OdGePoint3d(1.651939, 0.086907, -10.622159));
        arrPRCPoints.Add(new OdGePoint3d(2.340000, 0.086907, -10.622159));
        arrPRCPoints.Add(new OdGePoint3d(2.340000, -0.525546, -1.007479));
        arrPRCPoints.Add(new OdGePoint3d(1.748929, -0.525546, -1.007479));
        arrPRCPoints.Add(new OdGePoint3d(0.554405, -0.385123, -1.189754));
        arrPRCPoints.Add(new OdGePoint3d(-1.090275, 0.193590, -2.093077));
        arrPRCPoints.Add(new OdGePoint3d(-2.033066, 0.699427, -3.558721));
        arrPRCPoints.Add(new OdGePoint3d(-2.233148, 0.815043, -5.005757));
        arrPRCPoints.Add(new OdGePoint3d(-2.027386, 0.696525, -6.450222));
        arrPRCPoints.Add(new OdGePoint3d(-1.083239, 0.188581, -7.916059));
        arrPRCPoints.Add(new OdGePoint3d(0.561938, -0.384438, -8.811094));
        arrPRCPoints.Add(new OdGePoint3d(1.748929, -0.525546, -8.992521));
        arrPRCPoints.Add(new OdGePoint3d(2.340000, -0.525546, -8.992521));
        arrPRCPoints.Add(new OdGePoint3d(2.340000, -1.182808, -1.627834));
        arrPRCPoints.Add(new OdGePoint3d(1.746516, -1.182808, -1.627834));
        arrPRCPoints.Add(new OdGePoint3d(0.549870, -1.016441, -1.792741));
        arrPRCPoints.Add(new OdGePoint3d(-0.977089, -0.398839, -2.583190));
        arrPRCPoints.Add(new OdGePoint3d(-1.793971, 0.095379, -3.810181));
        arrPRCPoints.Add(new OdGePoint3d(-1.965501, 0.206071, -5.004782));
        arrPRCPoints.Add(new OdGePoint3d(-1.789089, 0.092388, -6.198009));
        arrPRCPoints.Add(new OdGePoint3d(-0.971595, -0.402892, -7.424109));
        arrPRCPoints.Add(new OdGePoint3d(0.558280, -1.016608, -8.208032));
        arrPRCPoints.Add(new OdGePoint3d(1.746516, -1.182808, -8.372166));
        arrPRCPoints.Add(new OdGePoint3d(2.340000, -1.182808, -8.372166));

        // - array of knots
        OdGeDoubleArray arrDoublesForKnots_U = new OdGeDoubleArray();
        arrDoublesForKnots_U.Add(0.0);
        arrDoublesForKnots_U.Add(0.0);
        arrDoublesForKnots_U.Add(0.0);
        arrDoublesForKnots_U.Add(0.0);
        arrDoublesForKnots_U.Add(0.428571428571429);
        arrDoublesForKnots_U.Add(1.0);
        arrDoublesForKnots_U.Add(1.0);
        arrDoublesForKnots_U.Add(1.0);
        arrDoublesForKnots_U.Add(1.0);

        OdGeDoubleArray arrDoublesForKnots_V = new OdGeDoubleArray();
        arrDoublesForKnots_V.Add(0.000000);
        arrDoublesForKnots_V.Add(0.000000);
        arrDoublesForKnots_V.Add(0.000000);
        arrDoublesForKnots_V.Add(0.000000);
        arrDoublesForKnots_V.Add(0.293235);
        arrDoublesForKnots_V.Add(0.586471);
        arrDoublesForKnots_V.Add(0.879706);
        arrDoublesForKnots_V.Add(1.026324);
        arrDoublesForKnots_V.Add(1.172941);
        arrDoublesForKnots_V.Add(1.466177);
        arrDoublesForKnots_V.Add(1.759412);
        arrDoublesForKnots_V.Add(2.052647);
        arrDoublesForKnots_V.Add(2.052647);
        arrDoublesForKnots_V.Add(2.052647);
        arrDoublesForKnots_V.Add(2.052647);

        // - array of weights
        OdGeDoubleArray arrPRCWeights = new OdGeDoubleArray();  // zero or for each control point

        // create OdGe nurb curve
        OdGeNurbSurface geSur = new OdGeNurbSurface();
        geSur.set(degree_in_u, degree_in_v, 0, 0, 5, 11, arrPRCPoints, arrPRCWeights, new OdGeKnotVector(arrDoublesForKnots_U), new OdGeKnotVector(arrDoublesForKnots_V));
        pPrcNurbsSurface.setFromOdGeSurface(geSur);

        pPrcNurbsSurface.setKnotType(1);
        pPrcNurbsSurface.setSurfaceForm(9);
      }
      return pPrcNurbsSurface;
    }

    public static OdPrcSurface CreateTorus()
    {
      OdPrcTorus pPrcTorus = OdPrcTorus.createObject();
      {
        OdPrcContentSurface srfContent = pPrcTorus.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named torus_T1 in srfContent");

        pPrcTorus.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, Globals.Oda2PI));

        // can add transformation if needed here
        OdPrcTransformation3d transform = new OdPrcTransformation3d();
        OdGeMatrix3d matr = new OdGeMatrix3d();
        matr *= OdGeMatrix3d.scaling(8);
        matr *= OdGeMatrix3d.rotation(1.02, OdGeVector3d.kXAxis);
        transform.set(matr);
        pPrcTorus.setTransformation(transform);
        // TBD

        pPrcTorus.setMajorRadius(0.1);
        pPrcTorus.setMinorRadius(0.05);
      }
      return pPrcTorus;
    }

    public static OdPrcSurface CreateAppleTorus()
    {
      OdPrcTorus pPrcTorus = OdPrcTorus.createObject();
      {
        OdPrcContentSurface srfContent = pPrcTorus.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named torus_T2 in srfContent");

        pPrcTorus.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, Globals.Oda2PI));

        // can add transformation if needed here
        OdPrcTransformation3d transform = new OdPrcTransformation3d();
        OdGeMatrix3d matr = new OdGeMatrix3d();
        matr *= OdGeMatrix3d.scaling(4.0);
        matr *= OdGeMatrix3d.rotation(0.91, OdGeVector3d.kXAxis);
        transform.set(matr);
        pPrcTorus.setTransformation(transform);
        // TBD
        pPrcTorus.setMajorRadius(0.035);
        pPrcTorus.setMinorRadius(0.1);
      }
      return pPrcTorus;
    }

    public static OdPrcSurface CreateOffset()
    {
      OdPrcOffsetSurface pPrcOffsetSurface = OdPrcOffsetSurface.createObject();
      {
        OdPrcContentSurface srfContent = pPrcOffsetSurface.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named offset in srfContent");

        pPrcOffsetSurface.setUVParameterization(new OdPrcUVParameterization(0, 8, 0, 8));

        // can add transformation if needed here
        OdPrcTransformation3d transform = new OdPrcTransformation3d();
        OdGeMatrix3d matr = new OdGeMatrix3d();
        OdGeVector3d vec = new OdGeVector3d(-1, -5, 0);
        matr *= OdGeMatrix3d.scaling(0.6);
        matr *= OdGeMatrix3d.translation(vec);
        matr *= OdGeMatrix3d.rotation(0.91, OdGeVector3d.kXAxis);
        matr *= OdGeMatrix3d.rotation(0.08, OdGeVector3d.kYAxis);
        transform.set(matr);
        pPrcOffsetSurface.setTransformation(transform);
        // TBD

        OdPrcExtrusionSurface pPrcExtrusionSurface = OdPrcExtrusionSurface.createObject();
        {
          OdPrcContentSurface _srfContent = pPrcExtrusionSurface.contentSurface();

          // set name
          _srfContent.baseGeometry().name().setName("named extrusion in srfContent");

          pPrcExtrusionSurface.setUVParameterization(new OdPrcUVParameterization(0, 8, 0, 8));

          // can add transformation if needed here
          // TBD

          OdPrcPolyLine2d crvPolyLine = OdPrcPolyLine2d.createObject();
          {
            OdPrcContentCurve crvContent = crvPolyLine.contentCurve();

            // - array of control points defining curve
            OdGePoint2dArray crvPoints = new OdGePoint2dArray();
            crvPoints.Add(new OdGePoint2d(0.0, 0.0));
            crvPoints.Add(new OdGePoint2d(3.0, 0.0));
            crvPoints.Add(new OdGePoint2d(3.0, 3.0));
            crvPoints.Add(new OdGePoint2d(0.0, 3.0));
            crvPoints.Add(new OdGePoint2d(0.0, 1.0));
            crvPoints.Add(new OdGePoint2d(2.0, 1.0));
            crvPoints.Add(new OdGePoint2d(2.0, 2.0));
            crvPoints.Add(new OdGePoint2d(1.0, 2.0));

            crvPolyLine.setPoints(crvPoints, true);
          }

          pPrcExtrusionSurface.setBaseCurve(crvPolyLine);
          pPrcExtrusionSurface.setsweepVector(OdGeVector3d.kZAxis);
        }

        pPrcOffsetSurface.setBaseSurface(pPrcExtrusionSurface);
        pPrcOffsetSurface.setOffsetDistance(0.5);
      }
      return pPrcOffsetSurface;
    }

    public static OdPrcSurface CreateTransform()
    {
      OdPrcTransformedSurface pPrcTransform = OdPrcTransformedSurface.createObject();
      {
        OdPrcContentSurface srfContent = pPrcTransform.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named transform in srfContent");

        pPrcTransform.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, Globals.Oda2PI));

        // can add transformation if needed here
        // TBD

        OdPrcNurbsSurface pPrcNurbsSurface = OdPrcNurbsSurface.createObject();
        {
          OdPrcContentSurface _srfContent = pPrcNurbsSurface.contentSurface();

          // set name
          _srfContent.baseGeometry().name().setName("named Nurbs in srfContent");

          // can add transformation if needed here
          // TBD

          int degree_in_u = 3;
          int degree_in_v = 3;

          // - array of control points defining curve
          OdGePoint3dArray arrPRCPoints = new OdGePoint3dArray();
          arrPRCPoints.Add(new OdGePoint3d(2.340000, -1.082736, 2.636552));
          arrPRCPoints.Add(new OdGePoint3d(1.362549, -1.082736, 2.636552));
          arrPRCPoints.Add(new OdGePoint3d(-0.608291, -0.705984, 2.263106));
          arrPRCPoints.Add(new OdGePoint3d(-3.123146, 0.692628, 0.473068));
          arrPRCPoints.Add(new OdGePoint3d(-4.468527, 1.811826, -2.305555));
          arrPRCPoints.Add(new OdGePoint3d(-4.751031, 2.062498, -5.010829));
          arrPRCPoints.Add(new OdGePoint3d(-4.460485, 1.805052, -7.712991));
          arrPRCPoints.Add(new OdGePoint3d(-3.114097, 0.683449, -10.489599));
          arrPRCPoints.Add(new OdGePoint3d(-0.594440, -0.706363, -12.264858));
          arrPRCPoints.Add(new OdGePoint3d(1.362549, -1.082736, -12.636552));
          arrPRCPoints.Add(new OdGePoint3d(2.340000, -1.082736, -12.636552));
          arrPRCPoints.Add(new OdGePoint3d(2.340000, -0.612156, 2.148675));
          arrPRCPoints.Add(new OdGePoint3d(1.449014, -0.612156, 2.148675));
          arrPRCPoints.Add(new OdGePoint3d(-0.348526, -0.300052, 1.791464));
          arrPRCPoints.Add(new OdGePoint3d(-2.696407, 0.880859, 0.095369));
          arrPRCPoints.Add(new OdGePoint3d(-3.978369, 1.838789, -2.497939));
          arrPRCPoints.Add(new OdGePoint3d(-4.248272, 2.053787, -5.010058));
          arrPRCPoints.Add(new OdGePoint3d(-3.970658, 1.832986, -7.519957));
          arrPRCPoints.Add(new OdGePoint3d(-2.687596, 0.872820, -10.110502));
          arrPRCPoints.Add(new OdGePoint3d(-0.336250, -0.300022, -11.793093));
          arrPRCPoints.Add(new OdGePoint3d(1.449014, -0.612156, -12.148675));
          arrPRCPoints.Add(new OdGePoint3d(2.340000, -0.612156, -12.148675));
          arrPRCPoints.Add(new OdGePoint3d(2.340000, 0.086907, 0.622159));
          arrPRCPoints.Add(new OdGePoint3d(1.651939, 0.086907, 0.622159));
          arrPRCPoints.Add(new OdGePoint3d(0.260600, 0.252936, 0.346781));
          arrPRCPoints.Add(new OdGePoint3d(-1.697724, 0.964283, -0.973132));
          arrPRCPoints.Add(new OdGePoint3d(-2.832725, 1.594685, -3.018412));
          arrPRCPoints.Add(new OdGePoint3d(-3.073413, 1.738681, -5.007989));
          arrPRCPoints.Add(new OdGePoint3d(-2.825793, 1.590912, -6.995324));
          arrPRCPoints.Add(new OdGePoint3d(-1.689364, 0.958200, -9.039041));
          arrPRCPoints.Add(new OdGePoint3d(0.269174, 0.254236, -10.348068));
          arrPRCPoints.Add(new OdGePoint3d(1.651939, 0.086907, -10.622159));
          arrPRCPoints.Add(new OdGePoint3d(2.340000, 0.086907, -10.622159));
          arrPRCPoints.Add(new OdGePoint3d(2.340000, -0.525546, -1.007479));
          arrPRCPoints.Add(new OdGePoint3d(1.748929, -0.525546, -1.007479));
          arrPRCPoints.Add(new OdGePoint3d(0.554405, -0.385123, -1.189754));
          arrPRCPoints.Add(new OdGePoint3d(-1.090275, 0.193590, -2.093077));
          arrPRCPoints.Add(new OdGePoint3d(-2.033066, 0.699427, -3.558721));
          arrPRCPoints.Add(new OdGePoint3d(-2.233148, 0.815043, -5.005757));
          arrPRCPoints.Add(new OdGePoint3d(-2.027386, 0.696525, -6.450222));
          arrPRCPoints.Add(new OdGePoint3d(-1.083239, 0.188581, -7.916059));
          arrPRCPoints.Add(new OdGePoint3d(0.561938, -0.384438, -8.811094));
          arrPRCPoints.Add(new OdGePoint3d(1.748929, -0.525546, -8.992521));
          arrPRCPoints.Add(new OdGePoint3d(2.340000, -0.525546, -8.992521));
          arrPRCPoints.Add(new OdGePoint3d(2.340000, -1.182808, -1.627834));
          arrPRCPoints.Add(new OdGePoint3d(1.746516, -1.182808, -1.627834));
          arrPRCPoints.Add(new OdGePoint3d(0.549870, -1.016441, -1.792741));
          arrPRCPoints.Add(new OdGePoint3d(-0.977089, -0.398839, -2.583190));
          arrPRCPoints.Add(new OdGePoint3d(-1.793971, 0.095379, -3.810181));
          arrPRCPoints.Add(new OdGePoint3d(-1.965501, 0.206071, -5.004782));
          arrPRCPoints.Add(new OdGePoint3d(-1.789089, 0.092388, -6.198009));
          arrPRCPoints.Add(new OdGePoint3d(-0.971595, -0.402892, -7.424109));
          arrPRCPoints.Add(new OdGePoint3d(0.558280, -1.016608, -8.208032));
          arrPRCPoints.Add(new OdGePoint3d(1.746516, -1.182808, -8.372166));
          arrPRCPoints.Add(new OdGePoint3d(2.340000, -1.182808, -8.372166));

          // - array of knots
          OdGeDoubleArray arrDoublesForKnots_U = new OdGeDoubleArray();
          arrDoublesForKnots_U.Add(0.0);
          arrDoublesForKnots_U.Add(0.0);
          arrDoublesForKnots_U.Add(0.0);
          arrDoublesForKnots_U.Add(0.0);
          arrDoublesForKnots_U.Add(0.428571428571429);
          arrDoublesForKnots_U.Add(1.0);
          arrDoublesForKnots_U.Add(1.0);
          arrDoublesForKnots_U.Add(1.0);
          arrDoublesForKnots_U.Add(1.0);

          OdGeDoubleArray arrDoublesForKnots_V = new OdGeDoubleArray();
          arrDoublesForKnots_V.Add(0.000000);
          arrDoublesForKnots_V.Add(0.000000);
          arrDoublesForKnots_V.Add(0.000000);
          arrDoublesForKnots_V.Add(0.000000);
          arrDoublesForKnots_V.Add(0.293235);
          arrDoublesForKnots_V.Add(0.586471);
          arrDoublesForKnots_V.Add(0.879706);
          arrDoublesForKnots_V.Add(1.026324);
          arrDoublesForKnots_V.Add(1.172941);
          arrDoublesForKnots_V.Add(1.466177);
          arrDoublesForKnots_V.Add(1.759412);
          arrDoublesForKnots_V.Add(2.052647);
          arrDoublesForKnots_V.Add(2.052647);
          arrDoublesForKnots_V.Add(2.052647);
          arrDoublesForKnots_V.Add(2.052647);

          // - array of weights
          OdGeDoubleArray arrPRCWeights = new OdGeDoubleArray();  // zero or for each control point

          // create OdGe nurb curve
          OdGeNurbSurface geSur = new OdGeNurbSurface();
          geSur.set(degree_in_u, degree_in_v, 0, 0, 5, 11, arrPRCPoints, arrPRCWeights, new OdGeKnotVector(arrDoublesForKnots_U), new OdGeKnotVector(arrDoublesForKnots_V));
          pPrcNurbsSurface.setFromOdGeSurface(geSur);

          pPrcNurbsSurface.setKnotType(1);
          pPrcNurbsSurface.setSurfaceForm(9);
        }

        OdPrcMath3dLinear math_transformation = OdPrcMath3dLinear.createObject();
        OdGeMatrix3d mat = math_transformation.mat();
        mat *= OdGeMatrix3d.scaling(0.05);
        OdGeVector3d vec = new OdGeVector3d(27, 0, 0);
        mat *= OdGeMatrix3d.translation(vec);
        mat *= OdGeMatrix3d.rotation(0.92, OdGeVector3d.kXAxis);
        mat[0, 0] = 0.8;
        mat[1, 1] = 0.27;

        math_transformation.setmat(mat);

        pPrcTransform.setBaseSurface(pPrcNurbsSurface);
        pPrcTransform.setmathTransformation(math_transformation);
      }
      return pPrcTransform;
    }

    public static OdPrcSurface CreatePlane()
    {
      OdPrcPlane pPrcPlane = OdPrcPlane.createObject();
      {
        OdPrcContentSurface srfContent = pPrcPlane.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named plane in srfContent");

        pPrcPlane.setUVParameterization(new OdPrcUVParameterization(0, 2, 0, 1));

        // can add transformation if needed here
        OdPrcTransformation3d transform = new OdPrcTransformation3d();
        transform.set(OdGeMatrix3d.rotation(3.52, OdGeVector3d.kXAxis));
        pPrcPlane.setTransformation(transform);
        // TBD
      }
      return pPrcPlane;
    }

    public static OdPrcSurface CreateBlend01()
    {
      OdPrcBlend01Surface pPrcBlend01Surface = OdPrcBlend01Surface.createObject();
      {
        OdPrcContentSurface srfContent = pPrcBlend01Surface.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named blend01 in srfContent");

        pPrcBlend01Surface.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, Globals.Oda2PI));

        // can add transformation if needed here
        OdPrcTransformation3d transform = new OdPrcTransformation3d();
        transform.set(OdGeMatrix3d.rotation(0.57, OdGeVector3d.kXAxis));
        pPrcBlend01Surface.setTransformation(transform);
        // TBD

        OdPrcNurbsCurve3d crvNurbsCenter = OdPrcNurbsCurve3d.createObject();
        {
          OdPrcContentCurve crvContent = crvNurbsCenter.contentCurve();

          // fill nurbs parameters
          // - non-array parameters
          int crvdegree = 3;

          // - array of control points defining curve
          OdGePoint3dArray arrPRCPoints = new OdGePoint3dArray();
          arrPRCPoints.Add(new OdGePoint3d(1.0, 0.0, 0.0));
          arrPRCPoints.Add(new OdGePoint3d(1.0, 0.55, 0.0));
          arrPRCPoints.Add(new OdGePoint3d(0.55, 1.0, 0.0));
          arrPRCPoints.Add(new OdGePoint3d(0.0, 1.0, 1.0));

          // - array of knots
          OdGeDoubleArray arrDoublesForKnots = new OdGeDoubleArray();
          arrDoublesForKnots.Add(1.0);
          arrDoublesForKnots.Add(1.0);
          arrDoublesForKnots.Add(1.0);
          arrDoublesForKnots.Add(1.0);
          arrDoublesForKnots.Add(2.0);
          arrDoublesForKnots.Add(2.0);
          arrDoublesForKnots.Add(2.0);
          arrDoublesForKnots.Add(2.0);
          OdGeKnotVector arrPRCKnots = new OdGeKnotVector(arrDoublesForKnots);

          // - array of weights
          OdGeDoubleArray arrPRCWeights = new OdGeDoubleArray();  // zero or for each control point

          // create OdGe nurb curve
          OdGeNurbCurve3d geCurve = new OdGeNurbCurve3d();
          geCurve.set(crvdegree, arrPRCKnots, arrPRCPoints, arrPRCWeights);
          crvNurbsCenter.setFromOdGeCurve(geCurve);
        }

        OdPrcNurbsCurve3d crvNurbsOrigin = OdPrcNurbsCurve3d.createObject();
        {
          OdPrcContentCurve crvContent = crvNurbsOrigin.contentCurve();

          // fill nurbs parameters
          // - non-array parameters
          int crvdegree = 3;

          // - array of control points defining curve
          OdGePoint3dArray arrPRCPoints = new OdGePoint3dArray();
          arrPRCPoints.Add(new OdGePoint3d(1.1, 0.0, 0.0));
          arrPRCPoints.Add(new OdGePoint3d(1.1, 0.61, 0.0));
          arrPRCPoints.Add(new OdGePoint3d(0.61, 1.1, 0.0));
          arrPRCPoints.Add(new OdGePoint3d(0.0, 1.1, 1.0));

          // - array of knots
          OdGeDoubleArray arrDoublesForKnots = new OdGeDoubleArray();
          arrDoublesForKnots.Add(1.0);
          arrDoublesForKnots.Add(1.0);
          arrDoublesForKnots.Add(1.0);
          arrDoublesForKnots.Add(1.0);
          arrDoublesForKnots.Add(2.0);
          arrDoublesForKnots.Add(2.0);
          arrDoublesForKnots.Add(2.0);
          arrDoublesForKnots.Add(2.0);
          OdGeKnotVector arrPRCKnots = new OdGeKnotVector(arrDoublesForKnots);

          // - array of weights
          OdGeDoubleArray arrPRCWeights = new OdGeDoubleArray();  // zero or for each control point

          // create OdGe nurb curve
          OdGeNurbCurve3d geCurve = new OdGeNurbCurve3d();
          geCurve.set(crvdegree, arrPRCKnots, arrPRCPoints, arrPRCWeights);
          crvNurbsOrigin.setFromOdGeCurve(geCurve);
        }

        pPrcBlend01Surface.setCenterCurve(crvNurbsCenter);
        pPrcBlend01Surface.setOriginCurve(crvNurbsOrigin);
      }
      return pPrcBlend01Surface;
    }

    public static OdPrcSurface CreateBlend02()
    {
      OdPrcBlend02Surface blend02 = OdPrcBlend02Surface.createObject();

      OdPrcContentSurface srfContent = blend02.contentSurface();

      // set name
      srfContent.baseGeometry().name().setName("named blend02 in srfContent");

      // can add transformation if needed here
      OdPrcTransformation3d transform = new OdPrcTransformation3d();
      OdGeMatrix3d mat = new OdGeMatrix3d();
      OdGeVector3d vec = new OdGeVector3d(-0.129, -0.045, 0.0);
      mat *= OdGeMatrix3d.scaling(700.0);
      mat *= OdGeMatrix3d.translation(vec);
      mat *= OdGeMatrix3d.rotation(Globals.OdaPI / 2, OdGeVector3d.kXAxis);
      transform.set(mat);
      blend02.setTransformation(transform);
      // TBD

      blend02.setUVParameterization(new OdPrcUVParameterization(-0.001607154928977807, 0.01195146616849432, 0, 1));

      OdPrcCylinder srfCyl = OdPrcCylinder.createObject();
      {
        OdPrcTransformation3d _transform = new OdPrcTransformation3d();
        OdGeMatrix3d matr = new OdGeMatrix3d();
        OdGePoint3d origin = new OdGePoint3d(0.1346409306333122, 0.05665149759597796, 0.05318000000000001);
        OdGeVector3d xAxis = new OdGeVector3d(-1, 0, 0);
        OdGeVector3d yAxis = new OdGeVector3d(0, 1, 0);
        OdGeVector3d zAxis = xAxis.crossProduct(yAxis);
        matr.setCoordSystem(origin, xAxis, yAxis, zAxis);
        _transform.set(matr);
        srfCyl.setTransformation(_transform);
        srfCyl.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, OdPrcDomain.kLowerInfinite, OdPrcDomain.kUpperInfinite));
        srfCyl.setRadius(0.007856180355214347);
      }

      OdPrcTorus bound_sur1 = OdPrcTorus.createObject();
      {
        OdPrcTransformation3d _transform = new OdPrcTransformation3d();
        OdGeMatrix3d matr = new OdGeMatrix3d();
        OdGePoint3d origin = new OdGePoint3d(0.1016940451762275, 0.03587310626005076, 0.02921);
        OdGeVector3d xAxis = new OdGeVector3d(1, 0, 0);
        OdGeVector3d yAxis = new OdGeVector3d(0, 1, 0);
        OdGeVector3d zAxis = xAxis.crossProduct(yAxis);
        matr.setCoordSystem(origin, xAxis, yAxis, zAxis);
        _transform.set(matr);
        bound_sur1.setTransformation(_transform);

        bound_sur1.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, Globals.Oda2PI));
        bound_sur1.setMajorRadius(0.02921000000000001);
        bound_sur1.setMinorRadius(0.00254); //0.002539
      }

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

        OdPrcTransformation3d _transform = new OdPrcTransformation3d();
        OdGeMatrix3d matr = new OdGeMatrix3d();
        OdGePoint3d origin = new OdGePoint3d(0.1346409306333122, 0.05665149759597796, 0.05318000000000001);
        OdGeVector3d xAxis = new OdGeVector3d(-1, 0, 0);
        OdGeVector3d yAxis = new OdGeVector3d(0, 1, 0);
        OdGeVector3d zAxis = xAxis.crossProduct(yAxis);
        matr.setCoordSystem(origin, xAxis, yAxis, zAxis);
        _transform.set(matr);
        surCyl.setTransformation(_transform);

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

        crvIntersection.setstartLimitPoint(new OdGePoint3d(0.1341041808452103, 0.04626918255341075, 0.02762582792403328));
        crvIntersection.setStartLimitType((uint)EPRCIntersectionLimitType.KEPRCIntersectionLimitTypeLimit);
        crvIntersection.setendLimitPoint(new OdGePoint3d(0.1264178276616657, 0.05029059015317995, 0.03425567263508969));
        crvIntersection.setEndLimitType((uint)EPRCIntersectionLimitType.KEPRCIntersectionLimitTypeLimit);
        crvIntersection.setChordalError(0.0005549915232164794);
        crvIntersection.setAngularError(0.3966089353475057);
        crvIntersection.setParameterizationDefinitionRespected(true);
      }

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

      return blend02;
    }

    public static OdPrcSurface CreateBlend03()
    {
      OdPrcBlend03Surface pPrcBlend03Surface = OdPrcBlend03Surface.createObject();
      {
        OdPrcContentSurface srfContent = pPrcBlend03Surface.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named blend03 in srfContent");

        pPrcBlend03Surface.setUVParameterization(new OdPrcUVParameterization(0.0, 0.018, 0, 0.0015, false, 1000, 1000, -1.78e-015, 0));

        // can add transformation if needed here
        OdPrcTransformation3d transform = new OdPrcTransformation3d();
        OdGeMatrix3d mat = new OdGeMatrix3d();
        OdGeVector3d vec = new OdGeVector3d(-2.311, -0.045, 6.463);
        mat *= OdGeMatrix3d.scaling(1700.0);
        mat *= OdGeMatrix3d.translation(vec);
        transform.set(mat);
        pPrcBlend03Surface.setTransformation(transform);
        // TBD

        OdGeDoubleArray arrParam = new OdGeDoubleArray();
        arrParam.Add(7.964017);
        arrParam.Add(9.646060);
        arrParam.Add(11.372563);
        arrParam.Add(13.077258);
        arrParam.Add(14.164829);
        arrParam.Add(15.581163);
        arrParam.Add(16.964170);
        arrParam.Add(17.452360);

        OdInt32Array arrMultip = new OdInt32Array();
        arrMultip.Add(6);
        arrMultip.Add(3);
        arrMultip.Add(3);
        arrMultip.Add(3);
        arrMultip.Add(3);
        arrMultip.Add(3);
        arrMultip.Add(3);
        arrMultip.Add(6);

        OdGePoint3dArray arrPRCPoints = new OdGePoint3dArray();
        arrPRCPoints.Add(new OdGePoint3d(2.312300, -5.159834, -3.251384));
        arrPRCPoints.Add(new OdGePoint3d(2.312859, -5.159738, -3.249346));
        arrPRCPoints.Add(new OdGePoint3d(2.313448, -5.159232, -3.250630));
        arrPRCPoints.Add(new OdGePoint3d(2.311346, -5.158807, -3.250832));
        arrPRCPoints.Add(new OdGePoint3d(2.312397, -5.159279, -3.249137));
        arrPRCPoints.Add(new OdGePoint3d(2.312452, -5.158120, -3.250088));
        arrPRCPoints.Add(new OdGePoint3d(2.310349, -5.158472, -3.249680));
        arrPRCPoints.Add(new OdGePoint3d(2.311930, -5.159133, -3.248666));
        arrPRCPoints.Add(new OdGePoint3d(2.311434, -5.157744, -3.248942));
        arrPRCPoints.Add(new OdGePoint3d(2.309721, -5.158902, -3.248336));
        arrPRCPoints.Add(new OdGePoint3d(2.311678, -5.159318, -3.248080));
        arrPRCPoints.Add(new OdGePoint3d(2.310814, -5.158191, -3.247595));
        arrPRCPoints.Add(new OdGePoint3d(2.309603, -5.159527, -3.247579));
        arrPRCPoints.Add(new OdGePoint3d(2.311662, -5.159589, -3.247737));
        arrPRCPoints.Add(new OdGePoint3d(2.310717, -5.158854, -3.246833));
        arrPRCPoints.Add(new OdGePoint3d(2.309806, -5.160620, -3.246960));
        arrPRCPoints.Add(new OdGePoint3d(2.311792, -5.160077, -3.247450));
        arrPRCPoints.Add(new OdGePoint3d(2.310957, -5.160023, -3.246205));
        arrPRCPoints.Add(new OdGePoint3d(2.310331, -5.161744, -3.246945));
        arrPRCPoints.Add(new OdGePoint3d(2.312028, -5.160597, -3.247443));
        arrPRCPoints.Add(new OdGePoint3d(2.311517, -5.161231, -3.246184));
        arrPRCPoints.Add(new OdGePoint3d(2.310567, -5.162092, -3.247086));
        arrPRCPoints.Add(new OdGePoint3d(2.312125, -5.160762, -3.247509));
        arrPRCPoints.Add(new OdGePoint3d(2.311764, -5.161607, -3.246323));

        OdGeDoubleArray arrRail2Angles = new OdGeDoubleArray();
        arrRail2Angles.Add(1.565043);
        arrRail2Angles.Add(1.504230);
        arrRail2Angles.Add(1.451011);
        arrRail2Angles.Add(1.474211);
        arrRail2Angles.Add(1.519005);
        arrRail2Angles.Add(1.566353);
        arrRail2Angles.Add(1.558732);
        arrRail2Angles.Add(1.542876);

        OdGeVector3dArray arrTangent = new OdGeVector3dArray();
        arrTangent.Add(new OdGeVector3d(-0.000472, 0.000770, 0.000104));
        arrTangent.Add(new OdGeVector3d(-0.000225, 0.000350, 0.000035));
        arrTangent.Add(new OdGeVector3d(-0.000499, 0.000829, 0.000098));
        arrTangent.Add(new OdGeVector3d(-0.000616, 0.000420, 0.000528));
        arrTangent.Add(new OdGeVector3d(-0.000298, 0.000184, 0.000207));
        arrTangent.Add(new OdGeVector3d(-0.000636, 0.000459, 0.000522));
        arrTangent.Add(new OdGeVector3d(-0.000501, -0.000035, 0.000770));
        arrTangent.Add(new OdGeVector3d(-0.000223, -0.000015, 0.000325));
        arrTangent.Add(new OdGeVector3d(-0.000505, -0.000028, 0.000769));
        arrTangent.Add(new OdGeVector3d(-0.000217, -0.000460, 0.000762));
        arrTangent.Add(new OdGeVector3d(-0.000067, -0.000198, 0.000342));
        arrTangent.Add(new OdGeVector3d(-0.000203, -0.000485, 0.000766));
        arrTangent.Add(new OdGeVector3d(0.000002, -0.000679, 0.000609));
        arrTangent.Add(new OdGeVector3d(0.000036, -0.000298, 0.000280));
        arrTangent.Add(new OdGeVector3d(0.000025, -0.000723, 0.000615));
        arrTangent.Add(new OdGeVector3d(0.000277, -0.000832, 0.000237));
        arrTangent.Add(new OdGeVector3d(0.000140, -0.000378, 0.000111));
        arrTangent.Add(new OdGeVector3d(0.000304, -0.000892, 0.000243));
        arrTangent.Add(new OdGeVector3d(0.000463, -0.000752, -0.000215));
        arrTangent.Add(new OdGeVector3d(0.000193, -0.000355, -0.000101));
        arrTangent.Add(new OdGeVector3d(0.000487, -0.000811, -0.000211));
        arrTangent.Add(new OdGeVector3d(0.000501, -0.000669, -0.000360));
        arrTangent.Add(new OdGeVector3d(0.000202, -0.000321, -0.000167));
        arrTangent.Add(new OdGeVector3d(0.000521, -0.000724, -0.000357));

        OdGeDoubleArray arrRail2Deriv = new OdGeDoubleArray();
        arrRail2Deriv.Add(-0.019119);
        arrRail2Deriv.Add(-0.043426);
        arrRail2Deriv.Add(-0.010798);
        arrRail2Deriv.Add(0.034903);
        arrRail2Deriv.Add(0.043425);
        arrRail2Deriv.Add(0.016909);
        arrRail2Deriv.Add(-0.026816);
        arrRail2Deriv.Add(-0.037386);

        OdGeVector3dArray arrSecondDeriv = new OdGeVector3dArray();
        arrSecondDeriv.Add(new OdGeVector3d(-0.000167, -0.000140, 0.000288));
        arrSecondDeriv.Add(new OdGeVector3d(-0.000089, -0.000071, 0.000112));
        arrSecondDeriv.Add(new OdGeVector3d(-0.000166, -0.000146, 0.000287));
        arrSecondDeriv.Add(new OdGeVector3d(-0.000004, -0.000252, 0.000203));
        arrSecondDeriv.Add(new OdGeVector3d(0.000004, -0.000114, 0.000089));
        arrSecondDeriv.Add(new OdGeVector3d(0.000004, -0.000269, 0.000205));
        arrSecondDeriv.Add(new OdGeVector3d(0.000127, -0.000265, 0.000072));
        arrSecondDeriv.Add(new OdGeVector3d(0.000076, -0.000113, 0.000043));
        arrSecondDeriv.Add(new OdGeVector3d(0.000138, -0.000284, 0.000075));
        arrSecondDeriv.Add(new OdGeVector3d(0.000195, -0.000226, -0.000086));
        arrSecondDeriv.Add(new OdGeVector3d(0.000098, -0.000100, -0.000029));
        arrSecondDeriv.Add(new OdGeVector3d(0.000204, -0.000245, -0.000083));
        arrSecondDeriv.Add(new OdGeVector3d(0.000205, -0.000171, -0.000197));
        arrSecondDeriv.Add(new OdGeVector3d(0.000088, -0.000081, -0.000085));
        arrSecondDeriv.Add(new OdGeVector3d(0.000211, -0.000186, -0.000196));
        arrSecondDeriv.Add(new OdGeVector3d(0.000173, -0.000032, -0.000316));
        arrSecondDeriv.Add(new OdGeVector3d(0.000056, -0.000025, -0.000148));
        arrSecondDeriv.Add(new OdGeVector3d(0.000173, -0.000038, -0.000317));
        arrSecondDeriv.Add(new OdGeVector3d(0.000092, 0.000144, -0.000313));
        arrSecondDeriv.Add(new OdGeVector3d(0.000022, 0.000057, -0.000145));
        arrSecondDeriv.Add(new OdGeVector3d(0.000087, 0.000151, -0.000314));
        arrSecondDeriv.Add(new OdGeVector3d(0.000062, 0.000193, -0.000280));
        arrSecondDeriv.Add(new OdGeVector3d(0.000014, 0.000083, -0.000127));
        arrSecondDeriv.Add(new OdGeVector3d(0.000055, 0.000204, -0.000282));

        OdGeDoubleArray arrRail2SecondDeriv = new OdGeDoubleArray();
        arrRail2SecondDeriv.Add(-0.029960);
        arrRail2SecondDeriv.Add(0.003757);
        arrRail2SecondDeriv.Add(0.029102);
        arrRail2SecondDeriv.Add(0.018330);
        arrRail2SecondDeriv.Add(-0.003814);
        arrRail2SecondDeriv.Add(-0.030778);
        arrRail2SecondDeriv.Add(-0.026091);
        arrRail2SecondDeriv.Add(-0.016805);

        pPrcBlend03Surface.setparameters(arrParam);
        pPrcBlend03Surface.setmultiplicities(arrMultip);
        pPrcBlend03Surface.setposition(arrPRCPoints);
        pPrcBlend03Surface.setrail2AnglesV(arrRail2Angles);
        pPrcBlend03Surface.settangent(arrTangent);
        pPrcBlend03Surface.setrail2DerivativesV(arrRail2Deriv);
        pPrcBlend03Surface.setsecondDerivatives(arrSecondDeriv);
        pPrcBlend03Surface.setrail2SecondDerivatives(arrRail2SecondDeriv);

        pPrcBlend03Surface.setRail2ParameterV(1.5);
        pPrcBlend03Surface.setTrimVMin(0);
        pPrcBlend03Surface.setTrimVMax(1.5);
      }
      return pPrcBlend03Surface;
    }

    public static void CreateConeWithLoops(OdPrcBrepData brepData)
    {
      OdPrcConnex pCurConnex = OdPrcConnex.createObject();
      brepData.addConnex(pCurConnex);

      {
        OdPrcShell pCurShell = OdPrcShell.createObject();
        pCurConnex.addShell(pCurShell);

        {
          OdPrcFace pCurFace = OdPrcFace.createObject();

          OdPrcCone pPrcCone = OdPrcCone.createObject();
          {
            OdGeMatrix3d matr = new OdGeMatrix3d();
            OdGePoint3d orPnt = new OdGePoint3d(0.00848600820104306, 0.01503506648794965, 0.0162750000534332);
            OdGeVector3d x = new OdGeVector3d(1, 0, 1.40002853754603e-008);
            OdGeVector3d y = new OdGeVector3d(0, -1, 0);
            OdGeVector3d z = new OdGeVector3d(x.crossProduct(y));
            matr.setCoordSystem(orPnt, x, y, z);
            OdPrcTransformation3d trans = new OdPrcTransformation3d();
            trans.set(matr);
            pPrcCone.setTransformation(trans);
            pPrcCone.setBottomRadius(0.0018);
            pPrcCone.setSemiAngle(0.7853981633974617);
            pPrcCone.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, -0.001799999999999952, 12345));

            OdPrcCircle3d crvCircle = OdPrcCircle3d.createObject();
            {
              OdPrcContentCurve crvContent = crvCircle.contentCurve();

              // set name
              crvContent.baseGeometry().name().setName("named circle in crvContent");

              // add some data to params
              OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
              crvCircle.setParameterization(curveParams);

              // can add transformation if needed here
              OdGeMatrix3d _matr = new OdGeMatrix3d();
              OdGePoint3d _orPnt = new OdGePoint3d(0.008486008203843119, 0.01503506648794965, 0.0160750000534332);
              OdGeVector3d _x = new OdGeVector3d(1, 0, 1.40002853754603e-008);
              OdGeVector3d _y = new OdGeVector3d(0, -1, 0);
              OdGeVector3d _z = new OdGeVector3d(_x.crossProduct(_y));
              _matr.setCoordSystem(_orPnt, _x, _y, _z);
              OdPrcTransformation3d transform = new OdPrcTransformation3d();
              transform.set(_matr);
              crvCircle.setTransformation(transform);
              // TBD
              crvCircle.setRadius(0.002);
            }

            OdPrcEdge edge = OdPrcEdge.createObject();
            edge.contentWireEdge().setcurve(crvCircle);

            OdPrcCoEdge coEdge = OdPrcCoEdge.createObject();
            coEdge.setEdge(edge);
            coEdge.setOrientationWithLoop((sbyte)Orientation.kOpposite);
            //coEdge.setOrientationUvWithLoop(kUnknown);

            OdPrcLoop loop = OdPrcLoop.createObject();
            pCurFace.addLoop(loop);
            loop.addCoEdge(coEdge);
            loop.setOrientationWithSurface((sbyte)Orientation.kSame);


            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            {
              OdPrcCircle3d _crvCircle = OdPrcCircle3d.createObject();
              {
                OdPrcContentCurve crvContent = _crvCircle.contentCurve();

                // set name
                crvContent.baseGeometry().name().setName("named circle in crvContent");

                // add some data to params
                OdPrcParameterization curveParams = new OdPrcParameterization(0, Globals.Oda2PI);
                _crvCircle.setParameterization(curveParams);

                // can add transformation if needed here
                OdGeMatrix3d _matr = new OdGeMatrix3d();
                OdGePoint3d _orPnt = new OdGePoint3d(0.00848600820104306, 0.01503506648794965, 0.0162750000534332);
                OdGeVector3d _x = new OdGeVector3d(1, 0, 1.40002853754603e-008);
                OdGeVector3d _y = new OdGeVector3d(0, -1, 0);
                OdGeVector3d _z = new OdGeVector3d(_x.crossProduct(_y));
                _matr.setCoordSystem(_orPnt, _x, _y, _z);
                OdPrcTransformation3d transform = new OdPrcTransformation3d();
                transform.set(_matr);
                _crvCircle.setTransformation(transform);
                // TBD
                _crvCircle.setRadius(0.0018);
              }

              OdPrcEdge _edge = OdPrcEdge.createObject();
              _edge.contentWireEdge().setcurve(_crvCircle);

              OdPrcCoEdge _coEdge = OdPrcCoEdge.createObject();
              _coEdge.setEdge(_edge);
              _coEdge.setOrientationWithLoop((sbyte)Orientation.kSame);
              //coEdge.setOrientationUvWithLoop(kUnknown);

              OdPrcLoop _loop = OdPrcLoop.createObject();
              pCurFace.addLoop(_loop);
              _loop.addCoEdge(_coEdge);
              _loop.setOrientationWithSurface((sbyte)Orientation.kSame);


            }
          }

          pCurFace.setbaseSurface(pPrcCone);
          pCurFace.setorientationSurfaceWithShell(Orientation.kSame);
          pCurFace.setSurfaceTrimDomain(null);
          pCurFace.setTolerance(0.0);

          pCurShell.addFace(pCurFace);
        }

        pCurShell.setShellIsClosed(false);
      }
    }
  }
}
