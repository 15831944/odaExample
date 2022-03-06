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
using OdPrcCreateSwigMgd.Samples.OdBrepModelSamples;
using Teigha.Core;
using Teigha.PRC;
using Teigha.TD;

namespace OdPrcCreateSwigMgd.Samples.OdMarkupSamples
{
  public class OdMarkupExample_MarkupViewExample : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "View example with brep cylinder and markups";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      OdPrcFile pFile = CreateViewExample();
      // export prc
      pFile.writeFile(pPrcStream);
    }

    public static OdPrcSurface createCylinderforView()
    {
      OdPrcCylinder pPrcCylinder = OdPrcCylinder.createObject();
      {
        OdPrcContentSurface  srfContent = pPrcCylinder.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named cylinder in srfContent");

        pPrcCylinder.setUVParameterization( new OdPrcUVParameterization(0, Globals.Oda2PI, 0, 9));
        // can add transformation if needed here
        // TBD

        pPrcCylinder.setRadius(2);

        OdPrcTransformation3d transform = new OdPrcTransformation3d();
        OdGeMatrix3d geMatrix = new OdGeMatrix3d();
        geMatrix.setCoordSystem(new OdGePoint3d(0, 0, 0), new OdGeVector3d(1, 0, 0), new OdGeVector3d(0, 0, -1), new OdGeVector3d(0, 1, 0));
        //transform.set(geMatrix);
        transform.set(geMatrix);
        pPrcCylinder.setTransformation(transform);

      }
      return pPrcCylinder;
    }

    public static OdPrcProductOccurrence CreateTopologyCommonForBrepCylinder(OdPrcFileStructure  FSt, OdGeExtents3d extents)
    {
      OdPrcProductOccurrence pRootPO = FSt.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
      OdPrcProductOccurrence newProductOccurrence = OdPrcCreateTopologyHelper.createProductOccurrence(FSt, pRootPO);
      OdPrcPartDefinition newDefinition = OdPrcCreateTopologyHelper.createPartDefinition(FSt, newProductOccurrence);

      // bounding box
      newDefinition.boundingBox().setbox(extents);

      // create brep model
      OdPrcBrepModel newBrep = OdPrcBrepModel.createObject();
      FSt.addObject(newBrep);
      newBrep.setIsClosed(true);
      newDefinition.representationItem().Add(newBrep.objectId());

      // create Brep Data
      OdPrcBrepData newBrepData = OdPrcBrepData.createObject();
      FSt.addObject(newBrepData);
      newBrepData.boundingBox().setbox(extents);
      newBrepData.contentBody().setBoundingBoxBehaviour(2);

      // set reference to this body in representation item
      newBrep.setReferenceToBody(newBrepData);

      // file structure geometry section
      OdPrcTopoContext newTopoContext = OdPrcCreateTopologyHelper.createTopoContext(FSt);
      newTopoContext.bodies().Add(newBrepData.objectId());
      return newProductOccurrence;
    }

    public static void CreateHeightDimensionMarkup(OdPrcMarkup markup)
    {
      markup.setType(OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Distance);

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor redCol = new OdPrcRgbColor();
      redCol.set(1, 0, 0);
      pFirstMkpTess.setColor(redCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 5;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont ) pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(2.5, 4, 0);
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("9.000", 3, 2) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(3);
      pntsArr[0].set(3, 9, 0);
      pntsArr[1].set(3.1, 8.8, 0);
      pntsArr[2].set(2.9, 8.8, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles ) pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      pntsArr[0].set(3, 0, 0);
      pntsArr[1].set(3.1, 0.2, 0);
      pntsArr[2].set(2.9, 0.2, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles ) pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr.resize(2);
      pntsArr[0].set(3, 0.2, 0);
      pntsArr[1].set(3, 3.5, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline ) pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr[0].set(3, 8.8, 0);
      pntsArr[1].set(3, 5.5, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline ) pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      OdPrcFileStructure pCurFS = markup.objectId().database() as OdPrcFileStructure;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pCurFS != null);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      markup.settessellation(mTess);
    }

    public static void CreateLengthDimensionMarkup(OdPrcMarkup markup)
    {
      markup.setType(OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Distance);

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor redCol = new OdPrcRgbColor();
      redCol.set(1, 0, 0);
      pFirstMkpTess.setColor(redCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 5;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont ) pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(-1.5, 10, 0);
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("4.000", 3, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(3);
      pntsArr[0].set(-2, 10, 0);
      pntsArr[1].set(-1.8, 10.1, 0);
      pntsArr[2].set(-1.8, 9.9, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles ) pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      pntsArr[0].set(2, 10, 0);
      pntsArr[1].set(1.8, 10.1, 0);
      pntsArr[2].set(1.8, 9.9, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles ) pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr.resize(2);
      pntsArr[0].set(-1.8, 10, 0);
      pntsArr[1].set(-1.5, 10, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline ) pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr[0].set(1.8, 10, 0);
      pntsArr[1].set(1.5, 10, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline ) pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      OdPrcFileStructure pCurFS = markup.objectId().database() as OdPrcFileStructure;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pCurFS != null);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      markup.settessellation(mTess);
    }

    public static void CreateDiameterDimensionMarkup(OdPrcMarkup markup)
    {
      markup.setType(OdPrcMarkup.MarkupType.kDimension, OdPrcMarkup.MarkupSubType.kDimension_Angle);

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor redCol = new OdPrcRgbColor();
      redCol.set(1, 0, 0);
      pFirstMkpTess.setColor(redCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      OdPrcFontKeysSameFont font = new OdPrcFontKeysSameFont();
      font.setFontName("Arial");
      font.setCharSet(0);
      font.fontKeys().resize(1);
      font.fontKeys()[0].font_size = 4;
      font.fontKeys()[0].attributes = 1;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont ) pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(-1.5, 9, -3);
      OdGeMatrix3d matr = new OdGeMatrix3d();
      OdGeVector3d vecX = new OdGeVector3d(0, 0, -1);
      OdGeVector3d vecY = new OdGeVector3d(1, 0, 0);
      matr.setCoordSystem(origP, vecX, vecY, vecX.crossProduct(vecY));
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setMatrix(matr);
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("\u2300", 1, 1) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufFont.createObject());
      font.fontKeys()[0].font_size = 5;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont ) pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      origP.set(-0.4, 9, -3.1);
      vecX.set(1, 0, 0);
      vecY.set(0, 0, -1);
      matr.setCoordSystem(origP, vecX, vecY, vecX.crossProduct(vecY));
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setMatrix(matr);
      OdPrcMarkupTessBufText pBufText1 = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText1.setText("4.00", 2, (float)1.5) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setNextInBlock(pBufText1);
      // end matrix

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(3);
      pntsArr[0].set(-2, 9, -3);
      pntsArr[1].set(-1.8, 9, -3.1);
      pntsArr[2].set(-1.8, 9, -2.9);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles ) pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufTriangles.createObject());
      pntsArr[0].set(2, 9, -3);
      pntsArr[1].set(1.8, 9, -3.1);
      pntsArr[2].set(1.8, 9, -2.9);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufTriangles ) pCurMkpTess).setTriangles(pntsArr) == OdResult.eOk);

      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr.resize(2);
      pntsArr[0].set(-1.8, 9, -3);
      pntsArr[1].set(1.8, 9, -3);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline ) pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      OdPrcFileStructure pCurFS = markup.objectId().database() as OdPrcFileStructure;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pCurFS != null);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      markup.settessellation(mTess);
    }

    public static void CreateHeightDimensionLeaders(OdPrcObjectIdArray leaders, OdPrcFileStructure newStructure)
    {
      //Create Leader
      OdPrcMarkupLeader leader = OdPrcMarkupLeader.createObject();
      newStructure.addObject(leader);

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor redCol = new OdPrcRgbColor();
      redCol.set(1, 0, 0);
      pFirstMkpTess.setColor(redCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(2);
      pntsArr[0].set(2, 0, 0);
      pntsArr[1].set(4, 0, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline ) pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, newStructure) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader.objectId());
      newStructure.fileStructureTessellation().tessellations().Add(mTess);

      leader = OdPrcMarkupLeader.createObject();
      newStructure.addObject(leader);

      pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      pFirstMkpTess.setColor(redCol);

      pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr[0].set(2, 9, 0);
      pntsArr[1].set(4, 9, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline ) pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, newStructure) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader.objectId());
      newStructure.fileStructureTessellation().tessellations().Add(mTess);
    }

    public static void CreateLengthDimensionLeaders(OdPrcObjectIdArray leaders, OdPrcFileStructure newStructure)
    {
      //Create Leader
      OdPrcMarkupLeader leader = OdPrcMarkupLeader.createObject();
      newStructure.addObject(leader);

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor redCol = new OdPrcRgbColor();
      redCol.set(1, 0, 0);
      pFirstMkpTess.setColor(redCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(2);
      pntsArr[0].set(-2, 9, 0);
      pntsArr[1].set(-2, 11, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline ) pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, newStructure) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader.objectId());
      newStructure.fileStructureTessellation().tessellations().Add(mTess);

      leader = OdPrcMarkupLeader.createObject();
      newStructure.addObject(leader);

      pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      pFirstMkpTess.setColor(redCol);

      pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr[0].set(2, 9, 0);
      pntsArr[1].set(2, 11, 0);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline ) pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, newStructure) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader.objectId());
      newStructure.fileStructureTessellation().tessellations().Add(mTess);
    }

    public static void CreateDiameterDimensionLeaders(OdPrcObjectIdArray leaders, OdPrcFileStructure newStructure)
    {
      //Create Leader
      OdPrcMarkupLeader leader = OdPrcMarkupLeader.createObject();
      newStructure.addObject(leader);

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      OdPrcRgbColor redCol = new OdPrcRgbColor();
      redCol.set(1, 0, 0);
      pFirstMkpTess.setColor(redCol);

      OdPrcMarkupTessBuf pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      OdPrcFloatPointArray pntsArr = new OdPrcFloatPointArray();
      pntsArr.resize(2);
      pntsArr[0].set(-2, 9, 0);
      pntsArr[1].set(-2, 9, -4);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline ) pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, newStructure) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader.objectId());
      newStructure.fileStructureTessellation().tessellations().Add(mTess);

      leader = OdPrcMarkupLeader.createObject();
      newStructure.addObject(leader);

      pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      pFirstMkpTess.setColor(redCol);

      pCurMkpTess = pFirstMkpTess.setNext(OdPrcMarkupTessBufPolyline.createObject());
      pntsArr[0].set(2, 9, 0);
      pntsArr[1].set(2, 9, -4);
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufPolyline ) pCurMkpTess).setPoints(pntsArr) == OdResult.eOk);

      mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, newStructure) == OdResult.eOk);
      mTess.setLabel("test");

      leader.settessellation(mTess);
      leaders.Add(leader.objectId());
      newStructure.fileStructureTessellation().tessellations().Add(mTess);
    }

    public static void AddViewExample(OdPrcFileStructure newStructure, OdPrcProductOccurrence newProductOccurrence)
    {
      OdPrcObjectId un_id;
      OdPrcName name = new OdPrcName();
      name.setName("test");

      //Create Leader
      OdPrcObjectIdArray  leaders = newProductOccurrence.markups().leaders();
      CreateHeightDimensionLeaders(leaders, newStructure);
      CreateLengthDimensionLeaders(leaders, newStructure);
      CreateDiameterDimensionLeaders(leaders, newStructure);

      OdPrcObjectIdArray  arr = newProductOccurrence.markups().markups();
      OdPrcMarkup heightDimensionMarkup = OdPrcMarkup.createObject();
      newStructure.addObject(heightDimensionMarkup);
      CreateHeightDimensionMarkup(heightDimensionMarkup);
      un_id = leaders[0];
      heightDimensionMarkup.leader().Add(un_id);
      un_id = leaders[1];
      heightDimensionMarkup.leader().Add(un_id);

      OdPrcMarkup lengthDimensionMarkup = OdPrcMarkup.createObject();
      newStructure.addObject(lengthDimensionMarkup);
      CreateLengthDimensionMarkup(lengthDimensionMarkup);
      un_id = leaders[2];
      lengthDimensionMarkup.leader().Add(un_id);
      un_id = leaders[3];
      lengthDimensionMarkup.leader().Add(un_id);

      OdPrcMarkup diameterDimensionMarkup = OdPrcMarkup.createObject();
      newStructure.addObject(diameterDimensionMarkup);
      CreateDiameterDimensionMarkup(diameterDimensionMarkup);
      un_id = leaders[4];
      diameterDimensionMarkup.leader().Add(un_id);
      un_id = leaders[5];
      diameterDimensionMarkup.leader().Add(un_id);

      arr.Add(heightDimensionMarkup.objectId());
      arr.Add(lengthDimensionMarkup.objectId());
      arr.Add(diameterDimensionMarkup.objectId());

      OdPrcObjectIdArray  arr_entity = newProductOccurrence.markups().annotationEntities();

      OdPrcAnnotationSet annSetFront = OdPrcAnnotationSet.createObject();
      annSetFront.setname(name);
      newStructure.addObject(annSetFront);
      OdPrcObjectIdArray  arr_front_ann = annSetFront.entities();

      {
        OdPrcAnnotationItem annForHeight = OdPrcAnnotationItem.createObject();
        annForHeight.setname(name);
        un_id = heightDimensionMarkup.objectId();
        annForHeight.setmarkup(un_id);
        newStructure.addObject(annForHeight);
        arr_front_ann.Add(annForHeight.objectId());
      }
      {
        OdPrcAnnotationItem annForLength = OdPrcAnnotationItem.createObject();
        annForLength.setname(name);
        un_id = lengthDimensionMarkup.objectId();
        annForLength.setmarkup(un_id);
        newStructure.addObject(annForLength);
        arr_front_ann.Add(annForLength.objectId());
      }
      arr_entity.Add(annSetFront.objectId());

      OdPrcAnnotationSet annSetTop = OdPrcAnnotationSet.createObject();
      annSetTop.setname(name);
      newStructure.addObject(annSetTop);
      OdPrcObjectIdArray  arr_top_ann = annSetTop.entities();
      {
        OdPrcAnnotationItem annForDiameter = OdPrcAnnotationItem.createObject();
        annForDiameter.setname(name);
        un_id = diameterDimensionMarkup.objectId();
        annForDiameter.setmarkup(un_id);
        newStructure.addObject(annForDiameter);
        arr_top_ann.Add(annForDiameter.objectId());
      }
      arr_entity.Add(annSetTop.objectId());

      newStructure.fileStructureTessellation().tessellations().Add(heightDimensionMarkup.tessellation());
      newStructure.fileStructureTessellation().tessellations().Add(lengthDimensionMarkup.tessellation());
      newStructure.fileStructureTessellation().tessellations().Add(diameterDimensionMarkup.tessellation());

      OdPrcObjectIdArray  arr_view = newProductOccurrence.annotationViews();
      OdPrcView frontView = OdPrcView.createObject();
      name.setName("frontView");
      frontView.setname(name);
      un_id = annSetFront.objectId();
      frontView.annotations().Add(un_id);

      OdPrcPlane frontPlane = OdPrcPlane.createObject();
      OdPrcContentSurface content_suface = new OdPrcContentSurface();
      content_suface.baseGeometry().setBaseInformation(false);
      frontPlane.setcontentSurface(content_suface);
      frontView.setplane(frontPlane);
      frontView.setIsAnnotationView(true);

      newStructure.addObject(frontView);
      arr_view.Add(frontView.objectId());

      OdPrcView topView = OdPrcView.createObject();
      name.setName("topView");
      topView.setname(name);
      un_id = annSetTop.objectId();
      topView.annotations().Add(un_id);

      OdPrcPlane topPlane = OdPrcPlane.createObject();
      content_suface.baseGeometry().setBaseInformation(false);
      topPlane.setcontentSurface(content_suface);
      OdPrcTransformation3d transform = new OdPrcTransformation3d();
      OdGeMatrix3d geMatrix = new OdGeMatrix3d();
      geMatrix.setCoordSystem(new OdGePoint3d(0, 9, 0), new OdGeVector3d(1, 0, 0), new OdGeVector3d(0, 0, -1), new OdGeVector3d(0, 1, 0));
      transform.set(geMatrix);
      topPlane.setTransformation(transform);
      topView.setplane( topPlane);
      topView.setIsAnnotationView(true);
      newStructure.addObject(topView);
      arr_view.Add(topView.objectId());
    }

    public static OdPrcFile CreateViewExample()
    {
      // common
      OdGeExtents3d extents = new OdGeExtents3d();
      extents.addPoint(new OdGePoint3d(0, 0, 0));
      extents.addPoint(new OdGePoint3d(1, 1, 1));
      OdPrcFile pFile = OdPrcCreateTopologyHelper.createTopologyCommon();
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure newStructure = fileStructures[fileStructures.Count - 1];

      CreateTopologyCommonForBrepCylinder(newStructure, extents);

      // Add line style to globals
      OdBrepModelExample.addLineStyleForBrep(newStructure, 1.0f, 0.0f, 0.0f);

      // Add graphic
      OdBrepModelExample.addGraphicDataToBrep(newStructure);

      // fill it with Brep Data
      OdPrcTopoContextPtrArray topologicalContext = newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext();
      OdPrcTopoContext newTopoContext = topologicalContext[topologicalContext.Count - 1];
      OdPrcObjectIdArray bodies = newTopoContext.bodies();
      OdPrcBrepData brepData = bodies[bodies.Count - 1].safeOpenObjectOdRx(Teigha.PRC.OpenMode.kForWrite, false) as OdPrcBrepData;
      OdBrepModelExample.FillTopoBrepFace(brepData, createCylinderforView());

      OdPrcProductOccurrence pRootPO = newStructure.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
      OdPrcProductOccurrence pPO = OdPrcCreateTopologyHelper.createProductOccurrence(newStructure, pRootPO);
      OdPrcPartDefinition pPD = OdPrcCreateTopologyHelper.createPartDefinition(newStructure, pPO);
      pPD.boundingBox().setbox(extents);

      AddViewExample(newStructure, pPO);

      return pFile;
    }
  }
}
