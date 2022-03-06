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

namespace OdPrcCreateSwigMgd.Samples.OdTessSamples
{
  public class OdTessExample_TessExample1 : OdTessExample
  {
    public override string Description
    {
      get
      {
        return "Many boxes as single prc tess export example";
      }
    }
    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // setup
      TriangleInfoPtrArray mesh = new TriangleInfoPtrArray();

      // start add objects to prc file (as tessellation)
      int countOfObjects = 1000;
      int objectsPerRow = 10;
      int dx = 2;
      int dy = 2;
      int shift_x = 0; // distance between boxes
      int shift_y = 0;
      for (int idx = 0; idx < (countOfObjects / objectsPerRow); ++idx)
      {
        for (int j = 0; j < objectsPerRow; ++j)
        {
          // - fill the tess representation of the body
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 0 + shift_x, 0 + shift_y, 0, 1 + shift_x, 1 + shift_y, 0, 1 + shift_x, 0 + shift_y, 0, 255, 0, 0);
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 1 + shift_x, 1 + shift_y, 0, 0 + shift_x, 0 + shift_y, 0, 0 + shift_x, 1 + shift_y, 0, 128, 0, 0);

          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 1 + shift_x, 0 + shift_y, 1, 1 + shift_x, 1 + shift_y, 1, 0 + shift_x, 0 + shift_y, 1, 0, 255, 0);
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 0 + shift_x, 1 + shift_y, 1, 0 + shift_x, 0 + shift_y, 1, 1 + shift_x, 1 + shift_y, 1, 0, 128, 0);

          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 1, 0, 0 + shift_x, 1 + shift_y, 0, 1 + shift_x, 1 + shift_y, 1, 1 + shift_x, 1 + shift_y, 0, 0, 0, 255);
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 1, 0, 1 + shift_x, 1 + shift_y, 1, 0 + shift_x, 1 + shift_y, 0, 0 + shift_x, 1 + shift_y, 1, 0, 0, 128);

          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, -1, 0, 1 + shift_x, 0 + shift_y, 0, 1 + shift_x, 0 + shift_y, 1, 0 + shift_x, 0 + shift_y, 0, 255, 255, 0);
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, -1, 0, 0 + shift_x, 0 + shift_y, 1, 0 + shift_x, 0 + shift_y, 0, 1 + shift_x, 0 + shift_y, 1, 128, 128, 0);

          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 1, 0, 0, 1 + shift_x, 1 + shift_y, 1, 1 + shift_x, 0 + shift_y, 0, 1 + shift_x, 1 + shift_y, 0, 0, 255, 255);
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 1, 0, 0, 1 + shift_x, 0 + shift_y, 0, 1 + shift_x, 1 + shift_y, 1, 1 + shift_x, 0 + shift_y, 1, 0, 128, 128);

          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, -1, 0, 0, 0 + shift_x, 0 + shift_y, 0, 0 + shift_x, 1 + shift_y, 1, 0 + shift_x, 1 + shift_y, 0, 255, 0, 255);
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, -1, 0, 0, 0 + shift_x, 1 + shift_y, 1, 0 + shift_x, 0 + shift_y, 0, 0 + shift_x, 0 + shift_y, 1, 128, 0, 128);

          shift_x = (shift_x + dx);
        }

        shift_y += dy;
        shift_x = 0;
      }

      // load module
      Globals.odrxDynamicLinker().loadModule("OdDwg2PrcExport", true);
      PdfExportServiceInterface pExportIFace = Globals.getPdfExportService();

      // write data into stream
      using (PDF2PRCExportParams _params = new PDF2PRCExportParams())
      {
        _params.m_exportAsBrep = false;
        OdRxObject pContext = pExportIFace.createPrcExportContext(null);
        OdResult res = PRC_Globals.exportMeshToPrc(mesh, pContext);
        if (res != OdResult.eOk)
        {
          throw new OdError(res);
        }
        res = pExportIFace.serialize(pPrcStream, pContext, _params);
        if (res != OdResult.eOk)
        {
          throw new OdError(res);
        }
      }
    }
  }

  public class OdTessExample_TessExample2 : OdTessExample
  {
    public override string Description
    {
      get
      {
        return "Many boxes as one prc tess per box export example";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      MemoryTransaction tr = MemoryManager.GetMemoryManager().StartTransaction();
      Globals.odrxDynamicLinker().loadModule("OdDwg2PrcExport");

      // setup
      // - prc file
      OdPrcFile newFile = OdPrcCreateTopologyHelper.createTopologyCommon();

      // create model topology for tessellation
      OdPrcFileStructurePtrArray fileStructures = newFile.fileStructures();
      OdPrcFileStructure newStructure = fileStructures[fileStructures.Count - 1];
      OdPrcProductOccurrence pRootPO = newStructure.fileStructureTree().internalData().getRootProductOccurrenceID().openObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcProductOccurrence;
      OdPrcPartDefinition pPD = OdPrcCreateTopologyHelper.createPartDefinition(newStructure, pRootPO);

      PdfExportServiceInterface pExportIFace = Globals.getPdfExportService();
      OdPrcExportContext pContext = pExportIFace.createPrcExportContext(null) as OdPrcExportContext;

      // start add objects to prc file (as tessellation)
      uint countOfObjects = 1000;
      uint objectsPerRow = 10;
      uint dx = 2;
      uint dy = 2;
      uint shift_x = 0; // distance between boxes
      uint shift_y = 0;
      for (uint idx = 0; idx < (countOfObjects / objectsPerRow); ++idx)
      {
        for (uint j = 0; j < objectsPerRow; ++j)
        {
          TriangleInfoPtrArray mesh = new TriangleInfoPtrArray();
          // - fill the tess representation of the body
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 0 + shift_x, 0 + shift_y, 0, 1 + shift_x, 1 + shift_y, 0, 1 + shift_x, 0 + shift_y, 0, 255, 0, 0);
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 1 + shift_x, 1 + shift_y, 0, 0 + shift_x, 0 + shift_y, 0, 0 + shift_x, 1 + shift_y, 0, 128, 0, 0);

          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 1 + shift_x, 0 + shift_y, 1, 1 + shift_x, 1 + shift_y, 1, 0 + shift_x, 0 + shift_y, 1, 0, 255, 0);
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 0 + shift_x, 1 + shift_y, 1, 0 + shift_x, 0 + shift_y, 1, 1 + shift_x, 1 + shift_y, 1, 0, 128, 0);

          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 1, 0, 0 + shift_x, 1 + shift_y, 0, 1 + shift_x, 1 + shift_y, 1, 1 + shift_x, 1 + shift_y, 0, 0, 0, 255);
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 1, 0, 1 + shift_x, 1 + shift_y, 1, 0 + shift_x, 1 + shift_y, 0, 0 + shift_x, 1 + shift_y, 1, 0, 0, 128);

          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, -1, 0, 1 + shift_x, 0 + shift_y, 0, 1 + shift_x, 0 + shift_y, 1, 0 + shift_x, 0 + shift_y, 0, 255, 255, 0);
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, -1, 0, 0 + shift_x, 0 + shift_y, 1, 0 + shift_x, 0 + shift_y, 0, 1 + shift_x, 0 + shift_y, 1, 128, 128, 0);

          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 1, 0, 0, 1 + shift_x, 1 + shift_y, 1, 1 + shift_x, 0 + shift_y, 0, 1 + shift_x, 1 + shift_y, 0, 0, 255, 255);
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 1, 0, 0, 1 + shift_x, 0 + shift_y, 0, 1 + shift_x, 1 + shift_y, 1, 1 + shift_x, 0 + shift_y, 1, 0, 128, 128);

          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, -1, 0, 0, 0 + shift_x, 0 + shift_y, 0, 0 + shift_x, 1 + shift_y, 1, 0 + shift_x, 1 + shift_y, 0, 255, 0, 255);
          OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, -1, 0, 0, 0 + shift_x, 1 + shift_y, 1, 0 + shift_x, 0 + shift_y, 0, 0 + shift_x, 0 + shift_y, 1, 128, 0, 128);

          shift_x = (shift_x + dx);

          OdPrcPolyBrepModel newPolyBrep = OdPrcCreateTopologyHelper.createRI<OdPrcPolyBrepModel>(newStructure, pPD);

          // - write tess into prc file
          OdPrcCreateTopologyHelper.fillTessellation(newStructure, mesh, pContext);
          OdPrcBaseTessDataPtrArray tessellations = newStructure.fileStructureTessellation().tessellations();
          newPolyBrep.settessellation(tessellations[tessellations.Count - 1]);
          
          // - bounding box
          OdGeExtents3d extents;
          OdPrcCreateTopologyHelper.meshExtents(mesh, out extents);
          pPD.boundingBox().setbox(extents);
        }

        shift_y += dy;
        shift_x = 0;
      }

      // write file
      try
      {
        OdPrcFileSettings pSettings = new OdPrcFileSettings();
        newFile.writeFile(pPrcStream, pSettings);
      }
      catch (OdError e)
      {
        throw e;
      }
      catch (Exception)
      {
        throw new OdError(OdResult.eExtendedError);
      }
      finally
      {
        MemoryManager.GetMemoryManager().StopTransaction(tr);
      }
    }
  }

  public abstract class OdTessExample : OdPrcCreateExample
  {

  }
}
