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

namespace OdPrcCreateSwigMgd.Samples
{
  public abstract class OdPrcCreateExample : Example
  {
    #region Interface
    public String out_prcFileName { get; set; }
    public OdPrcHostAppServices pPrcHost { get; set; }
    public OdPrcCreateSwigMgd_ExampleModes mode { get; set; }
    protected abstract void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost);

    public override void Run()
    {
      MemoryTransaction tr = MemoryManager.GetMemoryManager().StartTransaction();
      OdStreamBuf pPrcStream = Globals.odrxSystemServices().createFile(out_prcFileName, FileAccessMode.kFileWrite, FileShareMode.kShareDenyNo, FileCreationDisposition.kCreateAlways);
      Execute(pPrcStream, mode, HostApp as OdDbHostAppServices, pPrcHost);
      MemoryManager.GetMemoryManager().StopTransaction(tr);
    }

    public override bool CheckInputApplicationParams()
    {
      if (pPrcHost == null || String.IsNullOrEmpty(out_prcFileName))
        return false;
      return base.CheckInputApplicationParams();
    }

    public override string GetUsageInfo()
    {
      return String.Format("\"<out_prc_file>\"");
    }
    #endregion
  }

}
