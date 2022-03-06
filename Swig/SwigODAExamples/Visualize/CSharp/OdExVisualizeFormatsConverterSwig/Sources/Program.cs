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
using System.Text;
using Teigha.Core;
using Teigha.Visualize;

namespace OdExVisualizeFormatsConverterSwig
{
  class Program
  {
    static Program()
    {
      OdCreationNetSwigExampleLib.Helpers.OdNetSmokeTest.Use();
    }

    private static String GetUsage()
    {
      String none = Enum.GetName(typeof(OdExVisualizeConverterType), OdExVisualizeConverterType.None);

      StringBuilder sBuilder = new StringBuilder();
      sBuilder.Append("Usage: OdExVisualizeFormatsConverterSwig <convertType> <in_filePath> <out_filePath>\n");
      sBuilder.Append("  <convertType>  - can be :\n");
      foreach (string typeName in Enum.GetNames(typeof(OdExVisualizeConverterType)))
      {
        if (typeName == none)
          continue;
        sBuilder.Append(String.Format("                     {0}\n", typeName));
      }
      sBuilder.Append("  <in_filePath>  - full path to the input file\n");
      sBuilder.Append("  <out_filePath>  - full path to the output file\n");
      sBuilder.Append("\nPress ENTER to continue...\n");
      return sBuilder.ToString();
    }

    public enum OdExVisualizeConverterType
    {
      None = 0,
      DWG2OBJ,
      OBJ2DWG,
    }

    static void Main(string[] args)
    {
      if (args.Length < 3)
      {
        Console.Write(GetUsage());
        return;
      }

      OdExVisualizeConverterType convertType = OdExVisualizeConverterType.None;
      try { convertType = (OdExVisualizeConverterType)Enum.Parse(typeof(OdExVisualizeConverterType), args[0], true); }
      catch
      {
        Console.Write(GetUsage());
        return;
      }

      String inFilePath = args[1], outFilePath = args[2];

      /**********************************************************************/
      /* Start Root Memory Transaction                                      */
      /**********************************************************************/
      MemoryTransaction mTr = MemoryManager.GetMemoryManager().StartTransaction();

      /**********************************************************************/
      /* Activation ODA SDK                                                 */
      /**********************************************************************/
      Teigha.Core.Globals.odActivate(ActivationData.userInfo, ActivationData.userSignature);

      /**********************************************************************/
      /* Initialize Runtime Extension environment                           */
      /**********************************************************************/
      TV_Globals.odTvInitialize();

      try
      {
        OdExVisualizeConverterBase converterExample = null;

        switch (convertType)
        {
          case OdExVisualizeConverterType.DWG2OBJ: converterExample = new OdExVisualizeDwgToObjConverter(inFilePath, outFilePath); break;
          case OdExVisualizeConverterType.OBJ2DWG: converterExample = new OdExVisualizeObjToDwgConverter(inFilePath, outFilePath); break;
          case OdExVisualizeConverterType.None:
          default:
            throw new OdError("Convert type not defined or example not implemented");
        }
       
        converterExample.Convert();
      }
      catch (OdError e)
      {
        Console.WriteLine(e.description());
      }
      catch(Exception e)
      {
        Console.WriteLine(e.Message);
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
      TV_Globals.odTvUninitialize();
      Teigha.Core.Globals.odCleanUpStaticData();
    }
  }
}