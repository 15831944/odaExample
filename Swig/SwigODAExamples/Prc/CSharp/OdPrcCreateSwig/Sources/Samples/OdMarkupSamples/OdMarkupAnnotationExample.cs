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
  public class OdMarkupExample_MarkupAnnotationExample : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "Annotation example";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      OdPrcFile pFile = CreateAnnotationExample();
      // export prc
      pFile.writeFile(pPrcStream);
    }

    public static void CreateAnnItemMarkup(OdPrcMarkup markup)
    {
      markup.setType(OdPrcMarkup.MarkupType.kText);

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
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont ) pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(0, 0, 0);
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setMatrix(OdGeMatrix3d.translation(origP.asVector()));
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("Annotation Item", 3, 2) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      OdPrcFileStructure pCurFS = markup.objectId().database() as OdPrcFileStructure as OdPrcFileStructure;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pCurFS != null);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      markup.settessellation(mTess);
    }

    public static void CreateAnnItem1ForSetMarkup(OdPrcMarkup markup)
    {
      markup.setType(OdPrcMarkup.MarkupType.kText);

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
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont ) pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGePoint3d origP = new OdGePoint3d(0, 0, -1);
      OdGeMatrix3d matr = new OdGeMatrix3d();
      matr.setCoordSystem(origP, OdGeVector3d.kXAxis, new OdGeVector3d(0, 0, -1), new OdGeVector3d(0, 1, 0));
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setMatrix(matr);
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("Annotation Item.1", 3, 2) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      OdPrcFileStructure pCurFS = markup.objectId().database() as OdPrcFileStructure;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pCurFS != null);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      markup.settessellation(mTess);
    }

    public static void CreateAnnItem2ForSetMarkup(OdPrcMarkup markup)
    {
      markup.setType(OdPrcMarkup.MarkupType.kText);

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
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(((OdPrcMarkupTessBufFont ) pCurMkpTess).setFont(font) == OdResult.eOk);

      // matrix
      pCurMkpTess = pCurMkpTess.setNext(OdPrcMarkupTessBufMatrix.createObject());
      OdGeMatrix3d matr = new OdGeMatrix3d();
      matr.setCoordSystem(OdGePoint3d.kOrigin, OdGeVector3d.kXAxis, new OdGeVector3d(0, 0, -1), new OdGeVector3d(0, 1, 0));
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setMatrix(matr);
      OdPrcMarkupTessBufText pBufText = OdPrcMarkupTessBufText.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pBufText.setText("Annotation Item.2", 3, 2) == OdResult.eOk);
      ((OdPrcMarkupTessBufMatrix ) pCurMkpTess).setNextInBlock(pBufText);
      // end matrix

      OdPrcFileStructure pCurFS = markup.objectId().database() as OdPrcFileStructure;
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(pCurFS != null);

      OdPrcMarkupTess mTess = OdPrcMarkupTess.createObject();
      OdCreationNetSwigExampleLib.Helpers.ODA_VERIFY(mTess.setFromOdPrcMarkupTessBuf(pFirstMkpTess, pCurFS) == OdResult.eOk);
      mTess.setLabel("test");

      markup.settessellation(mTess);
    }


    public static void AddAnnotationExample(OdPrcFileStructure newStructure, OdPrcProductOccurrence newProductOccurrence)
    {
      OdPrcObjectId un_id;
      OdPrcName name = new OdPrcName();
      name.setName("test");

      OdPrcObjectIdArray  arr = newProductOccurrence.markups().markups();

      OdPrcMarkup annItemMarkup = OdPrcMarkup.createObject();
      newStructure.addObject(annItemMarkup);
      CreateAnnItemMarkup(annItemMarkup);

      OdPrcMarkup annItem1ForSetMarkup = OdPrcMarkup.createObject();
      newStructure.addObject(annItem1ForSetMarkup);
      CreateAnnItem1ForSetMarkup(annItem1ForSetMarkup);

      OdPrcMarkup annItem2ForSetMarkup = OdPrcMarkup.createObject();
      newStructure.addObject(annItem2ForSetMarkup);
      CreateAnnItem2ForSetMarkup(annItem2ForSetMarkup);

      arr.Add(annItemMarkup.objectId());
      arr.Add(annItem1ForSetMarkup.objectId());
      arr.Add(annItem2ForSetMarkup.objectId());

      OdPrcObjectIdArray  arr_entity = newProductOccurrence.markups().annotationEntities();

      OdPrcAnnotationItem annItem = OdPrcAnnotationItem.createObject();
      annItem.setname(name);
      un_id = annItemMarkup.objectId();
      annItem.setmarkup(un_id);
      newStructure.addObject(annItem);
      arr_entity.Add(annItem.objectId());

      OdPrcAnnotationSet annSet = OdPrcAnnotationSet.createObject();
      annSet.setname(name);
      newStructure.addObject(annSet);
      OdPrcObjectIdArray  arr_set_ann = annSet.entities();
      {
        OdPrcAnnotationItem annItem1ForSet = OdPrcAnnotationItem.createObject();
        annItem1ForSet.setname(name);
        un_id = annItem1ForSetMarkup.objectId();
        annItem1ForSet.setmarkup(un_id);
        newStructure.addObject(annItem1ForSet);
        arr_set_ann.Add(annItem1ForSet.objectId());
      }
      {
        OdPrcAnnotationItem annItem2ForSet = OdPrcAnnotationItem.createObject();
        annItem2ForSet.setname(name);
        un_id = annItem2ForSetMarkup.objectId();
        annItem2ForSet.setmarkup(un_id);
        newStructure.addObject(annItem2ForSet);
        arr_set_ann.Add(annItem2ForSet.objectId());
      }
      arr_entity.Add(annSet.objectId());


      newStructure.fileStructureTessellation().tessellations().Add(annItemMarkup.tessellation());
      newStructure.fileStructureTessellation().tessellations().Add(annItem1ForSetMarkup.tessellation());
      newStructure.fileStructureTessellation().tessellations().Add(annItem2ForSetMarkup.tessellation());

      OdPrcObjectIdArray  arr_view = newProductOccurrence.annotationViews();
      OdPrcView itemView = OdPrcView.createObject();
      name.setName("AnnotationItemView");
      itemView.setname(name);
      un_id = annItem.objectId();
      itemView.annotations().Add(un_id);

      OdPrcPlane itemPlane = OdPrcPlane.createObject();
      OdPrcContentSurface content_suface = new OdPrcContentSurface();
      content_suface.baseGeometry().setBaseInformation(false);
      itemPlane.setcontentSurface(content_suface);
      itemView.setplane(itemPlane);
      itemView.setIsAnnotationView(true);

      newStructure.addObject(itemView);
      arr_view.Add(itemView.objectId());

      OdPrcView setView = OdPrcView.createObject();
      name.setName("AnnotationSetView");
      setView.setname(name);
      un_id = annSet.objectId();
      setView.annotations().Add(un_id);

      OdPrcPlane setPlane = OdPrcPlane.createObject();
      content_suface.baseGeometry().setBaseInformation(false);
      setPlane.setcontentSurface(content_suface);
      OdPrcTransformation3d transform = new OdPrcTransformation3d();
      OdGeMatrix3d geMatrix = new OdGeMatrix3d();
      geMatrix.setCoordSystem(new OdGePoint3d(0, 9, 0), new OdGeVector3d(1, 0, 0), new OdGeVector3d(0, 0, -1), new OdGeVector3d(0, 1, 0));
      transform.set(geMatrix);
      setPlane.setTransformation(transform);
      setView.setplane(setPlane);
      setView.setIsAnnotationView(true);
      newStructure.addObject(setView);
      arr_view.Add(setView.objectId());
    }

    public static OdPrcFile CreateAnnotationExample()
    {
      // common
      OdGeExtents3d extents = new OdGeExtents3d();
      extents.addPoint(new OdGePoint3d(0, 0, 0));
      extents.addPoint(new OdGePoint3d(1, 1, 1));
      OdPrcFile pFile = OdPrcCreateTopologyHelper.createTopologyCommon();
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure pFS = fileStructures[fileStructures.Count - 1];

      OdPrcProductOccurrence pRootPO = pFS.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
      OdPrcProductOccurrence pPO = OdPrcCreateTopologyHelper.createProductOccurrence(pFS, pRootPO);
      OdPrcPartDefinition pPD = OdPrcCreateTopologyHelper.createPartDefinition(pFS, pPO);
      pPD.boundingBox().setbox(extents);

      AddAnnotationExample(pFS, pPO);

      return pFile;
    }
  }
}
