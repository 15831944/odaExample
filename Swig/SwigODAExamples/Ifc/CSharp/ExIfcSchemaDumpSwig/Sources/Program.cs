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

namespace ExIfcSchemaDumpSwigMgd
{
  class Program
  {
    static Program()
    {
      OdCreationNetSwigExampleLib.Helpers.OdNetSmokeTest.Use();
    }

    private static String sUsage =
    "\nExIfcSchemaDumpSwigMgd sample program. Copyright (c) 2020, Open Design Alliance\n" +
    "\tusage: ExIfcSchemaDump <target dump filename> <schema version>\n" +
    "\tsupported schema versions: Ifc2x3, Ifc4, Ifc4x2\n";



    static void Main(string[] args)
    {
      Console.WriteLine("\nExIfcSchemaDumpSwigMgd sample program. Copyright (c) 2020, Open Design Alliance\n");

      bool bInvalidArgs = (args.Length != 2);
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
        String wDump = args[0];
        String wSchemaName = args[1];

        StreamWriter DumpStream = new StreamWriter(wDump);

        OdExIfcShemaDumper dumper = new OdExIfcShemaDumper(DumpStream);

        OdDAI_Schema pSchema = sdai_Globals.oddaiGetSchema(wSchemaName);
        if (pSchema != null)
        {
          DumpStream.Write("SCHEMA {0};\n\n", pSchema.name());

          dumper.dumpTypes(pSchema.Types());
          dumper.dumpEntities(pSchema.Entities());

          DumpStream.Write("END_SCHEMA;");

          DumpStream.Flush();
          DumpStream.Close();
        }
        else
        {
          DumpStream.Write("Schema {0} is unsupported yet.\n\n", wSchemaName);
        }

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
