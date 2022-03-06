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
using ODA.Ifc.BCF;

namespace ExBcfLoadFileSwigMgd
{
  class Program
  {
    static Program()
    {
      OdCreationNetSwigExampleLib.Helpers.OdNetSmokeTest.Use();
    }

    private static String sUsage =
    "\nExBcfLoadFileSwigMgd sample program. Copyright (c) 2020, Open Design Alliance\n" +
    "\tusage: ExBcfLoadFileSwigMgd <filename> <outfilename> [workfolder]\n" +
    "\t <filename> - BCF archive to open.\n" +
    "\t <outfilename> - write BCF file if outfilename is not empty.\n" +
    "\t [workfolder] - work folder for BCF archive content, optional.\n" +
    "\nPress ENTER to continue...\n";

    static void Main(string[] args)
    {
      Console.WriteLine("\nExBcfLoadFileSwigMgd sample program. Copyright (c) 2020, Open Design Alliance\n");

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

      BCF_Globals.odBcfInitialize();

      try
      {
        String fileName = args[0];
        String outFileName = args[1];
        String workFolder = args.Length > 2 ? args[2] : services.m_SystemServices.getTemporaryPath();


        OdBcf_OdBcfDataAccessor pAccessor = OdBcf_OdBcfDataAccessorXml.createObject(workFolder);
        OdBcf_OdBcfArchive pArchive = pAccessor.getArchive(fileName);
        String rootDir = pArchive.getRootDir().GetFolder();


        //
        // Dump topics
        //
        OdBcf_OdBcfTopicFolderMap topicFolders = pArchive.GetTopics();


        foreach (KeyValuePair<OdGUID, OdBcf_OdBcfTopicFolder> node in topicFolders)
        {
          String strGUID = node.Key.toString();
          Console.WriteLine("\nTopicFolder GUID: {0}\n", strGUID);

          OdBcf_OdBcfTopicFolder topicFolder = node.Value;

          OdBcf_OdBcfMarkup markup = topicFolder.GetMarkup();

          OdBcf_OdBcfTopic topic = markup.GetTopic();
          Console.WriteLine(" GUID: {0}\n", topic.getGuid().toString());
          Console.WriteLine(" Title: {0}\n", topic.GetTitle());
          Console.WriteLine(" Author: {0}\n", topic.getCreationAuthor());
          Console.WriteLine(" Priority: {0}\n", topic.GetPriority());

          OdBcf_OdBcfCommentArray comments = markup.GetComment();
          if (comments.Count > 0)
          {
            Console.WriteLine(" Comments ({0}):\n", comments.Count);
            foreach (OdBcf_OdBcfComment comment in comments)
            {
              // ...
            }
          }

          Console.WriteLine("==================================\n");

        }

        if (!String.IsNullOrEmpty(outFileName))
        {
          Console.WriteLine("Writing BCF Project to: {0}...", outFileName);
          if (OdResult.eOk == pAccessor.putArchive(outFileName, pArchive))
          {
            Console.WriteLine(" ok\n");
          }
          else
          {
            Console.WriteLine(" failed\n");
          }
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

      BCF_Globals.odBcfUninitialize();

      Globals.odDbRootUninitialize();

      Globals.odrxUninitialize();
    }
  }
}
