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

namespace OdPrcCreateSwigMgd.Samples.OdBrepSamples
{
  public abstract class OdBrepExample : OdPrcCreateExample
  {
    #region Impl
    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      MemoryTransaction tr = MemoryManager.GetMemoryManager().StartTransaction();
      OdDb3dSolid p3dSolid = OdDb3dSolid.createObject();

      if (mode == OdPrcCreateSwigMgd_ExampleModes.BrepSphere)
      {
        p3dSolid.createSphere(10);
      }
      if (mode == OdPrcCreateSwigMgd_ExampleModes.BrepBox)
      {
        p3dSolid.createBox(10, 20, 30);
      }

      OdDbDatabase pDb = pH.createDatabase();
      OdDbBlockTableRecord pRec = pDb.getModelSpaceId().safeOpenObject(Teigha.TD.OpenMode.kForWrite) as OdDbBlockTableRecord;
      pRec.appendOdDbEntity(p3dSolid);

      PDF2PRCExportParams _params = new PDF2PRCExportParams();

      Globals.odrxDynamicLinker().loadModule("OdPrcModule");
      Globals.odrxDynamicLinker().loadModule("OdDwg2PrcExport");
      PdfExportServiceInterface pExportIFace = Globals.getPdfExportService();

      OdRxObject pContext = pExportIFace.createPrcExportContext(pDb);

      OdResult res = pExportIFace.ExportPrc(pContext, p3dSolid, _params);
      if (res != OdResult.eOk)
      {
        throw new OdError(res);
      }
      res = pExportIFace.serialize(pPrcStream, pContext, _params);
      if (res != OdResult.eOk)
      {
        throw new OdError(res);
      }
      MemoryManager.GetMemoryManager().StopTransaction(tr);
    }
    #endregion
  }

}
