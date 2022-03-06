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
using Teigha.TD;

namespace OdPdfExportWithPrcSwigMgd.Samples
{
  public class OdPdfExportWithPrcWithBackgroundExample : OdPdfExportWithPrcExample
  {
    #region Interface
    public override string Description => "Creates and exports box into pdf as brep with teal background";
    #endregion

    #region Impl
    public override void Execute(OdDbHostAppServices svcs, String pdfPath)
    {
      MemoryTransaction mStartTrans = MemoryManager.GetMemoryManager().StartTransaction();

      OdPdfExportWithPrcWithBackgroundExample.Execute(svcs, pdfPath, PDFExportParams.PRCSupport.kAsMesh, true, fillDatabase);

      MemoryManager.GetMemoryManager().StopTransaction(mStartTrans);
    }

    private new static void Execute(OdDbHostAppServices svcs, String pdfPath, PDFExportParams.PRCSupport flags, bool shouldUseSingleViewMode, DatabaseFillerFunc fillerfunc)
    {
      MemoryTransaction mStartTrans = MemoryManager.GetMemoryManager().StartTransaction();

      /******************************************************************/
      /* Create a Pdf export module                                     */
      /******************************************************************/
      OdRxModule mod = Globals.odrxDynamicLinker().loadApp("TD_PdfExport");
      PdfExportModule pdf_export_module = new PdfExportModule(OdRxModule.getCPtr(mod).Handle, false);

      Globals.odrxDynamicLinker().loadApp("OdPrcModule");
      Globals.odrxDynamicLinker().loadApp("OdDwg2PrcExport");

      /******************************************************************/
      /* Create a database and load the drawing into it.                */
      /******************************************************************/
      OdDbDatabase pDb = svcs.createDatabase();
      fillerfunc(pDb);

      /****************************************************************/
      /* Initialize the conversion parameters                         */
      /****************************************************************/
      OdPdfExport exporter = pdf_export_module.create();

      using (PDFExportParams _params = new PDFExportParams())
      {
        _params.setDatabase(pDb);
        _params.setVersion(PDFExportParams.PDFExportVersions.kPDFv1_6);
        _params.setOutput(Globals.odrxSystemServices().createFile(pdfPath, FileAccessMode.kFileWrite,
            FileShareMode.kShareDenyNo, FileCreationDisposition.kCreateAlways));

        _params.setExportFlags(PDFExportParams.PDFExportFlags.kDefault);

        _params.setTitle("Batch PDF File");
        _params.setAuthor("OdPdfExportWithPrcSwigMgd");
        _params.setCreator("Open Design Alliance");
        _params.setPRCMode(flags);
        OdPrcContextForPdfExport pContext = ((shouldUseSingleViewMode) ? Helpers.odCreatePrcAllInSingleViewContextForTD() : Helpers.odCreatePrcDefaultContextForTD()) as OdPrcContextForPdfExport;
        _params.setPRCContext(pContext);

        _params.setPrcBackground(0x0000ffff); // 00 ff ff => teal background should appear when file is opened

        /****************************************************************/
        /* Initialize the conversion parameters: Layouts                */
        /****************************************************************/

        OdDbBlockTableRecord pLayoutBlock = pDb.getActiveLayoutBTRId().safeOpenObject() as OdDbBlockTableRecord;
        OdDbLayout pLayout = pLayoutBlock.getLayoutId().safeOpenObject() as OdDbLayout;
        _params.layouts().Add(pLayout.getLayoutName());

        _params.pageParams().resize(1);


        UInt32 errCode = exporter.exportPdf(_params);
        if (errCode != 0)
        {
          String errMes = exporter.exportPdfErrorCode(errCode);
          Console.WriteLine(String.Format("ExportPdf error returned : 0x%x. \n%ls\n", errCode, errMes));
        }
      }

      MemoryManager.GetMemoryManager().StopTransaction(mStartTrans);
    }
    #endregion
  }
}
