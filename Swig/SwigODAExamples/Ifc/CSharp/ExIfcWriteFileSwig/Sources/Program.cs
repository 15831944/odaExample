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
using ODA.Ifc.IfcCore;
using OdIfcExamplesLibMgd;
using ODA.Sdai.sdai;

namespace ExIfcWriteFileSwigMgd
{
  class Program
  {
    static Program()
    {
      OdCreationNetSwigExampleLib.Helpers.OdNetSmokeTest.Use();
    }

    private static String sUsage =
      "\n\nusage: ExIfcWriteFileSwigMgd <file_read_from> <file_write_to>" +
      "\n<file_read_from> - input .ifc file to read from\n" +
      "\n<file_write_to> - output .ifc file to write to\n";

    static void Main(string[] args)
    {
      if (args.Length < 2)
      {
        Console.WriteLine(sUsage);
        return;
      }

      String ifcFileNameFrom = args[0];
      String ifcFileNameTo = args[1];

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

      IfcCore_Globals.odIfcInitialize(false /* No CDA */, true /* No geometry calculation needed */);

      try
      {
        OdIfcFile pFileOrigin = services.m_HostAppServices.createDatabase(IfcSchema.kScmUndefined);
        OdResult res = pFileOrigin.readFile(ifcFileNameFrom);

        if (pFileOrigin == null)
        {
          Console.WriteLine("\nRead file error.");
        }

        if (pFileOrigin.writeFile(ifcFileNameTo) != OdResult.eOk)
        {
          Console.WriteLine("\nWrite file error.");
        }

        OdStreamBuf fileStreamCopy = Globals.odrxSystemServices().createFile(ifcFileNameTo, FileAccessMode.kFileRead);

        if (fileStreamCopy == null)
        {
          Console.WriteLine("\nCannot create a stream copy.");
        }

        OdMemoryStream memoryStreamCopy = OdMemoryStream.createNew();
        fileStreamCopy.rewind();
        fileStreamCopy.copyDataTo(memoryStreamCopy);

        OdIfcFile pFileCopy = services.m_HostAppServices.createDatabase(IfcSchema.kScmUndefined);
        pFileCopy.readFile(fileStreamCopy);

        bool compareResult = true;

        Console.WriteLine("\n\n[begin] header compare.");

        if (!OdIfcModelCompare.CompareHeaders(pFileOrigin.getHeaderSection(), pFileCopy.getHeaderSection()))
        {
          Console.WriteLine("\nHeader section data has a difference.");
          compareResult = false;
        }
        else
        {
          Console.WriteLine("\n[end] header compare.");
          Console.WriteLine("\n\n[begin] models compare.");

          OdDAI_Model pModelOrig = pFileOrigin.getModel();
          OdDAI_Model pModelCopy = pFileCopy.getModel();

          if (!OdIfcModelCompare.CompareModels(pModelOrig, pModelCopy))
          {
            Console.WriteLine("\nEntity section data has a difference.");
            compareResult = false;
          }
          else
          {
            Console.WriteLine("\n[end] models compare.");
          }
        }

        if (compareResult)
        {
          Console.WriteLine("\n\n[result] Rewrited file is equal to original.\n");
        }
        else
        {
          Console.WriteLine("\n\n[result] Rewrited file is NOT equal to original.\n");
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
