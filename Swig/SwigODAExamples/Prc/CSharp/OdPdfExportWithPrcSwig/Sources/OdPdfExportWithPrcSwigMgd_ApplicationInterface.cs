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
using System.Collections.Generic;
using OdCreationNetSwigExampleLib;
using OdPdfExportWithPrcSwigMgd.Samples;
using Teigha.Core;

namespace OdPdfExportWithPrcSwigMgd
{
  public enum OdPdfExportWithPrcSwigMgd_ExampleModes
  {
    None = 0,
    M0,
    M1,
    M2,
    M3,
    M4
  }

  public class OdPdfExportWithPrcSwigMgd_ApplicationInterface : ExampleApplicationInterface<OdPdfExportWithPrcSwigMgd_ExampleModes>
  {
    public OdPdfExportWithPrcSwigMgd_ApplicationInterface(OdDbBaseHostAppServices hostApp, String[] app_args) : base(hostApp,app_args)
    {
    }

    private static Dictionary<OdPdfExportWithPrcSwigMgd_ExampleModes, Type> ModeToExample = new Dictionary<OdPdfExportWithPrcSwigMgd_ExampleModes, Type>()
    {
      {OdPdfExportWithPrcSwigMgd_ExampleModes.M0, typeof(OdPdfExportWithPrcConvertFromDwgFile)},
      {OdPdfExportWithPrcSwigMgd_ExampleModes.M1, typeof(OdPdfExportWithPrcExample)},
      {OdPdfExportWithPrcSwigMgd_ExampleModes.M2, typeof(OdPdfExportWithPrcSeveralEntetiesExample)},
      {OdPdfExportWithPrcSwigMgd_ExampleModes.M3, typeof(OdPdfExportWithPrcWithBackgroundExample)},
      {OdPdfExportWithPrcSwigMgd_ExampleModes.M4, typeof(OdPdfPrcFilterExample)},
    };

    protected override Dictionary<OdPdfExportWithPrcSwigMgd_ExampleModes, Type> ModeToExampleClass => ModeToExample;

    protected override bool InitExample(Example instance)
    {
      if (instance == null)
        return false;

      Type exampleType = instance.GetType();

      OdPdfExportWithPrcSwigMgd_ExampleModes mode = GetModeFromExampleType(exampleType);

      switch (mode)
      {
        case OdPdfExportWithPrcSwigMgd_ExampleModes.M0:
          {
            if (app_args.Length < 3)
              return false;
            ((OdPdfExportWithPrcConvertFromDwgFile)instance).InDwgPath = app_args[1];
            ((OdPdfExportWithPrcConvertFromDwgFile)instance).OutPrcPath = app_args[2];
            break;
          }
        case OdPdfExportWithPrcSwigMgd_ExampleModes.M1:
        case OdPdfExportWithPrcSwigMgd_ExampleModes.M2:
        case OdPdfExportWithPrcSwigMgd_ExampleModes.M3:
        case OdPdfExportWithPrcSwigMgd_ExampleModes.M4:
          {
            if (app_args.Length < 2)
              return false;
            ((OdPdfExportWithPrcExample)instance).PdfPath = app_args[1];
            break;
          }
        case OdPdfExportWithPrcSwigMgd_ExampleModes.None:
        default: return false;
      }

      return base.InitExample(instance);
    }

  }
}
