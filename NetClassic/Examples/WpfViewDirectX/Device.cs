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
using System.Windows;
using System.Windows.Interop;
using Teigha.DatabaseServices;
using Teigha.GraphicsInterface;
using Teigha.GraphicsSystem;
using Teigha.Runtime;

namespace WpfViewDirectX
{
  public class WpfViewDevice
  {
    public Device graphichsDevice;
    LayoutHelperDevice layoutHelperDevice;
    Control drawControl;

    public WpfViewDevice()
    {
    }

    public void Initialize(Control drawControl)
    {
      this.drawControl = drawControl;

      try
      {
        // load some predefined rendering module (may be also "WinDirectX" or "WinOpenGL")
        GsModule gsModule = (GsModule)SystemObjects.DynamicLinker.LoadModule("WinDirectX.txv", false, true);

        // create graphics device
        graphichsDevice = gsModule.CreateDevice();

        // create or get hidden window, so that OdGsDevice render the model on window
        IntPtr renderWindow = drawControl.GetHwndSourceOfHiddenWindowForRendering().Handle;

        // setup device properties
        using (Dictionary props = graphichsDevice.Properties)
        {
          if (props.Contains("WindowHWND")) // Check if property is supported
            props.AtPut("WindowHWND", new RxVariant(renderWindow)); // hWnd necessary for DirectX device
          if (props.Contains("DoubleBufferEnabled")) // Check if property is supported
            props.AtPut("DoubleBufferEnabled", new RxVariant(true));
          if (props.Contains("DiscardBackFaces")) // Check if property is supported
            props.AtPut("DiscardBackFaces", new RxVariant(true));
          // Enable scene graph usage onto renderer side
          if (props.Contains("UseSceneGraph")) // Check if property is supported
            props.AtPut("UseSceneGraph", new RxVariant(true));
          if (props.Contains("UseVisualStyles")) // Check if property is supported
            props.AtPut("UseVisualStyles", new RxVariant(true));
        }

        // setup paperspace viewports or tiles
        using (ContextForDbDatabase ctx = new ContextForDbDatabase(drawControl.database))
        {
          ctx.UseGsModel = true;
          layoutHelperDevice = LayoutHelperDevice.SetupActiveLayoutViews(graphichsDevice, ctx);
        }

        // set palette
        layoutHelperDevice.SetLogicalPalette(Device.DarkPalette);

        // call initial update size
        drawControl.Resize();
      }
      catch (System.Exception ex)
      {
        MessageBox.Show(ex.ToString());
      }
    }

    public void Deinitialize()
    {
      // ensure that deinitialization is happening in correct order
      if (layoutHelperDevice != null)
      {
        layoutHelperDevice.Dispose();
        layoutHelperDevice = null;
      }
      if (graphichsDevice != null)
      {
        graphichsDevice.Dispose();
        graphichsDevice = null;
      }
    }
  }
  
}
