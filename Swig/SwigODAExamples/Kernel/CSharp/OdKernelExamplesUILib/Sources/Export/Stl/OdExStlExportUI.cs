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
using System.Windows.Forms;
using Teigha.Core;
using OdKernelExamplesMgdLib.Export.Stl;

namespace OdKernelExamplesUIMgdLib.Export.Stl
{
  public static class OdExStlExportUI
  {
    public static void Export<TStlExportParamsFiller>(OdRxObject database)
       where TStlExportParamsFiller : OdExStlExportParamsFiller, new()
    {
      MemoryTransaction mTr = MemoryManager.GetMemoryManager().StartTransaction();

      try
      {
        OdExExport2StlForm<TStlExportParamsFiller> formFillExportParameters = new OdExExport2StlForm<TStlExportParamsFiller>();
        if (formFillExportParameters.ShowDialog() != DialogResult.OK)
          throw new Exception("Stl Export canceled");

        using (OdExStlExportParamsFiller.OdExStlExportParams parametrsExport = formFillExportParameters.StlExportParamsFiller.Generate(database))
        {
          OdExStlExport exportExample = new OdExStlExport();
          exportExample.Export(parametrsExport);
        }
      }
      catch (Exception err)
      {
        MessageBox.Show(
        err.Message,
        "Information",
        MessageBoxButtons.OK,
        MessageBoxIcon.Information);
      }
      finally
      {
        MemoryManager.GetMemoryManager().StopTransaction(mTr);
      }
    }
  }

}