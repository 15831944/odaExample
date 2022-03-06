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

namespace ExIfcExtractDataSwigMgd
{
  class Program
  {
    static Program()
    {
      OdCreationNetSwigExampleLib.Helpers.OdNetSmokeTest.Use();
    }

    private static String sUsage =
      "\n\nusage: ExIfcExtractDataSwigMgd " +
      "\n a full path to the input IFC file\n";

    static void Main(string[] args)
    {
      bool bInvalidArgs = (args.Length != 1);
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
        OdIfcFile pFile;
        String ifcFileName = (args[0]);

        Console.WriteLine("\nDump {0}.\n", ifcFileName);

        pFile = services.m_HostAppServices.createDatabase();
        OdResult res = pFile.readFile(ifcFileName);

        if (res == OdResult.eOk)
        {
          Console.WriteLine("\nFile opened successfully.\n");
        }
        else
        {
          Console.WriteLine("\nFile open error.");
          return;
        }

        OdDAI_OdHeaderSection headerSection = pFile.getHeaderSection();

        if (headerSection == null)
        {
          Console.WriteLine("\nError getting header section from the {0} file!", ifcFileName);
          return;
        }

        OdDAI_FileSchema pFileSchema = OdDAI_FileSchema.cast(headerSection.getEntityByType(OdDAI_OdHeaderEntityType.kFileSchema));

        OdAnsiStringArray schemaIdentifiers = new OdAnsiStringArray();
        pFileSchema.getSchemaIdentifiers(schemaIdentifiers);
        //or: pFileSchema.getAttr("schema_identifiers") >> schemaIdentifiers;
        String schemaName = schemaIdentifiers[0];

        if (schemaName != "IFC2X3" && schemaName != "IFC4" && schemaName != "IFC4X2")
        {
          Console.WriteLine("\nUnsupported file schema: {0}!", schemaName);
          return;
        }

        OdDAI_Model pModel = pFile.getModel();

        if (pModel == null)
        {
          Console.WriteLine("\nAn unexpected error occurred while opening the IFC file!");
          return;
        }

        Console.WriteLine("Model entities (schema name is \"{0}\"): \n", schemaName);

        OdDAI_InstanceIterator it = pModel.newIterator();
        OdIfc_OdIfcEntity pInst;

        OdExIfcEntityDumper dumper = new OdExIfcEntityDumper();
        uint entIdx;
        for (entIdx = 0; !it.done(); it.step(), ++entIdx)
        {
          //opens an entity
          pInst = OdIfc_OdIfcEntity.cast(it.id().openObject());

          if (pInst != null)
          {
            UInt64 id = OdRxValueHelper.rxvalue_cast<UInt64>(pInst.getAttr("_id"));

            String typeNameW = pInst.typeName();
            OdDAI_Entity pEntityDef = pInst.getInstanceType();

            Console.WriteLine("Entity {0}: \n", entIdx);
            Console.WriteLine("\tEntity handle (corresponds to the STEP-id) ={0}\n", id);
            Console.WriteLine("\tEntity type name = {0} (enum = {1})\n", typeNameW, pInst.type());
            dumper.dumpEntity(pInst, pEntityDef);

            if (pInst.isKindOf("ifcroot"))
              Console.WriteLine("\tDerived from IfcRoot!\n");
          }
        }

        Console.WriteLine("Found entities: {0}\n", entIdx);
        Console.WriteLine("Inverse aggregates: {0}\n", dumper.inverse_aggregates);
        Console.WriteLine("Empty inverse aggregates: {0}\n", dumper.empty_inverse_aggregates);
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
