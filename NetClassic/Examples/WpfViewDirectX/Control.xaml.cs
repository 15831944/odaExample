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
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Controls;
using Brushes = System.Windows.Media.Brushes;
using System.Windows;
using System.Windows.Interop;
using Size = System.Windows.Size;
using System.Windows.Media.Imaging;
using Teigha;
using Teigha.DatabaseServices;
using Teigha.GraphicsInterface;
using Teigha.GraphicsSystem;
using Teigha.Runtime;

namespace WpfViewDirectX
{

  public partial class Control : UserControl
  {
    Window HiddenWindowForRendering; // use this as surface for drawing
    public WpfViewDirectXD3DImage d3dImage;
    public Database database;
    WpfViewDevice device;

    public Control()
    {
      InitializeComponent();
      drawImage.Source = GetOdaLogo();
      device = new WpfViewDevice();
      d3dImage = new WpfViewDirectXD3DImage();
    }

    public void Initialize(Database database)
    {
      this.database = database;
      device.Initialize(this);
      d3dImage.Initialize(device.graphichsDevice);
      Resize();
      drawImage.Source = d3dImage;
    }

    /// <summary>
    /// Creates or returns the window, on which device will draw its image.
    /// </summary>
    public HwndSource GetHwndSourceOfHiddenWindowForRendering()
    {
      if (HiddenWindowForRendering == null)
      {
        HiddenWindowForRendering = new Window();
        HiddenWindowForRendering.Owner = Application.Current.MainWindow;
        HiddenWindowForRendering.Visibility = System.Windows.Visibility.Hidden;
        HiddenWindowForRendering.WindowStyle = System.Windows.WindowStyle.None;
        HiddenWindowForRendering.ShowInTaskbar = false;
        HiddenWindowForRendering.Background = Brushes.Transparent;
        HiddenWindowForRendering.AllowsTransparency = true;
        HiddenWindowForRendering.Show();
        HiddenWindowForRendering.Hide();
      }
      return HwndSource.FromVisual(HiddenWindowForRendering) as HwndSource;
    }

    /// <summary>
    /// Closes opened resources and prepares fields
    /// so control can be used again for another drawing database.
    /// Expected to be called before opening another dwg file.
    /// Must be called before database dispose, otherwise will not exit properly.
    /// </summary>
    public void Reinitialize()
    {
      if (device != null)
      {
        device.Deinitialize();
        device = new WpfViewDevice();
      }

      if (d3dImage != null)
      {
        d3dImage.Deinitialize();
        d3dImage = new WpfViewDirectXD3DImage();
      }
    }

    public void Update()
    {
      device.graphichsDevice.Update();
    }

    /// <summary>
    /// Frees resources in correct order and prepares control for being permanently deleted.
    /// Expected to be called before window closes.
    /// Must be called before database dispose, otherwise will not exit properly.
    /// </summary>
    public void Deinitialize()
    {
      if (device != null)
      {
        device.Deinitialize();
        device = null;
      }
        
      if (d3dImage != null)
      {
        d3dImage.Deinitialize();
        d3dImage = null;
      }
    }

    /// <summary>
    /// Updates device and drawing surface according to new size of window.
    /// </summary>
    public void Resize()
    {
      if (device == null || d3dImage == null || device.graphichsDevice == null)
        return;

      d3dImage.ClearBackBufferAndSurface();

      device.graphichsDevice.OnSize(GetControlSize());
      device.graphichsDevice.Update();

      d3dImage.UpdateSurface();
    }

    private System.Drawing.Size GetControlSize()
    {
      Size rect = RenderSize;
      System.Drawing.Size rectInt = new System.Drawing.Size((int)rect.Width, (int)rect.Height);
      return rectInt;
    }

    /// <summary>
    /// Returns ODA logo image to use it as background when no dwg file is opened.
    /// </summary>
    /// <returns></returns>
    private static BitmapSource GetOdaLogo()
    {
      BitmapSource bitmapSource;
      try
      {
        System.Drawing.Bitmap bitmap = WpfViewDirectX.Resources.oda_logo;

        bitmapSource = System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(
          bitmap.GetHbitmap(),
          IntPtr.Zero,
          System.Windows.Int32Rect.Empty,
          BitmapSizeOptions.FromWidthAndHeight(bitmap.Width, bitmap.Height));
      }
      #pragma warning disable 0168
      catch (System.Exception ex) // look at ex in debugger
      {
        bitmapSource = null;
      }
      #pragma warning restore 0168

      return bitmapSource;
    }
    private void UserControl_SizeChanged(object sender, SizeChangedEventArgs e)
    {
      Resize();
    }
  }

}
