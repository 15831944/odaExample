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
  public class OdMarkupExample_PlainTextMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with plain text type"; } }
  }

  public class OdMarkupExample_DistanceDimensionMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with distance dimension type"; } }
  }

  public class OdMarkupExample_DimensionRadiusMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with dimension radius type"; } }
  }

  public class OdMarkupExample_DiameterDimensionMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with diameter dimension type"; } }
  }

  public class OdMarkupExample_TangentDiameterDimensionMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with tangent diameter dimension type"; } }
  }

  public class OdMarkupExample_CylinderDiameterDimensionMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with cylinder diameter dimension type"; } }
  }

  public class OdMarkupExample_LengthDimensionMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with length dimension type"; } }
  }

  public class OdMarkupExample_AngleDimensionMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with angle dimension type"; } }
  }

  public class OdMarkupExample_DatumIdentifierMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with datum identifier type"; } }
  }

  public class OdMarkupExample_DatumTargetMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with datum target type"; } }
  }

  public class OdMarkupExample_GDTMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with geometric dimensioning and tolerance type"; } }
  }

  public class OdMarkupExample_RoughnessMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with roughness type"; } }
  }

  public class OdMarkupExample_TableMarkup : OdMarkupExample
  {
    public override string Description { get { return "Markup example with table type"; } }
  }

  public abstract class OdMarkupExample : OdPrcCreateExample
  {
    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      OdGeExtents3d extents = new OdGeExtents3d();
      extents.addPoint(new OdGePoint3d(0, 0, 0));
      extents.addPoint(new OdGePoint3d(1, 1, 1));
      OdPrcFile pFile = OdPrcCreateTopologyHelper.createTopologyCommon();
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure newStructure = fileStructures[fileStructures.Count - 1];

      OdPrcProductOccurrence pRootPO = newStructure.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
      OdPrcProductOccurrence pPO = OdPrcCreateTopologyHelper.createProductOccurrence(newStructure, pRootPO);
      OdPrcPartDefinition pPD = OdPrcCreateTopologyHelper.createPartDefinition(newStructure, pPO);
      pPD.boundingBox().setbox(extents);

      OdPrcName name = new OdPrcName();
      switch (mode)
      {
        case OdPrcCreateSwigMgd_ExampleModes.PlainTextMarkup:
          name.setName("PlainTextMarkup");
          FillTopoMarkups(newStructure, pPO, CreatePlainTextMarkup(newStructure), OdPrcMarkup.MarkupType.kText, OdPrcMarkup.MarkupSubType.kUnknownSubtype, CreateNoLeader(), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.DistanceDimensionMarkup:
          name.setName("DistanceDimensionMarkup");
          FillTopoMarkups(newStructure, pPO, CreateDistanceDimensionMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Distance, CreateDistanceDimensionLeader(newStructure), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.DimensionRadiusMarkup:
          name.setName("DimensionRadiusMarkup");
          FillTopoMarkups(newStructure, pPO, CreateDimensionRadiusMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Radius, CreateDimensionRadiusLeader(newStructure), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.DiameterDimensionMarkup:
          name.setName("DiameterDimensionMarkup");
          FillTopoMarkups(newStructure, pPO, CreateDiameterDimensionMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Diameter, CreateNoLeader(), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.TangentDiameterDimensionMarkup:
          name.setName("TangentDiameterDimensionMarkup");
          FillTopoMarkups(newStructure, pPO, CreateTangentDiameterDimensionMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Diameter_Tangent, CreateTangentDiameterDimensionLeader(newStructure), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.CylinderDiameterDimensionMarkup:
          name.setName("CylinderDiameterDimensionMarkup");
          FillTopoMarkups(newStructure, pPO, CreateCylinderDiameterDimensionMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Diameter_Cylinder, CreateCylinderDiameterDimensionLeader(newStructure), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.LengthDimensionMarkup:
          name.setName("LengthDimensionMarkup");
          FillTopoMarkups(newStructure, pPO, CreateLengthDimensionMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Length, CreateNoLeader(), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.AngleDimensionMarkup:
          name.setName("AngleDimensionMarkup");
          FillTopoMarkups(newStructure, pPO, CreateAngleDimensionMarkup(newStructure), OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Angle, CreateAngleDimensionLeader(newStructure), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.DatumIdentifierMarkup:
          name.setName("DatumIdentifierMarkup");
          FillTopoMarkups(newStructure, pPO, CreateDatumIdentifierMarkup(newStructure), OdPrcMarkup.MarkupType.kDatum, OdPrcMarkup.MarkupSubType.kDatum_Ident, CreateDatumIdentifierLeader(newStructure), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.DatumTargetMarkup:
          name.setName("DatumTargetMarkup");
          FillTopoMarkups(newStructure, pPO, CreateDatumTargetMarkup(newStructure), OdPrcMarkup.MarkupType.kDatum, OdPrcMarkup.MarkupSubType.kDatum_Target, CreateDatumTargetLeader(newStructure), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.GDTMarkup:
          name.setName("GDTMarkup");
          FillTopoMarkups(newStructure, pPO, CreateGDTMarkup(newStructure), OdPrcMarkup.MarkupType.kGdt, OdPrcMarkup.MarkupSubType.kGdt_Fcf, CreateNoLeader(), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.RoughnessMarkup:
          name.setName("RoughnessMarkup");
          FillTopoMarkups(newStructure, pPO, CreateRoughnessMarkup(newStructure), OdPrcMarkup.MarkupType.kRoughness, OdPrcMarkup.MarkupSubType.kUnknownSubtype, CreateNoLeader(), name);
          break;
        case OdPrcCreateSwigMgd_ExampleModes.TableMarkup:
          name.setName("TableMarkup");
          FillTopoMarkups(newStructure, pPO, CreateTableMarkup(newStructure), OdPrcMarkup.MarkupType.kTable, OdPrcMarkup.MarkupSubType.kUnknownSubtype, CreateNoLeader(), name);
          break;
        default:
          OdCreationNetSwigExampleLib.Helpers.ODA_ASSERT(false);
          break;
      }

      // export prc
      pFile.writeFile(pPrcStream);
    }

    // tessellation for markup with type =  1, sub_type = 0
    public static OdPrcMarkupTess CreatePlainTextMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 5;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(3, 3, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("Markup with Text type", 20, 4) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray polyLine = new OdPrcFloatPointArray();
      polyLine.resize(6);
      polyLine[0].set(0, 0, 0);
      polyLine[1].set(1, 1, 0);
      polyLine[2].set(25, 1, 0);
      polyLine[3].set(25, 7, 0);
      polyLine[4].set(1, 7, 0);
      polyLine[5].set(1, 1, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(polyLine) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    // tessellation for markup with type =  2, sub_type = 1
    public static OdPrcMarkupTess CreateDistanceDimensionMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Verdana");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 5;
      font.fontKeys()[0].attributes = 1 | 2 | 16; // bold, strike-out
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(2, 2.1, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("9.000", 5, 2) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(3);
      pntsArr[0].set(0, 2, 0);
      pntsArr[1].set(0.2, 2.1, 0);
      pntsArr[2].set(0.2, 1.9, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      pntsArr[0].set(9, 2, 0);
      pntsArr[1].set(8.8, 2.1, 0);
      pntsArr[2].set(8.8, 1.9, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr.resize(2);
      pntsArr[0].set(0, 2, 0);
      pntsArr[1].set(2, 2, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr[0].set(7, 2, 0);
      pntsArr[1].set(9, 2, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    // tessellation for markup with type =  2, sub_type = 7
    public static OdPrcMarkupTess CreateDimensionRadiusMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 5;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(2.5, 0.5, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("R", 1, 2) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      font.fontKeys()[0].font_size = 4;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(4, 1.5, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText1 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText1.setText(".1350", 5, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText1);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(4, 0, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText2 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText2.setText(".1150", 5, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText2);
      // end matrix

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    // tessellation for markup with type =  2, sub_type = 11
    public static OdPrcMarkupTess CreateDiameterDimensionMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 5;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(3, 0.3, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("\u2300", 1, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      font.fontKeys()[0].font_size = 4;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(4.3, 0.5, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText1 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText1.setText("3.127", 3, 2) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText1);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(3);
      pntsArr[0].set(0, 0, 0);
      pntsArr[1].set(0.2, 0.1, 0);
      pntsArr[2].set(0.2, -0.1, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      pntsArr[0].set(2, 0, 0);
      pntsArr[1].set(1.8, 0.1, 0);
      pntsArr[2].set(1.8, -0.1, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr.resize(2);
      pntsArr[0].set(0, 0, 0);
      pntsArr[1].set(10, 0, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    // tessellation for markup with type =  2, sub_type = 12
    public static OdPrcMarkupTess CreateTangentDiameterDimensionMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 5;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(3, 0.3, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("\u2300", 1, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      font.fontKeys()[0].font_size = 4;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(4.3, 0.5, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText1 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText1.setText("2.500", 3, 2) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText1);
      // end matrix

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(7.3, 0.5, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText2 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText2.setText("+/-.001 2P", 6, 2) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText2);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(3);
      pntsArr[0].set(0.4, 0, 0);
      pntsArr[1].set(0.2, 0.1, 0);
      pntsArr[2].set(0.2, -0.1, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      pntsArr[0].set(2.4, 0, 0);
      pntsArr[1].set(2.6, 0.1, 0);
      pntsArr[2].set(2.6, -0.1, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr.resize(2);
      pntsArr[0].set(0, 0, 0);
      pntsArr[1].set(14, 0, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    // tessellation for markup with type =  2, sub_type = 13
    public static OdPrcMarkupTess CreateCylinderDiameterDimensionMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 4;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(1, 3.2, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("\u2300", 1, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      font.fontKeys()[0].font_size = 5;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(2, 4, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText1 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText1.setText("49.07", 4, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText1);
      // end matrix

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(2, 3, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText2 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText2.setText("49.02", 4, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText2);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(3);
      pntsArr[0].set(0, 2.7, 0);
      pntsArr[1].set(0.2, 2.8, 0);
      pntsArr[2].set(0.2, 2.6, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      pntsArr[0].set(7, 2.7, 0);
      pntsArr[1].set(6.8, 2.8, 0);
      pntsArr[2].set(6.8, 2.6, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr.resize(2);
      pntsArr[0].set(0, 2.7, 0);
      pntsArr[1].set(7, 2.7, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    // tessellation for markup with type =  2, sub_type = 16
    public static OdPrcMarkupTess CreateLengthDimensionMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 4;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(3, 3, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("\u2300", 1, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      font.fontKeys()[0].font_size = 5;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(4, 3.2, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText1 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText1.setText("9.575", 4, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText1);
      // end matrix

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(8, 3.2, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText2 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText2.setText("\u00b1", (float)0.5, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText2);
      // end matrix

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(8.5, 3.2, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText3 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText3.setText("0.075", 4, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText3);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(3);
      pntsArr[0].set(0, 2.7, 0);
      pntsArr[1].set(0.2, 2.8, 0);
      pntsArr[2].set(0.2, 2.6, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      pntsArr[0].set(2, 2.7, 0);
      pntsArr[1].set(1.8, 2.8, 0);
      pntsArr[2].set(1.8, 2.6, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr.resize(2);
      pntsArr[0].set(0, 0, 0);
      pntsArr[1].set(0, 3, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr[0].set(2, 0, 0);
      pntsArr[1].set(2, 3, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr[0].set(0, 2.7, 0);
      pntsArr[1].set(12, 2.7, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    // tessellation for markup with type =  2, sub_type = 19
    public static OdPrcMarkupTess CreateAngleDimensionMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 4;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdGePoint3dArray circlePntsArr = new OdGePoint3dArray();
      circlePntsArr.resize(20);
      OdGePoint3d point = new OdGePoint3d(0, 0, 0);
      OdGeCircArc3d circle = new OdGeCircArc3d();
      circle.setCenter(point);
      circle.setRadius(5);
      circle.setAngles(Globals.OdaPI + Globals.OdaPI4, Globals.OdaPI + 1.5 * Globals.OdaPI4);
      circle.getSamplePoints(20, circlePntsArr);

      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize((uint)circlePntsArr.Count);
      for (int i = 0; i < circlePntsArr.Count; ++i)
      {
        pntsArr[i].set(circlePntsArr[i].x, circlePntsArr[i].y, circlePntsArr[i].z);
      }
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      circle.setAngles(Globals.Oda2PI - 1.5 * Globals.OdaPI4, Globals.Oda2PI - Globals.OdaPI4);
      circle.getSamplePoints(20, circlePntsArr);
      for (int i = 0; i < circlePntsArr.Count; ++i)
      {
        pntsArr[i].set(circlePntsArr[i].x, circlePntsArr[i].y, circlePntsArr[i].z);
      }
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      pntsArr.resize(3);
      pntsArr[0].set(-3.54, -3.54, 0);
      pntsArr[1].set(-3.34, -3.54, 0);
      pntsArr[2].set(-3.54, -3.74, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      pntsArr[0].set(3.54, -3.54, 0);
      pntsArr[1].set(3.34, -3.54, 0);
      pntsArr[2].set(3.54, -3.74, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(-1.5, -4.5, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("89\u00b0", 3, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(-1.5, -5.5, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText1 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText1.setText("91\u00b0", 3, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText1);
      // end matrix

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    // tessellation for markup with type =  7, sub_type = 1
    public static OdPrcMarkupTess CreateDatumIdentifierMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(5);
      pntsArr[0].set(1, 1, 0);
      pntsArr[1].set(5, 1, 0);
      pntsArr[2].set(5, 4, 0);
      pntsArr[3].set(1, 4, 0);
      pntsArr[4].set(1, 1, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 5;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(2, 2, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("A", 2, 3) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    // tessellation for markup with type =  7, sub_type = 2
    public static OdPrcMarkupTess CreateDatumTargetMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdGePoint3d point = new OdGePoint3d(2, 3, 0);
      OdGeCircArc3d circle = new OdGeCircArc3d();
      circle.setCenter(point);
      circle.setRadius(2);
      OdGePoint3dArray circlePntsArr = new OdGePoint3dArray();
      circlePntsArr.resize(100);
      circle.getSamplePoints(100, circlePntsArr);
      circlePntsArr.Add(circlePntsArr[0]);
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize((uint)circlePntsArr.Count);
      for (int i = 0; i < circlePntsArr.Count; ++i)
      {
        pntsArr[i].set(circlePntsArr[i].x, circlePntsArr[i].y, circlePntsArr[i].z);
      }
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr.resize(2);
      pntsArr[0].set(0, 3, 0);
      pntsArr[1].set(4, 3, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 5;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(1.5, 1.5, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("B", 1, 3) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    // tessellation for markup with type =  9, sub_type = 1
    public static OdPrcMarkupTess CreateGDTMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 5;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(1, 2, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("\u2225", 10, 4) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(13, 2, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText1 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText1.setText(".010", 10, 4) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText1);
      // end matrix

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(25, 2, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText2 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText2.setText("A", 5, 4) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText2);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(5);
      pntsArr[0].set(0, 1, 0);
      pntsArr[1].set(31, 1, 0);
      pntsArr[2].set(31, 7, 0);
      pntsArr[3].set(0, 7, 0);
      pntsArr[4].set(0, 1, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr.resize(2);
      pntsArr[0].set(12, 1, 0);
      pntsArr[1].set(12, 7, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr.resize(2);
      pntsArr[0].set(24, 1, 0);
      pntsArr[1].set(24, 7, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    // tessellation for markup with type =  12, sub_type = 0
    public static OdPrcMarkupTess CreateRoughnessMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 4;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(3);
      pntsArr[0].set(4.5, 1, 0);
      pntsArr[1].set(5, 1, 0);
      pntsArr[2].set(5, 0.5, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr[0].set(4, 0, 0);
      pntsArr[1].set(6, 2, 0);
      pntsArr[2].set(10, 2, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr.resize(5);
      pntsArr[0].set(9, 4, 0);
      pntsArr[1].set(7, 4, 0);
      pntsArr[2].set(8, 3, 0);
      pntsArr[3].set(10, 5, 0);
      pntsArr[4].set(11, 5, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(6.8, 4.3, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("250", 1, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    // tessellation for markup with type =  15, sub_type = 0
    public static OdPrcMarkupTess CreateTableMarkup(OdPrcFileStructure pCurFS)
    {
      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 5;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont)pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(1, 1, 0);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("Markup with table type", 20, 5) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix)pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      return mTess;
    }

    public static OdPrcMarkupLeaderPtrArray CreateNoLeader()
    {
      //Create Leader
      OdPrcMarkupLeaderPtrArray leaders = new OdPrcMarkupLeaderPtrArray();
      return leaders;
    }

    public static OdPrcMarkupLeaderPtrArray CreateDistanceDimensionLeader(OdPrcFileStructure pCurFS)
    {
      //Create Leader
      OdPrcMarkupLeaderPtrArray leaders = new OdPrcMarkupLeaderPtrArray();
      OdPrcMarkupLeader leader = OdPrcMarkupLeader.createObject();

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray arrPnts = new OdPrcFloatPointArray();
      arrPnts.resize(2);
      arrPnts[0].set(0, 0, 0);
      arrPnts[1].set(0, 2.2, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader);

      leader = OdPrcMarkupLeader.createObject();

      pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      pFirstMkpTess.setColor(greenCol);

      pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      arrPnts[0].set(9, 0, 0);
      arrPnts[1].set(9, 2.2, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader);
      return leaders;
    }

    public static OdPrcMarkupLeaderPtrArray CreateDimensionRadiusLeader(OdPrcFileStructure pCurFS)
    {
      //Create Leader
      OdPrcMarkupLeaderPtrArray leaders = new OdPrcMarkupLeaderPtrArray();
      OdPrcMarkupLeader leader = OdPrcMarkupLeader.createObject();

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      OdPrcFloatPointArray arrPnts = new OdPrcFloatPointArray();
      arrPnts.resize(3);
      arrPnts[0].set(0, 1, 0);
      arrPnts[1].set(0.2, 1.1, 0);
      arrPnts[2].set(0.2, 0.9, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles)pCurMkpTess).setTriangles(arrPnts) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      arrPnts.resize(2);
      arrPnts[0].set(0.2, 1, 0);
      arrPnts[1].set(2, 1, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader);
      return leaders;
    }

    public static OdPrcMarkupLeaderPtrArray CreateTangentDiameterDimensionLeader(OdPrcFileStructure pCurFS)
    {
      //Create Leader
      OdPrcMarkupLeaderPtrArray leaders = new OdPrcMarkupLeaderPtrArray();
      OdPrcMarkupLeader leader = OdPrcMarkupLeader.createObject();

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray arrPnts = new OdPrcFloatPointArray();
      arrPnts.resize(2);
      arrPnts[0].set(0.4, 3, 0);
      arrPnts[1].set(0.4, -0.3, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader);

      leader = OdPrcMarkupLeader.createObject();

      pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      pFirstMkpTess.setColor(greenCol);

      pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      arrPnts[0].set(2.4, 3, 0);
      arrPnts[1].set(2.4, -0.3, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader);
      return leaders;
    }

    public static OdPrcMarkupLeaderPtrArray CreateCylinderDiameterDimensionLeader(OdPrcFileStructure pCurFS)
    {
      //Create Leader
      OdPrcMarkupLeaderPtrArray leaders = new OdPrcMarkupLeaderPtrArray();
      OdPrcMarkupLeader leader = OdPrcMarkupLeader.createObject();

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray arrPnts = new OdPrcFloatPointArray();
      arrPnts.resize(2);
      arrPnts[0].set(0, 0, 0);
      arrPnts[1].set(0, 3, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader);

      leader = OdPrcMarkupLeader.createObject();

      pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      pFirstMkpTess.setColor(greenCol);

      pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      arrPnts[0].set(7, 0, 0);
      arrPnts[1].set(7, 3, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader);
      return leaders;
    }

    public static OdPrcMarkupLeaderPtrArray CreateAngleDimensionLeader(OdPrcFileStructure pCurFS)
    {
      //Create Leader
      OdPrcMarkupLeaderPtrArray leaders = new OdPrcMarkupLeaderPtrArray();
      OdPrcMarkupLeader leader = OdPrcMarkupLeader.createObject();

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray arrPnts = new OdPrcFloatPointArray();
      arrPnts.resize(2);
      arrPnts[0].set(-1.9, -1, 0);
      arrPnts[1].set(-3.7, -3.8, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader);

      leader = OdPrcMarkupLeader.createObject();

      pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      pFirstMkpTess.setColor(greenCol);

      pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      arrPnts[0].set(1.9, -1, 0);
      arrPnts[1].set(3.7, -3.8, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader);
      return leaders;
    }

    public static OdPrcMarkupLeaderPtrArray CreateDatumIdentifierLeader(OdPrcFileStructure pCurFS)
    {
      //Create Leader
      OdPrcMarkupLeaderPtrArray leaders = new OdPrcMarkupLeaderPtrArray();
      OdPrcMarkupLeader leader = OdPrcMarkupLeader.createObject();

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray arrPnts = new OdPrcFloatPointArray();
      arrPnts.resize(2);
      arrPnts[0].set(2, 0, 0);
      arrPnts[1].set(2, 1, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      arrPnts.resize(4);
      arrPnts[0].set(1.6, 0, 0);
      arrPnts[1].set(2.4, 0, 0);
      arrPnts[2].set(2, 0.5, 0);
      arrPnts[3].set(1.6, 0, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader);
      return leaders;
    }

    public static OdPrcMarkupLeaderPtrArray CreateDatumTargetLeader(OdPrcFileStructure pCurFS)
    {
      //Create Leader
      OdPrcMarkupLeaderPtrArray leaders = new OdPrcMarkupLeaderPtrArray();
      OdPrcMarkupLeader leader = OdPrcMarkupLeader.createObject();

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor greenCol = new OdPrcRgbColor();
      greenCol.set(0, 1, 0);
      pFirstMkpTess.setColor(greenCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray arrPnts = new OdPrcFloatPointArray();
      arrPnts.resize(2);
      arrPnts[0].set(2, 0, 0);
      arrPnts[1].set(2, 1, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      arrPnts[0].set(1.5, -0.5, 0);
      arrPnts[1].set(2.5, 0.5, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      arrPnts[0].set(1.5, 0.5, 0);
      arrPnts[1].set(2.5, -0.5, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline)pCurMkpTess).setPoints(arrPnts) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader);
      return leaders;
    }

    public static void FillTopoMarkups(OdPrcFileStructure newStructure, OdPrcProductOccurrence newProductOccurrence, OdPrcMarkupTess mTess, OdPrcMarkup.MarkupType type, OdPrcMarkup.MarkupSubType subtype, OdPrcMarkupLeaderPtrArray arr_leader, OdPrcName name)
    {
      OdPrcObjectId un_id;

      //Create Leader
      OdPrcObjectIdArray leaders = newProductOccurrence.markups().leaders();
      leaders.resize((uint)arr_leader.Count);
      for (int f = 0; f < arr_leader.Count; ++f)
      {
        newStructure.addObject(arr_leader[f]);
        leaders[f] = arr_leader[f].objectId();
      }
      if (leaders.Count > 0)
      {
        newStructure.fileStructureTessellation().tessellations().Add(arr_leader[0].tessellation());
        if (leaders.Count == 2)
        {
          newStructure.fileStructureTessellation().tessellations().Add(arr_leader[1].tessellation());
        }
      }
      OdPrcObjectIdArray arr = newProductOccurrence.markups().markups();
      OdPrcMarkup markup = OdPrcMarkup.createObject();
      newStructure.addObject(markup);
      markup.setname(name);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(markup.setType(type, subtype) == OdResult.eOk);
      markup.settessellation(mTess);
      if (leaders.Count > 0)
      {
        un_id = leaders[0];
        markup.leader().Add(un_id);
        if (leaders.Count == 2)
        {
          un_id = leaders[1];
          markup.leader().Add(un_id);
        }
      }
      arr.Add(markup.objectId());

      OdPrcObjectIdArray arr_entity = newProductOccurrence.markups().annotationEntities();
      OdPrcAnnotationItem ann_item = OdPrcAnnotationItem.createObject();

      ann_item.setname(name);
      un_id = markup.objectId();
      ann_item.setmarkup(un_id);
      newStructure.addObject(ann_item);
      arr_entity.Add(ann_item.objectId());

      newStructure.fileStructureTessellation().tessellations().Add(mTess);
    }
  }
}
