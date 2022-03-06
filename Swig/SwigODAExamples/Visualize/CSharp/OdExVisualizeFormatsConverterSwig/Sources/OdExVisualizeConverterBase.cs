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
using Teigha.Visualize;

namespace OdExVisualizeFormatsConverterSwig
{
  public abstract class OdExVisualizeConverterBase
  {
    private String m_inFilePath;
    private String m_outFilePath;

    public OdExVisualizeConverterBase(String inFilePath, String outFilePath)
    {
      m_inFilePath = inFilePath;
      m_outFilePath = outFilePath;
    }

    public void Convert()
    {
      MemoryTransaction mTr = MemoryManager.GetMemoryManager().StartTransaction();
      try
      {
        OdTvBaseImportParams importParams = CreateImportParams(m_inFilePath);
        if (importParams == null)
          throw new OdError("m_ImportParams is not defined");
        OdTvResult importRes = OdTvResult.tvOk;
        OdTvDatabaseId tvDbId = TV_Globals.odTvGetFactory().importFile(importParams, ref importRes);
        if (importRes != OdTvResult.tvOk)
          throw new OdError(String.Format("Import error code:{0}", importRes));

        OdTvDatabase tvDb = tvDbId.openObject();

        OdTvBaseExportParams exportParams = CreateExportParams(tvDb, m_outFilePath);
        if (exportParams == null)
          throw new OdError("m_ExportParams is not defined");

        OdTvResult exportRes = tvDb.exportTo(exportParams);
        if (exportRes != OdTvResult.tvOk)
          throw new OdError(String.Format("Export error code:{0}", exportRes));

      }
      catch (Exception err)
      {
        throw err;
      }
      finally
      {
        MemoryManager.GetMemoryManager().StopTransaction(mTr);
      }
    }

    protected abstract OdTvBaseImportParams CreateImportParams(string filePath);
    protected abstract OdTvBaseExportParams CreateExportParams(OdTvDatabase currectDatabase, string filePath);
  }

}