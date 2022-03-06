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
using System.Diagnostics;

namespace OdCreationNetSwigExampleLib
{
  public static class Helpers
  {
    public static void ODA_VERIFY(bool expr)
    {
      ODA_ASSERT(expr);
    }

    public static void ODA_ASSERT(bool expr)
    {
#if DEBUG
      Debug.Assert(expr);
#endif
    }

    /// <summary>
    /// Only internal functionality for smoke tests ODA .NET console applications
    /// </summary>
    public static class OdNetSmokeTest
    {
      private static bool bUsed = false;

      /// <summary>
      /// Initialize & use smoke test output
      /// </summary>
      public static void Use()
      {
        if (bUsed)
          return;
        bUsed = true;
        Init();
      }

      private static void Init()
      {
        StartExample();
        AppDomain.CurrentDomain.ProcessExit += ProcessExit;
      }

      private static void ProcessExit(object sender, EventArgs e)
      {
        AppDomain.CurrentDomain.ProcessExit -= ProcessExit;
        GC.Collect();
        GC.WaitForPendingFinalizers();
        FinishExample();
      }

      private static void StartExample()
      {
        Console.WriteLine("NET.SMOKE: Example started");
      }

      private static void FinishExample()
      {
        Console.WriteLine("NET.SMOKE: Example completed successfully");
      }
    }
  }
}
