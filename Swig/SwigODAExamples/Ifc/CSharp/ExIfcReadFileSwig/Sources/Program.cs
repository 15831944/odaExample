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
using ODA.Sdai.zipio;
using OdIfcExamplesLibMgd;

namespace ExIfcReadFileSwigMgd
{
  class Program
  {
    static Program()
    {
      OdCreationNetSwigExampleLib.Helpers.OdNetSmokeTest.Use();
    }

    private static String sUsage =
      "Usage: ExIfcReadFileSwigMgd <in filename> [out filename]\n" +
      "  <filename> - input .ifc or .ifczip file\n" +
      "  [out filename] - optional output .ifc or .ifczip file\n" +
      "\nPress ENTER to continue...\n";

    static void Main(string[] args)
    {
      Console.WriteLine("\nExIfcReadFileSwigMgd sample program. Copyright (c) 2020, Open Design Alliance\n");

      bool bInvalidArgs = (args.Length != 1 && args.Length != 2);
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
        String ifcInFileName = args[0];
        String ifcOutFileName = null;
        if (args.Length == 2)
          ifcOutFileName = args[1];

        bool isZip = Path.GetExtension(ifcInFileName) == ".ifczip";

        OdDAI_Repository pRepository = null;
        OdIfcFile pDatabase = null;

        {
          OdPerfTimerWrapper timerWrapper = new OdPerfTimerWrapper();
          timerWrapper.getTimer().start();
          OdResult res;

          if (isZip)
          {
            pRepository = OdDAI_Repository.createObject();
            OdRxModule module = Globals.odrxDynamicLinker().loadModule("ZipIO", true);
            OdZipIO_OdZipIOModule pZipIOModule = new OdZipIO_OdZipIOModule(OdRxModule.getCPtr(module).Handle, false);
            OdZipIO_OdZipIODiskFolder pDiskFolder = null;
            res = pZipIOModule.deserialize(ifcInFileName, pRepository, ref pDiskFolder);
          }
          else
          {
            pDatabase = services.m_HostAppServices.createDatabase(IfcSchema.kScmUndefined);
            res = pDatabase.readFile(ifcInFileName);
          }

          timerWrapper.getTimer().stop();
          if (res == OdResult.eOk)
          {
            Console.WriteLine("\nFile opened successfully.");
          }
          else
          {
            Console.WriteLine("\nFile open error.");
          }
          Console.WriteLine("\nOpening time: {0} msec", timerWrapper.getTimer().countedMSec());
        }

        if (!String.IsNullOrEmpty(ifcOutFileName))
        {
          OdPerfTimerWrapper timerWrapper = new OdPerfTimerWrapper();
          timerWrapper.getTimer().start();
          OdResult res;

          if (isZip)
          {
            OdRxModule module = Globals.odrxDynamicLinker().loadModule("ZipIO", true);
            OdZipIO_OdZipIOModule pZipIOModule = new OdZipIO_OdZipIOModule(OdRxModule.getCPtr(module).Handle, false);
            res = pZipIOModule.serialize(ifcOutFileName, pRepository);
          }
          else
          {
            res = pDatabase.writeFile(ifcOutFileName);
          }

          timerWrapper.getTimer().stop();
          if (res == OdResult.eOk)
          {
            Console.WriteLine("\nFile writed successfully.");
          }
          else
          {
            Console.WriteLine("\nFile writing error.");
          }
          Console.WriteLine("\nWriting time: {0} msec", timerWrapper.getTimer().countedMSec());
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
