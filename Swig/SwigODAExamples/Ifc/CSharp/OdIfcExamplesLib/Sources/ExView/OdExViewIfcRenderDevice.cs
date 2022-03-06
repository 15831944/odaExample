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


using ODA.Ifc.IfcCore;
using OdKernelExamplesMgdLib.ExView;
using System;
using Teigha.Core;

namespace OdIfcExamplesLibMgd
{
  /// <summary>
  /// This example specific render device. In this case for rendering OdIfcFile
  /// Class contains overrides methods for creation specific render device
  /// </summary>
  public class OdExViewIfcRenderDevice : OdExViewProductRenderDeviceBase
  {

    /// <summary>
    /// Creation instance with specific graphics module type
    /// </summary>
    /// <param name="gsModule"></param>
    public OdExViewIfcRenderDevice(OdExGsDeviceCreator.OdExGsModuleType gsModule) : base(gsModule)
    { }

    /// <summary>
    /// Creation instance with by default graphics module type.
    /// Module type by default WinGLES2.
    /// </summary>
    public OdExViewIfcRenderDevice() : this(OdExGsDeviceCreator.OdExGsModuleType.ExVisualizeDevice)
    {
    }

    public override void InitRenderDevice(OdRxObject database)
    {
      m_Database = database;
      try
      {
        m_GsDevice = Create_GsDeviceFromGsModule();

        OdGiContext giContext = Create_GiContext();

        m_GsDevice = CreateGsDevice(m_GsDevice, giContext);

        SetupColorPalette();

        OdIfcFile pDatabase = OdIfcFile.cast(m_Database);
        pDatabase.setContextSelection(IfcCore_Globals.OdIfc_Utils_getDefaultRepresentationContextsSelection(pDatabase, false));

        //Initial set Size
        ActiveView().setMode(m_RenderMode);
        ActiveView().setView(new OdGePoint3d(1, 1, 1), new OdGePoint3d(0, 0, 0), OdGeVector3d.kZAxis, 1000, 1000);
        OnSizeDevice();

        OnZoomToExtents(m_Database);

        //Initial update
        UpdateGsDevice();

      }
      catch (Exception ex)
      {
        UnInitRenderDevice();
        throw new Exception(String.Format("Error Initialize Rendering Device: {0}", ex.Message));
      }
    }

    /// <summary>
    /// Creation graphic context is according to database of OdIfcFile type
    /// </summary>
    /// <returns></returns>
    protected override OdGiContext Create_GiContext()
    {
      OdGiContextForIfcDatabase ctx = OdGiContextForIfcDatabase.createObject();
      OdIfcFile database = OdIfcFile.cast(m_Database);
      ctx.setDatabase(database);
      ctx.enableGsModel(true);
      return ctx;
    }

    /// <summary>
    /// Creation specific graphics layout helper is according to database of OdIfcFile type
    /// </summary>
    /// <param name="gsDevice"></param>
    /// <param name="giContext"></param>
    /// <returns></returns>
    protected override OdGsDevice CreateGsDevice(OdGsDevice gsDevice, OdGiContext giContext)
    {
      OdGiContextForIfcDatabase ifcCtx = OdGiContextForIfcDatabase.cast(giContext);
      OdGsIfcLayoutHelper hDevice = IfcCore_Globals.OdIfcGsManager_setupActiveLayoutViews(gsDevice, ifcCtx);

      // Set the device background color and palette
      UInt32[] CurPalette = Teigha.Core.AllPalettes.getLightPalette();
      hDevice.setBackgroundColor(CurPalette[0]);
      ifcCtx.setPaletteBackground(CurPalette[0]);
      hDevice.setLogicalPalette(CurPalette, 256);

      return hDevice;
    }

    /// <summary>
    /// Get Active view from GsDevice for ifc database
    /// </summary>
    /// <returns></returns>
    protected override OdGsView ActiveView()
    {
      OdGsIfcLayoutHelper gsHelper = OdGsIfcLayoutHelper.cast(m_GsDevice);
      return gsHelper.activeView();
    }

    /// <summary>
    /// Example zoom to extents for database of OdIfcFile type
    /// </summary>
    /// <param name="database"></param>
    protected override void OnZoomToExtents(OdRxObject database)
    {
      OdGsView view = ActiveView();
      OdAbstractViewPE pVpPE = OdAbstractViewPE.cast(view);
      pVpPE.zoomExtents(view);
    }

  }

}