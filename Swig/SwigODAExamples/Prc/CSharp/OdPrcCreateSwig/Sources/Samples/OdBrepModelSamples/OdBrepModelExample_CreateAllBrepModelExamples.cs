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
  public class OdBrepModelExample_AllBrepModelExamples : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "Brep model filled with all surface example";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // create prc with all brep examples
      OdPrcFile pFile = CreateAllBrepModels();

      // export prc
      pFile.writeFile(pPrcStream);
    }

    public static OdPrcFile CreateAllBrepModels()
    {
      // common
      OdGeExtents3d extents = new OdGeExtents3d();
      extents.addPoint(new OdGePoint3d(-5, -5, -5));
      extents.addPoint(new OdGePoint3d(5, 5, 5));
      OdPrcFile pFile = OdPrcCreateTopologyHelper.createTopologyCommon();
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure newStructure = fileStructures[fileStructures.Count - 1];

      OdPrcObjectIdArray getStartRootOccurrences = pFile.modelFileData().getStartRootOccurrences();
      OdPrcProductOccurrence rootOccurrence = getStartRootOccurrences[getStartRootOccurrences.Count - 1].openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
      OdPrcObjectIdArray son_occurrences = rootOccurrence.referencesOfProductOccurrence().getSonProductOccurrences();
      OdPrcTransformation3d shift = new OdPrcTransformation3d();

      // loop for all breps
      const int countImplementedBodies = 17;
      for (int idx = 0; idx < countImplementedBodies; ++idx)
      {
        OdPrcProductOccurrence newProductOccurrence = CreateTopologyCommonForBrepModel(pFile, extents, idx);

        // Add line style to globals
        OdBrepModelExample.addLineStyleForBrep(newStructure, 1.0f, 0.0f, 0.0f);

        // Add graphic
        OdBrepModelExample.addGraphicDataToBrep(newStructure);

        // fill it with Brep Data
        OdPrcTopoContextPtrArray topologicalContext = newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext();
        OdPrcTopoContext newTopoContext = topologicalContext[topologicalContext.Count - 1];

        OdPrcObjectIdArray bodies = newTopoContext.bodies();
        OdPrcBrepData brepData = bodies[bodies.Count - 1].safeOpenObjectOdRx(Teigha.PRC.OpenMode.kForWrite,false) as OdPrcBrepData;
        FillTopoBrepModel(brepData, idx);

        OdPrcObjectIdArray partDefinition = newStructure.fileStructureTree().partDefinition();
        OdPrcPartDefinition newDefinition = partDefinition[partDefinition.Count -1].safeOpenObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcPartDefinition;

        OdPrcObjectIdArray representationItem = newDefinition.representationItem();
        OdPrcBrepModel pBrepModel = representationItem[representationItem.Count -1].openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcBrepModel;

        OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBrepModel.updateIsClosedFlag() == OdResult.eOk);

        // add transformation
        OdGeVector3d translateVect = new OdGeVector3d(idx % 4 * (-30000), idx / 4 * -30000, 0);
        OdGeMatrix3d geMatrix = new OdGeMatrix3d();
        geMatrix.setTranslation(translateVect);
        ApplyScalingForBrep(ref geMatrix, idx);
        shift.set(geMatrix);
        newProductOccurrence.setLocation(shift);

        // add reference to root product occurrence
        son_occurrences.Add(newProductOccurrence.objectId());
      }
      return pFile;
    }

    // tweak scales of bodies for this test
    public static void ApplyScalingForBrep(ref OdGeMatrix3d geMatrix, int idx)
    {
      if (idx == 1)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(6000.0);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setToRotation(90.0f, OdGeVector3d.kYAxis);
        geMatrix = geMatrix * tmp2geMatrix;
        return;
      }

      if (idx < 3)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(6000.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 3)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(2000.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 4)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(2000.0);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setToRotation(90.0f, OdGeVector3d.kYAxis);
        geMatrix = geMatrix * tmp2geMatrix;
        return;
      }

      if (idx == 5)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(10000.0);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(-1.0, 0.0, 0.0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;
        return;
      }

      if (idx < 8)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(10000.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 8)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(2000.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 9)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(6000.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 10)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(12000.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 11)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(5000.0);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(0.0, 5.0, 0.0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;
        return;
      }

      if (idx == 12)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(7000.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }

      if (idx == 13)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(8000.0);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(-1.0, 1.0, 0.0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;
        return;
      }

      if (idx == 14)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(15000.0);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(-0.5, 0.0, 0.0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;

        OdGeMatrix3d tmp3geMatrix = new OdGeMatrix3d();
        tmp3geMatrix.setToRotation(0.35, OdGeVector3d.kYAxis);
        geMatrix = geMatrix * tmp3geMatrix;
        return;
      }

      if (idx == 15)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(7000.0);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(0.0, 53.0, -32.0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;
        return;
      }

      if (idx == 16)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(4000.0);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(-12.0, 8850.0, -5463.0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;
        return;
      }
    }


    public static OdPrcProductOccurrence CreateTopologyCommonForBrepModel(OdPrcFile pFile, OdGeExtents3d extents, int idx)
    {
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure newStructure = fileStructures[fileStructures.Count - 1];

      // product occurrence section
      OdPrcProductOccurrence newProductOccurrence = OdPrcProductOccurrence.createObject();
      newStructure.addObject(newProductOccurrence);

      OdPrcPartDefinition newDefinition = OdPrcCreateTopologyHelper.createPartDefinition(newStructure, newProductOccurrence);

      // bounding box
      newDefinition.boundingBox().box().set(extents.minPoint(),extents.maxPoint());

      // create brep model
      OdPrcBrepModel newBrep = OdPrcBrepModel.createObject();
      newStructure.addObject(newBrep);
      newBrep.setIsClosed(true);

      setName(newBrep, idx);
      newDefinition.representationItem().Add(newBrep.objectId());

      // create Brep Data
      OdPrcBrepData newBrepData = OdPrcBrepData.createObject();
      newStructure.addObject(newBrepData);
      newBrepData.boundingBox().box().set(extents.minPoint(),extents.maxPoint());
      newBrepData.contentBody().setBoundingBoxBehaviour(2);

      // set reference to this body in representation item
      newBrep.setReferenceToBody(newBrepData);

      // file structure geometry section
      OdPrcTopoContext newTopoContext = OdPrcCreateTopologyHelper.createTopoContext(newStructure);
      newTopoContext.bodies().Add(newBrepData.objectId());

      return newProductOccurrence;
    }


    public static void FillTopoBrepModel(OdPrcBrepData brepData, int subTest)
    {
      if (0 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateSphere());
      }
      else if (1 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateCylinder());
      }
      else if (2 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateCone());
      }
      else if (3 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateRuled());
      }
      else if (4 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateExtrusion());
      }
      else if (5 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateFromCurves());
      }
      else if (6 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateRevolution());
      }
      else if (7 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateCylindrical());
      }
      else if (8 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateNURBS());
      }
      else if (9 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateTorus());
      }
      else if (10 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateAppleTorus());
      }
      else if (11 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateOffset());
      }
      else if (12 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateTransform());
      }
      else if (13 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreatePlane());
      }
      else if (14 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateBlend01());
      }
      else if (15 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateBlend02());
      }
      else if (16 == subTest)
      {
        OdBrepModelExample.FillTopoBrepFace(brepData, OdBrepModelExample.CreateBlend03());
      }
      else
      {
        throw new Exception();
      }
    }


    public static void setName(OdPrcBrepModel brepModel, int subTest)
    {
      if (0 == subTest)
      {
        brepModel.name().setName("Sphere");
      }
      else if (1 == subTest)
      {
        brepModel.name().setName("Cylinder");
      }
      else if (2 == subTest)
      {
        brepModel.name().setName("Cone");
      }
      else if (3 == subTest)
      {
        brepModel.name().setName("Ruled");
      }
      else if (4 == subTest)
      {
        brepModel.name().setName("Extrusion");
      }
      else if (5 == subTest)
      {
        brepModel.name().setName("FromCurves");
      }
      else if (6 == subTest)
      {
        brepModel.name().setName("Revolution");
      }
      else if (7 == subTest)
      {
        brepModel.name().setName("Cylindrical");
      }
      else if (8 == subTest)
      {
        brepModel.name().setName("NURBS");
      }
      else if (9 == subTest)
      {
        brepModel.name().setName("TorusT1_origin");
      }
      else if (10 == subTest)
      {
        brepModel.name().setName("TorusT2_apple");
      }
      else if (11 == subTest)
      {
        brepModel.name().setName("Offset");
      }
      else if (12 == subTest)
      {
        brepModel.name().setName("Transform");
      }
      else if (13 == subTest)
      {
        brepModel.name().setName("Plane");
      }
      else if (14 == subTest)
      {
        brepModel.name().setName("Blend01");
      }
      else if (15 == subTest)
      {
        brepModel.name().setName("Blend02");
      }
      else if (16 == subTest)
      {
        brepModel.name().setName("Blend03");
      }
      else
      {
        throw new Exception();
      }
    }

  }
}

