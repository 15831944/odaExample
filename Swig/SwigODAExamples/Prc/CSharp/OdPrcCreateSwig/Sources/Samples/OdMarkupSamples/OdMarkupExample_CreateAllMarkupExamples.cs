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
using Teigha.Core;
using Teigha.PRC;
using Teigha.TD;

namespace OdPrcCreateSwigMgd.Samples.OdMarkupSamples
{
  public class OdMarkupExample_AllMarkupExamples : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "Markup example with some type";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // create prc with all markups examples
      OdPrcFile pFile = CreateAllMarkups();

      // export prc
      pFile.writeFile(pPrcStream);
    }

    void FillTopoMarkup(OdPrcFileStructure newStructure, OdPrcProductOccurrence newProductOccurrence, int subTest)
    {
      OdPrcName name = new OdPrcName();
      if (0 == subTest)
      {
        name.setName("PlainTextMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreatePlainTextMarkup(newStructure), OdPrcMarkup.MarkupType.kText, OdPrcMarkup.MarkupSubType.kUnknownSubtype, OdMarkupExample.CreateNoLeader(), name);
      }
      else if (1 == subTest)
      {
        name.setName("DistanceDimensionMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreateDistanceDimensionMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Distance, OdMarkupExample.CreateDistanceDimensionLeader(newStructure), name);
      }
      else if (2 == subTest)
      {
        name.setName("DimensionRadiusMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreateDimensionRadiusMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Radius, OdMarkupExample.CreateDimensionRadiusLeader(newStructure), name);
      }
      else if (3 == subTest)
      {
        name.setName("DiameterDimensionMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreateDiameterDimensionMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Diameter, OdMarkupExample.CreateNoLeader(), name);
      }
      else if (4 == subTest)
      {
        name.setName("TangentDiameterDimensionMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreateTangentDiameterDimensionMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Diameter_Tangent, OdMarkupExample.CreateTangentDiameterDimensionLeader(newStructure), name);
      }
      else if (5 == subTest)
      {
        name.setName("CylinderDiameterDimensionMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreateCylinderDiameterDimensionMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Diameter_Cylinder, OdMarkupExample.CreateCylinderDiameterDimensionLeader(newStructure), name);
      }
      else if (6 == subTest)
      {
        name.setName("LengthDimensionMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreateLengthDimensionMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Length, OdMarkupExample.CreateNoLeader(), name);
      }
      else if (7 == subTest)
      {
        name.setName("AngleDimensionMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreateAngleDimensionMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Angle, OdMarkupExample.CreateAngleDimensionLeader(newStructure), name);
      }
      else if (8 == subTest)
      {
        name.setName("DatumIdentifierMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreateDatumIdentifierMarkup(newStructure), OdPrcMarkup.MarkupType.kDatum, OdPrcMarkup.MarkupSubType.kDatum_Ident, OdMarkupExample.CreateDatumIdentifierLeader(newStructure), name);
      }
      else if (9 == subTest)
      {
        name.setName("DatumTargetMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreateDatumTargetMarkup(newStructure), OdPrcMarkup.MarkupType.kDatum, OdPrcMarkup.MarkupSubType.kDatum_Target, OdMarkupExample.CreateDatumTargetLeader(newStructure), name);
      }
      else if (10 == subTest)
      {
        name.setName("GDTMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreateGDTMarkup(newStructure), OdPrcMarkup.MarkupType.kGdt, OdPrcMarkup.MarkupSubType.kGdt_Fcf, OdMarkupExample.CreateNoLeader(), name);
      }
      else if (11 == subTest)
      {
        name.setName("RoughnessMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreateRoughnessMarkup(newStructure), OdPrcMarkup.MarkupType.kRoughness, OdPrcMarkup.MarkupSubType.kUnknownSubtype, OdMarkupExample.CreateNoLeader(), name);
      }
      else if (12 == subTest)
      {
        name.setName("TableMarkup");
        OdMarkupExample.FillTopoMarkups(newStructure, newProductOccurrence, OdMarkupExample.CreateTableMarkup(newStructure), OdPrcMarkup.MarkupType.kTable, OdPrcMarkup.MarkupSubType.kUnknownSubtype, OdMarkupExample.CreateNoLeader(), name);
      }
      else
      {
        OdCreationNetSwigExampleLib.Helpers.ODA_ASSERT(false);
      }
    }

    // tweak scales of bodies for this test
    void ApplyScalingForMarkup(OdGeMatrix3d geMatrix, int idx)
    {
      if (idx == 0)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(2.0);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }
      if (idx == 1)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(5);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(1, 0, 0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;

        return;
      }
      if (idx == 2)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(6);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(1, 0, 0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;

        return;
      }
      if (idx == 5)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(6);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(3, 0, 0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;

        return;
      }
      if (idx == 7)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(5);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(6, 4, 0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;

        return;
      }
      if (idx == 8)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(5);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(4, 0, 0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;

        return;
      }
      if (idx == 9)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(5);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(3, 0, 0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;

        return;
      }
      if (idx < 10)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(4.5);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }
      if (idx == 10)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(2);
        geMatrix = geMatrix * tmpgeMatrix;
        return;
      }
      if (idx == 11)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(8);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(-2, -2, 0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;

        return;
      }
      if (idx == 12)
      {
        OdGeMatrix3d tmpgeMatrix = new OdGeMatrix3d();
        tmpgeMatrix.setToScaling(4);
        geMatrix = geMatrix * tmpgeMatrix;

        OdGeVector3d translateVect = new OdGeVector3d(12, 0, 0);
        OdGeMatrix3d tmp2geMatrix = new OdGeMatrix3d();
        tmp2geMatrix.setTranslation(translateVect);
        geMatrix = geMatrix * tmp2geMatrix;

        return;
      }
    }

    OdPrcFile CreateAllMarkups()
    {
      // common
      OdGeExtents3d extents = new OdGeExtents3d();
      extents.addPoint(new OdGePoint3d(0, 0, 0));
      extents.addPoint(new OdGePoint3d(1, 1, 1));
      OdPrcFile pFile = OdPrcCreateTopologyHelper.createTopologyCommon();
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure pFS = fileStructures[fileStructures.Count - 1];

      OdPrcTransformation3d shift = new OdPrcTransformation3d();

      // loop for all markups
      const int countImplementedBodies = 13;
      for (int idx = 0; idx < countImplementedBodies; ++idx)
      {
        OdPrcProductOccurrence pRootPO = pFS.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
        OdPrcProductOccurrence pPO = OdPrcCreateTopologyHelper.createProductOccurrence(pFS, pRootPO);
        OdPrcPartDefinition pPD = OdPrcCreateTopologyHelper.createPartDefinition(pFS, pPO);
        pPD.boundingBox().setbox(extents);

        FillTopoMarkup(pFS, pPO, idx);

        // add transformation
        OdGeVector3d translateVect = new OdGeVector3d(idx % 3 * 50, idx / 3 * (-40), 0);
        OdGeMatrix3d geMatrix = new OdGeMatrix3d();
        geMatrix.setTranslation(translateVect);
        ApplyScalingForMarkup(geMatrix, idx);
        shift.set(geMatrix);
        pPO.setLocation(shift);
      }
      return pFile;
    }

  }
}