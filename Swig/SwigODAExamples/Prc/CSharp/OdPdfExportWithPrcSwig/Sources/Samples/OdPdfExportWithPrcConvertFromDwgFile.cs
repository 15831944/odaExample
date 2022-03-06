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
using OdCreationNetSwigExampleLib;
using Teigha.Core;
using Teigha.PRC;
using Teigha.TD;

namespace OdPdfExportWithPrcSwigMgd.Samples
{
  public class OdPdfExportWithPrcConvertFromDwgFile : Example
  {
    #region Interface
    public String InDwgPath;

    public String OutPrcPath;

    public override string Description => "Default example which demonstrated who convert Dwg to Prc by PdfExport";

    public override void Run()
    {
      Execute(HostApp as OdDbHostAppServices, InDwgPath, OutPrcPath);
    }

    public override bool CheckInputApplicationParams()
    {
      if (String.IsNullOrEmpty(InDwgPath))
        return false;
      if (String.IsNullOrEmpty(OutPrcPath))
        return false;
      return true;
    }

    public override String GetUsageInfo()
    {
      return String.Format("\"<in_dwg_file>\" \"<out_prc_file>\"");
    }
    #endregion

    #region Impl
    private void Execute(OdDbHostAppServices hostApp, String in_dwgPath, String out_prcPath)
    {
      MemoryManager mMan = MemoryManager.GetMemoryManager();
      MemoryTransaction mStartTrans = mMan.StartTransaction();

      Globals.odrxDynamicLinker().loadApp("OdPrcModule", false);
      Globals.odrxDynamicLinker().loadApp("OdDwg2PrcExport", false);

      OdDbDatabase db = hostApp.readFile(in_dwgPath);

      PRCStreamsMap outStreamsPRC = new PRCStreamsMap();
      OdRxModule mod = Globals.odrxDynamicLinker().loadApp("TD_PdfExport");
      PdfExportModule module = new PdfExportModule(OdRxModule.getCPtr(mod).Handle, false);
      OdPdfExport exporter = module.create();

      using (PDFExportParams publishParams = new PDFExportParams())
      {
        publishParams.setDatabase(db);
        publishParams.setPRCContext(Helpers.odCreatePrcAllInSingleViewContextForTD());
        publishParams.setPRCMode(PDFExportParams.PRCSupport.kAsBrep);

        UInt32 errCode = exporter.publish3d(publishParams, outStreamsPRC);
        if (errCode != 0)
        {
          String errMes = exporter.exportPdfErrorCode(errCode);
          Console.WriteLine(String.Format("ExportPdf error returned : 0x%x. \n%ls\n", errCode, errMes));
        }

        if (outStreamsPRC.Count != 0)
        {
          OdStreamBuf stream = outStreamsPRC[0];
          stream.rewind();

          OdStreamBuf pPrcStream = Globals.odrxSystemServices().createFile(out_prcPath, FileAccessMode.kFileWrite,
            FileShareMode.kShareDenyNo, FileCreationDisposition.kCreateAlways);

          OdPrcFile pFile = OdPrcFile.createObject();
          pFile.readFile(stream);
          pFile.writeFile(pPrcStream);
        }
      }
      mMan.StopTransaction(mStartTrans);
    }
    #endregion
  }
}
