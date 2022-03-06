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

namespace OdPrcCreateSwigMgd.Samples
{
  public class OdMultipleEntitiesExportExample : OdPrcCreateExample
  {
    public override string Description
    {
      get
      {
        return "Multiple entities export example";
      }
    }

    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // load module
      Globals.odrxDynamicLinker().loadModule("OdDwg2PrcExport", false);

      //setup export parameters
      using (PDF2PRCExportParams _params = new PDF2PRCExportParams())
      {
        //prepare database
        OdDbDatabase pDb = pH.createDatabase();
        OdDbBlockTableRecord pRec = pDb.getModelSpaceId().safeOpenObject(Teigha.TD.OpenMode.kForWrite) as OdDbBlockTableRecord;

        PdfExportServiceInterface pExportIFace = Globals.getPdfExportService();
        OdRxObject pContext = pExportIFace.createPrcExportContext(pDb);

        // create 3 solid objects and export them
        for (int i = 0; i < 3; ++i)
        {
          //create entity and add it to database
          OdDb3dSolid p3dSolid = OdDb3dSolid.createObject();
          p3dSolid.createFrustum(i + 1, 1.0, 1.0, 0.0);
          pRec.appendOdDbEntity(p3dSolid);

          //export entity
          OdResult _res = pExportIFace.ExportPrc(pContext, p3dSolid, _params);
          if (_res != OdResult.eOk)
          {
            throw new OdError(_res);
          }
        }

        //get PrcFile
        OdResult res = pExportIFace.serialize(pPrcStream, pContext, _params);
        if (res != OdResult.eOk)
        {
          throw new OdError(res);
        }
      }
    }
  }
}
