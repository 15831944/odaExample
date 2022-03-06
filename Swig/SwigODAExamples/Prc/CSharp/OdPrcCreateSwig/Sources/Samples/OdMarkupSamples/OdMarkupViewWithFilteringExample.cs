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

namespace OdPrcCreateSwigMgd.Samples.OdMarkupSamples
{
  public class OdMarkupExample_MarkupViewWithFilteringExample : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "View example with filtering objects";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      OdPrcFile pFile = CreateViewWithFilteringExample(filterByLayer: false);
      // export prc
      pFile.writeFile(pPrcStream);
    }

    OdPrcFile CreateViewWithFilteringExample(bool filterByLayer)
    {
      // common
      OdGeExtents3d extents = new OdGeExtents3d();
      extents.addPoint(new OdGePoint3d(-10, -10, -10));
      extents.addPoint(new OdGePoint3d(10, 10, 10));
      OdPrcFile pFile = OdPrcCreateTopologyHelper.createTopologyCommon();
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure newStructure = fileStructures[fileStructures.Count - 1];

      OdPrcObjectIdArray getStartRootOccurrences = pFile.modelFileData().getStartRootOccurrences();
      OdPrcProductOccurrence rootOccurrence = getStartRootOccurrences[getStartRootOccurrences.Count - 1].openObject((Teigha.PRC.OpenMode.kForWrite)) as OdPrcProductOccurrence;
      rootOccurrence.name().setName("rootPO");

      // product occurrence for torus
      OdPrcProductOccurrence newPOBrep1;
      {
        newPOBrep1 = OdMarkupExample_MarkupViewExample.CreateTopologyCommonForBrepCylinder(newStructure, extents);
        newPOBrep1.name().setName("TorusPO");

        // Add color
        OdPrcCreateTopologyHelper.addColorToBaseWithGraphics(newStructure, newPOBrep1, 1.0, 0.0, 0.0);

        // fill it with Brep Data
        OdPrcTopoContextPtrArray topologicalContext = newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext();
        OdPrcTopoContext newTopoContext = topologicalContext[topologicalContext.Count - 1];
        OdPrcObjectIdArray bodies = newTopoContext.bodies();
        OdPrcBrepData brepData = bodies[bodies.Count - 1].safeOpenObjectOdRx(Teigha.PRC.OpenMode.kForWrite,false) as OdPrcBrepData;;
        OdBrepModelExample.FillTopoBrepFace(brepData, CreateTorusForMkpView());

        OdPrcObjectIdArray partDefinition = newStructure.fileStructureTree().partDefinition();
        OdPrcPartDefinition newDefinition = partDefinition[partDefinition.Count - 1].safeOpenObject((Teigha.PRC.OpenMode.kForWrite)) as OdPrcPartDefinition;
        OdPrcObjectIdArray representationItem = newDefinition.representationItem();
        OdPrcBrepModel pBrepModel1 = representationItem[representationItem.Count - 1].openObject((Teigha.PRC.OpenMode.kForWrite)) as OdPrcBrepModel;
        pBrepModel1.name().setName("TorusBM");
        OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBrepModel1.updateIsClosedFlag() == OdResult.eOk);
      }

      // product occurrence for sphere
      OdPrcProductOccurrence newPOBrep2;
      {
        newPOBrep2 = OdMarkupExample_MarkupViewExample.CreateTopologyCommonForBrepCylinder(newStructure, extents);
        newPOBrep2.name().setName("SpherePO");

        // Add color
        OdPrcCreateTopologyHelper.addColorToBaseWithGraphics(newStructure, newPOBrep2, 0.0, 1.0, 0.0);

        // fill it with Brep Data
        OdPrcTopoContextPtrArray topologicalContext = newStructure.fileStructureGeometry().fileStructureExactGeometry().topologicalContext();
        OdPrcTopoContext newTopoContext = topologicalContext[topologicalContext.Count - 1];

        OdPrcObjectIdArray bodies = newTopoContext.bodies();
        OdPrcBrepData brepData = bodies[bodies.Count - 1].safeOpenObjectOdRx(Teigha.PRC.OpenMode.kForWrite,false) as OdPrcBrepData;
        OdBrepModelExample.FillTopoBrepFace(brepData, CreateSphereForMkpView());

        OdPrcObjectIdArray partDefinition = newStructure.fileStructureTree().partDefinition();
        OdPrcPartDefinition newDefinition = partDefinition[partDefinition.Count - 1].safeOpenObject((Teigha.PRC.OpenMode.kForWrite)) as OdPrcPartDefinition;

        OdPrcObjectIdArray representationItem = newDefinition.representationItem();
        OdPrcBrepModel pBrepModel2 = representationItem[representationItem.Count - 1].openObject((Teigha.PRC.OpenMode.kForWrite)) as OdPrcBrepModel;
        pBrepModel2.name().setName("SphereBM");
        OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBrepModel2.updateIsClosedFlag() == OdResult.eOk);
      }

      TextInfo textInfo = new TextInfo();
      textInfo.text = "Sphere and Torus";
      OdGeMatrix3d geMatrix = new OdGeMatrix3d();
      geMatrix.setTranslation(new OdGeVector3d(0, 5.5, -3.5));
      geMatrix *= OdGeMatrix3d.rotation(Globals.OdaPI + Globals.OdaPI2, OdGeVector3d.kZAxis);
      geMatrix *= OdGeMatrix3d.rotation(Globals.OdaPI2, OdGeVector3d.kXAxis);
      textInfo.matr = geMatrix;
      textInfo.textWidth = 6;
      textInfo.textHeight = 2;
      textInfo.color = new OdPrcRgbColor(0.0, 0.0, 1.0);
      textInfo.behBitField = PRC_Globals.PRC_GRAPHICS_Show;
      CreateTextMarkup(rootOccurrence, textInfo);

      AddViewWithFilteringExample(rootOccurrence, newPOBrep1, newPOBrep2);

      return pFile;
    }

    OdPrcAnnotationItem CreateTextMarkup(OdPrcProductOccurrence newProductOccurrence, TextInfo textInfo)
    {
      OdPrcFileStructure pCurFS = (OdPrcFileStructure)newProductOccurrence.objectId().database();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pCurFS != null);

      OdPrcMarkup pMkp = OdPrcMarkup.createObject();
      pCurFS.addObject(pMkp);

      pMkp.setBehaviourBitField(textInfo.behBitField);
      pMkp.setType(OdPrcMarkup.MarkupType.kText, OdPrcMarkup.MarkupSubType.kUnknownSubtype);

      OdPrcMarkupTessBufColor pFirstMkpTess = OdPrcMarkupTessBufColor.createObject();
      pFirstMkpTess.setColor(textInfo.color);

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
      ((OdPrcMarkupTessBufMatrix) pCurMkpTess).setMatrix(textInfo.matr);
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText(textInfo.text, (float)textInfo.textWidth, (float)textInfo.textHeight) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix) pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      pMkp.settessellation(mTess);
      pCurFS.fileStructureTessellation().tessellations().Add(mTess);

      OdPrcAnnotationItem pAnn = OdPrcAnnotationItem.createObject();
      pCurFS.addObject(pAnn);
      pAnn.setmarkup(pMkp.objectId());
      newProductOccurrence.markups().markups().Add(pMkp.objectId());
      newProductOccurrence.markups().annotationEntities().Add(pAnn.objectId());
      return pAnn;
    }

    void AddViewWithFilteringExample(OdPrcProductOccurrence newPO, OdPrcProductOccurrence newPOBrep1, OdPrcProductOccurrence newPOBrep2)
    {
      OdPrcFileStructure pCurFS = (OdPrcFileStructure)newPO.objectId().database();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pCurFS != null);

      OdPrcName name = new OdPrcName();
      name.setName("test");
      OdPrcObjectIdArray arr_view = newPO.annotationViews();
      OdPrcView torusView = OdPrcView.createObject();
      name.setName("TorusView");
      torusView.setname(name);

      OdPrcPlane torusPlane = OdPrcPlane.createObject();
      OdPrcContentSurface content_suface = new OdPrcContentSurface();
      OdPrcTransformation3d transform = new OdPrcTransformation3d();
      OdGeMatrix3d geMatrix = new OdGeMatrix3d();
      geMatrix.setTranslation(new OdGeVector3d(0, 1.3, -2));
      geMatrix *= OdGeMatrix3d.rotation(Globals.OdaPI + Globals.OdaPI2, OdGeVector3d.kZAxis);
      geMatrix *= OdGeMatrix3d.rotation(Globals.OdaPI2, OdGeVector3d.kXAxis);
      transform.set(geMatrix);
      torusPlane.setTransformation(transform);
      torusPlane.setUVParameterization(new OdPrcUVParameterization(OdPrcDomain.kInfinite));
      content_suface.baseGeometry().setBaseInformation(false);
      torusPlane.setcontentSurface(content_suface);
      torusView.setplane(torusPlane);
      torusView.setIsAnnotationView(true);
      torusView.setBehaviourBitField(PRC_Globals.PRC_GRAPHICS_FatherHeritShow);

      pCurFS.addObject(torusView);
      arr_view.Add(torusView.objectId());

      // markup for invisibility sphere
      OdPrcMarkupLinkedItem pMkpLIS = OdPrcMarkupLinkedItem.createObject();
      pCurFS.addObject(pMkpLIS);
      newPO.markups().linkedItem().Add(pMkpLIS.objectId());
      pMkpLIS.referencedProductOccurrence().setreferenceOnPRCBase(newPOBrep2.objectId());
      OdPrcObjectIdArray representationItem = newPOBrep2.getPartDefinition().representationItem();
      pMkpLIS.referenceData().setreferenceOnPRCBase(representationItem[representationItem.Count - 1]);
      pMkpLIS.setBehaviourBitField(PRC_Globals.PRC_GRAPHICS_FatherHeritShow);
      torusView.linkedItems().Add(pMkpLIS.objectId());
      // end of markup

      // create text
      TextInfo textInfo = new TextInfo();
      textInfo.text = "Torus";
      textInfo.matr = geMatrix;
      textInfo.textWidth = 2.3;
      textInfo.textHeight = 1.3;
      textInfo.color = new OdPrcRgbColor(1.0, 1, 0.0);
      textInfo.behBitField = PRC_Globals.PRC_GRAPHICS_FatherHeritShow;
      torusView.annotations().Add(CreateTextMarkup(newPOBrep1, textInfo).objectId());

      // camera configuration
      OdPrcCamera pCam1 = OdPrcCamera.createObject();
      pCurFS.addObject(pCam1);
      pCam1.location().set(-5.92978, -2.39579, 1.3594);
      pCam1.lookAt().set(0, 0, 0);
      pCam1.up().set(0.192772, 0.0778851, 0.978148);
      pCam1.setXFov(3.26917);
      pCam1.setYFov(3.26917);
      pCam1.setZFar(13.0767);
      pCam1.setOrthographic(true);
      pCam1.setAspectRatio(1.0);
      pCam1.setZNear(0.0);
      OdPrcSceneDisplayParameters pSDP1 = OdPrcSceneDisplayParameters.createObject();
      pCurFS.addObject(pSDP1);
      pSDP1.setcamera(pCam1.objectId());
      torusView.setsceneDisplayParameters(pSDP1.objectId());

      OdPrcView sphereView = OdPrcView.createObject();
      name.setName("SphereView");
      sphereView.setname(name);

      OdPrcPlane spherePlane = OdPrcPlane.createObject();
      content_suface.baseGeometry().setBaseInformation(false);
      spherePlane.setcontentSurface(content_suface);
      geMatrix.setTranslation(new OdGeVector3d(0, 6.1, -3.0));
      transform.set(geMatrix);
      spherePlane.setTransformation(transform);
      spherePlane.setUVParameterization(new OdPrcUVParameterization(OdPrcDomain.kInfinite));
      sphereView.setplane(spherePlane);
      sphereView.setIsAnnotationView(true);
      sphereView.setBehaviourBitField(PRC_Globals.PRC_GRAPHICS_FatherHeritShow);

      pCurFS.addObject(sphereView);
      arr_view.Add(sphereView.objectId());

      // markup for invisibility torus
      OdPrcMarkupLinkedItem pMkpLIT = OdPrcMarkupLinkedItem.createObject();
      pCurFS.addObject(pMkpLIT);
      newPO.markups().linkedItem().Add(pMkpLIT.objectId());
      pMkpLIT.referencedProductOccurrence().setreferenceOnPRCBase(newPOBrep1.objectId());

      representationItem = newPOBrep1.getPartDefinition().representationItem();
      pMkpLIT.referenceData().setreferenceOnPRCBase(representationItem[representationItem.Count - 1]);
      pMkpLIT.setBehaviourBitField(PRC_Globals.PRC_GRAPHICS_FatherHeritShow);
      sphereView.linkedItems().Add(pMkpLIT.objectId());
      // end of markup

      // create text
      textInfo.text = "Sphere";
      textInfo.matr = geMatrix;
      textInfo.textWidth = 2.3;
      textInfo.textHeight = 1.3;
      textInfo.color = new OdPrcRgbColor(0.0, 1.0, 1.0);
      textInfo.behBitField = PRC_Globals.PRC_GRAPHICS_FatherHeritShow;
      sphereView.annotations().Add(CreateTextMarkup(newPOBrep2, textInfo).objectId());

      // camera configuration
      OdPrcCamera pCam2 = OdPrcCamera.createObject();
      pCurFS.addObject(pCam2);
      pCam2.location().set(-5.92978, 2.60421, 1.3594);
      pCam2.lookAt().set(0, 5, 0);
      pCam2.up().set(0.192772, 0.0778851, 0.978148);
      pCam2.setXFov(4.0);
      pCam2.setYFov(4.0);
      pCam2.setZFar(13.0767);
      pCam2.setOrthographic(true);
      pCam2.setAspectRatio(1.0);
      pCam2.setZNear(0.0);
      OdPrcSceneDisplayParameters pSDP2 = OdPrcSceneDisplayParameters.createObject();
      pCurFS.addObject(pSDP2);
      pSDP2.setcamera(pCam2.objectId());
      sphereView.setsceneDisplayParameters(pSDP2.objectId());
    }

    OdPrcSurface CreateTorusForMkpView()
    {
      OdPrcTorus pPrcTorus = OdPrcTorus.createObject();
      {
        OdPrcContentSurface srfContent = pPrcTorus.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named torus in srfContent");

        pPrcTorus.setUVParameterization(new OdPrcUVParameterization(0, Globals.Oda2PI, 0, Globals.Oda2PI));

        // can add transformation if needed here
        // TBD

        pPrcTorus.setMajorRadius(1.5);
        pPrcTorus.setMinorRadius(0.75);
      }
      return pPrcTorus;
    }

    OdPrcSurface CreateSphereForMkpView()
    {
      OdPrcSphere pPrcSphere = OdPrcSphere.createObject();
      {
        OdPrcContentSurface srfContent = pPrcSphere.contentSurface();

        // set name
        srfContent.baseGeometry().name().setName("named sphere in srfContent");
        pPrcSphere.setUVParameterization(new OdPrcUVParameterization(0.0, Globals.Oda2PI, -Globals.OdaPI / 2, Globals.OdaPI / 2));

        // can add transformation if needed here
        OdPrcTransformation3d trans = new OdPrcTransformation3d();
        trans.set(OdGeMatrix3d.translation(new OdGeVector3d(0.0, 5.0, 0.0)));
        pPrcSphere.setTransformation(trans);
        // TBD

        pPrcSphere.setRadius(2.0);
      }
      return pPrcSphere;
    }

    public class TextInfo
    {
      public String text;
      public OdGeMatrix3d matr;
      public double textWidth;
      public double textHeight;
      public OdPrcRgbColor color;
      public UInt16 behBitField;

      public TextInfo()
      {
        textWidth = 1.0;
        textHeight = 1.0;
        behBitField = PRC_Globals.PRC_GRAPHICS_Show;
      }
    };
  }
}
