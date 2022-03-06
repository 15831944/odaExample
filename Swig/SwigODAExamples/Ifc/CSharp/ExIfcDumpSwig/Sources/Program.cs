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
using System.Text;
using Teigha.Core;
using System.IO;
using ODA.Sdai.sdai;
using ODA.Ifc.IfcCore;
using OdIfcExamplesLibMgd;

namespace ExIfcDumpSwigMgd
{
  class Program
  {
    static Program()
    {
      OdCreationNetSwigExampleLib.Helpers.OdNetSmokeTest.Use();
    }

    private static String sUsage =
    "\nExIfcDump sample program. Copyright (c) 2020, Open Design Alliance\n" +
    "\tusage: ExIfcDumpSwigMgd <source filename/start directory> <target dump filename> [<schema version>]\n" +
    "\tsupported schema versions: Ifc2x3, Ifc4, Ifc4x2, Any\n";

    static StreamWriter m_CurrentStaticDumper;

    static void customAssertFunc(String expr, String fileName, int nLine)
    {
      Console.Write("Assertion has occurs:\n" +
                    " Expression: {0}\n" +
                    " Filename: {1}\n" +
                    " Line number: {2}\n", expr, fileName, nLine);
      if (m_CurrentStaticDumper != null)
        m_CurrentStaticDumper.Write("{0} ({1}, line: {2})\n", expr, fileName, nLine);
    }

    static void Main(string[] args)
    {
      Globals.odSetAssertFunc(customAssertFunc);

      bool bInvalidArgs = args.Length < 2 || args.Length > 3;
      if (bInvalidArgs)
        bInvalidArgs = true;

      if (bInvalidArgs)
      {
        Console.WriteLine(sUsage);
        return;
      }

      /**********************************************************************/
      /* Start Root Memory Transaction                                      */
      /**********************************************************************/
      MemoryTransaction mTr = MemoryManager.GetMemoryManager().StartTransaction();

      OdIfcApplicationServicesSample services = new OdIfcApplicationServicesSample(ActivationData.userInfo, ActivationData.userSignature);

      /**********************************************************************/
      /* Initialize Runtime Extension environment                           */
      /**********************************************************************/
      Globals.odrxInitialize(services.m_SystemServices);

      Globals.odDbRootInitialize();

      IfcCore_Globals.odIfcInitialize(false /* No CDA */, false /* No geometry calculation needed */);

      try
      {
        String version = "ANY";
        if (args.Length == 3)
        {
          String strVersion = args[2];
          if (strVersion == "IFC2X3")
            version = "IFC2X3";
          else if (strVersion == "IFC4")
            version = "IFC4";
          else if (strVersion == "IFC4X2")
            version = "IFC4X2";
          else if (strVersion == "IFC4X3")
            version = "IFC4X3";
          else if (strVersion == "ANY")
          {
            Console.WriteLine("Unsupported file schema\n");
            return;
          }
        }

        String szSource = args[0], szDump = args[1];

        StreamWriter DumpStream = new StreamWriter(szDump);

        m_CurrentStaticDumper = DumpStream;

        DumpStream.Write(String.Format("Dump of {0}\n", szSource));
        DumpStream.Write(String.Format("\nResult file is {0}\n", szDump));

        /********************************************************************/
        /* Walk along file collection                                       */
        /********************************************************************/
        OdExIfcDumper dumper = new OdExIfcDumper(DumpStream);

        try
        {
          if (OdExIfcDumper.isDir(szSource))
          {
            dumper.WalkAlongDirectories(services.m_HostAppServices, szSource, version);
          }
          else
          {
            dumper.DumpFile(services.m_HostAppServices, szSource, version);
          }
        }
        catch (Exception err)
        {
          Console.WriteLine(err.Message);
        }
        finally
        {
          dumper.m_stats.writeToFile();
        }

        DumpStream.Flush();
        DumpStream.Close();
      }
      catch (OdError e)
      {
        Console.WriteLine(e.description());
      }
      catch (Exception err)
      {
        Console.WriteLine("\n\nUnexpected error. : {0}", err.Message);
      }
      finally
      {
        /**********************************************************************/
        /* Stop Root Memory Transaction                                      */
        /**********************************************************************/
        MemoryManager.GetMemoryManager().StopTransaction(mTr);
      }

      /**********************************************************************/
      /* Uninitialize Runtime Extension environment                         */
      /**********************************************************************/

      IfcCore_Globals.odIfcUninitialize();

      Globals.odDbRootUninitialize();

      Globals.odrxUninitialize();
    }
  }
}
