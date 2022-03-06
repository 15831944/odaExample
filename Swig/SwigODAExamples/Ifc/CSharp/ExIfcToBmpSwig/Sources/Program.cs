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

namespace OdExPointCloudConverterSampleSwig
{
  class Program
  {
    static Program()
    {
      OdCreationNetSwigExampleLib.Helpers.OdNetSmokeTest.Use();
    }

    private static String sUsage =
      "\n\tusage: ExIfcToBmpSwigMgd <source file> <destination file> [-DO]\n" +
      "\n\t-DO disables progress meter output.\n";

    static void Main(string[] args)
    {
      if (args.Length < 2)
      {
        Console.WriteLine(sUsage);
        return;
      }

      String srcFileName = args[0];
      String dstFileName = args[1];

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
        OdIfcFile pDatabase = services.m_HostAppServices.createDatabase(IfcSchema.kScmUndefined);

        if (pDatabase.readFile(srcFileName) != OdResult.eOk)
        {
          throw new OdError(OdResult.eCantOpenFile);
        }

        OdResult res = pDatabase.composeEntities();
        if (res != OdResult.eOk)
        {
          if (res == OdResult.eFileInternalErr)
          {
            throw new OdError(OdResult.eFileInternalErr);
          }
          if (res == OdResult.eNullPtr)
          {
            throw new OdError(OdResult.eNullPtr);
          }
        }

        OdGsModule module = (OdGsModule)Globals.odrxDynamicLinker().loadModule("WinBitmap.txv");
        if (module == null)
          module = (OdGsModule)Globals.odrxDynamicLinker().loadModule("WinGDI.txv");
        if (module == null)
          throw new Exception("Cannot load Gs module");

        OdGsDevice pBitmapDevice = module.createBitmapDevice();

        {
          OdGiContextForIfcDatabase pIfcContext = OdGiContextForIfcDatabase.createObject();

          pIfcContext.setDatabase(pDatabase);
          pIfcContext.enableGsModel(true);

          OdGsDevice pDevice = IfcCore_Globals.OdIfcGsManager_setupActiveLayoutViews(pBitmapDevice, pIfcContext);
          OdGsView pView = pDevice.viewAt(0);

          pView.setMode(OdGsView.RenderMode.kHiddenLine);
          pView.setView(new OdGePoint3d(1, 1, 1), new OdGePoint3d(0, 0, 0), OdGeVector3d.kZAxis, 1000, 1000);
          pDatabase.setContextSelection(IfcCore_Globals.OdIfc_Utils_getDefaultRepresentationContextsSelection(pDatabase, false));

          UInt32[] CurPalette = Teigha.Core.AllPalettes.getLightPalette();
          pDevice.setBackgroundColor(CurPalette[0]);
          pIfcContext.setPaletteBackground(CurPalette[0]);
          pDevice.setLogicalPalette(CurPalette, 256);

          OdGsDCRect screenRect = new OdGsDCRect(new OdGsDCPoint(0, 768), new OdGsDCPoint(1024, 0));

          pDevice.onSize(screenRect);
          pDevice.properties().putAt("BitPerPixel", new OdRxVariantValue((UInt32)24));
          OdAbstractViewPE pVpPE = OdAbstractViewPE.cast(pView);
          pVpPE.zoomExtents(pView);
          pDevice.update();

          OdGiRasterImage ptrImage = OdGiRasterImage.cast(pDevice.properties().getAt("RasterImage"));
          OdRxRasterServices pRasSvcs = (OdRxRasterServices)Teigha.Core.Globals.odrxDynamicLinker().loadApp("RxRasterServices");
          if (pRasSvcs == null)
            throw new Exception("Failed to load RxRasterServices module");

          bool statusSave = pRasSvcs.saveRasterImage(ptrImage, dstFileName);

          if (!statusSave)
            throw new Exception("Failed save image operation");
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
