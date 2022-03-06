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
using Teigha.Core;
using ODA.Sdai.sdai;
using ODA.Ifc.IfcCore;
using ODA.Ifc.IfcGeom;
using OdIfcExamplesLibMgd;

namespace ExIfcAccess2RepBodyGeoSwigMgd
{
  class Program
  {
    static Program()
    {
      OdCreationNetSwigExampleLib.Helpers.OdNetSmokeTest.Use();
    }

    private static String sUsage =
    "\nExIfcAccess2RepBodyGeoSwigMgd sample program. Copyright (c) 2021, Open Design Alliance\n" +
    "\tusage: ExIfcAccess2RepBodyGeoSwigMgd <filename>" +
    "\t <filename> - input ifc filepath.\n" +
    "\nPress ENTER to continue...\n";

    static void Main(string[] args)
    {
      Console.WriteLine("\nExIfcAccess2RepBodyGeoSwigMgd sample program. Copyright (c) 2021, Open Design Alliance\n");

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

      IfcCore_Globals.odIfcInitialize(false /* No CDA */, true /* No geometry calculation needed */, ModelerType.kFacetModeler);

      try
      {
        String ifcFileName = (args[0]);

        Console.WriteLine("\nDump {0}.\n", ifcFileName);

        OdIfcFile pFile = services.m_HostAppServices.createDatabase();
        OdResult res = pFile.readFile(ifcFileName);

        if (res == OdResult.eOk)
          Console.WriteLine("\nFile opened successfully.\n");
        else
          throw new OdError_CantOpenFile(ifcFileName);

        res = pFile.composeEntities();

        if (res == OdResult.eOk)
          Console.WriteLine("\nCompose Entities successfully.\n");
        else
          throw new OdError(res);

        OdDAI_Model pModel = pFile.getModel();

        if (pModel == null)
          throw new OdError("An unexpected error occurred while opening the IFC file!");

        OdDAI_OdDAIObjectIdSet productIdSet = pModel.getEntityExtent("IfcProduct");
        if (productIdSet == null)
          throw new OdError("productIdSet is null");

        OdDAIObjectIds productIds = productIdSet.getArray();

        for (int iProduct = 0; iProduct < productIds.Count; ++iProduct)
        {
          OdIfc_OdIfcEntity pEntity = OdIfc_OdIfcEntity.cast(productIds[iProduct].openObject());
          if (pEntity == null)
            continue;

          OdIfc_OdIfcCompound pCompound = OdIfc_OdIfcEntity.asCompound(pEntity);
          if (pCompound == null)
            continue;

          OdIfc_OdIfcProduct pProduct = OdIfc_OdIfcProduct.cast(pCompound);
          if (pProduct == null)
            continue;

          OdIfc_OdIfcGeometricRepresentationItemPtrArray geomItems = pProduct.getGeometricRepresentationItems();

          for (int iItem = 0; iItem < geomItems.Count; ++iItem)
          {
            OdIfc_OdIfcGeometricRepresentationItem pGeomItem = geomItems[iItem];
            OdIfc_OdIfcBodyVariant bodyContainer = pGeomItem.bodyContainer();

            // Don't save object from bodyContainer. The object make sense only at this place. Body should be copied if needed to use it later.
            switch (bodyContainer.kind())
            {
              case OdIfc_OdIfcBodyVariant.Type.kFacetModelerBody:
                {
                  Console.WriteLine("BodyContainer kind of {0} Not Implemented . Details here: https://jira.opendesign.com/browse/SWIG-1153", bodyContainer.kind().ToString());
                  break;
                }

              case OdIfc_OdIfcBodyVariant.Type.kMdBody:
                {
                  Console.WriteLine("BodyContainer kind of {0} Not Implemented . Details here: https://jira.opendesign.com/browse/SWIG-1153", bodyContainer.kind().ToString());
                  break;
                }

              case OdIfc_OdIfcBodyVariant.Type.kAcisBody:
                {
                  Console.WriteLine("BodyContainer kind of {0} Not Implemented . Details here: https://jira.opendesign.com/browse/SWIG-1153", bodyContainer.kind().ToString());
                  break;
                }

              case OdIfc_OdIfcBodyVariant.Type.kIfcBrep:
                {
                  OdBrBrep brep = bodyContainer.ifcBrep();
                  Console.WriteLine("Found IfcBrep");
                  break;
                }
            }
            // bodyContainer may not contain a body. For example, when underlying geometry is curve.
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

      IfcCore_Globals.odIfcUninitialize();

      Globals.odDbRootUninitialize();

      Globals.odrxUninitialize();
    }
  }
}
