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
  public class OdCrossSectionExample_SimpleSection : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "Cone with cross section example";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      simpleCrossSectioExample(pPrcStream, mode, pH, pPrcHost);
    }

    public static void simpleCrossSectioExample(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // create an object
      OdStreamBuf pMemStream = OdMemoryStream.createNew();
      createTestGeometryForCrossSectionTest(pMemStream, pH);

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
      }

      // create view with XZ clipping plane
      {
        OdPrcView pNewView = OdPrcView.createObject();
        pNewFileStructure.addObject(pNewView);
        OdPrcName name = new OdPrcName();
        name.setName("NE Isometric clipped by XZ");
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

        // - add clipping plane to the view
        OdPrcSurfacePtrArray viewClippingPlanes = pSceneDisplayParameters.clippingPlanes();
        OdPrcPlane pPlane = OdPrcPlane.createObject();
        OdGeVector3d normal = new OdGeVector3d(0.0, 1.0, 0.0);
        OdGePoint3d origin = new OdGePoint3d(0.0, 0.0, 0.0);
        normal.normalize();
        OdGePlane gePlane = new OdGePlane(origin, normal);
        OdGeInterval intU = new OdGeInterval(-3.0, 3);
        OdGeInterval intV = new OdGeInterval(-3.0, 3);
        gePlane.setEnvelope(intU, intV);
        pPlane.setFromOdGeSurface(gePlane);
        viewClippingPlanes.Add(pPlane);
      }

      // create view with XY clipping plane translated from origin
      {
        OdPrcView pNewView = OdPrcView.createObject();
        pNewFileStructure.addObject(pNewView);
        OdPrcName name = new OdPrcName();
        name.setName("top view clipped by XY");
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
        pCamera.up().set(-1.0, -1.0, 0.0);
        pCamera.location().set(0.0, 0.0, 5.0);
        pCamera.setXFov(1.0472); // - in radians
        pCamera.setYFov(1.0472);
        pSceneDisplayParameters.setcamera(new OdPrcObjectId(pCamera.id()));

        // - add clipping plane to the view
        {
          OdPrcSurfacePtrArray viewClippingPlanes = pSceneDisplayParameters.clippingPlanes();
          OdPrcPlane pPlane = OdPrcPlane.createObject();
          OdGeVector3d normal = new OdGeVector3d(0.0, 0.0, -1.0);
          OdGePoint3d origin = new OdGePoint3d(0.0, 0.0, 0.5);
          normal.normalize();
          OdGePlane gePlane = new OdGePlane(origin, normal);
          OdGeInterval intU = new OdGeInterval(-3.0, 3);
          OdGeInterval intV = new OdGeInterval(-3.0, 3);
          gePlane.setEnvelope(intU, intV);
          pPlane.setFromOdGeSurface(gePlane);
          viewClippingPlanes.Add(pPlane);
        }
        //     {
        //       // - add clipping plane to the view
        //       OdPrcSurfacePtrArray &viewClippingPlanes = ((OdPrcSceneDisplayParameters*)pSceneDisplayParameters).clippingPlanes();
        //       OdPrcPlane pPlane = OdPrcPlane.createObject();
        //       OdGeVector3d normal(0.0, 1.0, 0.0);
        //       OdGePoint3d origin(0.0, 0.0, 0.0);
        //       normal.normalize();
        //       OdGePlane gePlane(origin, normal);
        //       OdGeInterval intU(-3., 3);
        //       OdGeInterval intV(-3., 3);
        //       gePlane.setEnvelope(intU, intV);
        //       pPlane.setFromOdGeSurface(gePlane);
        //       viewClippingPlanes.Add(pPlane);
        //     }
      }

      // create view with tilted clipping plane
      {
        OdPrcView pNewView = OdPrcView.createObject();
        pNewFileStructure.addObject(pNewView);
        OdPrcName name = new OdPrcName();
        name.setName("NE Isometric clipped by 111");
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

        // - add clipping plane to the view
        OdPrcSurfacePtrArray viewClippingPlanes = pSceneDisplayParameters.clippingPlanes();
        OdPrcPlane pPlane = OdPrcPlane.createObject();
        OdGeVector3d normal = new OdGeVector3d(1.0, 1.0, 0.0);
        OdGePoint3d origin = new OdGePoint3d(0.0, 0.0, 0.0);
        normal.normalize();
        OdGePlane gePlane = new OdGePlane(origin, normal);
        OdGeInterval intU = new OdGeInterval(-3.0, 3);
        OdGeInterval intV = new OdGeInterval(-3.0, 3);
        gePlane.setEnvelope(intU, intV);
        pPlane.setFromOdGeSurface(gePlane);
        viewClippingPlanes.Add(pPlane);
      }

      // write file
      pFile.writeFile(pPrcStream);
    }

    public static void createTestGeometryForCrossSectionTest(OdStreamBuf pMemStream, OdDbHostAppServices pH)
    {
      // create a solid object
      OdDb3dSolid p3dSolid = OdDb3dSolid.createObject();
      p3dSolid.createFrustum(4.0, 1.0, 1.0, 0.0);

      OdDbDatabase pDb = pH.createDatabase();
      OdDbBlockTableRecord pRec = pDb.getModelSpaceId().safeOpenObject(Teigha.TD.OpenMode.kForWrite) as OdDbBlockTableRecord;
      pRec.appendOdDbEntity(p3dSolid);

      // load module
      Globals.odrxDynamicLinker().loadModule("OdDwg2PrcExport");
      PdfExportServiceInterface pExportIFace = Globals.getPdfExportService();

      // write file to stream
      using (PDF2PRCExportParams _params = new PDF2PRCExportParams())
      {
        OdRxObject pContext = pExportIFace.createPrcExportContext(pDb);
        OdResult res = pExportIFace.ExportPrc(pContext, p3dSolid, _params);
        if (res != OdResult.eOk)
        {
          throw new OdError(res);
        }
        res = pExportIFace.serialize(pMemStream, pContext, _params);
        if (res != OdResult.eOk)
        {
          throw new OdError(res);
        }
      }
    }
  }
}
