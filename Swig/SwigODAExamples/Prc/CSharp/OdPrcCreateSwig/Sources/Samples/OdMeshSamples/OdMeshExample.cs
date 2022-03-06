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

namespace OdPrcCreateSwigMgd.Samples.OdMeshSamples
{
  public abstract class OdMeshExample : OdPrcCreateExample
  {
    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      TriangleInfoPtrArray mesh = new TriangleInfoPtrArray();

      if (mode == OdPrcCreateSwigMgd_ExampleModes.MeshBox)
      {
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 255, 0, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 128, 0, 0);

        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 255, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 128, 0);

        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 255);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 128);

        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, -1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 255, 255, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, -1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 128, 128, 0);

        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 255, 255);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 128, 128);

        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, -1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 255, 0, 255);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, -1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 128, 0, 128);
      }
      if (mode == OdPrcCreateSwigMgd_ExampleModes.TriangleFan)
      {
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 255, 0, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 128, 0, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, 255);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 0, 0, 0, -1, 0, 0, -1, -1, 0, 0, 0, 128);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 0, 0, 0, -1, -1, 0, 0, -1, 0, 0, 255, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 0, 0, 0, 0, -1, 0, 1, 0, 0, 0, 128, 0);

      }
      if (mode == OdPrcCreateSwigMgd_ExampleModes.TriangleStripe)
      {
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 255);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 1, 1, 0, 0, 2, 0, 2, 0, 0, 1, 1, 2, 0, 0, 255);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, -1, 1, 2, 0, 0, 1, 1, 2, 0, 0, 0, 0, 0, 255);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, -1, 0, 1, 1, 1, 2, 0, 0, 0, 0, 2, 0, 0, 0, 255);
      }
      if (mode == OdPrcCreateSwigMgd_ExampleModes.TessCombination)
      {
        // Figure for combine type
        // - Roof
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 255, 0, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 0, 1, 1, -1, 0, 1, 0, 0, 1, 0, 255, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, -1, 0, 1, -1, -1, 1, 0, -1, 1, 255, 0, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 0, 0, 1, 0, -1, 1, 1, 0, 1, 0, 255, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 255);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, 1, -1, 0, 1, 0, -1, 1, 0, 0, 1, 0, 0, 255);

        // - Floor
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 0, 0, 0, 1, 0, 0, 0, -1, 0, 255, 0, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 0, 0, 0, 0, -1, 0, -1, -1, 0, 128, 0, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 0, 0, 0, -1, -1, 0, -1, 0, 0, 0, 0, 255);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 0, 0, 0, -1, 0, 0, 0, 1, 0, 0, 0, 128);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 255, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 0, -1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 128, 0);

        // - Walls
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 255, 0, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 255, 0);

        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 255);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 255, 255, 0);

        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, -1, 1, 0, 0, 1, 1, 0, 1, 0, -1, 0, 1, 255, 0, 255);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, -1, 1, 0, 0, 1, 0, -1, 0, 1, -1, 0, 0, 0, 255, 255);

        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, -1, 0, 0, -1, 0, 1, -1, 0, 0, -1, -1, 1, 128, 0, 0);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, -1, 0, 0, -1, 0, 0, -1, -1, 1, -1, -1, 0, 0, 128, 0);

        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, -1, 0, -1, -1, 1, -1, -1, 0, 0, -1, 1, 0, 0, 128);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 0, -1, 0, -1, -1, 0, 0, -1, 1, 0, -1, 0, 128, 128, 0);

        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 1, -1, 0, 0, -1, 1, 0, -1, 0, 1, 0, 1, 128, 0, 128);
        OdPrcCreateTopologyHelper.addSimpleTriangle(mesh, 1, -1, 0, 0, -1, 0, 1, 0, 1, 1, 0, 0, 0, 128, 128);
      }

      Globals.odrxDynamicLinker().loadModule("OdPrcModule");
      Globals.odrxDynamicLinker().loadModule("OdDwg2PrcExport");

      PdfExportServiceInterface pExportIFace = Globals.getPdfExportService();
      // write file to stream
      PDF2PRCExportParams _params = new PDF2PRCExportParams();
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

  public class OdMeshExample_MeshBox : OdMeshExample
  {
    public override string Description
    {
      get
      {
        return "box as mesh export example";
      }
    }
  }

  public class OdMeshExample_TriangleFan : OdMeshExample
  {
    public override string Description
    {
      get
      {
        return "triangle fan export example";
      }
    }
  }

  public class OdMeshExample_TriangleStripe : OdMeshExample
  {
    public override string Description
    {
      get
      {
        return "triangle stripe export example";
      }
    }
  }

  public class OdMeshExample_TessCombination : OdMeshExample
  {
    public override string Description
    {
      get
      {
        return "combination of triangle stripe and triangle fan example";
      }
    }
  }

}
