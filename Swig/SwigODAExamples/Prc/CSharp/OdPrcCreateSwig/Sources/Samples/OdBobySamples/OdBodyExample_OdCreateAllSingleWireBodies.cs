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
  public class OdBodyExample_AllSingleWireBodies : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "Single wire body filled with all curves example";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode , OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // create prc with all single wire bodies
      OdPrcFile pFile = CreateAllWiresModel();

      // export prc
      pFile.writeFile(pPrcStream);
    }

    private static OdPrcFile CreateAllWiresModel()
    {
      // common
      OdGeExtents3d extents = new OdGeExtents3d();
      extents.addPoint(new OdGePoint3d(0, 0, 0));
      extents.addPoint(new OdGePoint3d(1, 1, 1));
      OdPrcFile pFile = OdPrcCreateTopologyHelper.createTopologyCommon();
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure newStructure = fileStructures[fileStructures.Count - 1];

      OdPrcObjectIdArray getStartRootOccurrences = pFile.modelFileData().getStartRootOccurrences();
      OdPrcProductOccurrence rootOccurrence = getStartRootOccurrences[getStartRootOccurrences.Count -1].openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
      OdPrcObjectIdArray son_occurrences = rootOccurrence.referencesOfProductOccurrence().getSonProductOccurrences();

      OdPrcTransformation3d shift = new OdPrcTransformation3d();

      // loop for all wire bodies
      const int countImplementedBodies = 25;
      for (int idx = 0; idx < countImplementedBodies; ++idx)
      {
        OdPrcProductOccurrence newProductOccurrence = CreateTopologyCommonForSingleWire(pFile, extents, idx);

        // fill it with curve
        OdPrcTopoContextPtrArray topologicalContext = newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext();
        OdPrcTopoContext newTopoContext = topologicalContext[topologicalContext.Count - 1];
        OdPrcObjectIdArray bodies = newTopoContext.bodies();

        OdPrcSingleWireBody wireBody = bodies[bodies.Count - 1].safeOpenObjectOdRx(Teigha.PRC.OpenMode.kForWrite, false) as OdPrcSingleWireBody;
        FillTopoSingleWireBody(wireBody, idx);

        // add transformation
        //OdPrcProductOccurrence &newProductOccurrence = *newStructure.fileStructureTree().productOccurrence()[idx];
        OdGeVector3d translateVect = new OdGeVector3d(idx % 4 * (-100), idx / 4 * -100, 0);
        OdGeMatrix3d geMatrix = new OdGeMatrix3d();
        geMatrix.setTranslation(translateVect);
        ApplyScaling(geMatrix, idx);
        shift.set(geMatrix);
        newProductOccurrence.setLocation(shift);

        // add reference to root product occurrence
        //son_occurrences.push_back(newProductOccurrence.objectId());
        son_occurrences.Add(newProductOccurrence.objectId());
      }

      return pFile;
    }

    private static OdPrcProductOccurrence CreateTopologyCommonForSingleWire(OdPrcFile pFile, OdGeExtents3d extents, int idx)
    {
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure newStructure = fileStructures[fileStructures.Count -1];

      // product occurrence section
      OdPrcProductOccurrence newProductOccurrence = OdPrcProductOccurrence.createObject();
      newStructure.addObject(newProductOccurrence);

      OdPrcPartDefinition newDefinition = OdPrcCreateTopologyHelper.createPartDefinition(newStructure, newProductOccurrence);

      // - create single wire body
      OdPrcSingleWireBody wireBody = OdPrcSingleWireBody.createObject();
      newStructure.addObject(wireBody);

      // file structure geometry section
      OdPrcTopoContext newTopoContext = OdPrcCreateTopologyHelper.createTopoContext(newStructure);
      newTopoContext.bodies().Add(wireBody.objectId());

      // - create curve representation item
      OdPrcWireCurve newCurve = OdPrcWireCurve.createObject();
      newStructure.addObject(newCurve);
      setName(newCurve, idx);
      newCurve.setReferenceToBody(wireBody);
      newDefinition.representationItem().Add(newCurve.objectId());

      // bounding box
      newDefinition.boundingBox().box().set(extents.minPoint(),extents.maxPoint());

      return newProductOccurrence;
    }

    private static void setName(OdPrcWireCurve newCurve, int idx)
    {
      if (0 == idx)
      {
        newCurve.name().setName("line");
      }
      else if (1 == idx)
      {
        newCurve.name().setName("NURBS3d");
      }
      else if (2 == idx)
      {
        newCurve.name().setName("Circle");
      }
      else if (3 == idx)
      {
        newCurve.name().setName("polyline3d");
      }
      else if (4 == idx)
      {
        newCurve.name().setName("hyperbola");
      }
      else if (5 == idx)
      {
        newCurve.name().setName("parabola");
      }
      else if (6 == idx)
      {
        newCurve.name().setName("ellipse");
      }
      else if (7 == idx)
      {
        newCurve.name().setName("on surf");
      }
      else if (8 == idx)
      {
        newCurve.name().setName("helix T0");
      }
      else if (9 == idx)
      {
        newCurve.name().setName("intersection");
      }
      else if (10 == idx)
      {
        newCurve.name().setName("composite3d");
      }
      else if (11 == idx)
      {
        newCurve.name().setName("blend02boundary");
      }
      else if (12 == idx)
      {
        newCurve.name().setName("helix T1");
      }
      else if (13 == idx)
      {
        newCurve.name().setName("transform3d");
      }
      else if (14 == idx)
      {
        newCurve.name().setName("offset");
      }
      else if (15 == idx)
      {
        newCurve.name().setName("equation3d");
      }
      else if (16 == idx)
      {
        newCurve.name().setName("polyLine2d");
      }
      else if (17 == idx)
      {
        newCurve.name().setName("equation2d");
      }
      else if (18 == idx)
      {
        newCurve.name().setName("NURBS2d");
      }
      else if (19 == idx)
      {
        newCurve.name().setName("composite2d");
      }
      else if (20 == idx)
      {
        newCurve.name().setName("transform2d");
      }
      else if (21 == idx)
      {
        newCurve.name().setName("line 2d");
      }
      else if (22 == idx)
      {
        newCurve.name().setName("circle 2d");
      }
      else if (23 == idx)
      {
        newCurve.name().setName("hyperbola 2d");
      }
      else if (24 == idx)
      {
        newCurve.name().setName("parabola 2d");
      }
      else if (25 == idx)
      {
        newCurve.name().setName("ellipse 2d");
      }
      else
      {
        throw new Exception("Invalid idx number");
      }
    }

    private static void FillTopoSingleWireBody(OdPrcSingleWireBody wireBody, int idx)
    {
      if (0 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForLine(wireBody);
      }
      else if (1 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForNURBS(wireBody);
      }
      else if (2 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForCircle(wireBody);
      }
      else if (3 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForPolyLine(wireBody);
      }
      else if (4 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForHyperbola(wireBody);
      }
      else if (5 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForParabola(wireBody);
      }
      else if (6 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForEllipse(wireBody);
      }
      else if (7 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForOnSurf(wireBody);
      }
      else if (8 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForHelixT0(wireBody);
      }
      else if (9 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForIntersection(wireBody);
      }
      else if (10 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForComposite(wireBody);
      }
      else if (11 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForBlend02Boundary(wireBody);
      }
      else if (12 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForHelixT1(wireBody);
      }
      else if (13 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForTransform(wireBody);
      }
      else if (14 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForOffset(wireBody);
      }
      else if (15 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForEquation(wireBody);
      }
      else if (16 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForPolyLine2d(wireBody);
      }
      else if (17 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForEquation2d(wireBody);
      }
      else if (18 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForNURBS2d(wireBody);
      }
      else if (19 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForComposite2d(wireBody);
      }
      else if (20 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForTransform2d(wireBody);
      }
      else if (21 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForLine2d(wireBody);
      }
      else if (22 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForCircle2d(wireBody);
      }
      else if (23 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForHyperbola2d(wireBody);
      }
      else if (24 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForParabola2d(wireBody);
      }
      else if (25 == idx)
      {
        OdBodyExample.FillTopoSingleWireBodyForEllipse2d(wireBody);
      }
      else
      {
        throw new Exception("Invalid idx number");
      }
    }

    private static void ApplyScaling(OdGeMatrix3d geMatrix, int idx)
    {
      if (idx < 4)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(30.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 4)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(2.5);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setToRotation(90.0f, OdGeVector3d.kYAxis);
        geMatrix = geMatrix * tmp2geMatrix;

        return;
      }

      if (idx < 8)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(5.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 8)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(2.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 9)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(4000.0);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(-0.125, -0.045, 0.135);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;

        return;
      }

      if (idx == 11)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(4000.0);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(-0.125, -0.045, -0.03);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;

        return;
      }

      if (idx < 12)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(5.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 12)
      {
        return;
      }

      if (idx < 16)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(7.5);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx < 20)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(10);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 20)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToRotation(Globals.OdaPI / 2, tmpgeMatrix.getCsZAxis(), tmpgeMatrix.getCsOrigin());
        geMatrix = geMatrix * tmpgeMatrix;
        tmpgeMatrix.setToScaling(10);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if ((idx < 26) && (idx != 23))
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(10.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 23)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(5.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }
    }
  }
}
