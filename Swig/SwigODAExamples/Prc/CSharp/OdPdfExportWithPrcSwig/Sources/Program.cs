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
using OdPdfExportWithPrcSwigMgd.Samples;
using Teigha.Core;
using Teigha.TD;

namespace OdPdfExportWithPrcSwigMgd
{
  class Program
  {
    static Program()
    {
      OdCreationNetSwigExampleLib.Helpers.OdNetSmokeTest.Use();
    }

    static void Main(string[] args)
    {
      MemoryManager mMan = MemoryManager.GetMemoryManager();
      MemoryTransaction mStartTrans = mMan.StartTransaction();

      SystemServices systemServices = new SystemServices();
      ExHostAppServices hostApp = new ExHostAppServices();

      TD_Db.odInitialize(systemServices);

      Console.WriteLine("OdPdfExportWithPrcSwigMgd developed using {0} ver {1}", hostApp.product(), hostApp.versionString());

      OdPdfExportWithPrcSwigMgd_ApplicationInterface appInterface = new OdPdfExportWithPrcSwigMgd_ApplicationInterface(hostApp, args);

      try
      {
        Example example = appInterface.CreateExampleInstance();
        if (example != null)
        {
          if (example.CheckInputApplicationParams())
            example.Run();
          else
            appInterface.ShowCorrectInputParams();
        }
        else
          appInterface.ShowCorrectInputParams();
      }
      catch (OdError e)
      {
        Console.WriteLine("Example OdError: " + e.description());
      }
      catch (Exception ex)
      {
        Console.WriteLine("Other example error: " + ex.Message);
      }

      mMan.StopTransaction(mStartTrans);

      try
      {
        TD_Db.odUninitialize();
      }
      catch (OdError e)
      {
        Console.WriteLine("Cleanup OdError: " + e.description());
      }
      catch (Exception ex)
      {
        Console.WriteLine("Other cleanup error: " + ex.Message);
      }
      Teigha.Core.Helpers.odUninit();

      mMan.StopAll();
    }
  }
}
