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
  public class OdExVisualizeDwgToObjConverter : OdExVisualizeConverterBase
  {
    public OdExVisualizeDwgToObjConverter(String inFilePath, String outFilePath) : base(inFilePath, outFilePath)
    { }

    protected override OdTvBaseImportParams CreateImportParams(string filePath)
    {
      string ext = System.IO.Path.GetExtension(filePath);
      if (String.Compare(ext, ".dwg", true) != 0)
        throw new OdError("Input file is not dwg");

      OdTvDwgImportParams importParams = new OdTvDwgImportParams();
      importParams.setObjectNaming(true);
      importParams.setStoreSourceObjects(false);
      importParams.setFeedbackForChooseCallback(null);
      importParams.setFilePath(filePath);
      return importParams;
    }

    protected override OdTvBaseExportParams CreateExportParams(OdTvDatabase currentDatabase, string filePath)
    {
      string ext = System.IO.Path.GetExtension(filePath);
      if (String.Compare(ext, ".obj", true) != 0)
        throw new OdError("Output file is not obj");

      OdTvBaseExportParams exportParams = new OdTvBaseExportParams();
      exportParams.setFilePath(filePath);
      return exportParams;
    }
  }
}