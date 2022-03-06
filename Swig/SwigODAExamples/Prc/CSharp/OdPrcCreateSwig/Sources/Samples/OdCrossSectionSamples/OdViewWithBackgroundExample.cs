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

namespace OdPrcCreateSwigMgd.Samples.OdCrossSectionSamples
{
  public class OdCrossSectionExample_BackgroundExample : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "Cone with background example";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // create an object
      OdStreamBuf pMemStream = OdMemoryStream.createNew();
      OdCrossSectionExample_SimpleSection.createTestGeometryForCrossSectionTest(pMemStream, pH);

      // open file
      pMemStream.rewind();
      OdPrcFile pFile = pPrcHost.readFile(pMemStream);
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructure pNewFileStructure = fileStructures[fileStructures.Count - 1];

      // create view
      {
        OdPrcView pNewView = OdPrcView.createObject();
        pNewFileStructure.addObject(pNewView);
        OdPrcName name = new OdPrcName();
        name.setName("NE Isometric");
        pNewView.setname(name);
        // - add view to PO
        fileStructures = pFile.fileStructures();
        OdPrcProductOccurrencePtrArray productOccurrence = fileStructures[fileStructures.Count - 1].fileStructureTree().productOccurrence();
        OdPrcProductOccurrence productOc = productOccurrence[productOccurrence.Count - 1];
        OdPrcObjectIdArray arr_view = productOc.annotationViews();
        arr_view.Add(new OdPrcObjectId(pNewView.id()));
        OdPrcSceneDisplayParameters pSceneDisplayParameters = OdPrcSceneDisplayParameters.createObject();
        pNewFileStructure.addObject(pSceneDisplayParameters);
        pNewView.setsceneDisplayParameters(new OdPrcObjectId(pSceneDisplayParameters.id()));

        // - setup camera for view
        OdPrcCamera pCamera = OdPrcCamera.createObject();
        pNewFileStructure.addObject(pCamera);
        pCamera.lookAt().set(0.0, 0.0, 0.0);
        pCamera.up().set(0.0, 0.0, 1.0);
        pCamera.location().set(5.0, 5.0, 5.0);
        pCamera.setXFov(1.0472);
        pCamera.setYFov(1.0472);
        pSceneDisplayParameters.setcamera(new OdPrcObjectId(pCamera.id()));

        // create background for view
        OdPrcObjectId backgroundColorID = OdPrcCategory1LineStyle.createByColor(0.00, 1.00, 1.00, pNewFileStructure); // add line style to prc file
        pSceneDisplayParameters.setbackgroundStyle(backgroundColorID);
      }

      // write file
      pFile.writeFile(pPrcStream);
    }
  }
}
